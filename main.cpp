#pragma warning (disable: 4786)



#include "Container.h"
#include "LPCPLEX2.h"
#include <time.h>
#include <string>
#include <stdlib.h>
int main(int argc,char **argv)
{
	bool imprimir = false;
	char* file_to_read, * file_to_write;
	int TimeLimit = 2, seed = 1;
	file_to_read = "BR_1_1.txt";
	file_to_write = "Results.txt";
	int fullsupport = 0;
	int completeshipment = 0;
	float perdida = 1.0;
	int   bloaraya = 0;
	int vcs = 0;
	int porcentaje = 100; //Inicializamos como 100% para evitar fallos
	if ((argc > 2) && (argc % 2 == 1))
	{ //Se comprueba que haya pares de argumentos (y al menos un par)

		while (argc > 1)
		{
			if (strcmp(argv[1], "-TL") == 0)
			{
				//Tiempo
				sscanf(argv[2], "%d", &TimeLimit);
			}
			else if (strcmp(argv[1], "-I") == 0)
			{
				//File to read
				file_to_read = argv[2];

			}
			else if (strcmp(argv[1], "-FO") == 0)
			{
				file_to_write = argv[2];
			}
			else if (strcmp(argv[1], "-s") == 0)
			{
				sscanf(argv[2], "%d", &seed);
			}
			else if (strcmp(argv[1], "-imprimir") == 0)
			{
				//imprimir resultados en pantalla
				imprimir = true;

			}
			else if (strcmp(argv[1], "-FS") == 0)
			{
				//full support
				sscanf(argv[2], "%d", &fullsupport);
			}
			else if (strcmp(argv[1], "-BA") == 0)
			{
				//bloques araya
				sscanf(argv[2], "%d", &bloaraya);
			}
			else if (strcmp(argv[1], "-P") == 0)
			{
				//perdida de los bloques araya
				sscanf(argv[2], "%f", &perdida);
			}
			else if (strcmp(argv[1], "-VCS") == 0)
			{
				//función objetivo VCS
				sscanf(argv[2], "%d", &vcs);
			}
			else if (strcmp(argv[1], "-CS") == 0)
			{
				//complete shipment
				sscanf(argv[2], "%d", &completeshipment);
			}
			else if (strcmp(argv[1], "-PT") == 0)
			{
				//complete shipment
				sscanf(argv[2], "%d", &porcentaje);
			}
			argc -= 2;
			argv += 2;

		}
	}

	//Variables de tiempo
	//true si es el multicontainer
	//false el container
	//TimeLimit: tiempo máximo de ejecución del algoritmo (si el criterio de parada es por tiempo y no solamente por iteraciones)
	//File to read: base de datos con las instancias
	//File to write: documento donde se escriben los resultados
	//Seed: semilla
	//Imprimir: si se quiere o no obtener resultados por pantalla
	//fullsupport: 1 full support, 0 sin
	//complete shipment: 0 sin complete shipment, N>0 complete shipment	con implementación N
	//												1 
	//bloaraya: 0 sin bloques, 1 con bloques de araya, 2 mixto (bloques araya+capas), 3 mixto + vol o fit
	//Procedimiento mixto: el constructivo original se construye solamente con capas. Después de cada movimiento, cada espacio maximal se rellena con
	//					   capas o con bloques de araya, aleatoriamente. De estos últimos consideramos únicamente los formados por cajas distinas o
	//					   iguales pero con distinta orientación dentro del mismo bloque. En el 3, además, se cambia aleatoriamente la función objetivo
	//					   entre volumen y fit.
	//Perdida: % de perdida de los bloques de araya
	//VCS: 0 nada, 1 función objetivo VCS, 2 función objetivo VCS con parámetros aleatorios en cada iteración
	
	bool crear_bloques_araya = true;
	if (bloaraya == 0)
		crear_bloques_araya = false;
	
	CONTAINER Container(file_to_read, fullsupport, completeshipment, crear_bloques_araya, perdida, vcs);
	
	//Container.AnalisisInstancias(); //Función para analizar las instancias
	//return 0;
	//Container.CrearInstanciasPedidosFix(); //Función para crear las nuevas instancias BR con pedidos
	//return 0;
	/*Container.CrearBats();*/ //Para crear archivos ejecutables
	if (bloaraya == 2)
		Container.SetBloquesAll(true);
	if (bloaraya == 3)
	{
		Container.SetBloquesAll(true);
		Container.SetObjetivoMixto(true);
	}
	Container.Set_Random(false);
	Container.SetLimite(porcentaje);
	Container.Set_geometrica(10);
	Container.SetFichero(file_to_write);
	Container.SetTiempoGrasp(TimeLimit);
	Container.SetImprimir(true);
	
	
	//parametro para que haga sies igual a 
	// 0 Mejora con orig
	// 1 Mejora con vol
	// 2 Mejora con orig+vol
	//3 es por columnas
	// 9 es ninguna
//	int para=0;
	std::srand(seed);
	
	int para=1;
//	para=12;
//	para=10;
//	srand(atoi(argv[3]));
//	printf("Para %d",para);
//	int	para=10;
//	Container.SetValorQuita(para);
	
	//o es the new
	//1 es eculidena
	Container.SetEliminar(true);
//	Container.Set_Eleccion_Space(0);
//	Container.SetTipoMejora(0);
	//EL parametro me dice si es por capas T o por columnas F
	//para el mixto es un parametro del Grasp
//	Container.SetObjetivoCapas(true);
	//EL parametro me dice si es aleatorizado T o no F
//	Container.Constructivo(false);

	//Grasp
	//Para que haga aleatoriamente columnas y filas
	para=11;
	Container.SetTipoMejora(para);
//	Container.SetTipoMixto(false);
//	Container.Set_Nesquinas(para);
	Container.SetObjetivoCapas(true);
//	Container.Set_objetivo_vol(false);
	Container.SetMejoraLocal(false);
	Container.Set_Tipo_origen(0);
	Container.SetEliminar(false);
//	if (para==1)
//	Container.SetDescendent(false);
//	else
	Container.Set_MaximosMovimientos(100);
	Container.SetDescendent(false);
	//Container.Generar_Bloques
	/*Container.knapsack_bouknap();
	return 0;*/
	if (completeshipment == 0)
		Container.VNS(true);
	else
	{
		switch (completeshipment)
		{
		case 1:
			Container.PrimeraImplementacion();
			break;
		case 2:
			Container.VNSCS();
			break;
		case 3:
			Container.Constructivo_random_cs();
			break;
		case 4:
			Container.ConstruccionPorPedidos();
			break;
		}
	}
	/*Container.VNSCS();*/
	/*Container.VNS(true);*/
	/*Container.Constructivo_random();*/
	//Container.ConstruccionPorPedidos();
	/*Container.Constructivo_random();*/
//	Container.ILS_MC();
//	Container.SetDescendent(false);
	//pongo esto el 11/03/08
//	Container.PintarPieces();
//	Container.ConstructivoMC(false);
	//si es false es bin a bin de la otra forma
	//es todos juntos
	//quito esto el 11/03/08
//	Container.ConstructivoMC(false);

//	Container.SetJuntos(false);
//	Container.GraspMC_Global();


//	Container.ILS_MC();
//	Container.GraspMC_PorBin();
//	if (para==1)
//	{
//	Container.SetDescendent(true);
//		Container.VND(false);
//	}
//	if (para==2)
//		Container.VND(true);
//	Container.DibujarOpenGL(Container.Get_ListaBestConfiguracaos());

/*if (para==2)
else
	Container.VNS();*/
//	Container.CompactarConfiguracaos(Container.Get_ListaBestConfiguracaos());
//	Container.DibujarOpenGL(Container.Get_ListaBestConfiguracaos());

/*
if  (para==1)
	Container.VNS();
else
	Container.ILS();*/


//	Container.Set_MaximosMovimientos(1000);	

/*
	Container.Constructivo(false);
//	MejoraLocalVaciado(false);
	Container.Set_objetivo_vol(true);
	Container.Set_ImprimirMejoras(true);
	if (para==0)
	{
		Container.SetEliminar(true);

		Container.Set_MaximosMovimientos(100);

		Container.MejoraLocalVaciado(false);
	}
	if (para==1)
		Container.MejoraLocalCapa(false);
	if (para==2)
		Container.MejoraLocalPieza(false);
	if (para==3)
		Container.MejoraLocalQuitarBloque(false);
	if (para==4)
	{
		Container.Set_MaximosMovimientos(100);
		Container.Set_objetivo_vol(false);
		Container.MejoraLocalVaciado(false);
	}
	if (para==5)
	{
		Container.SetEliminar(true);

		Container.Set_objetivo_vol(false);
		Container.MejoraLocalReducirBloque(false);
	}

//	if (para==6)
//	{
//		Container.Set_objetivo_vol(false);
//		Container.MejoraLocalReducirBloque(false);
//	}
  //	Container.MejoraLocalCapa();
	//Variable para el VNS descendent
*/

//	Container.MejoraLocalVaciado(false);
	return 0;
}
