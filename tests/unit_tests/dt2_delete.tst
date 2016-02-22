// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

x=rand(1,10);
y=rand(1,10);
[tri,ptr]=delaunay_2(x,y);
//checking what error will be produced with wrong type of inputs
assert_checkerror("dt2_delete(x)","%s: Wrong type for input argument #%d: A pointer expected.",999,"dt2_delete",1);
assert_checkerror("dt2_delete(ptr,x)","%s: Wrong type for input argument #%d: A scalar string expected.",999,"dt2_delete",2);

//checking what error will be produced with wrong number of inputs
assert_checkerror("dt2_delete(ptr,ptr,ptr)","%s: Wrong number of input argument(s): %d to %d expected.",77,"dt2_delete",0,2);

