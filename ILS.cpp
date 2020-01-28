#pragma warning (disable: 4786)

//Para incluir el contenedor que tengo
#include "Container.h"
#include "LPCPLEX2.h"
//extern  "C" int  bouknap(int n, int* p, int* w, int* m, int* x, int c);

#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#endif
//#include "bouknap.c"


void CONTAINER::ILS()
{


	//Procesamiento de los parametros
	/*
	if ((argc > 2) && (argc % 2 == 1))
	{ //Se comprueba que haya pares de argumentos (y al menos un par)

		while (argc > 1)
		{
			if (strcmp(argv[1], "-t") == 0)
			{
				//Tiempo
				sscanf(argv[2], "%d", &Seconds);
			}
			else if (strcmp(argv[1], "-p") == 0)
			{
				//File to read
				file_to_read = argv[2];

			}
			else if (strcmp(argv[1], "-o") == 0)
			{
				file_to_write = argv[2];
			}
			else if (strcmp(argv[1], "-s") == 0)
			{
				sscanf(argv[2], "%d", &seed);
			}
			else if (strcmp(argv[1], "-name") == 0)
			{
				sscanf(argv[2], "%d", &TeamId);
			}
			else if (strcmp(argv[1], "-iter") == 0)
			{
				sscanf(argv[2], "%d", &Iter);
			}
			//For the test 
			else if (strcmp(argv[1], "-Param") == 0)
			{
				sscanf(argv[2], "%d", &Param);
			}
			argc -= 2;
			argv += 2;

		}
	}*/
	//ConstruirSolucion
	m_eliminar_espacios=false;
	m_mejora_local=false;
	m_objetivo_capas=true;
	m_Aleatorizado=false;
	m_objetivo_vol=true;
	srand(1);
	Constructivo(false);
	
	//MejoraLocal
	MejoraLocalVaciado(false);
	if (m_total_volumen_ocupado>=m_max_total_volumen_ocupado)
	{
		m_Best_Configuracao=m_Configuracaos;
	}

//	return;
	int iteraciones=0;
	do 
	{
		iteraciones++;
		//Perturbar la solucion
//		if (m_Spaces.size()>10)
//		int alea=get_random(1,19);
//		double val=(double)val/20;
//		QuitarBloque(val);
		MejoraLocalVaciado(true);
		//Mejora Local
		m_un_movimiento=false;
		m_max_movimientos=100;

		MejoraLocalVaciado(false);
		//Criterio de Aceptación
		//si es mayor guardo y continuo, en otro caso tengo que cambiar
		if (m_total_volumen_ocupado>=m_max_total_volumen_ocupado)
		{
			m_Best_Configuracao=m_Configuracaos;
		}
		else
		{
			std::list<CONFIGURACAO> lista_temp=m_Best_Configuracao;
			m_eliminar_espacios=false;
			ConstruirSolucion(lista_temp,true);
		}


	}while(iteraciones<30);
			m_fintime=clock();
	m_tiempo=((double)((double)m_fintime-m_inicio))/CLOCKS_PER_SEC;

	FILE *fin3;
	fin3=fopen(m_file_to_write,"a+");
	double pt=((double)m_max_total_volumen_ocupado/(double)((double)m_X*m_Y*m_Z))*100;
	fprintf(fin3,"%s\tV\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
	fclose(fin3);

}
void CONTAINER::ILS_MC()
{
	m_Pieces_Tabu.clear();
	for (int j=0;j<m_Q;j++)
		m_Pieces_Tabu.push_back(0);

	//ConstruirSolucion
	m_eliminar_espacios=false;
	m_mejora_local=false;
	m_objetivo_capas=true;
	m_Aleatorizado=false;
	m_objetivo_vol=true;
	srand(1);
	std::list< std::pair<int, std::list< CONFIGURACAO> > >::iterator it;
	std::list< CONFIGURACAO> ::iterator itC;
	ConstructivoMC(false);
	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
	{
		m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
		if (m_total_volumen_ocupado==m_total_volumen)
		{
			m_Best_nbins=m_ConfiguracaosMC.size();
			m_total_volumen_ocupado-=m_ConfiguracaosMC.back().first;
//quito la ultima que tenia
			for (itC=m_ConfiguracaosMC.back().second.begin();itC!=m_ConfiguracaosMC.back().second.end();itC++)
			{
				m_Pieces[(*itC).Get_Id()].Set_Num(0);
			}
			
			m_ConfiguracaosMC.pop_back();
			m_Best_ConfiguracaoMC=m_ConfiguracaosMC;


		}
		m_max_total_volumen_ocupado=m_total_volumen_ocupado;

	}	
	//MejoraLocal
/*	m_aleatorizado=true;
	MejoraLocalMCQuitarDosBin(false);

	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
	{
		m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
		if (m_total_volumen_ocupado==m_total_volumen)
		{
			m_Best_nbins--;
			m_total_volumen_ocupado-=m_ConfiguracaosMC.back().first;
			m_ConfiguracaosMC.pop_back();
			m_Best_ConfiguracaoMC=m_ConfiguracaosMC;

		}
		m_max_total_volumen_ocupado=m_total_volumen_ocupado;
		//Actualizo los valores 
		for (int j=0;j<m_Q;j++)
			m_Pieces[j].Set_Num(0);

		for (it=m_ConfiguracaosMC.begin();it!=m_ConfiguracaosMC.end();it++)
		{
			for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
			{
				m_Pieces[(*itC).Get_Id()].Set_Num((*itC).Get_Num());
			}
		}

	}*/
	VerificarSolucionMC(m_ConfiguracaosMC);

//	return;
	int iteraciones=0;
	do 
	{
		iteraciones++;
		//Perturbar la solucion
//		if (m_Spaces.size()>10)
//		int alea=get_random(1,19);
//		double val=(double)val/20;
//		QuitarBloque(val);
		m_Aleatorizado=true;
		m_objetivo_vol=get_random(0,1);
		MejoraLocalMCQuitarUltimos(true,true);
		m_objetivo_vol=true;
		m_Aleatorizado=false;
		//Mejora Local
		m_un_movimiento=false;
		m_max_movimientos=100;

		MejoraLocalMCQuitarDosBin(false);
		//Criterio de Aceptación
		//si es mayor guardo y continuo, en otro caso tengo que cambiar
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
		{
			m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
			if (m_total_volumen_ocupado==m_total_volumen)
			{
				m_Best_nbins--;
				m_total_volumen_ocupado-=m_ConfiguracaosMC.back().first;
				m_ConfiguracaosMC.pop_back();
				m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
			}
			m_max_total_volumen_ocupado=m_total_volumen_ocupado;

		}
		else
		{
			 m_ConfiguracaosMC=m_Best_ConfiguracaoMC;
			 m_total_volumen_ocupado=m_max_total_volumen_ocupado;
		}
		MejoraLocalMCQuitarUltimos(false,false);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
		{
			m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
			if (m_total_volumen_ocupado==m_total_volumen)
			{
				m_Best_nbins--;
				m_total_volumen_ocupado-=m_ConfiguracaosMC.back().first;
				m_ConfiguracaosMC.pop_back();
				m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
			}
			m_max_total_volumen_ocupado=m_total_volumen_ocupado;

		}
		else
		{
			 m_ConfiguracaosMC=m_Best_ConfiguracaoMC;
			 m_total_volumen_ocupado=m_max_total_volumen_ocupado;
		}


		//Actualizo los valores de la solucion
		//***********************
		for (int j=0;j<m_Q;j++)
			m_Pieces[j].Set_Num(0);

		for (it=m_ConfiguracaosMC.begin();it!=m_ConfiguracaosMC.end();it++)
		{
			for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
			{
				m_Pieces[(*itC).Get_Id()].Set_Num((*itC).Get_Num());
			}
		}
		VerificarSolucionMC(m_ConfiguracaosMC);
//		printf("%d\n",m_max_total_volumen_ocupado);

	}while(iteraciones<1000 && m_Best_nbins!=m_lb);
			m_fintime=clock();
	m_tiempo=((double)((double)m_fintime-m_inicio))/CLOCKS_PER_SEC;


	FILE *fin3;
	fin3=fopen(m_file_to_write,"a+");
	fprintf(fin3,"%s\t%d\t%d\t%d\t%f\n",m_Nombre,m_lb,m_Best_nbins,m_iter_best_actual,m_tiempo);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
	fclose(fin3);

}
//true si es secuencial
void CONTAINER::VND(bool secuencial)
{
	m_max_movimientos=100;
	//ConstruirSolucion
	m_eliminar_espacios=false;
	m_mejora_local=false;

	m_objetivo_capas=true;
	m_Aleatorizado=false;
	Constructivo(false);
	int temp=m_max_total_volumen_ocupado;
	m_objetivo_vol=true;
	int todos_explorados=0;
principio:	
	temp=m_max_total_volumen_ocupado;
	//MejoraLocal
	m_objetivo_vol=true;
	m_un_movimiento=false;
	m_max_movimientos=100;
	MejoraLocalVaciado(false);
	if (secuencial==false)
	m_un_movimiento=true;
	else
		m_un_movimiento=false;
	m_max_movimientos=1000;

	MejoraLocalCapa(false);
	if (secuencial==false && m_max_total_volumen_ocupado>temp)
		goto principio;
	m_objetivo_vol=false;
	m_max_movimientos=100;

	MejoraLocalVaciado(false);
	if (secuencial==false && m_max_total_volumen_ocupado>temp)
		goto principio;
	m_max_movimientos=100;
	m_objetivo_vol=true;
	MejoraLocalPieza(false);
	if (secuencial==false && m_max_total_volumen_ocupado>temp)
		goto principio;
	MejoraLocalReducirBloque(false);
	if (secuencial==false && m_max_total_volumen_ocupado>temp)
		goto principio;

	m_fintime=clock();
	m_tiempo=((double)((double)m_fintime-m_inicio))/CLOCKS_PER_SEC;

	FILE *fin3;
	fin3=fopen(m_file_to_write,"a+");
	double pt=((double)m_max_total_volumen_ocupado/(double)((double)m_X*m_Y*m_Z))*100;
	fprintf(fin3,"%s\tV\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
	fclose(fin3);
	/*DibujarOpenGL(m_Configuracaos);*/
}
//secuencial es para si queremos verlo de manera secuencial o no
void CONTAINER::VNS(bool secuencial)
{
	if (m_complete_shipment && m_cota_cs==0)
		CotaCompleteShipment();
	//FILE* fincs;
	//fincs = fopen(m_file_to_write, "a+");
	//fprintf(fincs, "p19\n");
	//fclose(fincs);
	m_Configuracaos.clear();
	m_Spaces.clear();
	m_total_volumen_ocupado = 0;
	m_total_volumen_cs_ocupado = 0;
	m_max_total_volumen_ocupado = 0;
	m_max_total_volumen_ocupado = 0;
	m_max_total_volumen_ocupado_mejora = 0;
	paraprobar = true;
	paraprobar2 = true;
	idbloque = 0;
	double time = 30;
	bool optimo = false;
	SetVerificar(true);
	SetDibujar(false);
	//	for (int ikl = 0; ikl<m_Q; ikl++)
	//		m_Pieces_Mejora.push_back(0);
	int total_iteraciones = 15;
	//Si es el secuencial el doble de iteraciones
	if (secuencial == true)
		total_iteraciones = 30;
	bool parar = false;
	//ConstruirSolucion
//	m_rotacion = true;
	m_por_bin = false;
	m_eliminar_espacios = false;
	m_mejora_local = false;
	//	m_descendent = false;
	m_objetivo_capas = true;
	m_Aleatorizado = false;
	m_un_movimiento = true;
	m_max_movimientos = 10;
	int cont = 0;
	
	Constructivo(false);
	/*FILE* fincs;*/
	//fincs = fopen(m_file_to_write, "a+");
	//fprintf(fincs, "p20\n");
	//fclose(fincs);
	double pt = ((double)m_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
	
	m_fintime = clock();
	m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
	if (m_complete_shipment == true && m_imprimir==true)
	{
		double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		printf("%d\t%d\t%f\t%d\t%f\t%f\t%d\n", m_total_volumen, m_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, m_tiempo, m_iteraciones);
	}
	else if (m_imprimir==true)
		printf("%d\t%d\t%f\t%f\n", m_total_volumen, m_total_volumen_ocupado, pt, m_tiempo);

	VerificarSolucion(m_Configuracaos);
	/*SetDibujar(true);
	DibujarOpenGL(m_Configuracaos);
	SetDibujar(false);*/
	//SetDibujar(true);
	//DibujarOpenGL(m_Configuracaos);
	//SetDibujar(false);
	//SetDibujar(true);
	//DibujarOpenGL(m_Configuracaos);
	//SetDibujar(false);
	int temp=m_max_total_volumen_ocupado;
	m_objetivo_vol=true;
	int todos_explorados=0;
	int iteraciones=0;
	int shaking=0;
	int kkkk = 0;
	int kkkkk = 0;
	int cont_vac;
	int cont_red;
	do {
	/*	FILE* fincs;
		fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p21\n");
		fclose(fincs);*/
		if (m_VCS_random == true)
		{
			alpha = get_random(1, 8);
			beta = get_random(0, 4);
			gamma = (double)(get_random(1, 4) / (double)10);
			p = (double)get_random(0, 5) / (double)100;
			Max_Iter_VCS = get_random(20, 40);
		}
		/*if (iteraciones == 27)
			int kk = 9;*/
		//if (iteraciones == 11)
		//{
		//	SetDibujar(true);
		//	DibujarOpenGL(m_Configuracaos);
		//}
		m_Bloques = m_Bloques_Guardados;
		kkkk = 0;
		kkkkk = 0;
		cont_vac = 0;
		cont_red = 0;
		int maxtemp = m_max_total_volumen_ocupado;
		//		printf("Shaking*************\n");
				//Fase de shaking********************** 
		//		if (shaking==0)

		if (shaking == 0)
		{
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p25\n");
			fclose(fincs);*/
			m_por_bin = false;
			do
			{
				/*if (m_full_supported==true)*/
					cont_vac++;
				/*if (kkkkk == 1 && iteraciones == 11)
					paraprobar = false;*/
				MejoraLocalVaciado(true);
			} while (m_total_volumen_ocupado == maxtemp && m_Q != 1 && m_Z != 1 && cont_vac < 10);
			/*m_por_bin = false;
			m_objetivo_vol = objetivo_vol_old;*/
		}
		if (shaking == 1)
		{
			/*DibujarOpenGL(m_Configuracaos);*/
			MejoraLocalCapa(true);
		/*	FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p26\n");
			fclose(fincs);*/
		}
		if (shaking == 2)
		{
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p27\n");
			fclose(fincs);*/
			m_por_bin = false;
			do
			{
				/*if (m_full_supported == true)*/
					cont_red++;
				MejoraLocalReducirBloque(true);
				/*SetDibujar(false);*/
			} while (m_total_volumen_ocupado == maxtemp && m_Q != 1 && m_Z != 1 && cont_red < 10);
		}
		if (shaking == 3)
		{
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p28\n");
			fclose(fincs);*/
			/*DibujarOpenGL(m_Configuracaos);*/
			MejoraLocalPieza(true);
		}
		if (shaking == 4)
		{
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p29\n");
			fclose(fincs);*/
			/*DibujarOpenGL(m_Configuracaos);*/
			/*SetDibujar(true);*/
			/*DibujarOpenGL(m_Configuracaos);*/
			int alea = get_random(10, 30);
			QuitarBloque((double)alea / (double)100);
		}
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p30\n");
		fclose(fincs);*/
		//Esto es el VND***********************
		temp = m_total_volumen_ocupado;
		m_objetivo_vol = true;
		todos_explorados = 0;
	principio:
		temp = m_total_volumen_ocupado;
		//MejoraLocal
		m_objetivo_vol = true;
		m_un_movimiento = false;
		m_max_movimientos = 100;
		m_por_bin = false;

		VerificarSolucion(m_Configuracaos);

		MejoraLocalVaciado(false);
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p31\n");
		fclose(fincs);*/
		m_por_bin = false;
		if (m_max_total_volumen_ocupado_mejora == m_total_volumen)
		{
			//printf("m_max_total_volumen_ocupado_mejora=%d\tm_max_total_volumen_ocupado=%d\tm_total_volumen_ocupado=%d\n", m_max_total_volumen_ocupado_mejora, m_max_total_volumen_ocupado, m_total_volumen_ocupado);
			m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();
			//double pt = ((double)m_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//printf("%d\tVU\t%d\t%f\t%d\t%f\t%f\t%d\n", m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, m_tiempo, iteraciones);

			goto fin;
		}
		VerificarSolucion(m_Configuracaos);
		temp = m_total_volumen_ocupado;

		m_max_movimientos = 1000;
		if (secuencial == false)
			m_un_movimiento = true;
		else
			m_un_movimiento = false;
		m_max_movimientos = 1000;
		
		MejoraLocalCapa(false);
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p32\n");
		fclose(fincs);*/
		VerificarSolucion(m_Configuracaos);
		if (secuencial == false && m_max_total_volumen_ocupado_mejora > temp)
			goto principio;
		if (m_max_total_volumen_ocupado_mejora == m_total_volumen)
		{
			//printf("m_max_total_volumen_ocupado_mejora=%d\tm_max_total_volumen_ocupado=%d\tm_total_volumen_ocupado=%d\n", m_max_total_volumen_ocupado_mejora, m_max_total_volumen_ocupado, m_total_volumen_ocupado);
			m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();
			//double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//double pt = ((double)m_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//printf("%d\tVU\t%d\t%f\t%d\t%f\t%f\t%d\n", m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, m_tiempo, iteraciones);

			goto fin;
		}
		m_objetivo_vol = false;
		m_max_movimientos = 100;
		m_por_bin = false;
		
		MejoraLocalVaciado(false);
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p33\n");
		fclose(fincs);*/
		VerificarSolucion(m_Configuracaos);
		m_por_bin = false;
		if (m_max_total_volumen_ocupado_mejora == m_total_volumen)
		{
			//printf("m_max_total_volumen_ocupado_mejora=%d\tm_max_total_volumen_ocupado=%d\tm_total_volumen_ocupado=%d\n", m_max_total_volumen_ocupado_mejora, m_max_total_volumen_ocupado, m_total_volumen_ocupado);
			m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();
			//double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//double pt = ((double)m_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//printf("%d\tVU\t%d\t%f\t%d\t%f\t%f\t%d\n", m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, m_tiempo, iteraciones);

			goto fin;
		}
		if (secuencial == false && m_max_total_volumen_ocupado_mejora > temp)
			goto principio;
		m_max_movimientos = 1000;
		m_objetivo_vol = true;

		MejoraLocalPieza(false);
		/*FILE* fincs;*/
	/*	fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p34\n");
		fclose(fincs);*/
		VerificarSolucion(m_Configuracaos);
		if (m_max_total_volumen_ocupado_mejora == m_total_volumen)
		{
			//printf("m_max_total_volumen_ocupado_mejora=%d\tm_max_total_volumen_ocupado=%d\tm_total_volumen_ocupado=%d\n", m_max_total_volumen_ocupado_mejora, m_max_total_volumen_ocupado, m_total_volumen_ocupado);
			m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();
			//double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//double pt = ((double)m_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//printf("%d\tVU\t%d\t%f\t%d\t%f\t%f\t%d\n", m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, m_tiempo, iteraciones);

			goto fin;
		}
		if (secuencial == false && m_max_total_volumen_ocupado_mejora > temp)
			goto principio;
		m_por_bin = false;

		MejoraLocalReducirBloque(false);
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p35\n");
		fclose(fincs);*/
		VerificarSolucion(m_Configuracaos);
		m_por_bin = false;
		if (m_max_total_volumen_ocupado_mejora == m_total_volumen)
		{
			//printf("m_max_total_volumen_ocupado_mejora=%d\tm_max_total_volumen_ocupado=%d\tm_total_volumen_ocupado=%d\n", m_max_total_volumen_ocupado_mejora, m_max_total_volumen_ocupado, m_total_volumen_ocupado);
			m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();
			//double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//double pt = ((double)m_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			//printf("%d\tVU\t%d\t%f\t%d\t%f\t%f\t%d\n", m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, m_tiempo, iteraciones);
			goto fin;
		}
		if (secuencial == false && m_max_total_volumen_ocupado_mejora > temp)
			goto principio;
		
		iteraciones++;
		//Criterio de Aceptación
		//si es mayor guardo y continuo, en otro caso tengo que cambiar

		if (m_total_volumen_ocupado > maxtemp)
		{
			parar = false;
			shaking = 0;
			m_Best_Configuracao = m_Configuracaos;
			if (m_complete_shipment == true)
			{
				/*FILE* fincs;
				fincs = fopen(m_file_to_write, "a+");
				fprintf(fincs, "p36\n");
				fclose(fincs);*/
				int volcs = FuncionObjetivoCompleteShipment();
				/*FILE* fincs;*/
				/*fincs = fopen(m_file_to_write, "a+");
				fprintf(fincs, "p37\n");
				fclose(fincs);*/
				if (volcs > m_total_volumen_cs_ocupado)
				{
					/*printf("%d\n",m_completos);*/
					m_total_volumen_cs_ocupado = volcs;
					completos_CS = m_completos;
					m_Spaces_CS = m_Spaces;
					m_Configuracaos_CS = m_Configuracaos;
					m_Pieces_CS = m_Pieces;
					m_Pedidos_CS = m_Pedidos;
					piece_unasigned_CS=piece_unasigned;

				}
				if (m_total_volumen_cs_ocupado == m_total_volumen)
				{
					/*FILE* fincs;
					fincs = fopen(m_file_to_write, "a+");
					fprintf(fincs, "p38\n");
					fclose(fincs);*/
					optimo = true;
					goto fin;
				}
			}
		}
		else
		{
			if (shaking != 4)
			{
				parar = false;
				shaking++;
			}
			else
			{
				parar = true;
				shaking = 0;
			}
			std::list<CONFIGURACAO> lista_temp = m_Best_Configuracao;
			m_eliminar_espacios = false;
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p39\n");
			fclose(fincs);*/
			ConstruirSolucion(lista_temp, true);
			/*FILE* fincs;*/
			/*fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p40\n");
			fclose(fincs);*/
		}

		m_fintime = clock();
		m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
		double pt = ((double)m_max_total_volumen_ocupado / (double)((double)m_X*m_Y*m_Z)) * 100;
		double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		
		if (m_imprimir)
		{
			if (m_complete_shipment==false)
				printf("%d\tVU\t%d\t%f\t%f\t%d\n", m_total_volumen, m_max_total_volumen_ocupado, pt, m_tiempo, iteraciones);
			else
				printf("%d\tVU\t%d\t%f\t%d\t%f\t%f\t%d\t%d\n", m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, m_tiempo, iteraciones, m_iteraciones);

		}
		if (m_tiempo >= time && time!=150 && m_imprimir==true)
		{
			time += 30;
			FILE* fin3;
			fin3 = fopen(m_file_to_write, "a+");
			double pt = ((double)m_max_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;

			if (m_complete_shipment==false)
				fprintf(fin3, "%s\t%d\t%d\tVU\t%d\t%f\t%d\t%f\n", m_Nombre, (m_X * m_Y * m_Z), m_total_volumen, m_max_total_volumen_ocupado, pt, iteraciones, m_tiempo);
			else
				fprintf(fin3, "%s\t%d\t%d\tVU\t%d\t%f\t%d\t%f\t%d\t%f\n", m_Nombre, (m_X* m_Y* m_Z), m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, iteraciones, m_tiempo);
			fclose(fin3);
		}
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p41\n");
		fclose(fincs);*/
	/*}while (iteraciones < 3);*/
		/*bool ent = false;
		for (int j = 0; j < m_Q; j++)
		{
			if (m_Pieces[j].Get_q() != m_Pieces[j].Get_Num())
				ent = true;
		}
		if (ent == false)
		{
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "m_max_total_volumen_ocupado: %d\t m_max_total_volumen_ocupado_mejora: %d\t m_total_volumen: %d\n", m_max_total_volumen_ocupado, m_max_total_volumen_ocupado_mejora, m_total_volumen);
			fclose(fincs);
		}*/
	/*}while(iteraciones<total_iteraciones && m_tiempo<m_time_final);*/ //Criterio de parada: iteraciones + tiempo

	}while (m_tiempo < m_time_final); //Criterio de parada: solo tiempo
	/*printf("%d\n", iteraciones);*/
	/*FILE* fincs;*/
	/*fincs = fopen(m_file_to_write, "a+");
	fprintf(fincs, "p22\n");
	fclose(fincs);*/
fin:
	if (m_tiempo < m_time_final && m_imprimir==true)
	{
		FILE* fin3;
		fin3 = fopen(m_file_to_write, "a+");
		double pt = ((double)m_max_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		for (; time<150; time+=30)
			fprintf(fin3, "%s\t%d\t%d\tVU\t%d\t%f\t%d\t%f\t%d\t%f\n", m_Nombre, (m_X* m_Y* m_Z), m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, iteraciones, m_tiempo);
		fclose(fin3);
		FILE* fincs;
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p23\n");
		fclose(fincs);*/
	}
	m_fintime=clock();
	m_tiempo=((double)((double)m_fintime-m_inicio))/CLOCKS_PER_SEC;
	//double t_vac = m_tiempo_vaciado / m_tiempo * 100;
	//double t_red = m_tiempo_reducir / m_tiempo * 100;
	//double t_qui = m_tiempo_quitar / m_tiempo * 100;
	//double t_pie = m_tiempo_pieza / m_tiempo * 100;
	//double t_cap = m_tiempo_capa / m_tiempo * 100;
	if (m_imprimir == true)
	{
		FILE* fin3;
		fin3 = fopen(m_file_to_write, "a+");
		pt = ((double)m_max_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		if (m_complete_shipment == false)
			fprintf(fin3, "%s\t%d\t%d\tVU\t%d\t%f\t%d\t%f\n", m_Nombre, (m_X * m_Y * m_Z), m_total_volumen, m_max_total_volumen_ocupado, pt, iteraciones, m_tiempo);
		else
		{
			if (optimo == false)
				fprintf(fin3, "%s\t%d\t%d\tVU\t%d\t%f\t%d\t%f\t%d\t%f\n", m_Nombre, (m_X * m_Y * m_Z), m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, iteraciones, m_tiempo);
			else
				fprintf(fin3, "%s\t%d\t%d\tVU\t%d\t%f\t%d\t%f\t%d\t%f\n", m_Nombre, (m_X * m_Y * m_Z), m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, iteraciones, m_tiempo);

		}
		//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
		fclose(fin3);
	}
	/*FILE* fincs;*/
	/*fincs = fopen(m_file_to_write, "a+");
	fprintf(fincs, "p24\n");
	fclose(fincs);*/
}
void CONTAINER::PrimeraImplementacion()
{
	int volumen_iterar = 0;
	bool comprobar = false;
	bool imprimir = false;
	m_tiempo_final_total = m_time_final;
	m_time_final = m_time_final / 2;
	m_imprimir = false;
	/*printf("%f\n", m_time_final);*/
	VNS(true); //Ejecutamos el VNS que nos devolverá la configuración con mayor porcentaje de volumen con complete shipment ocupado
	if (completos_CS == m_num_pedidos-1)
	{
		FILE* fincs;
		fincs = fopen(m_file_to_write, "a+");
		double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		fprintf(fincs, "%s\t%d\t%f\n", m_Nombre, m_total_volumen_cs_ocupado, ptcs);
		fclose(fincs);
		return;
	}
	double ptt1 = m_total_volumen_cs_ocupado / ((double)m_X * m_Y * m_Z) * 100;
	/*printf("%f\n", ptt1);*/
	m_fintime = clock();
	m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
	/*printf("inicial: %d\t%f\t%f\n", m_total_volumen_cs_ocupado, ptt1, m_tiempo);*/
	int volcsguardado = m_total_volumen_cs_ocupado;
	m_Configuracaos = m_Configuracaos_CS;
	m_Pieces = m_Pieces_CS;
	m_Spaces = m_Spaces_CS;
	m_Pedidos = m_Pedidos_CS;
	m_completos = completos_CS;
	piece_unasigned = piece_unasigned_CS;
	//Pongo la disponibilidad de cajas a 0 para todos los tipos
	for (int j = 0; j < m_Q; j++)
		m_Pieces[j].Set_Q(m_Pieces[j].Get_Num());
	std::vector<PIECE> pieces = m_Pieces;
	std::set<int> no_seleccionados;
	std::set<int> seleccionados;
	double pt = 0;
	int vol_falta = 0;
	LPCPLEX micplex;
	//Con las cajas no asignadas por el modelo, resolvemos otro modelo 
	//que haga asignaciones sin necesariamente completar pedidos,
	//y devuelve la lista con los candidatos a introducir en el contenedor
	micplex.modelo_semiasignacion(this);
	for (int i = 0; i < m_num_pedidos; i++)
	{
		if (m_Pedidos[i].Get_faltan().size()>0)
			m_Pedidos_candidatos.push_back(m_Pedidos[i]);
	}
	//printf("%d\n", m_completos);
	std::vector <PEDIDO> m_Pedidos_candidatos_CS = m_Pedidos_candidatos;;
	//guardo el volumen ocupado hasta el momento, e iteramos cambiando el coeficiente
	int volbucle = m_total_volumen_cs_ocupado;
	int volincompletos = m_vol_incompletos;
	double coef = 1.0;
	int contbucle = 0;
	do
	{
		/*ComprobarPedidos();*/
		//printf("%d\n", m_Pedidos_candidatos.size());
		//reinicio variables
		contbucle++;
		/*if (contbucle == 13)
		{
			printf("13");
		*/
		m_vol_incompletos = volincompletos;
		no_seleccionados.clear();
		seleccionados.clear();
		m_total_volumen_cs_ocupado = volbucle;
		/*if (contbucle == 2)
		{
			printf("1: %d\n", m_total_volumen_cs_ocupado);
		}*/
		/*for (int k = 0; k < m_Pedidos_candidatos.size(); k++)
		{
			m_Pedidos_candidatos[k].Set_complete(false);
			m_Pedidos_candidatos[k].Set_flag(false);
			m_Pedidos[m_Pedidos_candidatos[k].Get_Id()].Set_complete(false);
			m_Pedidos[m_Pedidos_candidatos[k].Get_Id()].Set_flag(false);
		}
		m_completos = 0;
		for (int i = 0; i < m_num_pedidos; i++)
		{
			if (m_Pedidos[i].Get_complete() == true)
				m_completos++;
		}*/
		m_Pieces = pieces;
		m_Configuracaos = m_Configuracaos_CS;
		m_Spaces = m_Spaces_CS;
		m_Pedidos = m_Pedidos_CS;
		m_Pedidos_candidatos = m_Pedidos_candidatos_CS;
		m_completos = 0;
		for (int i = 0; i < m_num_pedidos; i++)
		{
			if (m_Pedidos[i].Get_complete() == true)
				m_completos++;
		}
		coef = (double)get_random(15, 30)/10;
		ComprobarPedidos();
		//si no hay candidatos, solución óptima, imprimo y salgo del bucle
		if (m_Pedidos_candidatos.size() == 0)
		{
			volumen_iterar = m_total_volumen_cs_ocupado;
			FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			double ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
			fprintf(fincs, "%s\t%d\t%f\t%d\t%f\n", m_Nombre, m_total_volumen_cs_ocupado, ptcs, m_total_volumen_cs_ocupado, ptcs);
			fclose(fincs);
			break;
		}
		
		/*m_total_volumen_cs_ocupado = 0;
		for (int i = 0; i < m_num_pedidos; i++)
		{
			if (m_Pedidos[i].Get_complete() == true)
				m_total_volumen_cs_ocupado += m_Pedidos[i].Get_Volumen();
		}*/
		for (int i = 0; i < m_Pedidos_candidatos.size(); i++)
			no_seleccionados.insert(i);
		std::vector<int> eliminar;
		std::set<int>::iterator it = no_seleccionados.begin(), itfin = no_seleccionados.end();
		//int volguardo;
		//int volmax;
		//double ptini = (double)m_total_volumen_cs_ocupado / ((double)m_X * m_Y * m_Z) * 100;
		//if (m_Pedidos_candidatos.size() == 0 || m_completos == m_num_pedidos - 1)
		//	goto escribir;


		//elegimos de entre los candidatos cuales vamos a intentar colocar y qué cajas vamos a eliminar
		vol_falta = 0;
		do
		{
			switch (get_random(1, 3))
			{
			case 1:
			{
				ElegirPedidoVolumenDentro(m_Pedidos_candidatos);
				break;
			}
			case 2:
			{
				ElegirPedidoVolumenFuera(m_Pedidos_candidatos);
				break;
			}
			case 3:
			{
				ElegirPedidoVolumenFueraPt(m_Pedidos_candidatos);
				break;
			}
			}
			/*printf("%d\n", m_candidato);*/
			for (int j = 0; j < m_Q; j++)
			{
				vol_falta += m_Pedidos_candidatos[m_candidato].Get_faltan()[j] * m_Pieces[j].Get_Volumen();
				m_vol_incompletos -= (m_Pedidos_candidatos[m_candidato].Get_num_pieces_tipo()[j] - m_Pedidos_candidatos[m_candidato].Get_faltan()[j]) * m_Pieces[j].Get_Volumen();
			}
			if (coef * vol_falta < m_vol_incompletos)
			{
				no_seleccionados.erase(m_candidato);
				seleccionados.insert(m_candidato);
				m_Pedidos_candidatos[m_candidato].Set_flag(true);
				for (int j = 0; j < m_Q; j++)
					m_Pieces[j].Set_Q(m_Pieces[j].Get_q() + m_Pedidos_candidatos[m_candidato].Get_faltan()[j]);
			}

		} while (coef * vol_falta < m_vol_incompletos);
		/*if (contbucle == 2)
		{
			printf("2: %d\t%d\t%d\n", m_total_volumen_cs_ocupado, m_num_pedidos-1, m_completos);
		}*/
		std::set<int>::iterator itv;
		for (itv = no_seleccionados.begin(); itv != no_seleccionados.end(); itv++)
			m_Pedidos_candidatos[*itv].Set_flag(true);
		for (itv = seleccionados.begin(); itv != seleccionados.end(); itv++)
			m_Pedidos_candidatos[*itv].Set_flag(false);
		std::set<int>::iterator itSet;
		for (itSet = no_seleccionados.begin(); itSet != no_seleccionados.end(); itSet++)
		{
			for (int j = 0; j < m_Q; j++)
			{
				m_Pieces[j].Set_Q(m_Pieces[j].Get_q() - (m_Pedidos_candidatos[*itSet].Get_num_pieces_tipo()[j] - m_Pedidos_candidatos[*itSet].Get_faltan()[j]));
			}
		}
		if (imprimir)
		{
			printf("seleccionados: ");
			for (itSet = seleccionados.begin(); itSet != seleccionados.end(); itSet++)
				printf("%d\t", m_Pedidos_candidatos[*itSet].Get_Id());
			printf("\n");
		}


		std::vector<PIECE> piezas_guardada = m_Pieces;
		//Guardamos el número de cajas de cada tipo que hay que eliminar de la solución
		for (int j = 0; j < m_Q; j++)
		{
			int piez = 0;
			it = no_seleccionados.begin();
			for (; it != itfin; it++)
				piez += m_Pedidos_candidatos[*it].Get_num_pieces_tipo()[j] - m_Pedidos_candidatos[*it].Get_faltan()[j];
			if (imprimir)
				printf("caja: %d cuantas: %d\n", j, piez);
			eliminar.push_back(piez);
		}

		std::list<CONFIGURACAO> listaconf = m_Configuracaos;
		std::list<CONFIGURACAO>::iterator itC, itCfin, itC2;
		std::list<CONFIGURACAO> conf_eliminar;
		/*PintarSolucion(listaconf);*/
		//Para cada j, elegimos las eliminar[j] cajas más altas del contenedor
		int z1 = 0, z2 = 0;
		for (int j = 0; j < m_Q; j++)
		{
			if (eliminar[j] == 0)
				continue;
			for (int k = 0; k < eliminar[j]; k++)
			{
				bool primero = true;
				bool primero2 = true;
				z1 = 0;
				z2 = 0;
				for (itC = listaconf.begin(); itC != listaconf.end(); itC++)
				{
					if ((*itC).Get_Id() != j)
						continue;
					if ((*itC).Get_z2() >= z2 || primero == true)
					{

						if ((*itC).Get_z2() == z2 || primero == true)
						{
							if ((*itC).Get_z1() >= z1 || primero == true)
							{
								primero = false;
								z1 = (*itC).Get_z1();
								z2 = (*itC).Get_z2();
								itC2 = itC;
							}
						}
						else
						{
							z1 = (*itC).Get_z1();
							z2 = (*itC).Get_z2();
							itC2 = itC;
						}
					}
				}
				if (primero == false)
				{
					CONFIGURACAO Temp = *itC2;
					conf_eliminar.push_back(*itC2);
					listaconf.erase(itC2);
					if (Temp.Get_Num() > eliminar[j])
						break;
				}
			}
		}
		std::list<CONFIGURACAO>::iterator itCo, itCofin = conf_eliminar.end();
		std::list<CONFIGURACAO> para_eliminar;
		for (int j = 0; j < m_Q; j++)
		{
			if (eliminar[j] == 0)
				continue;
			for (itCo = conf_eliminar.begin(); itCo != itCofin; itCo++)
			{
				if ((*itCo).Get_Id() != j)
					continue;
				if ((*itCo).Get_Num() < eliminar[j])
				{
					CONFIGURACAO C(this, j, (*itCo).Get_x1() + 1, (*itCo).Get_y1() + 1, (*itCo).Get_z1() + 1, (*itCo).Get_x2() - 1, (*itCo).Get_y2() - 1, (*itCo).Get_z2() - 1, (*itCo).Get_Tipo(), (*itCo).Get_Num(), (*itCo).Get_orig());
					para_eliminar.push_back(C);
					eliminar[j] -= (*itCo).Get_Num();
					continue;
				}
				for (int z = 0; z < (*itCo).Get_dz() && eliminar[j] > 0; z++)
				{
					int sumoz = (((*itCo).Get_z2() - (*itCo).Get_z1()) / (*itCo).Get_dz());
					for (int x = 0; x < (*itCo).Get_dx() && eliminar[j] > 0; x++)
					{
						int sumox = (((*itCo).Get_x2() - (*itCo).Get_x1()) / (*itCo).Get_dx());
						for (int y = 0; y < (*itCo).Get_dy() && eliminar[j] > 0; y++)
						{
							int sumoy = (((*itCo).Get_y2() - (*itCo).Get_y1()) / (*itCo).Get_dy());
							CONFIGURACAO C(this, j, (*itCo).Get_x1() + x * sumox + 1, (*itCo).Get_y1() + y * sumoy + 1, (*itCo).Get_z2() - (z + 1) * sumoz + 1, (*itCo).Get_x1() + (x + 1) * sumox - 1, (*itCo).Get_y1() + (y + 1) * sumoy - 1, (*itCo).Get_z2() - z * sumoz - 1, 1, 1, 1);
							para_eliminar.push_back(C);
							eliminar[j]--;
						}
					}
				}
				break;
			}
		}
		std::set<int>::iterator itset;
		int aa = 0;
		if (comprobar)
		{
			int volu = 0;
			for (itset = seleccionados.begin(); itset != seleccionados.end(); itset++)
			{
				int ab = 0;
				for (int j = 0; j < m_Q; j++)
					ab += m_Pedidos_candidatos[*itset].Get_faltan()[j] * m_Pieces[j].Get_Volumen();
				volu += m_Pedidos_candidatos[*itset].Get_Volumen() - ab;
			}
			for (int i = 0; i < m_num_pedidos; i++)
			{
				if (m_Pedidos[i].Get_complete() == true)
					volu += m_Pedidos[i].Get_Volumen();
			}
			printf("%d\n", volu);
			aa = 0;
			std::list<CONFIGURACAO>::iterator itC1 = m_Configuracaos.begin(), itfinC1 = m_Configuracaos.end();
			for (; itC1 != itfinC1; itC1++)
				aa += (*itC1).Get_Volumen();
		}
		std::list<CONFIGURACAO>::iterator it2 = para_eliminar.begin(), it2fin = para_eliminar.end();
		//Eliminamos las cajas que sobran
		for (; it2 != it2fin; it2++)
			ActualizarListaDeBloques(*it2, m_Configuracaos, true);
		for (int j = 0; j < m_Q; j++)
			m_Pieces[j].Set_Num(0);
		std::list<CONFIGURACAO>::iterator ittt;
		for (ittt = m_Configuracaos.begin(); ittt != m_Configuracaos.end(); ittt++)
		{
			m_Pieces[(*ittt).Get_Id()].Add_Num((*ittt).Get_Num());
		}
		int bb = 0;
		if (comprobar)
		{
			std::list<CONFIGURACAO>::iterator itC1 = m_Configuracaos.begin(), itfinC1 = m_Configuracaos.end();
			for (itC1 = m_Configuracaos.begin(); itC1 != m_Configuracaos.end(); itC1++)
				bb += (*itC1).Get_Volumen();
			printf("%d\t%d\n", aa, bb);
			std::vector<int> v;
			for (int j = 0; j < m_Q; j++)
				v.push_back(0);
			for (itC1 = m_Configuracaos.begin(); itC1 != m_Configuracaos.end(); itC1++)
				v[(*itC1).Get_Id()] += (*itC1).Get_Num();

			for (itSet = seleccionados.begin(); itSet != seleccionados.end(); itSet++)
			{
				for (int j = 0; j < m_Q; j++)
				{
					v[j] += m_Pedidos_candidatos[*itSet].Get_faltan()[j];
				}
			}
			for (int j = 0; j < m_Q; j++)
			{
				if (v[j] != m_Pieces[j].Get_q())
					printf("mal piezasss");
			}
		}
		std::list<SPACE> spaces_guardada = m_Spaces;
		CompactarConfiguracaos(m_Configuracaos);
		/*PintarSolucion(m_Configuracaos);*/
		std::list<CONFIGURACAO> lista = m_Configuracaos;
		std::list<CONFIGURACAO> conf_guardada = m_Configuracaos;
		piezas_guardada = m_Pieces;

		m_Configuracaos.clear();
		m_Spaces.clear();
		for (int j = 0; j < m_Q; j++)
			m_Pieces[j].Set_Num(0);
		//Intentamos colocar todos los pedidos candidatos, si no es posible lo intentamos de uno en uno
		Constructivo(false);
		
		if (ComprobarConfiguracaosNoIntersectan(m_Configuracaos)==true)
			printf("MAL11");
		int cont = 0;
		for (int j = 0; j < m_Q; j++)
		{
			if (m_Pieces[j].Get_Num() == m_Pieces[j].Get_q())
			{
				cont++;
				continue;
			}
			m_Spaces = spaces_guardada;
			m_Pieces = piezas_guardada;
			m_Configuracaos = conf_guardada;
			/*break;*/
		}
		if (cont == m_Q)
		{
			m_completos += m_Pedidos_candidatos.size() - no_seleccionados.size();
			for (int i = 0; i < m_Pedidos_candidatos.size(); i++)
			{
				if (no_seleccionados.find(i) == no_seleccionados.end())
				{
					m_Pedidos_candidatos[i].Set_complete(true);
					m_Pedidos_candidatos[i].Set_flag(true);
					m_Pedidos[m_Pedidos_candidatos[i].Get_Id()].Set_flag(true);
					m_Pedidos[m_Pedidos_candidatos[i].Get_Id()].Set_complete(true);
					m_total_volumen_cs_ocupado += m_Pedidos_candidatos[i].Get_Volumen();
				}
			}
			ComprobarPedidos();
			/*PintarSolucion(m_Configuracaos);
			printf("%d pedidos completos\n", m_completos);
			for (int i = 0; i < m_num_pedidos; i++)
				printf("%d\t", m_Pedidos[i].Get_complete());*/
			/*if (contbucle == 2)
			{
				printf("3: %d\n", m_total_volumen_cs_ocupado);
			}*/
		}
		else
		{
			piezas_guardada = m_Pieces;
			
			for (int k = 0; k < m_Pedidos_candidatos.size(); k++)
			{
				if (no_seleccionados.find(k) != no_seleccionados.end())
					continue;
				if (imprimir)
					printf("k: %d\n", k);
				for (int j = 0; j < m_Q; j++)
				{
					m_Pieces[j].Set_Q(m_Pieces[j].Get_q() - m_Pedidos_candidatos[k].Get_faltan()[j]);
					if (imprimir && m_Pedidos_candidatos[k].Get_faltan()[j] > 0)
						printf("pedido: %d\t caja: %d\t faltan: %d\n", m_Pedidos_candidatos[k].Get_Id(), j, m_Pedidos_candidatos[k].Get_faltan()[j]);
				}
			}
			for (itSet = seleccionados.begin(); itSet != seleccionados.end(); itSet++)
				m_Pedidos_candidatos[*itSet].Set_flag(false);
			/*if (contbucle == 2)
			{
				printf("4: %d\t%d\t%d\n", m_total_volumen_cs_ocupado, m_num_pedidos-1, m_completos);
				for (int k = 0; k < m_Pedidos_candidatos.size(); k++)
					printf("Pedido %d: %d\t", m_Pedidos_candidatos[k].Get_Id(), m_Pedidos_candidatos[k].Get_complete());
				printf("\n");
			}*/
			//printf("completos %d\n", m_completos);
			/*for (int i = 0; i < m_num_pedidos; i++)
			{
				if (m_Pedidos[i].Get_complete())
					printf("%d: %d\n", i, 1);
				else
					printf("%d: %d\n", i, 0);
			}
			printf("\n");*/
			ComprobarPedidos();
			/*for (int i = 0; i < m_num_pedidos; i++)
			{
				if (m_Pedidos[i].Get_complete())
					printf("%d: %d\n", i, 1);
				else
					printf("%d: %d\n", i, 0);
			}
			printf("\n");*/
			while(m_num_pedidos - 1 != m_completos)
			{
				switch (get_random(1, 3))
				{
				case 1:
				{
					ElegirPedidoVolumenDentro(m_Pedidos_candidatos);
					break;
				}
				case 2:
				{
					ElegirPedidoVolumenFuera(m_Pedidos_candidatos);
					break;
				}
				case 3:
				{
					ElegirPedidoVolumenFueraPt(m_Pedidos_candidatos);
					break;
				}
				}
				if (m_candidato == 99999)
					break;
				/*if (contbucle == 2)*/
				//	printf("cand: %d\t%d\n\n", m_candidato, m_Pedidos_candidatos[m_candidato].Get_Id());
				int i = m_candidato;
				if (no_seleccionados.find(i) == no_seleccionados.end())
				{
					/*for (int i = 0; i < m_num_pedidos; i++)
					{
						if (m_Pedidos[i].Get_complete())
							printf("%d: %d\n", i, 1);
						else
							printf("%d: %d\n", i, 0);
					}
					printf("\n");*/
					ComprobarPedidos();
					if (imprimir)
						printf("i: %d\n", i);
					std::vector<PIECE>piez_g = m_Pieces;
					for (int j = 0; j < m_Q; j++)
						m_Pieces[j].Set_Q(m_Pieces[j].Get_q() + m_Pedidos_candidatos[i].Get_faltan()[j]);

					std::list<CONFIGURACAO> lista2 = m_Configuracaos;
					std::list<CONFIGURACAO> lista_guardada = m_Configuracaos;
					std::list<SPACE> spaces = m_Spaces;

					int mvol = m_total_volumen_ocupado;
					int mvolcs = m_total_volumen_cs_ocupado;
					/*ConstructivoCS(false);*/
					int cajas = 0;
					for (int j = 0; j < m_Q; j++)
					{
						if (m_Pedidos_candidatos[i].Get_faltan()[j] > 0)
						{
							cajas += m_Pedidos_candidatos[i].Get_faltan()[j];
							if (imprimir)
								printf("%d\t%d\t%d\t%d\n", j, m_Pieces[j].Get_x(), m_Pieces[j].Get_y(), m_Pieces[j].Get_z());
						}

					}
					if (imprimir)
					{
						printf("%d\t%d\t", m_Pedidos_candidatos[i].Get_Id(), cajas);
						PintarSolucion(lista2);
					}
					m_Random = true;
					m_Limite = 100;
					ConstruirSolucion(lista2, true);
					m_Random = false;
					/*for (int i = 0; i < m_num_pedidos; i++)
					{
						if (m_Pedidos[i].Get_complete())
							printf("%d: %d\n", i, 1);
						else
							printf("%d: %d\n", i, 0);
					}
					printf("\n");*/
					ComprobarPedidos();
					std::list<SPACE>::iterator itSp;
					std::vector<PIECE> piez;
					for (int j = 0; j < m_Q; j++)
					{
						if (m_Pieces[j].Get_q() - m_Pieces[j].Get_Num() > 0)
							piez.push_back(m_Pieces[j]);
					}
					if (imprimir)
					{
						for (int k = 0; k < piez.size(); k++)
							printf("%d\t%d\t%d\n", piez[k].Get_x(), piez[k].Get_y(), piez[k].Get_z());
					}
					MinimaDimension();
					if (comprobar)
					{
						int sumaa = 0;
						std::list<SPACE> Spa;
						for (itSp = m_Spaces.begin(); itSp != m_Spaces.end(); itSp++)
						{
							if ((*itSp).Get_dx() >= m_dimension_menor && (*itSp).Get_dy() >= m_dimension_menor && (*itSp).Get_dz() >= m_dimension_menor)
							{
								Spa.push_back(*itSp);
								sumaa++;
							}
						}
						printf("%d\n", sumaa);
						PintarSpaces(Spa);
					}
					for (int j = 0; j < m_Q; j++)
					{
						if (m_Pieces[j].Get_Num() != m_Pieces[j].Get_q())
						{
							ComprobarPedidos();
							if (imprimir)
								printf("%d\n", j);
							m_Pedidos_candidatos[i].Set_flag(true);
							m_Pedidos[m_Pedidos_candidatos[i].Get_Id()].Set_flag(true);
							m_Pieces = piez_g;
							m_Configuracaos = lista_guardada;
							m_Spaces = spaces;
							m_total_volumen_ocupado = mvol;
							m_total_volumen_cs_ocupado = mvolcs;
							ComprobarPedidos();
							break;
						}
					}
					if (m_Pedidos_candidatos[i].Get_flag() == false)
					{
						/*printf("candidato %d\t%d\n", i, m_Pedidos_candidatos[i].Get_Id());
						for (int i = 0; i < m_num_pedidos; i++)
						{
							if (m_Pedidos[i].Get_complete())
								printf("%d: %d\n", i, 1);
							else
								printf("%d: %d\n", i, 0);
						}
						for (int k = 0; k < m_Pedidos_candidatos.size(); k++)
						{
							if (m_Pedidos_candidatos[k].Get_complete())
								printf("%d: %d\n", m_Pedidos_candidatos[k].Get_Id(), 1);
							else
								printf("%d: %d\n", m_Pedidos_candidatos[k].Get_Id(), 0);
						}
						printf("\n");*/
						ComprobarPedidos();
						m_Pedidos_candidatos[i].Set_complete(true);
						m_Pedidos[m_Pedidos_candidatos[i].Get_Id()].Set_complete(true);
						m_completos++;
						m_total_volumen_cs_ocupado += m_Pedidos_candidatos[i].Get_Volumen();
						/*printf("%d\n", i);*/
						/*printf("candidato %d\t%d\n", i, m_Pedidos_candidatos[i].Get_Id());
						for (int i = 0; i < m_num_pedidos; i++)
						{
							if (m_Pedidos[i].Get_complete())
								printf("%d: %d\n", i, 1);
							else
								printf("%d: %d\n", i, 0);
						}*/
						/*for (int k = 0; k < m_Pedidos_candidatos.size(); k++)
						{
							if (m_Pedidos_candidatos[k].Get_complete())
								printf("%d: %d\n", m_Pedidos_candidatos[k].Get_Id(), 1);
							else
								printf("%d: %d\n", m_Pedidos_candidatos[k].Get_Id(), 0);
						}*/
						/*printf("\n");*/
						ComprobarPedidos();
					}
				}
			}
		}
		/*if (contbucle == 2)
		{
			if (ComprobarConfiguracaosNoIntersectan(m_Configuracaos) == true)
				printf("maaalalalala\n");
			std::vector<int> w;
			w.clear();
			for (int j = 0; j < m_Q; j++)
				w.push_back(0);
			for (int i = 0; i < m_num_pedidos; i++)
			{
				if (m_Pedidos[i].Get_complete() == true)
				{
					for (int j = 0; j < m_Q; j++)
						w[j] += m_Pedidos[i].Get_num_pieces_tipo()[j];
				}
			}
			for (ittt = m_Configuracaos.begin(); ittt != m_Configuracaos.end(); ittt++)
			{
				w[(*ittt).Get_Id()] -= (*ittt).Get_Num();
			}
			for (int j = 0; j < m_Q; j++)
			{
				if (w[j] > 0)
				{
					printf("comprov caja: %d cuantas: %d\n", j, w[j]);
					break;
				}
			}
			printf("%d\n", m_completos);
			printf("5: %d\n", m_total_volumen_cs_ocupado);
		}*/
		ComprobarPedidos();
		while (m_num_pedidos - 1 != m_completos)
		{
			switch (get_random(1, 3))
			{
			case 1:
			{
				ElegirPedidoVolumenDentro();
				break;
			}
			case 2:
			{
				ElegirPedidoVolumenFuera();
				break;
			}
			case 3:
			{
				ElegirPedidoVolumenFueraPt();
				break;
			}
			}
			if (m_candidato == 99999)
				break;
			std::vector<PIECE> piezas2 = m_Pieces;
			for (int j = 0; j < m_Q; j++)
				m_Pieces[j].Set_Q(m_Pieces[j].Get_q() + m_Pedidos[m_candidato].Get_num_pieces_tipo()[j]);
			std::list<CONFIGURACAO> lista2 = m_Configuracaos;
			std::list<SPACE> spaces = m_Spaces;
			
			int mvol = m_total_volumen_ocupado;
			int mvolcs = m_total_volumen_cs_ocupado;
			ConstructivoCS(false);
			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pieces[j].Get_Num() != m_Pieces[j].Get_q())
				{
					m_Pedidos[m_candidato].Set_flag(true);
					m_Pieces = piezas2;
					m_Configuracaos = lista2;
					m_Spaces = spaces;
					/*
					m_Configuracaos = configuracaos;*/
					m_total_volumen_ocupado = mvol;
					m_total_volumen_cs_ocupado = mvolcs;
					break;
				}
			}
			if (m_Pedidos[m_candidato].Get_flag() == false)
			{
				m_Pedidos[m_candidato].Set_complete(true);
				m_completos++;
				m_total_volumen_cs_ocupado += m_Pedidos[m_candidato].Get_Volumen();
				ComprobarPedidos();
			}
		}
		ComprobarPedidos();
		/*if (contbucle == 2)
		{
			printf("6: %d\n", m_total_volumen_cs_ocupado);
		}*/
		double ptt = m_total_volumen_cs_ocupado / ((double)m_X * m_Y * m_Z)*100;
		std::vector<int> w;
		w.clear();
		for (int j = 0; j < m_Q; j++)
			w.push_back(0);
		for (int i = 0; i < m_num_pedidos; i++)
		{
			if (m_Pedidos[i].Get_complete() == true)
			{
				for (int j = 0; j < m_Q; j++)
					w[j] += m_Pedidos[i].Get_num_pieces_tipo()[j];
			}
		}
		for (ittt = m_Configuracaos.begin(); ittt != m_Configuracaos.end(); ittt++)
		{
			w[(*ittt).Get_Id()] -= (*ittt).Get_Num();
		}
		for (int j = 0; j < m_Q; j++)
		{
			if (w[j] > 0)
			{
				printf("comprov caja: %d cuantas: %d\n", j, w[j]);
				break;
			}
		}
		/*PintarSolucion(m_Configuracaos);
		printf("%d pedidos completos\n", m_completos);
		for (int i = 0; i < m_num_pedidos; i++)
			printf("%d\t", m_Pedidos[i].Get_complete());*/

		m_fintime = clock();
		m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
		//printf("%d\t%f\t%f\tcoef: %f\n", m_total_volumen_cs_ocupado, ptt, m_tiempo, coef);
		int vo = 0;
		for (int i = 0; i < m_num_pedidos; i++)
		{
			if (m_Pedidos[i].Get_complete() == true)
				vo += m_Pedidos[i].Get_Volumen();
		}
		/*if (vo != m_total_volumen_cs_ocupado)
			exit(15);*/
		/*if (m_total_volumen_cs_ocupado > m_X* m_Y* m_Z)
		{
			printf("pasas\n");
		}*/
		if (m_total_volumen_cs_ocupado > volumen_iterar)
			volumen_iterar = m_total_volumen_cs_ocupado;
		m_fintime = clock();
		m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
	} while (m_tiempo<m_tiempo_final_total);
	if (volumen_iterar < volcsguardado)
		printf("vamal");
	FILE* fincs;
	fincs = fopen(m_file_to_write, "a+");
	double ptcs = ((double)volumen_iterar / (double)((double)m_X * m_Y * m_Z)) * 100;
	double ptcs1= ((double)volcsguardado / (double)((double)m_X * m_Y * m_Z)) * 100;
	fprintf(fincs, "%s\t%d\t%f\t%d\t%f\n", m_Nombre, volcsguardado, ptcs1, volumen_iterar, ptcs);
	fclose(fincs);
}
void CONTAINER::VNSCS()
{
	//Función que llama al VNS con las cajas exactas de los pedidos que el bouknap nos da como solución
	int voltotal = m_total_volumen;
	//Primero corremos el VNS sin Complete Shipment para tener una primera cota superior
	m_Random = false;
	m_complete_shipment = false;
	m_imprimir = false;
	m_time_final = m_tiempo_final_total / 10;
	VNS(true); 
	m_complete_shipment = true;
	int cantidad_cota = 1;
	m_max_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();
	/*printf("total: %d\tcs: %d\n", m_total_volumen_ocupado, m_max_total_volumen_cs_ocupado);*/
	int cota_para_knapsack = m_total_volumen_ocupado; //Con esta cota, resolvemos un knapsack que nos diga qué pedidos caben por volumen
	double pt = (((double)m_total_volumen_ocupado) / ((double)((double)m_X * m_Y * m_Z))) * 100;
	double pt2= (((double)m_max_total_volumen_cs_ocupado) / ((double)((double)m_X * m_Y * m_Z))) * 100;
	printf("total: %d\t%f\tcs: %d\t%f\n", m_total_volumen_ocupado, pt, m_max_total_volumen_cs_ocupado, pt2);
	std::vector<PEDIDO>::iterator itP = m_Pedidos.begin();
	int numpedidos = m_Pedidos.size();
	std::vector<PIECE>piezas_max=m_Pieces;
	//Se crean los vectores de enteros, profit es lo que ganamos
	//weight es el peso 
	//m cuántos de esa pieza
	//x sería la solución
	int max = 0, todas = 0;
	int* profit = (int*)calloc(numpedidos, sizeof(int));
	int* weight = (int*)calloc(numpedidos, sizeof(int));
	int* m = (int*)calloc(numpedidos, sizeof(int));
	int* x = (int*)calloc(numpedidos, sizeof(int));
	/*int* xguardo = (int*)calloc(numpedidos, sizeof(int));*/
	/*for (int i = 0; i < 150; i++)
	{
		weight[i] = 0;
		profit[i] = 0;
		m[i] = 0;
		x[i] = 0;
	}*/
	for (int i = 0; i < numpedidos; i++)
	{
		int d = m_Pedidos[i].Get_Volumen();
		profit[i] = (int)d;
		weight[i] = (int)d;
		//en este caso todos sería de 1
		m[i] = 1;
		x[i] = 0;
	}
	/*FILE* fincs;
	fincs = fopen(m_file_to_write, "a+");
	fprintf(fincs, "numpedidos: %d\t cotaparaknapsack: %d\n", numpedidos, cota_para_knapsack);
	fprintf(fincs, "i\t profit\t weight\t m\t x\n");
	for (int i = 0; i < numpedidos; i++)
		fprintf(fincs, "%d\t %d\t %d\t %d\t %d\n", i, profit[i], weight[i], m[i], x[i]);
	fclose(fincs);*/
	double porc = 0;
	int cont = 0;
	bool primero = true;
	bool prim = true;
	int cota_max = 0;
	bool salir = false;
	do
	{
		printf("\ncont: %d\n\n", cont);
		for (int i = 0; i < m_Q; i++)
		{
			m_Pieces[i].Set_Q(0);
			m_Pieces[i].Set_Num(0);
		}
		int contar = 0;
		do {
			contar++;
			for (int i = 0; i < numpedidos; i++)
				x[i] == 0;
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "numpedidos: %d\t cotaparaknapsack: %d\n", numpedidos, cota_para_knapsack);
			fprintf(fincs, "i\t profit\t weight\t m\t x\n");
			for (int i = 0; i < numpedidos; i++)
				fprintf(fincs, "%d\t %d\t %d\t %d\t %d\n", i, profit[i], weight[i], m[i], x[i]);
			fclose(fincs);*/
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p0\n");
			fclose(fincs);*/
			
			m_cota_cs = bouknap(numpedidos, profit, weight, m, x, cota_para_knapsack);

			printf("%d\n", m_cota_cs);
			/*FILE* fincs;*/
			/*fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p1\n");
			fclose(fincs);*/
			if (m_cota_cs >= cota_max && prim == false)
			{
				/*FILE* fincs;
				fincs = fopen(m_file_to_write, "a+");
				fprintf(fincs, "p2\n");
				fclose(fincs);*/
				break;
			}
			if (prim == true)
			{
			/*	FILE* fincs;
				fincs = fopen(m_file_to_write, "a+");
				fprintf(fincs, "p3\n");
				fclose(fincs);*/
				cota_max = m_cota_cs; //No tiene sentido intentar meter pedidos con volumen mayor a este
			}
			
		/*	printf("m cota cs: %d\t max cs: %d\n", m_cota_cs, m_max_total_volumen_cs_ocupado);*/
			if (m_cota_cs <= m_max_total_volumen_cs_ocupado)
			{
				/*FILE* fincs;
				fincs = fopen(m_file_to_write, "a+");
				fprintf(fincs, "p4\n");
				fclose(fincs);*/
				if (primero == true)
				{
					/*FILE* fincs;
					fincs = fopen(m_file_to_write, "a+");
					fprintf(fincs, "p5\n");
					fclose(fincs);*/
					primero = false;
					goto fin;
				}
				/*if (cantidad_cota > 0)
					printf("nopuedeser");*/
				if (cantidad_cota < 0)
					cota_para_knapsack = cota_para_knapsack - cantidad_cota - 1;
				else
				{
					m_cota_cs = cota_max;
					m_Pieces = piezas_max;
				}
			}
			primero = false;
			/*printf("cota_para_knapsack %d\n", cota_para_knapsack);*/
			m_fintime = clock();
			m_time_final = ((m_fintime - m_inicio) / CLOCKS_PER_SEC);
		} while (m_cota_cs <= m_max_total_volumen_cs_ocupado && m_time_final<m_tiempo_final_total/*&& contar<100*/);
		if (contar >= 100)
			goto fin;
		porc = (double)m_cota_cs / (double(m_X * m_Y * m_Z)) * 100;
		printf("knapsack: %d\t%f\n", m_cota_cs, porc);
		/*FILE* fincs;
		fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p6\n");
		fclose(fincs);*/
		if (cota_max == 0)
			printf("malproc2");
		if (m_cota_cs >= cota_max && prim == false)
		{
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p7\n");
			fclose(fincs);*/
			m_cota_cs = cota_max;
			m_Pieces = piezas_max;
			if (cantidad_cota > 0)
				cantidad_cota = (-1) * cantidad_cota;
			salir = true;
		}
		
		/*if (m_cota_cs == m_max_total_volumen_cs_ocupado)
			goto fin;*/
		//Si en algún momento hemos alcanzado esta cota, paramos porque ya lo tenemos
	/*	if (m_cota_cs == m_max_total_volumen_cs_ocupado)
			goto fin;*/
		//El knapsack devuelve los pedidos a colocar y el volumen que ocupan, y que será el volumen con CS si conseguimos meterlos todos
		double ptcs = (double)m_cota_cs / ((double)((double)m_X * m_Y * m_Z)) * 100;
		/*printf("COTA=%f\t%d\n", ptcs, m_cota_cs);*/
		//Ahora sería recorrer x y de cada pedido tomar las cajas para intentar meterlas todas
		if (salir == false)
		{
			for (int i = 0; i < numpedidos; i++)
			{
				if (x[i] == 1)
				{
					for (int j = 0; j < m_Q; j++)
					{
						m_Pieces[j].Add_q(m_Pedidos[i].Get_num_pieces_tipo()[j]);
					}
				}
			}
		}
		
		if (prim == true)
			piezas_max = m_Pieces;
		prim = false;
		/*int vol = 0;
		for (int j = 0; j < m_Q; j++)
		{
			vol += m_Pieces[j].Get_Volumen()*m_Pieces[j].Get_q();
		}
		if (vol != m_cota_cs)
		{
			FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "vol: %d\tm_cota_cs: %d\n", vol, m_cota_cs);
			fprintf(fincs, "i\tx[i]\n");
			for (int i = 0; i < m_num_pedidos; i++)
				fprintf(fincs, "%d\t%d\n", i, x[i]);
			fclose(fincs);
		}*/
		/*FILE* fincs;*/
	/*	fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p8\t%d\n", m_cota_cs);
		fclose(fincs);*/
		m_fintime = clock();
		if (cantidad_cota < 0)
		{
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p9\t%d\n", m_cota_cs);
			fclose(fincs);*/
//			double tiempo_lleva = ((m_fintime - m_inicio) / CLOCKS_PER_SEC);
			m_time_final = m_tiempo_final_total ;
			//dejar el tiempo que quede
		}
		else
		{
		/*	FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p10\n");
			fclose(fincs);*/
			m_time_final = ((m_fintime - m_inicio) / CLOCKS_PER_SEC) + m_tiempo_final_total/10;
			//		m_time_final = ((m_fintime - m_inicio) / CLOCKS_PER_SEC) + (double)150;
		}
		m_total_volumen = m_cota_cs;
		m_imprimir = false;
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "pbis\n");
		
		for (int j = 0; j < m_Q; j++)
			fprintf(fincs, "j: %d\t q: %d\t num: %d\n", j, m_Pieces[j].Get_q(), m_Pieces[j].Get_Num());
		fclose(fincs);*/
		/*fprintf(fincs, "spaces: %d\t confs: %d\n", m_Spaces.size(), m_Configuracaos.size());*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "%d\t%d\n", m_total_volumen, m_cota_cs);*/
		VNS(true); //Con el VNS intentamos colocar todos los pedidos devueltos por el knapsack
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p11\n");
		fclose(fincs);*/
		ptcs = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		pt = ((double)m_max_total_volumen_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
		printf("%d\t%d\t%d\t%f\t%d\t%f\t%d\t%f\n", (m_X * m_Y * m_Z), m_total_volumen, m_max_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs, cont, m_tiempo);
		//Me voy guardando la mejor solución de complete shipment
		if (m_total_volumen_cs_ocupado >= m_max_total_volumen_cs_ocupado)
		{
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p12\n");
			fclose(fincs);*/
				m_max_total_volumen_cs_ocupado = m_total_volumen_cs_ocupado;
				m_Best_CS_Configuracaos = m_Configuracaos;
				if (m_total_volumen_cs_ocupado == m_total_volumen) //Hemos conseguido meter todo
				{
					/*FILE* fincs;
					fincs = fopen(m_file_to_write, "a+");
					fprintf(fincs, "p13\n");
					fclose(fincs);*/
					//sube
					if (cantidad_cota > 0)
						cantidad_cota = (-1) * cantidad_cota / 2;
					else
						cantidad_cota=cantidad_cota/2;
				}
				else
				{
					/*FILE* fincs;
					fincs = fopen(m_file_to_write, "a+");
					fprintf(fincs, "p14\n");
					fclose(fincs);*/
					//baja
					cantidad_cota = m_cota_cs - m_max_total_volumen_ocupado;

				}


		}
		else
		{
			/*FILE* fincs;
			fincs = fopen(m_file_to_write, "a+");
			fprintf(fincs, "p15\n");
			fclose(fincs);*/
			//baja
			cantidad_cota = m_cota_cs - m_max_total_volumen_ocupado;
		}
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p16\n");
		fclose(fincs);*/
		cota_para_knapsack = m_cota_cs - cantidad_cota;
		m_fintime = clock();
		m_time_final = ((m_fintime - m_inicio) / CLOCKS_PER_SEC);
		cont++;
		/*FILE* fincs;*/
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p17\n");
		fclose(fincs);*/
	} while (salir == false && m_max_total_volumen_cs_ocupado != voltotal && m_time_final < m_tiempo_final_total && !(cont==1 && m_max_total_volumen_cs_ocupado == m_total_volumen));
fin:
	
	/*fincs = fopen(m_file_to_write, "a+");
	fprintf(fincs, "p18\n");
	fclose(fincs);*/
	FILE* fincs;
	fincs = fopen(m_file_to_write, "a+");
	double ptcs = ((double)m_max_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;
	fprintf(fincs, "%s\t%d\t%d\t%f\t%d\t%f\n", m_Nombre, (m_X * m_Y * m_Z), m_max_total_volumen_cs_ocupado, ptcs, cont, m_tiempo);
	fclose(fincs);
}
void CONTAINER::Constructivo_random()
{
	m_Random = true;
	paraprobar = true;
	paraprobar2 = true;
	idbloque = 0;
	double time = 100;
	SetVerificar(true);
	SetDibujar(false);
	std::vector<PIECE> piezas = m_Pieces;
	bool parar = false;
	//ConstruirSolucion
//	m_rotacion = true;
	m_por_bin = false;
	m_eliminar_espacios = false;
	m_mejora_local = false;
	//	m_descendent = false;
	m_objetivo_capas = true;
	m_Aleatorizado = false;
	m_un_movimiento = true;
	m_max_movimientos = 10;
	int vol = 0;
	m_imprimir = false;
	std::list<CONFIGURACAO> mejor_solucion;
	int cont = 0;
	int i = 0;
	for (; i < 100000 && m_tiempo < m_time_final; i++)
	{
		m_Pieces = piezas;
		m_Configuracaos.clear();
		m_Spaces.clear();
		m_total_volumen_ocupado = 0;
		Constructivo(false);
		/*SetDibujar(true);
		DibujarOpenGL(m_Configuracaos);
		SetDibujar(false);*/
		if (m_total_volumen_ocupado > vol)
		{
			vol = m_total_volumen_ocupado;
			mejor_solucion = m_Configuracaos;
		}
		m_fintime = clock();
		m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
	}
	double pt = ((double)vol / (double)((double)m_X * m_Y * m_Z)) * 100;
	m_fintime = clock();
	m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
	FILE* fichero;
	fichero = fopen(m_file_to_write, "a+");
	fprintf(fichero, "%d\t%d\t%f\t%d\t%f\n", m_total_volumen, vol, pt, i+1, m_tiempo);
	fclose(fichero);
}

void CONTAINER::Constructivo_random_cs()
{
	paraprobar = true;
	paraprobar2 = true;
	idbloque = 0;
	double time = 100;
	SetVerificar(true);
	SetDibujar(false);
	std::vector<PIECE> piezas = m_Pieces;
	bool parar = false;
	//ConstruirSolucion
//	m_rotacion = true;
	m_por_bin = false;
	m_eliminar_espacios = false;
	m_mejora_local = false;
	//	m_descendent = false;
	m_objetivo_capas = true;
	m_Aleatorizado = false;
	m_un_movimiento = true;
	m_max_movimientos = 10;
	int vol = 0;
	int voltotal = 0;
	int volum = 0;
	int numcajastemp = 0;
	int numcajas = 0;
	int pedidoscompletos = 0;
	std::list<CONFIGURACAO> mejor_solucion;
	std::vector<int> faltan;
	int cont = 0;
	int minimo = m_X*m_Y*m_Z;
	double m_tiempo_bucle = 0;
	double m_tiempo_constr = 0;
	bool entra = false;
	m_tiempo = 0;
	int tiem = 30;
	int k;
	for (k = 0; k < 100000 && m_tiempo < m_time_final; k++)
	{
		m_Random = true;
		/*printf("%d\n", k);*/
		for (int i = 0; i < m_num_pedidos; i++)
			m_Pedidos[i].Set_flag(false);
		m_Pieces = piezas;
		m_Configuracaos.clear();
		m_Spaces.clear();
		m_total_volumen_ocupado = 0;
		m_total_volumen_cs_ocupado = 0;
		//Construimos hasta el m_Limite % de la capacidad del contenedor
		m_imprimir = false;
		m_inicio_constr = clock();
		Constructivo(false);
		
		m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();
		
		std::vector<PIECE>piezas3 = m_Pieces;
		std::list<CONFIGURACAO> lista3 = m_Configuracaos;
		std::list<SPACE> spaces3 = m_Spaces;
		int mvol1 = m_total_volumen_ocupado;
		int mvolcs1 = m_total_volumen_cs_ocupado;
		std::vector<int> pedidos_entran;
		do
		{
			ElegirPedidoVolumenDentro();
			faltan.clear();
			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pedidos[m_candidato].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()) >= 0)
					faltan.push_back(m_Pedidos[m_candidato].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()));
				else
					faltan.push_back(0);
			}
			if (m_candidato != 99999)
				break;
			m_Pedidos[m_candidato].Set_flag(true);
			pedidos_entran.push_back(m_candidato);
			for (int j = 0; j < m_Q; j++)
				m_Pieces[j].Set_Q(m_Pieces[j].Get_Num() + faltan[j]);
		} while (m_candidato != 99999);
			m_Random = false;
			bool mblo = m_por_bloques;
			bool mbloara = m_por_bloques_ara;
			m_por_bloques_ara = false;
			m_por_bloques = false;
			/*ConstruirSolucion(lista, true);*/
			bool m_old_eliminar = m_eliminar_espacios;
			m_eliminar_espacios = false;
			std::list<SPACE>::iterator itS = m_Spaces.begin(), itSfin = m_Spaces.end();
			for (; itS != itSfin; itS++)
				(*itS).Set_Flag(false);
			ConstructivoCS(false);
			m_eliminar_espacios = m_old_eliminar;
			m_por_bloques = mblo;
			m_por_bloques_ara = mbloara;

			/*std::list<CONFIGURACAO> configuracaos=m_Configuracaos;*/
			/*m_Configuracaos.clear();
			m_Spaces.clear();*/

			/*m_total_volumen_ocupado = 0;*/
			/*m_total_volumen_cs_ocupado = 0;*/
			/*for (int j = 0; j < m_Q; j++)
				m_Pieces[j].Set_Num(0);*/
				/*Generar_Bloques(m_perdida, 10000, m_full_supported);

				Constructivo(false);*/
				/*m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();*/
			bool entra = false;
			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pieces[j].Get_Num() != m_Pieces[j].Get_q())
				{
					for (int i = 0; i < m_num_pedidos; i++)
					{
						if (m_Pedidos[i].Get_complete() == false)
							m_Pedidos[i].Set_flag(false);
					}
					m_Pieces = piezas3;
					m_Configuracaos = lista3;
					m_Spaces = spaces3;
					/*
					m_Configuracaos = configuracaos;*/
					m_total_volumen_ocupado = mvol1;
					m_total_volumen_cs_ocupado = mvolcs1;
					entra = true;
					break;
				}
			}
			if (entra == false)
			{
				for (int k = 0; k < pedidos_entran.size(); k++)
				{
					m_Pedidos[pedidos_entran[k]].Set_complete(true);
					m_total_volumen_cs_ocupado += m_Pedidos[pedidos_entran[k]].Get_Volumen();
					for (int j = 0; j < m_Q; j++)
						m_Pieces[j].Add_asign(m_Pedidos[pedidos_entran[k]].Get_num_pieces_tipo()[j]);
				}
				m_completos += pedidos_entran.size();
				
				double pt = (double)m_total_volumen_cs_ocupado / ((double)m_X * m_Y * m_Z) * 100;
				/*printf("%f\n", pt);*/
			}
		

		/*double pt = (double)m_total_volumen_cs_ocupado / ((double)m_X * m_Y * m_Z) * 100;
		double pt2 = (double)m_total_volumen_ocupado / ((double)m_X * m_Y * m_Z) * 100;*/
		/*printf("%f\t%f\n", pt2, pt);*/
		m_fin_constr = clock();
		m_tiempo_constr += ((double)((double)m_fin_constr - m_inicio_constr)) / CLOCKS_PER_SEC;
		m_inicio_bucle = clock();
		do {
			switch (get_random(1, 3))
			{
				case 1:
				{
					ElegirPedidoVolumenDentro();
					break;
				}
				case 2:
				{
					ElegirPedidoVolumenFuera();
					break;
				}
				case 3:
				{
					ElegirPedidoVolumenFueraPt();
					break;
				}
			}
			if (m_candidato == 99999) //Si no entra es o que están todos completos o porque los he probado y no caben (todos con flag=true)
				break;
			
			faltan.clear();
			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pedidos[m_candidato].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()) >= 0)
					faltan.push_back(m_Pedidos[m_candidato].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()));
				else
					faltan.push_back(0);
			}
			std::vector<PIECE>piezas2 = m_Pieces;
			for (int j = 0; j < m_Q; j++)
				m_Pieces[j].Set_Q(m_Pieces[j].Get_Num() + faltan[j]);
			/*for (int j = 0; j < m_Q; j++)
				printf("%d\t", faltan[j]);
			printf("\n");
			for (int i = 0; i < m_num_pedidos; i++)
			{
				if (m_Pedidos[i].Get_complete() == false)
				{
					printf("pedido: %d\t", i);
					for (int j = 0; j < m_Q; j++)
						printf("%d\t", m_Pedidos[i].Get_num_pieces_tipo()[j]);
					printf("\n");
				}
			}
			for (int j = 0; j < m_Q; j++)
				printf("%d\t", m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas());
			printf("\n%d\n", m_candidato);*/
			std::list<CONFIGURACAO> lista = m_Configuracaos;
			std::list<CONFIGURACAO> lista2 = m_Configuracaos;
			std::list<SPACE> spaces = m_Spaces;
			
			m_Random = false;
			bool mblo = m_por_bloques;
			bool mbloara = m_por_bloques_ara;
			m_por_bloques_ara = false;
			m_por_bloques=false;
			/*ConstruirSolucion(lista, true);*/
			bool m_old_eliminar = m_eliminar_espacios;
			m_eliminar_espacios = false;
			int mvol = m_total_volumen_ocupado;
			int mvolcs = m_total_volumen_cs_ocupado;
			std::list<SPACE>::iterator itS = m_Spaces.begin(), itSfin=m_Spaces.end();
			for (; itS != itSfin; itS++)
				(*itS).Set_Flag(false);
			ConstructivoCS(false);
			m_eliminar_espacios = m_old_eliminar;
			m_por_bloques = mblo;
			m_por_bloques_ara = mbloara;
			
			/*std::list<CONFIGURACAO> configuracaos=m_Configuracaos;*/
			/*m_Configuracaos.clear();
			m_Spaces.clear();*/
			
			/*m_total_volumen_ocupado = 0;*/
			/*m_total_volumen_cs_ocupado = 0;*/
			/*for (int j = 0; j < m_Q; j++)
				m_Pieces[j].Set_Num(0);*/
			/*Generar_Bloques(m_perdida, 10000, m_full_supported);
			
			Constructivo(false);*/
			/*m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();*/
			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pieces[j].Get_Num() != m_Pieces[j].Get_q())
				{
					m_Pedidos[m_candidato].Set_flag(true);
					m_Pieces = piezas2;
					m_Configuracaos = lista2;
					m_Spaces = spaces;
					/*
					m_Configuracaos = configuracaos;*/
					m_total_volumen_ocupado = mvol;
					m_total_volumen_cs_ocupado = mvolcs;
					break;
				}
			}
			if (m_Pedidos[m_candidato].Get_flag() == false)
			{
				m_Pedidos[m_candidato].Set_complete(true);
				for (int j = 0; j < m_Q; j++)
					m_Pieces[j].Add_asign(m_Pedidos[m_candidato].Get_num_pieces_tipo()[j]);
				m_completos++;
				m_total_volumen_cs_ocupado += m_Pedidos[m_candidato].Get_Volumen();
				double pt = (double)m_total_volumen_cs_ocupado / ((double)m_X * m_Y * m_Z) * 100;
				/*printf("%f\n", pt);*/
			}
		} while (m_completos != m_num_pedidos);

		/*pt = ((double)m_total_volumen_cs_ocupado / (double)((double)m_X * m_Y * m_Z)) * 100;*/
		m_fin_bucle = clock();
		m_tiempo_bucle += ((double)((double)m_fin_bucle - m_inicio_bucle)) / CLOCKS_PER_SEC;
		/*m_fintime = clock();
		m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;*/
		/*FILE* fichero;
		fichero = fopen(m_file_to_write, "a+");
		fprintf(fichero, "%d\t%d\t%f\t%d\t%f\t%f\t%f\n", m_total_volumen, m_total_volumen_cs_ocupado, pt, k+1, m_tiempo_constr, m_tiempo_bucle, m_tiempo);
		fclose(fichero);*/
		if (m_total_volumen_ocupado > voltotal)
			voltotal = m_total_volumen_ocupado;
		if (m_total_volumen_cs_ocupado > vol)
		{
			pedidoscompletos = m_completos;
			vol = m_total_volumen_cs_ocupado;
			mejor_solucion = m_Configuracaos;
		}
		m_fintime = clock();
		m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
		
		/*if (m_tiempo >= tiem)
		{
			tiem += 30;
			FILE* fin3;
			fin3 = fopen(m_file_to_write, "a+");
			double pt = ((double)voltotal / (double)((double)m_X * m_Y * m_Z)) * 100;
			double ptcs = ((double)vol / (double)((double)m_X * m_Y * m_Z)) * 100;
			fprintf(fin3, "%s\t%d\t%d\tVU\t%d\t%f\t%d\t%f\t%d\t%f\n", m_Nombre, (m_X * m_Y * m_Z), m_total_volumen, voltotal, pt, vol, ptcs, k, m_tiempo);
			fclose(fin3);
		}*/
	}
	double ptcs = ((double)vol / (double)((double)m_X * m_Y * m_Z)) * 100;
	double pt = ((double)voltotal / (double)((double)m_X * m_Y * m_Z)) * 100;
	m_fintime = clock();
	m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
	FILE* fichero;
	fichero = fopen(m_file_to_write, "a+");
	fprintf(fichero, "%d\t%d\t%f\t%d\t%f\t%d\t%d\t%f\t%f\t%f\n", m_total_volumen, voltotal, pt, vol, ptcs, pedidoscompletos, k+1, m_tiempo_constr, m_tiempo_bucle, m_tiempo);
	fclose(fichero);
}

