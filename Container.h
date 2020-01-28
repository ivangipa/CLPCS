#ifndef CONTAINER_H
#define CONTAINER_H
//lectura y escritura
#pragma warning(disable: 4786)
#define MAX_IMPORTANCIA 99999;
#define get_random(min1,max1) ((rand() %(int) (((max1)+1)-(min1)))+(min1))
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <cmath>

//#include <iostream>
//#include <fstream>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <utility>
#include <algorithm>
#include <math.h>
#include <assert.h>
#include <time.h>
//Para que pueda funcionar con las mfc
//#include <afxwin.h>
using namespace std;
/*
inline bool IncluidoFirstSecond(int Firstx1,int Firsty1,int Firstz1, int Firstx2,int Firsty2,int Firstz2,
								int Secondx1,int Secondy1,int Secondz1, int Secondx2,int Secondy2,int Secondz2){
	if (Firstx1>=Secondx1 && Firstx2<=Secondx2 
		&& Firsty1>=Secondy1 && Firsty2<=Secondy2 
		&& Firstz1>=Secondz1 && Firstz2<=Secondz2)
		return true;
	return false;
}*/

extern  "C" int  bouknap(int n, int* p, int* w, int* m, int* x, int c);

class PEDIDO;
class PIECE;
class SPACE;
class CONTAINER;
class CONFIGURACAO;
class MOVIMIENTO;
class MOVIMIENTOMC;
class BLOQUE;

//*********************
// CLASE BLOQUE_ARA
//********************
class BLOQUE_ARA {
	int m_Id;
	int m_x; //Largo tablero
	int m_y; //Ancho tablero
	int m_z;
	
	int pack_area_w;
	int pack_area_l;

	int m_Volumen; //Volumen de la pieza
	bool m_perdida;
	int m_peso;
	int m_volumen_ocupado;
	short int m_tipo; //Si todas las piezas del bloque son iguales y tienen la misma orientación (columna o capa), valor de 1 a 6. Si no, 0.
	//int m_nbloq; //Número de bloques utilizado en la solución


	BLOQUE_ARA* m_bloque1; //Puntero al bloque 1
	BLOQUE_ARA* m_bloque2; //Puntero al bloque 2
	int m_num_pieces; //numero de piezas utilizado
	std::map<int, int> m_num_pieces_tipo;//Numero de caja por tipo, primero tipo, segundo el número
	//Puntero estatico al Contenedor
	static CONTAINER* m_Container;
	int m_x2;
	int m_y2;
	int m_z2;
public:
	//constructor
	BLOQUE_ARA(int, int, int, int, int, std::map<int, int>&);
	BLOQUE_ARA(int id, int nx, int ny, int nz, CONTAINER* a, PIECE* p);
	BLOQUE_ARA(int id, int x, int y, int z, CONTAINER* a, int idpieza, int tipo);
	int Get_m_peso() { return m_peso; };
	void Print();

	BLOQUE_ARA() {};
	//destructor
	~BLOQUE_ARA() {};
	//Funciones set
	void Set_x(int a) { m_x = a; };
	void Set_y(int a) { m_y = a; };
	void Set_z(int a) { m_z = a; };
	void Set_x2(int a) { m_x2 = a; };
	void Set_y2(int a) { m_y2 = a; };
	void Set_z2(int a) { m_z2 = a; };
	void Set_volumen_ocupado(int a) { m_volumen_ocupado = a; };
	void Set_pack_area_l(int a) { pack_area_l = a; };
	void Set_pack_area_w(int a) { pack_area_w = a; };
	void Set_bloque1(BLOQUE_ARA* a) { m_bloque1 = a; };
	void Set_bloque2(BLOQUE_ARA* a) { m_bloque2 = a; };
	void Set_tipo(short int a) { m_tipo = a; };
	void Set_Id(int a) { m_Id = a; };
	//	bool compareBlocks(BLOQUE_ARA* const& b1, BLOQUE_ARA* const& b2);


	void Set_Num(int a) { m_num_pieces = a; };

	//int Get_Nbloq() { return m_nbloq; };
	int Get_Id() { return m_Id; };
	int Get_x() { return m_x; };
	int Get_y() { return m_y; };
	int Get_z() { return m_z; };
	int Get_x2() { return m_x2; };
	int Get_y2() { return m_y2; };
	int Get_z2() { return m_z2; };
	std::map<int, int>& Get_num_pieces_tipo() { return m_num_pieces_tipo; };
	BLOQUE_ARA &Get_bloque1() { return *m_bloque1; };
	BLOQUE_ARA &Get_bloque2() { return *m_bloque2; };
	int Get_pack_area_l() { return pack_area_l; };
	int Get_pack_area_w() { return pack_area_w; };
	int Get_volumen_ocupado() { return m_volumen_ocupado; };
	bool Get_Perdida() { return m_perdida; };
	int Get_Num() { return m_num_pieces; };
	int Get_Volumen() { return m_Volumen; };
	short int Get_tipo() { return m_tipo; };
	void Add_Num(int a) { m_num_pieces += a; };
};

bool less_than(const std::map<int, int>& l, const std::map<int, int>& r);


struct compareBlocks {
	bool operator()(BLOQUE_ARA* const& b1, BLOQUE_ARA* const& b2) const
	{
		if (b1->Get_volumen_ocupado() != b2->Get_volumen_ocupado())  return (b1->Get_volumen_ocupado() > b2->Get_volumen_ocupado());
		// if(b1.volume!=b2.volume) return (b1.volume > b2.volume);
		if (b1->Get_x() != b2->Get_x()) return (b1->Get_x() > b2->Get_x());
		if (b1->Get_y() != b2->Get_y()) return (b1->Get_y() > b2->Get_y());
		if (b1->Get_z() != b2->Get_z()) return (b1->Get_z() > b2->Get_z());

		if (less_than(b1->Get_num_pieces_tipo(), b2->Get_num_pieces_tipo())) return true;
		else return false;
	}
};



//************
//Clase ORIG
//
class ORIG
{
	//
	short int m_primero;
	short int m_segundo;
	short int m_tercero;
//	std::vector <short int> m_orig;
public:
	//constructor
	ORIG();
	~ORIG(){};
	ORIG(int a,int b,int c);
	short int GetPrimero(){return m_primero;};
	short int GetSegundo(){return m_segundo;};
	short int GetTercero(){return m_tercero;};
	void SetPrimero(short int a){m_primero=a;};
	void SetSegundo(short int a){m_segundo=a;};
	void SetTercero(short int a){m_tercero=a;};

	//	short int &ORIG::operator [](int i){return m_orig[i];};
};

//****************
//Clase Pedido
//****************

class PEDIDO {

	//id del pedido
	int m_Id;
	//volumen total del pedido
	int m_Volumen;
	//total cajas en el pedido
	int m_num_cajas;
	//Numero de caja por tipo, primero tipo, segundo el número
	std::vector<int> m_num_pieces_tipo;
	//Cargado completamente en el contenedor (1) o no (0)
	bool m_complete;
	//Volumen restante para completar el pedido en la solución con las cajas no asignadas que hay
	int m_vol_falta;
	//True si hemos intentado meter el pedido en la solución y el constructivo no lo ha conseguido
	bool m_flag;
	//Piezas que faltan para completar el pedido (valores distintos de cero si es candidato y no está completo)
	std::vector<int> m_faltan;
	//Puntero estatico al Contenedor
	static CONTAINER* m_Container;
	


public:

	//constructor
	//Por coordenadas
	PEDIDO(int id, std::vector<int> tipos_cajas, int total_cajas, CONTAINER *a);

	PEDIDO() {};
	//destructor
	~PEDIDO() {};

	std::vector<int>& Get_num_pieces_tipo() { return m_num_pieces_tipo; };
	int Get_Volumen() { return m_Volumen; };
	std::vector<int>& Get_faltan() { return m_faltan; };
	int Get_vol_falta() { return m_vol_falta; };
	int Get_num_cajas() { return m_num_cajas; };
	bool Get_complete() { return m_complete; };
	bool Get_flag() { return m_flag; };
	void Set_vol_falta(int a) { m_vol_falta = a; };
	void Set_complete(bool a) { m_complete = a; };
	void Set_flag(bool a) { m_flag = a; };
	int Get_Id() { return m_Id; };

};

//****************
//Clase Espacio
//****************
class SPACE{
	// origen
	int m_x1; int m_y1; 	int m_z1; 
	// fin 
	int m_x2; int m_y2; 	int m_z2; 
	// largo, ancho, alto
	int m_dx; int m_dy; 	int m_dz; 
	//bool m_bloque_espacio;
	bool m_Flag; // true si cabe algo, false en el otro sentido
	int m_Volumen; //Volumen de la pieza
	int m_val_dist;
	ORIG m_distancia_origen; //Distancia al origen
	//es a que esquina es la que esta más cercana
	// 1.(0,0,0) , 2.(0,Y,0)  3.(0,0,Z)  4.(0,Y,Z)  5.(X,0,0)  6.(X,Y,0)  7.(X,0,Z)  8.(X,Y,Z) 
	short int m_origen_distancia; 
	//Puntero estatico al Contenedor
	static CONTAINER *m_Container;

public:
	//constructor
	//Por coordenadas
	SPACE(int,int, int , int , int,int , CONTAINER *a );
	//Por vertice
	SPACE( CONTAINER *a ,int,int, int , int , int,int );
	SPACE(){};
	//destructor
	~SPACE(){};
	
