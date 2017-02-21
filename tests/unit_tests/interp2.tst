// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//checking if computed outputs are the same as expected
rootpath = cglab_getrootpath();
load(fullfile(rootpath, "tests/unit_tests/zp1.txt"));
n = 8;
x = linspace(0,2*%pi,n); y = x;
z = 2*sin(x')*cos(y);
xx = linspace(0,2*%pi, 40);
[xp,yp] = ndgrid(xx,xx);
zp1 = interp2(xp,yp, x, y, z);
assert_checkequal(zp,zp1);

//checking what error will be produced with wrong number of inputs
assert_checkerror("interp2(xp,yp,x,y)","%s: Wrong number of input argument(s): %d expected.",77,"interp2",5);

//checking what error will be produced with wrong types of inputs
str="abc";
assert_checkerror("zp1=interp2(str,yp, x, y, z)","%s: Wrong type for input argument #%d: A vector expected.",999,"interp2",1);
assert_checkerror("zp1=interp2(xp,str, x, y, z)","%s: Wrong type for input argument #%d: A vector expected.",999,"interp2",2);
assert_checkerror("zp1=interp2(xp,yp, str, y, z)","%s: Wrong type for input argument #%d: A vector expected.",999,"interp2",3);
assert_checkerror("zp1=interp2(xp,yp, x, str, z)","%s: Wrong type for input argument #%d: A vector expected.",999,"interp2",4);
assert_checkerror("zp1=interp2(xp,yp, x, y, str)","%s: Wrong type for input argument #%d: A vector expected.",999,"interp2",5);

//checking what error will be produced with wrong size of inputs
n = 8;
x = linspace(0,2*%pi,n); y = linspace(0,2*%pi,n+2);
z = 2*sin(x')*cos(y);
xx = linspace(0,2*%pi, 40);
[xp,yp] = ndgrid(xx,xx);
assert_checkerror("zp1 = interp2(xp,yp, x, y, z);","%s: size incompatibility between grid points and values",999,"interp2");

n = 8;
x = linspace(0,2*%pi,n); y = x;
z = 2*sin(x')*cos(y);
xx = linspace(0,2*%pi, 40);
yy = linspace(0,2*%pi, 35);
xp = ndgrid(xx,xx);
yp = ndgrid(yy,yy);
assert_checkerror("zp1 = interp2(xp,yp, x, y, z);","%s: bad inputs for xp, yp ",999,"interp2");
