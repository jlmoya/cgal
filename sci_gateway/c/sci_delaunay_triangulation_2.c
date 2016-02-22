// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#define __USE_DEPRECATED_STACK_FUNCTIONS__
#include "stack-c.h"
#include "localization.h"
#include "api_scilab.h"
#include "sciprint.h"
#include "Delaunay_2d.h"

int sci_delaunay_triangulation_2(char* fname)
{
    static int l3;
    static int minlhs=1, maxlhs=2, minrhs=2, maxrhs=2;
    
    SciErr sciErr;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAdressDt2X = NULL;
    double *pdVarDt2X = NULL;
    int iTypeDt2X = 0;  
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAdressDt2Y = NULL;
    double *pdVarDt2Y = NULL;
    int iTypeDt2Y = 0; 
    
    void* Ptr;
    int one =1;
    static int n = 3;
    int* data = 0;
    int *data2 = 0;
    int NbTri = 0;
    
    int j = 0;
    int i = 0;
    int k = 0;

    CheckRhs (minrhs,maxrhs) ;
    CheckLhs (minlhs,maxlhs) ;
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressDt2X);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
        
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAdressDt2Y);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressDt2X, &iTypeDt2X);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeDt2X != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }
        
    sciErr = getVarType(pvApiCtx, piAdressDt2Y, &iTypeDt2Y);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeDt2Y != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressDt2X,&m1,&n1,&pdVarDt2X);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressDt2Y,&m2,&n2,&pdVarDt2Y);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (!(m1 == m2) ||!(n1 == n2) )
    {
        Scierror(999,"%s: Incompatible inputs \r\n","delaunay");
        return 0;
    }
    
    Ptr = delaunay_triangulation_2(pdVarDt2X,pdVarDt2Y,n1);
    if(!Ptr)
    {
        sciprint("%s: Incompatible inputs \r\n","cdelaunay");
        return 0;
    }

    sciErr = createPointer(pvApiCtx, Rhs + 1,  (void*)Ptr);

    data =dt2_get_connectivity(Ptr,&NbTri);
    if (!data)
    {
        return 0;
    }
    
    data2 = (int*)malloc(sizeof(int)*3*NbTri);
    if (data2==NULL)
    {
        Scierror(999,"Can't allocate memory!\n");
        return 0;
    }
    
	for (j=0; j< NbTri; j++)
	{
		*(data2+j)= data[3*j];
		i = j + NbTri;
		*(data2+i)= data[1+3*j];
		k = i + NbTri;
		*(data2+k)= data[2+3*j];
	}
    
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 2, NbTri, n, data2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (Lhs != 2)
    {
        dt2_delete(Ptr);
    }

    LhsVar(1) = Rhs + 2;
    LhsVar(2) = Rhs + 1;
    PutLhsVar();
    free (data);
    free(data2);
    return 0;

}
