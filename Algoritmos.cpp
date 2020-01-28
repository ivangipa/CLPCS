#pragma warning (disable: 4786)

//Para incluir el contenedor que tengo
#include "Container.h"


//Le paso el parametro de si quiero que sea un constructivo aleatorizado
void CONTAINER::Constructivo(bool aleatorizado)
{
	bool ya_mejorado = false;
	m_objetivo_vol = true;

	m_Aleatorizado = aleatorizado;
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space(0, 0, 0, m_X, m_Y, m_Z, this);
	m_Spaces.push_back(Space);

	while (m_Spaces.size() > 0)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio
		SPACE& SpaceElegido = ElegirSpace();
		if (m_Spaces.size() == 0 || SpaceElegido.Get_Flag() == true)
		{
			/*if (m_complete_shipment==true)
				m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();*/
			if (m_imprimir == true)
			{
				FILE* fin3;
				fin3 = fopen(m_file_to_write, "a+");
				double pt = ((double)m_total_volumen_ocupado / (double)(m_X * m_Y * m_Z)) * 100;
				if (m_complete_shipment == true)
				{
					double ptcs = ((double)m_total_volumen_cs_ocupado / (double)(m_X * m_Y * m_Z)) * 100;
					fprintf(fin3, "%s\tV\t%d\tVU\t%d\t%f\t%d\t%f\n", m_Nombre, m_total_volumen, m_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs);
				}
				else
					fprintf(fin3, "%s\tV\t%d\tVU\t%d\t%f\n", m_Nombre, m_total_volumen, m_total_volumen_ocupado, pt);
				fclose(fin3);
			}
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		ORIG setmin(SpaceElegido.Get_dx(), SpaceElegido.Get_dy(), SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this, setmin, 999999);
		if (m_all_bloques == true)
			m_por_bloques_ara = false; //El constructivo que funcione sin bloques porque saca mejor solución
		//Elegir configuración para ese espacio
		if (m_por_bloques == false && m_por_bloques_ara == false)
			ElegirConfiguracao(SpaceElegido, Configuracao);
		else
		{
			if (m_por_bloques == true)
				ElegirConfiguracaoBloque(SpaceElegido, Configuracao);
			else
				ElegirConfiguracaoBloqueAra(SpaceElegido, Configuracao);
		}
			if (Configuracao.Get_Id() == 99999)
			{
				SpaceElegido.Set_Flag(true);
				continue;
			}
			//Actualizar lista de bloques
	//		DibujarSolucion(m_Spaces,m_Configuracaos);
			if (m_por_bloques == false && m_por_bloques_ara==false)
				ActualizarListas(SpaceElegido, Configuracao);
			else
			{
				if (m_por_bloques_ara == true)
					ActualizarListasAra(SpaceElegido, Configuracao);
				else
				{
					if (Configuracao.Get_Id() < 1000) //Si es menor que 1000 es pieza o capa de piezas, si es mayor o igual es bloque o capa de bloques
						ActualizarListas(SpaceElegido, Configuracao);
					else
						ActualizarListasBloque(SpaceElegido, Configuracao, false);
				}
			}
			std::list<SPACE> ::iterator it;
			if (m_mejora_local == true && ya_mejorado == false && m_total_volumen_ocupado >= m_val_quita * m_max_total_volumen_ocupado)
			{
				ya_mejorado = true;
				m_Spaces_Mejora = m_Spaces;
				m_Configuracaos_Mejora = m_Configuracaos;
				m_total_volumen_ocupado_mejora = m_total_volumen_ocupado;
				for (register int m = 0; m < m_Q; m++)
				{
					m_Pieces_Mejora[m] = m_Pieces[m].Get_Num();
				}
			}
			double pt = ((double)m_total_volumen_ocupado / ((double)m_X * m_Y * m_Z)) * 100;
			if (pt >= m_Limite && m_Random==true && m_complete_shipment==true)
				break;
			//Funcion que verifica si todo va bien
	//		printf("V %d VU %d %f\n",m_total_volumen,m_total_volumen_ocupado,pt);
	//	DibujarSolucion(m_Spaces,m_Configuracaos);

		}
		if (m_Aleatorizado == false && m_imprimir==true)
		{
			FILE* fin3;
			fin3 = fopen(m_file_to_write, "a+");
			double pt = ((double)m_total_volumen_ocupado / (double)m_total_volumen) * 100;
			fprintf(fin3, "%s\tV\t%d\tVU\t%d\t%f\n", m_Nombre, m_total_volumen, m_total_volumen_ocupado, pt);
			fclose(fin3);
		}

		VerificarSolucion(m_Configuracaos);

	}

void CONTAINER::ConstructivoCS(bool aleatorizado)	
{
	bool ya_mejorado = false;
	m_objetivo_vol = true;

	m_Aleatorizado = aleatorizado;
	while (m_Spaces.size() > 0)
	{
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio
		SPACE& SpaceElegido = ElegirSpace();
		if (m_Spaces.size() == 0 || SpaceElegido.Get_Flag() == true)
		{
			/*if (m_complete_shipment==true)
				m_total_volumen_cs_ocupado = FuncionObjetivoCompleteShipment();*/
			/*FILE* fin3;
			fin3 = fopen(m_file_to_write, "a+");
			double pt = ((double)m_total_volumen_ocupado / (double)(m_X * m_Y * m_Z)) * 100;
			if (m_complete_shipment == true && m_imprimir == true)
			{
				double ptcs = ((double)m_total_volumen_cs_ocupado / (double)(m_X * m_Y * m_Z)) * 100;
				fprintf(fin3, "%s\tV\t%d\tVU\t%d\t%f\t%d\t%f\n", m_Nombre, m_total_volumen, m_total_volumen_ocupado, pt, m_total_volumen_cs_ocupado, ptcs);
			}
			else if (m_imprimir == true)
				fprintf(fin3, "%s\tV\t%d\tVU\t%d\t%f\n", m_Nombre, m_total_volumen, m_total_volumen_ocupado, pt);
			fclose(fin3);*/
			return;
		}
			//si no eliminamos perdidas
			//if (m_Spaces.Get_Flag()==true) return 
			ORIG setmin(SpaceElegido.Get_dx(), SpaceElegido.Get_dy(), SpaceElegido.Get_dz());
			//Creo ya inicialmente la configuracao 
			CONFIGURACAO Configuracao(this, setmin, 999999);
			if (m_all_bloques == true)
				m_por_bloques_ara = false; //El constructivo que funcione sin bloques porque saca mejor solución
			//Elegir configuración para ese espacio
			if (m_por_bloques == false && m_por_bloques_ara == false)
				ElegirConfiguracao(SpaceElegido, Configuracao);
			else
			{
				if (m_por_bloques == true)
					ElegirConfiguracaoBloque(SpaceElegido, Configuracao);
				else
					ElegirConfiguracaoBloqueAra(SpaceElegido, Configuracao);
			}
			if (Configuracao.Get_Id() == 99999)
			{
				SpaceElegido.Set_Flag(true);
				continue;
			}
			//Actualizar lista de bloques
	//		DibujarSolucion(m_Spaces,m_Configuracaos);
			if (m_por_bloques == false && m_por_bloques_ara == false)
				ActualizarListas(SpaceElegido, Configuracao);
			else
			{
				if (m_por_bloques_ara == true)
					ActualizarListasAra(SpaceElegido, Configuracao);
				else
				{
					if (Configuracao.Get_Id() < 1000) //Si es menor que 1000 es pieza o capa de piezas, si es mayor o igual es bloque o capa de bloques
						ActualizarListas(SpaceElegido, Configuracao);
					else
						ActualizarListasBloque(SpaceElegido, Configuracao, false);
				}
			}
			/*std::list<SPACE> ::iterator it;
			if (m_mejora_local == true && ya_mejorado == false && m_total_volumen_ocupado >= m_val_quita * m_max_total_volumen_ocupado)
			{
				ya_mejorado = true;
				m_Spaces_Mejora = m_Spaces;
				m_Configuracaos_Mejora = m_Configuracaos;
				m_total_volumen_ocupado_mejora = m_total_volumen_ocupado;
				for (register int m = 0; m < m_Q; m++)
				{
					m_Pieces_Mejora[m] = m_Pieces[m].Get_Num();
				}
			}*/
			//Funcion que verifica si todo va bien
	//		printf("V %d VU %d %f\n",m_total_volumen,m_total_volumen_ocupado,pt);
	//	DibujarSolucion(m_Spaces,m_Configuracaos);

		}
		/*if (m_Aleatorizado == false && m_imprimir == true)
		{
			FILE* fin3;
			fin3 = fopen(m_file_to_write, "a+");
			double pt = ((double)m_total_volumen_ocupado / (double)m_total_volumen) * 100;
			fprintf(fin3, "%s\tV\t%d\tVU\t%d\t%f\n", m_Nombre, m_total_volumen, m_total_volumen_ocupado, pt);
			fclose(fin3);
		}*/

		VerificarSolucion(m_Configuracaos);

	}
