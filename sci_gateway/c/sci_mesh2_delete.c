// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Delaunay_mesher.h"

#include "localization.h"
#include "api_scilab.h"
#include "sciprint.h"
#include "Scierror.h"

int sci_mesh2_delete(GW_PARAMETERS){
    
    SciErr sciErr;
    int minrhs=0, maxrhs=2;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressMesh2Ptr = NULL;
    void *pdMesh2Ptr = NULL;
    int iTypeMesh2Ptr = 0;  
    
    int m2 = 0;
    int n2 = 0;
    
    int* piAddressMesh2PtrName = NULL;
    char *pdMesh2PtrName = NULL;
    int iTypeMesh2PtrName = 0;

    int* piLen      = NULL;
    char* pstData   = NULL;
    
    int i =0;
    int iRet = 0;
    char* job;
    int joblength;
    
    CheckRhs(minrhs,maxrhs);
    
    switch(Rhs)
    {
    case 1:
    {
        sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressMesh2Ptr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarType(pvApiCtx, piAddressMesh2Ptr, &iTypeMesh2Ptr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        
        if ( iTypeMesh2Ptr != sci_pointer )
        {
            Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
            return 0;
        }
        
        sciErr = getPointer(pvApiCtx, piAddressMesh2Ptr , &pdMesh2Ptr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        if (pdMesh2Ptr)
        {
            mesh2_delete(pdMesh2Ptr);
        }
    }
    break;
    case 2:{
        sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressMesh2Ptr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarType(pvApiCtx, piAddressMesh2Ptr, &iTypeMesh2Ptr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        if ( iTypeMesh2Ptr != sci_pointer )
        {
            Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
            return 0;
        }
        
        sciErr = getPointer(pvApiCtx, piAddressMesh2Ptr , &pdMesh2Ptr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressMesh2PtrName);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        sciErr = getVarType(pvApiCtx, piAddressMesh2PtrName, &iTypeMesh2Ptr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
        if ( (iTypeMesh2Ptr != sci_strings) || (!isScalar(pvApiCtx, piAddressMesh2PtrName)) )
        {
            Scierror(999,"%s: Wrong type for input argument #%d: A scalar string expected.\n",fname,2);
            return 0;
        }
        
        iRet = getAllocatedSingleString(pvApiCtx, piAddressMesh2PtrName, &pstData);
        if (iRet)
        {
            freeAllocatedSingleString(pstData);
            return iRet;
        }
        
        if (pdMesh2Ptr)
        {
            mesh2_delete(pdMesh2Ptr);
        }
        
        sciprint("clear %s",pstData);
        freeAllocatedSingleString(pstData);
    }
    break;
    default:
    {
        mesh2_delete(NULL);
        
    };
    }
    return 0;
    
    
    
    
}
