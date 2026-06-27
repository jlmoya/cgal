// ----------------------------------------------------------------------------
// cglab (CGAL) toolbox — macOS arm64 / Scilab 2027 build.
//
// Prerequisites:  brew install cgal gmp mpfr boost gettext
//
// CGAL 6 is header-only (no libCGAL since CGAL 5), so the geometry kernels are
// compiled straight into src/cpp/libcgal_cpp; only gmp + mpfr are linked, and they
// resolve at runtime through libcgal_cpp's embedded @rpath to /opt/homebrew. The
// standard builder.sce orchestrators (tbx_builder_src / _gateway) are unstable on
// this Scilab build, so we exec the per-component builders directly.
//
//   scilab-cli -nb -f build_macos.sce
//
// If a step reports ierr<>0 with a configure "C compiler cannot create executables",
// just re-run — that failure is intermittent on this toolchain.
// ----------------------------------------------------------------------------
ilib_verbose(1);
setenv("CPATH", "/opt/homebrew/opt/gettext/include");
setenv("LIBRARY_PATH", "/opt/homebrew/opt/gettext/lib:/opt/homebrew/lib/gcc/current/gcc/aarch64-apple-darwin25/16:/opt/homebrew/lib/gcc/current");
setenv("__USE_DEPRECATED_STACK_FUNCTIONS__", "YES");

root = get_absolute_file_path("build_macos.sce");

// [1/4] native CGAL kernels -> src/cpp/libcgal_cpp (template-heavy; slow first build)
ie = execstr("exec(fullfile(root, ""src"", ""cpp"", ""builder_cpp.sce""), -1)", "errcatch");
mprintf("[1/4] src/cpp (libcgal_cpp)     ierr=%d\n", ie);
if ie <> 0 then mprintf("      (configure can flake — re-run this script if so)\n"); end

// [2/4] C gateway -> sci_gateway/c/libgw_cglab (links libcgal_cpp)
ie = execstr("exec(fullfile(root, ""sci_gateway"", ""c"", ""builder_gateway_c.sce""), -1)", "errcatch");
mprintf("[2/4] sci_gateway/c (gw_cglab)  ierr=%d\n", ie);
if ie <> 0 then mprintf("      (configure can flake — re-run this script if so)\n"); end
// tbx_builder_gateway would normally emit this intermediate loader; write it ourselves.
mputl([ "sci_gateway_dir = get_absolute_file_path(""loader_gateway.sce"");" ; ..
        "exec(fullfile(sci_gateway_dir, ""c"", ""loader.sce""), -1);" ; "clear sci_gateway_dir;" ], ..
      fullfile(root, "sci_gateway", "loader_gateway.sce"));

// [3/4] macros
ie = execstr("tbx_build_macros(""cglab"", fullfile(root, ""macros""))", "errcatch");
mprintf("[3/4] macros                    ierr=%d\n", ie);

// [4/4] top-level loader.sce
ie = execstr("tbx_build_loader(""cglab"", root)", "errcatch");
mprintf("[4/4] loader                    ierr=%d\n", ie);

mprintf("\nDone. Load with:  exec(""%setc/cglab.start"")  (or restart Scilab with the toolbox installed)\n", root);
