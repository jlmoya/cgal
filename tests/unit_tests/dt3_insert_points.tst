// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//checking what error will be produced with wrong types of inputs
x = rand(1,10);
y = rand(1,10);
z = rand(1,10);
[tri,ptr] = delaunay_3(x,y,z);
new_x = rand(1,10);
new_y = rand(1,10);
new_z = rand(1,10);
dt3_insert_points(ptr,new_x,new_y,new_z);
assert_checkerror("dt3_insert_points(x,x,y,z)","%s: Wrong type for input argument #%d: A pointer expected.",999,"dt3_insert_points",1);
assert_checkerror("dt3_insert_points(ptr,ptr,y,z)","%s: Wrong type for input argument #%d: A vector expected.",999,"dt3_insert_points",2);
assert_checkerror("dt3_insert_points(ptr,x,ptr,z)","%s: Wrong type for input argument #%d: A vector expected.",999,"dt3_insert_points",3);
assert_checkerror("dt3_insert_points(ptr,x,y,ptr)","%s: Wrong type for input argument #%d: A vector expected.",999,"dt3_insert_points",4);

//checking what error will be produced with wrong number of inputs
assert_checkerror("dt3_insert_points(ptr,x)","%s: Wrong number of input argument(s): %d expected.",77,"dt3_insert_points",4);

//testing what error message is produced when inputs have wrong size 
x = rand(1,10);
y = rand(1,10);
z = rand(1,10);
[tri1,ptr] = delaunay_3(x,y,z);
new_x = rand(1,10);
new_y = rand(1,8);
new_z = rand(1,10);  
assert_checkerror("dt3_insert_points(ptr,new_x,new_y,new_z)", "%s: Incompatible inputs", 999, "dt3_insert_points");

//testing if computed outputs are the same as expected
x=[0.2113249    0.7560439    0.0002211    0.3303271    0.6653811];
y=[0.5608486    0.6623569    0.7263507    0.1985144    0.5442573];
z=[0.3076091    0.9329616    0.2146008    0.312642     0.3616361];
xx=[0.2113249    0.7560439];
yy=[0.0002211    0.3303271];
zz=[0.6653811    0.6283918];
[tetra,ptr] = delaunay_3(x,y,z);
dt3_insert_points(ptr,xx,yy,zz);
new_tetra = dt3_get_connectivity(ptr);
// A Delaunay triangulation is unique as a geometry but not in its numbering:
// cell order and vertex order within a cell follow CGAL's insertion strategy, so
// the pinned int32 matrix drifted on upgrade while the result stayed correct.
// Verified when this was rewritten: the current output is 8 tetrahedra over the
// 7 points with ZERO circumsphere violations, the same cell count the old
// expectation had.
//
// Retired expectation:
//   new_tetra1=int32([1 6 3 4;7 1 5 4;5 1 3 4;6 1 7 4;1 3 2 5;1 2 3 6;2 1 7 6;2 1 5 7]);
P = [[x(:);xx(:)] [y(:);yy(:)] [z(:);zz(:)]];
np = size(P,"r");
T = double(new_tetra);
assert_checkequal(size(T,"r"), 8);
assert_checktrue(min(T) >= 1 & max(T) <= np);
assert_checkequal(size(unique(T(:)),"*"), np);      // every point used
nviol = 0;
for k = 1:size(T,"r")
    id = T(k,:);
    q1=P(id(1),:); q2=P(id(2),:); q3=P(id(3),:); q4=P(id(4),:);
    A = 2*[q2-q1; q3-q1; q4-q1];
    bb = [sum(q2.^2)-sum(q1.^2); sum(q3.^2)-sum(q1.^2); sum(q4.^2)-sum(q1.^2)];
    assert_checktrue(abs(det(A)) > 1e-12);          // non-degenerate cell
    cc = (A\bb)'; rr = norm(cc - q1);
    for i = 1:np
        if and(i <> id) then
            if norm(P(i,:) - cc) < rr - 1e-9 then nviol = nviol + 1; end
        end
    end
end
assert_checkequal(nviol, 0);
