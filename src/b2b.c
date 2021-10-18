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

/* b2b.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/
#include <stdio.h>
#include "cmc_f2c.h"
#include <stdlib.h>
#include "f2c.h"
#include "structures.h"



/* *******************************************************************CASH */

/*<       SUBROUTINE CASH(IOPT,IPR) >*/
/* Subroutine */ int cash_(integer *iopt, integer *ipr)
{
  extern FILE *fp10;
    /* System generated locals */
    integer i__1;
    real r__1, r__2;

    /* Builtin functions */
    double pow_ri(real *, integer *);

    /* Local variables */
    static real cost, sumi, sumo;
    static integer i__, j, k;
    static real pf, profit, cch, scc, crf;
    static integer nni;
    static real ror;
    static integer nno;
    static real qin, qou;


#define iinmi_ref(a_1,a_2) min_1.iinmi[(a_2)*200 + a_1 - 201]
#define iinre_ref(a_1,a_2) ref_1.iinre[(a_2)*30 + a_1 - 31]
#define ioure_ref(a_1,a_2) ref_1.ioure[(a_2)*30 + a_1 - 31]


/*<    >*/
/*<    >*/
/*<       COMMON/NET/Q(999),P(999),CAPL(999),LAB(5),IUSE(300),LUSE(999) >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/

/* **** COMPUTE RATE OF RETURN */

/*<       GO TO(100,200,300),IOPT >*/
    switch (*iopt) {
	case 1:  goto L100;
	case 2:  goto L200;
	case 3:  goto L300;
    }

/*<   100 CONTINUE >*/
L100:

/* **** CONVERSION PROCESS */

/* CMC       WRITE(10,122)IPR */
/* CMC   122 FORMAT(//,1X,130(1H*),/,2X,'CONVERSION PROCESS',I6) */
fprintf(fp10, "\n\n **********************************************************************************************************************************\n  CONVERSION PROCESS%6d\n",(*ipr) )
;
/*<       J=IINPR(IPR) >*/
    j = pro_1.iinpr[*ipr - 1];
/*<       K=IOUPR(IPR) >*/
    k = pro_1.ioupr[*ipr - 1];
/* CMC       WRITE(10,722)J,P(J),Q(J) */
fprintf(fp10, "\n  INPUT LINK %6d            P= %12.2f            Q= %12.2f\n",
j,net_1.p[j - 1], net_1.q[j - 1]);
/* CMC       WRITE(10,822)K,P(K),Q(K) */
fprintf(fp10, "\n  OUTOUT LINK%6d            P= %12.2f            Q= %12.2f\n",
k,net_1.p[k - 1], net_1.q[k - 1]);

/*<    >*/
    r__1 = pro_1.rir[*ipr - 1] + 1.f;
    r__2 = pro_1.rir[*ipr - 1] + 1.f;
    crf = pro_1.rir[*ipr - 1] * pow_ri(&r__1, &pro_1.life[*ipr - 1]) / (
	    pow_ri(&r__2, &pro_1.life[*ipr - 1]) - 1.f);
/*<       SCC=TCI(IPR)/(CAPM(IPR)*CF(IPR)) >*/
    scc = pro_1.tci[*ipr - 1] / (pro_1.capm[*ipr - 1] * pro_1.cf[*ipr - 1]);
/*<       CCH=TCI(IPR)*CRF >*/
    cch = pro_1.tci[*ipr - 1] * crf;
/*<       PF=0.0 >*/
    pf = 0.f;
/*<       COST=P(J)*Q(J)+OM(IPR)*Q(K)+CCH >*/
    cost = net_1.p[j - 1] * net_1.q[j - 1] + pro_1.om[*ipr - 1] * net_1.q[k - 
	    1] + cch;
/*<       PROFIT=P(K)*Q(K)-COST >*/
    profit = net_1.p[k - 1] * net_1.q[k - 1] - cost;
/*<       ROR=PROFIT/COST >*/
    ror = profit / cost;

/* CMC CHECK ON E */
/* CMC       WRITE(10,522)TCI(IPR),CAPM(IPR),CF(IPR), */
/* CMC      1 OM(IPR),LIFE(IPR),PF,RIR(IPR),CRF,CCH,PSCALE,PROFIT,ROR */
    fprintf(fp10, "\n  CAPITAL COST FOR FACILITY    ($)%12.4e",pro_1.tci[*ipr - 1]);
    fprintf(fp10, "\n  FAC MAX CAPACITY   (     /YR)   %12.4e",pro_1.capm[*ipr - 1]);
    fprintf(fp10, "\n  CAPACITY FACTOR  (FRACTION)     %12.2f",pro_1.cf[*ipr - 1]);
    fprintf(fp10, "\n  NONFUEL O&M COST ($/     )      %12.2f",pro_1.om[*ipr - 1]);
    fprintf(fp10, "\n  UNIT LIFE (YEARS)               %2d",pro_1.life[*ipr - 1]);
    fprintf(fp10, "\n  PROFIT FACTOR (FRACTION)        %12.4f",pf);
    fprintf(fp10, "\n  INTEREST RATE  (FRACTION)       %12.4f",pro_1.rir[*ipr - 1]);
    fprintf(fp10, "\n  CAPITAL RECOVERY FACTOR         %12.5f",crf);
    fprintf(fp10, "\n  CAPITAL CHARGE ($/YR)           %12.2f",cch);
    fprintf(fp10, "\n  PROFIT  (%6.0f$/YR)            %12.0f",pri_1.pscale, profit);
    fprintf(fp10, "\n  RETURN ON INVESTMENT  (FRACTION)%12.4f",ror);
/*<       RETURN >*/
    return 0;

/*<   200 CONTINUE >*/
L200:

/* **** MULTI-INPUT PROCESS */

/* CMC       WRITE(10,222)IPR */
/* CMC   222 FORMAT(//,1X,130(1H*),/,2X,'MULTI-INPUT PROCESS',I6) */
fprintf(fp10, "\n\n **********************************************************************************************************************************\n  MULTI-INPUT PROCESS%6d\n", (*ipr));

/*<       NNI=NINMI(IPR) >*/
    nni = min_1.ninmi[*ipr - 1];
/*<       K=IOUMI(IPR) >*/
    k = min_1.ioumi[*ipr - 1];
/*<       SUMI=0.0 >*/
    sumi = 0.f;
/*<       DO 210 I=1,NNI >*/
    i__1 = nni;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       J=IINMI(IPR,I) >*/
	j = iinmi_ref(*ipr, i__);
/* CMC       WRITE(10,722)J,P(J),Q(J) */
/* CMC   722 FORMAT(/,2X,'INPUT LINK ',I6,12X,'P= ',F12.2,12X,'Q= ',F12.2) */
fprintf(fp10, "\n  INPUT LINK %6d            P= %12.2f            Q= %12.2f\n",
j,net_1.p[j - 1],net_1.q[j - 1]);

/*<   210 SUMI=SUMI+P(J)*Q(J) >*/
/* L210: */
	sumi += net_1.p[j - 1] * net_1.q[j - 1];
    }
