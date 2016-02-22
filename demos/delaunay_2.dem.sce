// ====================================================================
// Copyright
// Edyta PRZYMUS
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);

x =rand(1,10);
y =rand(1,10);
tri = delaunay_2(x,y);
[nbtri,nb] = size(tri);
tri = [tri tri(:,1)];
scf();
drawlater();
for k = 1:nbtri
plot2d(x(tri(k,:)),y(tri(k,:)),style = 2);
end
for k=1:10
vxlabels(k)=sprintf("P%d",k);
end
for k=1:10
xstring(x(k),y(k),vxlabels(k));
end
drawnow();
 
// ====================================================================
