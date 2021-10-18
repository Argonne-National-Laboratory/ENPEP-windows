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

/* ba.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/
#include <stdio.h>
#include "cmc_f2c.h"
#include "f2c.h"
#include "structures.h"


/* ******************************************************************* USE */

/*<       SUBROUTINE USE(ICODE,NL) >*/
/* Subroutine */ int use_(integer *icode, integer *nl)
{
    /* System generated locals */
extern FILE *fp12;
    integer i__1;

    /* Local variables */
    static integer i__;

/*<       COMMON/EL1/LWRIT(75),ITELF(75),ITELL(75),IECHO,IEECH,IFINL >*/
/*<       COMMON/NET/Q(999),P(999),CAPL(999),LAB(5),IUSE(300),LUSE(999) >*/
/*<    >*/
/*<       IF(ICODE.GT.1)GO TO 100 >*/
    if (*icode > 1) {
	goto L100;
    }
/*<       DO 10 I=1,NL >*/
    i__1 = *nl;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       IUSE(I)=0 >*/
	net_1.iuse[i__ - 1] = 0;
/*<    10 CONTINUE >*/
/* L10: */
    }
/*<       RETURN >*/
    return 0;

/*<   100 CONTINUE >*/
L100:
/* CMC   100 IF(IECHO.EQ.0)WRITE(12,101)NL */
/* CMC   101 FORMAT(//,2X,'++++++++++  ',2X,'MAX=',I10,/,2X,'AVAILABLE:') */
    if (el1_1.iecho == 0) 
      fprintf(fp12, "\n\n  ++++++++++    MAX=%10d\n  AVAILABLE:\n", *nl);


/*<       DO 12 I=1,NL >*/
    i__1 = *nl;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       IF(IUSE(I).EQ.1)GO TO 12 >*/
	if (net_1.iuse[i__ - 1] == 1) {
	    goto L12;
	}
	if (el1_1.iecho == 0) 
	  fprintf(fp12, "     %10d\n", i__);
/* CMC       IF(IECHO.EQ.0)WRITE(12,20)I */
/* CMC    20 FORMAT(5X,I10) */
/*<    12 CONTINUE >*/
L12:
	;
    }

	if (el1_1.iecho == 0) 
	  fprintf(fp12, "\n\n\n");
/* CMC       IF(IECHO.EQ.0)WRITE(12,25) */
/* CMC    25 FORMAT(///) */
/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* use_ */


/* ***************************************************************** VISIT */

/*<       SUBROUTINE VISIT(IPASS) >*/
/* Subroutine */ int visit_(integer *ipass)
{
extern FILE *fp6, *fp11;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];

int ct;
FILE *fpidisk;
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_cmp(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static char llab[5];
    static integer klim, k;
    extern /* Subroutine */ int elecs_(integer *);
    static integer idisk, kspec;
    extern /* Subroutine */ int de_(integer *, integer *, integer *), al_(
	    integer *, integer *, integer *), mi_(integer *, integer *, 
	    integer *), re_(integer *, integer *, integer *), pp_(integer *, 
	    integer *, integer *), rn_(integer *, integer *, integer *), pr_(
	    integer *, integer *, integer *), rs_(integer *, integer *, 
	    integer *);
    static char lde[4], lal[4], lbl[4], lel[4], lmi[4], lre[4], lpp[4], lpr[4]
	    , lrn[4], lrs[4];
    static integer num, kwr;
    static char lwr[4];
#define labw_ref(a_1,a_2,a_3) invis_1.labw[((a_3)*100 + (a_2))*2 + a_1 - \
203]

#define numb_ref(a_1,a_2) invis_1.numb[(a_2)*2 + a_1 - 3]

#define ispec_ref(a_1,a_2) invis_1.ispec[(a_2)*2 + a_1 - 3]

/*<    >*/
/*<    >*/
/*<    >*/

