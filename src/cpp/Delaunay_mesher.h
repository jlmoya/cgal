// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef DELAUNAY_MESHER_H
#define DELAUNAY_MESHER_H
#ifdef __cplusplus 
extern "C" { 
#endif

int mesh2_delete(void* Ptr);

int* mesh2_get_connectivity(void* Ptr,int*NbTri);

double* mesh2_get_coord(void* Ptr,int* nbpts);

void mesh2_refine(void* Ptr,double shapebound,double upperbound);

void mesh2_set_seeds(void* Ptr,double* x,double* y,int nbseeds);

void* mesh_2(double* Pslg,int nbconstraint);

#ifdef __cplusplus
} 
#endif
#endif

