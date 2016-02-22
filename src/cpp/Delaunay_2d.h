// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef DELAUNAY_2D_H
#define DELAUNAY_2D_H
#ifdef __cplusplus 
extern "C" { 
#endif

void* delaunay_triangulation_2(double* x, double* y,int nbc);

int* dt2_get_connectivity(void* Ptr,int*NbTri);

int dt2_delete(void* Ptr);

int* dt2_get_connectivity(void *Ptr,int *NbTri);

void dt2_insert_points(void* Ptr,double* x, double* y,int nbc);

void dt2_remove_points(void* Ptr,double* x, double* y,int nbc);

#ifdef __cplusplus
} 
#endif
#endif
