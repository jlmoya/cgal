// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


// testing if computed results are correct
x1 = [0.2855364    0.8607515    0.8494102    0.5257061    0.9931210    0.6488563];
y1 = [0.9923191    0.0500420    0.7485507    0.4104059    0.6084526    0.8544211];
z1 = [0.0642647    0.8279083    0.9262344    0.5667211    0.5711639    0.8160110];
t1 = [0.0568928    0.5595937    0.1249340    0.7279222    0.2677766    0.5465335];
S = [x1' y1' z1' t1'];
tes = delaunay_n(S);
tes1=int32([2  3  4  5  6;1  3  4  5  6;1  2  3  4  5]);
tes11=int32([2  5  3  6  3;3  6  4  1  4;4  1  5  2  5]);
bool1=(tes==tes1);
bool2=(tes==tes11);
assert_checktrue(bool1|bool2);

//checking the type of output
type1=type(tes);
assert_checkequal(type1,8.0);
[tes, ptr]=delaunay_n(S);
type2=type(ptr);
assert_checkequal(type2,128.0);

//checking what error will be produced with wrong types of inputs
str="abc";
assert_checkerror("tes=delaunay_n(str)","%s: Wrong type for input argument #%d: A vector expected.",999,"delaunay_n",1);

//checking what error will be produced with wrong number of inputs
assert_checkerror("tes=delaunay_n(S,S)","%s: Wrong number of input argument(s): %d expected.",77,"delaunay_n",1);

//checking the size of output
[rows, cols]=size(tes);
assert_checkequal(cols,5.0);
