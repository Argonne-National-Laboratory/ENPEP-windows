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

/* STARTUP PROCEDURE FOR UNIX FORTRAN PROGRAMS */

#include "stdio.h"
#include "signal1.h"

#ifndef SIGIOT
#ifdef SIGABRT
#define SIGIOT SIGABRT
#endif
#endif

#ifndef KR_headers
#undef VOID
#include "stdlib.h"
#endif

#ifndef VOID
#define VOID void
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NO__STDC
#define ONEXIT onexit
extern VOID f_exit();
#else
#ifndef KR_headers
extern void f_exit(void);
#ifndef NO_ONEXIT
#define ONEXIT atexit
extern int atexit(void (*)(void));
#endif
#else
#ifndef NO_ONEXIT
#define ONEXIT onexit
extern VOID f_exit();
#endif
#endif
#endif

#ifdef KR_headers
extern VOID f_init(), sig_die();
extern int MAIN__();
#define Int /* int */
#else
extern void f_init(void), sig_die(char*, int);
extern int MAIN__(void);
#define Int int
#endif

static VOID sigfdie(Sigarg)
{
Use_Sigarg;
sig_die("Floating Exception", 1);
}


static VOID sigidie(Sigarg)
{
Use_Sigarg;
sig_die("IOT Trap", 1);
}

#ifdef SIGQUIT
static VOID sigqdie(Sigarg)
{
Use_Sigarg;
sig_die("Quit signal", 1);
}
#endif


static VOID sigindie(Sigarg)
{
Use_Sigarg;
sig_die("Interrupt", 0);
}

static VOID sigtdie(Sigarg)
{
Use_Sigarg;
sig_die("Killed", 0);
}

#ifdef SIGTRAP
static VOID sigtrdie(Sigarg)
{
Use_Sigarg;
sig_die("Trace trap", 1);
}
#endif


int xargc;
char **xargv;
FILE *fp21;

#ifdef __cplusplus
	}
#endif

/* #ifdef KR_headers
main(argc, argv) int argc; char **argv;
#else */
main(int argc, char **argv)
// #endif
{ 
extern FILE *fp21;
xargc = argc;
xargv = argv;

  if(xargc !=2){
	  fprintf(stderr, "Please Supply Right Number of Arguments\n");
	  exit(0);
  }

  if((fp21 = fopen(xargv[1], "w"))==NULL){
    fprintf(stderr, "Couldnt open %s\n",xargv[1]);
    exit(0);
  }


signal1(SIGFPE, sigfdie);	/* ignore underflow, enable overflow */
#ifdef SIGIOT
signal1(SIGIOT, sigidie);
#endif
#ifdef SIGTRAP
signal1(SIGTRAP, sigtrdie);
#endif
#ifdef SIGQUIT
if(signal1(SIGQUIT,sigqdie) == SIG_IGN)
	signal1(SIGQUIT, SIG_IGN);
#endif
if(signal1(SIGINT, sigindie) == SIG_IGN)
	signal1(SIGINT, SIG_IGN);
signal1(SIGTERM,sigtdie);

#ifdef pdp11
	ldfps(01200); /* detect overflow as an exception */
#endif

f_init();
#ifndef NO_ONEXIT
ONEXIT(f_exit);
#endif
MAIN__();
#ifdef NO_ONEXIT
f_exit();
#endif
exit(0);	/* exit(0) rather than return(0) to bypass Cray bug */
return 0;	/* For compilers that complain of missing return values; */
		/* others will complain that this is unreachable code. */
}
