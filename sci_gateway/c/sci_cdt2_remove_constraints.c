// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#define __USE_DEPRECATED_STACK_FUNCTIONS__
#include "stack-c.h"
#include "api_scilab.h"
#include "localization.h"
#include <string.h>
#include "machine.h"
#include <math.h>
#include <stdio.h>
#include "Scierror.h"
#include "Constrained_Delaunay.h"


int sci_cdt2_remove_constraints(char* fname)
{
    int lPtr;
    
    SciErr sciErr;
    
    int m1 = 0, n1 = 0, l1=0;
    int *piAddressPtr = NULL;
    void *pdPtr = NULL;
    int iTypePtr = 0;  
    
    int m2 = 0, n2 = 0, l2=0;
    int *piAddressCxy = NULL;
    double *pdCxy = NULL;
    int iTypeCxy = 0;
    
    int minlhs=1, maxlhs=1, minrhs=2, maxrhs=2;

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
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressCxy);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressCxy, &iTypeCxy);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }  
    
    if ( iTypeCxy != sci_matrix)
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressCxy,&m2,&n2,&pdCxy);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    

    if (!(n2 == 4) )
    {
        Scierror(999,"%s: Incompatible inputs\n",fname);
        return 0;
    }

    if (!pdPtr)
    {
        return 0;
    }
    
    cdt2_remove_constraints(pdPtr,pdCxy,m2);

    LhsVar(1) = Rhs - 1;
    PutLhsVar();
    return 0;
}
