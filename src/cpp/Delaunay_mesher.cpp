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
// $Id: Delaunay_mesher.cpp 6 2005-12-05 15:53:46Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/Delaunay_mesher.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_mesher_2.h>
#include <CGAL/Delaunay_mesh_face_base_2.h>
#include <CGAL/Delaunay_mesh_size_criteria_2.h>
#include "cgal_exception.h"
#include <iostream>
#include <CGAL/assertions_behaviour.h>

extern "C"
{
#include "sciprint.h"
}

template <class CDT,class Criteria>
class Mesh2d : public CGAL::Delaunay_mesher_2<CDT,Criteria>
{
	public:
 		CDT cdt;
 		Mesh2d():CGAL::Delaunay_mesher_2<CDT,Criteria>(cdt){};
};

struct K : public CGAL::Exact_predicates_inexact_constructions_kernel {};
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Delaunay_mesh_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, Tds> CDT;
typedef CGAL::Delaunay_mesh_size_criteria_2<CDT> Criteria;
//typedef CGAL::Delaunay_mesher_2<CDT, Criteria> Mesher;
typedef Mesh2d<CDT, Criteria> Mesher;

typedef CDT::Vertex_handle Vertex_handle;
typedef CDT::Vertex_iterator Vertices_iterator;
typedef CDT::Face_iterator faces_iterator;
typedef CDT::Point Point;

std::set<Mesher*> ListOfMesher;

extern "C"
{
	void* mesh_2(double* Pslg,int nbconstraint)
	{
		Mesher* mesher= new Mesher;
		for(int i=0; i< nbconstraint; i++)
		{
			Point P1(Pslg[i],Pslg[i+nbconstraint]);
			Point P2(Pslg[i+2*nbconstraint],Pslg[i+3*nbconstraint]);
			mesher->cdt.insert_constraint(P1,P2);
		}
		mesher->refine_mesh();

		return (void*)mesher;
	}
}
extern "C"
{
    double* mesh2_get_coord(void* Ptr,int* nbpts)
	{
		Mesher* mesher = (Mesher*)Ptr;
 		int nbvertices = mesher->cdt.number_of_vertices();
		*nbpts = nbvertices;

		double* Coord = 0;
		Coord = (double*)malloc(2*nbvertices*sizeof(double));

		if(!Coord)return 0;

		int i =0;
		for (Vertices_iterator vit = mesher->cdt.finite_vertices_begin(); vit != mesher->cdt.finite_vertices_end(); ++vit)
		{
			Coord[i] = vit->point().x();
			Coord[i+(*nbpts)] = vit->point().y();
			i++;
		}

		return Coord;
	}
}
extern "C"
{
    int* mesh2_get_connectivity(void* Ptr,int*NbTri)
	{
		int* TRI = 0;
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try{
			Mesher* mesher = (Mesher*)Ptr;
			std::map<Vertex_handle,int> listVertex;
			std::vector<int> IndTRI;
			int ind = 1;
			for (Vertices_iterator vit = mesher->cdt.finite_vertices_begin(); vit != mesher->cdt.finite_vertices_end(); ++vit)
			{
				listVertex[vit] = ind;
				ind ++;
			}
			int count = 0;
			for(faces_iterator iter = mesher->cdt.finite_faces_begin(); iter!= mesher->cdt.finite_faces_end();++iter)
			{
				if(iter->is_marked())
				{
					Vertex_handle vertex1 = (*iter).vertex(0);
					Vertex_handle vertex2 = (*iter).vertex(1);
					Vertex_handle vertex3 = (*iter).vertex(2);

					IndTRI.push_back(listVertex[vertex1]);
					IndTRI.push_back(listVertex[vertex2]);
					IndTRI.push_back(listVertex[vertex3]);
					count++;
				}
			}

			unsigned int nbtri = IndTRI.size();
			TRI = (int*)malloc(nbtri*sizeof(int));
			if(!TRI) return 0;

			for(unsigned int j=0; j< nbtri; j++)
			{
				TRI[j] = IndTRI[j];
			}
			*NbTri = count;
		}catch(...)
		{
			sciprint("\terror: unable to get connectivity");
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
    void mesh2_refine(void* Ptr,double shapebound,double upperbound)
	{
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try{
			Mesher* mesher = (Mesher*)Ptr;
			mesher->set_criteria(Criteria(shapebound,upperbound));
			mesher->refine_mesh();
		}catch(...){};
	}
}

extern "C"
{
    void mesh2_set_seeds(void* Ptr,double* x,double* y,int nbseeds)
	{

		Mesher* mesher = (Mesher*)Ptr;
		std::vector<Point> SeedsList;
		for(int i=0; i< nbseeds; i++)
		{
			Point P(x[i],y[i]);
			SeedsList.push_back(P);
		}
		mesher->set_seeds(SeedsList.begin(),SeedsList.end(),false,true);
	}
}
extern "C"
{
    int mesh2_delete(void* Ptr)
	{
		Mesher* mesher = (Mesher*)Ptr;
		if(!mesher)
		{
			for(std::set<Mesher*>::iterator iter = ListOfMesher.begin();iter != ListOfMesher.end();iter++)
			{
				delete (*iter);
			}
			ListOfMesher.clear();
			return 0;
		}else
		{
			std::set<Mesher*>::iterator iter = ListOfMesher.find(mesher);
			if(iter != ListOfMesher.end())
			{
				ListOfMesher.erase(iter);
				delete mesher;
			}
		}
		return 0;
	}

}