	//Funciones Get
	int Get_x1(){return m_x1;};
	int Get_y1(){return m_y1;};
	int Get_z1(){return m_z1;};
	int Get_x2(){return m_x2;};
	int Get_y2(){return m_y2;};
	int Get_z2(){return m_z2;};
	//bool Get_bloque() { return m_bloque_espacio; };
	void Set_x1(int a){m_x1=a;};
	void Set_y1(int a){m_y1=a;};
	void Set_z1(int a){m_z1=a;};
	void Set_x2(int a){m_x2=a;};
	void Set_y2(int a){m_y2=a;};
	void Set_z2(int a){m_z2=a;};
	void Set_dx(int a){m_dx=a;};
	void Set_dy(int a){m_dy=a;};
	void Set_dz(int a){m_dz=a;};
	void Set_origen_distancia(short int a){m_origen_distancia=a;};
	//void Set_bloque(bool a) { m_bloque_espacio = a; };
	int Get_dx(){return m_dx;};
	int Get_dy(){return m_dy;};
	int Get_dz(){return m_dz;};
	bool Get_Flag(){return m_Flag;};
	short int Get_origen_distancia(){return m_origen_distancia;};
	int Get_Dist_Euclidea(){return m_val_dist;};
	ORIG & Get_Distancia(){return m_distancia_origen;};
//Funciones set
	void Set_Flag(bool a){m_Flag=a;};
	void Cambiar(ORIG &orig,int a,int b,int c);
	
	int Get_Volumen(){return m_Volumen;};
	//Calcula la minima distancia al origen con muchas podas
	void CalcularDistanciaOrigen();
	//Calcula la minima distancia al origen de la forma original
	void CalcularDistanciaOrigenOriginal();
	//Funcion de distancia 2 que solamente hace para cumplir la gravedad
	void CalcularDistanciaOrigenDos();
	void CalcularDistanciaOrigenEuclidea();
	void CalcularDistanciaOrigenEsquinas();
	void CalcularDistanciaOrigenFullSupported();

	void ModificarSpace(int x1,int y1, int z1, int x2, int y2, int z2);
	void CambiarEsquina(SPACE &);
	//Funcion para comparar dos set
//	bool Comparar_DistA_DistB(ORIG &A, int VolA,ORIG &B, int VolB);
	//Me dice si este espacio esta incluido en E
	bool Incluido(SPACE &E){return (m_x1>= E.Get_x1() && m_x2<=E.Get_x2() 
		&& m_y1>= E.Get_y1() && m_y2<=E.Get_y2() 
		&& m_z1>= E.Get_z1() && m_z2<=E.Get_z2());};

};

//*********************
// CLASE CONFIGURACAO
//********************
class CONFIGURACAO{
	int m_Id; //numero para identificar la pieza
	//Este es de las seis posibles maneras que se puede colocar
	//1.- apoyada cara x , 2.- rotada eje x
	//3.- apoyada cara y, 4.- rotada eje y
	//5.- apoyada cara z, 6.- rotada eje z
	short int m_tipo; 
	short int m_origen_distancia;
	ORIG m_set_distancias;
	int m_x1; //Posicion inicio
	int m_y1; //Posicion inicio 
	int m_z1; //Posicion inicio
	int m_x2; //Posicion fin
	int m_y2; //Posicion fin
	int m_z2; //Posicion fin
	int m_dx; //Numero de piezas en la dirección x
	int m_dy; //Numero de piezas en la dirección y
	int m_dz; //Numero de piezas en la dirección z
	int m_Volumen; //Volumen de la pieza
	int m_num; //numero de piezas utilizado
	bool m_bloque; //La pieza pertenece a un bloque (true) o no (false)
	/*std::vector<int> m_bloque_posi = {0, 0};*/ //Primera coordenada id del bloque, segunda coordenada indica el momento de entrada en la solución. Ej. {12, 3} Es el tercer bloque que ha entrado en la sol, y es del tipo 12
	static CONTAINER *m_Container;

public:
	//destructor
	~CONFIGURACAO(){};
	//constructor
	CONFIGURACAO(){};
	CONFIGURACAO(CONTAINER *a );

	CONFIGURACAO(CONTAINER *a ,int Id, int x1,int y1, int z1, int x2, int y2, int z2,short int tipo , int num,short int orig);
	CONFIGURACAO(CONTAINER *a ,ORIG sm, int num);
	CONFIGURACAO(CONTAINER *a ,int Id, int x1,int y1, int z1, int tx, int ty, int tz,int dx, int dy, int dz,  short int tipo , int num,short int orig);

	//Funciones Get
	//Funciones Get
	int Get_Id(){return m_Id;};
	int Get_x1(){return m_x1;};
	int Get_y1(){return m_y1;};
	int Get_z1(){return m_z1;};
	int Get_x2(){return m_x2;};
	int Get_y2(){return m_y2;};
	int Get_z2(){return m_z2;};
	bool Get_bloque() { return m_bloque; };
	short int Get_orig(){return m_origen_distancia;};
	void Set_Id(int a) { m_Id = a; };
	void Set_bloque(bool a) { m_bloque = a; };
	void Set_x1(int a){m_x1=a;};
	void Set_y1(int a){m_y1=a;};
	void Set_z1(int a){m_z1=a;};
	void Set_x2(int a){m_x2=a;};
	void Set_y2(int a){m_y2=a;};
	void Set_z2(int a){m_z2=a;};
	void Set_dx(int a){m_dx=a;};
	void Set_dy(int a){m_dy=a;};
	void Set_dz(int a){m_dz=a;};
	void Set_orig(int a) { m_origen_distancia = a; };
	void Set_Vol(int a){m_Volumen=a;};
	void Set_Num(int a){m_num=a;};
	//void Set_blo_pos(int a, int b) { m_bloque_posi[0] = a; m_bloque_posi[1] = b; };
	short int Get_Tipo(){return m_tipo;};
	int Get_dx(){return m_dx;};
	int Get_dy(){return m_dy;};
	int Get_dz(){return m_dz;};
	int Get_Num(){return m_num;};
	int Get_Volumen(){return m_Volumen;};
	//std::vector<int> Get_blo_pos() { return m_bloque_posi; };
	ORIG & Get_Distancia(){return m_set_distancias;};
	//

	//
	void CambiarEsquina(SPACE &E);
	void PonerMedidas2(int x1, int y1, int z1, int x2, int y2, int z2);
	void PonerMedidas1(int x1, int y1, int z1, int dx, int dy, int dz);
	void MejorCapaDeUnaBloque(SPACE &Espacio, BLOQUE &Pieza);
	void MejorCapaDeUnaBloqueMov(SPACE &Espacio, BLOQUE &Pieza);
	//Operaciones sencillas de la configuraca
//	OperacionesSencillas(int , int , int ,int , int , int );
	bool Mejor_DistA_Que_DistB_Configuracaos(ORIG &A, int NumA,ORIG &B, int NumB,int Vol);
	//Para crear columnas
	void MejorColumnaDeUnaPieza(SPACE &,PIECE &);
	void MejorColumnaDeUnaPiezaMov(SPACE&, PIECE&);
	double CS_Configuracao(int dx, int dy, int dz, int x, int y, int z);
	double CS_ConfiguracaoMov(std::list<CONFIGURACAO> *lista, int dx, int dy, int dz, int x, int y, int z);
	void CompararConColumnas(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int );
	void CompararConColumnasMov(std::list<CONFIGURACAO> *lista, short int tipo, SPACE& Espacio, int x, int y, int z, int Id, int);
	//Para crear capas
	void MejorCapaDeUnaPieza(SPACE &,PIECE &);
		void MejorBloqueDeUnaPieza(SPACE &,PIECE &);
	void MejorPieza(SPACE &Espacio,PIECE &Pieza);
	void MejorPiezaMov(SPACE &Espacio,PIECE &Pieza);

	int surface_in_contact_with_the_container_Configuracao(int dx, int dy, int dz, int x, int y, int z);
	int surface_in_contact_Configuracao(int dx, int dy, int dz, CONFIGURACAO& Bi, int x, int y, int z);

	void CompararConCapas(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas);
	void CompararConCapasMov(std::list<CONFIGURACAO> *lista, short int tipo, SPACE& Espacio, int x, int y, int z, int Id, int piezas_maximas);
	//Para crear bloque

	void CompararConBloques(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas);
	//Esta funcion me actualiza la configuracicao
	void CambiarConfiguracao(int numpiezas, int ca,int cb, int cc, int a,int b,int c, int id, short int tipo_rota, SPACE &Espacio);
	void CambiarConfiguracao(int numpiezas, int ca,int cb, int cc, int a,int b,int c, int id, short int tipo_rota);
	double VCS_Configuracao(int num, int dx, int dy, int dz, int Vol, SPACE& E, int x, int y, int z);
	double VCS_ConfiguracaoMov(std::list<CONFIGURACAO> *lista, int num, int dx, int dy, int dz, int Vol, SPACE& E, int x, int y, int z);
	
