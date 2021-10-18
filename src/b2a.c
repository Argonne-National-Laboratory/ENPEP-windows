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

/* b2a.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
   -lf2c -lm   (in that order)
   */
#include <stdio.h>
#include "cmc_f2c.h"
#include <stdlib.h>
#include "f2c.h"
#include "structures.h"


/* ******************************************************************** AL */

/*<       SUBROUTINE AL(IPASS,IPR,KSPEC) >*/
/* Subroutine */ int al_(integer *ipass, integer *ipr, integer *kspec)
{
  extern FILE *fp11, *fp6, *fp21;
  extern char LinkNodeNames[14][999][6];
  extern char LinkNodeSector[14][999][6];
  /* System generated locals */
  integer i__1, i__2;
  doublereal d__1, d__2;
  
  /* Builtin functions */
  double pow_dd(doublereal *, doublereal *);
  
  /* Local variables */
  static integer ipal[200], kpal[200], mpal[200];
  static real qbin;
  static integer lall;
  static real qall, vlag;
  static integer nout;
  static real qout;
  static integer ioms;
  static real dsup;
  static integer i__, j, k, l, m, lgflg;
  static real qinsv[200], qvout[200];
  static integer lsexp, lgrid;
  static real stock;
  static integer i2;
  static real qreal, tmpms, pa, pd;
  static integer no, np[200], ls;
  static real pn, pq;
  static integer ix, lp, jv, mx, kx, nx, nn;
  static real vnewms, den;
  static integer nin, nou, ist, ipm;
  static real qin, pnw, pdw;
  static integer ixm;
  static real qms, ssp, pps, vms, pms;

  
/* #define labs_ref(a_1,a_2) stk_1.labs[(a_2)*20 + a_1 - 21] */
#define prem_ref(a_1,a_2) min_1.prem[(a_2)*400 + a_1 - 401]
#define iinal_ref(a_1,a_2) all_1.iinal[(a_2)*400 + a_1 - 401]
#define ialpr_ref(a_1,a_2) all_1.ialpr[(a_2)*400 + a_1 - 401]
#define ioual_ref(a_1,a_2) all_1.ioual[(a_2)*400 + a_1 - 401]
#define split_ref(a_1,a_2) all_1.split[(a_2)*400 + a_1 - 401]
#define sen_ref(a_1,a_2) pri_1.sen[(a_2)*20 + a_1 - 21]
#define shr_ref(a_1,a_2) var_1.shr[(a_2)*200 + a_1 - 201]
#define oms_ref(a_1,a_2) all_1.oms[(a_2)*400 + a_1 - 401]
#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
#define rms_ref(a_1,a_2) all_1.rms[(a_2)*400 + a_1 - 401]
/* #define laba_ref(a_1,a_2) all_1.laba[(a_2)*200 + a_1 - 201] */

  
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<       COMMON/AL1/NGG(200) >*/
  /*<       COMMON/NET/Q(999),P(999),CAPL(999),LAB(5),IUSE(300),LUSE(999) >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<       COMMON/MODE/IRESON,ILOD,IELE,IMP,BOEMWH,BOEMBTU >*/
  
  /* ****** ASSIGN NUMBER OF OUTPUT LINKS. */
  
  /*<       NOU=NOUAL(IPR) >*/


  nou = all_1.noual[*ipr - 1];
  
  /* ****** ASSIGN STOCKPILE LINK NUMBER IF ONE EXISTS FOR THIS NODE. */
  
  /*<       LS=0 >*/
  ls = 0;
  /*<       IST=IALST(IPR) >*/
  ist = stk_1.ialst[*ipr - 1];
  /*<       IF(IST.EQ.0)GO TO 1978 >*/
  if (ist == 0) {
    goto L1978;
  }
  /*<       LS=IOUST(IST) >*/
  ls = stk_1.ioust[ist - 1];
  /*<       LSEXP = ISTKEXL(IST)                                               >*/
  lsexp = stk_1.istkexl[ist - 1];
  /*<  1978 CONTINUE >*/
 L1978:
  
  /* *****THIS SECTION FOR WRITING OUTPUT. */
  /*     IPASS = 5 */
  /*     IPASS = 6 */
  /*     IPASS = 7 */
  
  /*<       IF(IPASS.LE.4)GO TO 4409 >*/
  if (*ipass <= 4) {
    goto L4409;
  }
  /*<       IF(LS.EQ.0)GO TO 4919 >*/
  if (ls == 0) {
    goto L4919;
  }
  
  /*<       IF(IPASS.LT.6)GO TO 4511 >*/
  if (*ipass < 6) {
    goto L4511;
  }
  /*<       IPM=IPASS-5 >*/
  ipm = *ipass - 5;
  /* CMC       WRITE(11,4903)(LABS(IST,J),J=1,4) */
  fprintf(fp11, "  %s\n",stk_1.cmc_labs[ist]);
  
  /* CMC       IF(IPASS.EQ.6)WRITE(11,4415)IST,(SEN(IST,J),J=1,IOUTX) */
  /* CMC  4415 FORMAT(1X,I4,1X,'S',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      2  ,/,10X,5F11.1) */
  if (*ipass == 6) {
    fprintf(fp11," %4d S   ", ist);
    for(j=1; j<=pri_1.ioutx;j++){
      if( ((j-1)%10==0) && (j>1)) 
	fprintf(fp11,"\n          ");
      fprintf(fp11,"%11.1f", sen_ref(ist, j));
    }
    fprintf(fp11,"\n");
  }
  
  /* CMC       IF(IPASS.EQ.6)WRITE(11,4411)LS,(ZEN(1,LS,J),J=1,IOUTX) */
  /* CMC  4411 FORMAT(1X,I4,1X,'Q',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      2  ,/,10X,5F11.1) */
  
  if (*ipass == 6) {
    fprintf(fp11," %4d Q   ", ls);
    for(j=1; j<=pri_1.ioutx;j++){
      if( ((j-1)%10==0) && (j>1)) fprintf(fp11, "\n          ");
      fprintf(fp11,"%11.1f", zen_ref(1,ls, j));
    }
    fprintf(fp11,"\n");
  }
  
  
  
  /* CMC       IF(IPASS.EQ.7)WRITE(11,4412)LS,(ZEN(2,LS,J),J=1,IOUTX) */
  /* CMC  4412 FORMAT(1X,I4,1X,'P',3X,10F9.2,/,10X,10F9.2,/,10X,10F9.2 */
  /* CMC      1   ,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F2.2 */
  /* CMC      2   ,/,10X,5F9.2) */
  if (*ipass == 7) {
    fprintf(fp11," %4d P   ", ls);
    for(j=1; j<=pri_1.ioutx;j++){
      if( ((j-1)%10==0) && (j>1)) 
	fprintf(fp11, "\n          ");
      fprintf(fp11,"%9.2f", zen_ref(2,ls,j));
    }
    fprintf(fp11,"\n");
  }
  
  
  
  
  
  /*<       GO TO 4919 >*/
  goto L4919;
  
  /*<  4511 ZEN(1,LS,IOUTX)=Q(LS)*QSCALE >*/
 L4511:
  zen_ref(1, ls, pri_1.ioutx) = net_1.q[ls - 1] * var_1.qscale;
  /*<       ZEN(2,LS,IOUTX)=P(LS)*PSCALE >*/
  zen_ref(2, ls, pri_1.ioutx) = net_1.p[ls - 1] * pri_1.pscale;
  /* CMC  4104 FORMAT(2X,3A4,/,2X,I5,5X,'STOCK',I4,5X,I5,14X,'STOCKPILE=', */
  /* CMC      1 F14.3,5X,F14.3) */
  
  /*<  4919 CONTINUE >*/
 L4919:
  /* CMC  4919 IF(IPASS.GE.6)WRITE(11,4903)(LABA(IPR,J),J=1,4) */
  if (*ipass >= 6) {
    fprintf(fp11,"  %s\n",all_1.cmc_laba[*ipr]);

  }
  
  /*<       DO 4410 I=1,NOU >*/
  i__1 = nou;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IOUAL(IPR,I) >*/
    l = ioual_ref(*ipr, i__);
    /*<       IF(IPASS.LT.6)GO TO 4717 >*/
    if (*ipass < 6) {
      goto L4717;
    }
    /*<       IPM=IPASS-5 >*/
    ipm = *ipass - 5;
    /* CMC       IF(IPASS.EQ.6)WRITE(11,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
    if (*ipass == 6) {
      fprintf(fp11," %4d Q   ", l);
      for(j=1; j<=pri_1.ioutx;j++){
	if( ((j-1)%10==0) && (j>1)) 
	  fprintf(fp11,"\n          ");
	fprintf(fp11,"%11.1f", zen_ref(1,l, j));
      }
      fprintf(fp11,"\n");
    }
    
    /* CMC       IF(IPASS.EQ.7)WRITE(11,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
    if (*ipass == 7) {
      fprintf(fp11," %4d P   ", l);
      for(j=1; j<=pri_1.ioutx;j++){
	if( ((j-1)%10==0) && (j>1)) 
	  fprintf(fp11, "\n          ");
	fprintf(fp11,"%9.2f", zen_ref(2,l,j));
      }
      fprintf(fp11,"\n");
    }
    
    
    /*<       GO TO 4410 >*/
    goto L4410;
    
    /*<  4717 PQ=P(L)*Q(L) >*/
  L4717:
    pq = net_1.p[l - 1] * net_1.q[l - 1];
    /*<       ZEN(1,L,IOUTX)=Q(L)*QSCALE >*/
    zen_ref(1, l, pri_1.ioutx) = net_1.q[l - 1] * var_1.qscale;
    /*<       ZEN(2,L,IOUTX)=P(L)*PSCALE >*/
    zen_ref(2, l, pri_1.ioutx) = net_1.p[l - 1] * pri_1.pscale;
    /*<       IF(IST.GT.0)SEN(IST,IOUTX)=STOK(IST)*QSCALE >*/
    if (ist > 0) {
      sen_ref(ist, pri_1.ioutx) = stk_1.stok[ist - 1] * var_1.qscale;
    }
    
    /* CMC  4903 FORMAT(2X,4A4) */
    /*<  4410 CONTINUE >*/
  L4410:
    ;
  }
  /*<       RETURN >*/
  return 0;
  
  
  /* *****THIS SECTION FOR ITERATION LOGIC, UP AND DOWN.  ****************** */
  
  /*<  4409 CONTINUE >*/
 L4409:
  /*<       IF(IPASS.EQ.2)GO TO 200 >*/
  if (*ipass == 2) {
    goto L200;
  }
  
  /* **** BEGIN UP-PASS LOGIC. ********************************************* */
  
  /* **** COMPUTE WEIGHTED AVERAGE PRICE. */
  
  /* ........ ASSIGN NUMBER OF INPUT LINKS AND INITIALIZE. */
  
  /*<       NIN=NINAL(IPR) >*/
  nin = all_1.ninal[*ipr - 1];
  /*<       PN=0. >*/
  pn = 0.f;
  /*<       PD=0. >*/
  pd = 0.f;
  /*<       QIN=0. >*/
  qin = 0.f;
  /*<       PNW=0. >*/
  pnw = 0.f;
  /*<       PDW=0. >*/
  pdw = 0.f;
  
  /* ........ COMPUTE TOTAL QUANTITY INTO NODE. */
  
  /*<       DO 8877 I=1,NIN >*/
  i__1 = nin;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IINAL(IPR,I) >*/
    l = iinal_ref(*ipr, i__);
    
    /* ........ SKIP STOCKPILE NODE INPUT LINK. */
    
    /*<       IF(L.EQ.LS)GO TO 8877 >*/
    if (l == ls) {
      goto L8877;
    }
    /*<       QIN=QIN+Q(L) >*/
    qin += net_1.q[l - 1];
    /*<  8877 CONTINUE >*/
  L8877:
    ;
  }
  
  /* ........ BRANCH IF ONLY ONE INPUT LINK OR Q INPUT GT 0. */
  
  /*<       IF(NIN.EQ.1)GO TO 1341 >*/
  if (nin == 1) {
    goto L1341;
  }
  /*<       IF(QIN.GT.0.001)GO TO 1340 >*/
  if (qin > .001f) {
    goto L1340;
  }
  
  /* ........ TO GET HERE Q INPUT GT 0. */
  
  /*<  1341 DO 1010 I=1,NIN >*/
 L1341:
  i__1 = nin;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IINAL(IPR,I) >*/
    l = iinal_ref(*ipr, i__);
    
    /* ........ SKIP INPUT LINK FROM STOCKPILE. */
    
    /*<       IF(L.EQ.LS)GO TO 1010 >*/
    if (l == ls) {
      goto L1010;
    }
    
    /* ........ WTD AVE PRICE COMPUTATION. */
    /*         IF INPUT PRICE IS ZERO DO NOT INCLUDE. */
    
    /*  +++++ FIRST CHANGE +++++ */
    
    /*<       IF(P(L).LT.0.009)GO TO 1010 >*/
    if (net_1.p[l - 1] < .009f) {
      goto L1010;
    }
    /*<       PN=PN+P(L)*((1./P(L))**GM(IPR)) >*/
    d__1 = (doublereal) (1.f / net_1.p[l - 1]);
    d__2 = (doublereal) all_1.gm[*ipr - 1];
    pn += net_1.p[l - 1] * pow_dd(&d__1, &d__2);
    /*<       PD=PD+(1./P(L))**GM(IPR) >*/
    d__1 = (doublereal) (1.f / net_1.p[l - 1]);
    d__2 = (doublereal) all_1.gm[*ipr - 1];
    pd += pow_dd(&d__1, &d__2);
    /*<  1010 CONTINUE >*/
  L1010:
    ;
  }
  
  /* ........ SKIP NEXT SECTION SINCE Q INPUT GT 0. */
  
  /*<       IF (PD .GT. 0.0) GO TO 7989                                        >*/
  if (pd > 0.f) {
    goto L7989;
  }
  /*<       GO TO 1012 >*/
  goto L1012;
  
  /* ........ ZERO QUANTITY INPUT TO THIS NODE. */
  
  /*<  1340 DO 1011 I=1,NIN >*/
 L1340:
  i__1 = nin;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IINAL(IPR,I) >*/
    l = iinal_ref(*ipr, i__);
    /*<       IF(L.EQ.LS)GO TO 1011 >*/
    if (l == ls) {
      goto L1011;
    }
    
    /*<       PN=PN+P(L)*Q(L) >*/
    pn += net_1.p[l - 1] * net_1.q[l - 1];
    /*<       PD=PD+Q(L) >*/
    pd += net_1.q[l - 1];
    /*<  1011 CONTINUE >*/
  L1011:
    ;
  }
  
  /* ........ WTD AVERAGE PRICE EQUATION. */
  
  /*<  1012 IF(PD.GT.1.E-10)GO TO 7989 >*/
 L1012:
  if (pd > 1e-10f) {
    goto L7989;
  }
  /*<       PA=0.001 >*/
  pa = .001f;
  /*<       GO TO 1106 >*/
  goto L1106;
  /*<  7989 PA=PN/PD >*/
 L7989:
  pa = pn / pd;
  
  /* ****** LOOP OVER ALL OUTPUT LINKS. COMPUTE ENERGY FLOWS */
  /*       OUT OF NODE IF BASE YEAR. */
  
  /*<  1106 NO=NOUAL(IPR) >*/
 L1106:
  no = all_1.noual[*ipr - 1];
  /*<       QBIN=QIN >*/
  qbin = qin;
  
  /*<       DO 11 I=1,NO >*/
  i__1 = no;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IOUAL(IPR,I) >*/
    l = ioual_ref(*ipr, i__);
    
    /*<       IF(NTIME.GT.1)GO TO 1546 >*/
    if (var_1.ntime > 1) {
      goto L1546;
    }
    
    /*<       IF(LS.EQ.0)GO TO 3344 >*/
    if (ls == 0) {
      goto L3344;
    }
    /*<       QBIN=QIN+Q(LS) >*/
    qbin = qin + net_1.q[ls - 1];
    /*<  3344 Q(L)=QBIN*SPLIT(IPR,I) >*/
  L3344:
    net_1.q[l - 1] = qbin * split_ref(*ipr, i__);
    /*<  1546 CONTINUE >*/
  L1546:
    
    /* C........ ASSIGN AVERAGE PRICE TO LINK AND WRITE. */
    
    /*<       P(L)=PA >*/
    net_1.p[l - 1] = pa;
    
    /* CMC       IF(IWR1.GE.2)WRITE(6,202)IPR,L,NTIME,P(L) */
    /* CMC   202 FORMAT(2X,'P',5X,'ALLOC',I4,5X,'LINK',I4,5X,'TIME', */
    /* CMC      1I3,4X,1H$,F10.4) */
    fprintf(fp6, "  P     AL  %s (%s)     LINK  %s     YEAR%6d    $%10.4f\n",
	    LinkNodeNames[0][(*ipr)],LinkNodeSector[0][(*ipr)],LinkNodeNames[13][l],var_1.itime,net_1.p[l - 1]/units_1.unitcnvt[3]);
    /* C........ WRITE BASE YEAR QUANITITY. */
    
    /* CMC       IF (IWR1.GE.2.AND.NTIME.EQ.1) WRITE(6,1959)IPR,L,NTIME,Q(L) */
    /* CMC  1959 FORMAT(2X,'QB',4X,'ALLOC',I4,5X,'LINK',I4,5X,'TIME',I3,4X,F11.3) */
    if (var_1.iwr1 >= 2 && var_1.ntime == 1) {
      fprintf(fp6, "  QB    AL  %s (%s)     LINK  %s     YEAR%6d    %11.3f\n",
	      LinkNodeNames[0][(*ipr)],LinkNodeSector[0][(*ipr)],LinkNodeNames[13][l],var_1.itime, net_1.q[l - 1]/units_1.unitcnvt[8]);
    }
    /*<    11 CONTINUE >*/
    /* L11: */
  }
  
  /* ****** RETURN IF YEAR GREATER THAN BASE YEAR. */
  
  /*<       IF(NTIME.GT.1)RETURN >*/
  if (var_1.ntime > 1) {
    return 0;
  }
  
  /* ***** INITIALIZE SHARES FOR LAG AND RES MODE IF BASE YEAR. */
  
  /*<       QINSV(IPR)=QIN >*/
  qinsv[*ipr - 1] = qin;
  /*<       DO 1201 I=1,NIN >*/
  i__1 = nin;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IINAL(IPR,I) >*/
    l = iinal_ref(*ipr, i__);
    /*<       IF(L.EQ.LS)GO TO 1201                                              >*/
    if (l == ls) {
      goto L1201;
    }
    /*<       IF(QIN.LT.0.0001)GO TO 1201 >*/
    if (qin < 1e-4f) {
      goto L1201;
    }
    
    /*<       RMS(IPR,I)=Q(L)/QIN >*/
    rms_ref(*ipr, i__) = net_1.q[l - 1] / qin;
    /*<       SHR(IPR,I)=RMS(IPR,I) >*/
    shr_ref(*ipr, i__) = rms_ref(*ipr, i__);
    /*<  1201 CONTINUE >*/
  L1201:
    ;
  }
  
  /*<       RETURN >*/
  return 0;
  
  /* ****** END OF UP-PASS LOGIC. ********************************************** */
  
  
  /* **** BEGIN DOWN-PASS LOGIC.  ********************************************** */
  
  /*<   200 CONTINUE >*/
 L200:
  
  /* **** COMPUTE QUANTITY OUTPUT */
  /* **** FROM ALLOCATION NODE. */
  
  /*<       NOUT=NOUAL(IPR) >*/
  nout = all_1.noual[*ipr - 1];
  /*<       QOUT=0. >*/
  qout = 0.f;
  /*<       LGRID=0 >*/
  lgrid = 0;
  
  /*<       DO 112 I=1,NOUT >*/
  i__1 = nout;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IOUAL(IPR,I) >*/
    l = ioual_ref(*ipr, i__);
    /* **** SKIP QUANTITY OUTPUT FROM STOCK EXPORT LINK                       BPH10-92 */
    /*<       IF (L .EQ. LSEXP) GOTO 112                                         >*/
    if (l == lsexp) {
      goto L112;
    }
    /*<       QOUT=QOUT+Q(L) >*/
    qout += net_1.q[l - 1];
    /*<   112 CONTINUE >*/
  L112:
    ;
  }
  
  /* ***** IF ONLY ONE INPUT, ASSIGN QOUT AND RETURN. */
  
  /*<       NIN=NINAL(IPR) >*/
  nin = all_1.ninal[*ipr - 1];
  /*<       IF(NIN.GT.1)GO TO 3789 >*/
  if (nin > 1) {
    goto L3789;
  }
  
  /*<       L=IINAL(IPR,1) >*/
  l = iinal_ref(*ipr, 1);
  /*<       Q(L)=QOUT >*/
  net_1.q[l - 1] = qout;
  /* CMC       IF(IWR1.GE.2)WRITE(6,1827)IPR,L,NTIME,Q(L) */
  /* CMC  1827 FORMAT(2X,'Q',5X,'ALLOC',I4,5X,'LINK',I4,5X,'TIME',I3,4X, */
  /* CMC      1 F11.3,2X,'ONE INPUT ONLY') */
  if (var_1.iwr1 >= 2) 
    fprintf(fp6, "  Q     AL  %s (%s)     LINK  %s     YEAR%6d    %11.3f  ONE INPUT ONLY\n", 
		LinkNodeNames[0][(*ipr)],LinkNodeSector[0][(*ipr)],LinkNodeNames[13][l],var_1.itime,net_1.q[l - 1]/units_1.unitcnvt[8]);
  
  
  
  
  /*<       RETURN >*/
  return 0;
  
  /*<  3789 CONTINUE >*/
 L3789:
  
  /* ***** IF NO STOCKPILE, GO TO 115 FOR QUANTITY ALLOCATION. */
  
  /*<       IF(LS.EQ.0)GO TO 115 >*/
  if (ls == 0) {
    goto L115;
  }
  
  /*<       STOCK=ST(IST) >*/
  stock = stk_1.st[ist - 1];
  /*<       IF(QOUT-STOCK)113,113,114 >*/
  if (qout - stock <= 0.f) {
    goto L113;
  }
  else {
    goto L114;
  }
  
  /* ***** STOCKPILE SMALLER THAN QUANTITY DEMANDED. */
  
  /*<   114 QOUT=QOUT-STOCK >*/
 L114:
  qout -= stock;
  /*<       Q(LS)=STOCK >*/
  net_1.q[ls - 1] = stock;
  /*<       STOCK=0. >*/
  stock = 0.f;
  /*<       ST(IST)=0. >*/
  stk_1.st[ist - 1] = 0.f;
  
  /* CMC       IF(IWR1.GE.2)WRITE(6,602)IPR,LS,NTIME,Q(LS),STOCK */
  /* CMC   602 FORMAT(2X,'Q',5X,'ALLOC',I4,5X,'LINK',I4,5X,'TIME', */
  /* CMC      1I3,4X,F11.3,2X,'STOCKP=',F13.2) */
  if (var_1.iwr1 >= 2) 
    fprintf(fp6, "  Q     AL  %s (%s)    LINK  %s     YEAR%6d    %11.3f  STOCKP=%13.2f\n",
		LinkNodeNames[0][(*ipr)],LinkNodeSector[0][(*ipr)],LinkNodeNames[13][ls],var_1.itime,net_1.q[ls - 1]/units_1.unitcnvt[8],stock/units_1.unitcnvt[8]);
  
  
  /*<       GO TO 115 >*/
  goto L115;
  
  /* ***** STOCKPILE LARGER THAN QUANTITY DEMANDED. */
  
  /*<   113 STOCK=STOCK-QOUT >*/
 L113:
  stock -= qout;
  /*<       ST(IST)=STOCK >*/
  stk_1.st[ist - 1] = stock;
  /*<       Q(LS)=QOUT >*/
  net_1.q[ls - 1] = qout;
  
  /* CMC       IF(IWR1.GE.2)WRITE(6,602)IPR,LS,NTIME,Q(LS),STOCK */
  if (var_1.iwr1 >= 2) 
    fprintf(fp6, "  Q     AL  %s (%s)     LINK  %s     YEAR%6d    %11.3f  STOCKP=%13.2f\n",
		LinkNodeNames[0][(*ipr)],LinkNodeSector[0][(*ipr)],LinkNodeNames[13][ls],var_1.itime,net_1.q[ls - 1]/units_1.unitcnvt[8],stock/units_1.unitcnvt[8]);
  
  /*<       QOUT=0.0 >*/
  qout = 0.f;
  
  /* ***** ALLOCATION AFTER STOCKPILES HAVE BEEN CONSIDERED. */
  /* ***** INITIALIZE ALL INPUT QUANTITIES TO ZERO */
  /* ***** IF IN RES MODE, COMPUTE QUANTITIES ON INPUT LINKS BASED */
  /* ***** ON PREVIOUSLY COMPUTED SHARES, ASSIGN QUANTITIES TO INPUT */
  /* ***** LINKS, AND RETURN. */
  
  /*<   115 IX=0 >*/
 L115:
  ix = 0;
  /*<       IF(ITN.EQ.1.AND.NTIME.GT.2)QINSV(IPR)=QVOUT(IPR) >*/
  if (var_1.itn == 1 && var_1.ntime > 2) {
    qinsv[*ipr - 1] = qvout[*ipr - 1];
  }
  /*<       QVOUT(IPR)=QOUT >*/
  qvout[*ipr - 1] = qout;
  
  /*<       IF(NTIME.EQ.1) GO TO 120                                           >*/
  if (var_1.ntime == 1) {
    goto L120;
  }
  /* ***** CALCULATE TOTAL QUAN OF INPUT LINKS FOR PREVIOUS YEAR.            bh11-92 */
  /*                                                                        bh11-92 */
  /*<       OQUAN = 0.0                                                        >*/
  all_1.oquan = 0.f;
  /*<       DO 121 I=1,NIN                                                     >*/
  i__1 = nin;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IINAL(IPR,I)                                                     >*/
    l = iinal_ref(*ipr, i__);
    /*<       IF(L.EQ.LS)GO TO 121                                               >*/
    if (l == ls) {
      goto L121;
    }
    /*                                                                        bh11-92 */
    /*<       OQUAN = OQUAN + Q(L)                                               >*/
    all_1.oquan += net_1.q[l - 1];
    /*<   121 CONTINUE                                                           >*/
  L121:
    ;
  }
  /*                                                                        bh11-92 */
  /* **** SUBTRACT PRIORITY LINK QUANTITY TO GET TOTAL QUANT OF PREV YEAR MS bh11-92 */
  /*<       DO 117 I=1,NALPR(IPR)                                              >*/
  i__1 = all_1.nalpr[*ipr - 1];
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IALPR(IPR,I)                                                     >*/
    l = ialpr_ref(*ipr, i__);
    /*<       IF (L.EQ.0) GO TO 117                                              >*/
    if (l == 0) {
      goto L117;
    }
    /*<       OQUAN = OQUAN - Q(L)                                               >*/
    all_1.oquan -= net_1.q[l - 1];
    /*<   117 CONTINUE                                                           >*/
  L117:
    ;
  }
  
  /*<       IF(ITN.GT.1) GO TO 120                                             >*/
  if (var_1.itn > 1) {
    goto L120;
  }
  /* ***** CALCULATE PREVIOUS YEAR MARKET SHARES.                            bh4-91 */
  /*                                                                        bh4-91 */
  /*<       DO 221 I=1,NIN                                                     >*/
  i__1 = nin;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       OMS(IPR,I) = 0.0                                                   >*/
    oms_ref(*ipr, i__) = 0.f;
    /*<   221 CONTINUE                                                           >*/
    /* L221: */
  }
  /*                                                                        bh4-91 */
  /* **** COMPUTE PREVIOUS YEARS MS                                          bh4-91 */
  /*<       IOMS = 0                                                           >*/
  ioms = 0;
  /*<       DO 119 I=1,NIN                                                     >*/
  i__1 = nin;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IINAL(IPR,I)                                                     >*/
    l = iinal_ref(*ipr, i__);
    /*<       IF(L.EQ.LS)GO TO 119                                               >*/
    if (l == ls) {
      goto L119;
    }
    /* **** CHECK THAT LINK IS NOT A PRIORITY LINK                             bh4-91 */
    /*<       DO 118 I2=1,NALPR(IPR)                                             >*/
    i__2 = all_1.nalpr[*ipr - 1];
    for (i2 = 1; i2 <= i__2; ++i2) {
      /*<       LP=IALPR(IPR,I2)                                                   >*/
      lp = ialpr_ref(*ipr, i2);
      /*<       IF (L.EQ.LP) GO TO 119                                             >*/
      if (l == lp) {
	goto L119;
      }
      /*<   118 CONTINUE                                                           >*/
      /* L118: */
    }
    /*                                                                        bh4-91 */
    /*<       IOMS = IOMS + 1                                                    >*/
    ++ioms;
    /*<       IF (OQUAN.EQ.0.0) GO TO 119                                        >*/
    if (all_1.oquan == 0.f) {
      goto L119;
    }
    /*<       OMS(IPR,IOMS) = Q(L) / OQUAN                                       >*/
    oms_ref(*ipr, ioms) = net_1.q[l - 1] / all_1.oquan;
    /*<   119 CONTINUE                                                           >*/
  L119:
    ;
  }
  /*<       POQUAN(IPR) = OQUAN                                                >*/
  all_1.poquan[*ipr - 1] = all_1.oquan;
  
  /*<   120 DO 400 J=1,NIN >*/
 L120:
  i__1 = nin;
  for (j = 1; j <= i__1; ++j) {
    /*<       L=IINAL(IPR,J) >*/
    l = iinal_ref(*ipr, j);
    /*<       IF(L.EQ.LS)GO TO 400 >*/
    if (l == ls) {
      goto L400;
    }
    /*<       IF(ITN.GT.1)GO TO 2707 >*/
    if (var_1.itn > 1) {
      goto L2707;
    }
    /*<       RMS(IPR,J)=SHR(IPR,J) >*/
    rms_ref(*ipr, j) = shr_ref(*ipr, j);
    
    /*<       IF(IRESON.EQ.0)GO TO 2707 >*/
    if (mode_1.ireson == 0) {
      goto L2707;
    }
    /*<       Q(L)=QOUT*SHR(IPR,J) >*/
    net_1.q[l - 1] = qout * shr_ref(*ipr, j);
    /* CMC       IF(IWR1.GE.2)WRITE(6,1857)IPR,L,NTIME,Q(L) */
    /* CMC  1857 FORMAT(2X,'Q',5X,'ALLOC',I4,5X,'LINK',I4,5X,'TIME',I3,4X, */
    /* CMC      1 F11.3,2X,'RES MODE CALC') */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  Q     AL  %s (%s)     LINK  %s     YEAR%6d    %11.3f  RES MODE CALC\n",
		LinkNodeNames[0][(*ipr)], LinkNodeSector[0][(*ipr)],LinkNodeNames[13][l], var_1.itime,net_1.q[l - 1]/units_1.unitcnvt[8]);
    
    /*<  2707 Q(L)=0.0 >*/
  L2707:
    net_1.q[l - 1] = 0.f;
    /*<       IX=IX+1 >*/
    ++ix;
    /*<       IPAL(IX)=L >*/
    ipal[ix - 1] = l;
    /*<       MPAL(IX)=L >*/
    mpal[ix - 1] = l;
    /*<       KPAL(IX)=J >*/
    kpal[ix - 1] = j;
    /*<   400 CONTINUE >*/
  L400:
    ;
  }
  
  /* ***** RETURN IF IN RES MODE. */
  
  /*<       IF(IRESON.EQ.1)RETURN >*/
  if (mode_1.ireson == 1) {
    return 0;
  }
  
  /* ***** ALLOCATE QUANTITIES AMONG INPUT LINKS ON THE BASIS OF */
  /* ***** PRICES, CAPACITIES, AND PRIORITIES. */
  
  /*<       MX=IX >*/
  mx = ix;
  
  /* **** CHECK FOR ALLOCATION PRIORITIES */
  
  /*<       IF(NALPR(IPR).EQ.0)GO TO 300 >*/
  if (all_1.nalpr[*ipr - 1] == 0) {
    goto L300;
  }
  /*<       K=NALPR(IPR) >*/
  k = all_1.nalpr[*ipr - 1];
  
  /* ***** CHECK FOR GRID/NON-GRID ALLOCATION NODE. */
  
  /*<       IF(NGG(IPR).EQ.0)GO TO 931 >*/
  if (al1_1.ngg[*ipr - 1] == 0) {
    goto L931;
  }
  /*<       K=1 >*/
  k = 1;
  /*<       LGRID=NGG(IPR) >*/
  lgrid = al1_1.ngg[*ipr - 1];
  
  /* ***** ALLOCATE QUANTITIES TO PRIORITY LINKS. */
  
  /*<   931 DO 330 I=1,K >*/
 L931:
  i__1 = k;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IALPR(IPR,I) >*/
    l = ialpr_ref(*ipr, i__);
    /*<       IF(L.EQ.0)GO TO 330 >*/
    if (l == 0) {
      goto L330;
    }
    /*<       DO 319 J=1,IX >*/
    i__2 = ix;
    for (j = 1; j <= i__2; ++j) {
      /*<       IF(IPAL(J).EQ.L)GO TO 321 >*/
      if (ipal[j - 1] == l) {
	goto L321;
      }
      /*<   319 CONTINUE >*/
      /* L319: */
    }
    /*<       GO TO 322 >*/
    goto L322;
    /*<   321 IF(J.EQ.IX)GO TO 399 >*/
  L321:
    if (j == ix) {
      goto L399;
    }
    /*<       IXM=IX-1 >*/
    ixm = ix - 1;
    /*<       DO 327 JV=J,IXM >*/
    i__2 = ixm;
    for (jv = j; jv <= i__2; ++jv) {
      /*<       IPAL(JV)=IPAL(JV+1) >*/
      ipal[jv - 1] = ipal[jv];
      /*<       KPAL(JV)=KPAL(JV+1) >*/
      kpal[jv - 1] = kpal[jv];
      /*<   327 CONTINUE >*/
      /* L327: */
    }
    /*<   399 IX=IX-1 >*/
  L399:
    --ix;
    
    /*<   322 CONTINUE >*/
  L322:
    
    /*<       IF(CAPL(L)-QOUT)310,310,320 >*/
    if (net_1.capl[l - 1] - qout <= 0.f) {
      goto L310;
    } else {
      goto L320;
    }
    /*<   310 Q(L)=CAPL(L) >*/
  L310:
    net_1.q[l - 1] = net_1.capl[l - 1];
    /*<       QOUT=QOUT-Q(L) >*/
    qout -= net_1.q[l - 1];
    /* CMC       IF(IWR1.GE.3)WRITE(6,996) I, L, Q(L)                               bh4-91 */
    /* CMC   996 FORMAT(11X,'PRIORITY ',1I2,3X,'Q(',I3,')=',1F13.2)                 bh4-91 */
    if (var_1.iwr1 >= 3) 
      fprintf(fp6, "           PRIORITY %2d   Q(%s)=%13.2f\n",
	      i__, LinkNodeNames[13][l],net_1.q[l - 1]/units_1.unitcnvt[8]);
    
    /*<       GO TO 330 >*/
    goto L330;
    
    /*<   320 Q(L)=QOUT >*/
  L320:
    net_1.q[l - 1] = qout;
    /*<       DSUP=CAPL(L)-QOUT >*/
    dsup = net_1.capl[l - 1] - qout;
    /*<       QOUT=0.0 >*/
    qout = 0.f;
    /* CMC       IF(IWR1.GE.3)WRITE(6,996) I, L, Q(L)                               bh4-91 */
    if (var_1.iwr1 >= 3) 
      fprintf(fp6, "           PRIORITY %2d   Q(%s)=%13.2f\n",
	      i__, LinkNodeNames[13][l],net_1.q[l - 1]/units_1.unitcnvt[8]);
    
    /* ***** SEND POWER TO GRID IF EXCESS AND A GRID/NON-GRID NODE. */
    
    /*<       IF(NALPR(IPR).GT.0)GO TO 330 >*/
    if (all_1.nalpr[*ipr - 1] > 0) {
      goto L330;
    }
    /*<       Q(LGRID)=-DSUP >*/
    net_1.q[lgrid - 1] = -dsup;
    /*<       Q(L)=CAPL(L) >*/
    net_1.q[l - 1] = net_1.capl[l - 1];
    /* CMC       IF(IWR1.GE.3)WRITE(6,997) LGRID, Q(LGRID)         bh4-91 */
    if (var_1.iwr1 >= 3) 
      fprintf(fp6, "           GRID LINK     Q(%s)=%13.2f\n",
	      LinkNodeNames[13][lgrid], net_1.q[lgrid - 1]/units_1.unitcnvt[8]);
    
    /* CMC       IF(IWR1.GE.3)WRITE(6,997) L, Q(L)               bh4-91 */
    if (var_1.iwr1 >= 3) 
      fprintf(fp6, "           GRID LINK     Q(%s)=%13.2f\n",
	      LinkNodeNames[13][l], net_1.q[l - 1]/units_1.unitcnvt[8]);
    
    
    /* CMC   997 FORMAT(7X,'    GRID LINK   ','  Q(',I3,')=',1F13.2)      bh4-91 */
    
    /*<   330 CONTINUE >*/
  L330:
    ;
  }
  
  /* ***** ALLOCATE QUANTITY QOUT ON THE BASIS OF PRICE SHARES. */
  /* ***** LOAD NP, IPAL, AND IX INITIALLY. */
  
  /*<   300 CONTINUE                                                         >*/
 L300:
  
  /*<       QMS = QOUT                                                       >*/
  qms = qout;
  /*<       KX=IX                                                            >*/
  kx = ix;
  /*<       DO 101 I=1,KX >*/
  i__1 = kx;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       NP(I)=IPAL(I) >*/
    np[i__ - 1] = ipal[i__ - 1];
    /*<   101 CONTINUE >*/
    /* L101: */
  }
  
  /* **** SKIP MS ALLOCATION IF NO MS LINKS, IF STILL MORE Q PRINT MESSAGE   bh4-91 */
  /*<       IF((IX.EQ.0).AND.(QOUT.GT.0.0)) GO TO 309                          >*/
  if (ix == 0 && qout > 0.f) {
    goto L309;
  }
  /*<       IF(IX.EQ.0)GO TO 619                                               >*/
  if (ix == 0) {
    goto L619;
  }
  
  /* **** COMPUTE DENOMINATOR (PD) FOR MARKET SHARE CALCULATION */
  /* **** GIVEN IPR. */
  
  /* ........COMPUTE SCALE FACTOR SSP FOR PRICES IF NECESSARY. */
  /*<       LGFLG = -1                                                         >*/
  lgflg = -1;
  
  /* CMC       IF(IWR1.GE.3) WRITE(6,992) QMS                           bh4-91 */
  if (var_1.iwr1 >= 3) 
    fprintf(fp6, "                       ALLOCATE=%13.2f\n", qms/units_1.unitcnvt[8]);
  /* CMC   992 FORMAT(23X,'ALLOCATE=',1F13.2)                                     bh4-91 */
  /*<   301 PD=0. >*/
 L301:
  pd = 0.f;
  /*<       LALL=0 >*/
  lall = 0;
  /*<       SSP=1.00 >*/
  ssp = 1.f;
  /*                                                                        JL5-96 */
  /*      DO 2371 I=1,IX                                                    JL5-96 */
  /*      L=IPAL(I)                                                         JL5-96 */
  /*      K=KPAL(I)                                                         JL5-96 */
  /*      PTERM=P(L)*PREM(IPR,K)                                            JL5-96 */
  /*      IF(PTERM.GT.300.0)SSP=.01                                         JL5-96 */
  
  /* ........IF A ZERO PRICE EXISTS ON AN INPUT LINK, */
  /*        ALLOCATE ALL OUTPUT QUANTITY TO THE LINK. */
  
  /*     IF(PTERM.LT.1.E-10)GO TO 2372                                      bh4-91 */
  /* 2371 CONTINUE                                                          JL5-96 */
  /*      GO TO 2366                                                        JL5-96 */
  
  /* 2372 LALL=L                                                            JL5-96 */
  /*      GO TO 2374                                                        JL5-96 */
  
  /*<  2366 DO 371 I=1,IX >*/
  /* L2366: */
  i__1 = ix;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IPAL(I) >*/
    l = ipal[i__ - 1];
    /*<       K=KPAL(I) >*/
    k = kpal[i__ - 1];
    
    /* ........SCALE PRICE. */
    
    /*      PTERM=P(L)*PREM(IPR,K)                                             JL5-96 */
    /*      IF(PTERM.GT.300.0)SSP=.01                                          JL5-96 */
    /*<       PPS=P(L)*PREM(IPR,K)*SSP >*/
	
	pps = net_1.p[l - 1] * prem_ref(*ipr, k) * ssp;

    
    /*      SSP = 1.0                                                          JL5-96 */
    
    /* ........COMPUTE DENOMINATOR OF MARKET SHARE EQUATION. */
    
    /* +++++ SECOND CHANGE +++++ */
    
    /*     IF (PPS.GT.0.009)GO TO 3515                                        bh4-91 */
    /*<       IF (PPS.LT.0.01)PPS = 0.01                                         >*/
    if (pps < .01f) {
      pps = .01f;
    }
    /*      LALL=L                                                            bh4-91 */
    /*      GO TO 2374                                                        bh4-91 */
    /* 3515  continue */
    /*<        DEN= (1./PPS)**GM(IPR) >*/
    d__1 = (doublereal) (1.f / pps);
    d__2 = (doublereal) all_1.gm[*ipr - 1];
    den = pow_dd(&d__1, &d__2);
    
    /* ........ACCUMULATE DENOMINATOR TERM. */
    
    /*<       PD=PD + DEN >*/
    pd += den;
    /*<   371 CONTINUE >*/
    /* L371: */
  }
  
  /* ***** COMPUTE MARKET SHARES. */
  
  /*<  2374 QREAL=0.0 >*/
  /* L2374: */
  qreal = 0.f;
  /*<       QALL=0.0 >*/
  qall = 0.f;
  /*<       NX=0 >*/
  nx = 0;
  
  /*<       DO 116 I=1,IX >*/
  i__1 = ix;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IPAL(I) >*/
    l = ipal[i__ - 1];
    /*<       K=KPAL(I) >*/
    k = kpal[i__ - 1];
    /*<       IF(L.EQ.LGRID)GO TO 421 >*/
    if (l == lgrid) {
      goto L421;
    }
    /*<       IF(LALL.GT.0)GO TO 6604 >*/
    if (lall > 0) {
      goto L6604;
    }
    
    /*<       PPS=P(L)*PREM(IPR,K)*SSP >*/
    pps = net_1.p[l - 1] * prem_ref(*ipr, k) * ssp;

	
    /*<       IF (PPS.LT.0.01)PPS = 0.01                                         >*/
    if (pps < .01f) {
      pps = .01f;
    }
    /*<       DEN= (1./PPS)**GM(IPR) >*/
    d__1 = (doublereal) (1.f / pps);
    d__2 = (doublereal) all_1.gm[*ipr - 1];
    den = pow_dd(&d__1, &d__2);
    /*<       VNEWMS = DEN/PD                                                    >*/
    vnewms = den / pd;
    /*<       VMS = VNEWMS                                                       >*/
    vms = vnewms;
    /*<       IF (LGFLG.EQ.0) GO TO 995                                          >*/
    if (lgflg == 0) {
      goto L995;
    }
    /*                                                                        bh4-91 */
    /* **** IF FIRST PASS THROUGH APPLY THE LAG FUNCTION                       bh4-91 */
    /*<       VLAG = BL(IPR)                                                     >*/
    vlag = all_1.bl[*ipr - 1];
    /*<       IF (POQUAN(IPR).EQ.0.0 .OR. QMS.EQ.0.0) VLAG=1.0                   >*/
    if (all_1.poquan[*ipr - 1] == 0.f || qms == 0.f) {
      vlag = 1.f;
    }
    /*<       VMS = VNEWMS*VLAG + OMS(IPR,I)*(1.0-VLAG)                          >*/
    vms = vnewms * vlag + oms_ref(*ipr, i__) * (1.f - vlag);
    /*                                                                        bh4-91 */
    /*<   995 CONTINUE                                                           >*/
  L995:
    /*     Q(L)= QOUT*DEN/PD                                                  bh4-91 */
    /*<       Q(L)= Q(L) + QOUT*VMS                                              >*/
    net_1.q[l - 1] += qout * vms;
    /*<       GO TO 6603 >*/
    goto L6603;
    
    /* ........ASSIGN TOTAL Q TO INPUT LINK WITH ZERO P. */
    
    /*<  6604 Q(L)=0.0 >*/
  L6604:
    net_1.q[l - 1] = 0.f;
    /*<       IF(L.EQ.LALL)Q(L)=QOUT >*/
    if (l == lall) {
      net_1.q[l - 1] = qout;
    }
    
    /* ........CHECK IF ALLOCATED QUANTITY EXCEEDS CAPACITY. */
    
    /*<  6603 IF(Q(L)-CAPL(L))421,421,422 >*/
  L6603:
    if (net_1.q[l - 1] - net_1.capl[l - 1] <= 0.f) {
      goto L421;
    } else {
      goto L422;
    }
    /*<   421 NX=NX+1 >*/
  L421:
    ++nx;
    /*<       IPAL(NX)=L >*/
    ipal[nx - 1] = l;
    /*<       KPAL(NX) = K                                                       >*/
    kpal[nx - 1] = k;
    
    /*<       IF(IWR1.GE.3 .AND. LGFLG.NE.0 .AND. QMS.NE.0.0)  >*/
    /* CMC      1   WRITE(6,993) VMS, L, Q(L), VNEWMS, OMS(IPR,I), VLAG             bh4-91 */
    /* CMC   993 FORMAT(15X,'MS=',1F5.3,'  Q(',I3,')=',1F13.2,'   NMS=',1F5.3,      bh4-91 */
    /* CMC      1  '  OMS=',1F5.3,'  LAG=',1F5.3)                                   bh4-91 */
    if (var_1.iwr1 >= 3 && lgflg != 0 && qms != 0.f) 
      fprintf(fp6, "               MS=%5.3f  Q(%s)=%13.2f   NMS=%5.3f  OMS=%5.3f  LAG=%5.3f\n",
	      vms,LinkNodeNames[13][l],net_1.q[l - 1]/units_1.unitcnvt[8],vnewms,oms_ref(*ipr, i__),vlag );
    
    
    
    /* CMC       IF(IWR1.GE.3 .AND. LGFLG.EQ.0) WRITE(6,998) VMS, L, Q(L)           bh4-91 */
    /* CMC   998 FORMAT(15X,'MS=',1F5.3,'  Q(',I3,')=',1F13.2)                      bh4-91 */
    /*<       GO TO 116 >*/
    
    if (var_1.iwr1 >= 3 && lgflg == 0) 
      fprintf(fp6, "               MS=%5.3f  Q(%s)=%13.2f\n",
	      vms,LinkNodeNames[13][l],net_1.q[l - 1]/units_1.unitcnvt[8]);
    
    goto L116;
    
    /* ***** QREAL IS TOTAL QUANTITY TO REALOOLOCATE TO UNCAPACITATED LINKS */
    /* ***** BASED ON RELATIVE PRICES. */
    
    /*<   422 QREAL=QREAL+Q(L)-CAPL(L) >*/
  L422:
    qreal = qreal + net_1.q[l - 1] - net_1.capl[l - 1];
    /*<       Q(L)=CAPL(L) >*/
    net_1.q[l - 1] = net_1.capl[l - 1];
    /*     QALL=QALL+Q(L)                                                     bh4-91 */
    
    /*<       IF(IWR1.GE.3 .AND. LGFLG.NE.0)  CONTINUE >*/
    /* CMC ADDED CONTINUE ABOVE                                   bh4-91 */
    /* CMC      1   WRITE(6,994) VMS, L, Q(L), VNEWMS, OMS(IPR,I), VLAG, QREAL      bh4-91 */
    /* CMC   994 FORMAT(15X,'MS=',1F5.3,'  Q(',I3,')=',1F13.2,'   NMS=',1F5.3,      bh4-91 */
    /* CMC     +  '  OMS=',1F5.3,'  LAG=',1F5.3,/,14X,                             bh4-91 */
    /* CMC     + '       REALLOCATE=',1F13.2)                                      bh4-91 */
    if (var_1.iwr1 >= 3 && lgflg != 0) 
      fprintf(fp6, "               MS=%5.3f  Q(%s)=%13.2f   NMS=%5.3f  OMS=%5.3f  LAG=%5.3f\n                     REALLOCATE=%13.2f\n",
	      vms,LinkNodeNames[13][l],net_1.q[l - 1]/units_1.unitcnvt[8],vnewms,oms_ref(*ipr, i__),vlag, qreal/units_1.unitcnvt[8] );
    
    
    /* CMC       IF(IWR1.GE.3 .AND. LGFLG.EQ.0) WRITE(6,999) VMS, L, Q(L), QREAL    bh4-91 */
    /* CMC   999 FORMAT(15X,'MS=',1F5.3,'  Q(',I3,')=',1F13.2,/,14X,                bh4-91 */
    /* CMC     + '       REALLOCATE=',1F13.2)                                      bh4-91 */
    if (var_1.iwr1 >= 3 && lgflg == 0) 
      fprintf(fp6, "               MS=%5.3f  Q(%s)=%13.2f\n                     REALLOCATE=%13.2f\n",
	      vms,LinkNodeNames[13][l],net_1.q[l - 1]/units_1.unitcnvt[8],qreal/units_1.unitcnvt[8]);
    
    /*<   116 CONTINUE >*/
  L116:
    ;
  }
  
  /* ***** IX IS NUMBER OF LINKS UNCAPCITATED BEFORE Q REASSIGNMENT. */
  /* ***** NX IS NUMBER OF LINKS UNCAPACITATED AFTER Q REASSIGNMENT. */
  /* ***** IF NX EQ IX, ALL LINKS WITHIN CAPACITY AND NO FURTHER */
  /* ***** Q REASSIGNMENT IS NECESSARY. */
  /* ***** IF NX EQ 0, NO Q REASSIGNMENT IS POSSIBLE. */
  
  /*<       IF(NX.EQ.IX)GO TO 619 >*/
  if (nx == ix) {
    goto L619;
  }
  /*<       IF(NX.EQ.0)GO TO 309 >*/
  if (nx == 0) {
    goto L309;
  }
  /*<       IX=NX >*/
  ix = nx;
  /*     QOUT=QOUT-QALL                                                     bh4-91 */
  /*<       QOUT=QREAL                                                         >*/
  qout = qreal;
  /*<       LGFLG = 0                                                          >*/
  lgflg = 0;
  /*<       GO TO 301 >*/
  goto L301;
  
  /*<  309  CONTINUE >*/
 L309:
  /* CMC   309 IF(IWR1.GE.2)WRITE(6,777) */
  /* CMC   777 FORMAT(2X,'CAPACITY EXCEEDED ON ALL REMAINING ALLOCATION LINKS,', */
  /* CMC      1 ' QUANTITIES ARE CAPACITIES') */
  if (var_1.iwr1 >= 2) {
    fprintf(fp6, "  CAPACITY EXCEEDED ON ALL REMAINING ALLOCATION LINKS, QUANTITIES ARE CAPACITIES\n");
    fprintf(fp21, "Warning: Capacity exceeded on all remaining allocation links, quantities are capacities\n");

  }

  /* CMC       WRITE(*,778) */
  /* CMC   778 FORMAT(2X,'CAPACITY LIMIT REACHED ON ALL INPUT LINKS TO AN', */
  /* CMC      1 'ALLOCATION NODE.',/,'     CHECK DETAILED OUTPUT REPORT.') */
  
    fprintf(fp21, "Warning: Capacity limit reached on all input links to an allocation node. Check detailed output report.\n");


  /*<   619 DO 1212 I=1,MX >*/
 L619:
  i__1 = mx;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=MPAL(I) >*/
    l = mpal[i__ - 1];
    /*<       PMS=0.0 >*/
    pms = 0.f;


    /*<       IF(QVOUT(IPR).LT.0.0001)GO TO 1214                                 >*/
    if (qvout[*ipr - 1] < 1e-4f) {
      goto L1214;
    }
    /*<       PMS=Q(L)/QVOUT(IPR) >*/
    pms = net_1.q[l - 1] / qvout[*ipr - 1];
    
    /*<  1214 CONTINUE                                                           >*/
  L1214:
    /*     Q(L)=QVOUT(IPR)*PMS                                                bh4-91 */
    /*     QDUM=Q(L)                                                          bh4-91 */
    /* **** SHR() IS FRACTION OF (QUAN-STOCKS) ALLOCATED TO EACH INPUT LINK.   bh4-91 */
    /*<       SHR(IPR,I)=PMS >*/
    shr_ref(*ipr, i__) = pms;
    /*     IF(QINSV(IPR).LE.0.0001)GO TO 1230                                 bh4-91 */
    /*     SHR(IPR,I)=PMS*BL(IPR)+RMS(IPR,I)*(1.-BL(IPR))                     bh4-91 */
    /*     Q(L)=QVOUT(IPR)*SHR(IPR,I)                                         bh4-91 */
    
    /*<  1230 CONTINUE >*/
    /* L1230: */
    /*<       IF(IWR1.EQ.0)GO TO 1227 >*/
    if (var_1.iwr1 == 0) {
      goto L1227;
    }
    /*<  4378 CONTINUE >*/
    /* L4378: */
    /*<       IF(NALPR(IPR).GT.0)GO TO 1426 >*/
    if (all_1.nalpr[*ipr - 1] > 0) {
      goto L1426;
    }
    /*<  1427 CONTINUE                                                           >*/
  L1427:
    /*     CALCULATE THE MARKET SHARE FOR THIS MS LINK                        bh4-91 */
    /*<       TMPMS = 0.0                                                        >*/
    tmpms = 0.f;
    /*<       IF(QMS.GT.0.0001) TMPMS = Q(L) / QMS                               >*/
    if (qms > 1e-4f) {
      tmpms = net_1.q[l - 1] / qms;
    }
    /* CMC       IF(IWR1.GE.2)WRITE(6,1702)IPR,L,NTIME,Q(L),SHR(IPR,I),TMPMS        bh4-91 */
    /* CMC  1702 FORMAT(2X,'Q',5X,'ALLOC',I4,5X,'LINK',I4,5X,'TIME',                bh4-91 */
    /* CMC      1 I3,4X,F11.3,2X,'SHR=',F5.3,2X,' MS=',F5.3)    */
    	if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  Q     AL  %s (%s)     LINK  %s     YEAR%6d    %11.3f  SHR=%5.3f   MS=%5.3f\n",
	      LinkNodeNames[0][(*ipr)], LinkNodeSector[0][(*ipr)],LinkNodeNames[13][l],var_1.itime,net_1.q[l - 1]/units_1.unitcnvt[8],shr_ref(*ipr, i__),tmpms);
    

    /*<       GO TO 1227 >*/
    goto L1227;
    
    /*<  1426 NN=NALPR(IPR) >*/
  L1426:
    nn = all_1.nalpr[*ipr - 1];
    /*<       DO 1425 M=1,NN >*/
    i__2 = nn;
    for (m = 1; m <= i__2; ++m) {
      /*<       IF(L.EQ.IALPR(IPR,M))GO TO 1226 >*/
      if (l == ialpr_ref(*ipr, m)) {
	goto L1226;
      }
      /*<  1425 CONTINUE >*/
      /* L1425: */
    }
    /*<       GO TO 1427 >*/
    goto L1427;
    /*<  1226 CONTINUE >*/
  L1226:
    /* CMC  1226 IF(IWR1.GE.2)WRITE(6,1326)IPR,L,NTIME,Q(L),SHR(IPR,I),M            bh4-91 */
    /* CMC  1326 FORMAT(2X,'Q',5X,'ALLOC',I4,5X,'LINK',I4,5X,'TIME', */
    /* CMC      1 I3,4X,F11.3,2X,'SHR=',F5.3,'  PRI',I2)                            bh4-91 */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  Q     AL  %s (%s)     LINK  %s     YEAR%6d    %11.3f  SHR=%5.3f  PRI%2d\n",
	      LinkNodeNames[0][(*ipr)], LinkNodeSector[0][(*ipr)],LinkNodeNames[13][l], var_1.itime,net_1.q[l - 1]/units_1.unitcnvt[8], shr_ref(*ipr, i__),m);
    
    /*<  1227 CONTINUE >*/
  L1227:
    /*<  1212 CONTINUE >*/
    /* L1212: */
    ;
  }
  
  /*<       RETURN >*/
  return 0;
  
  /*<       END >*/
}  /* al_ */
  
#undef rms_ref
#undef zen_ref
#undef oms_ref
#undef shr_ref
#undef sen_ref
#undef split_ref
#undef ioual_ref
#undef ialpr_ref
#undef iinal_ref
#undef prem_ref
  
