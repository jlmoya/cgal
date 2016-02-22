// ====================================================================
// Copyright
// Edyta PRZYMUS
// This file is released into the public domain
// ====================================================================
demopath = get_absolute_file_path("cglab.dem.gateway.sce");

subdemolist = ["Delaunay Constrained Triangulation"             ,"constrained_delaunay.dem.sce"; ..
               "Delaunay Triangulation in 2d"                  ,"delaunay_2.dem.sce"     ; ..
               "Delaunay Triangulation in 3d"            ,"delaunay_3.dem.sce" ; ..
               "Bilinear interpolation"               ,"interp2.dem.sce" ; ..
               "Delaunay Mesh in 2d"               ,"mesh2.dem.sce" ; ..
               "Refining a Delaunay Mesh in 2d"               ,"mesh_2_refine.dem.sce" ; ..
               "3D Surface Mesh Generation"                     ,"surface_mesher.dem.sce" ; ..
               "Streamlines of a vector field"               ,"streamlines2.dem.sce" ; ];

subdemolist(:,2) = demopath + subdemolist(:,2);
// ====================================================================
