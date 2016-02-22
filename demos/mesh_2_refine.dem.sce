// ====================================================================
// Copyright
// Edyta PRZYMUS
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

C=[1 1 5 1; 5 1 7 3; 7 3 4 4; 4 4 3 6; 3 6 1 5; 1 5 1 1;...
5 2 5 3; 5 3 3 4; 3 4 2 2; 2 2 5 2];

[coord,tri,ptr]= mesh_2(C);
mesh2_set_seeds(ptr,3.5,2.5);

mesh2_refine(ptr,0.1,0.5);

tri = mesh2_get_connectivity(ptr);
coord = mesh2_get_coord(ptr);
[nbtri,nb] = size(tri);
tri = [tri tri(:,1)];
x=coord(:,1)';
y=coord(:,2)';
scf();
drawlater();
for k = 1:nbtri
plot2d(x(tri(k,:)),y(tri(k,:)),style = 2);
end
drawnow();

// ====================================================================
