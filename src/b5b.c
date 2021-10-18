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

/* b5b.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"
#include "structures.h"


/* *************************************************************** INPUT2 */

/*<       SUBROUTINE INPUT2 >*/
/* Subroutine */ int input2_(void)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer k;


#define iinre_ref(a_1,a_2) ref_1.iinre[(a_2)*30 + a_1 - 31]

/*<    >*/
/*<    >*/
/*<       COMMON/NET/Q(999),P(999),CAPL(999),LAB(5),IUSE(300),LUSE(999) >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<       COMMON/PRI2/LINKP(100) >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<       COMMON/EL1/LWRIT(75),ITELF(75),ITELL(75),IECHO,IEECH,IFINL >*/
/*<       COMMON/AL1/NGG(200) >*/
/*<    >*/
/*<       COMMON/MODE/IRESON,ILOD,IELE,IMP,BOEMWH,BOEMBTU >*/

/*<       CHARACTER*4 NODEL >*/
/*<       CHARACTER*4  LBL,LWR,LAL,LPR,LMI,LRE,LEL,LPP,LDE,LRS,LRN >*/
/*<       CHARACTER*4 LCAPL,LPRI,LOM,LEFF,LTCI,LCAPM,LCF,LLIFE,LIR >*/
/*<       CHARACTER*4 LIO,LSLAT,LPFF,LPRAT,LSTOC,LEXCS,LCNTL,LREMU >*/
/*<       CHARACTER*4 LALPH,LDELT,LPMAX,LPMIN,LLINP,LSIZE,LCA,LITM,LPAB >*/

/* ***** INITIALIZE CAPL TO BE UNCAPACITATED. */

/*<       DO 370 K=1,LNKMX >*/
    i__1 = var_1.lnkmx;
    for (k = 1; k <= i__1; ++k) {
/*<       LUSE(K)=0 >*/
	net_1.luse[k - 1] = 0;
/*<       CAPL(K)=1.0E+12 >*/
	net_1.capl[k - 1] = 1e12f;
/*<       Q(K)=0.0 >*/
	net_1.q[k - 1] = 0.f;
/*<       P(K)=0.0 >*/
	net_1.p[k - 1] = 0.f;
/*<   370 CONTINUE >*/
/* L370: */
    }


/* ***** FILL DEPLETABLE RESOURCE PROCESS OUTPUT LINK VECTOR. */

/*<       DO 350 K=1,NRSMX >*/
    i__1 = var_1.nrsmx;
    for (k = 1; k <= i__1; ++k) {
/*<       IOURS(K)=0 >*/
	res_1.iours[k - 1] = 0;
/*<   350 CONTINUE >*/
/* L350: */
    }
/* ***** FILL RENEWABLE RESOURCE PROCESS OUTPUT LINK VECTOR. */

/*<       DO 1499 K=1,NRNMX >*/
    i__1 = var_1.nrnmx;
    for (k = 1; k <= i__1; ++k) {
/*<       IOURN(K)=0 >*/
	ren_1.iourn[k - 1] = 0;
/*<  1499 CONTINUE >*/
/* L1499: */
    }

/* ***** FILL CONVERSION LINK VECTOR */

/*<       DO 551 K=1,NPRMX >*/
    i__1 = var_1.nprmx;
    for (k = 1; k <= i__1; ++k) {
/*<         IOUPR(K)=0 >*/
	pro_1.ioupr[k - 1] = 0;
/*<   551 CONTINUE >*/
/* L551: */
    }

/* ***** FILL MULTIPLE INPUT LINK VECTOR */

/*<       DO 552 K=1,NMIMX >*/
    i__1 = min_1.nmimx;
    for (k = 1; k <= i__1; ++k) {
/*<         IOUMI(K)=0                                                       >*/
	min_1.ioumi[k - 1] = 0;
/*<   552 CONTINUE >*/
/* L552: */
    }

/* ***** FILL REFINERY LINK VECTOR */

/*<       DO 553 K=1,NREMX >*/
    i__1 = min_1.nremx;
    for (k = 1; k <= i__1; ++k) {
/*<         IINRE(K,1)=0 >*/
	iinre_ref(k, 1) = 0;
/*<   553 CONTINUE >*/
/* L553: */
    }

/* ***** FILL DEMAND PROCESS INPUT LINK VECTOR */

/*<       DO 550 K=1,NDEMX >*/
    i__1 = dem_1.ndemx;
    for (k = 1; k <= i__1; ++k) {
/*<       IINDE(K)=0 >*/
	dem_1.iinde[k - 1] = 0;
/*<   550 CONTINUE >*/
/* L550: */
    }
/*<       RETURN >*/
    return 0;

/*<       END >*/
} /* input2_ */

#undef iinre_ref


