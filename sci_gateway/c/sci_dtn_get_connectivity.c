// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#define __USE_DEPRECATED_STACK_FUNCTIONS__
#include "stack-c.h"
#include <string.h>
#include "machine.h"
#include <math.h>
#include <stdio.h>
#include "localization.h"
#include "Delaunay_nd.h"
#include "api_scilab.h"



int sci_dtn_get_connectivity(char* fname)
{
    SciErr sciErr;

    int lPtr, l2;
    int minlhs=1, maxlhs=1, minrhs=1, maxrhs=1;
    
    static int m1 = 0, n1 = 0, l1 = 0;
    int *piAdressDtNPtr = NULL;
    void *pdVarDtNPtr = NULL;
    int iTypeDtNPtr = 0;  
    
    int* data = 0;
    void* Ptr = 0;
    int i = 0;
    int j = 0;
    int nbsimplices = 0;
    int curdim = 0;
    int n = 0;
    
    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressDtNPtr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressDtNPtr, &iTypeDtNPtr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    if ( iTypeDtNPtr != sci_pointer )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getPointer(pvApiCtx, piAdressDtNPtr , &pdVarDtNPtr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    data = dtn_get_connectivity(pdVarDtNPtr,&nbsimplices,&curdim);
    if (!data)
    {
        return 0;
    }

    n = curdim +1;
    
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 1, nbsimplices, n, data);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    free(data);

    return 0;
}
