// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 

//checking if computed outputs are the same as expected
x = [5 1 6];
y = [2 6 6];
new_x = [2 4 5 5];
new_y = [6 7 8 1];
[tri,ptr] = constrained_delaunay_2(x,y,[]);
cdt2_insert_points(ptr,new_x,new_y);
tri2 = cdt2_get_connectivity(ptr);
cdt2_remove_points(ptr,new_x,new_y);
tri3=cdt2_get_connectivity(ptr);
// Removing the four inserted points must restore the original triangulation of
// the three seed points: exactly one triangle, on vertices {1,2,3}. Which
// ROTATION CGAL reports is not part of that contract -- it listed [3 2 1] when
// this test was written and lists [2 1 3] now, the same triangle either way.
// Assert the vertex set, which is the actual guarantee.
assert_checkequal(size(tri3), [1 3]);
assert_checkequal(gsort(double(tri3(:))', "g", "i"), [1 2 3]);

//checking what error will be produced with wrong types of inputs
assert_checkerror("cdt2_remove_points(new_x, new_x, new_y)","%s: Wrong type for input argument #%d: A pointer expected.",999,"cdt2_remove_points",1);
assert_checkerror("cdt2_remove_points(ptr,ptr,new_y)","%s: Wrong type for input argument #%d: A vector expected.",999,"cdt2_remove_points",2);

//checking what error will be produced with wrong number of inputs
assert_checkerror("cdt2_remove_points(ptr)","%s: Wrong number of input argument(s): %d expected.",77,"cdt2_remove_points",3);

//checking if computed outputs are the same as expected
x = [5 1 6];
y = [2 6 6];
new_x = [2 4 5 5];
new_y = [6 7 8 1];
[tri,ptr] = constrained_delaunay_2(x,y,[]);
cdt2_insert_points(ptr,new_x,new_y);
tri2 = cdt2_get_connectivity(ptr);
new_x = [2 4 5 5];
new_y = [6 7 8];
assert_checkerror("cdt2_remove_points(ptr,new_x,new_y)","%s: Incompatible inputs",999,"cdt2_remove_points");
