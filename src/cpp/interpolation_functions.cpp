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
// $Id: interpolation_functions.cpp 23 2006-10-03 15:52:40Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/interpolation_functions.cpp $
//
// Author(s)     : Naceur Meskini
//=========================================================================


/********************************************************************/
//					Linear interpolation 
//
/********************************************************************/
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_3.h>

#include <CGAL/natural_neighbor_coordinates_2.h>
#include <CGAL/natural_neighbor_coordinates_3.h>
#include <CGAL/interpolation_functions.h>

#include <CGAL/Interpolation_gradient_fitting_traits_2.h>
#include <CGAL/sibson_gradient_fitting.h>
#include "cgal_exception.h"
#include <CGAL/assertions_behaviour.h>

extern "C"
{
#include "sciprint.h"
}

struct K : CGAL::Exact_predicates_inexact_constructions_kernel {};
typedef CGAL::Delaunay_triangulation_2<K>             			dt_2;
typedef CGAL::Delaunay_triangulation_3<K>             			dt_3;
typedef dt_3::Vertex_handle             						Vertex_handle;

typedef CGAL::Interpolation_gradient_fitting_traits_2<K> 		Traits;
typedef K::FT                                         			Coord_type;
typedef K::Point_2                                    			Point_2;
typedef K::Point_3                                    			Point_3;

extern "C"
{
	double* interp2(double* xi, double* yi,double* x,double* y,double* z,int x_n,int y_n,int xi_m,int xi_n)
	{
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		dt_2 T;
		std::map<Point_2, Coord_type, K::Less_xy_2> 		function_values;
		double* ZI = 0;
		typedef CGAL::Data_access< std::map<Point_2, Coord_type, K::Less_xy_2 > > Value_access;
// 		std::map<Point_2, K::Vector_2 , K::Less_xy_2 >    function_gradients;
// 		typedef CGAL::Data_access< std::map<Point_2, K::Vector_2, K::Less_xy_2 > > Gradient_access;
		try{		
			if (x_n != 0 && y_n != 0)
			{
				for (int i=0 ; i < x_n ; i++)
				{ 
					for (int j = 0 ; j < y_n ; j++)
					{
						K::Point_2 p(x[i],y[j]);
						T.insert(p);
						function_values.insert(std::make_pair(p,z[j*x_n+i]));
					}
				}
			}
			
	//  		sibson_gradient_fitting_nn_2(T,std::inserter(function_gradients,function_gradients.begin()),Value_access(function_values),Traits());	
			int xi_size = xi_m*xi_n;	
			ZI = (double*)malloc(xi_size*sizeof(double));	

			for (int i=0 ; i < xi_size ; i++)
			{

				K::Point_2 p(xi[i],yi[i]);
				std::vector< std::pair< Point_2, Coord_type > > coords;
				Coord_type norm = CGAL::natural_neighbor_coordinates_2(T, p,std::back_inserter(coords)).second ;
				
				Coord_type result  = CGAL::linear_interpolation(coords.begin(), coords.end(), norm,Value_access(function_values));
				ZI[i] = result;
				//TODO take in count the case where the function is C1
//   				std::pair<Coord_type, bool> res =  CGAL::sibson_c1_interpolation(coords.begin(),coords.end(),norm,p, Value_access(function_values), Gradient_access(function_gradients),Traits());
// 				if(res.second){
// 					ZI[i] = res.first;
// 				}else ZI[i] = 0.0;

			}
		}
		catch(...){
			sciprint("\terror: couldn't compute the interpolation for the given data");
			return 0;		
			}
			
		return ZI;
	}

}
/********************************************************************/
//					Linear interpolation 3d
//
/********************************************************************/

extern "C"
{
	double** interp3(double** xi, double** yi,double** zi,double* x,double* y,double* z,double*** v,int x_n,int y_n,int z_n,int xi_m,int xi_n)
	{
		CGAL::set_error_handler(_scilab_cgal_error_handler);
		double** V = 0;
		dt_3 T;
		std::map<Point_3, Coord_type, K::Less_xyz_3> 		function_values;	
		typedef CGAL::Data_access< std::map<Point_3, Coord_type, K::Less_xyz_3 > > Value_access;
		
		try{			
				if (x_n != 0 && y_n != 0)
				{
					for (int i=0 ; i < x_n ; i++)
					{ 
						for (int j = 0 ; j < y_n ; j++)
						{
							for(int k = 0 ; k < z_n ; k++)
							{
								K::Point_3 p(x[i],y[j],z[k]);
								T.insert(p);
								function_values.insert(std::make_pair(p,v[i][j][k]));
							}
						}
					}
				}
				V = (double**)malloc(xi_m*sizeof(double*));
				for (int i = 0 ; i < xi_m ; i++) V[i] = (double*)malloc(xi_n*sizeof(double));
				if(!V)return 0;
			
				for (int i = 0 ; i < xi_m ; i++)
				{
					for (int j = 0 ; j < xi_n ; j++)
					{
						K::Point_3 p(xi[i][j],yi[i][j],zi[i][j]);
						std::vector< std::pair< Vertex_handle, Coord_type > > coords;
						std::vector< std::pair< Point_3, Coord_type > > coords_2;
						Coord_type norm ;
						CGAL::laplace_natural_neighbor_coordinates_3(T, p,std::back_inserter(coords),norm) ;
						
						std::vector< std::pair< Vertex_handle, Coord_type > >::iterator it = coords.begin();				
						for (;it != coords.end(); it++) coords_2.push_back(std::make_pair(it->first->point(),it->second));
				
						Coord_type result  = CGAL::linear_interpolation(coords_2.begin(), coords_2.end(), norm,Value_access(function_values));
						V[i][j] = result;
					}
		
				}
	
			
		}catch(...)
			{
				sciprint("\terror: couldn't compute the interpolation for the given data");
				return 0;
			}
							
		return V;
	}

}
