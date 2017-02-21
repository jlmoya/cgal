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
assert_checkerror("dt3_remove_points(x,x,y,z)","%s: Wrong type for input argument #%d: A pointer expected.",999,"dt3_remove_points",1);
assert_checkerror("dt3_remove_points(ptr,ptr,y,z)","%s: Wrong type for input argument #%d: A vector expected.",999,"dt3_remove_points",2);
assert_checkerror("dt3_remove_points(ptr,x,ptr,z)","%s: Wrong type for input argument #%d: A vector expected.",999,"dt3_remove_points",3);
assert_checkerror("dt3_remove_points(ptr,x,y,ptr)","%s: Wrong type for input argument #%d: A vector expected.",999,"dt3_remove_points",4);

//checking what error will be produced with wrong number of inputs
assert_checkerror("dt3_remove_points(ptr,x)","%s: Wrong number of input argument(s): %d expected.",77,"dt3_remove_points",4);

//testing what error message is produced when inputs have wrong size 
x = rand(1,10);
y = rand(1,10);
z = rand(1,10);
[tri1,ptr] = delaunay_3(x,y,z);
new_x = rand(1,10);
new_y = rand(1,8); 
new_z = rand(1,10); 
assert_checkerror("dt3_remove_points(ptr,new_x,new_y,new_z)", "%s: Incompatible inputs", 999, "dt3_remove_points");

//checking if comupted results are the same as expected
x=[0.2113249    0.7560439    0.0002211    0.3303271    0.6653811];
y=[0.5608486    0.6623569    0.7263507    0.1985144    0.5442573];
z=[0.3076091    0.9329616    0.2146008    0.312642     0.3616361];
xx=[0.2113249];
yy=[0.5608486];
zz=[0.3076091];
[tetra,ptr] = delaunay_3(x,y,z);
dt3_remove_points(ptr,xx,yy,zz);
new_tetra = dt3_get_connectivity(ptr);
new_tetra1=int32([4  2  3  1]);
assert_checkequal(new_tetra,new_tetra1);
