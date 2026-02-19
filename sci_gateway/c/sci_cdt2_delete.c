// Copyright (C) 2011 - Edyta Przymus
//

// This file is part of CG-LAB; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CG-LAB.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Id: intConstrained_Delaunay.c 6 2005-12-05 15:53:46Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/intConstrained_Delaunay.c $
//
// Author(s)     : Naceur Meskini
//                 Edyta Przymus
//=========================================================================

// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Constrained_Delaunay.h"

#include "localization.h"
#include "api_scilab.h"   
#include "sciprint.h"
#include "Scierror.h"

int dt2_delete(void* Ptr);

int sci_cdt2_delete(GW_PARAMETERS)
{
    SciErr sciErr;
    int minrhs=0, maxrhs=2;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDt2Ptr = NULL;
    void *pdDt2Ptr = NULL;
    int iTypeDt2Ptr = 0;  
    
    int m2 = 0;
    int n2 = 0;
    
    int* piAddressDt2PtrName = NULL;
    char *pdDt2PtrName = NULL;
    int iTypeDt2PtrName = 0;

    int* piLen      = NULL;
    char* pstData   = NULL;
    
    int i =0;
    int iRet = 0;
    char* job;
    int joblength;
    
    CheckRhs(minrhs,maxrhs);
    
    switch (Rhs)
    {
        case 1:
        {
            sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressDt2Ptr);
            if(sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            sciErr = getVarType(pvApiCtx, piAddressDt2Ptr, &iTypeDt2Ptr);
            if(sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            
            if ( iTypeDt2Ptr != sci_pointer )
            {
                Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
                return 0;
            }
            
            sciErr = getPointer(pvApiCtx, piAddressDt2Ptr , &pdDt2Ptr);
            if(sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            if (pdDt2Ptr)
            {
                dt2_delete(pdDt2Ptr);
            }
            
        }
        break;
        
        case 2:
        {
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
            
            sciErr = getPointer(pvApiCtx, piAddressDt2Ptr , &pdDt2Ptr);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDt2PtrName);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            sciErr = getVarType(pvApiCtx, piAddressDt2PtrName, &iTypeDt2Ptr);
            if (sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
            
            if ( (iTypeDt2Ptr != sci_strings) || (!isScalar(pvApiCtx, piAddressDt2PtrName)) )
            {
                Scierror(999,"%s: Wrong type for input argument #%d: A scalar string expected.\n",fname,2);
                return 0;
            }
            
            iRet = getAllocatedSingleString(pvApiCtx, piAddressDt2PtrName, &pstData);
            if (iRet)
            {
                freeAllocatedSingleString(pstData);
                return iRet;
            }
            
            if (pdDt2Ptr)
            {
                cdt2_delete(pdDt2Ptr);
            }
            
            sciprint("clear %s",pstData);
            freeAllocatedSingleString(pstData);
        }
        break;
        default:
        {
            cdt2_delete(NULL);
            
        };
    }
    return 0;    
}
