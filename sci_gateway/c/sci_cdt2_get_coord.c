// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Constrained_Delaunay.h"

#include "api_scilab.h"
#include "Scierror.h"
#include "localization.h"

#include <string.h>
#include "machine.h"
#include <math.h>
#include <stdio.h>

int sci_cdt2_get_coord(GW_PARAMETERS)
{    
    SciErr sciErr;
    
    int minlhs=0, maxlhs=1, minrhs=1, maxrhs=1;
    
    int m1 = 0, n1 = 0, l1=0;
    int *piAddressPtr = NULL;
    double *pdPtr = NULL;
    int iTypePtr = 0;  
    
    int n = 2;
    double* Coord = 0;
    int nbpts = 0;
    int j = 0;
    void* Ptr;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressPtr);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressPtr, &iTypePtr);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }  
        
    if ( iTypePtr != sci_pointer )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getPointer(pvApiCtx, piAddressPtr , &pdPtr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    Coord = cdt2_get_coord(pdPtr,&nbpts);
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
    free(Coord);

    return 0;

}
