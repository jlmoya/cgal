// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Constrained_Delaunay.h"

#include "api_scilab.h"
#include "localization.h"
#include "Scierror.h"

#include <string.h>
#include "machine.h"
#include <math.h>
#include <stdio.h>

int sci_cdt2_get_connectivity(GW_PARAMETERS)
{
    SciErr sciErr;
    
    int minlhs=0, maxlhs=1, minrhs=1, maxrhs=1;
    
    int m1 = 0, n1 = 0, l2=0;
    int *piAddressPtr = NULL;
    void *pdPtr = NULL;
    int iTypePtr = 0;  
    

    int n = 3;
    int* data = 0;
    int *data2 = 0;
    void* Ptr =0;
    int NbTri = 0;
    int j = 0;
    int i = 0;
    int k = 0;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressPtr);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressPtr, &iTypePtr);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }  

    if ( iTypePtr != sci_pointer )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getPointer(pvApiCtx, piAddressPtr , &pdPtr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    data = cdt2_get_connectivity(pdPtr,&NbTri);
    if (!data)
    {
        Scierror(999, "%s: Incompatible inputs", "cdt2_get_connectivity");
        return 0;
    }
    
    data2 = (int*)MALLOC(sizeof(int)*3*NbTri);
    if(data2==NULL)
    {
        Scierror(999,"Can't allocate memory!\n");
        return 0;
    }
    
	for(j=0; j< NbTri; j++)
	{
		*(data2+j)= data[3*j];
		i = j + NbTri;
		*(data2+i)= data[1+3*j];
		k = i + NbTri;
		*(data2+k)= data[2+3*j];
	}
    
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 1, NbTri, n, data2);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    FREE(data);
    FREE(data2);
    return 0;
}
