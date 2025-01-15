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
// $Id: Surface_mesher.cpp 52 2006-12-01 13:28:16Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/Surface_mesher.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/make_surface_mesh.h>
#include <CGAL/Gray_level_image_3.h>
#include <CGAL/Implicit_surface_3.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include "cgal_exception.h"
#include <CGAL/assertions_behaviour.h>

extern "C"
{
#include "sciprint.h"
#include "sci_malloc.h"
}

struct Kernel : public CGAL::Exact_predicates_inexact_constructions_kernel {};
typedef CGAL::Surface_mesh_vertex_base_3< Kernel> 							Vb;
typedef CGAL::Surface_mesh_cell_base_3< Kernel> 								Cb;
typedef CGAL::Triangulation_data_structure_3< Vb, Cb> 						Tds;
typedef CGAL::Delaunay_triangulation_3< Kernel, Tds> 						Tr;
typedef CGAL::Surface_mesh_complex_2_in_triangulation_3<Tr> 				C2t3;

typedef CGAL::Gray_level_image_3<Kernel::FT, Kernel::Point_3> 				Gray_level_image;
typedef CGAL::Implicit_surface_3<Kernel, Gray_level_image> 					Surface_3;


typedef Tr::Point                          									Point_3;
typedef C2t3::Facet_iterator                    							Facet_iterator;
typedef C2t3::Vertex_handle    												vertex_handle;
typedef C2t3::Vertex_iterator 												Vertex_iterator;

Tr  tr ;   // 3D-Delaunay triangulation

extern "C"
{
   	void* surface_mesher(char * image_file,double iso_value,double* bounding_sphere,double* mesh_criteria)
	{

		CGAL::set_error_handler(_scilab_cgal_error_handler);
		tr.clear();
		C2t3* c2t3= new C2t3(tr);           // 2D-complex in 3D-Delaunay triangulation

		try
		{
			Gray_level_image image(image_file, iso_value);

			Kernel::Point_3 bounding_sphere_center(bounding_sphere[0], bounding_sphere[1], bounding_sphere[2]);
			Kernel::FT bounding_sphere_squared_radius = bounding_sphere[3];
			Kernel::Sphere_3 bounding_sphere(bounding_sphere_center,
											bounding_sphere_squared_radius);
			
			Surface_3 surface(image, bounding_sphere, 1e-2);
			CGAL::Surface_mesh_default_criteria_3<Tr> criteria(mesh_criteria[0],
																mesh_criteria[1],
																mesh_criteria[2]);
			make_surface_mesh(*c2t3, surface, criteria, CGAL::Manifold_tag());
	
		}catch(...)
			{
				sciprint("\terror: the surface defined by this image can not be build.");
				return 0;
			}

		return (void*)c2t3;
	}
}

extern "C"
{
   	int* sm_get_connectivity(void* Ptr,int* Nbtetra)
	{

		int* TES = 0;
		C2t3* dt = (C2t3*)Ptr;
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			std::map<vertex_handle,int> listVertex;
			std::vector<int> IndTRI;
			int ind = 1;
			for (Vertex_iterator vit = dt->vertices_begin(); vit != dt->vertices_end(); ++vit)
			{
				listVertex[vit.base()]= ind;
				ind ++;
			}
			int count = 0;
			for(Facet_iterator iter = dt->facets_begin(); iter!= dt->facets_end();++iter)
			{
				for( int i = 0 ; i < 4 ; i++)
				{
					int index = (*iter).second;
					if(i != index){
						IndTRI.push_back(listVertex[(*iter).first->vertex(i)]);
					}
					
				}
				count++;
			}

			*Nbtetra = dt->number_of_facets();

			unsigned int nbInd = IndTRI.size();
			TES = (int*)MALLOC(nbInd*sizeof(int));
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
					FREE(TES);
					TES = NULL;
				}
			}

		return TES;
	}
}

extern "C"
{
    double* sm_get_coord(void* Ptr,int* nbpts)
	{
		C2t3* tr = (C2t3*)Ptr;
		double* Coord = 0;
		try{
			int nbvertices = std::distance(tr->vertices_begin(),tr->vertices_end()) ;
			*nbpts = nbvertices;
				
			Coord = (double*)MALLOC(3*nbvertices*sizeof(double));
	
			if(!Coord)return 0;
	
			int i =0;
			for (Vertex_iterator vit = tr->vertices_begin(); vit != tr->vertices_end(); ++vit)
			{
				Coord[i] = vit->point().x();
				Coord[i+(*nbpts)] = vit->point().y();
				Coord[i+2*(*nbpts)] = vit->point().z();
				i++;
			}
		}catch(...){
			sciprint("\terror: unable to get coord of this object");
			if (Coord != NULL)
			{
				FREE(Coord);
				Coord = NULL;
			}		
		}

		return Coord;
	}
}

extern "C"
{
    int delete_surface_mesher(void* Ptr)
	{
		C2t3* dt = (C2t3*)Ptr;
		if(!dt) return 0;
		else delete dt;
		
		return 0;
	}

}

