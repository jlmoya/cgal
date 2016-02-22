// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef DELAUNAY_ND_H
#define DELAUNAY_ND_H
#ifdef __cplusplus 
extern "C" { 
#endif

extern void* delaunay_triangulation_n(double* pts,int n,int nbpts);

extern int* dtn_get_connectivity(void* Ptr,int* Nbsimplex,int* curdim);

extern int dtn_delete(void* Ptr);

void dtn_insert_points(void* Ptr,double* pts,int n,int nbpts);



#ifdef __cplusplus
} 
#endif
#endif
