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
#include "Scierror.h"

int sci_mesh2_get_connectivity(GW_PARAMETERS)
{
    SciErr sciErr;
    
    int lPtr,l3;
    int minlhs=0, maxlhs=1, minrhs=1, maxrhs=1;
    int n = 3;
    
    static int m1 = 0, n1 = 0;
    int *piAdressMesh2Ptr = NULL;
    void *pdVarMesh2Ptr = NULL;
    int iTypeMesh2Ptr = 0;  
    
    int* data = 0;
    int *data2 = 0;
    int NbTri = 0;
    int j = 0;
    int i = 0;
    int k = 0;
    void* Ptr;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressMesh2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressMesh2Ptr, &iTypeMesh2Ptr);
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
    
    sciErr = getPointer(pvApiCtx, piAdressMesh2Ptr , &pdVarMesh2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    data = mesh2_get_connectivity(pdVarMesh2Ptr,&NbTri);
    if (!data)
    {
        return 0;
    }
    
    data2 = (int*)malloc(sizeof(int)* 3 * NbTri);
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
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    free(data);
    free(data2);

    
}
