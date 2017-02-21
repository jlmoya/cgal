// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "interpolation_functions.h"

#include "localization.h"
#include "api_scilab.h"
#include "Scierror.h"

#include <stdlib.h>

void* create_output(int _iCoeff, int _iSize, int _iRows, int _iCols, void* _pvDataIn);
int sci_interp3(GW_PARAMETERS)
{
    int minlhs=1, maxlhs=1, minrhs=7, maxrhs=7;
    SciErr sciErr;
    
    
    static int m1 = 0, n1 = 0, l1 = 0;
    int *piAdressXi = NULL;
    double *pdVarXi = NULL;
    int iTypeXi = 0;
    
    static int m2 = 0, n2 = 0, l2 = 0;
    int *piAdressYi = NULL;
    double *pdVarYi = NULL;
    int iTypeYi= 0;
    
    static int m3 = 0, n3 = 0, l3 = 0;
    int *piAdressZi = NULL;
    double *pdVarZi = NULL;
    int iTypeZi = 0;
    
    static int m4 = 0, n4 = 0, l4 = 0;
    int *piAdressX = NULL;
    double *pdVarX = NULL;
    int iTypeX = 0;
    
    static int m5 = 0, n5 = 0, l5 = 0;
    int *piAdressY = NULL;
    double *pdVarY = NULL;
    int iTypeY = 0;
    
    static int m6 = 0, n6 = 0, l6 = 0;
    int *piAdressZ = NULL;
    double *pdVarZ = NULL;
    int iTypeZ = 0;
    
    static int m7 = 0, n7 = 0, l7 = 0;
    int *piAdressV = NULL;
    double *pdVarV = NULL;
    int iTypeV = 0;
    int iItem = 0;
    int* piChild = NULL;
    int iTypeChild = 0;
    int iRows = 0;
    int iCols = 0;
    int iRows1 = 0;
    int iCols1 = 0;
    double *pdblReal = 0;
    int *piLen = NULL;
    char **pstData  = NULL;
    int* puiData   = NULL;
    
    
    double** V = 0;
    int ii = 0;
    int j = 0;
    int i = 0;
    int k = 0;
    int N = 0;
    double** xp = 0;
    double** yp = 0;
    double** zp = 0;
    double*** v = 0;
    
    int counter =0;
	  int counter2=0;
	  
    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressXi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressXi, &iTypeXi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeXi != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A matrix expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressXi,&m1,&n1,&pdVarXi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAdressYi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressYi, &iTypeYi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeYi != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A matrix expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressYi,&m2,&n2,&pdVarYi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAdressZi);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressZi, &iTypeZi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeZi != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A matrix expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressZi,&m3,&n3,&pdVarZi);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if (m1 != m2 || m2 != m3 || n1 != n2 || n2 != n3 )
    {
        Scierror(999,"%s: bad inputs for xp, yp, zp \r\n","interp3");
        return 0;
    }
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAdressX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressX, &iTypeX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeX != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,4);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressX,&m4,&n4,&pdVarX);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 5, &piAdressY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressY, &iTypeY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeY != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,5);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressY,&m5,&n5,&pdVarY);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 6, &piAdressZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressZ, &iTypeZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeZ != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,6);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressZ,&m6,&n6,&pdVarZ);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if (m4 != 1 || m5 != 1 || m6 != 1)
    {
        Scierror(999,"%s: row vectors expected\n","interp3");
        return 0;
    }
    
    if (n4 != n5 || n5 != n6 || n6 != n4)
    {
        Scierror(999,"%s: bad inputs for x, y, z \r\n","interp3");
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 7, &piAdressV);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressV, &iTypeV);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeV != sci_mlist )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: An mlist expected.\n",fname,7);
        return 0;
    }
    
	sciErr = getListItemNumber(pvApiCtx, piAdressV, &iItem);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	

	
	sciErr = getListItemAddress(pvApiCtx, piAdressV,  1, &piChild);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	
	sciErr = getVarType(pvApiCtx, piChild, &iTypeChild);
	sciErr = getMatrixOfStringInList(pvApiCtx, piAdressV, 1, &iRows, &iCols, NULL, NULL);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}

	piLen = (int*)malloc(sizeof(int) * iRows * iCols);
	
	sciErr = getMatrixOfStringInList(pvApiCtx, piAdressV, 1, &iRows, &iCols, piLen, NULL);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}

	pstData = (char**)malloc(sizeof(char*) * iRows * iCols);
	for (i = 0 ; i < iRows * iCols ; i++)
	{
		pstData[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
	}

	sciErr = getMatrixOfStringInList(pvApiCtx, piAdressV, 1, &iRows, &iCols, piLen, pstData);

	sciErr = getListItemAddress(pvApiCtx, piAdressV,  2, &piChild);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	sciErr = getMatrixOfInteger32InList(pvApiCtx, piAdressV,2, &iRows1, &iCols1, &puiData);
	
	sciErr = getListItemAddress(pvApiCtx, piAdressV, 3, &piChild);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	
	sciErr = getMatrixOfDoubleInList(pvApiCtx, piAdressV, 3, &iRows, &iCols, &pdblReal);
	if (sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
    
    xp = (double**)malloc(m1*sizeof(double*));
    yp = (double**)malloc(m1*sizeof(double*));
    zp = (double**)malloc(m1*sizeof(double*));
    v = (double***)malloc((*puiData)*sizeof(double*));

    for (i = 0 ; i < m1 ; i++)
    {
        xp[i] = (double*)malloc(n1*sizeof(double));
        yp[i] = (double*)malloc(n1*sizeof(double));
        zp[i] = (double*)malloc(n1*sizeof(double));
    }
    
    for (i = 0 ; i < (*puiData) ; i++)
    {
        v[i] = (double**)malloc((*puiData+1)*sizeof(double*));
    }

    for (i = 0 ; i < (*(puiData+1)) ; i++)
    {
        for(j = 0 ; j < (*(puiData+2)) ; j++) 
         {
            v[i][j] = (double*)malloc((*(puiData+2))*sizeof(double));
         }
    }
    
  counter =0;
	for ( k =0 ; k < (*puiData) ; k++)
	{
		for ( j =0 ; j < (*(puiData+1)) ; j++)
		{
			for ( i =0 ; i < (*(puiData+2)) ; i++) 
			{
			    v[i][j][k] = (*(pdblReal+counter));
			    counter=counter+1;
			}
		}
	}
	
  counter2=0;
	
	for( j =0 ; j < n1 ; j++)
	{
		for( i =0 ; i < m1 ; i++)
		{
			xp[i][j] = *(pdVarXi+counter2);
			yp[i][j] = *(pdVarYi+counter2);
			zp[i][j] = *(pdVarZi+counter2);
			counter2=counter2+1;
		}
	}
	
    V = interp3(xp,yp,zp,pdVarX,pdVarY,pdVarZ,v,n4,n5,n6,m1,n1);
    
    if (!V)
    {
        return 0;
    }
    
    sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, m1, n1, *V);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    LhsVar(1) = Rhs + 1;
    PutLhsVar();
    
    for (i = 0 ; i < n4 ; i++)
    {
        for(j = 0 ; j < n5 ; j++) 
        {
        free(v[i][j]);
        }
    }
    
    for (i = 0 ; i < n4 ; i++)
    {
    free(v[i]);
    }
        
    for (i = 0 ; i < m1 ; i++)
    {
    free(xp[i]);
    free(yp[i]);
    free(zp[i]);
    free(V[i]);
    }

    free(xp);
    free(yp);
    free(zp);
    free(v);    
    free(V);

    return 0;

    
}
