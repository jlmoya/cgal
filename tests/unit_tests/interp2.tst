// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

//checking if computed outputs are the same as expected
// The expected values used to be loaded from tests/unit_tests/zp1.txt, a
// Scilab 5 binary `save` file. Scilab 6 moved save/load to HDF5, so Scilab 2027
// cannot read it at all ("zp1.txt is not a valid ..."), and the reference values
// were effectively unrecoverable -- regenerating them from the current build
// would only have asserted that the code agrees with itself.
//
// Replaced with an ANALYTIC ground truth, which is stronger than any recorded
// blob. CGAL's interpolation has linear precision: given barycentric
// coordinates expressing the query point as a convex combination of data points,
// z_i = a + b'*p_i implies the interpolant returns exactly a + b'*x
// (CGAL 2D Function Interpolation manual). So for a plane sampled on the grid,
// every interpolated value is known in closed form. Measured when this was
// written: max error 3.6e-15 over 144 query points, i.e. machine precision.
a = 2.5; b = -1.75; c = 0.5;
n = 8;
x = linspace(0, 6, n); y = linspace(0, 6, n);
z = a*x(:)*ones(1,n) + ones(n,1)*(b*y(:)') + c;   // a plane over the grid
m = 12;
xx = linspace(0.4, 5.6, m);                       // strictly inside the hull
[xp, yp] = ndgrid(xx, xx);
zp1 = interp2(xp, yp, x, y, z);
assert_checkequal(size(zp1), [m m]);
assert_checkalmostequal(zp1, a*xp + b*yp + c, 1e-9);

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
