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

/* b7.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
   -lf2c -lm   (in that order)
   */
#include <stdio.h>
#include "cmc_f2c.h"
#include <stdlib.h>
#include "f2c.h"


/* Common Block Declarations */

struct {
	char unitcode[13][50];
	char unitname[13][50];
	real unitcnvt[13];
} units_;

#define units_1 units_


union {
    struct {
		integer itn, itmax, ntime, nper;
		real rctol, epsn;
		integer iwr1, nnrep, nnrnp, nnpr, iers, ires, lnkmx, nrsmx;
		real whi, wlo, actol;
		integer nrnmx;
		real shr[4000]	/* was [200][10] */;
		integer nprmx, idmp[75], iyrb, itime, nnall, nnre, nnde, nnlnk, nnst,nnmi;
		real qscale;
		char qu[15], pu[15];
    } _1;
    struct {
		integer itn, itmax, ntime, nper;
		real rctol, epsn;
		integer iwr1, nnrep, nnrnp, nnpr, iers, ires, lnkmx, nrsmx;
		real whi, wlo, actol;
		integer nrnmx;
		real shr[4000]	/* was [200][10] */;
		integer nprmx, idmp[75], iyrb, itime, nnall, nnre, nnde, nnlnk, nnst,nnmi;
		real qscale;
		char qu[15], pu[15];
    } _2;
} var_;

#define var_1 (var_._1)
#define var_2 (var_._2) 


struct {
  real q[999], p[999], capl[999];
  integer lab[5], iuse[300], luse[999];
  real noTaxPrice[999];
} net_;

#define net_1 net_


struct {
  integer iours[75];
  real qt[92], hqt[92], hqtm[92], qtm[92], a[75], b[75];
  /* integer labr[375];	/* was [75][5] */
  char cmc_labr[75][30];
  real pprj[5625]	/* was [75][75] */;
  integer kpr[75];
  real plast[75], ab[75];
  real Efactors[75][50][3];		/* 75 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  real		noTaxPrice[75][75];
  real		fuelCost[75][75];
  real		economicRent[75][75];
  real		cumulativeQ[75][75];
} res_;

#define res_1 res_

struct {
  integer ndemx, iinde[200];
  char cmc_labd[200][20];
  real drat[15000]	/* was [200][75] */;
  integer kd[200];
  real qbase[200];
  real Efactors[200][50][3];		/* 200 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emiision tax */
} dem_;

#define dem_1 dem_

struct {
	/* increase arry size from 100 to 300 */
  real alpha[300], delta[300], pmax[300], pmin[300];
  integer iinpp[300];
  real pscale;
  integer ioupp[300];
  char cmc_labp[300][20];
  real sen[1500],	/* was [20][75]; sen is related stock pile rather than pricing node */
	   zen[149850]	/* was [2][999][75]; zen is used to store p and q values for all links */
    ;
  integer ioutx;
  integer linkp[300];
} pri_;


#define pri_1 pri_


struct {
  integer iinpr[300], ioupr[300];
  real om[300], cc[300], eff[300], tci[300], capm[300], cf[300];
  integer life[300];
  real rir[300];
  char cmc_labc[300][20];
  real Efactors[300][50][3];		/* 300 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  integer	baseYearLife[300] ;
  real		baseYearCap[300];
  real		baseYearCapital[300];
  integer	opUnits[300][75];
  real		opCap[300][75];
  integer	baseUnits[300][75];
  real		baseCap[300][75];
  real		baseSunk[300][75];
  integer	existingUnits[300][75];
  real		existingCap[300][75];
  real		existingSunk[300][75];
  real		demandNotServed[300][75];
  integer	newUnits[300][75];
  real		newCap[300][75];
  real		newCapital[300][75];
  real		operatingCost[300][75];
  real		totalCapital[300][75];
  real		avgInvestment[300][75];
  real		avgCap[300][75];
  real		avgCF[300][75];
  real		outputCapability[300][75];
} pro_;

#define pro_1 pro_

struct {
	/* MI Nodes have been increased from 15 to 200 */
  integer ninmi[200], iinmi[1000]	/* was [15][5] */, ioumi[200];
  real omm[200], ccm[200], rio[1000]	/* was [15][5] */, tcim[200], capmm[200], cfm[200];
  integer lifem[200];
  real rirm[200];
  char cmc_labm[201][30];	/* was [15][20] changed to [16][30] - Prakash */

  real prem[4000]	/* was [200][10] */;
  integer nremx, nmimx;
  real Efactors[200][50][3];		/* 200 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  integer	baseYearLife[200] ;
  real		baseYearCap[200];
  real		baseYearCapital[200];
  integer	opUnits[200][75];
  real		opCap[200][75];
  integer	baseUnits[200][75];
  real		baseCap[200][75];
  real		baseSunk[200][75];
  integer	existingUnits[200][75];
  real		existingCap[200][75];
  real		existingSunk[200][75];
  real		demandNotServed[200][75];
  integer	newUnits[200][75];
  real		newCap[200][75];
  real		newCapital[200][75];
  real		operatingCost[200][75];
  real		totalCapital[200][75];
  real		avgInvestment[200][75];
  real		avgCap[200][75];
  real		avgCF[200][75];
  real		outputCapability[200][75];
} min_;

#define min_1 min_

struct {
  integer ninre[30], iinre[60]	/* was [30][2] */, noure[30], ioure[
								    180]	/* was [30][6] */, istck[180]	/* was [30][6] */;
  real pff[30];
  integer ixces[180]	/* was [30][6] */;
  real slate[180]	/* was [30][6] */, omr[30], ccr[30], prat[180]	/* 
			   was [30][6] */;
  integer iordc[30];
  real tcir[30], capmr[30], cfr[30];
  integer lifer[30];
  real rirr[30];
  char cmc_labe[30][20];

  real remul[180]	/* was [30][6] */;
  integer icntl[180]	/* was [30][6] */, linpr[180]	/* was [30][6] */;
  real Efactors[30][50][3];		/* 30 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  integer	baseYearLife[30] ;
  real		baseYearCap[30];
  real		baseYearCapital[30];
  integer	opUnits[30][75];
  real		opCap[30][75];
  integer	baseUnits[30][75];
  real		baseCap[30][75];
  real		baseSunk[30][75];
  integer	existingUnits[30][75];
  real		existingCap[30][75];
  real		existingSunk[30][75];
  real		demandNotServed[30][75];
  integer	newUnits[30][75];
  real		newCap[30][75];
  real		newCapital[30][75];
  real		operatingCost[30][75];
  real		totalCapital[30][75];
  real		avgInvestment[30][75];
  real		avgCap[30][75];
  real		avgCF[30][75];
  real		outputCapability[30][75];
} ref_;

#define ref_1 ref_

struct {
  integer iourn[17];
  real prn[85]	/* was [17][5] */, qrn[85]	/* was [17][5] */;
  integer  nstep[17];
  char cmc_labn[17][20];

