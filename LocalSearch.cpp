#pragma warning (disable: 4786)

//Para incluir el contenedor que tengo
#include "Container.h"
#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#endif
int kkkk=0;

CONTAINER* MOVIMIENTOMC::m_Container=NULL;

CONTAINER* MOVIMIENTO::m_Container=NULL;
//Tenemos que aumentar o inserta los bloques en la solucion
void CONTAINER::MejoraLocalTipo(int tipo)
{
	m_eliminar_espacios=false;
	m_mejora_local=false;
	m_objetivo_capas=true;
	m_Aleatorizado=false;
	Constructivo(false);
	m_imprimir_mejoras=true;
	if (tipo==1)
	{
		MejoraLocalVaciado(false);
		VerificarSolucion(m_Configuracaos);
	}
	if (tipo==2)
	{
		MejoraLocalQuitarBloque(false);
		VerificarSolucion(m_Configuracaos);

	}
	if (tipo==3)
	{
		MejoraLocalCapa(false);
		VerificarSolucion(m_Configuracaos);
	}
	if (tipo==4)
	{
		MejoraLocalPieza(false);
		VerificarSolucion(m_Configuracaos);
	}

}
void CONTAINER::Constructivokk()
{
	m_eliminar_espacios=false;
	m_mejora_local=false;
	m_objetivo_capas=true;
	Constructivo(false);

}
void CONTAINER::MejoraLocalPieza(bool perturbar)
{
	/*FILE* fincs;
	fincs = fopen(m_file_to_write, "a+");
	fprintf(fincs, "p42\n");
	fclose(fincs);*/
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;
	int kki;
	int kkkk = 0;
	m_eliminar_espacios=true;
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	do
	{
		kki=0;
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p43\n");
		fclose(fincs);*/
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado;
//		int perdida_media=perdida/m_Spaces.size();

		MOVIMIENTO Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		std::list<SPACE> ::reverse_iterator it;
		bool parar=false;
		int piezas_fuera=0;
		int kkcant=0;
		//Aqui cuento cuantas piezas hay fuera
		for(int register i=0;i<m_Q ;i++)
		{
			if (m_Pieces[i].Get_q()-m_Pieces[i].Get_Num()>0)
			{
				piezas_fuera++;
				kkcant+=(m_Pieces[i].Get_q()-m_Pieces[i].Get_Num())*m_Pieces[i].Get_Volumen();
			}
			
		}
		
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p44\n");
		fclose(fincs);*/
		if (piezas_fuera == 0 && perturbar == true)
		{
		//	fincs = fopen(m_file_to_write, "a+");
			//fprintf(fincs, "piezasfuera: %d\n", piezas_fuera);
			//fclose(fincs);
		}
		int cont=0,alea=0;
		if (perturbar==true)
			alea=get_random(0,piezas_fuera-1);
		//fincs = fopen(m_file_to_write, "a+");
		//fprintf(fincs, "p44\n");
		//fclose(fincs);
		for(int i=0;i<m_Q && kki<(m_max_movimientos/8) && parar!=true && !(perturbar==true && kki>0);i++)
		{
			int numposibles=m_Pieces[i].Get_q()-m_Pieces[i].Get_Num();
			//numposibles es el n que puedo meter 
			if (numposibles >0)
			{
				if (perturbar==true && cont>=alea)
					continue;
				int mov_aqui=0;
			/*	fincs = fopen(m_file_to_write, "a+");
				fprintf(fincs, "p44a\n");
				fclose(fincs);*/
				for (it=m_Spaces.rbegin();it!=m_Spaces.rend() && mov_aqui*piezas_fuera<=m_max_movimientos && kki<m_max_movimientos  && parar!=true && !(perturbar==true && (kki>0));it++)
				{
		
					mov_aqui++;
					kki++;
					short int dir=(*it).Get_origen_distancia();
					for (short int dir_impongo=1;dir_impongo<8;dir_impongo++)
					{
						if (m_full_supported == true && (dir_impongo == 3 || dir_impongo == 4 || dir_impongo == 7 || dir_impongo == 8))
							continue;
						(*it).Set_origen_distancia(dir_impongo);
						SetDibujar(true);
						/*FILE* fincs;
						fincs = fopen(m_file_to_write, "a+");
						fprintf(fincs, "pmov1\n");
						fclose(fincs);*/
						Move.MejorUnaPiezaEspacio((*it),m_Pieces[i]);
						/*FILE* fincs;*/
						/*fincs = fopen(m_file_to_write, "a+");
						fprintf(fincs, "pmov2\n");
						fclose(fincs);*/
						SetDibujar(false);


						//esta funcion me compara los movimientos
						//si es mejor cambio el que tengo
					}
					//vuelvo a colocar en la direccion que tenia
					(*it).Set_origen_distancia(dir);
				}
				/*fincs = fopen(m_file_to_write, "a+");
				fprintf(fincs, "p44b\n");
				fclose(fincs);*/
				if (m_descendent==true && Move.Get_Val()>0)
					parar=true;
				cont++;


			}
		}
//		PintarSolucion(Mejor.Get_Configuracaos());
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p45\n");
		fclose(fincs);*/
		m_eliminar_espacios=false;
		ConstruirSolucion(Move.Get_Configuracaos(),true);
		/*fincs = fopen(m_file_to_write, "a+");
		fprintf(fincs, "p46\n");
		fclose(fincs);*/
		kkkk++;
		//if (ComprobarFullSupport(m_Configuracaos) == false)
		//	printf("%d\n", kkkk);
		DibujarSolucion(m_Spaces,m_Configuracaos);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora || perturbar==true)
		{
			lista_configuracaos=m_Configuracaos;
//			printf("uma Pieza %d %d\n",m_total_volumen_ocupado,kkkk);
		}

//		m_eliminar_espacios=false;
	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_un_movimiento!=true && perturbar!=true && m_total_volumen_ocupado!=m_total_volumen);
	//fincs = fopen(m_file_to_write, "a+");
	//fprintf(fincs, "p47\n");
	//fclose(fincs);
	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

	if (m_max_total_volumen_ocupado_mejora>m_max_total_volumen_ocupado)
		m_max_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	//fincs = fopen(m_file_to_write, "a+");
	//fprintf(fincs, "p48\n");
	//fclose(fincs);
	//vuelvo a ponerla 
//	m_Configuracaos=lista_configuracaos;
	ConstruirSolucion(lista_configuracaos,true);
	/*fincs = fopen(m_file_to_write, "a+");
	fprintf(fincs, "p49\n");
	fclose(fincs);*/
	DibujarSolucion(m_Spaces,m_Configuracaos);
//	DibujarOpenGL(m_Configuracaos);
	if (perturbar!=true)
	m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	VerificarSolucion(m_Configuracaos);
	/*fincs = fopen(m_file_to_write, "a+");
	fprintf(fincs, "p50\n");
	fclose(fincs);*/
	if (m_imprimir_mejoras==true)
	{
		printf("umafuera %d Fuer %d\n",kkkk,kki);
		m_fintime=clock();
		m_tiempo=((double)((double)m_fintime-m_inicio))/CLOCKS_PER_SEC;

		FILE *fin3;
		fin3=fopen(m_file_to_write,"a+");
		double pt=((double)m_max_total_volumen_ocupado/(double)((double)m_X*m_Y*m_Z))*100;
		fprintf(fin3,"%s\tPieza\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,(m_X*m_Y*m_Z),m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
		fclose(fin3);
	}
}
//Esta funcion intenta colocar la pieza en el espacio mas grande de cada bin 
void CONTAINER::MejoraLocalMCPieza(bool perturbar)
{
	int valtemp=m_total_volumen_ocupado;
	bool mejora=false;
	//Guardo en las tabu las originales para reemplazarlas
	//si es el 
	for (register int k=0;k<m_Q;k++)
		m_Pieces_Tabu[k]=m_Pieces[k].Get_Num();
	std::list< CONFIGURACAO > lista_configuracaos=m_ConfiguracaosMC.back().second;
	std::list< CONFIGURACAO > ::iterator itC;
	m_max_total_volumen_ocupado_mejora=0;
	int kki;
	m_eliminar_espacios=false;
	//Construyo la solucion del ultimo bin que es el más vacio
	//
//	int valthisbin=m_ConfiguracaosMC.back().first;
	m_Spaces.clear();
	//Quito las piezas de este bin
	for (itC=lista_configuracaos.begin();itC!=lista_configuracaos.end();itC++)
	{
		m_Pieces[(*itC).Get_Id()].Set_Num(0);
	}
	//Podria mejorar la funcion objetivo si coloca algo, pero es imposible
	//que coloque algo por tanto en cuanto vacia la lista se va
	ConstruirSolucionBinC(lista_configuracaos,true);
	lista_configuracaos=m_ConfiguracaosMC.back().second;
	m_eliminar_espacios=true;
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	do
	{
		kki=0;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado;
//		int perdida_media=perdida/m_Spaces.size();

		MOVIMIENTO Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		std::list<SPACE> ::reverse_iterator it;
		bool parar=false;
		int piezas_fuera=0;
		int kkcant=0;
		//Aqui cuento cuantas piezas hay fuera
		for(int register i=0;i<m_Q ;i++)
		{
			if (m_Pieces[i].Get_q()-m_Pieces[i].Get_Num()>0)
			{
				piezas_fuera++;
				kkcant+=(m_Pieces[i].Get_q()-m_Pieces[i].Get_Num())*m_Pieces[i].Get_Volumen();
			}
			
		}
		int cont=0,alea=0;
		if (perturbar==true)
			alea=get_random(0,piezas_fuera-1);
		m_max_movimientos=5000;
		for(int i=0;i<m_Q && kki<(m_max_movimientos/8) && parar!=true && !(perturbar==true && kki>0);i++)
		{
			int numposibles=m_Pieces[i].Get_q()-m_Pieces[i].Get_Num();
			//numposibles es el n que puedo meter 
			if (numposibles >0)
			{
				int mov_aqui=0;
				for (it=m_Spaces.rbegin();it!=m_Spaces.rend() && mov_aqui*piezas_fuera<=m_max_movimientos && kki<m_max_movimientos  && parar!=true && !(perturbar==true && (kki>0));it++)
				{
					//Lo ponemos en todas las esquinas 
					//ya que es mas facil para que entre alguna
					//si no en la mayoria de los casos se saldra
					short int dir=(*it).Get_origen_distancia();
					for (short int dir_impongo=1;dir_impongo<8;dir_impongo++)
					{
						(*it).Set_origen_distancia(dir_impongo);
						Move.MejorUnaPiezaEspacioMC((*it),m_Pieces[i]);
/*						ConstruirSolucionBinC(Move.Get_Configuracaos(),false);
						for (itC=m_Configuracaos().begin();itC!=m_Configuracaos.end();itC++)
						{
							m_Pieces[(*itC).Get_Id()].Set_Num(0);
						}
						Move.Set_Valor(m_total_volumen_ocupado-m_max_total_volumen_ocupado_mejora);
*/


						//esta funcion me compara los movimientos
						//si es mejor cambio el que tengo
					}
					//vuelvo a colocar en la direccion que tenia
					(*it).Set_origen_distancia(dir);
				}
				cont++;
			}
		}
//		PintarSolucion(Mejor.Get_Configuracaos());
		
		m_eliminar_espacios=false;

		//Dejo bin los items de los bin que he quitado
		for (itC=lista_configuracaos.begin();itC!=lista_configuracaos.end();itC++)
		{
			m_Pieces[(*itC).Get_Id()].Set_Num(0);
		}

		ConstruirSolucionBinC(Move.Get_Configuracaos(),false);
//		DibujarSolucion(m_Spaces,m_Configuracaos);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora )
		{
			valtemp+=(m_total_volumen_ocupado-m_max_total_volumen_ocupado_mejora);
			mejora=true;
			lista_configuracaos=m_Configuracaos;
//			printf("uma Pieza %d %d\n",m_total_volumen_ocupado,kkkk);
		}
		else
		{
			for (itC=m_Configuracaos.begin();itC!=m_Configuracaos.end();itC++)
			{
				m_Pieces[(*itC).Get_Id()].Set_Num(0);
			}

		}

//		m_eliminar_espacios=false;
	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_un_movimiento!=true && perturbar!=true && m_total_volumen_ocupado!=m_total_volumen);
	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

	//vuelvo a ponerla 
//	m_Configuracaos=lista_configuracaos;
	//La McConfiguracao no ha cambiado  por tanto
	//si he mejorado tengo que cambiar la ultima por esta
	if (mejora==true)
	{
		//Puede que haya cambiado en medio los valores por tanto tengo que 
		//ponerlos
		for (itC=lista_configuracaos.begin();itC!=lista_configuracaos.end();itC++)
		{
			m_Pieces[(*itC).Get_Id()].Set_Num(1);
		}

		m_ConfiguracaosMC.back().second=lista_configuracaos;
		m_ConfiguracaosMC.back().first=m_max_total_volumen_ocupado_mejora;
	}
	else
	{
		for (register int k=0;k<m_Q;k++)
			m_Pieces[k].Set_Num(m_Pieces_Tabu[k]);
	}
	m_total_volumen_ocupado=valtemp;
	VerificarSolucionMC(m_ConfiguracaosMC);

}
//^*******************Mejora Local multi container
// aqui lo que hacemos es vaciar un bin

void CONTAINER::MejoraLocalMCQuitarUnBinVieja(bool perturbar)
{
	//Tengo la lista de bins
	m_Aleatorizado=false;

	int kki=0;
	m_eliminar_espacios=true;
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;
	int volumen_anterior;
//	printf("**************************MEJORA**************************\n");
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	std::list< std::pair<int, std::list< CONFIGURACAO> > > ::iterator it;
	std::list< CONFIGURACAO> ::iterator itC;
	do
	{
//		FILE *fin3;
//		fopen_s(&fin3,"kk.txt","a+");
//		fprintf(fin3,"\n");
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
//		fclose(fin3);

		//Tenemos un set de enteros para evitar movimientos que constituyan 
		//volver a eliminar la misma region del espacio
		kki=0;
		m_eliminar_espacios=true;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado_mejora;
//		int perdida_media=perdida/m_Spaces.size();
		MOVIMIENTO Mejor(this);
		//Solamente queremos movernos para mejorar el que tenemos
		Mejor.Set_Vol(0);
		//Deberia hacerlo aletoriamente
//		bool parar=false;
		int lugar=0;
		for (it=m_ConfiguracaosMC.begin();it!=m_ConfiguracaosMC.end() ;it++)
		{	
			volumen_anterior=m_max_total_volumen_ocupado_mejora;
//			m_Pieces_Tabu.clear();
			for (int j=0;j<m_Q;j++)
				m_Pieces_Tabu[j]=m_Pieces[j].Get_Num();
			//Ya esta puesto la nueva 
			//Este es el bin que voy a vaciar 
			for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
			{
				m_Pieces_Tabu[(*itC).Get_Id()]=(m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num());
				volumen_anterior-=(*itC).Get_Volumen();

			}
			std::list<CONFIGURACAO> lista=(*it).second;
			lista.clear();
			ConstruirSolucionBin(lista,false);
			if ((m_total_volumen_ocupado+volumen_anterior)>Mejor.Get_Volumen())
			{
					
				Mejor.CambiarMejor(lista,(m_total_volumen_ocupado+volumen_anterior),lugar);
			}
			lugar++;
		}

//		PintarSolucion(Mejor.Get_Configuracaos());
//		m_eliminar_espacios=true;
		//esta variable es para que lo deje todo bien
//		ConstruirSolucion(Mejor.Get_Configuracaos(),true);
		
//		DibujarSolucion(m_Spaces,m_Configuracaos);
	
		if (Mejor.Get_Volumen()>m_max_total_volumen_ocupado_mejora )
		{
			//Tengo que arreglar la lista que tenia de espacios
			int cont=0;
			for (it=m_ConfiguracaosMC.begin(),cont=0;it!=m_ConfiguracaosMC.end() ;cont++)
			{
				if (cont==Mejor.Get_Val())
				{
					for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
					{
//						int kk=(*itC).Get_Id();
//						m_Pieces[(*itC).Get_Id()].Set_Num((m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num()));
						m_Pieces[(*itC).Get_Id()].Set_Num(0);

					}
					m_ConfiguracaosMC.erase(it);
					break;
				}
				++it;
			}
			//Aqui pongo los valores de las nuevas
			std::pair<int, std::list<CONFIGURACAO> >  p(m_max_total_volumen_ocupado_mejora-m_total_volumen_ocupado,Mejor.Get_Configuracaos());
			m_ConfiguracaosMC.push_back(p);
			m_total_volumen_ocupado=Mejor.Get_Volumen();
			//Actualizar cantidades de piezas
			for (itC=Mejor.Get_Configuracaos().begin();itC!=Mejor.Get_Configuracaos().end();itC++)
			{
//						int kk=(*itC).Get_Id();
				m_Pieces[(*itC).Get_Id()].Add_Num((*itC).Get_Num());

			}
//			printf("Vaciado %d %d\n",m_total_volumen_ocupado,m_total_volumen);
			VerificarSolucionMC(m_ConfiguracaosMC);
		}

//		m_eliminar_espacios=false;
	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_total_volumen_ocupado!=m_total_volumen);
	if (m_total_volumen_ocupado<m_max_total_volumen_ocupado_mejora)
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;


	m_Aleatorizado=true;

}
//Aqui elijo dos bin y los mezclo ??
//^*******************Mejora Local multi container
// aqui lo que hacemos es vaciar un bin

void CONTAINER::MejoraLocalMCQuitarDosBin(bool perturbar)
{
//	return;
	if (m_ConfiguracaosMC.size()<=2)
		return;
	//Tengo la lista de bins
	m_Aleatorizado=false;

//	int kki=0;
	m_eliminar_espacios=true;
	std::list< std::pair< int ,std::list<CONFIGURACAO> > > lista;
	m_max_total_volumen_ocupado_mejora=0;
//	int volumen_anterior;
//	printf("**************************MEJORA**************************\n");
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	std::list< std::pair<int, std::list< CONFIGURACAO> > > ::reverse_iterator itr,itr2;
	std::list< std::pair<int, std::list< CONFIGURACAO> > > ::iterator it,it2,itfin;
	std::list< CONFIGURACAO> ::iterator itC;
	//Construyo la lista tabu 
//	m_Pieces_Tabu.clear();
	for (int j=0;j<m_Q;j++)
		m_Pieces_Tabu[j]=0;
	std::vector< int > lista_quito;
	lista_quito.push_back(0);
	lista_quito.push_back(0);
	
	MOVIMIENTOMC Mejor(this);
	do
	{
//		FILE *fin3;
//		fopen_s(&fin3,"kk.txt","a+");
//		fprintf(fin3,"\n");
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
//		fclose(fin3);

		//Tenemos un set de enteros para evitar movimientos que constituyan 
		//volver a eliminar la misma region del espacio
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado_mejora;
//		int perdida_media=perdida/m_Spaces.size();
		Mejor.Set_Vol(0);
		//Solamente queremos movernos para mejorar el que tenemos


		//Deberia hacerlo aletoriamente

		int lugar=0;
		int lugar2=0;
		ORIG setmin(0,0,0);
		CONFIGURACAO C(this,setmin,999999);

		//		
/*		for (j=(m_Q-1);j>=0;j--)
		{
			if (m_Pieces[j].Get_Num()==0)
			{
		//Creo ya inicialmente la configuracao 
//				CONFIGURACAO Configuracao(this,setmin,999999);
				C.CambiarConfiguracao(1,1,1,1,m_Pieces[j].Get_x(),m_Pieces[j].Get_y(),m_Pieces[j].Get_z(), m_Pieces[j].Get_Id(),0);

			}
		}*/

		//Solamente ponemos una pieza de las que hay fuera
		//aunque exista la posibilidad de poner más de una
		if (m_tipo_orden_pieces!=50)
		{
		for (int j=0;j<m_Q;j++)
		{
			if (m_Pieces[j].Get_Num()==0 )
			{
		//Creo ya inicialmente la configuracao 
//				CONFIGURACAO Configuracao(this,setmin,999999);
				C.CambiarConfiguracao(1,1,1,1,m_Pieces[j].Get_x(),m_Pieces[j].Get_y(),m_Pieces[j].Get_z(), m_Pieces[j].Get_Id(),0);
				break;

			}
		}
		if (C.Get_Id()==99999)
		{
			for (int j=0;j<m_Q;j++)
			{
				if (m_Pieces[j].Get_Num()!=m_Pieces[j].Get_q() )
				{
			//Creo ya inicialmente la configuracao 
	//				CONFIGURACAO Configuracao(this,setmin,999999);
					C.CambiarConfiguracao(1,1,1,1,m_Pieces[j].Get_x(),m_Pieces[j].Get_y(),m_Pieces[j].Get_z(), m_Pieces[j].Get_Id(),0);
					break;

				}
			}

		}

		}
		else
		{
			int max=0;
			int elegido=0;
			for (int j=0;j<m_Q;j++)
			{
				if (m_Pieces[j].Get_Num()==0)
				{
					if (m_frecuencias[j]>=max)
					{
						elegido=j;
						max=m_frecuencias[j];
					}
		//Creo ya inicialmente la configuracao 
//				CONFIGURACAO Configuracao(this,setmin,999999);
				}
			}
//			printf("%d\t",elegido);
			C.CambiarConfiguracao(1,1,1,1,m_Pieces[elegido].Get_x(),m_Pieces[elegido].Get_y(),m_Pieces[elegido].Get_z(), m_Pieces[elegido].Get_Id(),0);
//			break;

		}
		for (itr=m_ConfiguracaosMC.rbegin();itr!=m_ConfiguracaosMC.rend() && (*itr).first<=(m_total_volumen/(m_Best_nbins-1));itr++,lugar++)
		{	
			m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
//			m_Pieces_Tabu.clear();
			//Ya esta puesto la n
			m_total_volumen_ocupado-=(*itr).first;
			itr2=itr;
			itr2++;
			if (itr2==m_ConfiguracaosMC.rend())
				break;
			lugar2=lugar+1;
			for (;itr2!=m_ConfiguracaosMC.rend()  ;itr2++,lugar2++)
			{
				//Quito el segundo bin
				int temp=m_total_volumen_ocupado;
				m_total_volumen_ocupado-=(*itr2).first;
//				m_Pieces_Tabu.clear();
				for (int j=0;j<m_Q;j++)
					m_Pieces_Tabu[j]=m_Pieces[j].Get_Num();
				//Vacio el primer bin
				for (itC=(*itr).second.begin();itC!=(*itr).second.end();itC++)
				{
					m_Pieces_Tabu[(*itC).Get_Id()]=(m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num());

				}
				//Vacio el segundo bin
				for (itC=(*itr2).second.begin();itC!=(*itr2).second.end();itC++)
				{
					m_Pieces_Tabu[(*itC).Get_Id()]=(m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num());

				}

				lista.clear();
				//Ahora relleno lo que queda, tengo que decirle cuantos quiero rellenar como he q
				//quitado dos pues relleno dos
//				if (m_iter_actual==618)	printf("h3");
				RellenarVariosBin(lista,2,true,C);
//				if (m_iter_actual==618)	printf("h4");
				//Vuelvo a colocar estos que son los que estaban equivocados
				lista_quito[0]=lugar;lista_quito[1]=lugar2;
				//Esta funcion me rellena lo que teniamos

				if ((m_total_volumen_ocupado)>Mejor.Get_Volumen())
				{
						
					Mejor.CambiarMejor(lista,(m_total_volumen_ocupado),lista_quito);

				}
//				if (m_iter_actual==618)	printf("h5");

				m_total_volumen_ocupado=temp;
//				lugar2++;
				if (m_descendent==true && Mejor.Get_Volumen()>m_max_total_volumen_ocupado_mejora) break;
			}
//			lugar++;
			if (m_descendent==true && Mejor.Get_Volumen()>m_max_total_volumen_ocupado_mejora) break;


		}

//		PintarSolucion(Mejor.Get_Configuracaos());
//		m_eliminar_espacios=true;
		//esta variable es para que lo deje todo bien
//		ConstruirSolucion(Mejor.Get_Configuracaos(),true);
	
//		DibujarSolucion(m_Spaces,m_Configuracaos);
//Aqui tengo que volver a colocar todo correctamente	
		if (Mejor.Get_Volumen()>m_max_total_volumen_ocupado_mejora)
		{
//						EscribirSolucionLatex2DMC(m_ConfiguracaosMC);

			//Primer lugar borro los dos bins que he cambiado
//			if (m_iter_actual==618)	printf("here1");
			int cont1=0;
			int vol=0;
			int tot=m_ConfiguracaosMC.size()-1;
//			printf("Mejora %d %d %d Iter %d\n",tot-Mejor.Get_Quitados()[0],tot-Mejor.Get_Quitados()[1],m_ConfiguracaosMC.size(),m_iter_actual);

			itfin=m_ConfiguracaosMC.end();
			for (it=m_ConfiguracaosMC.begin(),cont1=0;it!=itfin ;cont1++)
			{
				if (cont1==(tot-Mejor.Get_Quitados()[0]) || cont1==(tot-Mejor.Get_Quitados()[1]))
				{
					for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
					{

						m_Pieces[(*itC).Get_Id()].Set_Num((m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num()));
//						m_Pieces[(*itC).Get_Id()].Set_Num(0);


					}
					it=m_ConfiguracaosMC.erase(it);
				}
				else
				{
					vol+=(*it).first;	
				}
				++it;
			}
			//Aqui pongo los valores de las nuevas
			for (it=Mejor.Get_Configuracaos().begin();it!=Mejor.Get_Configuracaos().end() ;it++)
			{
				InsertarOrden(m_ConfiguracaosMC,(*it));
//				m_ConfiguracaosMC.insert(m_ConfiguracaosMC.begin(),Mejor.Get_Configuracaos().begin(),Mejor.Get_Configuracaos().end());
			}
			m_total_volumen_ocupado=Mejor.Get_Volumen();
			//Actualizar cantidades de piezas
			for (it=Mejor.Get_Configuracaos().begin();it!=Mejor.Get_Configuracaos().end();it++)
			{
				for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
				{
					m_Pieces[(*itC).Get_Id()].Add_Num((*itC).Get_Num());
				}

			}
//						EscribirSolucionLatex2DMC(m_ConfiguracaosMC);
	
//			for (int j=0;j<m_Q;j++)
//				m_Pieces[j].Set_Num(m_Pieces_Tabu[j]);
			
//			printf("Algo hace %d %d\n",m_total_volumen_ocupado,m_total_volumen);
			VerificarSolucionMC(m_ConfiguracaosMC);
//			if (m_iter_actual==618)	printf("here2");
		}

//		m_eliminar_espacios=false;
	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_total_volumen_ocupado!=m_total_volumen && perturbar==false);
	if (perturbar==false && m_total_volumen_ocupado<m_max_total_volumen_ocupado_mejora)
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;

//	if (m_iter_actual==618)	printf("here");
//	VerificarSolucionVSBP(m_Configuracaos_VSBP);	

}

//Aqui elijo un bin y lo vacio ??
//^*******************Mejora Local multi container
// aqui lo que hacemos es vaciar un bin

void CONTAINER::MejoraLocalMCQuitarUnBin(bool perturbar)
{
//	return;
	//Tengo la lista de bins
	m_Aleatorizado=false;


	m_eliminar_espacios=true;
	std::list< std::pair< int ,std::list<CONFIGURACAO> > > lista;
	m_max_total_volumen_ocupado_mejora=0;
	int volumen_anterior;
//	printf("**************************MEJORA**************************\n");
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	std::list< std::pair<int, std::list< CONFIGURACAO> > > ::reverse_iterator itr,itr2;
	std::list< std::pair<int, std::list< CONFIGURACAO> > > ::iterator it,it2,itfin;
	std::list< CONFIGURACAO> ::iterator itC;
	for (int j=0;j<m_Q;j++)
		m_Pieces_Tabu[j]=0;
	std::vector< int > lista_quito;
	lista_quito.push_back(0);

	MOVIMIENTOMC Mejor(this);
	do
	{
		//Tenemos un set de enteros para evitar movimientos que constituyan 
		//volver a eliminar la misma region del espacio
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
		Mejor.Set_Vol(0);
		int alea1=0;//get_random(0,m_ConfiguracaosMC.size()/3);
		if (perturbar==true)
		{
			alea1=get_random(0,m_ConfiguracaosMC.size()/3);
		}
		//Solamente queremos movernos para mejorar el que tenemos

		int cont=0;
		//Deberia hacerlo aletoriamente
		bool parar=false;
		int lugar=0;
		for (itr=m_ConfiguracaosMC.rbegin();itr!=m_ConfiguracaosMC.rend() && (*itr).first<=(m_total_volumen/(m_Best_nbins-1));itr++,lugar++)
		{	
			int temp=m_total_volumen_ocupado;
			if (perturbar==true && lugar!=alea1) continue;
			m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
//			m_Pieces_Tabu.clear();
			//Ya esta puesto la n
			m_total_volumen_ocupado-=(*itr).first;
			for (int j=0;j<m_Q;j++)
				m_Pieces_Tabu[j]=m_Pieces[j].Get_Num();
			//Vacio el primer bin
			for (itC=(*itr).second.begin();itC!=(*itr).second.end();itC++)
			{
				m_Pieces_Tabu[(*itC).Get_Id()]=(m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num());
			}
			lista.clear();
			//Ahora relleno lo que queda, tengo que decirle cuantos quiero rellenar como he q
			//quitado dos pues relleno dos
			RellenarVariosBin(lista,1);
			//Vuelvo a colocar estos que son los que estaban equivocados
			lista_quito[0]=lugar;
			//Esta funcion me rellena lo que teniamos
			if ((m_total_volumen_ocupado)>Mejor.Get_Volumen())
			{
						
				Mejor.CambiarMejor(lista,(m_total_volumen_ocupado),lista_quito);

			}

			m_total_volumen_ocupado=temp;
			if (m_descendent==true && Mejor.Get_Volumen()>m_max_total_volumen_ocupado_mejora) break;
			if (perturbar==true) break;
		}

		//Aqui tengo que volver a colocar todo correctamente	
		if (Mejor.Get_Volumen()>m_max_total_volumen_ocupado_mejora || perturbar==true )
		{
			//Primer lugar borro los dos bins que he cambiado
//			if (m_iter_actual==618)	printf("here1");
			int cont1=0;
			int vol=0;
			int tot=m_ConfiguracaosMC.size()-1;
			itfin=m_ConfiguracaosMC.end();
			for (it=m_ConfiguracaosMC.begin(),cont1=0;it!=itfin ;cont1++)
			{
				if (cont1==(tot-Mejor.Get_Quitados()[0]) )
				{
					for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
					{

//						m_Pieces[(*itC).Get_Id()].Set_Num((m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num()));
						m_Pieces[(*itC).Get_Id()].Set_Num(0);


					}
					it=m_ConfiguracaosMC.erase(it);
				}
				else
				{
					vol+=(*it).first;	
				}
				++it;
			}
			//Aqui pongo los valores de las nuevas
			for (it=Mejor.Get_Configuracaos().begin();it!=Mejor.Get_Configuracaos().end() ;it++)
			{
				InsertarOrden(m_ConfiguracaosMC,(*it));
//				m_ConfiguracaosMC.insert(m_ConfiguracaosMC.begin(),Mejor.Get_Configuracaos().begin(),Mejor.Get_Configuracaos().end());
			}
			m_total_volumen_ocupado=Mejor.Get_Volumen();
			//Actualizar cantidades de piezas
			for (it=Mejor.Get_Configuracaos().begin();it!=Mejor.Get_Configuracaos().end();it++)
			{
				for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
				{
					m_Pieces[(*itC).Get_Id()].Add_Num((*itC).Get_Num());
				}

			}
	
			
			VerificarSolucionMC(m_ConfiguracaosMC);
		}

	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_total_volumen_ocupado!=m_total_volumen && perturbar==false);
	if (perturbar==false && m_total_volumen_ocupado<m_max_total_volumen_ocupado_mejora)
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;

	if (perturbar!=true) m_Aleatorizado=true;

}

