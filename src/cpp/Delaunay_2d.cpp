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
// $Id: Delaunay_2d.cpp 42 2006-11-30 13:17:58Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/Delaunay_2d.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <map>
#include <vector>
#include <iostream>
#include "cgal_exception.h"
#include <CGAL/assertions_behaviour.h>

extern "C"
{
#include "sciprint.h"
}

/********************************************************************/
//					Delaunay 2D
//
/********************************************************************/
// typedef CGAL::Cartesian<double>  							K;
typedef CGAL::Exact_predicates_inexact_constructions_kernel  	K;
typedef CGAL::Delaunay_triangulation_2<K>  		Delaunay2d;
typedef Delaunay2d::Point   									Point;
typedef Delaunay2d::Vertex_handle 						Vertex_handle;
typedef Delaunay2d::Finite_vertices_iterator  Vertices_iterator;
typedef Delaunay2d::Finite_faces_iterator 		faces_iterator;
typedef Delaunay2d::Edge  	  								Edge;
typedef Delaunay2d::Finite_edges_iterator     Edges_iterator;

//------------------------------------------

std::set<Delaunay2d*> ListDelaunay; // permet de gerer la liste des pointeurs valid dans scilab.

//------------------------------------------
extern "C"
{
    void* delaunay_triangulation_2(double* x, double* y,int nbpts)
    {
        Delaunay2d* dt = new Delaunay2d;
        ListDelaunay.insert(dt);

        CGAL::set_error_handler(_scilab_cgal_error_handler);
        try
        {
            for(int i=0; i< nbpts; i++)
            {
                Point P(x[i],y[i]);
                Vertex_handle vertex = dt->insert(P);
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
    int* dt2_get_connectivity(void* Ptr,int*NbTri)
    {
        int* TRI = 0;
        CGAL::set_error_handler(_scilab_cgal_error_handler);
        try{
            Delaunay2d* dt = (Delaunay2d*)Ptr;

            std::map<Vertex_handle,int> listVertex;
            std::vector<int> IndTRI;
            int ind = 1;
            for (Vertices_iterator vit = dt->finite_vertices_begin(); vit != dt->finite_vertices_end(); ++vit)
            {
                listVertex[vit] = ind;
                ind ++;
            }
            int count = 0;
            for(faces_iterator iter = dt->finite_faces_begin(); iter!= dt->finite_faces_end();++iter)
            {
                Vertex_handle vertex1 = (*iter).vertex(0);
                Vertex_handle vertex2 = (*iter).vertex(1);
                Vertex_handle vertex3 = (*iter).vertex(2);

                IndTRI.push_back(listVertex[vertex1]);
                IndTRI.push_back(listVertex[vertex2]);
                IndTRI.push_back(listVertex[vertex3]);

                count++;
            }
            unsigned int nbtri = IndTRI.size();
            TRI = (int*)malloc(nbtri*sizeof(int));

            for(unsigned int j=0; j< nbtri; j++)
            {
                TRI[j] = IndTRI[j];
            }

            *NbTri = count;
        }
        catch(...)
        {
            sciprint("\terror: unable to get connectivity of this object");
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
    void dt2_insert_points(void* Ptr,double* x, double* y,int nbc)
    {
        Delaunay2d* dt = (Delaunay2d*)Ptr;
        try
        {
            for(int i=0; i< nbc; i++)
            {
                Point P(x[i],y[i]);
                dt->insert(P);
            }
        }catch(...){sciprint("\terror: unable to insert this point(s)");}
    }

}
extern "C"
{
    // nbc nember of points.
    void dt2_remove_points(void* Ptr,double* x, double* y,int nbc)
    {
        Delaunay2d* dt = (Delaunay2d*)Ptr;
        try
        {
            for(int i=0; i< nbc; i++)
            {
                Point P(x[i],y[i]);
                Vertex_handle vertex = dt->nearest_vertex(P);
                dt->remove(vertex);
            }
        }catch(...){sciprint("\terror: unable to remove this point(s)");}
    }

}
extern "C"
{
    int dt2_delete(void* Ptr)
    {
        Delaunay2d* dt = (Delaunay2d*)Ptr;
        try
        {
            if(!dt)
            {
                for(std::set<Delaunay2d*>::iterator iter = ListDelaunay.begin();iter != ListDelaunay.end();iter++)
                {
                    delete (*iter);
                }
                ListDelaunay.clear();
                return 0;
            }else
            {
                std::set<Delaunay2d*>::iterator iter = ListDelaunay.find(dt);
                if(iter != ListDelaunay.end())
                {
                    ListDelaunay.erase(iter);
                    delete dt;
                }
            }
        }catch(...){sciprint("\terror: this pointer(s) is (are) not removed");}
        return 0;
    }

}
