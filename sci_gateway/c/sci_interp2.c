// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "interpolation_functions.h"

#include "localization.h"
#include "api_scilab.h"
#include "Scierror.h"

int sci_interp2(GW_PARAMETERS)
{
    int minlhs=0, maxlhs=1, minrhs=5, maxrhs=5;
    
    SciErr sciErr;
    
    static int m1 = 0, n1 = 0, l1 = 0;
    int *piAdressXi = NULL;
    double *pdVarXi = NULL;
    int iTypeXi = 0;
    
    static int m2 = 0, n2 = 0, l2 = 0;
    int *piAdressYi = NULL;
    double *pdVarYi = NULL;
    int iTypeYi= 0;
    
    static int m3 = 0, n3 = 0, l3 = 0;
    int *piAdressX = NULL;
    double *pdVarX = NULL;
    int iTypeX = 0;
    
    static int m4 = 0, n4 = 0, l4 = 0;
    int *piAdressY = NULL;
    double *pdVarY = NULL;
    int iTypeY = 0;
    
    static int m5 = 0, n5 = 0, l5 = 0;
    int *piAdressZ = NULL;
    double *pdVarZ = NULL;
    int iTypeZ = 0;

    double* ZI = 0;
    int j = 0;
    int i = 0;
    int N = 0;
    
    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressXi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressXi, &iTypeXi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeXi != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressXi,&m1,&n1,&pdVarXi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAdressYi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressYi, &iTypeYi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeYi != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressYi,&m2,&n2,&pdVarYi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAdressX);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressX, &iTypeX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeX != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressX,&m3,&n3,&pdVarX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAdressY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressY, &iTypeY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeY != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,4);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressY,&m4,&n4,&pdVarY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 5, &piAdressZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressZ, &iTypeZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeZ != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,5);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressZ,&m5,&n5,&pdVarZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if (m5 != n4 || n5 != n3 )
    {
        Scierror(999,"%s: size incompatibility between grid points and values\r\n","interp2"); 
        return 0;
    }
    
    if(m1 != m2 || n1 != n2 )
    {
        Scierror(999,"%s: bad inputs for xp, yp \r\n","interp2");
        return 0;
    }
    
    ZI = interp2(pdVarXi,pdVarYi,pdVarX,pdVarY,pdVarZ,n3,n4,m1,n1);
    if (!ZI)
    {
        return 0;
    }
    
    sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, m1, n1, ZI);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    free(ZI);

    return 0;
    
}
