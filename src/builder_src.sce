// ====================================================================
// Edyta PRZYMUS
// Allan CORNET - DIGITEO - 2011
// ====================================================================
function builder_src()
  src_dir = get_absolute_file_path("builder_src.sce");
  tbx_builder_src_lang("cpp", src_dir);
endfunction

builder_src();
clear builder_src;
