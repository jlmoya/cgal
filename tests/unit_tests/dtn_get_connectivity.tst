// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 
//checking the type of output
x = [0.5878720    0.4829179    0.2232865    0.8400886    0.1205996];
y = [0.2855364    0.8607515    0.8494102    0.5257061    0.9931210];
z = [0.6488563    0.9923191    0.0500420    0.7485507    0.4104059];
points = [x' y' z'];
[tri,ptr] = delaunay_n(points);
new_x = [0.6084526    0.8544211];
new_y = [0.0642647    0.8279083];
new_z = [0.9262344    0.5667211];
new_points = [new_x' new_y' new_z'];
dtn_insert_points(ptr,new_points);
new_tri = dtn_get_connectivity(ptr);
new_tri1=int32([1  5  3  6;1  2  5  6;1  2  4  6;1  3  5  7;1  2  5  7;1  2  4  7]);
new_tri11=int32([1  5  1  5 ;5 6 3 7;3 1 5 1;6 2 7 2;1 4 1 4;2 6 2 7]);
type1=type(new_tri);
assert_checkequal(type1,8.0);
bool1=(new_tri==new_tri1);
bool2=(new_tri==new_tri11);
assert_checktrue(bool1|bool2);
str="abc";

//checking what error will be produced with wrong types of inputs
assert_checkerror("tes=dtn_get_connectivity(str)","%s: Wrong type for input argument #%d: A pointer expected.",999,"dtn_get_connectivity",1);

//checking what error will be produced with wrong number of inputs
assert_checkerror("tes=dtn_get_connectivity(ptr,ptr)","%s: Wrong number of input argument(s): %d expected.",77,"dtn_get_connectivity",1);
