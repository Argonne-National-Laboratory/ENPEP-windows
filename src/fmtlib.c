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

/*	@(#)fmtlib.c	1.2	*/
#define MAXINTLENGTH 23

#include "f2c.h"
#ifndef Allow_TYQUAD
#undef longint
#define longint long
#undef ulongint
#define ulongint unsigned long
#endif

#ifdef KR_headers
char *f__icvt(value,ndigit,sign, base) longint value; int *ndigit,*sign;
 register int base;
#else
char *f__icvt(longint value, int *ndigit, int *sign, int base)
#endif
{
	static char buf[MAXINTLENGTH+1];
	register int i;
	ulongint uvalue;

	if(value > 0) {
		uvalue = value;
		*sign = 0;
		}
	else if (value < 0) {
		uvalue = -value;
		*sign = 1;
		}
	else {
		*sign = 0;
		*ndigit = 1;
		buf[MAXINTLENGTH-1] = '0';
		return &buf[MAXINTLENGTH-1];
		}
	i = MAXINTLENGTH;
	do {
		buf[--i] = (uvalue%base) + '0';
		uvalue /= base;
		}
		while(uvalue > 0);
	*ndigit = MAXINTLENGTH - i;
	return &buf[i];
	}
