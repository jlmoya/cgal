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


int sci_cdt2_remove_points(char* fname)
{
    SciErr sciErr;
    
    int m1 = 0, n1 = 0, l1=0;
    int *piAddressPtr = NULL;
    double *pdPtr = NULL;
    int iTypePtr = 0;  
    
    int m2 = 0, n2 = 0, l2=0;
    int *piAddressX = NULL;
    double *pdX = NULL;
    int iTypeX = 0;  
    
    int m3 = 0, n3 = 0, l3=0;
    int *piAddressY = NULL;
    double *pdY = NULL;
    int iTypeY = 0;  
    
    
    int minlhs=1, maxlhs=1, minrhs=3, maxrhs=3;

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
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressX, &iTypeX);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }  
    
    if ( iTypeX != sci_matrix)
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressX,&m2,&n2,&pdX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressY, &iTypeY);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }  
    
    if ( iTypeY != sci_matrix)
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressY,&m3,&n3,&pdY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if (!(m2 == m3) ||!(n2 == n3) )
    {
        Scierror(999,"%s: Incompatible inputs \r\n",fname);
        return 0;
    }

    if (!pdPtr)
    {
        return 0;
    }
    
    cdt2_remove_points(pdPtr,pdX,pdY,n2);

    LhsVar(1) = Rhs - 2;
    PutLhsVar();
    return 0;


}
