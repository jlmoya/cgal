// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "convex_hull.h"

#include "localization.h"
#include "api_scilab.h"
#include "Scierror.h"

int sci_convex_hull_3(GW_PARAMETERS)
{
    static int l4;
    SciErr sciErr;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAdressX = NULL;
    double *pdVarX = NULL;
    int iTypeX = 0; 
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAdressY = NULL;
    double *pdVarY = NULL;
    int iTypeY = 0; 
    
    static int m3 = 0, n3 = 0, l3=0;
    int *piAdressZ = NULL;
    double *pdVarZ = NULL;
    int iTypeZ = 0; 
    
    static int minlhs=0, maxlhs=1, minrhs=3, maxrhs=3;
    int NbInd   =  0;
    int nbfacet =  0 , facetdegree = 0;
    int* data   =  0;
    int i = 0 , j = 0;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressX);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressX, &iTypeX);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
    
    if ( iTypeX != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressX,&m1,&n1,&pdVarX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAdressY);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressY, &iTypeY);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
    
    if ( iTypeY != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressY,&m2,&n2,&pdVarY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAdressZ);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressZ, &iTypeZ);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
    
    if ( iTypeZ != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressZ,&m3,&n3,&pdVarZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    data = convex_hull_3(pdVarX,pdVarY,pdVarZ,n1,&NbInd,&nbfacet,&facetdegree);
    
    if (!data)
    {
        return 0;
    }
    
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 1, nbfacet, facetdegree, data);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    FREE(data);
}
    
    