	std::list<CONFIGURACAO> Get_adjacent_blocks(int x1, int y1, int z1, int x2, int y2, int z2);
	std::list<CONFIGURACAO> Get_adjacent_blocksMov(std::list<CONFIGURACAO>* lista, int x1, int y1, int z1, int x2, int y2, int z2);
	//Esta función es creada para que  ponga las medidas en la configuración
	//pero la función de arriba las pone ahora directamente
	void InsertarOrdenadaRCL(CONFIGURACAO &Actual);
	void Cambiar(ORIG &orig,int a,int b,int c);
	bool Mayor(CONFIGURACAO &C,short int tipo);

//bool CONFIGURACAO::operator<(const CONFIGURACAO &p2)
bool operator<(const CONFIGURACAO &p2) ;
//Funcion para poner el numero de piezas en cada orientacion de la configuracao
	void PonerMedidas(int dx,int dy, int dz);
	void MejorCapaDeUnaPiezaMov(SPACE &Espacio,PIECE &Pieza);
	bool Mejor_DistA_Que_DistB_FullSupported(ORIG &A, int NumA, ORIG &B, int NumB, int Vol, int dx, int dy, int dz);



};
//*********************
// CLASE MOVIMIENTO
//********************
class MOVIMIENTO{
	CONFIGURACAO m_Configuracao;
	std::list<CONFIGURACAO> m_Configuracaos_new;
	//multiset donde mete cuantos hay en cada cuadrante
	//Es para cuando tenemos 2
	int m_val;
	int m_vol;
	static CONTAINER *m_Container;

public:
	MOVIMIENTO(CONTAINER *a){m_Container=a; m_val=-999999999;m_vol=0;};
	//constructor
	MOVIMIENTO(){};
	//destructor
	~MOVIMIENTO(){};
	//Funciones Get

	//Funciones Get
	int Get_Volumen(){return m_vol;};
	int Get_Val(){return m_val;};
	CONFIGURACAO &Get_Configuracao(){return m_Configuracao;};
	std::list<CONFIGURACAO> &Get_Configuracaos(){return m_Configuracaos_new;};
	//Funciones Set
	void Set_Vol(int a){m_vol=a;};
	void Set_Valor(int a){m_val=a;};
	void Set_Nuevos(std::list<CONFIGURACAO> &lista){m_Configuracaos_new=lista;};
	//**funciones de 
	//hay que evaluar el movimiento
	//esta funcion me dice cuanto es lo que vale ese movimiento
	//hace las intersecciones con los otros bloque y calcula
	//el valor de esa interseccion
	void EvaluacionMovimiento(CONFIGURACAO &,std::list<CONFIGURACAO> &lista,int );
	//Cuenta cuanto hay en cada cuadrante del container con la 
	//nueva lista de bloque
	void EvaluarMovimiento(std::list<CONFIGURACAO> &lista,int );
	bool ComprobarFullSupport(CONFIGURACAO &it, std::list<CONFIGURACAO> &lista);

	void ActualizarBloquesElegido( CONFIGURACAO &E,CONFIGURACAO &C,std::list <CONFIGURACAO> &lista_temp,SPACE &);

	void ActualizarListaDeBloques(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista,std::list<SPACE> &lista_espacios);


	void MejorCapaDeUnaPiezaEspacio(SPACE &Espacio,PIECE &Pieza);
	void MejorCapaDeUnaBloqueEspacio(SPACE &Espacio, BLOQUE &Pieza);
	void CompararConCapasEspacio(short int tipo,SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas);
	void ListaDeBloquesNuevos(CONFIGURACAO &C,std::list< CONFIGURACAO> &lista);

	void CambiarConfiguracao(CONFIGURACAO &C,int numpiezas, int ca,int cb, int cc, int a,int b,int c, int id, short int tipo_rota, SPACE &Espacio);
	void CompararMovimientos(MOVIMIENTO &otro);

//	bool EsMejorMovimientoA_que_B(std::multiset<double> &A,std::multiset<double> &B);

	void PonerConfiguracaoMov(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista_Con,std::list<CONFIGURACAO> &lista,bool compactada)	;
	void ActualizarListasMov(SPACE &EspacioT, CONFIGURACAO &Configuracao);
	void ActualizarListaEspaciosOriginalesMov(std::list<SPACE> &,CONFIGURACAO &);
	void ActualizarListaEspaciosBloquesMov(std::list<SPACE> &,CONFIGURACAO &);
	int EvaluacionMovimientoConstruir(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista);
	void ActualizarListaDeBloquesQuita(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista, bool rec);
	void ActualizarListaDeBloquesQuitaAbajo(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista_b, bool rec, CONFIGURACAO &Exc);
	void ActualizarBloquesElegidoQuita( CONFIGURACAO &Vieja,CONFIGURACAO &Nueva,std::list <CONFIGURACAO> &lista_temp, std::list<CONFIGURACAO> &lista_b);
	int ActualizarListaDeBloquesQuitaCantidad(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista);
	int ActualizarBloquesElegidoQuitaCantidad( CONFIGURACAO &Vieja,CONFIGURACAO &Nueva);
	void EvaluacionMovimientoConstruirOld(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista,int val);
	void MejorUnaPiezaEspacio(SPACE &Espacio,PIECE &Pieza);
	void MejorUnaPiezaEspacioMC(SPACE &Espacio,PIECE &Pieza);
	void RestarConfiguracaos(CONFIGURACAO &grande, CONFIGURACAO &peque, std::list < CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista_b, bool &izq, bool &der, bool &abj, bool &arr, bool &den, bool &fue);
	
	void CambiarMejor(std::list<CONFIGURACAO> &lista,int Vol);
	void CambiarMejor(std::list<CONFIGURACAO> &lista,int Vol,int pos);


	//
	
	//
};



//*********************
// CLASE MOVIMIENTO MULTICONTAINER
//********************
class MOVIMIENTOMC{
	std::list< std::pair< int , std::list<CONFIGURACAO> > > m_ConfiguracaosMC_new;
	//multiset donde mete cuantos hay en cada cuadrante
	std::vector< int > m_quitados;
	int m_vol;
	static CONTAINER *m_Container;

public:
	MOVIMIENTOMC(CONTAINER *a){m_Container=a; m_vol=-999999;};
	//constructor
	MOVIMIENTOMC(){};
	//destructor
	~MOVIMIENTOMC(){};
	//Funciones Get

	//Funciones Get
	int Get_Volumen(){return m_vol;};
	std::vector< int > &Get_Quitados(){return m_quitados;};
	std::list< std::pair< int , std::list<CONFIGURACAO> > > &Get_Configuracaos(){return m_ConfiguracaosMC_new;};
	//Funciones Set
	void Set_Vol(int a){m_vol=a;};

	void CambiarMejor(std::list< std::pair< int , std::list< CONFIGURACAO > > > &lista, int Vol,std::vector<int > &pos)
	{ m_ConfiguracaosMC_new=lista; m_vol=Vol; m_quitados=pos;};


	//
	
	//
};
//******************
//CLASE CONTENEDOR
//******************

class CONTAINER {

	int m_X; //Largo tablero
	int m_Y; //Ancho tablero
	int m_Z;
	int m_Numpieces; //Numero de piezas totales
	int m_Q;//Numeror de tipos de piezas
	int m_lb;//cota inferior para el multi container
	bool m_multicontainer;//me dice si es el multicontainer
	bool m_por_bin;//me dice si es un container normal pero por bin
	int m_nbins; //numero de bins 
	int m_Best_nbins;//mejor numero de bins
	int	m_PeorSolucion_nbins;//peor numero de bins

