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
// $Id: intConstrained_Delaunay.c 6 2005-12-05 15:53:46Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/intConstrained_Delaunay.c $
//
// Author(s)     : Naceur Meskini
//                 Edyta Przymus
//=========================================================================
#define __USE_DEPRECATED_STACK_FUNCTIONS__
#include "stack-c.h"
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
#include "stack-c.h"
#include "localization.h"
#include "api_scilab.h"
#include "sciprint.h"
#include "Delaunay_2d.h"

int sci_dt2_get_connectivity(char* fname)
{
    SciErr sciErr;	
    static int lPtr,l3;
    static int minlhs=1, maxlhs=1, minrhs=1, maxrhs=1;
    static int n = 3;
    
    static int m1 = 0, n1 = 0;
    int *piAdressDt2Ptr = NULL;
    void *pdVarDt2Ptr = NULL;
    int iTypeDt2Ptr = 0;  
    
    int* data = 0;
    int *data2 = 0;
    int NbTri = 0;
    int j = 0;
    int i = 0;
    int k = 0;
    void* Ptr;

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAdressDt2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAdressDt2Ptr, &iTypeDt2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    if ( iTypeDt2Ptr != sci_pointer )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A pointer expected.\n",fname,1);
        return 0;
    }
    
    sciErr = getPointer(pvApiCtx, piAdressDt2Ptr , &pdVarDt2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    data = dt2_get_connectivity(pdVarDt2Ptr,&NbTri);
    if (!data)
    {
        return 0;
    }
    
    data2 = (int*)malloc(sizeof(int)*3*NbTri);
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
    return 0;

}
