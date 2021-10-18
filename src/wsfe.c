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

/*write sequential formatted external*/
#include "f2c.h"
#include "fio.h"
#include "fmt.h"
extern int f__hiwater;

 int
x_wSL(Void)
{
	int n = f__putbuf('\n');
	f__hiwater = f__recpos = f__cursor = 0;
	return(n == 0);
}

 static int
xw_end(Void)
{
	int n;

	if(f__nonl) {
		f__putbuf(n = 0);
		fflush(f__cf);
		}
	else
		n = f__putbuf('\n');
	f__hiwater = f__recpos = f__cursor = 0;
	return n;
}

 static int
xw_rev(Void)
{
	int n = 0;
	if(f__workdone) {
		n = f__putbuf('\n');
		f__workdone = 0;
		}
	f__hiwater = f__recpos = f__cursor = 0;
	return n;
}

#ifdef KR_headers
integer s_wsfe(a) cilist *a;	/*start*/
#else
integer s_wsfe(cilist *a)	/*start*/
#endif
{	int n;
	if(!f__init) f_init();
	f__reading=0;
	f__sequential=1;
	f__formatted=1;
	f__external=1;
	if(n=c_sfe(a)) return(n);
	f__elist=a;
	f__hiwater = f__cursor=f__recpos=0;
	f__nonl = 0;
	f__scale=0;
	f__fmtbuf=a->cifmt;
	f__cf=f__curunit->ufd;
	if(pars_f(f__fmtbuf)<0) err(a->cierr,100,"startio");
	f__putn= x_putc;
	f__doed= w_ed;
	f__doned= w_ned;
	f__doend=xw_end;
	f__dorevert=xw_rev;
	f__donewrec=x_wSL;
	fmt_bg();
	f__cplus=0;
	f__cblank=f__curunit->ublnk;
	if(f__curunit->uwrt != 1 && f__nowwriting(f__curunit))
		err(a->cierr,errno,"write start");
	return(0);
}
