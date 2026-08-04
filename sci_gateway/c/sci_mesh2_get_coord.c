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
#include "Scierror.h"

int sci_mesh2_get_coord(GW_PARAMETERS)
{
    SciErr sciErr;
    
    int lPtr,l2;
    int minlhs=0, maxlhs=1, minrhs=1, maxrhs=1;
    int n = 2;
    
    static int m1 = 0, n1 = 0;
    int *piAdressMesh2Ptr = NULL;
    void *pdVarMesh2Ptr = NULL;
    int iTypeMesh2Ptr = 0;  
    
    double* Coord = 0;
    int nbpts = 0;
    int j = 0;
    void* Ptr;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressMesh2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressMesh2Ptr, &iTypeMesh2Ptr);
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
    
    sciErr = getPointer(pvApiCtx, piAdressMesh2Ptr , &pdVarMesh2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    Coord = mesh2_get_coord(pdVarMesh2Ptr,&nbpts);
    
    if (!Coord)
    {
        return 0;
    }
    
    sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, nbpts, n, Coord);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    FREE(Coord);
    
    return 0;   /* success: every error path above returns; falling off the
                    end of this int function was undefined behaviour. */
}
