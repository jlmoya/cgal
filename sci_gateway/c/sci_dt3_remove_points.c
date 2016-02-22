// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#define __USE_DEPRECATED_STACK_FUNCTIONS__
#include "stack-c.h"
#include "localization.h"
#include <string.h>
#include <stdio.h>
#include "api_scilab.h"
#include "Delaunay_3d.h"
int sci_dt3_remove_points(char* fname)
{
    SciErr sciErr;

    int lPtr;
    int minlhs=1, maxlhs=1, minrhs=4, maxrhs=4;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDt3Ptr = NULL;
    void *pdVarDt3Ptr = NULL;
    int iTypeDt3Ptr = 0;
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAddressDt3X = NULL;
    double *pdVarDt3X = NULL;
    int iTypeDt3X = 0;
    
    static int m3 = 0, n3 = 0, l3=0;
    int *piAddressDt3Y = NULL;
    double *pdVarDt3Y = NULL;
    int iTypeDt3Y = 0; 
    
    static int m4 = 0, n4 = 0, l4=0;
    int *piAddressDt3Z = NULL;
    double *pdVarDt3Z = NULL;
    int iTypeDt3Z = 0; 

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
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDt3X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3X, &iTypeDt3X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if ( iTypeDt3X != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3X,&m2,&n2,&pdVarDt3X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressDt3Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3Y, &iTypeDt3Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    } 
    
    if ( iTypeDt3Y != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3Y,&m3,&n3,&pdVarDt3Y);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAddressDt3Z);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3Z, &iTypeDt3Z);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    } 
    
    if ( iTypeDt3Z != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,4);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3Z,&m4,&n4,&pdVarDt3Z);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
        

    if (!(m2 == m3) ||!(n2 == n3)||!(n2 == n4)||!(m3 ==m4))
    {
        Scierror(999,"%s: Incompatible inputs \r\n",fname);
        return 0;
    }
    
    if (!pdVarDt3Ptr)
    {
        return 0;
    }

    dt3_remove_points(pdVarDt3Ptr,pdVarDt3X,pdVarDt3Y,pdVarDt3Z,n2);

    LhsVar(1) = Rhs - 3;
    PutLhsVar();
    return 0;


}