	std::vector< PEDIDO > m_Pedidos; //Lista de pedidos (si trabajamos con complete shipment)
	std::vector< PEDIDO > m_Pedidos_ordenados; //Lista de pedidos ordenados por volumen (si trabajamos con complete shipment)
	std::vector <PEDIDO> m_Pedidos_candidatos;
	std::vector< PIECE > m_Pieces;//Lista de piezas
	std::list< SPACE > m_Spaces; //Lista de espacios
	std::list< BLOQUE > m_Bloques; //Lista de bloques
	std::list< BLOQUE > m_Bloques_Mejora;
	std::list< BLOQUE > m_Bloques_Guardados;
	std::list< std::list< SPACE > > m_SpacesMC; //Lista de espacios multi container
	std::list< CONFIGURACAO > m_Configuracaos; //Lista de configuraciones
	std::list< CONFIGURACAO > m_Best_CS_Configuracaos; //Lista de configuraciones con mejor volumen complete shipment
	std::list< CONFIGURACAO > m_Configuracaos_Bloques; //Lista de configuraciones previas a colocar un bloque
	std::list< std::pair<int, std::list< CONFIGURACAO > > > m_ConfiguracaosMC; //Lista de bloques multicontainer
	std::list< CONFIGURACAO > m_ListaRCL; //Lista Restringida de Candidatos
	char m_Nombre[240];//Nombre de la instancia
	int m_vol_incompletos; //Volumen de las piezas asignadas a pedidos incompletos
	int m_total_volumen; //Total del volumen posible de llenar con las piezas
	int m_total_volumen_ocupado; //Total del volumen que se ha llenado del container
	int m_total_volumen_cs_ocupado; //Total de volumen ocupado por pedidos completos
	int m_cota_cs; //Cota superior para complete shipment: total volumen cajas - volumen pedido menor
	//menor dimension admitida, no tengo en cuenta rotaciones
	int m_dimension_menor;
	//menor volumen para que quepa una pieza
	int m_menor_volumen;
	//Funcion que me dice si el objetivo es el vol true o el orig fals
	bool m_objetivo_vol;
	//Funcion que me dices si quiero capas o columnas
	bool m_objetivo_capas;
	//Funcion que me dice si quiero uno mixto para el aleatorizado de col y capas
	bool m_tipo_mixto;
	//Candidato a ser el próximo pedido a completar (porque es al que menos volumen le queda fuera)
	int m_candidato;
	//variable para indicarme si utilizo constructivo aleatorizado
	bool m_Aleatorizado;
	//Tamaño de la lista restringida de candidatos
	int m_TamRCL;
	double m_Delta;
	//numero de iteraciones Grasp
	int m_max_iteraciones_Grasp;
	//iteracion actual
	int m_iter_actual;
	//iteracion consigue mejor solucion
	int m_iter_best_actual;
	//maximo del volumen ocupado
	int m_max_total_volumen_ocupado;
	int m_max_total_volumen_cs_ocupado;
	int m_max_total_volumen_ocupado_mejora;
	std::list<CONFIGURACAO> m_Best_Configuracao;
	int completos_CS;
	std::list<CONFIGURACAO> m_Configuracaos_CS;
	std::list<SPACE> m_Spaces_CS;
	std::vector<PIECE> m_Pieces_CS;
	std::vector<PEDIDO> m_Pedidos_CS;
	std::vector<int> piece_unasigned_CS;
	std::list< std::pair< int, std::list<CONFIGURACAO> > > m_Best_ConfiguracaoMC;
	std::list< std::pair< int, std::list<CONFIGURACAO> > > m_BestSolution_ConfiguracaoMC;
	//Variables para el método de mejora
	bool m_mejora_local;
	bool m_space_arriba = true; //Para construir el espacio de arriba o no
	bool m_boolrand;
	//Vector con el numero de piezas utilizado hasta mejora
	std::vector <int> m_Pieces_Mejora;
	std::vector <int> m_vec_lmax;
	std::vector <int> m_vec_wmax;
	std::vector <int> m_vec_hmax;
	//Lista de espacios hasta la mejora
	std::list <SPACE > m_Spaces_Mejora;
	//Lista de espacios hasta la mejora
	std::list <CONFIGURACAO > m_Configuracaos_Mejora;
	//Vector con las piezas no asignadas por el primer modelo
	std::vector<int> piece_unasigned;
	//volumen ocupado hasta el momento
	int m_total_volumen_ocupado_mejora;
	//Guardo la peor solucion conseguida hasta ahora
	int m_PeorSolucion_volumen;
	//Para el reactive Grasp
	int m_hastavalor;
	int idbloque;
	//Para el programa que dibuja
	bool m_paso_a_paso;
	bool paraprobar = true;
	bool paraprobar2;
	int contador = 0;
	//	CClientDC *m_clientedc;
		//factor para dibujar
	double m_factor;
	int m_Limite; //Porcentaje hasta el cual el constructivo aleatorizado construye de manera normal
	//es para dibujar o no
	bool m_Dibujar;
	//para verificar cualquier restricción en las soluciones
	bool m_Verificar;
	//son los grados con los que hago el dibujo
	double m_grados;
	//Tipo de graveda
	short int m_tipo_gravedad;
	//Tipo de mejora
	//o original
	//1 vol
	//2 es la original + volumen
	short int m_tipo_mejora;
	//Variables para guardar tiempos
	clock_t m_inicio, m_fintime, m_inicio_constr, m_fin_constr, m_fintime2, m_inicio_bucle, m_fin_bucle;
	double m_tiempo;
	double m_time_final;
	double m_tiempo_final_total;
	//Doubles para las medidas de estabilidad
	double m_medida1;
	double m_medida2;
	double m_medidaCG;
	double m_medida55por100;
	double m_medida100por100;
	//0 choose the space by my function
	//1 choose the space by euclidena
	short int m_tipo_eleccion_space;
	//
	double m_val_quita;
	bool m_movimientos;
	//
	bool m_eliminar_espacios;
	//para poner las piezas que llevo de los movimientos
	std::vector< short int > m_Pieces_Tabu;
	std::vector< short int > m_Pieces_Tabu2;
	std::vector< int > m_cajas_sin_asignar;

	bool m_imprimir_mejoras;
	//Variable para que haga un descendent
	bool m_descendent;
	//con esta variable decido lo que es
	bool m_juntos;
	//con esta variable pienso si se puedo rotar o no
	bool m_rotacion;
	char* m_file_to_write;
	bool m_imprimir;
	//para que solamente examine un movimiento
	bool m_un_movimiento;
	int m_max_movimientos;

	int m_dimension_menor_x;
	int m_dimension_menor_y;
	int m_dimension_menor_z;

	short int m_tipo_origen; //0 es el x, 1 es el y, 2 es el z
	//tipo de orden para las piezas
	short int m_tipo_orden_pieces;
	//vector donde guardamos las frecuencias de las piezas que se quedan fuera en el grasp
	std::vector< short int > m_frecuencias;
	//Si fijo algunos bins 
	int m_bin_fijados;
	short int m_nesquinas;
	int m_sum_freq;
	short int m_peso_diver;
	int gananciaCadaBin;
	int gananciaPartir;
	int gananciaUltimos;
	int m_iteraciones = 0;
	int m_num_pedidos;
	int m_completos;
	bool m_full_supported;
	bool m_complete_shipment;
	bool m_aleatorizado_cs;
	bool mindimcs;
	bool m_por_bloques;
	bool m_por_bloques_ara;
	bool m_all_bloques;
	float m_perdida;
	bool m_objetivo_mixto;
	bool m_juntar_spaces;
	int m_idBloques = 0;
	int m_blo_pos = 0;
	double p = 0.04;
	int alpha = 4;
	int beta = 1;
	int Max_Iter_VCS=40;
	double gamma = 0.2;
	bool m_VCS; //Para utilizar la función objetivo del VCS
	bool m_VCS_random; //Parámetros de la función objetivo VCS aleatorios en cada iteración dentro de sus respectivos rangos
	bool m_Fit; //Hacer el movimiento de vaciado y rellenado con Fit cuando utilizamos VCS
	bool m_Random; //Constructivo con bloques y aleatorizado con probabilidad geométrica
	int m_var_geom;

