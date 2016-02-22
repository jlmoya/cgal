// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


//checking if computed outputs are the same as expected
x=[46.    120.    207.    286.    366.    453.    543.    544.    473.    387.    300.    206.    136.    250.    346.    408.    527.    443.    306.    326. 196.    139.    264.    55.    58.    46.    118.    513.];
y=[36.    34.    37.    40.    38.    40.    35.    102.    102.    98.    93.    96.    167.    172.    101.    179.    198.    252.    183.    148.    172.   256.    259.    258.    167.    109.    104.    253.];
xy=[x;y];
[nhull,ind] = convex_hull_2(xy);
ind1=int32([1  2  7  8  17  28  23  24  26]);
nhull1=int32(9);
assert_checkequal(nhull,nhull1);
assert_checkequal(ind,ind1);

//checking what error will be produced with wrong number of inputs
assert_checkerror("convex_hull_2()","%s: Wrong number of input argument(s): %d expected.",77,"convex_hull_2",1);
assert_checkerror("convex_hull_2(x,y)","%s: Wrong number of input argument(s): %d expected.",77,"convex_hull_2",1);

//checking what error will be produced with wrong types of inputs
str="abc";
assert_checkerror("convex_hull_2(str)","%s: Wrong type for input argument #%d: A vector expected.",999,"convex_hull_2",1);

//checking what error will be produced with wrong size of inputs
assert_checkerror("convex_hull_2(x)","%s: Incompatible inputs ",999,"convex_hull_2");

