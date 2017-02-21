// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Surface_mesher.h"

#include "localization.h"
#include "api_scilab.h"
#include "sciprint.h"
#include "Scierror.h"

#include <string.h>
#include <stdio.h>

int sci_surface_mesher(GW_PARAMETERS)
{

    SciErr sciErr;
    
    static int m1 = 0, n1 = 0, l1 = 0;
    int *piAdressImageFile = NULL;
    char *pdVarImageFile = NULL;
    int iTypeImageFile = 0;
    
    static int m2 = 0, n2 = 0, l2 = 0;
    int *piAdressIsoValue = NULL;
    double pdVarIsoValue = 0;
    int iTypeIsoValue= 0;
    
    static int m3 = 0, n3 = 0, l3 = 0;
    int *piAdressBoundingSphere = NULL;
    double *pdVarBoundingSphere = NULL;
    int iTypeBoundingSphere = 0;
    
    static int m4 = 0, n4 = 0, l4 = 0;
    int *piAdressMeshCriteria = NULL;
    double *pdVarMeshCriteria = NULL;
    int iTypeMeshCriteria = 0;
    
    int minlhs=2, maxlhs=2, minrhs=4, maxrhs=4;
    int lsphere, msphere, nsphere;
    int lcriteria,mcriteria, ncriteria;

    void* Ptr=0;
    int one =1;

    int* data = 0;
    int *data2 = 0;
    double* Coord = 0;
    int n = 3,m=3;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int nbtriangle = 0,nbpts = 0;
    int iRet = 0;
    int isValidFile = 0;
    
    char ext1[] = "inr";
    char ext2[] = "dim";
    char ext3[] = "ima";
    char ext4[] = "hdr";
    char ext5[] = "img";
    char *extension = NULL;
    int cmp1, cmp2, cmp3, cmp4, cmp5;
    char ext0[3];

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressImageFile);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressImageFile, &iTypeImageFile);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeImageFile != sci_strings )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A string expected.\n",fname,1);
        return 0;
    }
    
    iRet = getAllocatedSingleString(pvApiCtx, piAdressImageFile, &pdVarImageFile);
    if(iRet)
    {
        freeAllocatedSingleString(pdVarImageFile);
        return iRet;
    }
    
    FILE *fp;
    if ( (fp=fopen(pdVarImageFile,"r")) == NULL ) 
    {
        Scierror(49,"%s: Incorrect file or format.\n",fname);
        return 0;     
    }  
    else
    {
        fclose(fp);
    }

    extension = strrchr(pdVarImageFile,'.');
    if(extension==NULL)
    {
        Scierror(49,"%s: Incorrect file or format.\n",fname);
        return 0;
    }
    strncpy(ext0,extension + 1,3);
    cmp1 = strncmp(ext1,ext0,3);
    cmp2 = strncmp(ext2,ext0,3);
    cmp3 = strncmp(ext3,ext0,3);
    cmp4 = strncmp(ext4,ext0,3);
    cmp5 = strncmp(ext5,ext0,3);

    if(!((cmp1==0) || (cmp2 == 0) || (cmp3 == 0) || (cmp4 == 0) || (cmp5 == 0)))
    {
        Scierror(49,"%s: Incorrect file or format.\n",fname);
        return 0;
    }

    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAdressIsoValue);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressIsoValue, &iTypeIsoValue);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeIsoValue != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    iRet = getScalarDouble(pvApiCtx, piAdressIsoValue, &pdVarIsoValue);
    if (iRet)
    {
        return iRet;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAdressBoundingSphere);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressBoundingSphere, &iTypeBoundingSphere);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeBoundingSphere != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressBoundingSphere,&m3,&n3,&pdVarBoundingSphere);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAdressMeshCriteria);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressMeshCriteria, &iTypeMeshCriteria);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeMeshCriteria != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,4);
        return 0;
    }

    sciErr = getMatrixOfDouble(pvApiCtx, piAdressMeshCriteria,&m4,&n4,&pdVarMeshCriteria);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
   
    
    Ptr = surface_mesher(pdVarImageFile,pdVarIsoValue,pdVarBoundingSphere,pdVarMeshCriteria);
    if (!Ptr)
    {
        return 0;
    }
    
    
    data = sm_get_connectivity(Ptr,&nbtriangle);
    if (!data)
    {
        return 0;
    }

    data2=(int*)malloc(sizeof(int)*(3*nbtriangle+3));
    if (data2==NULL)
    {
        Scierror(999,"Can't allocate memory!\n");
        return 0;
    }

	for(j=0; j< nbtriangle; j++)
	{
		*(data2+j)= data[3*j];
		i = j + nbtriangle;
		*(data2+i)= data[1+3*j];
		k = i + nbtriangle;
		*(data2+k)= data[2+3*j];

	}
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 1, nbtriangle, n, data2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    Coord = sm_get_coord(Ptr,&nbpts);
    if (!Coord)
    {
        return 0;
    }
    sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 2, nbpts, m, Coord);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    free(data);
    free(data2);
    free(Coord);
    delete_surface_mesher(Ptr);
    
    LhsVar(1) = Rhs + 1;
    LhsVar(2) = Rhs + 2;
    PutLhsVar();
    return 0;


    
}