	std::set<BLOQUE_ARA*, compareBlocks> m_set_Bloques;
	short int m_bloques_heterogeneos;
	std::set<short int> m_set_indices;
	std::set<short int> m_set_indices_copia;
	std::vector<BLOQUE_ARA*> m_vector_Bloques;
	std::set<int, std::greater<int> >setlmax;
	std::set<int, std::greater<int> >setwmax;
	std::set<int, std::greater<int> >sethmax;

public:
	//constructor 0 container 1 multicontainer
	CONTAINER(char* nombre, int caso, int CS, bool bloque, float perdida, int vcs);
	//Lee los datos del container y los modifica directamente en la clase container.
	CONTAINER() {};
	void SetTiempoGrasp(int a) { m_time_final = a; m_tiempo_final_total = a; }
	//destructor
	~CONTAINER() {};
	void CrearInstanciasPedidos();
	void CrearBats();
	//Lectura de datos
	void LeerDatosContainer(char* nombre);
	void LeerDatosContainerPedidos(char* nombre);
	void LeerDatosMultiContainer(char* nombre);
	//Escritura de datos
	void EscribirDatosProgramaDibujo();
	void RestarConfiguracaosCon(CONFIGURACAO& grande, CONFIGURACAO& peque, std::list < CONFIGURACAO>& lista, std::list<CONFIGURACAO>& lista_b, bool& izq, bool& der, bool& abj, bool& arr, bool& den, bool& fue);
	void RestarConfiguracaosConReducir(CONFIGURACAO& grande, CONFIGURACAO& peque, std::list < CONFIGURACAO>& lista, std::list<CONFIGURACAO>& lista_b, std::list<CONFIGURACAO>& lista2, bool& izq, bool& der, bool& abj, bool& arr, bool& den, bool& fue);
	void RestarConfiguracaosConReducirVol(CONFIGURACAO& grande, CONFIGURACAO& peque, std::list < CONFIGURACAO>& lista, std::list<CONFIGURACAO>& lista_b, int vol, bool& izq, bool& der, bool& abj, bool& arr, bool& den, bool& fue);
	//Funciones Get
//	CClientDC *GetClientedc(){return m_clientedc;};
	int GetMenorVolumen() { return m_menor_volumen; };
	std::set<int, std::greater<int> >Get_setlmax() { return setlmax; };
	std::set<int, std::greater<int> >Get_setwmax() { return sethmax; };
	std::set<int, std::greater<int> >Get_sethmax() { return setwmax; };
	void CrearInstanciasPedidosFix();
	void Set_Random(bool a) { m_Random = a; };
	void Set_geometrica(int a) { m_var_geom = a; };
	bool Get_complete_shipment() { return m_complete_shipment; };
	int Get_X() { return m_X; };
	char* Get_File() { return m_file_to_write; };
	int Get_Y() { return m_Y; };
	int Get_Z() { return m_Z; };
	int Get_Q() { return m_Q; };
	int Get_LB() { return m_lb; };
	int Get_candidato() { return m_candidato; };
	int Get_Iteraciones() { return m_iteraciones; };
	int Get_Nesquinas() { return m_nesquinas; };
	int Get_Volumen_Utilizado() { return m_total_volumen_ocupado; };
	int Get_Sum_Freq() { return m_sum_freq; };
	int Get_Volumen() { return m_total_volumen; };
	int Get_TamRCL() { return m_TamRCL; };
	std::vector<int> Get_unasigned() { return piece_unasigned; };
	bool Get_Juntos() { return m_juntos; };
	bool Get_Rotacion() { return m_rotacion; };
	bool Get_Full_Supported() { return m_full_supported; };
	void Add_vol_incompletos(int a) { m_vol_incompletos += a; };
	void Set_vol_incompletos(int a) { m_vol_incompletos = a; };
	std::vector<int> Get_cajas_sin_asignar() { return m_cajas_sin_asignar; };
	void Add_cajas_sin_asignar(int val, int pos) { m_cajas_sin_asignar.emplace(m_cajas_sin_asignar.begin() + pos, m_cajas_sin_asignar[pos] + val); };
	std::list <BLOQUE>& Get_ListaBloques() { return m_Bloques; };
	std::vector < PIECE >& Get_Piezas() { return m_Pieces; };
	std::vector < PEDIDO >& Get_Pedidos() { return m_Pedidos; };
	std::vector < PEDIDO >& Get_candidatos() { return m_Pedidos_candidatos; };
	void SetBloquesAll(bool a){m_all_bloques= a;};
	void SetObjetivoMixto(bool a) { m_objetivo_mixto = a; };
	bool GetBloquesAll() { return m_all_bloques; };
	bool GetObjetivoMixto() { return m_objetivo_mixto; };
	short int Get_Peso_Diver(){return m_peso_diver;};
	bool GetRandom() { return m_Random; };
	bool Get_MC(){return m_multicontainer;};
	bool Get_VCS() { return m_VCS; };
	int Get_num_pedidos() { return m_num_pedidos; };
	void Set_VCS(bool a) { m_VCS = a; };
	void Set_completos(int a) { m_completos = a; };
	void Set_candidato(int a) { m_candidato = a; };
	void Set_Complete_Shipment(bool a) { m_complete_shipment = a; };
	short int Get_tipo_origen(){return m_tipo_origen;};
	void Set_Tipo_origen(short int a){m_tipo_origen=a;};
	bool Get_Descendent(){return m_descendent;};
	bool Get_Solo_Uno(){return m_un_movimiento;};
	int Get_alpha() { return alpha; };
	int Get_beta() { return beta; };
	void Add_completos() { m_completos++; };
	void Add_vol_cs(int a) { m_total_volumen_cs_ocupado += a; };
	double Get_gamma() { return gamma; };
	double Get_p() { return p; };
	std::list <CONFIGURACAO> &Get_ListaConfiguracaos(){return m_Configuracaos;};
	std::list <CONFIGURACAO> &Get_ListaBestConfiguracaos(){return m_Best_Configuracao;};
	std::list <SPACE> &Get_ListaSpaces(){return m_Spaces;};
	std::list < CONFIGURACAO > & Get_ListaRCL(){return m_ListaRCL;};
	std::vector <short int> &GetPiecesTabu(){return m_Pieces_Tabu;};
	std::vector <short int> &GetFrecuencias(){return m_frecuencias;};
	bool Get_Aleatorizado(){return m_Aleatorizado;};
	void Set_objetivo_vol(bool a){m_objetivo_vol=a;};
	void Add_unasigned(int j, int a) { piece_unasigned[j] += a; };
	bool Get_objetivo_vol(){return m_objetivo_vol;};
	short int Get_Tipo_OrdenPieces(){return m_tipo_orden_pieces;};
	short int Get_Tipo_Gravedad(){return m_tipo_gravedad;};
	void Set_Nesquinas(short int a){m_nesquinas=a;};
	void  Set_Tipo_Gravedad(short int a){m_tipo_gravedad=a;};
	void  Set_ImprimirMejoras(bool a){m_imprimir_mejoras=a;};
	void  Set_MaximosMovimientos(int a){m_max_movimientos=a;};
	void Set_Eleccion_Space(short int a){m_tipo_eleccion_space=a;};
	void SetValorQuita(double a){m_val_quita=a;};
	void SetMovimientos(bool a){m_movimientos=a;};
	void SetDescendent(bool a){m_descendent=a;};
	void SetUnMovimiento(bool a){m_un_movimiento=a;};
	void SetJuntos(bool a){m_juntos=a;};
	void SetRotacion(bool a){m_rotacion=a;};
	void SetFichero(char* a) { m_file_to_write = a; };
	void SetImprimir(bool a) { m_imprimir = a; };
	void SetLimite(int a) { m_Limite = a; };
	//DibujarOpengL
	void EscribirMejorSolucionOpenGL(std::list<CONFIGURACAO> lista);
	/*int DibujarOpenGL( std::list<CONFIGURACAO> lista );*/
	double CrearFormulacionCPlexPMedian(double Val, double tiempo, double* x, char** colname, char* colnamestore);
	void PrintPMedian(double Val);
	void PrintObjectiveSumY(int a);
	void PrintSumYGreaterOrEqual(double val);
	void PrintSumVariableEqualm();
	void PrintObjectiveFunctionMaxMinSum27();
	void PrintIntegerVariablesX();
	void PrintConstraintsILP(double Val);
	void PrintIntegerVariablesY();
	int DibujarOpenGL(std::list<CONFIGURACAO> lista) { return 0; }; //Para el servidor
	void Diversificar(void);
	void ReducirBloquesConEstaPieza(int kblo, int cuantos);
	int FuncionObjetivoCompleteShipment();
	//Funciones set
	void SetNombre(char *name){strcpy(m_Nombre,name);};
	//**************Para dibujar
	void SetEliminar(bool a){m_eliminar_espacios=a;};
	void SetTipoMejora(short int a){m_tipo_mejora=a;};
	void SetObjetivoCapas(bool a){m_objetivo_capas=a;};
	void SetDibujar(bool a){m_Dibujar=a;};
	void SetVerificar(bool a) { m_Verificar = a; };
	void SetPasoaPaso(bool a){m_paso_a_paso=a;};
	void SetFactorDibujar(double factor){m_factor=factor;};
	void SetGrados(double a){m_grados=a;};
	void SetTipoMixto(bool a){m_tipo_mixto=a;};
//	void SetClienteDC(CClientDC *d){m_clientedc=d;};
	void SetMejoraLocal(bool a){m_mejora_local=a;};
	void DibujarSolucion(std::list< SPACE > &lista_espacios, std::list < CONFIGURACAO > &lista_configuracaos);
	void DibujarSolucion(std::list< std::pair< int ,std::list < CONFIGURACAO > > > &lista_configuracaos);
	void EliminarPieza(int Id);
	void DibujarBloques(std::list < CONFIGURACAO > &);
	void DibujarBloques( std::list < CONFIGURACAO > &lista_configuracaos,int corx, int cory);
	bool Mejor_DistA_Que_DistB_Bloques(ORIG& A, int NumA, ORIG& B, int NumB, int Vol);
	void DibujarCaja3D(int x1,int y1, int z1, int x2, int y2, int z2,int,bool );
	void DibujarCaja3DBin(int x1,int y1, int z1, int x2, int y2, int z2,int Id,bool opaca,int corx,int cory);
	void BorrarElemento(CONFIGURACAO &C, std::list<CONFIGURACAO> &lista);
	void  EscribirSolucion();
	std::list<BLOQUE_ARA *> Crear_Bloques(BLOQUE_ARA& b1, BLOQUE_ARA& b2, int  maxL, int maxW,
		int  maxH, double min_fr, bool fsb);
	bool feasible(std::map<int, int>& nb_left_boxes);
	//******Funcion que me dice si cabe alguna pieza
	bool CabeAlguna(int dx,int dy,int dz);
	//me dice si cabe alguna con esta orientacion
	bool EstimacionConEstaOrientacionAlguna(int dx,int dy,int dz, int x, int y,int z){ return  (x<=dx && y<=dy &&  z<=dz);};
	//Esta tiene que sumar por cuantas cajas de media esta soportada cada caja 
	//que no esta en el suelo
	double Medida1Estabilidad(std::list<CONFIGURACAO> &lista);
	void ElegirPedidoVolumenFuera();
	void ElegirPedidoVolumenFueraPt();
	void ElegirPedidoVolumenDentro();
	void ElegirPedidoVolumenFuera(std::vector<PEDIDO>pedidos);
	void ElegirPedidoVolumenFueraPt(std::vector<PEDIDO>pedidos);
	void ElegirPedidoVolumenDentro(std::vector<PEDIDO>pedidos);
	void PuedoJuntarParecidas(int pieza1, int pieza2, int ancho1, int largo1, int alto1, int ancho2, int largo2, short int tipo1, short int tipo2);
	void JuntarPiezasParecidas();
	void EliminarInclusionesNuevos(std::list < SPACE > &Lista);
	void EliminarInclusionesListaAntigua(std::list < SPACE > &Lista);
	void ColocarOrdenadosNuevos(std::list< SPACE > &);
	void InsertarOrden(SPACE &Espacio);
	void InsertarConfiguracaoOrden(CONFIGURACAO& C, std::list<CONFIGURACAO>& lista);
	void InsertarPedidoOrden(PEDIDO& P);
	void JuntarSpacesBloques(std::list<SPACE> &lista, std::list<SPACE> &lista_temp, CONFIGURACAO &C);
	void ActualizarListasBloque(SPACE &EspacioT, CONFIGURACAO &Configuracao, bool poner);
	void ActualizarListasAra(SPACE& E, CONFIGURACAO& C);
	void ActualizarListasAraMov(SPACE& E, CONFIGURACAO& C, std::list<SPACE> &lista_espacios);
	void ArreglarCompleteShipment();
	void CotaCompleteShipment();
	BLOQUE  & BuscarPiezasBloque(int);
	BLOQUE_ARA& BuscarPiezasBloqueAra(int);
	void CambiarConfiguracaoBloque(CONFIGURACAO &C, SPACE &E, BLOQUE &B, CONFIGURACAO &C1, CONFIGURACAO &C2, std::list < SPACE > &lista, bool poner);
	void CambiarConfiguracaoBloqueMov(CONFIGURACAO &C, SPACE &E, BLOQUE &B, CONFIGURACAO &C1, CONFIGURACAO &C2, std::list < SPACE > &lista, bool poner, std::list < SPACE > &lista_espacios);
	//Cuanta el numero de cajas que soportan esta caja
	int NumeroDeCajasSoportanEsta(int x1,int y1, int z1, int x2, int y2, int z2,std::list<CONFIGURACAO> &lista);
	bool ComprobarFullSupportUno(CONFIGURACAO &it, std::list<CONFIGURACAO> &lista);
	///**** Calcula la menor dimension para un espacio
	void MinimaDimension();
	void MinimaDimensionMC();
	void MinimaDimensionMCMov();
	void MinimaDimensionMCMovP();
	void AumentarPiezas();
	void EliminarSpace(std::list < SPACE > &, SPACE &);

