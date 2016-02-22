// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

x = rand(1,10);
y = rand(1,10);
[tri,ptr] = delaunay_2(x,y);
new_x = rand(1,10);
new_y = rand(1,10);
dt2_insert_points(ptr,new_x,new_y);
new_tri = dt2_get_connectivity(ptr);

//checking the type of output
type1=type(new_tri);
assert_checkequal(type1, 8.0);

//checking what error will be produced with wrong number of inputs
assert_checkerror("new_tri=dt2_get_connectivity()","%s: Wrong number of input argument(s): %d expected.",77,"dt2_get_connectivity",1);

//checking what error will be produced with wrong types of inputs
assert_checkerror("new_tri=dt2_get_connectivity(ptr,ptr)","%s: Wrong number of input argument(s): %d expected.",77,"dt2_get_connectivity",1);
assert_checkerror("new_tri=dt2_get_connectivity(x)","%s: Wrong type for input argument #%d: A pointer expected.",999,"dt2_get_connectivity",1);
