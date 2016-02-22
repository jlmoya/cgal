// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef DELAUNAY_3D_H
#define DELAUNAY_3D_H
#ifdef __cplusplus 
extern "C" { 
#endif

void* delaunay_triangulation_3(double* x, double* y,double* z,int nbpts);

int* dt3_get_connectivity(void* Ptr,int* Nbtetra);

int dt3_delete(void* Ptr);

int* dt3_get_connectivity(void* Ptr,int* Nbtetra);

void dt3_insert_points(void* Ptr,double* x, double* y,double* z,int nbpts);

void dt3_remove_points(void* Ptr,double* x, double* y,double* z,int nbpts);




#ifdef __cplusplus
} 
#endif
#endif
