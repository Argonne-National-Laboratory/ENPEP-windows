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
#include "errno.h"
#ifndef NULL
/* ANSI C */
#include "stddef.h"
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#ifdef MSDOS
#ifndef NON_UNIX_STDIO
#define NON_UNIX_STDIO
#endif
#endif

#ifdef UIOLEN_int
typedef int uiolen;
#else
typedef long uiolen;
#endif

/*units*/
typedef struct
{	FILE *ufd;	/*0=unconnected*/
	char *ufnm;
#ifndef MSDOS
	long uinode;
	int udev;
#endif
	int url;	/*0=sequential*/
	flag useek;	/*true=can backspace, use dir, ...*/
	flag ufmt;
	flag urw;	/* (1 for can read) | (2 for can write) */
	flag ublnk;
	flag uend;
	flag uwrt;	/*last io was write*/
	flag uscrtch;
} unit;

extern flag f__init;
extern cilist *f__elist;	/*active external io list*/
extern flag f__reading,f__external,f__sequential,f__formatted;
#undef Void
#ifdef KR_headers
#define Void /*void*/
extern int (*f__getn)();	/* for formatted input */
extern void (*f__putn)();	/* for formatted output */
extern void x_putc();
extern long f__inode();
extern VOID sig_die();
extern int (*f__donewrec)(), t_putc(), x_wSL();
extern int c_sfe(), err__fl(), xrd_SL(), f__putbuf();
#else
#define Void void
#ifdef __cplusplus
extern "C" {
#endif
extern int (*f__getn)(void);	/* for formatted input */
extern void (*f__putn)(int);	/* for formatted output */
extern void x_putc(int);
extern long f__inode(char*,int*);
extern void sig_die(char*,int);
extern void f__fatal(int,char*);
extern int t_runc(alist*);
extern int f__nowreading(unit*), f__nowwriting(unit*);
extern int fk_open(int,int,ftnint);
extern int en_fio(void);
extern void f_init(void);
extern int (*f__donewrec)(void), t_putc(int), x_wSL(void);
extern void b_char(char*,char*,ftnlen), g_char(char*,ftnlen,char*);
extern int c_sfe(cilist*), z_rnew(void);
extern int isatty(int);
extern int err__fl(int,int,char*);
extern int xrd_SL(void);
extern int f__putbuf(int);
#ifdef __cplusplus
	}
#endif
#endif
extern int (*f__doend)(Void);
extern FILE *f__cf;	/*current file*/
extern unit *f__curunit;	/*current unit*/
extern unit f__units[];
#define err(f,m,s) {if(f) errno= m; else f__fatal(m,s); return(m);}
#define errfl(f,m,s) return err__fl((int)f,m,s)

/*Table sizes*/
#define MXUNIT 100

extern int f__recpos;	/*position in current record*/
extern int f__cursor;	/* offset to move to */
extern int f__hiwater;	/* so TL doesn't confuse us */

#define WRITE	1
#define READ	2
#define SEQ	3
#define DIR	4
#define FMT	5
#define UNF	6
#define EXT	7
#define INT	8

#define buf_end(x) (x->_flag & _IONBF ? x->_ptr : x->_base + BUFSIZ)