//Le paso el parametro de si quiero que sea un constructivo aleatorizado
void CONTAINER::ConstructivoMC(bool aleatorizado)
{
	bool ya_mejorado=false;
	m_objetivo_vol=true;
//	if (m_tipo_orden_pieces==5)
//		m_objetivo_vol=false;
	m_ConfiguracaosMC.clear();

	m_Aleatorizado=aleatorizado;
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
	SPACE SpaceElegido(0,0,0,m_X,m_Y,m_Z,this);

	std::list< SPACE> primer_bin;
	primer_bin.push_back(Space);
	m_SpacesMC.push_back(primer_bin);
	m_Spaces=primer_bin;
	int temp=0;
	while (m_total_volumen_ocupado!=m_total_volumen)
	{	
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio
		bool posible=false;	
		ElegirSpace(SpaceElegido,posible);
		
		if (m_Spaces.size()==0 || (posible==false))
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
				m_SpacesMC.push_back(m_Spaces);
				m_Spaces=otro_bin;
				//meto las configuracaos en la lista
				std::pair< int, std::list< CONFIGURACAO> > p(thisbin,m_Configuracaos);
				InsertarOrden(m_ConfiguracaosMC,p);
//				m_ConfiguracaosMC.push_back(p);
				//borro la lista actual de configuracaos
				m_Configuracaos.clear();

				if (m_ConfiguracaosMC.size()+1==m_Best_nbins)
				{
//					m_nbins=m_ConfiguracaosMC.size();
					/*					if (m_Aleatorizado==false)
					{	
						FILE *fin3;
						fin3=fopen("Results.txt","a+");
						fprintf(fin3,"%s\t%d\t%d\n",m_Nombre,m_lb,m_ConfiguracaosMC.size()+m_bin_fijados);
						fclose(fin3);
					}
*/
//				DibujarSolucion(m_ConfiguracaosMC);
//					if (m_tipo_orden_pieces==5) printf("\n");
					return;
				}

			}
			else return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);
		if (m_tipo_orden_pieces==50 && SpaceElegido.Get_dx()==m_X && SpaceElegido.Get_dy()==m_Y && SpaceElegido.Get_dz()==m_Z)
		{
			int max=0;
			int elegido=0;
			for (int register j=0;j<m_Q;j++)
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
			Configuracao.CambiarConfiguracao(1,1,1,1,m_Pieces[elegido].Get_x(),m_Pieces[elegido].Get_y(),m_Pieces[elegido].Get_z(), m_Pieces[elegido].Get_Id(),0);
		}
		else
		//Elegir configuración para ese espacio
		ElegirConfiguracao(SpaceElegido,Configuracao);

		if (Configuracao.Get_Id()==99999)
		{
			EliminarSpace(m_Spaces,SpaceElegido);
//			SpaceElegido.Set_Flag(true);
			continue;
		}
		//Actualizar lista de bloques
//		DibujarSolucion(m_Spaces,m_Configuracaos);
//		if (Configuracao.Get_Num()>1 )
//			printf ("mas de uno Cons");

		ActualizarListas(SpaceElegido,Configuracao);
//		ComprobarTodosPosible();

/*		if (m_mejora_local==true && ya_mejorado==false && m_total_volumen_ocupado>=m_val_quita*m_max_total_volumen_ocupado)
		{
			ya_mejorado=true;
			m_Spaces_Mejora=m_Spaces;
			m_Configuracaos_Mejora=m_Configuracaos;
			m_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
			for (register int m=0;m<m_Q;m++)
			{
				m_Pieces_Mejora[m]=m_Pieces[m].Get_Num();
			}
		}
*/		//Funcion que verifica si todo va bien
//		printf("V %d VU %d %f\n",m_total_volumen,m_total_volumen_ocupado,pt);
//	DibujarSolucion(m_Spaces,m_Configuracaos);

//	PintarPieces();
	}
	//meto las configuracaos en la lista
	int thisbin=m_total_volumen_ocupado-temp;
	std::pair< int, std::list< CONFIGURACAO> > p(thisbin,m_Configuracaos);
	InsertarOrden(m_ConfiguracaosMC,p);
//	m_ConfiguracaosMC.push_back(p);
	m_nbins=m_ConfiguracaosMC.size();
//	DibujarSolucion(m_ConfiguracaosMC);
//	if (m_Aleatorizado==false)
//	{	
//		FILE *fin3;
//		fin3=fopen("Results.txt","a+");
//		fprintf(fin3,"%s\t%d\t%d\t%d\n",m_Nombre,m_lb,m_ConfiguracaosMC.size()+m_bin_fijados,m_bin_fijados);
//		fclose(fin3);
//	}

//	VerificarSolucion(m_Configuracaos);

}

void CONTAINER::EliminarSpace(std::list < SPACE > &lista, SPACE &eSpace)
{
	std::list < SPACE > ::iterator it;
	for (it = lista.begin();it!=lista.end();)
	{
		if ((*it).Get_x1()==eSpace.Get_x1() && (*it).Get_x2()==eSpace.Get_x2() &&
		(*it).Get_y1()==eSpace.Get_y1() && (*it).Get_y2()==eSpace.Get_y2() &&
		(*it).Get_z1()==eSpace.Get_z1() && (*it).Get_z2()==eSpace.Get_z2() ) 
		{
			lista.erase(it);
			break;
		}
		++it;
	}
}
//Le paso el parametro de si quiero que sea un constructivo aleatorizado
void CONTAINER::ConstructivoMC_TJuntos(bool aleatorizado)
{
	bool ya_mejorado=false;
	m_objetivo_vol=true;
	m_ConfiguracaosMC.clear();

	m_Aleatorizado=aleatorizado;
	m_SpacesMC.clear();
	//Inicialmente meto un espacio que es todo el contenedor
	for (int register k=1;k<m_Best_nbins;k++)
	{
		SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
		std::list< SPACE> primer_bin;
		primer_bin.push_back(Space);
		m_SpacesMC.push_back(primer_bin);
	}
//	m_Spaces=primer_bin;
	int temp=0;
	while (m_total_volumen_ocupado!=m_total_volumen)
	{	
		int num=0;
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio
		SPACE &SpaceElegido=ElegirSpaceMovimientoGlobal(m_SpacesMC,num);
		if (m_SpacesMC.size()==0 || SpaceElegido.Get_Flag()==true )
		{
			VerificarSolucionMC(m_ConfiguracaosMC);
			if (m_total_volumen_ocupado==m_total_volumen)
			{
				m_nbins=m_ConfiguracaosMC.size();
			}
			Ordenar(m_ConfiguracaosMC);
			DibujarSolucion(m_ConfiguracaosMC);
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Elegir configuración para ese espacio
		ElegirConfiguracao(SpaceElegido,Configuracao,num);

		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}
		//Actualizar lista de bloques
//		DibujarSolucion(m_Spaces,m_Configuracaos);

		ActualizarListas(SpaceElegido,Configuracao,num);
//		ComprobarTodosPosible();

/*		if (m_mejora_local==true && ya_mejorado==false && m_total_volumen_ocupado>=m_val_quita*m_max_total_volumen_ocupado)
		{
			ya_mejorado=true;
			m_Spaces_Mejora=m_Spaces;
			m_Configuracaos_Mejora=m_Configuracaos;
			m_total_volumen_ocupado_mejora=m_total_volumen_ocupado;
			for (register int m=0;m<m_Q;m++)
			{
				m_Pieces_Mejora[m]=m_Pieces[m].Get_Num();
			}
		}
*/		//Funcion que verifica si todo va bien
//		printf("V %d VU %d %f\n",m_total_volumen,m_total_volumen_ocupado,pt);
//	DibujarSolucion(m_Spaces,m_Configuracaos);

	}
	if (m_total_volumen_ocupado==m_total_volumen)
	{
		m_nbins=m_ConfiguracaosMC.size();
	}
			Ordenar(m_ConfiguracaosMC);

	VerificarSolucionMC(m_ConfiguracaosMC);


}