/*<       CHARACTER*4 NODEL >*/
/*<       CHARACTER*4 LBL,LWR,LAL,LPR,LMI,LRE,LEL,LPP,LDE,LRS,LRN,LLAB >*/
/*<       LBL='    ' >*/
    s_copy(lbl, "  ", (ftnlen)4, (ftnlen)4);

/*<       LWR='WR  ' >*/
    s_copy(lwr, "WR  ", (ftnlen)4, (ftnlen)4);
    /* strcpy(lwr, "WR");*/

/*<       LAL='AL  ' >*/
    s_copy(lal, "AL  ", (ftnlen)4, (ftnlen)4);
/*<       LPR='PR  ' >*/
    s_copy(lpr, "PR  ", (ftnlen)4, (ftnlen)4);
/*<       LMI='MI  ' >*/
/*    s_copy(lmi, "MI  ", (ftnlen)4, (ftnlen)4); */
	s_copy(lmi, "MI  ", (ftnlen)4, (ftnlen)4);
/*<       LRE='RE  ' >*/
    s_copy(lre, "RE  ", (ftnlen)4, (ftnlen)4);
/*<       LEL='EL  ' >*/
    s_copy(lel, "EL  ", (ftnlen)4, (ftnlen)4);
/*<       LPP='PP  ' >*/
    s_copy(lpp, "PP  ", (ftnlen)4, (ftnlen)4);
/*<       LDE='DE  ' >*/
    s_copy(lde, "DE  ", (ftnlen)4, (ftnlen)4);
/*<       LRS='RS  ' >*/
    s_copy(lrs, "RS  ", (ftnlen)4, (ftnlen)4);
/*<       LRN='RN  ' >*/
    s_copy(lrn, "RN  ", (ftnlen)4, (ftnlen)4);

/*<       KWR=0 >*/
    kwr = 0;

/* ***** GENERALLY OUTPUT GOES TO UNIT 6 FOR THE ITERATION P AND Q */
/* ***** SUMMARY.  IF IPASS = 6 OR 7 OUTPUT CONSISTS OF ZEN DUMP */
/* ***** FOR P AND Q ON ALL LINKS OVER ALL YEARS. */

/*<       IDISK=6 >*/
    idisk = 6;
   fpidisk = fp6;
/*<       IF(IPASS.GE.6)IDISK=11 >*/
    if (*ipass >= 6) {
	idisk = 11;
    fpidisk = fp11;
    }


/* ***** IPASS CODE, CALL SOURCE(TIMES), EXPLAN. */
/*           1  MAIN(1)    UP-PASS P CALC */
/*           2  MAIN(1)    DOWN-PASS Q CALC */
/*           3  MAIN(1)    Q ADJUSTMENT FOR ALL DEPLETABLE AND */
/*                          RENEWABLE RESOURCE PROCESSES (ONCE PER */
/*                          YEAR POST-CONVERG) */
/*           4  MAIN(1)    COMPUTE CASH FLOW SUMMARY FOR SELECTED */
/*                          PROCESSES - NOT USED (ONCE PER YEAR */
/*                          POST CONVERGENCE). */
/*           5  MAIN(1)    RECORD P AND Q LINK INFORMATION IN ZEN */
/*                          (ONCE PER YEAR POST CONVERG) */
/*           6  MAIN(1)    DUMP Q ON ALL LINKS AND YEARS FORM ZEN */
/*                          (ONCE AT END OF LAST YEAR). */
/*           7  MAIN(1)    DUMP P ON ALL LINKS AND YEARS FROM ZEN */
/*                          (ONCE AT END OF LAST YEAR). */


/*<       GO TO(100,200,300,400,100,100,100),IPASS >*/
    switch (*ipass) {
	case 1:  goto L100;
	case 2:  goto L200;
	case 3:  goto L300;
	case 4:  goto L400;
	case 5:  goto L100;
	case 6:  goto L100;
	case 7:  goto L100;
    }

/* ***** UP-PASS: */

/*<   100 CONTINUE >*/
L100:

