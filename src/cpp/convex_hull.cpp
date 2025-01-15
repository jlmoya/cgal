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
// $Id: convex_hull.cpp 28 2006-10-07 13:44:01Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/convex_hull.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <CGAL/Convex_hull_traits_3.h>
#include <CGAL/convex_hull_3.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef K::Point_2 Point_2;

extern "C"
{
#include "sci_malloc.h"

	int* convex_hull_2(double* xy,int nb,int* nbind)
	{
	//xy is (2,nb) matrix that represents points coordinates
		std::list<Point_2> input;
		std::vector<Point_2> output;
		int* ind = 0;
		for(int i=0; i< nb; i++)
		{
				Point_2 P(xy[2*i],xy[2*i+1]);
				input.push_back(P);
		}
		CGAL::convex_hull_2(input.begin(),input.end(),std::back_inserter(output));
		std::map<Point_2,int> list;
		int idPoint = 1;
		for(std::list<Point_2>::iterator iter = input.begin(); iter !=input.end() ; ++iter)
		{
			list[(*iter)] = idPoint;
			idPoint++;
		}
		*nbind = output.size();
		ind = (int*)MALLOC((*nbind)*sizeof(int));// faire des tests.
		for(unsigned int j = 0; j < output.size(); j++ )
		{
			ind[j] = list[output[j]];
		}

		return ind;
	}

}

typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Convex_hull_traits_3<K>          Traits;
typedef Traits::Polyhedron_3                   Polyhedron_3;
typedef K::Segment_3                           Segment_3;
typedef K::Point_3                             Point_3;
typedef Polyhedron_3::Facet_iterator			Facet_iterator;
typedef Polyhedron_3::Facet						Facet;
typedef Facet::Halfedge_handle 					Halfedge_handle;
typedef Facet::Halfedge_around_facet_const_circulator Halfedge_circulator;

extern "C"
{
	//--------------------------------------------------------------------------
	//	Inputs:
	// 			nbpts	: 	number of points
	//			x,y,z	: 	vectors of the same length of coordinates points.
	//	Output:
	// 			hull 	:	(Nbsimplex,curdim+1) array of simplices, each row contains one simplex.
	//--------------------------------------------------------------------------

	int* convex_hull_3(double* x,double* y,double* z,int nbpts,int * nbtab,int* nbfacet,int* facetdegree)
	{
		int * hull = 0;

 		std::vector<Point_3> points;
 		std::map<Point_3,int> listpoints;
 		std::vector<int> Indices;

 		int ind = 1;
 		for(int i=0; i< nbpts; i++)
 		{
 			Point_3 P(x[i],y[i],z[i]);
 			points.push_back(P);
			listpoints[P] = ind;
			ind++;
 		}
 		CGAL::Object ch_object;
 		// compute convex hull
 		CGAL::convex_hull_3(points.begin(), points.end(), ch_object);
 		// determine what kind of object it is
 		Segment_3 segment;
 		Polyhedron_3 polyhedron;
 		if ( CGAL::assign(segment, ch_object) )
 			std::cout << "convex hull is a segment " << std::endl;
 		else if ( CGAL::assign (polyhedron, ch_object) )
		{
 			std::cout << "convex hull is a polyhedron " << std::endl;
			for(Facet_iterator iter = polyhedron.facets_begin();iter != polyhedron.facets_end();iter++)
			{
				int nbedge = (*iter).facet_degree ();
				Halfedge_circulator edgecirculator = (*iter).facet_begin();
				for(int i = 0; i < nbedge ;i++)
				{
					Indices.push_back(listpoints[edgecirculator->vertex()->point()]);
					std::cout << listpoints[edgecirculator->vertex()->point()] << "  ";
					edgecirculator ++;
				}

				*facetdegree = (*iter).facet_degree (); // pas terrible. je suppose que toutes les 'facets' ont le meme degree.
			}
			*nbfacet = polyhedron.size_of_facets();
			unsigned int nbInd = Indices.size();
			*nbtab = nbInd;

			hull = (int*)MALLOC(nbInd*sizeof(int));

			for(unsigned int j=0; j< nbInd; j++)
			{
				hull[j] = Indices[j];
			}
 			return hull;
		}
 		else
 			std::cout << "convex hull error!" << std::endl;

		return 0;
	}
}