//Habría que cambiarla para que haga busqueda binaria
//FALTA
void CONTAINER::InsertarOrden(std::list< std::pair< int, std::list< CONFIGURACAO > > > &Lista, std::pair< int, std::list< CONFIGURACAO > > &nuevo)
{
	//Por si solamente hay uno
	if (Lista.size()==0)
	{
		Lista.push_back(nuevo);
		return;
	}

	std::list< std::pair< int, std::list< CONFIGURACAO > > > ::iterator itl;
	for (itl=Lista.begin();itl!=Lista.end();itl++)
	{
		if ((*itl).first<nuevo.first)
		{
			Lista.insert(itl,nuevo);
			return;
		}
	}
	//Si no hay ninguno más pequeño al final
	Lista.push_back(nuevo);
}
//void CONTAINER::InsertarOrdenConfiguracaos(std::list< std::list< CONFIGURACAO> > &lista, std::l
void CONTAINER::Grasp()
{
	srand(1);
	for (int ikl=0;ikl<m_Q;ikl++)
		m_Pieces_Mejora.push_back(0);
	m_PeorSolucion_volumen=999999999;
	m_objetivo_vol=true;
	m_Delta=0.9;
	m_max_iteraciones_Grasp=5000;
	
	//Valores para el reactive
	//Guardo las veces que ha pasado
	//Variables para el reactive
	std::vector< int > vec_veces(10);
	//Los valores
	std::vector< double > vec_valor(10);
	//Las buenas
	std::vector< double > vec_buenas(10);
	m_hastavalor=0;

	for (m_iter_actual=0;m_iter_actual<m_max_iteraciones_Grasp;m_iter_actual++)
	{
		//Dejar todo limpio
		m_Spaces.clear();
		m_Configuracaos.clear();
		m_total_volumen_ocupado=0;
		for (int j=0;j<m_Q;j++)
			m_Pieces[j].Set_Num(0);
		MinimaDimension();
//		int alea=get_random(1,9);
//		printf(" Val %d",alea);

		//Ajusta parámetros de reactive
		ReactiveDeltaPaso1(vec_veces,vec_valor,vec_buenas);
//		m_Delta
		//Ejecutar constructivo
//		printf(" %f", m_Delta);
		Constructivo(true);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
		{

//			DibujarSolucion(m_Spaces,m_Configuracaos);
			m_max_total_volumen_ocupado=m_total_volumen_ocupado;
//			DibujarSolucion(m_Spaces,m_Configuracaos);
	
					m_Best_Configuracao=m_Configuracaos;
			DibujarSolucion(m_Spaces,m_Best_Configuracao);
//			EscribirSolucion();		
		}
		//Busqueda Local
		if (m_mejora_local==true)
		{
				//Si la solución es muy buena lo hago en otro caso sNO
			int umbral=m_PeorSolucion_volumen+((0.5)*(double)(m_max_total_volumen_ocupado-m_PeorSolucion_volumen));
			if (m_total_volumen_ocupado>=(umbral))
			{
				//Mejora con orig
				if (m_tipo_mejora==0 ||m_tipo_mejora==2)
				{
					MejoraLocal(false);
					if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
					{

//					DibujarSolucion(m_Spaces,m_Configuracaos);
						m_max_total_volumen_ocupado=m_total_volumen_ocupado;
						m_Best_Configuracao=m_Configuracaos;
					}
				}
				if (m_tipo_mejora==1 ||m_tipo_mejora==2)
				{
				//Si la solución es muy buena lo hago en otro caso sNO
					VerificarSolucion(m_Best_Configuracao);
					//mejora con vol
					MejoraLocal(true);
					if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
					{

//						DibujarSolucion(m_Spaces,m_Configuracaos);
						m_Best_Configuracao=m_Configuracaos;

						m_max_total_volumen_ocupado=m_total_volumen_ocupado;
					}
				}
				if (m_tipo_mejora==3 )
				{
				//Si la solución es muy buena lo hago en otro caso sNO
					m_objetivo_capas=false;
					VerificarSolucion(m_Best_Configuracao);
					//mejora con vol
					MejoraLocal(true);
					if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
					{

//						DibujarSolucion(m_Spaces,m_Configuracaos);
						m_Best_Configuracao=m_Configuracaos;

						m_max_total_volumen_ocupado=m_total_volumen_ocupado;
					}
					m_objetivo_capas=true;
				}

			}
//			VerificarSolucion();
		}
		ReactiveDeltaPaso2(vec_veces,vec_valor);
		VerificarSolucion(m_Best_Configuracao);
//		DibujarSolucion(m_Spaces,m_Configuracaos);
		
	}
	//Esta funcion me hecha para abajo y a la derecha todas las piezecita
	//que tengo
//	CompactarConfiguracaos(m_Best_Configuracao);
	//Los paso para poder verificar la solucion
	//me la construye en el otro 
	//y me borra el que tengo 
	//tiene un parametro que es si ha sido compactada o no 
	//si no puedo buscar solo en las esquinas si es al reves en todas partes
//	PintarSolucion(m_Best_Configuracao);
//	ConstruirSolucion(m_Best_Configuracao,true);
	
//	EscribirSolucionLatex(m_Best_Configuracao);
	m_fintime=clock();
	m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

	FILE *fin3;
	fin3=fopen(m_file_to_write,"a+");
	double pt=((double)m_max_total_volumen_ocupado/(double)m_total_volumen)*100;
	fprintf(fin3,"%s\tV\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%f\n",m_Nombre,m_total_volumen,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_val_quita);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
	fclose(fin3);


}
void CONTAINER::GraspUnBin()
{
	m_PeorSolucion_volumen=999999999;
	m_objetivo_vol=true;
	m_Delta=0.9;
	std::list< CONFIGURACAO >::iterator itB1;
	std::list< std::pair<int, std::list< CONFIGURACAO > > >::iterator itB2;

	//Valores para el reactive
	//Guardo las veces que ha pasado
	//Variables para el reactive
	std::vector< int > vec_veces(10);
	//Los valores
	std::vector< double > vec_valor(10);
	//Las buenas
	std::vector< double > vec_buenas(10);
	m_hastavalor=0;

	for (m_iter_actual=0;m_iter_actual<m_max_iteraciones_Grasp;m_iter_actual++)
	{
		//Tengo que tener un vector suplementario o algo asi
		//Dejar todo limpio
		m_Spaces.clear();
		m_Configuracaos.clear();
		m_total_volumen_ocupado=0;
		for (int j=0;j<m_Q;j++)
			m_Pieces[j].Set_Num(0);
		for (itB2=m_ConfiguracaosMC.begin();itB2!=m_ConfiguracaosMC.end();itB2++)
		{
			for(itB1=(*itB2).second.begin();itB1!=(*itB2).second.end();itB1++)
			{	

				m_Pieces[(*itB1).Get_Id()].Add_Num((*itB1).Get_Num());
			}
		}
		MinimaDimensionMC();
//		int alea=get_random(1,9);
//		printf(" Val %d",alea);

		//Ajusta parámetros de reactive
		ReactiveDeltaPaso1(vec_veces,vec_valor,vec_buenas);
//		m_Delta
		//Ejecutar constructivo
//		printf(" %f", m_Delta);
		Constructivo(true);
		if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
		{

//			DibujarSolucion(m_Spaces,m_Configuracaos);
			m_max_total_volumen_ocupado=m_total_volumen_ocupado;
//			DibujarSolucion(m_Spaces,m_Configuracaos);
	
					m_Best_Configuracao=m_Configuracaos;
			DibujarSolucion(m_Spaces,m_Best_Configuracao);
//			EscribirSolucion();		
		}
		//Busqueda Local
		if (m_mejora_local==true)
		{
				//Si la solución es muy buena lo hago en otro caso sNO
			int umbral=m_PeorSolucion_volumen+((0.5)*(double)(m_max_total_volumen_ocupado-m_PeorSolucion_volumen));
			if (m_total_volumen_ocupado>=(umbral))
			{
				//Mejora con orig
				if (m_tipo_mejora==0 ||m_tipo_mejora==2)
				{
					MejoraLocal(false);
					if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
					{

//					DibujarSolucion(m_Spaces,m_Configuracaos);
						m_max_total_volumen_ocupado=m_total_volumen_ocupado;
						m_Best_Configuracao=m_Configuracaos;
					}
				}
				if (m_tipo_mejora==1 ||m_tipo_mejora==2)
				{
				//Si la solución es muy buena lo hago en otro caso sNO
//					VerificarSolucion(m_Best_Configuracao);
					//mejora con vol
					MejoraLocal(true);
					if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
					{

//						DibujarSolucion(m_Spaces,m_Configuracaos);
						m_Best_Configuracao=m_Configuracaos;

						m_max_total_volumen_ocupado=m_total_volumen_ocupado;
					}
				}
				if (m_tipo_mejora==3 )
				{
				//Si la solución es muy buena lo hago en otro caso sNO
					m_objetivo_capas=false;
//					VerificarSolucion(m_Best_Configuracao);
					//mejora con vol
					MejoraLocal(true);
					if (m_total_volumen_ocupado>m_max_total_volumen_ocupado)
					{

//						DibujarSolucion(m_Spaces,m_Configuracaos);
						m_Best_Configuracao=m_Configuracaos;

						m_max_total_volumen_ocupado=m_total_volumen_ocupado;
					}
					m_objetivo_capas=true;
				}

			}
//			VerificarSolucion();
		}
		ReactiveDeltaPaso2(vec_veces,vec_valor);
//		VerificarSolucion(m_Configuracaos);
//		DibujarSolucion(m_Spaces,m_Configuracaos);
		
	}
	


}
//esta funcion rellena cada bin con el grasp para un container
void CONTAINER::GraspMC_PorBin()
{
	srand(1);
	for (int ikl=0;ikl<m_Q;ikl++)
		m_Pieces_Mejora.push_back(0);
	m_por_bin=true;
	m_max_iteraciones_Grasp=5000;
	int total_volumen=0;
	std::list< CONFIGURACAO >::iterator itB1;
	std::list< std::pair< int, std::list< CONFIGURACAO > > >::iterator itB2;
	while (total_volumen!=m_total_volumen)
	{
		m_total_volumen_ocupado=0;
		m_max_total_volumen_ocupado=0;
		m_multicontainer=false;
		//Tengo que pasarle el valor que es para que cuando lo vea pare
		GraspUnBin();
		total_volumen+=m_max_total_volumen_ocupado;
		//Dejo todos como estan
		for (int ikl=0;ikl<m_Q;ikl++)
			m_Pieces[0].Set_Num(0);

		m_multicontainer=true;
		//Comprobar que todas tenga el numero de piezas que pone
		for(itB1=m_Best_Configuracao.begin();itB1!=m_Best_Configuracao.end();itB1++)
		{	

			m_Pieces[(*itB1).Get_Id()].Add_Num((*itB1).Get_Num());
		}
		for (itB2=m_ConfiguracaosMC.begin();itB2!=m_ConfiguracaosMC.end();itB2++)
		{
			for(itB1=(*itB2).second.begin();itB1!=(*itB2).second.end();itB1++)
			{	

				m_Pieces[(*itB1).Get_Id()].Add_Num((*itB1).Get_Num());
			}
		}
		m_SpacesMC.push_back(m_Spaces);
		//Mirar esto 
		int thisbin=m_total_volumen_ocupado;
		std::pair< int, std::list< CONFIGURACAO> > p(thisbin,m_Best_Configuracao);

		m_ConfiguracaosMC.push_back(p);
		m_Spaces.clear();
		m_Configuracaos.clear();


	}
	m_nbins=m_Configuracaos.size();
	m_fintime=clock();
	m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

	FILE *fin3;
	fin3=fopen(m_file_to_write,"a+");
	fprintf(fin3,"%s\t%d\t%d\t%f\n",m_Nombre,m_lb,m_nbins,m_tiempo);
//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
	fclose(fin3);

	//
}
void CONTAINER::GraspMC_Global()
{
//	bool Juntos=false;
	//Aqui inicializo el vector de piezas que hay fuera
	for (int ikl=0;ikl<m_Q;ikl++)
		m_Pieces_Mejora.push_back(0);
	for (int ikl=0;ikl<m_Q;ikl++)
		m_frecuencias.push_back(0);
	m_Pieces_Tabu.clear();
	for (int j=0;j<m_Q;j++)
	{
		m_Pieces_Tabu.push_back(0);
		m_Pieces_Tabu2.push_back(0);
	}

	m_PeorSolucion_volumen=999999999;
	m_objetivo_vol=true;
	m_Delta=0.9;
	int kk1=0;
	m_max_iteraciones_Grasp=50000;
//	m_eliminar_espacios=false;
	//Valores para el reactive
	//Guardo las veces que ha pasado
	//Variables para el reactive
	std::vector< int > vec_veces(10);
	//Los valores
	std::vector< double > vec_valor(10);
	//Las buenas
	std::vector< double > vec_buenas(10);
	m_hastavalor=0;

	m_fintime=clock();
	m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;
	if (m_Q==0)
		m_Best_nbins=0;
	m_eliminar_espacios=true;
	for (m_iter_actual=0;m_iter_actual<m_max_iteraciones_Grasp && (m_Best_nbins+m_bin_fijados)>m_lb && m_tiempo<m_time_final;m_iter_actual++)
	{
		m_tipo_origen=get_random(0,2);
		//Dejar todo limpio
		m_Spaces.clear();
		m_Configuracaos.clear();
		m_total_volumen_ocupado=0;
		for (int j=0;j<m_Q;j++)
			m_Pieces[j].Set_Num(0);
		MinimaDimensionMC();
//		int alea=get_random(1,9);


		//Ajusta parámetros de reactive
//		if (m_iter_actual==500) printf("eee1");
		m_multicontainer=false;
		ReactiveDeltaPaso1(vec_veces,vec_valor,vec_buenas);
		m_multicontainer=true;
//		if (m_iter_actual==500) printf("eee2");

//		m_Delta
		//Ejecutar constructivo
		Diversificar();
		if (m_juntos==false || m_iter_actual<=1)
			ConstructivoMC(true);
		else
			ConstructivoMC_TJuntos(true);
//		RellenarVariosBinGlobal();
//		if (m_tipo_orden_pieces==5 || m_iter_actual>=500 )
		DibujarSolucion(m_ConfiguracaosMC);		
		VerificarSolucionMC(m_ConfiguracaosMC);
		//guardo las frecuencias

//		Actualizo el vector de frecuencias de las que estan fuera si hay mas de una
//		pues meto mas de una
//		if (m_iter_actual%1000==0)
		printf(" Iter %d  \t%d \t%d\n",m_iter_actual,m_Best_nbins,m_BestSolution_ConfiguracaoMC.size());
//		VerificarSolucionMC(m_ConfiguracaosMC);
//		printf("%d\n",m_nbins);
		if (m_nbins<m_Best_nbins )
		{
			m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
			m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
			m_Best_nbins=m_nbins;
			m_iter_best_actual=m_iter_actual;
			m_max_total_volumen_ocupado=0;
		}
//		m_multicontainer=false;
//		ReactiveDeltaPaso2(vec_veces,vec_valor);
//		m_multicontainer=true;
// metemos las frecuencias de las piezas que no están en la solucion
		if (m_tipo_orden_pieces!=5)
		{
			for( int register kkk=0;kkk<m_Q;kkk++)
			{
				m_frecuencias[kkk]+=m_Pieces[kkk].Get_q()-m_Pieces[kkk].Get_Num();
			}
		}


		//Busqueda Local
		if (m_tipo_mejora>=1 && m_mejora_local==true && m_ConfiguracaosMC.size()!=m_Best_nbins)
		{
//			int umbral=m_PeorSolucion_volumen+((0.7)*(double)(m_total_volumen-m_PeorSolucion_volumen));

//			if (m_total_volumen_ocupado>max(((m_total_volumen)-((double)(m_total_volumen)/((double)2*(double)(m_Best_nbins-1)))),((double)0.95*(double)m_total_volumen)))
//			if (m_total_volumen_ocupado>((double)0.95*(double)m_total_volumen))
//			if (m_total_volumen_ocupado>=umbral)
//			if (m_total_volumen_ocupado>((m_total_volumen)-((double)(m_total_volumen)/(double)(m_Best_nbins-1))))
			if ( ((m_total_volumen_ocupado>((m_total_volumen)-((double)(m_total_volumen)/(double)(m_Best_nbins)))) &&
				(m_total_volumen_ocupado>((double)0.95*(double)m_total_volumen))))

			{
				kk1++;
			//^*****************************
inicio:
				int temp=m_total_volumen_ocupado;
				int temp2=m_total_volumen_ocupado;
				if (m_tipo_mejora==1 || m_tipo_mejora>=9)
//				MejoraLocalMCQuitarUltimosCadaBin(false);
				VerificarSolucionMC(m_ConfiguracaosMC);
				
//				MejoraLocalMCQuitarUltimos(false,false);
				//Si estan puestas todas las piezas por tanto he mejorado lo que 
				//tenia entonces
				if (m_total_volumen_ocupado==m_total_volumen)
				{
						for (register int k=0;k<100;k++)
						printf("Ultimos kjklj %d",m_iter_actual);
					m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
					m_Best_nbins=m_ConfiguracaosMC.size();
					m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
					m_iter_best_actual=m_iter_actual;
					m_max_total_volumen_ocupado=0;
					continue;

				}
				else
				{
					if (m_tipo_mejora==11 && m_total_volumen_ocupado>temp )
						goto inicio;

					if (m_tipo_mejora==2 || m_tipo_mejora>=9)
//				MejoraLocalMCQuitarUltimosPartir(false);
					MejoraLocalMCQuitarUltimos(false,false);
					VerificarSolucionMC(m_ConfiguracaosMC);
					//Si estan puestas todas las piezas por tanto he mejorado lo que 
					//tenia entonces
					if (m_total_volumen_ocupado==m_total_volumen)
					{
						m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
						m_Best_nbins=m_ConfiguracaosMC.size();
						m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
						m_iter_best_actual=m_iter_actual;
						m_max_total_volumen_ocupado=0;
						continue;

					}

					else
					{
					if (m_tipo_mejora==11 && m_total_volumen_ocupado>temp )
						goto inicio;

						if (m_tipo_mejora==3 || m_tipo_mejora>=9)
	//				MejoraLocalMCQuitarUltimosPartir(false);
//						MejoraLocalMCQuitarUltimosPartir(false);
						VerificarSolucionMC(m_ConfiguracaosMC);

					//Si estan puestas todas las piezas por tanto he mejorado lo que 
				//tenia entonces
						if (m_total_volumen_ocupado==m_total_volumen)
						{
							m_Best_ConfiguracaoMC=m_ConfiguracaosMC; 
							m_Best_nbins=m_ConfiguracaosMC.size();
							m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
							m_iter_best_actual=m_iter_actual;
							m_max_total_volumen_ocupado=0;
							continue;

						}

						else
						{
					if (m_tipo_mejora==11 && m_total_volumen_ocupado>temp )
						goto inicio;
//							VerificarSolucionMC(m_ConfiguracaosMC);
							m_objetivo_vol=false;

							if (m_tipo_mejora==4 || m_tipo_mejora>=9)
//								MejoraLocalMCQuitarUltimosCadaBin(false);
								VerificarSolucionMC(m_ConfiguracaosMC);
							if (m_total_volumen_ocupado==m_total_volumen)
							{
								for (register int k=0;k<100;k++)
									printf("Ultimos cada bin %d",m_iter_actual);
								m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
								m_Best_nbins=m_ConfiguracaosMC.size();
								m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
								m_iter_best_actual=m_iter_actual;
								m_max_total_volumen_ocupado=0;
								continue;

							}
							else
							{
					if (m_tipo_mejora==11 && m_total_volumen_ocupado>temp )
						goto inicio;
//								VerificarSolucionMC(m_ConfiguracaosMC);
//					m_objetivo_vol=false;

								if (m_tipo_mejora==5 || m_tipo_mejora>=9)
//									MejoraLocalMCQuitarUltimosPartir(false);
									VerificarSolucionMC(m_ConfiguracaosMC);
//					m_objetivo_vol=true;
								if (m_total_volumen_ocupado==m_total_volumen)
								{
									for (register int k=0;k<100;k++)
									printf("UltimosPartir5");
									m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
									m_Best_nbins=m_ConfiguracaosMC.size();
									m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
									m_iter_best_actual=m_iter_actual;
									m_max_total_volumen_ocupado=0;
									continue;

								}
								else
								{
//nuevo
//					if (m_iter_actual==2)
//						EscribirSolucionLatex2DMC(m_ConfiguracaosMC);
					if (m_tipo_mejora==11 && m_total_volumen_ocupado>temp )
						goto inicio;
									if (m_tipo_mejora==6|| m_tipo_mejora>=9)
									{
										m_objetivo_vol=false;
										MejoraLocalMCQuitarUltimos(false,false);
										VerificarSolucionMC(m_ConfiguracaosMC);
									}
									//Si estan puestas todas las piezas por tanto he mejorado lo que 
									//tenia entonces
									if (m_total_volumen_ocupado==m_total_volumen)
									{
										m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
										m_max_total_volumen_ocupado=0;
										m_Best_nbins=m_ConfiguracaosMC.size();
										m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
										m_iter_best_actual=m_iter_actual;
									}
									else
									{
					if (m_tipo_mejora==11 && m_total_volumen_ocupado>temp )
						goto inicio;
										if (m_tipo_mejora==7|| m_tipo_mejora>=9)
										{
											m_objetivo_vol=true;
											//true un solo movimiento
											if (m_tipo_mejora==7 || m_tipo_mejora==9)
											MejoraLocalMCQuitarDosBin(false);
											else MejoraLocalMCQuitarDosBin(true);
											VerificarSolucionMC(m_ConfiguracaosMC);
											}
										//Si estan puestas todas las piezas por tanto he mejorado lo que 
										//tenia entonces
										if (m_total_volumen_ocupado==m_total_volumen)
										{
											m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
											m_max_total_volumen_ocupado=0;
											m_Best_nbins=m_ConfiguracaosMC.size();
											m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
											m_iter_best_actual=m_iter_actual;
										}
										else
										{
											if (m_tipo_mejora==11 && m_total_volumen_ocupado>temp )
												goto inicio;
											if (m_tipo_mejora==8 || m_tipo_mejora>=9)
											{
												m_objetivo_vol=false;
												//true es un solo movimiento
												if (m_tipo_mejora==8 || m_tipo_mejora==9)
												MejoraLocalMCQuitarDosBin(false);
												else
												MejoraLocalMCQuitarDosBin(true);
												VerificarSolucionMC(m_ConfiguracaosMC);
											}
											//Si estan puestas todas las piezas por tanto he mejorado lo que 
											//tenia entonces
											if (m_total_volumen_ocupado==m_total_volumen)
											{
												m_Best_ConfiguracaoMC=m_ConfiguracaosMC;
												m_max_total_volumen_ocupado=0;

												m_Best_nbins=m_ConfiguracaosMC.size();
												m_BestSolution_ConfiguracaoMC=m_ConfiguracaosMC;
												m_iter_best_actual=m_iter_actual;
											}
											if ((m_tipo_mejora==11 || m_tipo_mejora==13) && m_total_volumen_ocupado>temp )
												goto inicio;
											if ((m_tipo_mejora==10 || m_tipo_mejora==12) && m_total_volumen_ocupado>temp2 )
											{
//												printf("\nIter %d Mejora",m_iter_actual);
												goto inicio;
											}
/*											else
											{
												if (m_tipo_mejora==-1 || m_tipo_mejora>=11)
												{
													VNDMC(false);
												}
												//Si estan puestas todas las piezas por tanto he mejorado lo que 
												//tenia entonces
												if (m_total_volumen_ocupado==m_total_volumen)
												{
													m_max_total_volumen_ocupado=0;
													m_Best_nbins=m_ConfiguracaosMC.size();
													m_iter_best_actual=m_iter_actual;
												}

											}
*/
  /*						else
						{
						}*/
										}
									}
								}
			
							}
						}

					}


				}


			}

//			VerificarSolucion();
		}
//		printf("%d %d %d\n",m_total_volumen_ocupado,m_max_total_volumen_ocupado,m_total_volumen);
//		VerificarSolucionMC(m_ConfiguracaosMC);
		m_multicontainer=false;
		ReactiveDeltaPaso2(vec_veces,vec_valor);
		m_multicontainer=true;

//		VerificarSolucion(m_Best_Configuracao);
//		DibujarSolucion(m_Spaces,m_Configuracaos);
		m_fintime=clock();
		m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

	}
/*	printf("Informacion final\n");
	for( int register kkk=0;kkk<m_Q;kkk++)
	{
		printf("%d\t%d\n",kkk,m_frecuencias[kkk]);
//		m_frecuencias[kkk]+=m_Pieces[kkk].Get_q()-m_Pieces[kkk].Get_Num();
	}
*/
	//Esta funcion me hecha para abajo y a la derecha todas las piezecita
	//que tengo
//	CompactarConfiguracaos(m_Best_Configuracao);
	//Los paso para poder verificar la solucion
	//me la construye en el otro 
	//y me borra el que tengo 
	//tiene un parametro que es si ha sido compactada o no 

//	EscribirSolucion(m_Best_Configuracao);
//	ConstruirSolucion(m_Best_Configuracao,true);
	EscribirSolucion3DMC(m_BestSolution_ConfiguracaoMC	);
//	EscribirSolucionLatex(m_Best_Configuracao);
//	printf("Gana Cada Bin %d\n", gananciaCadaBin);
//	printf("Gana   Partir %d\n", gananciaPartir);
//	printf("Gana  Ultimos %d\n", gananciaUltimos);
	m_fintime=clock();
	m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;
//	double kktiempo=((double)(m_fintime2-m_inicio))/CLOCKS_PER_SEC;
	FILE *fin3;
	fin3=fopen(m_file_to_write,"a+");
//	fprintf(fin3,"%s\t%d\t%d\t%d\t%f\t%f\t%d\t%d\n",m_Nombre,m_lb,m_Best_nbins+m_bin_fijados,m_iter_best_actual,m_tiempo,kktiempo,kk1,m_iter_actual);
//	fprintf(fin3,"%s\tLB\t%d\tBest\t%d\t%d\t%f\t%d\t%d\t%d\n",m_Nombre,m_lb,m_Best_nbins+m_bin_fijados,m_iter_best_actual,m_tiempo,kk1,m_iter_actual,m_tipo_mejora);
	fprintf(fin3, "%s\tLB\t%d\tBest\t%d\tIterBest\t%d\tTime\t%f\tTotalIter\t%d\n", m_Nombre, m_lb, m_Best_nbins + m_bin_fijados, m_iter_best_actual, m_tiempo,  m_iter_actual);

//	fprintf(fin3,"%s\tV\t%d\tVNU\t%d\tVU\t%d\t%f\t%f\tm1\t%f\tm2\t%f\t%d\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,m_max_total_volumen_ocupado,pt,m_tiempo,m_medida1,m_medida2,m_tipo_mejora);
	fclose(fin3);


}
void CONTAINER::MejoraLocal(bool fobjetivo)
{
	//Tengo que rellenar con la misma funcion 
	//en principio los rectangulitos que tengo antes debe
	//ser una muy parecida al Constructivo
	m_objetivo_vol=fobjetivo;

	m_Aleatorizado=false;
	//Aqui ya tengo los espacios
	//Tengo que poner la solucion como estaba anteriormente
	//esto lo tengo en un vector de int en cada posicion
	//cuantas habia utilizado de esa pieza
	m_total_volumen_ocupado=m_total_volumen_ocupado_mejora;
	m_Configuracaos=m_Configuracaos_Mejora;
	m_Spaces=m_Spaces_Mejora;
	for (register int ki=0;ki<m_Q;ki++)
	{
		//Pongo en cada pieza las que tengo
		m_Pieces[ki].Set_Num(m_Pieces_Mejora[ki]);
	}
//	m_Pieces_Mejora.clear();
	while (m_Spaces.size()>0)
	{	
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio
		SPACE &SpaceElegido=ElegirSpace();
		if (m_Spaces.size()==0) return;
//		if (SpaceElegido.Get_Flag()==true)
//			return;
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Elegir configuración para ese espacio
		ElegirConfiguracao(SpaceElegido,Configuracao);
		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}
		//Actualizar lista de bloques
//		DibujarSolucion(m_Spaces,m_Configuracaos);
		ActualizarListas(SpaceElegido,Configuracao);
		//Funcion que verifica si todo va bien
//		double pt=((double)m_total_volumen_ocupado/(double)m_total_volumen)*100;
//		printf("V %d VU %d %f\n",m_total_volumen,m_total_volumen_ocupado,pt);

	}
	VerificarSolucion(m_Best_Configuracao);
}
void CONTAINER::CompactarConfiguracaos(std::list<CONFIGURACAO> &lista)
{
	VerificarSolucion(lista);
	
//	PintarSolucion(lista);
	m_total_volumen_ocupado=m_max_total_volumen_ocupado;
	//fijo a que haga almenos una en cada sentido
	bool movido=true;
	short int sentido=0;
	DibujarSolucion(m_Spaces,lista);

	movido=FuerzaDeGravedad(lista,sentido);
//	PintarSolucion(lista);
	DibujarSolucion(m_Spaces,lista);
	m_Spaces.clear();
	m_Configuracaos=lista;
	VerificarSolucion(m_Configuracaos);

	sentido=1;
	movido=true;
	int parar=0;
	while (parar<3)
	{
		movido=FuerzaDeGravedad(lista,sentido);

		if (sentido==0)
			sentido=1;
		else
			sentido=0;
			if (sentido==1)
				
				sentido=2;
			else
				sentido=0;
			DibujarSolucion(m_Spaces,lista);
		if (movido==false)
			parar++;
		else
		{
			parar=0;
			movido=false;
		}
	}
	/*printf("\n");*/
	m_Spaces.clear();
	m_Configuracaos=lista;
	VerificarSolucion(m_Configuracaos);

	//Una vez hecho esta paso a la individual
	sentido=0;
//	PintarSolucion(lista);
	movido=FuerzaDeGravedadIndividual(lista,sentido);
	m_Spaces.clear();
	VerificarSolucion(m_Configuracaos);
//	PintarSolucion(lista);

	sentido=1;
	movido=true;
	parar=0;
	while (parar<3)
	{

//	PintarSolucion(lista);
		/*printf("una");*/
		movido=FuerzaDeGravedadIndividual(lista,sentido);

		if (sentido==0)
			sentido=1;
		else
		
			if (sentido==1)
				
				sentido=2;
			else
				sentido=0;
		DibujarSolucion(m_Spaces,lista);
	m_Spaces.clear();
//	PintarSolucion(lista);
	m_Configuracaos=lista;
//	PintarSolucion(lista);

	VerificarSolucion(m_Configuracaos);
		if (movido==false)
			parar++;
		else
		{
			parar=0;
			movido=false;
		}


	}
	m_medida1=Medida1Estabilidad(lista);
	m_medida2=Medida2Estabilidad(lista);

	/*printf("\n");*/
	m_Spaces.clear();
	m_Configuracaos=lista;

	VerificarSolucion(lista);
	//si quiero hacerla en las tres direcciones



}
//DEvuelve true si ha movido algo en otro caso devuelve false
bool CONTAINER::CompactarConfiguracaosEsquinas(std::list<CONFIGURACAO> &lista, short int lugar)
{
	//La quito por que aqui no he actualizado el numero de lo que tengo
//	VerificarSolucion(lista);
//	PintarSolucion(lista);
	//if (lista.size() == 0)
	//	return false;
	m_total_volumen_ocupado=m_max_total_volumen_ocupado;
	//fijo a que haga almenos una en cada sentido
	bool movido=true;
	short int sentido=0;
	DibujarSolucion(m_Spaces,lista);
	short int dir=0;
	//es a que esquina es la que esta más cercana
	// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z) 
	//primero en la x

	//int criterio_parada=0;
	//if (m_full_supported == false)
	//	criterio_parada = 3;
	//else
	//	criterio_parada = 2;
	sentido=1;
	movido=true;
	int parar=0;
	bool movido_algo=false;
	while (parar<3)
	{
		//eje z
		if (sentido == 0 && m_full_supported==true)
		{
			parar++;
			sentido = 2;
			continue;
		}
		if (sentido==0)
		{
			if (lugar<=2 || lugar==5 || lugar==6)
				dir=0;
			else
				dir=1;
		}
		//eje x
		if (sentido==1)
		{
			if (lugar<=4)
				dir=0;
			else
				dir=1;
		}
		//eje y 
		if (sentido==2)
		{
			if (lugar==1 || lugar==3 || lugar==5 || lugar==7)
				dir=0;
			else
				dir=1;
		}

		movido=FuerzaDeGravedadEsquina(lista,lugar,sentido,dir);
		//DibujarOpenGL(lista);
		if (movido==true)
			movido_algo=true;
		if (sentido==0)
			sentido=1;
		else
			sentido = 0;
			if (sentido == 1)
				sentido = 2;
			else
				sentido = 0;
		DibujarSolucion(m_Spaces,lista);
		if (movido==false)
			parar++;
		else
		{
			parar=0;
			movido=false;
		}
	}
	return movido_algo;
//	VerificarSolucion(lista);
	//si quiero hacerla en las tres direcciones



}
//al principio
void CONTAINER::ReactiveDeltaPaso1(std::vector <int > &vec_veces, std::vector <double> &vec_valor,std::vector <double> &vec_buenas)
{
	double total=0;
	int alea=0;
	//A partir de que valor empieza es el inicio 
	//esta más para abajo he puesto de 1 a 9
	if (m_iter_actual%100==0 && m_iter_actual>0)
	{
		total=0;
		m_hastavalor=0;
		//Calculo las medias para tener todos los posibles valores
		for (int ix=1;ix<10 ;ix++)
		{	
			if (vec_veces[ix]!=0 )
			{
				//Tengo la media de lo obtenido para el Delta ix		
				double meanix=((double)vec_valor[ix]/(double)vec_veces[ix]);
				//Tengo la suma de todas las medias 
				if (m_multicontainer==false)
				total+=pow((double)(meanix-m_PeorSolucion_volumen)/(double)(m_max_total_volumen_ocupado-m_PeorSolucion_volumen),10);
				if (m_multicontainer==true)
				total+=pow((double)(meanix-m_PeorSolucion_nbins)/(double)(m_Best_nbins-m_PeorSolucion_nbins),10);
			}
		}
		for (int ix=1;ix<10 ;ix++)
		{
			if (vec_veces[ix]!=0 )
			{
				//Tengo un porcentaje de los bueno que es 
				double meanix=((double)vec_valor[ix]/(double)vec_veces[ix]);
				double evalix=0;
				if (m_multicontainer==false)
				evalix=pow((double)(meanix-m_PeorSolucion_volumen)/(double)(m_max_total_volumen_ocupado-m_PeorSolucion_volumen),10);
				if (m_multicontainer==true)
				evalix=pow((double)(meanix-m_PeorSolucion_nbins)/(double)(m_Best_nbins-m_PeorSolucion_nbins),10);
				vec_buenas[ix]=((double)evalix/(double)total)*100;
				//	
				m_hastavalor+=vec_buenas[ix];
			}
		}
		//escribe lo que ha hecho
/*		printf("\n");
		for (ix=1;ix<10;ix++)
		{
			double meanix=(((double)vec_valor[ix]/(double)vec_veces[ix]));

			printf("%d %d %f %f\n",ix,vec_veces[ix],vec_buenas[ix],meanix);
		}
*/	}

	if (m_iter_actual<100 || m_hastavalor==0)
	{
		alea=get_random(1,9);
		m_Delta=(double)alea/(double)20;

	}
	else
	{
		alea=get_random(1,m_hastavalor);
		//busco cual es el que corresponde
		int suma=0;
		for (int ix=1;ix<10 && suma<alea;ix++)
		{	
			suma+=vec_buenas[ix];
			m_Delta=(double)ix/(double)20;
		}
	}

}
//Actualizar los valores de cada indice
void CONTAINER::ReactiveDeltaPaso2(std::vector <int> &vec_veces,std::vector <double> &vec_valor)
{
	int val=m_Delta*20;
	vec_veces[val]++;
	if (m_multicontainer==false) vec_valor[val]+=m_total_volumen_ocupado;
	if (m_multicontainer==true) vec_valor[val]+=m_nbins;

	
	//Actualizo la peor solucion obtenida
	if (m_multicontainer==false && m_total_volumen_ocupado<m_PeorSolucion_volumen)
		m_PeorSolucion_volumen=m_total_volumen_ocupado;
	if (m_multicontainer==true && m_nbins>m_PeorSolucion_nbins)
		m_PeorSolucion_nbins=m_nbins;
}
//Le doy una configuracao y me reconstruye la solucion para
//tener los espacios maximales otra vez

