// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef CONSTRAINED_DELAUNAY_H
#define CONSTRAINED_DELAUNAY_H
#ifdef __cplusplus 
extern "C" { 
#endif
void* constrained_delaunay_2(double* x, double* y,double* cxy,int nbpts,int
nbconstraint);

int* cdt2_get_connectivity(void* Ptr,int* NbTri);

double* cdt2_get_coord(void* Ptr,int* nbpts);

void cdt2_insert_points(void* Ptr,double* x, double* y,int nbpts);

void cdt2_insert_constraints(void* Ptr,double* cxy,int nbconstraint);

void cdt2_remove_constraints(void* Ptr,double* cxy,int nbconstraint);

void cdt2_remove_points(void* Ptr,double* x, double* y,int nbpts);

int cdt2_delete(void* Ptr);
#ifdef __cplusplus
} 
#endif
#endif
