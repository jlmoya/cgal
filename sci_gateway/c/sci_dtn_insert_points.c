// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Delaunay_nd.h"

#include "machine.h"
#include "localization.h"
#include "Scierror.h"
#include "api_scilab.h"

#include <string.h>
#include <math.h>
#include <stdio.h>

int sci_dtn_insert_points(GW_PARAMETERS)
{
    SciErr sciErr;
    
    static int lPtr;
    static int minlhs=0, maxlhs=1, minrhs=2, maxrhs=2;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDtNPtr = NULL;
    void *pdVarDtNPtr = NULL;
    int iTypeDtNPtr = 0;  
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAddressDtNNew = NULL;
    double *pdVarDtNNew = NULL;
    int iTypeDtNNew = 0; 

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressDtNPtr);
    if (sciErr.iErr)
    {
    printError(&sciErr, 0);
    return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDtNPtr, &iTypeDtNPtr);
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
    
    sciErr = getPointer(pvApiCtx, piAddressDtNPtr , &pdVarDtNPtr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDtNNew);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDtNNew, &iTypeDtNNew);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeDtNNew != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDtNNew,&m2,&n2,&pdVarDtNNew);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }


    if (!pdVarDtNPtr)
    {
    return 0;
    }
    
    dtn_insert_points(pdVarDtNPtr,pdVarDtNNew,n2,m2); //albo na odwrót

    LhsVar(1) = Rhs-1;
    PutLhsVar();
    return 0;


}
