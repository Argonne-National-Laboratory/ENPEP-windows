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
#include "lio.h"
#include "fmt.h" /* for f__doend */

extern flag f__lquit;
extern int f__lcount;
extern char *f__icptr;
extern char *f__icend;
extern icilist *f__svic;
extern int f__icnum, f__recpos;

static int i_getc(Void)
{
	if(f__recpos >= f__svic->icirlen) {
		if (f__recpos++ == f__svic->icirlen)
			return '\n';
		z_rnew();
		}
	f__recpos++;
	if(f__icptr >= f__icend)
		return EOF;
	return(*f__icptr++);
	}

 static
#ifdef KR_headers
int i_ungetc(ch, f) int ch; FILE *f;
#else
int i_ungetc(int ch, FILE *f)
#endif
{
	if (--f__recpos == f__svic->icirlen)
		return '\n';
	if (f__recpos < -1)
		err(f__svic->icierr,110,"recend");
	/* *--icptr == ch, and icptr may point to read-only memory */
	return *--f__icptr /* = ch */;
	}

 static void
#ifdef KR_headers
c_lir(a) icilist *a;
#else
c_lir(icilist *a)
#endif
{
	extern int l_eof;
	f__reading = 1;
	f__external = 0;
	f__formatted = 1;
	f__svic = a;
	L_len = a->icirlen;
	f__recpos = -1;
	f__icnum = f__recpos = 0;
	f__cursor = 0;
	l_getc = i_getc;
	l_ungetc = i_ungetc;
	l_eof = 0;
	f__icptr = a->iciunit;
	f__icend = f__icptr + a->icirlen*a->icirnum;
	f__cf = 0;
	f__curunit = 0;
	f__elist = (cilist *)a;
	}


#ifdef KR_headers
integer s_rsli(a) icilist *a;
#else
integer s_rsli(icilist *a)
#endif
{
	f__lioproc = l_read;
	f__lquit = 0;
	f__lcount = 0;
	c_lir(a);
	f__doend = 0;
	return(0);
	}

integer e_rsli(Void)
{ return 0; }

#ifdef KR_headers
integer s_rsni(a) icilist *a;
#else
extern int x_rsne(cilist*);

integer s_rsni(icilist *a)
#endif
{
	extern int nml_read;
	integer rv;
	cilist ca;
	ca.ciend = a->iciend;
	ca.cierr = a->icierr;
	ca.cifmt = a->icifmt;
	c_lir(a);
	rv = x_rsne(&ca);
	nml_read = 0;
	return rv;
	}
