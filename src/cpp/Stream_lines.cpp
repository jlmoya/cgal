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
// $Id: Stream_lines.cpp 28 2006-10-07 13:44:01Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/Stream_lines.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================


/********************************************************************/
//					Stream_lines_2
//
/********************************************************************/
#include <iostream>
#include <fstream>

#include <CGAL/Cartesian.h>
#include <CGAL/Filtered_kernel.h>
#include <CGAL/Stream_lines_2.h>
#include <CGAL/Runge_kutta_integrator_2.h>
#include <vector>
#include "cgal_exception.h"
#include <math.h>
#include <CGAL/assertions_behaviour.h>
#include <CGAL/Regular_grid_2.h>

extern "C"
{
#include "sciprint.h"
}

typedef double coord_type;
typedef CGAL::Cartesian<coord_type> K1;
typedef CGAL::Filtered_kernel<K1> K;
typedef CGAL::Regular_grid_2<K> Field;
typedef CGAL::Runge_kutta_integrator_2<Field> Runge_kutta_integrator;
typedef CGAL::Stream_lines_2<Field, Runge_kutta_integrator> Stl;
typedef Stl::Point_iterator_2 Point_iterator;
typedef Stl::Stream_line_iterator_2 stl_iterator;
typedef Stl::Point_2 Point;
typedef Stl::Vector_2 Vector;

extern "C"
{

	void* streamlines_2(double* u,double* v,double separating_distance,int u_m,int u_n,int* nb_stls,double integrator)
	{
	
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		Runge_kutta_integrator runge_kutta_integrator(integrator);
		std::vector<Point> points;
		std::vector<Vector> vector_data;
		try
		{
			int x_dim =0,y_dim = 0;
			if(u_n == 1){
				x_dim = (int)sqrt((double)u_m);
				y_dim = x_dim;	
			}else{
				x_dim = u_m;
				y_dim = u_n;			
			}
			
			Field regular_grid_2(x_dim, y_dim, 500, 500);

			for ( int j=0;j<y_dim;j++)
			{
				for ( int i=0;i<x_dim;i++)
				{
					regular_grid_2.set_field(i, j, Vector(u[j*x_dim+i],v[j*x_dim+i]));
				}
				
			}
			double dRat = 1.6;
			Stl*  Stream_lines = new Stl(regular_grid_2, runge_kutta_integrator,separating_distance,dRat);
			
			*nb_stls = (int) std::distance( Stream_lines->begin(),Stream_lines->end());
			
			return (void*)Stream_lines;
				
		}catch(...)
		{sciprint("\terror unable to compute a streamlines of this given data");}	
		
		return 0;

	}
  
}

extern "C"
{
	int* get_nbpts_of_stls(void* Ptr)
	{
		int* nbpts_of_stls = 0;
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			Stl*  Stream_lines = (Stl*)Ptr;
			int nb_stls = (int)std::distance(Stream_lines->begin(),Stream_lines->end());
			nbpts_of_stls = (int*)malloc(nb_stls*sizeof(int));
			if(!nbpts_of_stls)return 0;
			int i = 0;
			for(stl_iterator sit = Stream_lines->begin(); sit != Stream_lines->end(); sit++)
			{
				nbpts_of_stls[i] = (int)std::distance(sit->first,sit->second);
				i++;
			}
		
		}catch(...)
		{
			sciprint("\terror: failure in the function: get_nbpts_of_stls");
			if (nbpts_of_stls != NULL)
			{
				free(nbpts_of_stls);
				nbpts_of_stls = NULL;
			}		
		}	
		
		return nbpts_of_stls;

	}
  
}
extern "C"
{
	double* get_stls(void* Ptr,int nb_pts)
	{
		double* stls = 0;
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		try
		{
			Stl*  Stream_lines = (Stl*)Ptr;
			stls = (double*)malloc(2*nb_pts*sizeof(double));
			if(!stls)return 0;
			int i = 0;
			for(stl_iterator sit = Stream_lines->begin(); sit != Stream_lines->end(); sit++)
			{	
				for(Point_iterator pit = sit->first; pit != sit->second; pit++)
				{
					Point p = *pit;
					stls[2*i] =  p.x();
					stls[2*i+1] = p.y();
					i++;
				}
			}

		}catch(...)
		{
			sciprint("\terror: failure in the function: get_stls");
			if (stls != NULL)
			{
				free(stls);
				stls = NULL;
			}		
		}	
		
		return stls;

	}
  
}

extern "C"
{
    int delete_stls(void* Ptr)
	{
		Stl*  Stream_lines = (Stl*)Ptr;
		if(!Stream_lines) delete Stream_lines;
		return 0;
	}

}