//notar que son casos diferentes si esta compactada o no es mas facil si no esta compactada
//para que funcione correctamente compacta tiene que ser compactada en las tres dimensiones
//si no puede existir una pieza que vaya en medio de los espacios que no haya 
//empezado en ningun sitio si lo hago en X e Y pero en Z
void CONTAINER::ConstruirSolucion(std::list<CONFIGURACAO> &lista,bool compactada)
{
	m_objetivo_vol=true;
	m_Aleatorizado=false;
	m_total_volumen_ocupado=0;
	//Actualizo todos los valores de las piezas
	m_set_indices = m_set_indices_copia;
	for (int j=0;j<m_Q;j++)
		m_Pieces[j].Set_Num(0);
	MinimaDimension();
	m_Spaces.clear();
	m_Configuracaos.clear();
	//Inicialmente meto un espacio que es todo el contenedor
	SPACE Space(0,0,0,m_X,m_Y,m_Z,this);
	m_Spaces.push_back(Space);
	bool elquesea=false;
	while (m_Spaces.size()>0)
	{
		bool poner = false;
		bool elegir = false;
		//Elegir espacio
		//esta función sale si no encuentra ningún espacio

		//En esta cambia la funcion de eleccion ya que 
		//puede ser que la que elegimos ahora no sea la colocada 
		//si ha sido compactada 
		if (lista.size()==0)
			elquesea=true;

		SPACE& SpaceElegido = ElegirSpaceConstruccionNueva(elquesea);

		if (m_Spaces.size()==0 || SpaceElegido.Get_Flag()==true)
		{
			if (lista.size() != 0)
			{

				printf("Que pasa 2");
				/*for (int inkki = 0;;);*/
			}
			return;
		}
		//si no eliminamos perdidas
		//if (m_Spaces.Get_Flag()==true) return 
		ORIG setmin(SpaceElegido.Get_dx(),SpaceElegido.Get_dy(),SpaceElegido.Get_dz());
		//Creo ya inicialmente la configuracao 
		CONFIGURACAO Configuracao(this,setmin,999999);

		//Por si podemos poner mas piezas que esas

		//Elegir configuración para ese espacio
		//Poner configuracao y quitarla de la lista
		if (m_all_bloques == true)
			m_por_bloques_ara = get_random(0, 1);
		if (lista.size() == 0)
		{
			DibujarOpenGL(m_Configuracaos);
			if (m_por_bloques_ara==false && m_por_bloques==false)
				ElegirConfiguracao(SpaceElegido, Configuracao);
			else
			{
				if (m_por_bloques_ara == true)
				{
					ElegirConfiguracaoBloqueAra(SpaceElegido, Configuracao);
					elegir = true;
				}
		        else
			        ElegirConfiguracaoBloque(SpaceElegido, Configuracao);
			}
		}
		else
			PonerConfiguracao(SpaceElegido, Configuracao, lista, compactada);
		if (Configuracao.Get_Id()==99999)
		{
			SpaceElegido.Set_Flag(true);
			continue;
		}
		if (compactada==true)
		{
			//Todos a etiqueta false
			std::list<SPACE> ::iterator it;
			for (it=m_Spaces.begin();it!=m_Spaces.end();it++)
			{
				(*it).Set_Flag(false);
			}

		}
		//Actualizar lista de bloques
//		DibujarSolucion(m_Spaces,m_Configuracaos);
		if (m_por_bloques == false && (m_por_bloques_ara == false || (m_por_bloques_ara == true && elegir == false)))
		{
			ActualizarListas(SpaceElegido, Configuracao);
			//DibujarOpenGL(m_Configuracaos);
		}
		else
		{
			if (m_por_bloques_ara == true)
				ActualizarListasAra(SpaceElegido, Configuracao);
			else
			{
				if (Configuracao.Get_Id() < 1000)
				{
					ActualizarListas(SpaceElegido, Configuracao);
					//DibujarOpenGL(m_Configuracaos);
				}
				else
				{
					ActualizarListasBloque(SpaceElegido, Configuracao, poner);
					//DibujarOpenGL(m_Configuracaos);
					ComprobarTodosPosible(m_Configuracaos);
				}
			}
		}
		//DibujarOpenGL(m_Configuracaos);
	}

	VerificarSolucion(m_Configuracaos);

}
void CONTAINER::Diversificar()
{
	if (m_tipo_mejora<12) return;
	bool por_orden=false;
	m_fintime=clock();
	m_tiempo=((double)(m_fintime-m_inicio))/CLOCKS_PER_SEC;

	if (((2*m_iter_actual>m_max_iteraciones_Grasp)||((2*m_tiempo)>=m_time_final)) && m_iter_actual%500==0 && m_iter_actual>0)
//	if ( m_iter_actual%500==0 && m_iter_actual>0)
	{
		DibujarSolucion(m_ConfiguracaosMC);		
//		printf("Diver, %d",m_iter_actual);
		m_sum_freq=0;
		m_peso_diver=1;
//		printf("%d\t\n",m_iter_actual);
/*		for( int register kkk=0;kkk<m_Q;kkk++)
		{
			m_sum_freq+=m_frecuencias[kkk];
		}
*/		
		m_tipo_orden_pieces=5;
		if (por_orden==true)
		{
			m_sum_freq=0;
			m_peso_diver=1;
			for( int register kkk=0;kkk<m_Q;kkk++)
			{
				m_sum_freq+=m_frecuencias[kkk];
			}
			std::sort(m_Pieces.begin(),m_Pieces.end());
			std::vector< PIECE > ::iterator it;
			int id=0;
//		printf("Informacion cambiar\n");
//		int kkkk=0;
			for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
			{
//			printf("%d\t%d\n",id,m_frecuencias[(*it).Get_Id()]);
				(*it).Set_Id(id);

//			kkkk++;
//		printf("%d\t%d\t%d\t%d\n",(*it).Get_Volumen(),(*it).Get_x(),(*it).Get_y(),(*it).Get_z());	
			}
		}
/*		for( int kkk=0;kkk<m_Q;kkk++)
		{
			printf("%d\t%d\n",kkk,m_frecuencias[m_Pieces[kkk].Get_Id()]);
//		m_frecuencias[kkk]+=m_Pieces[kkk].Get_q()-m_Pieces[kkk].Get_Num();
		}
*/	

	}
	if (m_tipo_orden_pieces==5 && m_iter_actual%500==100 && m_iter_actual>100)
	{
//		printf("Ya no Diver, %d",m_iter_actual);
		
		m_tipo_orden_pieces=3;
		if (por_orden==true)
		{
			std::sort(m_Pieces.begin(),m_Pieces.end());
			std::vector< PIECE > ::iterator it;
		
			int id=0;

			for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
			{
				(*it).Set_Id(id);
//		printf("%d\t%d\t%d\t%d\n",(*it).Get_Volumen(),(*it).Get_x(),(*it).Get_y(),(*it).Get_z());	
			}
		}		

	}
}

