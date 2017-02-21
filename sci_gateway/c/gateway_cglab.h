#ifndef _GATEWAY_CGLAB_H
#define _GATEWAY_CGLAB_H

#include "version.h"
#if SCI_VERSION_MAJOR < 6
#define GW_PARAMETERS char *fname, unsigned long fname_len
#else
#define GW_PARAMETERS char *fname, void *pvApiCtx
#endif

#endif
