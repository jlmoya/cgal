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
#include "Delaunay_mesher.h"

#include "localization.h"
#include "api_scilab.h"
#include "sciprint.h"

int sci_mesh2_set_seeds(GW_PARAMETERS)
{
    SciErr sciErr;
    
    int lPtr;
    int minlhs=1, maxlhs=1, minrhs=3, maxrhs=3;
    
    static int m1 = 0, n1 = 0, l1=0;
    int *piAddressMesh2Ptr = NULL;
    void *pdMesh2Ptr = NULL;
    int iTypeMesh2Ptr = 0;
    
    static int m2 = 0, n2 = 0, l2=0;
    int *piAddressMesh2X = NULL;
    double *pdMesh2X = NULL;
    int iTypeMesh2X = 0;
    
    static int m3 = 0, n3 = 0, l3=0;
    int *piAddressMesh2Y = NULL;
    double *pdMesh2Y = NULL;
    int iTypeMesh2Y = 0; 

    CheckRhs(minrhs,maxrhs) ;
    CheckLhs(minlhs,maxlhs) ;
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddressMesh2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressMesh2Ptr, &iTypeMesh2Ptr);
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
    
    sciErr = getPointer(pvApiCtx, piAddressMesh2Ptr , &pdMesh2Ptr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressMesh2X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressMesh2X, &iTypeMesh2X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if ( iTypeMesh2X != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,2);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressMesh2X,&m2,&n2,&pdMesh2X);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddressMesh2Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    sciErr = getVarType(pvApiCtx, piAddressMesh2Y, &iTypeMesh2Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if ( iTypeMesh2Y != sci_matrix )
    {
        Scierror(999,"%s: Wrong type for input argument #%d: A vector expected.\n",fname,3);
        return 0;
    }
    
    sciErr = getMatrixOfDouble(pvApiCtx, piAddressMesh2Y,&m3,&n3,&pdMesh2Y);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if (!(m2 == m3) ||!(n2 == n3))
    {
        Scierror(999, "%s: Incompatible inputs.\n","mesh2_set_seeds");
        return 0;
    }
    
    if (!pdMesh2Ptr)
    {
        return 0;
    }
    
    mesh2_set_seeds(pdMesh2Ptr,pdMesh2X,pdMesh2Y,n2);
    
    LhsVar(1) = Rhs - 2;
    PutLhsVar();
    return 0;
}