//void CONTAINER::ArreglarCompleteShipment()
//{
//	std::vector<PEDIDO>::iterator it = m_Pedidos.begin(), itfin = m_Pedidos.end();
//	for (; it!=itfin; it++)
//	{
//		if ((*it).Get_complete()==false)
//		{
//			int vol = 0;
//			for (int j = 0; j < m_Pieces.size(); j++)
//			{
//				if (cplex.isExtracted(x_ij[i][j]) && cplex.getValue(x_ij[i][j]) > 0.01)
//				{
//					/*printf("x_%d_%d:%.2f\n", i, j, cplex.getValue(x_ij[i][j]));*/
//					vol += cplex.getValue(x_ij[i][j]) * (*contenedor).Get_Piezas()[j].Get_Volumen();
//				}
//			}
//			if ((*contenedor).Get_Pedidos()[i].Get_Volumen() - vol < minvol)
//			{
//				minvol = (*contenedor).Get_Pedidos()[i].Get_Volumen() - vol;
//				(*contenedor).Set_candidato(i);
//			}
//			(*contenedor).Get_Pedidos()[i].Set_vol_restante((*contenedor).Get_Pedidos()[i].Get_Volumen() - vol);
//		}
//	printf("El pedido mas proximo a completarse es el %d", m_candidato + 1);
//	//VaciarIncompletos() //Esta función borraría las cajas sin asignar que no valen para completar el pedido más cercano a completarse
//}



	//		Despues de ver la solucion*/

