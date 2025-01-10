// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


#include "gateway_cglab.h"
#include "localization.h"

extern double* interp2(double* xi, double* yi,double* x,double* y,double* z,int x_n,int y_n,int xi_m,int xi_n);

extern double** interp3(double** xi, double** yi,double** zi,double* x,double* y,double* z,double*** v,int x_n,int y_n,int z_n,int xi_m,int xi_n);

// extern int send_scilab_job(char *job);
//--------------------------------------------------------------
//			Interface interp2
//---------------------------------------------------------------
int sci_interp2(GW_PARAMETERS)
{
	int minlhs=0, maxlhs=1, minrhs=5, maxrhs=5;
	int x_m,x_n,l1,xi_m,xi_n,l2,y_m,y_n,l3,yi_m,yi_n,l4,z_m,z_n,l5,l6;

	double* ZI = 0;
	int j = 0;
	int i = 0;
	int N = 0;
	CheckRhs(minrhs,maxrhs) ;
	CheckLhs(minlhs,maxlhs) ;

	GetRhsVar(1, "d", &xi_m, &xi_n, &l1);
	GetRhsVar(2, "d", &yi_m, &yi_n, &l2);
	GetRhsVar(3, "d", &x_m, &x_n, &l3);
	GetRhsVar(4, "d", &y_m, &y_n, &l4);
	GetRhsVar(5, "d", &z_m, &z_n, &l5);

	if(z_m != y_n || z_n != x_n )
	{
		Scierror(999, "%s: size incompatibility between grid points and values", fname);
		return 0;
	}

	if(xi_m != yi_m || xi_n != yi_n )
	{
		Scierror(999, "%s: bad inputs for xp, yp", fname);
		return 0;
	}

	ZI = interp2(stk(l1),stk(l2),stk(l3),stk(l4),stk(l5),x_n,y_n,xi_m,xi_n);
	if(!ZI)return 0;
	CreateVar(6, "d",&xi_m, &xi_n, &l6);

	N = xi_m*xi_n;
	for(j=0; j< N; j++) *stk(l6+j)= ZI[j];

	LhsVar(1) = 6;

	free(ZI);

	return 0;

}

//--------------------------------------------------------------
//			Interface interp3
//---------------------------------------------------------------
int sci_interp3(GW_PARAMETERS)
{
	int minlhs=0, maxlhs=1, minrhs=7, maxrhs=7;
	int x_m,x_n,l1;
	int xi_m,xi_n,l2;
	int y_m,y_n,l3;
	int yi_m,yi_n,zi_m,zi_n,l4,z_m,z_n,l5,l6;
	int v_m,v_n,v_s,l7,l8;
	double** V = 0;
	int j = 0;
	int i = 0;
	int k = 0;
	int N = 0;
	double** xp = 0;
	double** yp = 0;
	double** zp = 0;
	double*** v = 0;

	CheckRhs(minrhs,maxrhs) ;
	CheckLhs(minlhs,maxlhs) ;

	GetRhsVar(1, "d", &xi_m, &xi_n, &l1);
	GetRhsVar(2, "d", &yi_m, &yi_n, &l2);
	GetRhsVar(3, "d", &zi_m, &zi_n, &l3);
	GetRhsVar(4, "d", &x_m, &x_n, &l4);
	GetRhsVar(5, "d", &y_m, &y_n, &l5);
	GetRhsVar(6, "d", &z_m, &z_n, &l6);
	GetRhsVar(7, "d", &v_m, &v_n, &l7);


	xp = (double**)malloc(xi_m*sizeof(double*));
	yp = (double**)malloc(xi_m*sizeof(double*));
	zp = (double**)malloc(xi_m*sizeof(double*));
	v = (double***)malloc(x_n*sizeof(double*));

	for (i = 0 ; i < xi_m ; i++)
	{
	 	xp[i] = (double*)malloc(xi_n*sizeof(double));
	 	yp[i] = (double*)malloc(xi_n*sizeof(double));
	 	zp[i] = (double*)malloc(xi_n*sizeof(double));
	}

	for (i = 0 ; i < x_n ; i++)
	{
	 	v[i] = (double**)malloc(y_n*sizeof(double*));
	}
	for (i = 0 ; i < x_n ; i++)
	{
		for(j = 0 ; j < y_n ; j++) v[i][j] = (double*)malloc(z_n*sizeof(double));
	}

	for( j =0 ; j < xi_n ; j++)
	{
		for( i =0 ; i < xi_m ; i++)
		{
			xp[i][j] = *stk(l1+j*xi_m+i);
			yp[i][j] = *stk(l2+j*xi_m+i);
			zp[i][j] = *stk(l3+j*xi_m+i);
		}
	}

	for( k =0 ; k < z_n ; k++)
	{
		for( j =0 ; j < y_n ; j++)
		{
			for( i =0 ; i < x_n ; i++) v[i][j][k] = *stk(l7+i+j*x_n+k*x_n*y_n);

		}
	}

	V = interp3(xp,yp,zp,stk(l4),stk(l5),stk(l6),v,x_n,y_n,z_n,xi_m,xi_n);
	if(!V)return 0;

	CreateVar(8, "d",&xi_m, &xi_n, &l8);

	N = xi_m*xi_n;
	for (i =0 ; i < xi_m ; i++){
		for(j=0; j< xi_n; j++) *stk(l8+i*xi_n+j)= V[i][j];
	}
	LhsVar(1) = 8;

	for (i = 0 ; i < x_n ; i++)
	{
		for(j = 0 ; j < y_n ; j++) free(v[i][j]);
	}

	for (i = 0 ; i < x_n ; i++) free(v[i]);

	for (i = 0 ; i < xi_m ; i++)
	{
	 	free(xp[i]);
		free(yp[i]);
		free(zp[i]);
		free(V[i]);
	}

	free(xp);
	free(yp);
	free(zp);
	free(v);
	free(V);

	return 0;

}

