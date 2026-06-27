# cglab — CGAL computational geometry for Scilab

Scilab bindings for [CGAL](https://www.cgal.org) (Computational Geometry Algorithms
Library): Delaunay triangulations (2D / 3D / nD), constrained Delaunay, convex hulls
(2D / 3D), 2D mesh generation, surface meshing, stream lines and natural-neighbour
interpolation.

## macOS (Apple Silicon) / Scilab 2027

This fork builds cglab from source on macOS arm64 against **CGAL 6** and Scilab 2027.

### Prerequisites

```sh
brew install cgal gmp mpfr boost gettext
```

CGAL 6 is **header-only** (there has been no `libCGAL` since CGAL 5), so the geometry
kernels are compiled straight into `src/cpp/libcgal_cpp`. Only **gmp** and **mpfr** are
linked, and they resolve at runtime through libcgal_cpp's embedded `@rpath` to
`/opt/homebrew` — no bundled `thirdparty/Darwin` is required.

### Build

```sh
scilab-cli -nb -f build_macos.sce
```

This compiles `src/cpp/libcgal_cpp` (the CGAL kernels), the C gateway
`sci_gateway/c/libgw_cglab`, the macros, and the loader. The standard
`builder.sce` orchestrators (`tbx_builder_src` / `tbx_builder_gateway`) are unstable on
this Scilab build, so `build_macos.sce` execs the per-component builders directly. If a
step reports a configure error *"C compiler cannot create executables"*, just re-run —
that failure is intermittent on this toolchain.

### Load & use

```scilab
exec('loader.sce');                 // or install the toolbox so it auto-loads

x = [0 1 1 0 0.5];  y = [0 0 1 1 0.5];
tri = delaunay(x, y)                // 2D Delaunay triangulation

h = convex_hull_2([x ; y])          // 2D convex hull (2-by-n matrix of points)

X=[0 1 0 0 0.25]; Y=[0 0 1 0 0.25]; Z=[0 0 0 1 0.25];
t3 = delaunay_3(X, Y, Z)            // 3D Delaunay triangulation
```

### What changed for the macOS port

- `src/cpp/builder_cpp.sce` — added a `Darwin` branch linking Homebrew CGAL/gmp/mpfr
  (header-only CGAL: no `-lCGAL`), with `@rpath` to `/opt/homebrew` for gmp/mpfr.
- `src/cpp/convex_hull.cpp` — `#include <CGAL/Polyhedron_3.h>` (CGAL 6 no longer pulls it
  in transitively via `convex_hull_3.h`).
- `src/cpp/cgal_exception.cpp` — dropped the out-of-line constructor that duplicates the
  inline definition in `cgal_exception.h` (a redefinition error under modern clang).
- `etc/cglab.start` — the `Darwin` branch no longer links a non-existent
  `thirdparty/Darwin/.../libCGAL.dylib`; gmp/mpfr load via libcgal_cpp's rpath.

## License

CeCILL (see `license.txt`). CGAL itself is GPL/LGPL — see <https://www.cgal.org/license.html>.
