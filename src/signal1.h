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

/* You may need to adjust the definition of signal1 to supply a */
/* cast to the correct argument type.  This detail is system- and */
/* compiler-dependent.   The #define below assumes signal.h declares */
/* type SIG_PF for the signal function's second argument. */

/* For some C++ compilers, "#define Sigarg_t ..." may be appropriate. */

#include <signal.h>

#ifndef Sigret_t
#define Sigret_t void
#endif
#ifndef Sigarg_t
#ifdef KR_headers
#define Sigarg_t
#else
#define Sigarg_t int
#endif
#endif /*Sigarg_t*/

#ifdef USE_SIG_PF	/* compile with -DUSE_SIG_PF under IRIX */
#define sig_pf SIG_PF
#else
typedef Sigret_t (*sig_pf)(Sigarg_t);
#endif

#define signal1(a,b) signal(a,(sig_pf)b)

#ifdef __cplusplus
#define Sigarg ...
#define Use_Sigarg
#else
#define Sigarg Int n
#define Use_Sigarg n = n	/* shut up compiler warning */
#endif
