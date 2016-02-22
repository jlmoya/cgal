// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

C=[1 1 5 1; 5 1 7 3; 7 3 4 4; 4 4 3 6; 3 6 1 5; 1 5 1 1;5 2 5 3; 5 3 3 4; 3 4 2 2; 2 2 5 2];
[coord,tri,ptr]= mesh_2(C);
mesh2_set_seeds(ptr,3.5,2.5);

//checking what error will be produced with wrong number of inputs
assert_checkerror("mesh2_set_seeds(ptr)","%s: Wrong number of input argument(s): %d expected.",77,"mesh2_set_seeds",3);
assert_checkerror("mesh2_set_seeds(ptr,2.5)","%s: Wrong number of input argument(s): %d expected.",77,"mesh2_set_seeds",3);

//checking what error will be produced with wrong types of inputs
assert_checkerror("mesh2_set_seeds(3.5,3.5,2.5)","%s: Wrong type for input argument #%d: A pointer expected.",999,"mesh2_set_seeds",1);
assert_checkerror("mesh2_set_seeds(ptr,ptr,2.5)","%s: Wrong type for input argument #%d: A vector expected.",999,"mesh2_set_seeds",2);
assert_checkerror("mesh2_set_seeds(ptr,3.5,ptr)","%s: Wrong type for input argument #%d: A vector expected.",999,"mesh2_set_seeds",3);

//checking what error will be produced with wrong size of inputs
assert_checkerror("mesh2_set_seeds(ptr,[3.5 3.5],2.5)","%s: Incompatible inputs.",999,"mesh2_set_seeds");

