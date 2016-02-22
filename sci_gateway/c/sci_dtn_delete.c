// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#define __USE_DEPRECATED_STACK_FUNCTIONS__
#include "stack-c.h"
#include <string.h>
#include "machine.h"
#include <math.h>
#include <stdio.h>
#include "localization.h"
#include "api_scilab.h"
#include "Delaunay_nd.h"


int sci_dtn_delete(char* fname)
{
    
    SciErr sciErr;
    int minrhs=0, maxrhs=2;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDtNPtr = NULL;
    void *pdDtNPtr = NULL;
    int iTypeDtNPtr = 0;  
    
    int m2 = 0;
    int n2 = 0;
    
    int* piAddressDtNPtrName = NULL;
    char *pdDtNPtrName = NULL;
    int iTypeDtNPtrName = 0;

    int* piLen		= NULL;
    char* pstData	= NULL;
    
    int i =0;
    int iRet = 0;
    char* job;
    int joblength;
    
    CheckRhs(minrhs,maxrhs);
    
    switch (Rhs)
    {
    case 1:
    {
        sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressDtNPtr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarType(pvApiCtx, piAddressDtNPtr, &iTypeDtNPtr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        
        if ( iTypeDtNPtr != sci_pointer )
        {
            Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
            return 0;
        }
        
        sciErr = getPointer(pvApiCtx, piAddressDtNPtr , &pdDtNPtr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        if (pdDtNPtr)
        {
            dt2_delete(pdDtNPtr);
        }
    }
    break;
    case 2:
    {
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
        
        sciErr = getPointer(pvApiCtx, piAddressDtNPtr , &pdDtNPtr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDtNPtrName);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarType(pvApiCtx, piAddressDtNPtrName, &iTypeDtNPtr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        if ( (iTypeDtNPtr != sci_strings) || (!isScalar(pvApiCtx, piAddressDtNPtrName)) )
        {
            Scierror(999,"%s: Wrong type for input argument #%d: A scalar string expected.\n",fname,2);
            return 0;
        }
        
        iRet = getAllocatedSingleString(pvApiCtx, piAddressDtNPtrName, &pstData);
        if (iRet)
        {
            freeAllocatedSingleString(pstData);
            return iRet;
        }
        
        if (pdDtNPtr)
        {
            dt2_delete(pdDtNPtr);
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