  real rlim[17];
  integer mup[17], jwrit[75], itfir[75], itlas[75];
  char ititl[6][256];								/* was integer changed to char -Prakash */
  real Efactors[17][50][3];		/* 17 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  real		economicRent[17][75];
  real		fuelCost[17][75];
  real		noTaxPrice[17][75];
} ren_;

#define ren_1 ren_

struct {
  integer ioust[20];
  real stok[20], st[20];
  char cmc_labs[20][20];
  integer ialst[400], istc[20], istkexl[20];
  real stkexr[20];
} stk_;

#define stk_1 stk_



/* ******************************************************************** RE */

/* CMC 990427 CHANGED MMMI BELOW INTO NNMI IN COMMON BLOCK ALL */

/*<       SUBROUTINE RE(IPASS,IPR,KSPEC) >*/
/* Subroutine */ int re_(integer *ipass, integer *ipr, integer *kspec)
{
  int ct;
  extern int emisflag;
  extern FILE *fp11, *fp6, *fp25;
  extern char LinkNodeNames[14][999][6];
  extern char LinkNodeSector[14][999][6];
  real emisTax;
  int i,j;
  /* System generated locals */
  integer i__1;
  
  /* Local variables */
  static real delq;
  static integer iord, nout;
  static real qreq;
  static integer i__, k, l, j1[6], j2[6];
  static real t1, t2, t3, t4;
  static integer l2;
  static real qrmax;
  static integer la, in, ll, lk, lp;
  static real pq;
  static integer ns, lx, nj1, nj2, las, lin, ipm, nou;
  
/*#define labe_ref(a_1,a_2) ref_1.labe[(a_2)*30 + a_1 - 31] */
#define prat_ref(a_1,a_2) ref_1.prat[(a_2)*30 + a_1 - 31]
#define iinre_ref(a_1,a_2) ref_1.iinre[(a_2)*30 + a_1 - 31]
#define ioure_ref(a_1,a_2) ref_1.ioure[(a_2)*30 + a_1 - 31]
#define istck_ref(a_1,a_2) ref_1.istck[(a_2)*30 + a_1 - 31]
#define ixces_ref(a_1,a_2) ref_1.ixces[(a_2)*30 + a_1 - 31]
#define slate_ref(a_1,a_2) ref_1.slate[(a_2)*30 + a_1 - 31]
#define remul_ref(a_1,a_2) ref_1.remul[(a_2)*30 + a_1 - 31]
#define icntl_ref(a_1,a_2) ref_1.icntl[(a_2)*30 + a_1 - 31]
#define linpr_ref(a_1,a_2) ref_1.linpr[(a_2)*30 + a_1 - 31]
#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
  
  /*<       DIMENSION PC(6),J1(6),J2(6) >*/
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
  
  /*<       NOU=NOURE(IPR) >*/
  nou = ref_1.noure[*ipr - 1];
  /*<       GO TO(4409,4409,4409,4409,4455,4455,4455),IPASS >*/
  switch (*ipass) {
  case 1:  goto L4409;
  case 2:  goto L4409;
  case 3:  goto L4409;
  case 4:  goto L4409;
  case 5:  goto L4455;
  case 6:  goto L4455;
  case 7:  goto L4455;
  }
  
  /* CMC  4903 FORMAT(2X,5A4) */
  /*<  4455 CONTINUE >*/
 L4455:
  /* CMC  4455 IF(IPASS.GE.6)WRITE(11,4903)(LABE(IPR,J),J=1,4) */
  if (*ipass >= 6) {
      fprintf(fp11, "  %s\n", ref_1.cmc_labe[*ipr]);

  }
  
  /*<       DO 4410 I=1,NOU >*/
  i__1 = nou;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IOURE(IPR,I) >*/
    l = ioure_ref(*ipr, i__);
    
    /*<       IF(IPASS.LT.6)GO TO 4667 >*/
    if (*ipass < 6) {
      goto L4667;
    }
    /*<       IPM=IPASS-5 >*/
    ipm = *ipass - 5;
    /* CMC       IF(IPASS.EQ.6)WRITE(11,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
    /* CMC  4411 FORMAT(1X,I4,1X,'Q',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
    /* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
    /* CMC      2  ,/,10X,5F11.1) */
    if (*ipass == 6) {
      fprintf(fp11, " %4d Q   ",l);
      for (j = 1; j <= pri_1.ioutx; ++j) {
	if(( (j-1)%10==0)&& (j>1) )fprintf(fp11, "\n          ");
	fprintf(fp11, "%11.1f", zen_ref(1,l,j));
	
      }
      fprintf(fp11, "\n");
    }
    
    /* CMC       IF(IPASS.EQ.7)WRITE(11,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
    /* CMC  4412 FORMAT(1X,I4,1X,'P',3X,10F9.2,/,10X,10F9.2,/,10X,10F9.2 */
    /* CMC      1   ,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F2.2 */
    /* CMC      2   ,/,10X,5F9.2) */
    if (*ipass == 7) {
		/* fprint was printing Q instead of P - Prakash  */
      fprintf(fp11, " %4d P   ",l);
      for (j = 1; j <= pri_1.ioutx; ++j) {
	if(( (j-1)%10==0)&& (j>1) )fprintf(fp11, "\n          ");
	fprintf(fp11, "%9.2f", zen_ref(2,l,j));
      }
      fprintf(fp11, "\n");
    }
    /*<       GO TO 4410 >*/
    goto L4410;
    
    /*<  4667 PQ=P(L)*Q(L) >*/
  L4667:
    pq = net_1.p[l - 1] * net_1.q[l - 1];
    /*<       ZEN(1,L,IOUTX)=Q(L)*QSCALE >*/
    zen_ref(1, l, pri_1.ioutx) = net_1.q[l - 1] * var_1.qscale;
    /*<       ZEN(2,L,IOUTX)=P(L)*PSCALE >*/
    zen_ref(2, l, pri_1.ioutx) = net_1.p[l - 1] * pri_1.pscale;
    /*<  4410 CONTINUE >*/
  L4410:
    ;
  }
  /*<       RETURN >*/
  return 0;
  
  /*<  4409 CONTINUE >*/
 L4409:
  /*<       IF(IPASS.EQ.2)GO TO 200 >*/
  if (*ipass == 2) {
    goto L200;
  }
  
  /* ***** UP-PASS LOGIC STARTS HERE. */
  
  /*<       IN=IINRE(IPR,1) >*/
  in = iinre_ref(*ipr, 1);
  
  /* ***** COMPUTE PRODUCT PRICES BASED ON TOTAL REVENUE = TOTAL COST */
  /* *****  X (1 + PROFIT FACTOR). */
  
  /*<       NJ1=0 >*/
  nj1 = 0;
  /*<       NJ2=0 >*/
  nj2 = 0;
  
  /* ***** LOOP OVER SECOND TO LAST OUTPUT LINKS AND SORT INTO TWO */
  /* ***** GROUPS.  GROUP 1 CONSISTS OF LINKS WITH P BASED ON INPUT */
  /* ***** P.  GROUP 2 CONSISTS OF LINKS WITH P BASED ON FIRST OUTPUT */
  /* ***** LINK P. */
  
  /*<       DO 10 I=2,NOU >*/
  i__1 = nou;
  for (i__ = 2; i__ <= i__1; ++i__) {
    /*<       LAS=LINPR(IPR,I) >*/
    las = linpr_ref(*ipr, i__);
    /*<       IF(LAS.NE.IN)GO TO 11 >*/
    if (las != in) {
      goto L11;
    }
    
    /* ***** PRICE BASED ON INPUT LINK. */
    
    /*<       NJ1=NJ1+1 >*/
    ++nj1;
    /*<       J1(NJ1)=I >*/
    j1[nj1 - 1] = i__;
    /*<       GO TO 10 >*/
    goto L10;
    
    /* ***** PRICE BASED ON FIRST OUTPUT LINK. */
    
    /*<    11 NJ2=NJ2+1 >*/
  L11:
    ++nj2;
    /*<       J2(NJ2)=I >*/
    j2[nj2 - 1] = i__;
    /*<    10 CONTINUE >*/
  L10:
    ;
  }
  
