#pragma warning (disable: 4786)


//#include "bouknap.c"
#include "Container.h"
#include "LPCPLEX2.h"
#include <random>

extern  "C" int  bouknap(int n, int* p, int* w, int* m, int* x, int c);

//Para que pueda tener las piezas información del contenedor
CONTAINER* BLOQUE::m_Container = NULL;
CONTAINER* SPACE::m_Container=NULL;
CONTAINER* PIECE::m_Container=NULL;
CONTAINER* CONFIGURACAO::m_Container=NULL;



//Orden por volumen
//Si tienen el mismo valor la más grande
bool PIECE::operator <( const PIECE & p2) const
{
	if (m_Container->Get_Tipo_OrdenPieces()==0)
	{
		//Por el área de lo que puedo poner
		return (m_x>p2.Get_x());
	}
	if (m_Container->Get_Tipo_OrdenPieces()==1)
	{
		return (m_y>p2.Get_y());
	}
	if (m_Container->Get_Tipo_OrdenPieces()==2)
	{
		return (m_z>p2.Get_z());
	}
	if (m_Container->Get_Tipo_OrdenPieces()==3)
	{
		//Si no son restringidas
		if (m_Volumen==p2.Get_Volumen())
		{
			//Por la eficiencia
			if (m_x==p2.Get_x())
			{
				if (m_y==p2.Get_y())
				{
					return (m_z>p2.Get_z());
				}
				else	

				return (m_y>p2.Get_y());
				//(p1.largo*p1.ancho)>(p2.largo*p2.ancho);
			}
			else
				//Por el área de lo que puedo poner
			return (m_x>p2.Get_x());//(p1.max*p1.largo*p1.ancho)>(p2.max*p2.largo*p2.ancho);
		}
		else
			return (m_Volumen>p2.Get_Volumen());
	}
	if (m_Container->Get_Tipo_OrdenPieces()==4)
	{
		if (m_Container->GetFrecuencias()[m_Id]==m_Container->GetFrecuencias()[p2.m_Id])
		{
			//Si no son restringidas
			if (m_Volumen==p2.Get_Volumen())
			{
				//Por la eficiencia
				if (m_x==p2.Get_x())
				{
					if (m_y==p2.Get_y())
					{
						return (m_z>p2.Get_z());
					}
					else		

					return (m_y>p2.Get_y());
				//(p1.largo*p1.ancho)>(p2.largo*p2.ancho);
				}
				else
					//Por el área de lo que puedo poner
				return (m_x>p2.Get_x());//(p1.max*p1.largo*p1.ancho)>(p2.max*p2.largo*p2.ancho);
			}
			else
				return (m_Volumen>p2.Get_Volumen());
		}
			else
				return (m_Container->GetFrecuencias()[m_Id]>m_Container->GetFrecuencias()[p2.Get_Id()]);
	}
	if (m_Container->Get_Tipo_OrdenPieces()==5)
	{
		double t=m_Container->Get_Peso_Diver()*(((double)(m_Container->GetFrecuencias()[m_Id]* (double)100)/(double)m_Container->Get_Sum_Freq())+((double)m_Volumen*100/(double)((double)m_Container->Get_X()*m_Container->Get_Y()*m_Container->Get_Z())));
		double tt=m_Container->Get_Peso_Diver()*(((double)(m_Container->GetFrecuencias()[p2.Get_Id()]* (double)100)/(double)m_Container->Get_Sum_Freq())+((double)p2.Get_Volumen()*100/(double)((double)m_Container->Get_X()*m_Container->Get_Y()*m_Container->Get_Z())));
		if (t==tt)
		{
			//Si no son restringidas
			if (m_Volumen==p2.Get_Volumen())
			{
				//Por la eficiencia
				if (m_x==p2.Get_x())
				{
					if (m_y==p2.Get_y())
					{
						return (m_z>p2.Get_z());
					}
					else		

					return (m_y>p2.Get_y());
				//(p1.largo*p1.ancho)>(p2.largo*p2.ancho);
				}
				else
					//Por el área de lo que puedo poner
				return (m_x>p2.Get_x());//(p1.max*p1.largo*p1.ancho)>(p2.max*p2.largo*p2.ancho);
			}
			else
				return (m_Volumen>p2.Get_Volumen());
		}
			else
			return (t>tt);
	}
	printf("problem");
	for (int j = 0;;);
}

bool CONFIGURACAO::operator<(const CONFIGURACAO &p2) 
{
	if (m_Container->Get_Tipo_Gravedad()==0)
	{
		//Si no son restringidas
		if ((m_z1)==(p2.m_z1))
		{
			//Por la eficiencia
			if (m_x1==p2.m_x1)
			{
				return (m_y1<p2.m_y1);
			}
			else
				//Por el área
			return (m_x1<p2.m_x1);
		}
		else
			return (m_z1<p2.m_z1);
	}
	if (m_Container->Get_Tipo_Gravedad()==1)
	{
		//Si no son restringidas
		if ((m_x1)==(p2.m_x1))
		{
			//Por la eficiencia
			if (m_z1==p2.m_z1)
			{
				return (m_y1<p2.m_y1);
			}
			else
				//Por el área
			return (m_z1<p2.m_z1);
		}
		else
			return (m_x1<p2.m_x1);
	}
	if (m_Container->Get_Tipo_Gravedad()==2)
	{
		//Si no son restringidas
		if ((m_y1)==(p2.m_y1))
		{
			//Por la eficiencia
			if (m_x1==p2.m_x1)
			{
				return (m_z1<p2.m_z1);
			}
			else
				//Por el área
			return (m_x1<p2.m_x1);
		}
		else
			return (m_y1<p2.m_y1);
	}
	//Para dibujar
	if (m_Container->Get_Tipo_Gravedad()==3)
	{
		//Si no son restringidas
		if ((m_x1)==(p2.m_x1))
		{
			//Por la eficiencia
			if (m_z1==p2.m_z1)
			{
				return (m_y1<p2.m_y1);
			}
			else
				//Por el área
			return (m_z1<p2.m_z1);
		}
		else
			return (m_x1<p2.m_x1);
	}
	return true;
}

ORIG::ORIG()
{
//	std::vector<short int> vec(3);
//	m_orig=vec;
	m_primero = 0;
	m_segundo = 0;
	m_tercero = 0;
	
}

ORIG::ORIG(int a,int b, int c)
{
//	std::vector<short int> vec(3);
//	m_orig=vec;
//	m_orig.push_back(0);
//	m_orig.push_back(0);
//	m_orig.push_back(0);

	if (a>=max(b,c))
	{
		m_tercero=a;
		if (b>=c)
		{
			m_segundo=b;
			m_primero=c;
		}
		else
		{
			m_primero=b;
			m_segundo=c;

		}
	}
	else
	{
		if (b>=c)
		{
			m_tercero=b;
			if (c>=a)
			{
				m_segundo=c;
				m_primero=a;
			}
			else
			{
				m_segundo=a;
				m_primero=c;

			}
		}
		else
		{
			m_tercero=c;
			if (b>=a)
			{
				m_segundo=b;
				m_primero=a;
			}
			else
			{
				m_segundo=a;
				m_primero=b;

			}
		}
	}
}
void SPACE::ModificarSpace(int x1,int y1, int z1, int x2, int y2, int z2)
{
	m_x1=x1; m_y1=y1; m_z1=z1;
	m_x2=x2; m_y2=y2; m_z2=z2;
	m_dx=x2-x1; m_dy=y2-y1; m_dz=z2-z1;
	m_Volumen=m_dx*m_dy*m_dz;
	if (m_Container->Get_Full_Supported() == false)
	{
		CalcularDistanciaOrigen();

	}
	else
		CalcularDistanciaOrigenFullSupported();
}


void SPACE::Cambiar(ORIG &orig, int a,int b,int c)
{
	
	if (a>=max(b,c))
	{
		orig.SetTercero(a);
		if (b>=c)
		{
			orig.SetSegundo(b);
			orig.SetPrimero(c);
		}
		else
		{
			orig.SetPrimero(b);
			orig.SetSegundo(c);

		}
	}
	else
	{
		if (b>=c)
		{
			orig.SetTercero(b);
			if (c>=a)
			{
				orig.SetSegundo(c);
				orig.SetPrimero(a);
			}
			else
			{
				orig.SetSegundo(a);
				orig.SetPrimero(c);

			}
		}
		else
		{
			orig.SetTercero(c);
			if (b>=a)
			{
				orig.SetSegundo(b);
				orig.SetPrimero(a);
			}
			else
			{
				orig.SetSegundo(a);
				orig.SetPrimero(b);

			}
		}
	}
}
void CONFIGURACAO::Cambiar(ORIG &orig,int a,int b,int c)
{

	if (a>=max(b,c))
	{
		orig.SetTercero(a);
		if (b>=c)
		{
			orig.SetSegundo(b);
			orig.SetPrimero(c);
		}
		else
		{
			orig.SetPrimero(b);
			orig.SetSegundo(c);

		}
	}
	else
	{
		if (b>=c)
		{
			orig.SetTercero(b);
			if (c>=a)
			{
				orig.SetSegundo(c);
				orig.SetPrimero(a);
			}
			else
			{
				orig.SetSegundo(a);
				orig.SetPrimero(c);

			}
		}
		else
		{
			orig.SetTercero(c);
			if (b>=a)
			{
				orig.SetSegundo(b);
				orig.SetPrimero(a);
			}
			else
			{
				orig.SetSegundo(a);
				orig.SetPrimero(b);

			}
		}
	}
}
void CONTAINER::InicializarVariables()
{
	m_total_volumen_ocupado=0;
	m_Dibujar=false;
	m_max_total_volumen_ocupado=0;
	m_objetivo_vol=true;
	m_tipo_mixto=false;
		m_nesquinas=2;
		m_Aleatorizado=false;
		m_total_volumen_ocupado=0;
		m_Dibujar=false;
		m_max_total_volumen_ocupado=0;
		m_objetivo_vol=true;
		m_tipo_mixto=false;
		m_medida1=0;
		m_medida2=0;
		m_imprimir_mejoras=false;
		m_multicontainer=true;
		m_nbins=0;
		m_Best_nbins=m_Q;//Lo pongo al maximo valor
		m_PeorSolucion_nbins=0;
		m_por_bin=false;
		m_bin_fijados=0;
		m_tiempo=0;
		m_inicio=0;
		//reducir piezas 
		AumentarPiezas();

		std::vector< PIECE > ::iterator it;
		m_tipo_orden_pieces=3;
		std::sort(m_Pieces.begin(),m_Pieces.end());
		int id=0;
		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
		{
			(*it).Set_Id(id);
		}
//		printf("Viejas\n");
//		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
//		{
//			printf("%d, (%d,%d)\n",(*it).Get_Id(),(*it).Get_x(),(*it).Get_y());
//		}
//		printf("Nuevas\n");
		ReducirPiezasYBins();

}
//caso me dice si es 0 container o 1 multicontainer
CONTAINER::CONTAINER(char *nombre,int caso, int CS, bool bloque, float perdida, int vcs)
{
	m_all_bloques = false;
	m_perdida = perdida;
	m_VCS = false;
	m_VCS_random = false;
	m_Fit = true; //En true, pasa en el VND por el movimiento de vaciado y rellenado con función objetivo fit
	m_objetivo_mixto = false;
	p = 0.04;
	alpha = 4;
	beta = 1;
	gamma = 0.2;
	Max_Iter_VCS = 30;
	m_iter_best_actual=0;
	m_tipo_orden_pieces=0;
	m_full_supported = false;
	m_juntar_spaces = false;
	m_por_bloques = false;
	m_por_bloques_ara = bloque;
	m_bloques_heterogeneos = 0;
	m_complete_shipment = false;
	if (m_por_bloques_ara == true)
		m_por_bloques = false;
	if (m_por_bloques == true)
		m_por_bloques_ara = false;
	if (caso<=1)
	{
		//Pongo el tiempo a cero
		m_inicio=clock();
		if (caso == 1)
			m_full_supported = true;
		else
			m_full_supported = false;
		if (CS >= 1)
		{
			m_complete_shipment = true;
			if (CS == 3 || CS == 4)
			{
				m_aleatorizado_cs = true;
				mindimcs = false;
			}
		}
		else
			m_complete_shipment = false;
		if (vcs == 1)
			m_VCS = true;
		else if (vcs == 2)
		{
			m_VCS = true;
			m_VCS_random = true;
		}

		m_juntar_spaces = m_full_supported; //Cuando sea full support, que junte espacios
		if (m_complete_shipment == false)
			LeerDatosContainer(nombre);
		else
			LeerDatosContainerPedidos(nombre);
		if (m_por_bloques == true)
		{
			JuntarPiezasParecidas();
			if (m_Bloques.size() == 0)
				m_por_bloques = false;
		}
		if (m_por_bloques_ara == true)
		{
			Generar_Bloques(perdida, 10000, m_full_supported);
			/*std::set<BLOQUE_ARA*, compareBlocks>::iterator itB = m_set_Bloques.begin(), itBfin=m_set_Bloques.end();
			std::copy(m_set_Bloques.begin(), m_set_Bloques.end(), std::back_inserter(m_vector_Bloques));
			for (short int i = 0; i < m_set_Bloques.size(); i++)
			{
				m_set_indices.insert(i);
				(**itB).Set_Id(i);
				itB++;
			}
			m_set_indices_copia = m_set_indices;*/
		}
		/*else if (vcs==1)
			Generar_Bloques(1, 10000, m_full_supported);*/
		m_total_volumen_ocupado=0;
		m_cota_cs = 0;
		m_total_volumen_cs_ocupado = 0;
		//para construir por bloques o no
		m_Dibujar=false;
		m_Verificar = true;
		m_max_total_volumen_ocupado=0;
		m_objetivo_vol=true;
		m_tipo_mixto=false;
		m_medida1=0;
		m_medida2=0;
		m_imprimir_mejoras=false;
		m_multicontainer=false;
		m_por_bin = false;
		m_rotacion = true;
	}
	else
	{
		//Pongo el tiempo a cero
		m_inicio=clock();
		m_max_iteraciones_Grasp=5000;
		LeerDatosMultiContainer(nombre);
		gananciaCadaBin=0;
		gananciaPartir=0;
		gananciaUltimos=0;

		m_nesquinas=2;
		m_Aleatorizado=false;
		m_total_volumen_ocupado=0;
		m_Verificar = true;
		m_Dibujar=false;
		m_max_total_volumen_ocupado=0;
		m_objetivo_vol=true;
		m_tipo_mixto=false;
		m_medida1=0;



		m_medida2=0;
		m_imprimir_mejoras=false;
		m_multicontainer=true;
		m_nbins=0;
		m_PeorSolucion_nbins=0;
		m_por_bin=false;
		m_bin_fijados=0;
		std::vector< PIECE > ::iterator it;
		if (m_rotacion==false)
		m_Best_nbins=m_Q;//Lo pongo al maximo valor
		else
		{
			m_Best_nbins=0;
			for (it=m_Pieces.begin();it!=m_Pieces.end();it++)
			{
				m_Best_nbins+=(*it).Get_q();
			}				
		}
		m_tipo_orden_pieces=3;
		std::sort(m_Pieces.begin(),m_Pieces.end());
		int id=0;
		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
		{
			(*it).Set_Id(id);
		}
		if (m_rotacion==false)
		{
//		printf("Viejas\n");
//		PintarPieces();

//		printf("Nuevas\n");
		ReducirPiezasYBins();
//		PintarPieces();
		ReducirPiezasX();
		ReducirPiezasY();
		ReducirPiezasZ();
//		PintarPieces();
		AumentarPiezas();

//		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
//		{
//			printf("%d, (%d,%d)\n",(*it).Get_Id(),(*it).Get_x(),(*it).Get_y());
//		}
		m_tipo_orden_pieces=3;
		std::sort(m_Pieces.begin(),m_Pieces.end());
		id=0;
		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
		{
			(*it).Set_Id(id);
		}
//		JuntarPiezasIguales();
//		PintarPieces();
		m_tipo_orden_pieces=3;
		std::sort(m_Pieces.begin(),m_Pieces.end());
		id=0;
		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
		{
			(*it).Set_Id(id);
		}
//		printf("Nuevas");
//		PintarPieces();
		}
	}
	
}
void CONTAINER::PintarPieces()
{
		std::vector< PIECE > ::iterator it;
	int id=0;
	printf("\nBin %d %d %d\n",m_X,m_Y,m_Z);
	for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
	{
		printf("%d, (%d,%d, %d) Num %d Max %d \n",(*it).Get_Id(),(*it).Get_x(),(*it).Get_y(),(*it).Get_z(),(*it).Get_Num(),(*it).Get_q());
	}
}

void CONTAINER::JuntarPiezasIguales()
{
	bool juntar=false;
	do{
		juntar=false;
	std::vector <PIECE> ::iterator itkkj;
	int i=0;
	for ( i=0,itkkj=m_Pieces.begin();itkkj!=m_Pieces.end() && juntar!=true && i<m_Q-1; i++)
//	for (register int i=0;juntar!=true && i<m_Q-1;i++)
	{
		//Juntar Pieces iguales
		if (m_Pieces[i].Get_x()==m_Pieces[i+1].Get_x() &&
			m_Pieces[i].Get_y()==m_Pieces[i+1].Get_y() &&
			m_Pieces[i].Get_z()==m_Pieces[i+1].Get_z())
		{
			m_Pieces[i].Add_q(m_Pieces[i+1].Get_q());
			juntar=true;
			m_Q--;
			m_Pieces.erase((itkkj+1));
//			printf("He juntado Pieces iguales");
			
		}
		++itkkj;
	}
	}
	while(juntar==true);

}
//Para la creación la x,y,z si es posible rotarla en cada dirección y la cantidad
PIECE::PIECE(int id,int x, bool Px,int y,bool Py, int z, bool Pz, int q,CONTAINER *a)
{
	m_Id=id;
	m_x=x;m_y=y;m_z=z;
	m_Rotate_x=Px;
	m_Rotate_y=Py;
	m_Rotate_z=Pz;
	m_Volumen=m_x*m_y*m_z;
	m_num=0;
	m_q=q;
	m_Container=a;
	m_asignadas = 0;

}
void CONTAINER::EscribirDatosProgramaDibujo()
{
	FILE *fin2;
	char *nombre="a";
	strcpy(nombre,"");
	strcpy(nombre,m_Nombre);
	strcat(nombre,".dat");
	fin2=fopen(nombre,"a+");
	std::list< CONFIGURACAO >::iterator itl;
	fprintf(fin2,"Contentor:\n Profund. Largura Altura   Limite Peso\n");
	fprintf(fin2,"%d\t%d\t%d\t7000000\n\n",m_X,m_Y,m_Z);
	fprintf(fin2,"Tipo Quant.  Dimensoes   Orient.       Limite Peso       Peso\n");
	fprintf(fin2,"# Destino2\n");
	int i=0;
	for (itl=m_Configuracaos.begin(), i=1;itl!=m_Configuracaos.end();itl++,i++)
	{
		fprintf(fin2,"* %d %d %d %d %d %d %d",i,(*itl).Get_x1(),(*itl).Get_y1(),(*itl).Get_z1(),(*itl).Get_x2(),(*itl).Get_y2(),(*itl).Get_z2());

	}
	fclose(fin2);

}
void CONTAINER::CotaCompleteShipment()
{
	//Como todas las instancias ocupan menos en volumen que el del contenedor, la cota superior ficticia (suponiendo que no vamos a poder meterlo todo) será la suma
	//de los volumenes de todos los pedidos excepto el de menor tamaño
	int minimo = m_X * m_Y * m_Z;
	int pedido = 0;
	for (int i = 0; i < m_num_pedidos; i++)
	{
		if (m_Pedidos[i].Get_Volumen() < minimo)
		{
			minimo = m_Pedidos[i].Get_Volumen();
			pedido = i;
		}
	}
	m_cota_cs = m_total_volumen - minimo;
	/*double porcn = 100 * (double)m_cota_cs / (double)(m_X * m_Y * m_Z);
	FILE* fich;
	fich = fopen(m_file_to_write, "a+");
	std::fprintf(fich, "%d\t%f\t%d\t%d\n", m_cota_cs, porcn, pedido + 1, minimo);
	std::fclose(fich);
	printf("Cota: %d\t%f\t Prox pedido: %d\t%d\n", m_cota_cs, porcn, pedido + 1, minimo);*/
}
void CONTAINER::LeerDatosContainer(char *nombre)
{
	FILE *fin2;
	m_Q=0;
	m_total_volumen=0;
	strcpy(m_Nombre,nombre);
	fin2=fopen(nombre,"r+");
	if (fin2==NULL)
	{
		printf("Problemas al leer el archivo del container, no se encuentra el archivo %s",nombre );
		exit(4);
	}
	//Leemos el número de piezas
	fscanf(fin2,"%d",&m_Q);
	//Las coordenadas del contenedor
	fscanf(fin2,"%d %d %d",&m_X,&m_Y,&m_Z);
	//Variables temporales para almacenar el número de piezas
//	m_total_volumen=m_X*m_Y*m_Z;
	int Id,x,y,z,q;
	int  R1x,R1y,R1z;
	bool Rx, Ry, Rz;
	for (int register i=0;i<m_Q;i++)
	{
		m_Numpieces++;
		//Leemos las coordenadas de las piezas
		fscanf(fin2,"%d %d %d %d %d %d %d %d" , &Id, &x, &R1x, &y, &R1y, &z, &R1z,&q);
		Rx = R1x; Ry = R1y; Rz = R1z;
		PIECE Piece(Id-1,x,Rx,y,Ry,z,Rz,q,this);
		
		m_total_volumen+=Piece.Get_Volumen()*q;
		m_Pieces.push_back(Piece);
	}
	//Conforme voy leyendo los datos del container puedo ver cual es la 
	//mas pequena en cada dirección, calculamos minimos para cada dirección
	MinimaDimension();

	fclose(fin2);
}
void CONTAINER::LeerDatosContainerPedidos(char* nombre)
{
	FILE* fin2;
	m_Q = 0;
	m_total_volumen = 0;
	strcpy(m_Nombre, nombre);
	fin2 = fopen(nombre, "r+");
	if (fin2 == NULL)
	{
		printf("Problemas al leer el archivo del container, no se encuentra el archivo %s", nombre);
		exit(4);
	}
	//Leemos el número de piezas
	fscanf(fin2, "%d", &m_Q);
	//Las coordenadas del contenedor
	fscanf(fin2, "%d %d %d", &m_X, &m_Y, &m_Z);
	//Variables temporales para almacenar el número de piezas
//	m_total_volumen=m_X*m_Y*m_Z;
	int Id, x, y, z, q;
	int  R1x, R1y, R1z;
	bool Rx, Ry, Rz;
	for (int register i = 0; i < m_Q; i++)
	{
		m_Numpieces++;
		//Leemos las coordenadas de las piezas
		fscanf(fin2, "%d %d %d %d %d %d %d %d", &Id, &x, &R1x, &y, &R1y, &z, &R1z, &q);
		Rx = R1x; Ry = R1y; Rz = R1z;
		PIECE Piece(Id - 1, x, Rx, y, Ry, z, Rz, q, this);

		m_total_volumen += Piece.Get_Volumen() * q;
		m_Pieces.push_back(Piece);
	}
	//Conforme voy leyendo los datos del container puedo ver cual es la 
	//mas pequena en cada dirección, calculamos minimos para cada dirección
	MinimaDimension();
	if (m_complete_shipment == true)
	{
		m_vol_incompletos = 0;
		m_completos = 0;
		int id, totalcajas, aux;
		std::vector<int> tipos_cajas;
		//Número de pedidos
		fscanf(fin2, "%d", &m_num_pedidos);
		for (int register i = 0; i < m_num_pedidos; i++)
		{
			tipos_cajas.clear();
			fscanf(fin2, "%d", &id);
			for (int register j = 0; j < m_Q; j++)
			{
				fscanf(fin2, "%d", &aux);
				tipos_cajas.push_back(aux);
			}
			fscanf(fin2, "%d", &totalcajas);
			PEDIDO Pedido(id-1, tipos_cajas, totalcajas, this);
			m_Pedidos.push_back(Pedido);
			
		}
	}
	fclose(fin2);
}
void CONTAINER::LeerDatosMultiContainer(char *nombre)
{
	FILE *fin2;
	m_Q=0;
	m_total_volumen=0;
	strcpy(m_Nombre,nombre);
	fin2=fopen(nombre,"a+");
	if (fin2==NULL)
	{
		printf("Problemas al leer el archivo del container, no se encuentra el archivo %s",nombre );
		exit(4);
	}
	//Leemos el número de piezas
	fscanf(fin2,"%d %d",&m_Q,&m_lb);
	int kk=0;
//	fscanf(fin2,"%d",&m_Q);
//	m_lb=1;
//	fscanf(fin2,"%d ",&m_Q);
	//Las coordenadas del contenedor
	fscanf(fin2,"%d %d %d",&m_X,&m_Y,&m_Z);
//	fscanf(fin2,"%d ",&m_X);
	//Variables temporales para almacenar el número de piezas
//	m_total_volumen=m_X*m_Y*m_Z;
	int Id,x,y,z,q;
	bool Rx,Ry,Rz;
	for (int register i=0;i<m_Q;i++)
	{
		if (m_lb!=0)
		{
		m_Numpieces++;
		//Leemos las coordenadas de las piezas
//		fscanf(fin2,"%d %d %d %d %d %d %d %d" , &Id, &x, &Rx, &y, &Ry, &z, &Rz,&q);
		fscanf(fin2,"%d %d %d %d " , &Id, &x, &y, &z );
//		fscanf(fin2,"%d %d %d " , &Id, &x, &y );
//		PIECE Piece(Id-1,x,0,y,0,z,0,1,this);
		PIECE Piece(i,x,0,y,0,z,0,1,this);
		m_total_volumen+=Piece.Get_Volumen()*1;
		m_Pieces.push_back(Piece);
		}
		else
		{
		m_Numpieces++;
		//Leemos las coordenadas de las piezas
//		fscanf(fin2,"%d %d %d %d %d %d %d %d" , &Id, &x, &Rx, &y, &Ry, &z, &Rz,&q);
		fscanf(fin2,"%d %d %d %d %d %d %d %d" , &Id, &x, &Rx, &y, &Ry, &z, &Rz,&q);
		PIECE Piece(Id,x,Rx,y,Ry,z,Rz,q,this);
		
		m_total_volumen+=Piece.Get_Volumen()*q;
		m_Pieces.push_back(Piece);
		}
	}
	//Conforme voy leyendo los datos del container puedo ver cual es la 
	//mas pequena en cada dirección, calculamos minimos para cada dirección
	m_lb=ceil((double) m_total_volumen/(double)((double)m_X*m_Y*m_Z));
	if (m_lb<=0) 
	{
		MinimaDimension();
		m_lb=ceil((double) m_total_volumen/(double)((double)m_X*m_Y*m_Z));
		m_rotacion=true;

	}
	
	else	
	{
		MinimaDimensionMC();
		m_rotacion=false;
	}
	fprintf(fin2,"\n");
	for (int i=0;i<m_Q;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\n",i,m_Pieces[i].Get_x(),m_Pieces[i].Get_y(),m_Pieces[i].Get_z(),m_Pieces[i].Get_q());
	}
	fclose(fin2);
}
void CONTAINER::MinimaDimension()
{	
	if (m_aleatorizado_cs == true && mindimcs==true)
		return;
	mindimcs = true;
	m_dimension_menor=m_X;
	m_menor_volumen=m_X*m_Y*m_Z;
	for (int register icp=0;icp<m_Q;icp++)
	{
		if (m_Pieces[icp].Get_Num()==m_Pieces[icp].Get_q())
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
void CONTAINER::MinimaDimensionMC()
{	
	m_dimension_menor_x=m_X;
	m_dimension_menor_y=m_Y;
	m_dimension_menor_z=m_Z;
	m_menor_volumen=m_X*m_Y*m_Z;
	for (int register icp=0;icp<m_Q;icp++)
	{
		if (m_Pieces[icp].Get_Num()==m_Pieces[icp].Get_q())
			continue;
		if ((m_Pieces[icp].Get_x()*m_Pieces[icp].Get_y()*m_Pieces[icp].Get_z())<m_menor_volumen)
			m_menor_volumen=m_Pieces[icp].Get_x()*m_Pieces[icp].Get_y()*m_Pieces[icp].Get_z();
		if (m_Pieces[icp].Get_x()<m_dimension_menor_x)
				m_dimension_menor_x=m_Pieces[icp].Get_x();
		if (m_Pieces[icp].Get_y()<m_dimension_menor_y)
				m_dimension_menor_y=m_Pieces[icp].Get_y();
		if (m_Pieces[icp].Get_z()<m_dimension_menor_z)
			m_dimension_menor_z=m_Pieces[icp].Get_z();

	}

}

void CONTAINER::MinimaDimensionMCMov()
{	
	m_dimension_menor_x=m_X;
	m_dimension_menor_y=m_Y;
	m_dimension_menor_z=m_Z;
	m_menor_volumen=m_X*m_Y*m_Z;
	for (int register icp=0;icp<m_Q;icp++)
	{
		if (m_Pieces_Tabu[icp]==m_Pieces[icp].Get_q())
			continue;
		if ((m_Pieces[icp].Get_x()*m_Pieces[icp].Get_y()*m_Pieces[icp].Get_z())<m_menor_volumen)
			m_menor_volumen=m_Pieces[icp].Get_x()*m_Pieces[icp].Get_y()*m_Pieces[icp].Get_z();
		if (m_Pieces[icp].Get_x()<m_dimension_menor_x)
				m_dimension_menor_x=m_Pieces[icp].Get_x();
		if (m_Pieces[icp].Get_y()<m_dimension_menor_y)
				m_dimension_menor_y=m_Pieces[icp].Get_y();
		if (m_Pieces[icp].Get_z()<m_dimension_menor_z)
			m_dimension_menor_z=m_Pieces[icp].Get_z();

	}

}

void CONTAINER::MinimaDimensionMCMovP()
{	
	m_dimension_menor_x=m_X;
	m_dimension_menor_y=m_Y;
	m_dimension_menor_z=m_Z;
	m_menor_volumen=m_X*m_Y*m_Z;
	for (int register icp=0;icp<m_Q;icp++)
	{
		if (m_Pieces_Tabu2[icp]==m_Pieces[icp].Get_q())
			continue;
		if ((m_Pieces[icp].Get_x()*m_Pieces[icp].Get_y()*m_Pieces[icp].Get_z())<m_menor_volumen)
			m_menor_volumen=m_Pieces[icp].Get_x()*m_Pieces[icp].Get_y()*m_Pieces[icp].Get_z();
		if (m_Pieces[icp].Get_x()<m_dimension_menor_x)
				m_dimension_menor_x=m_Pieces[icp].Get_x();
		if (m_Pieces[icp].Get_y()<m_dimension_menor_y)
				m_dimension_menor_y=m_Pieces[icp].Get_y();
		if (m_Pieces[icp].Get_z()<m_dimension_menor_z)
			m_dimension_menor_z=m_Pieces[icp].Get_z();

	}

}

PEDIDO::PEDIDO(int id, std::vector<int> tipos_cajas, int total_cajas, CONTAINER *a)
{
	m_flag = false;
	m_vol_falta = 0;
	m_Id = id;
	m_num_cajas = total_cajas;
	m_Volumen = 0;
	m_complete = false;
	for (int i = 0; i < tipos_cajas.size(); i++)
	{
		m_num_pieces_tipo.push_back(tipos_cajas[i]);
		m_Volumen += ((a->Get_Piezas()[i]).Get_Volumen()) * tipos_cajas[i];
	}

}
//****************

SPACE::SPACE(int x1,int y1, int z1, int x2, int y2,int z2 ,CONTAINER *a)
{
	m_x1=x1; m_y1=y1; m_z1=z1;
	m_x2=x2; m_y2=y2; m_z2=z2;
	
	m_dx=x2-x1; m_dy=y2-y1; m_dz=z2-z1;
	m_Volumen=m_dx*m_dy*m_dz;
	m_Flag=false;
	m_Container=a;
	//m_bloque_espacio = false;

//	CalcularDistanciaOrigen();
//	CalcularDistanciaOrigenEsquinas();
	if (a->Get_Full_Supported() == false)
		CalcularDistanciaOrigenDos();
	else
		CalcularDistanciaOrigenFullSupported();
/*	if (m_Container->Get_MC()==true && m_Container->Get_Juntos()==true)
	CalcularDistanciaOrigen();
	else
	CalcularDistanciaOrigenDos();*/
/*	int tipo=m_origen_distancia;
	m_distancia_origen.clear();
	CalcularDistanciaOrigenOriginal();
	if (m_origen_distancia!=tipo)
		int gato=9;
*/
}

SPACE::SPACE(CONTAINER *a,int x1,int y1, int z1, int x2, int y2,int z2 )
{
	m_x1=x1; m_y1=y1; m_z1=z1;
	m_x2=m_x1+x2; m_y2=m_y1+y2; m_z2=m_z1+z2;
	
	m_dx=x2; m_dy=y2; m_dz=z2;
	m_Volumen=m_dx*m_dy*m_dz;
	m_Flag=false;
	m_Container=a;
	//m_bloque_espacio = false;
//	CalcularDistanciaOrigen();
/*	if (m_Container->Get_MC()==true && m_Container->Get_Juntos()==true)
	CalcularDistanciaOrigen();
	else
	CalcularDistanciaOrigenDos();
	*/

	if (a->Get_Full_Supported() == false)
		CalcularDistanciaOrigenDos();
	else
		CalcularDistanciaOrigenFullSupported();
//	CalcularDistanciaOrigenEsquinas();

/*	int tipo=m_origen_distancia;
	m_distancia_origen.clear();
	CalcularDistanciaOrigenOriginal();
	if (m_origen_distancia!=tipo)
		int gato=9;
*/

}
//Para el contenedor
// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z) 
//Para el space
// 1. (m_x1,m_y1, m_z1) ,2 . (m_x1,m_y2,m_z1) 3 (m_x1, m_y1, m_z2) 4 (m_x1,m_y2,m_z2)
// 5. (m_x2,m_y1, m_z1) ,6   (m_x2,m_y2,m_z1) 7 (m_x2,m_y1,m_z2) 8 (m_x2,m_y2,m_z2)
// Me devuelve true si es mejor la primera que la segunda
bool CONFIGURACAO::Mejor_DistA_Que_DistB_FullSupported(ORIG &A, int NumA, ORIG &B, int NumB, int Vol, int dx, int dy, int dz)
{
	//otra opcion mucho mas compleja es calcular cuantas podrian estar encima de esta y colocar esa
	//pieza
	//	if (CuantasEncima(m_x2-m_x1,m_y2-m_y1)<CuantasEncima(dx,dy)) return false;
	//	else return true;



	//area
	if (m_Container->Get_objetivo_vol() == true)
	{
		if (((m_x2 - m_x1) * (m_y2 - m_y1)) < (dx * dy)) return false;
		//		if (m_Volumen==Vol && NumA>NumB) return false;
		//si tienen igual area por volumen
		if (m_Volumen > Vol && ((m_x2 - m_x1) * (m_y2 - m_y1)) == (dx * dy)) return false;

		return true;
	}
	/*		if (((m_x2-m_x1)*(m_y2-m_y1))>(dx*dy)) return true;
	//Si tienen igual volumen e igual area
	if (A.GetPrimero()>B.GetPrimero()) return false;
	if (A.GetPrimero()<B.GetPrimero()) return true;
	if (A.GetSegundo()>B.GetSegundo()) return false;
	if (A.GetSegundo()<B.GetSegundo()) return true;
	if (A.GetTercero()>B.GetTercero()) return false;
	if (A.GetTercero()<B.GetTercero()) return true;
	if (NumA<=NumB) return true;
	else
	return false;*/
	//Solamente funcion objetivo
	//si ya no caben mas encima
	//area
	/*		if (((m_x2-m_x1)*(m_y2-m_y1))<(dx*dy)) return false;
	else
	{
	if (((m_x2-m_x1)*(m_y2-m_y1))==(dx*dy))
	{
	if (m_Volumen>Vol)
	{
	return true;
	}
	if (m_Volumen==Vol)
	{
	//Para que ponga las mas cuadradas
	if ((m_x2-m_x1)+(m_y2-m_y1)<dx+dy)
	return true;
	else
	return false;
	}
	}
	}*/

	/*		if (((m_x2-m_x1)*(m_y2-m_y1))>(dx*dy)) return true;
	//Si tienen igual volumen e igual area
	if (A.GetPrimero()>B.GetPrimero()) return false;
	if (A.GetPrimero()<B.GetPrimero()) return true;
	if (A.GetSegundo()>B.GetSegundo()) return false;
	if (A.GetSegundo()<B.GetSegundo()) return true;
	if (A.GetTercero()>B.GetTercero()) return false;
	if (A.GetTercero()<B.GetTercero()) return true;
	if (NumA<=NumB) return true;
	else
	return false;*/
	else
	{

		//Comparo componente a componente
		//Comparo componente a componente
		if (A.GetPrimero() > B.GetPrimero()) return false;
		if (A.GetPrimero() < B.GetPrimero()) return true;
		if (A.GetSegundo() > B.GetSegundo()) return false;
		if (A.GetSegundo() < B.GetSegundo()) return true;
		if (A.GetTercero() > B.GetTercero()) return false;
		if (A.GetTercero() < B.GetTercero()) return true;
		if (NumA <= NumB) return true;
		else
			return false;
	}
}
void SPACE::CalcularDistanciaOrigenFullSupported()
{
	/*	if (m_Container->Get_Tipo_Origen()==1)
	{
	Cambiar(m_distancia_origen,m_x1,m_y1,m_z1);
	m_origen_distancia=1;
	return;
	}
	*/	//Tengo que hacer todo lo posible para que esta función evite calculos ya que consume
	//la mayor parte del porcentaje del tiempo
	//Tienen que tener a x1 menor que esto para que pueda ser uno de los 3 siguientes
	if (m_x1 <= (m_Container->Get_X() - m_x2))
	{
		if (m_y1 <= (m_Container->Get_Y() - m_y2))
		{

			Cambiar(m_distancia_origen, m_x1, m_y1, m_z1);
			m_origen_distancia = 1;
		}
		else
		{


			//Posicion 2
			//solamente cambia la segunda componente por tanto
			Cambiar(m_distancia_origen, m_x1, m_Container->Get_Y() - m_y2, m_z1);
			m_origen_distancia = 2;

		}

	}
	else
	{
		//Si el final esta antes del container pues tiene que ser uno de los 
		//primeros
		//Posicion 5
		if (m_y1 <= (m_Container->Get_Y() - m_y2))
		{
			Cambiar(m_distancia_origen, m_Container->Get_X() - m_x2, m_y1, m_z1);
			m_origen_distancia = 5;

		}
		else
		{
			//Posicion 6
			Cambiar(m_distancia_origen, m_Container->Get_X() - m_x2, m_Container->Get_Y() - m_y2, m_z1);
			m_origen_distancia = 6;
		}
	}
}

void SPACE::CalcularDistanciaOrigen()
{
	//el primero la distancia al (0,0,0)

	//Tengo que hacer todo lo posible para que esta función evite calculos ya que consume
	//la mayor parte del porcentaje del tiempo
	//Tienen que tener a x1 menor que esto para que pueda ser uno de los 3 siguientes
	if (m_x1<=(m_Container->Get_X()-m_x2))
	{
		if (m_z1<=(m_Container->Get_Z()-m_z2))
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2))
			{
				
				Cambiar(m_distancia_origen,m_x1,m_y1,m_z1);
				m_origen_distancia=1;
			}
			else
			{


				//Posicion 2
				//solamente cambia la segunda componente por tanto
				Cambiar(m_distancia_origen,m_x1,m_Container->Get_Y()-m_y2,m_z1);
				m_origen_distancia=2;

			}
		}
		else
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2))
			
			{
				//Posicion 3

				Cambiar(m_distancia_origen,m_x1,m_y1,m_Container->Get_Z()-m_z2);
				m_origen_distancia=3;	

			}
			else
			{
			//Posicion 4
				Cambiar(m_distancia_origen,m_x1,m_Container->Get_Y()-m_y2,m_Container->Get_Z()-m_z2);
				m_origen_distancia=4;	
	
			}
		}

	}
	else
	{
		//Si el final esta antes del container pues tiene que ser uno de los 
		//primeros
		//Posicion 5
		if (m_z1<=(m_Container->Get_Z()-m_z2))
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2))
			{
				Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_y1,m_z1);
				m_origen_distancia=5;
	
			}
			else
			{
				//Posicion 6
				Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_Container->Get_Y()-m_y2,m_z1);
				m_origen_distancia=6;

			}
		}
		else
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2))
			{

				//Posicion 7
				Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_y1,m_Container->Get_Z()-m_z2);
				m_origen_distancia=7;

			}
			else
			{
				//Posicion 8
				Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_Container->Get_Y()-m_y2,m_Container->Get_Z()-m_z2);
				m_origen_distancia=8;
			}
		}
	}
}
void SPACE::CalcularDistanciaOrigenEsquinas()
{
	//el primero la distancia al (0,0,0)

	//Tengo que hacer todo lo posible para que esta función evite calculos ya que consume
	//la mayor parte del porcentaje del tiempo
	//Tienen que tener a x1 menor que esto para que pueda ser uno de los 3 siguientes
	if (m_Container->Get_Nesquinas()==1)
	{
		m_origen_distancia=1;
		Cambiar(m_distancia_origen,m_x1,m_y1,m_z1);
		return;
	}

	if (m_x1<=(m_Container->Get_X()-m_x2) || m_Container->Get_Nesquinas()<=4)
	{
		if (m_z1<=(m_Container->Get_Z()-m_z2) )
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2) || m_Container->Get_Nesquinas()<=2)
			{
				
				Cambiar(m_distancia_origen,m_x1,m_y1,m_z1);
				m_origen_distancia=1;
			}
			else
			{


				//Posicion 2
				//solamente cambia la segunda componente por tanto
				Cambiar(m_distancia_origen,m_x1,m_Container->Get_Y()-m_y2,m_z1);
				m_origen_distancia=2;

			}
		}
		else
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2) || m_Container->Get_Nesquinas()<=2)
			
			{
				//Posicion 3

				Cambiar(m_distancia_origen,m_x1,m_y1,m_Container->Get_Z()-m_z2);
				m_origen_distancia=3;	

			}
			else
			{
			//Posicion 4
				Cambiar(m_distancia_origen,m_x1,m_Container->Get_Y()-m_y2,m_Container->Get_Z()-m_z2);
				m_origen_distancia=4;	
	
			}
		}

	}
	else
	{
		//Si el final esta antes del container pues tiene que ser uno de los 
		//primeros
		//Posicion 5
		if (m_z1<=(m_Container->Get_Z()-m_z2) )
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2) || m_Container->Get_Nesquinas()<=2)
			{
				Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_y1,m_z1);
				m_origen_distancia=5;
	
			}
			else
			{
				//Posicion 6
				Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_Container->Get_Y()-m_y2,m_z1);
				m_origen_distancia=6;

			}
		}
		else
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2) || m_Container->Get_Nesquinas()<=2)
			{

				//Posicion 7
				Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_y1,m_Container->Get_Z()-m_z2);
				m_origen_distancia=7;

			}
			else
			{
				//Posicion 8
				Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_Container->Get_Y()-m_y2,m_Container->Get_Z()-m_z2);
				m_origen_distancia=8;
			}
		}
	}
}
void SPACE::CalcularDistanciaOrigenEuclidea()
{
	//el primero la distancia al (0,0,0)

	//Tengo que hacer todo lo posible para que esta función evite calculos ya que consume
	//la mayor parte del porcentaje del tiempo
	//Tienen que tener a x1 menor que esto para que pueda ser uno de los 3 siguientes
	if (m_x1<=(m_Container->Get_X()-m_x2))
	{
		if (m_z1<=(m_Container->Get_Z()-m_z2))
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2))
			{
				
				m_val_dist=m_x1^2+m_y1^2+m_z1^2;
				m_origen_distancia=1;
			}
			else
			{


				//Posicion 2
				//solamente cambia la segunda componente por tanto
				m_val_dist=m_x1^2+(m_Container->Get_Y()-m_y2)^2+m_z1^2;
				m_origen_distancia=2;

			}
		}
		else
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2))
			
			{
				//Posicion 3

				m_val_dist=m_x1^2+(m_y2)^2+(m_Container->Get_Z()-m_z2)^2;
				m_origen_distancia=3;	

			}
			else
			{
			//Posicion 4
				m_val_dist=m_x1^2+(m_Container->Get_Y()-m_y2)^2+(m_Container->Get_Z()-m_z2)^2;
				m_origen_distancia=4;	
	
			}
		}

	}
	else
	{
		//Si el final esta antes del container pues tiene que ser uno de los 
		//primeros
		//Posicion 5
		if (m_z1<=(m_Container->Get_Z()-m_z2))
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2))
			{
				m_val_dist=(m_distancia_origen,m_Container->Get_X()-m_x2)^2+(m_y1)^2+(m_z1)^2;

				m_origen_distancia=5;
	
			}
			else
			{
				//Posicion 6
				m_val_dist=(m_distancia_origen,m_Container->Get_X()-m_x2)^2+(m_Container->Get_Y()-m_y2)^2+(m_z1)^2;

				m_origen_distancia=6;

			}
		}
		else
		{
			if (m_y1<=(m_Container->Get_Y()-m_y2))
			{

				//Posicion 7
				m_val_dist=(m_distancia_origen,m_Container->Get_X()-m_x2)^2+(m_y1)^2+(m_Container->Get_Z()-m_z2)^2;
				m_origen_distancia=7;

			}
			else
			{
				//Posicion 8
				m_val_dist=(m_distancia_origen,m_Container->Get_X()-m_x2)^2+(m_Container->Get_Y()-m_y2)^2+(m_Container->Get_Z()-m_z2)^2;

				m_origen_distancia=8;
			}
		}
	}
}
void SPACE::CalcularDistanciaOrigenDos()
{
//	m_origen_distancia=1;
//	return;
	//Si Distancia z
	if (m_Container->Get_tipo_origen()==2)
	{
		int alea=get_random(0,1);
		if ((m_z1-alea)<=(m_Container->Get_Z()-m_z2))
		{
					
			Cambiar(m_distancia_origen,m_x1,m_y1,m_z1);
			m_origen_distancia=1;
		}
		else
		{


			//Posicion 2
			//solamente cambia la segunda componente por tanto
			Cambiar(m_distancia_origen,m_x1,m_y1,m_Container->Get_Z()-m_z2);
			m_origen_distancia=3;

		}
	}
	if (m_Container->Get_tipo_origen()==0)
	{
		int alea=get_random(0,1);
		if ((m_x1-alea)<=(m_Container->Get_X()-m_x2))
		{
				
			Cambiar(m_distancia_origen,m_x1,m_y1,m_z1);
			m_origen_distancia=1;
		}
		else
		{


			//Posicion 2
			//solamente cambia la segunda componente por tanto
			Cambiar(m_distancia_origen,m_Container->Get_X()-m_x2,m_y1,m_z1);
			m_origen_distancia=5;

		}
	}
	if (m_Container->Get_tipo_origen()==1)
	{
		int alea=get_random(0,1);
		if ((m_y1-alea)<=(m_Container->Get_Y()-m_y2))
		{
				
			Cambiar(m_distancia_origen,m_x1,m_y1,m_z1);
			m_origen_distancia=1;
		}
		else
		{


			//Posicion 2
			//solamente cambia la segunda componente por tanto
			Cambiar(m_distancia_origen,m_x1,m_Container->Get_Y()-m_y2,m_z1);
			m_origen_distancia=2;

		}
	}
}
//Original Calcular distancia a origen sin cota
//Para el contenedor
// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z) 
//Para el space
// 1. (m_x1,m_y1, m_z1) ,2 . (m_x1,m_y2,m_z1) 3 (m_x1, m_y1, m_z2) 4 (m_x1,m_y2,m_z2)
// 5. (m_x2,m_y1, m_z1) ,6   (m_x2,m_y2,m_z1) 7 (m_x2,m_y1,m_z2) 8 (m_x2,m_y2,m_z2)
void SPACE::CalcularDistanciaOrigenOriginal()
{

}

bool CONTAINER::Mejor_DistA_Que_DistB_Origen(ORIG &A, int VolA,ORIG &B, int VolB)
{
	//Comparo componente a componente
	if (A.GetPrimero()>B.GetPrimero()) return false;
	if (A.GetPrimero()<B.GetPrimero()) return true;
	if (A.GetSegundo()>B.GetSegundo()) return false;
	if (A.GetSegundo()<B.GetSegundo()) return true;
	if (A.GetTercero()>B.GetTercero()) return false;
	if (A.GetTercero()<B.GetTercero()) return true;
	if (VolA<=VolB) return true;
	else 
		return false;
}
//Devuelve true si es mejor la primera que la segunda
bool CONTAINER::Mejor_DistA_Que_DistB_Espacios(ORIG &A, int VolA,ORIG &B, int VolB)
{
	//Comparo componente a componente
	if (A.GetPrimero()>B.GetPrimero()) return false;
	if (A.GetPrimero()<B.GetPrimero()) return true;
	if (A.GetSegundo()>B.GetSegundo()) return false;
	if (A.GetSegundo()<B.GetSegundo()) return true;
	if (A.GetTercero()>B.GetTercero()) return false;
	if (A.GetTercero()<B.GetTercero()) return true;
	if (VolA<=VolB) return true;
	else 
		return false;
}//Devuelve true si es mejor la primera que la segunda
bool CONTAINER::Mejor_DistA_Que_DistB_Espacios_Euclidea(int A, int VolA,int B, int VolB)
{
	if (A<B) return true;
	if (A>B) return false;
	if (VolA<=VolB) return true;
	else 
		return false;

}


//Devuelve true si es mejor el primer espacio al segundo
/*bool CONTAINER::Mejor_DistA_Que_DistB(SPACE &A ,SPACE &B)
{
//	if (m_tipo_eleccion_space==0)
//	{

	if (A.Get_Distancia().GetPrimero()>B.Get_Distancia().GetPrimero()) return false;
	if (A.Get_Distancia().GetPrimero()<B.Get_Distancia().GetPrimero()) return true;
	if (A.Get_Distancia().GetSegundo()>B.Get_Distancia().GetSegundo()) return false;
	if (A.Get_Distancia().GetSegundo()<B.Get_Distancia().GetSegundo()) return true;
	if (A.Get_Distancia().GetTercero()>B.Get_Distancia().GetTercero()) return false;
	if (A.Get_Distancia().GetTercero()<B.Get_Distancia().GetTercero()) return true;
	if (A.Get_Volumen()<=B.Get_Volumen()) return true;
	else 
		return false;
//	return Mejor_DistA_Que_DistB_Espacios(A.Get_Distancia(),A.Get_Volumen(),B.Get_Distancia(),B.Get_Volumen());
//	}
//	else
//		return Mejor_DistA_Que_DistB_Espacios_Euclidea(A.Get_Dist_Euclidea(),A.Get_Volumen(),B.Get_Dist_Euclidea(),B.Get_Volumen());
}*/
void CONTAINER::RestarConfiguracaosCon(CONFIGURACAO &grande, CONFIGURACAO &peque, std::list < CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista_b, bool &izq, bool &der, bool &abj, bool &arr, bool &den, bool &fue)
{
	//Función recursiva para eliminar superposiciones en el full supported
	
	int kkkk = 0;
	//Izquierda
	if (izq == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), peque.Get_x2(), peque.Get_y1(), peque.Get_z2(), grande.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloques(ConfElim, lista_b, false);
	}

	//Derecha
	if (der == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), peque.Get_x1(), grande.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloques(ConfElim, lista_b, false);
	}

	//Dentro
	if (den == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), grande.Get_x2(), peque.Get_y1(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloques(ConfElim, lista_b, false);
	}

	//Fuera
	if (fue == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), peque.Get_x1(), peque.Get_y2(), peque.Get_z2(), peque.Get_x2(), grande.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloques(ConfElim, lista_b, false);
	}

	//Arriba
	if (arr == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, peque.Get_Id(), peque.Get_x1(), peque.Get_y1(), peque.Get_z2(), peque.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), peque.Get_orig());
		ActualizarListaDeBloques(ConfElim, lista_b, false);
	}

	//Abajo
	if (abj == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, peque.Get_Id(), peque.Get_x1(), peque.Get_y1(), peque.Get_z2(), peque.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), peque.Get_orig());
		ActualizarListaDeBloquesAbajo(ConfElim, lista_b,grande);
	}

	if (kkkk == 0)
	{
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), grande.Get_x2(), grande.Get_y2(), this->Get_Z(), grande.Get_Tipo(), grande.Get_Num(), grande.Get_orig());
		ActualizarListaDeBloques(ConfElim, lista_b, false);
	}

	/*if (kkkk != 1)
	{
		printf("algo va mal");
		for (int i = 0;;);
	}*/


}
void CONTAINER::RestarConfiguracaosConReducir(CONFIGURACAO &grande, CONFIGURACAO &peque, std::list < CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista_b, std::list<CONFIGURACAO> &lista2, bool &izq, bool &der, bool &abj, bool &arr, bool &den, bool &fue)
{
	//Función recursiva para eliminar superposiciones en el full supported

	int kkkk = 0;
	//Izquierda
	if (izq == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), peque.Get_x2(), peque.Get_y1(), peque.Get_z2(), grande.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesReducir(ConfElim, lista_b,lista2);
	}

	//Derecha
	if (der == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), peque.Get_x1(), grande.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesReducir(ConfElim, lista_b,lista2);
	}

	//Dentro
	if (den == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), grande.Get_x2(), peque.Get_y1(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesReducir(ConfElim, lista_b,lista2);
	}

	//Fuera
	if (fue == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), peque.Get_x1(), peque.Get_y2(), peque.Get_z2(), peque.Get_x2(), grande.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesReducir(ConfElim, lista_b,lista2);
	}

	//Arriba
	if (arr == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, peque.Get_Id(), peque.Get_x1(), peque.Get_y1(), peque.Get_z2(), peque.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), peque.Get_orig());
		ActualizarListaDeBloquesReducir(ConfElim, lista_b,lista2);
	}

	//Abajo
	if (abj == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, peque.Get_Id(), peque.Get_x1(), peque.Get_y1(), peque.Get_z2(), peque.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), peque.Get_orig());
		ActualizarListaDeBloquesReducirAbajo(ConfElim, lista_b, lista2,grande);
	}

	if (kkkk == 0)
	{
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), grande.Get_x2(), grande.Get_y2(), this->Get_Z(), grande.Get_Tipo(), grande.Get_Num(), grande.Get_orig());
		ActualizarListaDeBloquesReducir(ConfElim, lista_b,lista2);
	}

	/*if (kkkk != 1)
	{
		printf("algo va mal");
		for (int i = 0;;);
	}*/


}
void CONTAINER::RestarConfiguracaosConReducirVol(CONFIGURACAO &grande, CONFIGURACAO &peque, std::list < CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista_b, int vol, bool &izq, bool &der, bool &abj, bool &arr, bool &den, bool &fue)
{
	//Función recursiva para eliminar superposiciones en el full supported

	int kkkk = 0;
	//Izquierda
	if (izq == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), peque.Get_x2(), peque.Get_y1(), peque.Get_z2(), grande.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesReducirVol(ConfElim, lista_b, vol);
	}

	//Derecha
	if (der == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), peque.Get_x1(), grande.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesReducirVol(ConfElim, lista_b, vol);
	}

	//Dentro
	if (den == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), grande.Get_x2(), peque.Get_y1(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesReducirVol(ConfElim, lista_b, vol);
	}

	//Fuera
	if (fue == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, grande.Get_Id(), peque.Get_x1(), peque.Get_y2(), peque.Get_z2(), peque.Get_x2(), grande.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesReducirVol(ConfElim, lista_b, vol);
	}

	//Arriba
	if (arr == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, peque.Get_Id(), peque.Get_x1(), peque.Get_y1(), peque.Get_z2(), peque.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), peque.Get_orig());
		ActualizarListaDeBloquesReducirVol(ConfElim, lista_b, vol);
	}

	//Abajo
	if (abj == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(this, peque.Get_Id(), peque.Get_x1(), peque.Get_y1(), peque.Get_z2(), peque.Get_x2(), peque.Get_y2(), this->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), peque.Get_orig());
		ActualizarListaDeBloquesReducirVol(ConfElim, lista_b, vol);
	}

	if (kkkk == 0)
	{
		CONFIGURACAO ConfElim(this, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), grande.Get_x2(), grande.Get_y2(), this->Get_Z(), grande.Get_Tipo(), grande.Get_Num(), grande.Get_orig());
		ActualizarListaDeBloquesReducirVol(ConfElim, lista_b, vol);
	}

	/*if (kkkk != 1)
	{
		printf("algo va mal");
		for (int i = 0;;);
	}*/


}

void MOVIMIENTO::RestarConfiguracaos(CONFIGURACAO &grande, CONFIGURACAO &peque, std::list < CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista_b, bool &izq, bool &der, bool &abj, bool &arr, bool &den, bool &fue)
{
	int kkkk = 0;	//Función recursiva para eliminar superposiciones en el full supported
	//Izquierda
	if (izq == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(m_Container, grande.Get_Id(), peque.Get_x2(), peque.Get_y1(), peque.Get_z2(), grande.Get_x2(), peque.Get_y2(), m_Container->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesQuita(ConfElim, lista_b, false);
	}

	//Derecha
	if (der == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(m_Container, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), peque.Get_x1(), grande.Get_y2(), m_Container->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesQuita(ConfElim, lista_b,false);
	}

	//Dentro
	if (den == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(m_Container, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), grande.Get_x2(), peque.Get_y1(), m_Container->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesQuita(ConfElim, lista_b,false);
	}

	//Fuera
	if (fue == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(m_Container, grande.Get_Id(), peque.Get_x1(), peque.Get_y2(), peque.Get_z2(), peque.Get_x2(), grande.Get_y2(), m_Container->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), grande.Get_orig());
		ActualizarListaDeBloquesQuita(ConfElim, lista_b,false);
	}

	//Arriba
	if (arr == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(m_Container, peque.Get_Id(), peque.Get_x1(), peque.Get_y1(), peque.Get_z2(), peque.Get_x2(), peque.Get_y2(), m_Container->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), peque.Get_orig());
		ActualizarListaDeBloquesQuita(ConfElim, lista_b, false);
	}

	//Abajo
	if (abj == true)
	{
		kkkk++;
		CONFIGURACAO ConfElim(m_Container, peque.Get_Id(), peque.Get_x1(), peque.Get_y1(), peque.Get_z2(), peque.Get_x2(), peque.Get_y2(), m_Container->Get_Z(), peque.Get_Tipo(), (grande.Get_Num() - peque.Get_Num()), peque.Get_orig());
		ActualizarListaDeBloquesQuitaAbajo(ConfElim, lista_b, false,grande);
	}

	if (kkkk == 0)
	{
		CONFIGURACAO ConfElim(m_Container, grande.Get_Id(), grande.Get_x1(), grande.Get_y1(), grande.Get_z2(), grande.Get_x2(), grande.Get_y2(), m_Container->Get_Z(), grande.Get_Tipo(), grande.Get_Num(), grande.Get_orig());
		ActualizarListaDeBloquesQuita(ConfElim, lista_b, false);
	}

	/*if (kkkk != 1)
	{
		printf("algo va mal");
		for (int i = 0;;);
	}*/
	

}

SPACE & CONTAINER::ElegirSpace(bool &posi)
{
	std::list<SPACE> ::iterator it,elegido;
	bool quedan_todavia=false;
	bool primero=true;;
	//Los recorro todos comparando cual es el mejor
	std::list< SPACE > ::iterator itfin=m_Spaces.end();

	for (it=m_Spaces.begin();it!=itfin;)
	{
//		SPACE kk=(*it);
		if ((*it).Get_Flag()==false  && (m_multicontainer==true || (m_multicontainer==false && (*it).Get_dx()>=m_dimension_menor_x  && (*it).Get_dy()>=m_dimension_menor_y  && (*it).Get_dz()>=m_dimension_menor_z )))
		{
//			if (m_multicontainer==true)
//				return (*it);
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
			++it;	
		}
		//Funcion que me elimina los espacios 
		//si la quito todo funsiona igual 
		else
		{
			//cambiado el 16_02
//			if (m_eliminar_espacios==true && (*it).Get_Bin()==false)
			if (m_eliminar_espacios==true )
			{
				//si es uno de los originales lo borro en otro caso NO

				it=m_Spaces.erase(it);
				if (it==itfin && m_Spaces.size()>0)
				{
					it=m_Spaces.begin();

				}
			}
			else
				++it;

		}


	}

	if (quedan_todavia==false || m_Spaces.size()==0) 
	{
//		printf("No quedan espacios");
//		if (m_max_total_volumen_ocupado==0)
//			m_max_total_volumen_ocupado=m_total_volumen_ocupado;
/*		if (m_Aleatorizado==false && m_mejora_local==false)
		{
			FILE *fin3;
			fopen_s(&fin3,"Results.txt","a+");
			double pt=((double)m_total_volumen_ocupado/(double)m_total_volumen)*100;
			fprintf(fin3,"%s\tV\t%d\tVU\t%d\t%f\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,pt);
			fclose(fin3);
		}
*/		
		SPACE espacio(0,0,0,0,0,0,this);
		
		return espacio;
	}
	posi=true;
	return (*elegido);
}

void CONTAINER::ElegirSpace(SPACE &espacio, bool &posi)
{
	std::list<SPACE> ::iterator it,elegido;
	bool quedan_todavia=false;
	bool primero_1=true;;
	//Los recorro todos comparando cual es el mejor
	std::list< SPACE > ::iterator itfin=m_Spaces.end();

	for (it=m_Spaces.begin();it!=itfin;)
	{
//		SPACE kk=(*it);
		if ((*it).Get_Flag()==false  && ( m_multicontainer==true || (m_multicontainer==false && (*it).Get_dx()>=m_dimension_menor_x  && (*it).Get_dy()>=m_dimension_menor_y  && (*it).Get_dz()>=m_dimension_menor_z )))
		{
//			if (m_multicontainer==true)
//				return (*it);
			quedan_todavia=true;
			if (primero_1==true) 
			{
				elegido=it;
				primero_1=false;

			}
			else
			{
				if (Mejor_DistA_Que_DistB((*elegido),(*it))==false)
				{
					elegido=it;
				}
			}
			++it;	
		}
		//Funcion que me elimina los espacios 
		//si la quito todo funsiona igual 
		else
		{
			//cambiado el 16/02/2015
//			if (m_eliminar_espacios==true && (*it).Get_Bin()==false)
			if (m_eliminar_espacios==true )
			{
				//si es uno de los originales lo borro en otro caso NO

				it=m_Spaces.erase(it);
				if (it==itfin && m_Spaces.size()>0)
				{
					it=m_Spaces.begin();

				}
			}
			else
				++it;

		}


	}

	if (quedan_todavia==false || m_Spaces.size()==0) 
	{
//		printf("No quedan espacios");
//		if (m_max_total_volumen_ocupado==0)
//			m_max_total_volumen_ocupado=m_total_volumen_ocupado;
/*		if (m_Aleatorizado==false && m_mejora_local==false)
		{
			FILE *fin3;
			fopen_s(&fin3,"Results.txt","a+");
			double pt=((double)m_total_volumen_ocupado/(double)m_total_volumen)*100;
			fprintf(fin3,"%s\tV\t%d\tVU\t%d\t%f\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,pt);
			fclose(fin3);
		}
*/		
//		SPACE espacio(0,0,0,0,0,0,this);
		
		return ;
	}
	posi=true;
	espacio.ModificarSpace(elegido->Get_x1(),elegido->Get_y1(),elegido->Get_z1(),elegido->Get_x2(),elegido->Get_y2(),elegido->Get_z2());
}

//Esta función es la que me elije un space de la lista de espacios
//el número de espacios tiene que ser de por lo menos uno para que funcione
SPACE & CONTAINER::ElegirSpace()
{
	std::list<SPACE> ::iterator it,elegido;
	bool quedan_todavia=false;
	bool primero=true;;
	//Los recorro todos comparando cual es el mejor
	std::list< SPACE > ::iterator itfin=m_Spaces.end();
/*	if (m_multicontainer==true && m_Aleatorizado==true)
	{
		int alea=get_random(0,m_Spaces.size());
		int cont=0;
		for (it=m_Spaces.begin();it!=itfin;)
		{
			if (alea==cont)
				return (*it);
			cont++;
		}
	}
*/	for (it = m_Spaces.begin(); it != itfin;)
	{
		//		SPACE kk=(*it);
		//		if (m_Aleatorizado==true)
		//			if (kk==k) return (*it);
	if ((*it).Get_Flag() == false && (m_multicontainer == true || (m_multicontainer == false && (*it).Get_dx() >= m_dimension_menor && (*it).Get_dy() >= m_dimension_menor && (*it).Get_dz() >= m_dimension_menor && (*it).Get_Volumen() >= m_menor_volumen)))
	{
			quedan_todavia = true;
			if (primero == true)
			{
				/*if (m_Aleatorizado == false)
				{
					if (m_full_supported == true)
						return *it;
				}*/
				elegido = it;
				primero = false;

			}
			else
			{
				if (m_Aleatorizado == false)
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
				//				elegido=it;
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
						if ((*it).Get_z1() < (*elegido).Get_z1())
							elegido = it;
						if ((*it).Get_z1() == (*elegido).Get_z1())
						{
							if (Mejor_DistA_Que_DistB((*elegido), (*it)) == false)
							{
								elegido = it;
							}
						}
					}

				}
			}
			++it;
		}
		//Funcion que me elimina los espacios 
		//si la quito todo funsiona igual 
		else
		{
			if (m_eliminar_espacios==true)
			    it=m_Spaces.erase(it);
			else
				++it;

		}


	}

	if (quedan_todavia==false || m_Spaces.size()==0) 
	{
//		std::list< SPACE > ::iterator itkk=m_Spaces.begin();
////		if (m_Spaces.size()==0)
//			return (*itkk);
//		printf("No quedan espacios");
//		if (m_max_total_volumen_ocupado==0)
//			m_max_total_volumen_ocupado=m_total_volumen_ocupado;
/*		if (m_Aleatorizado==false && m_mejora_local==false)
		{
			FILE *fin3;
			fin3=fopen("Results.txt","a+");
			double pt=((double)m_total_volumen_ocupado/(double)m_total_volumen)*100;
			fprintf(fin3,"%s\tV\t%d\tVU\t%d\t%f\n",m_Nombre,m_total_volumen,m_total_volumen_ocupado,pt);
			fclose(fin3);
		}
*/		
		return m_Spaces.front();
	}
	return (*elegido);
}
//Esta función es la que me elije un space de la lista de espacios
//el número de espacios tiene que ser de por lo menos uno para que funcione
SPACE & CONTAINER::ElegirSpaceConstruccion()
{
	std::list<SPACE> ::iterator it,elegido;
	bool quedan_todavia=false;
	bool primero=true;;
	//Los recorro todos comparando cual es el mejor
	std::list< SPACE > ::iterator itfin=m_Spaces.end();
	for (it=m_Spaces.begin();it!=itfin;it++)
	{
//		SPACE kk=(*it);
		if ((*it).Get_Flag()==false)
		{
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
	if (quedan_todavia==false || m_Spaces.size()==0) 
	{
		
		return m_Spaces.front();
	}
	return (*elegido);
}
//Esta función es la que me elije un space de la lista de espacios
//el número de espacios tiene que ser de por lo menos uno para que funcione
SPACE & CONTAINER::ElegirSpaceConstruccionNueva(bool rapido)
{
		std::list<SPACE> ::iterator it, elegido;
		bool quedan_todavia = false;
		bool primero = true;;
		//Los recorro todos comparando cual es el mejor
		std::list< SPACE > ::iterator itfin = m_Spaces.end();
		for (it = m_Spaces.begin(); it != itfin; it++)
		{
			//		SPACE kk=(*it);
					/*if (rapido == true)
					{*/
			if ((*it).Get_Flag() == false)
			{
				quedan_todavia = true;
				if (primero == true)
				{
					elegido = it;
					primero = false;

				}
				else
				{
					if (Mejor_DistA_Que_DistB((*elegido), (*it)) == false)
					{
						elegido = it;
					}
				}
			}
			if (primero == false && rapido == true)
				break;
			//Funcion que me elimina los espacios 
			//si la quito todo funsiona igual 
		}
		if (quedan_todavia == false || m_Spaces.size() == 0)
		{

			return m_Spaces.front();
		}
		return (*elegido);
}
SPACE& CONTAINER::ElegirSpacePonerConfiguracao(std::list<CONFIGURACAO> lista)
{
	std::list<CONFIGURACAO>::iterator C = lista.begin();
	std::list<SPACE>::iterator itS, itSfin = m_Spaces.end();

	for (itS = m_Spaces.begin(); itS != itSfin; itS++)
	{
		if ((*itS).Get_x1() <= (*C).Get_x1() && (*itS).Get_y1() <= (*C).Get_y1() && (*itS).Get_z1() == (*C).Get_z1() &&
			(*itS).Get_x2() >= (*C).Get_x2() && (*itS).Get_y2() >= (*C).Get_y2() && (*itS).Get_z2() >= (*C).Get_z2())
			return *itS;
	}
}


CONFIGURACAO::CONFIGURACAO(CONTAINER *a ,int Id, int x1,int y1, int z1, int x2, int y2, int z2,short int tipo , int num,short int orig)
{
	m_Id=Id;
	m_origen_distancia=orig;
	m_x1=x1; m_y1=y1; m_z1=z1;
	m_x2=x2; m_y2=y2; m_z2=z2;
	m_tipo=tipo;
	m_num=num;
	m_Volumen=(x2-x1)*(y2-y1)*(z2-z1);
	m_Container=a;
	m_bloque = false;
	m_dx = 0;
	m_dy = 0;
	m_dz = 0;
	/*m_Id_bloque = 0;*/

}
CONFIGURACAO::CONFIGURACAO(CONTAINER *a ,int Id, int x1,int y1, int z1, int tx, int ty, int tz,int dx, int dy, int dz,  short int tipo , int num,short int orig)
{
	m_Id=Id;
	m_x1=x1; m_y1=y1; m_z1=z1;
	m_origen_distancia=orig;
	m_x2=x1+tx; m_y2=y1+ty; m_z2=z1+tz;
	m_dx=dx; m_dy=dy; m_dz=dz; 
	m_tipo=tipo;
	m_num=m_dx*m_dy*m_dz;
	m_Volumen=(m_x2-m_x1)*(m_y2-m_y1)*(m_z2-m_z1);
	m_Container=a;
	m_bloque = false;
	/*m_Id_bloque = 0;*/

}
CONFIGURACAO::CONFIGURACAO(CONTAINER *a ,ORIG sm, int num)
{
	m_Id=99999;
	m_x1=0; m_y1=0; m_z1=0;
	m_x2=0; m_y2=0; m_z2=0;
	m_tipo=0;
	m_origen_distancia = 0;
	m_set_distancias=sm;
	m_num=num;
	m_Volumen=0;
	m_Container=a;
	m_bloque = false;
	m_dx = 0;
	m_dy = 0;
	m_dz = 0;
	/*m_Id_bloque = 0;*/


}
CONFIGURACAO::CONFIGURACAO(CONTAINER *a )
{

	m_Id=99999;
	m_origen_distancia=0;
	m_x1=0; m_y1=0; m_z1=0;
	m_x2=0; m_y2=0; m_z2=0;
	m_tipo=0;
	m_Volumen=0;
	m_Container=a;
	m_bloque = false;
	m_dx = 0;
	m_dy = 0;
	m_dz = 0;
	m_num = 0;
	/*m_Id_bloque = 0;*/
}
int CONTAINER::Estimacion(SPACE &Espacio)
{
	int estima=0;
	for (int icp=0;icp<m_Q;icp++)
	{
		if (m_Pieces[icp].Get_Num()<m_Pieces[icp].Get_q())
		{
//			int esima_pieza=0;
			//Aqui pongo algo por si solamente existe una copia para que no la meta
			//muchas veces
//			if (estima_pieza>0 && (m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num())==1)
//			{
//				estima++;
//				continue;
//			}
			if (m_multicontainer==false && m_por_bin==false)
			{
				if (m_Pieces[icp].Get_Rz()==true)
				{
					estima+=EstimacionConEstaOrientacion(Espacio,m_Pieces[icp].Get_x(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_Id(),m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num());
					estima+=EstimacionConEstaOrientacion(Espacio,m_Pieces[icp].Get_y(),m_Pieces[icp].Get_x(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_Id(),m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num());
				}
				if (m_Pieces[icp].Get_Ry()==true)
				{
					estima+=EstimacionConEstaOrientacion(Espacio,m_Pieces[icp].Get_x(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_Id(),m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num());	
					estima+=EstimacionConEstaOrientacion(Espacio,m_Pieces[icp].Get_z(),m_Pieces[icp].Get_x(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_Id(),m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num());
				}
				if (m_Pieces[icp].Get_Rx()==true)
				{
					estima+=EstimacionConEstaOrientacion(Espacio,m_Pieces[icp].Get_z(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_x(),m_Pieces[icp].Get_Id(),m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num());
					estima+=EstimacionConEstaOrientacion(Espacio,m_Pieces[icp].Get_y(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_x(),m_Pieces[icp].Get_Id(),m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num());
				}
			}
			else
			{
				if ((Espacio.Get_dx()>=m_Pieces[icp].Get_x() &&
					Espacio.Get_dy()>=m_Pieces[icp].Get_y() &&
					Espacio.Get_dz()>=m_Pieces[icp].Get_z()))
					estima+=m_Pieces[icp].Get_q();
//				estima+=EstimacionConEstaOrientacion(Espacio,m_Pieces[icp].Get_x(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_Id(),m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num());
			}
//			estima=estima+estima_pieza;
		}
	}
	return estima;

}
/*
int CONTAINER::EstimacionConEstaOrientacionAlguna(int dx,int dy,int dz, int x, int y,int z, int Id,int piezas_maximas)
{
	if (!(dx>=x &&
		dy>=y &&
		dz>=z))
		return 0;
	else return 1;

}*/
int CONTAINER::EstimacionConEstaOrientacion(SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas)
{
	if (!(Espacio.Get_dx()>=x &&
		Espacio.Get_dy()>=y &&
		Espacio.Get_dz()>=z))
		return 0;
	if (piezas_maximas==1) return 1;
	int suma=0;
	int Eje_x=min(Espacio.Get_dx()/x,piezas_maximas);
	int Eje_y=min(Espacio.Get_dy()/y,piezas_maximas);
	int Eje_z=min(Espacio.Get_dz()/z,piezas_maximas);
	if (Eje_x>1)
		suma++;
	if (Eje_y>1)
		suma++;
	if (Eje_z>1)
		suma++;
	return suma;

}
bool CONTAINER::CabeAlguna(int dx,int dy, int dz)
{

	bool cabe_alguna=0;
	for (int icp=0;icp<m_Q;icp++)
	{
		if (m_Pieces[icp].Get_Num()<m_Pieces[icp].Get_q())
		{
//			int esima_pieza=0;
			//Aqui pongo algo por si solamente existe una copia para que no la meta
			//muchas veces
//			if (estima_pieza>0 && (m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num())==1)
//			{
//				estima++;
//				continue;
//			}
			if (m_Pieces[icp].Get_Rz()==true)
			{
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_x(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_z());
				if (cabe_alguna==true) return true;

				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_y(),m_Pieces[icp].Get_x(),m_Pieces[icp].Get_z());
				if (cabe_alguna==true) return true;
			}
			if (m_Pieces[icp].Get_Ry()==true)
			{
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_x(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_y());
				if (cabe_alguna==true) return true;
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_z(),m_Pieces[icp].Get_x(),m_Pieces[icp].Get_y());
				if (cabe_alguna==true) return true;
			}
			if (m_Pieces[icp].Get_Rx()==true)
			{
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_z(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_x());
				if (cabe_alguna==true) return true;
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_y(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_x());
				if (cabe_alguna==true) return true;
			}
//			estima=estima+estima_pieza;
		}
	}
	return false;
}
bool CONTAINER::CabeAlgunaMov(int dx,int dy, int dz)
{

	bool cabe_alguna=false;
	for (int icp=0;icp<m_Q;icp++)
	{
		if (m_Pieces_Tabu[icp]<m_Pieces[icp].Get_q())
		{
//			int esima_pieza=0;
			//Aqui pongo algo por si solamente existe una copia para que no la meta
			//muchas veces
//			if (estima_pieza>0 && (m_Pieces[icp].Get_q()-m_Pieces[icp].Get_Num())==1)
//			{
//				estima++;
//				continue;
//			}
			if (m_Pieces[icp].Get_Rz()==true)
			{
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_x(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_z());
				if (cabe_alguna==true) return true;

				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_y(),m_Pieces[icp].Get_x(),m_Pieces[icp].Get_z());
				if (cabe_alguna==true) return true;
			}
			if (m_Pieces[icp].Get_Ry()==true)
			{
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_x(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_y());
				if (cabe_alguna==true) return true;
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_z(),m_Pieces[icp].Get_x(),m_Pieces[icp].Get_y());
				if (cabe_alguna==true) return true;
			}
			if (m_Pieces[icp].Get_Rx()==true)
			{
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_z(),m_Pieces[icp].Get_y(),m_Pieces[icp].Get_x());
				if (cabe_alguna==true) return true;
				cabe_alguna=EstimacionConEstaOrientacionAlguna(dx,dy,dz,m_Pieces[icp].Get_y(),m_Pieces[icp].Get_z(),m_Pieces[icp].Get_x());
				if (cabe_alguna==true) return true;
			}
//			estima=estima+estima_pieza;
		}
	}
	return false;
}
//Esta funcion es la que devuelve la mejor configuración
//de las cajas en el espacio
void CONTAINER::ElegirConfiguracao(SPACE &Espacio,CONFIGURACAO &Configuracao)	
{
	//Para el aleatorizado hago una estimacion que va a ser una estimacion d
	//los que puedo tener en la lista mas o menos
	if (m_objetivo_mixto == true)
	{
		if (get_random(0, 1) == 1)
			m_objetivo_vol = true;
		else
			m_objetivo_vol = false;
	}
	if (m_Aleatorizado==true)
	{
		m_TamRCL=Estimacion(Espacio);
		if (m_TamRCL==0) 
			return;
		//Tamaño de la lista de posibles
//		printf("Tam RCL %d %f %f",m_TamRCL,m_Delta,m_TamRCL*m_Delta);

		m_TamRCL=ceil((double)m_TamRCL*m_Delta);
//		printf("TRCL %d\t%d\t ",m_TamRCL,m_Configuracaos.size());

	}
	if (m_multicontainer==false && m_por_bin==false)
	{

	if (m_tipo_mixto==true)
	{
		if (get_random(0,1)==1)
			m_objetivo_capas=true;
		else
			m_objetivo_capas=false;
	}
	if (m_objetivo_capas == true)
	{
		if (m_por_bloques == true)
		{
			std::list< BLOQUE > ::iterator itb;
			for (itb = m_Bloques.begin(); itb != m_Bloques.end(); itb++)
			{
				//m_Container->Get_Piezas()[id1].Get_q() / num1, m_Container->Get_Piezas()[id2].Get_q() / num2
				if ((*itb).Get_Num1() <= m_Pieces[(*itb).Get_Id1()].Get_q() - m_Pieces[(*itb).Get_Id1()].Get_Num() && (*itb).Get_Num2() <= m_Pieces[(*itb).Get_Id2()].Get_q() - m_Pieces[(*itb).Get_Id2()].Get_Num())
					Configuracao.MejorCapaDeUnaBloque(Espacio, (*itb));

			}
		}
		for (int imc=0;imc<m_Q;imc++)
		{	
			
			if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
			Configuracao.MejorCapaDeUnaPieza(Espacio,m_Pieces[imc]);
		}
	}
	else
	{
		for (int imc=0;imc<m_Q;imc++)
		{	
			if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
				//Cambiar para que vaya con columnas
			Configuracao.MejorColumnaDeUnaPieza(Espacio,m_Pieces[imc]);
		}

	}
	}
	else
	{
		if (m_rotacion==false)
		{
		for (int imc=0;imc<m_Q;imc++)
		{	
//			if ((imc)==56)
//				printf("KK");
//			int kk=m_Pieces[imc].Get_Num();
			if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
//			Configuracao.MejorPieza(Espacio,m_Pieces[imc]);
			Configuracao.CompararConCapas(1,Espacio,m_Pieces[imc].Get_x(),m_Pieces[imc].Get_y(),m_Pieces[imc].Get_z(),m_Pieces[imc].Get_Id(),(m_Pieces[imc].Get_q()-m_Pieces[imc].Get_Num()));
			if (m_objetivo_vol==true && m_ListaRCL.size()==m_TamRCL) 
				break;
		}
		}
		else
		{
			for (int imc=0;imc<m_Q;imc++)
			{	

				if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
				Configuracao.MejorCapaDeUnaPieza(Espacio,m_Pieces[imc]);
			}
		}
	}


	//Si es aleatorizado ya tengo todos ahora tengo que elegir uno
	if (m_Aleatorizado==true)
	{
		//Elegir uno al azar 
		//Puede ser que la estimacion sea por encima y luego no pueda
		//colocar tantas por esto
		int alea=get_random(0,min(m_TamRCL-1,(int)m_ListaRCL.size()-1));
		int cont=0;
		std::list < CONFIGURACAO > ::iterator it;
		for (it=m_ListaRCL.begin();it!=m_ListaRCL.end();it++)
		{
			if (alea==cont) 
			{
				/*m_Configuracaos.push_back((*it));*/
				InsertarConfiguracaoOrden(*it, m_Configuracaos);
//				m_total_volumen_ocupado+=(*it).Get_Volumen();
				Configuracao=(*it);
				m_ListaRCL.clear();
				return;
			}
		
			cont++;

		}
	}
	if (Configuracao.Get_Id()!=99999 && Configuracao.Get_Id()<1000)
	{
		
		/*m_Configuracaos.push_back(Configuracao);*/
		InsertarConfiguracaoOrden(Configuracao, m_Configuracaos);
//		m_total_volumen_ocupado+=Configuracao.Get_Volumen();
	}

}
void CONTAINER::ElegirConfiguracao(SPACE &Espacio,CONFIGURACAO &Configuracao,int num)	
{
	//Para el aleatorizado hago una estimacion que va a ser una estimacion d
	//los que puedo tener en la lista mas o menos
	if (m_Aleatorizado==true)
	{
		m_TamRCL=Estimacion(Espacio);
		if (m_TamRCL==0) 
			return;
		//Tamaño de la lista de posibles
//		printf("Tam RCL %d %f %f",m_TamRCL,m_Delta,m_TamRCL*m_Delta);

		m_TamRCL=ceil((double)m_TamRCL*m_Delta);
//		printf("TRCL %d\t%d\t ",m_TamRCL,m_Configuracaos.size());

	}
	if (m_multicontainer==false && m_por_bin==false)
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
			
			if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
			Configuracao.MejorCapaDeUnaPieza(Espacio,m_Pieces[imc]);
		}
	}
	else
	{
		for (int imc=0;imc<m_Q;imc++)
		{	
			
			if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
				//Cambiar para que vaya con columnas
			Configuracao.MejorColumnaDeUnaPieza(Espacio,m_Pieces[imc]);
		}

	}
	}
	else
	{
		for (int imc=0;imc<m_Q;imc++)
		{	
			
			if (m_Pieces[imc].Get_Num()<m_Pieces[imc].Get_q())
//			Configuracao.MejorPieza(Espacio,m_Pieces[imc]);
			Configuracao.CompararConCapas(1,Espacio,m_Pieces[imc].Get_x(),m_Pieces[imc].Get_y(),m_Pieces[imc].Get_z(),m_Pieces[imc].Get_Id(),(m_Pieces[imc].Get_q()-m_Pieces[imc].Get_Num()));
//			Configuracao.CompararConCapas(1,Espacio,m_Pieces[imc].Get_x(),m_Pieces[imc].Get_y(),m_Pieces[imc].Get_z(),m_Pieces[imc].Get_Id(),1);
			if (m_objetivo_vol==true && m_ListaRCL.size()==m_TamRCL && (m_tipo_orden_pieces==3 || (m_tipo_orden_pieces==5 && Espacio.Get_x1()==0 && Espacio.Get_y1()==0))) 
				break;
		}
	}


	//Si es aleatorizado ya tengo todos ahora tengo que elegir uno
	if (m_Aleatorizado==true)
	{
		//Elegir uno al azar 
		//Puede ser que la estimacion sea por encima y luego no pueda
		//colocar tantas por esto
		int alea=get_random(0,min(m_TamRCL-1,(int)m_ListaRCL.size()-1));
		int cont=0;
		std::list < CONFIGURACAO > ::iterator it;
		for (it=m_ListaRCL.begin();it!=m_ListaRCL.end();it++)
		{
			if (alea==cont) 
			{
				std::list< std::pair< int, std:: list < CONFIGURACAO > >  >::iterator itB;
				int cont2=0;
				bool colocado=false;
				for(itB=m_ConfiguracaosMC.begin();itB!=m_ConfiguracaosMC.end() && colocado==false;itB++)
				{
					if (cont2==num)
					{
						colocado=true;
						(*itB).second.push_back((*it));
						(*itB).first+=(*it).Get_Volumen();
						break;
					}
					cont2++;
				}
				if (colocado==false)
				{
					std::list<CONFIGURACAO> lista_configuracaos;
					lista_configuracaos.push_back(*it);
					std::pair< int, std::list < CONFIGURACAO >  > p((*it).Get_Volumen(),lista_configuracaos);
					m_ConfiguracaosMC.push_back(p);
				}

//				m_total_volumen_ocupado+=(*it).Get_Volumen();
				Configuracao=(*it);
				m_ListaRCL.clear();
				return;
			}
		
			cont++;

		}
	}
	if (Configuracao.Get_Id()!=99999)
	{
		std::list< std::pair< int, std:: list < CONFIGURACAO > >  >::iterator it;
		int cont=0;
		bool colocado=false;
		for(it=m_ConfiguracaosMC.begin();it!=m_ConfiguracaosMC.end() && colocado==false;it++)
		{
			colocado=true;
			if (cont==num)
			{

				(*it).second.push_back(Configuracao);
				(*it).first+=Configuracao.Get_Volumen();
			}
			cont++;
		}
		if (colocado==false)
		{
			std::list<CONFIGURACAO> lista_configuracaos;
			lista_configuracaos.push_back(Configuracao);

			std::pair< int, std::list < CONFIGURACAO > > p(Configuracao.Get_Volumen(),lista_configuracaos);
			m_ConfiguracaosMC.push_back(p);
		}


//		m_total_volumen_ocupado+=Configuracao.Get_Volumen();
	}

}

//Esta funcion es la que pone la configuracao donde toque
void CONTAINER::PonerConfiguracao(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista,bool compactada)	
{
	std::list<CONFIGURACAO> ::iterator it,itfin=lista.end(),it2, it3;
	//Tengo que bucar una configuracao que tenga de vertice el mismo que el space
	bool fin=false;
	bool primero = true;
	for (it=lista.begin();it!=itfin && fin!=true && primero==true;)
	{
		//Me vale cualquiera de los que tengo o mejor
		//lo busco para el que me haya dicho el 

		//Si compactada==false, habría que arreglar el if para que funcione con bloques bien (puede que entre una configuracao, pero la otra no)
		if (compactada==false)
		{
			switch (Espacio.Get_origen_distancia())
			{
				case 1:
				{
					if (Espacio.Get_x1()==(*it).Get_x1() &&
						Espacio.Get_y1()==(*it).Get_y1() &&
						Espacio.Get_z1()==(*it).Get_z1() )
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
					if (Espacio.Get_x1()==(*it).Get_x1() &&
						Espacio.Get_y2()==(*it).Get_y2() &&
						Espacio.Get_z1()==(*it).Get_z1() )
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
					if (Espacio.Get_x1()==(*it).Get_x1() &&
						Espacio.Get_y1()==(*it).Get_y1() &&
						Espacio.Get_z2()==(*it).Get_z2() )
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
					if (Espacio.Get_x1()==(*it).Get_x1() &&
						Espacio.Get_y2()==(*it).Get_y2() &&
						Espacio.Get_z2()==(*it).Get_z2() )
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
					if (Espacio.Get_x2()==(*it).Get_x2() &&
						Espacio.Get_y1()==(*it).Get_y1() &&
						Espacio.Get_z1()==(*it).Get_z1() )	

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
					if (Espacio.Get_x2()==(*it).Get_x2() &&
						Espacio.Get_y2()==(*it).Get_y2() &&
						Espacio.Get_z1()==(*it).Get_z1() )	

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
				case  7:
				{
					if (Espacio.Get_x2()==(*it).Get_x2() &&
						Espacio.Get_y1()==(*it).Get_y1() &&
						Espacio.Get_z2()==(*it).Get_z2() )	

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
					if (Espacio.Get_x2()==(*it).Get_x2() &&
						Espacio.Get_y2()==(*it).Get_y2() &&
						Espacio.Get_z2()==(*it).Get_z2() )
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
			if (m_juntar_spaces == true)
				primero = false;
			if (m_full_supported == false)
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
						InsertarConfiguracaoOrden(*it, m_Configuracaos);
						/*m_Configuracaos.push_back((*it));*/
						it = lista.erase(it);
						fin = true;
					}
					else
						++it;
			}
			else
			{
				if (Espacio.Get_x2() >= (*it).Get_x2() &&
					Espacio.Get_y2() >= (*it).Get_y2() &&
					Espacio.Get_z2() >= (*it).Get_z2() &&
					Espacio.Get_x1() <= (*it).Get_x1() &&
					Espacio.Get_y1() <= (*it).Get_y1() &&
					Espacio.Get_z1() <= (*it).Get_z1())
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

}
//void CONTAINER::ColocarBloqueEntero(std::vector<int> &blo_pos, std::list<CONFIGURACAO> &lista)
//{
//	int idblo = blo_pos[0];
//	int pos = blo_pos[1];
//	std::list<CONFIGURACAO>::iterator it, itfin = lista.end();
//	for (it = lista.begin(); it != itfin;) //Borro todas las piezas del bloque porque lo meteré entero luego
//	{
//		if (pos == (*it).Get_blo_pos()[1])
//			it = lista.erase(it);
//		else
//			++it;
//	}
//}
//Calcula cual es la mejor de las posibles configuracao que tiene cada posible 
//rotacion, es decir, hay que pasarle x, y, z y el numero y el devuelve una configuracao
void CONFIGURACAO::MejorColumnaDeUnaPieza(SPACE& Espacio, PIECE& Pieza)
{
	if (Pieza.Get_Rz() == true)
	{
		CompararConColumnas(1, Espacio, Pieza.Get_x(), Pieza.Get_y(), Pieza.Get_z(), Pieza.Get_Id(), Pieza.Get_q() - Pieza.Get_Num());
		CompararConColumnas(2, Espacio, Pieza.Get_y(), Pieza.Get_x(), Pieza.Get_z(), Pieza.Get_Id(), Pieza.Get_q() - Pieza.Get_Num());
	}
	if (Pieza.Get_Ry() == true)
	{
		CompararConColumnas(3, Espacio, Pieza.Get_x(), Pieza.Get_z(), Pieza.Get_y(), Pieza.Get_Id(), Pieza.Get_q() - Pieza.Get_Num());
		CompararConColumnas(4, Espacio, Pieza.Get_z(), Pieza.Get_x(), Pieza.Get_y(), Pieza.Get_Id(), Pieza.Get_q() - Pieza.Get_Num());
	}
	if (Pieza.Get_Rx() == true)
	{
		CompararConColumnas(5, Espacio, Pieza.Get_z(), Pieza.Get_y(), Pieza.Get_x(), Pieza.Get_Id(), Pieza.Get_q() - Pieza.Get_Num());
		CompararConColumnas(6, Espacio, Pieza.Get_y(), Pieza.Get_z(), Pieza.Get_x(), Pieza.Get_Id(), Pieza.Get_q() - Pieza.Get_Num());
	}
}
void CONFIGURACAO::MejorColumnaDeUnaPiezaMov(SPACE &Espacio,PIECE &Pieza)
{
	if (Pieza.Get_Rz()==true)
	{
		CompararConColumnas(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()- m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
		CompararConColumnas(2,Espacio,Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()- m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
	}
	if (Pieza.Get_Ry()==true)
	{
		CompararConColumnas(3,Espacio,Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()- m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
		CompararConColumnas(4,Espacio,Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()- m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
	}
	if (Pieza.Get_Rx()==true)
	{
		CompararConColumnas(5,Espacio,Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()- m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
		CompararConColumnas(6,Espacio,Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()- m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
	}
}
void CONFIGURACAO::MejorPieza(SPACE &Espacio,PIECE &Pieza)
{
	CompararConCapas(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
}
void CONFIGURACAO::MejorPiezaMov(SPACE &Espacio,PIECE &Pieza)
{
	CompararConCapas(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
}

void CONFIGURACAO::MejorCapaDeUnaPieza(SPACE &Espacio,PIECE &Pieza)
{
	if (Pieza.Get_Rz()==true)
	{
		CompararConCapas(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConCapas(2,Espacio,Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
	if (Pieza.Get_Ry()==true)
	{
		CompararConCapas(3,Espacio,Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConCapas(4,Espacio,Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
	if (Pieza.Get_Rx()==true)
	{
		CompararConCapas(5,Espacio,Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConCapas(6,Espacio,Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
}

void CONFIGURACAO::MejorCapaDeUnaPiezaMov(SPACE &Espacio,PIECE &Pieza)
{
	if (Pieza.Get_Rz()==true)
	{
		CompararConCapas(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
		CompararConCapas(2,Espacio,Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
	}
	if (Pieza.Get_Ry()==true)
	{
		CompararConCapas(3,Espacio,Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()-m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
		CompararConCapas(4,Espacio,Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()-m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
	}
	if (Pieza.Get_Rx()==true)
	{
		CompararConCapas(5,Espacio,Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()-m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
		CompararConCapas(6,Espacio,Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()-m_Container->GetPiecesTabu()[Pieza.Get_Id()]);
	}
	int kk = 9;
}
void CONFIGURACAO::MejorBloqueDeUnaPieza(SPACE &Espacio,PIECE &Pieza)
{
	if (Pieza.Get_Rz()==true)
	{
		CompararConBloques(1,Espacio,Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConBloques(2,Espacio,Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
	if (Pieza.Get_Ry()==true)
	{
		CompararConBloques(3,Espacio,Pieza.Get_x(),Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConBloques(4,Espacio,Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_y(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
	if (Pieza.Get_Rx()==true)
	{
		CompararConBloques(5,Espacio,Pieza.Get_z(),Pieza.Get_y(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
		CompararConBloques(6,Espacio,Pieza.Get_y(),Pieza.Get_z(),Pieza.Get_x(),Pieza.Get_Id(),Pieza.Get_q()-Pieza.Get_Num());
	}
	int kk = 9;
}


//Esta funcion puede generar columnas 

void CONFIGURACAO::CompararConColumnas(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas)
{
	//La pieza no cabe
	if (!(Espacio.Get_dx()>=x &&
		Espacio.Get_dy()>=y &&
		Espacio.Get_dz()>=z))
		return;
	int Caso=1,numActual=1;
	//Tres posibles casos
	int Eje_x,Eje_y,Eje_z;
	for (Caso=1;Caso<=3;Caso++)
	{
		Eje_x=min(Espacio.Get_dx()/x,piezas_maximas);
		Eje_y=min(Espacio.Get_dy()/y,piezas_maximas);
		Eje_z=min(Espacio.Get_dz()/z,piezas_maximas);
		//Para que si solo hay uno no haga ninguno mais
		if (Caso>1 && Eje_x==1 && Eje_y==1 && Eje_z==1 )
			break;
		switch (Caso)
		{
			case 1:
				{
					Eje_y=1;
					Eje_z=1;
					numActual=Eje_x;
					break;
				}
			case 2:
				{
					if (Eje_y==1) continue;
					Eje_x=1;
					Eje_z=1;
					//en  y
					numActual=Eje_y;
					break;
				}
			// en z
			case 3:
				{
					if (Eje_z==1) continue;
					Eje_x=1;
					Eje_y=1;
					numActual=Eje_z;
					break;

				}
		}
		//Dimensiones de la pieza las naturales
		//en x, las demas son unas por tanto esta configuracao
		//Tengo que poner eje, que ya esta puesto por el espacio

		ORIG OrigActual(Espacio.Get_dx()-Eje_x*x,Espacio.Get_dy()-Eje_y*y,Espacio.Get_dz()-Eje_z*z);
		int Vol=Eje_x*x*Eje_y*y*Eje_z*z;
		//Para el constructivo 
		if (m_Container->Get_Aleatorizado() == false)
		{
			if (m_Container->Get_Full_Supported() == false)
			{
				if (Mejor_DistA_Que_DistB_Configuracaos(m_set_distancias, m_num, OrigActual, numActual, Vol) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}
			else
			{
				if (Mejor_DistA_Que_DistB_FullSupported(m_set_distancias, m_num, OrigActual, numActual, Vol, Eje_x*x, Eje_y*y, Eje_z*z) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}

		}
		//Para hacer un constructivo aleatorizado
		//La diferencia es que aqui tengo que tener una lista que es la que me controla cuantos 
		//pueden caber 
		else
		{
			//Tengo que ver si puedo o no meterla en la lista 
			//En la configuracion que tengo es la pero posible

			//Esta funcion inserta esta en la RCL
			//y a su vez deja esta igual al minimo
			//FALTA
			m_set_distancias=OrigActual;
			CambiarConfiguracao(numActual, Eje_x,Eje_y,Eje_z,x, y, z, Id,tipo, Espacio);
			InsertarOrdenadaRCL(*this);
			std::list <CONFIGURACAO> ::iterator it;
			m_set_distancias=(*m_Container->Get_ListaRCL().begin()).Get_Distancia();
			m_num=(*m_Container->Get_ListaRCL().begin()).Get_Num();
		}
	}
}
void CONFIGURACAO::CompararConColumnasMov(std::list<CONFIGURACAO> *lista, short int tipo, SPACE& Espacio, int x, int y, int z, int Id, int piezas_maximas)
{
	//La pieza no cabe
	if (!(Espacio.Get_dx() >= x &&
		Espacio.Get_dy() >= y &&
		Espacio.Get_dz() >= z))
		return;
	int Caso = 1, numActual = 1;
	double VCS = 0;
	double VCS_Temp = 0;
	bool primero = true;
	int x1=0, y1=0, z1=0;
	//Tres posibles casos
	int Eje_x, Eje_y, Eje_z;
	for (Caso = 1; Caso <= 3; Caso++)
	{
		Eje_x = min(Espacio.Get_dx() / x, piezas_maximas);
		Eje_y = min(Espacio.Get_dy() / y, piezas_maximas);
		Eje_z = min(Espacio.Get_dz() / z, piezas_maximas);
		//Para que si solo hay uno no haga ninguno mais
		if (Caso > 1 && Eje_x == 1 && Eje_y == 1 && Eje_z == 1)
			break;
		switch (Caso)
		{
		case 1:
		{
			Eje_y = 1;
			Eje_z = 1;
			numActual = Eje_x;
			break;
		}
		case 2:
		{
			if (Eje_y == 1) continue;
			Eje_x = 1;
			Eje_z = 1;
			//en  y
			numActual = Eje_y;
			break;
		}
		// en z
		case 3:
		{
			if (Eje_z == 1) continue;
			Eje_x = 1;
			Eje_y = 1;
			numActual = Eje_z;
			break;

		}
		}
		//Dimensiones de la pieza las naturales
		//en x, las demas son unas por tanto esta configuracao
		//Tengo que poner eje, que ya esta puesto por el espacio

		ORIG OrigActual(Espacio.Get_dx() - Eje_x * x, Espacio.Get_dy() - Eje_y * y, Espacio.Get_dz() - Eje_z * z);
		int Vol = Eje_x * x * Eje_y * y * Eje_z * z;
		//Para el constructivo 
		if (m_Container->Get_Aleatorizado() == false && m_Container->Get_VCS() == false)
		{
			if (m_Container->Get_Full_Supported() == false)
			{
				if (Mejor_DistA_Que_DistB_Configuracaos(m_set_distancias, m_num, OrigActual, numActual, Vol) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}
			else
			{
				if (Mejor_DistA_Que_DistB_FullSupported(m_set_distancias, m_num, OrigActual, numActual, Vol, Eje_x * x, Eje_y * y, Eje_z * z) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}

		}
		//Para hacer un constructivo aleatorizado
		//La diferencia es que aqui tengo que tener una lista que es la que me controla cuantos 
		//pueden caber 
		else if (m_Container->Get_VCS() == false)
		{
			//Tengo que ver si puedo o no meterla en la lista 
			//En la configuracion que tengo es la pero posible

			//Esta funcion inserta esta en la RCL
			//y a su vez deja esta igual al minimo
			//FALTA
			m_set_distancias = OrigActual;
			CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
			InsertarOrdenadaRCL(*this);
			std::list <CONFIGURACAO> ::iterator it;
			m_set_distancias = (*m_Container->Get_ListaRCL().begin()).Get_Distancia();
			m_num = (*m_Container->Get_ListaRCL().begin()).Get_Num();
		}
		if (m_Container->Get_VCS() == true)
		{
			int dx = Eje_x * x;
			int dy = Eje_y * y;
			int dz = Eje_z * z;
			switch (Espacio.Get_origen_distancia())
			{
			case 1: //(0,0,0)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z1();
				break;
			case 2: //(0,Y,0)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y2() - Eje_y * y;
				z1 = Espacio.Get_z1();
				break;
			case 3: //(0,0,Z)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z2() - Eje_z * z;
				break;
			case 4: //(0,Y,Z)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y2() - Eje_y * y;
				z1 = Espacio.Get_z2() - Eje_z * z;
				break;
			case 5: //(X,0,0)
				x1 = Espacio.Get_x2() - Eje_x * x;
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z1();
				break;
			case 6: //(X,Y,0)
				x1 = Espacio.Get_x2() - Eje_x * x;
				y1 = Espacio.Get_y2() - Eje_y * y;
				z1 = Espacio.Get_z1();
				break;
			case 7: //(X,0,Z)
				x1 = Espacio.Get_x2() - Eje_x * x;
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z2() - Eje_z * z;
				break;
			case 8: //(X,Y,Z)
				x1 = Espacio.Get_x2() - Eje_x * x;
				y1 = Espacio.Get_y2() - Eje_y * y;
				z1 = Espacio.Get_z2() - Eje_z * z;
				break;
			}
			if (primero == true)
			{
				VCS = VCS_ConfiguracaoMov(lista, numActual, dx, dy, dz, Vol, Espacio, x1, y1, z1);
				m_set_distancias = OrigActual;
				CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
			}
			else
			{
				VCS_Temp = VCS_ConfiguracaoMov(lista, numActual, dx, dy, dz, Vol, Espacio, x1, y1, z1);
				if (VCS < VCS_Temp)
				{
					VCS = VCS_Temp;
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}
			primero = false;
		}
	}
}

void CONFIGURACAO::CompararConCapas(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas)
{
	//La pieza no cabe
	if (!(Espacio.Get_dx()>=x &&
		Espacio.Get_dy()>=y &&
		Espacio.Get_dz()>=z))
		return;
	int Caso=1,numActual=1;
	int x1, y1, z1;
//	if (piezas_maximas>1)
//		int kk=9;
//ç	std::multiset< short int > setActual;
	//Tres posibles casos
	int Eje_x,Eje_y,Eje_z;
	for (Caso=1;Caso<=6;Caso++)
	{
//		if (m_Container->Get_objetivo_vol()==false)	setActual.clear();
		Eje_x=min(Espacio.Get_dx()/x,piezas_maximas);
		Eje_y=min(Espacio.Get_dy()/y,piezas_maximas);
		Eje_z=min(Espacio.Get_dz()/z,piezas_maximas);
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
					Eje_y=1;
					Eje_z=min(Eje_z, (piezas_maximas/Eje_x));
					//Si no puedo colocar mas que una ya lo he hecho en el anterior
					if (Eje_z==1) continue;
					numActual=Eje_x*Eje_y;
					break;
				}
			case 3:
				{
					if (Eje_y==1) continue;
					Eje_x=min(Eje_x, (piezas_maximas/Eje_y));
					if (Eje_x==1) continue;
					Eje_z=1;
					//en  y
					numActual=Eje_y*Eje_x;
					break;
				}
			case 4:
				{
					if (Eje_y==1) continue;
					Eje_x=1;
					Eje_z=min(Eje_z, (piezas_maximas/Eje_y));
					if (Eje_z==1) continue;
					//en  y
					numActual=Eje_y*Eje_z;
					break;
				}

			// en z
			case 5:
				{
					if (Eje_z==1) continue;
					Eje_y=1;
					Eje_x=min(Eje_x, (piezas_maximas/Eje_z));
					if (Eje_x==1) continue;

					numActual=Eje_z*Eje_x;
					break;

				}
			case 6:
				{
					if (Eje_z==1) continue;
					Eje_x=1;
					Eje_y=min(Eje_y, (piezas_maximas/Eje_z));
					if (Eje_x==1) continue;
					numActual=Eje_z*Eje_y;
					break;

				}
		}
		//Tengo columnas ahora tengo que hacer caras con esa columna
		//En eje y
		 
		//Dimensiones de la pieza las naturales
		//en x, las demas son unas por tanto esta configuracao
		//Tengo que poner eje, que ya esta puesto por el espacio
		ORIG OrigActual(Espacio.Get_dx() - Eje_x * x, Espacio.Get_dy() - Eje_y * y, Espacio.Get_dz() - Eje_z * z);
		if (m_Container->Get_objetivo_vol()==false)
		{
			Cambiar(OrigActual,Espacio.Get_dx()-Eje_x*x,Espacio.Get_dy()-Eje_y*y,Espacio.Get_dz()-Eje_z*z);
		}
		int Vol=Eje_x*x*Eje_y*y*Eje_z*z;
		//Para el constructivo 
		if (m_Container->Get_Aleatorizado()==false)
		{
			if (m_Container->Get_Full_Supported() == false)
			{
				if (Mejor_DistA_Que_DistB_Configuracaos(m_set_distancias, m_num, OrigActual, numActual, Vol) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}
			else
			{
				if (Mejor_DistA_Que_DistB_FullSupported(m_set_distancias, m_num, OrigActual, numActual, Vol, Eje_x*x, Eje_y*y, Eje_z*z) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					if (m_set_distancias.GetPrimero() < 0 || m_set_distancias.GetSegundo() < 0 || m_set_distancias.GetTercero() < 0)
						int kk = 9;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}

		}
		//Para hacer un constructivo aleatorizado
		//La diferencia es que aqui tengo que tener una lista que es la que me controla cuantos 
		//pueden caber 
		else
		{
			//Tengo que ver si puedo o no meterla en la lista 
			//En la configuracion que tengo es la pero posible

			//Esta funcion inserta esta en la RCL
			//y a su vez deja esta igual al minimo
			//FALTA
			if (m_Container->Get_objetivo_vol()==false)
			{

//				m_set_distancias.clear();
				m_set_distancias=OrigActual;
			}
			CambiarConfiguracao(numActual, Eje_x,Eje_y,Eje_z,x, y, z, Id,tipo, Espacio);
			InsertarOrdenadaRCL(*this);
			if (m_Container->Get_objetivo_vol()==false)
			{

				m_set_distancias=(*m_Container->Get_ListaRCL().begin()).Get_Distancia();
			}
			m_num=(*m_Container->Get_ListaRCL().begin()).Get_Num();

		}
	}
}
void CONFIGURACAO::CompararConCapasMov(std::list<CONFIGURACAO> *lista, short int tipo, SPACE& Espacio, int x, int y, int z, int Id, int piezas_maximas)
{
	//La pieza no cabe
	if (!(Espacio.Get_dx() >= x &&
		Espacio.Get_dy() >= y &&
		Espacio.Get_dz() >= z))
		return;
	int Caso = 1, numActual = 1;
	double VCS = 0;
	double VCS_Temp = 0;
	bool primero = true;
	int x1=0, y1=0, z1=0;
	//	if (piezas_maximas>1)
	//		int kk=9;
	//ç	std::multiset< short int > setActual;
		//Tres posibles casos
	int Eje_x, Eje_y, Eje_z;
	for (Caso = 1; Caso <= 6; Caso++)
	{
		//		if (m_Container->Get_objetivo_vol()==false)	setActual.clear();
		Eje_x = min(Espacio.Get_dx() / x, piezas_maximas);
		Eje_y = min(Espacio.Get_dy() / y, piezas_maximas);
		Eje_z = min(Espacio.Get_dz() / z, piezas_maximas);
		//Para que si solo hay uno no haga ninguno mais
		if (Caso > 1 && Eje_x == 1 && Eje_y == 1 && Eje_z == 1)
			break;
		switch (Caso)
		{
		case 1:
		{
			Eje_z = 1;
			Eje_y = min(Eje_y, (piezas_maximas / Eje_x));
			numActual = Eje_x * Eje_y;
			break;
		}
		case 2:
		{
			Eje_y = 1;
			Eje_z = min(Eje_z, (piezas_maximas / Eje_x));
			//Si no puedo colocar mas que una ya lo he hecho en el anterior
			if (Eje_z == 1) continue;
			numActual = Eje_x * Eje_y;
			break;
		}
		case 3:
		{
			if (Eje_y == 1) continue;
			Eje_x = min(Eje_x, (piezas_maximas / Eje_y));
			if (Eje_x == 1) continue;
			Eje_z = 1;
			//en  y
			numActual = Eje_y * Eje_x;
			break;
		}
		case 4:
		{
			if (Eje_y == 1) continue;
			Eje_x = 1;
			Eje_z = min(Eje_z, (piezas_maximas / Eje_y));
			if (Eje_z == 1) continue;
			//en  y
			numActual = Eje_y * Eje_z;
			break;
		}

		// en z
		case 5:
		{
			if (Eje_z == 1) continue;
			Eje_y = 1;
			Eje_x = min(Eje_x, (piezas_maximas / Eje_z));
			if (Eje_x == 1) continue;

			numActual = Eje_z * Eje_x;
			break;

		}
		case 6:
		{
			if (Eje_z == 1) continue;
			Eje_x = 1;
			Eje_y = min(Eje_y, (piezas_maximas / Eje_z));
			if (Eje_x == 1) continue;
			numActual = Eje_z * Eje_y;
			break;

		}
		}
		//Tengo columnas ahora tengo que hacer caras con esa columna
		//En eje y

		//Dimensiones de la pieza las naturales
		//en x, las demas son unas por tanto esta configuracao
		//Tengo que poner eje, que ya esta puesto por el espacio
		ORIG OrigActual(Espacio.Get_dx() - Eje_x * x, Espacio.Get_dy() - Eje_y * y, Espacio.Get_dz() - Eje_z * z);
		if (m_Container->Get_objetivo_vol() == false && m_Container->Get_VCS() == false)
		{
			Cambiar(OrigActual, Espacio.Get_dx() - Eje_x * x, Espacio.Get_dy() - Eje_y * y, Espacio.Get_dz() - Eje_z * z);
		}
		int Vol = Eje_x * x * Eje_y * y * Eje_z * z;
		//Para el constructivo 
		if (m_Container->Get_Aleatorizado() == false && m_Container->Get_VCS() == false)
		{
			if (m_Container->Get_Full_Supported() == false)
			{
				if (Mejor_DistA_Que_DistB_Configuracaos(m_set_distancias, m_num, OrigActual, numActual, Vol) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}
			else
			{
				if (Mejor_DistA_Que_DistB_FullSupported(m_set_distancias, m_num, OrigActual, numActual, Vol, Eje_x * x, Eje_y * y, Eje_z * z) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					if (m_set_distancias.GetPrimero() < 0 || m_set_distancias.GetSegundo() < 0 || m_set_distancias.GetTercero() < 0)
						int kk = 9;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}

		}
		//Para hacer un constructivo aleatorizado
		//La diferencia es que aqui tengo que tener una lista que es la que me controla cuantos 
		//pueden caber 
		else if (m_Container->Get_VCS() == false)
		{
			//Tengo que ver si puedo o no meterla en la lista 
			//En la configuracion que tengo es la pero posible

			//Esta funcion inserta esta en la RCL
			//y a su vez deja esta igual al minimo
			//FALTA
			if (m_Container->Get_objetivo_vol() == false)
			{

				//				m_set_distancias.clear();
				m_set_distancias = OrigActual;
			}
			CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
			InsertarOrdenadaRCL(*this);
			if (m_Container->Get_objetivo_vol() == false)
			{

				m_set_distancias = (*m_Container->Get_ListaRCL().begin()).Get_Distancia();
			}
			m_num = (*m_Container->Get_ListaRCL().begin()).Get_Num();

		}
		if (m_Container->Get_VCS() == true)
		{
			int dx = Eje_x * x;
			int dy = Eje_y * y;
			int dz = Eje_z * z;
			switch (Espacio.Get_origen_distancia())
			{
			case 1: //(0,0,0)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z1();
				break;
			case 2: //(0,Y,0)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y2() - Eje_y * y;
				z1 = Espacio.Get_z1();
				break;
			case 3: //(0,0,Z)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z2() - Eje_z * z;
				break;
			case 4: //(0,Y,Z)
				x1 = Espacio.Get_x1();
				y1 = Espacio.Get_y2() - Eje_y * y;
				z1 = Espacio.Get_z2() - Eje_z * z;
				break;
			case 5: //(X,0,0)
				x1 = Espacio.Get_x2() - Eje_x * x;
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z1();
				break;
			case 6: //(X,Y,0)
				x1 = Espacio.Get_x2() - Eje_x * x;
				y1 = Espacio.Get_y2() - Eje_y * y;
				z1 = Espacio.Get_z1();
				break;
			case 7: //(X,0,Z)
				x1 = Espacio.Get_x2() - Eje_x * x;
				y1 = Espacio.Get_y1();
				z1 = Espacio.Get_z2() - Eje_z * z;
				break;
			case 8: //(X,Y,Z)
				x1 = Espacio.Get_x2() - Eje_x * x;
				y1 = Espacio.Get_y2() - Eje_y * y;
				z1 = Espacio.Get_z2() - Eje_z * z;
				break;
			}
			if (primero == true)
			{
				VCS = VCS_ConfiguracaoMov(lista, numActual, dx, dy, dz, Vol, Espacio, x1, y1, z1);
				m_set_distancias = OrigActual;
				CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
			}
			else
			{
				VCS_Temp = VCS_ConfiguracaoMov(lista, numActual, dx, dy, dz, Vol, Espacio, x1, y1, z1);
				if (VCS < VCS_Temp)
				{
					VCS = VCS_Temp;
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}
			primero = false;
		}
	}
}

void CONFIGURACAO::CompararConBloques(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas)
{
	//La pieza no cabe
	if (!(Espacio.Get_dx()>=x &&
		Espacio.Get_dy()>=y &&
		Espacio.Get_dz()>=z))
		return;
	int Caso=1,numActual=1;
//ç	std::multiset< short int > setActual;
	//Tres posibles casos
	int Eje_x,Eje_y,Eje_z;
	for (Caso=1;Caso<=6;Caso++)
	{
//		if (m_Container->Get_objetivo_vol()==false)	setActual.clear();
		Eje_x=min(Espacio.Get_dx()/x,piezas_maximas);
		Eje_y=min(Espacio.Get_dy()/y,piezas_maximas);
		Eje_z=min(Espacio.Get_dz()/z,piezas_maximas);
		//Para que si solo hay uno no haga ninguno mais
		if (Caso>1 && Eje_x==1 && Eje_y==1 && Eje_z==1 )
			break;
		switch (Caso)
		{
			//Eje XYz
			case 1:
				{
					
					Eje_y=min(Eje_y, (piezas_maximas/Eje_x));
					Eje_z=min(Eje_z, ((piezas_maximas/Eje_x)/Eje_y));
					numActual=Eje_x*Eje_y*Eje_z;
					break;
				}
				//eje xzy
			case 2:
				{
					Eje_z=min(Eje_z, (piezas_maximas/Eje_x));
					Eje_y=min(Eje_y, ((piezas_maximas/Eje_x)/Eje_z));
					numActual=Eje_x*Eje_y*Eje_z;
					//Si no puedo colocar mas que una ya lo he hecho en el anterior
					break;
				}//eje yxz
			case 3:
				{
					if (Eje_y==1) continue;
					Eje_x=min(Eje_x, (piezas_maximas/Eje_y));
					Eje_z=min(Eje_z, ((piezas_maximas/Eje_y)/Eje_x));

					if (Eje_x==1) continue;
					//en  y
					numActual=Eje_y*Eje_x*Eje_z;
					break;
				}
			case 4:
				{//eje yzx
					if (Eje_y==1) continue;
					Eje_z=min(Eje_z, (piezas_maximas/Eje_y));
					Eje_x=min(Eje_x, ((piezas_maximas/Eje_y)/Eje_z));
					if (Eje_z==1) continue;
					//en  y
					numActual=Eje_y*Eje_z*Eje_x;
					break;
				}

			// en z
			case 5: 
				{//eje zxy
					if (Eje_z==1) continue;
					Eje_x=min(Eje_x, (piezas_maximas/Eje_z));
					Eje_y=min(Eje_y, ((piezas_maximas/Eje_z)/Eje_x));

					if (Eje_x==1) continue;

					numActual=Eje_z*Eje_x*Eje_y;
					break;

				}
			case 6:
				{
					if (Eje_z==1) continue;
					Eje_y=min(Eje_y, (piezas_maximas/Eje_z));
					Eje_x=min(Eje_x, ((piezas_maximas/Eje_z)/Eje_y));
					if (Eje_x==1) continue;
					numActual=Eje_z*Eje_y*Eje_x;
					break;

				}
		}
		//Tengo columnas ahora tengo que hacer caras con esa columna
		//En eje y
		 
		//Dimensiones de la pieza las naturales
		//en x, las demas son unas por tanto esta configuracao
		//Tengo que poner eje, que ya esta puesto por el espacio
		ORIG OrigActual(Espacio.Get_dx() - Eje_x * x, Espacio.Get_dy() - Eje_y * y, Espacio.Get_dz() - Eje_z * z);
		if (m_Container->Get_objetivo_vol()==false)	
		{
			Cambiar(OrigActual,Espacio.Get_dx()-Eje_x*x,Espacio.Get_dy()-Eje_y*y,Espacio.Get_dz()-Eje_z*z);
		}
		int Vol=Eje_x*x*Eje_y*y*Eje_z*z;
		//Para el constructivo 
		if (m_Container->Get_Aleatorizado() == false)
		{
			if (m_Container->Get_Full_Supported() == false)
			{
				if (Mejor_DistA_Que_DistB_Configuracaos(m_set_distancias, m_num, OrigActual, numActual, Vol) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}
			else
			{
				if (Mejor_DistA_Que_DistB_FullSupported(m_set_distancias, m_num, OrigActual, numActual, Vol, Eje_x*x, Eje_y*y, Eje_z*z) == false)
				{
					//				m_set_distancias.clear();
					m_set_distancias = OrigActual;
					CambiarConfiguracao(numActual, Eje_x, Eje_y, Eje_z, x, y, z, Id, tipo, Espacio);
				}
			}

		}
		//Para hacer un constructivo aleatorizado
		//La diferencia es que aqui tengo que tener una lista que es la que me controla cuantos 
		//pueden caber 
		else
		{
			//Tengo que ver si puedo o no meterla en la lista 
			//En la configuracion que tengo es la pero posible

			//Esta funcion inserta esta en la RCL
			//y a su vez deja esta igual al minimo
			//FALTA
			if (m_Container->Get_objetivo_vol()==false)
			{

//				m_set_distancias.clear();
				m_set_distancias=OrigActual;
			}
			CambiarConfiguracao(numActual, Eje_x,Eje_y,Eje_z,x, y, z, Id,tipo, Espacio);
			InsertarOrdenadaRCL(*this);
			if (m_Container->Get_objetivo_vol()==false)
			{

				m_set_distancias=(*m_Container->Get_ListaRCL().begin()).Get_Distancia();
			}
			m_num=(*m_Container->Get_ListaRCL().begin()).Get_Num();

		}
	}
}
//Repasar funcion 
//Esta funcion puede generar columnas 
///
//???????????
/*
void CONFIGURACAO::CompararConCapasMejorada(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas)
{
	//La pieza no cabe
	if (!(Espacio.Get_dx()>=x &&
		Espacio.Get_dy()>=y &&
		Espacio.Get_dz()>=z))
		return;

	int Caso=1,numActual=1;
	//Tres posibles casos
	int Eje_x_Max,Eje_y_Max,Eje_z_Max,Eje_x,Eje_y,Eje_z;
	for (Caso=1;Caso<=6;Caso++)
	{
//		if (m_Container->Get_objetivo_vol()==false)	setActual.clear();
		Eje_x_Max=min(Espacio.Get_dx()/x,piezas_maximas);
		Eje_y_Max=min(Espacio.Get_dy()/y,piezas_maximas);
		Eje_z_Max=min(Espacio.Get_dz()/z,piezas_maximas);
		//Para que si solo hay uno no haga ninguno mais
		if (Caso>1 && Eje_x_Max==1 && Eje_y_Max==1 && Eje_z_Max==1 )
			break;
		switch (Caso)
		{
			case 1:
				{
					Eje_x=Eje_x_Max;
					Eje_z=1;
					Eje_y=min(Eje_y_Max, (piezas_maximas/Eje_x_Max));
					numActual=Eje_x*Eje_y;
					break;
				}
			case 2:
				{
					Eje_x=Eje_x_Max;
					Eje_y=1;
					Eje_z=min(Eje_z_Max, (piezas_maximas/Eje_x_Max));
					//Si no puedo colocar mas que una ya lo he hecho en el anterior
					if (Eje_z==1) continue;
					numActual=Eje_x*Eje_y;
					break;
				}
			case 3:
				{
					Eje_y=Eje_y_Max;
					if (Eje_y==1) continue;
					Eje_x=min(Eje_x_Max, (piezas_maximas/Eje_y_Max));
					if (Eje_x==1) continue;
					if (Eje_x==Eje_x_Max) 
						continue;
					Eje_z=1;
					//en  y
					numActual=Eje_y*Eje_x;
					break;
				}
			case 4:
				{
					Eje_y=Eje_y_Max;

					if (Eje_y==1) continue;
					Eje_x=1;
					Eje_z=min(Eje_z_Max, (piezas_maximas/Eje_y_Max));
					if (Eje_z==1) continue;
					//en  y
					numActual=Eje_y*Eje_z;
					break;
				}

			// en z
			case 5:
				{
					Eje_z=Eje_z_Max;

					if (Eje_z==1) continue;
					Eje_y=1;
					Eje_x=min(Eje_x_Max, (piezas_maximas/Eje_z_Max));
					if (Eje_x==Eje_x_Max) 
						continue;
					if (Eje_x==1) continue;

					numActual=Eje_z*Eje_x;
					break;

				}
			case 6:
				{
					Eje_z=Eje_z_Max;

					if (Eje_z==1) continue;
					Eje_x=1;
					Eje_y=min(Eje_y_Max, (piezas_maximas/Eje_z_Max));
					if (Eje_y==Eje_y_Max) 
						continue;

					if (Eje_y==1) continue;
					numActual=Eje_z*Eje_y;
					break;

				}
		}
		//Tengo columnas ahora tengo que hacer caras con esa columna
		//En eje y
		 
		//Dimensiones de la pieza las naturales
		//en x, las demas son unas por tanto esta configuracao
		//Tengo que poner eje, que ya esta puesto por el espacio
		ORIG OrigActual;
		if (m_Container->Get_objetivo_vol()==false)	
		{
			Cambiar(OrigActual,Espacio.Get_dx()-Eje_x*x,Espacio.Get_dy()-Eje_y*y,Espacio.Get_dz()-Eje_z*z);
		}
		int Vol=Eje_x*x*Eje_y*y*Eje_z*z;
		//Para el constructivo 
		if (m_Container->Get_Aleatorizado()==false)
		{
			if (Mejor_DistA_Que_DistB_Configuracaos(m_set_distancias,m_num,OrigActual,numActual,Vol)==false)
			{
//				m_set_distancias.clear();
				m_set_distancias=OrigActual;
				CambiarConfiguracao(numActual, Eje_x,Eje_y,Eje_z,x, y, z, Id,tipo, Espacio);
			}
		}
		//Para hacer un constructivo aleatorizado
		//La diferencia es que aqui tengo que tener una lista que es la que me controla cuantos 
		//pueden caber 
		else
		{
			//Tengo que ver si puedo o no meterla en la lista 
			//En la configuracion que tengo es la pero posible

			//Esta funcion inserta esta en la RCL
			//y a su vez deja esta igual al minimo
			//FALTA
			if (m_Container->Get_objetivo_vol()==false)
			{

//				m_set_distancias.clear();
				m_set_distancias=OrigActual;
			}
			CambiarConfiguracao(numActual, Eje_x,Eje_y,Eje_z,x, y, z, Id,tipo, Espacio);
			InsertarOrdenadaRCL(*this);
			if (m_Container->Get_objetivo_vol()==false)
			{

				m_set_distancias=(*m_Container->Get_ListaRCL().begin()).Get_Distancia();
			}
			m_num=(*m_Container->Get_ListaRCL().begin()).Get_Num();

		}
	}
}
*/
void CONFIGURACAO::InsertarOrdenadaRCL(CONFIGURACAO &Actual)
{
	//Por si solamente hay uno
	if (m_Container->Get_ListaRCL().size()==0)
	{
		m_Container->Get_ListaRCL().push_back(Actual);
		return;
	}
	//Si tengo mas de los que necesito como voy a meter uno
	//Si no hay ninguno más pequeño al final
	std::list< CONFIGURACAO > ::iterator itl;
	for (itl=m_Container->Get_ListaRCL().begin();itl!=m_Container->Get_ListaRCL().end();itl++)
	{
		if (m_Container->Get_objetivo_vol() == true)
		{
			if ((*itl).Get_Volumen() > Get_Volumen())
			{

				m_Container->Get_ListaRCL().insert(itl, Actual);
				if (m_Container->Get_ListaRCL().size() > m_Container->Get_TamRCL())
					m_Container->Get_ListaRCL().pop_front();
				return;
			}
		}
		else
		{
			if (Mejor_DistA_Que_DistB_FullSupported(m_set_distancias, m_num, (*itl).Get_Distancia(), (*itl).Get_Num(), (*itl).Get_Volumen(), (*itl).Get_x2() - (*itl).Get_x1(), (*itl).Get_y2() - (*itl).Get_y1(), (*itl).Get_z2() - (*itl).Get_z1()) == false)
			{

				m_Container->Get_ListaRCL().insert(itl, Actual);
				if (m_Container->Get_ListaRCL().size() > m_Container->Get_TamRCL())
					m_Container->Get_ListaRCL().pop_front();
				return;
			}
		}
	}
	//Si es mas grande que todos los demas
	m_Container->Get_ListaRCL().push_back(Actual);
	if (m_Container->Get_ListaRCL().size()>m_Container->Get_TamRCL())
		m_Container->Get_ListaRCL().pop_front();

}
//Esta funcion me cambia la configuracao de la columna o bloque que haya elegido
//Esta funcion esta preparada para si queremos meter mas de una columna en el bloque
//ahora tendríamos tantas columnas como filas en el bloque
void CONFIGURACAO::CambiarConfiguracao(int numpiezas, int ca,int cb, int cc, int a,int b,int c, int id, short int tipo_rota, SPACE &Espacio)
{
//	short int tipo=Espacio.Get_origen_distancia();
	m_origen_distancia=Espacio.Get_origen_distancia();
	m_Id=id;
	m_tipo=tipo_rota;
	m_dx=ca;
	m_dy=cb;
	m_dz=cc;
	m_num=ca*cb*cc;
	m_Volumen=a*ca*b*cb*c*cc;
	switch (Espacio.Get_origen_distancia())
	{
		case 1:
		{
			m_x1=Espacio.Get_x1(); m_x2=m_x1+ca*a;
			m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
			m_z1=Espacio.Get_z1(); m_z2=m_z1+cc*c;
		}
		break;
		case  2:
		{
			m_x1=Espacio.Get_x1(); m_x2=m_x1+ca*a;
			m_y2=Espacio.Get_y2(); m_y1=m_y2-cb*b;
			m_z1=Espacio.Get_z1(); m_z2=m_z1+cc*c;
		}
		break;
		case 3:
		{
			m_x1=Espacio.Get_x1(); m_x2=m_x1+ca*a;
			m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
			m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
		}
		break;
		case  4:
		{
			m_x1=Espacio.Get_x1(); m_x2=m_x1+ca*a;
			m_y2=Espacio.Get_y2(); m_y1=m_y2-cb*b;
			m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
		}
		break;
		case  5:
		{
			m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
			m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
			m_z1=Espacio.Get_z1(); m_z2=m_z1+cc*c;
		}
		break;
		case  6:
		{
			m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
			m_y2=Espacio.Get_y2(); m_y1=m_y2-cb*b;
			m_z1=Espacio.Get_z1(); m_z2=m_z1+cc*c;
		}
		break;
		case  7:
		{
			m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
			m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
			m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
		}
		break;
		case  8:
		{
			m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
			m_y2=Espacio.Get_y2(); m_y1=m_y2-cb*b;
			m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
		}
		break;

	}
}
//Esta funcion me cambia la configuracao de la columna o bloque que haya elegido
//Esta funcion esta preparada para si queremos meter mas de una columna en el bloque
//ahora tendríamos tantas columnas como filas en el bloque
void CONFIGURACAO::CambiarConfiguracao(int numpiezas, int ca,int cb, int cc, int a,int b,int c, int id, short int tipo_rota)
{
//	short int tipo=Espacio.Get_origen_distancia();
	m_origen_distancia=1;
	m_Id=id;
	m_tipo=tipo_rota;
	m_dx=ca;
	m_dy=cb;
	m_dz=cc;
	m_num=ca*cb*cc;
	m_Volumen=a*ca*b*cb*c*cc;
	m_x1=0; m_x2=m_x1+ca*a;
	m_y1=0; m_y2=m_y1+cb*b;
	m_z1=0; m_z2=m_z1+cc*c;


}
void CONFIGURACAO::PonerMedidas(int dx,int dy, int dz)
{
	m_dx=dx;
	m_dy=dy;
	m_dz=dz;
	m_num=m_dx*m_dy*m_dz;
	
}

double CONTAINER::VCS_Bloque(std::list<CONFIGURACAO> *lista, BLOQUE_ARA &B, SPACE& E, int x, int y, int z)
{
	double C = CS_Bloque(lista, B, x, y, z);
	int lmax = 0;
	int wmax = 0;
	int hmax = 0;
	int difx = E.Get_dx() - B.Get_x();
	int dify = E.Get_dy() - B.Get_y();
	int difz = E.Get_dz() - B.Get_z();
	if (difx >= *setlmax.rbegin())
		lmax = *setlmax.lower_bound(difx);
	if (dify >= *setwmax.rbegin())
		wmax = *setwmax.lower_bound(dify);
	if (difz >= *sethmax.rbegin())
		hmax = *sethmax.lower_bound(difz);
	/*int lmax = 0;
	int wmax = 0;
	int hmax = 0;
	std::set<BLOQUE_ARA*, compareBlocks>::iterator it=m_set_Bloques.begin(), itfin = m_set_Bloques.end();
	for (; it != itfin; it++)
	{
		if ((**it).Get_x() > lmax && (**it).Get_x() <= (E.Get_x2() - E.Get_x1()) - B.Get_x())
			lmax = (**it).Get_x();
		if ((**it).Get_y() > wmax && (**it).Get_y() <= (E.Get_y2() - E.Get_y1()) - B.Get_y())
			wmax = (**it).Get_y();
		if ((**it).Get_z() > hmax && (**it).Get_z() <= (E.Get_z2() - E.Get_z1()) - B.Get_z())
			hmax = (**it).Get_z();
		if (lmax == (E.Get_x2() - E.Get_x1()) - B.Get_x() && wmax == (E.Get_y2() - E.Get_y1()) - B.Get_y() && hmax == (E.Get_z2() - E.Get_z1()) - B.Get_z())
			break;
	}*/
	double Loss=(double)((double)E.Get_Volumen() - (((double)B.Get_x() + lmax) * ((double)B.Get_y() + wmax) * ((double)B.Get_z() + hmax)))/((double)E.Get_Volumen());
	int N=B.Get_Num();

	return (B.Get_volumen_ocupado() * pow(C, (double)alpha) * pow((1 - Loss), (double)beta) * pow((double)N, -gamma));
}

double CONFIGURACAO::VCS_Configuracao(int num, int dx, int dy, int dz, int Vol, SPACE& E, int x, int y, int z)
{
	double C = CS_Configuracao(dx, dy, dz, x, y, z);
	int lmax = 0;
	int wmax = 0;
	int hmax = 0;
	//if (E.Get_dx() - dx >= *(m_Container->Get_setlmax()).rbegin())
	//	int lmax = *(m_Container->Get_setlmax()).lower_bound((E.Get_dx()) - dx);
	//if (E.Get_dy() - dy >= *(m_Container->Get_setwmax()).rbegin())
	//	int wmax = *(m_Container->Get_setwmax()).lower_bound((E.Get_dy()) - dy);
	//if (E.Get_dz() - dz >= *(m_Container->Get_sethmax()).rbegin())
	//	int hmax = *(m_Container->Get_sethmax()).lower_bound((E.Get_dz()) - dz);

	//double Loss = (E.Get_Volumen() - ((dx + lmax) * (dy + wmax) * (dz + hmax))) / (E.Get_Volumen());
	int N = num;

	return (Vol * pow(C, (double)(m_Container->Get_alpha())) /** pow((1 - Loss), (double)(m_Container->Get_beta()))*/ * pow((double)N, -(m_Container->Get_gamma())));
}
double CONFIGURACAO::VCS_ConfiguracaoMov(std::list<CONFIGURACAO> *lista, int num, int dx, int dy, int dz, int Vol, SPACE& E, int x, int y, int z)
{
	double C = CS_ConfiguracaoMov(lista, dx, dy, dz, x, y, z);
	int lmax = 0;
	int wmax = 0;
	int hmax = 0;
	/*if (E.Get_dx() - dx >= *(m_Container->Get_setlmax()).rbegin())
		int lmax = *(m_Container->Get_setlmax()).lower_bound((E.Get_dx()) - dx);
	if (E.Get_dy() - dy >= *(m_Container->Get_setwmax()).rbegin())
		int wmax = *(m_Container->Get_setwmax()).lower_bound((E.Get_dy()) - dy);
	if (E.Get_dz() - dz >= *(m_Container->Get_sethmax()).rbegin())
		int hmax = *(m_Container->Get_sethmax()).lower_bound((E.Get_dz()) - dz);*/

	double Loss = (E.Get_Volumen() - ((dx + lmax) * (dy + wmax) * (dz + hmax))) / (E.Get_Volumen());
	int N = num;

	return (Vol * pow(C, (double)(m_Container->Get_alpha())) * pow((1 - Loss), (double)(m_Container->Get_beta())) * pow((double)N, -(m_Container->Get_gamma())));
}

double CONTAINER::CS_Bloque(std::list<CONFIGURACAO> *lista, BLOQUE_ARA& B, int x, int y, int z)
{
	int l = B.Get_x();
	int w = B.Get_y();
	int h = B.Get_z();
	double s = 0;
	std::list<CONFIGURACAO> Configuracaos_adyacentes = Get_adjacent_blocks(lista, x, y, z, x+l, y+w, z+h);
	std::list<CONFIGURACAO>::iterator it, itfin = Configuracaos_adyacentes.end();
	for (it = Configuracaos_adyacentes.begin(); it != itfin; it++)
		s += surface_in_contact_Bloque(B, *it, x, y, z);
	s += surface_in_contact_with_the_container_Bloque(B, x, y, z);
	return (s / (2 * ((double)w * h + (double)l * h + (double)l * w)));
}
double CONFIGURACAO::CS_Configuracao(int l, int w, int h, int x, int y, int z)
{
	double s = 0;
	std::list<CONFIGURACAO> Configuracaos_adyacentes = Get_adjacent_blocks(x, y, z, x + l, y + w, z + h);
	std::list<CONFIGURACAO>::iterator it, itfin = Configuracaos_adyacentes.end();
	for (it = Configuracaos_adyacentes.begin(); it != itfin; it++)
		s += surface_in_contact_Configuracao(l, w, h, *it, x, y, z);
	s += surface_in_contact_with_the_container_Configuracao(l, w, h, x, y, z);
	return (s / ((double)2 * ((double)w * h + (double)l * h + (double)l * w)));
}
double CONFIGURACAO::CS_ConfiguracaoMov(std::list<CONFIGURACAO> *lista, int l, int w, int h, int x, int y, int z)
{
	double s = 0;
	std::list<CONFIGURACAO> Configuracaos_adyacentes = Get_adjacent_blocksMov(lista, x, y, z, x + l, y + w, z + h);
	std::list<CONFIGURACAO>::iterator it, itfin = Configuracaos_adyacentes.end();
	for (it = Configuracaos_adyacentes.begin(); it != itfin; it++)
		s += surface_in_contact_Configuracao(l, w, h, *it, x, y, z);
	s += surface_in_contact_with_the_container_Configuracao(l, w, h, x, y, z);
	return (s / ((double)2 * ((double)w * h + (double)l * h + (double)l * w)));
}

std::list<CONFIGURACAO> CONTAINER::Get_adjacent_blocks(std::list<CONFIGURACAO> *lista_C, int x1, int y1, int z1, int x2, int y2, int z2)
{
	std::list<CONFIGURACAO> lista;
	std::list<CONFIGURACAO>::iterator it, itfin = lista_C->end();
	for (it = lista_C->begin(); it != itfin; it++)
	{
		if (!(y2 <= (*it).Get_y1() || y1 >= (*it).Get_y2()) && !(z2 <= (*it).Get_z1() || z1 >= (*it).Get_z2()))
		{
			if (x2 >= (*it).Get_x2())
			{
				if ((*it).Get_x2() >= x1 - p * ((double)x2 - x1))
					InsertarConfiguracaoOrden(*it, lista);
			}
			else
			{
				if (x2 >= (*it).Get_x1() - p * ((double)x2 - x1))
					InsertarConfiguracaoOrden(*it, lista);
			}
		}
		if (!(x2 <= (*it).Get_x1() || x1 >= (*it).Get_x2()) && !(z2 <= (*it).Get_z1() || z1 >= (*it).Get_z2()))
		{
			if (y2 >= (*it).Get_y2())
			{
				if ((*it).Get_y2() >= y1 - p * ((double)y2 - y1))
					InsertarConfiguracaoOrden(*it, lista);
			}
			else
			{
				if (y2 >= (*it).Get_y1() - p * ((double)y2 - y1))
					InsertarConfiguracaoOrden(*it, lista);
			}
		}
		if (!(y2 <= (*it).Get_y1() || y1 >= (*it).Get_y2()) && !(x2 <= (*it).Get_x1() || x1 >= (*it).Get_x2()))
		{
			if (z2 >= (*it).Get_z2())
			{
				if ((*it).Get_z2() >= z1 - p * ((double)z2 - z1))
					InsertarConfiguracaoOrden(*it, lista);
			}
			else
			{
				if (z2 >= (*it).Get_z1() - p * ((double)z2 - z1))
					InsertarConfiguracaoOrden(*it, lista);
			}
		}
	}
	return lista;
}
std::list<CONFIGURACAO> CONFIGURACAO::Get_adjacent_blocks(int x1, int y1, int z1, int x2, int y2, int z2)
{
	std::list<CONFIGURACAO> lista;
	std::list<CONFIGURACAO>::iterator it= (m_Container->Get_ListaConfiguracaos()).begin(), itfin = (m_Container->Get_ListaConfiguracaos()).end();
	for (it; it != itfin; it++)
	{
		if ((x2 >= (*it).Get_x1() - (m_Container->Get_p()) * ((double)x2 - x1) || (*it).Get_x2() >= x1 - (m_Container->Get_p()) * ((double)x2 - x1)) && !(y2 <= (*it).Get_y1() || y1 >= (*it).Get_y2()) && !(z2 <= (*it).Get_z1() || z1 >= (*it).Get_z2()))
			m_Container->InsertarConfiguracaoOrden(*it, lista);
		if ((y2 >= (*it).Get_y1() - (m_Container->Get_p()) * ((double)y2 - y1) || (*it).Get_y2() >= y1 - (m_Container->Get_p()) * ((double)y2 - y1)) && !(x2 <= (*it).Get_x1() || x1 >= (*it).Get_x2()) && !(z2 <= (*it).Get_z1() || z1 >= (*it).Get_z2()))
			m_Container->InsertarConfiguracaoOrden(*it, lista);
		if ((z2 >= (*it).Get_z1() - (m_Container->Get_p()) * ((double)z2 - z1) || (*it).Get_z2() >= z1 - (m_Container->Get_p()) * ((double)z2 - z1)) && !(y2 <= (*it).Get_y1() || y1 >= (*it).Get_y2()) && !(x2 <= (*it).Get_x1() || x1 >= (*it).Get_x2()))
			m_Container->InsertarConfiguracaoOrden(*it, lista);
	}
	return lista;
}
std::list<CONFIGURACAO> CONFIGURACAO::Get_adjacent_blocksMov(std::list<CONFIGURACAO> *lista_conf, int x1, int y1, int z1, int x2, int y2, int z2)
{
	std::list<CONFIGURACAO> lista;
	std::list<CONFIGURACAO>::iterator it = lista_conf->begin(), itfin = lista_conf->end();
	for (it; it != itfin; it++)
	{
		if ((x2 >= (*it).Get_x1() - (m_Container->Get_p()) * ((double)x2 - x1) || (*it).Get_x2() >= x1 - (m_Container->Get_p()) * ((double)x2 - x1)) && !(y2 <= (*it).Get_y1() || y1 >= (*it).Get_y2()) && !(z2 <= (*it).Get_z1() || z1 >= (*it).Get_z2()))
			m_Container->InsertarConfiguracaoOrden(*it, lista);
		if ((y2 >= (*it).Get_y1() - (m_Container->Get_p()) * ((double)y2 - y1) || (*it).Get_y2() >= y1 - (m_Container->Get_p()) * ((double)y2 - y1)) && !(x2 <= (*it).Get_x1() || x1 >= (*it).Get_x2()) && !(z2 <= (*it).Get_z1() || z1 >= (*it).Get_z2()))
			m_Container->InsertarConfiguracaoOrden(*it, lista);
		if ((z2 >= (*it).Get_z1() - (m_Container->Get_p()) * ((double)z2 - z1) || (*it).Get_z2() >= z1 - (m_Container->Get_p()) * ((double)z2 - z1)) && !(y2 <= (*it).Get_y1() || y1 >= (*it).Get_y2()) && !(x2 <= (*it).Get_x1() || x1 >= (*it).Get_x2()))
			m_Container->InsertarConfiguracaoOrden(*it, lista);
	}
	return lista;
}
int CONTAINER::surface_in_contact_Bloque(BLOQUE_ARA& B, CONFIGURACAO& Bi, int x, int y, int z)
{
	int l = B.Get_x();
	int w = B.Get_y();
	int h = B.Get_z();
	int xi = Bi.Get_x1();
	int yi = Bi.Get_y1();
	int zi = Bi.Get_z1();
	int li = Bi.Get_x2() - xi;
	int wi = Bi.Get_y2() - yi;
	int hi = Bi.Get_z2() - zi;
	int xmin = max(x, xi);
	int ymin = max(y, yi);
	int zmin = max(z, zi);
	int xmax = min(x + l, Bi.Get_x2());
	int ymax = min(y + w, Bi.Get_y2());
	int zmax = min(z + h, Bi.Get_z2());

	if ((x+l <= xi && x + (double)l >= xi-p*l )|| (Bi.Get_x2() <= x && Bi.Get_x2() >= x-p*l))
		return (ymax - ymin) * (zmax - zmin);
	else if ((y+w <= yi && y + (double)w >= yi-p*w) || (Bi.Get_y2() <= y && Bi.Get_y2() >= y-p*w))
		return (xmax - xmin) * (zmax - zmin);
	else
		return (xmax - xmin) * (ymax - ymin);
}
int CONFIGURACAO::surface_in_contact_Configuracao(int l, int w, int h, CONFIGURACAO& Bi, int x, int y, int z)
{
	int xi = Bi.Get_x1();
	int yi = Bi.Get_y1();
	int zi = Bi.Get_z1();
	int li = Bi.Get_x2() - xi;
	int wi = Bi.Get_y2() - yi;
	int hi = Bi.Get_z2() - zi;
	int xmin = max(x, xi);
	int ymin = max(y, yi);
	int zmin = max(z, zi);
	int xmax = min(x + l, Bi.Get_x2());
	int ymax = min(y + w, Bi.Get_y2());
	int zmax = min(z + h, Bi.Get_z2());

	if ((x + l <= xi && x + (double)l >= xi - (m_Container->Get_p()) * l) || (Bi.Get_x2() <= x && Bi.Get_x2() >= x - (m_Container->Get_p()) * l))
		return (ymax - ymin) * (zmax - zmin);
	else if ((y + w <= yi && y + (double)w >= yi - (m_Container->Get_p()) * w) || (Bi.Get_y2() <= y && Bi.Get_y2() >= y - (m_Container->Get_p()) * w))
		return (xmax - xmin) * (zmax - zmin);
	else
		return (xmax - xmin) * (ymax - ymin);
}

int CONTAINER::surface_in_contact_with_the_container_Bloque(BLOQUE_ARA& B, int x, int y, int z)
{
	int s = 0;
	int l = B.Get_x();
	int w = B.Get_y();
	int h = B.Get_z();
	if (x <= p*l)
		s += w * h;
	if (x + (double)l >= Get_X()-p*l)
		s += w * h;
	if (y <= p*w)
		s += l * h;
	if (y + (double)w >= Get_Y()-p*w)
		s += l * h;
	if (z <= p*h)
		s += l * w;
	if (z + (double)h >= Get_Z()-p*h)
		s += l * w;
	return s;
}
int CONFIGURACAO::surface_in_contact_with_the_container_Configuracao(int l, int w, int h, int x, int y, int z)
{
	int s = 0;
	if (x <= (m_Container->Get_p()) * l)
		s += w * h;
	if (x + (double)l >= m_Container->Get_X() - (m_Container->Get_p()) * l)
		s += w * h;
	if (y <= (m_Container->Get_p()) * w)
		s += l * h;
	if (y + (double)w >= m_Container->Get_Y() - (m_Container->Get_p()) * w)
		s += l * h;
	if (z <= (m_Container->Get_p()) * h)
		s += l * w;
	if (z + (double)h >= m_Container->Get_Z() - (m_Container->Get_p()) * h)
		s += l * w;
	return s;
}

// Me devuelve true si es mejor la primera que la segunda
bool CONFIGURACAO::Mejor_DistA_Que_DistB_Configuracaos(ORIG &A, int NumA,ORIG &B, int NumB,int Vol)
{

	if (m_Container->Get_objetivo_vol()==true)
	{//Solamente funcion objetivo
		if (m_Volumen < Vol) return false;
//		if ((m_Volumen - m_Container->GetMenorVolumen() * NumA) < (Vol - m_Container->GetMenorVolumen() * NumB)) return false;
	//	else return true;
		if (m_Volumen>Vol) return true;
//		if (m_Volumen==Vol && NumA>NumB) return false;
//		Esto es lo nuevo que debo probar para ver si fusiona
		if (m_Volumen==Vol) return get_random(0,1);


		return true;
	}

	//Comparo componente a componente
	//Comparo componente a componente
	if (A.GetPrimero() > B.GetPrimero()) return false;
	if (A.GetPrimero() < B.GetPrimero()) return true;
	if (A.GetSegundo() > B.GetSegundo()) return false;
	if (A.GetSegundo() < B.GetSegundo()) return true;
	if (A.GetTercero() > B.GetTercero()) return false;
	if (A.GetTercero() < B.GetTercero()) return true;
	if (NumA <= NumB) return true;
	else
		return false;
}

void CONTAINER::ActualizarListas(SPACE &EspacioT, CONFIGURACAO &Configuracao,int num)
{
	//Pongo cual es la lista de espacios que tengo ahora mismo
	std::list< std::list< SPACE > >::iterator itC;
	int cont=0;
	for (itC=m_SpacesMC.begin();itC!=m_SpacesMC.end() && cont<=num;itC++,cont++)
	{
		if (cont==num)
			m_Spaces=(*itC);
	}
	//Primero actualizo el numero que  a su vez actualiza el flag
	m_Pieces[Configuracao.Get_Id()].Add_Num(Configuracao.Get_Num());
	m_total_volumen_ocupado+=Configuracao.Get_Volumen();
	std::list< SPACE > ::iterator it;
	bool quitar_piezas=false;
	//si he quitado una tipo de pieza
	if (m_multicontainer==false && m_por_bin == false)
	{

		if (m_Pieces[Configuracao.Get_Id()].Get_Num()==m_Pieces[Configuracao.Get_Id()].Get_q() &&
		(m_Pieces[Configuracao.Get_Id()].Get_x()==m_dimension_menor||m_Pieces[Configuracao.Get_Id()].Get_y()==m_dimension_menor ||m_Pieces[Configuracao.Get_Id()].Get_z()==m_dimension_menor))	
		{
			MinimaDimension();
			quitar_piezas=true;
		}
	}
	else
	{
		if (m_Pieces[Configuracao.Get_Id()].Get_Num()==m_Pieces[Configuracao.Get_Id()].Get_q() &&
		(m_Pieces[Configuracao.Get_Id()].Get_x()==m_dimension_menor_x||m_Pieces[Configuracao.Get_Id()].Get_y()==m_dimension_menor_y ||m_Pieces[Configuracao.Get_Id()].Get_z()==m_dimension_menor_z))	
		{
			MinimaDimensionMC();
			quitar_piezas=true;

		}

	}
	//Ahora tengo que meter los nuevos espacios producidos por la configuracao 
	//ademas los tengo que meter en orden porque despues estarán ordenados y es ir colocandolos en le lugar correspondiente
	std::list< SPACE > lista_temp;	
	if (m_multicontainer == false && m_por_bin == false)
		
		(EspacioT, Configuracao, lista_temp);
	else
	    ActualizarEspaciosElegidoMC(EspacioT,Configuracao,lista_temp);


//Eliminar este espacio
	//FALTA 
	for (it = m_Spaces.begin();it!=m_Spaces.end();)
	{
		if ((*it).Get_x1()==EspacioT.Get_x1() && (*it).Get_x2()==EspacioT.Get_x2() &&
			(*it).Get_y1()==EspacioT.Get_y1() && (*it).Get_y2()==EspacioT.Get_y2() &&
			(*it).Get_z1()==EspacioT.Get_z1() && (*it).Get_z2()==EspacioT.Get_z2() ) 
		{
			m_Spaces.erase(it);
			break;
		}
		++it;
	}
	//
	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin=m_Spaces.end();
	for (it = m_Spaces.begin();it!=m_Spaces.end();)
	{
		//Si se intersectan hacer los espacios
//			SPACE kk=(*it);
//		if ((*it).Get_Flag()==true) continue;
		if (!(Configuracao.Get_x2() <= (*it).Get_x1() ||  Configuracao.Get_x1() >= (*it).Get_x2())
			&& !(Configuracao.Get_y2() <= (*it).Get_y1() ||  Configuracao.Get_y1() >= (*it).Get_y2())
			&& !(Configuracao.Get_z2() <= (*it).Get_z1() ||  Configuracao.Get_z1() >= (*it).Get_z2()))
		{

			if (m_multicontainer == false && m_por_bin == false)
				ActualizarEspaciosElegido((*it), Configuracao, lista_temp);
			else
				ActualizarEspaciosElegidoMC((*it),Configuracao,lista_temp);

			//Tengo que hacer el -- porque me apunta al siguiente
			it=m_Spaces.erase(it);
		}
		else

			++it;

	}

	quitar_piezas = false;
	if (quitar_piezas==true)
	{
	if (m_multicontainer==false)
	{
		//Aqui pruebo si puede quitar alguno y es mas rapido
		if (m_eliminar_espacios==true)
		{
			std::list<SPACE> ::iterator itfin1=m_Spaces.end();
			for (it=m_Spaces.begin();it!=itfin1;)
			{
				if ((m_dimension_menor>min(min((*it).Get_dx(),(*it).Get_dy()),(*it).Get_dz()))
					|| CabeAlguna((*it).Get_dx(),(*it).Get_dy(),(*it).Get_dz()) ==false )
				{
					it=m_Spaces.erase(it);

				}
				else
					++it;
			}
		}
	}
	else
	{
		std::list<SPACE> ::iterator itfin2=m_Spaces.end();
		for (it=m_Spaces.begin();it!=itfin2;)
		{
			if ((m_dimension_menor_x>(*it).Get_dx()) ||
				(m_dimension_menor_y>(*it).Get_dy()) ||
				(m_dimension_menor_z>(*it).Get_dz()) ||
				(m_menor_volumen>(*it).Get_Volumen()))
			{
				it=m_Spaces.erase(it);

			}
			else
				++it;
		}
	}
	}

	//Buscar inclusiones pero solamente con  los nuevos entres ssi
	//la lista esta ordenada se supone
	EliminarInclusionesNuevos(lista_temp);
	//Buscar inclusiones de los nuevos con los antiguos esta función me debería colocar ya las
	//nuevas ordenadas

	//para cuando solo hay tres que los ordene
	if (m_multicontainer==true && m_Spaces.size()==0)
	{
		std::list<SPACE> lista_temp2;
		ColocarOrdenadosNuevos(lista_temp2,lista_temp);
		lista_temp=lista_temp2;
	}

	EliminarInclusionesListaAntigua(m_Spaces,lista_temp);

	//Esta función incluye los nuevos en la lista 
	//15-09-06 
//	m_Spaces.insert(m_Spaces.begin(),lista_temp.begin(),lista_temp.end());
	ColocarOrdenadosNuevos(m_Spaces,lista_temp);
	//Volver a colocar los bins donde tocas
	cont=0;
	for (itC=m_SpacesMC.begin();itC!=m_SpacesMC.end() && cont<=num;itC++,cont++)
	{
		if (cont==num)
			(*itC)=m_Spaces;
	}
	
//	EliminarMasDe100Espacios(m_Spaces);



}


void CONTAINER::ActualizarListas(SPACE &EspacioT, CONFIGURACAO &Configuracao)
{
	//Pongo cual es la lista de espacios que tengo ahora mismo
	//Primero actualizo el numero que  a su vez actualiza el flag
	m_Pieces[Configuracao.Get_Id()].Add_Num(Configuracao.Get_Num());
	m_total_volumen_ocupado+=Configuracao.Get_Volumen();
	std::list< SPACE > ::iterator it;
	/*bool quitar_piezas=false;*/
	//si he quitado una tipo de pieza
	if ((m_multicontainer==false && m_por_bin == false) || m_rotacion==true)
	{

		if (m_Pieces[Configuracao.Get_Id()].Get_Num()==m_Pieces[Configuracao.Get_Id()].Get_q() &&
		(m_Pieces[Configuracao.Get_Id()].Get_x()==m_dimension_menor||m_Pieces[Configuracao.Get_Id()].Get_y()==m_dimension_menor ||m_Pieces[Configuracao.Get_Id()].Get_z()==m_dimension_menor))	
		{
			MinimaDimension();
			/*quitar_piezas=true;*/
		}
	}
	else
	{
		if (m_Pieces[Configuracao.Get_Id()].Get_Num()==m_Pieces[Configuracao.Get_Id()].Get_q() &&
		(m_Pieces[Configuracao.Get_Id()].Get_x()==m_dimension_menor_x||m_Pieces[Configuracao.Get_Id()].Get_y()==m_dimension_menor_y ||m_Pieces[Configuracao.Get_Id()].Get_z()==m_dimension_menor_z))	
		{
			MinimaDimensionMC();
			/*quitar_piezas=true;*/

		}

	}
	//Ahora tengo que meter los nuevos espacios producidos por la configuracao 
	//ademas los tengo que meter en orden porque despues estarán ordenados y es ir colocandolos en le lugar correspondiente
	std::list< SPACE > lista_temp;	
	if ((m_multicontainer == false && m_por_bin == false) || m_rotacion == true)
		ActualizarEspaciosElegido(EspacioT, Configuracao, lista_temp);
	else
		ActualizarEspaciosElegidoMC(EspacioT,Configuracao,lista_temp);
	if (m_juntar_spaces == true)
		JuntarSpacesBloques(m_Spaces, lista_temp, Configuracao);

//Eliminar este espacio
	//FALTA 
	for (it = m_Spaces.begin();it!=m_Spaces.end();)
	{
		if ((*it).Get_x1()==EspacioT.Get_x1() && (*it).Get_x2()==EspacioT.Get_x2() &&
			(*it).Get_y1()==EspacioT.Get_y1() && (*it).Get_y2()==EspacioT.Get_y2() &&
			(*it).Get_z1()==EspacioT.Get_z1() && (*it).Get_z2()==EspacioT.Get_z2() ) 
		{
			m_Spaces.erase(it);
			break;
		}
		++it;
	}
	//
	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin=m_Spaces.end();
	for (it = m_Spaces.begin();it!=m_Spaces.end();)
	{
		//Si se intersectan hacer los espacios
//			SPACE kk=(*it);
//		if ((*it).Get_Flag()==true) continue;
		if (!(Configuracao.Get_x2() <= (*it).Get_x1() ||  Configuracao.Get_x1() >= (*it).Get_x2())
			&& !(Configuracao.Get_y2() <= (*it).Get_y1() ||  Configuracao.Get_y1() >= (*it).Get_y2())
			&& !(Configuracao.Get_z2() <= (*it).Get_z1() ||  Configuracao.Get_z1() >= (*it).Get_z2()))
		{

			if (m_multicontainer==false && m_por_bin == false)
				ActualizarEspaciosElegido((*it),Configuracao,lista_temp);
			else
				ActualizarEspaciosElegidoMC((*it),Configuracao,lista_temp);

			//Tengo que hacer el -- porque me apunta al siguiente
			it=m_Spaces.erase(it);
		}
		else

			++it;

	}
	if (m_juntar_spaces == true)
		JuntarSpacesBloques(m_Spaces, lista_temp, Configuracao);
	//quitar_piezas = false;
	//if (quitar_piezas==true)
	//{
	//if (m_multicontainer==false)
	//{
	//	//Aqui pruebo si puede quitar alguno y es mas rapido
	//	if (m_eliminar_espacios==true)
	//	{
	//		std::list<SPACE> ::iterator itfin1=m_Spaces.end();
	//		for (it=m_Spaces.begin();it!=itfin1;)
	//		{
	//			if (((m_dimension_menor>min(min((*it).Get_dx(),(*it).Get_dy()),(*it).Get_dz()))
	//				|| CabeAlguna((*it).Get_dx(),(*it).Get_dy(),(*it).Get_dz()) ==false))
	//			{
	//				it=m_Spaces.erase(it);

	//			}
	//			else
	//				++it;
	//		}
	//	}
	//}
	//else
	//{
	//	std::list<SPACE> ::iterator itfin2=m_Spaces.end();
	//	for (it=m_Spaces.begin();it!=itfin2;)
	//	{
	//		if ((m_dimension_menor_x>(*it).Get_dx()) ||
	//			(m_dimension_menor_y>(*it).Get_dy()) ||
	//			(m_dimension_menor_z>(*it).Get_dz()) ||
	//			(m_menor_volumen>(*it).Get_Volumen()))
	//		{
	//			it=m_Spaces.erase(it);

	//		}
	//		else
	//			++it;
	//	}
	//}
	//}

	//Buscar inclusiones pero solamente con  los nuevos entres ssi
	//la lista esta ordenada se supone
	EliminarInclusionesNuevos(lista_temp);
	//Buscar inclusiones de los nuevos con los antiguos esta función me debería colocar ya las
	//nuevas ordenadas

	//para cuando solo hay tres que los ordene
	if (m_multicontainer==true && m_Spaces.size()==0)
	{
		std::list<SPACE> lista_temp2;
		ColocarOrdenadosNuevos(lista_temp2,lista_temp);
		lista_temp=lista_temp2;
	}

	EliminarInclusionesListaAntigua(m_Spaces,lista_temp);

	//Esta función incluye los nuevos en la lista 
	//15-09-06 
//	m_Spaces.insert(m_Spaces.begin(),lista_temp.begin(),lista_temp.end());
	ColocarOrdenadosNuevos(m_Spaces,lista_temp);

	/*ComprobarEspaciosNoIncluidos(m_Spaces);*/
	/*EliminarInclusionesNuevos(m_Spaces);*/
//	EliminarMasDe100Espacios(m_Spaces);



}
void CONTAINER::ColocarOrdenadosNuevos(std::list< SPACE > &lista,std::list< SPACE > &lista_temp)
{

	std::list< SPACE >::iterator it;
	for (it=lista_temp.begin();it!=lista_temp.end();it++)
	{
//		SPACE kk=(*it);
		InsertarOrden(lista,(*it));
	}

}
void CONTAINER::ActualizarEspaciosElegido(SPACE &E, CONFIGURACAO &C,std::list <SPACE> &lista_temp)
{
	//Podemos tener seis posibles espacios nuevos
	int dimx=E.Get_x2()-E.Get_x1();
	int dimy=E.Get_y2()-E.Get_y1();
	int dimz=E.Get_z2()-E.Get_z1();
	
	//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
	if ((C.Get_x1()-E.Get_x1())>0)
	{
		//Si se da esto es un espacio en el que no voy a poder colocar nada 
		//Por ahora no lo creo
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min((C.Get_x1() - E.Get_x1()), dimy), dimz) && (m_menor_volumen <= ((C.Get_x1() - E.Get_x1()) * dimy * dimz)))
		{
			if (m_eliminar_espacios == false || CabeAlguna(C.Get_x1() - E.Get_x1(), dimy, dimz) == true)
			{
				SPACE Espacio(this, E.Get_x1(), E.Get_y1(), E.Get_z1(), (C.Get_x1() - E.Get_x1()), dimy, dimz);
				InsertarOrden(lista_temp, Espacio);
			}
		}
	}


	//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
	if ((E.Get_x2()-C.Get_x2())>0)
	{
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min((E.Get_x2() - C.Get_x2()), dimy), dimz) && (m_menor_volumen <= ((E.Get_x2() - C.Get_x2()) * dimy * dimz)))
		{
			if (m_eliminar_espacios == false || CabeAlguna((E.Get_x2() - C.Get_x2()), dimy, dimz) == true)
			{
				SPACE Espacio(this, C.Get_x2(), E.Get_y1(), E.Get_z1(), (E.Get_x2() - C.Get_x2()), dimy, dimz);
				InsertarOrden(lista_temp, Espacio);
			}
		}
	}
	//Abajo
	//Abajo: if (zC1-zE1)>0 espaço es (xE2-xE1, yE2-yE1, (zC1-zE1)) v: (xE1,yE1,zC1)
	if ((C.Get_z1() - E.Get_z1()) > 0)
	{
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min(dimx, dimy), (C.Get_z1() - E.Get_z1())) && (m_menor_volumen <= ((C.Get_z1() - E.Get_z1()) * dimx * dimy)))
		{
			if (m_eliminar_espacios == false || CabeAlguna(dimx, dimy, (C.Get_z1() - E.Get_z1())) == true)
			{
				SPACE Espacio(this, E.Get_x1(), E.Get_y1(), E.Get_z1(), dimx, dimy, (C.Get_z1() - E.Get_z1()));
				InsertarOrden(lista_temp, Espacio);
			}
		}
	}

	//Arriba
	//Arriba:  if (zE2-zC2)>0 espaço es (xE2-xE1, yE2-yE1, (zE2-zC2)) v: (xE1,yE1,zE1)
	if ((E.Get_z2()-C.Get_z2())>0 && m_space_arriba==true)
	{
		if (m_full_supported == false)
		{
			if (m_eliminar_espacios == false || m_dimension_menor <= min(min(dimx, dimy), (E.Get_z2() - C.Get_z2())) && (m_menor_volumen <= (dimx*dimy* (E.Get_z2() - C.Get_z2()))))
			{
				if (m_eliminar_espacios == false || CabeAlguna(dimx, dimy, (E.Get_z2() - C.Get_z2())) == true)
				{

					SPACE Espacio(this, E.Get_x1(), E.Get_y1(), C.Get_z2(), dimx, dimy, (E.Get_z2() - C.Get_z2()));
					InsertarOrden(lista_temp, Espacio);
				}
			}
		}
		else
		{
			if ((C.Get_Id() < 1000 || (C.Get_Id() >= 1000 && m_por_bloques == false)))
			{
				if (m_juntar_spaces == false)
				{
					if (m_eliminar_espacios == false || m_dimension_menor <= min(min((min(C.Get_x2(), E.Get_x2()) - min(C.Get_x1(), E.Get_x1())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1()))), (E.Get_z2() - C.Get_z2())) && (m_menor_volumen <= ((min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1()))*(min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())) * (E.Get_z2() - C.Get_z2()))))
					{
						if (m_eliminar_espacios == false || CabeAlguna((min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())), (E.Get_z2() - C.Get_z2())) == true)
						{
							SPACE Espacio(this, max(C.Get_x1(), E.Get_x1()), max(C.Get_y1(), E.Get_y1()), C.Get_z2(), (min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())), (E.Get_z2() - C.Get_z2()));
							InsertarOrden(lista_temp, Espacio);
						}
					}
				}
				else
				{
					if (m_eliminar_espacios == false || m_dimension_menor <= (E.Get_z2() - C.Get_z2()) && (m_menor_volumen <= (m_X * m_Y * (E.Get_z2() - C.Get_z2()))))
					{
						if (m_eliminar_espacios == false || CabeAlguna(m_X, m_Y, (E.Get_z2() - C.Get_z2())) == true)
						{
							SPACE Espacio(this, max(C.Get_x1(), E.Get_x1()), max(C.Get_y1(), E.Get_y1()), C.Get_z2(), (min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())), (E.Get_z2() - C.Get_z2()));
							InsertarOrden(lista_temp, Espacio);
							//JuntarSpacesBloques(m_Spaces, lista_temp, C); //Esto aqui?
						}
					}
				}
			}
		}
//		lista_temp.push_back(Espacio);
	}
	//Fuera
	//Furera: if (yE1-yC1)>0 espaço es (xE2-xE1, (yE1-yC1),zE2-zE1) v: (xE1,yC1,zE1)
	if ((C.Get_y1() - E.Get_y1()) > 0)
	{
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min(dimx, (C.Get_y1() - E.Get_y1())), dimz) && (m_menor_volumen <= ((C.Get_y1() - E.Get_y1()) * dimx * dimz)))
		{
			if (m_eliminar_espacios == false || CabeAlguna(dimx, (C.Get_y1() - E.Get_y1()), dimz) == true)
			{
				SPACE Espacio(this, E.Get_x1(), E.Get_y1(), E.Get_z1(), dimx, (C.Get_y1() - E.Get_y1()), dimz);
				InsertarOrden(lista_temp, Espacio);
			}
		}
	}
	//Dentro
	//Dentro:  if (zC2-zE2)>0 espaço es (xE2-xE1,yE2-yE1, (zC2-zE2)) v: (xE1,yE1,zE1)
	if ((E.Get_y2()-C.Get_y2())>0)
	{
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min(dimx, (E.Get_y2() - C.Get_y2())), dimz) && (m_menor_volumen <= ((E.Get_y2() - C.Get_y2()) * dimx * dimz)))
		{
			if (m_eliminar_espacios == false || CabeAlguna(dimx, (E.Get_y2() - C.Get_y2()), dimz) == true)
			{
				SPACE Espacio(this, E.Get_x1(), C.Get_y2(), E.Get_z1(), dimx, (E.Get_y2() - C.Get_y2()), dimz);
				InsertarOrden(lista_temp, Espacio);
			}
		}
	}
}
void CONTAINER::ActualizarEspaciosElegidoMC(SPACE &E, CONFIGURACAO &C,std::list <SPACE> &lista_temporal)
{
	//Podemos tener seis posibles espacios nuevos
	int dimx=E.Get_x2()-E.Get_x1();
	int dimy=E.Get_y2()-E.Get_y1();
	int dimz=E.Get_z2()-E.Get_z1();
	

	//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
	if ((C.Get_x1()-E.Get_x1())>0)
	{
		//Si se da esto es un espacio en el que no voy a poder colocar nada 
		//Por ahora no lo creo
		if (m_eliminar_espacios==false || (m_dimension_menor_x<=(C.Get_x1()-E.Get_x1()) && m_dimension_menor_y<=dimy && m_dimension_menor_z<=dimz))
		{
			SPACE Espacio(this,E.Get_x1(),E.Get_y1(),E.Get_z1(),(C.Get_x1()-E.Get_x1()),dimy,dimz );
			InsertarOrden(lista_temporal,Espacio);
		}
	}


	//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
	if ((E.Get_x2()-C.Get_x2())>0)
	{
		if (m_eliminar_espacios==false || (m_dimension_menor_x<=(E.Get_x2()-C.Get_x2()) && m_dimension_menor_y<=dimy && m_dimension_menor_z<=dimz))
		{

			SPACE Espacio(this,C.Get_x2(),E.Get_y1(),E.Get_z1(),(E.Get_x2()-C.Get_x2()),dimy,dimz);
			InsertarOrden(lista_temporal,Espacio);
		}
//		lista_temp.push_back(Espacio);
	}
	//Abajo
	//Abajo: if (yC1-yE1)>0 espaço es (xE2-xE1, (yC1-yE1),zE2-zE1) v: (xE1,yC1,zE1)
	if ((C.Get_y1()-E.Get_y1())>0)
	{
		if (m_eliminar_espacios==false || (m_dimension_menor_y<=(C.Get_y1()-E.Get_y1()) && m_dimension_menor_x<=dimx && m_dimension_menor_z<=dimz))
		{


			SPACE Espacio(this,E.Get_x1(),E.Get_y1(),E.Get_z1(),dimx,(C.Get_y1()-E.Get_y1()),dimz  );
			InsertarOrden(lista_temporal,Espacio);
		}
//		lista_temp.push_back(Espacio);
	}

	//Arriba
	//Arriba:  if (yE2-yC2)>0 espaço es (xE2-xE1, (yE2-yC2),zE2-zE1) v: (xE1,yE1,zE1)
	if ((E.Get_y2()-C.Get_y2())>0)
	{
		if (m_eliminar_espacios==false || (m_dimension_menor_y<=(E.Get_y2()-C.Get_y2()) && m_dimension_menor_x<=dimx && m_dimension_menor_z<=dimz))
		{

			SPACE Espacio(this,E.Get_x1(),C.Get_y2(),E.Get_z1(),dimx,(E.Get_y2()-C.Get_y2()),dimz  );

			InsertarOrden(lista_temporal,Espacio);
		}
//		lista_temp.push_back(Espacio);
	}
	//Fuera
	//Furera: if (zE1-zC1)>0 espaço es (xE2-xE1,yE2-yE1, (zE1-zC1)) v: (xE1,yE1,zC1)
	if ((C.Get_z1()-E.Get_z1())>0)
	{
		if (m_eliminar_espacios==false || (m_dimension_menor_z<=(C.Get_z1()-E.Get_z1()) && m_dimension_menor_x<=dimx && m_dimension_menor_y<=dimy))
		{

			SPACE Espacio(this,E.Get_x1(),E.Get_y1(),E.Get_z1(),dimx,dimy,(C.Get_z1()-E.Get_z1()) );
			InsertarOrden(lista_temporal,Espacio);
		}
//		lista_temp.push_back(Espacio);
	}
	//Dentro
	//Dentro:  if (zC2-zE2)>0 espaço es (xE2-xE1,yE2-yE1, (zC2-zE2)) v: (xE1,yE1,zE1)
	if ((E.Get_z2()-C.Get_z2())>0)
	{
		if (m_full_supported == false)
		{

			if (m_eliminar_espacios == false || (m_dimension_menor_z <= (E.Get_z2() - C.Get_z2()) && m_dimension_menor_x <= dimx && m_dimension_menor_y <= dimy))
			{


				SPACE Espacio(this, E.Get_x1(), E.Get_y1(), C.Get_z2(), dimx, dimy, (E.Get_z2() - C.Get_z2()));
				InsertarOrden(lista_temporal, Espacio);
			}
		}
		else
		{
			if (m_dimension_menor <= min(min((C.Get_x2() - C.Get_x1()), (C.Get_y2() - C.Get_y1())), (E.Get_z2() - C.Get_z2())) && (m_menor_volumen <= ((C.Get_x2() - C.Get_x1())*(C.Get_y2() - C.Get_y1())*(E.Get_z2() - C.Get_z2()))))
			{
				if (CabeAlguna((C.Get_x2() - C.Get_x1()), (C.Get_y2() - C.Get_y1()), (E.Get_z2() - C.Get_z2())) == true)
				{
					SPACE Espacio(this, max(C.Get_x1(), E.Get_x1()), max(C.Get_y1(), E.Get_y1()), C.Get_z2(), (min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())), (E.Get_z2() - C.Get_z2()));

					InsertarOrden(lista_temporal, Espacio);
				}
			}
		}

//		lista_temp.push_back(Espacio);
	}
	


}
void CONTAINER::ActualizarEspaciosElegidoMov(SPACE &E, CONFIGURACAO &C,std::list <SPACE> &lista_temporal, std::list <SPACE> &lista_espacios)
{
	//Podemos tener seis posibles espacios nuevos
	int dimx=E.Get_x2()-E.Get_x1();
	int dimy=E.Get_y2()-E.Get_y1();
	int dimz=E.Get_z2()-E.Get_z1();

	//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
	if ((C.Get_x1() - E.Get_x1()) > 0)
	{
		//Si se da esto es un espacio en el que no voy a poder colocar nada 
		//Por ahora no lo creo
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min((C.Get_x1() - E.Get_x1()), dimy), dimz) && (m_menor_volumen <= ((C.Get_x1() - E.Get_x1()) * dimy * dimz)))
		{
			if (m_eliminar_espacios == false || CabeAlgunaMov(C.Get_x1() - E.Get_x1(), dimy, dimz) == true)
			{
				SPACE Espacio(this, E.Get_x1(), E.Get_y1(), E.Get_z1(), (C.Get_x1() - E.Get_x1()), dimy, dimz);
				InsertarOrden(lista_temporal, Espacio);
			}
		}
	}


	//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
	if ((E.Get_x2()-C.Get_x2())>0)
	{
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min((E.Get_x2() - C.Get_x2()), dimy), dimz) && (m_menor_volumen <= ((E.Get_x2() - C.Get_x2()) * dimy * dimz)))
		{
			if (m_eliminar_espacios == false || CabeAlgunaMov((E.Get_x2() - C.Get_x2()), dimy, dimz) == true)
			{
				SPACE Espacio(this, C.Get_x2(), E.Get_y1(), E.Get_z1(), (E.Get_x2() - C.Get_x2()), dimy, dimz);
				InsertarOrden(lista_temporal, Espacio);
			}
		}
	}
	//Abajo
	//Abajo: if (zC1-zE1)>0 espaço es (xE2-xE1, yE2-yE1, (zC1-zE1)) v: (xE1,yE1,zC1)
	if ((C.Get_z1()-E.Get_z1())>0)
	{
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min(dimx, dimy), (C.Get_z1() - E.Get_z1())) && (m_menor_volumen <= ((C.Get_z1() - E.Get_z1()) * dimx * dimy)))
		{
			if (m_eliminar_espacios == false || CabeAlgunaMov(dimx, dimy, (C.Get_z1() - E.Get_z1())) == true)
			{
				SPACE Espacio(this, E.Get_x1(), E.Get_y1(), E.Get_z1(), dimx, dimy, (C.Get_z1() - E.Get_z1()));
				InsertarOrden(lista_temporal, Espacio);
			}
		}
	}

	//Arriba
	//Arriba:  if (zE2-zC2)>0 espaço es (xE2-xE1, yE2-yE1, (zE2-zC2)) v: (xE1,yE1,zE1)
	if ((E.Get_z2()-C.Get_z2())>0 && m_space_arriba == true)
	{
	    if (m_full_supported == false)
		{
			if (m_eliminar_espacios == false || m_dimension_menor <= min(min(dimx, (E.Get_z2() - C.Get_z2())), dimy) && (m_menor_volumen <= ((E.Get_z2() - C.Get_z2())*dimx*dimy)))
			{
				if (m_eliminar_espacios == false || CabeAlgunaMov(dimx, dimy, (E.Get_z2() - C.Get_z2())) == true)
				{
					SPACE Espacio(this, E.Get_x1(), E.Get_y1(), C.Get_z2(), dimx, dimy, (E.Get_z2() - C.Get_z2()));
					InsertarOrden(lista_temporal, Espacio);
				}
			}
		}
		else
		{
			if (C.Get_Id() < 1000 || (C.Get_Id()>=1000 && m_por_bloques==false))
			{
				if (m_juntar_spaces == false)
				{
					if (m_eliminar_espacios == false || m_dimension_menor <= min(min((min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())), (E.Get_z2() - C.Get_z2())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1()))) && (m_menor_volumen <= ((min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())) * (E.Get_z2() - C.Get_z2()) * (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())))))
					{
						if (m_eliminar_espacios == false || CabeAlgunaMov((min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())), (E.Get_z2() - C.Get_z2())) == true)
						{
							SPACE Espacio(this, max(C.Get_x1(), E.Get_x1()), max(C.Get_y1(), E.Get_y1()), C.Get_z2(), (min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())), (E.Get_z2() - C.Get_z2()));
							InsertarOrden(lista_temporal, Espacio);
						}
					}
				}
				else
				{
					if (m_eliminar_espacios == false || m_dimension_menor <= (E.Get_z2() - C.Get_z2()) && (m_menor_volumen <= (m_X * (E.Get_z2() - C.Get_z2()) * m_Y)))
					{
						if (m_eliminar_espacios == false || CabeAlgunaMov(m_X, m_Y, (E.Get_z2() - C.Get_z2())) == true)
						{
							SPACE Espacio(this, max(C.Get_x1(), E.Get_x1()), max(C.Get_y1(), E.Get_y1()), C.Get_z2(), (min(C.Get_x2(), E.Get_x2()) - max(C.Get_x1(), E.Get_x1())), (min(C.Get_y2(), E.Get_y2()) - max(C.Get_y1(), E.Get_y1())), (E.Get_z2() - C.Get_z2()));
							InsertarOrden(lista_temporal, Espacio);
							/*JuntarSpacesBloques(lista_espacios, lista_temporal, C);*/
						}
					}
				}
			}
		}
//		lista_temp.push_back(Espacio);
	}
	//Fuera
	//Furera: if (yE1-yC1)>0 espaço es (xE2-xE1, (yE1-yC1), zE2-zE1) v: (xE1,yC1,zE1)
	if ((C.Get_y1() - E.Get_y1()) > 0)
	{
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min(dimx, dimz), (C.Get_y1() - E.Get_y1())) && (m_menor_volumen <= ((C.Get_y1() - E.Get_y1()) * dimx * dimz)))
		{
			if (m_eliminar_espacios == false || CabeAlgunaMov(dimx, (C.Get_y1() - E.Get_y1()), dimz) == true)
			{
				SPACE Espacio(this, E.Get_x1(), E.Get_y1(), E.Get_z1(), dimx, (C.Get_y1() - E.Get_y1()), dimz);
				InsertarOrden(lista_temporal, Espacio);
			}
		}
	}

	//Dentro
	//Dentro:  if (yC2-yE2)>0 espaço es (xE2-xE1, (yC2-yE2), zE2-zE1) v: (xE1,yE1,zE1)
	if ((E.Get_y2() - C.Get_y2()) > 0)
	{
		if (m_eliminar_espacios == false || m_dimension_menor <= min(min(dimx, dimz), (E.Get_y2() - C.Get_y2())) && (m_menor_volumen <= ((E.Get_y2() - C.Get_y2()) * dimx * dimz)))
		{
			if (m_eliminar_espacios == false || CabeAlgunaMov(dimx, (E.Get_y2() - C.Get_y2()), dimz) == true)
			{
				SPACE Espacio(this, E.Get_x1(), C.Get_y2(), E.Get_z1(), dimx, (E.Get_y2() - C.Get_y2()), dimz);
				InsertarOrden(lista_temporal, Espacio);
			}
		}
	}
}
//Esta funcion crea las nuevas configuraciones que surgen al separar un trozo de la configuración
//además las mete en orden para que luego se puedan meter en la funcióny no haya que volver a ordenar

//Esta funcion crea las nuevas configuraciones que surgen al separar un trozo de la configuración
//además las mete en orden para que luego se puedan meter en la funcióny no haya que volver a ordenar

void CONTAINER::ActualizarConfiguracaoGravedad(CONFIGURACAO &E, int x1,int y1, int z1, int x2, int y2, int z2,std::list <CONFIGURACAO> &lista_temp, short int sentido)
{
	//Podemos tener seis posibles Configuracaos nuevos
	int dimx=E.Get_x2()-E.Get_x1();
	int dimy=E.Get_y2()-E.Get_y1();
	int dimz=E.Get_z2()-E.Get_z1();
	//Para un de los otros dos lo hago como la caja y el otro como es
		//Recordar tengo que poner cuantos hay en cada direccion Saludines
	if (sentido==0)
	{
		//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
		if ((x1-E.Get_x1())>0)
		{
			//Si se da esto es un Configuracao en el que no voy a poder colocar nada 
			//Por ahora no lo creo
			if (0<min(min((x1-E.Get_x1()),dimy),dimz) )
			{
				CONFIGURACAO Configuracao(this, E.Get_Id(),E.Get_x1(),E.Get_y1(),E.Get_z1(),E.Get_x1()+(x1-E.Get_x1()),E.Get_y1()+dimy,E.Get_z1()+dimz ,E.Get_Tipo(),0,E.Get_orig());
				//Tengo que decirle cuantas en el eje x, eje y y ejez
				Configuracao.PonerMedidas((x1-E.Get_x1())/((E.Get_x2()-E.Get_x1())/E.Get_dx()),E.Get_dy(),E.Get_dz());
				lista_temp.push_back(Configuracao);
			}
		}


		//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
		if ((E.Get_x2()-x2)>0)
		{
			if (0<min(min((E.Get_x2()-x2),dimy),dimz) )
			{

				CONFIGURACAO Configuracao(this, E.Get_Id(),x2,E.Get_y1(),E.Get_z1(),x2+(E.Get_x2()-x2),E.Get_y1()+dimy,E.Get_z1()+dimz,E.Get_Tipo(),0,E.Get_orig());
				Configuracao.PonerMedidas((E.Get_x2()-x2)/((E.Get_x2()-E.Get_x1())/E.Get_dx()),E.Get_dy(),E.Get_dz());

				lista_temp.push_back(Configuracao);
			}
		}
		//Estos dos mas pequños
		//Abajo
		//Abajo: if (yC1-yE1)>0 espaço es (xE2-xE1, (yC1-yE1),zE2-zE1) v: (xE1,yC1,zE1)
		if ((y1-E.Get_y1())>0)
		{
			if (0<min(min(dimx,(y1-E.Get_y1())),dimz) )
			{

				CONFIGURACAO Configuracao(this, E.Get_Id(),x1,E.Get_y1(),E.Get_z1(),x1+x2-x1,E.Get_y1()+(y1-E.Get_y1()),E.Get_z1()+dimz  ,E.Get_Tipo(),0,E.Get_orig());
				Configuracao.PonerMedidas(1,(y1-E.Get_y1())/((E.Get_y2()-E.Get_y1())/E.Get_dy()),E.Get_dz());

				lista_temp.push_back(Configuracao);
			}
		}
		//Arriba
		//Arriba:  if (yE2-yC2)>0 espaço es (xE2-xE1, (yE2-yC2),zE2-zE1) v: (xE1,yE1,zE1)
		if ((E.Get_y2()-y2)>0)
		{
		if (0<min(min(dimx,(E.Get_y2()-y2)),dimz) )
		{

			CONFIGURACAO Configuracao(this, E.Get_Id(),x1,y2,E.Get_z1(),x1+x2-x1,y2+(E.Get_y2()-y2),E.Get_z1()+dimz  ,E.Get_Tipo(),0,E.Get_orig());
			Configuracao.PonerMedidas(1,(E.Get_y2()-y2)/((E.Get_y2()-E.Get_y1())/E.Get_dy()),E.Get_dz());

			lista_temp.push_back(Configuracao);
		}
	}
	}
	if (sentido==1)
	{

	//ya que los de arriba y abajo no son necesairos
	//Fuera
	//Furera: if (zE1-zC1)>0 espaço es (xE2-xE1,yE2-yE1, (zE1-zC1)) v: (xE1,yE1,zC1)
	if ((z1-E.Get_z1())>0)
	{
		if (0<min(min(dimx,dimy),(z1-E.Get_z1())) )
		{

			CONFIGURACAO Configuracao(this, E.Get_Id(),E.Get_x1(),E.Get_y1(),E.Get_z1(),E.Get_x1()+dimx,E.Get_y1()+dimy,E.Get_z1()+(z1-E.Get_z1()),E.Get_Tipo(),0,E.Get_orig());
			Configuracao.PonerMedidas(E.Get_dx(),E.Get_dy(),(z1-E.Get_z1())/((E.Get_z2()-E.Get_z1())/E.Get_dz()));
			lista_temp.push_back(Configuracao);
		}
	}
	//Dentro
	//Dentro:  if (zC2-zE2)>0 espaço es (xE2-xE1,yE2-yE1, (zC2-zE2)) v: (xE1,yE1,zE1)
	if ((E.Get_z2()-z2)>0)
	{
		if (0<min(min(dimx,dimy),(E.Get_z2()-z2)) )
		{

			CONFIGURACAO Configuracao(this, E.Get_Id(),E.Get_x1(),E.Get_y1(),z2,E.Get_x1()+dimx,E.Get_y1()+dimy,z2+(E.Get_z2()-z2) ,E.Get_Tipo(),0,E.Get_orig());
			Configuracao.PonerMedidas(E.Get_dx(),E.Get_dy(),(E.Get_z2()-z2)/((E.Get_z2()-E.Get_z1())/E.Get_dz()));

			lista_temp.push_back(Configuracao);
		}
	}

		//Estos dos mas pequños
	//Abajo
	//Abajo: if (yC1-yE1)>0 espaço es (xE2-xE1, (yC1-yE1),zE2-zE1) v: (xE1,yC1,zE1)
	if ((y1-E.Get_y1())>0)
	{
		if (0<min(min(dimx,(y1-E.Get_y1())),dimz) )
		{

			CONFIGURACAO Configuracao(this, E.Get_Id(),E.Get_x1(),E.Get_y1(),z1,E.Get_x1()+dimx,E.Get_y1()+(y1-E.Get_y1()),z1+z2-z1  ,E.Get_Tipo(),0,E.Get_orig());
			Configuracao.PonerMedidas(E.Get_dx(),(y1-E.Get_y1())/((E.Get_y2()-E.Get_y1())/E.Get_dy()),1);
			lista_temp.push_back(Configuracao);
		}
	}
	//Arriba
	//Arriba:  if (yE2-yC2)>0 espaço es (xE2-xE1, (yE2-yC2),zE2-zE1) v: (xE1,yE1,zE1)
	if ((E.Get_y2()-y2)>0)
	{
		if (0<min(min(dimx,(E.Get_y2()-y2)),dimz) )
		{

			CONFIGURACAO Configuracao(this, E.Get_Id(),E.Get_x1(),y2,z1,E.Get_x1()+dimx,y2+(E.Get_y2()-y2),z1+z2-z1  ,E.Get_Tipo(),0,E.Get_orig());
			Configuracao.PonerMedidas(E.Get_dx(),(E.Get_y2()-y2)/((E.Get_y2()-E.Get_y1())/E.Get_dy()),1);

			lista_temp.push_back(Configuracao);
		}
	}
	}

	if (sentido==2)
	{

	//ya que los de arriba y abajo no son necesairos
	//Fuera
	//Furera: if (zE1-zC1)>0 espaço es (xE2-xE1,yE2-yE1, (zE1-zC1)) v: (xE1,yE1,zC1)
	if ((z1-E.Get_z1())>0)
	{
		if (0<min(min(dimx,dimy),(z1-E.Get_z1())) )
		{

			CONFIGURACAO Configuracao(this, E.Get_Id(),x1,E.Get_y1(),E.Get_z1(),x2,E.Get_y1()+dimy,E.Get_z1()+(z1-E.Get_z1()),E.Get_Tipo(),0,E.Get_orig());
			Configuracao.PonerMedidas(1,E.Get_dy(),(z1-E.Get_z1())/((E.Get_z2()-E.Get_z1())/E.Get_dz()));
			lista_temp.push_back(Configuracao);
		}
	}
	//Dentro
	//Dentro:  if (zC2-zE2)>0 espaço es (xE2-xE1,yE2-yE1, (zC2-zE2)) v: (xE1,yE1,zE1)
	if ((E.Get_z2()-z2)>0)
	{
		if (0<min(min(dimx,dimy),(E.Get_z2()-z2)) )
		{

			CONFIGURACAO Configuracao(this, E.Get_Id(),x1,E.Get_y1(),z2,x2,E.Get_y1()+dimy,z2+(E.Get_z2()-z2) ,E.Get_Tipo(),0,E.Get_orig());
			Configuracao.PonerMedidas(1,E.Get_dy(),(E.Get_z2()-z2)/((E.Get_z2()-E.Get_z1())/E.Get_dz()));

			lista_temp.push_back(Configuracao);
		}
	}

		//Estos dos mas pequños
	//Abajo
	//Abajo: if (yC1-yE1)>0 espaço es (xE2-xE1, (yC1-yE1),zE2-zE1) v: (xE1,yC1,zE1)
		//Izquierda: if (xE1-xC1)>0 espaço es ((xE1-xC1),yE2-yE1,zE2-zE1)  v: (xE1,yE1,zE1)
		if ((x1-E.Get_x1())>0)
		{
			//Si se da esto es un Configuracao en el que no voy a poder colocar nada 
			//Por ahora no lo creo
			if (0<min(min((x1-E.Get_x1()),dimy),dimz) )
			{
				CONFIGURACAO Configuracao(this, E.Get_Id(),E.Get_x1(),E.Get_y1(),E.Get_z1(),E.Get_x1()+(x1-E.Get_x1()),E.Get_y1()+dimy,E.Get_z1()+dimz ,E.Get_Tipo(),0,E.Get_orig());
				//Tengo que decirle cuantas en el eje x, eje y y ejez
				Configuracao.PonerMedidas((x1-E.Get_x1())/((E.Get_x2()-E.Get_x1())/E.Get_dx()),E.Get_dy(),E.Get_dz());
				lista_temp.push_back(Configuracao);
			}
		}


		//Derecha:  if (xC2-xE2)>0 espaço es ((xC2-xE2),yE2-yE1,zE2-zE1) v: (xC2,yE1,zE1)
		if ((E.Get_x2()-x2)>0)
		{
			if (0<min(min((E.Get_x2()-x2),dimy),dimz) )
			{

				CONFIGURACAO Configuracao(this, E.Get_Id(),x2,E.Get_y1(),E.Get_z1(),x2+(E.Get_x2()-x2),E.Get_y1()+dimy,E.Get_z1()+dimz,E.Get_Tipo(),0,E.Get_orig());
				Configuracao.PonerMedidas((E.Get_x2()-x2)/((E.Get_x2()-E.Get_x1())/E.Get_dx()),E.Get_dy(),E.Get_dz());

				lista_temp.push_back(Configuracao);
			}
		}

	}

}
//Habría que cambiarla para que haga busqueda binaria
//FALTA
void CONTAINER::InsertarOrden(std::list<SPACE> &lista_vieja,SPACE &Espacio)
{
	/*if (Espacio.Get_dx() * Espacio.Get_dy() * Espacio.Get_dz() != Espacio.Get_Volumen())
		printf("no cuadra volumen");*/
	if (Espacio.Get_x2() - Espacio.Get_x1() < m_dimension_menor || Espacio.Get_y2() - Espacio.Get_y1() < m_dimension_menor || Espacio.Get_z2() - Espacio.Get_z1() < m_dimension_menor)
		int kjk = 9;
	if (Espacio.Get_x1() == Espacio.Get_x2())
		return;
	if (Espacio.Get_y1() == Espacio.Get_y2())
		return;
	if (Espacio.Get_z1() == Espacio.Get_z2())
		return;
	//Por si solamente hay uno
	if (lista_vieja.size()==0)
	{
		lista_vieja.push_back(Espacio);
		return;
	}

	std::list<SPACE> ::iterator itl;
	for (itl=lista_vieja.begin();itl!=lista_vieja.end();itl++)
	{
		if ((*itl).Get_Volumen()>Espacio.Get_Volumen())
		{
			lista_vieja.insert(itl,Espacio);
			return;
		}
	}
	//Si no hay ninguno más pequeño al final
	lista_vieja.push_back(Espacio);
	//if (Espacio.Get_y2() != 233)
	//	printf("spacemal");
}
//Mirar que no es igual a una que estaba e insertar en orden
//Habría que cambiarla para que haga busqueda binaria
//FALTA
void CONTAINER::InsertarOrdenUnica(std::list<SPACE> &lista_vieja,SPACE &Espacio)
{
	//Por si solamente hay uno
	if (lista_vieja.size()==0)
	{
		lista_vieja.push_back(Espacio);
		return;
	}

	std::list<SPACE> ::iterator itl;
	for (itl=lista_vieja.begin();itl!=lista_vieja.end();itl++)
	{
		if ((*itl).Get_Volumen()>=Espacio.Get_Volumen())
		{
			//Si esta incluida no la meto
			if (Espacio.Incluido((*itl)))
				return;
			lista_vieja.insert(itl,Espacio);
			return;
		}
	}
	//Si no hay ninguno más pequeño al final
	lista_vieja.push_back(Espacio);
}
void CONTAINER::EliminarInclusiones()
{
	std::list<SPACE> ::iterator itl,itl2;
/*	for (itl=m_Spaces.begin();itl!=m_Spaces.end();itl++)
	{
		SPACE E=(*itl);
	}
	
	*/	std::list < SPACE > ::iterator itfin=m_Spaces.end();
	for (itl=m_Spaces.begin();itl!=itfin;)
	{
//		SPACE kk=(*itl);
		itl2=itl;
		itl2++;
		if (itl2==itfin)
			break;
		bool borrado=false;
		for (;itl2!=itfin;itl2++)
		{
			
			if ((*itl).Incluido((*itl2))==true)
			{
				//Me devuelve el puntero que apunta al siguiente
				//por tanto le tengo que quita algo
				borrado=true;
				itl=m_Spaces.erase(itl);
				break;
			}
		}
		if (borrado==true) 
			++itl;
	}
}
void CONTAINER::EliminarInclusionesNuevos(std::list < SPACE > &Lista)
{
	std::list<SPACE> ::iterator itl,itl2;
	for (itl=Lista.begin();itl!=Lista.end();itl++)
	{
		itl2=itl;
		itl2++;
		//entra = false;
		if (itl2==Lista.end())
			break;
		/*bool borrado = false;*/
		for (;itl2!=Lista.end();itl2++)
		{

//			No me hace falta porque esta ordenada y seguro que 
//			no se da 
//			if ((*itl2).Get_Volumen()<(*itl).Get_Volumen()) 
//				continue;
//			if (IncluidoFirstSecond((*itl).Get_x1(),(*itl).Get_y1(),(*itl).Get_z1(),(*itl).Get_x2(),(*itl).Get_y2(),(*itl).Get_z2(),(*itl2).Get_x1(),(*itl2).Get_y1(),(*itl2).Get_z1(),(*itl2).Get_x2(),(*itl2).Get_y2(),(*itl2).Get_z2())==true)
			if ((*itl).Incluido(*itl2) == true)
			{
				//Me devuelve el puntero que apunta al siguiente
				//por tanto le tengo que quita algo
				/*borrado = true;*/
				itl = Lista.erase(itl);
				if (Lista.size() != 0)
				{
					if (itl != Lista.begin())
						itl--;
				}
				else return;
				break;
			}
		}
		/*if (borrado==false)
		    ++itl;*/
	}
}

void CONTAINER::EliminarInclusionesListaAntigua(std::list<SPACE>& lista_Viejos, std::list <SPACE >& Lista)
{
	std::list<SPACE> ::iterator itl;
	std::list<SPACE> ::reverse_iterator itl2;
	bool entra = false;
	for (itl = Lista.begin(); itl != Lista.end();itl++)
	{
		//		SPACE kk=(*itl);
	/*	entra = false;*/
	/*	bool borrado = false;*/
		for (itl2 = lista_Viejos.rbegin(); itl2 != lista_Viejos.rend(); itl2++)
		{
			//			SPACE kk2=(*itl2);
			if ((*itl2).Get_Volumen() < (*itl).Get_Volumen())
			{
				break;
			}
			if ((*itl).Incluido((*itl2)) == true)
			{
				/*if (Lista.size() == 1)
					int kl = 1;*/
				//			if (IncluidoFirstSecond((*itl).Get_x1(),(*itl).Get_y1(),(*itl).Get_z1(),(*itl).Get_x2(),(*itl).Get_y2(),(*itl).Get_z2(),(*itl2).Get_x1(),(*itl2).Get_y1(),(*itl2).Get_z1(),(*itl2).Get_x2(),(*itl2).Get_y2(),(*itl2).Get_z2())==true)
				//			{

							//Si esta incluido termina 
							//Si esta incluido termina 
				itl = Lista.erase(itl);
				/*borrado = true;*/
				/*if (Lista.size() != 0)
				{*/
				/*if (itl != Lista.begin())
					itl--;
				else
					entra = true;*/
				if (Lista.size() != 0)
				{
					if (itl != Lista.begin())
						itl--;
				}
				else return;
				/*}
				else return;*/

				break;
			}
		}
		/*if (borrado == false)
			++itl;*/
	}
}
/*
bool SPACE::Incluido(SPACE &E)
{	
	if (m_x1>= E.Get_x1() && m_x2<=E.Get_x2() 
		&& m_y1>= E.Get_y1() && m_y2<=E.Get_y2() 
		&& m_z1>= E.Get_z1() && m_z2<=E.Get_z2())
		return true;
	return false;
}*/

bool CONTAINER::ComprobarTodosPosibleMC(std::list< std::pair<int, std::list<CONFIGURACAO> > > &lista)
{
	std::list< std::pair<int, std::list<CONFIGURACAO> > >::iterator it;

	std::list< CONFIGURACAO >::iterator itB1;
	std::list< SPACE >::iterator itB3;
	//Comprobar que todas tenga el numero de piezas que pone
	for (int ik=0;ik<m_Q;ik++)
	{	

		int utili=m_Pieces[ik].Get_Num();
		if (m_Pieces[ik].Get_Num()>m_Pieces[ik].Get_q())
			return true;
		
		int kk=0;
		for (it=lista.begin();it!=lista.end();it++)
		{
			for(itB1=(*it).second.begin();itB1!=(*it).second.end();itB1++)
			{
			CONFIGURACAO b=(*itB1);
			int kk3=m_Pieces[(*itB1).Get_Id()].Get_x();
			int kk33=m_Pieces[(*itB1).Get_Id()].Get_y();
			int kk333=m_Pieces[(*itB1).Get_Id()].Get_z();
				if ((*itB1).Get_Id()==ik)
					kk+=(*itB1).Get_Num();
				if (((*itB1).Get_x2()-(*itB1).Get_x1())%m_Pieces[(*itB1).Get_Id()].Get_x()!=0)
					return true;
				if (((*itB1).Get_y2()-(*itB1).Get_y1())%m_Pieces[(*itB1).Get_Id()].Get_y()!=0)
					return true;
				if (((*itB1).Get_z2()-(*itB1).Get_z1())%m_Pieces[(*itB1).Get_Id()].Get_z()!=0)
					return true;
			}
		}
		if (utili!=kk)
		{
			printf("Aqui esta mal utili %d kk %d",utili, kk);
			return true;
		}
	}
	int val=0;
	int val2=0;
	int val3=0;
	for (it=lista.begin();it!=lista.end();it++)
	{
		val3=0;
		for(itB1=(*it).second.begin();itB1!=(*it).second.end();itB1++)
		{
			CONFIGURACAO b1=(*itB1);
		val+=(((*itB1).Get_x2()-(*itB1).Get_x1())*((*itB1).Get_y2()-(*itB1).Get_y1())*((*itB1).Get_z2()-(*itB1).Get_z1()));
		val2+=(*itB1).Get_Volumen();
		val3+=(*itB1).Get_Volumen();
		if((*itB1).Get_x1()>=0 && m_X>=(*itB1).Get_x2() &&
		   (*itB1).Get_y1()>=0 && m_Y>=(*itB1).Get_y2()  &&
		   (*itB1).Get_z1()>=0 && m_Z>=(*itB1).Get_z2() && (*itB1).Get_Num()<=m_Pieces[(*itB1).Get_Id()].Get_q() )
			continue;
		return true;

		}
		if (val3!=(*it).first)
			return true;
	}
	if (val!=m_total_volumen_ocupado)
		return true;

	return false;
}

void CONTAINER::VerificarSolucionMC(std::list< std::pair<int, std::list<CONFIGURACAO> > > &lista)
{
	return;
	std::list< std::pair<int, std::list<CONFIGURACAO> > > ::iterator it;
	for (it=lista.begin();it!=lista.end() ;it++)
	{
		if (ComprobarConfiguracaosNoIntersectan((*it).second)==true) 
		{

			printf("Problemas con las configuracaos, se cortan");
			exit(3);
		}

	}
	if (ComprobarTodosPosibleMC(lista)==true)
	{
		printf("Iter %d,Tamano es %d %d,Un espacio o una configuracao tiene mal las coordenadas o pone más piezas de las permitidas",m_iter_actual,m_Spaces.size(),m_Configuracaos.size());
		for(int i=0;;)
		exit(2);
		
	}

}
void CONTAINER::VerificarSolucion(std::list<CONFIGURACAO> &lista)
{
	return;
	if (m_Verificar == false)
		return;
	m_iteraciones++;
	if (ComprobarDistBien(lista) == true)
		printf("mal");
	if (ComprobarConfiguracaosNoIntersectan(lista)==true) 
	{
		if (ComprobarTodosPosible(lista) == true)
			printf("Tamano es %d %d,Un espacio o una configuracao tiene mal las coordenadas o pone mas piezas de las permitidas\n", m_Spaces.size(), m_Configuracaos.size());
		if (ComprobarConfiguracaosNoIntersectanSpaces(lista) == true)
			printf("Problemas con las configuracaos, se cortan con los espacios vacios\n");
		printf("Problemas con las configuracaos, se cortan");
		/*for (int i = 0;;);*/
		exit(3);
	}

	if (ComprobarTodosPosible(lista)==true)
	{
		DibujarOpenGL(lista);
		/*for(int i=0;;)*/
		printf("Tamano es %d %d,Un espacio o una configuracao tiene mal las coordenadas o pone más piezas de las permitidas",m_Spaces.size(),m_Configuracaos.size());
		exit(2);
		
	}
	if (ComprobarConfiguracaosNoIntersectanSpaces(lista)==true) 
	{
		/*for(int i=0;;)*/

		printf("Problemas con las configuracaos, se cortan con los espacios vacios");
		exit(4);
	}
	if (m_full_supported==true && ComprobarFullSupport(lista) == false)
	{
		/*for (int i = 0;;)*/
			printf("Hay piezas sin soporte");
		exit(5);
	}
}
void CONTAINER::ComprobarPedidos()
{
	
	bool flag = true;
	std::vector<int> w;
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
	std::list<CONFIGURACAO>::iterator ittt;
	for (ittt = m_Configuracaos.begin(); ittt != m_Configuracaos.end(); ittt++)
	{
		w[(*ittt).Get_Id()] -= (*ittt).Get_Num();
	}
	for (int j = 0; j < m_Q; j++)
	{
		if (w[j] > 0)
		{
			printf("comprov caja: %d cuantas: %d\n", j, w[j]);
			flag = false;
		}
	}

	int vol = m_total_volumen_cs_ocupado;

	for (int i = 0; i < m_num_pedidos; i++)
	{
		if (m_Pedidos[i].Get_complete() == true)
		{
			vol -= m_Pedidos[i].Get_Volumen();
			/*printf("%d\n", vol);*/
		}
	}
	if (vol != 0)
	{
		printf("m_pedidos_mal\n");
		flag = false;
	}

	vol = m_total_volumen_cs_ocupado;
	std::set<int> indices;
	for (int i = 0; i < m_num_pedidos; i++)
		indices.insert(i);
	for (int k = 0; k < m_Pedidos_candidatos.size(); k++)
	{
		if (m_Pedidos_candidatos[k].Get_complete() == true)
			vol -= m_Pedidos_candidatos[k].Get_Volumen();
		indices.erase(m_Pedidos_candidatos[k].Get_Id());
	}
	std::set<int>::iterator its;
	for (its=indices.begin(); its!=indices.end(); its++)
	{
		if (m_Pedidos[*its].Get_complete() == true)
			vol -= m_Pedidos[*its].Get_Volumen();
	}
	if (vol != 0)
	{
		printf("m_pedidos_candidatos_mal\n");
		flag = false;
	}

	if (ComprobarConfiguracaosNoIntersectan(m_Configuracaos) == true)
	{
		printf("conf intersectan");
		flag == false;
	}

	if (flag == false)
		exit(12);
}
bool CONTAINER::ComprobarConfiguracaosNoIntersectan(std::list<CONFIGURACAO> &lista)
{
	if (m_Verificar == false)
		return false;
	m_iteraciones++;
	std::list< CONFIGURACAO >::iterator itB1,itB2,itB3;
	for(itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		itB2=itB1;
		itB2++;
		if (itB2==lista.end()) break;
		for(itB3=itB2;itB3!=lista.end();itB3++)
		{
			if( (*itB1).Get_x1()>=(*itB3).Get_x2() || (*itB3).Get_x1()>=(*itB1).Get_x2() )
				continue;
			if( (*itB1).Get_y1()>=(*itB3).Get_y2() || (*itB3).Get_y1()>=(*itB1).Get_y2() )
				continue;	
			if( (*itB1).Get_z1()>=(*itB3).Get_z2() || (*itB3).Get_z1()>=(*itB1).Get_z2() )
				continue;
			CONFIGURACAO E1=(*itB1);
			CONFIGURACAO E2=(*itB3);
			/*printf("mierda Se cortan dos configuracaos");
			for (int i=0;;);*/
//				
			return true;

		}
	}
	return false;
}
void CONTAINER::ComprobarEspaciosNoIncluidos(std::list<SPACE>& lista)
{
	std::list<SPACE>::iterator it, itfin = lista.end(), it2;
	for (it = lista.begin(); it != itfin; it++)
	{
		it2 = it;
		it2++;
		for (; it2 != itfin; it2++)
		{
			if ((*it).Get_Volumen() > (*it2).Get_Volumen())
			{
				printf("espacios mal ordenados");
				exit(7);
			}
			if ((*it).Incluido(*it2) == true)
			{
				printf("no borra espacios bien");
				exit(6);
			}
		}
	}
}
bool CONTAINER::ComprobarTodosPosible(std::list<CONFIGURACAO> &lista)
{
	if (m_Verificar == false)
		return false;
	std::list< CONFIGURACAO >::iterator itB1;
	std::list< SPACE >::iterator itB3;
	//Comprobar que todas tenga el numero de piezas que pone
	for (int ik=0;ik<m_Q;ik++)
	{	
		int utili=m_Pieces[ik].Get_Num();
		int kk=0;
		for(itB1=lista.begin();itB1!=lista.end();itB1++)
		{
			if ((*itB1).Get_Id()==ik)
				kk+=(*itB1).Get_Num();
		}
		if (utili != kk)
		{
			printf("5");
			return true;
		}
	}
	//sumo todas las que he puesto de una pieza y que no sobrepasen las que teni
	for (int ik=0;ik<m_Q;ik++)
	{	
		int utili=0;
		for(itB1=lista.begin();itB1!=lista.end();itB1++)
		{
			if ((*itB1).Get_Id()==ik)
				utili+=(*itB1).Get_Num();
		}
		if (utili > m_Pieces[ik].Get_q())
		{
			printf("4");
			return true;
		}
	}
	int val=0;
	int val2=0;
	for(itB1=lista.begin();itB1!=lista.end();itB1++)
	{
			CONFIGURACAO b1=(*itB1);
		val+=(((*itB1).Get_x2()-(*itB1).Get_x1())*((*itB1).Get_y2()-(*itB1).Get_y1())*((*itB1).Get_z2()-(*itB1).Get_z1()));
		val2+=(*itB1).Get_Volumen();
		if((*itB1).Get_x1()>=0 && m_X>=(*itB1).Get_x2() &&
		   (*itB1).Get_y1()>=0 && m_Y>=(*itB1).Get_y2()  &&
		   (*itB1).Get_z1()>=0 && m_Z>=(*itB1).Get_z2() && (*itB1).Get_Num()<=m_Pieces[(*itB1).Get_Id()].Get_q() )
			continue;
		printf("3");
		return true;


	}
	//if (val != val2)
	//	printf("aqui");
	if (val2 != m_total_volumen_ocupado)
	{
		printf("2");
		return true;
	}
	int contador = 0;
	for(itB3=m_Spaces.begin();itB3!=m_Spaces.end();itB3++)
	{
			SPACE b2=(*itB3);
			contador++;

		if((*itB3).Get_x1()>=0 && m_X>=(*itB3).Get_x2() &&
		   (*itB3).Get_y1()>=0 && m_Y>=(*itB3).Get_y2()  &&
		   (*itB3).Get_z1()>=0 && m_Z>=(*itB3).Get_z2() )
		   continue;
		printf("1");
		return true;

	}

	return false;
}
bool CONTAINER::ComprobarLimites(CONFIGURACAO &itB1)
{
	return 0;
	if ((itB1).Get_x1() >= 0 && m_X >= (itB1).Get_x2() &&
		(itB1).Get_y1() >= 0 && m_Y >= (itB1).Get_y2() &&
		(itB1).Get_z1() >= 0 && m_Z >= (itB1).Get_z2() && (itB1).Get_Num() <= m_Pieces[(itB1).Get_Id()].Get_q())
		return false;
	else
	{
		printf("1");
		return false;
	}
}
bool CONTAINER::ComprobarConfiguracaosNoIntersectanSpaces(std::list<CONFIGURACAO> &lista)
{
	//return false;
	if (m_Verificar == false)
		return false;
	std::list< CONFIGURACAO >::iterator itB1;
	std::list< SPACE >::iterator itB3;
	for(itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		for(itB3=m_Spaces.begin();itB3!=m_Spaces.end();itB3++)
		{
//			BLOQUE b1=(*itB1);
//			BLOQUE b2=(*itB2);
			if ((*itB3).Get_Flag()==true) continue;
			if( (*itB1).Get_x1()>=(*itB3).Get_x2() || (*itB3).Get_x1()>=(*itB1).Get_x2() )
				continue;
			if( (*itB1).Get_y1()>=(*itB3).Get_y2() || (*itB3).Get_y1()>=(*itB1).Get_y2() )
				continue;	
			if( (*itB1).Get_z1()>=(*itB3).Get_z2() || (*itB3).Get_z1()>=(*itB1).Get_z2() )
				continue;
			CONFIGURACAO C=(*itB1);
			SPACE E=(*itB3);
			return true;

		}
	}
	return false;
}
bool CONTAINER::ComprobarDistBien(std::list<CONFIGURACAO>& lista)
{
	return false;
	if (m_Verificar == false)
		return false;
	std::list< CONFIGURACAO >::iterator itB1;
	for (itB1 = lista.begin(); itB1 != lista.end(); itB1++)
	{
		if ((*itB1).Get_Distancia().GetPrimero() < 0 || (*itB1).Get_Distancia().GetSegundo() < 0 || (*itB1).Get_Distancia().GetTercero() < 0)
			return true;
	}
	return false;
}
bool CONTAINER::ComprobarConfiguracaosNoIntersectanSpacesMov(std::list<CONFIGURACAO> &lista, std::list<SPACE> &lista_es)
{
	//return false;
	if (m_Verificar == false)
		return false;
	std::list< CONFIGURACAO >::iterator itB1;
	std::list< SPACE >::iterator itB3;
	for (itB1 = lista.begin(); itB1 != lista.end(); itB1++)
	{
		for (itB3 = lista_es.begin(); itB3 != lista_es.end(); itB3++)
		{
			//			BLOQUE b1=(*itB1);
			//			BLOQUE b2=(*itB2);
			if ((*itB3).Get_Flag() == true) continue;
			if ((*itB1).Get_x1() >= (*itB3).Get_x2() || (*itB3).Get_x1() >= (*itB1).Get_x2())
				continue;
			if ((*itB1).Get_y1() >= (*itB3).Get_y2() || (*itB3).Get_y1() >= (*itB1).Get_y2())
				continue;
			if ((*itB1).Get_z1() >= (*itB3).Get_z2() || (*itB3).Get_z1() >= (*itB1).Get_z2())
				continue;
			CONFIGURACAO C = (*itB1);
			SPACE E = (*itB3);
			return true;

		}
	}
	return false;
}
bool CONTAINER::ComprobarFullSupport(std::list<CONFIGURACAO> &lista)
{
	if (m_full_supported == false)
		return true;
	if (m_Verificar == false)
		return true;
	int area;
	bool det, del, izq,dch;
	std::list<CONFIGURACAO>::iterator it,it2;
	for (it = lista.begin(); it != lista.end(); it++)
	{
		if ((*it).Get_z1() == 0)
			continue;
		area = ((*it).Get_y2() - (*it).Get_y1())*((*it).Get_x2() - (*it).Get_x1());
		for (it2 = lista.begin(); it2 != lista.end(); it2++)
		{
			if ((*it2).Get_z2() != (*it).Get_z1())
				continue;
			if ((*it2).Get_x2() <= (*it).Get_x1() || (*it2).Get_x1() >= (*it).Get_x2())
				continue;
			if ((*it2).Get_y2() <= (*it).Get_y1() || (*it2).Get_y1() >= (*it).Get_y2())
				continue;
			det = (*it2).Get_y2() > (*it).Get_y2(); //true si sobresale por detrás
			del = (*it2).Get_y1() < (*it).Get_y1(); //true si sobresale por delante
			izq = (*it2).Get_x1() < (*it).Get_x1(); //true si sobresale por la izquierda
			dch = (*it2).Get_x2() > (*it).Get_x2(); //true si sobresale por la derecha

			if (det == false && del == false && izq == false && dch == false) //Toda la it2 está dentro y por tanto se resta su area
				area = area - ((*it2).Get_y2() - (*it2).Get_y1())*((*it2).Get_x2() - (*it2).Get_x1()); 
			if (det == true && del == false && izq == false && dch == false)//Sale solo por detras
				area = area - ((*it2).Get_x2() - (*it2).Get_x1())*((*it).Get_y2() - (*it2).Get_y1()); 
			if (det == false && del == true && izq == false && dch == false)//Sale solo por delante
				area = area - ((*it2).Get_x2() - (*it2).Get_x1())*((*it2).Get_y2() - (*it).Get_y1());
			if (det == false && del == false && izq == true && dch == false)//Sale solo por la izquierda
				area = area - ((*it2).Get_x2() - (*it).Get_x1())*((*it2).Get_y2() - (*it2).Get_y1());
			if (det == false && del == false && izq == false && dch == true)//Sale solo por la derecha
				area = area - ((*it).Get_x2() - (*it2).Get_x1())*((*it2).Get_y2() - (*it2).Get_y1());
			if (det == true && del == true && izq == false && dch == false)//Detras y delante
				area = area - ((*it).Get_y2() - (*it).Get_y1())*((*it2).Get_x2() - (*it2).Get_x1());
			if (det == true && del == false && izq == true && dch == false)//Detras e izquierda
				area = area - ((*it).Get_y2() - (*it2).Get_y1())*((*it2).Get_x2() - (*it).Get_x1());
			if (det == true && del == false && izq == false && dch == true)//Detras y derecha
				area = area - ((*it).Get_y2() - (*it2).Get_y1())*((*it).Get_x2() - (*it2).Get_x1());
			if (det == false && del == true && izq == true && dch == false)//Delante e izquierda
				area = area - ((*it2).Get_y2() - (*it).Get_y1())*((*it2).Get_x2() - (*it).Get_x1());
			if (det == false && del == false && izq == true && dch == true)//izquierda y derecha
				area = area - ((*it2).Get_y2() - (*it2).Get_y1())*((*it).Get_x2() - (*it).Get_x1());
			if (det == false && del == true && izq == false && dch == true)//Delante y derecha
				area = area - ((*it2).Get_y2() - (*it).Get_y1())*((*it).Get_x2() - (*it2).Get_x1());
			if (det == true && del == true && izq == true && dch == false)
				area = area - ((*it).Get_y2() - (*it).Get_y1())*((*it2).Get_x2() - (*it).Get_x1());
			if (det == true && del == true && izq == false && dch == true)
				area = area - ((*it).Get_y2() - (*it).Get_y1())*((*it).Get_x2() - (*it2).Get_x1());
			if (det == true && del == false && izq == true && dch == true)
				area = area - ((*it).Get_y2() - (*it2).Get_y1())*((*it).Get_x2() - (*it).Get_x1());
			if (det == false && del == true && izq == true && dch == true)
				area = area - ((*it2).Get_y2() - (*it).Get_y1())*((*it).Get_x2() - (*it).Get_x1());
			if (det == true && del == true && izq == true && dch == true)
				area = 0;
		}
		if (area > 0)
		{
			SetDibujar(true);
			DibujarOpenGL(lista);
			return false;
		}
		/*if (area < 0)
		{
			SetDibujar(true);
			DibujarOpenGL(lista);
			printf("Corregir ComprobarFullSupport");
			for (int i = 0;;);
		}*/
	}
	return true;
}

bool CONTAINER::ComprobarFullSupportUno(CONFIGURACAO &it, std::list<CONFIGURACAO> &lista)
{
	if (m_full_supported == false)
		return true;
	int area;
	bool det, del, izq, dch;
	std::list<CONFIGURACAO>::iterator it2;
	if ((it).Get_z1() == 0)
		return true;
	area = ((it).Get_y2() - (it).Get_y1())*((it).Get_x2() - (it).Get_x1());
	for (it2 = lista.begin(); it2 != lista.end(); it2++)
	{
		if ((*it2).Get_z2() != (it).Get_z1())
			continue;
		if ((*it2).Get_x2() <= (it).Get_x1() || (*it2).Get_x1() >= (it).Get_x2())
			continue;
		if ((*it2).Get_y2() <= (it).Get_y1() || (*it2).Get_y1() >= (it).Get_y2())
			continue;
		det = (*it2).Get_y2() > (it).Get_y2(); //true si sobresale por detrás
		del = (*it2).Get_y1() < (it).Get_y1(); //true si sobresale por delante
		izq = (*it2).Get_x1() < (it).Get_x1(); //true si sobresale por la izquierda
		dch = (*it2).Get_x2() > (it).Get_x2(); //true si sobresale por la derecha

		if (det == false && del == false && izq == false && dch == false) //Toda la it2 está dentro y por tanto se resta su area
			area = area - ((*it2).Get_y2() - (*it2).Get_y1())*((*it2).Get_x2() - (*it2).Get_x1());
		if (det == true && del == false && izq == false && dch == false)//Sale solo por detras
			area = area - ((*it2).Get_x2() - (*it2).Get_x1())*((it).Get_y2() - (*it2).Get_y1());
		if (det == false && del == true && izq == false && dch == false)//Sale solo por delante
			area = area - ((*it2).Get_x2() - (*it2).Get_x1())*((*it2).Get_y2() - (it).Get_y1());
		if (det == false && del == false && izq == true && dch == false)//Sale solo por la izquierda
			area = area - ((*it2).Get_x2() - (it).Get_x1())*((*it2).Get_y2() - (*it2).Get_y1());
		if (det == false && del == false && izq == false && dch == true)//Sale solo por la derecha
			area = area - ((it).Get_x2() - (*it2).Get_x1())*((*it2).Get_y2() - (*it2).Get_y1());
		if (det == true && del == true && izq == false && dch == false)//Detras y delante
			area = area - ((it).Get_y2() - (it).Get_y1())*((*it2).Get_x2() - (*it2).Get_x1());
		if (det == true && del == false && izq == true && dch == false)//Detras e izquierda
			area = area - ((it).Get_y2() - (*it2).Get_y1())*((*it2).Get_x2() - (it).Get_x1());
		if (det == true && del == false && izq == false && dch == true)//Detras y derecha
			area = area - ((it).Get_y2() - (*it2).Get_y1())*((it).Get_x2() - (*it2).Get_x1());
		if (det == false && del == true && izq == true && dch == false)//Delante e izquierda
			area = area - ((*it2).Get_y2() - (it).Get_y1())*((*it2).Get_x2() - (it).Get_x1());
		if (det == false && del == false && izq == true && dch == true)//izquierda y derecha
			area = area - ((*it2).Get_y2() - (*it2).Get_y1())*((it).Get_x2() - (it).Get_x1());
		if (det == false && del == true && izq == false && dch == true)//Delante y derecha
			area = area - ((*it2).Get_y2() - (it).Get_y1())*((it).Get_x2() - (*it2).Get_x1());
		if (det == true && del == true && izq == true && dch == false)
			area = area - ((it).Get_y2() - (it).Get_y1())*((*it2).Get_x2() - (it).Get_x1());
		if (det == true && del == true && izq == false && dch == true)
			area = area - ((it).Get_y2() - (it).Get_y1())*((it).Get_x2() - (*it2).Get_x1());
		if (det == true && del == false && izq == true && dch == true)
			area = area - ((it).Get_y2() - (*it2).Get_y1())*((it).Get_x2() - (it).Get_x1());
		if (det == false && del == true && izq == true && dch == true)
			area = area - ((*it2).Get_y2() - (it).Get_y1())*((it).Get_x2() - (it).Get_x1());
		if (det == true && del == true && izq == true && dch == true)
			area = 0;
	}
	if (area > 0)
	{
		DibujarOpenGL(lista);
		return false;
	}
	if (area < 0)
	{
		printf("Corregir ComprobarFullSupport");
		for (int i = 0;;);
	}
	return true;
}
bool MOVIMIENTO::ComprobarFullSupport(CONFIGURACAO &it,std::list<CONFIGURACAO> &lista)
{
	if (m_Container -> Get_Full_Supported() == false)
		return true;
	int area;
	bool det, del, izq, dch;
	std::list<CONFIGURACAO>::iterator it2;
    if ((it).Get_z1() == 0)
	    return true;
	area = ((it).Get_y2() - (it).Get_y1())*((it).Get_x2() - (it).Get_x1());
	for (it2 = lista.begin(); it2 != lista.end(); it2++)
	{
		if ((*it2).Get_z2() != (it).Get_z1())
			continue;
		if ((*it2).Get_x2() <= (it).Get_x1() || (*it2).Get_x1() >= (it).Get_x2())
			continue;
		if ((*it2).Get_y2() <= (it).Get_y1() || (*it2).Get_y1() >= (it).Get_y2())
			continue;
		det = (*it2).Get_y2() > (it).Get_y2(); //true si sobresale por detrás
		del = (*it2).Get_y1() < (it).Get_y1(); //true si sobresale por delante
		izq = (*it2).Get_x1() < (it).Get_x1(); //true si sobresale por la izquierda
		dch = (*it2).Get_x2() > (it).Get_x2(); //true si sobresale por la derecha

		if (det == false && del == false && izq == false && dch == false) //Toda la it2 está dentro y por tanto se resta su area
			area = area - ((*it2).Get_y2() - (*it2).Get_y1())*((*it2).Get_x2() - (*it2).Get_x1());
		if (det == true && del == false && izq == false && dch == false)//Sale solo por detras
			area = area - ((*it2).Get_x2() - (*it2).Get_x1())*((it).Get_y2() - (*it2).Get_y1());
		if (det == false && del == true && izq == false && dch == false)//Sale solo por delante
			area = area - ((*it2).Get_x2() - (*it2).Get_x1())*((*it2).Get_y2() - (it).Get_y1());
		if (det == false && del == false && izq == true && dch == false)//Sale solo por la izquierda
			area = area - ((*it2).Get_x2() - (it).Get_x1())*((*it2).Get_y2() - (*it2).Get_y1());
		if (det == false && del == false && izq == false && dch == true)//Sale solo por la derecha
			area = area - ((it).Get_x2() - (*it2).Get_x1())*((*it2).Get_y2() - (*it2).Get_y1());
		if (det == true && del == true && izq == false && dch == false)//Detras y delante
			area = area - ((it).Get_y2() - (it).Get_y1())*((*it2).Get_x2() - (*it2).Get_x1());
		if (det == true && del == false && izq == true && dch == false)//Detras e izquierda
			area = area - ((it).Get_y2() - (*it2).Get_y1())*((*it2).Get_x2() - (it).Get_x1());
		if (det == true && del == false && izq == false && dch == true)//Detras y derecha
			area = area - ((it).Get_y2() - (*it2).Get_y1())*((it).Get_x2() - (*it2).Get_x1());
		if (det == false && del == true && izq == true && dch == false)//Delante e izquierda
			area = area - ((*it2).Get_y2() - (it).Get_y1())*((*it2).Get_x2() - (it).Get_x1());
		if (det == false && del == false && izq == true && dch == true)//Izquierda y derecha
			area = area - ((*it2).Get_y2() - (*it2).Get_y1())*((it).Get_x2() - (it).Get_x1());
		if (det == false && del == true && izq == false && dch == true)//Delante y derecha
			area = area - ((*it2).Get_y2() - (it).Get_y1())*((it).Get_x2() - (*it2).Get_x1());
		if (det == true && del == true && izq == true && dch == false)
			area = area - ((it).Get_y2() - (it).Get_y1())*((*it2).Get_x2() - (it).Get_x1());
		if (det == true && del == true && izq == false && dch == true)
			area = area - ((it).Get_y2() - (it).Get_y1())*((it).Get_x2() - (*it2).Get_x1());
		if (det == true && del == false && izq == true && dch == true)
			area = area - ((it).Get_y2() - (*it2).Get_y1())*((it).Get_x2() - (it).Get_x1());
		if (det == false && del == true && izq == true && dch == true)
			area = area - ((*it2).Get_y2() - (it).Get_y1())*((it).Get_x2() - (it).Get_x1());
		if (det == true && del == true && izq == true && dch == true)
			area = 0;
	}
	if (area > 0)
	{
		//DibujarOpenGL(lista);
		return false;
	}
	if (area < 0)
	{
		printf("Corregir ComprobarFullSupport");
		for (int i = 0;;);
	}
return true;
}
bool CONTAINER::ComprobarConfiguracaosNoIntersectanSpaces(std::list<CONFIGURACAO> &lista,std::list<SPACE> &lista_espacios)
{

	std::list< CONFIGURACAO >::iterator itB1;
	std::list< SPACE >::iterator itB3;
	for(itB1=lista.begin();itB1!=lista.end();itB1++)
	{
		for(itB3=lista_espacios.begin();itB3!=lista_espacios.end();itB3++)
		{
			CONFIGURACAO b1=(*itB1);
			SPACE b2=(*itB3);
			if ((*itB3).Get_Flag()==true) continue;
			if( (*itB1).Get_x1()>=(*itB3).Get_x2() || (*itB3).Get_x1()>=(*itB1).Get_x2() )
				continue;
			if( (*itB1).Get_y1()>=(*itB3).Get_y2() || (*itB3).Get_y1()>=(*itB1).Get_y2() )
				continue;	
			if( (*itB1).Get_z1()>=(*itB3).Get_z2() || (*itB3).Get_z1()>=(*itB1).Get_z2() )
				continue;
			CONFIGURACAO C=(*itB1);
			SPACE E=(*itB3);
			return true;

		}
	}
	return false;
}
void CONTAINER:: EscribirSolucion()
{
	FILE *fin3;
	fin3=fopen("Result2.txt","a+");
	fprintf(fin3,"%d\n",m_max_total_volumen_ocupado);
	std::list< CONFIGURACAO > ::iterator it;
	for (it=m_Configuracaos.begin();it!=m_Configuracaos.end();it++)
	{
		fprintf(fin3,"(%d %d) (%d %d) Pieza %d \n",(*it).Get_x1(),(*it).Get_y1(),(*it).Get_x2(),(*it).Get_y2(),(*it).Get_Id());
	}
	fclose(fin3);
}
void CONTAINER:: EscribirSolucion(std::list<CONFIGURACAO> lista)
{
	FILE *fin3;
	fin3=fopen("Result2.txt","a+");
	fprintf(fin3,"%d\n",m_max_total_volumen_ocupado);
	std::list< CONFIGURACAO > ::iterator it;
	for (it=lista.begin();it!=lista.end();it++)
	{
		fprintf(fin3,"(%d %d) (%d %d) Pieza %d \n",(*it).Get_x1(),(*it).Get_y1(),(*it).Get_x2(),(*it).Get_y2(),(*it).Get_Id());
	}
	fclose(fin3);
}
void CONTAINER:: EscribirSolucionLatex(std::list<CONFIGURACAO> lista)
{
	
	m_tipo_gravedad=2;
	lista.sort();

	FILE *fin3;
	fin3=fopen("Result2.txt","a+");
	fprintf(fin3,"%d\n",m_max_total_volumen_ocupado);
	std::list< CONFIGURACAO > ::iterator itC;
//	float divide=20;
//	fprintf(fin3,"\\CubeThreeD[ A=%.3f,B=%.3f,C=%.3f](%.3f,%.3f,%.3f)\n",(double)m_Y/20,(double)m_X/20,(double)m_Z/20,(double)m_Y/20,(double)m_X/20,(double)m_Z/20);


	//Ahora las lineas que van de un lado al otro
	//Esto dibuja bloque enteros de piezas
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
		for (int register i=1;i<=(*itC).Get_dx();i++)
		{
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz();k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
//					CONFIGURACAO kk=(*itC);
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1(),(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x2(),(*itC).Get_y2(),(*itC).Get_z1()+k*sumok,(*itC).Get_Id());
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1(),(*itC).Get_x2(),(*itC).Get_y1()+j*sumoj,(*itC).Get_z2(),(*itC).Get_Id());
					fprintf(fin3," \\CubeThreeD[ A=\t%.3f\t,B=\t%.3f\t,C=\t%.3f\t](\t%.3f\t,\t%.3f\t,\t%.3f\t)\n",
						(double)sumoj/20,(double)sumoi/20,(double)sumok/20,
					(double)((*itC).Get_y1()+(double)((double)j-1)*sumoj+sumoj/2)/10,
					(double)((*itC).Get_x1()+(double)((double)i-1)*sumoi+sumoi/2)/10,
					(double)((*itC).Get_z1()+(double)((double)k-1)*sumok+sumok/2)/10);

				}
			}
		}
	}
	fclose(fin3);
}

void CONTAINER:: EscribirSolucionLatex2D(std::list<CONFIGURACAO> lista)
{
	
	m_tipo_gravedad=2;
	lista.sort();

	FILE *fin3;
	fin3=fopen("Result2.txt","a+");
	fprintf(fin3,"%d\n",m_total_volumen_ocupado);
	std::list< CONFIGURACAO > ::iterator itC;
//	float divide=20;
//	fprintf(fin3,"\\CubeThreeD[ A=%.3f,B=%.3f,C=%.3f](%.3f,%.3f,%.3f)\n",(double)m_Y/20,(double)m_X/20,(double)m_Z/20,(double)m_Y/20,(double)m_X/20,(double)m_Z/20);


	//Ahora las lineas que van de un lado al otro
	//Esto dibuja bloque enteros de piezas
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
		for (int register i=1;i<=(*itC).Get_dx();i++)
		{
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz();k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
//					CONFIGURACAO kk=(*itC);
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1(),(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x2(),(*itC).Get_y2(),(*itC).Get_z1()+k*sumok,(*itC).Get_Id());
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1(),(*itC).Get_x2(),(*itC).Get_y1()+j*sumoj,(*itC).Get_z2(),(*itC).Get_Id());
					fprintf(fin3," \\ \psframe[fillcolor=white,fillstyle=solid]    (%d,%d)(%d,%d)\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_x1()+(i)*sumoi,(*itC).Get_y1()+(j)*sumoj);
//						(double)sumoj/20,(double)sumoi/20,(double)sumok/20,,
//					(double)((*itC).Get_y1()+(double)(j-1)*sumoj+sumoj/2)/10,
//					(double)((*itC).Get_x1()+(double)(i-1)*sumoi+sumoi/2)/10,
//					(double)((*itC).Get_z1()+(double)(k-1)*sumok+sumok/2)/10);

				}
			}
		}
	}
	fclose(fin3);
}
void CONTAINER:: EscribirSolucionLatex2DMC(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista)
{
	

	FILE *fin3;
	fin3=fopen("Result2.txt","a+");
	fprintf(fin3,"%d\n",m_total_volumen_ocupado);
	std::list< std::pair< int , std::list<CONFIGURACAO> > > ::iterator itMC;
	std::list< CONFIGURACAO > ::iterator itC;
//	float divide=20;
//	fprintf(fin3,"\\CubeThreeD[ A=%.3f,B=%.3f,C=%.3f](%.3f,%.3f,%.3f)\n",(double)m_Y/20,(double)m_X/20,(double)m_Z/20,(double)m_Y/20,(double)m_X/20,(double)m_Z/20);


	//Ahora las lineas que van de un lado al otro
	//Esto dibuja bloque enteros de piezas
	for (itMC=lista.begin();itMC!=lista.end();itMC++)
	{
		fprintf(fin3," \\\subfigure{\\\pspicture(0,0)(%d,%d)   \n",m_X,m_Y);

//\subfigure{\pspicture(-10,0)(28,10)
	for (itC=(*itMC).second.begin();itC!=(*itMC).second.end();itC++)
	{
		for (int register i=1;i<=(*itC).Get_dx();i++)
		{
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz();k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
//					CONFIGURACAO kk=(*itC);
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1(),(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x2(),(*itC).Get_y2(),(*itC).Get_z1()+k*sumok,(*itC).Get_Id());
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1(),(*itC).Get_x2(),(*itC).Get_y1()+j*sumoj,(*itC).Get_z2(),(*itC).Get_Id());
					fprintf(fin3," \\\psframe[fillcolor=white,fillstyle=solid]    (%d,%d)(%d,%d)\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_x1()+(i)*sumoi,(*itC).Get_y1()+(j)*sumoj);
//						(double)sumoj/20,(double)sumoi/20,(double)sumok/20,,
//					(double)((*itC).Get_y1()+(double)(j-1)*sumoj+sumoj/2)/10,
//					(double)((*itC).Get_x1()+(double)(i-1)*sumoi+sumoi/2)/10,
//					(double)((*itC).Get_z1()+(double)(k-1)*sumok+sumok/2)/10);

				}
			}
		}
	}
	fprintf(fin3," \\\endpspicture}  \n");

	}
	fclose(fin3);
}
void CONTAINER:: EscribirSolucion2DMC(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista)
{
	

	FILE *fin3;
	fin3=fopen("Resulta2.txt","a+");
	fprintf(fin3,"%d\n",m_total_volumen_ocupado);
	std::list< std::pair< int , std::list<CONFIGURACAO> > > ::iterator itMC;
	std::list< CONFIGURACAO > ::iterator itC;
//	float divide=20;
//	fprintf(fin3,"\\CubeThreeD[ A=%.3f,B=%.3f,C=%.3f](%.3f,%.3f,%.3f)\n",(double)m_Y/20,(double)m_X/20,(double)m_Z/20,(double)m_Y/20,(double)m_X/20,(double)m_Z/20);


	//Ahora las lineas que van de un lado al otro
	//Esto dibuja bloque enteros de piezas
	for (itMC=lista.begin();itMC!=lista.end();itMC++)
	{
		fprintf(fin3," Bin (0,0)(%d,%d)   \n",m_X,m_Y);

//\subfigure{\pspicture(-10,0)(28,10)
	for (itC=(*itMC).second.begin();itC!=(*itMC).second.end();itC++)
	{
		for (int register i=1;i<=(*itC).Get_dx();i++)
		{
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz();k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
//					CONFIGURACAO kk=(*itC);
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1(),(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x2(),(*itC).Get_y2(),(*itC).Get_z1()+k*sumok,(*itC).Get_Id());
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1(),(*itC).Get_x2(),(*itC).Get_y1()+j*sumoj,(*itC).Get_z2(),(*itC).Get_Id());
					fprintf(fin3," (%d,%d)(%d,%d) Pieza %d\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_x1()+(i)*sumoi,(*itC).Get_y1()+(j)*sumoj , (*itC).Get_Id());
//						(double)sumoj/20,(double)sumoi/20,(double)sumok/20,,
//					(double)((*itC).Get_y1()+(double)(j-1)*sumoj+sumoj/2)/10,
//					(double)((*itC).Get_x1()+(double)(i-1)*sumoi+sumoi/2)/10,
//					(double)((*itC).Get_z1()+(double)(k-1)*sumok+sumok/2)/10);

				}
			}
		}
	}
	fprintf(fin3,"  \n");

	}
	fclose(fin3);
}
void CONTAINER:: EscribirSolucion3DMC(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista)
{
	

	FILE *fin3;
	fin3=fopen("Result2.txt","w+");
	fprintf(fin3,"Mejor solución %d\n",lista.size());
	std::list< std::pair< int , std::list<CONFIGURACAO> > > ::iterator itMC;
	std::list< CONFIGURACAO > ::iterator itC;
//	float divide=20;
//	fprintf(fin3,"\\CubeThreeD[ A=%.3f,B=%.3f,C=%.3f](%.3f,%.3f,%.3f)\n",(double)m_Y/20,(double)m_X/20,(double)m_Z/20,(double)m_Y/20,(double)m_X/20,(double)m_Z/20);

	//Ahora las lineas que van de un lado al otro
	//Esto dibuja bloque enteros de piezas
	int cont=0;
	for (itMC=lista.begin();itMC!=lista.end();itMC++,cont++)
	{
		fprintf(fin3," Bin %d (0,0,0)(%d,%d,%d)   \n",cont, m_X,m_Y,m_Z);


//\subfigure{\pspicture(-10,0)(28,10)
	for (itC=(*itMC).second.begin();itC!=(*itMC).second.end();itC++)
	{
		for (int register i=1;i<=(*itC).Get_dx();i++)
		{
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz();k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
//					CONFIGURACAO kk=(*itC);
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1(),(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x2(),(*itC).Get_y2(),(*itC).Get_z1()+k*sumok,(*itC).Get_Id());
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1(),(*itC).Get_x2(),(*itC).Get_y1()+j*sumoj,(*itC).Get_z2(),(*itC).Get_Id());
//					fprintf(fin3," \\\psframe[fillcolor=white,fillstyle=solid]    (%d,%d)(%d,%d)\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_x1()+(i)*sumoi,(*itC).Get_y1()+(j)*sumoj);
					fprintf(fin3," (%d,%d,%d)(%d,%d,%d)\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+(i)*sumoi,(*itC).Get_y1()+(j)*sumoj,(*itC).Get_z1()+(k)*sumok);
//						(double)sumoj/20,(double)sumoi/20,(double)sumok/20,,
//					(double)((*itC).Get_y1()+(double)(j-1)*sumoj+sumoj/2)/10,
//					(double)((*itC).Get_x1()+(double)(i-1)*sumoi+sumoi/2)/10,
//					(double)((*itC).Get_z1()+(double)(k-1)*sumok+sumok/2)/10);

				}
			}
		}
	}
		

	fprintf(fin3,"  \n");

	}
	fclose(fin3);
}
void CONTAINER:: EscribirSolucionLatex3DMC(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista)
{
	

	FILE *fin3;
	fin3=fopen("Result2.txt","a+");
	fprintf(fin3,"%d\n",m_total_volumen_ocupado);
	std::list< std::pair< int , std::list<CONFIGURACAO> > > ::iterator itMC;
	std::list< CONFIGURACAO > ::iterator itC;
//	float divide=20;
//	fprintf(fin3,"\\CubeThreeD[ A=%.3f,B=%.3f,C=%.3f](%.3f,%.3f,%.3f)\n",(double)m_Y/20,(double)m_X/20,(double)m_Z/20,(double)m_Y/20,(double)m_X/20,(double)m_Z/20);


	//Ahora las lineas que van de un lado al otro
	//Esto dibuja bloque enteros de piezas
	for (itMC=lista.begin();itMC!=lista.end();itMC++)
	{
		fprintf(fin3," \\ \subfigure{\\\psset{unit=0.1cm,Beta=10,Alpha=20,subticks=7}\\\pspicture(%d,0)(%d,%d)   \n",-m_Z,m_X,m_Z+m_Y);


//\subfigure{\pspicture(-10,0)(28,10)
	for (itC=(*itMC).second.begin();itC!=(*itMC).second.end();itC++)
	{
		for (int register i=1;i<=(*itC).Get_dx();i++)
		{
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz();k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
//					CONFIGURACAO kk=(*itC);
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1(),(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x2(),(*itC).Get_y2(),(*itC).Get_z1()+k*sumok,(*itC).Get_Id());
//					DibujarCaja3D((*itC).Get_x1(),(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1(),(*itC).Get_x2(),(*itC).Get_y1()+j*sumoj,(*itC).Get_z2(),(*itC).Get_Id());
//					fprintf(fin3," \\\psframe[fillcolor=white,fillstyle=solid]    (%d,%d)(%d,%d)\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_x1()+(i)*sumoi,(*itC).Get_y1()+(j)*sumoj);
					fprintf(fin3," \\ \pstThreeDBox[fillstyle=solid,fillcolor=yellow](%d,%d,%d)(%d,0,0)(0,%d,0)(0,0,%d)\n",(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,sumoi,sumoj,sumok);
//						(double)sumoj/20,(double)sumoi/20,(double)sumok/20,,
//					(double)((*itC).Get_y1()+(double)(j-1)*sumoj+sumoj/2)/10,
//					(double)((*itC).Get_x1()+(double)(i-1)*sumoi+sumoi/2)/10,
//					(double)((*itC).Get_z1()+(double)(k-1)*sumok+sumok/2)/10);

				}
			}
		}
	}
		fprintf(fin3," \\ \pstThreeDBox(%d,%d,%d)(%d,0,0)(0,%d,0)(0,0,%d)\n",0,0,0,m_X,m_Y,m_Z);

	fprintf(fin3," \\ \endpspicture}  \n");

	}
	fclose(fin3);
}
void CONTAINER:: PintarSolucion(std::list<CONFIGURACAO> &lista)
{
	printf("\n");
	std::list< CONFIGURACAO > ::iterator it;
	for (it=lista.begin();it!=lista.end();it++)
	{
		printf("(%d %d %d) (%d %d %d) Pieza %d  Cantidad %d max %d \n",(*it).Get_x1(),(*it).Get_y1(),(*it).Get_z1(),(*it).Get_x2(),(*it).Get_y2(),(*it).Get_z2(),(*it).Get_Id(),(*it).Get_Num(),m_Pieces[(*it).Get_Id()].Get_q());
	}
	printf("\n");


}
void CONTAINER:: PintarSpaces(std::list<SPACE> &lista)
{
	printf("\n");
	std::list< SPACE > ::iterator it;
	for (it=lista.begin();it!=lista.end();it++)
	{
		printf("(%d %d %d) (%d %d %d) Vol %d Dim: (%d %d %d)\n",(*it).Get_x1(),(*it).Get_y1(),(*it).Get_z1(),(*it).Get_x2(),(*it).Get_y2(),(*it).Get_z2(),(*it).Get_Volumen(), (*it).Get_dx(), (*it).Get_dy(), (*it).Get_dz());
	}
	printf("\n");


}
//Esta funcion mueve las cajas en un sentido 
bool CONTAINER::FuerzaDeGravedad(std::list<CONFIGURACAO> &lista,short int sentido)
{
	bool movido=false;
	//Las ordenamos por el eje que toque
//	//el sentido es hacia donde la puedo mover 
//	BubbleSort(m_Best_Configuracao,0);
	//Esta variable es para que las tenga ordenadas de la forma
	//que queramos
	m_tipo_gravedad=sentido;
	lista.sort();
	//0 eje_z
	//1 eje_x
	//2 eje_y
//	PintarSolucion(m_Best_Configuracao);
//	sentido=0;
	std::list<CONFIGURACAO> ::iterator itC;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
//		CONFIGURACAO kk=(*itC);
		if (sentido==0 && (*itC).Get_z1()==0) continue;
		if (sentido==1 && (*itC).Get_x1()==0) continue;
		int muevo=PuedoMover(lista,(*itC).Get_x1(),(*itC).Get_y1(),(*itC).Get_z1(),(*itC).Get_x2(),(*itC).Get_y2(),(*itC).Get_z2(),sentido);
		if (sentido==0 && muevo>0)
		{
			movido=true;
			(*itC).Set_z1((*itC).Get_z1()-muevo);
			(*itC).Set_z2((*itC).Get_z2()-muevo);
		}
		if (sentido==1 && muevo>0)
		{
			movido=true;
			(*itC).Set_x1((*itC).Get_x1()-muevo);
			(*itC).Set_x2((*itC).Get_x2()-muevo);
		}
		if (sentido==2 && muevo>0)
		{
			movido=true;
			(*itC).Set_y1((*itC).Get_y1()-muevo);
			(*itC).Set_y2((*itC).Get_y2()-muevo);
		}
		// Para piezas
		/*
		for (int register i=1;i<=(*itC).Get_dx();i++)
		{
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz();k++)
				{
					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
					//Le paso las tres dimensiones y eta funcion me devuelve si la puedo mover y cuanto para abajo
					int muevo=PuedoMover((*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,(*itC).Get_Id(),sentido);
				}
			}
		}
		*/
	}
//	PintarSolucion(m_Best_Configuracao);
	return movido;

}
//Esta funcion mueve las cajas en un sentido 
bool CONTAINER::FuerzaDeGravedadIndividual(std::list<CONFIGURACAO> &lista,short int sentido)
{
	bool movido=false;
	//Las ordenamos por el eje que toque
//	//el sentido es hacia donde la puedo mover 
//	BubbleSort(m_Best_Configuracao,0);
	//Esta variable es para que las tenga ordenadas de la forma
	//que queramos
	m_tipo_gravedad=sentido;
	lista.sort();
	//0 eje_z
	//1 eje_x
	//2 eje_y
//	PintarSolucion(m_Best_Configuracao);
//	sentido=0;
	std::list<CONFIGURACAO> ::iterator itC,itC2;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
//		CONFIGURACAO kk=(*itC);
		if (sentido==0 && (*itC).Get_z1()==0) continue;
		if (sentido==1 && (*itC).Get_x1()==0) continue;
		if (sentido==2 && (*itC).Get_y1()==0) continue;
		bool fini=false;
		// Para piezas
		for (int register i=1;i<=(*itC).Get_dx() && fini!=true;i++)
		{
			
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());
			bool finj=false;
			for (int register j=1;j<=(*itC).Get_dy() && finj!=true;j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());
				bool fink=false;

				for (int register k=1;k<=(*itC).Get_dz() && fink!=true;k++)
				{
					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
					//Si es en un sentido o en otro solamente tengo en cuenta 
					//para un lado
					if (sentido==0)
					{
						k=1;
						sumok=((*itC).Get_z2()-(*itC).Get_z1());
						fink=true;
					}
					if (sentido==1)
					{
						i=1;
						sumoi=((*itC).Get_x2()-(*itC).Get_x1());
						fini=true;

					}
					if (sentido==2)
					{
						j=1;
						sumoj=((*itC).Get_y2()-(*itC).Get_y1());
						finj=true;

					}

					int muevo=PuedoMover(lista,(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,sentido);
					//Tengo que dividir la capa en trozos ya que una caja individual si la 
					//puedo bajar
//					CONFIGURACAO kk=(*itC);

					if (sentido==0 && muevo>0)
					{
//						printf("algo se mueve");
						//Tengo que llamar a la funcion con la configuracion
						//que tengo 
						std::list< CONFIGURACAO > lista_Temp;
						//Tengo que meter algunas nuevas configuracaos
						ActualizarConfiguracaoGravedad((*itC),(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,lista_Temp,sentido);
						//Cambio la actual configuracao
						//Tengo que poner el numero 
						itC->Set_x1((*itC).Get_x1()+(i-1)*sumoi);
						itC->Set_y1((*itC).Get_y1()+(j-1)*sumoj);
						itC->Set_x2((*itC).Get_x1()+sumoi);
						itC->Set_y2((*itC).Get_y1()+sumoj);
						itC->Set_dx(1);	
						itC->Set_dy(1);
						itC->Set_dz((*itC).Get_dz());
						itC->Set_Num((*itC).Get_dz());
						itC->Set_z1((*itC).Get_z1()-muevo);
						itC->Set_z2((*itC).Get_z2()-muevo);
						itC->Set_Vol(((*itC).Get_z2()-(*itC).Get_z1())*((*itC).Get_y2()-(*itC).Get_y1())*((*itC).Get_x2()-(*itC).Get_x1()));
						//Actualizar esta configuraco me crea algunas nuevas
						itC2=itC;
						if (itC!=lista.end()) itC2++;
						

						lista.insert(itC2,lista_Temp.begin(),lista_Temp.end());

						movido=true;
					}
					if (sentido==2 && muevo>0)
					{


//						printf("algo se mueve");
						int vol=(*itC).Get_Volumen();
						//Tengo que llamar a la funcion con la configuracion
						//que tengo 
						std::list< CONFIGURACAO > lista_Temp;
						//Tengo que meter algunas nuevas configuracaos
						ActualizarConfiguracaoGravedad((*itC),(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,lista_Temp,sentido);

						movido=true;
						int numto=(*itC).Get_Num();
						itC->Set_z1((*itC).Get_z1()+(k-1)*sumok);
						itC->Set_z2((*itC).Get_z1()+sumok);
						itC->Set_x1((*itC).Get_x1()+(i-1)*sumoi);
						itC->Set_x2((*itC).Get_x1()+sumoi);
						//Pongo las piezas que tuviera en la direccion de x
						itC->Set_dx(1);	
						itC->Set_dy((*itC).Get_dy());
						itC->Set_dz(1);
						itC->Set_Num((*itC).Get_dy());
						itC->Set_y1((*itC).Get_y1()-muevo);
						itC->Set_y2((*itC).Get_y2()-muevo);
						itC->Set_Vol(((*itC).Get_z2()-(*itC).Get_z1())*((*itC).Get_y2()-(*itC).Get_y1())*((*itC).Get_x2()-(*itC).Get_x1()));
						std::list<CONFIGURACAO> ::iterator itkk;
						int vol2=(*itC).Get_Volumen();
						for (itkk=lista_Temp.begin();itkk!=lista_Temp.end();itkk++)
						{
							vol2+=(*itkk).Get_Volumen();
						}
						if (vol2!=vol)
							int kko=0;
						itC2=itC;
						if (itC!=lista.end()) itC2++;

						lista.insert(itC2,lista_Temp.begin(),lista_Temp.end());
					}				
					if (sentido==1 && muevo>0)
					{


//						printf("algo se mueve");

						//Tengo que llamar a la funcion con la configuracion
						//que tengo 
						std::list< CONFIGURACAO > lista_Temp;
						//Tengo que meter algunas nuevas configuracaos
						ActualizarConfiguracaoGravedad((*itC),(*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,lista_Temp,sentido);

						movido=true;
						int numto=(*itC).Get_Num();
						itC->Set_z1((*itC).Get_z1()+(k-1)*sumok);
						itC->Set_z2((*itC).Get_z1()+sumok);
						itC->Set_y1((*itC).Get_y1()+(j-1)*sumoj);
						itC->Set_y2((*itC).Get_y1()+sumoj);
						//Pongo las piezas que tuviera en la direccion de x
						itC->Set_dx((*itC).Get_dx());	
						itC->Set_dy(1);
						itC->Set_dz(1);
						itC->Set_Num((*itC).Get_dx());
						itC->Set_x1((*itC).Get_x1()-muevo);
						itC->Set_x2((*itC).Get_x2()-muevo);
						itC->Set_Vol(((*itC).Get_z2()-(*itC).Get_z1())*((*itC).Get_y2()-(*itC).Get_y1())*((*itC).Get_x2()-(*itC).Get_x1()));

						itC2=itC;
						if (itC!=lista.end()) itC2++;

						lista.insert(itC2,lista_Temp.begin(),lista_Temp.end());
					}
				}
			}
		}

	}
//	PintarSolucion(m_Best_Configuracao);
	return movido;

}
//Me dice  cuanto la puedo mover en alguna dirección
//o eje_z
//1 eje_x
//2 eje_y
int CONTAINER::PuedoMover(std::list<CONFIGURACAO> &lista,int x1,int y1,int z1,int x2,int y2,int z2,short int sentido)
{
	//Me dice cuanto puedo mover esta pieza 
	//lo primero es localizar el maximo
	//Lo primero es ver si se intersectan
	int mintemp=0,min=m_X;
	if (sentido==0)
		min=z1;
	if (sentido==1)
		min=x1;
	if (sentido==2)
		min=y1;
	std::list<CONFIGURACAO> ::iterator itC;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
//		CONFIGURACAO kk=(*itC);
		if (sentido==0)
		{
			if ((*itC).Get_z1()>=z1) 
				return min;
			if ((*itC).Get_z2()>z1) 
				continue;


			//Si no intersectan con eje_x
			if (!((x2 <= (*itC).Get_x1()) ||  (x1 >= (*itC).Get_x2()))
				&& !((y2 <= (*itC).Get_y1()) ||  (y1 >= (*itC).Get_y2())))
			{
			if (z1==((*itC).Get_z2())) 	return 0;
				mintemp=z1-((*itC).Get_z2());
			if (mintemp < min)
				min=mintemp;
			}
		}
		if (sentido==1)
		{
			if ((*itC).Get_x1()>=x1) return min;
			if ((*itC).Get_x2()>x1) continue;
			//Si intersectan con eje_x
			if (!(z2 <= (*itC).Get_z1() ||  z1 >= (*itC).Get_z2())
				&& !(y2 <= (*itC).Get_y1() ||  y1 >= (*itC).Get_y2()))
			{
				
			if ( x1==((*itC).Get_x2())) 				return 0;
			mintemp=x1-(*itC).Get_x2();
			if (mintemp < min)
				min=mintemp;
			}
		}
		if (sentido==2)
		{
			if ((*itC).Get_y1()>=y1) return min;
			if ((*itC).Get_y2()>y1) continue;
			//Si intersectan con eje_x
			if (!(z2 <= (*itC).Get_z1() ||  z1 >= (*itC).Get_z2())
				&& !(x2 <= (*itC).Get_x1() ||  x1 >= (*itC).Get_x2()))
			{
				
			if ( y1==((*itC).Get_y2())) 
				return 0;
			mintemp=y1-(*itC).Get_y2();
			if (mintemp < min)
				min=mintemp;
			}
		}

	}
	return 0;
}
void CONTAINER::Ordenar(std::list< std::pair< int ,std::list< CONFIGURACAO > > > &lista) 
{
	std::list< std::pair< int ,std::list < CONFIGURACAO > > > ::iterator itc,itc2,itfin ;
	bool fin;
	itfin=lista.end();
	do 
	{
		fin=true;
	    for (itc=lista.begin();itc!=itfin;itc++) 
		{
//			PintarSolucion(lista);
			itc2=itc;
			itc2++;
//			CONFIGURACAO kk=(*itc);
//			CONFIGURACAO kk2=(*itc2);
			if (itc2==itfin)
			break;
			if ((*itc).first<(*itc2).first) 
			{
				int k=(*itc).first;
				std::list < CONFIGURACAO > lista_temp=(*itc).second;
				(*itc).first=(*itc2).first;
				(*itc).second=(*itc2).second;
				(*itc2).first=k;
				(*itc2).second=lista_temp;
//				int kk=(*itc).first;
//				int kk2=(*itc2).first;
	            fin=false;
		
			}
		}
//		PintarSolucion(lista);

	} while (fin==false);
} 
void CONTAINER::BubbleSort(std::list< CONFIGURACAO> &lista,short int tipo) 
{
	std::list< CONFIGURACAO > ::iterator itc,itc2,itfin;
	bool fin;
	itfin=lista.end();
	do 
	{
		fin=true;
	    for (itc=lista.begin();itc!=itfin;itc++) 
		{
			PintarSolucion(lista);
			itc2=itc;
			itc2++;
//			CONFIGURACAO kk=(*itc);
//			CONFIGURACAO kk2=(*itc2);
			if (itc2==itfin)
			break;
			if ((*itc).Mayor((*itc2),tipo)==true) 
			{
				std::list< CONFIGURACAO > ::iterator ittemp;
				ittemp=itc;
				itc=itc2;
				itc2=ittemp;
	            fin=false;
			PintarSolucion(lista);
		
			}
		}
//		PintarSolucion(lista);

	} while (fin==false);
} 
bool CONFIGURACAO::Mayor(CONFIGURACAO &C,short int tipo)
{
	//Por el eje z
	if (tipo==0)
	{
		//Si no son restringidas
		if ((m_z1)==(C.m_z1))
		{
			//Por la eficiencia
			if (m_x1==C.m_x1)
			{
				return (m_y1>C.m_y1);
			}
			else
				//Por el área
			return (m_x1>C.m_x1);
		}
		else
			return (m_z1>C.m_z1);
	}
	return true;
}
void CONTAINER::BorrarElemento(CONFIGURACAO &C, std::list<CONFIGURACAO> &lista)
{
	std::list<CONFIGURACAO>::iterator it;
	for (it = lista.begin(); it != lista.end();)
	{
		if ((*it).Get_x1() == C.Get_x1() && (*it).Get_x2() == C.Get_x2() && (*it).Get_y1() == C.Get_y1() && (*it).Get_y2() == C.Get_y2() && (*it).Get_z1() == C.Get_z1() && (*it).Get_z2() == C.Get_z2())
		{
			it = lista.erase(it);
		}
		else
			++it;
	}
}
double CONTAINER::Medida1Estabilidad(std::list<CONFIGURACAO> &lista)
{
	//Esta tiene que sumar por cuantas cajas de media esta soportada cada caja 
	//que no esta en el suelo
	int total=0;
	int numcaixas=0;
	m_medidaCG=0;
	m_medida55por100=0;
	m_medida100por100=0;
	int numcaixasTotales=0,numcaixas100por100=0,numcaixasCG=0,numcaixas55por100=0;
	std::list<CONFIGURACAO> ::iterator itC,itC2;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
//		CONFIGURACAO kk=(*itC);


		// Para piezas
		for (int register i=1;i<=(*itC).Get_dx() ;i++)
		{
			
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz() ;k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
					//Si esta en el suelo no me vale para la tercera medida
					if (((*itC).Get_z1()+(k-1)*sumok)==0)
					{
						numcaixas100por100++;
						numcaixas55por100++;
						numcaixasCG++;
						numcaixasTotales++;
						continue;
					}
					int kkespia=1;
					int kkespia2=0;
					if (EstaCajaSoportada((*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,lista,100)==true)
						numcaixas100por100++;
					if (EstaCajaSoportada((*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,lista,55)==true)
						numcaixas55por100++;
					else
						kkespia=0;
			
					int difx=sumoi/2;
					int dify=sumoj/2;
					if (2*difx==sumoi)
					{
						difx--;
					}
					if (2*dify==sumoj)
					{
						dify--;
					}
					if (numcaixas55por100==85)
						int kkk=9;
					if (EstaCajaSoportada((*itC).Get_x1()+(i-1)*sumoi+difx,(*itC).Get_y1()+(j-1)*sumoj+dify,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi-difx,(*itC).Get_y1()+j*sumoj-dify,(*itC).Get_z1()+k*sumok,lista,10)==true)
						numcaixasCG++;
					if (numcaixas55por100<numcaixasCG)
						int kkk=9;
					else kkespia2=1;
					if (kkespia==0 && kkespia2==0)
						int kkkit=0;

					numcaixasTotales++;
					total+=NumeroDeCajasSoportanEsta((*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,lista);

					numcaixas++;
				}
			}
		}
	}
	m_medidaCG=((double)numcaixasCG/(double)numcaixasTotales);
	m_medida100por100=((double)numcaixas100por100/(double)numcaixasTotales);
	m_medida55por100=((double)numcaixas55por100/(double)numcaixasTotales);
	//Medidas de estabilidad 1_1.1_2,1_3
	return ((double)total/(double)numcaixas);
}
//Cuanta el numero de cajas que soportan esta caja
int CONTAINER::NumeroDeCajasSoportanEsta(int x1,int y1, int z1, int x2, int y2, int z2,std::list<CONFIGURACAO> &lista)
{
	int numero=0;
	//Tengo que recorrer todas las cajas 
	std::list<CONFIGURACAO> ::iterator itC,itC2;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
//		CONFIGURACAO kk=(*itC);
		// Para piezas
		for (int register i=1;i<=(*itC).Get_dx() ;i++)
		{
			
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz() ;k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
					//Como ya tengo que lo soportan tengo que ver cuantas
					//cajas la soportan
					if (((*itC).Get_z1()+(k)*sumok)!=z1) continue;
					if (!((x2<=(*itC).Get_x1()+(i-1)*sumoi) ||  x1>=((*itC).Get_x1()+i*sumoi))
						&& !((y2<= (*itC).Get_y1()+(j-1)*sumoj) ||  y1>=((*itC).Get_y1()+j*sumoj)))
					{
						numero++;
					}

				}
			}
		}
	}
	return numero;
}	
//Cuanta el numero de cajas que soportan esta caja
int CONTAINER::EstaCajaSoportada(int x1,int y1, int z1, int x2, int y2, int z2,std::list<CONFIGURACAO> &lista,int cantidad)
{
	int numero=0;
	int areapieza=(x2-x1)*(y2-y1);
	int areacorta=0;
	//Tengo que recorrer todas las cajas 
	std::list<CONFIGURACAO> ::iterator itC,itC2;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
//		CONFIGURACAO kk=(*itC);
		// Para piezas
		for (int register i=1;i<=(*itC).Get_dx() ;i++)
		{
			
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz() ;k++)
				{

					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());
					//Como ya tengo que lo soportan tengo que ver cuantas
					//cajas la soportan
					if (((*itC).Get_z1()+(k)*sumok)!=z1) continue;
					if (!((x2<=(*itC).Get_x1()+(i-1)*sumoi) ||  x1>=((*itC).Get_x1()+i*sumoi))
						&& !((y2<= (*itC).Get_y1()+(j-1)*sumoj) ||  y1>=((*itC).Get_y1()+j*sumoj)))
					{
						int kk1=(*itC).Get_x1()+(i-1)*sumoi;
						int kk2=(*itC).Get_y1()+(j-1)*sumoj;
						//Aqui ahora tengo que ver cuanto se corta
						int minx1=min(x1,((*itC).Get_x1()+(i-1)*sumoi));
						int miny1=min(y1,((*itC).Get_y1()+(j-1)*sumoj));
						int maxx2=max(x2,((*itC).Get_x1()+(i)*sumoi));
						int maxy2=max(y2,((*itC).Get_y1()+(j)*sumoj));
						//Se corta en x
						int cx=(x2-x1)+(sumoi)-(maxx2-minx1);
						int cy=(y2-y1)+(sumoj)-(maxy2-miny1);
						areacorta+=cx*cy;
						if (areacorta>=((double)cantidad*areapieza/(double)100))
							return true;
						
					}

				}
			}
		}
	}
	return false;
}	
//Esta mide el número medio de cajas que tiene 3 lados pegados a otras cajas
	//Por tanto lo primero recorrer todas las cajas
double CONTAINER::Medida2Estabilidad(std::list<CONFIGURACAO> &lista)
{

	int total=0;
	int numcaixas=0;
	std::list<CONFIGURACAO> ::iterator itC,itC2;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{
		// Para piezas
		for (int register i=1;i<=(*itC).Get_dx() ;i++)
		{
//			CONFIGURACAO kk=(*itC);
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());

				for (int register k=1;k<=(*itC).Get_dz() ;k++)
				{
					int sumok=(((*itC).Get_z2()-(*itC).Get_z1())/(*itC).Get_dz());

					total+=EstaCajaTiene3Pegados((*itC).Get_x1()+(i-1)*sumoi,(*itC).Get_y1()+(j-1)*sumoj,(*itC).Get_z1()+(k-1)*sumok,(*itC).Get_x1()+i*sumoi,(*itC).Get_y1()+j*sumoj,(*itC).Get_z1()+k*sumok,lista);
					numcaixas++;
				}
			}
		}
	}
	return ((double)total/(double)numcaixas)*100;
}
//Cuanta el numero de cajas que soportan esta caja
int CONTAINER::EstaCajaTiene3Pegados(int x1,int y1, int z1, int x2, int y2, int z2,std::list<CONFIGURACAO> &lista)
{
	std::list<CONFIGURACAO> ::iterator itC,itC2;
	short int ladox1=0,ladox2=0,ladoy1=0,ladoy2=0;
	for (itC=lista.begin();itC!=lista.end();itC++)
	{

		// Para piezas
		for (int register i=1;i<=(*itC).Get_dx() ;i++)
		{
//			CONFIGURACAO kk=(*itC);
			int sumoi=(((*itC).Get_x2()-(*itC).Get_x1())/(*itC).Get_dx());

			for (int register j=1;j<=(*itC).Get_dy();j++)
			{
				int sumoj=(((*itC).Get_y2()-(*itC).Get_y1())/(*itC).Get_dy());
				//Para la z no tengo que hacerlo, vamos qu no es necesario
				//si intersecta con z
				if (!(z2<=(*itC).Get_z1() ||  z1>=(*itC).Get_z2()))
				{
					if ((*itC).Get_x1()+i*sumoi==x1 || x1==0)
						ladox1=1;
					if ((*itC).Get_x1()+(i-1)*sumoi==x2 || x2==m_X)
						ladox2=1;
					if ((*itC).Get_y1()+j*sumoj==y1 || y1==0)
						ladoy1=1;
					if ((*itC).Get_y1()+(j-1)*sumoj==y2 || y2==m_Y)
						ladoy2=1;
				}
			}
		}


	}
	int sum=ladox1+ladox2+ladoy1+ladoy2;
	if (sum>=3)
		return 0;
	else return 1;

}
void CONTAINER::AumentarPiezas()
{
	return;
	m_tipo_orden_pieces=0;
	std::sort(m_Pieces.begin(),m_Pieces.end());

	//REduzco el tamano del strip
	m_X=ValoresPosibles(0,m_X);
		//Hago el vector para que se calcule más rapido
	//Aqui hago la reducción de piezas
	for (register int kk=0;kk<m_Q;kk++)
	{
		//Para X
		//Tener en cuenta que aqui utilizo el que tengo para hacer los valores posibles
		int mas_grande=(m_X-m_Pieces[kk].Get_x())-ValoresPosibles(0,m_X-m_Pieces[kk].Get_x());
		m_Pieces[kk].Add_Volumen(mas_grande*m_Pieces[kk].Get_y()*m_Pieces[kk].Get_z()*m_Pieces[kk].Get_q());
//		if ((mas_grande+m_Piezas[kk].ancho)==m_W) continue;
		m_total_volumen+=mas_grande*m_Pieces[kk].Get_y()*m_Pieces[kk].Get_z()*m_Pieces[kk].Get_q();
		m_Pieces[kk].Set_x(m_Pieces[kk].Get_x()+mas_grande);
//		if (m_Pieces[kk].Get_x()+mas_grande==m_X)
//			printf("X");
	}

	m_tipo_orden_pieces=1;
	std::sort(m_Pieces.begin(),m_Pieces.end());
	//REduzco el tamano del strip
	m_Y=ValoresPosibles(1,m_Y);

	
	for (int kk=0;kk<m_Q;kk++)
	{
		int ky=m_Pieces[kk].Get_y();

		//Para Y
		//Tener en cuenta que aqui utilizo el que tengo para hacer los valores posibles
		int mas_grande=(m_Y-m_Pieces[kk].Get_y())-ValoresPosibles(1,m_Y-m_Pieces[kk].Get_y());

//		if ((mas_grande+m_Piezas[kk].ancho)==m_W) continue;
		m_Pieces[kk].Add_Volumen(mas_grande*m_Pieces[kk].Get_x()*m_Pieces[kk].Get_z()*m_Pieces[kk].Get_q());
		m_total_volumen+=mas_grande*m_Pieces[kk].Get_x()*m_Pieces[kk].Get_z()*m_Pieces[kk].Get_q();
		m_Pieces[kk].Set_y(m_Pieces[kk].Get_y()+mas_grande);
//		if (m_Pieces[kk].Get_y()+mas_grande==m_Y)
//			printf("Y");
	}

	m_tipo_orden_pieces=2;
	std::sort(m_Pieces.begin(),m_Pieces.end());
	//REduzco el tamano del strip
	m_Z=ValoresPosibles(2,m_Z);

	for (int kk=0;kk<m_Q;kk++)
	{

		//Para Z
		//Tener en cuenta que aqui utilizo el que tengo para hacer los valores posibles
		int mas_grande=(m_Z-m_Pieces[kk].Get_z())-ValoresPosibles(2,m_Z-m_Pieces[kk].Get_z());

//		if ((mas_grande+m_Piezas[kk].ancho)==m_W) continue;
		m_Pieces[kk].Add_Volumen(mas_grande*m_Pieces[kk].Get_x()*m_Pieces[kk].Get_y()*m_Pieces[kk].Get_q());
		m_total_volumen+=mas_grande*m_Pieces[kk].Get_x()*m_Pieces[kk].Get_y()*m_Pieces[kk].Get_q();
		m_Pieces[kk].Set_z(m_Pieces[kk].Get_z()+mas_grande);
//		if (m_Pieces[kk].Get_z()+mas_grande==m_Z)
//			printf("Z");

	}
	m_fintime2=clock();

}//En esta funcion tengo los bins ordenados por orden solamente se hace para las 
//piezas con todas sus dimensiones mayores que la mitad
void CONTAINER::ReducirPiezasYBins()
{
	return;
	//Las medidas de los bins pueden cambiar
	//falta poner que no esté repetido cuidadorrrrrrrrrrrr

/*	bool cambio=false;
	for (int bin=0;bin<m_b;bin++)
	{
		cambio=false;
		int X=ValoresPosibles(0,bin,m_Bins[bin].Get_x());
		if (X<m_Bins[bin].Get_x()) 
		{
			cambio=true;
			m_Bins[bin].Set_x(X);
		}
		int Y=ValoresPosibles(1,bin,m_Bins[bin].Get_y());
		if (Y<m_Bins[bin].Get_y()) 
		{
			cambio=true;

			m_Bins[bin].Set_y(Y);
		}
		int Z=ValoresPosibles(2,bin,m_Bins[bin].Get_z());
		if (Z<m_Bins[bin].Get_z()) 
		{
			cambio=true;

			m_Bins[bin].Set_z(Z);
		}
		if (cambio==false)
		{
			int Vol=ValoresPosibles(3,bin,m_Bins[bin].Get_Volumen());
			m_Bins[bin].Set_Volumen(Vol);
			m_Bins[bin].Set_Valor((double)(m_Bins[bin].Get_Coste())/(double)(m_Bins[bin].Get_Volumen()));
		}

		if (cambio==true)
		{
			m_Bins[bin].Set_Volumen(m_Bins[bin].Get_x()* m_Bins[bin].Get_y() * m_Bins[bin].Get_z());
			int Vol=ValoresPosibles(3,bin,m_Bins[bin].Get_Volumen());
			m_Bins[bin].Set_Volumen(Vol);
			m_Bins[bin].Set_Valor((double)(m_Bins[bin].Get_Coste())/(double)(m_Bins[bin].Get_Volumen()));
		}
		

	}
*/

	bool quitar=false;

	for (int j=0;j<m_Q;j++)
	{
		m_Pieces_Tabu.push_back(0);
	}
	int kkQ=m_Q;


	int k123=0;




	for (k123=0;k123<m_Q;k123++)
	{
		bool puede_que_si=false;
		//Condicion para que la pieza 

		int kkX=m_Pieces[k123].Get_x();
		int kky=m_Pieces[k123].Get_y();

		int kkz=m_Pieces[k123].Get_z();

		if (2*m_Pieces[k123].Get_x()>m_X && 2*m_Pieces[k123].Get_y()>m_Y && 2*m_Pieces[k123].Get_z()>m_Z  )
		{
			int vol=0;
			int kx=m_X-m_Pieces[k123].Get_x();
			int ky=m_Y-m_Pieces[k123].Get_y();
			int kz=m_Z-m_Pieces[k123].Get_z();
			int voltemp=(m_X*m_Y*m_Z)-(m_Pieces[k123].Get_x()*m_Pieces[k123].Get_y()*m_Pieces[k123].Get_z());
			int minx=m_X;
			int miny=m_Y;
			int minz=m_Z;
			if (kx==0 && ky==0 && kz==0)
				puede_que_si=true;
			//Miramos todas las que estan fuera y medimos los volumenes
			int segunda=-1;
			for (register int kk=0;kk<m_Q && puede_que_si==false;kk++)
			{
				if ((m_Pieces[kk].Get_x()<=kx) || 
					(m_Pieces[kk].Get_y()<=ky) ||
				    (m_Pieces[kk].Get_z()<=kz))
				{
//					m_Pieces[kk].Set_Num(m_Pieces[kk].Get_q());
					vol+=m_Pieces[kk].Get_Volumen();
					if (minx>m_Pieces[kk].Get_x())
						minx=m_Pieces[kk].Get_x();
					if (miny>m_Pieces[kk].Get_y())
						miny=m_Pieces[kk].Get_y();

					if (minz>m_Pieces[kk].Get_z())
						minz=m_Pieces[kk].Get_z();
					//Si existe una pieza que ocupe justo el hueco
					//la meto
					if (kx==0 && ky==0 && m_Pieces[kk].Get_z()==kz && m_Pieces[kk].Get_x()==m_X && m_Pieces[kk].Get_y()==m_Y)
					{
						vol=0;
						puede_que_si=true;
						segunda=kk;
						 
					}
					if (kx==0 && kz==0 && m_Pieces[kk].Get_y()==ky && m_Pieces[kk].Get_x()==m_X && m_Pieces[kk].Get_z()==m_Z)
					{
						vol=0;
						puede_que_si=true;
						segunda=kk;


					}
					if (ky==0 && kz==0 && m_Pieces[kk].Get_x()==kx && m_Pieces[kk].Get_y()==m_Y && m_Pieces[kk].Get_z()==m_Z)
					{
						vol=0;
						puede_que_si=true;
						segunda=kk;

					}

					
				}

			}
			//Si la última pieza es mayor que la siguiente, metería esta
			if (puede_que_si==false && m_Pieces[m_Q-(int)1].Get_x()<=minx &&
				m_Pieces[m_Q-(int)1].Get_y()<=miny &&
				m_Pieces[m_Q-(int)1].Get_z()<=minz && vol>voltemp && (vol-m_Pieces[m_Q-(int)1].Get_Volumen())<=voltemp)
			{
				puede_que_si=true;
//				for (int i=0;;i++);
//					printf("pue ser");
			}




			//Aqui llamamos al Grasp para que coloque los bins
			if (vol<=voltemp || puede_que_si==true)
			{
				//Si hay mas piezas que caben aqui
				if (vol>0)
				{
					m_total_volumen_ocupado=0;
					for (int j=0;j<m_Q;j++)
					{
						m_Pieces_Tabu[j]=0;
					}

					std::list< std::pair< int ,std::list<CONFIGURACAO> > > lista;
//					printf("una pieza");
					ORIG setmin(0,0,0);
					CONFIGURACAO C(this,setmin,999999);
					m_tipo_origen=0;

					C.CambiarConfiguracao(1,1,1,1,m_Pieces[k123].Get_x(),m_Pieces[k123].Get_y(),m_Pieces[k123].Get_z(), m_Pieces[k123].Get_Id(),0);
					lista.clear();
					RellenarVariosBin(lista,1,true,C);
					//puedo quitar estos items
					if ((puede_que_si==false && m_total_volumen_ocupado==(vol+(m_Pieces[k123].Get_x()*m_Pieces[k123].Get_y()*m_Pieces[k123].Get_z()))  )
						|| (puede_que_si==true && m_total_volumen_ocupado==(vol+m_Pieces[k123].Get_Volumen()-m_Pieces[m_Q-(int)1].Get_Volumen())))
					{
						quitar=true;
						for (register int kj=0;kj<kkQ;kj++)
						{
							if (m_Pieces_Tabu[kj]>0)
							{
								//Eliminar la que tenga id igual kj
								std::vector< PIECE > ::iterator itP;


								EliminarPieza(kj);

								
							}
						}
						m_bin_fijados++;
						std::vector< PIECE > ::iterator it;
						int id=0;
						for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
						{
							(*it).Set_Id(id);
						}	

					}
				}
				//solamente hay una pieza
				else
				{
//					printf("una pieza\n");
					
					quitar=true;
					
//					printf("%d, (%d,%d, %d) Num %d\n",m_Pieces[k123].Get_Id(),m_Pieces[k123].Get_x(),m_Pieces[k123].Get_y(),m_Pieces[k123].Get_z(),m_Pieces[k123].Get_q());
					EliminarPieza(m_Pieces[k123].Get_Id());

					m_bin_fijados++;
					if (segunda!=-1)
					{
						std::vector< PIECE > ::iterator itP;


						EliminarPieza(segunda);

					}
					k123=-1;
					std::vector< PIECE > ::iterator it;
					int id=0;
					for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
					{
						(*it).Set_Id(id);
					}	

				}

			}
		}

	}
//	printf("Se han quitado %d Bins\n",m_bin_fijados);
	if (quitar==true)
	{
		std::vector< PIECE > ::iterator it;
		int id=0;
		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
		{
			(*it).Set_Id(id);
		}	

	}
	m_total_volumen_ocupado=0;
}

void CONTAINER::EliminarPieza(int Id)
{
	std::vector< PIECE > ::iterator itP;
	for (itP=m_Pieces.begin();itP!=m_Pieces.end();)
	{
		if ((*itP).Get_Id()==Id)
		{
			m_total_volumen-=(*itP).Get_Volumen();
//			int kk=(*itP).Get_q();
//			printf("%d\n",kk);
			m_Q--;
			m_Pieces.erase(itP);
			return;
		}
		++itP;
	}
	return;
}//Esta funcion intenta hacer mas grandes las piezas 

//que no puedan entrar con mas piezas quito esas piezas y hago mas grande el bin
void CONTAINER::ReducirPiezasX()
{
	return;
	m_tipo_orden_pieces=0;
	std::sort(m_Pieces.begin(),m_Pieces.end());

	bool quitar=false;
	for (int j=0;j<m_Q;j++)
	{
		m_Pieces_Tabu.push_back(0);
	}
	int kkQ=m_Q;
	for (register int k=0;k<m_Q;k++)
	{
		bool no_se_puede=false;
		int x=m_Pieces[k].Get_x();
		int y=m_Pieces[k].Get_y();
		int z=m_Pieces[k].Get_z();
		//Primero para las X
		if (2*m_Pieces[k].Get_x()>m_X )
		{
			int vol=0;
			int volmin=0;
			int kx=m_X-m_Pieces[k].Get_x();
			int voltemp=kx*y*z;
			int minx=kx;
			int miny=m_Pieces[k].Get_y();
			int minz=m_Pieces[k].Get_z();
			if (kx==0) 
				no_se_puede=true;
			//Miramos todas las que estan fuera y medimos los volumenes
			for (register int kk=0;kk<m_Q && no_se_puede==false;kk++)
			{
				if ((m_Pieces[kk].Get_x()<=kx) )
				{
//					m_Pieces[kk].Set_Num(m_Pieces[kk].Get_q());
					vol+=m_Pieces[kk].Get_Volumen();
					if (m_Pieces[kk].Get_y()>miny)
						no_se_puede=true;
					if (m_Pieces[kk].Get_z()>minz)
						no_se_puede=true;
					
				}

			}

			//Aqui llamamos al Grasp para que coloque los bins
			if (vol<=voltemp && no_se_puede==false)
			{
				//Si hay mas piezas que caben aqui
				if (vol>0)
				{
					m_total_volumen_ocupado=0;
					for (int j=0;j<m_Q;j++)
					{
						m_Pieces_Tabu[j]=0;
					}

					std::list< std::pair< int ,std::list<CONFIGURACAO> > > lista;
//					printf("una pieza");
					ORIG setmin(0,0,0);
					CONFIGURACAO C(this,setmin,999999);
					m_tipo_origen=0;
					int X=m_X;
					int Y=m_Y;
					int Z=m_Z;
					m_X=m_X;
					m_Y=m_Pieces[k].Get_y();
					m_Z=m_Pieces[k].Get_z();
					C.CambiarConfiguracao(1,1,1,1,m_Pieces[k].Get_x(),m_Pieces[k].Get_y(),m_Pieces[k].Get_z(), m_Pieces[k].Get_Id(),0);
					lista.clear();
					RellenarVariosBin(lista,1,true,C);
					m_X=X;
					m_Y=Y;
					m_Z=Z;
					//puedo quitar estos items
					if (m_total_volumen_ocupado==(vol+(m_Pieces[k].Get_x()*m_Pieces[k].Get_y()*m_Pieces[k].Get_z()))  )
					{
						quitar=true;
						for (register int kj=0;kj<kkQ;kj++)
						{
							if (m_Pieces_Tabu[kj]>0)
							{
								//Eliminar la que tenga id igual kj
								EliminarPieza(kj);

							}
						}
						m_total_volumen+=kx*y*z;

						m_Pieces[k].Set_x(m_X);
					}

				}
				//solamente hay una pieza
				else
				{
						m_total_volumen+=kx*y*z;

					m_Pieces[k].Set_x(m_X);


				}

			}
		}

	}


	if (quitar==true)
	{
		std::vector< PIECE > ::iterator it;
		int id=0;
		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
		{
			(*it).Set_Id(id);
		}	

	}
	m_total_volumen_ocupado=0;
}
//Esta funcion intenta hacer mas grandes las piezas 

//que no puedan entrar con mas piezas quito esas piezas y hago mas grande el bin
void CONTAINER::ReducirPiezasY()
{
	return;
	m_tipo_orden_pieces=1;
	std::sort(m_Pieces.begin(),m_Pieces.end());

	bool quitar=false;
	for (int j=0;j<m_Q;j++)
	{
		m_Pieces_Tabu.push_back(0);
	}
	int kkQ=m_Q;
	for (register int k=0;k<m_Q;k++)
	{
		bool no_se_puede=false;
		int x=m_Pieces[k].Get_x();
		int y=m_Pieces[k].Get_y();
		int z=m_Pieces[k].Get_z();
		//Primero para las X
		if (2*m_Pieces[k].Get_y()>m_Y )
		{
			int vol=0;
			int volmin=0;
			int ky=m_Y-m_Pieces[k].Get_y();
			int voltemp=ky*x*z;
			int minx=m_Pieces[k].Get_x();
			int miny=ky;
			int minz=m_Pieces[k].Get_z();
			if (ky==0) 
				no_se_puede=true;
			//Miramos todas las que estan fuera y medimos los volumenes
			for (register int kk=0;kk<m_Q && no_se_puede==false;kk++)
			{
				if ((m_Pieces[kk].Get_y()<=ky) )
				{
//					m_Pieces[kk].Set_Num(m_Pieces[kk].Get_q());
					vol+=m_Pieces[kk].Get_Volumen();
					if (m_Pieces[kk].Get_x()>minx)
						no_se_puede=true;
					if (m_Pieces[kk].Get_z()>minz)
						no_se_puede=true;
					
				}

			}

			//Aqui llamamos al Grasp para que coloque los bins
			if (vol<=voltemp && no_se_puede==false)
			{
				//Si hay mas piezas que caben aqui
				if (vol>0)
				{
					m_total_volumen_ocupado=0;
					for (int j=0;j<m_Q;j++)
					{
						m_Pieces_Tabu[j]=0;
					}

					std::list< std::pair< int ,std::list<CONFIGURACAO> > > lista;
					printf("una pieza");
					ORIG setmin(0,0,0);
					CONFIGURACAO C(this,setmin,999999);
					m_tipo_origen=0;
					int X=m_X;
					int Y=m_Y;
					int Z=m_Z;
					m_X=m_Pieces[k].Get_x();
					m_Y=m_Y;
					m_Z=m_Pieces[k].Get_z();
					C.CambiarConfiguracao(1,1,1,1,m_Pieces[k].Get_x(),m_Pieces[k].Get_y(),m_Pieces[k].Get_z(), m_Pieces[k].Get_Id(),0);
					lista.clear();
					RellenarVariosBin(lista,1,true,C);
					m_X=X;
					m_Y=Y;
					m_Z=Z;
					//puedo quitar estos items
					if (m_total_volumen_ocupado==(vol+(m_Pieces[k].Get_x()*m_Pieces[k].Get_y()*m_Pieces[k].Get_z()))  )
					{
						quitar=true;
						for (register int kj=0;kj<kkQ;kj++)
						{
							if (m_Pieces_Tabu[kj]>0)
							{
								//Eliminar la que tenga id igual kj
								EliminarPieza(kj);
							}
						}
										for (int i=0;i<10;i++)
				printf("Y");
						m_total_volumen+=ky*z*x;

						m_Pieces[k].Set_y(m_Y);
					}

				}
				//solamente hay una pieza
				else
				{
						m_total_volumen+=ky*z*x;

					m_Pieces[k].Set_y(m_Y);


				}

			}
		}

	}


	if (quitar==true)
	{
		std::vector< PIECE > ::iterator it;
		int id=0;
		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
		{
			(*it).Set_Id(id);
		}	

	}
	m_total_volumen_ocupado=0;
}
//Esta funcion intenta hacer mas grandes las piezas 

//que no puedan entrar con mas piezas quito esas piezas y hago mas grande el bin
void CONTAINER::ReducirPiezasZ()
{
	if (m_Z==1)
		return;
	return;
	m_tipo_orden_pieces=2;
	std::sort(m_Pieces.begin(),m_Pieces.end());

	bool quitar=false;
	for (int j=0;j<m_Q;j++)
	{
		m_Pieces_Tabu.push_back(0);
	}
	int kkQ=m_Q;
	for (register int k=0;k<m_Q;k++)
	{
		bool no_se_puede=false;
		int x=m_Pieces[k].Get_x();
		int y=m_Pieces[k].Get_y();
		int z=m_Pieces[k].Get_z();
		//Primero para las X
		if (2*m_Pieces[k].Get_z()>m_Z )
		{
			int vol=0;
			int volmin=0;
			int kz=m_Z-m_Pieces[k].Get_z();
			int voltemp=kz*y*x;
			int miny=m_Pieces[k].Get_y();
			int minz=kz;
			int minx=m_Pieces[k].Get_x();
			if (kz==0) 
				no_se_puede=true;
			//Miramos todas las que estan fuera y medimos los volumenes
			for (register int kk=0;kk<m_Q && no_se_puede==false;kk++)
			{
				if ((m_Pieces[kk].Get_z()<=kz) )
				{
//					m_Pieces[kk].Set_Num(m_Pieces[kk].Get_q());
					vol+=m_Pieces[kk].Get_Volumen();
					if (m_Pieces[kk].Get_x()>minx)
						no_se_puede=true;
					if (m_Pieces[kk].Get_y()>miny)
						no_se_puede=true;
					
				}

			}

			//Aqui llamamos al Grasp para que coloque los bins
			if (vol<=voltemp && no_se_puede==false)
			{
				//Si hay mas piezas que caben aqui
				if (vol>0)
				{
					m_total_volumen_ocupado=0;
					for (int j=0;j<m_Q;j++)
					{
						m_Pieces_Tabu[j]=0;
					}

					std::list< std::pair< int ,std::list<CONFIGURACAO> > > lista;
					printf("una pieza");
					ORIG setmin(0,0,0);
					CONFIGURACAO C(this,setmin,999999);
					m_tipo_origen=0;
					int X=m_X;
					int Y=m_Y;
					int Z=m_Z;
					m_X=m_Pieces[k].Get_x();
					m_Y=m_Pieces[k].Get_y();
					m_Z=m_Z;
					C.CambiarConfiguracao(1,1,1,1,m_Pieces[k].Get_x(),m_Pieces[k].Get_y(),m_Pieces[k].Get_z(), m_Pieces[k].Get_Id(),0);
					lista.clear();
					RellenarVariosBin(lista,1,true,C);
					m_X=X;
					m_Y=Y;
					m_Z=Z;
					//puedo quitar estos items
					if (m_total_volumen_ocupado==(vol+(m_Pieces[k].Get_x()*m_Pieces[k].Get_y()*m_Pieces[k].Get_z()))  )
					{
						quitar=true;
						for (register int kj=0;kj<kkQ;kj++)
						{
							if (m_Pieces_Tabu[kj]>0)
							{
								//Eliminar la que tenga id igual kj
								EliminarPieza(m_Pieces[k].Get_Id());
							}
						}
						for (int i=0;i<10;i++)
							printf("Z");
						m_total_volumen+=kz*y*x;
						m_Pieces[k].Set_z(m_Z);
					}

				}
				//solamente hay una pieza
				else
				{
						m_total_volumen+=kz*y*x;

					m_Pieces[k].Set_z(m_Z);


				}

			}
		}

	}


	if (quitar==true)
	{
		std::vector< PIECE > ::iterator it;
		int id=0;
		for (it=m_Pieces.begin(),id=0;it!=m_Pieces.end();it++,id++)
		{
			(*it).Set_Id(id);
		}	

	}
	m_total_volumen_ocupado=0;
}
void CONTAINER::knapsack_bouknap()
{
	std::vector<PEDIDO>::iterator itP = m_Pedidos.begin();
	int numpedidos = m_Pedidos.size();
	//Se crean los vectores de enteros, profit es lo que ganamos
	//weight es el peso 
	//m cuántos de esa pieza
	//x sería la solución
	int max = 0, todas = 0;
	int* profit = (int*)calloc(numpedidos, sizeof(int));
	int* weight = (int*)calloc(numpedidos, sizeof(int));
	int* m = (int*)calloc(numpedidos, sizeof(int));
	int* x = (int*)calloc(numpedidos, sizeof(int));
	/*for (int i = 0; i < 150; i++)
	{
		weight[i] = 0;
		profit[i] = 0;
		m[i] = 0;
		x[i] = 0;
	}*/
	for (int i = 0; i < numpedidos; i++, itP++)
	{
		int d = (*itP).Get_Volumen();
		profit[i] = (int)d;
		weight[i] = (int)d;
		//en este caso todos sería de 1
		m[i] = 1;

	}
	printf("Aqui 1");
	int z = bouknap(numpedidos, profit, weight, m, x, (m_X * m_Y * m_Z)*0.95);
	printf("Aqui 2");
	//z es lo máximo
	//en x ahora tendría cuáles escoge

	double pt = (double)z / (double)((double)m_X * m_Y * m_Z);
	printf("Cota superior: V=%d\t Porcentaje=%f\n", z, pt);
}

int CONTAINER::ValoresPosibles(int tipo,int c)
{
	//Tengo que mandarle el numpiezas
	int ctefobj=0,cota;
	int max=0,todas=0;
	int *profit=(int *)calloc(m_Q,sizeof(int));
	int *weight=(int *)calloc(m_Q,sizeof(int));
	int *m=(int *)calloc(m_Q,sizeof(int));
	int *x=(int *)calloc(m_Q,sizeof(int));
	for (int i=0;i<m_Q;i++)
	{
		if (tipo==0)
		profit[i]=m_Pieces[i].Get_x();
		if (tipo==1)
		profit[i]=m_Pieces[i].Get_y();
		if (tipo==2)
		profit[i]=m_Pieces[i].Get_z();
		weight[i]=profit[i];
		m[i]=m_Pieces[i].Get_q()-m_Pieces[i].Get_Num();
		//maximo es lo ocupan todas las piezas
		max+=m[i]*profit[i];
		//El valor de todas las piezas
		todas+=profit[i]*m[i];
		//Si no es obligatoria en la función objetivo
	}
	//Si no puede meter todas las piezas en la mochila
	if (max> c) cota=bouknap(m_Q,profit,weight,m,x,c);
	else cota=todas;
	return cota;
//	printf("Todo %d Cota %d Fijo %d\n",cota+ctefobj,cota,ctefobj);
}
void CONTAINER::DibujarCaja3D(int x1, int y1, int z1, int x2, int y2, int z2, int Id, bool opaca)
{
}
void CONTAINER::DibujarCaja3DBin(int x1, int y1, int z1, int x2, int y2, int z2, int Id, bool opaca, int corx, int cory)
{
}
void CONTAINER::DibujarBloques(std::list < CONFIGURACAO > &lista_configuracaos, int corx, int cory)
{
}
void CONTAINER::DibujarBloques(std::list < CONFIGURACAO > &lista_configuracaos)
{
}
void CONTAINER::DibujarSolucion(std::list < std::pair< int, std::list < CONFIGURACAO > > > &lista_configuracaos)
{
}
void CONTAINER::DibujarSolucion(std::list< SPACE > &lista_espacios, std::list < CONFIGURACAO > &lista_configuracaos)
{
}
void CONTAINER::JuntarPiezasParecidas()
{
	for (register int i = 0; i < m_Q; i++)
	{
		//Elijo una pieza y recorro la lista hasta encontra alguna que sea parecida
		//busco en altura
		if (i == m_Q - 1) continue;

		for (register int k = (i + 1); k < m_Q; k++)
		{
			//No voy a juntar una consigo misma
			//Ahora tengo dos piezas
			//Casos 
			//si puede estar en esta posicion
			if (m_Pieces[i].Get_Rx() == true)
			{
				//son igual en una, me falta la otra
				if (m_Pieces[k].Get_Rx() == true && m_Pieces[k].Get_x() == m_Pieces[i].Get_x())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_y(), m_Pieces[i].Get_z(), m_Pieces[i].Get_x(), m_Pieces[k].Get_y(), m_Pieces[k].Get_z(), 1, 1);
					//en este caso ya tengo que son iguales 

				}
				if (m_Pieces[k].Get_Ry() == true && m_Pieces[k].Get_y() == m_Pieces[i].Get_x())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_y(), m_Pieces[i].Get_z(), m_Pieces[i].Get_x(), m_Pieces[k].Get_x(), m_Pieces[k].Get_z(), 1, 3);
					//en este caso ya tengo que son iguales 

				}
				if (m_Pieces[k].Get_Rz() == true && m_Pieces[k].Get_z() == m_Pieces[i].Get_x())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_y(), m_Pieces[i].Get_z(), m_Pieces[i].Get_x(), m_Pieces[k].Get_y(), m_Pieces[k].Get_x(), 1, 5);
					//en este caso ya tengo que son iguales 

				}

			}
			//O en esta
			if (m_Pieces[i].Get_Ry() == true)
			{
				//son igual en una, me falta la otra
				if (m_Pieces[k].Get_Rx() == true && m_Pieces[k].Get_x() == m_Pieces[i].Get_y())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_x(), m_Pieces[i].Get_z(), m_Pieces[i].Get_y(), m_Pieces[k].Get_y(), m_Pieces[k].Get_z(), 3, 1);
					//en este caso ya tengo que son iguales 

				}
				if (m_Pieces[k].Get_Ry() == true && m_Pieces[k].Get_y() == m_Pieces[i].Get_y())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_x(), m_Pieces[i].Get_z(), m_Pieces[i].Get_y(), m_Pieces[k].Get_x(), m_Pieces[k].Get_z(), 3, 3);
					//en este caso ya tengo que son iguales 

				}
				if (m_Pieces[k].Get_Rz() == true && m_Pieces[k].Get_z() == m_Pieces[i].Get_y())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_x(), m_Pieces[i].Get_z(), m_Pieces[i].Get_y(), m_Pieces[k].Get_x(), m_Pieces[k].Get_y(), 3, 5);
					//en este caso ya tengo que son iguales 

				}

			}
			//o en esta
			if (m_Pieces[i].Get_Rz() == true)
			{
				//son igual en una, me falta la otra
				if (m_Pieces[k].Get_Rx() == true && m_Pieces[k].Get_x() == m_Pieces[i].Get_z())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_x(), m_Pieces[i].Get_y(), m_Pieces[i].Get_z(), m_Pieces[k].Get_y(), m_Pieces[k].Get_z(), 5, 1);
					//en este caso ya tengo que son iguales 

				}
				if (m_Pieces[k].Get_Ry() == true && m_Pieces[k].Get_y() == m_Pieces[i].Get_z())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_x(), m_Pieces[i].Get_y(), m_Pieces[i].Get_z(), m_Pieces[k].Get_x(), m_Pieces[k].Get_z(), 5, 3);
					//en este caso ya tengo que son iguales 

				}
				if (m_Pieces[k].Get_Rz() == true && m_Pieces[k].Get_z() == m_Pieces[i].Get_z())
				{

					PuedoJuntarParecidas(i, k, m_Pieces[i].Get_x(), m_Pieces[i].Get_y(), m_Pieces[i].Get_z(), m_Pieces[k].Get_x(), m_Pieces[k].Get_y(), 5, 5);
					//en este caso ya tengo que son iguales 

				}
			}


		}
	}
}

//esta funcion mira si puedo juntar y los junta si es posible
void CONTAINER::PuedoJuntarParecidas(int pieza1, int pieza2, int ancho1, int largo1, int alto1, int ancho2, int largo2, short int tipo1, short int tipo2)
{
	//Un criterio puede ser dejar todas los que tenga un tanto 
	//por ciento menor
	double factor = 0.02;
	int total_area_junta = (ancho1*largo1 + ancho2 * largo2);
	double minima_per = (double)factor*(double)total_area_junta;
	//sin rotar ninguna
	if (largo2 > largo1)
	{
		int tipo_o1 = tipo1;
		int tipo_o2 = tipo2;
		if ((((double)largo2 - largo1)*ancho1) <= minima_per)
		{
			BLOQUE B(pieza2, pieza1, ancho1 + ancho2, largo2, alto1, ancho2, largo2, ancho1, largo1, this, 1, 1, tipo_o1, tipo_o2);
			m_Bloques.push_back(B);

		}
		else
		{
			//tiene perdida 0 eso seguro
			if ((double)(largo2%largo1)*ancho1 <= minima_per && (largo1*m_Pieces[pieza1].Get_q()) >= largo2)
			{
				BLOQUE B(pieza2, pieza1, ancho1 + ancho2, largo2, alto1, ancho2, largo2, ancho1, largo1, this, 1, (largo2 / largo1), tipo_o1, tipo_o2);
				m_Bloques.push_back(B);
			}
		}

	}
	else
	{
		int tipo_o1 = tipo1;
		int tipo_o2 = tipo2;

		if ((((double)largo1 - largo2)*ancho2) <= minima_per)
		{
			BLOQUE B(pieza1, pieza2, ancho1 + ancho2, largo1, alto1, ancho1, largo1, ancho2, largo2, this, 1, 1, tipo_o1, tipo_o2);
			m_Bloques.push_back(B);

		}
		else
		{

			if ((double)(largo1%largo2)*ancho2 <= minima_per && (largo2*m_Pieces[pieza2].Get_q()) >= largo1)
			{
				BLOQUE B(pieza1, pieza2, ancho1 + ancho2, largo1, alto1, ancho1, largo1, ancho2, largo2, this, 1, (largo1 / largo2), tipo_o1, tipo_o2);
				m_Bloques.push_back(B);
			}
		}

	}
	//rotadas las dos

	if (ancho2 > ancho1)
	{
		int tipo_o1 = tipo1 + 1;
		int tipo_o2 = tipo2 + 1;
		if ((((double)ancho2 - ancho1)*largo1) <= minima_per)
		{
			BLOQUE B(pieza2, pieza1, largo1 + largo2, ancho2, alto1, largo2, ancho2, largo1, ancho1, this, 1, 1, tipo_o1, tipo_o2);
			m_Bloques.push_back(B);

		}
		else
		{
			//tiene perdida 0 eso seguro
			if ((double)(ancho2%ancho1)*largo1 <= minima_per && (ancho1*m_Pieces[pieza1].Get_q()) >= ancho2)
			{
				BLOQUE B(pieza2, pieza1, largo1 + largo2, ancho2, alto1, largo2, ancho2, largo1, ancho1, this, 1, (ancho2 / ancho1), tipo_o1, tipo_o2);
				m_Bloques.push_back(B);
			}
		}

	}
	else
	{
		int tipo_o1 = tipo1 + 1;
		int tipo_o2 = tipo2 + 1;

		if ((((double)ancho1 - ancho2)*largo2) <= minima_per)
		{
			BLOQUE B(pieza1, pieza2, largo1 + largo2, ancho1, alto1, largo1, ancho1, largo2, ancho2, this, 1, 1, tipo_o1, tipo_o2);
			m_Bloques.push_back(B);

		}
		else
		{
			//tiene perdida 0 eso seguro
			if (((double)(ancho1%ancho2)*largo2) <= minima_per && (ancho2*m_Pieces[pieza2].Get_q()) >= ancho1)
			{
				BLOQUE B(pieza1, pieza2, largo1 + largo2, ancho1, alto1, largo1, ancho1, largo2, ancho2, this, 1, (ancho1 / ancho2), tipo_o1, tipo_o2);
				m_Bloques.push_back(B);
			}
		}
	}
	//rotada la segunda
	if (ancho2 > largo1)
	{
		int tipo_o1 = tipo1;
		int tipo_o2 = tipo2 + 1;

		if ((((double)ancho2 - largo1)*ancho1) <= minima_per)
		{
			BLOQUE B(pieza2, pieza1, largo2 + ancho1, ancho2, alto1, largo2, ancho2, ancho1, largo1, this, 1, 1, tipo_o1, tipo_o2);
			m_Bloques.push_back(B);

		}
		else
		{
			//tiene perdida 0 eso seguro
			if (((double)(ancho2%largo1)*ancho1) <= minima_per && (largo1*m_Pieces[pieza1].Get_q()) >= ancho2)
			{
				BLOQUE B(pieza2, pieza1, largo2 + ancho1, ancho2, alto1, largo2, ancho2, ancho1, largo1, this, 1, (ancho2 / largo1), tipo_o1, tipo_o2);
				m_Bloques.push_back(B);
			}
		}
	}
	else
	{
		int tipo_o1 = tipo1;
		int tipo_o2 = tipo2 + 1;

		if ((((double)largo1 - ancho2)*largo2) <= minima_per)
		{
			BLOQUE B(pieza1, pieza2, largo2 + ancho1, largo1, alto1, ancho1, largo1, largo2, ancho2, this, 1, 1, tipo_o1, tipo_o2);
			m_Bloques.push_back(B);

		}
		else
		{
			//tiene perdida 0 eso seguro
			if (((double)(largo1%ancho2)*largo2) <= minima_per && (ancho2*m_Pieces[pieza2].Get_q()) >= largo1)
			{
				BLOQUE B(pieza1, pieza2, largo2 + ancho1, largo1, alto1, ancho1, largo1, largo2, ancho2, this, 1, (largo1 / ancho2), tipo_o1, tipo_o2);
				m_Bloques.push_back(B);
			}
		}
	}
	//rotada la primera
	if (ancho1 > largo2)
	{
		int tipo_o1 = tipo1 + 1;
		int tipo_o2 = tipo2;

		if ((((double)ancho1 - largo2)*ancho2) <= minima_per)
		{
			BLOQUE B(pieza1, pieza2, largo1 + ancho2, ancho1, alto1, largo1, ancho1, ancho2, largo2, this, 1, 1, tipo_o1, tipo_o2);
			m_Bloques.push_back(B);

		}
		else
		{
			//tiene perdida 0 eso seguro
			if (((double)(ancho1%largo2)*ancho2) <= minima_per && (largo2*m_Pieces[pieza2].Get_q()) >= ancho1)
			{
				BLOQUE B(pieza1, pieza2, largo1 + ancho2, ancho1, alto1, largo1, ancho1, ancho2, largo2, this, 1, (ancho1 / largo2), tipo_o1, tipo_o2);
				m_Bloques.push_back(B);
			}
		}

	}
	else
	{
		int tipo_o1 = tipo1 + 1;
		int tipo_o2 = tipo2;

		if ((((double)largo2 - ancho1)*largo1) <= minima_per)
		{
			BLOQUE B(pieza2, pieza1, largo1 + ancho2, largo2, alto1, ancho2, largo2, largo1, ancho1, this, 1, 1, tipo_o1, tipo_o2);
			m_Bloques.push_back(B);

		}
		else
		{
			//tiene perdida 0 eso seguro
			if (((double)(largo2%ancho1)*largo1) <= minima_per && (ancho1*m_Pieces[pieza1].Get_q()) >= largo2)
			{
				BLOQUE B(pieza2, pieza1, largo1 + ancho2, largo2, alto1, ancho2, largo2, largo1, ancho1, this, 1, (largo2 / ancho1), tipo_o1, tipo_o2);
				m_Bloques.push_back(B);
			}
		}
	}
}
void CONTAINER::ElegirConfiguracaoBloque(SPACE &Espacio, CONFIGURACAO &Configuracao)
{
	//Para el aleatorizado hago una estimacion que va a ser una estimacion d
	//los que puedo tener en la lista mas o menos
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
		//if (m_full_supported == true)
		//{
			std::list< BLOQUE > ::iterator itb;
			for (itb = m_Bloques.begin(); itb != m_Bloques.end(); itb++)
			{
				//m_Container->Get_Piezas()[id1].Get_q() / num1, m_Container->Get_Piezas()[id2].Get_q() / num2
				if ((*itb).Get_Num1()<=m_Pieces[(*itb).Get_Id1()].Get_q()- m_Pieces[(*itb).Get_Id1()].Get_Num() && (*itb).Get_Num2() <= m_Pieces[(*itb).Get_Id2()].Get_q()- m_Pieces[(*itb).Get_Id2()].Get_Num())
				    Configuracao.MejorCapaDeUnaBloque(Espacio, (*itb));

			}

		//}
		//		}
		for (int imc = 0; imc < m_Q; imc++)
		{

			if (m_Pieces[imc].Get_Num() < m_Pieces[imc].Get_q())
				Configuracao.MejorCapaDeUnaPieza(Espacio, m_Pieces[imc]);
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

			if (m_Pieces[imc].Get_Num() < m_Pieces[imc].Get_q())
				//Cambiar para que vaya con columnas
				Configuracao.MejorColumnaDeUnaPieza(Espacio, m_Pieces[imc]);
		}

	}
	//Si es aleatorizado ya tengo todos ahora tengo que elegir uno
	if (m_Aleatorizado == true)
	{
		//Elegir uno al azar 
		//Puede ser que la estimacion sea por encima y luego no pueda
		//colocar tantas por esto
		int alea = get_random(0, min(m_TamRCL - 1, (int)m_ListaRCL.size() - 1));
		int cont = 0;
		std::list < CONFIGURACAO > ::iterator it;
		for (it = m_ListaRCL.begin(); it != m_ListaRCL.end(); it++)
		{
			if (alea == cont)
			{
				//si es un bloque mas tarde lo voy a meter
				if ((*it).Get_Id() < 1000)
					InsertarConfiguracaoOrden(*it, m_Configuracaos);
					/*m_Configuracaos.push_back((*it));*/

				//				m_total_volumen_ocupado+=(*it).Get_Volumen();
				Configuracao = (*it);
				m_ListaRCL.clear();
				return;
			}

			cont++;

		}
	}
	if (Configuracao.Get_Id() != 99999)
	{
		if (Configuracao.Get_Id() < 1000) //los bloques entran luego
			InsertarConfiguracaoOrden(Configuracao, m_Configuracaos);
			/*m_Configuracaos.push_back(Configuracao);*/

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
bool CONTAINER::Mejor_DistA_Que_DistB_Bloques(ORIG& A, int NumA, ORIG& B, int NumB, int Vol)
{
	//Comparo componente a componente
	if (A.GetPrimero() > B.GetPrimero()) return false;
	if (A.GetPrimero() < B.GetPrimero()) return true;
	if (A.GetSegundo() > B.GetSegundo()) return false;
	if (A.GetSegundo() < B.GetSegundo()) return true;
	if (A.GetTercero() > B.GetTercero()) return false;
	if (A.GetTercero() < B.GetTercero()) return true;
	if (NumA <= NumB) return true;
	else
		return false;
}

void CONTAINER::ElegirConfiguracaoBloqueAra(SPACE& Espacio, CONFIGURACAO& Configuracao)
{
	//std::set<BLOQUE_ARA*, compareBlocks>::iterator it, itfin = m_set_Bloques.end();
	bool perdida;
	int pack_area_x = 0, pack_area_z = 0;
	std::set<BLOQUE_ARA*, compareBlocks>::iterator it, itR, it2, elegido;
	std::set<BLOQUE_ARA*, compareBlocks> bloques_random;
	ORIG m_set_distancias;
	int numActual=0;
	int jjj = 0;
	int kkk = 0;
	int ncaben = 0;
	int max_iter = Max_Iter_VCS;
	int contador = 0;
	bool primero = true;
	bool entra = false;
	bool first = false;
	bool entra_rnd = false;
	bool evaluar = false;
	double VCS=0.0;
	std::vector<int> caben;
	int x1 = 0, y1 = 0, z1 = 0;
	if (m_objetivo_mixto == true)
	{
		if (get_random(0, 1) == 1)
			m_objetivo_vol = true;
		else
			m_objetivo_vol = false;
	}
	int cont = 0;
	m_boolrand = false;
	it = find_if(m_set_Bloques.begin(), m_set_Bloques.end(), buscar_por_volumen(Espacio, m_Pieces, m_all_bloques));
	if (it == m_set_Bloques.end())
		return;
	caben.push_back((**it).Get_Id());
	if (m_Random==true)
	{
		if (get_random(1, 100) <= m_var_geom)
		{
			elegido = it;
			first = true;
		}
		if (m_VCS == true && first == true)
		{
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
			VCS = VCS_Bloque(&m_Configuracaos, **it, Espacio, x1, y1, z1);
		}
		else if (m_VCS == true)
			evaluar = true;

		it2 = it;
		it2++;
		for (; it2 != m_set_Bloques.end() && contador < max_iter; it2++)
		{
			if (Espacio.Get_dx() < (**it2).Get_x())
				continue;
			if (Espacio.Get_dy() < (**it2).Get_y())
				continue;
			if (Espacio.Get_dz() < (**it2).Get_z())
				continue;
			std::map<int, int>::iterator itm, itmfin = (**it2).Get_num_pieces_tipo().end();
			bool puede = false;
			for (itm = ((**it2).Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
			{
				puede = m_Pieces[itm->first].Get_q() - m_Pieces[itm->first].Get_Num() >= itm->second;
				if (puede == false)
					break;
			}
			if (puede == false)
				continue;
			contador++;
			caben.push_back((**it2).Get_Id());
			if (get_random(1, 100) <= m_var_geom)
			{
				if (m_VCS == true)
				{
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
					double VCS_temp = VCS_Bloque(&m_Configuracaos, **it2, Espacio, x1, y1, z1);
					if (VCS_temp > VCS || evaluar==true)
					{
						evaluar = false;
						elegido = it2;
						VCS = VCS_temp;
						entra_rnd = true;
					}
				}
				else
				{
					elegido = it2;
					entra_rnd = true;
				}
			}
		}
		if (entra_rnd == false)
		{
			std::default_random_engine generator;
			std::geometric_distribution<int> distribution((double)m_var_geom/100);
			int ngeo = distribution(generator);
			if (ngeo <= caben.size() - 1 && ngeo > 0)
				elegido = find_if(m_set_Bloques.begin(), m_set_Bloques.end(), buscar_por_id(caben[ngeo]));
			else
				elegido = it;
		}
		it = elegido;
	}	
	else if (m_VCS == true)
	{
		double VCS = 0;
		std::set<BLOQUE_ARA*, compareBlocks>::iterator it2;
		for (it2 = it; it2 != m_set_Bloques.end() && contador < max_iter; it2++)
		{
			if (Espacio.Get_dx() < (**it2).Get_x())
				continue;
			if (Espacio.Get_dy() < (**it2).Get_y())
				continue;
			if (Espacio.Get_dz() < (**it2).Get_z())
				continue;
			std::map<int, int>::iterator itm, itmfin = (**it2).Get_num_pieces_tipo().end();
			bool puede = false;
			for (itm = ((**it2).Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
			{
				puede = m_Pieces[itm->first].Get_q() - m_Pieces[itm->first].Get_Num() >= itm->second;
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
				VCS=VCS_Bloque(&m_Configuracaos, **it2, Espacio, x1, y1, z1);
				continue;
			}
			double VCS_temp = VCS_Bloque(&m_Configuracaos, **it2, Espacio, x1, y1, z1);
			if (VCS_temp > VCS)
			{
				it = it2;
				VCS = VCS_temp;
			}
		}
	}
	else if (m_objetivo_vol == false)
	{
	/*	std::set<BLOQUE_ARA*, compareBlocks> bloques_fit;
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
				puede = m_Pieces[itm->first].Get_q() - m_Pieces[itm->first].Get_Num() >= itm->second;
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
				jjj = kkk;
				it = it2;
				if (m_set_distancias.GetPrimero() == 0 && m_set_distancias.GetPrimero() == 0 && m_set_distancias.GetPrimero() == 0)
					break;
			}
			/*printf("%d\t%d\n", kkk, jjj);*/
			if (primero == true)
				printf("mal1");
		}
	}
	if (m_full_supported==true)
		m_space_arriba = false;
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
	// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z)
	Configuracao.PonerMedidas1(x1, y1, z1, (**it).Get_x(), (**it).Get_y(), (**it).Get_z());
	Configuracao.Set_orig(Espacio.Get_origen_distancia());
	Configuracao.Set_Id((**it).Get_Id());
	Configuracao.Set_bloque(true);
	m_blo_pos++;
	ColocarPiezasBloque(x1, y1, z1, 0, 0, 0, **it, m_Configuracaos, Espacio.Get_origen_distancia());
}

void CONFIGURACAO::MejorCapaDeUnaBloque(SPACE &Espacio, BLOQUE &Pieza)
{
	if (Pieza.Get_Rz() == true)
	{
		CompararConCapas(1, Espacio, Pieza.Get_x(), Pieza.Get_y(), Pieza.Get_z(), Pieza.Get_Id(), min((m_Container->Get_Piezas()[Pieza.Get_Id1()].Get_q() - m_Container->Get_Piezas()[Pieza.Get_Id1()].Get_Num()) / Pieza.Get_Num1(), (m_Container->Get_Piezas()[Pieza.Get_Id2()].Get_q() - m_Container->Get_Piezas()[Pieza.Get_Id2()].Get_Num()) / Pieza.Get_Num2()));
		CompararConCapas(2, Espacio, Pieza.Get_y(), Pieza.Get_x(), Pieza.Get_z(), Pieza.Get_Id(), min((m_Container->Get_Piezas()[Pieza.Get_Id1()].Get_q() - m_Container->Get_Piezas()[Pieza.Get_Id1()].Get_Num()) / Pieza.Get_Num1(), (m_Container->Get_Piezas()[Pieza.Get_Id2()].Get_q() - m_Container->Get_Piezas()[Pieza.Get_Id2()].Get_Num()) / Pieza.Get_Num2())); //Hay que cambiar el piezas máximas
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
void CONFIGURACAO::MejorCapaDeUnaBloqueMov(SPACE &Espacio, BLOQUE &Pieza)
{
	if (Pieza.Get_Rz() == true)
	{
		CompararConCapas(1, Espacio, Pieza.Get_x(), Pieza.Get_y(), Pieza.Get_z(), Pieza.Get_Id(), min((m_Container->Get_Piezas()[Pieza.Get_Id1()].Get_q() - m_Container->GetPiecesTabu()[Pieza.Get_Id1()]) / Pieza.Get_Num1(), (m_Container->Get_Piezas()[Pieza.Get_Id2()].Get_q() - m_Container->GetPiecesTabu()[Pieza.Get_Id2()]) / Pieza.Get_Num2()));
		CompararConCapas(2, Espacio, Pieza.Get_y(), Pieza.Get_x(), Pieza.Get_z(), Pieza.Get_Id(), min((m_Container->Get_Piezas()[Pieza.Get_Id1()].Get_q() - m_Container->GetPiecesTabu()[Pieza.Get_Id1()]) / Pieza.Get_Num1(), (m_Container->Get_Piezas()[Pieza.Get_Id2()].Get_q() - m_Container->GetPiecesTabu()[Pieza.Get_Id2()]) / Pieza.Get_Num2())); 
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
void CONTAINER::ActualizarListasBloque(SPACE &EspacioT, CONFIGURACAO &Configuracao, bool poner)
{
	BLOQUE  &B = BuscarPiezasBloque(Configuracao.Get_Id());
	int kk2 = m_Pieces[B.Get_Id1()].Get_Num();
	bool quitar_piezas = false;
	bool fin = false;
	//Actualizo numero de piezas
	//para la primera
	//Primero actualizo el numero que  a su vez actualiza el flag
	m_Pieces[B.Get_Id1()].Add_Num(Configuracao.Get_Num()*B.Get_Num1());
	int kk21 = m_Pieces[B.Get_Id1()].Get_Num();
	m_total_volumen_ocupado += m_Pieces[B.Get_Id1()].Get_Volumen()*(Configuracao.Get_Num())*B.Get_Num1();
	//si he quitado una tipo de pieza
	if (m_Pieces[B.Get_Id1()].Get_Num() == m_Pieces[B.Get_Id1()].Get_q() &&
		(m_Pieces[B.Get_Id1()].Get_x() == m_dimension_menor || m_Pieces[B.Get_Id1()].Get_y() == m_dimension_menor || m_Pieces[B.Get_Id1()].Get_z() == m_dimension_menor))
	{
		MinimaDimension();
		quitar_piezas = true;
	}
	int kk = m_Pieces[B.Get_Id2()].Get_Num();
	//para la segunda
	m_Pieces[B.Get_Id2()].Add_Num(Configuracao.Get_Num()*B.Get_Num2());
	int kk22 = m_Pieces[B.Get_Id2()].Get_Num();

	m_total_volumen_ocupado += m_Pieces[B.Get_Id2()].Get_Volumen()*Configuracao.Get_Num()*B.Get_Num2();
	//si he quitado una tipo de pieza
	if (m_Pieces[B.Get_Id2()].Get_Num() == m_Pieces[B.Get_Id2()].Get_q() &&
		(m_Pieces[B.Get_Id2()].Get_x() == m_dimension_menor || m_Pieces[B.Get_Id2()].Get_y() == m_dimension_menor || m_Pieces[B.Get_Id2()].Get_z() == m_dimension_menor))
	{
		MinimaDimension();
		quitar_piezas = true;
	}

	//Ahora tengo que meter los nuevos espacios producidos por la configuracao 
	//ademas los tengo que meter en orden porque despues estarán ordenados y es ir colocandolos en le lugar correspondiente
	//Aqui tengo dos casos si no hay perdida es igual que antes 
//	if (B.Get_Perdida()==false)
//	{
	int p1 = B.Get_Id1();
	int p2 = B.Get_Id2();
	int n2 = B.Get_Num2();
	//		EliminarBloquesConEstaPieza(p1);
	//		EliminarBloquesConEstaPieza(p2);
		//Voy a quitar la ultima configuracion que he metido y voy 
		//en la lista de piezas y voy a meter aqui dos configuracaos nuevas y ademas elimino el espacio
		//primero las nuevas configuraciones 
		//esta es la grande
	ORIG setmin(0, 0, 0);
	CONFIGURACAO C1(this, setmin, 99999), C2(this, setmin, 99999);
	C1.Set_bloque(true);
	C2.Set_bloque(true);
	//if (poner == true)
	//{
	//	int jj = 0;
	//	std::list<CONFIGURACAO>::reverse_iterator it;
	//	for (it = m_Configuracaos.rbegin(); it != m_Configuracaos.rend() && jj < 2; it++)
	//	{
	//		if (jj == 0)
	//			C2 = *it;
	//		if (jj == 1)
	//			C1 = *it;
	//		jj++;
	//	}

	//}
	std::list< SPACE > lista_temp;
	CambiarConfiguracaoBloque(Configuracao, EspacioT, B, C1, C2, lista_temp, poner);
	/*if (poner == true)
		Configuracao = C;*/


	//	C1.Set_Id(-1000000);
	//	C2.Set_Id(-1000000);
	//if (C1.Get_y2() - C1.Get_y1() != m_Pieces[C1.Get_Id()].Get_y()*C1.Get_Num())
	//	printf("error conf 1");
	//if (C2.Get_y2() - C2.Get_y1() != m_Pieces[C2.Get_Id()].Get_y()*C2.Get_Num())
	//	printf("error conf 1");

	//std::list<CONFIGURACAO>::iterator itbl, itblfin = m_Configuracaos_Bloques.end();
	//for (itbl = m_Configuracaos_Bloques.begin(); itbl != itblfin && fin == false; itbl++)
	//{
	//	if ((*itbl).Get_x1() == Configuracao.Get_x1() &&
	//		(*itbl).Get_x2() == Configuracao.Get_x2() &&
	//		(*itbl).Get_y1() == Configuracao.Get_y1() &&
	//		(*itbl).Get_y2() == Configuracao.Get_y2() &&
	//		(*itbl).Get_z1() == Configuracao.Get_z1() &&
	//		(*itbl).Get_z2() == Configuracao.Get_z2() &&
	//		(*itbl).Get_Id() == Configuracao.Get_Id())
	//	{
	//		Configuracao = *itbl;
	//		fin = true;
	//	}
	//}
	//if (fin == false)
	//{
	//	Configuracao.Set_Id_bloque(m_Configuracaos_Bloques.size() + 1);
	//	m_Configuracaos_Bloques.push_back(Configuracao);
	//}
	//if (poner == false)
	//{
	//idbloque++;
	//	C1.Set_Id_bloque(idbloque);
	//	C2.Set_Id_bloque(idbloque);
	//}
	ComprobarLimites(C1);
	ComprobarLimites(C2);
	if (poner == false)
	{
		/*m_Configuracaos.push_back(C1);
		m_Configuracaos.push_back(C2);*/
		if (C2.Get_x1() == C1.Get_x2())
		{
			/*m_Configuracaos.push_back(C1);
			m_Configuracaos.push_back(C2);*/
			InsertarConfiguracaoOrden(C1, m_Configuracaos);
			InsertarConfiguracaoOrden(C2, m_Configuracaos);
		}
		else
		{
			if (C1.Get_x1() == C2.Get_x2())
			{
			/*	m_Configuracaos.push_back(C2);
				m_Configuracaos.push_back(C1);*/
				InsertarConfiguracaoOrden(C2, m_Configuracaos);
				InsertarConfiguracaoOrden(C1, m_Configuracaos);
			}
			else
			{
				if (C2.Get_z1() == C1.Get_z2())
				{
					/*m_Configuracaos.push_back(C1);
					m_Configuracaos.push_back(C2);*/
					InsertarConfiguracaoOrden(C1, m_Configuracaos);
					InsertarConfiguracaoOrden(C2, m_Configuracaos);
				}
				else
				{
					/*m_Configuracaos.push_back(C2);
					m_Configuracaos.push_back(C1);*/
					InsertarConfiguracaoOrden(C2, m_Configuracaos);
					InsertarConfiguracaoOrden(C1, m_Configuracaos);
				}

			}
		}
	}
	ActualizarEspaciosElegido(EspacioT, Configuracao, lista_temp);
	//if (m_full_supported == true)
	//{
	//	/*std::list<SPACE> lista_aux = m_Spaces;*/
	//	JuntarSpacesBloques(m_Spaces, lista_temp, Configuracao);
	//}
	ReducirBloquesConEstaPieza(p1, Configuracao.Get_Num());
	ReducirBloquesConEstaPieza(p2, Configuracao.Get_Num()*n2);

	//Eliminar este espacio
	std::list< SPACE > ::iterator it;
	//FALTA 
	for (it = m_Spaces.begin(); it != m_Spaces.end(); it++)
	{
		if ((*it).Get_x1() == EspacioT.Get_x1() && (*it).Get_x2() == EspacioT.Get_x2() &&
			(*it).Get_y1() == EspacioT.Get_y1() && (*it).Get_y2() == EspacioT.Get_y2() &&
			(*it).Get_z1() == EspacioT.Get_z1() && (*it).Get_z2() == EspacioT.Get_z2())
		{
			m_Spaces.erase(it);
			break;
		}

	}
	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin = m_Spaces.end();
	for (it = m_Spaces.begin(); it != m_Spaces.end();)
	{
		//Si se intersectan hacer los espacios
//			SPACE kk=(*it);
//		if ((*it).Get_Flag()==true) continue;
		if (!(Configuracao.Get_x2() <= (*it).Get_x1() || Configuracao.Get_x1() >= (*it).Get_x2())
			&& !(Configuracao.Get_y2() <= (*it).Get_y1() || Configuracao.Get_y1() >= (*it).Get_y2())
			&& !(Configuracao.Get_z2() <= (*it).Get_z1() || Configuracao.Get_z1() >= (*it).Get_z2()))
		{

			ActualizarEspaciosElegido((*it), Configuracao, lista_temp);

			//Tengo que hacer el -- porque me apunta al siguiente
			it = m_Spaces.erase(it);
		}
		else
			++it;

	}
	/*quitar_piezas = false;*/
	if (quitar_piezas == true)
	{
		if (m_multicontainer == false)
		{
			//Aqui pruebo si puede quitar alguno y es mas rapido
			if (m_eliminar_espacios == true)
			{
				std::list<SPACE> ::iterator itfin1 = m_Spaces.end();
				for (it = m_Spaces.begin(); it != itfin1;)
				{
					if (((m_dimension_menor > min(min((*it).Get_dx(), (*it).Get_dy()), (*it).Get_dz()))
						|| CabeAlguna((*it).Get_dx(), (*it).Get_dy(), (*it).Get_dz()) == false) && (*it).Get_y1()!=Configuracao.Get_y2())
					{
						it = m_Spaces.erase(it);

					}
					else
						++it;
				}
			}
		}
		else
		{
			std::list<SPACE> ::iterator itfin2 = m_Spaces.end();
			for (it = m_Spaces.begin(); it != itfin2;)
			{
				if ((m_dimension_menor_x > (*it).Get_dx()) ||
					(m_dimension_menor_y > (*it).Get_dy()) ||
					(m_dimension_menor_z > (*it).Get_dz()) ||
					(m_menor_volumen > (*it).Get_Volumen()))
				{
					it = m_Spaces.erase(it);

				}
				else
					++it;
			}
		}
	}

	//Buscar inclusiones pero solamente con  los nuevos entres ssi
	EliminarInclusionesNuevos(lista_temp);
	//Buscar inclusiones de los nuevos con los antiguos esta función me debería colocar ya las
	//nuevas ordenadas
	//Aqui pruebo si puede quitar alguno y es mas rapido

	EliminarInclusionesListaAntigua(m_Spaces,lista_temp);

	//Esta función incluye los nuevos en la lista 
	//15-09-06 
//	m_Spaces.insert(m_Spaces.begin(),lista_temp.begin(),lista_temp.end());
	ColocarOrdenadosNuevos(m_Spaces, lista_temp);

	/*EliminarInclusionesNuevos(m_Spaces);*/
	//	EliminarInclusiones();
	//	}

}
void CONTAINER::ActualizarListasBloqueMov(SPACE &EspacioT, CONFIGURACAO &Configuracao, std::list<SPACE> &lista_espacios, std::list<CONFIGURACAO> &lista_configuracaos, bool poner)
{
	BLOQUE  &B = BuscarPiezasBloque(Configuracao.Get_Id());
	int kk2 = m_Pieces_Tabu[B.Get_Id1()];
	bool quitar_piezas = false;
	bool fin = false;
	//Actualizo numero de piezas
	//para la primera
	//Primero actualizo el numero que  a su vez actualiza el flag
	//m_Pieces[B.Get_Id1()].Add_Num(Configuracao.Get_Num()*B.Get_Num1());
	m_Pieces_Tabu[B.Get_Id1()]+=Configuracao.Get_Num()*B.Get_Num1();
	if (m_Pieces_Tabu[B.Get_Id1()] > m_Pieces[B.Get_Id1()].Get_q())
		printf("fallo1");
	int kk21 = m_Pieces_Tabu[B.Get_Id1()];
	m_total_volumen_ocupado += m_Pieces[B.Get_Id1()].Get_Volumen()*(Configuracao.Get_Num())*B.Get_Num1();
	//si he quitado una tipo de pieza
	if (m_Pieces_Tabu[B.Get_Id1()] == m_Pieces[B.Get_Id1()].Get_q() &&
		(m_Pieces[B.Get_Id1()].Get_x() == m_dimension_menor || m_Pieces[B.Get_Id1()].Get_y() == m_dimension_menor || m_Pieces[B.Get_Id1()].Get_z() == m_dimension_menor))
	{
		MinimaDimensionMov();
		quitar_piezas = true;
	}
	int kk = m_Pieces_Tabu[B.Get_Id2()];
	//para la segunda
	m_Pieces_Tabu[B.Get_Id2()]+=Configuracao.Get_Num()*B.Get_Num2();
	if (m_Pieces_Tabu[B.Get_Id2()] > m_Pieces[B.Get_Id2()].Get_q())
		printf("fallo2");
	int kk22 = m_Pieces_Tabu[B.Get_Id2()];

	m_total_volumen_ocupado += m_Pieces[B.Get_Id2()].Get_Volumen()*Configuracao.Get_Num()*B.Get_Num2();
	//si he quitado una tipo de pieza
	if (m_Pieces_Tabu[B.Get_Id2()] == m_Pieces[B.Get_Id2()].Get_q() &&
		(m_Pieces[B.Get_Id2()].Get_x() == m_dimension_menor || m_Pieces[B.Get_Id2()].Get_y() == m_dimension_menor || m_Pieces[B.Get_Id2()].Get_z() == m_dimension_menor))
	{
		MinimaDimensionMov();
		quitar_piezas = true;
	}

	//Ahora tengo que meter los nuevos espacios producidos por la configuracao 
	//ademas los tengo que meter en orden porque despues estarán ordenados y es ir colocandolos en le lugar correspondiente
	//Aqui tengo dos casos si no hay perdida es igual que antes 
//	if (B.Get_Perdida()==false)
//	{
	int p1 = B.Get_Id1();
	int p2 = B.Get_Id2();
	int n2 = B.Get_Num2();
	//		EliminarBloquesConEstaPieza(p1);
	//		EliminarBloquesConEstaPieza(p2);
		//Voy a quitar la ultima configuracion que he metido y voy 
		//en la lista de piezas y voy a meter aqui dos configuracaos nuevas y ademas elimino el espacio
		//primero las nuevas configuraciones 
		//esta es la grande
	ORIG setmin(0, 0, 0);
	CONFIGURACAO C1(this, setmin, 99999), C2(this, setmin, 99999);
	if (poner == true)
	{
		int jj = 0;
		std::list<CONFIGURACAO>::reverse_iterator it;
		for (it = lista_configuracaos.rbegin(); it != lista_configuracaos.rend() && jj < 2; it++)
		{
			if (jj == 0)
				C2 = *it;
			if (jj == 1)
				C1 = *it;
			jj++;
		}

	}
	std::list< SPACE > lista_temp;
	CambiarConfiguracaoBloqueMov(Configuracao, EspacioT, B, C1, C2, lista_temp, poner, lista_espacios);
	C1.Set_bloque(true);
	C2.Set_bloque(true);
	/*if (poner == true)
		Configuracao = C;*/
	//if (C1.Get_y2() - C1.Get_y1() != m_Pieces[C1.Get_Id()].Get_y()*C1.Get_Num())
	//	printf("error conf 1");
	//if (C2.Get_y2() - C2.Get_y1() != m_Pieces[C2.Get_Id()].Get_y()*C2.Get_Num())
	//	printf("error conf 2");
	//	C1.Set_Id(-1000000);
	//	C2.Set_Id(-1000000);
	//std::list<CONFIGURACAO>::iterator itbl, itblfin = m_Configuracaos_Bloques.end();
	//for (itbl = m_Configuracaos_Bloques.begin(); itbl != itblfin && fin==false; itbl++)
	//{
	//	if ((*itbl).Get_x1() == Configuracao.Get_x1() &&
	//		(*itbl).Get_x2() == Configuracao.Get_x2() &&
	//		(*itbl).Get_y1() == Configuracao.Get_y1() &&
	//		(*itbl).Get_y2() == Configuracao.Get_y2() &&
	//		(*itbl).Get_z1() == Configuracao.Get_z1() &&
	//		(*itbl).Get_z2() == Configuracao.Get_z2() &&
	//		(*itbl).Get_Id() == Configuracao.Get_Id())
	//	{
	//		Configuracao = *itbl;
	//		fin = true;
	//	}
	//}
	//if (fin==false)
	//{
	//	Configuracao.Set_Id_bloque(m_Configuracaos_Bloques.size() + 1);
	//	m_Configuracaos_Bloques.push_back(Configuracao);
	//}
	//if (poner == false)
	//{
	/*idbloque++;
	C1.Set_Id_bloque(idbloque);
	C2.Set_Id_bloque(idbloque);*/
	//}
	if (poner == false)
	{
		/*lista_configuracaos.push_back(C1);
		lista_configuracaos.push_back(C2);*/
		if (C2.Get_x1() == C1.Get_x2())
		{
			/*lista_configuracaos.push_back(C1);
			lista_configuracaos.push_back(C2);*/
			InsertarConfiguracaoOrden(C1, lista_configuracaos);
			InsertarConfiguracaoOrden(C2, lista_configuracaos);
		}
		else
		{
			if (C1.Get_x1() == C2.Get_x2())
			{
				/*lista_configuracaos.push_back(C2);
				lista_configuracaos.push_back(C1);*/
				InsertarConfiguracaoOrden(C2, lista_configuracaos);
				InsertarConfiguracaoOrden(C1, lista_configuracaos);
			}
			else
			{
				if (C2.Get_z1() == C1.Get_z2())
				{
					/*lista_configuracaos.push_back(C1);
					lista_configuracaos.push_back(C2);*/
					InsertarConfiguracaoOrden(C1, lista_configuracaos);
					InsertarConfiguracaoOrden(C2, lista_configuracaos);
				}
				else
				{
					/*lista_configuracaos.push_back(C2);
					lista_configuracaos.push_back(C1);*/
					InsertarConfiguracaoOrden(C2, lista_configuracaos);
					InsertarConfiguracaoOrden(C1, lista_configuracaos);
				}

			}
		}
	}
	ActualizarEspaciosElegidoMov(EspacioT, Configuracao, lista_temp, lista_espacios);
	//if (m_full_supported == true)
	//{
	//	/*std::list<SPACE> lista_aux = lista_espacios;*/
	//	JuntarSpacesBloques(lista_espacios, lista_temp, Configuracao);
	//}
	ReducirBloquesConEstaPieza(p1, Configuracao.Get_Num());
	ReducirBloquesConEstaPieza(p2, Configuracao.Get_Num()*n2);

	//Eliminar este espacio
	std::list< SPACE > ::iterator it;
	//FALTA 
	for (it = lista_espacios.begin(); it != lista_espacios.end(); it++)
	{
		if ((*it).Get_x1() == EspacioT.Get_x1() && (*it).Get_x2() == EspacioT.Get_x2() &&
			(*it).Get_y1() == EspacioT.Get_y1() && (*it).Get_y2() == EspacioT.Get_y2() &&
			(*it).Get_z1() == EspacioT.Get_z1() && (*it).Get_z2() == EspacioT.Get_z2())
		{
			lista_espacios.erase(it);
			break;
		}

	}
	//Primero miro con los que hay ya que
	std::list< SPACE > ::iterator itfin = lista_espacios.end();
	for (it = lista_espacios.begin(); it != lista_espacios.end();)
	{
		//Si se intersectan hacer los espacios
//			SPACE kk=(*it);
//		if ((*it).Get_Flag()==true) continue;
		if (!(Configuracao.Get_x2() <= (*it).Get_x1() || Configuracao.Get_x1() >= (*it).Get_x2())
			&& !(Configuracao.Get_y2() <= (*it).Get_y1() || Configuracao.Get_y1() >= (*it).Get_y2())
			&& !(Configuracao.Get_z2() <= (*it).Get_z1() || Configuracao.Get_z1() >= (*it).Get_z2()))
		{

			ActualizarEspaciosElegidoMov((*it), Configuracao, lista_temp, lista_espacios);

			//Tengo que hacer el -- porque me apunta al siguiente
			it = lista_espacios.erase(it);
		}
		else
			++it;

	}
	/*quitar_piezas = false;*/
	if (m_multicontainer == false)
	{
		//Aqui pruebo si puede quitar alguno y es mas rapido
		if (m_eliminar_espacios == true && quitar_piezas == true)
		{
			std::list<SPACE> ::iterator itfin1 = lista_espacios.end();
			for (it = lista_espacios.begin(); it != itfin1;)
			{
				if (((m_dimension_menor > min(min((*it).Get_x2() - (*it).Get_x1(), (*it).Get_y2() - (*it).Get_y1()), (*it).Get_z2() - (*it).Get_z1()))
					|| CabeAlgunaMov((*it).Get_x2() - (*it).Get_x1(), (*it).Get_y2() - (*it).Get_y1(), (*it).Get_z2() - (*it).Get_z1()) == false)&&(*it).Get_y1()!=Configuracao.Get_y2())
				{
					it = lista_espacios.erase(it);

				}
				else
					++it;
			}
		}
	}
	else
	{
		std::list<SPACE> ::iterator itfin1 = lista_espacios.end();
		for (it = lista_espacios.begin(); it != itfin1;)
		{
			if ((m_dimension_menor_x > (*it).Get_dx()) ||
				(m_dimension_menor_y > (*it).Get_dy()) ||
				(m_dimension_menor_z > (*it).Get_dz()) ||
				(m_menor_volumen > (*it).Get_Volumen()))
			{
				it = lista_espacios.erase(it);

			}
			else
				++it;
		}
	}
	//Buscar inclusiones pero solamente con  los nuevos entres ssi
	EliminarInclusionesNuevosBloque(lista_temp);
	//Buscar inclusiones de los nuevos con los antiguos esta función me debería colocar ya las
	//nuevas ordenadas
	//Aqui pruebo si puede quitar alguno y es mas rapido

	EliminarInclusionesListaAntigua(lista_espacios, lista_temp);

	//Esta función incluye los nuevos en la lista 
	//15-09-06 
//	m_Spaces.insert(m_Spaces.begin(),lista_temp.begin(),lista_temp.end());
	ColocarOrdenadosNuevos(lista_espacios, lista_temp);
	/*EliminarInclusionesNuevosBloque(lista_espacios);*/


	/*if (ComprobarConfiguracaosNoIntersectanSpaces(lista_configuracaos))
		SetDibujar(false);*/
	//	EliminarInclusiones();
	//	}
	//lista_espacios = lista_temp; //20/3/2019 linea comentada, en principio no hace falta
}

BLOQUE  &CONTAINER::BuscarPiezasBloque(int kblo)
{
	if (m_Bloques.size() == 0)
	{
		printf("whathappens");
		for (int i = 0;;);
	}
	std::list< BLOQUE> ::iterator itb, it1=m_Bloques.begin();
	for (itb = m_Bloques.begin(); itb != m_Bloques.end(); itb++)
	{
		if (kblo == (*itb).Get_Id())
			return (*itb);
	}
	printf("algo raro");
	return (*it1);
}
void CONTAINER::CambiarConfiguracaoBloque(CONFIGURACAO &C, SPACE &E, BLOQUE &B, CONFIGURACAO &C1, CONFIGURACAO &C2, std::list < SPACE > &lista, bool poner)
{
	if (poner == false)
	{
		C1.Set_Id(B.Get_Id1());
		C2.Set_Id(B.Get_Id2());
		C1.Set_dx(C.Get_dx());
		C1.Set_dy(C.Get_dy());
		C1.Set_dz(C.Get_dz());
		C2.Set_dx(C.Get_dx());
		C2.Set_dy(C.Get_dy());
		C2.Set_dz(C.Get_dz());
		C1.Set_Num(C.Get_Num()*B.Get_Num1());
		C2.Set_Num(C.Get_Num()*B.Get_Num2());
		C1.Set_Vol(m_Pieces[C1.Get_Id()].Get_Volumen()*C1.Get_Num());
		C2.Set_Vol(m_Pieces[C2.Get_Id()].Get_Volumen()*C2.Get_Num());
		C1.Set_orig(E.Get_origen_distancia());
		C2.Set_orig(E.Get_origen_distancia());
	}

	switch (C.Get_Tipo())
	{
		//original
	case 1:
	{
		if (poner == false)
		{
			C1.PonerMedidas2(C.Get_x1(), C.Get_y1(), C.Get_z1(), C.Get_x1() + (B.Get_x_P1()*C.Get_dx()), C.Get_y1() + (B.Get_y()*C.Get_dy()), C.Get_z1() + (B.Get_z_P1()*C.Get_dz()*B.Get_Num1()));
			C2.PonerMedidas2(C1.Get_x2(), C1.Get_y1(), C1.Get_z1(), C1.Get_x2() + (B.Get_x_P2()*C.Get_dx()), C.Get_y1() + (B.Get_y()*C.Get_dy()), C1.Get_z1() + (B.Get_z_P2()*C.Get_dz()*B.Get_Num2()));
		}
		//Ahora pongo los espacios vacios 
		//son tres uno en el que no podre poner nada
		//y dos grandes
		//SPACE Espacio(this, C.Get_x1(), C.Get_y1(), C.Get_z2(), C.Get_x2() - C.Get_x1(), C2.Get_y2() - C.Get_y1(), E.Get_z2() - C.Get_z2());
		//SPACE Espacio(this, C.Get_x1(), C.Get_y2(), C.Get_z1(), C.Get_x2() - C.Get_x1(), E.Get_y2() - C.Get_y2(), C2.Get_z2() - C.Get_z1());//26-4-19 cambio el de abajo por este
		/*if (min(C2.Get_z2(), C1.Get_z2()) != C2.Get_z2())
			printf("no cuadra");*/
		if (m_full_supported == true)
		{
			SPACE Espacio(this, 0, 0, 0, m_X, m_Y, m_Z);
			if (poner == false || C1.Get_z1() == C2.Get_z1())
				Espacio.ModificarSpace(C.Get_x1(), C.Get_y2(), C.Get_z1(), C.Get_x2(), E.Get_y2(), min(C2.Get_z2(), C1.Get_z2()));
			else
				Espacio.ModificarSpace(C.Get_x1(), C.Get_y2(), max(C2.Get_z1(), C1.Get_z1()), C.Get_x2(), E.Get_y2(), C.Get_z2());
			if (E.Get_origen_distancia() != 1 && poner == false)
				Espacio.CambiarEsquina(E);
			lista.push_back(Espacio);
		}
		//if (Espacio.Get_y2() != 233)
		//{
		//	Espacio.Set_y2(233);
		//}
		if (B.Get_Perdida() == true)
		{
			//				Asi tendrimaos dos arriba este mas pequeno

			//				SPACE Espacio2(this,C.Get_x1(),C.Get_y1(),C.Get_z2(),C1.Get_x2()-C.Get_x1(),C1.Get_y2()-C.Get_y1(),E.Get_z2()-C.Get_z2() );
			//SPACE Espacio3(this, C1.Get_x2(), C2.Get_y2(), C.Get_z1(), E.Get_x2() - C1.Get_x2(), E.Get_y2() - C2.Get_y2(), E.Get_z2() - C.Get_z1());
			SPACE Espacio3(this, 0, 0, 0, m_X, m_Y, m_Z);
			if (poner==false || C1.Get_z1() == C2.Get_z1())
			    Espacio3.ModificarSpace(C1.Get_x2(), E.Get_y1(), C2.Get_z2(), E.Get_x2(), E.Get_y2(), E.Get_z2());
			else
				Espacio3.ModificarSpace(C1.Get_x2(), E.Get_y1(), E.Get_z1(), E.Get_x2(), E.Get_y2(), C2.Get_z1());
			/*if (Espacio3.Get_y2() != 233)
			{
				Espacio3.Set_y2(233);
         }*/
			if (E.Get_origen_distancia() != 1 && poner==false)
			{
				//					Espacio2.CambiarEsquina(E);
				Espacio3.CambiarEsquina(E);

		    }
			//				lista.push_back(Espacio2);
			lista.push_back(Espacio3);
		}
		if (E.Get_origen_distancia() != 1 && poner ==false)
		{
			C1.CambiarEsquina(E);
			C2.CambiarEsquina(E);
			C.CambiarEsquina(E);
		}

		//el pequeno es el que tengo que meter 


	}
	break;
	case  2:
	{
		/*printf("case 2");*/
		if (poner == false)
		{
			C1.PonerMedidas2(C.Get_x1(), C.Get_y1(), C.Get_z1(), C.Get_x1() + (B.Get_z_P1()*C.Get_dx()*B.Get_Num1()), C.Get_y1() + (B.Get_y()*C.Get_dy()), C.Get_z1() + (B.Get_x_P1()*C.Get_dz()));
			C2.PonerMedidas2(C1.Get_x1(), C1.Get_y1(), C1.Get_z2(), C1.Get_x1() + (B.Get_z_P2()*C.Get_dx()*B.Get_Num2()), C.Get_y1() + (B.Get_y()*C.Get_dy()), C1.Get_z2() + (B.Get_x_P2()*C.Get_dz()));
		}
		//Ahora pongo los espacios vacios 
		//son tres uno en el que no podre poner nada
		//y dos grandes
		//SPACE Espacio(this, C.Get_x1(), C.Get_y1(), C.Get_z2(), C2.Get_x2() - C.Get_x1(), C.Get_y2() - C.Get_y1(), E.Get_z2() - C.Get_z2());
		if (m_full_supported == true)
		{
			SPACE Espacio(this, 0, 0, 0, m_X, m_Y, m_Z);
			if (poner == false || C1.Get_x1() == C2.Get_x1())
				Espacio.ModificarSpace(C.Get_x1(), C.Get_y2(), C.Get_z1(), min(C2.Get_x2(), C1.Get_x2()), E.Get_y2(), C.Get_z2());
			else
				Espacio.ModificarSpace(max(C2.Get_x1(), C1.Get_x1()), C.Get_y2(), C.Get_z1(), C.Get_x2(), E.Get_y2(), C.Get_z2());
			if (E.Get_origen_distancia() != 1 && poner == false)
				Espacio.CambiarEsquina(E);
			lista.push_back(Espacio);
		}
		/*if (Espacio.Get_y2() != 233)
		{
			Espacio.Set_y2(233);
		}*/
		if (B.Get_Perdida() == true)
		{
			//				Asi tendrimaos dos arriba este mas pequeno
			//				SPACE Espacio2(this,C.Get_x1(),C.Get_y1(),C.Get_z2(),C1.Get_x2()-C.Get_x1(),C1.Get_y2()-C.Get_y1(),E.Get_z2()-C.Get_z2() );
			//SPACE Espacio3(this, C2.Get_x2(), C1.Get_y2(), C.Get_z1(), E.Get_x2() - C2.Get_x2(), E.Get_y2() - C1.Get_y2(), E.Get_z2() - C.Get_z1());
			SPACE Espacio3(this, 0, 0, 0, m_X, m_Y, m_Z);
			if (poner == false || C1.Get_x1() == C2.Get_x1())
			    Espacio3.ModificarSpace(C2.Get_x2(), E.Get_y1(), C1.Get_z2(), E.Get_x2(), E.Get_y2(), E.Get_z2());
		   else
			    Espacio3.ModificarSpace(E.Get_x1(), E.Get_y1(), C1.Get_z2(), C2.Get_x1(), E.Get_y2(), E.Get_z2());
			/*if (Espacio3.Get_y2() != 233)
			{
				Espacio.Set_y2(233);
			}*/


			if (E.Get_origen_distancia() != 1 && poner == false)
			{
				//					Espacio2.CambiarEsquina(E);
				Espacio3.CambiarEsquina(E);

			}
		     //				lista.push_back(Espacio2);
			lista.push_back(Espacio3);
		}
		if (E.Get_origen_distancia() != 1 && poner == false)
		{
			C1.CambiarEsquina(E);
			C2.CambiarEsquina(E);
			C.CambiarEsquina(E);
		}

		//el pequeno va a caber nada
	}
	/*		break;
			case 3:
			{
				m_x1=Espacio.Get_x1(); m_x2=m_x1+ca*a;
				m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
				m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
			}
			break;
			case  4:
			{
				m_x1=Espacio.Get_x1(); m_x2=m_x1+ca*a;
				m_y2=Espacio.Get_y2(); m_y1=m_y2-cb*b;
				m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
			}
			break;
			case  5:
			{
				m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
				m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
				m_z1=Espacio.Get_z1(); m_z2=m_z1+cc*c;
			}
			break;
			case  6:
			{
				m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
				m_y2=Espacio.Get_y2(); m_y1=m_y2-cb*b;
				m_z1=Espacio.Get_z1(); m_z2=m_z1+cc*c;
			}
			break;
			case  7:
			{
				m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
				m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
				m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
			}
			break;
	*/
	}


}
void CONTAINER::CambiarConfiguracaoBloqueMov(CONFIGURACAO &C, SPACE &E, BLOQUE &B, CONFIGURACAO &C1, CONFIGURACAO &C2, std::list < SPACE > &lista, bool poner, std::list < SPACE > &lista_espacios)
{
	if (poner == false)
	{
		C1.Set_Id(B.Get_Id1());
		C2.Set_Id(B.Get_Id2());
		C1.Set_dx(C.Get_dx());
		C1.Set_dy(C.Get_dy());
		C1.Set_dz(C.Get_dz());
		C2.Set_dx(C.Get_dx());
		C2.Set_dy(C.Get_dy());
		C2.Set_dz(C.Get_dz());
		C1.Set_Num(C.Get_Num()*B.Get_Num1());
		C2.Set_Num(C.Get_Num()*B.Get_Num2());
		C1.Set_Vol(m_Pieces[C1.Get_Id()].Get_Volumen()*C1.Get_Num());
		C2.Set_Vol(m_Pieces[C2.Get_Id()].Get_Volumen()*C2.Get_Num());
		C1.Set_orig(E.Get_origen_distancia());
		C2.Set_orig(E.Get_origen_distancia());
	}

	switch (C.Get_Tipo())
	{
		//original
	case 1:
	{
		if (poner == false)
		{
			C1.PonerMedidas2(C.Get_x1(), C.Get_y1(), C.Get_z1(), C.Get_x1() + (B.Get_x_P1()*C.Get_dx()), C.Get_y1() + (B.Get_y()*C.Get_dy()), C.Get_z1() + (B.Get_z_P1()*C.Get_dz()*B.Get_Num1()));
			C2.PonerMedidas2(C1.Get_x2(), C1.Get_y1(), C1.Get_z1(), C1.Get_x2() + (B.Get_x_P2()*C.Get_dx()), C.Get_y1() + (B.Get_y()*C.Get_dy()), C1.Get_z1() + (B.Get_z_P2()*C.Get_dz()*B.Get_Num2()));
		}
		//Ahora pongo los espacios vacios 
		//son tres uno en el que no podre poner nada
		//y dos grandes
		//SPACE Espacio(this, C.Get_x1(), C.Get_y1(), C.Get_z2(), C.Get_x2() - C.Get_x1(), C2.Get_y2() - C.Get_y1(), E.Get_z2() - C.Get_z2());
		//SPACE Espacio(this, C.Get_x1(), C.Get_y2(), C.Get_z1(), C.Get_x2() - C.Get_x1(), E.Get_y2() - C.Get_y2(), C2.Get_z2() - C.Get_z1());//26-4-19 cambio el de abajo por este
		/*if (min(C2.Get_z2(), C1.Get_z2()) != C2.Get_z2())
			printf("no cuadra");*/
		if (m_full_supported == true)
		{
			SPACE Espacio(this, 0, 0, 0, m_X, m_Y, m_Z);
			if (poner == false || C1.Get_z1() == C2.Get_z1())
				Espacio.ModificarSpace(C.Get_x1(), C.Get_y2(), C.Get_z1(), C.Get_x2(), E.Get_y2(), min(C2.Get_z2(), C1.Get_z2()));
			else
				Espacio.ModificarSpace(C.Get_x1(), C.Get_y2(), max(C2.Get_z1(), C1.Get_z1()), C.Get_x2(), E.Get_y2(), C.Get_z2());
			if (E.Get_origen_distancia() != 1 && poner == false)
				Espacio.CambiarEsquina(E);
			lista.push_back(Espacio);
		}
		//if (Espacio.Get_y2() != 233)
		//{
		//	Espacio.Set_y2(233);
		//}
		if (B.Get_Perdida() == true)
		{
			//				Asi tendrimaos dos arriba este mas pequeno

			//				SPACE Espacio2(this,C.Get_x1(),C.Get_y1(),C.Get_z2(),C1.Get_x2()-C.Get_x1(),C1.Get_y2()-C.Get_y1(),E.Get_z2()-C.Get_z2() );
			//SPACE Espacio3(this, C1.Get_x2(), C2.Get_y2(), C.Get_z1(), E.Get_x2() - C1.Get_x2(), E.Get_y2() - C2.Get_y2(), E.Get_z2() - C.Get_z1());
			SPACE Espacio3(this, 0, 0, 0, m_X, m_Y, m_Z);
			if (poner == false || C1.Get_z1() == C2.Get_z1())
				Espacio3.ModificarSpace(C1.Get_x2(), E.Get_y1(), C2.Get_z2(), E.Get_x2(), E.Get_y2(), E.Get_z2());
			else
				Espacio3.ModificarSpace(C1.Get_x2(), E.Get_y1(), E.Get_z1(), E.Get_x2(), E.Get_y2(), C2.Get_z1());
			/*if (Espacio3.Get_y2() != 233)
			{
				Espacio3.Set_y2(233);
		 }*/
			if (E.Get_origen_distancia() != 1 && poner == false)
			{
				//					Espacio2.CambiarEsquina(E);
				Espacio3.CambiarEsquina(E);

			}
			//				lista.push_back(Espacio2);
			lista.push_back(Espacio3);
		}
		if (E.Get_origen_distancia() != 1 && poner == false)
		{
			C1.CambiarEsquina(E);
			C2.CambiarEsquina(E);
			C.CambiarEsquina(E);
		}

		//el pequeno es el que tengo que meter 


	}
	break;
	case  2:
	{
		/*printf("case 2");*/
		if (poner == false)
		{
			C1.PonerMedidas2(C.Get_x1(), C.Get_y1(), C.Get_z1(), C.Get_x1() + (B.Get_z_P1()*C.Get_dx()*B.Get_Num1()), C.Get_y1() + (B.Get_y()*C.Get_dy()), C.Get_z1() + (B.Get_x_P1()*C.Get_dz()));
			C2.PonerMedidas2(C1.Get_x1(), C1.Get_y1(), C1.Get_z2(), C1.Get_x1() + (B.Get_z_P2()*C.Get_dx()*B.Get_Num2()), C.Get_y1() + (B.Get_y()*C.Get_dy()), C1.Get_z2() + (B.Get_x_P2()*C.Get_dz()));
		}
		//Ahora pongo los espacios vacios 
		//son tres uno en el que no podre poner nada
		//y dos grandes
		//SPACE Espacio(this, C.Get_x1(), C.Get_y1(), C.Get_z2(), C2.Get_x2() - C.Get_x1(), C.Get_y2() - C.Get_y1(), E.Get_z2() - C.Get_z2());
		if (m_full_supported == true)
		{
			SPACE Espacio(this, 0, 0, 0, m_X, m_Y, m_Z);
			if (poner == false || C1.Get_x1() == C2.Get_x1())
				Espacio.ModificarSpace(C.Get_x1(), C.Get_y2(), C.Get_z1(), min(C2.Get_x2(), C1.Get_x2()), E.Get_y2(), C.Get_z2());
			else
				Espacio.ModificarSpace(max(C2.Get_x1(), C1.Get_x1()), C.Get_y2(), C.Get_z1(), C.Get_x2(), E.Get_y2(), C.Get_z2());
			if (E.Get_origen_distancia() != 1 && poner == false)
				Espacio.CambiarEsquina(E);
			lista.push_back(Espacio);
		}
		/*if (Espacio.Get_y2() != 233)
		{
			Espacio.Set_y2(233);
		}*/
		if (B.Get_Perdida() == true)
		{
			//				Asi tendrimaos dos arriba este mas pequeno
			//				SPACE Espacio2(this,C.Get_x1(),C.Get_y1(),C.Get_z2(),C1.Get_x2()-C.Get_x1(),C1.Get_y2()-C.Get_y1(),E.Get_z2()-C.Get_z2() );
			//SPACE Espacio3(this, C2.Get_x2(), C1.Get_y2(), C.Get_z1(), E.Get_x2() - C2.Get_x2(), E.Get_y2() - C1.Get_y2(), E.Get_z2() - C.Get_z1());
			SPACE Espacio3(this, 0, 0, 0, m_X, m_Y, m_Z);
			if (poner == false || C1.Get_x1() == C2.Get_x1())
				Espacio3.ModificarSpace(C2.Get_x2(), E.Get_y1(), C1.Get_z2(), E.Get_x2(), E.Get_y2(), E.Get_z2());
			else
				Espacio3.ModificarSpace(E.Get_x1(), E.Get_y1(), C1.Get_z2(), C2.Get_x1(), E.Get_y2(), E.Get_z2());
			/*if (Espacio3.Get_y2() != 233)
			{
				Espacio.Set_y2(233);
			}*/


			if (E.Get_origen_distancia() != 1 && poner == false)
			{
				//					Espacio2.CambiarEsquina(E);
				Espacio3.CambiarEsquina(E);

			}
			//				lista.push_back(Espacio2);
			lista.push_back(Espacio3);
		}
		if (E.Get_origen_distancia() != 1 && poner == false)
		{
			C1.CambiarEsquina(E);
			C2.CambiarEsquina(E);
			C.CambiarEsquina(E);
		}

		//el pequeno va a caber nada
	}
	/*		break;
			case 3:
			{
				m_x1=Espacio.Get_x1(); m_x2=m_x1+ca*a;
				m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
				m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
			}
			break;
			case  4:
			{
				m_x1=Espacio.Get_x1(); m_x2=m_x1+ca*a;
				m_y2=Espacio.Get_y2(); m_y1=m_y2-cb*b;
				m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
			}
			break;
			case  5:
			{
				m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
				m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
				m_z1=Espacio.Get_z1(); m_z2=m_z1+cc*c;
			}
			break;
			case  6:
			{
				m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
				m_y2=Espacio.Get_y2(); m_y1=m_y2-cb*b;
				m_z1=Espacio.Get_z1(); m_z2=m_z1+cc*c;
			}
			break;
			case  7:
			{
				m_x2=Espacio.Get_x2(); m_x1=m_x2-ca*a;
				m_y1=Espacio.Get_y1(); m_y2=m_y1+cb*b;
				m_z2=Espacio.Get_z2(); m_z1=m_z2-cc*c;
			}
			break;
	*/
	}


}
void CONFIGURACAO::PonerMedidas2(int x1, int y1, int z1, int x2, int y2, int z2)
{
	m_x1 = x1; m_y1 = y1; m_z1 = z1;
	m_x2 = x2; m_y2 = y2; m_z2 = z2;

}
void CONFIGURACAO::PonerMedidas1(int x1, int y1, int z1, int dx, int dy, int dz)
{
	m_x1 = x1; m_y1 = y1; m_z1 = z1;
	m_x2 = m_x1+dx; m_y2 = m_y1 + dy; m_z2 = m_z1 + dz;

}
void CONFIGURACAO::CambiarEsquina(SPACE &E)
{
	int x = m_x2 - m_x1;
	int y = m_y2 - m_y1;
	int z = m_z2 - m_z1;
	if (E.Get_origen_distancia() == 2)
	{
		m_y2 = E.Get_y2() - (m_y1 - E.Get_y1());
		m_y1 = m_y2 - y;
	}
	if (E.Get_origen_distancia() == 3)
	{
		m_z2 = E.Get_z2() - (m_z1 - E.Get_z1());
		m_z1 = m_z2 - z;
	}
	if (E.Get_origen_distancia() == 4)
	{
		m_y2 = E.Get_y2() - (m_y1 - E.Get_y1());
		m_y1 = m_y2 - y;
		m_z2 = E.Get_z2() - (m_z1 - E.Get_z1());
		m_z1 = m_z2 - z;
	}
	if (E.Get_origen_distancia() == 5)
	{
		m_x2 = E.Get_x2() - (m_x1 - E.Get_x1());
		m_x1 = m_x2 - x;
	}
	if (E.Get_origen_distancia() == 6)
	{
		m_y2 = E.Get_y2() - (m_y1 - E.Get_y1());
		m_y1 = m_y2 - y;
		m_x2 = E.Get_x2() - (m_x1 - E.Get_x1());
		m_x1 = m_x2 - x;
	}
	if (E.Get_origen_distancia() == 7)
	{
		m_z2 = E.Get_z2() - (m_z1 - E.Get_z1());
		m_z1 = m_z2 - z;
		m_x2 = E.Get_x2() - (m_x1 - E.Get_x1());;
		m_x1 = m_x2 - x;
	}
	if (E.Get_origen_distancia() == 8)
	{
		m_y2 = E.Get_y2() - (m_y1 - E.Get_y1());
		m_y1 = m_y2 - y;
		m_z2 = E.Get_z2() - (m_z1 - E.Get_z1());
		m_z1 = m_z2 - z;
		m_x2 = E.Get_x2() - (m_x1 - E.Get_x1());;
		m_x1 = m_x2 - x;
	}
}
void SPACE::CambiarEsquina(SPACE &E)
{
	if (E.Get_origen_distancia() == 2)
	{
		m_y2 = E.Get_y2() - (m_y1 - E.Get_y1());
		m_y1 = m_y2 - m_dy;
	}
	if (E.Get_origen_distancia() == 3)
	{
		m_z2 = E.Get_z2() - (m_z1 - E.Get_z1());
		m_z1 = m_z2 - m_dz;
	}
	if (E.Get_origen_distancia() == 4)
	{
		m_y2 = E.Get_y2() - (m_y1 - E.Get_y1());
		m_y1 = m_y2 - m_dy;
		m_z2 = E.Get_z2() - (m_z1 - E.Get_z1());
		m_z1 = m_z2 - m_dz;
	}
	if (E.Get_origen_distancia() == 5)
	{
		m_x2 = E.Get_x2() - (m_x1 - E.Get_x1());
		m_x1 = m_x2 - m_dx;
	}
	if (E.Get_origen_distancia() == 6)
	{
		m_y2 = E.Get_y2() - (m_y1 - E.Get_y1());
		m_y1 = m_y2 - m_dy;
		m_x2 = E.Get_x2() - (m_x1 - E.Get_x1());
		m_x1 = m_x2 - m_dx;
	}
	if (E.Get_origen_distancia() == 7)
	{
		m_z2 = E.Get_z2() - (m_z1 - E.Get_z1());
		m_z1 = m_z2 - m_dz;
		m_x2 = E.Get_x2() - (m_x1 - E.Get_x1());;
		m_x1 = m_x2 - m_dx;
	}
	if (E.Get_origen_distancia() == 8)
	{
		m_y2 = E.Get_y2() - (m_y1 - E.Get_y1());
		m_y1 = m_y2 - m_dy;
		m_z2 = E.Get_z2() - (m_z1 - E.Get_z1());
		m_z1 = m_z2 - m_dz;
		m_x2 = E.Get_x2() - (m_x1 - E.Get_x1());;
		m_x1 = m_x2 - m_dx;
	}
}
void CONTAINER::ReducirBloquesConEstaPieza(int kblo, int cuantos)
{
	std::list< BLOQUE> ::iterator itb;
	std::list<BLOQUE> ::iterator itbfin = m_Bloques.end();
	for (itb = m_Bloques.begin(); itb != itbfin;)
	{

		if (kblo == (*itb).Get_Id1() || kblo == (*itb).Get_Id2())
		{
			//if (m_Pieces[kblo].Get_Num() == m_Pieces[kblo].Get_q())
				//itb = m_Bloques.erase(itb); //Esto es lo que había en un principio, pero ahora no conviene eliminar un bloque de la lista cuando lo he puesto en la solución
			//else
			//{
				if (kblo == (*itb).Get_Id1())
					(*itb).Set_Num((*itb).Get_Num() - ceil((double)cuantos / (double)(*itb).Get_Num1()));
				if (kblo == (*itb).Get_Id2())
					(*itb).Set_Num((*itb).Get_Num() - ceil((double)cuantos / (double)(*itb).Get_Num2()));
				//if ((*itb).Get_Num() <= 0)
				//	itb = m_Bloques.erase(itb);
				//else
				//	++itb;
			//}
		}
		//else
			++itb;
	}
}
void CONTAINER::EliminarInclusionesNuevosBloque(std::list < SPACE > &Lista)
{
	std::list<SPACE> ::iterator itl, itl2;
	for (itl = Lista.begin(); itl != Lista.end(); itl++)
	{

		itl2 = itl;
		itl2++;

		if (itl2 == Lista.end())
			break;
		for (; itl2 != Lista.end(); itl2++)
		{

			if ((*itl2).Get_Volumen() < (*itl).Get_Volumen())
				continue;
			if ((*itl).Incluido(*itl2) == true)
			{

				//Me devuelve el puntero que apunta al siguiente
				//por tanto le tengo que quita algo
				itl = Lista.erase(itl);
				if (Lista.size() != 0)
				{
					if (itl != Lista.begin())
						itl--;
				}
				else
					return;
				break;



			}
		}

	}
}
void CONTAINER::EliminarInclusionesListaAntigua(std::list <SPACE > &Lista)
{
	bool entra = false;
	if (m_Spaces.size() == 0)
		return;
	std::list<SPACE> ::iterator itl;
	std::list<SPACE> ::reverse_iterator itl2;
	for (itl = Lista.begin(); itl != Lista.end();)
	{
		//		SPACE kk=(*itl);
		//		itl2=itl;
		//		itl2++;
		//		if (itl2==m_Spaces.end())
		//			break;
		for (itl2 = m_Spaces.rbegin(); itl2 != m_Spaces.rend(); itl2++)
		{
			//			SPACE kk2=(*itl2);
			if ((*itl2).Get_Volumen() < (*itl).Get_Volumen())
			{
				entra = true;
				++itl;
				break;
			}
			if ((*itl).Incluido((*itl2)) == true)
			{
				//Si esta incluido termina 
				entra = true;
				itl = Lista.erase(itl);
				if (Lista.size() == 0)
					return;
				/*if (Lista.size() != 0)
				{
					if (itl != Lista.begin())
						itl--;
				}
				else return;*/
				break;
			}
		}
		if (entra == false)
			++itl;
		else
			entra=false;
	}
}
void CONTAINER::ColocarOrdenadosNuevos(std::list< SPACE > &lista_temp)
{
	std::list< SPACE >::iterator it;
	for (it = lista_temp.begin(); it != lista_temp.end(); it++)
	{
		//		SPACE kk=(*it);
		InsertarOrden((*it));
	}
}
void CONTAINER::InsertarOrden(SPACE &Espacio)
{
	if( !(Espacio.Get_x1() >= 0 && m_X >= Espacio.Get_x2() &&
		Espacio.Get_y1() >= 0 && m_Y >= Espacio.Get_y2() &&
		Espacio.Get_z1() >= 0 && m_Z >= Espacio.Get_z2()))
	{
		for (int i = 0; ;);
	}
	//Por si solamente hay uno
	if (m_Spaces.size() == 0)
	{
		m_Spaces.push_back(Espacio);
		return;
	}

	std::list<SPACE> ::iterator itl;
	for (itl = m_Spaces.begin(); itl != m_Spaces.end(); itl++)
	{
		if ((*itl).Get_Volumen() > Espacio.Get_Volumen())
		{
			m_Spaces.insert(itl, Espacio);
			return;
		}
	}
	//Si no hay ninguno más pequeño al final
	m_Spaces.push_back(Espacio);
}

void CONTAINER::InsertarConfiguracaoOrden(CONFIGURACAO &C, std::list<CONFIGURACAO> &lista)
{
	if (C.Get_x1() == C.Get_x2() || C.Get_y1() == C.Get_y2() || C.Get_z1() == C.Get_z2())
		return;
	//lista.push_back(C);
	//return;
	if (!(m_full_supported == true))
	{
		lista.push_back(C);
		return;
	}
	if (lista.size() == 0)
	{
		lista.push_back(C);
		return;
	}

	std::list<CONFIGURACAO>::iterator it, itfin = lista.end();

	for (it=lista.begin();it!=itfin;it++)
	{
		if ((*it).Get_z2() == C.Get_z2())
		{
			if ((*it).Get_x1() == C.Get_x1())
			{
				if ((*it).Get_y1() == C.Get_y1())
				{
					if ((*it).Get_z1() >= C.Get_z1())
					{
						lista.insert(it, C);
						return;
					}
				}
				if ((*it).Get_y1() > C.Get_y1())
				{
					lista.insert(it, C);
					return;
				}
			}
			if ((*it).Get_x1() > C.Get_x1())
			{
				lista.insert(it, C);
				return;
			}
		}
		if ((*it).Get_z2() > C.Get_z2())
		{
			lista.insert(it, C);
			return;
		}
	}
	lista.push_back(C);
}
void CONTAINER::InsertarPedidoOrden(PEDIDO& P)
{
	if (m_Pedidos_ordenados.size() == 0)
	{
		m_Pedidos_ordenados.push_back(P);
		return;
	}

	std::vector<PEDIDO>::iterator it = m_Pedidos_ordenados.begin() , itfin = m_Pedidos_ordenados.end();
	for (;it!=itfin;)
	{
		if (P.Get_Volumen() > (*it).Get_Volumen())
		{
			m_Pedidos_ordenados.insert(it, P);
			return;
		}
		else
			it++;
	}
	m_Pedidos_ordenados.push_back(P);
}
//void CONTAINER::JuntarConfiguracaos(std::list<CONFIGURACAO>& lista, CONFIGURACAO& C)
//{
//	std::list<CONFIGURACAO>::iterator it, itfin = lista.end();
//	for (it = lista.begin(); it != itfin; it++)
//	{
//		if ((*it).Get_Id() != C.Get_Id())
//			continue;
//		if ((*it).Get_Tipo() != C.Get_Tipo())
//			continue;
//
//	}
//}
//bool CONTAINER::ComprobarContacto(CONFIGURACAO& C1, CONFIGURACAO& C2)
//{
//	if (C1.Get_x2() == C2.Get_x1())
//
//	if (C2.Get_x2() == C1.Get_x1())
//
//	if (C1.Get_y2() == C2.Get_y1())
//
//	if (C2.Get_y2() == C1.Get_y1())
//
//	if (C1.Get_z2() == C2.Get_z1())
//
//	if (C2.Get_z2() == C1.Get_z1())
//
//}
void CONTAINER::JuntarSpacesBloques(std::list<SPACE> &lista, std::list<SPACE> &lista_temp, CONFIGURACAO &Configuracao)
{
	std::list<SPACE> lista_final;
	std::list<SPACE>::iterator it, itfin = lista.end(), itN, itNfin = lista_temp.end();
	for (itN = lista_temp.begin(); itN != lista_temp.end(); itN++)
	{
		std::list<SPACE> lista_nueva;
		for (it = lista.begin(); it != itfin;)
		{
			if ((*it).Get_z1()==0 || (*itN).Get_z1()==0 || (*it).Get_z1()!=(*itN).Get_z1() || ((*it).Get_x2() != (*itN).Get_x1() && (*it).Get_x1() != (*itN).Get_x2() && (*it).Get_y2() != (*itN).Get_y1() && (*it).Get_y1() != (*itN).Get_y2())) //No se tocan
			{
				++it;
				continue;
			}
			if (((*it).Get_x2() == (*itN).Get_x1() || (*it).Get_x1() == (*itN).Get_x2()) && min((*it).Get_y2(), (*itN).Get_y2())>max((*it).Get_y1(), (*itN).Get_y1())) //Se tocan por los laterales
			{
				SPACE Espacio(min((*it).Get_x1(), (*itN).Get_x1()), max((*it).Get_y1(), (*itN).Get_y1()), (*itN).Get_z1(), max((*it).Get_x2(), (*itN).Get_x2()), min((*it).Get_y2(), (*itN).Get_y2()), min((*it).Get_z2(), (*itN).Get_z2()), this);
				if (Espacio.Get_dx() < 0 || Espacio.Get_dy() < 0 || Espacio.Get_dz() < 0)
					printf("jd");
				if (!(Configuracao.Get_x2() <= Espacio.Get_x1() || Configuracao.Get_x1() >= Espacio.Get_x2())
					&& !(Configuracao.Get_y2() <= Espacio.Get_y1() || Configuracao.Get_y1() >= Espacio.Get_y2())
					&& !(Configuracao.Get_z2() <= Espacio.Get_z1() || Configuracao.Get_z1() >= Espacio.Get_z2()))
				{
					++it;
					continue;
				}
				else
				{
					/*if ((*it).Incluido(Espacio) == true)
						it = lista.erase(it);
					else
						++it;*/
					InsertarOrden(lista_nueva, Espacio);
					InsertarOrden(lista_nueva, *it);
					++it;
				}
				continue;
			}
			if (((*it).Get_y2() == (*itN).Get_y1() || (*it).Get_y1() == (*itN).Get_y2()) && min((*it).Get_x2(), (*itN).Get_x2()) > max((*it).Get_x1(), (*itN).Get_x1()))  //Se tocan por delante o por detrás
			{
				SPACE Espacio(max((*it).Get_x1(), (*itN).Get_x1()), min((*it).Get_y1(), (*itN).Get_y1()), (*itN).Get_z1(), min((*it).Get_x2(), (*itN).Get_x2()), max((*it).Get_y2(), (*itN).Get_y2()), min((*it).Get_z2(), (*itN).Get_z2()), this);
				if (Espacio.Get_dx() < 0 || Espacio.Get_dy() < 0 || Espacio.Get_dz() < 0)
					printf("jd");
				if (!(Configuracao.Get_x2() <= Espacio.Get_x1() || Configuracao.Get_x1() >= Espacio.Get_x2())
					&& !(Configuracao.Get_y2() <= Espacio.Get_y1() || Configuracao.Get_y1() >= Espacio.Get_y2())
					&& !(Configuracao.Get_z2() <= Espacio.Get_z1() || Configuracao.Get_z1() >= Espacio.Get_z2()))
				{
					++it;
					continue;
				}
				else
				{
					/*if ((*it).Incluido(Espacio) == true)
						it = lista.erase(it);
					else*/
					InsertarOrden(lista_nueva, Espacio);
					InsertarOrden(lista_nueva, *it);
					++it;
				}
				continue;
			}
			else
				++it;
		}
		if (lista_nueva.size()>2)
		    JuntarSpacesNuevos(lista_nueva);
		std::list<SPACE>::iterator itE, itEfin = lista_nueva.end();
		for (itE = lista_nueva.begin(); itE != itEfin; itE++)
			InsertarOrden(lista_final, *itE);
		InsertarOrden(lista_final, *itN);
		EliminarInclusionesNuevos(lista_final);
	}
	lista_temp = lista_final;
}
void CONTAINER::JuntarSpacesNuevos(std::list<SPACE>& lista)
{
	std::list<SPACE>::iterator it, it2, itfin = lista.end();
	std::list<SPACE> lista_final;
	bool nuevos = false;
	for (it = lista.begin(); it != itfin; it++)
	{
		it2 = it;
		it2++;
		if (it2 == itfin)
			break;
		for (; it2 != lista.end(); it2++)
		{
			if ((*it).Get_x1() == (*it2).Get_x1() && (*it).Get_x2() == (*it2).Get_x2() && ((*it).Get_y2() >= (*it2).Get_y1() && (*it).Get_y2() <= (*it2).Get_y2() || (*it2).Get_y2() >= (*it).Get_y1() && (*it2).Get_y2() <= (*it).Get_y2()) && (*it).Get_z1() == (*it2).Get_z1())
			{
				SPACE Espacio((*it).Get_x1(), min((*it).Get_y1(), (*it2).Get_y1()), (*it).Get_z1(), (*it).Get_x2(), max((*it).Get_y2(), (*it2).Get_y2()), min((*it).Get_z2(), (*it2).Get_z2()), this);
				InsertarOrden(lista_final, Espacio);
				nuevos = true;
				continue;
			}
			if ((*it).Get_y1() == (*it2).Get_y1() && (*it).Get_y2() == (*it2).Get_y2() && ((*it).Get_x2() >= (*it2).Get_x1() && (*it).Get_x2() <= (*it2).Get_x2() || (*it2).Get_x2() >= (*it).Get_x1() && (*it2).Get_x2() <= (*it).Get_x2()) && (*it).Get_z1() == (*it2).Get_z1())
			{
				SPACE Espacio(min((*it).Get_x1(), (*it2).Get_x1()), (*it).Get_y1(), (*it).Get_z1(), max((*it).Get_x2(), (*it2).Get_x2()), (*it).Get_y2(), min((*it).Get_z2(), (*it2).Get_z2()), this);
				InsertarOrden(lista_final, Espacio);
				nuevos = true;
				continue;
			}
			if (((*it).Get_x2() == (*it2).Get_x1() || (*it).Get_x1() == (*it2).Get_x2()) && min((*it).Get_y2(), (*it2).Get_y2()) > max((*it).Get_y1(), (*it2).Get_y1()))  //Se tocan por los laterales
			{
				SPACE Espacio(min((*it).Get_x1(), (*it2).Get_x1()), max((*it).Get_y1(), (*it2).Get_y1()), (*it2).Get_z1(), max((*it).Get_x2(), (*it2).Get_x2()), min((*it).Get_y2(), (*it2).Get_y2()), min((*it).Get_z2(), (*it2).Get_z2()), this);
				InsertarOrden(lista_final, Espacio);
				nuevos = true;
				continue;
			}
			if (((*it).Get_y2() == (*it2).Get_y1() || (*it).Get_y1() == (*it2).Get_y2()) && min((*it).Get_x2(), (*it2).Get_x2()) > max((*it).Get_x1(), (*it2).Get_x1()))   //Se tocan por delante o por detrás
			{
				SPACE Espacio(max((*it).Get_x1(), (*it2).Get_x1()), min((*it).Get_y1(), (*it2).Get_y1()), (*it2).Get_z1(), min((*it).Get_x2(), (*it2).Get_x2()), max((*it).Get_y2(), (*it2).Get_y2()), min((*it).Get_z2(), (*it2).Get_z2()), this);
				InsertarOrden(lista_final, Espacio);
				nuevos = true;
				continue;
			}
		}
	}
	EliminarInclusionesNuevos(lista_final);
	if (nuevos == true)
		JuntarSpacesNuevos(lista_final);
	std::list<SPACE>::iterator itE, itEfin = lista.end();
	for (itE = lista.begin(); itE != itEfin; itE++)
		InsertarOrden(lista_final, *itE);
	lista = lista_final;
}

BLOQUE::BLOQUE(int id1, int id2, int x, int y, int z, CONTAINER *a, int num1, int num2)
{
	m_Id1 = id1;
	m_Id2 = id2;
	m_x = x; m_y = y; m_z = z;
	m_Volumen = m_x * m_y*m_z;
	m_Container = a;
	m_num = 0;
	std::vector<PIECE> piezas = m_Container->Get_Piezas();
	std::list<BLOQUE> bloques = m_Container->Get_ListaBloques();
	//	m_num=min(;

	m_perdida = false;
	m_Id = bloques.size() + 1000;
	m_q = min(piezas[id1].Get_q(), piezas[id2].Get_q());
	//m_num = m_q;
	m_Rotate_z = true;
	m_Rotate_x = false;
	m_Rotate_y = false;
	if (piezas[id1].Get_Rx() == true && piezas[id1].Get_Ry() == true &&
		piezas[id1].Get_Rz() == true && piezas[id2].Get_Rx() == true && piezas[id2].Get_Ry() == true &&
		piezas[id2].Get_Rz() == true)
	{
		m_Rotate_x = true;
		m_Rotate_y = true;
	}
	m_S_x = 0;
	m_S_y = 0;
	m_S_z = 0;
	m_idblo = 0;
	m_num1 = 0;
	m_num2 = 0;
	m_peso = 0;
	m_tipo_1 = 0;
	m_tipo_2 = 0;
	m_x1 = 0;
	m_x2 = 0;
	m_z1 = 0;
	m_z2 = 0;


}
//Para la creación la x,y,z si es posible rotarla en cada dirección y la cantidad
BLOQUE::BLOQUE(int id1, int id2, int x, int z, int y, int x1, int z1, int x2, int z2, CONTAINER *a, int num1, int num2, short int t1, short int t2)
{
	m_Id1 = id1;
	m_Id2 = id2;
	m_x = x; m_y = y; m_z = z;
	m_x1 = x1; m_z1 = z1;
	m_x2 = x2; m_z2 = z2;
	m_num = 0;
	//m_nbloq = 0;
	m_num1 = num1;
	m_num2 = num2;
	//	//Este es de las seis posibles maneras que se puede colocar
	//1.- cara x V, 2.- rotada eje x
	//3.- cara y V,  4.- rotada eje y
	//5.- cara z V, 6.- rotada eje z
	m_tipo_1 = t1;
	m_tipo_2 = t2;
	m_Container = a;
	m_Volumen = x1 * z1*y + (x2*z2*y*num2);
	if (m_Volumen != x * y*z)
		m_perdida = true;
	else
		m_perdida = false;
	m_Id = m_Container->Get_ListaBloques().size() + 1000;
	m_q = min(m_Container->Get_Piezas()[id1].Get_q() / num1, m_Container->Get_Piezas()[id2].Get_q() / num2);
	m_num = m_q;
	if (m_num == 0)
		int kk = 9;
	m_Rotate_y = true;
	m_Rotate_x = false;
	//	if (
	m_Rotate_z = false;
	//Si tengo perdida no puedo poner mas de uno en vertical 
	if (m_perdida == false && m_Container->Get_Piezas()[id1].Get_Rx() == true && m_Container->Get_Piezas()[id1].Get_Ry() == true &&
		m_Container->Get_Piezas()[id1].Get_Rz() == true && m_Container->Get_Piezas()[id2].Get_Rx() == true && m_Container->Get_Piezas()[id2].Get_Ry() == true &&
		m_Container->Get_Piezas()[id2].Get_Rz() == true)
	{
		m_Rotate_x = true;
		m_Rotate_z = true;
	}
	m_S_x = 0;
	m_S_y = 0;
	m_S_z = 0;
	m_idblo = 0;
	m_peso = 0;

} 
int CONTAINER::FuncionObjetivoCompleteShipment()
{
	m_completos = 0;
	for (int i = 0; i < m_num_pedidos; i++)
		m_Pedidos[i].Set_complete(false);
	piece_unasigned.clear();
	for (int j = 0; j < m_Q; j++)
	{

		m_Pieces[j].Set_asign(0);
		piece_unasigned.push_back(0);
	}
	LPCPLEX micplex;
	micplex.modelo_pedidos(this);
	int volumen = 0;
	for (int i = 0; i < m_num_pedidos; i++)
	{
		if (m_Pedidos[i].Get_complete() == true)
		{
			volumen += m_Pedidos[i].Get_Volumen();
			if (m_Random == true)
			{
				for (int j = 0; j < m_Q; j++)
					m_Pieces[j].Add_asign(m_Pedidos[i].Get_num_pieces_tipo()[j]);
			}
		}
	}
	/*double pt = 100 * (double)volumen / (double)(m_X * m_Y * m_Z);*/
	/*if (m_volumen_ocupado_cs < volumen)
		m_volumen_ocupado_cs = volumen;*/
	return volumen;
}
//25-3-19 cambio de coordenadas z e y, en el otro programa las dimensiones están intercambiadas
//BLOQUE::BLOQUE(int id1, int id2, int x, int y, int z, int x1, int y1, int x2, int y2, CONTAINER *a, int num1, int num2, short int t1, short int t2)
//{
//	m_Id1 = id1;
//	m_Id2 = id2;
//	m_x = x; m_y = y; m_z = z;
//	m_x1 = x1; m_y1 = y1;
//	m_x2 = x2; m_y2 = y2;
//	m_num = 0;
//	//m_nbloq = 0;
//	m_num1 = num1;
//	m_num2 = num2;
//	//	//Este es de las seis posibles maneras que se puede colocar
//	//1.- cara x V, 2.- rotada eje x
//	//3.- cara y V,  4.- rotada eje y
//	//5.- cara z V, 6.- rotada eje z
//	m_tipo_1 = t1;
//	m_tipo_2 = t2;
//	m_Container = a;
//	m_Volumen = x1 * y1*z + (x2*y2*z*num2);
//	if (m_Volumen != x * y*z)
//		m_perdida = true;
//	else
//		m_perdida = false;
//	m_Id = m_Container->Get_ListaBloques().size() + 1000;
//	m_q = min(m_Container->Get_Piezas()[id1].Get_q() / num1, m_Container->Get_Piezas()[id2].Get_q() / num2);
//	m_num = m_q;
//	if (m_num == 0)
//		int kk = 9;
//	m_Rotate_z = true;
//	m_Rotate_x = false;
//	//	if (
//	m_Rotate_y = false;
//	//Si tengo perdida no puedo poner mas de uno en vertical 
//	if (m_perdida == false && m_Container->Get_Piezas()[id1].Get_Rx() == true && m_Container->Get_Piezas()[id1].Get_Ry() == true &&
//		m_Container->Get_Piezas()[id1].Get_Rz() == true && m_Container->Get_Piezas()[id2].Get_Rx() == true && m_Container->Get_Piezas()[id2].Get_Ry() == true &&
//		m_Container->Get_Piezas()[id2].Get_Rz() == true)
//	{
//		m_Rotate_x = true;
//		m_Rotate_y = true;
//	}
//
//}