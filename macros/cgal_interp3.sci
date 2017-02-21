// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

function [c]=cgal_interp3(xp,yp,zp,x,y,z,v)
    [lhs,rhs] = argn();
    if (lhs > 1) | (rhs <> 7)  then
        error("input or output not valid");
    end	
    V=[];
    n = 0;
    m = size(v);
    n = m(1)*m(2)*m(3)
    for i =1:n
        V(i) = v('entries')(i)
    end
    c = interp_3(xp,yp,zp,x,y,z,V)
endfunction