  /* ***** J1 IS SET OF LINKS (ORDINAL) WHOSE PRICE WILL BE BASED ON */
  /* ***** THE INPUT PRICE.  J2 IS SET OF LINKS(ORDINAL) WHOSE PRICE */
  /* ***** WILL BE BASED ON THE FIRST OUTPUT PRICE. */
  
  /* ***** COMPUTE FIRST TERM. */
  
  /*<       T1=(P(IN)+OMR(IPR)+CCR(IPR))*(1.+PFF(IPR)) >*/
  t1 = (net_1.p[in - 1] + ref_1.omr[*ipr - 1] + ref_1.ccr[*ipr - 1])
    * (ref_1.pff[*ipr - 1] + 1.f);
  
  /* ***** COMPUTE SECOND TERM. */
  
  /*<       T2=0.0 >*/
  t2 = 0.f;
  /*<       IF(NJ1.EQ.0)GO TO 12 >*/
  if (nj1 == 0) {
    goto L12;
  }
  /*<       DO 13 I=1,NJ1 >*/
  i__1 = nj1;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       IORD=J1(I) >*/
    iord = j1[i__ - 1];
    /*<       T2=T2 + PRAT(IPR,IORD)*SLATE(IPR,IORD) >*/
    t2 += prat_ref(*ipr, iord) * slate_ref(*ipr, iord);
    /*<    13 CONTINUE >*/
    /* L13: */
  }
  /*<       T2=P(IN)*T2 >*/
  t2 = net_1.p[in - 1] * t2;
  
  /* ***** COMPUTE THIRD TERM. */
  
  /*<    12 T3=0.0 >*/
 L12:
  t3 = 0.f;
  t4=0.f;
  /*<       IF(NJ2.EQ.0)GO TO 14 >*/
  if (nj2 == 0) {
    goto L14;
  }
  /*<       DO 15 I=1,NJ2 >*/
  i__1 = nj2;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       IORD=J2(I) >*/
    iord = j2[i__ - 1];
    /*<       T3=T3+PRAT(IPR,IORD)*SLATE(IPR,IORD) >*/
    t3 += prat_ref(*ipr, iord) * slate_ref(*ipr, iord);
	
    /*<    15 CONTINUE >*/
    /* L15: */
  }
  /*<    14 T3 = T3 + SLATE(IPR,1) >*/
 L14:
  t3 += slate_ref(*ipr, 1);
  
  /* ***** ASSIGN PRODUCT PRICES TO FIRST REFINERY OUTPUT LINK. */
  
  for(i__=1;i__<=nou;++i__)
	t4 += slate_ref(*ipr, i__);


  /*<       L=IOURE(IPR,1) >*/
  l = ioure_ref(*ipr, 1);
  /*<       P(L)=(T1-T2)/T3 >*/
  net_1.p[l - 1] = (t1 - t2) / t3;
 
  /* compute emission tax and add to price */
  emisTax=0;
  for(i=0;i<50;i++){
	  emisTax = emisTax + ref_1.Efactors[*ipr-1][i][0] * ref_1.Efactors[*ipr-1][i][1]
				* 5.7356 * ref_1.Efactors[*ipr-1][i][2]/1000/t4;
	}

  /*fprintf(fp25, "Year  Itn NodeType   NodeName   Sector   UEmisTax   Total P   Quantity\n");*/
	if(emisflag==1)
		fprintf(fp25, "%4d%  3d    RE         %s      %s  %10.4f       %10.4f\n",
			var_1.itime, var_1.itn, LinkNodeNames[5][(*ipr)],LinkNodeSector[5][(*ipr)],emisTax/units_1.unitcnvt[3], 
			(emisTax+net_1.p[l - 1])/units_1.unitcnvt[3]);
		
	

  net_1.p[l - 1]=net_1.p[l - 1] + emisTax;

  /*<       IF(NTIME.EQ.1)Q(L)=Q(IN)*SLATE(IPR,1) >*/
  if (var_1.ntime == 1) {
    net_1.q[l - 1] = net_1.q[in - 1] * slate_ref(*ipr, 1);
  }
  /* CMC       IF(IWR1.GE.2)WRITE(6,202)IPR,L,NTIME,P(L) */
  /* CMC   202 FORMAT(2X,'P',5X,'REFRY',I4,5X,'LINK',I4,5X,'TIME', */
  /* CMC      1I3,4X,1H$,F10.4) */
  if (var_1.iwr1 >= 2) 
    fprintf(fp6, "  P     RE  %s (%s)     LINK  %s     YEAR%6d    $%10.4f\n",
	    LinkNodeNames[5][(*ipr)], LinkNodeSector[5][(*ipr)],LinkNodeNames[13][l], var_1.itime, net_1.p[l - 1]/units_1.unitcnvt[3]);
  
  /*<       IF(NOU.EQ.1)GO TO 16 >*/
  if (nou == 1) {
    goto L16;
  }
  
  /* ***** ASSIGN PRODUCT PRICES TO REMAINING REFINERY OUTPUT LINKS. */
  
  /*<       DO 17 I=2,NOU >*/
  i__1 = nou;
  for (i__ = 2; i__ <= i__1; ++i__) {
    /*<       LP=LINPR(IPR,I) >*/
    lp = linpr_ref(*ipr, i__);
    /*<       L=IOURE(IPR,I) >*/
    l = ioure_ref(*ipr, i__);
    /*<       P(L)=P(LP)*PRAT(IPR,I) >*/
    net_1.p[l - 1] = (net_1.p[lp - 1]- emisTax) * prat_ref(*ipr, i__)+emisTax;
    /*<       IF(NTIME.EQ.1)Q(L)=Q(IN)*SLATE(IPR,I) >*/
    if (var_1.ntime == 1) {
      net_1.q[l - 1] = net_1.q[in - 1] * slate_ref(*ipr, i__);
    }
    /* CMC       IF(IWR1.GE.2)WRITE(6,202)IPR,L,NTIME,P(L) */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  P     RE  %s (%s)     LINK  %s     YEAR%6d    $%10.4f\n",
	      LinkNodeNames[5][(*ipr)], LinkNodeSector[5][(*ipr)],LinkNodeNames[13][l], var_1.itime, net_1.p[l - 1]/units_1.unitcnvt[3]);
    
    /*<    17 CONTINUE >*/
    /* L17: */
  }
  /*<    16 CONTINUE >*/
 L16:
  
  /* ***** END OF PRICE CALCULATION FOR UP-PASS. */
  
  /*<       RETURN >*/
  return 0;
  
  /* ***** REFINERY DOWNPASS LOGIC. */
  
  /*<   200 CONTINUE >*/
 L200:
  
  /*<       NOUT=NOURE(IPR) >*/
  nout = ref_1.noure[*ipr - 1];
  /*<       L2=IORDC(IPR) >*/
  l2 = ref_1.iordc[*ipr - 1];
  
  /*<       if (iordc(ipr) .ne. 0) go to 4499 >*/
  if (ref_1.iordc[*ipr - 1] != 0) {
    goto L4499;
  }
  /*<       qrmax = 0.0 >*/
  qrmax = 0.f;
  /*<       do 4500 i=1,nout >*/
  i__1 = nout;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<          if (slate(ipr,i) .lt. 0.01) go to 4500 >*/
    if (slate_ref(*ipr, i__) < .01f) {
      goto L4500;
    }
    /*<          ll = ioure(ipr,i) >*/
    ll = ioure_ref(*ipr, i__);
    /*<          qreq = q(ll) / slate(ipr,i) >*/
    qreq = net_1.q[ll - 1] / slate_ref(*ipr, i__);
    /*<          if (qreq .lt. qrmax) go to 4500 >*/
    if (qreq < qrmax) {
      goto L4500;
    }
    /*<          l2 = ll >*/
    l2 = ll;
    /*<          qrmax = qreq >*/
    qrmax = qreq;
    /*<  4500 continue >*/
  L4500:
    ;
  }
  /*<  4499 continue >*/
 L4499:
  
  /*<       DO 5011 I=1,NOUT >*/
  i__1 = nout;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       IF(L2.EQ.IOURE(IPR,I))GO TO 5012 >*/
    if (l2 == ioure_ref(*ipr, i__)) {
      goto L5012;
    }
    /*<  5011 CONTINUE >*/
    /* L5011: */
  }
  /*<  5012 IORD=I >*/
 L5012:
  iord = i__;
  
  /*<       QREQ=Q(L2)/SLATE(IPR,IORD) >*/
  qreq = net_1.q[l2 - 1] / slate_ref(*ipr, iord);

 /* the following code inserted by Prakash. This is the fix
 if all plant capacity is less than the single plant capacity */

  lin = iinre_ref(*ipr, 1);
  if (qreq > net_1.capl[lin-1])
	  qreq = net_1.capl[lin-1];


  /* ***** IF REFINERY CONTROLS Q ON ANOTHER LINK, GO TO 1616. */
  
  /*<       IF(KSPEC.EQ.1)GO TO 1616 >*/
  if (*kspec == 1) {
    goto L1616;
  }
  
  /*<       DO 110 I=1,NOUT >*/
  i__1 = nout;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IOURE(IPR,I) >*/
    l = ioure_ref(*ipr, i__);
    
    /* ***** NO SHORTAGE OR EXCESS FOR PRODUCT WHICH REFINERY IS SIZED ON. */
    
    /*<       IF(L.EQ.L2)GO TO 110 >*/
	
	/* Commented by Prakash 
	 if (l == l2) {
      goto L110;
    } */

    /*<       DELQ=Q(L)-QREQ*SLATE(IPR,I) >*/
    delq = net_1.q[l - 1] - qreq * slate_ref(*ipr, i__);
    /*<       IF(ABS(DELQ).LT.0.01)GO TO 110 >*/
    if (dabs(delq) < .01f) {
      goto L110;
    }
    /*<       IF(DELQ)111,111,112 >*/
    if (delq <= 0.f) {
      goto L111;
    } else {
      goto L112;
    }
    
    /* **** EXCESS PRODUCTION OF THIS PRODUCT; */
    /* **** ADD EXCESS SUPPLY TO STOCKPILE. */
    
    /*<   111 NS=ISTCK(IPR,I) >*/
  L111:
    ns = istck_ref(*ipr, i__);
    /*<       IF(NS.EQ.0)GO TO 110 >*/
    if (ns == 0) {
      goto L110;
    }
    /*<       DELQ=-DELQ >*/
    delq = -delq;
    /*<       ST(NS)=ST(NS)+DELQ >*/
    stk_1.st[ns - 1] += delq;
    /*<       LA=IOUST(NS) >*/
    la = stk_1.ioust[ns - 1];
    /*<       Q(LA)=Q(LA)-DELQ >*/
    net_1.q[la - 1] -= delq;
    
    /* CMC       IF(IWR1.GE.2)WRITE(6,203)NS,DELQ,ST(NS) */
    /* CMC   203 FORMAT(65X,'STOCKPILE',I4,2X,'INCREASED BY',F10.3,5X,'(STOCKPILE=' */
    /* CMC      1 ,F10.3,')') */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "                                                                 STOCKPILE  %s (%s)  INCREASED BY%10.3f     (STOCKPILE=%10.3f)\n",
	      LinkNodeNames[8][ns], LinkNodeSector[8][(ns)],delq/units_1.unitcnvt[8], stk_1.st[ns - 1]/units_1.unitcnvt[8]);
    
    
    /* CMC       IF(IWR1.GE.2)WRITE(6,802)LA,NTIME,Q(LA) */
    /*C CMC   802 FORMAT(2X,'Q',5X,'NEW Q',9X,'LINK',I4,5X,'TIME',*/
    /*C CMC      1I3,4X,F11.3)*/
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  Q     NEW Q         LINK  %s     YEAR%6d    %11.3f\n",
	      LinkNodeNames[13][la], var_1.itime, net_1.q[la - 1]/units_1.unitcnvt[8]);
    
    /* ***** REASSIGN REFINERY PRODUCT OUTPUT. */
    
    /*<       Q(L)=QREQ*SLATE(IPR,I) >*/
    net_1.q[l - 1] = qreq * slate_ref(*ipr, i__);
    
    /* CMC       IF(IWR1.GE.2)WRITE(6,803)L,DELQ */
    /* CMC   803 FORMAT(65X,'REFINERY OUT LINK',I4,2X,'INCREASED BY',F10.3) */
    /* CMC       IF(IWR1.GE.2)WRITE(6,802)L,NTIME,Q(L) */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "                                                                 REFINERY OUT LINK  %s  INCREASED BY%10.3f\n",LinkNodeNames[13][l],delq/units_1.unitcnvt[8]);
    
    /*<       GO TO 110 >*/
    goto L110;
    
    /* **** PRODUCTION SHORTFALL; */
    /* **** ADD EXCESS DEMAND TO INDICATED LINKS. */
    
    /*<   112 LX=IXCES(IPR,I) >*/
  L112:
    lx = ixces_ref(*ipr, i__);
    
    /* ***** IF IXCES = 0, EXCESS DEMAND WILL NOT BE MET. */
    
    /*<       IF(LX.EQ.0)GO TO 672 >*/
    if (lx == 0) {
      goto L672;
    }
    /*<       Q(LX)=Q(LX)+DELQ >*/
	
    net_1.q[lx - 1] += delq;
	
    /* CMC       IF(IWR1.GE.2)WRITE(6,303)LX,DELQ */
    /* CMC   303 FORMAT(65X,'PETR PROD LINK',I4,2X,'INCREASED BY',F10.3) */
	
	/* the fprint has more arguments than requrired -  Prakash */
	if (var_1.iwr1 >= 2) 
      fprintf(fp6, "                                                                 PETR PROD LINK  %s  INCREASED BY%10.3f\n", 
	      LinkNodeNames[13][lx],net_1.q[lx - 1]/units_1.unitcnvt[8]);


