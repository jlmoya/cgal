// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Delaunay_2d.h"

#include "localization.h"
#include "api_scilab.h"
#include "Scierror.h"

int sci_dt2_remove_points(GW_PARAMETERS)
{
    SciErr sciErr;
    static int minlhs=1, maxlhs=1, minrhs=3, maxrhs=3;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDt2Ptr = NULL;
    void *pdVarDt2Ptr = NULL;
    int iTypeDt2Ptr = 0;  
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAddressDt2X = NULL;
    double *pdDt2X = NULL;
    int iTypeDt2X = 0; 
        
    static int m3 = 0, n3 = 0, l3=0;
    int *piAddressDt2Y = NULL;
    double *pdDt2Y = NULL;
    int iTypeDt2Y = 0; 
    
    static int lPtr;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressDt2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt2Ptr, &iTypeDt2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    if ( iTypeDt2Ptr != sci_pointer )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getPointer(pvApiCtx, piAddressDt2Ptr , &pdVarDt2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressDt2Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
        
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDt2X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt2Y, &iTypeDt2Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeDt2Y != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
        
    sciErr = getVarType(pvApiCtx, piAddressDt2X, &iTypeDt2X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeDt2X != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt2Y,&m3,&n3,&pdDt2Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt2X,&m2,&n2,&pdDt2X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    

    if (!(m2 == m3) ||!(n2 == n3) )
    {
        Scierror(999, "%s: Incompatible inputs", fname);
        return 0;
    }
    
    if (!pdVarDt2Ptr)
    {
        return 0;
    }
    
    dt2_remove_points(pdVarDt2Ptr,pdDt2Y,pdDt2X,n2);
    
    LhsVar(1) = Rhs - 2;
    PutLhsVar();
    return 0;


}