//Para escribir bloque
/*
		for (it=m_Spaces.begin();it!=m_Spaces.end();it++)
		{
			printf("(%d,%d),(%d,%d)",(*it).Get_x1(),(*it).Get_y1(),(*it).Get_x2(),(*it).Get_y2());
			for (int kk=0;kk<3;kk++)
				printf("%d  ",(*it).Get_Distancia()[kk]);
			printf("\n");
		}
*/
void CONTAINER::ElegirPedidoVolumenFuera()
{
	//Función que elige el pedido con menor volumen por introducir en el contenedor, aprovechando las cajas sin asignar
	Set_candidato(99999);
	int minimo = m_X * m_Y * m_Z;
	int numcajas = 0;
	int volum = 0;
	int numcajastemp = 0;
	for (int i = 0; i < m_num_pedidos; i++)
	{
		if (m_Pedidos[i].Get_complete() == false && m_Pedidos[i].Get_flag() == false)
		{
			volum = 0;
			numcajastemp = 0;
			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()) > 0)
				{
					volum += (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas())) * m_Pieces[j].Get_Volumen();
					numcajastemp += (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()));
				}
			}
			if (volum < minimo && volum != m_Pedidos[i].Get_Volumen()) //si el volumen que queda es el total del pedido, no utiliza cajas de dentro, entonces descartamos
			{
				minimo = volum;
				numcajas = numcajastemp;
				Set_candidato(i);
			}
		}
	}
	if (minimo == m_X * m_Y * m_Z)
	{
		for (int i = 0; i < m_num_pedidos; i++)
		{
			if (m_Pedidos[i].Get_complete() == false && m_Pedidos[i].Get_flag() == false && m_Pedidos[i].Get_Volumen() < minimo)
			{
				minimo = m_Pedidos[i].Get_Volumen();
				Set_candidato(i);
			}
		}
	}
}
void CONTAINER::ElegirPedidoVolumenDentro()
{
	//Función que elige el pedido que mayor volumen de cajas sin asignar utiliza
	Set_candidato(99999);
	int maximo = 0;
	int numcajas = 0;
	int volum = 0;
	int numcajastemp = 0;
	for (int i = 0; i < m_num_pedidos; i++)
	{
		if (m_Pedidos[i].Get_complete() == false && m_Pedidos[i].Get_flag() == false)
		{
			volum = 0;
			numcajastemp = 0;
			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()) > 0)
				{
					volum += (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas())) * m_Pieces[j].Get_Volumen();
					numcajastemp += (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()));
				}
			}
			if (m_Pedidos[i].Get_Volumen() - volum > maximo) 
			{
				maximo = volum;
				numcajas = numcajastemp;
				Set_candidato(i);
			}
		}
	}
	if (maximo == 0)
	{
		int minimo = m_X * m_Y * m_Z;
		for (int i = 0; i < m_num_pedidos; i++)
		{
			if (m_Pedidos[i].Get_complete() == false && m_Pedidos[i].Get_flag() == false && m_Pedidos[i].Get_Volumen() < minimo)
			{
				minimo = m_Pedidos[i].Get_Volumen();
				Set_candidato(i);
			}
		}
	}//Si el maximo es 0, todas las piezas de dentro están asignadas y por tanto pasamos a elegir por volumen de pedido
}
void CONTAINER::ElegirPedidoVolumenFueraPt()
{
	//Función que elige el pedido con menor volumen por introducir en el contenedor, aprovechando las cajas sin asignar, pero en porcentaje respecto al volumen total del pedido
	Set_candidato(99999);
	int minimo = 100;
	int numcajas = 0;
	int volum = 0;
	int numcajastemp = 0;
	double pt = 0;
	for (int i = 0; i < m_num_pedidos; i++)
	{
		if (m_Pedidos[i].Get_complete() == false && m_Pedidos[i].Get_flag() == false)
		{
			pt = 0;
			volum = 0;
			numcajastemp = 0;
			for (int j = 0; j < m_Q; j++)
			{
				if (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()) > 0)
				{
					volum += (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas())) * m_Pieces[j].Get_Volumen();
					numcajastemp += (m_Pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()));
				}
			}
			pt = (double)volum / (double)(m_Pedidos[i].Get_Volumen());
			if (pt < minimo && volum != m_Pedidos[i].Get_Volumen()) //si el volumen que queda es el total del pedido, no utiliza cajas de dentro, entonces descartamos
			{
				minimo = volum;
				numcajas = numcajastemp;
				Set_candidato(i);
			}
		}
	}
	if (minimo == m_X*m_Y*m_Z)
	{
		for (int i = 0; i < m_num_pedidos; i++)
		{
			if (m_Pedidos[i].Get_complete() == false && m_Pedidos[i].Get_flag() == false && m_Pedidos[i].Get_Volumen() < minimo)
			{
				minimo = m_Pedidos[i].Get_Volumen();
				Set_candidato(i);
			}
		}
	}
}
void CONTAINER::ElegirPedidoVolumenFuera(std::vector<PEDIDO>pedidos)
{
	//Función que elige el pedido con menor volumen por introducir en el contenedor, aprovechando las cajas sin asignar
	Set_candidato(99999);
	int minimo = m_X * m_Y * m_Z;
	int numcajas = 0;
	int volum = 0;
	int numcajastemp = 0;
	for (int i = 0; i < pedidos.size(); i++)
	{
		if (pedidos[i].Get_flag() == false && pedidos[i].Get_complete() == false)
		{
			volum = 0;
			numcajastemp = 0;
			for (int j = 0; j < m_Q; j++)
			{
				if (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()) > 0)
				{
					volum += (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas())) * m_Pieces[j].Get_Volumen();
					numcajastemp += (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()));
				}
			}
			if (volum < minimo && volum != pedidos[i].Get_Volumen()) //si el volumen que queda es el total del pedido, no utiliza cajas de dentro, entonces descartamos
			{
				minimo = volum;
				numcajas = numcajastemp;
				Set_candidato(i);
			}
		}
	}
	if (minimo == m_X * m_Y * m_Z)
	{
		for (int i = 0; i < pedidos.size(); i++)
		{
			if (pedidos[i].Get_complete() == false && pedidos[i].Get_flag() == false && pedidos[i].Get_Volumen() < minimo)
			{
				minimo = pedidos[i].Get_Volumen();
				Set_candidato(i);
			}
		}
	}
}
void CONTAINER::ElegirPedidoVolumenDentro(std::vector<PEDIDO>pedidos)
{
	//Función que elige el pedido que mayor volumen de cajas sin asignar utiliza
	Set_candidato(99999);
	int maximo = 0;
	int numcajas = 0;
	int volum = 0;
	int numcajastemp = 0;
	for (int i = 0; i < pedidos.size(); i++)
	{
		if (pedidos[i].Get_flag() == false && pedidos[i].Get_complete() == false)
		{
			volum = 0;
			numcajastemp = 0;
			for (int j = 0; j < m_Q; j++)
			{
				if (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()) > 0)
				{
					volum += (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas())) * m_Pieces[j].Get_Volumen();
					numcajastemp += (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()));
				}
			}
			if (pedidos[i].Get_Volumen() - volum > maximo)
			{
				maximo = volum;
				numcajas = numcajastemp;
				Set_candidato(i);
			}
		}
	}
	if (maximo == 0)
	{
		int minimo = m_X * m_Y * m_Z;
		for (int i = 0; i < pedidos.size(); i++)
		{
			if (pedidos[i].Get_complete() == false && pedidos[i].Get_flag() == false && pedidos[i].Get_Volumen() < minimo)
			{
				minimo = pedidos[i].Get_Volumen();
				Set_candidato(i);
			}
		}
	}//Si el maximo es 0, todas las piezas de dentro están asignadas y por tanto pasamos a elegir por volumen de pedido
}
void CONTAINER::ElegirPedidoVolumenFueraPt(std::vector<PEDIDO>pedidos)
{
	//Función que elige el pedido con menor volumen por introducir en el contenedor, aprovechando las cajas sin asignar, pero en porcentaje respecto al volumen total del pedido
	Set_candidato(99999);
	int minimo = 100;
	int numcajas = 0;
	int volum = 0;
	int numcajastemp = 0;
	double pt = 0;
	for (int i = 0; i < pedidos.size(); i++)
	{
		if (pedidos[i].Get_flag() == false && pedidos[i].Get_complete() == false)
		{
			pt = 0;
			volum = 0;
			numcajastemp = 0;
			for (int j = 0; j < m_Q; j++)
			{
				if (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()) > 0)
				{
					volum += (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas())) * m_Pieces[j].Get_Volumen();
					numcajastemp += (pedidos[i].Get_num_pieces_tipo()[j] - (m_Pieces[j].Get_Num() - m_Pieces[j].Get_asignadas()));
				}
			}
			pt = (double)volum / (double)(pedidos[i].Get_Volumen());
			if (pt < minimo && volum != pedidos[i].Get_Volumen()) //si el volumen que queda es el total del pedido, no utiliza cajas de dentro, entonces descartamos
			{
				minimo = volum;
				numcajas = numcajastemp;
				Set_candidato(i);
			}
		}
	}
	if (minimo == m_X * m_Y * m_Z)
	{
		for (int i = 0; i < pedidos.size(); i++)
		{
			if (pedidos[i].Get_complete() == false && pedidos[i].Get_flag() == false && pedidos[i].Get_Volumen() < minimo)
			{
				minimo = pedidos[i].Get_Volumen();
				Set_candidato(i);
			}
		}
	}
}