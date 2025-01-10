// ====================================================================
// Copyright
// Edyta PRZYMUS
// This file is released into the public domain
// ====================================================================
mode(-1);
lines(0);
demos_path = get_absolute_file_path();
load(fullfile(demos_path,"field.sod"),'u','v');
[l,l2] = streamlines_2(u,v,3.5,1.0);
scf();
plot(l(:,1),l(:,2),"marker",".","markersize",1,"linest","none");
