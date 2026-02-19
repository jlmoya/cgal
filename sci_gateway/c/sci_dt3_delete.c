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
#include "sciprint.h"
#include "Scierror.h"

#include <string.h>
#include <stdio.h>

int dt2_delete(void* Ptr);

int sci_dt3_delete(GW_PARAMETERS)
{
    
    SciErr sciErr;
    int minrhs=0, maxrhs=2;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDt3Ptr = NULL;
    void *pdDt3Ptr = NULL;
    int iTypeDt3Ptr = 0;  
    
    int m2 = 0;
    int n2 = 0;
    
    int* piAddressDt3PtrName = NULL;
    char *pdDt3PtrName = NULL;
    int iTypeDt3PtrName = 0;

    int* piLen		= NULL;
    char* pstData	= NULL;
    
    int i =0;
    int iRet = 0;
    char* job;
    int joblength;
    
    CheckRhs(minrhs,maxrhs);
    
    switch(Rhs)
    {
    case 1:
    {
        sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressDt3Ptr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarType(pvApiCtx, piAddressDt3Ptr, &iTypeDt3Ptr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        
        if ( iTypeDt3Ptr != sci_pointer )
        {
            Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
            return 0;
        }
        
        sciErr = getPointer(pvApiCtx, piAddressDt3Ptr , &pdDt3Ptr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        if (pdDt3Ptr)
        {
            dt2_delete(pdDt3Ptr);
        }
    }
    break;
    case 2:
    {
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
        
        sciErr = getPointer(pvApiCtx, piAddressDt3Ptr , &pdDt3Ptr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDt3PtrName);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarType(pvApiCtx, piAddressDt3PtrName, &iTypeDt3Ptr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        if ( (iTypeDt3Ptr != sci_strings) || (!isScalar(pvApiCtx, piAddressDt3PtrName)) )
        {
            Scierror(999,"%s: Wrong type for input argument #%d: A scalar string expected.\n",fname,2);
            return 0;
        }
        
        iRet = getAllocatedSingleString(pvApiCtx, piAddressDt3PtrName, &pstData);
        if (iRet)
        {
            freeAllocatedSingleString(pstData);
            return iRet;
        }
        
        if (pdDt3Ptr)
        {
            dt2_delete(pdDt3Ptr);
        }
        
        sciprint("clear %s",pstData);
        freeAllocatedSingleString(pstData);
    }
    break;
    default:
    {
        dt2_delete(NULL);
        
    };
    
    }
    return 0;
    
}
