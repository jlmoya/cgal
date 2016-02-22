// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


function [tri] = delaunay(x, y, z)
    [lhs,rhs]=argn();
    
    if lhs<>1 then
        error(sprintf(gettext("%s: Wrong number of output argument: %d expected.\n"), "delaunay", 1));
    end
    
    if rhs==2 then
        tri=delaunay_2(x,y);
    
    elseif rhs==3 then
        tri=delaunay_3(x,y,z);
    
    elseif rhs==1 then
        [mpts, ndim]=size(x);
        if ndim==2 then
            tri=delaunay_2(x(:,1)',x(:,2)');
        end
        
        if ndim==3 then
            tri=delaunay_3(x(:,1)',x(:,2)',x(:,3)');
        end
        
        if ~(ndim==2 | ndim==3) then
            error(sprintf(gettext("%s: Wrong size for input argument #%d: A 2-by-n or 3-by-m matrix expected.\n"), "delaunay"));
        end
    
    else
        error(sprintf(gettext("%s: Wrong number of input arguments: %d to %d expected.\n"), "delaunay", 1,3));
    end
    
    endfunction
        