/*	if (var_1.iwr1 >= 2) 
      fprintf(fp6, "                                                                 PETR PROD LINK%4d  INCREASED BY%10.3f\n", 
	      lx, var_1.ntime,net_1.q[lx - 1]); */

    
    /* CMC       IF(IWR1.GE.2)WRITE(6,302)LX,NTIME,Q(LX) */
    /* CMC   302 FORMAT(2X,'Q',5X,'NEW Q',9X,'LINK',I4,5X,'TIME', */
    /* CMC      1I3,4X,F11.3) */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  Q     NEW Q         LINK  %s     YEAR%6d    %11.3f\n",
	      LinkNodeNames[13][lx],var_1.itime,net_1.q[lx - 1]/units_1.unitcnvt[8]);
    
    
    /* ***** REASSIGN REFINERY PRODUCT OUTPUT. */
    
    /*<   672 Q(L)=QREQ*SLATE(IPR,I) >*/
  L672:
    net_1.q[l - 1] = qreq * slate_ref(*ipr, i__);
    
    /* CMC       IF(IWR1.GE.2)WRITE(6,903)L,DELQ */
    /* CMC   903 FORMAT(65X,'REFINERY OUT LINK',I4,2X,'DECREASED BY',F10.3) */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "                                                                 REFINERY OUT LINK  %s  DECREASED BY%10.3f\n", LinkNodeNames[13][l],delq/units_1.unitcnvt[8]);
  
  
  /* CMC       IF(IWR1.GE.2)WRITE(6,802)L,NTIME,Q(L) */
  /* CMC   802 FORMAT(2X,'Q',5X,'NEW Q',9X,'LINK',I4,5X,'TIME', */
  /* CMC      1I3,4X,F11.3) */
  if (var_1.iwr1 >= 2) 
    fprintf(fp6, "  Q     NEW Q         LINK  %s     YEAR%6d    %11.3f\n",
	    LinkNodeNames[13][l],var_1.itime,net_1.q[l - 1]/units_1.unitcnvt[8]);
  
  /*<   110 CONTINUE >*/
 L110:
  ;
}

