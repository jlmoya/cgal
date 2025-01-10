// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Delaunay_3d.h"

#include "api_scilab.h"
#include "localization.h"

#include <string.h>
#include <stdio.h>

int sci_dt3_insert_points(GW_PARAMETERS)
{
    SciErr sciErr;

    int lPtr;
    int minlhs=0, maxlhs=1, minrhs=4, maxrhs=4;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDt3Ptr = NULL;
    void *pdVarDt3Ptr = NULL;
    int iTypeDt3Ptr = 0;
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAddressDt3NewX = NULL;
    double *pdVarDt3NewX = NULL;
    int iTypeDt3NewX = 0;
    
    static int m3 = 0, n3 = 0, l3=0;
    int *piAddressDt3NewY = NULL;
    double *pdVarDt3NewY = NULL;
    int iTypeDt3NewY = 0; 
    
    static int m4 = 0, n4 = 0, l4=0;
    int *piAddressDt3NewZ = NULL;
    double *pdVarDt3NewZ = NULL;
    int iTypeDt3NewZ = 0; 

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressDt3Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3Ptr, &iTypeDt3Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    if ( iTypeDt3Ptr != sci_pointer )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getPointer(pvApiCtx, piAddressDt3Ptr , &pdVarDt3Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDt3NewX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3NewX, &iTypeDt3NewX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if ( iTypeDt3NewX != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3NewX,&m2,&n2,&pdVarDt3NewX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressDt3NewY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3NewY, &iTypeDt3NewY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    } 
    
    if ( iTypeDt3NewY != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3NewY,&m3,&n3,&pdVarDt3NewY);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAddressDt3NewZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3NewZ, &iTypeDt3NewZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    } 
    
    if ( iTypeDt3NewZ != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,4);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3NewZ,&m4,&n4,&pdVarDt3NewZ);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
        

    if (!(m2 == m3) ||!(n2 == n3)||!(n2 == n4)||!(m3 ==m4))
    {
        Scierror(999,"%s: Incompatible inputs", fname);
        return 0;
    }
    
    if (!pdVarDt3Ptr)
    {
        return 0;
    }

    dt3_insert_points(pdVarDt3Ptr,pdVarDt3NewX,pdVarDt3NewY,pdVarDt3NewZ,n2);

    LhsVar(1) = Rhs - 3;
    PutLhsVar();
    return 0;


}
