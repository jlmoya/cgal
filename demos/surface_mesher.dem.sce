// ====================================================================
// Copyright
// Edyta PRZYMUS
// This file is released into the public domain
// ====================================================================

mode(-1);
lines(0);

p = cglab_getrootpath();
image_1 = p+"/demos/skull_2.9.inr";
bounded_sphere = [122.0 102.0 117.0 200.0*200.0*2.0];
mesh_criteria = [30 5 5];
[tri,coord] = surface_mesher(image_1,2.9,bounded_sphere,mesh_criteria);

xx = matrix(coord(tri,1),-1,3)';
yy = matrix(coord(tri,2),-1,3)';
zz = matrix(coord(tri,3),-1,3)';

h = plot3d(xx,yy,zz)
h.color_mode=0
a=gca();
a.isoview="on";
a.rotation_angles=[98,-53];
// ====================================================================
