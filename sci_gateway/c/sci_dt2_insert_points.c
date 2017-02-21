// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


#include "gateway_cglab.h"
#include "localization.h"
#include "api_scilab.h"
#include "sciprint.h"
#include "Delaunay_2d.h"

int sci_dt2_insert_points(GW_PARAMETERS)
{
    SciErr sciErr;
    static int minlhs=1, maxlhs=1, minrhs=3, maxrhs=3;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDt2Ptr = NULL;
    void *pdVarDt2Ptr = NULL;
    int iTypeDt2Ptr = 0;  
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAddressDt2NewX = NULL;
    double *pdVarDt2NewX = NULL;
    int iTypeDt2NewX = 0; 
        
    static int m3 = 0, n3 = 0, l3=0;
    int *piAddressDt2NewY = NULL;
    double *pdVarDt2NewY = NULL;
    int iTypeDt2NewY = 0; 
    
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
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressDt2NewY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
        
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDt2NewX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt2NewY, &iTypeDt2NewY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeDt2NewY != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
        
    sciErr = getVarType(pvApiCtx, piAddressDt2NewX, &iTypeDt2NewX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeDt2NewX != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt2NewY,&m3,&n3,&pdVarDt2NewY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt2NewX,&m2,&n2,&pdVarDt2NewX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    

    if (!(m2 == m3) ||! (n2 == n3) )
    {
        Scierror(999, "%s: Incompatible inputs.\n",fname);
        return 0;
    }

    if (!pdVarDt2Ptr)
    {
        return 0;
    }
    
    dt2_insert_points(pdVarDt2Ptr,pdVarDt2NewX,pdVarDt2NewY,n2);
    
    LhsVar(1) = Rhs - 2;
    PutLhsVar();
    return 0;


}