/* ***** IF THIS IS A SPECIAL REFINERY ADJUST CAPACITY OF ASSOCIATED LINK. */

/*<  1616 DO 1614 K=1,NOUT >*/
 L1616:
i__1 = nout;
for (k = 1; k <= i__1; ++k) {
  /*<       LK=IOURE(IPR,K) >*/
  lk = ioure_ref(*ipr, k);
  /*<       LX=ICNTL(IPR,K) >*/
  lx = icntl_ref(*ipr, k);
  /*<       IF(LX.EQ.0)GO TO 1614 >*/
  if (lx == 0) {
    goto L1614;
  }
  /*<       NS=ISTCK(IPR,K) >*/
  ns = istck_ref(*ipr, k);
  /*<       IF(NS.EQ.0)GO TO 7903 >*/
  if (ns == 0) {
    goto L7903;
  }
  
  /*<       CAPL(LX)=(Q(LK)+ST(NS))*REMUL(IPR,K) >*/
  net_1.capl[lx - 1] = (net_1.q[lk - 1] + stk_1.st[ns - 1]) * remul_ref(
									*ipr, k);
  /*<       GO TO 7904 >*/
  goto L7904;
  
  /*<  7903 CAPL(LX)=Q(LK)*REMUL(IPR,K) >*/
 L7903:
  net_1.capl[lx - 1] = net_1.q[lk - 1] * remul_ref(*ipr, k);
  /*<  7904 CONTINUE >*/
 L7904:
  /* CMC  7904 IF(IWR1.GE.2)WRITE(6,2521)LX,CAPL(LX),LK */
  /* CMC  2521 FORMAT(2X,'CAPACITY ON LINK',I4,2X,'CHANGED TO',F10.3, */
  /* CMC      1 2X,'VIA LINK',I4) */
  if (var_1.iwr1 >= 2) 
    fprintf(fp6, "  CAPACITY ON LINK  %s  CHANGED TO%10.3f  VIA LINK  %s\n",
	    LinkNodeNames[13][lx],net_1.capl[lx - 1]/units_1.unitcnvt[8],LinkNodeNames[13][lk]);
  
  /*<  1614 CONTINUE >*/
 L1614:
  ;
}

/* ***** ASSIGN CRUDE INPUT QUANTITY. */

/*<  1613 LIN=IINRE(IPR,1) >*/
/* L1613: */
lin = iinre_ref(*ipr, 1);
/*<       Q(LIN)=QREQ >*/
net_1.q[lin - 1] = qreq;

/* CMC       IF(IWR1.GE.2)WRITE(6,402)IPR,LIN,NTIME,Q(LIN) */
/* CMC   402 FORMAT(2X,'Q',5X,'REFRY',I4,5X,'LINK',I4,5X,'TIME', */
/* CMC      1I3,4X,F11.3) */
if (var_1.iwr1 >= 2) 
     fprintf(fp6, "  Q     RE  %s (%s)     LINK  %s     YEAR%6d    %11.3f\n",
	     LinkNodeNames[5][(*ipr)],LinkNodeSector[5][(*ipr)],LinkNodeNames[13][lin],var_1.itime, net_1.q[lin - 1]/units_1.unitcnvt[8]);


     
     /*<       RETURN >*/
     return 0;
     
     /*<       END >*/
   } /* re_ */

/* #undef labe_ref*/
#undef zen_ref
#undef linpr_ref
#undef icntl_ref
#undef remul_ref
#undef slate_ref
#undef ixces_ref
#undef istck_ref
#undef ioure_ref
#undef iinre_ref
#undef prat_ref
     
     
     
     /* ******************************************************************** RN */
     
     /* CMC 990427 ADDED ,POQUAN(200) TO COMMON ALL TO MATCH OTHERS */
     
     /*<       SUBROUTINE RN(IPASS,IPR,KSPEC) >*/
     /* Subroutine */ int rn_(integer *ipass, integer *ipr, integer *kspec)
{
extern int emisflag;
extern FILE *fp11, *fp6, *fp25;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];


  /* System generated locals */
  integer i__1;
  real r__1;
  

  /* Local variables */
  static real pprn;
  static integer i__, j, l;
  static real w;
  static integer nelim;
  static real hp;
  static integer nn;
  static real pq;
  static integer ns, ipm, jpr;
  real emisTax;
  int i;

