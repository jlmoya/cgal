// Copyright (C) 2011 - Edyta Przymus
// Allan CORNET - DIGITEO - 2011
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// ====================================================================

function builder_gw()
  sci_gateway_dir = get_absolute_file_path('builder_gateway.sce');
  languages = 'c';
  tbx_builder_gateway_lang(languages, sci_gateway_dir);
  tbx_build_gateway_loader(languages, sci_gateway_dir);
  tbx_build_gateway_clean(languages, sci_gateway_dir);
endfunction

builder_gw();
clear builder_gw;
