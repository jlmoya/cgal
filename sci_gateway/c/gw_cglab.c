#ifdef __cplusplus
extern "C" {
#endif
#include <mex.h> 
#include <sci_gateway.h>
#include <api_scilab.h>
#include <MALLOC.h>
static int direct_gateway(char *fname,void F(void)) { F();return 0;};
extern Gatefunc sci_constrained_delaunay_2;
extern Gatefunc sci_cdt2_get_connectivity;
extern Gatefunc sci_cdt2_get_coord;
extern Gatefunc sci_cdt2_insert_points;
extern Gatefunc sci_cdt2_remove_points;
extern Gatefunc sci_cdt2_insert_constraints;
extern Gatefunc sci_cdt2_remove_constraints;
extern Gatefunc sci_cdt2_delete;
extern Gatefunc sci_convex_hull_2;
extern Gatefunc sci_convex_hull_3;
extern Gatefunc sci_delaunay_triangulation_2;
extern Gatefunc sci_dt2_get_connectivity;
extern Gatefunc sci_dt2_insert_points;
extern Gatefunc sci_dt2_remove_points;
extern Gatefunc sci_dt2_delete;
extern Gatefunc sci_delaunay_triangulation_3;
extern Gatefunc sci_dt3_get_connectivity;
extern Gatefunc sci_dt3_insert_points;
extern Gatefunc sci_dt3_remove_points;
extern Gatefunc sci_dt3_delete;
extern Gatefunc sci_mesh_2;
extern Gatefunc sci_mesh2_set_seeds;
extern Gatefunc sci_mesh2_get_connectivity;
extern Gatefunc sci_mesh2_get_coord;
extern Gatefunc sci_mesh2_refine;
extern Gatefunc sci_mesh2_delete;
extern Gatefunc sci_delaunay_triangulation_n;
extern Gatefunc sci_dtn_get_connectivity;
extern Gatefunc sci_dtn_insert_points;
extern Gatefunc sci_dtn_delete;
extern Gatefunc sci_dtn_delete;
extern Gatefunc sci_interp2;
extern Gatefunc sci_interp3;
extern Gatefunc sci_streamlines_2;
extern Gatefunc sci_surface_mesher;
static GenericTable Tab[]={
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_constrained_delaunay_2,"constrained_delaunay_2"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_cdt2_get_connectivity,"cdt2_get_connectivity"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_cdt2_get_coord,"cdt2_get_coord"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_cdt2_insert_points,"cdt2_insert_points"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_cdt2_remove_points,"cdt2_remove_points"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_cdt2_insert_constraints,"cdt2_insert_constraints"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_cdt2_remove_constraints,"cdt2_remove_constraints"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_cdt2_delete,"cdt2_delete"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_convex_hull_2,"convex_hull_2"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_convex_hull_3,"convex_hull_3"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_delaunay_triangulation_2,"delaunay_2"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dt2_get_connectivity,"dt2_get_connectivity"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dt2_insert_points,"dt2_insert_points"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dt2_remove_points,"dt2_remove_points"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dt2_delete,"dt2_delete"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_delaunay_triangulation_3,"delaunay_3"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dt3_get_connectivity,"dt3_get_connectivity"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dt3_insert_points,"dt3_insert_points"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dt3_remove_points,"dt3_remove_points"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dt3_delete,"dt3_delete"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_mesh_2,"mesh_2"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_mesh2_set_seeds,"mesh2_set_seeds"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_mesh2_get_connectivity,"mesh2_get_connectivity"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_mesh2_get_coord,"mesh2_get_coord"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_mesh2_refine,"mesh2_refine"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_mesh2_delete,"mesh2_delete"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_delaunay_triangulation_n,"delaunay_n"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dtn_get_connectivity,"dtn_get_connectivity"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dtn_insert_points,"dtn_insert_points"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dtn_delete,"dtn_delete"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_dtn_delete,"dtn_delete"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_interp2,"interp2"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_interp3,"interp3"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_streamlines_2,"streamlines_2"},
  {(Myinterfun)sci_gateway_without_putlhsvar,sci_surface_mesher,"surface_mesher"},
};
 
int C2F(gw_cglab)()
{
  Rhs = Max(0, Rhs);
  if (*(Tab[Fin-1].f) != NULL) 
  {
     if(pvApiCtx == NULL)
     {
       pvApiCtx = (StrCtx*)MALLOC(sizeof(StrCtx));
     }
     pvApiCtx->pstName = (char*)Tab[Fin-1].name;
    (*(Tab[Fin-1].f))(Tab[Fin-1].name,Tab[Fin-1].F);
  }
  return 0;
}
#ifdef __cplusplus
}
#endif
