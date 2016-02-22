// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

// this function is proposed by Enrico Segre.
function cgal_streamlines(cell_array)
    clf();
    s = size(cell_array);
    nb_stls = s(2);			
    drawlater()
    for i = 1:nb_stls
        stl = cell_array(1,i);
        stl = cell2mat(stl);
        plot(stl(:,1),stl(:,2),"marker",".","markersize",1,"linest","none");
    end
    drawnow()
endfunction 
