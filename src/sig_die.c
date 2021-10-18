/*******************************************************************

						COPYRIGHT NOTIFICATION

********************************************************************

	Copyright © 2021, UChicago Argonne, LLC

	All Rights Reserved
	Software Name: 	ENPEP- Balance
	By: Argonne National Laboratory
	OPEN SOURCE LICENSE

********************************************************************

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

********************************************************************

DISCLAIMER

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

********************************************************************
 				
*/

#include "stdio.h"
#include "signal.h"

#ifndef SIGIOT
#ifdef SIGABRT
#define SIGIOT SIGABRT
#endif
#endif

#ifdef KR_headers
void sig_die(s, kill) register char *s; int kill;
#else
#include "stdlib.h"
#ifdef __cplusplus
extern "C" {
#endif
 extern void f_exit(void);
extern FILE  *fp21;
void sig_die(register char *s, int kill)
#endif
{
	/* print error message, then clear buffers */
	fprintf(fp21, "%s\n", s);

	if(kill)
		{
		fflush(fp21);
		f_exit();
		fflush(fp21);
		/* now get a core */
#ifdef SIGIOT
		signal(SIGIOT, SIG_DFL);
#endif
		abort();
		}
	else {
#ifdef NO_ONEXIT
		f_exit();
#endif
		exit(1);
		}
	}
#ifdef __cplusplus
}
#endif
