// Copyright (c) 2005  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CG-LAB; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CG-LAB.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Id: Constrained_Delaunay.cpp 6 2005-12-05 15:53:46Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/Constrained_Delaunay.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Filtered_kernel.h>
#include <CGAL/Cartesian.h>
//#include <CGAL/Simple_cartesian.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <map>
#include <vector>
#include <iostream>
#include "cgal_exception.h"
#include "Constrained_Delaunay.h"

/********************************************************************/
//					Constrained_Delaunay_triangulation_2
//
/********************************************************************/


struct Kernel : CGAL::Exact_predicates_inexact_constructions_kernel 		{};
typedef CGAL::Triangulation_vertex_base_2<Kernel>                     	cVb;
typedef CGAL::Constrained_triangulation_face_base_2<Kernel>          		Fb;
typedef CGAL::Triangulation_data_structure_2<cVb,Fb>              		TDS;
typedef CGAL::No_intersection_tag                                 		Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<Kernel, TDS, Itag> 	CDT;

typedef CDT::Point         										 		Point_2;
typedef CDT::Vertex_handle 												cVertex_handle;
typedef CDT::Finite_faces_iterator 								cfaces_iterator;
typedef CDT::Face_handle 										      Face_handle;

std::set<CDT*> ListOfCDT;
extern "C" int send_scilab_job(char *job);

extern "C"
{
    void* constrained_delaunay_2(double* x, double* y,double* cxy,int nbpts,int nbconstraint)
	{
		CDT* cdt = new CDT;
		ListOfCDT.insert(cdt);
		//CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			// insertion des points.
			for(int i=0; i< nbpts; i++)
			{
				Point_2 P(x[i],y[i]);
				cdt->insert(P);
			}
			// insertion des contraintes.
			for(int i=0; i< nbconstraint; i++)
			{
				Point_2 P1(cxy[i],cxy[i+nbconstraint]);
				Point_2 P2(cxy[i+2*nbconstraint],cxy[i+3*nbconstraint]);
				cdt->insert_constraint(P1,P2);
			}
		}catch(...)
			{
				send_scilab_job("printf(''error:\t the triangulation is not valid with the given points and constaints\n'')");
				return 0;
			}
		return (void*) cdt;
	}

}


extern "C"
{
    int* cdt2_get_connectivity(void* Ptr,int* NbTri)
	{
		CDT* cdt = (CDT*)Ptr;
 		int* TRI = 0;
		//CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			std::map<cVertex_handle,int> listVertex;
			std::vector<int> IndTRI;

			CDT::Finite_vertices_iterator vit;
			int ind = 1;
			for (vit = cdt->finite_vertices_begin(); vit != cdt->finite_vertices_end(); ++vit)
			{
				listVertex[vit] = ind;
				ind ++;
			}

			int count = 0;
			for(cfaces_iterator iter = cdt->finite_faces_begin(); iter!= cdt->finite_faces_end();++iter)
			{
				cVertex_handle vertex1 = (*iter).vertex(0);
				cVertex_handle vertex2 = (*iter).vertex(1);
				cVertex_handle vertex3 = (*iter).vertex(2);
				IndTRI.push_back(listVertex[vertex1]);
				IndTRI.push_back(listVertex[vertex2]);
				IndTRI.push_back(listVertex[vertex3]);

				count++;
			}

			*NbTri = count;

			unsigned int nbtri = IndTRI.size();
			TRI = (int*)malloc(nbtri*sizeof(int));

			if(!TRI)return 0;

			for(unsigned int j=0; j< nbtri; j++)
			{
				TRI[j] = IndTRI[j];
			}
		}catch(...)
			{
				send_scilab_job("printf(''\terror: unable to get connectivity of this object'')");
				if (TRI != NULL)
				{
					free(TRI);
					TRI = NULL;
				}
			}
		return TRI;
	}
}

