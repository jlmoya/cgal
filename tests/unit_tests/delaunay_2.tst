// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
str="abc";
x=[ 0.9058    0.1270    0.9134    0.6324   0.0975  0.9058    0.1270    0.9134    0.6324    0.0975];
y=[ 0.9706    0.9572    0.4854    0.8003   0.1419  0.4218    0.9157    0.7922    0.9595    0.6557];
z=[0.5608486    0.6623569    0.7263507    0.1985144    0.5442573    0.2320748    0.2312237    0.2164633    0.8833888    0.6525135];
u=[0.3076091    0.9329616    0.2146008    0.312642    0.3616361];
xx=rand(1,10);
yy=rand(1,10);
tri1=int32([7   2   10;9   2   7 ;8   1   4;8   4   3;4   5   6;4   6   3;4   7   10;4   9   7;1   9   4;1  2  9;4   10   5]);
tri=delaunay_2(x,y);
// testing if computed results are correct
assert_checkequal(tri,tri1);

//testing what error message is produced when wrong number of arguments is given
assert_checkerror ( "tri2=delaunay_2()", "%s: Wrong number of input argument(s): %d expected." , 77,"delaunay_2",2);
assert_checkerror ( "tri2=delaunay_2(x)", "%s: Wrong number of input argument(s): %d expected." , 77,"delaunay_2",2);
assert_checkerror ( "tri2=delaunay_2(x,y,z)", "%s: Wrong number of input argument(s): %d expected." , 77,"delaunay_2",2);

//testing what error message is produced when wrong type of inputs is given
assert_checkerror ( "tri2=delaunay_2(str,x)", "%s: Wrong type for input argument #%d: A vector expected." , 999,"delaunay_2",1);
assert_checkerror ( "tri2=delaunay_2(x,str)", "%s: Wrong type for input argument #%d: A vector expected." , 999,"delaunay_2",2);

//testing size and types of output with random arguments
delaunay_2(xx,yy);
[rows, cols]=size(tri);
assert_checkequal(cols,3.0);
[tri,ptr]=delaunay_2(x,y);
type1=type(tri);
assert_checkequal(type1,8.0);
type2=type(ptr);
assert_checkequal(type2,128.0);

//testing what error message is produced when inputs have wrong size
assert_checkerror ( "tri2=delaunay_2(x,u)", "%s: Incompatible inputs", 999, "delaunay_2");