/* CMC       WRITE(10,822)K,P(K),Q(K) */
/* CMC   822 FORMAT(/,2X,'OUTPUT LINK',I6,12X,'P= ',F12.2,12X,'Q= ',F12.2) */
fprintf(fp10,"\n  OUTPUT LINK%6d            P= %12.2f            Q= %12.2f\n",
k,net_1.p[k - 1],net_1.q[k - 1]);

/*<    >*/
    r__1 = min_1.rirm[*ipr - 1] + 1.f;
    r__2 = min_1.rirm[*ipr - 1] + 1.f;
    crf = min_1.rirm[*ipr - 1] * pow_ri(&r__1, &min_1.lifem[*ipr - 1]) / (
	    pow_ri(&r__2, &min_1.lifem[*ipr - 1]) - 1.f);
/*<       CCH=TCIM(IPR)*CRF >*/
    cch = min_1.tcim[*ipr - 1] * crf;
/*<       SCC=TCIM(IPR)/(CAPM(IPR)*CFM(IPR)) >*/
    scc = min_1.tcim[*ipr - 1] / (pro_1.capm[*ipr - 1] * min_1.cfm[*ipr - 1]);
/*<       PF=0.0 >*/
    pf = 0.f;
/*<       COST=SUMI+OMM(IPR)*Q(K)+CCH >*/
    cost = sumi + min_1.omm[*ipr - 1] * net_1.q[k - 1] + cch;
