#ifndef _LPCPLEX_H_
#define _LPCPLEX_H_

#include "Container.h"
#include "ilcplex/ilocplex.h"
ILOSTLBEGIN

#pragma warning(disable:4786)
#pragma warning(disable:4996)


using namespace std;
/*
	IloIntVarArray  variable entera
	IloNumVarArray  variable real
*/
typedef IloIntVarArray NumVector;
typedef IloArray<IloNumVarArray> NumVarMatrixF;
typedef IloArray<IloIntVarArray> NumVarMatrix;
typedef IloArray<IloNumVarArray> NumVarMatrix2F;
typedef IloArray<IloIntVarArray> NumVarMatrix2;
typedef IloArray<IloArray<IloNumVarArray> > NumVarMatrix3F;
typedef IloArray<IloArray<IloIntVarArray> > NumVarMatrix3;
typedef IloArray<IloArray<IloArray<IloIntVarArray> > > NumVarMatrix4;
typedef IloArray<IloBoolVarArray> BoolVarMatrix;



class LPCPLEX
{

	char m_nombre[200];

	IloEnv env;
	IloModel model;
	IloCplex cplex;
	IloEnv env2;
	IloModel model2;
	IloCplex cplex2;

public:

	void modelo_pedidos(CONTAINER* contenedor);
	void modelo_semiasignacion(CONTAINER* contenedor);
	void dibujar_solucion(NumVarMatrix2& x_ij, NumVector& z_i, int& numpedidos, int& numtiposcaja);
};


#endif