void CONTAINER::ConstruccionPorPedidos()
{
	std::vector<PIECE>piezas = m_Pieces;
	int volmejor = 0;
	do
	{
		m_completos = 0;
		m_total_volumen_cs_ocupado = 0;
		SPACE Space(0, 0, 0, m_X, m_Y, m_Z, this);
		m_Spaces.clear();
		m_Spaces.push_back(Space);
		m_Configuracaos.clear();
		m_Pieces = piezas;
		for (int i = 0; i < m_num_pedidos; i++)
		{
			m_Pedidos[i].Set_complete(false);
			m_Pedidos[i].Set_flag(false);
		}
		m_Pedidos_ordenados.clear();
		for (int i = 0; i < m_num_pedidos; i++)
			InsertarPedidoOrden(m_Pedidos[i]);
		paraprobar = true;
		paraprobar2 = true;
		idbloque = 0;
		double time = 100;
		SetVerificar(true);
		SetDibujar(false);
		std::vector<PIECE> piezas = m_Pieces;
		for (int i = 0; i < m_Q; i++)
			m_Pieces[i].Set_Q(0);
		bool parar = false;
		//ConstruirSolucion
	//	m_rotacion = true;
		m_por_bin = false;
		m_eliminar_espacios = false;
		m_mejora_local = false;
		//	m_descendent = false;
		m_objetivo_capas = true;
		m_Aleatorizado = false;
		m_un_movimiento = true;
		m_max_movimientos = 10;
		int vol = 0;
		int voltotal = 0;
		int volum = 0;
		int numcajastemp = 0;
		int numcajas = 0;
		int pedidoscompletos = 0;
		std::list<CONFIGURACAO> mejor_solucion;
		std::vector<int> faltan;
		int cont = 0;
		int minimo = m_X * m_Y * m_Z;
		double m_tiempo_bucle = 0;
		double m_tiempo_constr = 0;
		bool entra = false;
		m_tiempo = 0;
		int tiem = 30;
		int k;
		double pt = 0;
		int contpedidos = 0;
		std::vector<int> vectorandom;
		for (int i = 0; i < m_num_pedidos; i++)
			vectorandom.push_back(i);
		std::set<int>::iterator itr;
		int indicerandom = 0;

		/* Elección pedido(s) */
		/*for (int i = 0; i < m_num_pedidos; i++)
			{
				m_candidato = i;*/						//Esto sería del pedido mayor al menor
				/*for (int i = m_num_pedidos-1; i >= 0; i--)
					{
						m_candidato = i;*/						//Esto sería del pedido menor al mayor
		while (vectorandom.size() > 0)
		{
			indicerandom = get_random(0, vectorandom.size() - 1);
			m_candidato = vectorandom[indicerandom];					//Esto sería eligiendo los pedidos aleatoriamente
			vectorandom.erase(vectorandom.begin() + indicerandom);
			std::vector<PIECE>piezas2 = m_Pieces;
			/*Constructivo*/
			for (int j = 0; j < m_Q; j++)
				m_Pieces[j].Add_q(m_Pedidos_ordenados[m_candidato].Get_num_pieces_tipo()[j]);

			std::list<CONFIGURACAO> lista = m_Configuracaos;
			std::list<CONFIGURACAO> lista2 = m_Configuracaos;
			std::list<SPACE> spaces = m_Spaces;
			m_Random = false;
			bool mblo = m_por_bloques;
			bool mbloara = m_por_bloques_ara;
			m_por_bloques_ara = false;
			m_por_bloques = false;
			/*ConstruirSolucion(lista, true);*/
			bool m_old_eliminar = m_eliminar_espacios;
			m_eliminar_espacios = false;
			int mvolcs = m_total_volumen_cs_ocupado;
			std::list<SPACE>::iterator itS = m_Spaces.begin(), itSfin = m_Spaces.end();
			for (; itS != itSfin; itS++)
				(*itS).Set_Flag(false);
			ConstructivoCS(false);
			m_eliminar_espacios = m_old_eliminar;
			m_por_bloques = mblo;
			m_por_bloques_ara = mbloara;

			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pieces[j].Get_Num() != m_Pieces[j].Get_q())
				{
					m_Pedidos_ordenados[m_candidato].Set_flag(true);
					m_Pieces = piezas2;
					m_Configuracaos = lista2;
					m_Spaces = spaces;
					/*
					m_Configuracaos = configuracaos;*/
					m_total_volumen_cs_ocupado = mvolcs;
					break;
				}
			}
			if (m_Pedidos_ordenados[m_candidato].Get_flag() == false)
			{
				m_Pedidos_ordenados[m_candidato].Set_complete(true);
				for (int j = 0; j < m_Q; j++)
					m_Pieces[j].Add_asign(m_Pedidos_ordenados[m_candidato].Get_num_pieces_tipo()[j]);
				m_completos++;
				m_total_volumen_cs_ocupado += m_Pedidos_ordenados[m_candidato].Get_Volumen();
				pt = (double)m_total_volumen_cs_ocupado / ((double)m_X * m_Y * m_Z) * 100;
				/*printf("%f\n", pt);*/
			}
			/*else
				printf("%f\n", pt);*/
		}
		pt = (double)m_total_volumen_cs_ocupado / ((double)m_X * m_Y * m_Z) * 100;
		/*printf("%d\t%f\n", m_total_volumen_cs_ocupado, pt);*/
		if (m_total_volumen_cs_ocupado > volmejor)
			volmejor = m_total_volumen_cs_ocupado;
		m_fintime = clock();
		m_tiempo = ((double)((double)m_fintime - m_inicio)) / CLOCKS_PER_SEC;
	}while (m_tiempo < m_tiempo_final_total);
	double pt2 = (double)volmejor / ((double)m_X * m_Y * m_Z)*100;
	FILE* fichero;
	fichero = fopen(m_file_to_write, "a+");
	fprintf(fichero, "%s\t%d\t%f\t%d\t%f\n", m_Nombre, volmejor, pt2, m_completos, m_tiempo);
	fclose(fichero);
}
void CONTAINER::AnalisisInstancias()
{
	FILE* fichero;
	fichero = fopen("Analisis_instancias_pedidos_cajas.txt", "a+");
	fprintf(fichero, "%s\t", m_Nombre);
	for (int i = 0; i < m_num_pedidos; i++)
	{
		/*int cajas = 0;
		for (int j = 0; j < m_Q; j++)
		{
			cajas += m_Pedidos[i].Get_num_pieces_tipo()[j];
		}
		if (cajas != m_Pedidos[i].Get_num_cajas())
			fprintf(fichero, "error");
		else*/
		if (i==m_num_pedidos-1)
			fprintf(fichero, "%d", m_Pedidos[i].Get_num_cajas());
		else
			fprintf(fichero, "%d\t", m_Pedidos[i].Get_num_cajas());
	}
	fprintf(fichero, "\n");
	fclose(fichero);

	FILE* fichero1;
	fichero1 = fopen("Analisis_instancias_pedidos_volumen.txt", "a+");
	fprintf(fichero1, "%s\t", m_Nombre);
	for (int i = 0; i < m_num_pedidos; i++)
	{
		/*int cajas = 0;
		for (int j = 0; j < m_Q; j++)
		{
			cajas += m_Pedidos[i].Get_num_pieces_tipo()[j];
		}
		if (cajas != m_Pedidos[i].Get_num_cajas())
			fprintf(fichero1, "error");
		else*/
		if (i == m_num_pedidos - 1)
			fprintf(fichero1, "%d", m_Pedidos[i].Get_Volumen());
		else
			fprintf(fichero1, "%d\t", m_Pedidos[i].Get_Volumen());
	}
	fprintf(fichero1, "\n");
	fclose(fichero1);
}

