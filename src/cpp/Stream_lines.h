// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef STREAM_LINES_H
#define STREAM_LINES_H
#ifdef __cplusplus 
extern "C" { 
#endif

void* streamlines_2(double* u,double* v,double separating_distance,int u_m,int u_n,int* nb_stls,double integrator);

int* get_nbpts_of_stls(void* Ptr);

double* get_stls(void* Ptr,int nb_pts);

int delete_stls(void* Ptr);

#ifdef __cplusplus
} 
#endif
#endif