//Aqui elijo tres bin y los mezclo ??
//^*******************Mejora Local multi container
// aqui lo que hacemos es vaciar un bin

void CONTAINER::MejoraLocalMCQuitarTresBin(bool perturbar)
{
//	return;
	if (m_ConfiguracaosMC.size()<=6)
		return;
	//Tengo la lista de bins
	m_Aleatorizado=false;


	m_eliminar_espacios=true;
	std::list< std::pair< int ,std::list<CONFIGURACAO> > > lista;
	m_max_total_volumen_ocupado_mejora=0;

//	printf("**************************MEJORA**************************\n");
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	std::list< std::pair<int, std::list< CONFIGURACAO> > > ::reverse_iterator itr,itr2,itr3;
	std::list< std::pair<int, std::list< CONFIGURACAO> > > ::iterator it,it2,itfin;
	std::list< CONFIGURACAO> ::iterator itC;
	//Construyo la lista tabu 
//	m_Pieces_Tabu.clear();
	for (int j=0;j<m_Q;j++)
		m_Pieces_Tabu[j]=0;
	std::vector< int > lista_quito;
	lista_quito.push_back(0);
	lista_quito.push_back(0);
	lista_quito.push_back(0);

	MOVIMIENTOMC Mejor(this);
	do
	{
//		FILE *fin3;
//		fopen_s(&fin3,"kk.txt","a+");
//		fprintf(fin3,"\n");
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
//		fclose(fin3);

		//Tenemos un set de enteros para evitar movimientos que constituyan 
		//volver a eliminar la misma region del espacio
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado_mejora;
//		int perdida_media=perdida/m_Spaces.size();
		Mejor.Set_Vol(0);
		int alea1=0;//get_random(0,m_ConfiguracaosMC.size()/3);
		int alea2=0;//get_random(alea1+1,m_ConfiguracaosMC.size());
		int alea3=0;//get_random(alea2,m_ConfiguracaosMC.size()-1);
		if (perturbar==true)
		{
			alea1=get_random(0,m_ConfiguracaosMC.size()/3);
			alea2=get_random(alea1+1,m_ConfiguracaosMC.size()/2);
			alea3=get_random(alea2,m_ConfiguracaosMC.size()-1);
		}
		//Solamente queremos movernos para mejorar el que tenemos

		//Deberia hacerlo aletoriamente

		int lugar=0;
		int lugar2=0;
		int lugar3=0;
		int kki = 0;
		for (itr=m_ConfiguracaosMC.rbegin();itr!=m_ConfiguracaosMC.rend() && (kki<20) && (*itr).first<=(m_total_volumen/(m_Best_nbins-1));itr++,lugar++)
		{	
			if (perturbar==true && lugar!=alea1) continue;
			m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
//			m_Pieces_Tabu.clear();
			//Ya esta puesto la n
			m_total_volumen_ocupado-=(*itr).first;
			itr2=itr;
			itr2++;
			if (itr2==m_ConfiguracaosMC.rend())
				break;
			lugar2=lugar+1;
			for (;itr2!=m_ConfiguracaosMC.rend() && (kki<20) && (*itr2).first<=(m_total_volumen/(m_Best_nbins-1));itr2++,lugar2++)
			{
				int temp=m_total_volumen_ocupado;
				m_total_volumen_ocupado-=(*itr2).first;

				if (perturbar==true && lugar2!=alea2) continue;
				itr3=itr2;
				itr3++;
				if (itr3==m_ConfiguracaosMC.rend())
					break;
				lugar3=lugar2+1;
				for (;itr3!=m_ConfiguracaosMC.rend() && (kki<20);itr3++,lugar3++)
				{
					if (perturbar==true && lugar3!=alea3) continue;
					//Quito el segundo bin
					int temp2=m_total_volumen_ocupado;
					m_total_volumen_ocupado-=(*itr3).first;
//				m_Pieces_Tabu.clear();
					for (int j=0;j<m_Q;j++)
						m_Pieces_Tabu[j]=m_Pieces[j].Get_Num();
					//Vacio el primer bin
					for (itC=(*itr).second.begin();itC!=(*itr).second.end();itC++)
					{
						m_Pieces_Tabu[(*itC).Get_Id()]=(m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num());

					}
					//Vacio el segundo bin
					for (itC=(*itr2).second.begin();itC!=(*itr2).second.end();itC++)
					{
						m_Pieces_Tabu[(*itC).Get_Id()]=(m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num());

					}
					//Vacio el tercer bin
					for (itC=(*itr3).second.begin();itC!=(*itr3).second.end();itC++)
					{
						m_Pieces_Tabu[(*itC).Get_Id()]=(m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num());

					}
					lista.clear();
				//Ahora relleno lo que queda, tengo que decirle cuantos quiero rellenar como he q
				//quitado dos pues relleno dos
//				if (m_iter_actual==618)	printf("h3");
					RellenarVariosBin(lista,3);
					kki++;
//				if (m_iter_actual==618)	printf("h4");
				//Vuelvo a colocar estos que son los que estaban equivocados
					lista_quito[0]=lugar;lista_quito[1]=lugar2;lista_quito[2]=lugar3;
				//Esta funcion me rellena lo que teniamos

					if ((m_total_volumen_ocupado)>Mejor.Get_Volumen())
					{
						
						Mejor.CambiarMejor(lista,(m_total_volumen_ocupado),lista_quito);

					}
//				if (m_iter_actual==618)	printf("h5");

					m_total_volumen_ocupado=temp2;
					if (perturbar==true) break;

//				lugar2++;
				}
				m_total_volumen_ocupado=temp;

				if (perturbar==true) break;
			}
//			lugar++;
			if (perturbar==true) break;

		}

//		PintarSolucion(Mejor.Get_Configuracaos());
//		m_eliminar_espacios=true;
		//esta variable es para que lo deje todo bien
//		ConstruirSolucion(Mejor.Get_Configuracaos(),true);

//		DibujarSolucion(m_Spaces,m_Configuracaos);
//Aqui tengo que volver a colocar todo correctamente	
		if (Mejor.Get_Volumen()>m_max_total_volumen_ocupado_mejora || perturbar==true )
		{
			//Primer lugar borro los dos bins que he cambiado
//			if (m_iter_actual==618)	printf("here1");
			int cont=0;
			int vol=0;
			int tot=m_ConfiguracaosMC.size()-1;
			itfin=m_ConfiguracaosMC.end();
			for (it=m_ConfiguracaosMC.begin(),cont=0;it!=itfin ;cont++)
			{
				if (cont==(tot-Mejor.Get_Quitados()[0]) || cont==(tot-Mejor.Get_Quitados()[1]) || cont==(tot-Mejor.Get_Quitados()[2]) )
				{
					for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
					{

//						m_Pieces[(*itC).Get_Id()].Set_Num((m_Pieces[(*itC).Get_Id()].Get_Num()-(*itC).Get_Num()));
						m_Pieces[(*itC).Get_Id()].Set_Num(0);


					}
					it=m_ConfiguracaosMC.erase(it);
				}
				else
				{
					vol+=(*it).first;	
				}
				++it;
			}
			//Aqui pongo los valores de las nuevas
			for (it=Mejor.Get_Configuracaos().begin();it!=Mejor.Get_Configuracaos().end() ;it++)
			{
				InsertarOrden(m_ConfiguracaosMC,(*it));
//				m_ConfiguracaosMC.insert(m_ConfiguracaosMC.begin(),Mejor.Get_Configuracaos().begin(),Mejor.Get_Configuracaos().end());
			}
			m_total_volumen_ocupado=Mejor.Get_Volumen();
			//Actualizar cantidades de piezas
			for (it=Mejor.Get_Configuracaos().begin();it!=Mejor.Get_Configuracaos().end();it++)
			{
				for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
				{
					m_Pieces[(*itC).Get_Id()].Add_Num((*itC).Get_Num());
				}

			}
	
//			for (int j=0;j<m_Q;j++)
//				m_Pieces[j].Set_Num(m_Pieces_Tabu[j]);
			
//			printf("Algo hace %d %d\n",m_total_volumen_ocupado,m_total_volumen);
			VerificarSolucionMC(m_ConfiguracaosMC);
//			if (m_iter_actual==618)	printf("here2");
		}

//		m_eliminar_espacios=false;
	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_total_volumen_ocupado!=m_total_volumen && perturbar==false);
	if (perturbar==false && m_total_volumen_ocupado<m_max_total_volumen_ocupado_mejora)
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
//	printf("%d\n",kki);
	if (perturbar!=true) m_Aleatorizado=true;
//	if (m_iter_actual==618)	printf("here");

}
//^*******************Mejora Local multi container
// aqui lo que hacemos es quitar un tanto por ciento de los ultimos bin
// quitamos al menos un bin

void CONTAINER::MejoraLocalMCQuitarUltimos(bool global,bool perturbar)
{
	//Tengo la lista de bins
	m_Aleatorizado=false;


	m_eliminar_espacios=true;
	m_max_total_volumen_ocupado_mejora=0;

//	printf("**************************MEJORA**************************\n");
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	//Tenemos un set de enteros para evitar movimientos que constituyan 
	//volver a eliminar la misma region del espacio
	m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
	std::set<int> volumenes_estudiados;

	m_eliminar_espacios=true;
	m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado_mejora;
	std::list< std::pair<int,std::list< CONFIGURACAO > > >  ::iterator it,it2,itfin=m_ConfiguracaosMC.end();
	std::list< CONFIGURACAO> ::iterator itC;

	//Deberia hacerlo aletoriamente

//	int lugar=0;
	m_total_volumen_ocupado=0;
	for (int j=0;j<m_Q;j++)
		m_Pieces_Tabu[j]=0;
	int desde=30;
	int hasta=90;
	if (perturbar==true) 
	{ 
		desde=0;
		hasta=90;
	}
	double valor=(double)get_random(desde,hasta)/(double)100;
//	printf("%f  J",valor); 
//	printf("\n");
	bool insertar=false;
	int penultimoval=0;
//	lugar=m_ConfiguracaosMC.size();
	for (it=m_ConfiguracaosMC.begin();it!=itfin ;)
	{	
		it2=it;
		it2++;
		m_total_volumen_ocupado+=(*it).first;
		//Quitamos el container si todo se puede quitar
		if ((m_total_volumen_ocupado<((double)(valor)*(m_total_volumen)) ) && (it2!=itfin)  )
		{
//			m_total_volumen_ocupado+=(*it).first;
			//Ya esta puesto la nueva 
//			printf("%d\n",(*it).first);
			for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
			{
				m_Pieces_Tabu[(*itC).Get_Id()]+=(*itC).Get_Num();
			}
			++it;

		}
		else
		{
			//Ahora quitamos solamente un trozo
			m_total_volumen_ocupado-=(*it).first;
			if (m_total_volumen_ocupado<((double)(valor)*(m_total_volumen)) )
			{
				penultimoval=m_total_volumen_ocupado;
				for (itC=(*it).second.begin();itC!=(*it).second.end();)
				{
//					m_Pieces_Tabu[(*itC).Get_Id()]=(*itC).Get_Num();
					m_total_volumen_ocupado+=(*itC).Get_Volumen();
					if (m_total_volumen_ocupado<((double)(valor)*(m_total_volumen)) )
						++itC;
					else
						itC=(*it).second.erase(itC);
				}
				//Tengo que terminar de rellenar este bin 
				//con el constructivo
				int temp=m_total_volumen_ocupado;
				ConstruirSolucionBin((*it).second,false);
				m_total_volumen_ocupado=temp;
				++it;
				insertar=true;
			}
			else 
				it=m_ConfiguracaosMC.erase(it);
		}
	}
	if (insertar==true)
	{
		int volthisbin=0;
		for (itC=m_ConfiguracaosMC.back().second.begin();itC!=m_ConfiguracaosMC.back().second.end();itC++)
		{
				volthisbin+=(*itC).Get_Volumen();
		}
		m_ConfiguracaosMC.back().first=volthisbin;
		m_total_volumen_ocupado=penultimoval+volthisbin;
	}
	if (m_ConfiguracaosMC.size()<(m_Best_nbins-1))
	{
		if (global==true)
		RellenarVariosBinGlobal(m_ConfiguracaosMC);
		else
		RellenarVariosBin(m_ConfiguracaosMC);
	}
	//Esto es para que no la cambie 
	if (m_total_volumen_ocupado<=m_max_total_volumen_ocupado_mejora && perturbar!=true )
	{
		m_ConfiguracaosMC=m_Best_ConfiguracaoMC;
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	}
	//en este caso cambio la solucion
	else
	{
		for (int j=0;j<m_Q;j++)
			m_Pieces[j].Set_Num(m_Pieces_Tabu[j]);

	}
	m_Aleatorizado=true;

}

//Buqueda local que va quitando desde 3 hasta el 90 por ciento de la solucion y la vuelve a lle nar
//^*******************Mejora Local multi container
// aqui lo que hacemos es quitar un tanto por ciento de los ultimos bin
// quitamos al menos un bin

void CONTAINER::MejoraLocalMCQuitarUltimosLS(bool global,bool perturbar)
{
	//Tengo la lista de bins
	m_Aleatorizado=false;

	int kki=0;
	m_eliminar_espacios=true;
	m_max_total_volumen_ocupado_mejora=0;

//	printf("**************************MEJORA**************************\n");
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	//Tenemos un set de enteros para evitar movimientos que constituyan 
	//volver a eliminar la misma region del espacio
	m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
	double valor=0;
	bool mejorar=false;
	do{
		mejorar=false;
//		FILE *fin3;
//		fopen_s(&fin3,"kk.txt","a+");
//		fprintf(fin3,"\n");
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
//		fclose(fin3);

		//Tenemos un set de enteros para evitar movimientos que constituyan 
		//volver a eliminar la misma region del espacio
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado_mejora;
//		int perdida_media=perdida/m_Spaces.size();
	
		kki=0;
		m_eliminar_espacios=true;
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado_mejora;
		std::list< std::pair<int,std::list< CONFIGURACAO > > >  ::iterator it,it2,itfin=m_ConfiguracaosMC.end();
		std::list< CONFIGURACAO> ::iterator itC;

		//Deberia hacerlo aletoriamente

//	int lugar=0;
		m_total_volumen_ocupado=0;
		for (int quito=90;quito>30;quito-=10)
		{
			for (int j=0;j<m_Q;j++)
				m_Pieces_Tabu[j]=0;
			m_total_volumen_ocupado=0;
			//	printf("\n");
			bool insertar=false;
			int penultimoval=0;
			valor=(double)quito/(double)100;
//	lugar=m_ConfiguracaosMC.size();
			for (it=m_ConfiguracaosMC.begin();it!=itfin ;)
			{	
				it2=it;
				it2++;
				m_total_volumen_ocupado+=(*it).first;
				//Quitamos el container si todo se puede quitar
				if ((m_total_volumen_ocupado<((double)(valor)*(m_total_volumen)) ) && (it2!=itfin)  )
				{
					for (itC=(*it).second.begin();itC!=(*it).second.end();itC++)
					{
						m_Pieces_Tabu[(*itC).Get_Id()]=(*itC).Get_Num();
					}
					++it;
				}
				else
				{
					//Ahora quitamos solamente un trozo
					m_total_volumen_ocupado-=(*it).first;
					if (m_total_volumen_ocupado<((double)(valor)*(m_total_volumen)) )
					{
						penultimoval=m_total_volumen_ocupado;
						for (itC=(*it).second.begin();itC!=(*it).second.end();)
						{
//							m_Pieces_Tabu[(*itC).Get_Id()]=(*itC).Get_Num();
							m_total_volumen_ocupado+=(*itC).Get_Volumen();
							if (m_total_volumen_ocupado<((double)(valor)*(m_total_volumen)) )
								++itC;
							else
								itC=(*it).second.erase(itC);
						}
						//Tengo que terminar de rellenar este bin 
						//con el constructivo
						int temp=m_total_volumen_ocupado;
						ConstruirSolucionBin((*it).second,false);
						m_total_volumen_ocupado=temp;
						++it;
						insertar=true;
					}
					else 
						it=m_ConfiguracaosMC.erase(it);
				}
				
			}
		
			if (insertar==true)
			{
				int volthisbin=0;
				for (itC=m_ConfiguracaosMC.back().second.begin();itC!=m_ConfiguracaosMC.back().second.end();itC++)
				{
						volthisbin+=(*itC).Get_Volumen();
				}
				m_ConfiguracaosMC.back().first=volthisbin;
				m_total_volumen_ocupado=penultimoval+volthisbin;
			}
			if (m_ConfiguracaosMC.size()<(m_Best_nbins-1))
			{
				if (global==true)
				RellenarVariosBinGlobal(m_ConfiguracaosMC);
				else
				RellenarVariosBin(m_ConfiguracaosMC);
			}
		//Esto es para que no la cambie 
			if (m_total_volumen_ocupado<=m_max_total_volumen_ocupado_mejora && perturbar!=true )
			{
				m_ConfiguracaosMC=m_Best_ConfiguracaoMC;
				m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
			}
			//en este caso cambio la solucion
			else
			{
				m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
				mejorar=true;
				for (int j=0;j<m_Q;j++)
					m_Pieces[j].Set_Num(m_Pieces_Tabu[j]);
				m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

			}
			if (mejorar==true) break;
		}
	}while(mejorar==true && m_total_volumen_ocupado!=m_total_volumen);
	m_Aleatorizado=true;
	VerificarSolucionMC(m_ConfiguracaosMC);
}
void CONTAINER::MejoraLocalVaciado(bool perturbar)
{
	int kkk = 0;
	int kkkki = 0;
	if (m_Spaces.size()<2) return;
	int kki = 0;
	int ka = 0;
	m_eliminar_espacios=true;
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;

	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	do
	{
		//Tenemos un set de enteros para evitar movimientos que constituyan 
		//volver a eliminar la misma region del espacio
		std::set<int> volumenes_estudiados;
		kki=0;
		m_eliminar_espacios=true;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado_mejora;
//		int perdida_media=perdida/m_Spaces.size();
		MOVIMIENTO Mejor(this),Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		Mejor.Set_Vol(0);
		std::list<SPACE> ::reverse_iterator it,it2;
		int alea=0;
		if (perturbar==true)
			 alea=get_random(0,m_Spaces.size()-2)+1;
		int cont=0;
		//Deberia hacerlo aletoriamente
		bool parar=false;
		for (it=m_Spaces.rbegin();it!=m_Spaces.rend() && kki<m_max_movimientos && parar!=true;it++)
		{
			
//			SPACE kkk=(*it);
			cont++;
			if (perturbar==true && alea!=cont) //POR AQUÍIIIIIIIIIIIII
				continue;
			it2=it;
			it2++;
			/*kki2++;
			kki = 0;*/
			if (it2==m_Spaces.rend())
				break;
			for (;it2!=m_Spaces.rend() && kki<m_max_movimientos  && parar!=true;it2++)
			{
				//Esta se trata de quitar todo lo que envuelve a estos dos
				//rectangulos y volver a rellenar

				int minx1=min((*it).Get_x1(),(*it2).Get_x1());
				int maxx2=max((*it).Get_x2(),(*it2).Get_x2());
				int miny1=min((*it).Get_y1(),(*it2).Get_y1());
				int maxy2=max((*it).Get_y2(),(*it2).Get_y2());
				int minz1=min((*it).Get_z1(),(*it2).Get_z1());
				int maxz2=max((*it).Get_z2(),(*it2).Get_z2());
				CONFIGURACAO Configuracao(this,0,minx1,miny1,minz1,maxx2,maxy2,maxz2,1,1,0);
				std::pair<std::set<int> ::iterator, bool> p=volumenes_estudiados.insert(Configuracao.Get_Volumen());
				//Si ya estaba probar con otro
				if (p.second==false)
					continue;
				
				kki++;
				std::list<CONFIGURACAO> lista=m_Configuracaos;
				ActualizarListaDeBloques(Configuracao,lista, false);
				ConstruirSolucionMovimientos(lista, false);

				if (ComprobarConfiguracaosNoIntersectan(lista) == true)
				{
					printf("%d\n", kkk);
					printf("aqui1 inters");
					for (int i = 0;;);
				}
				if (ComprobarFullSupport(lista)==false)
				{
					printf("%d\n", kkk);
					printf("aqui1");
					for (int i = 0;;);
				}
				if (m_total_volumen_ocupado>Mejor.Get_Volumen())
				{
					
					Mejor.CambiarMejor(lista,m_total_volumen_ocupado);
				}
				if (m_descendent==true && Mejor.Get_Val()>m_max_total_volumen_ocupado)
					parar=true;

				if (perturbar==true)
				break;

			}
			if (perturbar==true)
				break;

		}

		//esta variable es para que lo deje todo bien
		m_eliminar_espacios=false;
		ConstruirSolucion(Mejor.Get_Configuracaos(),true);
		if (ComprobarConfiguracaosNoIntersectanSpaces(m_Configuracaos) == true)
			printf("%d", ka);
		if (ComprobarConfiguracaosNoIntersectan(m_Configuracaos) == true)
			int kj = 1;
		if (ComprobarFullSupport(m_Configuracaos) == false)
		{
			printf("aqui2 %d\n",ka);
			for (int i = 0;;);
		}

		ComprobarTodosPosible(m_Configuracaos);
		DibujarSolucion(m_Spaces,m_Configuracaos);
		VerificarSolucion(m_Configuracaos);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora || perturbar==true)
		{
			lista_configuracaos=m_Configuracaos;
		}
	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && perturbar==false && m_un_movimiento!=true && m_total_volumen_ocupado!=m_total_volumen);
	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

	if (m_max_total_volumen_ocupado_mejora>m_max_total_volumen_ocupado)
		m_max_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	//vuelvo a ponerla 
	//esta variable es para que lo deje todo bien

	if (perturbar != true)
	{
		ConstruirSolucion(lista_configuracaos, true);
		m_total_volumen_ocupado = m_max_total_volumen_ocupado_mejora;
	}

	if (m_imprimir_mejoras==true)
	{
		printf("umafuera \n");
		m_fintime=clock();
		m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

		FILE *fin3;
		fin3=fopen(m_file_to_write,"a+");
		double pt=((double)m_max_total_volumen_ocupado/(double)(m_X*m_Y*m_Z))*100;
		fprintf(fin3,"%s\tVaciado\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
		fclose(fin3);
	}
}
void CONTAINER::MejoraLocalVaciadoTres(bool perturbar)
{
	int kki=0;
	m_eliminar_espacios=true;
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;

	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	do
	{
		kki=0;
		m_eliminar_espacios=true;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado_mejora;
//		int perdida_media=perdida/m_Spaces.size();
		MOVIMIENTO Mejor(this),Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		Mejor.Set_Vol(0);
		std::list<SPACE> ::reverse_iterator it,it2,it3;
		int alea=0;
		if (perturbar==true)
			 alea=get_random(1,m_Spaces.size()-2);
		int cont=0;
		//Deberia hacerlo aletoriamente
		for (it=m_Spaces.rbegin();it!=m_Spaces.rend() && kki<1000;it++)
		{
			
			cont++;
			if (perturbar==true && alea!=cont) 
				continue;
			it2=it;
			it2++;
			if (it2==m_Spaces.rend())
				break;
			for (;it2!=m_Spaces.rend() && kki<1000;it2++)
			{
				it3=it2;
				it3++;
				if (it3==m_Spaces.rend())
					break;
			for (;it3!=m_Spaces.rend() && kki<1000;it3++)
			{

//				if ((*it2).Get_Volumen()<perdida_media)
//					continue;

				kki++;
				//Esta se trata de quitar todo lo que envuelve a estos dos
				//rectangulos y volver a rellenar
				int minx1=min(min((*it).Get_x1(),(*it2).Get_x1()),(*it3).Get_x1());
				int maxx2=max(max((*it).Get_x2(),(*it2).Get_x2()),(*it3).Get_x2());
				int miny1=min(min((*it).Get_y1(),(*it2).Get_y1()),(*it3).Get_y1());
				int maxy2=max(max((*it).Get_y2(),(*it2).Get_y2()),(*it3).Get_y2());
				int minz1=min(min((*it).Get_z1(),(*it2).Get_z1()),(*it3).Get_z1());
				int maxz2=max(max((*it).Get_z2(),(*it2).Get_z2()),(*it3).Get_z2());
				CONFIGURACAO Configuracao(this,0,minx1,miny1,minz1,maxx2,maxy2,maxz2,1,1,0);
				std::list<CONFIGURACAO> lista=m_Configuracaos;
				ActualizarListaDeBloques(Configuracao,lista, false);
				ConstruirSolucionMovimientos(lista,true);
				if (m_total_volumen_ocupado>Mejor.Get_Volumen())
				{
					Mejor.CambiarMejor(lista,m_total_volumen_ocupado);
				}

			}
				if (perturbar==true)
					break;


			}
			if (perturbar==true)
				break;
		}
//		PintarSolucion(Mejor.Get_Configuracaos());
//		m_eliminar_espacios=true;
		//esta variable es para que lo deje todo bien
		m_eliminar_espacios=false;
		ConstruirSolucion(Mejor.Get_Configuracaos(),true);
		DibujarSolucion(m_Spaces,m_Configuracaos);
		VerificarSolucion(m_Configuracaos);
	
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora ||perturbar==true)
		{	
			lista_configuracaos=m_Configuracaos;
		}
		printf("uma %d %d\n",m_total_volumen_ocupado,kkkk);
//		m_eliminar_espacios=false;
	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && perturbar==false);
	if (m_max_total_volumen_ocupado_mejora>m_max_total_volumen_ocupado)
		m_max_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	//vuelvo a ponerla 
	//esta variable es para que lo deje todo bien
	ConstruirSolucion(lista_configuracaos,true);
	
	if (perturbar!=true)
	m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;

	if (m_imprimir_mejoras==true)
	{
		printf("umafuera \n");
		m_fintime=clock();
		m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

		FILE *fin3;
		fin3=fopen(m_file_to_write,"a+");
		double pt=((double)m_max_total_volumen_ocupado/(double)(m_X*m_Y*m_Z))*100;
		fprintf(fin3,"%s\tVaciado\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
		fclose(fin3);
	}
}
//Esta mejora quito un bloque mueve todos los que tienen el mismo tipo
//en la configuracion y continuo
void CONTAINER::MejoraLocalQuitarBloque(bool perturbar)
{
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;

	int kki=0;
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	do
	{
//	EscribirSolucionLatex2D(m_Configuracaos);
		kki=0;
		m_eliminar_espacios=true;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
		MOVIMIENTO Mejor(this),Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		Mejor.Set_Vol(0);
		std::list<CONFIGURACAO> ::iterator it;
		int hasta=m_Configuracaos.size();
		int cont=0,alea=0;
		if (perturbar==true)
			alea=get_random(1,hasta);
		bool parar=false;
		for (it=m_Configuracaos.begin();it!=m_Configuracaos.end() && cont<=hasta && parar!=true;)
		{

			cont++;
			if (perturbar==true && alea!=cont) 
				continue;
			//borro este bloque, pero primero me quedo en la direccion que 
			//voy a compactar los bloques
			short int lugar=(*it).Get_orig();
			CONFIGURACAO Temp=(*it);
			it=m_Configuracaos.erase(it);
			//Cambiado lo de abajo
			it--;

			std::list<CONFIGURACAO> lista=m_Configuracaos;
//			PintarSolucion(lista);
			//una vez que lo he quitado muevo hacia las esquinas de los lados
			//que toquen dependiendo del lugar 
			//Tengo que mirar si ha cambiado algo ya que si no ha cambiado 
			//nada entonces no merece la pena que construya la solucion
			bool algo_se_mueve=CompactarConfiguracaosEsquinas(lista,lugar);
			if (algo_se_mueve==false)
			{
				//Cambiado lo de abajo
				/*m_Configuracaos.push_back(Temp);*/
				InsertarConfiguracaoOrden(Temp,m_Configuracaos);

				continue;
			}
			ComprobarConfiguracaosNoIntersectan(lista);
//			PintarSolucion(lista);
			//Una vez que tengo esto es volver a rellenar
			//0 es de forma aleatoria la eleccion de la pieza
			//1 me dice si quiero rellenar las que faltan de la manera normal
			//2 si es por la fobjetivo nueva
			//
//			if (cont==12 && Temp.Get_x1()==0 && Temp.Get_x2()==8)
//			if (cont==7)
//			EscribirSolucionLatex2D(lista);

			ConstruirSolucionMovimientos(lista,true);
			ComprobarConfiguracaosNoIntersectan(lista);

			if (m_total_volumen_ocupado>Mejor.Get_Volumen())
			{

				Mejor.CambiarMejor(lista,m_total_volumen_ocupado);
			}
			//Esto es para mantener la misma configuracao inicial
			/*m_Configuracaos.push_back(Temp);*/
			InsertarConfiguracaoOrden(Temp, m_Configuracaos);

			if (m_descendent==true && Mejor.Get_Val()>m_max_total_volumen_ocupado)
				parar=true;
			if (perturbar==true)
				break;
			++it;
			
		}
		//No necesito los espacios, los puedo quitar
		//es importante que la ponga para la solucion
		ConstruirSolucion(Mejor.Get_Configuracaos(),true);
		DibujarSolucion(m_Spaces,m_Configuracaos);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora || perturbar==true)
		{
//			EscribirSolucionLatex2D(m_Configuracaos);
//			printf("uma Bloqueuma Bloqueuma Bloqueuma Bloqueuma Bloque %d %d\n",m_total_volumen_ocupado,kkkk);
			lista_configuracaos=m_Configuracaos;
		}

//		PintarSolucion(Mejor.Get_Configuracaos());
//		m_eliminar_espacios=true;
//		m_eliminar_espacios=false;

	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_un_movimiento!=true);
	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

	if (m_max_total_volumen_ocupado_mejora>m_max_total_volumen_ocupado)
		m_max_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	//vuelvo a ponerla 