/* #define labn_ref(a_1,a_2) ren_1.labn[(a_2)*17 + a_1 - 18] */
#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
#define prn_ref(a_1,a_2) ren_1.prn[(a_2)*17 + a_1 - 18]
#define qrn_ref(a_1,a_2) ren_1.qrn[(a_2)*17 + a_1 - 18]
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
  
  
  /*<       L=IOURN(IPR) >*/
  l = ren_1.iourn[*ipr - 1];

  /*<       IF(IPASS.LT.6)GO TO 4511 >*/
  if (*ipass < 6) {
    goto L4511;
  }
  /*<       IPM=IPASS-5 >*/
  ipm = *ipass - 5;
  
  /* CMC       WRITE(11,4903)(LABN(IPR,J),J=1,3) */
  /* CMC  4903 FORMAT(2X,5A4) */
    fprintf(fp11, "  %s\n", ren_1.cmc_labn[*ipr]);

  
  
  /* CMC       IF(IPASS.EQ.6)WRITE(11,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
  /* CMC  4411 FORMAT(1X,I4,1X,'Q',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      2  ,/,10X,5F11.1) */
  if (*ipass == 6) {
    fprintf(fp11, " %4d Q   ",l);
    for (j = 1; j <= pri_1.ioutx; ++j) {
      if(( (j-1)%10==0)&& (j>1) )fprintf(fp11, "\n          ");
      fprintf(fp11, "%11.1f", zen_ref(1,l,j));
    }
    fprintf(fp11, "\n");
  }
  /* CMC       IF(IPASS.EQ.7)WRITE(11,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
  /* CMC  4412 FORMAT(1X,I4,1X,'P',3X,10F9.2,/,10X,10F9.2,/,10X,10F9.2 */
  /* CMC      1   ,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F2.2 */
  /* CMC      2   ,/,10X,5F9.2) */
  if (*ipass == 7) {
	  /* fprint was printing Q instead of P -  Prakash  */
    fprintf(fp11, " %4d P   ",l);
    for (j = 1; j <= pri_1.ioutx; ++j) {
      if(( (j-1)%10==0)&& (j>1) )fprintf(fp11, "\n          ");
      fprintf(fp11, "%9.2f", zen_ref(2,l,j));
    }
    fprintf(fp11, "\n");
  }
  /*<       RETURN >*/
  return 0;
  
  /*<  4511 IF(IPASS.NE.5)GO TO 4409 >*/
 L4511:
  if (*ipass != 5) {
    goto L4409;
  }
  
  /*<       PQ=P(L)*Q(L) >*/
  pq = net_1.p[l - 1] * net_1.q[l - 1];
  /*<       ZEN(1,L,IOUTX)=Q(L)*QSCALE >*/
  zen_ref(1, l, pri_1.ioutx) = net_1.q[l - 1] * var_1.qscale;
  /*<       ZEN(2,L,IOUTX)=P(L)*PSCALE >*/
  zen_ref(2, l, pri_1.ioutx) = net_1.p[l - 1] * pri_1.pscale;
  /*<       RETURN >*/
  return 0;
  
  /*<  4409 CONTINUE >*/
 L4409:
  /*<       IF(IPASS.GT.1)GO TO 200 >*/
  if (*ipass > 1) {
    goto L200;
  }
  
  /* ***** UP-PASS LOGIC. */
  
  /*<       NS=NSTEP(IPR) >*/
  ns = ren_1.nstep[*ipr - 1];


  /*<       IF(NTIME.EQ.1) GO TO 1004 >*/
  if (var_1.ntime == 1) {
    goto L1004;
  }
  /*<       IF(ITN.GT.1)GO TO 1004 >*/
  if (var_1.itn > 1) {
    goto L1004;
  }
  /*<       IF(MUP(IPR).EQ.0)GO TO 1004 >*/
  if (ren_1.mup[*ipr - 1] == 0) {
    goto L1004;
  }
  
  /* ***** MOVE UP RESOURCE COST CURVE. */
  
  /*<       DO 1005 I=1,NS >*/
  i__1 = ns;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       IF(Q(L).LT.QRN(IPR,I))GO TO 2002 >*/
    if (net_1.q[l - 1] < qrn_ref(*ipr, i__)) {
      goto L2002;
    }
    /*<  1005 CONTINUE >*/
    /* L1005: */
  }
  
  /* ***** DEPLETABLE RESOURCE HAS BEEN EXHAUSTED. */
  
  /*<       NSTEP(IPR)=1 >*/
  ren_1.nstep[*ipr - 1] = 1;
  /*<       QRN(IPR,1)=0.0 >*/
  qrn_ref(*ipr, 1) = 0.f;
  /*<       PRN(IPR,1)=9999.999 >*/
  prn_ref(*ipr, 1) = 9999.999f;
  /*<       MUP(IPR)=0 >*/
  ren_1.mup[*ipr - 1] = 0;
  /*<       GO TO 1004 >*/
  goto L1004;
  
  /* ***** I IS STEP NUMBER THAT ALLOCATION STOPPED ON. */
  
  /*<  2002 NELIM=I-1 >*/
 L2002:
  nelim = i__ - 1;
  /*<       NSTEP(IPR)=NS-NELIM >*/
  ren_1.nstep[*ipr - 1] = ns - nelim;
  /*<       NN=NSTEP(IPR) >*/
  nn = ren_1.nstep[*ipr - 1];
  /*<       DO 1717 J=1,NN >*/
  i__1 = nn;
  for (j = 1; j <= i__1; ++j) {
    /*<       QRN(IPR,J)=QRN(IPR,J+NELIM)-Q(L) >*/
    qrn_ref(*ipr, j) = qrn_ref(*ipr, j + nelim) - net_1.q[l - 1];
    /*<       PRN(IPR,J)=PRN(IPR,J+NELIM) >*/
    prn_ref(*ipr, j) = prn_ref(*ipr, j + nelim);
    /*<  1717 CONTINUE >*/
    /* L1717: */
  }
  
  /* ***** COMPUTE RESOURCE PRICE BASED ON STEP NUMBER I. */
  
  /*<  1004 DO 1001 I=1,NS >*/
 L1004:
  i__1 = ns;

  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       IF(Q(L).LT.QRN(IPR,I))GO TO 1002 >*/
    if (net_1.q[l - 1] < qrn_ref(*ipr, i__)) {
      goto L1002;
    }
    /*<  1001 CONTINUE >*/
    /* L1001: */
  }
  /*<       PPRN=PRN(IPR,NS) >*/
  pprn = prn_ref(*ipr, ns);
     
  /*<       GO TO 1003 >*/
  goto L1003;
  
  /*<  1002 PPRN=PRN(IPR,I) >*/
 L1002:
  pprn = prn_ref(*ipr, i__);
  /*<  1003 P(L)=PPRN >*/
 L1003:
  net_1.p[l - 1] = pprn;
  net_1.noTaxPrice[l - 1] = net_1.p[l - 1];
  ren_1.noTaxPrice[*ipr - 1][var_1.ntime-1] = net_1.noTaxPrice[l - 1];

  /* compute emission tax and add to price */
  emisTax=0;
  for(i=0;i<50;i++){
	  emisTax = emisTax +  ren_1.Efactors[*ipr-1][i][0] * ren_1.Efactors[*ipr-1][i][1]
				 * 5.7356 * ren_1.Efactors[*ipr-1][i][2]/1000;
	}

	/*fprintf(fp25, "Year  Itn NodeType   NodeName   Sector   UEmisTax   Total P   \n");*/
	if(emisflag==1)
		fprintf(fp25, "%4d%  3d    RN         %s      %s  %10.4f       %10.4f\n",
			var_1.itime, var_1.itn, LinkNodeNames[6][(*ipr)],LinkNodeSector[6][(*ipr)],emisTax/units_1.unitcnvt[3], 
			(emisTax+net_1.p[l - 1])/units_1.unitcnvt[3]);


    net_1.p[l - 1]=net_1.p[l - 1] + emisTax;


  /* CMC       IF(IWR1.GE.2)WRITE(6,203)IPR,L,NTIME,P(L) */
  /* CMC   203 FORMAT(2X,'P',5X,'RNWPR',I4,5X,'LINK',I4,5X,'TIME', */
  /* CMC      1I3,4X,1H$,F10.4) */
  
  if (var_1.iwr1 >= 2) 
    fprintf(fp6, "  P     RN  %s (%s)     LINK  %s     YEAR%6d    $%10.4f\n",
	    LinkNodeNames[6][(*ipr)], LinkNodeSector[6][(*ipr)],LinkNodeNames[13][l], var_2.itime, net_1.p[l - 1]/units_1.unitcnvt[3]);
  /*<       RETURN >*/
  return 0;
  
  /* ***** DOWN-PASS LOGIC. */
  
  /* ***** COMPUTE NEW QUANTITIES BASED ON DIAGONAL SECANT ALGORITHM. */
  
  /*<   200 JPR=IPR+NRSMX >*/
 L200:
  jpr = *ipr + var_1.nrsmx;
  /*<       HQT(JPR)=Q(L) >*/
  res_1.hqt[jpr - 1] = net_1.q[l - 1];
  /*<       W=0.5 >*/
  w = .5f;
  /*<       IF(ITN.LE.1)GO TO 301 >*/
  if (var_1.itn <= 1) {
    goto L301;
  }
  /*<       IF(ABS(QT(JPR)-QTM(JPR)).LT.EPSN)GO TO 301 >*/
  if ((r__1 = res_1.qt[jpr - 1] - res_1.qtm[jpr - 1], dabs(r__1)) < 
      var_1.epsn) {
    goto L301;
  }
  /*<       HP=(HQT(JPR)-HQTM(JPR))/(QT(JPR)-QTM(JPR)) >*/
  hp = (res_1.hqt[jpr - 1] - res_1.hqtm[jpr - 1]) / (res_1.qt[jpr - 1] - 
						     res_1.qtm[jpr - 1]);
  /*<       IF(ABS(1.-HP).LT.EPSN)GO TO 301 >*/
  if ((r__1 = 1.f - hp, dabs(r__1)) < var_1.epsn) {
    goto L301;
  }
  
  /* ***** COMPUTE RELAXATION PARAMETER. */
  
  /*<       W=1./(1.-HP) >*/
  w = 1.f / (1.f - hp);
  /*<       IF(W.GT.WHI)W=WHI >*/
  if (w > var_1.whi) {
    w = var_1.whi;
  }
  /*<       IF(W.LT.WLO)W=WLO >*/
  if (w < var_1.wlo) {
    w = var_1.wlo;
  }
  
  /*<   301 Q(L)=W*HQT(JPR)+(1.-W)*QT(JPR) >*/
 L301:
  net_1.q[l - 1] = w * res_1.hqt[jpr - 1] + (1.f - w) * res_1.qt[jpr - 1];
  
  /* CMC C***** SAVE QUANTITIES AND TRANSFORMATIONS FOR NEXT ITERATION. */
  
  /*<   201 QTM(JPR)=QT(JPR) >*/
  /* L201: */
  res_1.qtm[jpr - 1] = res_1.qt[jpr - 1];
  /*<       QT(JPR)=Q(L) >*/
  res_1.qt[jpr - 1] = net_1.q[l - 1];
  /*<       HQTM(JPR)=HQT(JPR) >*/
  res_1.hqtm[jpr - 1] = res_1.hqt[jpr - 1];