extern "C"
{
    double* cdt2_get_coord(void* Ptr,int* nbpts)
	{
		//CGAL::set_error_handler(_scilab_cgal_error_handler);
		double* Coord = 0;
		try
		{
			CDT* cdt = (CDT*)Ptr;
			int nbvertices = cdt->number_of_vertices();
			*nbpts = nbvertices;


			Coord = (double*)malloc(2*nbvertices*sizeof(double));

			if(!Coord)return 0;

			int i =0;
			CDT::Finite_vertices_iterator vit;
			for (vit = cdt->finite_vertices_begin(); vit != cdt->finite_vertices_end(); ++vit)
			{
				Coord[i] = vit->point().x();
				Coord[i+(*nbpts)] = vit->point().y();
				i++;
			}
		}catch(...)
			{
				send_scilab_job("printf(''\terror: unable to get coordinates of this object'')");
				if (Coord != NULL)
				{
					free(Coord);
					Coord = NULL;
				}
			}
			return Coord;
	}
}

extern "C"
{
    void cdt2_insert_points(void* Ptr,double* x, double* y,int nbpts)
	{
		CDT* cdt = (CDT*)Ptr;
		//CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			for(int i=0; i< nbpts; i++)
			{
				Point_2 P(x[i],y[i]);
				cdt->insert(P);
			}
		}catch(...)
			{
					send_scilab_job("printf(''\terror: unable to insert this point(s)'')");
			}
	}

}
extern "C"
{
    void cdt2_insert_constraints(void* Ptr,double* cxy,int nbconstraint)
	{
		//CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			CDT* cdt = (CDT*)Ptr;
			for(int i=0; i< nbconstraint; i++)
			{
				Point_2 P1(cxy[i],cxy[i+nbconstraint]);
				Point_2 P2(cxy[i+2*nbconstraint],cxy[i+3*nbconstraint]);
				cdt->insert_constraint(P1,P2);
				if(!cdt->is_valid())send_scilab_job("printf(''\terror: with this new constraint(s) cdt becomes not valid'')");
			}
		}catch(...)
			{
					send_scilab_job("printf(''\terror: unable to insert this constraint(s)'')");
			}
	}

}
extern "C"
{
    void cdt2_remove_constraints(void* Ptr,double* cxy,int nbconstraint)
	{
		//CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			CDT* cdt = (CDT*)Ptr;

			for(int i=0; i< nbconstraint; i++)
			{
				Point_2 P1(cxy[i],cxy[i+nbconstraint]);
				Point_2 P2(cxy[i+2*nbconstraint],cxy[i+3*nbconstraint]);

				int id1,id2;
				CDT::Locate_type type1,type2;
				Face_handle face1 = cdt->locate(P1,type1,id1);
				Face_handle face2 = cdt->locate(P2,type2,id2);
				cVertex_handle vertex1 = face1->vertex(id1);
				cVertex_handle vertex2 = face2->vertex(id2);

				Face_handle face;
				int id;

				if(cdt->is_edge(vertex1,vertex2,face,id) ){
					cdt->remove_constraint(face,id);
				}
			}
		}catch(...)
			{
					send_scilab_job("printf(''\terror: unable to remove this constraint(s)'')");
			}
	}

}

extern "C"
{
    void cdt2_remove_points(void* Ptr,double* x, double* y,int nbpts)
	{
		//CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			CDT* cdt = (CDT*)Ptr;
			for(int i=0; i< nbpts; i++)
			{
				Point_2 P(x[i],y[i]);
				int id;
				CDT::Locate_type type;
				Face_handle face = cdt->locate(P,type,id);
				cVertex_handle vertex = face->vertex(id);
				if(type == 0/*VERTEX*/)cdt->remove(vertex);
			}
		}catch(...)
			{
					send_scilab_job("printf(''\terror: unable to remove this points(s)'')");
			}
	}

}
extern "C"
{
    int cdt2_delete(void* Ptr)
	{
		//CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{

			CDT* cdt = (CDT*)Ptr;
			if(!cdt)
			{
				for(std::set<CDT*>::iterator iter = ListOfCDT.begin();iter != ListOfCDT.end();iter++)
				{
					delete (*iter);
				}
				ListOfCDT.clear();
				return 0;
			}else
			{
				std::set<CDT*>::iterator iter = ListOfCDT.find(cdt);
				if(iter != ListOfCDT.end())
				{
					ListOfCDT.erase(iter);
					delete cdt;
				}
			}
		}catch(...)
			{
					send_scilab_job("printf(''\terror: unable to delete this pointer(s)'')");
			}
			return 0;
	}

}

