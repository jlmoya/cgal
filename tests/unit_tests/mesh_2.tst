// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


//checking if computed outputs are the same as expected
C=[1 1 5 1; 5 1 7 3; 7 3 4 4; 4 4 3 6; 3 6 1 5; 1 5 1 1;5 2 5 3; 5 3 3 4; 3 4 2 2; 2 2 5 2];
[coord,tri]= mesh_2(C);
coord1=[1.       1.;5.       1.;7.       3.;4.       4.;3.       6.;1.       5.;5.       2.;5.       3.;3.       4.;2.       2.;6.       2.;3.       1.;5.5      3.5;3.5      5;1.       3.;4.       3.5;5.5      1.5;3.5      2.;2.   1.;4.75     3.75;1.       2.;3.5      3.75;4.5      3.25;2.5      3.;3.375    2.875];
coord2=[1.       1.;5.       1.;7.       3.;4.       4.;3.       6.;1.       5.;5.       2.;5.       3.;3.       4.;2.       2.;6.       2.;3.       1.;3.5      5;5.5      3.5;1.       3.;4.       3.5;5.5      1.5;3.5      2.;2.   1.;4.75     3.75;1.       2.;3.5      3.75;4.5      3.25;2.5      3.;3.375    2.875];
tri1=int32([5 6 9;2   7  18;4  16  20;1  10  21;18  23  25;8  20  23;10  15  21;20  16  23;12   2  18;8   7  11;10  12  18;5   9  13;9   4  13;8  11  14;11   3  14;9  15  24;9   6  15;8  14  20;24  18  25;11   7  17;7   2  17;10  18  24;15  10  24;12  10  19;10   1  19;16   4  22;4   9  22;18   7  23;7   8  23;22  24  25;22   9  24;23  16  25;16  22  25]);
tri2=int32([5   6   9;2   7  18;9  15  24 ;4  16  20;9   6  15;9   4  14;18  23  25;5   9  14;1  10  21;20  16  23;12   2  18;8   7  11;10  12  18;8  11  13;11   3  13;8  20  23;10  15  21;8  13  20;24  18  25;11   7  17; 7   2  17;10  18  24;15  10  24;12  10  19;10   1  19;16   4  22; 4   9  22;18   7  23;7   8  23;22  24  25;22   9  24;23  16  25;16  22  25]);
boolean1=(tri==tri1);
boolean2=(tri==tri2);
boolean3=(coord==coord1);
boolean4=(coord==coord2);
assert_checktrue(boolean1|boolean2);
assert_checktrue(boolean3 |boolean4);

//checking what error will be produced with wrong number of inputs
assert_checkerror("[coord, tri]=mesh_2(C,C)","%s: Wrong number of input argument(s): %d expected.",77,"mesh_2",1);

//checking what error will be produced with wrong types of inputs
str="abc";
assert_checkerror("[coord, tri]=mesh_2(str)","%s: Wrong type for input argument #%d: A vector expected.",999,"mesh_2",1);

//checking what error will be produced when the input has wrong size
C=[1 1 5; 5 1 7; 7 3 4; 4 4 3; 3 6 1; 1 5 1;...
5 2 5; 5 3 3; 3 4 2; 2 2 5];
assert_checkerror("[coord,tri]=mesh_2(C)","%s: Incompatible inputs ",999,"mesh_2");