/*<       IF(IWR1.EQ.0)GO TO 99 >*/
  if (var_1.iwr1 == 0) {
    goto L99;
  }
  /* CMC       IF(IWR1.GE.1)WRITE(6,401)IPR,L,NTIME,Q(L),HQT(JPR),QTM(JPR) */
  /* CMC   401 FORMAT(2X,'Q',5X,'RNWPR',I4,5X,'LINK',I4,5X,'TIME', */
  /* CMC      1I3,4X,F11.3,7X,'Q(K+1)',10X,'H(Q(K))',F10.4, */
  /* CMC      23X,'Q(K)',F10.4) */
  if (var_2.iwr1 >= 1) 
    fprintf(fp6, "  Q     RN  %s (%s)     LINK  %s     YEAR%6d    %11.3f       Q(K)%10.4f\n",
	    LinkNodeNames[6][(*ipr)], LinkNodeSector[6][(*ipr)],LinkNodeNames[13][l],var_2.itime,net_1.q[l - 1]/units_1.unitcnvt[8],res_1.hqt[jpr - 1],res_1.qtm[jpr - 1]);
  
  


  /*<    99 RETURN >*/
 L99:
  return 0;
  /*<       END >*/
} /* rn_ */

/* #undef labn_ref */
#undef qrn_ref
#undef prn_ref
#undef zen_ref



/* ******************************************************************** RS */

