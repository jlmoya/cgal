// Copyright (C) 2011 - Edyta Przymus
//
// This file is part of CG-LAB; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CG-LAB.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Id: intDelaunay_mesher.c 6 2005-12-05 15:53:46Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/intDelaunay_mesher.c $
//
// Author(s)     : Naceur Meskini
//               : Edyta Przymus
//=========================================================================

// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt

#include "gateway_cglab.h"
#include "Stream_lines.h"

#include "localization.h"
#include "api_scilab.h"
#include "sciprint.h"

int sci_streamlines_2(GW_PARAMETERS)
{
    SciErr sciErr;
    
    int minlhs=2, maxlhs=2, minrhs=4, maxrhs=4;
    int l5;
    
    static int m1 = 0, n1 = 0, l1 = 0;
    int *piAdressU = NULL;
    double *pdVarU = NULL;
    int iTypeU = 0;
    
    static int m2 = 0, n2 = 0, l2 = 0;
    int *piAdressV = NULL;
    double *pdVarV = NULL;
    int iTypeV = 0;
    
    static int m3 = 0, n3 = 0, l3 = 0;
    int *piAdressSd = NULL;
    double *pdVarSd = NULL;
    int iTypeSd = 0;
    
    static int m4 = 0, n4 = 0, l4 = 0;
    int *piAdressStep = NULL;
    double *pdVarStep = NULL;
    int iTypeStep = 0;
    
    
    int j = 0;
    int i = 0;
    int nL = 1,lL;
    int integr_m,integr_n;
    int nb_stls = 0;
    int N = 2;
    int one = 1,l6;
    int size = 0;
    int nb_pts = 0;

    double* stls = 0;
    double *stls2 = 0;
    void* Ptr;
    int* nbpts_of_stls = 0;
    int *nbpts_of_stls2 = 0;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    //GetRhsVar(1, "d", &u_m, &u_n, &l1);
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressU);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressU, &iTypeU);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeU != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressU,&m1,&n1,&pdVarU);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAdressV);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressV, &iTypeV);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeV != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressV,&m2,&n2,&pdVarV);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAdressSd);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressSd, &iTypeSd);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeSd != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressSd,&m3,&n3,&pdVarSd);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAdressStep);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressStep, &iTypeStep);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }   
        
    if ( iTypeU != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,4);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAdressStep,&m4,&n4,&pdVarStep);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    Ptr = streamlines_2(pdVarU,pdVarV,*pdVarSd,m1,n1,&nb_stls,*pdVarStep);
    
    if (!Ptr)
    {
        return 0;
    }
    
    
    nbpts_of_stls = get_nbpts_of_stls(Ptr);
    
    if (!nbpts_of_stls)
    {
        return 0;
    }
    
    for (i = 0; i < nb_stls ; i++)
    {
        nb_pts = nb_pts + nbpts_of_stls[i];
    }
    
    stls = get_stls(Ptr,nb_pts);
    
    if (!stls)
    {
        return 0;
    }
    
    delete_stls(Ptr);
    
    size = nb_stls+1;
    
    //CreateVar(5, "d", &nb_pts, &N, &l5);
    
    stls2 = (double*)malloc(sizeof(double) * 2*nb_pts);
    if(stls2 == NULL)
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,4);
        return 0;
    }

	for (j = 0 ; j< nb_pts ;j++)
	{
		*(stls2 + j) = stls[2*j];
		*(stls2 + j+nb_pts) = stls[2*j+1];
	}
    
    sciErr = createMatrixOfDouble(pvApiCtx, Rhs + 1, nb_pts, N, stls2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    nbpts_of_stls2 = (int*)malloc(sizeof(int) * size);
    if (nbpts_of_stls2==NULL)
    {
        Scierror(999,"Can't allocate memory!\n");
        return 0;
    }
    
	*nbpts_of_stls2 = nb_stls;
	
	for (j = 1 ; j< size ;j++)
	{
		*(nbpts_of_stls2 + j) = nbpts_of_stls[j-1];
	}
    
    sciErr = createMatrixOfInteger32(pvApiCtx, Rhs + 2, size, one, nbpts_of_stls2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    LhsVar(1) = Rhs + 1;
    LhsVar(2) = Rhs + 2;
    PutLhsVar();
    free(nbpts_of_stls);
    free(nbpts_of_stls2);
    free(stls);
    free(stls2);

    
    
}
