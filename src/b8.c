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

/* b8.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/
#include <stdio.h>
#include "cmc_f2c.h"
#include "f2c.h"
#include "structures.h"



/* ***************************************************************** TOELE */

/*<       SUBROUTINE TOELE >*/
/* Subroutine */ int toele_(void)
{
extern FILE *fp12, *fp21;
char buf[1024];
FILE *fp4, *fp2;
int pos;
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static integer link, i__, l, k;
    static char fname[11];
    static integer iyend, lform[10];
    static real row[750]	/* was [75][10] */;


#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
#define row_ref(a_1,a_2) row[(a_2)*75 + a_1 - 76]



/* ***** SEND FUEL PRICES TO ELECTRIC MODULE. */
/*<       DIMENSION ROW(75,10),LFORM(10) >*/
/*<       COMMON/EL1/LWRIT(75),ITELF(75),ITELL(75),IECHO,IEECH,IFINL >*/
/*<    >*/
/*<    >*/
/*<       CHARACTER*11   FNAME >*/

/* ***** ROW IS THE MATRIC OF FUEL PRICES.  ROWS ARE THE YEARS AND */
/* ***** COLUMNS ARE THE FUELS.  ZERO IT INITIALLY. */

/*<       DO 10 K=1,10 >*/
    for (k = 1; k <= 10; ++k) {
/*<       DO 11 I=1,30 >*/
	for (i__ = 1; i__ <= 30; ++i__) {
/*<       ROW(I,K)=0.0 >*/
	    row_ref(i__, k) = 0.f;
/*<    11 CONTINUE >*/
/* L11: */
	}
/*<    10 CONTINUE >*/
/* L10: */
    }

/* ***** GET LINK NUMBERS FOR FUELS FROM BALANCE FORM INPUT. */

/* CMC       OPEN(4,FILE='FINKS.DAT',STATUS='OLD')                             MJ060686 */
/* CMC       IF(IECHO.EQ.0)WRITE(12,1989) */
/* CMC  1989 FORMAT(//,' FILE: FINKS.DAT ; ELECTRIC FUEL LINKS',               MJ060686 */
/* CMC      1' READ BY TOELE:') */
/* CMC       READ(4,190)(LFORM(L),L=1,10) */
/* CMC          IF(IECHO.EQ.0)WRITE(12,1910)(LFORM(L),L=1,10) */
/* CMC  190  FORMAT(I3) */
/* CMC  1910 FORMAT(1X,I3) */
/* CMC       CLOSE (4) */

  
  if((fp4=fopen("./finks.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open FINKS.DAT\n");
    exit(0);
  }
    if (el1_1.iecho == 0) 
      fprintf(fp12, "\n\n  FILE: FINKS.DAT ; ELECTRIC FUEL LINKS READ BY TOELE:\n");

    for (l = 1; l <= 10; ++l) {
      fgets(buf, sizeof(buf), fp4);pos=0;
      lform[l - 1]= atoi( substring(buf,pos,3));pos+=3;
    }

    if (el1_1.iecho == 0) 
      for (l = 1; l <= 10; ++l) 
	fprintf(fp12, " %3d\n", lform[l - 1]);

    fclose(fp4);

/* ***** LOAD THE PRICES ON THESE LINKS AS STORED IN ZEN INTO THE */
/* ***** ROW MATRIX. */

/*<       DO 12 K=1,10 >*/
    for (k = 1; k <= 10; ++k) {
/*<       LINK=LFORM(K) >*/
	link = lform[k - 1];
/*<       IF(LINK.EQ.0)GO TO 12 >*/
	if (link == 0) {
	    goto L12;
	}

/* ***** COMPUTE FUEL PRICES FROM LOCAL CURRENCY/BOE TO */
/* ***** U.S. CENTS/10**6 KILOCALORIE. */

/*<       DO 13 I=1,NPER >*/
	i__1 = var_1.nper;
	for (i__ = 1; i__ <= i__1; ++i__) {
/*<       ROW(I,K)=ZEN(2,LINK,I)/PSCALE*(100./1.37) >*/
	    row_ref(i__, k) = zen_ref(2, link, i__) / pri_1.pscale * 
		    72.992700729926995f;
/*<    13 CONTINUE >*/
/* L13: */
	}
/*<    12 CONTINUE >*/
L12:
	;
    }

/* CMC C***** WRITE TO FILE TO BE READ BY ELECTRIC. */

/*<       IYEND=IYRB+NPER-1 >*/
    iyend = var_1.iyrb + var_1.nper - 1;
/*<       FNAME='TOELEC.DAT' >*/
    s_copy(fname, "TOELEC.DAT", (ftnlen)11, (ftnlen)10);
/* CMC       OPEN (2, FILE=FNAME,STATUS='UNKNOWN') */
/* CMC       WRITE(2,719)IYRB,NPER */
/* CMC   719 FORMAT(5X,2I5) */

    if((fp2=fopen("./toelec.dat", "w"))==NULL){
      fprintf(fp21, "Error: Couldnt open TOELEC.DAT\n");
      exit(0);
    }
    fprintf(fp2, "  %5d%5d\n", var_1.iyrb, var_1.nper);

/*<       DO 14 I=1,NPER >*/
    i__1 = var_1.nper;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* CMC       WRITE(2,720)(ROW(I,K),K=1,10) */
/* CMC   720 FORMAT(5X,10F7.1)                                                 MJ060986 */
      fprintf(fp2, "     ");
      for (k = 1; k <= 10; ++k) 
	fprintf(fp2, "%7.1f", row_ref(i__, k));
      fprintf(fp2, "\n");
      
      
/*<    14 CONTINUE >*/
/* L14: */
    }
/* CMC       CLOSE(2) */
    fclose(fp2);

/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* toele_ */

#undef row_ref
#undef zen_ref



/* ***************************************************************** TOLOD */

/*<       SUBROUTINE TOLOD >*/
/* Subroutine */ int tolod_(void)
{
FILE *fp2, *fp21;
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static integer last;
    static char fname[12];
    static integer iy;


/*<       COMMON/NET/Q(999),P(999),CAPL(999),LAB(5),IUSE(300),LUSE(999) >*/
/*<       COMMON/TOLOAD/AGENR(75),ALOAD(75),IOUEL >*/
/*<    >*/
/*<       CHARACTER*12   FNAME >*/
/*<       INTEGER        LAST >*/


/* CMC C***** WRITE AGENR AND ALOAD TO A FILE READABLE BY LOAD MODULE. */


/*<       FNAME='LAGLF.DAT' >*/
    s_copy(fname, "LAGLF.DAT", (ftnlen)12, (ftnlen)9);
/* CMC       OPEN(2,FILE=FNAME,STATUS='UNKNOWN') */

  if((fp2=fopen("./laglf.dat", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open LAGLF.DAT\n");
    exit(0);
  }

/*     ************************************************************* */

/*<       LAST = (IYRB + NPER) - 1 >*/
    last = var_1.iyrb + var_1.nper - 1;
/* CMC       WRITE(2,22)IYRB */
/* CMC       WRITE(2,22)LAST */

    fprintf(fp2, " %5d\n", var_1.iyrb );
    fprintf(fp2, " %5d\n", last);


/*<       DO 24 IY=1,NPER >*/
    i__1 = var_1.nper;
    for (iy = 1; iy <= i__1; ++iy) {
/* CMC          WRITE(2,26)AGENR(IY) */
   fprintf(fp2, " %10.2f\n", toload_1.agenr[iy - 1]);

/*<    24 CONTINUE >*/
/* L24: */
    }
/*<       DO 25 IY=1,NPER >*/
    i__1 = var_1.nper;
    for (iy = 1; iy <= i__1; ++iy) {
/* CMC          WRITE(2,27)ALOAD(IY) */
   fprintf(fp2, " %10.6f\n", toload_1.aload[iy - 1]);

/*<    25 CONTINUE >*/
/* L25: */
    }
/* CMC       CLOSE(2) */
fclose(fp2);

/* CMC    22 FORMAT(1X,I5) */
/* CMC    26 FORMAT(1X,F10.2) */
/* CMC    27 FORMAT(1X,F10.6)                                                  MJ060986 */

/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* tolod_ */

