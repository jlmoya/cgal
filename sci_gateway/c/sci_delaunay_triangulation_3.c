// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt


#include "gateway_cglab.h"
#include "localization.h"
#include <string.h>
#include <stdio.h>
#include "api_scilab.h"
#include "sciprint.h"
#include "Delaunay_3d.h"

int sci_delaunay_triangulation_3(GW_PARAMETERS)
{
    SciErr sciErr;
    
    int l4;
    int minlhs=1, maxlhs=2, minrhs=3, maxrhs=3;

    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDt3X = NULL;
    double *pdDt3X = NULL;
    int iTypeDt3X = 0;  
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAddressDt3Y = NULL;
    double *pdDt3Y = NULL;
    int iTypeDt3Y = 0; 
    
    static int m3 = 0, n3 = 0, l3=0;
    int *piAddressDt3Z = NULL;
    double *pdDt3Z = NULL;
    int iTypeDt3Z = 0; 
    
    
    void* Ptr=0;
    int one =1;

    int* data = 0;
    int *data2 = 0;
    int n = 4;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int nbtetra = 0;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressDt3X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
            
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressDt3Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressDt3Z);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3X, &iTypeDt3X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeDt3X != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }
        
    sciErr = getVarType(pvApiCtx, piAddressDt3Y, &iTypeDt3Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if ( iTypeDt3Y != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDt3Z, &iTypeDt3Z);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }  
        
    if ( iTypeDt3Z != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3X,&m1,&n1,&pdDt3X);
    if	(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3Y,&m2,&n2,&pdDt3Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDt3Z,&m3,&n3,&pdDt3Z);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (!(m1 == m2) ||!(n1 == n2)||!(n1 == n3) )
    {
        Scierror(999,"%s: Incompatible inputs \r\n","delaunay3");
        return 0;
    }

    Ptr = delaunay_triangulation_3(pdDt3X,pdDt3Y,pdDt3Z,n1);
    if(!Ptr)
    {
        sciprint("%s: Incompatible inputs \r\n","cdelaunay");
        return 0;
    }

    data = dt3_get_connectivity(Ptr,&nbtetra);
    if (!data)
    {
        return 0;
    }
    
    data2 = (int*)malloc(sizeof(int)* 4*nbtetra);
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

    if (Lhs == 1) 
    {
        dt3_delete(Ptr);
    }
    else 
    {
        sciErr = createPointer(pvApiCtx, Rhs + 2,  (void*)Ptr);
    }

    LhsVar(1) = Rhs + 1;
    LhsVar(2) = Rhs + 2;
    PutLhsVar();
    free(data);
    free(data2);
    return 0;
}
