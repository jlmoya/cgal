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
// $Id: Delaunay_nd.cpp 12 2005-12-15 11:10:09Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/Delaunay_nd.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include <CGAL/Cartesian_d.h>
#include <CGAL/Delaunay_d.h>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include "cgal_exception.h"
#include <CGAL/assertions_behaviour.h>
extern"C"
{
#include "sciprint.h"
#include "sci_malloc.h"
}

/********************************************************************/
//					Delaunay nD
//
/********************************************************************/
typedef CGAL::Cartesian_d<double>  		Ker;
typedef CGAL::Delaunay_d<Ker> 			Delaunay_d;
typedef Delaunay_d::Point_d             Point_d;
typedef Delaunay_d::Simplex_iterator 	Simplex_iterator;
typedef Delaunay_d::Vertex_handle 		Vertex_handle;

std::set<Delaunay_d*> ListDelaunay_d;

extern"C"
{
    void* delaunay_triangulation_n(double* pts,int n,int nbpts)
    {
        CGAL::set_error_handler(_scilab_cgal_error_handler);
        Delaunay_d* dt= new  Delaunay_d(n);
        ListDelaunay_d.insert(dt);
        try{
            for(int j=0; j< nbpts; j++)
            {
                double*  coord = new double[n];
                for(int i=0; i< n; i++)
                {
                    coord[i]= pts[i*nbpts+j];
                }
                Point_d P(n,coord,coord+n);
                dt->insert(P);
                delete[] coord;
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
extern"C"
{
    //--------------------------------------------------------------------------
    //	Inputs:
    // 			nbpts	: 	# of points.
    //			n 		:	space dimension.
    //			curdim	: 	current dimension, the affine dimension.
    //			pts 	:	(nbpts,n) array representing nbpts points of n-D space
    //	Output:
    // 			TES 	:	(Nbsimplex,curdim+1) array of simplices, each row contains one simplex.
    //--------------------------------------------------------------------------

    int* dtn_get_connectivity(void* Ptr,int* Nbsimplex,int* curdim)
    {
        int* TES = 0	;
        int count = 0;
        Delaunay_d* dt=  (Delaunay_d*)Ptr;
        CGAL::set_error_handler(_scilab_cgal_error_handler);

        std::map<Vertex_handle,int> listVertex;
        std::vector<int> IndTRI;

        Delaunay_d::Vertex_iterator vit;
        try
        {
            int ind = 1;
            for (vit = dt->vertices_begin(); vit != dt->vertices_end(); ++vit)
            {
                listVertex[vit]= ind;
                ind ++;
            }

            // on recupere la dimemson du l'espace courant.
            int dcur = dt->current_dimension();
            *curdim = dcur;


            for(Simplex_iterator iter = dt->simplices_begin(); iter!= dt->simplices_end();++iter)
            {
                for(int i =0; i <= dcur; i++ )
                {
                    Vertex_handle vertex = dt->vertex_of_simplex(iter,i);
                    IndTRI.push_back(listVertex[vertex]);//printf("%i  ",listVertex[vertex]);
                }
                //
                count++;
            }
        }catch(...)
        {
            sciprint("\terror: unable to get connectivity of this object");
            return 0;
        }
        // on recupere le nombre de simplexes.
        *Nbsimplex = count;

        unsigned int nbInd = IndTRI.size();
        TES = (int*)MALLOC(nbInd*sizeof(int));

        if(!TES) return 0;

        for(unsigned int j=0; j< nbInd; j++)
        {
            TES[j] = IndTRI[j];
        }
        return TES;
    }
}

extern "C"
{
    void dtn_insert_points(void* Ptr,double* pts,int n,int nbpts)
    {

        CGAL::set_error_handler(_scilab_cgal_error_handler);
        try
        {
            Delaunay_d* dt = ( Delaunay_d*)Ptr;
            dt->is_valid();
            for(int j=0; j< nbpts; j++)
            {
                double*  coord = new double[n];
                for(int i=0; i< n; i++)
                {
                    coord[i]= pts[i*nbpts+j];
                }
                Point_d P(n,coord,coord+n);
                dt->insert(P);
                delete[] coord;
            }
        }
        catch(...)
            {
                sciprint("\terror: unable to insert this point(s)");
            }
    }

}
extern "C"
{
    int dtn_delete(void* Ptr)
    {
        Delaunay_d* dt = ( Delaunay_d*)Ptr;
        CGAL::set_error_handler(_scilab_cgal_error_handler);
        try
        {
            if(!dt)
            {
                for(std::set< Delaunay_d*>::iterator iter = ListDelaunay_d.begin();iter != ListDelaunay_d.end();iter++)
                {
                    delete (*iter);
                }
                ListDelaunay_d.clear();
                return 0;
            }else
            {
                std::set< Delaunay_d*>::iterator iter = ListDelaunay_d.find(dt);
                if(iter != ListDelaunay_d.end())
                {
                    ListDelaunay_d.erase(iter);
                    delete dt;
                }
            }
        }
        catch(...)
        {
            sciprint("\terror: this pointer(s) is (are) not removed");
        }
        return 0;
    }
}