	//Esta mide el número medio de cajas que tiene 3 lados pegados a otras cajas
	//Por tanto lo primero recorrer todas las cajas
	double Medida2Estabilidad(std::list<CONFIGURACAO> &lista);
	int EstaCajaTiene3Pegados(int x1,int y1, int z1, int x2, int y2, int z2,std::list<CONFIGURACAO> &lista);
	int surface_in_contact_with_the_container_Bloque(BLOQUE_ARA& B, int x, int y, int z);
	int surface_in_contact_Bloque(BLOQUE_ARA& B, CONFIGURACAO& Bi, int x, int y, int z);
	double CS_Bloque(std::list<CONFIGURACAO> *lista, BLOQUE_ARA& B, int x, int y, int z);
	double VCS_Bloque(std::list<CONFIGURACAO> *lista, BLOQUE_ARA& B, SPACE &E, int x, int y, int z);
	
	std::list<CONFIGURACAO> Get_adjacent_blocks(std::list<CONFIGURACAO> *lista, int x1, int y1, int z1, int x2, int y2, int z2);

	//Compara dos conjuntos devuelve true si el primero es mejor que el segundo
	bool Mejor_DistA_Que_DistB_Espacios(ORIG &A, int VolA,ORIG &B, int VolB);
	//DEvuelve true si es mejor segun el orden de los vertices
	bool Mejor_DistA_Que_DistB_Origen(ORIG &A, int VolA,ORIG &B, int VolB);
	//Una vez que tiene la mejor solucion la intenta mover hacia un eje
	void CompactarConfiguracaos(std::list<CONFIGURACAO> &lista);
	bool  FuerzaDeGravedad(std::list<CONFIGURACAO> &,short int sentido);
	bool FuerzaDeGravedadIndividual(std::list<CONFIGURACAO> &,short int sentido);
	void ColocarBloqueEntero(std::vector<int> &blo_pos, std::list<CONFIGURACAO> &lista);
	int PuedoMover(std::list<CONFIGURACAO> &,int,int,int,int,int,int,short int);
	//Para que si empiezo desde uno inicialize las variables
	void InicializarVariables(void);


	bool Mejor_DistA_Que_DistB(SPACE & A, SPACE & B)
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
	};
	void ElegirConfiguracao(SPACE &,CONFIGURACAO &);
	void ElegirConfiguracao(SPACE &,CONFIGURACAO &,int);
	void ElegirConfiguracaoBloque(SPACE &, CONFIGURACAO &);
	void ElegirConfiguracaoBloqueAra(SPACE& Espacio, CONFIGURACAO& Configuracao);
	SPACE &ElegirSpace();
	void Constructivo(bool);
	void ConstructivoCS(bool);
	void ConstructivoMC(bool aleatorizado);
	void ConstructivoMC_TJuntos(bool aleatorizado);
	void ConstruirSolucionBin(std::list<CONFIGURACAO> &lista,bool manera);
	void ConstruirSolucionBinPartir(std::list<CONFIGURACAO> &lista,bool manera);
	void ConstruirSolucionBinC(std::list<CONFIGURACAO> &lista,bool manera);
	void RellenarVariosBinGlobal();
	void RellenarVariosBin(std::list< std::pair< int,  std::list<CONFIGURACAO> > > &lista);
	void RellenarVariosBin(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista,int hasta);
	void RellenarVariosBin(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista,int hasta,bool,CONFIGURACAO &);
	void RellenarVariosBinGlobal(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista);

	void Grasp();
	void GraspMC_Global( );
	void GraspMC_PorBin();
	void GraspUnBin();
	void VNDMC(bool secuencial);

	void MejoraLocal(bool fobjetivo);
	void ReactiveDeltaPaso1(std::vector <int > &vec_veces, std::vector <double> &vec_valor,std::vector <double> &vec_buenas);
	void ReactiveDeltaPaso2(std::vector <int > &vec_veces, std::vector <double> &vec_valor);
	void ActualizarConfiguracaoGravedad(CONFIGURACAO &E, int x1,int y1, int z1, int x2, int y2, int z2,std::list <CONFIGURACAO> &lista_temp, short int sentido);

	void ActualizarListas(SPACE &Espacio, CONFIGURACAO &Configuracao);
	void ActualizarListas(SPACE &Espacio, CONFIGURACAO &Configuracao,int );
	void ActualizarEspaciosElegido(SPACE &E, CONFIGURACAO &C, std::list< SPACE > &);
	void ActualizarEspaciosElegidoMC(SPACE &E, CONFIGURACAO &C,std::list <SPACE> &lista_temp);
	void ActualizarEspaciosElegidoMCP(SPACE &E, CONFIGURACAO &C,std::list <SPACE> &lista_temp);

	//Para insertalos en la lista ordenada
	void ColocarOrdenadosNuevos(std::list < SPACE > &,std::list< SPACE > &);
	void InsertarOrden(std::list < SPACE > &,SPACE &Espacio);
	//esta funcion me mantiene ordenados los bins de mayor a menor
	void InsertarOrden(std::list< std::pair< int, std::list< CONFIGURACAO > > > &Lista, std::pair< int, std::list< CONFIGURACAO > > &nuevo);

	void EliminarInclusiones();
	void EliminarInclusionesNuevosBloque(std::list < SPACE > &Lista);
	//Compara todos los de la lista con lo que ya hay metidos para ver si hay alguna inclusión
	void EliminarInclusionesListaAntigua(std::list < SPACE > &,std::list < SPACE > &Lista);
