// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Delaunay_mesher.h"

#include "localization.h"
#include "api_scilab.h"
#include "sciprint.h"

int sci_mesh2_refine(GW_PARAMETERS)
{
    
    //int l1, m1, n1,m2, n2, m3, n3,l2,lPtr;
    
    SciErr sciErr;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressMesh2Ptr = NULL;
    void *pdMesh2Ptr = NULL;
    int iTypeMesh2Ptr = 0;
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAddressMesh2ShapeBound = NULL;
    double *pdMesh2ShapeBound = NULL;
    int iTypeMesh2ShapeBound = 0;
    
    static int m3 = 0, n3 = 0, l3=0;
    int *piAddressMesh2UpperBound = NULL;
    double *pdMesh2UpperBound = NULL;
    int iTypeMesh2UpperBound = 0; 
    
    int minlhs=1, maxlhs=1, minrhs=1, maxrhs=3;
    double shapebound =0.,upperbound=0.;
    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    switch(Rhs)
    {
        case 1:
        {
            sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressMesh2Ptr);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            sciErr = getVarType(pvApiCtx, piAddressMesh2Ptr, &iTypeMesh2Ptr);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            
            if ( iTypeMesh2Ptr != sci_pointer )
            {
                Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
                return 0;
            }
            
            sciErr = getPointer(pvApiCtx, piAddressMesh2Ptr , &pdMesh2Ptr);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
        }
        break;
        case 3:
        {
            sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressMesh2Ptr);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            sciErr = getVarType(pvApiCtx, piAddressMesh2Ptr, &iTypeMesh2Ptr);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            
            if ( iTypeMesh2Ptr != sci_pointer )
            {
                Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
                return 0;
            }
            
            sciErr = getPointer(pvApiCtx, piAddressMesh2Ptr , &pdMesh2Ptr);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            
            sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressMesh2ShapeBound);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            sciErr = getVarType(pvApiCtx, piAddressMesh2ShapeBound, &iTypeMesh2ShapeBound);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            if ( iTypeMesh2ShapeBound != sci_matrix )
            {
                Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
                return 0;
            }
            
            sciErr = getMatrixOfDouble(pvApiCtx, piAddressMesh2ShapeBound,&m2,&n2,&pdMesh2ShapeBound);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }   
            
            sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressMesh2UpperBound);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            sciErr = getVarType(pvApiCtx, piAddressMesh2UpperBound, &iTypeMesh2UpperBound);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            if ( iTypeMesh2UpperBound != sci_matrix )
            {
                Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
                return 0;
            }
            
            sciErr = getMatrixOfDouble(pvApiCtx, piAddressMesh2UpperBound,&m3,&n3,&pdMesh2UpperBound);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            if (!(m2 == m3) ||!(n2 == n3) ||!(n2 == 1))
            {
                Scierror(999, "%s: Incompatible inputs.\n","mesh2_refine");
                return 0;
            }
            shapebound = *pdMesh2ShapeBound;
            upperbound = *pdMesh2UpperBound;
        }
        break;
        default:
        {
                sciprint(999,"%s: Incompatible inputs \r\n","mesh2_refine");
                return 0;
        };
    }

    if (!pdMesh2Ptr)
    {
        return 0;
    }
    
    mesh2_refine(pdMesh2Ptr,shapebound,upperbound);

    LhsVar(1) = Rhs - 2;
    PutLhsVar();
    return 0;
    
    
    
    
    
}
