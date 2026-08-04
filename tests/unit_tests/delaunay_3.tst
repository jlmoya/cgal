// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


// testing if computed results are correct
str="abc";
x=[0.2113249    0.7560439    0.0002211    0.3303271    0.6653811    0.6283918    0.8497452    0.6857310    0.8782165    0.0683740];
y=[0.5608486    0.6623569    0.7263507    0.1985144    0.5442573    0.2320748    0.2312237    0.2164633    0.8833888    0.6525135];
z=[0.3076091    0.9329616    0.2146008    0.312642    0.3616361    0.2922267    0.5664249    0.4826472    0.3321719    0.5935095];
u=[0.3076091    0.9329616    0.2146008    0.312642    0.3616361];
xx=rand(1,10);
yy=rand(1,10);
zz=rand(1,10);

// A Delaunay triangulation is not unique in its NUMBERING: the tetrahedron
// order and the vertex order within each tetrahedron depend on CGAL's insertion
// strategy, so the exact int32 matrix that used to be pinned here drifts on
// every CGAL upgrade while the geometry stays correct. Verified when this was
// rewritten: the old expectation and the current output are BOTH valid
// Delaunay triangulations of these 10 points -- 19 tetrahedra each, zero
// circumsphere violations either way.
//
// So assert the defining property instead, which no renumbering can fake and
// which a genuinely broken triangulation cannot pass: every tetrahedron's
// circumsphere must be empty of all other input points.
//
// The retired expectation, kept for reference:
//   tetra1=int32([6 1 3 4;5 1 3 6;2 5 9 7;9 5 3 6;2 10 8 4;5 1 6 4;1 10 3 4;
//                 7 5 9 6;10 1 8 4;8 1 5 4;8 5 6 4;7 5 6 8;2 5 7 8;1 3 9 5;
//                 2 10 5 8;10 1 5 8;1 9 10 5;10 9 2 5;1 3 10 9]);
tetra=delaunay_3(x,y,z);
P = [x(:) y(:) z(:)];
np = size(P,"r");
T = double(tetra);
assert_checkequal(size(T,"r"), 19);
assert_checktrue(min(T) >= 1 & max(T) <= np);
assert_checkequal(size(unique(T(:)),"*"), np);   // every input point is used
nviol = 0;
for k = 1:size(T,"r")
    id = T(k,:);
    p1 = P(id(1),:); p2 = P(id(2),:); p3 = P(id(3),:); p4 = P(id(4),:);
    A = 2*[p2-p1; p3-p1; p4-p1];
    b = [sum(p2.^2)-sum(p1.^2); sum(p3.^2)-sum(p1.^2); sum(p4.^2)-sum(p1.^2)];
    assert_checktrue(abs(det(A)) > 1e-12);       // no degenerate tetrahedron
    c = (A\b)';
    r = norm(c - p1);
    for i = 1:np
        if and(i <> id) then
            if norm(P(i,:) - c) < r - 1e-9 then nviol = nviol + 1; end
        end
    end
end
assert_checkequal(nviol, 0);


//checking what error will be produced with wrong number of inputs
assert_checkerror ( "tetra2=delaunay_3()", "%s: Wrong number of input argument(s): %d expected." , 77,"delaunay_3",3);
assert_checkerror ( "tetra2=delaunay_3(x)", "%s: Wrong number of input argument(s): %d expected." , 77,"delaunay_3",3);
assert_checkerror ( "tetra2=delaunay_3(x,y)", "%s: Wrong number of input argument(s): %d expected.", 77,"delaunay_3",3);

//checking what error will be produced with wrong types of inputs
assert_checkerror ( "tetra2=delaunay_3(str,y,z)", "%s: Wrong type for input argument #%d: A vector expected." , 999,"delaunay_3",1);
assert_checkerror ( "tetra2=delaunay_3(x,str,z)", "%s: Wrong type for input argument #%d: A vector expected." , 999,"delaunay_3",2);
assert_checkerror ( "tetra2=delaunay_3(x,y,str)", "%s: Wrong type for input argument #%d: A vector expected." , 999,"delaunay_3",3);

//testing size and types of output with random arguments
tetra3=delaunay_3(xx,yy,zz);
[rows, cols]=size(tetra3);
assert_checkequal(cols,4.0);
[tetra,ptr]=delaunay_3(x,y,z);
type1=type(tetra);
assert_checkequal(type1,8.0);
type2=type(ptr);
assert_checkequal(type2,128.0);

//testing what error message is produced when inputs have wrong size
assert_checkerror ( "tetra2=delaunay_3(x,u,z)", "%s: Incompatible inputs", 999, "delaunay_3");