void CONTAINER::CrearBats()
{
	FILE* bat;
	bat = fopen("Todas_pedidos.bat", "a+");
	for (int k = 10; k < 30; k += 5)
	{
		for (int i = 1; i <= 15; i++)
		{
			for (int j = 1; j <= 100; j++)
				fprintf(bat, "x64\\Release\\LogisticVNS  -I Container\\Individualizadas\\BR_%d_%d_%d.txt	-TL 150 -FS 0 -BA 0 -P 1 -VCS 2 -CS 4 -FO CompleteShipment.txt\n", i, j, k);
		}
	}
	fclose(bat);
	//	
	//fclose(bat);
	//FILE* bat2;
	//bat2 = fopen("10Primeras_pedidos_15.bat", "a+");
	//for (int i = 1; i <= 15; i++)
	//{
	//	for (int j = 1; j <= 10; j++)
	//	{
	//		/*for (int k = 10; k < 30; )
	//		{*/
	//		int k = 15;
	//		if (i < 8)
	//			fprintf(bat2, "x64\\Release\\LogisticVNS  -I Container\\Individualizadas\\BR_%d_%d_%d.txt	-TL 150 -FS 0 -BA 1 -P 1 -VCS 2 -CS 1 -FO CompleteShipment15.txt\n", i, j, k);
	//		else
	//			fprintf(bat2, "x64\\Release\\LogisticVNS  -I Container\\Individualizadas\\BR_%d_%d_%d.txt	-TL 150 -FS 0 -BA 1 -P 0.98 -VCS 2 -CS 1 -FO CompleteShipment15.txt\n", i, j, k);
	//		/*k += 5;*/
	//	/*}*/
	//	}
	//}
	//fclose(bat2);
	//FILE* bat3;
	//bat3 = fopen("10Primeras_pedidos_20.bat", "a+");
	//for (int i = 1; i <= 15; i++)
	//{
	//	for (int j = 1; j <= 10; j++)
	//	{
	//		/*for (int k = 10; k < 30; )
	//		{*/
	//		int k = 20;
	//		if (i < 8)
	//			fprintf(bat3, "x64\\Release\\LogisticVNS  -I Container\\Individualizadas\\BR_%d_%d_%d.txt	-TL 150 -FS 0 -BA 1 -P 1 -VCS 2 -CS 1 -FO CompleteShipment20.txt\n", i, j, k);
	//		else
	//			fprintf(bat3, "x64\\Release\\LogisticVNS  -I Container\\Individualizadas\\BR_%d_%d_%d.txt	-TL 150 -FS 0 -BA 1 -P 0.98 -VCS 2 -CS 1 -FO CompleteShipment20.txt\n", i, j, k);
	//		/*k += 5;*/
	//	/*}*/
	//	}
	//}
	//fclose(bat3);
	//FILE* bat4;
	//bat4 = fopen("10Primeras_pedidos_25.bat", "a+");
	//for (int i = 1; i <= 15; i++)
	//{
	//	for (int j = 1; j <= 10; j++)
	//	{
	//		/*for (int k = 10; k < 30; )
	//		{*/
	//		int k = 25;
	//		if (i < 8)
	//			fprintf(bat4, "x64\\Release\\LogisticVNS  -I Container\\Individualizadas\\BR_%d_%d_%d.txt	-TL 150 -FS 0 -BA 1 -P 1 -VCS 2 -CS 1 -FO CompleteShipment25.txt\n", i, j, k);
	//		else
	//			fprintf(bat4, "x64\\Release\\LogisticVNS  -I Container\\Individualizadas\\BR_%d_%d_%d.txt	-TL 150 -FS 0 -BA 1 -P 0.98 -VCS 2 -CS 1 -FO CompleteShipment25.txt\n", i, j, k);
	//		/*k += 5;*/
	//	/*}*/
	//	}
	//}
	//fclose(bat4);
	return;
}