void  EscribirSolucion3DMC(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista);
	//Funcion que verifica varias cosas de la solucion
	void VerificarSolucion(std::list<CONFIGURACAO> &lista);
	void VerificarSolucionMC(std::list< std::pair<int, std::list<CONFIGURACAO> > > &lista);
	void EscribirSolucion(std::list<CONFIGURACAO> lista);

	//Funcion que comprueba si dos configuracaos intersectan es para verificar
	void ComprobarPedidos();
	bool ComprobarConfiguracaosNoIntersectan(std::list<CONFIGURACAO> &lista);
	//Funcion que mira si se cortan las configuracaos y los espacios vacios
	bool ComprobarConfiguracaosNoIntersectanSpaces(std::list<CONFIGURACAO> &lista);
	bool ComprobarDistBien(std::list<CONFIGURACAO>& lista);
	bool ComprobarConfiguracaosNoIntersectanSpacesMov(std::list<CONFIGURACAO> &lista, std::list<SPACE> &lista_es);
	bool ComprobarLimites(CONFIGURACAO &itB1);
	bool ComprobarFullSupport(std::list<CONFIGURACAO> &lista);
	bool ComprobarConfiguracaosNoIntersectanSpaces(std::list<CONFIGURACAO> &lista,std::list<SPACE> &lista_espacios);
	void ComprobarEspaciosNoIncluidos(std::list<SPACE>& lista);

	
	//Comprobar que todos los bloques son posibles
	bool ComprobarTodosPosible(std::list<CONFIGURACAO> &lista);
	bool ComprobarTodosPosibleMC(std::list< std::pair<int, std::list<CONFIGURACAO> > > &lista);

	//Estimacion de cuantas caben
	int EstimacionConEstaOrientacion(SPACE &Espacio, int x, int y,int z, int Id,int piezas_maximas);
	//Estimacion 

	int Estimacion(SPACE &Espacio);
	//Método de la burbuja para ordenar
	void Ordenar(std::list< std::pair < int, std::list< CONFIGURACAO > > > &);
	void BubbleSort(std::list<CONFIGURACAO> &lista,short int tipo) ;
	void  PintarSolucion(std::list<CONFIGURACAO> &lista);
	void EscribirSolucionLatex(std::list<CONFIGURACAO> lista);
	void EscribirSolucionLatex2D(std::list<CONFIGURACAO> lista);
	void EscribirSolucionLatex2DMC(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista);
	void EscribirSolucion2DMC(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista);
	void EscribirSolucionLatex3DMC(std::list< std::pair< int , std::list<CONFIGURACAO> > > &lista);
	//Le doy una configuracao y me reconstruye la solucion para
	//tener los espacios maximales otra vez
	void ConstruirSolucion(std::list<CONFIGURACAO> &lista,bool );
	void ConstruirSolucionP(std::list<CONFIGURACAO> &lista,bool );
	void PonerConfiguracao(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista,bool );

	//Para la otra distancia
	bool Mejor_DistA_Que_DistB_Espacios_Euclidea(int A, int VolA,int B, int VolB);
	//Funciones necesarias en el tabu
	//**********************
	void MejoraLocalMCQuitarUnBinVieja(bool perturbar);
	void MejoraLocalMCQuitarUnBin(bool perturbar);
	void MejoraLocalMCQuitarDosBin(bool perturbar);
	void MejoraLocalMCQuitarTresBin(bool perturbar);
	void MejoraLocalMCQuitarUltimos(bool,bool);
	void MejoraLocalMCQuitarUltimosCadaBin(bool);
	void MejoraLocalMCQuitarUltimosPartir(bool);
	void MejoraLocalMCQuitarUltimosLS(bool,bool);
	void MejoraLocalMCPieza(bool );

	void MejoraLocalTipo(int tipo);

	void MejoraLocalCapa(bool perturbar);
	void MejoraLocalPieza(bool perturbar);
	void MejoraLocalVaciado(bool perturbar);
	void MejoraLocalVaciadoTres(bool perturbar);
	void MejoraLocalQuitarBloque(bool perturbar);
	void MejoraLocalReducirBloque(bool perturbar);
	void MejoraLocalQuitarBloquePorCiento(bool perturbar);

	void ILS();
	void ILS_MC();

	void QuitarBloque(double porcentaje);
	int ValoresPosibles(int tipo,int c);


	int EstaCajaSoportada(int x1,int y1, int z1, int x2, int y2, int z2,std::list<CONFIGURACAO> &lista,int cantidad);
	void ConstruirSolucionMovimientos(std::list<CONFIGURACAO> &lista,bool );
	void RellenarSpaces(std::list<SPACE> &,std::list<CONFIGURACAO> &);

	void PonerConfiguracaoMov(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista_Con,std::list<CONFIGURACAO> &lista)	;
	void PonerConfiguracaoMovBloque(SPACE &Espacio, CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, bool compactada);
	void ElegirConfiguracaoMov(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista);
	void ElegirConfiguracaoMovBloqueAra(SPACE& SpaceElegido, CONFIGURACAO& Configuracao, std::list<CONFIGURACAO>& lista_configuracaos);
	void ElegirConfiguracaoMovBloque(SPACE &Espacio, CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista);
	void ElegirConfiguracaoMovDistinta(SPACE &Espacio,CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista);
	void ActualizarListasMov(SPACE &EspacioT, CONFIGURACAO &Configuracao,std::list<SPACE> &lista_espacios);
	void ActualizarListasBloqueMov(SPACE &EspacioT, CONFIGURACAO &Configuracao, std::list<SPACE> &lista_espacios, std::list<CONFIGURACAO> &lista_configuracaos, bool poner);
	void ActualizarListasMovP(SPACE &EspacioT, CONFIGURACAO &Configuracao,std::list<SPACE> &lista_espacios);

	//elegir space construciion
	SPACE & ElegirSpaceConstruccion();
	void ElegirMejorBloqueAumentar(SPACE &Espacio,MOVIMIENTO &M);
	void ElegirMejorPiezaAumentar(SPACE &Espacio,MOVIMIENTO &M);
	SPACE& ElegirSpaceMovimiento(std::list<SPACE>& lista, std::list<CONFIGURACAO>& lista_conf);// , bool poner);
	SPACE& ElegirSpacePonerConfiguracaoMov(std::list<CONFIGURACAO>& lista_configuracaos, std::list<SPACE>& lista_espacios);
	SPACE & ElegirSpaceMovimientoGlobal(std::list< std::list< SPACE > > &lista,int &Dequebin);
	void ElegirSpace(SPACE &espacio, bool &posi);
	void JuntarSpaces(std::list<SPACE> &lista,std::list<SPACE> &);
	SPACE & ElegirSpace(bool &posi);
	void ElegirSpaceMovimiento(SPACE &espacio,std::list<SPACE> &lista,bool  &posi);
	void MinimaDimensionMov();
	void EliminarMasDe100Espacios(std::list<SPACE> &lista_espacios);

	bool JuntarTwoSpaces(SPACE &Space1, SPACE &Space2, std::list<SPACE> &lista_espacios);
	//No estan ordenadas, es decir elimino las incluisiones pero no necesito que la lista ordenada
	void EliminarInclusionesDeLaSegundaListaEnLaPrimera(std::list<SPACE> &lista_Viejos,std::list <SPACE > &Lista);
	void EliminarInclusionesEstaLista(std::list < SPACE > &Lista);
	void InsertarOrdenUnica(std::list<SPACE> &lista_vieja,SPACE &Espacio);
	bool CabeAlgunaMov(int dx,int dy, int dz);
	void ActualizarEspaciosElegidoMov(SPACE& E, CONFIGURACAO& C, std::list <SPACE>& lista_temp, std::list <SPACE>& lista_espacios);
	void PintarSpaces(std::list<SPACE> &lista);
	void Maximalizar(std::list<SPACE> &lista1);
	void ActualizarBloquesElegido( CONFIGURACAO &Vieja,CONFIGURACAO &Nueva,std::list <CONFIGURACAO> &lista_temp, std::list<CONFIGURACAO> &lista);
	void ActualizarBloquesElegidoReducir(CONFIGURACAO &Vieja, CONFIGURACAO &Nueva, std::list <CONFIGURACAO> &lista_temp, std::list<CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista2);
	void ActualizarBloquesElegidoReducirVol(CONFIGURACAO &Vieja, CONFIGURACAO &Nueva, std::list <CONFIGURACAO> &lista_temp, std::list<CONFIGURACAO> &lista, int vol);
	void ActualizarListaDeBloques(CONFIGURACAO &Configuracao,std::list<CONFIGURACAO> &lista, bool guardar);
	void ActualizarListaDeBloquesAbajo(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, CONFIGURACAO &Exc);
	void ActualizarListaDeBloquesReducir(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista2);
	void ActualizarListaDeBloquesReducirAbajo(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, std::list<CONFIGURACAO> &lista2, CONFIGURACAO &Exc);
	void ActualizarListaDeBloquesReducirVol(CONFIGURACAO &Configuracao, std::list<CONFIGURACAO> &lista, int vol);
	bool CompactarConfiguracaosEsquinas(std::list<CONFIGURACAO> &lista,short int lugar);
	bool FuerzaDeGravedadEsquina(std::list<CONFIGURACAO> &lista,short int lugar,short int sentido, short int dir);
	int PuedoMover(std::list<CONFIGURACAO> &lista,int x1,int y1,int z1,int x2,int y2,int z2,short int sentido,short int dir);
	void Constructivokk();
	SPACE & ElegirSpaceConstruccionNueva(bool );
	SPACE& ElegirSpacePonerConfiguracao(std::list<CONFIGURACAO> lista);
	void VNS(bool secuencial);
	void VNSCS();
	void PrimeraImplementacion();
	void Constructivo_random();
	void Constructivo_random_cs();
	void ConstruccionPorPedidos();
	void knapsack_bouknap();
	void AnalisisInstancias();
	void VND(bool secuencial);
	void ReducirPiezasYBins();
	void ReducirPiezasX();
	void ReducirPiezasY();
	void ReducirPiezasZ();
	void JuntarPiezasIguales();

	void PintarPieces();
	void JuntarSpacesNuevos(std::list<SPACE>& lista);

	///

	std::set<BLOQUE_ARA*,compareBlocks> Generar_bloques_sencillos();
	void Generar_Bloques(double min_fr, int max_bl, bool fsb);
	void ColocarPiezasBloque(int xi, int yi, int zi, int x0, int y0, int z0, BLOQUE_ARA& Bloque, std::list<CONFIGURACAO>& lista, int orig);


};