/*<       PROFIT=P(K)*Q(K)-COST >*/
    profit = net_1.p[k - 1] * net_1.q[k - 1] - cost;
/*<       ROR=PROFIT/COST >*/
    ror = profit / cost;
/* CMC       WRITE(10,522)TCIM(IPR),CAPMM(IPR), */
/* CMC      1 CFM(IPR),OMM(IPR),LIFEM(IPR),PF,RIRM(IPR),CRF,CCH,PSCALE,PROFIT, */
/* CMC      2 ROR */
/* CMC   522 FORMAT(      /,2X,'CAPITAL COST FOR FACILITY    ($)',E12.4, */
/* CMC      4             /,2X,'FAC MAX CAPACITY   (     /YR)   ',E12.4, */
/* CMC      5             /,2X,'CAPACITY FACTOR  (FRACTION)     ',F12.2, */
/* CMC      A             /,2X,'NONFUEL O&M COST ($/     )      ',F12.2, */
/* CMC      6             /,2X,'UNIT LIFE (YEARS)               ',I12, */
/* CMC      D             /,2X,'PROFIT FACTOR (FRACTION)        ',F12.4, */
/* CMC      7             /,2X,'INTEREST RATE  (FRACTION)       ',F12.4, */
/* CMC      9             /,2X,'CAPITAL RECOVERY FACTOR         ',F12.5, */
/* CMC      B             /,2X,'CAPITAL CHARGE ($/YR)           ',F12.2, */
/* CMC      C             /,2X,'PROFIT  (',F6.0,'$/YR)    ',8X,F12.0, */
/* CMC      1             /,2X,'RETURN ON INVESTMENT  (FRACTION)',F12.4) */
    fprintf(fp10, "\n  CAPITAL COST FOR FACILITY    ($)%12.4e",min_1.tcim[*ipr - 1]);
    fprintf(fp10, "\n  FAC MAX CAPACITY   (     /YR)   %12.4e",min_1.capmm[*ipr - 1]);
    fprintf(fp10, "\n  CAPACITY FACTOR  (FRACTION)     %12.2f",min_1.cfm[*ipr - 1]);
    fprintf(fp10, "\n  NONFUEL O&M COST ($/     )      %12.2f",min_1.omm[*ipr - 1]);
    fprintf(fp10, "\n  UNIT LIFE (YEARS)               %2d",min_1.lifem[*ipr - 1]);
    fprintf(fp10, "\n  PROFIT FACTOR (FRACTION)        %12.4f",pf);
    fprintf(fp10, "\n  INTEREST RATE  (FRACTION)       %12.4f",min_1.rirm[*ipr - 1]);
    fprintf(fp10, "\n  CAPITAL RECOVERY FACTOR         %12.5f",crf);
    fprintf(fp10, "\n  CAPITAL CHARGE ($/YR)           %12.2f",cch);
    fprintf(fp10, "\n  PROFIT  (%6.0f$/YR)            %12.0f",pri_1.pscale, profit);
    fprintf(fp10, "\n  RETURN ON INVESTMENT  (FRACTION)%12.4f",ror);

/*<       RETURN >*/
    return 0;

/*<   300 CONTINUE >*/
L300:

/* **** REFINERIES */

/* CMC       WRITE(10,322)IPR */
/* CMC   322 FORMAT(//,1X,130(1H*),/,2X,'REFINERY',I6) */
fprintf(fp10, "\n\n **********************************************************************************************************************************\n  REFINERY%6d\n",(*ipr) );

/*<       NNI=NINRE(IPR) >*/
    nni = ref_1.ninre[*ipr - 1];
