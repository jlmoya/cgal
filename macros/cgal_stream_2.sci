// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

function [c] = cgal_stream_2(u,v,dsep,integrator)
// this function computes the streamlines of a given regular field defined by u
//and v.
// u and v have the same size and can be either matrices or a sample vectors.
// the output of this function is a cell array of matrices defining the
//streamlines.

    [lhs,rhs] = argn();
    if lhs > 1 or rhs > 4 then
        error("input or output not valid");
    end
    if ~exists("integrator") then 
        integrator = 1
    end
    [l,l2]= streamlines_2(u,v,dsep,integrator);
    nb_stls = size(l2,"r");
    nb_pts =[];
    for i = 1:nb_stls-1
        nb_pts(i) = l2(i);
    end 
    c = cell(1,nb_stls-1);
    count = 0;
    for i = 1:nb_stls-1
        c(1,i).entries = l(count+1:count+nb_pts(i),:);
        count = count + nb_pts(i);
    end

endfunction
 
