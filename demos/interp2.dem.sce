// ====================================================================
// Copyright
// Edyta PRZYMUS
// This file is released into the public domain
// ====================================================================

mode(-1);
lines(0);

n = 8;
x = linspace(0,2*%pi,n); y = x;
z = 2*sin(x')*cos(y);
xx = linspace(0,2*%pi, 40);
[xp,yp] = ndgrid(xx,xx);
zp = interp2(xp,yp, x, y, z);

scf()
plot3d(xx, xx, zp, flag=[2 6 4])
[xg,yg] = ndgrid(x,x);
param3d1(xg,yg, list(z,-9*ones(1,n)), flag=[0 0])
xtitle("Bilinear interpolation of 2sin(x)sin(y)")
legends("interpolation points",-9,1)
show_window();

// ====================================================================