/*<       NNO=NOURE(IPR) >*/
    nno = ref_1.noure[*ipr - 1];
/*<       QIN=0.0 >*/
    qin = 0.f;
/*<       SUMI=0.0 >*/
    sumi = 0.f;
/*<       DO 310 I=1,NNI >*/
    i__1 = nni;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       J=IINRE(IPR,I) >*/
	j = iinre_ref(*ipr, i__);
/* CMC       WRITE(10,722)J,P(J),Q(J) */
fprintf(fp10, "\n  INPUT LINK %6d            P= %12.2f            Q= %12.2f\n",
j,net_1.p[j - 1],net_1.q[j - 1]);
/*<       QIN=QIN+Q(J) >*/
	qin += net_1.q[j - 1];
/*<   310 SUMI=SUMI+P(J)*Q(J) >*/
/* L310: */
	sumi += net_1.p[j - 1] * net_1.q[j - 1];
    }
/*<       QOU=0.0 >*/
    qou = 0.f;
/*<       SUMO=0.0 >*/
    sumo = 0.f;
/*<       DO 320 I=1,NNO >*/
    i__1 = nno;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       K=IOURE(IPR,I) >*/
	k = ioure_ref(*ipr, i__);
/* CMC       WRITE(10,822)K,P(K),Q(K) */
/* C CMC   822 FORMAT(/,2X,'OUTPUT LINK',I6,12X,'P= ',F12.2,12X,'Q= ',F12.2)*/
	fprintf(fp10, "\n  OUTPUT LINK%6d            P= %12.2f            Q= %12.2f\n",
		k,net_1.p[k - 1],net_1.q[k - 1]);

/*<       QOU=QOU+Q(K) >*/
	qou += net_1.q[k - 1];
/*<       SUMO=SUMO+P(K)*Q(K) >*/
	sumo += net_1.p[k - 1] * net_1.q[k - 1];
/*<   320 CONTINUE >*/
/* L320: */
    }
/*<       PF=PFF(IPR) >*/
    pf = ref_1.pff[*ipr - 1];
/*<       COST=SUMI+OMR(IPR)*QOU+CCH >*/
    cost = sumi + ref_1.omr[*ipr - 1] * qou + cch;
/*<       PROFIT=SUMO-COST >*/
    profit = sumo - cost;
/*<       ROR=PROFIT/COST >*/
    ror = profit / cost;
/*<    >*/
    r__1 = ref_1.rirr[*ipr - 1] + 1.f;
    r__2 = ref_1.rirr[*ipr - 1] + 1.f;
    crf = ref_1.rirr[*ipr - 1] * pow_ri(&r__1, &ref_1.lifer[*ipr - 1]) / (
	    pow_ri(&r__2, &ref_1.lifer[*ipr - 1]) - 1.f);
/*<       CCH=TCIR(IPR)*CRF >*/
    cch = ref_1.tcir[*ipr - 1] * crf;
/*<       SCC=TCIR(IPR)/(CAPMR(IPR)*CFR(IPR)) >*/
    scc = ref_1.tcir[*ipr - 1] / (ref_1.capmr[*ipr - 1] * ref_1.cfr[*ipr - 1])
	    ;
/* CMC       WRITE(10,522)TCIR(IPR),CAPMR(IPR), */
/* CMC      1 CFR(IPR),OMR(IPR),LIFER(IPR),PF,RIRR(IPR),CRF,CCH,PSCALE,PROFIT, */
/* CMC      2 ROR */

