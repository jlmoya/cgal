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
// $Id: Delaunay_3d.cpp 6 2005-12-05 15:53:46Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/Delaunay_3d.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_3.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <map>
#include <vector>
#include <iostream>
#include "cgal_exception.h"
#include <CGAL/assertions_behaviour.h>

extern"C"
{
#include "sciprint.h"
}

/********************************************************************/
//					Delaunay 3D
//
/********************************************************************/
typedef CGAL::Exact_predicates_inexact_constructions_kernel 				Kernel;
typedef CGAL::Triangulation_vertex_base_with_info_3<int, Kernel>  	Vb;
typedef CGAL::Triangulation_data_structure_3<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_3<Kernel, Tds>                 Delaunay3d;
typedef Delaunay3d::Point                          									Point_3;
typedef Delaunay3d::Cell_handle                    									Cell_handle;
typedef Delaunay3d::Vertex_handle    																vertex_handle;
typedef Delaunay3d::Finite_cells_iterator 													cells_iterator;

std::set<Delaunay3d*> ListOfTriangulations;

extern "C"
{
   	void* delaunay_triangulation_3(double* x, double* y,double* z,int nbpts)
	{
		Delaunay3d* dt = new Delaunay3d;
		ListOfTriangulations.insert(dt);
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			for(int i=0; i< nbpts; i++)
			{
				Point_3 P(x[i],y[i],z[i]);
				dt->insert(P);
			}
			dt->is_valid();
		}catch(...)
			{
				sciprint("\terror: the triangulation is not valid with the given points");
				return 0;
			}
		return (void*)dt;
	}
}
extern "C"
{
   	int* dt3_get_connectivity(void* Ptr,int* Nbtetra)
	{

		int* TES = 0;
		Delaunay3d* dt = (Delaunay3d*)Ptr;
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			std::map<vertex_handle,int> listVertex;
			std::vector<int> IndTRI;
			Delaunay3d::Finite_vertices_iterator vit;
			int ind = 1;
			for (vit = dt->finite_vertices_begin(); vit != dt->finite_vertices_end(); ++vit)
			{
				listVertex[vit]= ind;
				ind ++;
			}
			int count = 0;
			for(cells_iterator iter = dt->finite_cells_begin(); iter!= dt->finite_cells_end();++iter)
			{
				vertex_handle vertex0 = (*iter).vertex(0);
				vertex_handle vertex1 = (*iter).vertex(1);
				vertex_handle vertex2 = (*iter).vertex(2);
				vertex_handle vertex3 = (*iter).vertex(3);

				IndTRI.push_back(listVertex[vertex0]);
				IndTRI.push_back(listVertex[vertex1]);
				IndTRI.push_back(listVertex[vertex2]);
				IndTRI.push_back(listVertex[vertex3]);
				count++;
			}

			*Nbtetra = count;

			unsigned int nbInd = IndTRI.size();
			TES = (int*)malloc(nbInd*sizeof(int));
			if(!TES) return 0;
			for(unsigned int j=0; j< nbInd; j++)
			{
				TES[j] = IndTRI[j];
			}
		}catch(...)
			{
				sciprint("\terror: unable to get connectivity of this object");
				if (TES != NULL)
				{
					free(TES);
					TES = NULL;
				}
			}

		return TES;
	}
}
extern "C"
{
	// nbc nember of points.
    void dt3_insert_points(void* Ptr,double* x, double* y,double* z,int nbpts)
	{
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			Delaunay3d* dt = (Delaunay3d*)Ptr;
			for(int i=0; i< nbpts; i++)
			{
				Point_3 P(x[i],y[i],z[i]);
				dt->insert(P);
			}
		}catch(...)
			{
					sciprint("\terror: unable to insert this point(s)");
			}
	}

}
extern "C"
{
    void dt3_remove_points(void* Ptr,double* x, double* y,double* z,int nbpts)
	{
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			Delaunay3d* dt = (Delaunay3d*)Ptr;
			for(int i=0; i< nbpts; i++)
			{
				Point_3 P(x[i],y[i],z[i]);
				vertex_handle vertex = dt->nearest_vertex(P);
				dt->remove(vertex);
			}
		}catch(...)
			{
					sciprint("\terror: unable to remove this point(s)");
			}
	}
}
extern "C"
{
    int dt3_delete(void* Ptr)
	{
		Delaunay3d* dt = (Delaunay3d*)Ptr;
		if(!dt)
		{
			for(std::set<Delaunay3d*>::iterator iter = ListOfTriangulations.begin();iter != ListOfTriangulations.end();iter++)
			{
				delete (*iter);
			}
			ListOfTriangulations.clear();
			return 0;
		}else
		{
			std::set<Delaunay3d*>::iterator iter = ListOfTriangulations.find(dt);
			if(iter != ListOfTriangulations.end())
			{
				ListOfTriangulations.erase(iter);
				delete dt;
			}
		}
		return 0;
	}

}

