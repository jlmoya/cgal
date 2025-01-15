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
#include "sci_malloc.h"

#include <string.h>
#include <stdio.h>

int sci_dt3_get_connectivity(GW_PARAMETERS)
{
    SciErr sciErr;
    
    int lPtr,l2;
    int minlhs=0, maxlhs=1, minrhs=1, maxrhs=1;
    int n = 4;
    
    static int m1 = 0, n1 = 0;
    int *piAdressDt3Ptr = NULL;
    void *pdVarDt3Ptr = NULL;
    int iTypeDt3Ptr = 0;  
    
    
    int* data = 0;
    int *data2 = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int nbtetra = 0;
    void* Ptr;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressDt3Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressDt3Ptr, &iTypeDt3Ptr);
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
    
    sciErr = getPointer(pvApiCtx, piAdressDt3Ptr , &pdVarDt3Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    data = dt3_get_connectivity(pdVarDt3Ptr,&nbtetra);
    if (!data)
    {
        return 0;
    }
    
    data2 = (int*)MALLOC(sizeof(int)* 4*nbtetra);
    if(data2==NULL)
    {
        Scierror(999,"Can't allocate memory!\n");
        return 0;
    }
    
	for(j=0; j< nbtetra; j++)
	{
		*(data2+j)= data[4*j];
		i = j + nbtetra;
		*(data2+i)= data[1+4*j];
		k = i + nbtetra;
		*(data2+k)= data[2+4*j];
		l = k + nbtetra;
		*(data2+l)= data[3+4*j];
	}
    
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 1, nbtetra, n, data2);
    if (sciErr.iErr)
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
