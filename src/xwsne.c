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
#include "fmt.h"

extern int f__Aquote;

 static VOID
nl_donewrec(Void)
{
	(*f__donewrec)();
	PUT(' ');
	}

#ifdef KR_headers
x_wsne(a) cilist *a;
#else
#include "string.h"

 VOID
x_wsne(cilist *a)
#endif
{
	Namelist *nl;
	char *s;
	Vardesc *v, **vd, **vde;
	ftnint *number, type;
	ftnlen *dims;
	ftnlen size;
	static ftnint one = 1;
	extern ftnlen f__typesize[];

	nl = (Namelist *)a->cifmt;
	PUT('&');
	for(s = nl->name; *s; s++)
		PUT(*s);
	PUT(' ');
	f__Aquote = 1;
	vd = nl->vars;
	vde = vd + nl->nvars;
	while(vd < vde) {
		v = *vd++;
		s = v->name;
#ifdef No_Extra_Namelist_Newlines
		if (f__recpos+strlen(s)+2 >= L_len)
#endif
			nl_donewrec();
		while(*s)
			PUT(*s++);
		PUT(' ');
		PUT('=');
		number = (dims = v->dims) ? dims + 1 : &one;
		type = v->type;
		if (type < 0) {
			size = -type;
			type = TYCHAR;
			}
		else
			size = f__typesize[type];
		l_write(number, v->addr, size, type);
		if (vd < vde) {
			if (f__recpos+2 >= L_len)
				nl_donewrec();
			PUT(',');
			PUT(' ');
			}
		else if (f__recpos+1 >= L_len)
			nl_donewrec();
		}
	f__Aquote = 0;
	PUT('/');
	}
