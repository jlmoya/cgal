// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//checking if computed outputs are the same as expected
C=[1 1 5 1; 5 1 7 3; 7 3 4 4; 4 4 3 6; 3 6 1 5; 1 5 1 1;5 2 5 3; 5 3 3 4; 3 4 2 2; 2 2 5 2];
[coord,tri,ptr]= mesh_2(C);
mesh2_set_seeds(ptr,3.5,2.5);
tri = mesh2_get_connectivity(ptr);
tri1=int32([5   6   9;2   7  18;9  15  24;4  16  20;9  6   15;9  4  14;5  9   14;1  10   21;20  16  23;12   2  18;8   7  11;10  12  18;8   11  13;11  3  13;8  20  23;10  15  21;8  13   20;11  7  17;7   2  17;15  10   24;12  10  19;10   1   19;16   4   22;4  9  22]);
tri3=int32([5   6   9;2   7  18;4  16  20 ;1  10  21;8  20  23; 10  15  21;20  16  23;12   2  18;8   7  11;10  12  18;5   9  13;9 4 13;8 11 14;11   3  14;9 15 24;9   6  15;8  14  20;11   7  17;7   2  17;15  10  24;12  10  19;10   1  19;16   4  22;4   9  22]);
test1=(tri==tri1);
test2=(tri==tri3);
assert_checktrue(test1|test2);

//checking what error will be produced with wrong number of inputs
assert_checkerror("tri=mesh2_get_connectivity(ptr,ptr)","%s: Wrong number of input argument(s): %d expected.",77,"mesh2_get_connectivity",1);

//checking what error will be produced with wrong types of inputs
assert_checkerror("tri=mesh2_get_connectivity(C)","%s: Wrong type for input argument #%d: A pointer expected.",999,"mesh2_get_connectivity",1);