/* CMC CHECK ON E */
    fprintf(fp10, "\n  CAPITAL COST FOR FACILITY    ($)%12.4e",pro_1.tci[*ipr - 1]);
    fprintf(fp10, "\n  FAC MAX CAPACITY   (     /YR)   %12.4e",pro_1.capm[*ipr - 1]);
    fprintf(fp10, "\n  CAPACITY FACTOR  (FRACTION)     %12.2f",pro_1.cf[*ipr - 1]);
    fprintf(fp10, "\n  NONFUEL O&M COST ($/     )      %12.2f",pro_1.om[*ipr - 1]);
    fprintf(fp10, "\n  UNIT LIFE (YEARS)               %2d",pro_1.life[*ipr - 1]);
    fprintf(fp10, "\n  PROFIT FACTOR (FRACTION)        %12.4f",pf);
    fprintf(fp10, "\n  INTEREST RATE  (FRACTION)       %12.4f",pro_1.rir[*ipr - 1]);
    fprintf(fp10, "\n  CAPITAL RECOVERY FACTOR         %12.5f",crf);
    fprintf(fp10, "\n  CAPITAL CHARGE ($/YR)           %12.2f",cch);
    fprintf(fp10, "\n  PROFIT  (%6.0f$/YR)            %12.0f",pri_1.pscale, profit);
    fprintf(fp10, "\n  RETURN ON INVESTMENT  (FRACTION)%12.4f",ror);


/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* cash_ */

#undef ioure_ref
#undef iinre_ref
#undef iinmi_ref




/* ***************************************************************** CONVG */

/*<       SUBROUTINE CONVG(ICON) >*/
/* Subroutine */ int convg_(integer *icon)
{
extern FILE *fp6, *fp11, *fp21;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static real qdel;
    static integer jcon;
    static real aerr__;
    static integer nlim;
    static real rerr[92];
    static integer i__, l;
    static real resid;
    static integer im;
    static real qq, residm;
    static integer inx;


/*<       DIMENSION RERR(92) >*/
/*<    >*/
/*<    >*/
/*<       COMMON/NET/Q(999),P(999),CAPL(999),LAB(5),IUSE(300),LUSE(999) >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/

/* ***** CHECK FOR CONVERGENCE AT RESOURCE NODES. */

/*<       RESIDM=0.0 >*/
    residm = 0.f;
/*<       ICON=1 >*/
    *icon = 1;
/* CMC       IF(IWR1.GE.1)WRITE(6,299) */
/* CMC   299 FORMAT(/,2X,'CONVERGENCE REPORT:') */
    if (var_1.iwr1 >= 1) 
fprintf(fp6, "\n  CONVERGENCE REPORT:\n");

/*<       NLIM=NRSMX+NRNMX >*/
    nlim = var_1.nrsmx + var_1.nrnmx;
/*<       IM=1                                                               >*/
    im = 1;
/*<       DO 10 I=1,NLIM >*/
    i__1 = nlim;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       IF(I.GT.NRSMX)GO TO 1202 >*/
	if (i__ > var_1.nrsmx) {
	    goto L1202;
	}
/*<       L=IOURS(I) >*/
	l = res_1.iours[i__ - 1];
/*<       GO TO 1203 >*/
	goto L1203;

/*<  1202 INX=I-NRSMX >*/
L1202:
	inx = i__ - var_1.nrsmx;
/*<       L=IOURN(INX) >*/
	l = ren_1.iourn[inx - 1];

/*<  1203 IF(L.EQ.0)GO TO 10 >*/
L1203:
	if (l == 0) {
	    goto L10;
	}
/*<       QDEL=Q(L)-QT(I) >*/
/*	if(i__ == 5) */
	
	qdel = net_1.q[l - 1] - res_1.qt[i__ - 1];
/*<       QQ=QT(I) >*/
	qq = res_1.qt[i__ - 1];
/*<       RESID=QDEL/(0.001+QQ) >*/
	resid = qdel / (qq + .001f);
/* CMC       IF(IWR1.GE.1)WRITE(6,300)L,QT(I),Q(L),RESID */
/* CMC   300 FORMAT(2X,'LINK=',I4,5X,'Q=',F11.3,5X,'HQ=',F11.3,5X,'ERROR=', */
/* CMC      1 E12.4) */
	if (var_1.iwr1 >= 1) 
fprintf(fp6, "  LINK=%s     Q=%11.3f     HQ=%11.3f     ERROR=%12.4e\n",
LinkNodeNames[13][l], res_1.qt[i__ - 1]/units_1.unitcnvt[8], net_1.q[l - 1]/units_1.unitcnvt[8], resid);

/*<       IF(ABS(RESID).LE.ABS(RESIDM))GO TO 1107 >*/
	if (dabs(resid) <= dabs(residm)) {
	    goto L1107;
	}
/*<       RESIDM=RESID >*/
	residm = resid;
/*<       IM=I >*/
	im = i__;

/*<  1107 JCON=0 >*/
L1107:
	jcon = 0;
/*<       IF(ABS(RESID).GT.RCTOL)GO TO 115 >*/
	if (dabs(resid) > var_1.rctol) {
	    goto L115;
	}
/*<       JCON=1 >*/
	jcon = 1;
/*<       GO TO 116 >*/
	goto L116;

/*<   115 AERR=Q(L)-QT(I) >*/
L115:
	aerr__ = net_1.q[l - 1] - res_1.qt[i__ - 1];
/*<       IF(AERR.LT.0.00)AERR=-AERR >*/
	if (aerr__ < 0.f) {
	    aerr__ = -aerr__;
	}
/*<       RERR(I)=AERR >*/
	rerr[i__ - 1] = aerr__;
/*<       IF(AERR.GT.ACTOL)GO TO 116 >*/
	if (aerr__ > var_1.actol) {
	    goto L116;
	}
/*<       JCON=1 >*/
	jcon = 1;

/*<   116 ICON=ICON*JCON >*/
L116:
	*icon *= jcon;
/*<    10 CONTINUE >*/
L10:
	;
    }

