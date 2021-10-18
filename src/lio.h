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

/*	copy of ftypes from the compiler */
/* variable types
 * numeric assumptions:
 *	int < reals < complexes
 *	TYDREAL-TYREAL = TYDCOMPLEX-TYCOMPLEX
 */

/* 0-10 retain their old (pre LOGICAL*1, etc.) */
/* values to allow mixing old and new objects. */

#define TYUNKNOWN 0
#define TYADDR 1
#define TYSHORT 2
#define TYLONG 3
#define TYREAL 4
#define TYDREAL 5
#define TYCOMPLEX 6
#define TYDCOMPLEX 7
#define TYLOGICAL 8
#define TYCHAR 9
#define TYSUBR 10
#define TYINT1 11
#define TYLOGICAL1 12
#define TYLOGICAL2 13
#ifdef Allow_TYQUAD
#undef TYQUAD
#define TYQUAD 14
#endif

#define	LINTW	24
#define	LINE	80
#define	LLOGW	2
#ifdef Old_list_output
#define	LLOW	1.0
#define	LHIGH	1.e9
#define	LEFMT	" %# .8E"
#define	LFFMT	" %# .9g"
#else
#define	LGFMT	"%.9G"
#endif
/* LEFBL 20 should suffice; 24 overcomes a NeXT bug. */
#define	LEFBL	24

typedef union
{
	char	flchar;
	short	flshort;
	ftnint	flint;
#ifdef Allow_TYQUAD
	longint fllongint;
#endif
	real	flreal;
	doublereal	fldouble;
} flex;
extern int f__scale;
#ifdef KR_headers
extern int (*f__lioproc)(), (*l_getc)(), (*l_ungetc)();
extern int l_read(), l_write();
#else
#ifdef __cplusplus
extern "C" {
#endif
extern int (*f__lioproc)(ftnint*, char*, ftnlen, ftnint);
extern int l_write(ftnint*, char*, ftnlen, ftnint);
extern void x_wsne(cilist*);
extern int c_le(cilist*), (*l_getc)(void), (*l_ungetc)(int,FILE*);
extern int l_read(ftnint*,char*,ftnlen,ftnint);
extern integer e_rsle(void), e_wsle(void), s_wsne(cilist*);
extern int z_rnew(void);
#ifdef __cplusplus
	}
#endif
#endif
extern ftnint L_len;
