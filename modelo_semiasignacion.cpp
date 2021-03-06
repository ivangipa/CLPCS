#pragma warning(disable:4786)

#include "Container.h"
#include "LPCPLEX2.h"
#include <assert.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <ilconcert/ilolinear.h>


void LPCPLEX::modelo_semiasignacion(CONTAINER* contenedor)
{

	double value2;
	model = IloModel(env);
	IloRangeArray restr(env);
	int maxtime = 1;
	IloNum max_time = maxtime; //tiempo del modelo

	char nombre[20];
	std::vector<int> ind;
	for (int i = 0; i < (*contenedor).Get_num_pedidos(); i++)
	{
		if ((*contenedor).Get_Pedidos()[i].Get_complete() == false)
			ind.push_back(i);
	}

	int numpedido = ind.size();
	/*for (int i = 0; i < ind.size(); i++)
		printf("%d\n", ind[i]);*/
	int numtiposcaja = (*contenedor).Get_Q();
	//Cajas del tipo j que tiene el pedido i
	std::vector<std::vector<int> > n_ij;
	for (int i = 0; i < numpedido; i++)
		n_ij.push_back((*contenedor).Get_Pedidos()[ind[i]].Get_num_pieces_tipo());
	//Cajas del tipo j en la soluci�n que no pertenecen a pedidos completos por la asignaci�n completa
	std::vector<int> n_j;
	/*for (int j = 0; j < numtiposcaja; j++)
		n_j.push_back(0);
	for (int i = 0; i < (*contenedor).Get_num_pedidos(); i++)
	{
		if ((*contenedor).Get_Pedidos()[i].Get_complete() == true)
		{
			for (int j = 0; j < numtiposcaja; j++)
				n_j[j] += (*contenedor).Get_Pedidos()[i].Get_num_pieces_tipo()[j];
		}
	}*/
	for (int j = 0; j < numtiposcaja; j++)
	{
		n_j.push_back((((*contenedor).Get_unasigned())[j]));
		/*for (int i = 0; i < numpedido; i++)
		{
			if ((*contenedor).Get_Pedidos()[i].Get_complete() == false)
				n_j.push_back(min((*contenedor).Get_Piezas()[j].Get_Num(), (*contenedor).Get_Pedidos()[i].Get_num_pieces_tipo()[j]));
		}*/
		/*printf("%d\t", n_j[j]);*/
	}
	/*printf("\n");*/
	//Volumen del pedido i
	std::vector<int> v_i;
	for (int i = 0; i < numpedido; i++)
		v_i.push_back((((*contenedor).Get_Pedidos())[ind[i]]).Get_Volumen());
	/*printf("v_i=\t");
	for (int i = 0; i < v_i.size(); i++)
		printf("%d\t", v_i[i]);
	printf("\n");*/
	/*printf("n_j=\t");
	for (int j = 0; j < n_j.size(); j++)
		printf("%d:\t%d\n", j, n_j[j]);*/
	/*printf("\n");*/
	/*printf("n_ij=\t");
	for (int i = 0; i < numpedido; i++)
	{
		for (int j = 0; j < numtiposcaja; j++)
			printf("%d\t", n_ij[i][j]);
		printf("\n");
	}*/

	//Creo las variables
	NumVarMatrix2 x_ij(env, numpedido);
	NumVector z_i(env);

	/**********************************************************/
	/***************** INICIALIZO VARIABLES *******************/
	/**********************************************************/

	//inicializo la variable Z_i
	z_i = IloIntVarArray(env, numpedido, 0, 1);
	for (int i = 0; i < numpedido; i++)
	{
		sprintf(nombre, "Z%d", i);
		z_i[i].setName(nombre);
	}


	//inicializo la variable X_ij
	for (int i = 0; i < numpedido; i++)
	{
		x_ij[i] = IloIntVarArray(env, numtiposcaja);
		for (int j = 0; j < numtiposcaja; j++)
		{
			x_ij[i][j] = IloIntVar(env, 0, n_ij[i][j]);
			sprintf(nombre, "X_%d_%d", i, j);
			x_ij[i][j].setName(nombre);

		}
	}

	/**********************************************************/
	/***************** RESTRICCIONES **************************/
	/**********************************************************/

		//sum_i x_ij = n_j, para todo j
	for (int j = 0; j < numtiposcaja; j++)
	{
		IloExpr v1(env);
		for (int i = 0; i < numpedido; i++)
		{
			v1 += x_ij[i][j];
		}
		restr.add(IloRange(env, n_j[j], v1, n_j[j]));
		v1.end();
	}

	//x_ij<=z_i n_ij, para todo i, j
	for (int j = 0; j < numtiposcaja; j++)
	{
		for (int i = 0; i < numpedido; i++)
		{
			IloExpr v1(env);
			v1 = n_ij[i][j] * z_i[i] - x_ij[i][j];
			restr.add(IloRange(env, 0, v1, IloInfinity));
			v1.end();
		}

	}

	//A�ADIMOS LAS RESTRICCIONES AL MODELO 
	model.add(restr);

	/**********************************************************/
	/***************FUNCION OBJETIVO **************************/
	/**********************************************************/

	IloExpr Expression_fobj(env);

	for (int i = 0; i < numpedido; i++)
	{
		Expression_fobj += v_i[i] * z_i[i];
	}


	model.add(IloMinimize(env, Expression_fobj));
	Expression_fobj.end();


	/***************************************************************/
	/*************** EJECUTAMOS EL MODELO **************************/
	/***************************************************************/
	try {

		IloCplex cplex(model);
		cplex.setOut(env.getNullStream()); //Para no imprimir por pantalla
		//No hace el probing
		//cplex.setParam(IloCplex::Probe, -1);
		//1 CORE
		cplex.setParam(IloCplex::Threads, 1);
		//para que utilice memoria de disco para trasferir nodos de la mem principal a disco.
		/*cplex.setParam(IloCplex::NodeFileInd, 3);*/
		//limite de tiempo
		cplex.setParam(IloCplex::TiLim, max_time); //TIEMPO EN SEGUNDOS

		/*cplex.exportModel("ivan.lp");*/

		//CPXsetintparam(env,CPX_PARAM_THREADS,1);

		//numero de filas y columnas del modelo
		int nr = cplex.getNrows();
		int nc = cplex.getNcols();

		//resolver el modelo y tomamos tiempos
		IloNum inicio, fin;
		clock_t t_ini, t_fin;

		inicio = cplex.getCplexTime();
		t_ini = clock();


		IloBool result = cplex.solve();

		t_fin = clock();
		fin = cplex.getCplexTime();

		double secs = (double)(fin - inicio);
		/*printf("%2f \n", secs);*/

		int vol = 0;
		int minvol = (*contenedor).Get_X() * (*contenedor).Get_Y() * (*contenedor).Get_Z();
		int candidato = 0;
		bool completo = true;

		//Estado del algoritmo	al terminar
		IloCplex::Status estado = cplex.getCplexStatus();
		IloCplex::Status sub_estado = cplex.getCplexSubStatus();


		if (result == false)
		{


			
			//fprintf(f, "%s ", nom);
			IloAlgorithm::Status est = cplex.getStatus();
			if (cplex.getStatus() == IloAlgorithm::Infeasible)
			{
				FILE* f = fopen("./estadomodelo.txt", "a+");
				fprintf(f, "Infeaseble\n");
				fclose(f);
				cplex.exportModel("ivan.lp");
			}
			else
			{
				if (cplex.getStatus() == IloAlgorithm::Unbounded)
				{
					FILE* f = fopen("./estadomodelo.txt", "a+");
					fprintf(f, "Unbounded\n");
					fclose(f);
				}
				FILE* f = fopen("./estadomodelo.txt", "a+");
				fprintf(f, "nosol;%.2f;%.2f\n", cplex.getNnodes(), cplex.getTime());
				fclose(f);
			}
			
		}
		else
		{
			//Si ha encontrado alguna solucion posible
			if (cplex.getSolnPoolNsolns() > 0)
			{
				value2 = cplex.getObjValue();
				//|bestnode-bestinteger|/(1e-10+|bestinteger|)
				double relativeGap = std::abs(cplex.getObjValue() - cplex.getBestObjValue()) / (std::abs(cplex.getObjValue()) + 1e-10);

				//Aqui escribir la solucion en un fichero externo

				//estoy en el optimo, leo las variables y continuo
				if (relativeGap == 0)
				{
					/*(*contenedor).Set_completos(0);*/
					(*contenedor).Set_vol_incompletos(0);
					for (int i = 0; i < numpedido; i++)
					{
						/*(*contenedor).Get_Pedidos()[i].Set_complete(false);*/
						completo = true;
						if (cplex.isExtracted(z_i[i]) && cplex.getValue(z_i[i]) > 0.01)
						{
							/*printf("z_%d:%.2f\n", i, cplex.getValue(z_i[i]));*/
							/*(*contenedor).Add_completos();*/
							/*bool pr = false;
							if (i == 0)
								pr = true;*/
							for (int j = 0; j < numtiposcaja; j++)
							{
								if (cplex.isExtracted(x_ij[i][j]))
								{
									if ((*contenedor).Get_Pedidos()[ind[i]].Get_num_pieces_tipo()[j] != cplex.getValue(x_ij[i][j]))
									{
										completo = false;
										(*contenedor).Get_Pedidos()[ind[i]].Get_faltan().push_back((*contenedor).Get_Pedidos()[ind[i]].Get_num_pieces_tipo()[j] - cplex.getValue(x_ij[i][j]));
										//if (pr==true)
											//printf("inc: %d/t size: %d\n", (*contenedor).Get_Pedidos()[ind[i]].Get_num_pieces_tipo()[j] - cplex.getValue(x_ij[i][j]), (*contenedor).Get_Pedidos()[ind[i]].Get_faltan().size());
									}
									else
									{
										(*contenedor).Get_Pedidos()[ind[i]].Get_faltan().push_back(0);
										//if (pr==true)
											//printf("com: 0/t size: %d\n", (*contenedor).Get_Pedidos()[ind[i]].Get_faltan().size());
									}
								}
								else
									printf("modelo semi mal\n");
							}
							/*printf("%d\t%d\n", i, completo);*/
							if (completo == true)
							{
								(*contenedor).Add_completos();
								(*contenedor).Add_vol_cs((*contenedor).Get_Pedidos()[ind[i]].Get_Volumen());
								(*contenedor).Get_Pedidos()[ind[i]].Set_complete(true);
							}
							else
							{
								(*contenedor).Get_Pedidos()[ind[i]].Set_complete(false);
								/*(*contenedor).Get_candidatos().push_back((*contenedor).Get_Pedidos()[ind[i]]);*/
								for (int j = 0; j < numtiposcaja; j++)
									(*contenedor).Add_vol_incompletos(cplex.getValue(x_ij[i][j]) * (*contenedor).Get_Piezas()[j].Get_Volumen());
							}
						}
						else if (cplex.isExtracted(z_i[i]))
						{
							(*contenedor).Get_Pedidos()[ind[i]].Set_complete(false);
						}
			
						/*else if (cplex.isExtracted(z_i[i]) && (*contenedor).GetRandom()==true)
						{
							vol = 0;
							for (int j = 0; j < numtiposcaja; j++)
							{
								if (cplex.isExtracted(x_ij[i][j]) && cplex.getValue(x_ij[i][j]) > 0.01)
									vol += cplex.getValue(x_ij[i][j]) * (*contenedor).Get_Piezas()[j].Get_Volumen();
							}
							(*contenedor).Get_Pedidos()[i].Set_vol_falta((*contenedor).Get_Pedidos()[i].Get_Volumen() - vol);
							if ((*contenedor).Get_Pedidos()[i].Get_Volumen() - vol < minvol)
							{
								minvol = (*contenedor).Get_Pedidos()[i].Get_Volumen() - vol;
								(*contenedor).Set_candidato(i);
							}
						}*/
					}
					
				
					//int suma = 0;
					//for (int i = 0; i < numpedido; i++)
					//	suma += (*contenedor).Get_Pedidos()[i].Get_Volumen() * cplex.getValue(z_i[i]);
					//printf("%d\t%d\n", (*contenedor).Get_Volumen_Utilizado(), suma);
					//printf("x_ij: numero de cajas del tipo j en el pedido i en la solucion\n");
					//for (int i = 0; i < numpedido; i++)
					//{
					//	for (int j = 0; j < numtiposcaja; j++)
					//	{
					//		if (cplex.isExtracted(x_ij[i][j]))
					//			printf("%2.f\t", cplex.getValue(x_ij[i][j]));
					//		/*if (cplex.isExtracted(x_ij[i][j])>0.01)
					//			printf("pedido: %d\t caja: %d\t%2.f\n", i, j, cplex.getValue(x_ij[i][j]));*/
					//	}
					//	printf("\n");
					//}

					/*printf("z_i: 1 si el pedido esta completo, 0 en otro caso\n");
					for (int i = 0; i < numpedido; i++)
					{
						if (cplex.isExtracted(z_i[i]) && cplex.getValue(z_i[i]) > 0.01)
							printf("%d\t", 1);
						else if (cplex.isExtracted(z_i[i]) && cplex.getValue(z_i[i]) < 0.99)
							printf("%d\t", 0);
					}
					printf("\n");*/
				}


			}
		}

		cplex.end();
		model.end();
		env.end();
	}
	catch (IloException & e)
	{
		printf("EXCEPCION");
		std::cerr << "IloException: " << e << "Status" << e;
	}
}
