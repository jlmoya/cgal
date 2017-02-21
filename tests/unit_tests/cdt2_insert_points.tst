// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//checking what error will be produced with wrong types of inputs
x = rand(1,10)*5;
y = rand(1,10)*4;
new_x = rand(1,4)*6;
new_y = rand(1,4)*3;
C=[8.    2.     7.    4.;6.    4.5    4.    5.;3.    6.     3.    7.;3.    4.     2.    3.;9.    4.     8.    7.];
[tri,ptr] = constrained_delaunay_2(x,y,C);
cdt2_insert_points(ptr,new_x,new_y);
assert_checkerror("cdt2_insert_points(new_x, new_x, new_y)","%s: Wrong type for input argument #%d: A pointer expected.",999,"cdt2_insert_points",1);
assert_checkerror("cdt2_insert_points(ptr,ptr,new_y)","%s: Wrong type for input argument #%d: A vector expected.",999,"cdt2_insert_points",2);

//checking what error will be produced with wrong number of inputs
assert_checkerror("cdt2_insert_points(ptr)","%s: Wrong number of input argument(s): %d expected.",77,"cdt2_insert_points",3);

//checking what error will be produced when the inputs has wrong size
x = rand(1,10)*5;
y = rand(1,10)*4;
new_x = rand(1,4)*6;
new_y = rand(1,3)*3;
C=[8.    2.     7.    4.;6.    4.5    4.    5.;3.    6.     3.    7.;3.    4.     2.    3.;9.    4.     8.    7.];
[tri,ptr] = constrained_delaunay_2(x,y,C);
assert_checkerror("cdt2_insert_points(ptr,new_x,new_y)","%s: Incompatible inputs",999,"cdt2_insert_points");

//checking if computed outputs are the same as expected
x=[1.0566243    3.7802193    0.0011057];
y=[2.2433944    2.6494277    2.9054027];
new_x=[1.8456544    5.5977697    1.2876047    1.875852];
new_y=[1.0849083    0.8766800    1.6992746    1.4479416];
[tri,ptr] = constrained_delaunay_2(x,y,C);
cdt2_insert_points(ptr,new_x,new_y);
new_tri=cdt2_get_connectivity(ptr);
new_tri1=int32([10  11  13;2   3   5;7   7   4;17   6  12;11  13   7;16   8  13;16   9   9;1   3  15;3   8   2;2   7  14;15   9   4;6   8   5;6  10  15;15   7  14;5  11  16;2   2   3;6  10  14;7   8  17;3  11  16;11  10   2;8   1  17;13  16  14;5  11   2;12   6  11;1   5  17]);