//*********************
// CLASE PIEZA
//********************
class PIECE{
	int m_Id; //numero para identificar la pieza
	int m_x; //Largo tablero
	int m_y; //Ancho tablero
	int m_z;
	int m_q; //Numero de piezas
	//Siempre alguno es posible
	bool m_Rotate_x; //SE puede rotar en dirección vertical en el eje x
	bool m_Rotate_y; //Se puede rotar en dirección en el eje y
	bool m_Rotate_z; //Se puede rotar en dirección en el eje z.
	int m_Volumen; //Volumen de la pieza
	int m_num; //numero de piezas utilizado
	int m_asignadas; //Cuando tenemos complete shipment, número de cajas que están asignadas, es decir, que pertenecen a un pedido completo
	//Puntero estatico al Contenedor
	static CONTAINER *m_Container;

public:
	//constructor
	PIECE(int,int, bool, int , bool, int ,bool , int ,CONTAINER *a);
	PIECE(){};
	bool operator < ( const PIECE& p2) const;

	//destructor
	~PIECE(){};
	bool is_valid_orientation(int );
	//Funciones set
	void Set_x(int a){m_x=a;};
	void Set_y(int a){m_y=a;};
	void Set_z(int a){m_z=a;};
	void Set_Num(int a){m_num=a;};
	void Set_Q(int a) { m_q = a; };
	void Add_Volumen(int a){m_Volumen+=a;};
	//Funciones Get
	void Set_Id(int a){m_Id=a;};
	void Set_asign(int a) { m_asignadas = a; };
	int Get_Id() const {return m_Id;};
	int Get_x() const {return m_x;};
	int Get_y() const {return m_y;};
	int Get_z() const {return m_z;};
	bool Get_Rx(){return m_Rotate_x;};
	bool Get_Ry(){return m_Rotate_y;};
	bool Get_Rz(){return m_Rotate_z;};
	int Get_Num(){return m_num;};
	int Get_q(){return m_q;};
	int Get_Volumen() const {return m_Volumen;};
	int Get_asignadas() { return m_asignadas; };
	void Add_Num(int a){m_num+=a;};
	void Add_q(int a){m_q+=a;};
	void Add_asign(int a) { m_asignadas += a; };

};

//*********************
// CLASE BLOQUE
//********************
class BLOQUE {
	int m_Id1; //numero para identificar la pieza 1 (bloques formados por dos tipos de piezas)
	int m_Id2; //numero para identificar la pieza 2 (bloques formados por dos tipos de piezas)
	int m_Id;
	int m_x; //Largo tablero
	int m_y; //Ancho tablero
	int m_z;
	int m_num1;
	int m_num2;
	int m_x1;
	int m_z1;
	int m_x2;
	int m_z2;
	int m_idblo;
	short int m_tipo_1;
	short int m_tipo_2;
	int m_q; //Numero de piezas
	//Siempre alguno es posible
	bool m_Rotate_x; //SE puede rotar en dirección vertical en el eje x
	bool m_Rotate_y; //Se puede rotar en dirección en el eje y
	bool m_Rotate_z; //Se puede rotar en dirección en el eje z.
	int m_Volumen; //Volumen de la pieza
	bool m_perdida;
	int m_peso;
	//int m_nbloq; //Número de bloques utilizado en la solución

	int  m_S_x;
	int  m_S_y;
	int  m_S_z;

	int m_num; //numero de piezas utilizado
	//Puntero estatico al Contenedor
	static CONTAINER *m_Container;

public:
	//constructor
	BLOQUE(int, int, int, int, int, CONTAINER *a, int, int);
	//BLOQUE::BLOQUE(int id1, int id2, int x, int y, int z, int x1, int y1, int x2, int y2, CONTAINER *a, int, int);
	BLOQUE(int, int, int, int, int, int, int, int, int, CONTAINER *a, int, int, short int, short int);

	int Get_m_peso() { return m_peso; };
	int Get_Sx() { return m_S_x; };
	int Get_Sy() { return m_S_y; };
	int Get_Sz() { return m_S_z; };

	BLOQUE() {};
	//destructor
	~BLOQUE() {};
	//Funciones set
	void Set_x(int a) { m_x = a; };
	void Set_y(int a) { m_y = a; };
	void Set_z(int a) { m_z = a; };
	void Set_Sx(int a) { m_S_x = a; };
	void Set_Sy(int a) { m_S_y = a; };
	void Set_Sz(int a) { m_S_z = a; };
	void Set_Num(int a) { m_num = a; };
	//Funciones Get
	int Get_Id1() { return m_Id1; };
	int Get_Id2() { return m_Id2; };
	int Get_Num1() { return m_num1; };
	int Get_Num2() { return m_num2; };
	//int Get_Nbloq() { return m_nbloq; };
	int Get_Id() { return m_Id; };
	int Get_x() { return m_x; };
	int Get_y() { return m_y; };
	int Get_x_P1() { return m_x1; };
	int Get_z_P1() { return m_z1; };
	int Get_x_P2() { return m_x2; };
	int Get_z_P2() { return m_z2; };
	int Get_z() { return m_z; };
	bool Get_Rx() { return m_Rotate_x; };
	bool Get_Ry() { return m_Rotate_y; };
	bool Get_Rz() { return m_Rotate_z; };
	bool Get_Perdida() { return m_perdida; };
	int Get_Num() { return m_num; };
	int Get_q() { return m_q; };
	int Get_Volumen() { return m_Volumen; };
	void Add_Num(int a) { m_num += a; };
};
struct buscar_por_id {
	buscar_por_id(int const& id) : id(id) {}
	bool operator() (BLOQUE_ARA* const& B) {
		return B->Get_Id() == id;
	}
private:
	int id;
};
struct buscar_por_volumen {
	buscar_por_volumen(SPACE const& E, std::vector<PIECE> const& m_Pieces, bool const& mixto) : E(E), m_Pieces(m_Pieces), mixto(mixto) {}
	bool operator() (BLOQUE_ARA* const& B) {
		if (mixto==true && B->Get_tipo() == 0)
			return false;
		if (B->Get_Volumen() > E.Get_Volumen())
			return false;
		if (E.Get_dx() < B->Get_x())
			return false;
		if (E.Get_dy() < B->Get_y())
			return false;
		if (E.Get_dz() < B->Get_z())
			return false;
		std::map<int, int>::iterator itm, itmfin = B->Get_num_pieces_tipo().end();
		bool puede = false;
		for (itm = (B->Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
		{
			puede = m_Pieces[itm->first].Get_q() - m_Pieces[itm->first].Get_Num() >= itm->second;
			if (puede == false)
				return false;
		}
		return true;
	}
private:
	SPACE E;
	std::vector<PIECE> m_Pieces;
	bool mixto;
};
struct buscar_por_volumen_mov {
	buscar_por_volumen_mov(SPACE const& E, std::vector<short int> const& m_Pieces_tabu, std::vector<PIECE> const& m_Pieces, bool const &mixto) : E(E), m_Pieces_tabu(m_Pieces_tabu), m_Pieces(m_Pieces), mixto(mixto) {}
	bool operator() (BLOQUE_ARA* const& B) {
		if (B->Get_Volumen() > E.Get_Volumen())
			return false;
		if (E.Get_dx() < B->Get_x())
			return false;
		if (E.Get_dy() < B->Get_y())
			return false;
		if (E.Get_dz() < B->Get_z())
			return false;
		std::map<int, int>::iterator itm, itmfin = B->Get_num_pieces_tipo().end();
		bool puede = false;
		for (itm = (B->Get_num_pieces_tipo().begin()); itm != itmfin; itm++)
		{
			puede = (m_Pieces[itm->first].Get_q() - m_Pieces_tabu[itm->first] >= itm->second);
			if (puede == false)
				return false;
		}
		return true;
	}
private:
	SPACE E;
	std::vector<short int> m_Pieces_tabu;
	std::vector<PIECE> m_Pieces;
	bool mixto;
};







#endif