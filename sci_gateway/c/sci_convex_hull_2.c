// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt=

#include "gateway_cglab.h"
#include "convex_hull.h"

#include "localization.h"
#include "api_scilab.h"
#include "Scierror.h"

int sci_convex_hull_2(GW_PARAMETERS)
{
    static int l2, l3;
    
    SciErr sciErr;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAdressXY = NULL;
    double *pdVarXY = NULL;
    int iTypeXY = 0; 
    
    
    static int minlhs=0, maxlhs=2, minrhs=1, maxrhs=1;
    int NbInd;
    int* data = 0;
    int m = 1;
    int n = 1;
    int i = 0;
    
    
    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressXY);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressXY, &iTypeXY);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
    
    if ( iTypeXY != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressXY,&m1,&n1,&pdVarXY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if (!(m1 == 2))
    {
        Scierror(999,"%s: Incompatible inputs", "convex_hull_2");
        return 0;
    }
    
    data = convex_hull_2(pdVarXY,n1,&NbInd);
    
    if (!data)
    {
        return 0;
    }
    
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 1, m, n, &NbInd);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
        
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 2, m, NbInd, data);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    LhsVar(1) = Rhs + 1;
    LhsVar(2) = Rhs + 2;
    
    PutLhsVar();
    FREE(data);
    
    
    
    return 0;   /* success: every error path above returns; falling off the
                    end of this int function was undefined behaviour. */
}