/* CMC 990427 ADDED ,POQUAN(200) COMMON ALL */
/*<       SUBROUTINE RS(IPASS,IPR,KSPEC) >*/
/* Subroutine */ int rs_(integer *ipass, integer *ipr, integer *kspec)
{
  extern int emisflag;
  extern FILE *fp11, *fp6, *fp25;
  extern char LinkNodeNames[14][999][6];
  extern char LinkNodeSector[14][999][6];
  real emisTax;
  int ct;
  int i,j;
  /* System generated locals */
  double r__1;
  
  /* Local variables */
  static integer l;
  static real w, hp;
  static integer ks;
  static real pq;
  static integer ipm;
  static real rat;
  
  /* #define labr_ref(a_1,a_2) res_1.labr[(a_2)*75 + a_1 - 76]*/
#define pprj_ref(a_1,a_2) res_1.pprj[(a_2)*75 + a_1 - 76]
#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
  
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
  
  /*<       L=IOURS(IPR) >*/
  l = res_1.iours[*ipr - 1];
  
  /*<       IF(IPASS.LT.6)GO TO 4511 >*/
  if (*ipass < 6) {
    goto L4511;
  }
  /*<       IPM=IPASS-5 >*/
  ipm = *ipass - 5;
/* CMC       WRITE(11,4903)(LABR(IPR,J),J=1,4) */
/* CMC  4903 FORMAT(2X,5A4) */
fprintf(fp11, "  %s\n", res_1.cmc_labr[*ipr]);

  
  /* CMC       IF(IPASS.EQ.6)WRITE(11,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
  /* CMC  4411 FORMAT(1X,I4,1X,'Q',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      2  ,/,10X,5F11.1) */
  if (*ipass == 6) {
    fprintf(fp11, " %4d Q   ",l);
    for (j = 1; j <= pri_1.ioutx; ++j) {
      if(( (j-1)%10==0)&& (j>1) )fprintf(fp11, "\n          ");
      fprintf(fp11, "%11.1f", zen_ref(1,l,j));
      
    }
    fprintf(fp11, "\n");
  }
  
  /* CMC       IF(IPASS.EQ.7)WRITE(11,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
  /* CMC  4412 FORMAT(1X,I4,1X,'P',3X,10F9.2,/,10X,10F9.2,/,10X,10F9.2 */
  /* CMC      1   ,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F2.2 */
  /* CMC      2   ,/,10X,5F9.2) */
  if (*ipass == 7) {
	  /* fprint was printing Q instead of P  - Prakash  */
    fprintf(fp11, " %4d P   ",l);
    for (j = 1; j <= pri_1.ioutx; ++j) {
      if(( (j-1)%10==0)&& (j>1) )fprintf(fp11, "\n          ");
      fprintf(fp11, "%9.2f", zen_ref(2,l,j));
    }
    fprintf(fp11, "\n");
  }
  
  /*<       RETURN >*/
  return 0;
  
  /*<  4511 IF(IPASS.NE.5)GO TO 4409 >*/
 L4511:
  if (*ipass != 5) {
    goto L4409;
  }
  
  /*<       PQ=P(L)*Q(L) >*/
  pq = net_1.p[l - 1] * net_1.q[l - 1];
  /*<       ZEN(1,L,IOUTX)=Q(L)*QSCALE >*/
  zen_ref(1, l, pri_1.ioutx) = net_1.q[l - 1] * var_1.qscale;
  /*<       ZEN(2,L,IOUTX)=P(L)*PSCALE >*/
  zen_ref(2, l, pri_1.ioutx) = net_1.p[l - 1] * pri_1.pscale;
  /*<       RETURN >*/
  return 0;
  
  /*<  4409 CONTINUE >*/
 L4409:
  /*<       IF(IPASS.GT.1)GO TO 200 >*/
  if (*ipass > 1) {
    goto L200;
  }
  
  /* ***** UP-PASS LOGIC. */
  /*<       RAT=1.0 >*/
  rat = 1.f;
  /*<       IF(NTIME.GT.1)GO TO 1677 >*/
  if (var_1.ntime > 1) {
    goto L1677;
  }
  /*<        P(L)=PLAST(IPR) >*/
  net_1.p[l - 1] = res_1.plast[*ipr - 1];
  net_1.noTaxPrice[l - 1] = res_1.plast[*ipr - 1];
  res_1.noTaxPrice[*ipr-1][var_1.ntime-1] = net_1.noTaxPrice[l - 1];

  /*<       GO TO 1678 >*/
  goto L1678;
  /*<  1677 IF(ITN.EQ.1)PLAST(IPR)=P(L) >*/
 L1677:
  if (var_1.itn == 1) {
  //  res_1.plast[*ipr - 1] = net_1.p[l - 1];
	res_1.plast[*ipr - 1] = net_1.noTaxPrice[l - 1];
  }
  /*<       KS=KPR(IPR) >*/
  ks = res_1.kpr[*ipr - 1];
  /*<       RAT=1.+PPRJ(KS,NTIME-1) >*/
  rat = pprj_ref(ks, var_1.ntime - 1) + 1.f;
  
  /*<  6666 P(L)=PLAST(IPR)*RAT+B(IPR)*Q(L)+AB(IPR)*Q(L)**2 >*/
  /* L6666: */
  /* Computing 2nd power */
   r__1 = net_1.q[l - 1];
  net_1.p[l - 1] = res_1.plast[*ipr - 1] * rat + res_1.b[*ipr - 1] * 
    net_1.q[l - 1] + res_1.ab[*ipr - 1] * (r__1 * r__1);
 
// res_1.noTaxPrice[*ipr-1][var_1.ntime-1] = res_1.noTaxPrice[*ipr-1][var_1.ntime-2]*rat +
//											res_1.b[*ipr - 1] * net_1.q[l - 1] +
//											res_1.ab[*ipr - 1] * (r__1 * r__1);

  net_1.noTaxPrice[l - 1] = net_1.p[l - 1];	
  res_1.noTaxPrice[*ipr-1][var_1.ntime-1] = net_1.noTaxPrice[l - 1];

  /* C      WRITE(11,7777)IPR,L,PLAST(IPR),RAT,B(IPR),Q(L),P(L),NTIME,ITN */
  /* C 7777 FORMAT(2X,'$$$$$$ IPR L PLAST(IPR) RAT B(IPR) Q(L) P(L)', */
  /*    1 2I5,5F12.3,2I5) */

  /*<  1678 CONTINUE >*/
 L1678:

	/* compute emission tax and add to price */
  emisTax=0;
  for(i=0;i<50;i++){
		emisTax = emisTax + res_1.Efactors[*ipr-1][i][0] * res_1.Efactors[*ipr-1][i][1]
				   * 5.7356 * res_1.Efactors[*ipr-1][i][2]/1000;
		}

  /*fprintf(fp25, "Year  Itn NodeType   NodeName   Sector   UEmisTax   Total P   \n");*/
	if(emisflag==1)
		fprintf(fp25, "%4d%  3d    RN         %s      %s  %10.4f       %10.4f\n",
			var_1.itime, var_1.itn, LinkNodeNames[7][(*ipr)],LinkNodeSector[7][(*ipr)],emisTax/units_1.unitcnvt[3], 
			(emisTax+net_1.p[l - 1])/units_1.unitcnvt[3]);



	

  net_1.p[l - 1]=net_1.p[l - 1] + emisTax;





  /* CMC  1678 IF(IWR1.GE.2)WRITE(6,203)IPR,L,NTIME,P(L) */
  /* CMC   203 FORMAT(2X,'P',5X,'RESPR',I4,5X,'LINK',I4,5X,'TIME', */
  /* CMC      1I3,4X,1H$,F10.4) */
  if (var_2.iwr1 >= 2) 
    fprintf(fp6, "  P     RS  %s (%s)     LINK  %s     YEAR%6d    $%10.4f\n",
	    LinkNodeNames[7][(*ipr)],LinkNodeSector[7][(*ipr)],LinkNodeNames[13][l], var_2.itime,net_1.p[l - 1]/units_1.unitcnvt[3]);
  
  /*<       RETURN >*/
  return 0;
  
  /* ***** DOWN-PASS LOGIC. */
  
  /* ***** COMPUTE NEW QUANTITIES BASED ON DIAGONAL SECANT ALGORITHM. */
  
  /*<   200 HQT(IPR)=Q(L) >*/
 L200:
  res_1.hqt[*ipr - 1] = net_1.q[l - 1];
  /*<       W=0.5 >*/
  w = .5f;
  /*<       IF(ITN.LE.1)GO TO 301 >*/
  if (var_1.itn <= 1) {
    goto L301;
  }
  /*<       IF(ABS(QT(IPR)-QTM(IPR)).LT.EPSN)GO TO 301 >*/
  if ((r__1 = res_1.qt[*ipr - 1] - res_1.qtm[*ipr - 1], dabs(r__1)) < 
      var_1.epsn) {
    goto L301;
  }
  /*<       HP=(HQT(IPR)-HQTM(IPR))/(QT(IPR)-QTM(IPR)) >*/
  hp = (res_1.hqt[*ipr - 1] - res_1.hqtm[*ipr - 1]) / (res_1.qt[*ipr - 1] - 
						       res_1.qtm[*ipr - 1]);
  /*<       IF(ABS(1.-HP).LT.EPSN)GO TO 301 >*/
  if ((r__1 = 1.f - hp, dabs(r__1)) < var_1.epsn) {
    goto L301;
  }
  
  /* ***** COMPUTE RELAXATION PARAMETER. */
  
  /*<       W=1./(1.-HP) >*/
  w = 1.f / (1.f - hp);
  /*<       IF(W.GT.WHI)W=WHI >*/
  if (w > var_1.whi) {
    w = var_1.whi;
  }
  /*<       IF(W.LT.WLO)W=WLO >*/
  if (w < var_1.wlo) {
    w = var_1.wlo;
  }
  
  /*<   301 Q(L)=W*HQT(IPR)+(1.-W)*QT(IPR) >*/
 L301:
   net_1.q[l - 1] = w * res_1.hqt[*ipr - 1] + (1.f - w) * res_1.qt[*ipr - 1];
  
  /* C***** SAVE QUANTITIES AND TRANSFORMATIONS FOR NEXT ITERATION. */
  
  /*<   201 QTM(IPR)=QT(IPR) >*/
  /* L201: */
  res_1.qtm[*ipr - 1] = res_1.qt[*ipr - 1];
  /*<       QT(IPR)=Q(L) >*/
  res_1.qt[*ipr - 1] = net_1.q[l - 1];
  /*<       HQTM(IPR)=HQT(IPR) >*/
  res_1.hqtm[*ipr - 1] = res_1.hqt[*ipr - 1];
  
  /* CMC       IF(IWR1.GE.1)WRITE(6,401)IPR,L,NTIME,Q(L),HQT(IPR),QTM(IPR) */
  /* CMC   401 FORMAT(2X,'Q',5X,'RESPR',I4,5X,'LINK',I4,5X,'TIME', */
  /* CMC      1I3,4X,F11.3,7X,'Q(K+1)',10X,'H(Q(K))',F10.4, */
  /* CMC      23X,'Q(K)',F10.4) */
  if (var_2.iwr1 >= 1) 
    fprintf(fp6, "  Q     RS  %s (%s)     LINK  %s     YEAR%6d    %11.3f       Q(K+1)          H(Q(K))%10.4f               Q(K)%10.4f\n", 
	    
	    LinkNodeNames[7][(*ipr)],LinkNodeSector[7][(*ipr)],LinkNodeNames[13][l],var_2.itime,net_1.q[l - 1]/units_1.unitcnvt[8], res_1.hqt[*ipr - 1]/units_1.unitcnvt[8],res_1.qtm[*ipr - 1]/units_1.unitcnvt[8]);
  /*<    99 RETURN >*/
  /* L99: */
  
   
  
  
  return 0;
  /*<       END >*/
} /* rs_ */

/* #undef labr_ref */
#undef zen_ref
#undef pprj_ref
