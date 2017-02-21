// Copyright (C) 2011 - Edyta Przymus
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Delaunay_nd.h"

#include "api_scilab.h"
#include "machine.h"
#include "localization.h"

#include <string.h>
#include <math.h>
#include <stdio.h>

int sci_delaunay_triangulation_n(GW_PARAMETERS)
{

    SciErr sciErr;

    int l2;
    int minlhs=1, maxlhs=2, minrhs=1, maxrhs=1;
    
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressDtN = NULL;
    double *pdDtN = NULL;
    int iTypeDtN = 0;
    
    void* Ptr = 0;
    int one =1;

    int* data = 0;
    int i = 0;
    int j = 0;
    int nbsimplices = 0;
    int curdim = 0;
    int n = 0;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressDtN);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressDtN, &iTypeDtN);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if ( iTypeDtN != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressDtN,&m1,&n1,&pdDtN);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
    
    Ptr = delaunay_triangulation_n(pdDtN,n1,m1);
    if (!Ptr)
    {
        Scierror(999, "%s: Incompatible inputs", "delaunay_triangulation_n");
        return 0;
    }
    
    data = dtn_get_connectivity(Ptr,&nbsimplices,&curdim);
    if (!data)
    {
        return 0;
    }


    n = curdim +1;
    
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 1, nbsimplices, n, data);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if (Lhs == 1)
    {
        dtn_delete(Ptr);
    }
    
    else 
    {
        sciErr = createPointer(pvApiCtx, Rhs + 2,  (void*)Ptr);
    }

    LhsVar(1) = Rhs + 1;
    LhsVar(2) = Rhs + 2;
    PutLhsVar();
    free(data);

    return 0;


}
