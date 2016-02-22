// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#ifndef SURFACE_MESHER_H
#define SURFACE_MESHER_H
#ifdef __cplusplus 
extern "C" { 
#endif

void* surface_mesher(char * image_file,double iso_value,double* bounding_sphere,double* mesh_criteria);

int* sm_get_connectivity(void* Ptr,int* Nbtetra);

double* sm_get_coord(void* Ptr,int* nbpts);

int delete_surface_mesher(void* Ptr);

int send_scilab_job(char *job);


#ifdef __cplusplus
} 
#endif
#endif

