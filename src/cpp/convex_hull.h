// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H
#ifdef __cplusplus 
extern "C" { 
#endif

int* convex_hull_3(double* x,double* y,double* z,int nbpts,int * nbtab,int* nbfacet,int* facetdegree);

int* convex_hull_2(double* xy,int nb,int* nbind);

#ifdef __cplusplus
} 
#endif
#endif
