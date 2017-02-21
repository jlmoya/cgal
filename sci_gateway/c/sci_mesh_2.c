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

int sci_mesh_2(GW_PARAMETERS){

    SciErr sciErr;
    int l3,l4;

    static int m1 = 0, n1 = 0, l1=0;
    int *piAdressPslg = NULL;
    double *pdVarPslg = NULL;
    int iTypePslg = 0;

    int minlhs=1, maxlhs=3, minrhs=1, maxrhs=1;
    void* Ptr;
    int one =1;
    int n = 3,m = 2;
    int* data = 0;
    int *data2 = 0;
    double* Coord = 0;
    double *Coord2 = 0;
    int NbTri = 0,nbpts = 0;
    int j = 0;
    int i = 0;
    int k = 0;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressPslg);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getVarType(pvApiCtx, piAdressPslg, &iTypePslg);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if ( iTypePslg != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }

    sciErr = getMatrixOfDouble(pvApiCtx, piAdressPslg,&m1,&n1,&pdVarPslg);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (!(n1 == 4) )
    {
        Scierror(999,"%s: Incompatible inputs", fname);
        return 0;
    }

    Ptr = mesh_2(pdVarPslg,m1);
    if(!Ptr)
    {
        Scierror(999, "%s: Incompatible inputs", "mesh_2");
        return 0;
    }

    sciErr = createPointer(pvApiCtx, Rhs + 1,  (void*)Ptr);

    Coord = mesh2_get_coord(Ptr,&nbpts);

    if(!Coord)
    {
        return 0;
    }

    sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 2, nbpts, m, Coord);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    data = mesh2_get_connectivity(Ptr,&NbTri);
    if (!data)
    {
        return 0;
    }

    data2 = (int*)malloc(sizeof(int) * 3*NbTri);
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

    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 3, NbTri, n, data2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }


    LhsVar(1) = Rhs + 2;
    LhsVar(2) = Rhs + 3;
    LhsVar(3) = Rhs + 1;
    PutLhsVar();

    free(data);
    free(data2);
    free(Coord);








}