//	m_Configuracaos=lista_configuracaos;
	m_eliminar_espacios=false;
	//vuelvo a ponerla 
	//esta variable es para que lo deje todo bien

	ConstruirSolucion(lista_configuracaos,true);

	if (perturbar!=true) 
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	VerificarSolucion(m_Configuracaos);
	if (m_imprimir_mejoras==true)
	{
		printf("umafuera \n");
		m_fintime=clock();
		m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

		FILE *fin3;
		fin3=fopen(m_file_to_write,"a+");
		double pt=((double)m_max_total_volumen_ocupado/(double)(m_X*m_Y*m_Z))*100;
		fprintf(fin3,"%s\tBloque\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
		fclose(fin3);
	}
}
/*
//Esta mejora quito un bloque mueve todos los que tienen el mismo tipo
//en la configuracion y continuo
void CONTAINER::MejoraLocalQuitarBloquePorCiento(bool perturbar)
{
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;

	int kki=0;
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	do
	{
//	EscribirSolucionLatex2D(m_Configuracaos);
		kki=0;
		m_eliminar_espacios=true;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
		MOVIMIENTO Mejor(this),Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		Mejor.Set_Vol(0);
		std::list<CONFIGURACAO> ::iterator it;
		int hasta=m_Configuracaos.size();
		int cont=0,alea=0;
		if (perturbar==true)
			alea=get_random(1,hasta);
		bool parar=false;
		for (it=m_Configuracaos.begin();it!=m_Configuracaos.end() && cont<=hasta && parar!=true;it++)
		{

			cont++;
			if (perturbar==true && alea!=cont) 
				continue;
			short int lugar=(*it).Get_orig();
			CONFIGURACAO Temp=(*it);

			lista=m_Configuracaos;
			//lo borro de la lista
			for (
			std::list<CONFIGURACAO> lista,lista_temp;
			//Eliminar un porcentaje hasta llegar al final
			for (;it2!=m_Configuracaos.end() && Vol<(m_total_volumen/10);it2++)
			{
				if ((*it2).Get_ori
				//borro este bloque, pero primero me quedo en la direccion que 
				//voy a compactar los bloques
				lista=m_Configuracaos;
//				lista_temp.push_back(Temp);
	//			PintarSolucion(lista);
				//una vez que lo he quitado muevo hacia las esquinas de los lados
				//que toquen dependiendo del lugar 
				//Tengo que mirar si ha cambiado algo ya que si no ha cambiado 
				//nada entonces no merece la pena que construya la solucion
				bool algo_se_mueve=CompactarConfiguracaosEsquinas(lista,lugar);
			}

//			PintarSolucion(lista);
			//Una vez que tengo esto es volver a rellenar
			//0 es de forma aleatoria la eleccion de la pieza
			//1 me dice si quiero rellenar las que faltan de la manera normal
			//2 si es por la fobjetivo nueva
			//
//			if (cont==12 && Temp.Get_x1()==0 && Temp.Get_x2()==8)
//			if (cont==7)
//			EscribirSolucionLatex2D(lista);

			ConstruirSolucionMovimientos(lista,true);
			ComprobarConfiguracaosNoIntersectan(lista);

			if (m_total_volumen_ocupado>Mejor.Get_Volumen())
			{

				Mejor.CambiarMejor(lista,m_total_volumen_ocupado);
			}
			//Esto es para mantener la misma configuracao inicial

			m_Configuracaos.push_back(Temp);

			if (m_descendent==true && Mejor.Get_Val()>m_max_total_volumen_ocupado)
				parar=true;
			if (perturbar==true)
				break;


		}
		std::list<CONFIGURACAO> ::iterator itkk;
		//No necesito los espacios, los puedo quitar
		//es importante que la ponga para la solucion
		ConstruirSolucion(Mejor.Get_Configuracaos(),true);
		DibujarSolucion(m_Spaces,m_Configuracaos);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora || perturbar==true)
		{
//			EscribirSolucionLatex2D(m_Configuracaos);
			printf("uma Bloqueuma Bloqueuma Bloqueuma Bloqueuma Bloque %d %d\n",m_total_volumen_ocupado,kkkk);
			lista_configuracaos=m_Configuracaos;
		}

//		PintarSolucion(Mejor.Get_Configuracaos());
//		m_eliminar_espacios=true;
//		m_eliminar_espacios=false;

	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_un_movimiento!=true);
	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

	if (m_max_total_volumen_ocupado_mejora>m_max_total_volumen_ocupado)
		m_max_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	//vuelvo a ponerla 
//	m_Configuracaos=lista_configuracaos;
	m_eliminar_espacios=false;
	//vuelvo a ponerla 
	//esta variable es para que lo deje todo bien

	ConstruirSolucion(lista_configuracaos,true);

	if (perturbar!=true) 
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	VerificarSolucion(m_Configuracaos);
	if (m_imprimir_mejoras==true)
	{
		printf("umafuera \n");
		m_fintime=clock();
		m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

		FILE *fin3;
		fopen_s(&fin3,"Results.txt","a+");
		double pt=((double)m_max_total_volumen_ocupado/(double)(m_X*m_Y*m_Z))*100;
		fprintf(fin3,"%s\tBloque\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
		fclose(fin3);
	}
}*/
//Esta mejora quito un bloque mueve todos los que tienen el mismo tipo
//en la configuracion y continuo
void CONTAINER::MejoraLocalReducirBloque(bool perturbar)
{
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;
	int kkkkj = 0;
	int kki=0;
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	do
	{
//	EscribirSolucionLatex2D(m_Configuracaos);
//		printf("KKKKK\n");
		kki=0;
		m_eliminar_espacios=true;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
		MOVIMIENTO Mejor(this),Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		Mejor.Set_Vol(0);
		std::list<CONFIGURACAO> ::iterator it, it2;
		int hasta=m_Configuracaos.size();
		int cont=0,alea=0;
		if (perturbar==true)
			alea=get_random(1,hasta);
		bool parar=false;
		for (it=m_Configuracaos.begin();it!=m_Configuracaos.end() && cont<=hasta && parar!=true;/*it++*/)
		{
			cont++;
			if (perturbar==true && alea!=cont) 
				continue;
			//borro este bloque, pero primero me quedo en la direccion que 
			//voy a compactar los bloques
			short int lugar=(*it).Get_orig();
			CONFIGURACAO Temp=(*it);
			std::list<CONFIGURACAO> lista2;
			/*if ((*it).Get_Id_bloque()>0)
				for (it2=m_Configuracaos.begin())*/
			/*DibujarOpenGL(m_Configuracaos);*/
			it=m_Configuracaos.erase(it);
			/*if (it!=m_Configuracaos.begin())
			it--;*/
			/*DibujarOpenGL(m_Configuracaos);*/
//			DibujarOpenGL(m_Configuracaos);
//			Mejor.Set_Nuevos(m_Configuracaos);
//			m_Configuracaos_new = m_Configuracaos;
			std::list<CONFIGURACAO> lista;
			//Aqui reduzcon un bloque si se da el caso
			for (int register i=1;i<=Temp.Get_dx() && perturbar != true;i++)
			{
				int sumoi=((Temp.Get_x2()-Temp.Get_x1())/Temp.Get_dx());

				for (int register j=1;j<=Temp.Get_dy() && perturbar != true;j++)
				{
					int sumoj=((Temp.Get_y2()-Temp.Get_y1())/Temp.Get_dy());

					for (int register k=1;k<=Temp.Get_dz() && perturbar != true;k++)
					{
						int sumok=((Temp.Get_z2()-Temp.Get_z1())/Temp.Get_dz());

						if ((i+j+k)==(Temp.Get_dx()+Temp.Get_dy()+Temp.Get_dz()) && (i+j+k)!=3)
							continue;
						if ((i+j+k)!=3)
						{
							if (Temp.Get_orig() > 8)
							{
								for (int kikk = 0;;){ printf("mierda1"); }
							}
							// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z) 
							if (Temp.Get_orig()==1)
							{
								CONFIGURACAO Configuracao(this,Temp.Get_Id(),Temp.Get_x1(),Temp.Get_y1(),Temp.Get_z1(),i*sumoi,j*sumoj,k*sumok,i,j,k,Temp.Get_Tipo(),i*j*k,Temp.Get_orig());
								lista=m_Configuracaos;
								if (m_full_supported == true)
								{
									if (ComprobarFullSupportUno(Configuracao, lista))
									{
										/*lista.push_back(Configuracao);*/
										InsertarConfiguracaoOrden(Configuracao, lista);
										if (Temp.Get_z2() == Configuracao.Get_z2())
										{
											CONFIGURACAO ConfFantasma(this, 0, Configuracao.Get_x2(), Configuracao.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
											if (Temp.Get_dy() != 1)
											{
												CONFIGURACAO ConfFantasma2(this, 0, Configuracao.Get_x1(), Configuracao.Get_y2(), Temp.Get_z2(), Configuracao.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
												ActualizarListaDeBloquesReducir(ConfFantasma2, lista, lista2);
											}
										}
										else
										{
											CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
										}
									}
								}
								else
									InsertarConfiguracaoOrden(Configuracao, lista);
									/*lista.push_back(Configuracao);*/
								//DibujarOpenGL(lista);
								//DibujarOpenGL(lista);
								if (Configuracao.Get_Volumen()==0)
									printf("mierda1");
							}

							if (Temp.Get_orig() == 2)
							{
								CONFIGURACAO Configuracao(this, Temp.Get_Id(), Temp.Get_x1(), Temp.Get_y2() - j * sumoj, Temp.Get_z1(), i * sumoi, j * sumoj, k * sumok, i, j, k, Temp.Get_Tipo(), i * j * k, Temp.Get_orig());
								lista = m_Configuracaos;
								if (m_full_supported == true)
								{
									if (ComprobarFullSupportUno(Configuracao, lista))
									{
										/*lista.push_back(Configuracao);*/
										InsertarConfiguracaoOrden(Configuracao, lista);
										if (Temp.Get_z2() == Configuracao.Get_z2())
										{
											CONFIGURACAO ConfFantasma(this, 0, Configuracao.Get_x2(), Temp.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
											CONFIGURACAO ConfFantasma2(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Configuracao.Get_x2(), Configuracao.Get_y1(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma2, lista, lista2);
										}
										else
										{
											CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
										}
									}
								}
								else
									InsertarConfiguracaoOrden(Configuracao, lista);
									/*lista.push_back(Configuracao);*/
								//DibujarOpenGL(lista);
								if (Configuracao.Get_Volumen() == 0)
									printf("mierda3");
							}

							if (Temp.Get_orig()==3)
							{
								CONFIGURACAO Configuracao(this,Temp.Get_Id(),Temp.Get_x1(),Temp.Get_y1(), Temp.Get_z2() - k * sumok,i*sumoi,j*sumoj,k*sumok,i,j,k,Temp.Get_Tipo(),i*j*k,Temp.Get_orig());
								
								lista = m_Configuracaos;
								InsertarConfiguracaoOrden(Configuracao, lista);
								/*lista.push_back(Configuracao);*/
								if (Configuracao.Get_Volumen()==0)
									printf("mierda3");
							}

							if (Temp.Get_orig()==4)
							{
								CONFIGURACAO Configuracao(this,Temp.Get_Id(),Temp.Get_x1(),Temp.Get_y2()-j*sumoj,Temp.Get_z2()-k*sumok,i*sumoi,j*sumoj,k*sumok,i,j,k,Temp.Get_Tipo(),i*j*k,Temp.Get_orig());
								
								lista = m_Configuracaos;
								InsertarConfiguracaoOrden(Configuracao, lista);
								/*lista.push_back(Configuracao);*/
								if (Configuracao.Get_Volumen()==0)
									printf("mierda4");
							}
							if (Temp.Get_orig()==5)
							{
								CONFIGURACAO Configuracao(this,Temp.Get_Id(),Temp.Get_x2()-i*sumoi,Temp.Get_y1(),Temp.Get_z1(),i*sumoi,j*sumoj,k*sumok,i,j,k,Temp.Get_Tipo(),i*j*k,Temp.Get_orig());
								
								lista = m_Configuracaos;
								if (m_full_supported == true)
								{
									if (ComprobarFullSupportUno(Configuracao, lista))
									{
										/*lista.push_back(Configuracao);*/
										InsertarConfiguracaoOrden(Configuracao, lista);
										if (Temp.Get_z2() == Configuracao.Get_z2())
										{
											CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Configuracao.Get_x1(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
											CONFIGURACAO ConfFantasma2(this, 0, Configuracao.Get_x1(), Configuracao.Get_y2(), Temp.Get_z2(), Configuracao.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma2, lista, lista2);
										}
										else
										{
											CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
										}
									}
								}
								else
									InsertarConfiguracaoOrden(Configuracao, lista);
									/*lista.push_back(Configuracao);*/
								if (Configuracao.Get_Volumen()==0)
									printf("mierda5");
							}

							if (Temp.Get_orig() == 6)
							{
								CONFIGURACAO Configuracao(this, Temp.Get_Id(), Temp.Get_x2() - i * sumoi, Temp.Get_y2() - j * sumoj, Temp.Get_z1(), i * sumoi, j * sumoj, k * sumok, i, j, k, Temp.Get_Tipo(), i * j * k, Temp.Get_orig());
								
								lista = m_Configuracaos;
								if (m_full_supported == true)
								{
									if (ComprobarFullSupportUno(Configuracao, lista))
									{
										/*lista.push_back(Configuracao);*/
										InsertarConfiguracaoOrden(Configuracao, lista);
										if (Temp.Get_z2() == Configuracao.Get_z2())
										{
											CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Configuracao.Get_x1(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
											CONFIGURACAO ConfFantasma2(this, 0, Configuracao.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Configuracao.Get_x2(), Configuracao.Get_y1(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma2, lista, lista2);
										}
										else
										{
											CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
											ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
										}
									}
								}
								else
									InsertarConfiguracaoOrden(Configuracao, lista);
									/*lista.push_back(Configuracao);*/
								//DibujarOpenGL(lista);
								if (Configuracao.Get_Volumen() == 0)
									printf("mierda7");
							}

							if (Temp.Get_orig()==7)
							{
								CONFIGURACAO Configuracao(this, Temp.Get_Id(), Temp.Get_x2() - i * sumoi, Temp.Get_y1(), Temp.Get_z2() - k * sumok, i* sumoi, j* sumoj, k* sumok, i, j, k, Temp.Get_Tipo(), i* j* k, Temp.Get_orig());
								
								lista = m_Configuracaos;
								InsertarConfiguracaoOrden(Configuracao, lista);
								/*lista.push_back(Configuracao);*/
								if (Configuracao.Get_Volumen()==0)
									printf("mierda6");
							}
							
							if (Temp.Get_orig()==8)
							{
								CONFIGURACAO Configuracao(this,Temp.Get_Id(),Temp.Get_x2()-i*sumoi,Temp.Get_y2()-j*sumoj,Temp.Get_z2()-k*sumok,i*sumoi,j*sumoj,k*sumok,i,j,k,Temp.Get_Tipo(),i*j*k,Temp.Get_orig());
								ComprobarLimites(Configuracao);
								lista = m_Configuracaos;
								InsertarConfiguracaoOrden(Configuracao, lista);
								/*lista.push_back(Configuracao);*/
							}
						}
						else
						{
						    lista = m_Configuracaos;
//							DibujarOpenGL(lista);
							if (m_full_supported==true)
							{
								CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
								ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
							}
						}
						/*DibujarOpenGL(lista);*/
						//una vez que lo he quitado muevo hacia las esquinas de los lados
						//que toquen dependiendo del lugar 
						//Tengo que mirar si ha cambiado algo ya que si no ha cambiado 
						//nada entonces no merece la pena que construya la solucion
						/*if (m_full_supported == false)
						{*/
							bool algo_se_mueve = CompactarConfiguracaosEsquinas(lista, lugar);
							////SetDibujar(false);
							if (algo_se_mueve == false)
							{
								continue;
							}
							/*DibujarOpenGL(lista);*/
						/*}*/
						ComprobarConfiguracaosNoIntersectan(lista);
						if (m_full_supported == true && ComprobarFullSupport(lista) == false)
						{
							printf("shit");
							for (int i = 0;;);
						}
//					PintarSolucion(lista);
				//Una vez que tengo esto es volver a rellenar
				//0 es de forma aleatoria la eleccion de la pieza
				//1 me dice si quiero rellenar las que faltan de la manera normal
				//2 si es por la fobjetivo nueva
				//
	//			if (cont==12 && Temp.Get_x1()==0 && Temp.Get_x2()==8)
	//			if (cont==7)
	//			EscribirSolucionLatex2D(lista);
						bool objetivo_capas_old = m_objetivo_capas;
						kkkkj++;
						/*if (kkkkj == 2 && paraprobar==false)
							SetDibujar(true);*/
						/*DibujarOpenGL(lista);*/
					ConstruirSolucionMovimientos(lista,true);
					/*DibujarOpenGL(lista);*/
					/*if (ComprobarConfiguracaosNoIntersectan(lista))*/
					/*if (ComprobarFullSupport(lista)==false)*/
					if (m_full_supported == true && ComprobarFullSupport(lista) == false)
					{
						printf("shit");
						for (int i = 0;;);
					}


					if (m_total_volumen_ocupado>Mejor.Get_Volumen())
					{

						Mejor.CambiarMejor(lista,m_total_volumen_ocupado);
					}

				//Esto es para mantener la misma configuracao inicial
				}
			}

		}
//		printf("KKK333\n");
			if (m_descendent==true && Mejor.Get_Val()>m_max_total_volumen_ocupado)
				parar=true;
			if (perturbar==true)
				break;
			//meto esta pieza que he quitado
			/*m_Configuracaos.push_back(Temp);*/
			InsertarConfiguracaoOrden(Temp, m_Configuracaos);

		}
		std::list<CONFIGURACAO> ::iterator itkk;
		//No necesito los espacios, los puedo quitar
		//es importante que la ponga para la solucion
		ConstruirSolucion(Mejor.Get_Configuracaos(),true);
		DibujarSolucion(m_Spaces,m_Configuracaos);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora || perturbar==true)
		{
//			EscribirSolucionLatex2D(m_Configuracaos);
//			printf("uma Reducir Bloque %d %d\n",m_total_volumen_ocupado,kkkk);
			lista_configuracaos=m_Configuracaos;
		}

//		PintarSolucion(Mejor.Get_Configuracaos());
//		m_eliminar_espacios=true;
//		m_eliminar_espacios=false;

	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora /*&& perturbar==false*/ && m_un_movimiento!=true && m_total_volumen_ocupado!=m_total_volumen);
	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

	if (m_max_total_volumen_ocupado_mejora>m_max_total_volumen_ocupado)
		m_max_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	//vuelvo a ponerla 
//	m_Configuracaos=lista_configuracaos;
	m_eliminar_espacios=false;
	//vuelvo a ponerla 
	//esta variable es para que lo deje todo bien
	//DibujarOpenGL(lista_configuracaos);
	ConstruirSolucion(lista_configuracaos,true);
	if (perturbar!=true) 
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	VerificarSolucion(m_Configuracaos);
	if (m_imprimir_mejoras==true)
	{
		printf("umafuera \n");
		m_fintime=clock();
		m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

		FILE *fin3;
		fin3=fopen(m_file_to_write,"a+");
		double pt=((double)m_max_total_volumen_ocupado/(double)(m_X*m_Y*m_Z))*100;
		fprintf(fin3,"%s\tReducir Bloque\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
		fclose(fin3);
	}
}

//Esta funcion mas bien seria u n shakin //Esta mejora quito un bloque mueve todos los que tienen el mismo tipo
//en la configuracion y continuo
void CONTAINER::QuitarBloque(double porcentaje)
{
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;

	int kki=0;

	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	int volumen_quito=0;
	do
	{
		kki=0;
		m_eliminar_espacios=true;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
		MOVIMIENTO Mejor(this),Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		Mejor.Set_Vol(0);
		std::list<CONFIGURACAO> ::iterator it;
		int hasta=m_Configuracaos.size();
		if (hasta == 0)
			break;
		int cont=0,alea=0;
		alea=get_random(1,hasta);
		bool parar=false;
		bool blo = false;
		for (it=m_Configuracaos.begin();it!=m_Configuracaos.end() && cont<=hasta && parar!=true && volumen_quito<(porcentaje*m_total_volumen_ocupado);)
		{
			cont++;
			if ( alea!=cont) 
				continue;
			if (alea>cont)
				break;
			//borro este bloque, pero primero me quedo en la direccion que 
			//voy a compactar los bloques
			short int lugar=(*it).Get_orig();
			CONFIGURACAO Temp=(*it);
			it=m_Configuracaos.erase(it);
			std::list<CONFIGURACAO> lista = m_Configuracaos;
			volumen_quito += Temp.Get_Volumen();
		/*	DibujarOpenGL(lista);*/
			if (m_full_supported == true)
			{
				CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
				ActualizarListaDeBloquesReducirVol(ConfFantasma, lista, volumen_quito);
			}
			/*DibujarOpenGL(lista);*/
//			PintarSolucion(lista);
			//una vez que lo he quitado muevo hacia las esquinas de los lados
			//que toquen dependiendo del lugar 
			/*if (m_por_bloques==false && m_full_supported==false)*/
		        CompactarConfiguracaosEsquinas(lista,lugar);
			/*	DibujarOpenGL(lista);*/

			ComprobarConfiguracaosNoIntersectan(lista);
			if (m_full_supported == true || m_por_bloques==true)
				m_Configuracaos = lista;
			if (m_Configuracaos.size() == 0)
				break;
		}

	}while(volumen_quito<(porcentaje*m_total_volumen_ocupado));
//			PintarSolucion(lista);
		//Una vez que tengo esto es volver a rellenar
		//0 es de forma aleatoria la eleccion de la pieza
		//1 me dice si quiero rellenar las que faltan de la manera normal
		//2 si es por la fobjetivo nueva
		//```````^
	//Esto es para mantener la misma configuracao inicial
		//No necesito los espacios, los puedo quitar
		//es importante que la ponga para la solucion
		m_eliminar_espacios=false;
		std::list<CONFIGURACAO> lista=m_Configuracaos;
		/*DibujarOpenGL(lista);*/
		ConstruirSolucion(lista,true);
		DibujarSolucion(m_Spaces,m_Configuracaos);
//		printf("uma Bloque %d %d\n",m_total_volumen_ocupado,kkkk);

//		PintarSolucion(Mejor.Get_Configuracaos());
//		m_eliminar_espacios=true;
//		m_eliminar_espacios=false;

	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

	if (m_max_total_volumen_ocupado_mejora>m_max_total_volumen_ocupado)
		m_max_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	//vuelvo a ponerla 
//	m_Configuracaos=lista_configuracaos;
}
//Tenemos que aumentar o inserta los bloques en la solucion
void CONTAINER::MejoraLocalCapa(bool perturbar)
{
	std::list<CONFIGURACAO> lista_configuracaos=m_Configuracaos;
	m_max_total_volumen_ocupado_mejora=0;
	int kki;
	int kkkk = 0;
	m_eliminar_espacios=true;
	//esto es para buscar cual es el movimiento mejor de aumenta
	//Recorremos los maximales para encontrar cual es el más apropiado
	do
	{
//		EscribirSolucionLatex2D(m_Configuracaos);
		kki=0;
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
			m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
//		int perdida=m_X*m_Y*m_Z-m_max_total_volumen_ocupado;
//		int perdida_media=perdida/m_Spaces.size();

		MOVIMIENTO Move(this);
		//Solamente queremos movernos para mejorar el que tenemos
		std::list<SPACE> ::reverse_iterator it;
		bool parar=false;
		int alea=0,cont=0;
		if (perturbar==true)
			alea=get_random(1,m_Spaces.size()-1);


		for (it=m_Spaces.rbegin();it!=m_Spaces.rend() && kki<m_max_movimientos && parar!=true;it++)
		{
			cont++;
			if (perturbar==true && alea!=cont) 
				continue;

			//En mov tengo la mejor configuracao que puedo ya cumpliendo los
			//criterios de ser tabu o no pero para este espacio
			/*if (m_por_bloques == false)
			{*/
				for (int register i = 0; i < m_Q && parar != true && !(perturbar == true && kki > 0); i++)
				{

					int numposibles = m_Pieces[i].Get_q() - m_Pieces[i].Get_Num();
					//numposibles es el n que puedo meter 
					if (numposibles > 0)
					{
						kki++;
						//me devuelve la mejor capa de una pieza
						//aqui tengo que meter dentro el criterio tabu
						Move.MejorCapaDeUnaPiezaEspacio((*it), m_Pieces[i]);
						//esta funcion me compara los movimientos
						//si es mejor cambio el que tengo
					}
					if (m_descendent == true && Move.Get_Val() > 0)
						parar = true;

				}
		
		}
		//En algunas ocasiones puede meter algo mas al hacer un movimiento
		//menor que 0 pero al ampliarla puede ser que sea mas grande
//		PintarSolucion(Mejor.Get_Configuracaos());
		m_eliminar_espacios=false;
		ConstruirSolucion(Move.Get_Configuracaos(),true);
		/*DibujarOpenGL(m_Configuracaos);*/
		if (ComprobarConfiguracaosNoIntersectan(m_Configuracaos))
			printf("%d", kkkk);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora || perturbar==true)
		{
//			EscribirSolucionLatex2D(m_Configuracaos);
			DibujarSolucion(m_Spaces,m_Configuracaos);
			lista_configuracaos=m_Configuracaos;
//			printf("uma Capa %d %d\n",m_total_volumen_ocupado,kkkk);
		}
//		DibujarOpenGL(lista_configuracaos);
	
//		m_eliminar_espacios=false;
	}while(m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora && m_un_movimiento!=true && perturbar!=true && m_total_volumen_ocupado!=m_total_volumen);
	if (m_total_volumen_ocupado>m_max_total_volumen_ocupado_mejora)
		m_max_total_volumen_ocupado_mejora=m_total_volumen_ocupado;

	if (m_max_total_volumen_ocupado_mejora>m_max_total_volumen_ocupado)
		m_max_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;
	//vuelvo a ponerla 
//	m_Configuracaos=lista_configuracaos;
	m_eliminar_espacios=false;
	ConstruirSolucion(lista_configuracaos,true);
	if (perturbar!=true) 
		m_total_volumen_ocupado=m_max_total_volumen_ocupado_mejora;

	if (m_imprimir_mejoras==true)
	{
		printf("umafuera %d Fuer %d\n",kkkk,kki);
		m_fintime=clock();
		m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

		FILE *fin3;
		fin3=fopen(m_file_to_write,"a+");
		double pt=((double)m_max_total_volumen_ocupado/(double)(m_X*m_Y*m_Z))*100;
		fprintf(fin3,"%s\tCapa\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
		fclose(fin3);
	}
}
void MOVIMIENTO::MejorCapaDeUnaBloqueEspacio(SPACE &Espacio, BLOQUE &Pieza)
{
	if (Pieza.Get_Rz() == true)
	{
		CompararConCapasEspacio(1, Espacio, Pieza.Get_x(), Pieza.Get_y(), Pieza.Get_z(), Pieza.Get_Id(), 1);
		CompararConCapasEspacio(2, Espacio, Pieza.Get_y(), Pieza.Get_x(), Pieza.Get_z(), Pieza.Get_Id(), 1);
	}
	/*if (Pieza.Get_Ry() == true)
	{
		CompararConCapas(3, Espacio, Pieza.Get_x(), Pieza.Get_z(), Pieza.Get_y(), Pieza.Get_Id(), Pieza.Get_Num());
		CompararConCapas(4, Espacio, Pieza.Get_z(), Pieza.Get_x(), Pieza.Get_y(), Pieza.Get_Id(), Pieza.Get_Num());
	}
	if (Pieza.Get_Rx() == true)
	{
		CompararConCapas(5, Espacio, Pieza.Get_z(), Pieza.Get_y(), Pieza.Get_x(), Pieza.Get_Id(), Pieza.Get_Num());
		CompararConCapas(6, Espacio, Pieza.Get_y(), Pieza.Get_z(), Pieza.Get_x(), Pieza.Get_Id(), Pieza.Get_Num());
	}*/

}
void MOVIMIENTO::MejorCapaDeUnaPiezaEspacio(SPACE &Espacio,PIECE &Pieza)
{
	if (Pieza.Get_Rz()==true)
	{
		CompararConCapasEspacio(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConCapasEspacio(2,Espacio,Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
	if (Pieza.Get_Ry()==true)
	{
		CompararConCapasEspacio(3,Espacio,Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConCapasEspacio(4,Espacio,Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
	if (Pieza.Get_Rx()==true)
	{
		CompararConCapasEspacio(5,Espacio,Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConCapasEspacio(6,Espacio,Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
}
void MOVIMIENTO::MejorUnaPiezaEspacio(SPACE &Espacio,PIECE &Pieza)
{
	if (Pieza.Get_Rz()==true)
	{
		CompararConCapasEspacio(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),1);
		CompararConCapasEspacio(2,Espacio,Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_Id(),1);
	}
	if (Pieza.Get_Ry()==true)
	{
		CompararConCapasEspacio(3,Espacio,Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_Id(),1);
		CompararConCapasEspacio(4,Espacio,Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_Id(),1);
	}
	if (Pieza.Get_Rx()==true)
	{
		CompararConCapasEspacio(5,Espacio,Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_Id(),1);
		CompararConCapasEspacio(6,Espacio,Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_Id(),1);
	}
}
void MOVIMIENTO::MejorUnaPiezaEspacioMC(SPACE &Espacio,PIECE &Pieza)
{
	CompararConCapasEspacio(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),1);
}
//esta funcion mide lo que se solapa con el espacio
//por tanto, tenemos que mirarlo 
void CONTAINER::ElegirMejorPiezaAumentar(SPACE &Espacio,MOVIMIENTO &M)
{
	//tenemos dos opciones una es mirar la interseccion con todo lo que hays
	//otra es simplemente mirarlo con el que esta posicionado
	for(int register i=0;i<m_Q;i++)
	{
		int numposibles=m_Pieces[i].Get_q()-m_Pieces[i].Get_Num();
		//numposibles es el n que puedo meter 
		if (numposibles >0)
		{
			//me devuelve la mejor capa de una pieza
			//aqui tengo que meter dentro el criterio tabu
			M.MejorUnaPiezaEspacio(Espacio,m_Pieces[i]);

		}
	}


}
//esta funcion mide lo que se solapa con el espacio
//por tanto, tenemos que mirarlo 
void CONTAINER::ElegirMejorBloqueAumentar(SPACE &Espacio,MOVIMIENTO &M)
{
	//tenemos dos opciones una es mirar la interseccion con todo lo que hays
	//otra es simplemente mirarlo con el que esta posicionado
	for(int register i=0;i<m_Q;i++)
	{
		int numposibles=m_Pieces[i].Get_q()-m_Pieces[i].Get_Num();
		//numposibles es el n que puedo meter 
		if (numposibles >0)
		{
			//me devuelve la mejor capa de una pieza
			//aqui tengo que meter dentro el criterio tabu
			M.MejorCapaDeUnaPiezaEspacio(Espacio,m_Pieces[i]);

		}
	}


}
//Esta funcion esta hecha para el tabu
//Compara con lo que tiene y me dice si es mejor
void MOVIMIENTO::CompararConCapasEspacio(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas)
{
	
	//Ahora la pieza no cabe seguro
	int Caso=1,numActual=1;
	//	std::multiset< short int > setActual;
	//Tres posibles casos
	int Eje_x,Eje_y,Eje_z;
	//solamente pongo tres casos aqui
	//Hacemos el maximo es lo que hay puesto del lado pero con el maximo 
	//para que haya mas que uno
	//		if (m_Container->Get_objetivo_vol()==false)	setActual.clear();
	/*if (x == 0 || y == 0 || z == 0 || Espacio.Get_dx() == 0 || Espacio.Get_dy() == 0 || Espacio.Get_dz() == 0)
	{
		FILE* fincs;
		fincs = fopen(m_Container->Get_File(), "a+");
		fprintf(fincs, "pif\n");
		fclose(fincs);
	}*/
	Eje_x=max(min(Espacio.Get_dx()/x,piezas_maximas),1);
	Eje_y=max(min(Espacio.Get_dy()/y,piezas_maximas),1);
	Eje_z=max(min(Espacio.Get_dz()/z,piezas_maximas),1);
	for (Caso=1;Caso<=3;Caso++)
	{

		
		//Para que si solo hay uno no haga ninguno mais
		if (Caso>1 && Eje_x==1 && Eje_y==1 && Eje_z==1 )
			break;
		switch (Caso)
		{
			case 1:
				{
					Eje_z=1;
					Eje_y=min(Eje_y, (piezas_maximas/Eje_x));
					numActual=Eje_x*Eje_y;
					break;
				}
			case 2:
				{
					if (Eje_y==1) continue;
					Eje_x=min(Eje_x, (piezas_maximas/Eje_y));
					if (Eje_x==1) continue;
					Eje_z=1;
					//en  y
					numActual=Eje_y*Eje_x;
					break;
				}

			// en z
			case 3:
				{
					if (Eje_z==1) continue;
					Eje_y=1;
					Eje_x=min(Eje_x, (piezas_maximas/Eje_z));
					if (Eje_x==1) continue;

					numActual=Eje_z*Eje_x;
					break;

				}
		}
		kkkk++;
		int Pongo=Eje_x*x*Eje_y*y*Eje_z*z;

		//Tengo que poner una funcion que me haga la evaluacion de lo que quito inicial
		//es decir hago lo que quito
		//Ahora tengo que decidir como es mejor una configuracion
		//que tora
		//primero tengo que evaluar el movimiento
		//esta funcion me dice con los que corta y lo que quito y tambien me da la nueva lista 
		//de bloques que coloco
		//Para hacer un constructivo aleatorizado
		//La diferencia es que aqui tengo que tener una lista que es la que me controla cuantos 
		//pueden caber 
		CONFIGURACAO Temp(m_Container);
		Temp.CambiarConfiguracao(numActual, Eje_x,Eje_y,Eje_z,x, y, z, Id,tipo, Espacio);
		if ((Temp.Get_x2()>m_Container->Get_X()|| Temp.Get_x1()<0 )) continue;
		if ((Temp.Get_y2()>m_Container->Get_Y() || Temp.Get_y1()<0 )) continue;
		if ((Temp.Get_z2()>m_Container->Get_Z() || Temp.Get_z1()<0 )) continue;
		std::list<CONFIGURACAO> lista=m_Container->Get_ListaConfiguracaos();
		//Me devuelve cuantos pierdo al poner esta 
		int Quito=ActualizarListaDeBloquesQuitaCantidad(Temp,lista);

		int val=Pongo-Quito;
//		EvaluacionMovimiento(Temp,lista,valor);
//***************
/*		printf("Comparo\n");
		for (it=m_val.begin();it!=m_val.end();it++)
			printf("%f\t",(*it));
		printf("\n");
		for (it=valor.begin();it!=valor.end();it++)
			printf("%f\t",(*it));
		printf("\n");*/
//***************
		if (val > m_val)
		{
			if (m_Container->Get_Full_Supported() == true)
			{
				CONFIGURACAO ConfFantasma(m_Container, 0, Temp.Get_x1(), Temp.Get_y1(), Temp.Get_z2(), Temp.Get_x2(), Temp.Get_y2(), m_Container->Get_Z(), 1, 1, 0);
				ActualizarListaDeBloquesQuita(ConfFantasma, lista, false);
				/*m_Container->DibujarOpenGL(lista);*/
				ActualizarListaDeBloquesQuita(Temp, lista, true);
				m_Container->InsertarConfiguracaoOrden(Temp, lista);
				/*m_Container->DibujarOpenGL(lista);*/
				if (ComprobarFullSupport(Temp, lista) == true)
				{
					m_val = val;
					m_Configuracaos_new = lista;
					m_Configuracao.CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}
			if (m_Container->Get_Full_Supported() == false)
			{
				ActualizarListaDeBloquesQuita(Temp, lista, true);
				m_val = val;
				m_Configuracaos_new = lista;
				m_Configuracao.CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
			}
		}

	}
}
//Esta funcion le doy la configuracao 
//y me da el valor de lo que vale la nueva configuracao
//problema que se cicle el algoritmo, otro problema es que si utilizo lo mismo que 
//que hacia en el tabu y coloco las piezas tardare mas que si unicamente veo con cuantas intersecta
//y quita mas lo que gano
//oPero para tener en la lista tabu la lista de perdidas tendria que tenerlo todo
void MOVIMIENTO::EvaluacionMovimiento(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista,int val)
{
	//esta funcion primero tiene que cortar todos los bloques ya existentes 
	
	lista=m_Container->Get_ListaConfiguracaos();
	m_Container->VerificarSolucion(m_Configuracaos_new);
	//
	std::list<SPACE> lista_espacios_nuevos;
	//Primero vamos a ver si es la mejor
	//Me crea los espacios que se cortan con los que tenia
	ActualizarListaDeBloques(Configuracao,lista,lista_espacios_nuevos);
	//Ahora tengo que juntar estos espacios que no son maximales
	
	ActualizarListaEspaciosBloquesMov(lista_espacios_nuevos,Configuracao);
	//Esto es para construir la nueva solucion
//*************
//	m_Container->ConstruirSolucionMovimientos(lista);
	//Actualizo los nuevo que he metido tambien
	std::list<SPACE> lista_espacios=m_Container->Get_ListaSpaces();
	//Ahora la actualizar puede darse que alguno de los espacios
	//este incluido
	ActualizarListaEspaciosOriginalesMov(lista_espacios,Configuracao);
	
	m_Container->ComprobarConfiguracaosNoIntersectanSpaces(lista,lista_espacios_nuevos);
//	m_Container->PintarSpaces(lista_espacios);
//	m_Container->PintarSpaces(lista_espacios_nuevos);

	m_Container->JuntarSpaces(lista_espacios,lista_espacios_nuevos);

	lista_espacios.insert(lista_espacios.begin(),lista_espacios_nuevos.begin(),lista_espacios_nuevos.end());
	m_Container->ComprobarConfiguracaosNoIntersectanSpaces(lista,lista_espacios);
//	std::list<CONFIGURACAO> lista_tempkk=lista;
//	m_Container->PintarSpaces(lista_espacios);
//	m_Container->ConstruirSolucion(lista_tempkk,true);
//	m_Container->PintarSpaces(m_Container->Get_ListaSpaces());
	m_Container->RellenarSpaces(lista_espacios,lista);

	//despues de tener los bloque evaluo el movimiento 
//	lista=m_Container->Get_ListaConfiguracaos();
	EvaluarMovimiento(lista,val);
	m_Container->VerificarSolucion(lista);
	//
}
//Esta funcion le doy la configuracao 
//y me da el valor de lo que vale la nueva configuracao
//problema que se cicle el algoritmo, otro problema es que si utilizo lo mismo que 
//que hacia en el tabu y coloco las piezas tardare mas que si unicamente veo con cuantas intersecta
//y quita mas lo que gano
//oPero para tener en la lista tabu la lista de perdidas tendria que tenerlo todo
void MOVIMIENTO::EvaluacionMovimientoConstruirOld(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista,int val)
{
	//esta funcion primero tiene que cortar todos los bloques ya existentes 
	
	lista=m_Container->Get_ListaConfiguracaos();
	m_Container->VerificarSolucion(m_Configuracaos_new);
	//
	std::list<SPACE> lista_espacios_nuevos;
	//Me crea los espacios que se cortan con los que tenia
	ActualizarListaDeBloques(Configuracao,lista,lista_espacios_nuevos);
	//Ahora tengo que juntar estos espacios que no son maximales
	
//	ActualizarListaEspaciosBloquesMov(lista_espacios_nuevos,Configuracao);
	//Esto es para construir la nueva solucion
//*************
//	m_Container->ConstruirSolucionMovimientos(lista);
	//Actualizo los nuevo que he metido tambien
//	std::list<SPACE> lista_espacios=m_Container->Get_ListaSpaces();
	//Ahora la actualizar puede darse que alguno de los espacios
	//este incluido
//	ActualizarListaEspaciosOriginalesMov(lista_espacios,Configuracao);
	
//	m_Container->ComprobarConfiguracaosNoIntersectanSpaces(lista,lista_espacios_nuevos);
//	m_Container->JuntarSpaces(lista_espacios,lista_espacios_nuevos);

//	lista_espacios.insert(lista_espacios.begin(),lista_espacios_nuevos.begin(),lista_espacios_nuevos.end());
//	m_Container->ComprobarConfiguracaosNoIntersectanSpaces(lista,lista_espacios);
	m_Container->ConstruirSolucionMovimientos(lista,1);
//	m_Container->RellenarSpaces(lista_espacios,lista);
	//despues de tener los bloque evaluo el movimiento 
//	lista=m_Container->Get_ListaConfiguracaos();
	EvaluarMovimiento(lista,val);
	m_Container->VerificarSolucion(lista);
	//
}
int MOVIMIENTO::EvaluacionMovimientoConstruir(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista)
{
	//esta funcion primero tiene que cortar todos los bloques ya existentes 
	
	m_Container->VerificarSolucion(m_Configuracaos_new);
	//
//	std::list<SPACE> lista_espacios_nuevos;
	//Me crea los espacios que se cortan con los que tenia
	int Quito=ActualizarListaDeBloquesQuitaCantidad(Configuracao,lista);
	return Quito;
	//Ahora tengo que juntar estos espacios que no son maximales
//	ActualizarListaEspaciosBloquesMov(lista_espacios_nuevos,Configuracao);
	//Esto es para construir la nueva solucion
//*************
//	m_Container->ConstruirSolucionMovimientos(lista);
	//Actualizo los nuevo que he metido tambien
//	std::list<SPACE> lista_espacios=m_Container->Get_ListaSpaces();
	//Ahora la actualizar puede darse que alguno de los espacios
	//este incluido
//	ActualizarListaEspaciosOriginalesMov(lista_espacios,Configuracao);
	
//	m_Container->ComprobarConfiguracaosNoIntersectanSpaces(lista,lista_espacios_nuevos);
//	m_Container->JuntarSpaces(lista_espacios,lista_espacios_nuevos);

//	lista_espacios.insert(lista_espacios.begin(),lista_espacios_nuevos.begin(),lista_espacios_nuevos.end());
//	m_Container->ComprobarConfiguracaosNoIntersectanSpaces(lista,lista_espacios);
//	m_Container->ConstruirSolucionMovimientos(lista);
//	m_Container->RellenarSpaces(lista_espacios,lista);
	//despues de tener los bloque evaluo el movimiento 
//	lista=m_Container->Get_ListaConfiguracaos();
//	EvaluarMovimiento(lista,val);
//	m_Container->VerificarSolucion(lista);
	//
}
void CONTAINER::RellenarSpaces(std::list<SPACE> &lista_espacios,std::list<CONFIGURACAO> &lista_configuracaos)
{
	//poner los numeritos
	m_Pieces_Tabu.clear();
	for (int j=0;j<m_Q;j++)
		m_Pieces_Tabu.push_back(0);
	std::list<CONFIGURACAO> ::iterator it1;
	//Aqui pongo todas las componentes del vector a lo que estaban
	for (it1=lista_configuracaos.begin();it1!=lista_configuracaos.end();it1++)
	{
		m_Pieces_Tabu[(*it1).Get_Id()]+=(*it1).Get_Num();
	}
	if (m_Pieces_Tabu[(*it1).Get_Id()] > m_Pieces[(*it1).Get_Id()].Get_q())
		printf("fallo3");
//	m_total_volumen_ocupado=0;
	MinimaDimensionMov();
	//Inicialmente meto un espacio que es todo el contenedor

	while (lista_espacios.size()>0)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		std::list<SPACE> ::iterator it;
//		bool fin=true;
		SPACE &SpaceElegido=ElegirSpaceMovimiento(lista_espacios, lista_configuracaos);
		if (SpaceElegido.Get_Flag()==true)
		{
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Por si podemos poner mas piezas que esas

		//Elegir configuración para ese espacio
		//Poner configuracao y quitarla de la lista
		ElegirConfiguracaoMov(SpaceElegido,Configuracao,lista_configuracaos);

		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}

		ActualizarListasMov(SpaceElegido,Configuracao,lista_espacios);

	}


	VerificarSolucion(m_Configuracaos);


}
//Tengo ya la nueva lista de bloque y evaluo lo que hay en cada trozo
void MOVIMIENTO::EvaluarMovimiento(std::list<CONFIGURACAO> &lista,int val)
{
	//Contar cuanto volumen hay

	double Cuad1=0,Cuad2=0,Cuad3=0,Cuad4=0;
	std::list<CONFIGURACAO> ::iterator it;
	for (it=lista.begin();it!=lista.end();it++)
	{
		//tengo que contar lo que hay en cada uno de los cuadrantes y meterlo por orden 
		//en la clase lista tabu
		//primer cuadrante
		if ((2*(*it).Get_x1()<m_Container->Get_X()) && (2*(*it).Get_z1()<m_Container->Get_Z()))
			Cuad1+=(min((double)m_Container->Get_X()/2, (double)(*it).Get_x2())-(*it).Get_x1())*(min((double)m_Container->Get_Z()/2, (double)(*it).Get_z2())-(*it).Get_z1())*((*it).Get_y2()-(*it).Get_y1());
		//segundo cuadrante
		if ((2*(*it).Get_x1()<m_Container->Get_X()) && (2*(*it).Get_z2()>m_Container->Get_Z()))
			Cuad2+=(min((double)m_Container->Get_X()/2, (double)(*it).Get_x2())-(*it).Get_x1())*((*it).Get_z2()-max((double)m_Container->Get_Z()/2, (double)(*it).Get_z1()))*((*it).Get_y2()-(*it).Get_y1());
		//tercer cuadrante
		if ((2*(*it).Get_x2()>m_Container->Get_X()) && (2*(*it).Get_z1()<m_Container->Get_Z()))
			Cuad3+=((*it).Get_x2()-max((double)m_Container->Get_X()/2, (double)(*it).Get_x1()))*(min((double)m_Container->Get_Z()/2, (double)(*it).Get_z2())-(*it).Get_z1())*((*it).Get_y2()-(*it).Get_y1());
		//cuarto cuadrante
		if ((2*(*it).Get_x2()>m_Container->Get_X()) && (2*(*it).Get_z2()>m_Container->Get_Z()))
			Cuad4+=((*it).Get_x2()-max((double)m_Container->Get_X()/2, (double)(*it).Get_x1()))*((*it).Get_z2()-max((double)m_Container->Get_Z()/2, (double)(*it).Get_z1()))*((*it).Get_y2()-(*it).Get_y1());
	}
	val=(Cuad1+Cuad2+Cuad3+Cuad4);
}

void MOVIMIENTO::ActualizarListaDeBloques(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista,std::list<SPACE> &lista_espacios)
{
	std::list< CONFIGURACAO > lista_temp;
	std::list<CONFIGURACAO> ::iterator itC,itfin=lista.end();
	for (itC=lista.begin();itC!=itfin;)
	{
//		CONFIGURACAO kk=(*itC);
		SPACE Espacio;
		if (!(Configuracao.Get_x2() <= (*itC).Get_x1() ||  Configuracao.Get_x1()  >= (*itC).Get_x2())
			&& !(Configuracao.Get_y2() < (*itC).Get_y1() ||  Configuracao.Get_y1()  >= (*itC).Get_y2())
			&& !(Configuracao.Get_z2()  <= (*itC).Get_z1() ||  Configuracao.Get_z1()  >= (*itC).Get_z2()))
		{

			ActualizarBloquesElegido((*itC),Configuracao,lista_temp,Espacio);
			//Este espacio se corta con la nueva configuracao, por eso quito meto los que no 
			//se cortan
			lista_espacios.push_back(Espacio);
			//Tengo que hacer el -- porque me apunta al siguiente
			itC=lista.erase(itC);
		}
		else
			++itC;

	}
	lista_temp.insert(lista_temp.begin(),Configuracao);
	//Aqui tengo que juntar la lista con el nuevo espacio
	lista.insert(lista.end(),lista_temp.begin(),lista_temp.end());
//	m_Container->PintarSolucion(lista);
	m_Container->VerificarSolucion(lista);
	
}
void CONTAINER::ActualizarListaDeBloques(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista, bool guardar)
{
	std::list< CONFIGURACAO > lista_temp, listabloq;
	std::list<CONFIGURACAO> ::iterator itC,itfin=lista.end();

	for (itC=lista.begin();itC!=lista.end();)
	{
//		CONFIGURACAO kk=(*itC);
		SPACE Espacio;
		if (!(Configuracao.Get_x2() <= (*itC).Get_x1() ||  Configuracao.Get_x1()  >= (*itC).Get_x2())
			&& !(Configuracao.Get_y2() <= (*itC).Get_y1() ||  Configuracao.Get_y1()  >= (*itC).Get_y2())
			&& !(Configuracao.Get_z2()  <= (*itC).Get_z1() ||  Configuracao.Get_z1()  >= (*itC).Get_z2()))
		{
			ActualizarBloquesElegido(*itC,Configuracao,lista_temp,lista);
			//Este espacio se corta con la nueva configuracao, por eso quito meto los que no 
			//se cortan
			itC = lista.erase(itC);
		}
		else
				++itC;
		//printf("%d\n", cont);
	}
	if (guardar)
	{
		std::list<CONFIGURACAO>::iterator it, it2fin = lista_temp.end();
		for (it = lista_temp.begin(); it != it2fin; it++)
			InsertarConfiguracaoOrden(*it, lista);
	}
	//Aqui tengo que juntar la lista con el nuevo espacio
//	m_Container->PintarSolucion(lista);
	
}
void CONTAINER::ActualizarListaDeBloquesAbajo(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista,CONFIGURACAO &Exc)
{
	std::list< CONFIGURACAO > lista_temp;
	std::list<CONFIGURACAO> ::iterator itC, itfin = lista.end(), it2, it3;
	bool f = false;

	for (itC = lista.begin(); itC != itfin;)
	{
		bool entra = false;
		if ((*itC).Get_x1() == Exc.Get_x1() && (*itC).Get_x2() == Exc.Get_x2() && (*itC).Get_y1() == Exc.Get_y1() && (*itC).Get_y2() == Exc.Get_y2() && (*itC).Get_z1() == Exc.Get_z1() && (*itC).Get_z2() == Exc.Get_z2())
		{
			++itC;
			continue;
		}
	    SPACE Espacio;
		if (!(Configuracao.Get_x2() <= (*itC).Get_x1() || Configuracao.Get_x1() >= (*itC).Get_x2())
			&& !(Configuracao.Get_y2() <= (*itC).Get_y1() || Configuracao.Get_y1() >= (*itC).Get_y2())
			&& !(Configuracao.Get_z2() <= (*itC).Get_z1() || Configuracao.Get_z1() >= (*itC).Get_z2()))
		{
			ActualizarBloquesElegido(*itC, Configuracao, lista_temp, lista);
			//Este espacio se corta con la nueva configuracao, por eso quito meto los que no 
			//se cortan
			//Tengo que hacer el -- porque me apunta al siguiente
			itC = lista.erase(itC);
		}
		else
			++itC;

	}
	if (m_full_supported == false)
	{
		std::list<CONFIGURACAO>::iterator it, it2fin = lista_temp.end();
		for (it = lista_temp.begin(); it != it2fin; it++)
			InsertarConfiguracaoOrden(*it, lista);
	}
	//Aqui tengo que juntar la lista con el nuevo espacio
//	m_Container->PintarSolucion(lista);

}
void CONTAINER::ActualizarListaDeBloquesReducir(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista2)
{
	std::list< CONFIGURACAO > lista_temp;
	std::list<CONFIGURACAO> ::iterator itC, itfin = lista.end(),it2,it3;
	bool f = false;
	for (itC = lista.begin(); itC != itfin;)
	{
		//		CONFIGURACAO kk=(*itC);
		SPACE Espacio;
		if (!(Configuracao.Get_x2() <= (*itC).Get_x1() || Configuracao.Get_x1() >= (*itC).Get_x2())
			&& !(Configuracao.Get_y2() <= (*itC).Get_y1() || Configuracao.Get_y1() >= (*itC).Get_y2())
			&& !(Configuracao.Get_z2() <= (*itC).Get_z1() || Configuracao.Get_z1() >= (*itC).Get_z2()))
		{
			bool entra = false;
			ActualizarBloquesElegidoReducir((*itC), Configuracao, lista_temp, lista,lista2);
			//Este espacio se corta con la nueva configuracao, por eso quito meto los que no 
			//se cortan
			/*lista2.push_back(*itC);*/
			InsertarConfiguracaoOrden(*itC, lista2);
			itC = lista.erase(itC);
		}
		else
			++itC;

	}

	//Aqui tengo que juntar la lista con el nuevo espacio
	//lista.insert(lista.end(), lista_temp.begin(), lista_temp.end());

	//Aqui tengo que juntar la lista con el nuevo espacio
//	m_Container->PintarSolucion(lista);

}
void CONTAINER::ActualizarListaDeBloquesReducirAbajo(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista2, CONFIGURACAO &Exc)
{
	std::list< CONFIGURACAO > lista_temp;
	std::list<CONFIGURACAO> ::iterator itC, itfin = lista.end(),it2, it3;
	bool f = false;
	for (itC = lista.begin(); itC != itfin;)
	{
		bool entra = false;
		if ((*itC).Get_x1() == Exc.Get_x1() && (*itC).Get_x2() == Exc.Get_x2() && (*itC).Get_y1() == Exc.Get_y1() && (*itC).Get_y2() == Exc.Get_y2() && (*itC).Get_z1() == Exc.Get_z1() && (*itC).Get_z2() == Exc.Get_z2())
		{
			++itC;
			continue;
		}
		//		CONFIGURACAO kk=(*itC);
		SPACE Espacio;
		if (!(Configuracao.Get_x2() <= (*itC).Get_x1() || Configuracao.Get_x1() >= (*itC).Get_x2())
			&& !(Configuracao.Get_y2() <= (*itC).Get_y1() || Configuracao.Get_y1() >= (*itC).Get_y2())
			&& !(Configuracao.Get_z2() <= (*itC).Get_z1() || Configuracao.Get_z1() >= (*itC).Get_z2()))
		{

			ActualizarBloquesElegidoReducir((*itC), Configuracao, lista_temp, lista, lista2);
			//Este espacio se corta con la nueva configuracao, por eso quito meto los que no 
			//se cortan
			//Tengo que hacer el -- porque me apunta al siguiente
			/*lista2.push_back(*itC);*/
			InsertarConfiguracaoOrden(*itC, lista2);
			//if ((*itC).Get_Id_bloque() > 0) //Si esto pasa en algún momento, entonces es que m_por_bloques=true
			//{
			//	it2 = itC;
			//	it2++;
			//	for (; it2 != itfin;)
			//	{
			//		if ((*it2).Get_Id_bloque() == (*itC).Get_Id_bloque())
			//		{
			//			entra = true;
			//			CONFIGURACAO Temp = *it2;
			//			RestarConfiguracaosCon(Temp, Temp, lista_temp, lista, f, f, f, f, f, f);
			//			it2 = lista.erase(it2);
			//		}
			//		else
			//			++it2;
			//	}
			//	if (entra == false)
			//	{
			//		it3 = itC;
			//		it3--;
			//		if ((*it3).Get_Id_bloque() == (*itC).Get_Id_bloque())
			//		{
			//			CONFIGURACAO Temp = *it3;
			//			RestarConfiguracaosCon(Temp, Temp, lista_temp, lista, f, f, f, f, f, f);
			//			it3 = lista.erase(it3);
			//		}
			//		else
			//			printf("no deberia entrar aqui");
			//	}

			//}
			itC = lista.erase(itC);
		}
		else
			++itC;

	}

	//Aqui tengo que juntar la lista con el nuevo espacio
//	m_Container->PintarSolucion(lista);

}
void CONTAINER::ActualizarListaDeBloquesReducirVol(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, int vol)
{
	std::list< CONFIGURACAO > lista_temp;
	std::list<CONFIGURACAO> ::iterator itC, itfin = lista.end(),it2,it3;
	bool f = false;
	for (itC = lista.begin(); itC != itfin;)
	{
		bool entra = false;
		//		CONFIGURACAO kk=(*itC);
		SPACE Espacio;
		if (!(Configuracao.Get_x2() <= (*itC).Get_x1() || Configuracao.Get_x1() >= (*itC).Get_x2())
			&& !(Configuracao.Get_y2() <= (*itC).Get_y1() || Configuracao.Get_y1() >= (*itC).Get_y2())
			&& !(Configuracao.Get_z2() <= (*itC).Get_z1() || Configuracao.Get_z1() >= (*itC).Get_z2()))
		{
			ActualizarBloquesElegidoReducirVol((*itC), Configuracao, lista_temp, lista, vol);
			itC = lista.erase(itC);
		}
		else
			++itC;

	}

	//Aqui tengo que juntar la lista con el nuevo espacio
//	m_Container->PintarSolucion(lista);

}
void MOVIMIENTO::ActualizarListaDeBloquesQuita(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista_b, bool rec)
{
	//m_Container->VerificarSolucion(lista_b);
	std::list< CONFIGURACAO > lista_temp;
	std::list<CONFIGURACAO> ::iterator itCC,itCfin=lista_b.end();
	for (itCC=lista_b.begin();itCC!=itCfin;)
	{
		if (!(Configuracao.Get_x2() <= (*itCC).Get_x1() ||  Configuracao.Get_x1()  >= (*itCC).Get_x2())
			&& !(Configuracao.Get_y2() <= (*itCC).Get_y1() ||  Configuracao.Get_y1()  >= (*itCC).Get_y2())
			&& !(Configuracao.Get_z2()  <= (*itCC).Get_z1() ||  Configuracao.Get_z1()  >= (*itCC).Get_z2()))
		{
			ActualizarBloquesElegidoQuita((*itCC),Configuracao,lista_temp,lista_b);
			itCC=lista_b.erase(itCC);
		}
		else
			++itCC;

	}
	if (rec == true)
	{
		lista_temp.insert(lista_temp.begin(), Configuracao);
	}
	//Aqui tengo que juntar la lista con el nuevo espacio
	//if (m_Container->Get_Full_Supported()==false)
	if (m_Container->Get_Full_Supported()==false)
	    lista_b.insert(lista_b.end(),lista_temp.begin(),lista_temp.end());
//	m_Container->PintarSolucion(lista);
//	m_Container->VerificarSolucion(lista_b);
//	return quito;
	
}
void MOVIMIENTO::ActualizarListaDeBloquesQuitaAbajo(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista_b, bool rec,CONFIGURACAO &Exc)
{
	//m_Container->VerificarSolucion(lista_b);
	std::list< CONFIGURACAO > lista_temp;
	std::list<CONFIGURACAO> ::iterator itCC, itCfin = lista_b.end(),it2,it3;
	bool f = false;
	for (itCC = lista_b.begin(); itCC != itCfin;)
	{
		bool entra = false;
		if ((*itCC).Get_x1() == Exc.Get_x1() && (*itCC).Get_x2() == Exc.Get_x2() && (*itCC).Get_y1() == Exc.Get_y1() && (*itCC).Get_y2() == Exc.Get_y2() && (*itCC).Get_z1() == Exc.Get_z1() && (*itCC).Get_z2() == Exc.Get_z2())
		{
			++itCC;
			continue;
		}
		if (!(Configuracao.Get_x2() <= (*itCC).Get_x1() || Configuracao.Get_x1() >= (*itCC).Get_x2())
			&& !(Configuracao.Get_y2() <= (*itCC).Get_y1() || Configuracao.Get_y1() >= (*itCC).Get_y2())
			&& !(Configuracao.Get_z2() <= (*itCC).Get_z1() || Configuracao.Get_z1() >= (*itCC).Get_z2()))
		{

			ActualizarBloquesElegidoQuita((*itCC), Configuracao, lista_temp, lista_b);
			//Este espacio se corta con la nueva configuracao, por eso quito meto los que no 
			//se cortan
			//if ((*itCC).Get_Id_bloque() > 0) //Si esto pasa en algún momento, entonces es que m_por_bloques=true
			//{
			//	it2 = itCC;
			//	it2++;
			//	for (; it2 != itCfin;)
			//	{
			//		if ((*it2).Get_Id_bloque() == (*itCC).Get_Id_bloque())
			//		{
			//			entra = true;
			//			CONFIGURACAO Temp = *it2;
			//			RestarConfiguracaos(Temp, Temp, lista_temp, lista_b, f, f, f, f, f, f);
			//			it2 = lista_b.erase(it2);
			//		}
			//		else
			//			++it2;
			//	}
			//	if (entra == false)
			//	{
			//		it3 = itCC;
			//		it3--;
			//		if ((*it3).Get_Id_bloque() == (*itCC).Get_Id_bloque())
			//		{
			//			CONFIGURACAO Temp = *it3;
			//			RestarConfiguracaos(Temp, Temp, lista_temp, lista_b, f, f, f, f, f, f);
			//			it3 = lista_b.erase(it3);
			//		}
			//		else
			//			printf("no deberia entrar aqui");
			//	}

			//}
//			lista_espacios.push_back(Espacio);
			//Tengo que hacer el -- porque me apunta al siguiente
//				CONFIGURACAO kk=(*itC);
//			exit(3);
			itCC = lista_b.erase(itCC);
		}
		else
			++itCC;

	}
	if (rec == true)
	{
		lista_temp.insert(lista_temp.begin(), Configuracao);
	}
	//Aqui tengo que juntar la lista con el nuevo espacio
	if (m_Container->Get_Full_Supported()==false)
		lista_b.insert(lista_b.end(), lista_temp.begin(), lista_temp.end());
	//	m_Container->PintarSolucion(lista);
	//	m_Container->VerificarSolucion(lista_b);
	//	return quito;

}
int MOVIMIENTO::ActualizarListaDeBloquesQuitaCantidad(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista)
{
	int quito=0;
	std::list<CONFIGURACAO> ::iterator itC,itfin=lista.end();
	for (itC=lista.begin();itC!=itfin;itC++)
	{
//		SPACE Espacio;
		if (!(Configuracao.Get_x2() <= (*itC).Get_x1() ||  Configuracao.Get_x1()  >= (*itC).Get_x2())
			&& !(Configuracao.Get_y2() <= (*itC).Get_y1() ||  Configuracao.Get_y1()  >= (*itC).Get_y2())
			&& !(Configuracao.Get_z2()  <= (*itC).Get_z1() ||  Configuracao.Get_z1()  >= (*itC).Get_z2()))
		{

			quito+=ActualizarBloquesElegidoQuitaCantidad((*itC),Configuracao);
			//Este espacio se corta con la nueva configuracao, por eso quito meto los que no 
			//se cortan
//			lista_espacios.push_back(Espacio);
			//Tengo que hacer el -- porque me apunta al siguiente
//				CONFIGURACAO kk=(*itC);

		}

	}
	return quito;
	
}
//Dados dos bloques deja los bloques para que no se intersecten
//ademas tiene que meter todas las perdidas nuevas que van a aparecetr
void MOVIMIENTO::ActualizarBloquesElegidoQuita( CONFIGURACAO &Vieja,CONFIGURACAO &Nueva,std::list <CONFIGURACAO> &lista_temp, std::list<CONFIGURACAO> &lista_b)
{
	//es distinta a la de los espacios ya que en esta no
	//se pueden cortar las configuraciones
	//E es la configuracao vieja
	//C es la configuraco nueva
	//Podemos tener seis posibles espacios nuevos
	int dimx=Vieja.Get_x2()-Vieja.Get_x1();
	int x=dimx/Vieja.Get_dx();
	int dimy=Vieja.Get_y2()-Vieja.Get_y1();
	int y=dimy/Vieja.Get_dy();
	int dimz=Vieja.Get_z2()-Vieja.Get_z1();
	int z=dimz/Vieja.Get_dz();
	int x1=Vieja.Get_x1(),y1=Vieja.Get_y1(),z1=Vieja.Get_z1();
	int x2=Vieja.Get_x2(),y2=Vieja.Get_y2(),z2=Vieja.Get_z2();
	bool izq = false;
	bool der = false;
	bool arr = false;
	bool abj = false;
	bool den = false;
	bool fue = false;
	int kkk = 0;
	int kk2 = 0;

//	int Antes=Vieja.Get_Volumen();
//	int Ahora=0;
	if (m_Container->Get_Full_Supported()== true)
	{
		//Abajo
		if ((Nueva.Get_z1() - Vieja.Get_z1()) >= z)
		{
			abj = true;
			z1 = Vieja.Get_z1() + ((Nueva.Get_z1() - Vieja.Get_z1()) / z)*z;
			int num = Vieja.Get_dx()*((Nueva.Get_z1() - Vieja.Get_z1()) / z)*Vieja.Get_dy();
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z1(), x2 - x1, dimy, ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z, ((x2 - x1) / x), Vieja.Get_dy(), ((Nueva.Get_z1() - Vieja.Get_z1()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
			/*lista_b.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_b);
			if (m_Container->Get_Full_Supported() == true)
			{
				RestarConfiguracaos(Vieja, Configuracao, lista_temp, lista_b, izq, der, abj, arr, den, fue);
				kkk++;
				kk2++;
			}
			abj = false;
		}
		//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
		if ((Nueva.Get_x1() - Vieja.Get_x1()) >= x && kk2 == 0)
		{
			izq = true;
			//Si se da esto es un espacio en el que no voy a poder colocar nada 
			//Por ahora no lo creo
			//este el numero de piezas del bloque
			x1 = Vieja.Get_x1() + ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x;
			int num = ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), Vieja.Get_x1(), Vieja.Get_y1(), Vieja.Get_z1(), ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x, dimy, dimz, ((Nueva.Get_x1() - Vieja.Get_x1()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);
			lista_b.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_b);
			if (m_Container->Get_Full_Supported() == true)
			{
				RestarConfiguracaos(Vieja, Configuracao, lista_temp, lista_b, izq, der, abj, arr, den, fue);
				kkk++;
			}
			izq = false;
		}


		//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
		if ((Vieja.Get_x2() - Nueva.Get_x2()) >= x && kk2 == 0)
		{
			der = true;
			x2 = Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x;

			int num = ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, Vieja.Get_y1(), Vieja.Get_z1(), ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, dimy, dimz, ((Vieja.Get_x2() - Nueva.Get_x2()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);
			lista_b.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_b);
			if (m_Container->Get_Full_Supported() == true)
			{
				RestarConfiguracaos(Vieja, Configuracao, lista_temp, lista_b, izq, der, abj, arr, den, fue);
				kkk++;
			}
			der = false;
		}

		//Fuera
		if ((Nueva.Get_y1() - Vieja.Get_y1()) >= y && kk2 == 0)
		{
			fue = true;
			y1 = Vieja.Get_y1() + ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y;

			int num = Vieja.Get_dx()*Vieja.Get_dz()*((Nueva.Get_y1() - Vieja.Get_y1()) / y);
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), x1, Vieja.Get_y1(), z1, x2 - x1, ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Nueva.Get_y1() - Vieja.Get_y1()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);
			lista_b.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_b);
			if (m_Container->Get_Full_Supported() == true)
			{
				RestarConfiguracaos(Vieja, Configuracao, lista_temp, lista_b, izq, der, abj, arr, den, fue);
				kkk++;
			}
			fue = false;
		}
		//Dentro
		if ((Vieja.Get_y2() - Nueva.Get_y2()) >= y && kk2 == 0)
		{
			den = true;
			y2 = Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y;
			int num = Vieja.Get_dx()*Vieja.Get_dz()*((Vieja.Get_y2() - Nueva.Get_y2()) / y);
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), x1, Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z1, x2 - x1, ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Vieja.Get_y2() - Nueva.Get_y2()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);
			lista_b.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_b);
			if (m_Container->Get_Full_Supported() == true)
			{
				RestarConfiguracaos(Vieja, Configuracao, lista_temp, lista_b, izq, der, abj, arr, den, fue);
				kkk++;
			}
			den = false;
		}
		//Arriba
		if ((Vieja.Get_z2() - Nueva.Get_z2()) >= z && kkk == 0 && kk2 == 0)
		{
			arr = true;
			z2 = Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z)*z;
			int num = Vieja.Get_dx()*((Vieja.Get_z2() - Nueva.Get_z2()) / z)*Vieja.Get_dy();
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z, x2 - x1, dimy, ((Vieja.Get_z2() - Nueva.Get_z2()) / z)* z, ((x2 - x1) / x), Vieja.Get_dy(), ((Vieja.Get_z2() - Nueva.Get_z2()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);
			lista_b.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_b);
			if (m_Container->Get_Full_Supported() == true)
			{
				RestarConfiguracaos(Vieja, Configuracao, lista_temp, lista_b, izq, der, abj, arr, den, fue);
				kkk++;
			}
			arr = false;
		}

		if (m_Container->Get_Full_Supported() == true && kkk == 0 && kk2 == 0)
		{
			RestarConfiguracaos(Vieja, Vieja, lista_temp, lista_b, izq, der, abj, arr, den, fue);
		}
	}
	else
	{
		if ((Nueva.Get_x1() - Vieja.Get_x1()) > x)
		{
			//Si se da esto es un espacio en el que no voy a poder colocar nada 
			//Por ahora no lo creo
			//este el numero de piezas del bloque
			x1 = Vieja.Get_x1() + ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x;
			int num = ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), Vieja.Get_x1(), Vieja.Get_y1(), Vieja.Get_z1(), ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x, dimy, dimz, ((Nueva.Get_x1() - Vieja.Get_x1()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
		}


		//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
		if ((Vieja.Get_x2() - Nueva.Get_x2()) > x)
		{
			x2 = Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x;

			int num = ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, Vieja.Get_y1(), Vieja.Get_z1(), ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, dimy, dimz, ((Vieja.Get_x2() - Nueva.Get_x2()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);

		}
		//Abajo
		if ((Nueva.Get_z1() - Vieja.Get_z1()) > z)
		{
			z1 = Vieja.Get_z1() + ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z;
			int num = Vieja.Get_dx() * ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * Vieja.Get_dy();
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z1(), x2 - x1, dimy, ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z, ((x2 - x1) / x), Vieja.Get_dy(), ((Nueva.Get_z1() - Vieja.Get_z1()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);

		}

		//Arriba
		if ((Vieja.Get_z2() - Nueva.Get_z2()) > z)
		{
			z2 = Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z;
			int num = Vieja.Get_dx() * ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * Vieja.Get_dy();
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z, x2 - x1, dimy, ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z, ((x2 - x1) / x), Vieja.Get_dy(), ((Vieja.Get_z2() - Nueva.Get_z2()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);

		}
		//Fuera
		if ((Nueva.Get_y1() - Vieja.Get_y1()) > y)
		{
			y1 = Vieja.Get_y1() + ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y;
			int num = Vieja.Get_dx()*Vieja.Get_dz()*((Nueva.Get_y1() - Vieja.Get_y1()) / y);
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), x1, Vieja.Get_y1(), z1, x2 - x1, ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Nueva.Get_y1() - Vieja.Get_y1()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);


		}
		//Dentro
		if ((Vieja.Get_y2() - Nueva.Get_y2()) > y)
		{
			y2 = Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y;
			int num = Vieja.Get_dx()*Vieja.Get_dz()*((Vieja.Get_y2() - Nueva.Get_y2()) / y);
			CONFIGURACAO Configuracao(m_Container, Vieja.Get_Id(), x1, Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z1, x2 - x1, ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Vieja.Get_y2() - Nueva.Get_y2()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
		}

	}

//	Espacio.ModificarSpace(x1,y1,z1,x2,y2,z2);
//	return (Antes-Ahora);


}
//Solamente me devuelve la cantidad
int MOVIMIENTO::ActualizarBloquesElegidoQuitaCantidad( CONFIGURACAO &Vieja,CONFIGURACAO &Nueva)
{
	//es distinta a la de los espacios ya que en esta no
	//se pueden cortar las configuraciones
	//E es la configuracao vieja
	//C es la configuraco nueva
	//Podemos tener seis posibles espacios nuevos
	int dimx=Vieja.Get_x2()-Vieja.Get_x1();
	int x=dimx/Vieja.Get_dx();
	int dimy=Vieja.Get_y2()-Vieja.Get_y1();
	int y=dimy/Vieja.Get_dy();
	int dimz=Vieja.Get_z2()-Vieja.Get_z1();
	int z=dimz/Vieja.Get_dz();
	int Antes=Vieja.Get_Volumen();
	int Ahora=0;
	int x1=Vieja.Get_x1(),z1=Vieja.Get_z1();
	int x2=Vieja.Get_x2(),z2=Vieja.Get_z2();

	//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
	if ((Nueva.Get_x1()-Vieja.Get_x1())>x)
	{
		x1=Vieja.Get_x1()+((Nueva.Get_x1()-Vieja.Get_x1())/x)*x;

		//Si se da esto es un espacio en el que no voy a poder colocar nada 
		//Por ahora no lo creo
		//este el numero de piezas del bloque
		Ahora+=((Nueva.Get_x1()-Vieja.Get_x1())/x)*x*dimy*dimz;
	}


	//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
	if ((Vieja.Get_x2()-Nueva.Get_x2())>x)
	{
		x2=Vieja.Get_x2()-((Vieja.Get_x2()-Nueva.Get_x2())/x)*x;

		Ahora+=((Vieja.Get_x2()-Nueva.Get_x2())/x)*x*dimy*dimz;
	
	}
	//Abajo
	if ((Nueva.Get_z1() - Vieja.Get_z1()) > z)
	{
		z1 = Vieja.Get_z1() + ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z;

		Ahora += ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z * (x2 - x1) * dimy;

	}

	//Arriba
	if ((Vieja.Get_z2() - Nueva.Get_z2()) > z)
	{
		z2 = Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z;

		Ahora += ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z * (x2 - x1) * dimy;

	}
	//Fuera
	if ((Nueva.Get_y1()-Vieja.Get_y1())>z)
	{
		Ahora+=((Nueva.Get_y1()-Vieja.Get_y1())/y)*y*(x2-x1)*(z2-z1);


	}
	//Dentro
	if ((Vieja.Get_y2()-Nueva.Get_y2())>y)
	{
		Ahora+=((Vieja.Get_y2()-Nueva.Get_y2())/y)*y*(x2-x1)*(z2-z1);

	}

	if ((Antes-Ahora)<0)
		int kk=9;
	return (Antes-Ahora);


}

//Dados dos bloques deja los bloques para que no se intersecten
//ademas tiene que meter todas las perdidas nuevas que van a aparecetr
void CONTAINER::ActualizarBloquesElegido( CONFIGURACAO &Vieja,CONFIGURACAO &Nueva,std::list <CONFIGURACAO> &lista_temp, std::list<CONFIGURACAO> &lista)
{
	//es distinta a la de los espacios ya que en esta no
	//se pueden cortar las configuraciones
	//E es la configuracao vieja
	//C es la configuraco nueva
	//Podemos tener seis posibles espacios nuevos
	int dimx=Vieja.Get_x2()-Vieja.Get_x1();
	int x=dimx/Vieja.Get_dx();
	int dimy=Vieja.Get_y2()-Vieja.Get_y1();
	int y=dimy/Vieja.Get_dy();
	int dimz=Vieja.Get_z2()-Vieja.Get_z1();
	int z=dimz/Vieja.Get_dz();
	int x1=Vieja.Get_x1(),y1=Vieja.Get_y1(),z1=Vieja.Get_z1();
	int x2=Vieja.Get_x2(),y2=Vieja.Get_y2(),z2=Vieja.Get_z2();
	bool izq = false;
	bool der = false;
	bool abj = false;
	bool arr = false;
	bool den = false;
	bool fue = false;
	int kkk = 0;
	int kk2 = 0;

	if (m_full_supported == true)
	{
		//Abajo
		if ((Nueva.Get_z1() - Vieja.Get_z1()) > z)
		{
			abj = true;
			z1 = Vieja.Get_z1() + ((Nueva.Get_z1() - Vieja.Get_z1()) / z)*z;
			int num = Vieja.Get_dx()*((Nueva.Get_z1() - Vieja.Get_z1()) / z)*Vieja.Get_dy();
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z1(), x2 - x1, dimy, ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z, ((x2 - x1) / x), Vieja.Get_dy(), ((Nueva.Get_z1() - Vieja.Get_z1()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
			RestarConfiguracaosCon(Vieja, Configuracao, lista_temp, lista, izq, der, abj, arr, den, fue);
			kkk++;
			kk2++;
			abj = false;
		}

		//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
		if ((Nueva.Get_x1() - Vieja.Get_x1()) > x && kk2 == 0)
		{
			izq = true;
			//Si se da esto es un espacio en el que no voy a poder colocar nada 
			//Por ahora no lo creo
			//este el numero de piezas del bloque
			x1 = Vieja.Get_x1() + ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x;
			int num = ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), Vieja.Get_x1(), Vieja.Get_y1(), Vieja.Get_z1(), ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x, dimy, dimz, ((Nueva.Get_x1() - Vieja.Get_x1()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
			RestarConfiguracaosCon(Vieja, Configuracao, lista_temp, lista, izq, der, abj, arr, den, fue);
			kkk++;
			izq = false;
		}


		//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
		if ((Vieja.Get_x2() - Nueva.Get_x2()) > x && kk2 == 0)
		{
			der = true;
			x2 = Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x;

			int num = ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, Vieja.Get_y1(), Vieja.Get_z1(), ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, dimy, dimz, ((Vieja.Get_x2() - Nueva.Get_x2()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
			RestarConfiguracaosCon(Vieja, Configuracao, lista_temp, lista, izq, der, abj, arr, den, fue);
		    kkk++;
			der = false;
		}

		//Fuera
		if ((Nueva.Get_y1() - Vieja.Get_y1()) > y && kk2 == 0)
		{
			fue = true;
			y1 = Vieja.Get_y1() + ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y;

			int num = Vieja.Get_dx()*Vieja.Get_dz()*((Nueva.Get_y1() - Vieja.Get_y1()) / y);
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), z1, x2 - x1, ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Nueva.Get_y1() - Vieja.Get_y1()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
			RestarConfiguracaosCon(Vieja, Configuracao, lista_temp, lista, izq, der, abj, arr, den, fue);
			kkk++;
			fue = false;
		}
		//Dentro
		if ((Vieja.Get_y2() - Nueva.Get_y2()) > y && kk2 == 0)
		{
			den = true;
			y2 = Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y;
			int num = Vieja.Get_dx()*Vieja.Get_dz()*((Vieja.Get_y2() - Nueva.Get_y2()) / y);
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z1, x2 - x1, ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Vieja.Get_y2() - Nueva.Get_y2()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
			RestarConfiguracaosCon(Vieja, Configuracao, lista_temp, lista, izq, der, abj, arr, den, fue);
			kkk++;
			den = false;
		}
		//Arriba
		if ((Vieja.Get_z2() - Nueva.Get_z2()) > z && kkk == 0 && kk2 == 0)
		{
			arr = true;
			z2 = Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z)*z;
			int num = Vieja.Get_dx()*((Vieja.Get_z2() - Nueva.Get_z2()) / z)*Vieja.Get_dy();
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) /z) * z, x2 - x1, dimy, ((Vieja.Get_z2() - Nueva.Get_z2()) / z)* z, ((x2 - x1) / x), Vieja.Get_dy(), ((Vieja.Get_z2() - Nueva.Get_z2()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
			RestarConfiguracaosCon(Vieja, Configuracao, lista_temp, lista, izq, der, abj, arr, den, fue);
			kkk++;
			arr = false;
		}
			RestarConfiguracaosCon(Vieja, Vieja, lista_temp, lista, izq, der, abj, arr, den, fue);
	}
	else
	{
		//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
		if ((Nueva.Get_x1() - Vieja.Get_x1()) > x)
		{
			//Si se da esto es un espacio en el que no voy a poder colocar nada 
			//Por ahora no lo creo
			//este el numero de piezas del bloque
			x1 = Vieja.Get_x1() + ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x;
			int num = ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), Vieja.Get_x1(), Vieja.Get_y1(), Vieja.Get_z1(), ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x, dimy, dimz, ((Nueva.Get_x1() - Vieja.Get_x1()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
		}


		//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
		if ((Vieja.Get_x2() - Nueva.Get_x2()) > x)
		{
			x2 = Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x;

			int num = ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, Vieja.Get_y1(), Vieja.Get_z1(), ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, dimy, dimz, ((Vieja.Get_x2() - Nueva.Get_x2()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);

		}
		//Abajo
		if ((Nueva.Get_z1() - Vieja.Get_z1()) > z)
		{
			z1 = Vieja.Get_z1() + ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z;
			int num = Vieja.Get_dx() * Vieja.Get_dy() * ((Nueva.Get_z1() - Vieja.Get_z1()) / z);
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z1(), x2 - x1, dimy, ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z, ((x2 - x1) / x), Vieja.Get_dy(), ((Nueva.Get_z1() - Vieja.Get_z1()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
		}

		//Arriba
		if ((Vieja.Get_z2() - Nueva.Get_z2()) > z)
		{
			z2 = Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z;
			int num = Vieja.Get_dx() * ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * Vieja.Get_dy();
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z, x2 - x1, dimy, ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z, ((x2 - x1) / x), Vieja.Get_dy(), ((Vieja.Get_z2() - Nueva.Get_z2()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
		}
		//Fuera
		if ((Nueva.Get_y1() - Vieja.Get_y1()) > y)
		{
			y1 = Vieja.Get_y1() + ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y;

			int num = Vieja.Get_dx()*Vieja.Get_dz()*((Nueva.Get_y1() - Vieja.Get_y1()) / y);
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), z1, x2 - x1, ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Nueva.Get_y1() - Vieja.Get_y1()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);

		}
		//Dentro
		if ((Vieja.Get_y2() - Nueva.Get_y2()) > y)
		{
			y2 = Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y;
			int num = Vieja.Get_dx()*Vieja.Get_dz()*((Vieja.Get_y2() - Nueva.Get_y2()) / y);
			CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z1, x2 - x1, ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Vieja.Get_y2() - Nueva.Get_y2()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
			/*lista_temp.push_back(Configuracao);*/
			InsertarConfiguracaoOrden(Configuracao, lista_temp);
		}
		
	}
}
void CONTAINER::ActualizarBloquesElegidoReducir(CONFIGURACAO &Vieja, CONFIGURACAO &Nueva, std::list <CONFIGURACAO> &lista_temp, std::list<CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista2)
{
	//es distinta a la de los espacios ya que en esta no
	//se pueden cortar las configuraciones
	//E es la configuracao vieja
	//C es la configuraco nueva
	//Podemos tener seis posibles espacios nuevos
	int dimx = Vieja.Get_x2() - Vieja.Get_x1();
	int x = dimx / Vieja.Get_dx();
	int dimy = Vieja.Get_y2() - Vieja.Get_y1();
	int y = dimy / Vieja.Get_dy();
	int dimz = Vieja.Get_z2() - Vieja.Get_z1();
	int z = dimz / Vieja.Get_dz();
	int x1 = Vieja.Get_x1(), y1 = Vieja.Get_y1(), z1 = Vieja.Get_z1();
	int x2 = Vieja.Get_x2(), y2 = Vieja.Get_y2(), z2 = Vieja.Get_z2();
	bool izq = false;
	bool der = false;
	bool abj = false;
	bool arr = false;
	bool den = false;
	bool fue = false;
	int kkk = 0;
	int kk2 = 0;

	//Abajo
	if ((Nueva.Get_z1() - Vieja.Get_z1()) >= z)
	{
		abj = true;
		z1 = Vieja.Get_z1() + ((Nueva.Get_z1() - Vieja.Get_z1()) / z)*z;
		int num = Vieja.Get_dx()*Vieja.Get_dy() * ((Nueva.Get_z1() - Vieja.Get_z1()) / z);
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z1(), x2 - x1, dimy, ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z, ((x2 - x1) / x), Vieja.Get_dy(), ((Nueva.Get_z1() - Vieja.Get_z1()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			RestarConfiguracaosConReducir(Vieja, Configuracao, lista_temp, lista, lista2, izq, der, abj, arr, den, fue);
			kkk++;
			kk2++;
		}
		abj = false;
	}

	//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
	if ((Nueva.Get_x1() - Vieja.Get_x1()) >= x && kk2==0)
	{
		izq = true;
		//Si se da esto es un espacio en el que no voy a poder colocar nada 
		//Por ahora no lo creo
		//este el numero de piezas del bloque
		x1 = Vieja.Get_x1() + ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x;
		int num = ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), Vieja.Get_x1(), Vieja.Get_y1(), Vieja.Get_z1(), ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x, dimy, dimz, ((Nueva.Get_x1() - Vieja.Get_x1()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			RestarConfiguracaosConReducir(Vieja, Configuracao, lista_temp, lista, lista2,izq, der, abj, arr, den, fue);
			kkk++;
		}
		izq = false;
	}


	//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
	if ((Vieja.Get_x2() - Nueva.Get_x2()) >= x && kk2 == 0)
	{
		der = true;
		x2 = Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x;

		int num = ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, Vieja.Get_y1(), Vieja.Get_z1(), ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, dimy, dimz, ((Vieja.Get_x2() - Nueva.Get_x2()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			RestarConfiguracaosConReducir(Vieja, Configuracao, lista_temp, lista, lista2,izq, der, abj, arr, den, fue);
			kkk++;
		}
		der = false;
	}
	
	//Fuera
	if ((Nueva.Get_y1() - Vieja.Get_y1()) >= y && kk2 == 0)
	{
		fue = true;
		y1 = Vieja.Get_y1() + ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y;

		int num = Vieja.Get_dx()*((Nueva.Get_y1() - Vieja.Get_y1()) / y) * Vieja.Get_dz();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), z1, x2 - x1, ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Nueva.Get_y1() - Vieja.Get_y1()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			RestarConfiguracaosConReducir(Vieja, Configuracao, lista_temp, lista, lista2,izq, der, abj, arr, den, fue);
			kkk++;
		}
		fue = false;
	}
	//Dentro
	if ((Vieja.Get_y2() - Nueva.Get_y2()) >= y && kk2 == 0)
	{
		den = true;
		y2 = Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y;
		int num = Vieja.Get_dx()*((Vieja.Get_y2() - Nueva.Get_y2()) / y) * Vieja.Get_dz();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z1, x2 - x1, ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Vieja.Get_y2() - Nueva.Get_y2()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			RestarConfiguracaosConReducir(Vieja, Configuracao, lista_temp, lista, lista2,izq, der, abj, arr, den, fue);
			kkk++;
		}
		den = false;
	}
	//Arriba
	if ((Vieja.Get_z2() - Nueva.Get_z2()) >= z && kkk == 0 && kk2 == 0)
	{
		arr = true;
		z2 = Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z)*z;
		int num = Vieja.Get_dx()*((Vieja.Get_z2() - Nueva.Get_z2()) / z)*Vieja.Get_dy();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z, x2 - x1, dimy, ((Vieja.Get_z2() - Nueva.Get_z2()) / z)* z, ((x2 - x1) / x), Vieja.Get_dy(), ((Vieja.Get_z2() - Nueva.Get_z2()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			RestarConfiguracaosConReducir(Vieja, Configuracao, lista_temp, lista, lista2, izq, der, abj, arr, den, fue);
			kkk++;
		}
		arr = false;
	}

	if (m_full_supported == true && kkk == 0 && kk2==0)
	{
		RestarConfiguracaosConReducir(Vieja, Vieja, lista_temp, lista, lista2,izq, der, abj, arr, den, fue);
	}
}

void CONTAINER::ActualizarBloquesElegidoReducirVol(CONFIGURACAO &Vieja, CONFIGURACAO &Nueva, std::list <CONFIGURACAO> &lista_temp, std::list<CONFIGURACAO> &lista, int vol)
{
	//es distinta a la de los espacios ya que en esta no
	//se pueden cortar las configuraciones
	//E es la configuracao vieja
	//C es la configuraco nueva
	//Podemos tener seis posibles espacios nuevos
	int dimx = Vieja.Get_x2() - Vieja.Get_x1();
	int x = dimx / Vieja.Get_dx();
	int dimy = Vieja.Get_y2() - Vieja.Get_y1();
	int y = dimy / Vieja.Get_dy();
	int dimz = Vieja.Get_z2() - Vieja.Get_z1();
	int z = dimz / Vieja.Get_dz();
	int x1 = Vieja.Get_x1(), y1 = Vieja.Get_y1(), z1 = Vieja.Get_z1();
	int x2 = Vieja.Get_x2(), y2 = Vieja.Get_y2(), z2 = Vieja.Get_z2();
	bool izq = false;
	bool der = false;
	bool abj = false;
	bool arr = false;
	bool den = false;
	bool fue = false;
	int kkk = 0;
	int kk2 = 0;

	//Abajo
	if ((Nueva.Get_z1() - Vieja.Get_z1()) > z)
	{
		abj = true;
		z1 = Vieja.Get_z1() + ((Nueva.Get_z1() - Vieja.Get_z1()) / z)*z;
		int num = Vieja.Get_dx()*((Nueva.Get_z1() - Vieja.Get_z1()) / z)*Vieja.Get_dy();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z1(), x2 - x1, dimy, ((Nueva.Get_z1() - Vieja.Get_z1()) / z) * z, ((x2 - x1) / x), Vieja.Get_dy(), ((Nueva.Get_z1() - Vieja.Get_z1()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			vol += Vieja.Get_Volumen() - Configuracao.Get_Volumen();
			RestarConfiguracaosConReducirVol(Vieja, Configuracao, lista_temp, lista, vol, izq, der, abj, arr, den, fue);
			kkk++;
			kk2++;
		}
		abj = false;
	}

	//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
	if ((Nueva.Get_x1() - Vieja.Get_x1()) > x && kk2 == 0)
	{
		izq = true;
		//Si se da esto es un espacio en el que no voy a poder colocar nada 
		//Por ahora no lo creo
		//este el numero de piezas del bloque
		x1 = Vieja.Get_x1() + ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x;
		int num = ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), Vieja.Get_x1(), Vieja.Get_y1(), Vieja.Get_z1(), ((Nueva.Get_x1() - Vieja.Get_x1()) / x)*x, dimy, dimz, ((Nueva.Get_x1() - Vieja.Get_x1()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			vol += Vieja.Get_Volumen() - Configuracao.Get_Volumen();
			RestarConfiguracaosConReducirVol(Vieja, Configuracao, lista_temp, lista, vol, izq, der, abj, arr, den, fue);
			kkk++;
		}
		izq = false;
	}


	//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
	if ((Vieja.Get_x2() - Nueva.Get_x2()) > x && kk2 == 0)
	{
		der = true;
		x2 = Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x;

		int num = ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*Vieja.Get_dy()*Vieja.Get_dz();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), Vieja.Get_x2() - ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, Vieja.Get_y1(), Vieja.Get_z1(), ((Vieja.Get_x2() - Nueva.Get_x2()) / x)*x, dimy, dimz, ((Vieja.Get_x2() - Nueva.Get_x2()) / x), Vieja.Get_dy(), Vieja.Get_dz(), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			vol += Vieja.Get_Volumen() - Configuracao.Get_Volumen();
			RestarConfiguracaosConReducirVol(Vieja, Configuracao, lista_temp, lista, vol, izq, der, abj, arr, den, fue);
			kkk++;
		}
		der = false;
	}

	//Fuera
	if ((Nueva.Get_y1() - Vieja.Get_y1()) > y && kk2 == 0)
	{
		fue = true;
		y1 = Vieja.Get_y1() + ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y;

		int num = Vieja.Get_dx()*Vieja.Get_dz()*((Nueva.Get_y1() - Vieja.Get_y1()) / y);
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), z1, x2 - x1, ((Nueva.Get_y1() - Vieja.Get_y1()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Nueva.Get_y1() - Vieja.Get_y1()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			vol += Vieja.Get_Volumen() - Configuracao.Get_Volumen();
			RestarConfiguracaosConReducirVol(Vieja, Configuracao, lista_temp, lista, vol, izq, der, abj, arr, den, fue);
			kkk++;
		}
		fue = false;
	}
	//Dentro
	if ((Vieja.Get_y2() - Nueva.Get_y2()) > y && kk2 == 0)
	{
		den = true;
		y2 = Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y;
		int num = Vieja.Get_dx()*Vieja.Get_dz()*((Vieja.Get_y2() - Nueva.Get_y2()) / y);
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y2() - ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z1, x2 - x1, ((Vieja.Get_y2() - Nueva.Get_y2()) / y)*y, z2 - z1, ((x2 - x1) / x), ((Vieja.Get_y2() - Nueva.Get_y2()) / y), ((z2 - z1) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			vol += Vieja.Get_Volumen() - Configuracao.Get_Volumen();
			RestarConfiguracaosConReducirVol(Vieja, Configuracao, lista_temp, lista, vol, izq, der, abj, arr, den, fue);
			kkk++;
		}
		den = false;
	}
	//Arriba
	if ((Vieja.Get_z2() - Nueva.Get_z2()) > z && kkk == 0 && kk2 == 0)
	{
		arr = true;
		z2 = Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z)*z;
		int num = Vieja.Get_dx()*((Vieja.Get_z2() - Nueva.Get_z2()) / z)*Vieja.Get_dy();
		CONFIGURACAO Configuracao(this, Vieja.Get_Id(), x1, Vieja.Get_y1(), Vieja.Get_z2() - ((Vieja.Get_z2() - Nueva.Get_z2()) / z) * z, x2 - x1, dimy, ((Vieja.Get_z2() - Nueva.Get_z2()) / z)* z, ((x2 - x1) / x), Vieja.Get_dy(), ((Vieja.Get_z2() - Nueva.Get_z2()) / z), Vieja.Get_Tipo(), num, Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);
		lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista_temp);
		InsertarConfiguracaoOrden(Configuracao, lista);
		if (m_full_supported == true)
		{
			vol += Vieja.Get_Volumen() - Configuracao.Get_Volumen();
			RestarConfiguracaosConReducirVol(Vieja, Configuracao, lista_temp, lista, vol, izq, der, abj, arr, den, fue);
			kkk++;
		}
		arr = false;
	}

	if (m_full_supported == true && kkk == 0 && kk2 == 0)
	{
		vol += Vieja.Get_Volumen();
		RestarConfiguracaosConReducirVol(Vieja, Vieja, lista_temp, lista, vol, izq, der, abj, arr, den, fue);
	}
}

//Dados dos bloques deja los bloques para que no se intersecten
//ademas tiene que meter todas las perdidas nuevas que van a aparecetr
void MOVIMIENTO::ActualizarBloquesElegido( CONFIGURACAO &Vieja,CONFIGURACAO &Nueva,std::list <CONFIGURACAO> &lista_temp,SPACE &Espacio)
{
	//es distinta a la de los espacios ya que en esta no
	//se pueden cortar las configuraciones
	//E es la configuracao vieja
	//C es la configuraco nueva
	//Podemos tener seis posibles espacios nuevos
	int dimx=Vieja.Get_x2()-Vieja.Get_x1();
	int x=dimx/Vieja.Get_dx();
	int dimy=Vieja.Get_y2()-Vieja.Get_y1();
	int y=dimy/Vieja.Get_dy();
	int dimz=Vieja.Get_z2()-Vieja.Get_z1();
	int z=dimz/Vieja.Get_dz();
	int x1=Vieja.Get_x1(),y1=Vieja.Get_y1(),z1=Vieja.Get_z1();
	int x2=Vieja.Get_x2(),y2=Vieja.Get_y2(),z2=Vieja.Get_z2();

	//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
	if ((Nueva.Get_x1()-Vieja.Get_x1())>x)
	{
		//Si se da esto es un espacio en el que no voy a poder colocar nada 
		//Por ahora no lo creo
		//este el numero de piezas del bloque
		x1=Vieja.Get_x1()+((Nueva.Get_x1()-Vieja.Get_x1())/x)*x;
		int num=((Nueva.Get_x1()-Vieja.Get_x1())/x)*Vieja.Get_dy()*Vieja.Get_dz();
		CONFIGURACAO Configuracao(m_Container,Vieja.Get_Id(),Vieja.Get_x1(),Vieja.Get_y1(),Vieja.Get_z1(),((Nueva.Get_x1()-Vieja.Get_x1())/x)*x,dimy,dimz ,((Nueva.Get_x1()-Vieja.Get_x1())/x), Vieja.Get_dy(),Vieja.Get_dz(),Vieja.Get_Tipo(),num,Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);*/
		m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
	}


	//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
	if ((Vieja.Get_x2()-Nueva.Get_x2())>x)
	{
		x2=Vieja.Get_x2()-((Vieja.Get_x2()-Nueva.Get_x2())/x)*x;

		int num=((Vieja.Get_x2()-Nueva.Get_x2())/x)*Vieja.Get_dy()*Vieja.Get_dz();
		CONFIGURACAO Configuracao(m_Container,Vieja.Get_Id(),Vieja.Get_x2()-((Vieja.Get_x2()-Nueva.Get_x2())/x)*x,Vieja.Get_y1(),Vieja.Get_z1(),((Vieja.Get_x2()-Nueva.Get_x2())/x)*x,dimy,dimz ,((Vieja.Get_x2()-Nueva.Get_x2())/x), Vieja.Get_dy(),Vieja.Get_dz(),Vieja.Get_Tipo(),num,Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);*/
		m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
	
	}
	//Abajo
	if ((Nueva.Get_y1()-Vieja.Get_y1())>y)
	{
		y1=Vieja.Get_y1()+((Nueva.Get_y1()-Vieja.Get_y1())/y)*y;
		int num=Vieja.Get_dx()*((Nueva.Get_y1()-Vieja.Get_y1())/y)*Vieja.Get_dz();
		CONFIGURACAO Configuracao(m_Container,Vieja.Get_Id(),x1,Vieja.Get_y1(),Vieja.Get_z1(),x2-x1,((Nueva.Get_y1()-Vieja.Get_y1())/y)*y,dimz ,((x2-x1)/x),((Nueva.Get_y1()-Vieja.Get_y1())/y),Vieja.Get_dz(),Vieja.Get_Tipo(),num,Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);*/
		m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
	}

	//Arriba
	if ((Vieja.Get_y2()-Nueva.Get_y2())>y)
	{
		y2=Vieja.Get_y2()-((Vieja.Get_y2()-Nueva.Get_y2())/y)*y;
		int num=Vieja.Get_dx()*((Vieja.Get_y2()-Nueva.Get_y2())/y)*Vieja.Get_dz();
		CONFIGURACAO Configuracao(m_Container,Vieja.Get_Id(),x1,Vieja.Get_y2()-((Vieja.Get_y2()-Nueva.Get_y2())/y)*y,Vieja.Get_z1(),x2-x1,((Vieja.Get_y2()-Nueva.Get_y2())/y)*y,dimz ,((x2-x1)/x),((Vieja.Get_y2()-Nueva.Get_y2())/y),Vieja.Get_dz(),Vieja.Get_Tipo(),num,Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);*/
		m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
	}
	//Fuera
	if ((Nueva.Get_z1()-Vieja.Get_z1())>z)
	{
		z1=Vieja.Get_z1()+((Nueva.Get_z1()-Vieja.Get_z1())/z)*z;

		int num=Vieja.Get_dx()*Vieja.Get_dy()*((Nueva.Get_z1()-Vieja.Get_z1())/z);
		CONFIGURACAO Configuracao(m_Container,Vieja.Get_Id(),x1,y1,Vieja.Get_z1(),x2-x1,y2-y1,((Nueva.Get_z1()-Vieja.Get_z1())/z)*z ,((x2-x1)/x),((y2-y1)/y),((Nueva.Get_z1()-Vieja.Get_z1())/z),Vieja.Get_Tipo(),num,Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);*/
		m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);

	}
	//Dentro
	if ((Vieja.Get_z2()-Nueva.Get_z2())>z)
	{
		z2=Vieja.Get_z2()-((Vieja.Get_z2()-Nueva.Get_z2())/z)*z;
		int num=Vieja.Get_dx()*Vieja.Get_dy()*((Vieja.Get_z2()-Nueva.Get_z2())/z);
		CONFIGURACAO Configuracao(m_Container,Vieja.Get_Id(),x1,y1,Vieja.Get_z2()-((Vieja.Get_z2()-Nueva.Get_z2())/z)*z,x2-x1,y2-y1,((Vieja.Get_z2()-Nueva.Get_z2())/z)*z ,((x2-x1)/x),((y2-y1)/y),((Vieja.Get_z2()-Nueva.Get_z2())/z),Vieja.Get_Tipo(),num,Vieja.Get_orig());
		/*lista_temp.push_back(Configuracao);*/
		m_Container->InsertarConfiguracaoOrden(Configuracao, lista_temp);
	}
	Espacio.ModificarSpace(x1,y1,z1,x2,y2,z2);


}
void MOVIMIENTO::CambiarMejor(std::list<CONFIGURACAO> &lista,int Vol)
{
	m_vol=Vol;
	m_val=Vol;
	m_Configuracaos_new=lista;
}
void MOVIMIENTO::CambiarMejor(std::list<CONFIGURACAO> &lista,int Vol,int pos)
{
	m_vol=Vol;
	m_val=pos;
	m_Configuracaos_new=lista;
}
void MOVIMIENTO::CompararMovimientos(MOVIMIENTO &otro)
{
	if (m_val>otro.Get_Val())
		return;
	if (m_val<otro.Get_Val())
	{
		m_vol=otro.Get_Volumen();
		m_val=otro.Get_Val();
		m_Configuracao=otro.Get_Configuracao();
		m_Configuracaos_new=otro.Get_Configuracaos();
	}
}
/*
bool MOVIMIENTO::EsMejorMovimientoA_que_B(std::multiset<double> &A,std::multiset<double> &B)
{
	std::multiset< double > ::reverse_iterator itrk,itrk2;
	itrk=A.rbegin();
	itrk2=B.rbegin();
	if ((*itrk)>=(*itrk2))
		return true;
	else 
		return false;
}
*/
void CONTAINER::ConstruirSolucionBin(std::list<CONFIGURACAO> &lista,bool manera)
{

	m_total_volumen_ocupado=0;
	
//	m_total_volumen_ocupado=0;

	MinimaDimensionMCMov();
	std::list<CONFIGURACAO> lista_configuracaos;
	std::list<SPACE> lista_espacios;
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
	lista_espacios.push_back(Space);
	bool primera=true;

	while (lista_espacios.size()>0)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		std::list<SPACE> ::iterator it;
		SPACE &SpaceElegido=ElegirSpaceMovimiento(lista_espacios, lista);
		if (SpaceElegido.Get_Flag()==true)
		{
		/*	if (lista.size()!=0)
			{

				printf("Que pasa");
				for (int inkki=0;;);
			}*/

			lista=lista_configuracaos;
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Por si podemos poner mas piezas que esas

		//Elegir configuración para ese espacio
		if (lista.size()==0)
		ElegirConfiguracaoMov(SpaceElegido,Configuracao,lista_configuracaos);

		else
		PonerConfiguracaoMov(SpaceElegido,Configuracao,lista_configuracaos,lista);


		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}

		ActualizarListasMov(SpaceElegido,Configuracao,lista_espacios);
		if (primera==true && lista.size()==0)
		{
			primera=false;
			std::list<SPACE> ::iterator itl;
			for (itl=lista_espacios.begin();itl!=lista_espacios.end();itl++)
			{
				(*itl).Set_Flag(false);
			}
		}
	}

	lista=lista_configuracaos;

//	VerificarSolucion(m_Configuracaos);

}
//si manera es true solamente es contruir en otro caso es tambien poder meter mas piezas
void CONTAINER::ConstruirSolucionBinC(std::list<CONFIGURACAO> &lista,bool manera)
{

	m_total_volumen_ocupado=0;
	
//	m_total_volumen_ocupado=0;

	MinimaDimensionMCMov();
	m_Spaces.clear();
	m_Configuracaos.clear();
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
	m_Spaces.push_back(Space);
	bool primera=true;
	bool elquesea=false;

	while (m_Spaces.size()>0 && ((lista.size()>0 && manera==true )|| (manera==false)))
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		std::list<SPACE> ::iterator it;
		if (lista.size()==0)
			elquesea=true;
		SPACE &SpaceElegido=ElegirSpaceConstruccionNueva(elquesea);
		if (m_Spaces.size()==0 || SpaceElegido.Get_Flag()==true)
		{
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Por si podemos poner mas piezas que esas

		//Elegir configuración para ese espacio
		if (lista.size()==0)
		ElegirConfiguracao(SpaceElegido,Configuracao);

		else
		PonerConfiguracao(SpaceElegido,Configuracao,lista,true);


		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}

		ActualizarListas(SpaceElegido,Configuracao);
		if (primera==true && lista.size()==0)
		{
			primera=false;
			std::list<SPACE> ::iterator itl;
			for (itl=m_Spaces.begin();itl!=m_Spaces.end();itl++)
			{
				(*itl).Set_Flag(false);
			}
		}
	}


//	VerificarSolucion(m_Configuracaos);

}
void CONTAINER::RellenarVariosBin(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista )
{
	bool una_distinta=false;
	MinimaDimensionMCMov();
	std::list<CONFIGURACAO> lista_configuracaos;
	std::list<SPACE> lista_espacios;
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space1(0,0,0,m_X,m_Y,m_Z,this);
	SPACE SpaceElegido(0,0,0,m_X,m_Y,m_Z,this);
	lista_espacios.push_back(Space1);

	int temp=m_total_volumen_ocupado;
	while (m_total_volumen_ocupado!=m_total_volumen)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		bool posible=false;
		ElegirSpaceMovimiento(SpaceElegido,lista_espacios,posible);
		if (lista_espacios.size()==0 || posible==false )
		{
			if (m_total_volumen_ocupado!=m_total_volumen)
			{
				int thisbin=m_total_volumen_ocupado-temp;
				temp=m_total_volumen_ocupado;
				//empiezo otro bin
				SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
				SpaceElegido=Space;
				std::list< SPACE> otro_bin;
				otro_bin.push_back(Space);
				m_SpacesMC.push_back(lista_espacios);
				lista_espacios=otro_bin;
				std::pair< int, std::list< CONFIGURACAO > > p(thisbin,lista_configuracaos);
				//meto las configuracaos en la lista
//				m_ConfiguracaosMC.push_back(p);
				InsertarOrden(m_ConfiguracaosMC,p);
				//borro la lista actual de configuracaos
				lista_configuracaos.clear();
				if (m_ConfiguracaosMC.size()+1==m_Best_nbins)
					return;
			}
			else return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Por si podemos poner mas piezas que esas

		//Elegir configuración para ese espacio
		ElegirConfiguracaoMov(SpaceElegido,Configuracao,lista_configuracaos);

		if (Configuracao.Get_Id()==99999)
		{
			
			SpaceElegido.Set_Flag(true);
			std::list<SPACE> ::iterator itL1;
			for (itL1=lista_espacios.begin();itL1!=lista_espacios.end();itL1++)
			{
				if (((*itL1).Get_x1()==SpaceElegido.Get_x1()) &&
					((*itL1).Get_x2()==SpaceElegido.Get_x2()) &&
					((*itL1).Get_y1()==SpaceElegido.Get_y1()) &&
					((*itL1).Get_y2()==SpaceElegido.Get_y2()) &&
					((*itL1).Get_z1()==SpaceElegido.Get_z1()) &&
					((*itL1).Get_z2()==SpaceElegido.Get_z2()) )
				{
					(*itL1).Set_Flag(true);

				}
			}
			continue;

		}

		ActualizarListasMov(SpaceElegido,Configuracao,lista_espacios);
	}
	int thisbin=m_total_volumen_ocupado-temp;

	std::pair< int, std::list< CONFIGURACAO > > p(thisbin,lista_configuracaos);
	//meto las configuracaos en la lista
	InsertarOrden(m_ConfiguracaosMC,p);

//	m_ConfiguracaosMC.push_back(p);


//	VerificarSolucion(m_Configuracaos);

}

//La diferencia con la anterior es que esta no la mete en Configuracaos
void CONTAINER::RellenarVariosBin(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista,int hasta)
{
	bool una_distinta=false;
	
//	m_total_volumen_ocupado=0;
	std::list<CONFIGURACAO> ::iterator it;
	MinimaDimensionMCMov();
	std::list<CONFIGURACAO> lista_configuracaos;
	std::list<SPACE> lista_espacios;
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
	lista_espacios.push_back(Space);
	bool primera=true;
	int temp=m_total_volumen_ocupado;
	while (m_total_volumen_ocupado!=m_total_volumen)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		SPACE &SpaceElegido=ElegirSpaceMovimiento(lista_espacios, m_Configuracaos); //He puesto m_Configuracaos para que no se queje
		if (lista_espacios.size()==0 || SpaceElegido.Get_Flag()==true)
		{
			if (m_total_volumen_ocupado!=m_total_volumen)
			{
				int thisbin=m_total_volumen_ocupado-temp;
				temp=m_total_volumen_ocupado;
				//empiezo otro bin
				SpaceElegido=Space;
				std::list< SPACE> otro_bin;
				otro_bin.push_back(Space);
				lista_espacios=otro_bin;
				std::pair< int, std::list< CONFIGURACAO > > p(thisbin,lista_configuracaos);
				//meto las configuracaos en la lista
				InsertarOrden(lista,p);
				//borro la lista actual de configuracaos
				lista_configuracaos.clear();
				if (lista.size()==hasta)
					return;
			}
			else return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);
		//Por si fijamos alguna pieza
		//Elegir configuración para ese espacio
		ElegirConfiguracaoMov(SpaceElegido,Configuracao,lista_configuracaos);

		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}
//				if (m_iter_actual==673)	printf("H");
//				if (m_iter_actual==673)	printf("h4-,%d",SpaceElegido.Get_x1());
		ActualizarListasMov(SpaceElegido,Configuracao,lista_espacios);
//				if (m_iter_actual==673)	printf("h8");
	}
	int thisbin=m_total_volumen_ocupado-temp;

	std::pair< int, std::list< CONFIGURACAO > > p(thisbin,lista_configuracaos);
	//meto las configuracaos en la lista
	InsertarOrden(lista,p);

//	m_ConfiguracaosMC.push_back(p);


//	VerificarSolucion(m_Configuracaos);

}


//La diferencia con la anterior es que esta no la mete en Configuracaos
void CONTAINER::RellenarVariosBin(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista,int hasta,bool fijar, CONFIGURACAO &C)
{
	bool una_distinta=false;
	
//	m_total_volumen_ocupado=0;
	std::list<CONFIGURACAO> ::iterator it;
	MinimaDimensionMCMov();
	std::list<CONFIGURACAO> lista_configuracaos;
	std::list<SPACE> lista_espacios;
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
		SPACE SpaceElegido(0,0,0,m_X,m_Y,m_Z,this);
	lista_espacios.push_back(Space);
	bool primera=true;
	int temp=m_total_volumen_ocupado;
	while (m_total_volumen_ocupado!=m_total_volumen)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		bool posible=false;
		ElegirSpaceMovimiento(SpaceElegido,lista_espacios,posible);


		if (lista_espacios.size()==0 || posible==false )
		
		{
			if (m_total_volumen_ocupado!=m_total_volumen)
			{
				int thisbin=m_total_volumen_ocupado-temp;
				temp=m_total_volumen_ocupado;
				//empiezo otro bin
				SpaceElegido=Space;
				std::list< SPACE> otro_bin;
				otro_bin.push_back(Space);
				lista_espacios=otro_bin;
				std::pair< int, std::list< CONFIGURACAO > > p(thisbin,lista_configuracaos);
				//meto las configuracaos en la lista
				InsertarOrden(lista,p);
				//borro la lista actual de configuracaos
				lista_configuracaos.clear();
				if (lista.size()==hasta)
					return;
			}
			else return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);
		//Por si fijamos alguna pieza
		if (fijar==true)
		{
			fijar=false;
			Configuracao=C;
			lista_configuracaos.push_back(C);
		}
		else
		//Elegir configuración para ese espacio
		ElegirConfiguracaoMov(SpaceElegido,Configuracao,lista_configuracaos);

		if (Configuracao.Get_Id()==99999)
		{
			
			SpaceElegido.Set_Flag(true);
			std::list<SPACE> ::iterator itL1;
			for (itL1=lista_espacios.begin();itL1!=lista_espacios.end();itL1++)
			{
				if (((*itL1).Get_x1()==SpaceElegido.Get_x1()) &&
					((*itL1).Get_x2()==SpaceElegido.Get_x2()) &&
					((*itL1).Get_y1()==SpaceElegido.Get_y1()) &&
					((*itL1).Get_y2()==SpaceElegido.Get_y2()) &&
					((*itL1).Get_z1()==SpaceElegido.Get_z1()) &&
					((*itL1).Get_z2()==SpaceElegido.Get_z2()) )
				{
					(*itL1).Set_Flag(true);
					
				}
			}
			continue;

		}
//				if (m_iter_actual==673)	printf("H");
//				if (m_iter_actual==673)	printf("h4-,%d",SpaceElegido.Get_x1());
		ActualizarListasMov(SpaceElegido,Configuracao,lista_espacios);
//				if (m_iter_actual==673)	printf("h8");
	}
	int thisbin=m_total_volumen_ocupado-temp;

	std::pair< int, std::list< CONFIGURACAO > > p(thisbin,lista_configuracaos);
	//meto las configuracaos en la lista
	InsertarOrden(lista,p);

//	m_ConfiguracaosMC.push_back(p);


//	VerificarSolucion(m_Configuracaos);

}
//


//******************esta es una funcion en la que voy a rellenar pero de manera conjunta

void CONTAINER::RellenarVariosBinGlobal(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista)
{
//	printf("\n");
	bool una_distinta=false;
	
//	m_total_volumen_ocupado=0;

	std::list< std::pair< int , std::list<CONFIGURACAO> > > ::iterator itC;
	std::list< std::list<SPACE> > ::iterator itS;
	int colocado=lista.size();
	MinimaDimensionMCMov();
	std::list<CONFIGURACAO> lista_configuracaos;
	std::list<SPACE> lista_espacios;
	//Inicialmente meto un espacio que es todo el contenedor
	//Aqui tengo que poner tantos bins como la funcion objetivo menos
	m_SpacesMC.clear();
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
	lista_espacios.push_back(Space);
	for (int k=colocado;k<(m_Best_nbins-1);k++)
		m_SpacesMC.push_back(lista_espacios);
	for (int k=colocado;k<(m_Best_nbins-1);k++)
	{
		std::pair<int, std::list<CONFIGURACAO> > p(0,lista_configuracaos);
		lista.push_back(p);
	}
	bool primera=true;
	int temp=m_total_volumen_ocupado;
	while (m_total_volumen_ocupado!=m_total_volumen && m_SpacesMC.size()!=0)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		std::list<SPACE> ::iterator it;
		int EnqueBin=0;
		SPACE &SpaceElegido=ElegirSpaceMovimientoGlobal(m_SpacesMC,EnqueBin);
//		printf("%d",EnqueBin);
		if (EnqueBin==999999)
		{ 
			//Actualizo los valores de las piezas
			std::list< CONFIGURACAO > ::iterator it2;
			for (itC=lista.begin();itC!=lista.end();itC++)
			{
				if ((*itC).first==0)
				{
					int thisbin=0;
					for (it2=(*itC).second.begin();it2!=(*itC).second.end();it2++)
					{
						thisbin+=(*it2).Get_Volumen();
					}
					(*itC).first=thisbin;

				}
			}
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Por si podemos poner mas piezas que esas

		//Elegir configuración para ese espacio
		int cont=0;
		for (itC=lista.begin();itC!=lista.end() && cont<=(EnqueBin+colocado);itC++,cont++)
		{
			if (cont==(EnqueBin+colocado))
			{	
				ElegirConfiguracaoMov(SpaceElegido,Configuracao,(*itC).second);
//				if (Configuracao.Get_Id()!=99999)
//				{
/*					printf("colocado %d Espacio %d Meto en Bin %d\n",colocado,EnqueBin,cont);
					printf("Esp x1 %d y1 %d z1 %d x2 %d y2 %d z2 %d \n",
						SpaceElegido.Get_x1(),SpaceElegido.Get_y1(),SpaceElegido.Get_z1(),
						SpaceElegido.Get_x2(),SpaceElegido.Get_y2(),SpaceElegido.Get_z2());

					printf("Con x1 %d y1 %d z1 %d x2 %d y2 %d z2 %d \n",
						Configuracao.Get_x1(),Configuracao.Get_y1(),Configuracao.Get_z1(),
						Configuracao.Get_x2(),Configuracao.Get_y2(),Configuracao.Get_z2());
					ComprobarConfiguracaosNoIntersectan((*itC).second);
				}*/
			}
		}
		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}
		cont=0;
		for (itS=m_SpacesMC.begin();itS!=m_SpacesMC.end() && cont<=EnqueBin;itS++,cont++)
		{
			if (cont==EnqueBin)
			ActualizarListasMov(SpaceElegido,Configuracao,(*itS));
		}
	
	}
	 std::list<CONFIGURACAO>  ::iterator  it;
	//Hay que recorrer la lista para poner los tamanos de los bin 
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
		if ((*itC).first==0)
		{
			int thisbin=0;
			for (it=(*itC).second.begin();it!=(*itC).second.end();it++)
			{
				thisbin+=(*it).Get_Volumen();
			}
			(*itC).first=thisbin;

		}
	}
//	m_ConfiguracaosMC.push_back(p);


//	VerificarSolucion(m_Configuracaos);

}
/*
void CONTAINER::RellenarVariosBinGlobal()
{
//	printf("\n");
	bool una_distinta=false;
	
//	m_total_volumen_ocupado=0;
	std::list<CONFIGURACAO> ::iterator it;
	std::list< std::pair< int , std::list<CONFIGURACAO> > > ::iterator itC;
	std::list< std::list<SPACE> > ::iterator itS;
	int colocado=0;
	MinimaDimensionMCMov();
	std::list<CONFIGURACAO> lista_configuracaos;
	std::list<SPACE> lista_espacios;
	//Inicialmente meto un espacio que es todo el contenedor
	//Aqui tengo que poner tantos bins como la funcion objetivo menos
	m_SpacesMC.clear();
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
	lista_espacios.push_back(Space);
	for (int k=colocado;k<(m_Best_nbins-1);k++)
		m_SpacesMC.push_back(lista_espacios);
	bool primera=true;
	int temp=m_total_volumen_ocupado;
	while (m_total_volumen_ocupado!=m_total_volumen && m_SpacesMC.size()!=0)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		std::list<SPACE> ::iterator it;
		int EnqueBin=0;
		SPACE &SpaceElegido=ElegirSpaceMovimientoGlobal(m_SpacesMC,EnqueBin);
//		printf("%d",EnqueBin);
		if (EnqueBin==999999)
		{ 
			//Actualizo los valores de las piezas
			std::list< CONFIGURACAO > ::iterator it2;
			for (itC=lista.begin();itC!=lista.end();itC++)
			{
				if ((*itC).first==0)
				{
					int thisbin=0;
					for (it2=(*itC).second.begin();it2!=(*itC).second.end();it2++)
					{
						thisbin+=(*it2).Get_Volumen();
					}
					(*itC).first=thisbin;

				}
			}
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Por si podemos poner mas piezas que esas

		//Elegir configuración para ese espacio
		int cont=0;
		for (itC=lista.begin();itC!=lista.end() && cont<=(EnqueBin+colocado);itC++,cont++)
		{
			if (cont==(EnqueBin+colocado))
			{	
				ElegirConfiguracaoMov(SpaceElegido,Configuracao,(*itC).second);
//				if (Configuracao.Get_Id()!=99999)
//				{
			}
		}
		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}
		cont=0;
		for (itS=m_SpacesMC.begin();itS!=m_SpacesMC.end() && cont<=EnqueBin;itS++,cont++)
		{
			if (cont==EnqueBin)
			ActualizarListasMov(SpaceElegido,Configuracao,(*itS));
		}
	
	}
	//Hay que recorrer la lista para poner los tamanos de los bin 
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
		if ((*itC).first==0)
		{
			int thisbin=0;
			for (it=(*itC).second.begin();it!=(*itC).second.end();it++)
			{
				thisbin+=(*it).Get_Volumen();
			}
			(*itC).first=thisbin;

		}
	}
//	m_ConfiguracaosMC.push_back(p);


//	VerificarSolucion(m_Configuracaos);

}*/
void CONTAINER::ConstruirSolucionMovimientos(std::list<CONFIGURACAO> &lista,bool manera)
{
	bool una_distinta=false;
	m_total_volumen_ocupado=0;
	m_set_indices = m_set_indices_copia;
	m_Pieces_Tabu.clear();
	for (int j=0;j<m_Q;j++)
		m_Pieces_Tabu.push_back(0);
	bool m_eliminar_espacios_old=true;

	MinimaDimensionMov();
	std::list<CONFIGURACAO> lista_configuracaos;
	std::list<SPACE> lista_espacios;
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
	lista_espacios.push_back(Space);
	bool primera=true;
	int jjj = 0;
	while (lista_espacios.size()>0)
	{
		jjj++;
		
		bool elegir = false;
		bool poner = false;
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		std::list<SPACE> ::iterator it;
		SPACE& SpaceElegido = ElegirSpaceMovimiento(lista_espacios, lista);

		if (SpaceElegido.Get_Flag()==true)
		{
			if (lista.size()!=0)
			{

				printf("Que pasa");
				for (int inkki=0;;);
			}

			lista=lista_configuracaos;
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		//Creo ya inicialmente la configuracao 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Por si podemos poner mas piezas que esas
		if (m_all_bloques == true)
			m_por_bloques_ara = get_random(0, 1);
		//Elegir configuración para ese espacio
		//Poner configuracao y quitarla de la lista
		if (lista.size()==0)
		{
			if (m_por_bloques_ara == false)
				ElegirConfiguracaoMov(SpaceElegido, Configuracao, lista_configuracaos);
			else
			{
				ElegirConfiguracaoMovBloqueAra(SpaceElegido, Configuracao, lista_configuracaos);
				elegir = true;
			}
		}
		else
		{
			PonerConfiguracaoMov(SpaceElegido, Configuracao, lista_configuracaos, lista);
			poner = true;
		}

		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}
		if (poner == true && m_juntar_spaces == true)
		{
			m_eliminar_espacios_old = m_eliminar_espacios;
			m_eliminar_espacios = false;
		}
		if (m_por_bloques == false && (m_por_bloques_ara==false || (m_por_bloques_ara==true && elegir==false)))
			ActualizarListasMov(SpaceElegido, Configuracao, lista_espacios);
		else
		{
			if (m_por_bloques_ara == true)
				ActualizarListasAraMov(SpaceElegido, Configuracao, lista_espacios);
			else
			{
				if (Configuracao.Get_Id() < 1000)
					ActualizarListasMov(SpaceElegido, Configuracao, lista_espacios);
				else
				{
					ActualizarListasBloqueMov(SpaceElegido, Configuracao, lista_espacios, lista_configuracaos, poner);
					poner = false;
				}
			}
			if (ComprobarConfiguracaosNoIntersectan(lista_configuracaos))
				printf("3");
		}
		if (poner == true && m_juntar_spaces == true)
			m_eliminar_espacios = m_eliminar_espacios_old;
		/*DibujarOpenGL(lista_configuracaos);*/
		/*if (ComprobarFullSupport(lista_configuracaos) == false)
		{
			printf("aqui4");
			for (int i = 0;;);
		}*/
		if ((primera==true && lista.size()==0) || (m_full_supported==true && lista.size()!=0))
		{
			primera=false;
			std::list<SPACE> ::iterator itl;
			for (itl=lista_espacios.begin();itl!=lista_espacios.end();itl++)
			{
				(*itl).Set_Flag(false);
			}
		}
		/*ComprobarTodosPosible(lista);*/
	}

	lista=lista_configuracaos;

//	VerificarSolucion(m_Configuracaos);

}


//Esta funcion es la que devuelve la mejor configuración
//de las cajas en el espacio
void CONTAINER::ElegirConfiguracaoMov(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista)	
{
	if (m_tipo_mixto==true)
	{
		if (get_random(0,1)==1)
			m_objetivo_capas=true;
		else
			m_objetivo_capas=false;
	}
	if (m_objetivo_mixto == true)
	{
		if (get_random(0, 1) == 1)
			m_objetivo_vol = true;
		else
			m_objetivo_vol = false;
	}
	if (m_multicontainer!=true)
	{

		if (m_objetivo_capas==true)
		{
			if (m_por_bloques==true)
			{
				std::list< BLOQUE > ::iterator itb;
				for (itb = m_Bloques.begin(); itb != m_Bloques.end(); itb++)
				{
					if ((*itb).Get_Num1() <= m_Pieces[(*itb).Get_Id1()].Get_q() - m_Pieces_Tabu[(*itb).Get_Id1()] && (*itb).Get_Num2() <= m_Pieces[(*itb).Get_Id2()].Get_q() - m_Pieces_Tabu[(*itb).Get_Id2()])
						Configuracao.MejorCapaDeUnaBloqueMov(Espacio, (*itb));

				}
			}
			for (int imc=0;imc<m_Q;imc++)
			{	
			
				if (m_Pieces_Tabu[imc]<m_Pieces[imc].Get_q())
				Configuracao.MejorCapaDeUnaPiezaMov(Espacio,m_Pieces[imc]);
			}
		}
		else
		{
			for (int imc=0;imc<m_Q;imc++)
			{	
			
				if (m_Pieces_Tabu[imc] < m_Pieces[imc].Get_q())
				{
					//Cambiar para que vaya con columnas
					Configuracao.MejorColumnaDeUnaPiezaMov(Espacio, m_Pieces[imc]);
				}
			}

		}
	}
	else
	{

		for (int imc=0;imc<m_Q;imc++)
		{	
			
			if (m_Pieces_Tabu[imc]<m_Pieces[imc].Get_q())
			{
//				Configuracao.MejorPiezaMov(Espacio,m_Pieces[imc]);
				Configuracao.CompararConCapas(1,Espacio,m_Pieces[imc].Get_x(),m_Pieces[imc].Get_y(),m_Pieces[imc].Get_z(),m_Pieces[imc].Get_Id(),(m_Pieces[imc].Get_q()-m_Pieces_Tabu[imc]));

			}
			//cambio
			if (m_objetivo_vol==true && Configuracao.Get_Id()!=99999) break;
		}
	}

	if (Configuracao.Get_Id() != 99999 && Configuracao.Get_Id() < 1000)
	{
		/*lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista);
		//		m_total_volumen_ocupado+=Configuracao.Get_Volumen();
	}
	//if (Configuracao.Get_Id())
	//	printf("aquiii");

}
void CONTAINER::ElegirConfiguracaoMovBloqueAra(SPACE& Espacio, CONFIGURACAO& Configuracao, std::list<CONFIGURACAO>& lista_configuracaos)
{
	//std::set<BLOQUE_ARA*, compareBlocks>::iterator it, itfin = m_set_Bloques.end();
	bool perdida;
	int pack_area_x = 0, pack_area_z = 0;
	ORIG m_set_distancias;
	int numActual=0;
	bool primero = true;
	int cont = 0;
	int kkk = 0;
	int jjj = 0;
	int max_iter = Max_Iter_VCS;//150;
	int contador = 0;
	if (m_objetivo_mixto == true)
	{
		if (get_random(0, 1) == 1)
			m_objetivo_vol = true;
		else
			m_objetivo_vol = false;
	}
	m_boolrand = false;
	std::set<BLOQUE_ARA*, compareBlocks>::iterator it = find_if(m_set_Bloques.begin(), m_set_Bloques.end(), buscar_por_volumen_mov(Espacio, m_Pieces_Tabu, m_Pieces, m_all_bloques));
	if (it == m_set_Bloques.end() && m_Random == true)
	{
		it = find_if(m_set_Bloques.begin(), m_set_Bloques.end(), buscar_por_volumen_mov(Espacio, m_Pieces_Tabu, m_Pieces, m_all_bloques));
		if (it == m_set_Bloques.end())
			return;
	}
	else if (it == m_set_Bloques.end() && m_Random == false)
		return;
	
	int x1=0, y1=0, z1=0;
	int cont_temp = 0;
	if (m_VCS == true && m_Random==false/* && m_objetivo_vol==true*/)
	{
		
		double VCS = 0;
		double VCS_temp = 0;
		std::set<BLOQUE_ARA*, compareBlocks>::iterator it2;
		for (it2 = it; it2 != m_set_Bloques.end() && contador < max_iter; it2++)
		{
			if (!(Espacio.Get_x2() - Espacio.Get_x1() >= (**it2).Get_x() && Espacio.Get_y2() - Espacio.Get_y1() >= (**it2).Get_y() && Espacio.Get_z2() - Espacio.Get_z1() >= (**it2).Get_z()))
				continue;
			std::map<int, int>::iterator itm, itmfin = (**it2).Get_num_pieces_tipo().end();
			bool puede = false;
			for (itm = ((**it2).Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
			{
				puede = (m_Pieces[itm->first].Get_q() - m_Pieces_Tabu[itm->first] >= itm->second);
				if (puede == false)
					break;
			}
			if (puede == false)
				continue;
			contador++;
			switch (Espacio.Get_origen_distancia())
			{
			case 1: //(0,0,0)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z1();
				break;
			case 2: //(0,Y,0)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y2() - (**it2).Get_y();
				z1 = Espacio.Get_z1();
				break;
			case 3: //(0,0,Z)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z2() - (**it2).Get_z();
				break;
			case 4: //(0,Y,Z)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y2() - (**it2).Get_y();
				z1 = Espacio.Get_z2() - (**it2).Get_z();
				break;
			case 5: //(X,0,0)
				x1 = Espacio.Get_x2() - (**it2).Get_x();
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z1();
				break;
			case 6: //(X,Y,0)
				x1 = Espacio.Get_x2() - (**it2).Get_x();
				y1 = Espacio.Get_y2() - (**it2).Get_y();
				z1 = Espacio.Get_z1();
				break;
			case 7: //(X,0,Z)
				x1 = Espacio.Get_x2() - (**it2).Get_x();
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z2() - (**it2).Get_z();
				break;
			case 8: //(X,Y,Z)
				x1 = Espacio.Get_x2() - (**it2).Get_x();
				y1 = Espacio.Get_y2() - (**it2).Get_y();
				z1 = Espacio.Get_z2() - (**it2).Get_z();
				break;
			}
			if (primero == true)
			{
				primero = false;
				it = it2;
				VCS = VCS_Bloque(&lista_configuracaos, **it2, Espacio, x1, y1, z1);
				continue;
			}
			VCS_temp = VCS_Bloque(&lista_configuracaos, **it2, Espacio, x1, y1, z1);
			if (VCS_temp > VCS)
			{
				it = it2;
				cont_temp = contador;
				if (cont_temp > 140)
					int kk = 8;
				VCS = VCS_temp;
			}
		}
	}
	else if (m_objetivo_vol == false && m_Random == false)
	{
		/*std::set<BLOQUE_ARA*> bloques_fit;
		bloques_fit.insert(it, m_set_Bloques.end());*/
		std::set<BLOQUE_ARA*, compareBlocks>::iterator it2;
		for (it2 = it; it2 != m_set_Bloques.end() && contador < max_iter; it2++)
		{
			if (!(Espacio.Get_x2() - Espacio.Get_x1() >= (**it2).Get_x() && Espacio.Get_y2() - Espacio.Get_y1() >= (**it2).Get_y() && Espacio.Get_z2() - Espacio.Get_z1() >= (**it2).Get_z()))
				continue;
			std::map<int, int>::iterator itm, itmfin = (**it2).Get_num_pieces_tipo().end();
			bool puede = false;
			for (itm = ((**it2).Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
			{
				puede = (m_Pieces[itm->first].Get_q() - m_Pieces_Tabu[itm->first] >= itm->second);
				if (puede == false)
					break;
			}
			if (puede == false)
				continue;
			contador++;
			kkk++;
			ORIG OrigActual(Espacio.Get_dx() - (**it2).Get_x(), Espacio.Get_dy() - (**it2).Get_y(), Espacio.Get_dz() - (**it2).Get_z());
			if (primero==true)
			{
				primero = false;
				m_set_distancias = OrigActual;
				numActual = (**it2).Get_Num();
				it = it2;
				if (m_set_distancias.GetPrimero() == 0 && m_set_distancias.GetPrimero() == 0 && m_set_distancias.GetPrimero() == 0)
					break;
				continue;
			}
			if (Mejor_DistA_Que_DistB_Bloques(m_set_distancias, (**it2).Get_Num(), OrigActual, numActual, (**it2).Get_Volumen()) == false)
			{
				m_set_distancias = OrigActual;
				numActual = (**it2).Get_Num();
				it = it2;
				jjj = kkk;
				if (m_set_distancias.GetPrimero() == 0 && m_set_distancias.GetPrimero() == 0 && m_set_distancias.GetPrimero() == 0)
					break;
			}

		}
		/*printf("%d\t%d\n", kkk, jjj);*/
		if (primero == true)
			printf("mal1");
	}
	if (m_full_supported == true)
		m_space_arriba = false;
	// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z)
	switch (Espacio.Get_origen_distancia())
	{
	case 1: //(0,0,0)
		x1 = Espacio.Get_x1();
		y1 = Espacio.Get_y1();
		z1 = Espacio.Get_z1();
		break;
	case 2: //(0,Y,0)
		x1 = Espacio.Get_x1();
		y1 = Espacio.Get_y2() - (**it).Get_y();
		z1 = Espacio.Get_z1();
		break;
	case 3: //(0,0,Z)
		x1 = Espacio.Get_x1();
		y1 = Espacio.Get_y1();
		z1 = Espacio.Get_z2() - (**it).Get_z();
		break;
	case 4: //(0,Y,Z)
		x1 = Espacio.Get_x1();
		y1 = Espacio.Get_y2() - (**it).Get_y();
		z1 = Espacio.Get_z2() - (**it).Get_z();
		break;
	case 5: //(X,0,0)
		x1 = Espacio.Get_x2() - (**it).Get_x();
		y1 = Espacio.Get_y1();
		z1 = Espacio.Get_z1();
		break;
	case 6: //(X,Y,0)
		x1 = Espacio.Get_x2() - (**it).Get_x();
		y1 = Espacio.Get_y2() - (**it).Get_y();
		z1 = Espacio.Get_z1();
		break;
	case 7: //(X,0,Z)
		x1 = Espacio.Get_x2() - (**it).Get_x();
		y1 = Espacio.Get_y1();
		z1 = Espacio.Get_z2() - (**it).Get_z();
		break;
	case 8: //(X,Y,Z)
		x1 = Espacio.Get_x2() - (**it).Get_x();
		y1 = Espacio.Get_y2() - (**it).Get_y();
		z1 = Espacio.Get_z2() - (**it).Get_z();
		break;
	}
	Configuracao.PonerMedidas1(x1, y1, z1, (**it).Get_x(), (**it).Get_y(), (**it).Get_z());
	Configuracao.Set_orig(Espacio.Get_origen_distancia());
	Configuracao.Set_Id((**it).Get_Id());
	Configuracao.Set_bloque(true);
	m_blo_pos++;
	ColocarPiezasBloque(x1, y1, z1, 0, 0, 0, **it, lista_configuracaos, Espacio.Get_origen_distancia());
//	printf("\n num %d", cont_temp);
}
void CONTAINER::ElegirConfiguracaoMovBloque(SPACE &Espacio, CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista)
{
	if (m_Aleatorizado == true)
	{
		m_TamRCL = Estimacion(Espacio);
		if (m_TamRCL == 0)
			return;
		//Tamaño de la lista de posibles
//		printf("Tam RCL %d %f %f",m_TamRCL,m_Delta,m_TamRCL*m_Delta);

		m_TamRCL = ceil((double)m_TamRCL*m_Delta);
		//		printf("Tam RCL %d ",m_TamRCL);

	}
	if (m_tipo_mixto == true)
	{
		if (get_random(0, 1) == 1)
			m_objetivo_capas = true;
		else
			m_objetivo_capas = false;
	}
	if (m_objetivo_capas == true)
	{
		//		if (m_Aleatorizado==false)
		//		{
			std::list< BLOQUE > ::iterator itb;
			for (itb = m_Bloques.begin(); itb != m_Bloques.end(); itb++)
			{
				if ((*itb).Get_Num1() <= m_Pieces[(*itb).Get_Id1()].Get_q() - m_Pieces_Tabu[(*itb).Get_Id1()] && (*itb).Get_Num2() <= m_Pieces[(*itb).Get_Id2()].Get_q() - m_Pieces_Tabu[(*itb).Get_Id2()])
				    Configuracao.MejorCapaDeUnaBloqueMov(Espacio, (*itb));

			}

		//		}
		for (int imc = 0; imc < m_Q; imc++)
		{

			if (m_Pieces_Tabu[imc] < m_Pieces[imc].Get_q())
				Configuracao.MejorCapaDeUnaPiezaMov(Espacio, m_Pieces[imc]);
			//			if (Configuracao.Get_Id()!=99999 && m_objetivo_vol==true && m_Aleatorizado==false)
			//				break;
			//			if (m_objetivo_vol==true && m_Aleatorizado==true && m_ListaRCL.size()==m_TamRCL)
			//				break;
		}
		//		if (m_full_supported==true && m_Aleatorizado==false)
	}
	else
	{
		for (int imc = 0; imc < m_Q; imc++)
		{

			if (m_Pieces_Tabu[imc] < m_Pieces[imc].Get_q())
				//Cambiar para que vaya con columnas
				Configuracao.MejorColumnaDeUnaPiezaMov(Espacio, m_Pieces[imc]);
		}

	}
	//Si es aleatorizado ya tengo todos ahora tengo que elegir uno
	//if (m_Aleatorizado == true)
	//{
	//	//Elegir uno al azar 
	//	//Puede ser que la estimacion sea por encima y luego no pueda
	//	//colocar tantas por esto
	//	int alea = get_random(0, min(m_TamRCL - 1, m_ListaRCL.size() - 1));
	//	int cont = 0;
	//	std::list < CONFIGURACAO > ::iterator it;
	//	for (it = m_ListaRCL.begin(); it != m_ListaRCL.end(); it++)
	//	{
	//		if (alea == cont)
	//		{
	//			//si es un bloque mas tarde lo voy a meter
	//			if ((*it).Get_Id() < 1000)
	//				m_Configuracaos.push_back((*it));

	//			//				m_total_volumen_ocupado+=(*it).Get_Volumen();
	//			Configuracao = (*it);
	//			m_ListaRCL.clear();
	//			return;
	//		}

	//		cont++;

	//	}
	//}
	if (Configuracao.Get_Id() != 99999)
	{
		if (Configuracao.Get_Id() < 1000)
			InsertarConfiguracaoOrden(Configuracao, lista);
			/*lista.push_back(Configuracao);*/

		//		InsertarOrden(m_Configuracaos,Configuracao);


		/*		else
				{
					std::list < BLOQUE > ::iterator itb;
					CONFIGURACAO Configuracao1(this,Configuracao.Get_x1(),Configuracao.Get_y1(),Configuracao.Get_z1(),
						Configuracaos.Get_x1()+m_Pieces[Configuracao.Get_Id()].Get_x(),
						Configuracaos.Get_y1()+m_Pieces[Configuracao.Get_Id()].Get_y(),
						Configuracaos.Get_z1()+m_Pieces[Configuracao.Get_Id()].Get_z(),
						Configuracao.Get_Tipo(),1);

					CONFIGURACAO Configuracao2(this,Configuracao.Get_x2(),Configuracao.Get_y2(),Configuracao.Get_z2(),
						Configuracaos.Get_x1()+m_Pieces[Configuracao.Get_Id()].Get_x(),
						Configuracaos.Get_y1()+m_Pieces[Configuracao.Get_Id()].Get_y(),
						Configuracaos.Get_z1()+m_Pieces[Configuracao.Get_Id()].Get_z(),
						Configuracao.Get_Tipo(),1);
					CONFIGURACAO Configuracao2(this, Espacio.Get_Id(),Espacio.Get_x1(),Espacio.Get_y1(),Espacio.Get_z1(),x1+x2-x1,y2+(E.Get_y2()-y2),E.Get_z1()+dimz  ,E.Get_Tipo(),0);

				}*/
				//		m_Configuracaos.push_back(Configuracao);
				//		m_total_volumen_ocupado+=Configuracao.Get_Volumen();
	}

}

//Esta funcion es la que devuelve la mejor configuración
//de las cajas en el espacio
void CONTAINER::ElegirConfiguracaoMovDistinta(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista)	
{
	if (m_tipo_mixto==true)
	{
		if (get_random(0,1)==1)
			m_objetivo_capas=true;
		else
			m_objetivo_capas=false;
	}
	if (m_objetivo_capas==true)
	{
		for (int imc=0;imc<m_Q;imc++)
		{	
			//solamente cambia esto que mete una que no estaba
			//pero en principio puede meter la misma pieza si era una copia
			if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
			Configuracao.MejorCapaDeUnaPiezaMov(Espacio,m_Pieces[imc]);
		}
	}
	else
	{
		for (int imc=0;imc<m_Q;imc++)
		{	
			
			if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
				//Cambiar para que vaya con columnas
			Configuracao.MejorColumnaDeUnaPiezaMov(Espacio,m_Pieces[imc]);
		}

	}

	if (Configuracao.Get_Id()!=99999)
	{
		/*lista.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, lista);
//		m_total_volumen_ocupado+=Configuracao.Get_Volumen();
	}

}

//Esta funcion es la que pone la configuracao donde toque
void CONTAINER::PonerConfiguracaoMov(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista_Con,std::list<CONFIGURACAO> &lista)	
{
	std::list<CONFIGURACAO> ::iterator it,itfin=lista.end();
	//Tengo que bucar una configuracao que tenga de vertice el mismo que el space
	bool fin=false;
	bool primero = true;
	//bool haybloques = false;
	//for (it = lista.begin(); it != itfin && haybloques == false; it++)
	//{
	//	if ((*it).Get_Id_bloque() > 0)
	//		haybloques = true;
	//}
	for (it=lista.begin();it!=itfin && fin!=true && primero == true;)
	{
		if (m_juntar_spaces==true)
			primero = false;
		if ((Espacio.Get_x2() >= (*it).Get_x2() &&
			Espacio.Get_y2() >= (*it).Get_y2() &&
			Espacio.Get_z2() >= (*it).Get_z2() &&
			Espacio.Get_x1() <= (*it).Get_x1() &&
			Espacio.Get_y1() <= (*it).Get_y1() &&
			Espacio.Get_z1() <= (*it).Get_z1()))
			{
				Configuracao = (*it);
				/*lista_Con.push_back((*it));*/
				InsertarConfiguracaoOrden(*it, lista_Con);
				it = lista.erase(it);
				fin = true;
			}
		else
			++it;
	}
}
void CONTAINER::PonerConfiguracaoMovBloque(SPACE &Espacio, CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, bool compactada)
{
	std::list<CONFIGURACAO> ::iterator it, itfin = lista.end();
	//Tengo que bucar una configuracao que tenga de vertice el mismo que el space
	bool fin = false;
	for (it = lista.begin(); it != itfin && fin != true;)
	{
		//Me vale cualquiera de los que tengo o mejor
		//lo busco para el que me haya dicho el 
		if (compactada == false)
		{
			switch (Espacio.Get_origen_distancia())
			{
			case 1:
			{
				if (Espacio.Get_x1() == (*it).Get_x1() &&
					Espacio.Get_y1() == (*it).Get_y1() &&
					Espacio.Get_z1() == (*it).Get_z1())
				{
					Configuracao = (*it);
					/*m_Configuracaos.push_back((*it));*/
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					it = lista.erase(it);
					fin = true;

				}
				else
					++it;

			}
			break;
			case  2:
			{
				if (Espacio.Get_x1() == (*it).Get_x1() &&
					Espacio.Get_y2() == (*it).Get_y2() &&
					Espacio.Get_z1() == (*it).Get_z1())
				{
					Configuracao = (*it);
					/*m_Configuracaos.push_back((*it));*/
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					fin = true;

					it = lista.erase(it);

				}
				else
					++it;
			}
			break;
			case 3:
			{
				if (Espacio.Get_x1() == (*it).Get_x1() &&
					Espacio.Get_y1() == (*it).Get_y1() &&
					Espacio.Get_z2() == (*it).Get_z2())
				{
					Configuracao = (*it);
					/*m_Configuracaos.push_back((*it));*/
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					fin = true;

					it = lista.erase(it);

				}
				else
					++it;
			}
			break;
			case  4:
			{
				if (Espacio.Get_x1() == (*it).Get_x1() &&
					Espacio.Get_y2() == (*it).Get_y2() &&
					Espacio.Get_z2() == (*it).Get_z2())
				{
					Configuracao = (*it);
					/*m_Configuracaos.push_back((*it));*/
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					fin = true;
					it = lista.erase(it);

				}
				else
					++it;
			}
			break;
			case  5:
			{
				if (Espacio.Get_x2() == (*it).Get_x2() &&
					Espacio.Get_y1() == (*it).Get_y1() &&
					Espacio.Get_z1() == (*it).Get_z1())

				{
					Configuracao = (*it);
					/*m_Configuracaos.push_back((*it));*/
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					fin = true;
					it = lista.erase(it);

				}
				else
					++it;
			}
			break;
			case  6:
			{
				if (Espacio.Get_x2() == (*it).Get_x2() &&
					Espacio.Get_y2() == (*it).Get_y2() &&
					Espacio.Get_z1() == (*it).Get_z1())

				{
					Configuracao = (*it);
				/*	m_Configuracaos.push_back((*it));*/
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					fin = true;
					it = lista.erase(it);

				}
				else
					++it;
			}
			break;
			case  7:
			{
				if (Espacio.Get_x2() == (*it).Get_x2() &&
					Espacio.Get_y1() == (*it).Get_y1() &&
					Espacio.Get_z2() == (*it).Get_z2())

				{
					Configuracao = (*it);
					/*m_Configuracaos.push_back((*it));*/
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					fin = true;
					it = lista.erase(it);

				}
				else
					++it;
			}
			break;
			case  8:
			{
				if (Espacio.Get_x2() == (*it).Get_x2() &&
					Espacio.Get_y2() == (*it).Get_y2() &&
					Espacio.Get_z2() == (*it).Get_z2())
				{
					Configuracao = (*it);
					/*m_Configuracaos.push_back((*it));*/
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					fin = true;
					it = lista.erase(it);

				}
				else
					++it;
			}
			break;

			}
		}

		else
		{
			if ((Espacio.Get_x1() == (*it).Get_x1() &&
				Espacio.Get_y1() == (*it).Get_y1() &&
				Espacio.Get_z1() == (*it).Get_z1()) ||
				(Espacio.Get_x1() == (*it).Get_x1() &&
					Espacio.Get_y2() == (*it).Get_y2() &&
					Espacio.Get_z1() == (*it).Get_z1()) ||
					(Espacio.Get_x1() == (*it).Get_x1() &&
						Espacio.Get_y1() == (*it).Get_y1() &&
						Espacio.Get_z2() == (*it).Get_z2()) ||
						(Espacio.Get_x1() == (*it).Get_x1() &&
							Espacio.Get_y2() == (*it).Get_y2() &&
							Espacio.Get_z2() == (*it).Get_z2()) ||
							(Espacio.Get_x2() == (*it).Get_x2() &&
								Espacio.Get_y1() == (*it).Get_y1() &&
								Espacio.Get_z1() == (*it).Get_z1()) ||
								(Espacio.Get_x2() == (*it).Get_x2() &&
									Espacio.Get_y2() == (*it).Get_y2() &&
									Espacio.Get_z1() == (*it).Get_z1()) ||
									(Espacio.Get_x2() == (*it).Get_x2() &&
										Espacio.Get_y1() == (*it).Get_y1() &&
										Espacio.Get_z2() == (*it).Get_z2()) ||
										(Espacio.Get_x2() == (*it).Get_x2() &&
											Espacio.Get_y2() == (*it).Get_y2() &&
											Espacio.Get_z2() == (*it).Get_z2()) ||
											(Espacio.Get_x2() >= (*it).Get_x2() &&
												Espacio.Get_y2() >= (*it).Get_y2() &&
												Espacio.Get_z2() >= (*it).Get_z2() &&
												Espacio.Get_x1() <= (*it).Get_x1() &&
												Espacio.Get_y1() <= (*it).Get_y1() &&
												Espacio.Get_z1() <= (*it).Get_z1()))
			{
				Configuracao = (*it);
				/*m_Configuracaos.push_back((*it));*/
				InsertarConfiguracaoOrden(*it, m_Configuracaos);
				it = lista.erase(it);
				fin = true;

			}
			else
				++it;

		}

	}

}
void CONTAINER::EliminarMasDe100Espacios(std::list<SPACE> &lista_espacios)
{
	int tam=lista_espacios.size();
	if (tam<=100)
		return;
	int cont=0;
	std::list< SPACE > ::iterator it;

	for (it=lista_espacios.begin();it!=lista_espacios.end() && cont<(tam-100);)
	{
		cont++;
		it=lista_espacios.erase(it);
		

		
	}
}
void CONTAINER::ActualizarListasMov(SPACE &EspacioT, CONFIGURACAO &Configuracao,std::list<SPACE> &lista_espacios)
{
	//Primero actualizo el numero que  a su vez actualiza el flag
	m_Pieces_Tabu[Configuracao.Get_Id()]+=Configuracao.Get_Num();
	m_total_volumen_ocupado+=Configuracao.Get_Volumen();
	std::list< SPACE > ::iterator it;
	//
	bool quitar_piezas=false;
	if (m_multicontainer==false && m_por_bin == false)
	{

		if (m_Pieces_Tabu[Configuracao.Get_Id()]==m_Pieces[Configuracao.Get_Id()].Get_q() &&
		(m_Pieces[Configuracao.Get_Id()].Get_x()==m_dimension_menor||m_Pieces[Configuracao.Get_Id()].Get_y()==m_dimension_menor ||m_Pieces[Configuracao.Get_Id()].Get_z()==m_dimension_menor))	
		{
			MinimaDimensionMov();
			quitar_piezas=true;
		}
	}
	else
	{

	//si he quitado una tipo de pieza
		if (m_Pieces_Tabu[Configuracao.Get_Id()]==m_Pieces[Configuracao.Get_Id()].Get_q() &&
		(m_Pieces[Configuracao.Get_Id()].Get_x()==m_dimension_menor_x||m_Pieces[Configuracao.Get_Id()].Get_y()==m_dimension_menor_y ||m_Pieces[Configuracao.Get_Id()].Get_z()==m_dimension_menor_z))	
		{
			MinimaDimensionMCMov();
			quitar_piezas=true;
		}


	}

	//Ahora tengo que meter los nuevos espacios producidos por la configuracao 
	//ademas los tengo que meter en orden porque despues estarán ordenados y es ir colocandolos en le lugar correspondiente
	std::list< SPACE > lista_temp;	
	if (m_multicontainer == false && m_por_bin == false)
		ActualizarEspaciosElegidoMov(EspacioT, Configuracao, lista_temp, lista_espacios);
	else
	    ActualizarEspaciosElegidoMC(EspacioT,Configuracao,lista_temp);
//	if (m_iter_actual==618)	printf("hh2-,%d",Configuracao.Get_Id());
	if (m_juntar_spaces == true)
		JuntarSpacesBloques(lista_espacios, lista_temp, Configuracao);

//Eliminar este espacio
	//FALTA 
	for (it = lista_espacios.begin();it!=lista_espacios.end();it++)
	{
		if ((*it).Get_x1()==EspacioT.Get_x1() && (*it).Get_x2()==EspacioT.Get_x2() &&
			(*it).Get_y1()==EspacioT.Get_y1() && (*it).Get_y2()==EspacioT.Get_y2() &&
			(*it).Get_z1()==EspacioT.Get_z1() && (*it).Get_z2()==EspacioT.Get_z2() )
		{
			lista_espacios.erase(it);
			break;
		}
	}



	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin=lista_espacios.end();
	for (it = lista_espacios.begin();it!=lista_espacios.end();)
	{
		//Si se intersectan hacer los espacios
//			SPACE kk=(*it);
//		if ((*it).Get_Flag()==true) continue;
		if (!(Configuracao.Get_x2() <= (*it).Get_x1() ||  Configuracao.Get_x1() >= (*it).Get_x2())
			&& !(Configuracao.Get_y2() <= (*it).Get_y1() ||  Configuracao.Get_y1() >= (*it).Get_y2())
			&& !(Configuracao.Get_z2() <= (*it).Get_z1() ||  Configuracao.Get_z1() >= (*it).Get_z2()))
		{
			if (m_multicontainer == false && m_por_bin == false)
				ActualizarEspaciosElegidoMov((*it), Configuracao, lista_temp, lista_espacios);
			else
			    ActualizarEspaciosElegidoMC((*it),Configuracao,lista_temp);

			//Tengo que hacer el -- porque me apunta al siguiente
			it=lista_espacios.erase(it);
		}
		else
			++it;

	}
	if (m_juntar_spaces == true)
		JuntarSpacesBloques(lista_espacios, lista_temp, Configuracao);
//	if (quitar_piezas==true)
//	{
	/*quitar_piezas = false;*/
	if (m_multicontainer==false)
	{
		//Aqui pruebo si puede quitar alguno y es mas rapido
		if (m_eliminar_espacios==true && quitar_piezas==true && m_juntar_spaces == false )
		{
			std::list<SPACE> ::iterator itfin1=lista_espacios.end();
			for (it=lista_espacios.begin();it!=itfin1;)
			{
				if (((m_dimension_menor>min(min((*it).Get_x2()-(*it).Get_x1(),(*it).Get_y2()-(*it).Get_y1()),(*it).Get_z2()-(*it).Get_z1()))
					|| CabeAlgunaMov((*it).Get_x2()-(*it).Get_x1(),(*it).Get_y2()-(*it).Get_y1(),(*it).Get_z2()-(*it).Get_z1()) ==false))
				{
					it=lista_espacios.erase(it);

				}
				else
					++it;
			}
		}
	}
	else
	{
		std::list<SPACE> ::iterator itfin1=lista_espacios.end();
		for (it=lista_espacios.begin();it!=itfin1;)
		{
			if ((m_dimension_menor_x>(*it).Get_dx()) ||
				(m_dimension_menor_y>(*it).Get_dy()) ||
				(m_dimension_menor_z>(*it).Get_dz()) ||
				(m_menor_volumen>(*it).Get_Volumen()))
			{
				it=lista_espacios.erase(it);

			}
			else
				++it;
		}
	}
//	}

	//Buscar inclusiones pero solamente con  los nuevos entres ssi
	EliminarInclusionesNuevos(lista_temp);
	//Buscar inclusiones de los nuevos con los antiguos esta función me debería colocar ya las
	//nuevas ordenadas
	/*if (contador == 30)
		SetDibujar(false);*/
	EliminarInclusionesListaAntigua(lista_espacios,lista_temp);
	//Esta función incluye los nuevos en la lista 
	//15-09-06 
//	m_Spaces.insert(m_Spaces.begin(),lista_temp.begin(),lista_temp.end());
	ColocarOrdenadosNuevos(lista_espacios,lista_temp);
	/*ComprobarEspaciosNoIncluidos(lista_espacios);*/
	//int tam1 = lista_espacios.size();
	//PintarSpaces(lista_espacios);
	/*EliminarInclusionesNuevos(lista_espacios);*/ //Repaso si hay inclusiones porque EliminarInclusionesListaAntigua no parece que funcione bien
	//PintarSpaces(lista_espacios);
	//int tam2 = lista_espacios.size();
	//contador++;
	//if (tam1 != tam2)
	//	printf("%d", contador);
		/*printf("ah pajaro");*/

//	EliminarMasDe100Espacios(lista_espacios);
//	EliminarInclusiones();


}
/*
	std:multiset< int > ::iterator itm;
	for (itm=Best.Get_Val(),itm2=Best.Get_Val();itm!=Best.Get_Val().end() && itm2!=otro.Get_Val();itm++,itm2++)
	{
		if ((*itm)<(*itm2))
			return true;
*/
SPACE & CONTAINER::ElegirSpaceMovimientoGlobal(std::list< std::list<SPACE> > &lista,int &Dequebin)
{
	//Elige por el mas pequeno
/*	std::list<SPACE> ::iterator it,elegido;
	for (it=lista.begin();it!=lista.end();it++)
	{
//		SPACE kk=(*it);
		if ((*it).Get_Flag()==false)
		{
				return (*it);
		}
	}
	return (lista.front());
*/	std::list<SPACE> ::iterator it,elegido;
	bool quedan_todavia=false;
	bool primero=true;;
	//Los recorro todos comparando cual es el mejor
	std::list< std::list< SPACE > > ::iterator itC;
	int lugarS=0;
	for (itC=lista.begin(),lugarS;itC!=lista.end();itC++,lugarS++)
	{
		std::list< SPACE > ::iterator itfin=(*itC).end();
		for (it=(*itC).begin();it!=itfin;it++)
		{
//		SPACE kk=(*it);	
			if ((*it).Get_Flag()==false)
			{
				quedan_todavia=true;
				if (primero==true) 
				{
					elegido=it;
					primero=false;
					Dequebin=lugarS;


				}
				else
				{
					if (Mejor_DistA_Que_DistB((*elegido),(*it))==false)
					{
						elegido=it;
						Dequebin=lugarS;

					}
				}
			}
			//Funcion que me elimina los espacios 
			//si la quito todo funsiona igual 
		}

	}
	if (quedan_todavia==false || lista.size()==0) 
	{
		Dequebin=999999;
		return (lista.front()).front();
	}
	return (*elegido);

}
SPACE& CONTAINER::ElegirSpaceMovimiento(std::list<SPACE>& lista, std::list<CONFIGURACAO>& lista_conf)// , bool poner)
{
	//Elige por el mas pequeno
/*	std::list<SPACE> ::iterator it,elegido;
	for (it=lista.begin();it!=lista.end();it++)
	{
//		SPACE kk=(*it);
		if ((*it).Get_Flag()==false)
		{
				return (*it);
		}
	}
	return (lista.front());
*/	
	/*if (lista_conf.size() == 0)
	{*/
		std::list<SPACE> ::iterator it, elegido;
		bool quedan_todavia = false;
		bool primero = true;
		//Los recorro todos comparando cual es el mejor
		std::list< SPACE > ::iterator itfin = lista.end();
		for (it = lista.begin(); it != itfin; it++)
		{
			//		SPACE kk=(*it);
					/*if (poner == true)
					{*/
			if ((*it).Get_Flag() == false)
			{
				//			if (get_random(0,3)==2) return (*it);
				quedan_todavia = true;
				if (primero == true)
				{
					/*if (m_full_supported == true)
						return *it;*/
					elegido = it;
					primero = false;

				}
				else
				{
					if (m_full_supported == false)
					{
						if (Mejor_DistA_Que_DistB((*elegido), (*it)) == false)
						{
							elegido = it;
						}
					}
					else
					{
						if ((*it).Get_Volumen() < (*elegido).Get_Volumen())
							elegido = it;
						if ((*it).Get_Volumen() == (*elegido).Get_Volumen())
						{
							if (Mejor_DistA_Que_DistB((*elegido), (*it)) == false)
							{
								elegido = it;
							}
						}

					}
				}
			}
			//Funcion que me elimina los espacios 
			//si la quito todo funsiona igual 
		}
		if (quedan_todavia == false || lista.size() == 0)
		{

			return lista.front();
		}
		return (*elegido);
}
SPACE& CONTAINER::ElegirSpacePonerConfiguracaoMov(std::list<CONFIGURACAO>& lista_configuracaos, std::list<SPACE>& lista_espacios)
{
	std::list<CONFIGURACAO>::iterator C = lista_configuracaos.begin();
	std::list<SPACE>::iterator itS, itSfin = lista_espacios.end();

	for (itS = lista_espacios.begin(); itS != itSfin; itS++)
	{
		if ((*itS).Get_x1() <= (*C).Get_x1() && (*itS).Get_y1() <= (*C).Get_y1() && (*itS).Get_z1() == (*C).Get_z1() &&
			(*itS).Get_x2() >= (*C).Get_x2() && (*itS).Get_y2() >= (*C).Get_y2() && (*itS).Get_z2() >= (*C).Get_z2())
			return *itS;
	}
}


void CONTAINER::ElegirSpaceMovimiento(SPACE &espacio,std::list<SPACE> &lista,bool  &posi)
{
	//Elige por el mas pequeno
/*	std::list<SPACE> ::iterator it,elegido;
	for (it=lista.begin();it!=lista.end();it++)
	{
//		SPACE kk=(*it);
		if ((*it).Get_Flag()==false)
		{
				return (*it);
		}
	}
	return (lista.front());
*/	std::list<SPACE> ::iterator it,elegido;
	bool quedan_todavia=false;
	bool primero=true;;
	//Los recorro todos comparando cual es el mejor
	std::list< SPACE > ::iterator itfin=lista.end();
	for (it=lista.begin();it!=itfin;it++)
	{
//		SPACE kk=(*it);
		if ((*it).Get_Flag()==false)
		{
//			if (get_random(0,3)==2) return (*it);
			quedan_todavia=true;
			if (primero==true) 
			{
				elegido=it;
				primero=false;

			}
			else
			{
				if (Mejor_DistA_Que_DistB((*elegido),(*it))==false)
				{
					elegido=it;
				}
			}
		}
		//Funcion que me elimina los espacios 
		//si la quito todo funsiona igual 


	}
	if (quedan_todavia==false || lista.size()==0) 
	{
		
		return ;
	}
	posi=true;
	espacio.ModificarSpace(elegido->Get_x1(),elegido->Get_y1(),elegido->Get_z1(),elegido->Get_x2(),elegido->Get_y2(),elegido->Get_z2());


}
void CONTAINER::MinimaDimensionMov()
{	
	m_dimension_menor=m_X;
	m_menor_volumen=m_X*m_Y*m_Z;
	for (int register icp=0;icp<m_Q;icp++)
	{
		if (m_Pieces_Tabu[icp]==m_Pieces[icp].Get_q())
			continue;
		if ((m_Pieces[icp].Get_x()*m_Pieces[icp].Get_y()*m_Pieces[icp].Get_z())<m_menor_volumen)
			m_menor_volumen=m_Pieces[icp].Get_x()*m_Pieces[icp].Get_y()*m_Pieces[icp].Get_z();
		if (m_Pieces[icp].Get_x()<m_dimension_menor)
				m_dimension_menor=m_Pieces[icp].Get_x();
		if (m_Pieces[icp].Get_y()<m_dimension_menor)
				m_dimension_menor=m_Pieces[icp].Get_y();
		if (m_Pieces[icp].Get_z()<m_dimension_menor)
			m_dimension_menor=m_Pieces[icp].Get_z();

	}

}
void CONTAINER::Maximalizar(std::list<SPACE> &lista1)
{
	bool mover=false;
	std::list<SPACE> lista_nuevos;
	do
	{
		lista_nuevos.clear();
		std::list<SPACE> ::iterator it,itC,it1fin=lista1.end();
		for (it=lista1.begin();it!=it1fin && lista_nuevos.size()==0;)
		{
			itC=it;
			itC++;
			if (itC==it1fin)
				break;
			mover=false;
			for (;itC!=it1fin && mover!=true;)
			{
				std::list<SPACE> lista_temp;

				SPACE kk=(*it);
				SPACE kkk=(*itC);
				//se cortan
				if (JuntarTwoSpaces((*it),(*itC),lista_temp)==true)
				{

					lista_nuevos.insert(lista_nuevos.begin(),lista_temp.begin(),lista_temp.end());

					//eliminar el primero
					if ((*it).Get_dx()==0)
					{
						it=lista1.erase(it);
						if ((*itC).Get_dx() == 0)
						{
							if (it == itC)
								++it;
							itC = lista1.erase(itC);
						}
						mover=true;
						break;
					}
					//eliminar el segundo
					if ((*itC).Get_dx()==0)
						itC=lista1.erase(itC);
					else
						++itC;
				}
				else
					++itC;	

			}
			if (mover==false)
				++it;
		}
		EliminarInclusionesDeLaSegundaListaEnLaPrimera(lista1,lista_nuevos);
		lista1.insert(lista1.begin(),lista_nuevos.begin(),lista_nuevos.end());
		EliminarInclusionesEstaLista(lista1);
	}while(lista_nuevos.size()!=0 && lista1.size()>1);

}
//Pueden darse tres casos que cambie los de una lista que cambie los de la otra o que 
//se cree una nueva perdida que tenga parte de las dos anteriores
//Mirar porque se pueden quitar algunos if innecesarios
void CONTAINER::JuntarSpaces(std::list<SPACE> &lista1,std::list<SPACE> &lista2)
{
	//No se puede hacer asi ya que si las ponemos en una lista 2
	//estas también pueden tener que juntarse entre ellas
	//para que todo sea correcto
	if (lista2.size()==0 || lista1.size()==0)
		return;
	bool mover=false;
	do
	{
		std::list<SPACE> lista_nuevos;

		std::list<SPACE> ::iterator it,itC,it1fin=lista1.end(),it2fin=lista2.end();
		for (it=lista1.begin();it!=it1fin && lista2.size()>0;)
		{
	//Estos son si son más grandes, hago mas grande el hueco que he hecho
			mover=false;
			for (itC=lista2.begin();itC!=it2fin && mover!=true;)
			{
				std::list<SPACE> lista_temp;

				SPACE kk=(*it);
				SPACE kkk=(*itC);
				//se cortan
				if (JuntarTwoSpaces((*it),(*itC),lista_temp)==true)
				{

					EliminarInclusionesDeLaSegundaListaEnLaPrimera(lista_nuevos,lista_temp);
					lista_nuevos.insert(lista_nuevos.begin(),lista_temp.begin(),lista_temp.end());

					//eliminar el primero
					if ((*it).Get_dx()==0)
					{
						it=lista1.erase(it);
						mover=true;
					}
					//eliminar el segundo
					if ((*itC).Get_dx()==0)
						itC=lista2.erase(itC);
					else
						++itC;
				}
				else
					++itC;	

			}
			if (mover==false)
				++it;
		}
		if (lista_nuevos.size() > 1)
		{
			contador++;
			printf("%d\n", contador);
			/*if (contador == 11)
				SetDibujar(false);*/
			Maximalizar(lista_nuevos);
		}
			//		    int kk=lista_nuevos.size();
		EliminarInclusionesDeLaSegundaListaEnLaPrimera(lista1, lista_nuevos);
		EliminarInclusionesDeLaSegundaListaEnLaPrimera(lista2, lista_nuevos);
//		EliminarInclusionesListaAntigua(lista1,lista2);
/*		if (lista_nuevos.size()<kk) 
		{
			printf("Ocurria estas inclusiones extrano");
		}
*/		lista1.insert(lista1.begin(),lista2.begin(),lista2.end());
		lista2.clear();
		lista2.insert(lista2.begin(),lista_nuevos.begin(),lista_nuevos.end());
//		printf("\nOtraIteracion\n");

	}while(lista2.size()!=0);

}

void CONTAINER::CrearInstanciasPedidos()
{
	srand(1);
	for (int npedidos = 10; npedidos < 26; npedidos += 5)
	{
		std::vector<int> pedidos_iniciales;
		std::string nombre(m_Nombre);
		std::string name_r;
		std::size_t found = nombre.find(".txt");
		if (found != std::string::npos)
			name_r = nombre.substr(0, nombre.find(".txt") ) ;

		std::string name = name_r + "_" + std::to_string(npedidos) + ".txt";
		FILE* read;
		read = fopen(name.c_str(), "w+");
		if (read == NULL)
		{
			fprintf(stderr, "Can't open input file %s!\n", name.c_str());
			exit(0);
		}
		fprintf(read, "%d\n", m_Q);
		fprintf(read, "%d\t%d\t%d\n", m_X, m_Y, m_Z);
		for (int j = 0; j < m_Q; j++)
		{
			fprintf(read, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", j + 1, m_Pieces[j].Get_x(), m_Pieces[j].Get_Rx(), m_Pieces[j].Get_y(), m_Pieces[j].Get_Ry(), m_Pieces[j].Get_z(), m_Pieces[j].Get_Rz(), m_Pieces[j].Get_q());
			pedidos_iniciales.push_back(m_Pieces[j].Get_q());
		}
		
		int Npedidos = 0;
		std::vector< std::vector<int> > pedidos;
		for (int k = 0 ; k <npedidos; k++)
		{

			
			std::vector<int>  pedido;
			int algo = 0;
			for (int j = 0; j < m_Q; j++)
			{
				int kq = 0;
				for (int i = 0; i < m_Pieces[j].Get_q(); i++)
				{
					if (get_random(1, npedidos) == npedidos)
						kq++;
				}
				if ((pedidos_iniciales[j] - kq) < 0)
					kq = pedidos_iniciales[j];
				if (k==(npedidos-1))
					kq= pedidos_iniciales[j];
				algo += kq;
				pedido.push_back(kq);
				pedidos_iniciales[j] = pedidos_iniciales[j] - kq;
				
			}
			Npedidos++;
			pedidos.push_back(pedido);
			if (algo == 0)
			{

				bool arreglado = false;
				for (int k1 = 0; k1 < (Npedidos-1) && arreglado!=true; k1++)
				{
					int masdeuno = 0;
					for (int j = 0; j < m_Q && masdeuno<2; j++)
					{
						masdeuno += pedidos[k1][j];
						if (masdeuno > 1)
						{
							pedidos[Npedidos - 1][j] = 1;
							pedidos[k1][j] = -1;

							arreglado = true;
						}

					}
				}

			}


		}
		fprintf(read, "%d\n", npedidos);
		for (int k = 0; k < npedidos; k++)
		{
			fprintf(read, "%d\t", k+1);
			int suma = 0;
			for (int j = 0; j < m_Q; j++)
			{
				fprintf(read, "%d\t", pedidos[k][j]);
				suma += pedidos[k][j];
			}
			
			fprintf(read, "%d\t", suma);
			fprintf(read, "\n");
		}
		fclose(read);


	}


}


void CONTAINER::CrearInstanciasPedidosFix()
{
	srand(1);
	for (int npedidos = 50; npedidos < 51; npedidos += 5)
	{
		std::vector<int> pedidos_iniciales;
		std::string nombre(m_Nombre);
		std::string name_r;
		std::size_t found = nombre.find(".txt");
		if (found != std::string::npos)
			name_r = nombre.substr(0, nombre.find(".txt"));

		std::string name = name_r + "_" + std::to_string(npedidos) + ".txt";
		FILE* read;
		read = fopen(name.c_str(), "w+");
		if (read == NULL)
		{
			fprintf(stderr, "Can't open input file %s!\n", name.c_str());
			exit(0);
		}
		fprintf(read, "%d\n", m_Q);
		fprintf(read, "%d\t%d\t%d\n", m_X, m_Y, m_Z);
		for (int j = 0; j < m_Q; j++)
		{
			fprintf(read, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", j + 1, m_Pieces[j].Get_x(), m_Pieces[j].Get_Rx(), m_Pieces[j].Get_y(), m_Pieces[j].Get_Ry(), m_Pieces[j].Get_z(), m_Pieces[j].Get_Rz(), m_Pieces[j].Get_q());
			pedidos_iniciales.push_back(m_Pieces[j].Get_q());
		}

		int Npedidos = 0;
		std::vector< std::vector<int> > pedidos;
		//Creo la matriz de pedidos
		for (int k = 0; k < npedidos; k++)
		{
			std::vector<int> temp(m_Q + 1);
			pedidos.push_back(temp);
		}
		//Asigno al azar los pedidos
		/*for (int j = 0; j < m_Q; j++)
		{
			int kq = 0;*/
			for (int j = 0; j < m_Q; j++)
			{
				for (int i = 0; i < m_Pieces[j].Get_q(); i++)
				{
					pedidos[get_random(0, npedidos - 1)][j]++;

				}
			}
		/*}*/
		//Pongo la suma total
		for (int k = 0; k < npedidos; k++)
		{
			int Total = 0;
			for (int j = 0; j < m_Q; j++)
			{
				Total += pedidos[k][j];
			}
			pedidos[k][m_Q ] = Total;
		}
		//Si hay alguno que se haya quedado sin nada asigno
		for (int k = 0; k < npedidos; k++)
		{
			if (pedidos[k][m_Q ] == 0)
			{

				bool arreglado = false;
				for (int k1 = 0; k1 < npedidos && arreglado != true; k1++)
				{
					if (pedidos[k1][m_Q ] > 1)
					{
						for (int j = 0; j < m_Q && arreglado!=true; j++)
						{

							if (pedidos[k1][j] >= 1)
							{
								//intercambio
								pedidos[k1][j] -= 1;
								pedidos[k][j] = 1;
								//Pongo los totales
								pedidos[k1][m_Q ] -= 1;
								pedidos[k][m_Q ] = 1;
								arreglado = true;
							}

						}
					}
				}

			}


		}
		fprintf(read, "%d\n", npedidos);
		for (int k = 0; k < npedidos; k++)
		{
			fprintf(read, "%d\t", k + 1);
			int suma = 0;
			for (int j = 0; j < m_Q; j++)
			{
				fprintf(read, "%d\t", pedidos[k][j]);
				suma += pedidos[k][j];
			}

			fprintf(read, "%d\t", suma);
			fprintf(read, "\n");
		}
		fclose(read);


	}


}
//Devuelve true si se cortan y false si no y tambien devuelve los otros dos 
//modificados con dx igual a cero
bool CONTAINER::JuntarTwoSpaces(SPACE &Space1, SPACE &Space2, std::list<SPACE> &lista_espacios)
{
	//Hay tres casos el tercero es crear una nueva que se crea con los maximos
	int minx1=min(Space1.Get_x1(),Space2.Get_x1());
	int maxx2=max(Space1.Get_x2(),Space2.Get_x2());
	if ((maxx2-minx1)>(Space1.Get_dx()+Space2.Get_dx()))
		return false;
	int miny1=min(Space1.Get_y1(),Space2.Get_y1());
	int maxy2=max(Space1.Get_y2(),Space2.Get_y2());
	if ((maxy2-miny1)>(Space1.Get_dy()+Space2.Get_dy()))
		return false;
	int minz1=min(Space1.Get_z1(),Space2.Get_z1());
	int maxz2=max(Space1.Get_z2(),Space2.Get_z2());
	if ((maxz2-minz1)>(Space1.Get_dz()+Space2.Get_dz()))
		return false;
	//Si el espacio 2 esta incluido en el uno
	if (Space2.Incluido(Space1)) return false;
	//Caso que se junten en uno

	//Si pasa aqui ya tenemos que se cortan
	int maxx1=max(Space1.Get_x1(),Space2.Get_x1());
	int maxy1=max(Space1.Get_y1(),Space2.Get_y1());
	int maxz1=max(Space1.Get_z1(),Space2.Get_z1());
	int minx2=min(Space1.Get_x2(),Space2.Get_x2());
	int miny2=min(Space1.Get_y2(),Space2.Get_y2());
	int minz2=min(Space1.Get_z2(),Space2.Get_z2());
	//*********************
	//Los tres nuevos
	//el primero
	if (minx1<maxx2 && maxy1<miny2 && maxz1<minz2)
	{
		SPACE Espacio(minx1,maxy1,maxz1,maxx2,miny2,minz2,this);
		if (Espacio.Incluido(Space1)==false && Espacio.Incluido(Space2)==false)
		{
//	printf("\nEspacio1 %d %d %d %d %d %d\n",Space1.Get_x1(),Space1.Get_y1(),Space1.Get_z1(),Space1.Get_x2(),Space1.Get_y2(),Space1.Get_z2());
//	printf("Espacio2 %d %d %d %d %d %d\n",Space2.Get_x1(),Space2.Get_y1(),Space2.Get_z1(),Space2.Get_x2(),Space2.Get_y2(),Space2.Get_z2());
//	printf("Espacio3 %d %d %d %d %d %d\n",Espacio.Get_x1(),Espacio.Get_y1(),Espacio.Get_z1(),Espacio.Get_x2(),Espacio.Get_y2(),Espacio.Get_z2());
//			Espacio.Incluido(Space1);

			InsertarOrdenUnica(lista_espacios,Espacio);
			if (Space1.Incluido(Espacio)==true)
				Space1.Set_dx(0);
			if (Space2.Incluido(Espacio)==true)
				Space2.Set_dx(0);
		}
	}
	//el segundo
	if (maxx1<minx2 && miny1<maxy2 && maxz1<minz2)
	{
		SPACE Espacio(maxx1,miny1,maxz1,minx2,maxy2,minz2,this);
		if (Espacio.Incluido(Space1)==false && Espacio.Incluido(Space2)==false)
		{
//	printf("\nEspacio1 %d %d %d %d %d %d\n",Space1.Get_x1(),Space1.Get_y1(),Space1.Get_z1(),Space1.Get_x2(),Space1.Get_y2(),Space1.Get_z2());
//	printf("Espacio2 %d %d %d %d %d %d\n",Space2.Get_x1(),Space2.Get_y1(),Space2.Get_z1(),Space2.Get_x2(),Space2.Get_y2(),Space2.Get_z2());
//	printf("Espacio3 %d %d %d %d %d %d\n",Espacio.Get_x1(),Espacio.Get_y1(),Espacio.Get_z1(),Espacio.Get_x2(),Espacio.Get_y2(),Espacio.Get_z2());
//			Espacio.Incluido(Space1);
			InsertarOrdenUnica(lista_espacios,Espacio);
			if (Space1.Incluido(Espacio)==true)
				Space1.Set_dx(0);
			if (Space2.Incluido(Espacio)==true)
				Space2.Set_dx(0);
		}

	}
	//el tercero
	if (maxx1<minx2 && maxy1<miny2 && minz1<maxz2)
	{
		SPACE Espacio(maxx1,maxy1,minz1,minx2,miny2,maxz2,this);
		if (Espacio.Incluido(Space1)==false && Espacio.Incluido(Space2)==false)
		{
//	printf("\nEspacio1 %d %d %d %d %d %d\n",Space1.Get_x1(),Space1.Get_y1(),Space1.Get_z1(),Space1.Get_x2(),Space1.Get_y2(),Space1.Get_z2());
//	printf("Espacio2 %d %d %d %d %d %d\n",Space2.Get_x1(),Space2.Get_y1(),Space2.Get_z1(),Space2.Get_x2(),Space2.Get_y2(),Space2.Get_z2());
//	printf("Espacio3 %d %d %d %d %d %d\n",Espacio.Get_x1(),Espacio.Get_y1(),Espacio.Get_z1(),Espacio.Get_x2(),Espacio.Get_y2(),Espacio.Get_z2());
//			Espacio.Incluido(Space1);
			InsertarOrdenUnica(lista_espacios,Espacio);
			if (Space1.Incluido(Espacio)==true)
				Space1.Set_dx(0);
			if (Space2.Incluido(Espacio)==true)
				Space2.Set_dx(0);
		}

	}

	if (lista_espacios.size()>0)
	return true;
	else
		return false;


}
void MOVIMIENTO::ActualizarListaEspaciosBloquesMov(std::list<SPACE> &lista_espacios,CONFIGURACAO &Configuracao)
{
	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin=lista_espacios.end(),it;
		std::list<SPACE> lista_temp2;

	for (it = lista_espacios.begin();it!=itfin;)
	{
		//Si se intersectan hacer los espacios
			SPACE kk=(*it);
//		if ((*it).Get_Flag()==true) continue;
		std::list<SPACE> lista_temp;
		if (!(Configuracao.Get_x2() <= (*it).Get_x1() ||  Configuracao.Get_x1() >= (*it).Get_x2())
			&& !(Configuracao.Get_y2() <= (*it).Get_y1() ||  Configuracao.Get_y1() >= (*it).Get_y2())
			&& !(Configuracao.Get_z2() <= (*it).Get_z1() ||  Configuracao.Get_z1() >= (*it).Get_z2()))
		{

			m_Container->ActualizarEspaciosElegido((*it),Configuracao,lista_temp);

			//Tengo que hacer el -- porque me apunta al siguiente
			it=lista_espacios.erase(it);
			if (lista_temp2.size()>0 && lista_temp.size()>0) m_Container->JuntarSpaces(lista_temp2,lista_temp);
			lista_temp2.insert(lista_temp2.begin(),lista_temp.begin(),lista_temp.end());
		}
		else
			++it;

	}
	lista_espacios.insert(lista_espacios.begin(),lista_temp2.begin(),lista_temp2.end());
}
void MOVIMIENTO::ActualizarListaEspaciosOriginalesMov(std::list<SPACE> &lista_espacios,CONFIGURACAO &Configuracao)
{
	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin=lista_espacios.end(),it;
		std::list<SPACE> lista_temp2;

	for (it = lista_espacios.begin();it!=itfin;)
	{
		//Si se intersectan hacer los espacios
			SPACE kk=(*it);
//		if ((*it).Get_Flag()==true) continue;
		std::list<SPACE> lista_temp;
		if (!(Configuracao.Get_x2() <= (*it).Get_x1() ||  Configuracao.Get_x1() >= (*it).Get_x2())
			&& !(Configuracao.Get_y2() <= (*it).Get_y1() ||  Configuracao.Get_y1() >= (*it).Get_y2())
			&& !(Configuracao.Get_z2() <= (*it).Get_z1() ||  Configuracao.Get_z1() >= (*it).Get_z2()))
		{

			m_Container->ActualizarEspaciosElegido((*it),Configuracao,lista_temp);
			lista_temp2.insert(lista_temp2.begin(),lista_temp.begin(),lista_temp.end());

			//Tengo que hacer el -- porque me apunta al siguiente
			it=lista_espacios.erase(it);
		}
		else
			++it;

	}
	//Tengo que meter los nuevos producidos
	m_Container->EliminarInclusionesEstaLista(lista_temp2);
	m_Container->EliminarInclusionesDeLaSegundaListaEnLaPrimera(lista_espacios,lista_temp2);
	lista_espacios.insert(lista_espacios.begin(),lista_temp2.begin(),lista_temp2.end());
}
void CONTAINER::EliminarInclusionesEstaLista(std::list < SPACE > &Lista)
{
	std::list<SPACE> ::iterator itl,itl2;
	for (itl=Lista.begin();itl!=Lista.end();)
	{

		itl2=itl;
		itl2++;

		if (itl2==Lista.end())
			break;

		for (;itl2!=Lista.end();itl2++)
		{

			
			if ((*itl).Incluido(*itl2)==true)
			{

				//Me devuelve el puntero que apunta al siguiente
				//por tanto le tengo que quita algo
				itl=Lista.erase(itl);
				itl--;
				break;


			}
		}
		++itl;
	}
}
void CONTAINER::EliminarInclusionesDeLaSegundaListaEnLaPrimera(std::list<SPACE> &lista_Viejos,std::list <SPACE > &Lista)
{
	std::list<SPACE> ::iterator itl;
	std::list<SPACE> ::reverse_iterator itl2;
	for (itl=Lista.begin();itl!=Lista.end();)
	{
//		SPACE kk=(*itl);
//		itl2=itl;
//		itl2++;
//		if (itl2==m_Spaces.end())
//			break;
		for (itl2=lista_Viejos.rbegin();itl2!=lista_Viejos.rend();)
		{
//			SPACE kk2=(*itl2);
			if ((*itl).Incluido((*itl2))==true)
			{
				//Si esta incluido termina 
				itl=Lista.erase(itl);
				break;
			}
			++itl2;
		}
		if (itl!=Lista.end())
		    ++itl;
	}
}
//Esta funcion mueve las cajas que tienen el mismo lugar hacia ese lugar
bool CONTAINER::FuerzaDeGravedadEsquina(std::list<CONFIGURACAO> &lista,short int lugar,short int sentido, short int dir)
{
	bool movido=false;
	std::list<CONFIGURACAO>lista2;
//Tengo 8 posibles sentidos
	//es a que esquina es la que esta más cercana
	// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z) 
	//	PintarSolucion(m_Best_Configuracao);
//	sentido=0;
	std::list<CONFIGURACAO> ::iterator itC;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
		bool retroceso = false;
		CONFIGURACAO Temp = (*itC);
//		CONFIGURACAO kkk=(*itC);
		if ((*itC).Get_orig()!=lugar)
			continue;
		//Primero en las x y asi
		if (sentido==0 && ((*itC).Get_z1()==0 || (*itC).Get_z2()==m_Z))
			continue;
		if (sentido==1 && ((*itC).Get_x1()==0 || (*itC).Get_x2()==m_X))
			continue;
		if (sentido==2 && ((*itC).Get_y1()==0 || (*itC).Get_y2()==m_Y))
			continue;
		int muevo=PuedoMover(lista,(*itC).Get_x1(),(*itC).Get_y1(),(*itC).Get_z1(),(*itC).Get_x2(),(*itC).Get_y2(),(*itC).Get_z2(),sentido,dir);
		if (sentido == 0 && muevo > 0)
		{
			if (dir == 0)
			{
				movido = true;
				(*itC).Set_z1((*itC).Get_z1() - muevo);
				(*itC).Set_z2((*itC).Get_z2() - muevo);
			}
			else
			{
				movido = true;
				(*itC).Set_z1((*itC).Get_z1() + muevo);
				(*itC).Set_z2((*itC).Get_z2() + muevo);

			}
		}
		if (sentido==1 && muevo>0)
		{
			if(dir==0)
			{
				movido=true;
				(*itC).Set_x1((*itC).Get_x1()-muevo);
				(*itC).Set_x2((*itC).Get_x2()-muevo);
				if (m_full_supported == true)
				{
					CONFIGURACAO ConfFantasma(this, 0, (*itC).Get_x2(), (*itC).Get_y1(), (*itC).Get_z2(), Temp.Get_x2(), (*itC).Get_y2(), this->Get_Z(), 1, 1, 0);
					ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
				}
			}
			else
			{
				movido=true;
				(*itC).Set_x1((*itC).Get_x1()+muevo);
				(*itC).Set_x2((*itC).Get_x2()+muevo);
				if (m_full_supported == true)
				{
					CONFIGURACAO ConfFantasma(this, 0, Temp.Get_x1(), (*itC).Get_y1(), (*itC).Get_z2(), (*itC).Get_x1(), (*itC).Get_y2(), this->Get_Z(), 1, 1, 0);
					ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
				}
			}
		}
		if (sentido == 2 && muevo > 0)
		{
			if (dir == 0)
			{
				movido = true;
				(*itC).Set_y1((*itC).Get_y1() - muevo);
				(*itC).Set_y2((*itC).Get_y2() - muevo);
				if (m_full_supported == true)
				{
					CONFIGURACAO ConfFantasma(this, 0, (*itC).Get_x1(), (*itC).Get_y2(), (*itC).Get_z2(), (*itC).Get_x2(), Temp.Get_y2(), this->Get_Z(), 1, 1, 0);
					ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
				}
			}
			else
			{
				movido = true;
				(*itC).Set_y1((*itC).Get_y1() + muevo);
				(*itC).Set_y2((*itC).Get_y2() + muevo);
				if (m_full_supported == true)
				{
					CONFIGURACAO ConfFantasma(this, 0, (*itC).Get_x1(), Temp.Get_y1(), (*itC).Get_z2(), (*itC).Get_x2(), (*itC).Get_y1(), this->Get_Z(), 1, 1, 0);
					ActualizarListaDeBloquesReducir(ConfFantasma, lista, lista2);
				}
			}
		}
		ComprobarFullSupport(lista);
	}
//	PintarSolucion(m_Best_Configuracao);
	return movido;

}
// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z) 
//
int CONTAINER::PuedoMover(std::list<CONFIGURACAO> &lista,int x1,int y1,int z1,int x2,int y2,int z2,short int sentido,short int dir)
{
	//Me dice cuanto puedo mover esta pieza 
	//lo primero es localizar el maximo
	//Lo primero es ver si se intersectan

	//Me dice si la pieza está soportada por el suelo del container o no
	bool soporta_suelo;
	int x2_fs = m_X; //cuales serian los valores iniciales!!!!!!!!
	int x1_fs = 0;
	int y2_fs = m_Y;
	int y1_fs = 0;
	std::list<CONFIGURACAO> lista_fullsupport;
	std::list<CONFIGURACAO>::iterator itfs;
	if (z1 == 0) //Si está en el suelo puedo moverme sin restricción por full support
		soporta_suelo = true;
	else
		soporta_suelo = false;
	//Si hay full support, los movimientos de compactación se restringen para que no queden bloques sin soporte
	if (m_full_supported == true && soporta_suelo==false)
	{
		for (itfs = lista.begin(); itfs != lista.end(); itfs++)
		{
			if ((*itfs).Get_z2() != z1) //El final del bloque debe coincidir con el principio del otro para poder plantear si lo soporta o no
				continue;
			if ((*itfs).Get_x2() <= x1 || (*itfs).Get_x1() >= x2)
				continue;
			if ((*itfs).Get_y2() <= y1 || (*itfs).Get_y1() >= y2)
				continue;
			//lista_fullsupport.push_back(*itfs); //Si llega hasta aquí es que itfs soporta al bloque que intentamos compactar
			if ((*itfs).Get_x1() <= x1) //como hacer esto para que calcule lo que quiero!!!!!!!!!
				x1_fs = max((*itfs).Get_x1(),x1_fs);
			if ((*itfs).Get_y1() <= y1)
				y1_fs = max((*itfs).Get_y1(),y1_fs);
			if ((*itfs).Get_x2() >= x2)
				x2_fs = min((*itfs).Get_x2(),x2_fs);
			if ((*itfs).Get_y2() >= y2)
				y2_fs = min((*itfs).Get_y2(),y2_fs);
		}
	}

	int mintemp=0,min=m_X;	
	if (sentido == 0)
	{
		if (dir == 0)		min = z1;
		if (dir == 1)		min = m_Z - z2;
	}
	if (sentido==1)
	{
		if (dir==0)		min=x1-x1_fs;
		if (dir==1)		min=x2_fs-x2;
	}
	if (sentido == 2)
	{
		if (dir == 0)		min = y1 - y1_fs;
		if (dir == 1)		min = y2_fs - y2;
	}
	std::list<CONFIGURACAO> ::iterator itC;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{

//		CONFIGURACAO kk=(*itC);
		if (sentido == 0)
		{
			if (dir == 0)
			{
				if ((*itC).Get_z1() >= z1)
					continue;
				//Si no intersectan con eje_x
				if (!((y2 <= (*itC).Get_y1()) || (y1 >= (*itC).Get_y2()))
					&& !((x2 <= (*itC).Get_x1()) || (x1 >= (*itC).Get_x2())))
				{
					if (z1 == ((*itC).Get_z2())) 	return 0;
					mintemp = z1 - ((*itC).Get_z2());
					if (mintemp < min)
						min = mintemp;
				}

			}
			else
			{
				if ((*itC).Get_z2() <= z2)
					continue;
				//Si no intersectan con eje_x
				if (!((y2 <= (*itC).Get_y1()) || (y1 >= (*itC).Get_y2()))
					&& !((x2 <= (*itC).Get_x1()) || (x1 >= (*itC).Get_x2())))
				{
					if (z2 == ((*itC).Get_z1())) 	return 0;
					mintemp = ((*itC).Get_z1()) - z2;
					if (mintemp < min)
						min = mintemp;
				}

			}
		}
		if (sentido==1)
		{
			if (dir==0)
			{
				if ((*itC).Get_x1()>=x1) 
					continue;
				//Si no intersectan con eje_x
				if (!((z2 <= (*itC).Get_z1()) ||  (z1 >= (*itC).Get_z2()))
					&& !((y2 <= (*itC).Get_y1()) ||  (y1 >= (*itC).Get_y2())))
				{
					if (x1==((*itC).Get_x2())) 	return 0;
						mintemp=x1-((*itC).Get_x2());
						if (mintemp < min)
						{
							if (m_full_supported == false)
								min = mintemp;
							else
							{
								if (x1 - x1_fs < mintemp && soporta_suelo == false)
									min = x1 - x1_fs;
								else
									min = mintemp;
							}
						}
				}

			}
			else
			{
				if ((*itC).Get_x2()<=x2) 
					continue;
				//Si no intersectan con eje_x
				if (!((z2 <= (*itC).Get_z1()) ||  (z1 >= (*itC).Get_z2()))
					&& !((y2 <= (*itC).Get_y1()) ||  (y1 >= (*itC).Get_y2())))
				{
					if (x2==((*itC).Get_x1())) 	return 0;
						mintemp=((*itC).Get_x1())-x2;
						if (mintemp < min)
						{
							if (m_full_supported == false)
								min = mintemp;
							else
							{
								if (x2_fs - x2 < mintemp && soporta_suelo == false)
									min = x2_fs - x2;
								else
									min = mintemp;
							}
						}
				}

			}
		}
		if (sentido == 2)
		{
			if (dir == 0)
			{
				if ((*itC).Get_y1() >= y1)
					continue;
				//Si no intersectan con eje_x
				if (!((x2 <= (*itC).Get_x1()) || (x1 >= (*itC).Get_x2()))
					&& !((z2 <= (*itC).Get_z1()) || (z1 >= (*itC).Get_z2())))
				{
					if (y1 == ((*itC).Get_y2())) 	return 0;
					mintemp = y1 - ((*itC).Get_y2());
					if (mintemp < min)
					{
						if (m_full_supported == false)
							min = mintemp;
						else
						{
							if (y1 - y1_fs < mintemp && soporta_suelo == false)
								min = y1 - y1_fs;
							else
								min = mintemp;
						}
					}
				}

			}
			else
			{
				if ((*itC).Get_y2() <= y2)
					continue;
				//Si no intersectan con eje_x
				if (!((x2 <= (*itC).Get_x1()) || (x1 >= (*itC).Get_x2()))
					&& !((z2 <= (*itC).Get_z1()) || (z1 >= (*itC).Get_z2())))
				{
					if (y2 == ((*itC).Get_y1())) 	return 0;
					mintemp = ((*itC).Get_y1()) - y2;
					if (mintemp < min)
					{
						if (m_full_supported == false)
							min = mintemp;
						else
						{
							if (y2_fs - y2 < mintemp && soporta_suelo == false)
								min = y2_fs - y2;
							else
								min = mintemp;
						}
					}
				}

			}


		}
	}
//	return 0;
	return min;
}