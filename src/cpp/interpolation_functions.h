// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef INTERPOLATION_FUNCTIONS_H
#define INTERPOLATION_FUNCTIONS_H
#ifdef __cplusplus 
extern "C" { 
#endif

double** interp3(double** xi, double** yi,double** zi,double* x,double* y,double* z,double*** v,int x_n,int y_n,int z_n,int xi_m,int xi_n);

double* interp2(double* xi, double* yi,double* x,double* y,double* z,int x_n,int y_n,int xi_m,int xi_n);




#ifdef __cplusplus
} 
#endif
#endif
