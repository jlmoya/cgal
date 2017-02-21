// Copyright (c) 2005  INRIA Sophia-Antipolis (France).
// All rights reserved.
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
// $Id: scilab_job.c 6 2005-12-05 15:53:46Z nmeskini $
// $URL: svn://scm.gforge.inria.fr/svn/cglab/trunk/cglab/src/libCG-LAB/src/scilab_job.c $
//
// Author(s)     : Naceur Meskini
//=========================================================================

#include "version.h"
#if SCI_VERSION_MAJOR < 6
#define __USE_DEPRECATED_STACK_FUNCTIONS__
#endif

#include "call_scilab.h"
#include "Scierror.h"
#include "machine.h"

#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif
int send_scilab_job(char *job)
{
    #ifdef _MSC_VER
    if (StartScilab(NULL, NULL, NULL) == FALSE)
    #else
    if (StartScilab(getenv("SCI"), NULL, NULL) == FALSE)
    #endif
    {
        Scierror(999, "%s: Error while calling StartScilab().\n", "send_scilab_job");
        return -1;
    }

    return SendScilabJob(job);
    return 0;
}
#ifdef __cplusplus
}
#endif
