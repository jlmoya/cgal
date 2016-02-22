// ====================================================================
// Copyright
// Edyta PRZYMUS
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);


x = [5 1 6];
y = [2 6 6];
C=[8.    2.     7.    4.;6.    4.5    4.    5.;3.    6.     3.    7.;3.    4.     2.    3.;9.    4.     8.    7.];
[tri,ptr] = constrained_delaunay_2(x,y,C);
coord = cdt2_get_coord(ptr);
X=coord(:,1)';
Y=coord(:,2)';
[nbtri,nb] = size(tri);
tri = [tri tri(:,1)];
scf();
drawlater();
for k = 1:nbtri
plot2d(X(tri(k,:)),Y(tri(k,:)),style = 2);
end
[nbconstraints,nb] = size(C);
for i = 1:nbconstraints
	plot2d([C(i,1) C(i,3)]',[C(i,2) C(i,4)]',style = 3);
	plot2d([C(i,1) C(i,3)]',[C(i,2) C(i,4)]',style = -5);
end
drawnow();

// ====================================================================
