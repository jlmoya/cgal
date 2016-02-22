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

#ifdef __cplusplus
extern "C"
{
#endif
#define __USE_DEPRECATED_STACK_FUNCTIONS__
#include"stack-c.h"
#include <string.h>
#include "machine.h"
#include <stdio.h>
extern int C2F(scirun)(char * startup, int lstartup);
int send_scilab_job(char *job)
{
	static char buf[1024];
	static char format[]="Err=execstr('%s','errcatch','n');quit;";
	int m,n,lp;
	sprintf(buf,format,job);
	fprintf(stderr,"job envoye %s\n",buf);
	C2F(scirun)(buf,strlen(buf));
	GetMatrixptr("Err", &m, &n, &lp);
	return (int) *stk(lp);
}
#ifdef __cplusplus
}
#endif
