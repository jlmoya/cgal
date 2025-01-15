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
#include "sci_malloc.h"

#include <string.h>
#include "machine.h"
#include <math.h>
#include <stdio.h>

int sci_constrained_delaunay_2(GW_PARAMETERS)
{
    SciErr sciErr;
    
    int minlhs=0, maxlhs=2, minrhs=3, maxrhs=3;
    
    int m1 = 0, n1 = 0, l1=0;
    int *piAddressX = NULL;
    double *pdX = NULL;
    int iTypeX = 0;  
    
    int m2 = 0, n2 = 0, l2=0;
    int *piAddressY = NULL;
    double *pdY = NULL;
    int iTypeY = 0; 
    
    
    int m3 = 0, n3 = 0, l3=0;
    int *piAddressCxy = NULL;
    double *pdCxy = NULL;
    int iTypeCxy = 0;  
    
    
    
    int l4;
    int n = 3,one = 1;
    int* data = 0;
    int *data2 = 0;
    void* Ptr =0;
    int NbTri = 0;
    int j = 0;
    int i = 0;
    int k = 0;
    
    
    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3,&piAddressCxy);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressX, &iTypeX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
    
    if ( iTypeX != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressY, &iTypeY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
    
    if ( iTypeY != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressCxy, &iTypeCxy);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
    
    if ( iTypeCxy != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
            
        
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressX,&m1,&n1,&pdX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressY,&m2,&n2,&pdY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressCxy,&m3,&n3,&pdCxy);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
        
    
    if (!(m1 == m2) ||!(n1 == n2) )
    {
        Scierror(999,"%s: Wrong size for input argument #%d: .\n",fname,1); //both inputs of the same range
        return 0;       
    }
        
    
    Ptr = constrained_delaunay_2(pdX,pdY,pdCxy,n1,m3);
    if (!Ptr)
    {
        Scierror(999, "%s: Incompatible inputs", "constrained_delaunay_2");
        return 0;
    }
        
    data = cdt2_get_connectivity(Ptr,&NbTri);
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
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }


    FREE(data);
    FREE(data2);
    if (Lhs == 1)
    {
        cdt2_delete(Ptr);
    }

    else 
    {
        sciErr = createPointer(pvApiCtx, Rhs + 2,  (void*)Ptr);
    }
    
    LhsVar(1) = Rhs + 1;
    LhsVar(2) = Rhs + 2;
    PutLhsVar();
    return 0;
}
