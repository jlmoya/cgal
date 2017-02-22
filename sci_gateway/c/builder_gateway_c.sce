// Copyright (C) 2011 - Edyta Przymus
// Allan CORNET - DIGITEO - 2011
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// ====================================================================


function build_gateway_cpp()
  gateway_c_path = get_absolute_file_path("builder_gateway_c.sce");
  include_flag = ilib_include_flag([gateway_c_path; fullpath(gateway_c_path + "/../../src/cpp")]);

  WITHOUT_AUTO_PUTLHSVAR = %t;

  gw_files = ['sci_cdt2_delete.c', ..
              'sci_cdt2_get_connectivity.c', ..
              'sci_cdt2_get_coord.c', ..
              'sci_cdt2_insert_constraints.c', ..
              'sci_cdt2_insert_points.c', ..
              'sci_cdt2_remove_constraints.c', ..
              'sci_cdt2_remove_points.c', ..
              'sci_constrained_delaunay_2.c', ..
              'sci_convex_hull_2.c', ..
              'sci_convex_hull_3.c', ..
              'sci_delaunay_triangulation_2.c', ..
              'sci_dt2_get_connectivity.c', ..
              'sci_dt2_insert_points.c', ..
              'sci_dt2_remove_points.c', ..
              'sci_dt2_delete.c', ..
              'sci_delaunay_triangulation_3.c', ..
              'sci_dt3_get_connectivity.c', ..
              'sci_dt3_insert_points.c', ..
              'sci_dt3_remove_points.c', ..
              'sci_dt3_delete.c', ..
              'sci_interp2.c', ..
              'sci_interp3.c', ..
              'sci_streamlines_2.c', ..
              'sci_surface_mesher.c',..
              'sci_delaunay_triangulation_n.c', ..
              'sci_dtn_get_connectivity.c', ..
              'sci_dtn_insert_points.c', ..
              'sci_dtn_delete.c', ..
              'sci_mesh_2.c', ..
              'sci_mesh2_get_connectivity.c', ..
              'sci_mesh2_get_coord.c', ..
              'sci_mesh2_refine.c', ..
              'sci_mesh2_set_seeds.c', ..
              'sci_mesh2_delete.c'];

  gw_functions = ['constrained_delaunay_2', 'sci_constrained_delaunay_2'; ..
                  'cdt2_get_connectivity' 'sci_cdt2_get_connectivity'; ..
                  'cdt2_get_coord' 'sci_cdt2_get_coord'; ..
                  'cdt2_insert_points' 'sci_cdt2_insert_points'; ..
                  'cdt2_remove_points' 'sci_cdt2_remove_points'; ..
                  'cdt2_insert_constraints' 'sci_cdt2_insert_constraints'; ..
                  'cdt2_remove_constraints' 'sci_cdt2_remove_constraints'; ..
                  'cdt2_delete' 'sci_cdt2_delete'; ..
                  'convex_hull_2' 'sci_convex_hull_2'; ..
                  'convex_hull_3' 'sci_convex_hull_3'; ..
                  'delaunay_2' 'sci_delaunay_triangulation_2'; ..
                  'dt2_get_connectivity' 'sci_dt2_get_connectivity'; ..
                  'dt2_insert_points' 'sci_dt2_insert_points'; ..
                  'dt2_remove_points' 'sci_dt2_remove_points'; ..
                  'dt2_delete' 'sci_dt2_delete'; ..
                  'delaunay_3' 'sci_delaunay_triangulation_3'; ..
                  'dt3_get_connectivity' 'sci_dt3_get_connectivity'; ..
                  'dt3_insert_points' 'sci_dt3_insert_points'; ..
                  'dt3_remove_points' 'sci_dt3_remove_points'; ..
                  'dt3_delete' 'sci_dt3_delete'; ..
                  'mesh_2' 'sci_mesh_2'; ..
                  'mesh2_set_seeds' 'sci_mesh2_set_seeds'; ..
                  'mesh2_get_connectivity' 'sci_mesh2_get_connectivity'; ..
                  'mesh2_get_coord' 'sci_mesh2_get_coord'; ..
                  'mesh2_refine' 'sci_mesh2_refine'; ..
                  'mesh2_delete' 'sci_mesh2_delete'; ..
                  'delaunay_n' 'sci_delaunay_triangulation_n'; ..
                  'dtn_get_connectivity' 'sci_dtn_get_connectivity'; ..
                  'dtn_insert_points' 'sci_dtn_insert_points'; ..
                  'dtn_delete' 'sci_dtn_delete'; ..
                  'dtn_delete' 'sci_dtn_delete'; ..
                  'interp2' 'sci_interp2'; ..
                  'interp3' 'sci_interp3'; ..
                  'streamlines_2' 'sci_streamlines_2'; ..
                  'surface_mesher' 'sci_surface_mesher'];


tbx_build_gateway("gw_cglab", gw_functions, gw_files , ..
                  gateway_c_path, ..
                  ["../../src/cpp/libcgal_cpp"], "", include_flag);

endfunction

build_gateway_cpp();
clear build_gateway_cpp
