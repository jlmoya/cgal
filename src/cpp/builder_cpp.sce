// ====================================================================
// Edyta PRZYMUS
// Allan CORNET - DIGITEO - 2011
// Scilab Enterprises - 2015
// ====================================================================
function builder_src_cpp()

  src_cpp_path = get_absolute_file_path('builder_cpp.sce');
  thirdparty_path = fullfile(src_cpp_path, "../../thirdparty");
  cd ..
  os = getos();
  [version, opts] = getversion();
  arch = opts(2);
  thirdparty_path = fullpath(fullfile(thirdparty_path, os, arch));

  CPPFLAGS = ilib_include_flag(src_cpp_path);

  if getos() == "Windows" then
      CPPFLAGS = CPPFLAGS + ilib_include_flag(fullfile(thirdparty_path, "include"));
      lib_path = fullfile(thirdparty_path, "lib");
      disp(lib_path)
      LDFLAGS =  fullfile(lib_path, "libgmp-10.lib");
      if (isDebug())
        LDFLAGS = LDFLAGS + " " + fullfile(lib_path, "libboost_thread-vc143-mt-gd-x64-1_86.lib");
        LDFLAGS =  LDFLAGS + " " + fullfile(lib_path, "CGAL-vc140-mt-gd-4.7.lib");
        LDFLAGS = LDFLAGS + " " + fullfile(lib_path, "CGAL_ImageIO-vc140-mt-gd-4.7.lib");
      else
        LDFLAGS = LDFLAGS + " " + fullfile(lib_path, "libboost_thread-vc143-mt-x64-1_86.lib");
        LDFLAGS =  LDFLAGS + " " + fullfile(lib_path, "CGAL-vc140-mt-4.7.lib");
        LDFLAGS = LDFLAGS + " " + fullfile(lib_path, "CGAL_ImageIO-vc140-mt-4.7.lib");
      end
  else
      CPPFLAGS = CPPFLAGS + ilib_include_flag(fullfile(thirdparty_path, "include"));
      LDFLAGS = "-L" + fullfile(thirdparty_path, "lib");
      LDFLAGS = LDFLAGS + " -lCGAL -lCGAL_ImageIO";
  end

  files_cpp = ['Constrained_Delaunay.cpp', ..
         'convex_hull.cpp', ..
         'Delaunay_2d.cpp', ..
         'Delaunay_3d.cpp', ..
         'Delaunay_mesher.cpp', ..
         'Delaunay_nd.cpp', ..
         'interpolation_functions.cpp', ..
         'Stream_lines.cpp', ..
         'Surface_mesher.cpp'] ;

   tbx_build_src('cgal_cpp', ..
                 files_cpp, ..
                 'cpp', ..
                 src_cpp_path, ..
                 '', ..
                 LDFLAGS, ..
                 CPPFLAGS);
endfunction

builder_src_cpp();
clear builder_src_cpp;