/* ***** SET CONVERGENCE FLAG IF MAXIMUM RESIDUAL WITHIN TOLERANCE. */


/* CMC       IF(IWR1.GE.1)WRITE(6,120)ITIME,ITN,RCTOL,RESIDM */
/* CMC   120 FORMAT(/,2X,'#',5X,I5,5X,'ITERATION=',I5,5X,'REL TOL=',F7.4, */
/* CMC      1 5X,'REL ERR MAX=',E14.6) */
    if (var_1.iwr1 >= 1) 
fprintf(fp6, "\n  #     %5d     ITERATION=%5d     REL TOL=%7.4f     REL ERR MAX=%14.6e\n",
var_1.itime,var_1.itn,var_1.rctol,residm);

/* CMC       WRITE(11,129)ITIME,ITN,RESIDM,RERR(IM) */
/* CMC   129 FORMAT(2X,I5,5X,'ITERATION =',I5,5X,'MAX REL ERR =',E14.6, */
/* CMC      1 5X,'ABS ERR =',F8.1,'     #') */
fprintf(fp11, "  %5d     ITERATION =%5d     MAX REL ERR =%14.6e     ABS ERR =%8.1f     #\n",
var_1.itime, var_1.itn, residm, rerr[im - 1]);

fprintf(fp21,"  %5d     ITERATION =%5d     MAX REL ERR =%14.6e     ABS ERR =%8.1f     #\n",
var_1.itime, var_1.itn, residm, rerr[im - 1]);

/* CMC       WRITE(*,9129)ITIME,ITN,RESIDM,RERR(IM) */
/* CMC  9129 FORMAT(2X,I5,2X,'ITER=',I5,3X,'MAX RERR=',E14.6, */
/* CMC      1 3X,'AERR=',F8.1,' #') */
/* CMC UNKNOWN */

/*<       IF(IWR1.EQ.0)RETURN >*/
    if (var_1.iwr1 == 0) {
	return 0;
    }
/* CMC       IF(ABS(RESIDM).GT.RCTOL.AND.ICON.EQ.1)WRITE(6,121)ACTOL */
/* CMC   121 FORMAT(/,2X,'ALL LINKS EXCEEDING REL ERR TOL ARE ', */
/* CMC      1 'WITHIN ABS ERR TOL OF',F10.2) */
    if (dabs(residm) > var_1.rctol && *icon == 1) 
fprintf(fp6, "\n  ALL LINKS EXCEEDING REL ERR TOL ARE WITHIN ABS ERR TOL OF%10.2f\n", var_1.actol);
/*<       RETURN >*/
    return 0;

/*<       END >*/
} /* convg_ */

