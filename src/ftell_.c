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

#include "f2c.h"
#include "fio.h"

 static FILE *
#ifdef KR_headers
unit_chk(Unit, who) integer Unit; char *who;
#else
unit_chk(integer Unit, char *who)
#endif
{
	if (Unit >= MXUNIT || Unit < 0)
		f__fatal(101, who);
	return f__units[Unit].ufd;
	}

 integer
#ifdef KR_headers
ftell_(Unit) integer *Unit;
#else
ftell_(integer *Unit)
#endif
{
	FILE *f;
	return (f = unit_chk(*Unit, "ftell")) ? ftell(f) : -1L;
	}

 int
#ifdef KR_headers
fseek_(Unit, offset, whence) integer *Unit, *offset, *whence;
#else
fseek_(integer *Unit, integer *offset, integer *whence)
#endif
{
	FILE *f;
	int w = (int)*whence;
#ifdef SEEK_SET
	static int wohin[3] = { SEEK_SET, SEEK_CUR, SEEK_END };
#endif
	if (w < 0 || w > 2)
		w = 0;
#ifdef SEEK_SET
	w = wohin[w];
#endif
	return	!(f = unit_chk(*Unit, "fseek"))
		|| fseek(f, *offset, w) ? 1 : 0;
	}
