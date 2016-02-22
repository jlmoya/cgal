// ====================================================================
// Copyright
// Edyta PRZYMUS
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

x =rand(1,10);
y =rand(1,10);
z =rand(1,10);
tetra = delaunay_3(x,y,z);
[nbtetra,nb] = size(tetra);
tri1=[tetra(:,1) tetra(:,2) tetra(:,3)];
tri2=[tetra(:,2) tetra(:,3) tetra(:,4)];
tri3=[tetra(:,1) tetra(:,3) tetra(:,4)];
tri4=[tetra(:,1) tetra(:,2) tetra(:,4)];
tri1 = [tri1 tri1(:,1)];
tri2 = [tri2 tri2(:,1)];
tri3 = [tri3 tri3(:,1)];
tri4 = [tri4 tri4(:,1)];
scf();
drawlater();
for k = 1:nbtetra
param3d(x(tri1(k,:)),y(tri1(k,:)),z(tri1(k,:)));
param3d(x(tri2(k,:)),y(tri2(k,:)),z(tri2(k,:)));
param3d(x(tri3(k,:)),y(tri3(k,:)),z(tri3(k,:)));
param3d(x(tri4(k,:)),y(tri4(k,:)),z(tri4(k,:)));
end
drawnow();
 
// ====================================================================