/*<       DO 10 K=1,KUP >*/
    i__1 = invis_1.kup;
    for (k = 1; k <= i__1; ++k) {
/*<       LLAB=NODEL(1,K) >*/
	s_copy(llab, invis_1.nodel[1][k], (ftnlen)4, (ftnlen)4);
/*<       NUM=NUMB(1,K) >*/
	num = numb_ref(1, k);
/*<       KSPEC=ISPEC(1,K) >*/
	kspec = ispec_ref(1, k);
/*<       IF(LLAB.NE.LAL)GO TO 11 >*/
	if (s_cmp(llab, lal, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L11;
	}
/*<       CALL AL(IPASS,NUM,KSPEC) >*/
	al_(ipass, &num, &kspec);
/*<       GO TO 10 >*/
	goto L10;

/*<    11 IF(LLAB.NE.LPR)GO TO 12 >*/
L11:
	if (s_cmp(llab, lpr, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L12;
	}
/*<       CALL PR(IPASS,NUM,KSPEC) >*/
	pr_(ipass, &num, &kspec);
/*<       GO TO 10 >*/
	goto L10;

/*<    12 IF(LLAB.NE.LMI)GO TO 13 >*/
L12:
	if (s_cmp(llab, lmi, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L13;
	}
/*<       CALL MI(IPASS,NUM,KSPEC) >*/
	mi_(ipass, &num, &kspec);
/*<       GO TO 10 >*/
	goto L10;
/*<    13 IF(LLAB.NE.LRE)GO TO 14 >*/
L13:
	if (s_cmp(llab, lre, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L14;
	}
/*<       CALL RE(IPASS,NUM,KSPEC) >*/
	re_(ipass, &num, &kspec);
/*<       GO TO 10 >*/
	goto L10;

/*<    14 IF(LLAB.NE.LEL)GO TO 15 >*/
L14:
	if (s_cmp(llab, lel, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L15;
	}
/*<       IF(IELECS.EQ.0)GO TO 15 >*/
	if (invis_1.ielecs == 0) {
	    goto L15;
	}
/*<       CALL ELECS(IPASS) >*/
	elecs_(ipass);
/*<       GO TO 10 >*/
	goto L10;

/*<    15 IF(LLAB.NE.LPP)GO TO 16 >*/
L15:
	if (s_cmp(llab, lpp, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L16;
	}
/*<       CALL PP(IPASS,NUM,KSPEC) >*/
	pp_(ipass, &num, &kspec);
/*<       GO TO 10 >*/
	goto L10;

/*<    16 IF(LLAB.NE.LDE)GO TO 17 >*/
L16:
	if (s_cmp(llab, lde, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L17;
	}
/*<       CALL DE(IPASS,NUM,KSPEC) >*/
	de_(ipass, &num, &kspec);
/*<       GO TO 10 >*/
	goto L10;

/*<    17 IF(LLAB.NE.LWR)GO TO 18 >*/
L17:
	/*if (strcmp(llab, lwr) != 0) {*/
	if (s_cmp(llab, lwr, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L18;
	}

/*<       IF(IPASS.GT.3)GO TO 10 >*/
	if (*ipass > 3) {
	    goto L10;
	}
/*<       KWR=KWR+1 >*/
	++kwr;
/* CMC       IF(IWR1.GE.1.OR.IDISK.EQ.11)WRITE(IDISK,180)(LABW(1,KWR,J),J=1,5) */
/* CMC   180 FORMAT(/,2X,5A4) */
/*<       GO TO 10 >*/
	if (var_1.iwr1 >= 1 || idisk == 11) {
	  fprintf(fpidisk, "\n  ");
	  for(ct=1; ct<=5; ct++)
	    fprintf(fpidisk, "%4d", labw_ref(1, kwr, ct));
	  fprintf(fpidisk, "\n");
	}
	goto L10;

/*<    18 IF(LLAB.NE.LRS)GO TO 19 >*/
L18:
	if (s_cmp(llab, lrs, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L19;
	}
/*<       CALL RS(IPASS,NUM,KSPEC) >*/
	rs_(ipass, &num, &kspec);
/*<       GO TO 10 >*/
	goto L10;

/*<    19 IF(LLAB.NE.LRN)GO TO 10 >*/
L19:
	if (s_cmp(llab, lrn, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L10;
	}
/*<       CALL RN(IPASS,NUM,KSPEC) >*/
	rn_(ipass, &num, &kspec);
/*<       GO TO 10 >*/
	goto L10;

/*<    10 CONTINUE >*/
L10:
	;
    }

/*<       RETURN >*/
    return 0;

/* ***** DOWNPASS NEXT: */

/*<   200 CONTINUE >*/
L200:

/*<       DO 20 K=1,KDWN >*/
    i__1 = invis_1.kdwn;
    for (k = 1; k <= i__1; ++k) {
/*<       LLAB=NODEL(2,K) >*/
	s_copy(llab, invis_1.nodel[2][k], (ftnlen)4, (ftnlen)4);
/*<       NUM=NUMB(2,K) >*/
	num = numb_ref(2, k);
/*<       KSPEC=ISPEC(2,K) >*/
	kspec = ispec_ref(2, k);

/*<       IF(LLAB.NE.LAL)GO TO 21 >*/
	if (s_cmp(llab, lal, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L21;
	}
/*<       CALL AL(IPASS,NUM,KSPEC) >*/
	al_(ipass, &num, &kspec);
/*<       GO TO 20 >*/
	goto L20;

/*<    21 IF(LLAB.NE.LPR)GO TO 22 >*/
L21:
	if (s_cmp(llab, lpr, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L22;
	}
/*<       CALL PR(IPASS,NUM,KSPEC) >*/
	pr_(ipass, &num, &kspec);
/*<       GO TO 20 >*/
	goto L20;

/*<    22 IF(LLAB.NE.LMI)GO TO 23 >*/
L22:
	if (s_cmp(llab, lmi, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L23;
	}
/*<       CALL MI(IPASS,NUM,KSPEC) >*/
	mi_(ipass, &num, &kspec);
/*<       GO TO 20 >*/
	goto L20;
/*<    23 IF(LLAB.NE.LRE)GO TO 24 >*/
L23:
	if (s_cmp(llab, lre, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L24;
	}
/*<       CALL RE(IPASS,NUM,KSPEC) >*/
	re_(ipass, &num, &kspec);
/*<       GO TO 20 >*/
	goto L20;

/*<    24 IF(LLAB.NE.LEL)GO TO 25 >*/
L24:
	if (s_cmp(llab, lel, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L25;
	}
/*<       IF(IELECS.EQ.0)GO TO 25 >*/
	if (invis_1.ielecs == 0) {
	    goto L25;
	}
/*<       CALL ELECS(IPASS) >*/
	elecs_(ipass);
/*<       GO TO 20 >*/
	goto L20;

/*<    25 IF(LLAB.NE.LPP)GO TO 26 >*/
L25:
	if (s_cmp(llab, lpp, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L26;
	}
/*<       CALL PP(IPASS,NUM,KSPEC) >*/
	pp_(ipass, &num, &kspec);
/*<       GO TO 20 >*/
	goto L20;

/*<    26 IF(LLAB.NE.LDE)GO TO 27 >*/
L26:
	if (s_cmp(llab, lde, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L27;
	}
/*<       CALL DE(IPASS,NUM,KSPEC) >*/
	de_(ipass, &num, &kspec);
/*<       GO TO 20 >*/
	goto L20;

/*<    27 IF(LLAB.NE.LWR)GO TO 28 >*/
L27:
	/*if (strcmp(llab, lwr) != 0) {*/
	if (s_cmp(llab, lwr, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L28;
	}
/*<       KWR=KWR+1 >*/
	++kwr;
/* CMC       IF(IWR1.GE.1.OR.IDISK.EQ.11)WRITE(IDISK,180)(LABW(2,KWR,J),J=1,5) */
/*<       GO TO 20 >*/
	if (var_1.iwr1 >= 1 || idisk == 11) {
	  fprintf(fpidisk, "\n  ");
	  for(ct=1; ct<=5; ct++)
	    fprintf(fpidisk, "%4d", labw_ref(2, kwr, ct));
	  fprintf(fpidisk, "\n");
	}
	goto L20;

/*<    28 IF(LLAB.NE.LRS)GO TO 29 >*/
L28:
	if (s_cmp(llab, lrs, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L29;
	}
/*<       CALL RS(IPASS,NUM,KSPEC) >*/
	rs_(ipass, &num, &kspec);
/*<       GO TO 20 >*/
	goto L20;

/*<    29 IF(LLAB.NE.LRN)GO TO 20 >*/
L29:
	if (s_cmp(llab, lrn, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L20;
	}
/*<       CALL RN(IPASS,NUM,KSPEC) >*/
	rn_(ipass, &num, &kspec);
/*<       GO TO 20 >*/
	goto L20;

/*<    20 CONTINUE >*/
L20:
	;
    }

/*<       RETURN >*/
    return 0;

/* ***** RESOURCES */

/*<   300 CONTINUE >*/
L300:

/*<       KLIM=NRSMX+NRNMX+10 >*/
    klim = var_1.nrsmx + var_1.nrnmx + 10;

/*<       DO 30 K=1,KLIM >*/
    i__1 = klim;
    for (k = 1; k <= i__1; ++k) {
/*<       LLAB=NODEL(1,K) >*/
	s_copy(llab, invis_1.nodel[1][k], (ftnlen)4, (ftnlen)4);
/*<       NUM=NUMB(1,K) >*/
	num = numb_ref(1, k);
/*<       KSPEC=ISPEC(1,K) >*/
	kspec = ispec_ref(1, k);

/*<       IF(LLAB.NE.LWR)GO TO 38 >*/
	/*if (strcmp(llab, lwr) != 0) {*/
	if (s_cmp(llab, lwr, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L38;
	}
/*<       KWR=KWR+1 >*/
	++kwr;
/* CMC       IF(IWR1.GE.1.OR.IDISK.EQ.11)WRITE(IDISK,180)(LABW(1,KWR,J),J=1,5) */
/*<       GO TO 30 >*/
	if (var_1.iwr1 >= 1 || idisk == 11) {
	  fprintf(fpidisk, "\n  ");
	  for(ct=1; ct<=5; ct++)
	    fprintf(fpidisk, "%4d", labw_ref(1, kwr, ct));
	  fprintf(fpidisk, "\n");
	}
	goto L30;

/*<    38 IF(LLAB.NE.LRS)GO TO 39 >*/
L38:
	if (s_cmp(llab, lrs, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L39;
	}
/*<       CALL RS(IPASS,NUM,KSPEC) >*/
	rs_(ipass, &num, &kspec);
/*<       GO TO 30 >*/
	goto L30;

/*<    39 IF(LLAB.NE.LRN)GO TO 30 >*/
L39:
	if (s_cmp(llab, lrn, (ftnlen)4, (ftnlen)4) != 0) {
	    goto L30;
	}
/*<       CALL RN(IPASS,NUM,KSPEC) >*/
	rn_(ipass, &num, &kspec);
/*<       GO TO 30 >*/
	goto L30;

/*<    30 CONTINUE >*/
L30:
	;
    }
/*<       RETURN >*/
    return 0;

/* ***** COST ANALYSIS */

/*<   400 CONTINUE >*/
L400:

/* ***** THIS SECTION WAS USED FOR CALLING COST AT THE END OF EACH */
/* ***** YEAR. */

/* *    CALL CASH(3,1) */

/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* visit_ */

#undef labw_ref
#undef ispec_ref
#undef numb_ref


