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

/* b3.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
   -lf2c -lm   (in that order)
   */
#include <stdio.h>
#include <stdlib.h>
#include "cmc_f2c.h"
#include "f2c.h"
#include "structures.h"

/* Common Block Declarations */



/* Table of constant values */

static integer c__2 = 2;
static integer c__3 = 3;


/* ******************************************************************** DE */


/*<       SUBROUTINE DE(IPASS,IPR,KSPEC) >*/
/* Subroutine */ int de_(integer *ipass, integer *ipr, integer *kspec)
{
  extern FILE *fp5, *fp6;
  extern char LinkNodeNames[14][999][6];
  extern char LinkNodeSector[14][999][6];
  int ct;
  char buf[1024];
  char cmc_mab[1024];

  static real dgrr;
  static integer l, ids;

  
#define drat_ref(a_1,a_2) dem_1.drat[(a_2)*200 + a_1 - 201]
  
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
  
  /* ***** END OF UP-PASS. START OF DOWN-PASS. */
  /* ***** ASSUME FIXED END USE DEMAND; DO NOT CHANGE QUANTITIES */
  /* ***** ON DEMAND LINKS. */
  
  /*<       L=IINDE(IPR) >*/
  l = dem_1.iinde[*ipr - 1];
  /*<       DGRR=0.0 >*/
  dgrr = 0.f;
  /*<       IF(NTIME.EQ.1)GO TO 300 >*/
  if (var_1.ntime == 1) {
    goto L300;
  }
  /*<       IDS=KD(IPR) >*/
  ids = dem_1.kd[*ipr - 1];
  /*<       DGRR=DRAT(IDS,NTIME-1) >*/
  dgrr = drat_ref(ids, var_1.ntime - 1);
  /*<   300 IF(ITN.GT.1)GO TO 100 >*/
 L300:
  if (var_1.itn > 1) {
    goto L100;
  }
  /*<       QBASE(IPR)=Q(L) >*/
  dem_1.qbase[*ipr - 1] = net_1.q[l - 1];
  
  /*<   100 Q(L)=QBASE(IPR)*(1.+DGRR) >*/
 L100:
  net_1.q[l - 1] = dem_1.qbase[*ipr - 1] * (dgrr + 1.f);
  
  /* CMC       IF(IWR1.GE.2)WRITE(6,202)IPR,L,NTIME,Q(L) */
  /* CMC   202 FORMAT(2X,'Q',5X,'DEMAN',I4,5X,'LINK',I4,5X,'TIME', */
  /* CMC      1I3,4X,F11.3) */
  if (var_1.iwr1 >= 2) 
    fprintf(fp6, "  Q     DE  %s (%s)     LINK  %s     YEAR%6d    %11.3f\n",
	    LinkNodeNames[1][(*ipr)],LinkNodeSector[1][(*ipr)],LinkNodeNames[13][l],var_1.itime,net_1.q[l - 1]/units_1.unitcnvt[8] );
  /*<       RETURN >*/
  return 0;
  /*<       END >*/
} /* de_ */

#undef drat_ref



/* ***************************************************************** ELECS */
/* LAST UPDATE: Jean Trommels 9/4/89 */
/* NOTE: RIR was used locally; I have changed it to RIRE and put it in a */
/* common block.  This is in no way related to RIR in the common block PRO. */

/* Steve Bacon 04/1994: the variables ispecLOV and optionalLOV have been */
/*                      added to the ELEC1 common block */

/* Jianwen Lin 01/27/97: optionalLOV is moved to a new common block, in order */
/*                       to specify special events for optionalLOV and XMLOD */
/*                       ,XLFAC, --the minimum load factor and avarage load */
/*                       factor */

/*<       SUBROUTINE ELECS(IPASS) >*/
/* Subroutine */ int elecs_(integer *ipass)
{
  char cmc_mab[1024];
  extern int emisflag;
  extern FILE *fp13, *fp11,*fp21, *fp25, *elecf;
  FILE *ielc ,*iein, *iall, *fp14, *fp30;
  extern FILE *fp5, *fp6;
  extern char LinkNodeNames[14][999][6];
  extern char LinkNodeSector[14][999][6];
  int ct, pos;
  char buf[1024];
  
  integer i__1, i__2;
  real r__1, r__2, r__3, r__4, r__5;
  
  /* Builtin functions */
  double pow_ri(real *, integer *);
  
  /* Local variables */
  static real dcap;
  static integer  life;
  static real peak;
  static real capr, capx;
  static integer ilnk;
  static real fcst, pvra, cost, qout;
  static integer ipks, isum, iprocnum[300], i__, j, k, l, ilowestindex, n;
  static real r__, t, x, rcapi;
  static integer nload, lifer;
  static real rmarg, r8, r9;
  static integer i5, numax, mumax, jpass, lcopt;
  static real y1, a0, a1, a2, a3, a4, a5;
  static integer i1, i2;
  static real r1, r2, r3, r4, r5, r6, r7;
  static integer i3, i4, nocon;
  static real pkreq;
  static integer nisun, iutmp;
  static real compvalue;
  static integer ncell;
  static real xincr, scost, tener, sener, xordf;
  static integer ma;
  static real xordl, yordf, yordl;
  static integer ldone;
  static real v;
  static integer jj, il, kk;
  static real uener, u, fcost, energ, yb;
  static integer lp;
  static real ht;
  static integer np, iu;
  static real vcost;
  static integer ns;
  static real pr;
  static integer nt;
  static real rm;
  static integer nx;
  static real electr, xx, xordfs, yordfs, xordls, yordls, fac, rlowestval, 
  avc, crf;
  static integer jjj;
  static real pmc, enl;
  static integer numaxr8, lin, ipk, lnk, ipm;
  extern /* Subroutine */ int err_(integer *);
  static real qin, rat;
  static integer ius, lou;
  static real pvr, rc4j;
  
  static integer la1, la2;
  static integer iy;
  
  real emisTax;
  int i;

#define labe_ref(a_1,a_2) elec1_1.labe[(a_2)*300 + a_1 - 301]
#define labv_ref(a_1,a_2) elec2_1.labv[(a_2)*50 + a_1 - 51]
#define xldci_ref(a_1,a_2) elec1_1.xldci[(a_2)*52 + a_1 - 53]
#define qunit_ref(a_1,a_2) elec_1.qunit[(a_2)*75 + a_1 - 76]
#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
#define noperat_ref(a_1,a_2) elec_1.noperat[(a_2)*75 + a_1 - 76]
  
  /*<    >*/
  /* REMOVED , FROM ABOVE LINE */
  /*     5 ispecLOV(300), optionalLOV(300)                                  STB 04/94 */
  /*<       COMMON/ELEC4/ispecLOV(300), optionalLOV(300), XMLOD, XLFAC         >*/
  /*<    >*/
  /*<       COMMON/ELEC3/PEAKF,RIRE,NINEL,NOUPL,QIOUEL,MUNIT                   >*/
  /*<    >*/
  /*<       COMMON/EL1/LWRIT(75),ITELF(75),ITELL(75),IECHO,IEECH,IFINL >*/
  /*<    >*/
  /*<       COMMON/NET/Q(999),P(999),CAPL(999),LAB(5),IUSE(300),LUSE(999) >*/
  /*<    >*/
  /*<    >*/
  /*<       COMMON/TOLOAD/AGENR(75),ALOAD(75),IOUEL >*/
  /*<       COMMON/MODE/IRESON,ILOD,IELE,IMP,BOEMWH,BOEMBTU >*/
  
  /* ***** BRANCH ON IPASS = -1   BASE YEAR INPUT DATA, CALL FROM INPUT */
  /*                         0   INPUT DATA ON/AFTER THIRD PERIOD, CALL FROM INPUT */
  /*                         1   UP-PASS ITERATION, CALL FROM VISIT */
  /*                         2   DOWN-PASS ITERATION, CALL FROM VISIT */
  /*                         5   POST-CONVERGENCE ITERATION, CALL FROM VISIT */
  /*                         6   OUTPUT Q FOR ALL YEARS, CALL FROM VISIT */
  /*                         7   OUTPUT P FOR ALL YEARS, CALL FROM VISIT */
  
  /* ***** UNIT OUTPUT CODES: */
  
  /*      IEIN  = UNIT NO. FOR DUMP OF INPUT DATA */
  /*      IELC = UNIT NO. FOR ELECTRIC SECTOR OUTPUT */
  /*      IALL  = UNIT NO. FOR FINAL ALL-YEAR PRICE/QUANTITY LINK SUMMARY */
  
  /* ***** Variable declarations */
  /*<       INTEGER iProcNum(300) >*/
  /*<       REAL R8,R9 >*/
  /*<       INTEGER I5 >*/
  /* ***** */
  /*<       IELC=13 >*/
  ielc = fp13;
  /*<       IEIN=13 >*/
  iein = fp13;
  /*<       IALL=11 >*/
  iall = fp11;
  
  
  /* ***** SET LIMITS ON GENERATING UNITS AND CONVERSIONS. */
  
  /*<       NUMAX=300 >*/
  numax = 300;
  /*<       MUMAX=40 >*/
  mumax = 135;			/* No. of conversions increased to 135 - Prakash */
  
  /*<       JPASS=IPASS+2 >*/
  jpass = *ipass + 2;
  /*<       GO TO(100,300,200,200,200,200,200,3995,3995),JPASS >*/
  switch (jpass) {
  case 1:  goto L100;
  case 2:  goto L300;
  case 3:  goto L200;
  case 4:  goto L200;
  case 5:  goto L200;
  case 6:  goto L200;
  case 7:  goto L200;
  case 8:  goto L3995;
  case 9:  goto L3995;
  }

  /*<  3995 CONTINUE >*/
 L3995:
  /*<       IPM=IPASS-5 >*/
  ipm = *ipass - 5;
  /*<       DO 1119 I=1,NOUPL >*/
  i__1 = elec3_1.noupl;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       L=IOUPL(I) >*/
    l = elec1_1.ioupl[i__ - 1];
    /* CMC       IF(IPASS.EQ.6)WRITE(IALL,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
    if (*ipass == 6) {
      fprintf(iall, " %4d Q   ",l);
      for(j=1;j<=pri_1.ioutx;j++){
	if(((j-1)%10==0)&&(j>1))
	  fprintf(iall, "\n          ");
	fprintf(iall, "%11.1f", zen_ref(1, l, j));
      }
      fprintf(iall, "\n");
    }
    
    /* CMC       IF(IPASS.EQ.7)WRITE(IALL,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
    if (*ipass == 7) {
      fprintf(iall, " %4d P   ",l);
      for(j=1;j<=pri_1.ioutx;j++){
	if(((j-1)%10==0)&&(j>1))
	  fprintf(iall, "\n          ");
	fprintf(iall, "%9.2f", zen_ref(2, l, j));
      }
      fprintf(iall, "\n");
    }
    
    /*<  1119 CONTINUE >*/
    /* L1119: */
  }
  
  /*<       L=IOUEL >*/
  l = toload_1.iouel;
  /* CMC       IF(IPASS.EQ.6)WRITE(IALL,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
  if (*ipass == 6) {
    fprintf(iall, " %4d Q   ",l);
    for(j=1;j<=pri_1.ioutx;j++){
      if(((j-1)%10==0)&&(j>1))
	fprintf(iall, "\n          ");
      fprintf(iall, "%11.1f", zen_ref(1, l, j));
    }
    fprintf(iall, "\n");
  }
  /* CMC       IF(IPASS.EQ.7)WRITE(IALL,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
  if (*ipass == 7) {
    fprintf(iall, " %4d P   ",l);
    for(j=1;j<=pri_1.ioutx;j++){
      if(((j-1)%10==0)&&(j>1))
	fprintf(iall, "\n          ");
      fprintf(iall, "%9.2f", zen_ref(2, l, j));
    }
    fprintf(iall, "\n");
  }
  /* CMC  4411 FORMAT(1X,I4,1X,'Q',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
  /* CMC      2  ,/,10X,5F11.1) */
  /* CMC  4412 FORMAT(1X,I4,1X,'P',3X,10F9.2,/,10X,10F9.2,/,10X,10F9.2 */
  /* CMC      1   ,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F2.2 */
  /* CMC      2   ,/,10X,5F9.2) */
  /*<       RETURN >*/
  return 0;
  
  /* CMC C***** READ ELECTRIC SECTOR DATA AT BASE YEAR CALL FROM INPUT. */
  
  /*<   100 CONTINUE >*/
 L100:
  /* CMC       READ(5,1909)(MAB(J),J=1,5),IEECH */
  /* assign unit types from b033.dat for thermal and b034.dat for hydro*/
		
	if((fp30=fopen("./b033.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open B033.DAT\n");
    exit(0);
	}
	
	j=0;
	while(!feof(fp30)){
	  fgets(buf,sizeof(buf),fp30);pos=0;
	  k =  atoi(substring(buf, pos,3)); pos+=3;
	  if(k==0)
		  break;
	  j=j+1;
	  elec5_1.unitnumber[j-1] =  k;
	  strcpy(elec5_1.unitname[j-1], substring(buf, pos,12 ));
	  elec5_1.unitname[j-1][8]='\0';
	  elec5_1.unittype[j-1]=1;
	  /*skip one line*/
	  fgets(buf,sizeof(buf),fp30);pos=0;
	}
	
	fclose(fp30);
	if((fp30=fopen("./b034.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open B034.DAT\n");
    exit(0);
	}
	
	while(!feof(fp30)){
	  fgets(buf,sizeof(buf),fp30);pos=0;
	   k =  atoi(substring(buf, pos,3)); pos+=3;
	  if(k==0)
		  break;
	  j=j+1;
	  elec5_1.unitnumber[j-1] =  k;
	  strcpy(elec5_1.unitname[j-1], substring(buf, pos,12 ));
	  elec5_1.unitname[j-1][8]='\0';
	  elec5_1.unittype[j-1]=2;
	   /*skip one line*/
	  fgets(buf,sizeof(buf),fp30);pos=0;	
	}
	fclose(fp30);




  fgets(buf, sizeof(buf), fp5);
  pos = 0;
  strcpy(cmc_mab, substring(buf,pos,20));pos+=20;
  el1_1.ieech = atoi(substring(buf,pos,5));
  
  /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,4343)(ITITL(K),K=1,114) */
  /* CMC  4343 FORMAT(1H1,6(/,1X,'**********',2X,19A4),//) */
  
   if (el1_1.ieech == 0) {
      fprintf(iein, "1\n"); /* CMC CHECK */
      for(k=1; k<=6; k++){
		fprintf(iein, " **********  ");
		fprintf(iein, "%s", ren_1.ititl[k-1] );
      }
		fprintf(iein, "\n\n");
    }


    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,1909)(MAB(J),J=1,5),IEECH */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s", cmc_mab);
      fprintf(iein,"%5d\n", el1_1.ieech);
    }
    /* CMC UNKNOWN */
    /* CMC       READ(5,4907)LA1,LA2,(LWRIT(IY),IY=1,75)                bh-9-91 */
  fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 5));pos+=5;
  for(iy=1;iy<=25;iy++){
    el1_1.lwrit[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
  }
  fgets(buf, sizeof(buf), fp5);pos=0;
  pos+=5;
  for(iy=26;iy<=50;iy++){
    el1_1.lwrit[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
  }
  fgets(buf, sizeof(buf), fp5);pos=0;
  pos+=5;
  for(iy=51;iy<=75;iy++){
    el1_1.lwrit[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
  }
  /* CMC UNKNOWN */
  /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,4907)LA1,LA2,(LWRIT(IY),IY=1,NPER) */
  if (el1_1.ieech == 0) {
    fprintf(iein, "%s", cmc_mab);
      for(iy=1;iy<=25;iy++)
	fprintf(iein, "%3d", el1_1.lwrit[iy - 1]);
      fprintf(iein, "\n");
    fprintf(iein, "%s", cmc_mab);
      for(iy=26;iy<=50;iy++)
	fprintf(iein, "%3d", el1_1.lwrit[iy - 1]);
      fprintf(iein, "\n");
    fprintf(iein, "%s", cmc_mab);
      for(iy=51;iy<=75;iy++)
	fprintf(iein, "%3d", el1_1.lwrit[iy - 1]);
      fprintf(iein, "\n");
    }
    /* CMC  4907 FORMAT(A2,A3,25I3,/,A2,A3,25I3,/,A2,A3,25I3)          bh-9-91 */
    /* CMC       READ(5,4907)LA1,LA2,(ITELF(IY),IY=1,75) */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 5));pos+=5;
    for(iy=1;iy<=25;iy++){
      el1_1.itelf[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
    }
    fgets(buf, sizeof(buf), fp5);pos=0;
  pos+=5;
  for(iy=26;iy<=50;iy++){
      el1_1.itelf[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
    }
    fgets(buf, sizeof(buf), fp5);pos=0;
  pos+=5;
    for(iy=51;iy<=75;iy++){
      el1_1.itelf[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
    }
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,4907)LA1,LA2,(ITELF(IY),IY=1,NPER) */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s", cmc_mab);
      for(iy=1;iy<=25;iy++)
	fprintf(iein, "%3d", el1_1.itelf[iy - 1]);
      fprintf(iein, "\n");
      fprintf(iein, "%s", cmc_mab);
      for(iy=26;iy<=50;iy++)
	fprintf(iein, "%3d", el1_1.itelf[iy - 1]);
      fprintf(iein, "\n");
      fprintf(iein, "%s", cmc_mab);
      for(iy=51;iy<=75;iy++)
	fprintf(iein, "%3d", el1_1.itelf[iy - 1]);
      fprintf(iein, "\n");
    }
    /* CMC       READ(5,4907)LA1,LA2,(ITELL(IY),IY=1,75) */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 5));pos+=5;
    for(iy=1;iy<=25;iy++){
      el1_1.itell[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
    }
    fgets(buf, sizeof(buf), fp5);pos=0;
  pos+=5;
    for(iy=26;iy<=50;iy++){
      el1_1.itell[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
    }
    fgets(buf, sizeof(buf), fp5);pos=0;
  pos+=5;
    for(iy=51;iy<=75;iy++){
      el1_1.itell[iy - 1] = atoi(substring(buf, pos, 3));pos+=3;
    }
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,4907)LA1,LA2,(ITELL(IY),IY=1,NPER) */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s",cmc_mab);
      for(iy=1;iy<=25;iy++)
	fprintf(iein, "%3d", el1_1.itell[iy - 1]);
      fprintf(iein, "\n");
      fprintf(iein, "%s",cmc_mab);
      for(iy=26;iy<=50;iy++)
	fprintf(iein, "%3d", el1_1.itell[iy - 1]);
      fprintf(iein, "\n");
      fprintf(iein, "%s",cmc_mab);
      for(iy=51;iy<=75;iy++)
	fprintf(iein, "%3d", el1_1.itell[iy - 1]);
      fprintf(iein, "\n");
    }
    /* CMC       READ(5,1909)(MAB(J),J=1,5),(IINEL(J),J=1,20) */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;

    for(j=1;j<=10;j++){
      elec1_1.iinel[j - 1] = atoi(substring(buf, pos, 5));pos+=5;
    }
    fgets(buf, sizeof(buf), fp5);pos=20;
    for(j=11;j<=20;j++){
      elec1_1.iinel[j - 1] = atoi(substring(buf, pos, 5));pos+=5;
    }
    
    /* ***** COMPUTE NO. INPUT LINKS TO ELECTRIC SECTOR. */
    
    /*<       NINEL=0 >*/
    elec3_1.ninel = 0;
    /*<       DO 1776 J=1,20 >*/
    for (j = 1; j <= 20; ++j) {
      /*<       IF(IINEL(J).EQ.0)GO TO 1777 >*/
      if (elec1_1.iinel[j - 1] == 0) {
	goto L1777;
      }
      /*<       NINEL=NINEL+1 >*/
      ++elec3_1.ninel;
      /*<  1776 CONTINUE >*/
      /* L1776: */
    }
    /*<  1777 CONTINUE >*/
  L1777:
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,211)(MAB(J),J=1,5),NINEL, */
    /* CMC      1 (IINEL(J),J=1,NINEL) */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s     %5d", cmc_mab, elec3_1.ninel);
      for (j = 1; j <= elec3_1.ninel; ++j) {
	if(( (j-1)%10==0)&&(j>1))  
	  fprintf(iein, "\n                              ");
	 fprintf(iein, "%5d", elec1_1.iinel[j - 1]);
       }
      fprintf(iein, "\n");
    }
    /* CMC   211 FORMAT(5A4,5X,11I5,/,30X,10I5) */




    /* CMC       READ(5,1909)(MAB(J),J=1,5),(IOUPL(J),J=1,20) */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;
    for(j=1;j<=10;j++){
      elec1_1.ioupl[j - 1] = atoi(substring(buf, pos, 5));pos+=5;
    }
    fgets(buf, sizeof(buf), fp5);pos=20;
    for(j=11;j<=20;j++){
      elec1_1.ioupl[j - 1] = atoi(substring(buf, pos, 5));pos+=5;
    }
    
    /* ***** COMPUTE NO. OUTPUT LINKS FROM ELECTRIC SECTOR. */
    
    /*<       NOUPL=0 >*/
    elec3_1.noupl = 0;
    /*<       DO 1778 J=1,20 >*/
    for (j = 1; j <= 20; ++j) {
      /*<       IF(IOUPL(J).EQ.0)GO TO 1779 >*/
      if (elec1_1.ioupl[j - 1] == 0) {
	goto L1779;
      }
      /*<       NOUPL=NOUPL+1 >*/
      ++elec3_1.noupl;
      /*<  1778 CONTINUE >*/
      /* L1778: */
    }
    /*<  1779 CONTINUE >*/
  L1779:
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,211)(MAB(J),J=1,5),NOUPL, */
    /* CMC      1 (IOUPL(J),J=1,NOUPL) */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s", cmc_mab);
      fprintf(iein, "     %5d", elec3_1.noupl);
      for(j=1;j<=elec3_1.noupl;j++){
	if( ( (j-1)%10==0)&&(j>1))
	  fprintf(iein, "\n                              ");
	fprintf(iein, "     %5d", elec1_1.ioupl[j - 1]);
      }
      fprintf(iein, "\n");
    }
    
    
    
    
    /* ***** CHECK LINKS FOR PREVIOUS ASSIGNMENT. */
    
    /*<       DO 399 J=1,NINEL >*/
	i__1 = elec3_1.ninel;
     for (j = 1; j <= i__1; ++j) {
      /*<       IL=IINEL(J) >*/
      il = elec1_1.iinel[j - 1];
      /*<       IF(LUSE(IL).EQ.1)CALL ERR(2) >*/
      if (net_1.luse[il - 1] == 1) {
	err_(&c__2);
      }
      /*<   399 CONTINUE >*/
      /* L399: */
    }
    
    /*<       DO 1505 J=1,NINEL >*/
    i__1 = elec3_1.ninel;
    for (j = 1; j <= i__1; ++j) {
      /*<       IL=IINEL(J) >*/
      il = elec1_1.iinel[j - 1];
      /*<       LUSE(IL)=1 >*/
      net_1.luse[il - 1] = 1;
      /*<  1505 CONTINUE >*/
      /* L1505: */
    }
    
    /*<       DO 1200 J=1,NOUPL >*/
    i__1 = elec3_1.noupl;
    for (j = 1; j <= i__1; ++j) {
      /*<       IL=IOUPL(J) >*/
      il = elec1_1.ioupl[j - 1];
      /*<       IF(LUSE(IL).EQ.1)CALL ERR(2) >*/
      if (net_1.luse[il - 1] == 1) {
	err_(&c__2);
      }
      /*<  1200 CONTINUE >*/
      /* L1200: */
    }
    
    /*<       DO 1199 J=1,NOUPL >*/
    i__1 = elec3_1.noupl;
    for (j = 1; j <= i__1; ++j) {
      /*<       IL=IOUPL(J) >*/
      il = elec1_1.ioupl[j - 1];
      /*<       LUSE(IL)=1 >*/
      net_1.luse[il - 1] = 1;
      /*<  1199 CONTINUE >*/
      /* L1199: */
    }
    
    /* CMC       READ(5,1909)(MAB(J),J=1,5),IOUEL */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;
    toload_1.iouel = atoi(substring(buf, pos, 5));pos+=5;
    
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,211)(MAB(J),J=1,5),IOUEL */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s", cmc_mab);
      fprintf(iein, "     %5d\n", toload_1.iouel);
    }
    
    /* CMC       READ(5,20)(MAB(J),J=1,5),Q(IOUEL) */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;
    net_1.q[toload_1.iouel - 1] = atof(substring(buf, pos, 10));pos+=10;
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,20)(MAB(J),J=1,5),Q(IOUEL) */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s", cmc_mab);
      fprintf(iein, "%10.2f\n", net_1.q[toload_1.iouel - 1] );
    }
    
    /*<       QIOUEL = Q(IOUEL)                                                  >*/
    elec3_1.qiouel = net_1.q[toload_1.iouel - 1];
    
    /* CMC       READ(5,20)(MAB(J),J=1,5),PEAKF,RMARG */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;
  elec3_1.peakf = atof(substring(buf, pos, 10));pos+=10;
    rmarg = atof(substring(buf, pos, 10));pos+=10;
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,20)(MAB(J),J=1,5),PEAKF,RMARG */
    if (el1_1.ieech == 0) {
       fprintf(iein, "%s", cmc_mab);
     fprintf(iein, "%10.2f", elec3_1.peakf);
      fprintf(iein, "%10.2f\n", rmarg);
    }
    
    /* CMC       READ(5,20)(MAB(J),J=1,5),RIRE                           JT6/13/89 */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;
    elec3_1.rire = atof(substring(buf, pos, 10));pos+=10;
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,20)(MAB(J),J=1,5),RIRE          JT6/13/89 */
    if (el1_1.ieech == 0) {
       fprintf(iein, "%s", cmc_mab);
      fprintf(iein, "%10.2f\n", elec3_1.rire );
    }
    
    /*  C     READ(5,20)(MAB(J),J=1,5),RIR */
    /*  C     IF(IEECH.EQ.0)WRITE(IEIN,20)(MAB(J),J=1,5),RIR */
    
    /* CMC       READ(5,1760)(MAB(J),J=1,5),LCOPT,XMLOD,XLFAC */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;
  /* changed pos+=5 to pos+=10 - Prakash  */
    lcopt = atoi(substring(buf, pos, 10));pos+=10;
    elec4_1.xmlod = atof(substring(buf, pos, 10));pos+=10;
    elec4_1.xlfac = atof(substring(buf, pos, 10));pos+=10;
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,1760)(MAB(J),J=1,5),LCOPT,XMLOD,XLFAC */
    if (el1_1.ieech == 0) {
       fprintf(iein, "%s", cmc_mab);
      fprintf(iein, "%5d", lcopt);
      fprintf(iein, "%10.3f", elec4_1.xmlod);
      fprintf(iein, "%10.3f", elec4_1.xlfac );
      fprintf(iein, "\n");
    }
    
    /* CMC  1760 FORMAT(5A4,I5,2F10.3) */
    
    /* CMC       READ(5,20)(MAB(J),J=1,5),A0,A1,A2,A3,A4,A5 */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;
    a0 = atof(substring(buf, pos, 10));pos+=10;
    a1 = atof(substring(buf, pos, 10));pos+=10;
    a2 = atof(substring(buf, pos, 10));pos+=10;
    a3 = atof(substring(buf, pos, 10));pos+=10;
    a4 = atof(substring(buf, pos, 10));pos+=10;
    a5 = atof(substring(buf, pos, 10));pos+=10;
    
    /* C***** IF LCOPT=1, LDC COEFFS. ARE READ IN. */
    /* ***** IF LCOPT=2, LDC COEFFS. ARE COMPUTED BY SNYDER METHOD. */
    
    /*<       IF(LCOPT.EQ.1)GO TO 1970 >*/
    if (lcopt == 1) {
      goto L1970;
    }
    /*<       Y1=XMLOD >*/
    y1 = elec4_1.xmlod;
    /*<       YB=XLFAC >*/
    yb = elec4_1.xlfac;
    /*<       A0=1. >*/
    a0 = 1.f;
    /*<       A1=6.*(3.*YB-Y1-2.) >*/
    a1 = (yb * 3.f - y1 - 2.f) * 6.f;
    /*<       A2=-82.*YB+27.*Y1+55. >*/
    a2 = yb * -82.f + y1 * 27.f + 55.f;
    /*<       A3=4.*(38.*YB-10.*Y1-28.) >*/
    a3 = (yb * 38.f - y1 * 10.f - 28.f) * 4.f;
    /*<       A4=20.*(-6.*YB+Y1+5.) >*/
    a4 = (yb * -6.f + y1 + 5.f) * 20.f;
    /*<       A5=32.*(YB-1.) >*/
    a5 = (yb - 1.f) * 32.f;
    /*<  1970 CONTINUE >*/
  L1970:
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,20)(MAB(J),J=1,5),A0,A1,A2,A3,A4,A5 */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s", cmc_mab);
      fprintf(iein, "%10.2f", a0 );
      fprintf(iein, "%10.2f", a1 );
      fprintf(iein, "%10.2f", a2 );
      fprintf(iein, "%10.2f", a3 );
      fprintf(iein, "%10.2f", a4 );
      fprintf(iein, "%10.2f", a5 );
      fprintf(iein, "\n");
    }
    
    /* CMC       READ(5,211)(MAB(J),J=1,5),NCELL */
    fgets(buf, sizeof(buf), fp5);pos=0;
  strcpy(cmc_mab, substring(buf, pos, 20));pos+=20;
    pos+=5;
    ncell = atoi(substring(buf, pos, 5));pos+=5;
    
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,211)(MAB(J),J=1,5),NCELL */
    if (el1_1.ieech == 0) {
      fprintf(iein, "%s", cmc_mab);
      fprintf(iein, "     %5d", ncell );
      fprintf(iein, "\n");
    }
    
    /*<       IUS=0 >*/
    ius = 0;
    
    /*<       DCAP=0.0 >*/
    dcap = 0.f;
    /*<       NUNIT=0 >*/
    elec_1.nunit = 0;
    
    /* CMC C***** LOOP FOR READ-IN OF UNIT DATA. */
    
    /*<    >*/
    /*< i__1 = numaxr8; >*/
    /*< i__2 = i5; >*/
    /*< for (k = 1; i__2 < 0 ? k >= i__1 : k <= i__1; k += i__2) { >*/
  i__1 = numax;
  for (k = 1; k <= i__1; ++k) {

      
      /* CMC       READ(5,96) I,(MAB(KK),KK=1,3),I1,I2,R1,R2,R3,R4,R5,R6,R7,I3,I4,   stb 05/94 */
      /* CMC UNKNOWN */
      
   /* CMC    96 FORMAT(I3,3A4,2I3,4F7.2,F10.2,2F5.2,2I5,/,F18.2,I2,F7.2)          STB 05/94 */

      fgets(buf, sizeof(buf), fp5);pos=0;
      i__ = atoi(substring(buf, pos, 3));pos+=3;
      strcpy(cmc_mab, substring(buf, pos, 12));pos+=12;	
      i1 = atoi(substring(buf, pos,3 ));pos+=3;
      i2 = atoi(substring(buf, pos,3 ));pos+=3;
      r1 = atof(substring(buf, pos,7 ));pos+=7;
      r2 = atof(substring(buf, pos,7 ));pos+=7;
      r3 = atof(substring(buf, pos,7 ));pos+=7;
      r4 = atof(substring(buf, pos,7 ));pos+=7;
      r5 = atof(substring(buf, pos,10 ));pos+=10;
      r6 = atof(substring(buf, pos,5 ));pos+=5;
      r7 = atof(substring(buf, pos,5 ));pos+=5;
      i3 = atoi(substring(buf, pos,5 ));pos+=5;
      i4 = atoi(substring(buf, pos,5 ));pos+=5;
      fgets(buf, sizeof(buf), fp5);pos=0;
      r8 = atof(substring(buf, pos,18 ));pos+=18;
      i5 = atoi(substring(buf, pos,2 ));pos+=2;
      r9 = atof(substring(buf, pos,7 ));pos+=7;
      
      strcpy(elec1_1.unitname[k-1],cmc_mab);
	  elec1_1.unitname[k-1][8]='\0';	
      /* CMC C***** IF I=0 ALL UNITS HAVE BEEN READ. */
      /*<       IF(I.EQ.0)GO TO 1791 >*/
      if (i__ == 0) {
	goto L1791;
      }

      /* ***** TRANSFER DATA IF VALID UNIT NUMBER. */
      
      /* STB 05/27/94: keep track of the PROCESS NUMBER for a leter search, I */
      /* CMC *  don't know how this is already done (if it is already done, so I've */
      /*  added the array iProcNum) */
      /*<       iProcNum(K) = I >*/
      iprocnum[k - 1] = i__;
      /*<       DO 7099 KK=1,3 >*/
      for (kk = 1; kk <= 3; ++kk) {
	/*<       LABE(K,KK)=MAB(KK)                                                 >*/
	labe_ref(k, kk) = elec1_1.mab[kk - 1];
	/*<  7099 CONTINUE >*/
	/* L7099: */
      }
      /*<       IINLK(K)=I1                                                        >*/
      elec1_1.iinlk[k - 1] = i1;
      /*<       IOULK(K)=I2                                                        >*/
      elec1_1.ioulk[k - 1] = i2;
      /*<       CAP(K)=  R1                                                        >*/
      elec1_1.cap[k - 1] = r1;
	  elec1_1.basecap[k - 1] = r1;	
      /*<       CAPC(K)= R2                                                        >*/
      elec1_1.capc[k - 1] = r2;
	  elec1_1.baseCapital[k-1] = r2;
      /*<       OMA(K)=  R3                                                        >*/
      elec1_1.oma[k - 1] = r3;
      /*<       OMB(K)=  R4                                                        >*/
      elec1_1.omb[k - 1] = r4;
      /*<       HTRT(K)= R5                                                        >*/
      elec1_1.htrt[k - 1] = r5;
      /*<       FORC(K)= R6                                                        >*/
      elec1_1.forc[k - 1] = r6;
      /*<       DMAIN(K)=R7                                                        >*/
      elec1_1.dmain[k - 1] = r7;
      /*<       IYRF(K)= I3                                                        >*/
      elec1_1.iyrf[k - 1] = i3;
      /*<       LIFE=    I4 >*/
      life = i4;
      /*<       UMIN(K)= R8                                                        >*/
      elec1_1.umin[k - 1] = r8;
      /*<       ispecLOV(K) = I5                                                   >*/
      elec4_1.ispeclov[k - 1] = i5;
      /*<       optionalLOV(K) = R9                                                >*/
      elec4_1.optionallov[k - 1] = r9;
      /*<       NUNIT=NUNIT+1 >*/
      ++elec_1.nunit;
      
      /*<       IYRR(K)=IYRF(K)+LIFE                                               >*/
      elec1_1.iyrr[k - 1] = elec1_1.iyrf[k - 1] + life;
      /* look here for to see in rire is 0 in future years */
      /*<       CRF=(RIRE*(1.+RIRE)**LIFE)/((1.+RIRE)**LIFE-1.)                    >*/
      r__1 = elec3_1.rire + 1.f;
      r__2 = elec3_1.rire + 1.f;
      crf = elec3_1.rire * pow_ri(&r__1, &life) / (pow_ri(&r__2, &life) - 
						   1.f);
      /*     CRF=(RIR*(1.+RIR)**LIFE)/((1.+RIR)**LIFE-1.) */
      /*<       CAPC(K)=CAPC(K)*CRF                                                >*/
      elec1_1.capc[k - 1] *= crf;
      
      /* ***** COMPUTE DERATED CAPACITY BASED ON FORCED OUTAGE RATE. */
      
      /*<       CAP(K)=CAP(K)*(1.-FORC(K))*(1.-DMAIN(K)/365.)                      >*/
      elec1_1.cap[k - 1] = elec1_1.cap[k - 1] * (1.f - elec1_1.forc[k - 1]) 
	* (1.f - elec1_1.dmain[k - 1] / 365.f);
      /*<       DCAP=DCAP+CAP(K)                                                   >*/
      dcap += elec1_1.cap[k - 1];
      
      /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,97)I,(LABE(K,KK),KK=1,3),IINLK(K),       BH 6/89 */
      /* CMC      1 IOULK(K),CAP(K),                                                 BH 6/89 */
      /* CMC     X CAPC(K),                                                         BH 6/89 */
      /* CMC     1 OMA(K),OMB(K),HTRT(K),FORC(K),DMAIN(K),IYRF(K),IYRR(K),UMIN(K)   BH 6/89 */
      
      if (el1_1.ieech == 0) 
	fprintf(iein, " %3d%s%5d%5d%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%5d%5d%5.2f\n",
		i__, elec1_1.unitname[k-1],
		elec1_1.iinlk[k - 1],
		elec1_1.ioulk[k - 1],
		elec1_1.cap[k - 1],
		elec1_1.capc[k - 1],
		elec1_1.oma[k - 1],
		elec1_1.omb[k - 1],
		elec1_1.htrt[k - 1],
		elec1_1.forc[k - 1],
		elec1_1.dmain[k - 1],
		elec1_1.iyrf[k - 1],
		elec1_1.iyrr[k - 1],
		elec1_1.umin[k - 1]);

 /*    fprintf(iein, " %3d%4d%4d%4d%5d%5d%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%5d%5d%5.2f\n",
		i__, labe_ref(k, 1),labe_ref(k, 2),labe_ref(k, 3),
		elec1_1.iinlk[k - 1],
		elec1_1.ioulk[k - 1],
		elec1_1.cap[k - 1],
		elec1_1.capc[k - 1],
		elec1_1.oma[k - 1],
		elec1_1.omb[k - 1],
		elec1_1.htrt[k - 1],
		elec1_1.forc[k - 1],
		elec1_1.dmain[k - 1],
		elec1_1.iyrf[k - 1],
		elec1_1.iyrr[k - 1],
		elec1_1.umin[k - 1]); The print statement is modified as above - Prakash */
      
      /*<       NUSE(K)=0                                                          >*/
      elec_1.nuse[k - 1] = 0;
      /*<       IF(ITIME.GT.IYRF(K))NUSE(K)=IYRF(K)                                >*/
      if (var_1.itime > elec1_1.iyrf[k - 1]) {
	elec_1.nuse[k - 1] = elec1_1.iyrf[k - 1];
      }
      /*<    10 CONTINUE >*/
      /* L10: */

    }
  L1791:    
	/* assign unit type 1 - thermal 2- hydro */
	i__1 = elec_1.nunit;
	for (k = 1; k <= i__1; ++k) {
		for(j=1;j<=i__1;++j){
			if(iprocnum[k-1]==elec5_1.unitnumber[j-1])
				if(strcmp(elec1_1.unitname[k-1],elec5_1.unitname[j-1])==0){
					elec1_1.unitype[k-1]=elec5_1.unittype[j-1];
					break;
				}
		}
	}



    /* CMC C***** READ UNIT CONVERSION DATA AND MODIFY AS WITH EXISTING UNIT DATA. */
    
    /*<  1791 CONTINUE >*/

    /* CMC  1791 IF(IEECH.EQ.0)WRITE(IEIN,711)NUNIT */
    /* CMC   711 FORMAT(' ** DATA INPUT FOR ',I4,' UNITS') */
    if (el1_1.ieech == 0) 
      fprintf(iein, " ** DATA INPUT FOR %4d UNITS\n", elec_1.nunit);

    /* CMC NEED TO FIX NEXT TWO BLOCKS */
    /* CMC       READ(5,211)(LABV(1,KK),KK=1,3) */
/*     fgets(buf, sizeof(buf), fp5);pos=0; */
/*     for(j=1;j<=3;j++){ */
/*       labv_ref(1, j) = atoi(substring(buf, pos, 4));pos+=4; */
/*     } */
    
    
    /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,211)(LABV(1,KK),KK=1,3) */
/*     if (el1_1.ieech == 0) { */
/*       for(j=1;j<=3;j++) */
/* 	fprintf("%4d", labv_ref(1, j)) ; */
/*       fprintf("\n"); */
/*     } */
    


    /* CMC C***** LOOP FOR READ-IN OF UNIT CONVERSION DATA. */
  fgets(buf, sizeof(buf), fp5);pos=0;
   
    /*<       MUNIT=0        >*/
    elec3_1.munit = 0;
    /*<       DO 1511 K=1,MUMAX >*/
    i__2 = mumax;
    for (k = 1; k <= i__2; ++k) {
      /* 99 FORMAT(I3,3A4,   2I3,   4F7.2,F10.2,2F5.2, 2I5,/,13X,F5.2)*/
      /* CMC       READ(5,99)IC1(K),(LABV(K,KK),KK=1,3),IC2(K),IC3(K),RC4(K),RC5(K), */
      /* CMC      1 RC6(K),RC7(K),RC8(K),RC9(K),RC10(K),IC11(K),LIFE,RC11(K) */
      
      fgets(buf, sizeof(buf), fp5);pos=0;
      pos=0;
      elec2_1.ic1[k - 1]  = atoi(substring(buf, pos, 3));pos+=3;
      strcpy(cmc_mab, substring(buf, pos, 12));pos+=12;
      elec2_1.ic2[k - 1] = atoi(substring(buf, pos, 3));pos+=3;
      elec2_1.ic3[k - 1] = atoi(substring(buf, pos, 3));pos+=3;
      elec2_1.rc4[k - 1] = atof(substring(buf, pos, 7));pos+=7;
      elec2_1.rc5[k - 1] = atof(substring(buf, pos, 7));pos+=7;
      elec2_1.rc6[k - 1] = atof(substring(buf, pos, 7));pos+=7;
      elec2_1.rc7[k - 1] = atof(substring(buf, pos, 7));pos+=7;
      elec2_1.rc8[k - 1] = atof(substring(buf, pos, 10));pos+=10;
      elec2_1.rc9[k - 1] = atof(substring(buf, pos, 5));pos+=5;
      elec2_1.rc10[k - 1] = atof(substring(buf, pos, 5));pos+=5;
      elec2_1.ic11[k - 1] = atoi(substring(buf, pos, 5));pos+=5;
      life = atoi(substring(buf, pos, 5));pos+=5;
      
      fgets(buf, sizeof(buf), fp5);pos=13;
      elec2_1.rc11[k - 1] = atof(substring(buf, pos, 5));pos+=5;
      
      strcpy(elec2_1.unitname[k-1],cmc_mab);
      elec2_1.unitname[k-1][8]='\0';
      /*<       RC10(K) = RC10(K) * 100.0                                          >*/
      /* no need to multiply with 100 - Prakash Thimmapuram */
	  /*elec2_1.rc10[k - 1] *= 100.f;*/
      
      /* ***** IF IC1(K)=0, END OF UNIT CONVERSION DATA. */
      
      /*<       IF(IC1(K).EQ.0)GO TO 1783 >*/
      if (elec2_1.ic1[k - 1] == 0) {
	goto L1783;
      }
      /*<       MUNIT=MUNIT+1 >*/
      ++elec3_1.munit;
      
      /*<       IC12(K)=IC11(K)+LIFE >*/
      elec2_1.ic12[k - 1] = elec2_1.ic11[k - 1] + life;
      /*<       CRF=(RIRE*(1.+RIRE)**LIFE)/((1.+RIRE)**LIFE-1.)                    >*/
      r__1 = elec3_1.rire + 1.f;
      r__2 = elec3_1.rire + 1.f;
      crf = elec3_1.rire * pow_ri(&r__1, &life) / (pow_ri(&r__2, &life) - 
						   1.f);
      /*     CRF=(RIR*(1.+RIR)**LIFE)/((1.+RIR)**LIFE-1.) */
      /*<       RC5(K)=RC5(K)*CRF >*/
      elec2_1.rc5[k - 1] *= crf;
      /*<       RC4(K)=RC4(K)*(1.-RC9(K))*(1.-RC10(K)/365.) >*/
      elec2_1.rc4[k - 1] = elec2_1.rc4[k - 1] * (1.f - elec2_1.rc9[k - 1]) *
	(1.f - elec2_1.rc10[k - 1] / 365.f);
      
      /* CMC       IF(IEECH.EQ.0)WRITE(IEIN,97)IC1(K),(LABV(K,KK),KK=1,3),IC2(K), */
      /* CMC      1 IC3(K),RC4(K), */
      /* CMC      1 RC5(K),RC6(K),RC7(K),RC8(K),RC9(K),RC10(K),IC11(K),IC12(K), */
      /* CMC      2 RC11(K) */
      if (el1_1.ieech == 0) 
	fprintf(iein, " %3d%s%5d%5d%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%5d%5d %5.2f\n",
		elec2_1.ic1[k - 1],
		elec2_1.unitname[k-1],
		elec2_1.ic2[k - 1],
		elec2_1.ic3[k - 1],
		elec2_1.rc4[k - 1], 
		elec2_1.rc5[k - 1], 
		elec2_1.rc6[k - 1], 
		elec2_1.rc7[k - 1], 
		elec2_1.rc8[k - 1], 
		elec2_1.rc9[k - 1], 
		elec2_1.rc10[k - 1], 
		elec2_1.ic11[k - 1], 
		elec2_1.ic12[k - 1],
		elec2_1.rc11[k - 1]);
      
      
      /*<  1511 CONTINUE >*/
      /* L1511: */
    }
    
    
    /*<  1783 CONTINUE >*/
  L1783:
    /* CMC  1783 IF(IEECH.EQ.0)WRITE(IEIN,811)MUNIT */
    /* CMC   811 FORMAT(' ** DATA INPUT FOR ',I4,' UNIT CONVERSIONS') */
    if (el1_1.ieech == 0) 
      fprintf(iein, " ** DATA INPUT FOR %4d UNIT CONVERSIONS",elec3_1.munit);
    
    
    
    /*<       RETURN >*/
    return 0;
    
    /* ***** INPUT ELECTRIC SECTOR DATA SUBSEQUENT TO SECOND YEAR. */
    
    /*<   300 CONTINUE >*/
  L300:
    /*<       RETURN >*/
    return 0;
    
    /* ***** BRANCH FOR ELECTRIC SECTOR ITERATION. */
    
    /*<   200 CONTINUE >*/
  L200:
    
    /*<       DO 3115 MA=1,NUNIT >*/
    i__2 = elec_1.nunit;
    for (ma = 1; ma <= i__2; ++ma) {
      /*<       KUSE(MA)=NUSE(MA) >*/
      elec_1.kuse[ma - 1] = elec_1.nuse[ma - 1];
      /*<  3115 CONTINUE >*/
      /* L3115: */
    }
    
    /* ***** IWRE IS SET IN MAIN. */
    
    /* CMC  8313 IF(IWRE.EQ.1)WRITE(IELC,2214)ITIME,ITN */
    /* CMC  2214 FORMAT(1H1,2(1X,100(1H+),/),2X,'ELECTRIC SECTOR SUMMARY FOR', */
    /* CMC      1 I7,'   ITERATION ',I5) */
    
    if (elec_1.iwre == 1) {
      fprintf(ielc, " ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
      fprintf(ielc, " ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
      fprintf(ielc, " ELECTRIC SECTOR SUMMARY FOR%7d   ITERATION %5d\n",
	      var_1.itime, var_1.itn);
    }
    
    
    /* ***** SKIP IF NO UNIT CONVERSIONS. */
    
    /*<       IF(MUNIT.EQ.0)GO TO 1313 >*/
    if (elec3_1.munit == 0) {
      goto L1313;
    }
    /*<       IF(ITN.GT.1)GO TO 1313 >*/
    if (var_1.itn > 1) {
      goto L1313;
    }
    /*<       IF(IPASS.NE.1)GO TO 1313 >*/
    if (*ipass != 1) {
      goto L1313;
    }
    
    /*<       NOCON=0 >*/
    nocon = 0;
    /*<       DO 1314 J=1,MUNIT >*/
    i__2 = elec3_1.munit;
    for (j = 1; j <= i__2; ++j) {
      /*<       IF(IC11(J).NE.ITIME)GO TO 1314 >*/
      if (elec2_1.ic11[j - 1] != var_1.itime) {
	goto L1314;
      }
      /*<       NOCON=NOCON+1 >*/
      ++nocon;
      /* CMC       IF(NOCON.EQ.1.AND.IWRE.EQ.1)WRITE(IELC,5588)ITIME */
      /* CMC  5588 FORMAT(1H1,1X,50(1H-),/,2X,50(1H-),/,2X,'UNIT CONVERSIONS FOR  ', */
      /* CMC      1 I5,//) */
      if (nocon == 1 && elec_1.iwre == 1) {
	fprintf(ielc," --------------------------------------------------\n");
	fprintf(ielc,"  --------------------------------------------------\n");
	fprintf(ielc,"  UNIT CONVERSIONS FOR  %5d\n\n",var_1.itime);
      }
      /* STB 05/26/94 : the process number is currently being used as an index, */
      /*   rather than searching for it from the list */
      /*   (i.e. proc#(IC1(J)) != IC1(J)) - so search for it. */
      /*      I=IC1(J)  <-- this is the culprit! */
      /*<       DO 5589 K = 1, NUNIT >*/
      i__1 = elec_1.nunit;
      for (k = 1; k <= i__1; ++k) {
	/*<         IF (iProcNum(K) .EQ. IC1(J)) THEN >*/
	if (iprocnum[k - 1] == elec2_1.ic1[j - 1]) {
	  /*<           I=K >*/
	  i__ = k;
	  /*<           GOTO 5560 >*/
	  goto L5560;
	  /*<         END IF >*/
	}
	/*< 5589  CONTINUE >*/
	/* L5589: */
      }
      /*< 5560  CONTINUE >*/
    L5560:
      /*<       IINLK(I)=IC2(J) >*/
      elec1_1.iinlk[i__ - 1] = elec2_1.ic2[j - 1];
      /*<       IOULK(I)=IC3(J) >*/
      elec1_1.ioulk[i__ - 1] = elec2_1.ic3[j - 1];
      
      /* ***** LIFER IS THE REMAINING LIFE OF THE UNIT.  LP IS THE */
      /* ***** REMAINING NUMBER OF PAYMENTS ON ORIGINAL UNIT. */
      
      /*<       LIFER=IYRR(I)-ITIME >*/
      lifer = elec1_1.iyrr[i__ - 1] - var_1.itime;
      /*<       LP=LIFER >*/
      lp = lifer;
      
      /*<       XX=1./(1.+RIRE)                                                    >*/
      xx = 1.f / (elec3_1.rire + 1.f);
      /*     XX=1./(1.+RIR) */
      /*<       FAC=(1.-XX**LP)/(1.-XX) >*/
      fac = (1.f - pow_ri(&xx, &lp)) / (1.f - xx);
      
      /* ***** RCAPI IS THE UN-DERATED ORIGINAL UNIT CAPACITY. */
      /* ***** PVR IS THE $ REMAINING ON DEBT FOR ORIGINAL UNIT. */
      
      /*<       RCAPI=CAP(I)*1000./((1.-FORC(I))*(1.-DMAIN(I)/365.)) >*/
      rcapi = elec1_1.cap[i__ - 1] * 1e3f / ((1.f - elec1_1.forc[i__ - 1]) *
					     (1.f - elec1_1.dmain[i__ - 1] / 365.f));
      /*<       PVR=CAPC(I)*FAC*RCAPI >*/
      pvr = elec1_1.capc[i__ - 1] * fac * rcapi;
      
      /*<       LIFE=IC12(J)-IC11(J) >*/
      life = elec2_1.ic12[j - 1] - elec2_1.ic11[j - 1];
      /*<       CRF=(RIRE*(1.+RIRE)**LIFE)/((1.+RIRE)**LIFE-1.)                    >*/
      r__1 = elec3_1.rire + 1.f;
      r__2 = elec3_1.rire + 1.f;
      crf = elec3_1.rire * pow_ri(&r__1, &life) / (pow_ri(&r__2, &life) - 
						   1.f);
      /*     CRF=(RIR*(1.+RIR)**LIFE)/((1.+RIR)**LIFE-1.) */
      
      /* ***** RC4J IS THE UN-DERATED CAPACITY OF UNIT AFTER CONVERSION. */
      /* ***** PVRA IS THE REMAINING CAPITAL COST OF ORIGINAL UNIT AMORTIZED */
      /* *****  OVER THE CONVERTED UNIT'S LIFE AND ON THE BASIS OF THE */
      /* *****  CONVERTED UNIT'S CAPACITY (IN $/KW/YR). */
      
      /* CMC       IF(RC9(J).EQ.1.) WRITE(*,*) 'Forced outage too large ', RC9(J)      JL 12/95 */
      /* CMC UNKNOWN */
      /* CMC       IF(RC10(J).GE.364.) WRITE(*,*) 'Planned outage too large ',RC10(J)  JL 12/95 */
      
      
	  if(elec2_1.rc9[j - 1] >= 1)
		  fprintf(fp21, "Warning: Forced outage too large\n");
	  if(elec2_1.rc10[j - 1] >= 364)
		  fprintf(fp21, "Warning: Planned outage too large\n"); 

      /*<       RC4J=RC4(J)*1000./((1.-RC9(J))*(1.-RC10(J)/365.)) >*/
      rc4j = elec2_1.rc4[j - 1] * 1e3f / ((1.f - elec2_1.rc9[j - 1]) * (1.f 
									- elec2_1.rc10[j - 1] / 365.f));
	  
      /*<       PVRA=PVR*CRF/RC4J >*/
      pvra = pvr * crf / rc4j;
      /*<       CAPC(I)=RC5(J)+PVRA >*/
      elec1_1.capc[i__ - 1] = elec2_1.rc5[j - 1] + pvra;
      /*<       CAP(I)=RC4(J) >*/
      elec1_1.cap[i__ - 1] = elec2_1.rc4[j - 1];

	  elec1_1.basecap[i__ -1]=rc4j/1000;

      /*<       OMA(I)=RC6(J) >*/
      elec1_1.oma[i__ - 1] = elec2_1.rc6[j - 1];
      /*<       OMB(I)=RC7(J) >*/
      elec1_1.omb[i__ - 1] = elec2_1.rc7[j - 1];
      /*<       HTRT(I)=RC8(J) >*/
      elec1_1.htrt[i__ - 1] = elec2_1.rc8[j - 1];
      /*<       FORC(I)=RC9(J) >*/
      elec1_1.forc[i__ - 1] = elec2_1.rc9[j - 1];
      /*<       DMAIN(I)=RC10(J) >*/
      elec1_1.dmain[i__ - 1] = elec2_1.rc10[j - 1];
      /*<       UMIN(I)=RC11(J) >*/
      elec1_1.umin[i__ - 1] = elec2_1.rc11[j - 1];
      /*<       IYRF(I)=IC11(J) >*/
      elec1_1.iyrf[i__ - 1] = elec2_1.ic11[j - 1];
      /*<       IYRR(I)=IC12(J) >*/
      elec1_1.iyrr[i__ - 1] = elec2_1.ic12[j - 1];
      
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,1317)(LABE(I,KH),KH=1,3), */
      /* CMC      1 (LABV(J,KK),KK=1,3), */
      /* CMC      1 LIFER,PVR,PVRA,RC5(J),CAPC(I) */
      /* CMC  1317 FORMAT(/,5X,'UNIT   ',3A4,'   CONVERTED TO UNIT   ',3A4, */
      /* CMC      1 /,5X,'PRESENT VALUE OF REMAINING DEBT OVER ',I4,' YEARS ($) =', */
      /* CMC      2 F10.3,/,5X,'AMORTIZED REMAINING COST OF OLD UNIT ($/KW/YR) =', */
      /* CMC      3 F10.3,/,5X,'AMORTIZED COST OF CONVERSION ($/KW/YR) = ',F10.3, */
      /* CMC      4 /,5X,'TOTAL AMORTIZED CAPITAL COST OF CONVERTED UNIT ($/KW/YR) =' */
      /* CMC      5 ,F10.3) */
      
      if (elec_1.iwre == 1) {
	fprintf(ielc, "     UNIT   %4d%4d%4d   CONVERTED TO UNIT   %4d%4d%4d\n",
		labe_ref(i__, 1),labe_ref(i__, 2),labe_ref(i__, 3), 
		labv_ref(j,1),labv_ref(j,2),labv_ref(j,3));
	fprintf(ielc, "     PRESENT VALUE OF REMAINING DEBT OVER %4d YEARS ($) =%10.3f\n",
		lifer, pvr);
	fprintf(ielc, "     AMORTIZED REMAINING COST OF OLD UNIT ($/KW/YR) =%10.3f\n",pvra);
	
	fprintf(ielc, "     AMORTIZED COST OF CONVERSION ($/KW/YR) = %10.3f\n",elec2_1.rc5[j - 1]);
	fprintf(ielc, "     TOTAL AMORTIZED CAPITAL COST OF CONVERTED UNIT ($/KW/YR) =%10.3f\n", 
		elec1_1.capc[i__ - 1]);
      }
      
      /*<  1318 DO 1315 KK=1,3 >*/
      /* L1318: */
      for (kk = 1; kk <= 3; ++kk) {
	/*<       LABE(I,KK)=LABV(J,KK) >*/
	labe_ref(i__, kk) = labv_ref(j, kk);
	/*<  1315 CONTINUE >*/
	/* L1315: */
      }
      
      /*<  1314 CONTINUE >*/
    L1314:
      ;
    }
    
    /* ***** CONVERT ELEC DEMAND FROM 000 BOE TO MWH. */
    
    /*<  1313 ELECTR=Q(IOUEL)*1000.*BOEMWH >*/
  L1313:
    electr = net_1.q[toload_1.iouel - 1] * 1e3f * mode_1.boemwh;
    
    /*     Jianwen Lin 1/27/97: before computing demand, the coefficients need to */
    /*                          be recalculated if the load factor special */
    /*                          events are specified */
    /*<       IF(LCOPT.EQ.1)GO TO 1997 >*/
    if (lcopt == 1) {
      goto L1997;
    }
    /*<       Y1=XMLOD >*/
    y1 = elec4_1.xmlod;
    /*<       YB=XLFAC >*/
    yb = elec4_1.xlfac;
    /*<       A0=1. >*/
    a0 = 1.f;
    /*<       A1=6.*(3.*YB-Y1-2.) >*/
    a1 = (yb * 3.f - y1 - 2.f) * 6.f;
    /*<       A2=-82.*YB+27.*Y1+55. >*/
    a2 = yb * -82.f + y1 * 27.f + 55.f;
    /*<       A3=4.*(38.*YB-10.*Y1-28.) >*/
    a3 = (yb * 38.f - y1 * 10.f - 28.f) * 4.f;
    /*<       A4=20.*(-6.*YB+Y1+5.) >*/
    a4 = (yb * -6.f + y1 + 5.f) * 20.f;
    /*<       A5=32.*(YB-1.) >*/
    a5 = (yb - 1.f) * 32.f;
    /*<  1997 CONTINUE >*/
  L1997:
    /*<       PEAK=(1./8760.)*ELECTR/(A0+A1/2.+A2/3.+A3/4.+A4/5.+A5/6.) >*/
    peak = electr * 1.1415525114155251e-4f / (a0 + a1 / 2.f + a2 / 3.f + a3 / 
					      4.f + a4 / 5.f + a5 / 6.f);
    /*<       PKREQ=PEAK*(1. + RMARG) >*/
    pkreq = peak * (rmarg + 1.f);
    /* CMC       IF(IWRE.EQ.1)WRITE(IELC,207)ELECTR,PEAK,RMARG,PKREQ */
    if (elec_1.iwre == 1) 
      fprintf(ielc, "\n\n ELEC DEMAND (MWH) = %10.0f     PEAK DEMAND (MW) = %10.0f     RES MARG =%5.2f     PK + RES REQ (MW) =%10.0f\n",electr, peak, rmarg, pkreq);
    
    /* ***** INITIALIZE FUEL INPUTS TO ELECTRIC SECTOR FOR ITERATION. */
    
    /*<       DO 750 L=1,NINEL >*/
    i__2 = elec3_1.ninel;
    for (l = 1; l <= i__2; ++l) {
      /*<       LNK=IINEL(L) >*/
      lnk = elec1_1.iinel[l - 1];
      /*<       Q(LNK)=0.0 >*/
      net_1.q[lnk - 1] = 0.f;
      /*<   750 CONTINUE >*/
      /* L750: */
    }
    
    /*<       NISUN=0 >*/
    nisun = 0;
    /*<       DCAP=0.0 >*/
    dcap = 0.f;
    /*                                                                       CM 7/88 */
    /* ***** SKIP IF NO UNIT CONVERSIONS                                      CM 7/88 */
    /*                                                                       CM 7/88 */
    /*<       IF (MUNIT .EQ. 0) GOTO 885                                         >*/
    if (elec3_1.munit == 0) {
      goto L885;
    }
    
    /*<       DO 881 I=1,MUNIT >*/
    i__2 = elec3_1.munit;
    for (i__ = 1; i__ <= i__2; ++i__) {
      /*<       LOU=IC3(I) >*/
      lou = elec2_1.ic3[i__ - 1];
      /*<       Q(LOU)=0.0 >*/
      net_1.q[lou - 1] = 0.f;
      /*<   881 CONTINUE >*/
      /* L881: */
    }
    
    /* enter number of units to be loaded first bph 6/90 */
    
    /*< 885   ius=0 >*/
  L885:
    ius = 0;


    /* CMC  882 OPEN (14, FILE = 'b069.dat',  STATUS = 'UNKNOWN')  */
    /* CMC      read (14,884,end=883) iutmp */
    /* CMC      ius=ius+1 */
    /* CMC      iunit(ius)=iutmp */
    /* CMC      goto 882 */
    /* CMC  883 continue                   */
    /* CMC  884 format (i3) */
    /* CMC      close (14) */

    if((fp14=fopen("./b069.dat", "r"))!=NULL){
      while(1){
	fgets(buf, sizeof(buf), fp14);
	if(feof(fp14) )
	  break;
	
	iutmp = atoi(buf);
	++ius;
	elec1_1.iunit[ius - 1] = iutmp;
      }
      fclose(fp14);
    }



    /*<       DO 88 I=1,NUNIT                                                    >*/
    i__2 = elec_1.nunit;
    for (i__ = 1; i__ <= i__2; ++i__) {
      /*<       LOU=IOULK(I) >*/
      lou = elec1_1.ioulk[i__ - 1];
      /*<       Q(LOU)=0.0 >*/
      net_1.q[lou - 1] = 0.f;
      /*<       IF(ITIME.LT.IYRF(I))GO TO 88 >*/
      if (var_1.itime < elec1_1.iyrf[i__ - 1]) {
	goto L88;
      }
      /*<       IF(ITIME.GE.IYRR(I))GO TO 88 >*/
      if (var_1.itime >= elec1_1.iyrr[i__ - 1]) {
	goto L88;
      }
      
      /* ***** COMPUTE VARIABLE COSTS FOR OPERATIONAL UNITS BASED ON PRICES. */
      
      /*<       DCAP=DCAP+CAP(I) >*/
      dcap += elec1_1.cap[i__ - 1];
      /*<       L=IINLK(I) >*/
      l = elec1_1.iinlk[i__ - 1];
      /*<       PR=0.0 >*/
      pr = 0.f;
      /*<       IF(L.EQ.0)GO TO 911 >*/
      if (l == 0) {
	goto L911;
      }
      /*<       PR=P(L) >*/
      pr = net_1.p[l - 1];
      /*<   911 VARCT(I)=OMB(I)/1000.+PR*HTRT(I)/(BOEMBTU*1.E+06) >*/
    L911:
      elec1_1.varct[i__ - 1] = elec1_1.omb[i__ - 1] / 1e3f + pr * 
	elec1_1.htrt[i__ - 1] / (mode_1.boembtu * 1e6f);
	
	emisTax=0;
	for(i=0;i<50;i++){
		emisTax = emisTax + elec_1.Efactors[i__-1][i][0] * elec_1.Efactors[i__-1][i][1]
				  * 5.7356 * elec_1.Efactors[i__-1][i][2]/1000;
	}
	
	/*fprintf(fp25, "Year  Itn NodeType   NodeName   Sector   UEmisTax   Total P   \n");*/
	 if(emisflag==1 && elec1_1.unitype[iu-1]==1)	
	  fprintf(fp25, "%4d%  3d    TU         %s      %s  %10.4f\n",
	      var_1.itime, var_1.itn, LinkNodeNames[11][i__],LinkNodeSector[11][i__],emisTax/units_1.unitcnvt[3]);

	 
	/* emission  tax is in $/boe convert it to $/kwh */
	elec1_1.varct[i__ - 1]=elec1_1.varct[i__ - 1] + emisTax * elec1_1.htrt[i__ - 1] / (mode_1.boembtu * 1e6f);;


      /*<       TEMP(I)=VARCT(I) >*/
      elec1_1.temp[i__ - 1] = elec1_1.varct[i__ - 1];
      
      /* ***** ISUN(.) CONTAINS UNIT NOS. OF UNITS TO BE LOADED BASED ON COSTS. */
      
      /*<       IF(IUS.EQ.0)GO TO 402  >*/
      if (ius == 0) {
	goto L402;
      }
      /*<       DO 401 J=1,IUS >*/
      i__1 = ius;
      for (j = 1; j <= i__1; ++j) {
	/*<       IF(I.EQ.IUNIT(J))GO TO 88 >*/
	if (i__ == elec1_1.iunit[j - 1]) {
	  goto L88;
	}
	/*<   401 CONTINUE >*/
	/* L401: */
      }
      /*<   402 CONTINUE >*/
    L402:
      /*<       NISUN=NISUN+1 >*/
      ++nisun;
      /*<       ISUN(NISUN)=I >*/
      elec1_1.isun[nisun - 1] = i__;
      
      /*<    88 CONTINUE >*/
    L88:
      ;
    }
    
    /* ***** ORDER UNITS ON THE BASIS OF VARIABLE COST (VARCT). */
    /*     STB 05/02/94: or on the optional loading order value */
    
    /*      NX=NISUN */
    /*      DO 13 I=1,NISUN */
    /*      XM=1.E+06 */
    /*      JM=0 */
    
    /*      DO 12 K=1,NX */
    /*      J=ISUN(K) */
    /*      IF(TEMP(J).GE.XM)GO TO 12 */
    /*      XM=TEMP(J) */
    /*      KM=K */
    /*      JM=J */
    /*   12 CONTINUE */
    
    /*      IF(JM.EQ.0)CALL ERR(3) */
    /*      IUNIT(I+IUS)=JM */
    /*      NX=NX-1 */
    /*      IF(KM.EQ.NX+1)GO TO 13 */
    
    /*      DO 473 M=KM,NX */
    /*      ISUN(M)=ISUN(M+1) */
    /*  473 CONTINUE */
    
    /*   13 CONTINUE */
    
    
    /* STB replacement: */
    /*<       nx=nisun >*/
    nx = nisun;
    /*<       do 14 I=1,nisun >*/
    i__2 = nisun;
    for (i__ = 1; i__ <= i__2; ++i__) {
      /*<         ilowestindex = 0 >*/
      ilowestindex = 0;
      /*<         rlowestval = 1.0E+06 >*/
      rlowestval = 1e6f;
      /* look for the unit with the lowest cost (or optional loading order value) */
      /*<         do 12 J=1,nx >*/
      i__1 = nx;
      for (j = 1; j <= i__1; ++j) {
	/*       JL 04/04/97: The ispecLOV value should be iProcNum(isun(j)), not */
	/*                       isun(j), the original is */
	/*          if (ispecLOV(isun(J)) .EQ. 1) then                                JL 04/4/97 */
	/*<           if (ispecLOV(iProcNum(isun(J))) .EQ. 1) then                   >*/
	
	/* if (elec4_1.ispeclov[iprocnum[elec1_1.isun[j - 1] - 1] - 1] == 1) */
    /* The above line has been modified as below - Prakash  */
	 if (elec4_1.ispeclov[elec1_1.isun[j - 1] - 1] == 1)
		{
	    /*           the optionalLOV needs to be / 1000 in order to accurately */
	    /*           compare it to TEMP() */
	    /*<             compValue = optionalLOV(iProcNum(isun(J))) / 1000.0          >*/
	    
		/* compvalue = elec4_1.optionallov[iprocnum[elec1_1.isun[j - 1]- 1] - 1] / 1e3f; */
		/* the above line has been modified as below - Prakash  */
		 compvalue = elec4_1.optionallov[elec1_1.isun[j - 1] - 1] / 1e3f;
	    /*<           else >*/
	} else {
	  /*<             compValue = TEMP(ISUN(J)) >*/
	  compvalue = elec1_1.temp[elec1_1.isun[j - 1] - 1]; 
	  
	  /*<           end if >*/
	}
	/*<           if (compValue .LT. rlowestval) then >*/
	if (compvalue < rlowestval) {
	  /*<             rlowestval = compValue >*/
	  rlowestval = compvalue;
	  /*<             ilowestindex = J >*/
	  ilowestindex = j;
	  /*<           end if >*/
	}
	/*<    12   continue >*/
	/* L12: */
      }
      /* store the lowest as the next in line to be loaded */
      /*<         if (ilowestindex .EQ. 0) call ERR(3) >*/
      if (ilowestindex == 0) {
	err_(&c__3);
      }
      /*<         IUNIT(IUS+I) = ISUN(ilowestindex) >*/
      elec1_1.iunit[ius + i__ - 1] = elec1_1.isun[ilowestindex - 1];

      /* now remove the entry just selected */
      /*<         nx=nx-1 >*/
      --nx;
      /*<         do 13 J=ilowestindex,nx >*/
      i__1 = nx;
      for (j = ilowestindex; j <= i__1; ++j) {
	/*<           ISUN(J) = ISUN(J+1) >*/
	elec1_1.isun[j - 1] = elec1_1.isun[j];
	/*<    13   continue >*/
	/* L13: */
      }
      
      /*<    14 continue   >*/
      /* L14: */
    }
    
    
    /*<       NLOAD=NISUN+IUS >*/
    nload = nisun + ius;
    
    /* ***** IF PASSED FIRST ITERATION, LOAD DURATION CURVE EXISTS. */
    
    /*<       IF(ITN.GT.1)GO TO 905 >*/
    if (var_1.itn > 1) {
      goto L905;
    }
    
    /* ***** COMPUTE DISCRETE INVERSE LOAD DURATION CURVE. */
    
    /*<       R=NCELL >*/
    r__ = (real) ncell;
    /*<       XINCR=1./R >*/
    xincr = 1.f / r__;
    /*<       T=0.0 >*/
    t = 0.f;
    /*<       N=NCELL+1 >*/
    n = ncell + 1;
    /*<       NP=NCELL+2 >*/
    np = ncell + 2;
    
    /*<       DO 15 J=1,N >*/
    i__2 = n;
    for (j = 1; j <= i__2; ++j) {
      /*<       XLDCI(J,1)=A0+A1*T+A2*T**2+A3*T**3+A4*T**4+A5*T**5 >*/
      /* Computing 2nd power */
      r__1 = t;
      /* Computing 3rd power */
      r__2 = t;
      /* Computing 4th power */
      r__3 = t, r__3 *= r__3;
      /* Computing 5th power */
      r__4 = t, r__5 = r__4, r__4 *= r__4;
      xldci_ref(j, 1) = a0 + a1 * t + a2 * (r__1 * r__1) + a3 * (r__2 * (
									 r__2 * r__2)) + a4 * (r__3 * r__3) + a5 * (r__5 * (r__4 * 
															    r__4));
      /*<       XLDCI(J,2)=T >*/
      xldci_ref(j, 2) = t;
      /*<       XLDCI(J,1)=XLDCI(J,1)*PEAK >*/
      xldci_ref(j, 1) = xldci_ref(j, 1) * peak;
      /*<       XLDCI(J,2)=XLDCI(J,2)*8760. >*/
      xldci_ref(j, 2) = xldci_ref(j, 2) * 8760.f;
      /*<       T=T+XINCR >*/
      t += xincr;
      /*<       IF(J.EQ.NCELL)T=0.9999 >*/
      if (j == ncell) {
	t = .9999f;
      }
      /*<    15 CONTINUE >*/
      /* L15: */
    }
    /*<       XLDCI(NP,1)=0.0 >*/
    xldci_ref(np, 1) = 0.f;
    /*<       XLDCI(NP,2)=8760. >*/
    xldci_ref(np, 2) = 8760.f;
    
    /* ***** REVERSE XLDCI VECTORS. */
    
    /*<       NT=NP/2 >*/
    nt = np / 2;
    /*<       DO 37 J=1,NT >*/
    i__2 = nt;
    for (j = 1; j <= i__2; ++j) {
      /*<       K=NP-J+1 >*/
      k = np - j + 1;
      /*<       DO 38 L=1,2 >*/
      for (l = 1; l <= 2; ++l) {
	/*<       X=XLDCI(K,L) >*/
	x = xldci_ref(k, l);
	/*<       XLDCI(K,L)=XLDCI(J,L) >*/
	xldci_ref(k, l) = xldci_ref(j, l);
	/*<       XLDCI(J,L)=X >*/
	xldci_ref(j, l) = x;
	/*<    38 CONTINUE >*/
	/* L38: */
      }
      /*<    37 CONTINUE >*/
      /* L37: */
    }
    
    /* ***** OUTPUT LOAD DURATION CURVE. */
    
    /*<  905  CONTINUE >*/
  L905:
    /* CMC   905 IF(IWRE.EQ.1)WRITE(IELC,606) */
    if (elec_1.iwre == 1) 
      fprintf(ielc, "\n\nLOAD DURATION CURVE:\n          POINT           TIME           LOAD\n");
    
    /*<       DO 51 J=1,NP >*/
    i__2 = np;
    for (j = 1; j <= i__2; ++j) {
      /*<       JJ=NP-J+1 >*/
      jj = np - j + 1;
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,31)J,XLDCI(JJ,2),XLDCI(JJ,1) */
      if (elec_1.iwre == 1) 
	
	/* fprintf(ielc, "     %10d%10d%10d\n", j, xldci_ref(jj, 2),xldci_ref(jj, 1)); */
	/* the above print statement has been modified as below - Prakash  */
    fprintf(ielc, "     %10d%       15.6f%           15.6f\n", j, xldci_ref(jj, 2),xldci_ref(jj, 1));  
      /*<    51 CONTINUE >*/
      /* L51: */
    }
    
    /* ***** LOAD UNITS ONTO LOAD DURATION CURVE. */
    
    /* CMC       IF(IWRE.EQ.1)WRITE(IELC,608) */
    if (elec_1.iwre == 1) {
      fprintf(ielc, "\n\n  UNIT      OPTIONAL       UNIT      UNIT  YEAR      UNIT UNIT UTIL    ENERGY      UNIT       CUM       CUM    PROD   EXIST\n");
      fprintf(ielc, "  NAME      LD ORDER     V COST    F COST BUILT     CAPAC UTIL  MIN        IN    ENERGY    ENERGY      COST   CAPAC   CAPAC\n");
      fprintf(ielc, "                          $/MWH      $/MW              MW            10*3 BOE       MWH  10*6 MWH    10*6 $      MW      MW\n");
    }

	
    /*<       N=1 >*/
    n = 1;
    /*<       IPK=0 >*/
    ipk = 0;
    /*<       COST=0.0 >*/
    cost = 0.f;
    /*<       SCOST=0.0 >*/
    scost = 0.f;
    /*<       CAPX=0.0 >*/
    capx = 0.f;
    /*<       CAPR=0.0 >*/
    capr = 0.f;
    /*<       TENER=0.0 >*/
    tener = 0.f;
    /*<       SENER=0.0 >*/
    sener = 0.f;
    /*<       XORDF=XLDCI(1,1) >*/
    xordf = xldci_ref(1, 1);
    /*<       XORDL=XLDCI(2,1) >*/
    xordl = xldci_ref(2, 1);
    /*<       YORDF=XLDCI(1,2) >*/
    yordf = xldci_ref(1, 2);
    /*<       YORDL=XLDCI(2,2) >*/
    yordl = xldci_ref(2, 2);
    /*<       LDONE=0 >*/
    ldone = 0;
    
    /* ***** LOAD UNITS ACCORDING TO LOAD ORDER. */
    
    /*<         jjj = 1 >*/
    jjj = 1;
    /*<       DO 1002 I=1,NLOAD >*/
    i__2 = nload;
    for (i__ = 1; i__ <= i__2; ++i__) {
      /*<       IU=IUNIT(I) >*/
      iu = elec1_1.iunit[i__ - 1];
      /*<       V=VARCT(IU)*1000. >*/
      v = elec1_1.varct[iu - 1] * 1e3f;
      /*<       UENER=0.0 >*/
      uener = 0.f;
	  elec1_1.generation[iu-1] = uener;
      /*<       U=0.0 >*/
      u = 0.f;
      /*<       QIN=0.0 >*/
      qin = 0.f;
      /*<       QOUT=0.0 >*/
      qout = 0.f;
      /*<       XORDFS = XORDF                                                     >*/
      xordfs = xordf;
      /*<       XORDLS = XORDL                                                     >*/
      xordls = xordl;
      /*<       YORDFS = YORDF                                                     >*/
      yordfs = yordf;
      /*<       YORDLS = YORDL                                                     >*/
      yordls = yordl;
      
      /*<       IF(LDONE.EQ.0)GO TO 7997 >*/
      if (ldone == 0) {
	goto L7997;
      }
      
      /* ***** CHECK IF RESERVE MARGIN HAS BEEN MET AND UNIT NOT USED BEFORE. */
      
      /*<       IF(LDONE.EQ.2.AND.NUSE(IU).EQ.0)GO TO 8008 >*/
      if (ldone == 2 && elec_1.nuse[iu - 1] == 0) {
	goto L8008;
      }
      
      /* ***** UNIT DOES NOT EXIST BUT IS REQUIRED TO MEET RESERVE REQTS */
      /* ***** ONLY.  BUILD UNIT AND LOAD AT ZERO POWER OUTPUT. */
      
      /*<       CAPR=CAPR+CAP(IU) >*/
      capr += elec1_1.cap[iu - 1];
      /*<       PMC=VARCT(IU)*100. >*/
      pmc = elec1_1.varct[iu - 1] * 100.f;
      
      /* ***** COMPUTE FIXED COST FOR UNIT IN TERMS OF $/MW. */
      
      /*<       IF(NUSE(IU).EQ.0)KUSE(IU)=ITIME >*/
      if (elec_1.nuse[iu - 1] == 0) {
	elec_1.kuse[iu - 1] = var_1.itime;
      }
      /*<       FCST=(CAPC(IU)+OMA(IU))*1000. >*/
      fcst = (elec1_1.capc[iu - 1] + elec1_1.oma[iu - 1]) * 1e3f;
      /*<       FCOST=FCST*CAP(IU)/((1.-FORC(IU))*(1.-DMAIN(IU)/365.)) >*/
      fcost = fcst * elec1_1.cap[iu - 1] / ((1.f - elec1_1.forc[iu - 1]) * (
									    1.f - elec1_1.dmain[iu - 1] / 365.f));
      /*<       COST=COST+FCOST >*/
      cost += fcost;
      /*<       SCOST=COST/1.E+06 >*/
      scost = cost / 1e6f;
      
      /*<       IF(IWRE.EQ.1) then >*/
      if (elec_1.iwre == 1) {
	/*<         IF (ispecLOV(iProcNum(IU)) .EQ. 0) THEN >*/
	if (elec4_1.ispeclov[iu - 1] == 0) {
	  /* CMC           WRITE(IELC,7204)(LABE(IU,KK),KK=1,3),                         JL 04/04/97 */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST,             JL 04/04/97 */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  /*<         else >*/
	  fprintf(ielc, "  %s%10.4f %10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	} else {
	  /* CMC           WRITE(IELC,7205)(LABE(IU,KK),KK=1,3), */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST, */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  /*<         end if >*/
	  fprintf(ielc, "  %s%10.4f*%10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	}
	
	/* In the avove print statement elec4_1.optionallov[iprocnum[iu - 1] - 1] has been modified to
		elec4_1.optionallov[iu - 1] - Prakash  */

	/*<       end if >*/
      }



      /*<       IF(LDONE.LT.2.OR.NUSE(IU).EQ.0)GO TO 8514 >*/
      if (ldone < 2 || elec_1.nuse[iu - 1] == 0) {
	goto L8514;
      }
      
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,7219) */
      /* CMC  7219 FORMAT(2X,'VVV*  ABOVE UNIT NOT NEEDED BUT ALREADY EXISTS.  ', */
      /* CMC      1 'FIXED COSTS ADDED.') */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  VVV*  ABOVE UNIT NOT NEEDED BUT ALREADY EXISTS.  FIXED COSTS ADDED.\n");
      /*<       GO TO 8513 >*/
      goto L8513;
      
      /*<  8514 CONTINUE >*/
    L8514:
      /* CMC  8514 IF(IWRE.EQ.1)WRITE(IELC,7201) */
      /* CMC  7201 FORMAT(2X,'RRR*  ABOVE UNIT USED TO MEET RESERVE REQTS ONLY') */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  RRR*  ABOVE UNIT USED TO MEET RESERVE REQTS ONLY\n");
      
      /*<  8513 IF(CAPR.LT.PEAK*(1.+RMARG))GO TO 1001 >*/
    L8513:
      if (capr < peak * (rmarg + 1.f)) {
	goto L1001;
      }
      /*<       LDONE=2 >*/
      ldone = 2;
      /*<       GO TO 1001 >*/
      goto L1001;
      
      /* ***** UNIT COULD BE BUILT BUT IS NOT NEEDED TO SUPPLY POWER. */
      /* ***** PRINT MESSAGE TO THIS EFFECT. */
      
      /*<  8008 IF (IWRE.EQ.1) then >*/
    L8008:
      if (elec_1.iwre == 1) {
	/*<         IF (ispecLOV(iProcNum(IU)) .EQ. 0) THEN >*/
	if (elec4_1.ispeclov[iu -  1] == 0) {
	  /* CMC           WRITE(IELC,7204)(LABE(IU,KK),KK=1,3),                         JL 04/04/97 */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST,             JL 04/04/97 */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  /*<         else >*/
	  fprintf(ielc, "  %s%10.4f %10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	} else {
	  /* CMC           WRITE(IELC,7205)(LABE(IU,KK),KK=1,3), */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST, */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  fprintf(ielc, "  %s%10.4f*%10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	  /*<         end if >*/
	/* In the above print and if staements 	elec4_1.optionallov[iprocnum[iu - 1] - 1] has been changed to
		elec4_1.ispeclov[iu -  1] - Prakash  */


	}
	/*<       end if >*/
      }


      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,7901) */
      /* CMC  7901 FORMAT(2X,'AAA*  ABOVE UNIT NOT CONSTRUCTED. NO POWER REQD') */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  AAA*  ABOVE UNIT NOT CONSTRUCTED. NO POWER REQD\n");
      /*<       GO TO 1001 >*/
      goto L1001;
      
      /* ***** IF IPK = 1, CONSIDER LOADING ONLY PEAKER UNITS. */
      
      /*<  7997 IF(IPK.EQ.0)GO TO 1009 >*/
    L7997:
      if (ipk == 0) {
	goto L1009;
      }
      /*<       IF(UMIN(IU).LE.0.001) GO TO 1009 >*/
      if (elec1_1.umin[iu - 1] <= .001f) {
	goto L1009;
      }
      
      /* ***** ADD FIXED COST OF UNIT IF USED PREVIOUSLY. */
      
      /*<       IF(NUSE(IU).EQ.0)GO TO 9001 >*/
      if (elec_1.nuse[iu - 1] == 0) {
	goto L9001;
      }
      /*<       CAPR=CAPR+CAP(IU) >*/
      capr += elec1_1.cap[iu - 1];
      /*<       PMC=VARCT(IU)*100. >*/
      pmc = elec1_1.varct[iu - 1] * 100.f;
      /*<       FCST=(CAPC(IU)+OMA(IU))*1000. >*/
      fcst = (elec1_1.capc[iu - 1] + elec1_1.oma[iu - 1]) * 1e3f;
      /*<       FCOST=FCST*CAP(IU)/((1.-FORC(IU))*(1.-DMAIN(IU)/365.)) >*/
      fcost = fcst * elec1_1.cap[iu - 1] / ((1.f - elec1_1.forc[iu - 1]) * (
									    1.f - elec1_1.dmain[iu - 1] / 365.f));
      /*<       COST=COST+FCOST >*/
      cost += fcost;
      /*<       SCOST=COST/1.E+06 >*/
      scost = cost / 1e6f;
      
      /*<  9001 IF (IWRE.EQ.1) then >*/
    L9001:
      if (elec_1.iwre == 1) {
	/*<         IF (ispecLOV(iProcNum(IU)) .EQ. 0) THEN >*/
	if (elec4_1.ispeclov[iu - 1] == 0) {
	  /* CMC           WRITE(IELC,7204)(LABE(IU,KK),KK=1,3),                         JL 04/04/97 */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST,             JL 04/04/97 */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  fprintf(ielc, "  %s%10.4f %10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	  /*<         else >*/
	} else {
	  /* CMC           WRITE(IELC,7205)(LABE(IU,KK),KK=1,3), */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST, */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  fprintf(ielc, "  %s%10.4f*%10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	  /*<         end if >*/
	  /* In the above print and if staements 	elec4_1.optionallov[iprocnum[iu - 1] - 1] has been changed to
		elec4_1.ispeclov[iu -  1] - Prakash  */
	}
	/*<       end if >*/
      }



      /* CMC       IF(IWRE.EQ.1.AND.NUSE(IU).GT.0)WRITE(IELC,7202) */
      /* CMC  7202 FORMAT(2X,'PPP*  ABOVE UNIT EXISTS BUT ONLY PEAKING UNITS', */
      /* CMC      1 ' ELIGIBLE.  FIXED COSTS ADDED.') */
      if (elec_1.iwre == 1 && elec_1.nuse[iu - 1] > 0) 
	fprintf(ielc, "  PPP*  ABOVE UNIT EXISTS BUT ONLY PEAKING UNITS ELIGIBLE.  FIXED COSTS ADDED.\n");
      
      /* CMC       IF(IWRE.EQ.1.AND.NUSE(IU).EQ.0)WRITE(IELC,7402) */
      /* CMC  7402 FORMAT(2X,'PPP*  ABOVE UNIT NOT BUILT.  ONLY PEAKING', */
      /* CMC      1' UNITS ELIGIBLE.') */
      if (elec_1.iwre == 1 && elec_1.nuse[iu - 1] == 0) 
	fprintf(ielc, "  PPP*  ABOVE UNIT NOT BUILT.  ONLY PEAKING UNITS ELIGIBLE.\n");
      
      /*<       GO TO 1001 >*/
      goto L1001;
      
      /* ***** LOAD UNIT IU. */
      
      /*<  1009 NS=N >*/
    L1009:
      ns = n;
      /*<       CAPX=CAPX+CAP(IU) >*/
      capx += elec1_1.cap[iu - 1];
      /*<       CAPR=CAPR+CAP(IU) >*/
      capr += elec1_1.cap[iu - 1];
      
      /*<  1006 IF(YORDL.GT.YORDF)YORDL=YORDF >*/
    L1006:
      if (yordl > yordf) {
	yordl = yordf;
      }
      /*<       IF(CAPX.LE.XORDL)GO TO 91 >*/
      if (capx <= xordl) {
	goto L91;
      }
      
      /* ***** UNIT OVERLAPS NEXT CELL. LOAD ENTIRE CELL. */
      
      /*<       ENERG=(XORDL-XORDF)*YORDL+0.5*(XORDL-XORDF)*(YORDF-YORDL) >*/
      energ = (xordl - xordf) * yordl + (xordl - xordf) * .5f * (yordf - 
								 yordl);
      /*<       UENER=UENER+ENERG >*/
      uener += energ;
	  elec1_1.generation[iu-1] = uener;
      
      /*<       N=N+1 >*/
      ++n;
      /*<       IF(N.LT.NP)GO TO 706 >*/
      if (n < np) {
	goto L706;
      }
      
      /* ***** SYSTEM HAS JUST BECOME FULLY LOADED. */
      
      /*<       LDONE=1 >*/
      ldone = 1;
      /*<       IF(CAPR.GE.PEAK*(1.+RMARG))LDONE=2 >*/
      if (capr >= peak * (rmarg + 1.f)) {
	ldone = 2;
      }
      /*<       GO TO 9442 >*/
      goto L9442;
      
      /* ***** GO TO NEXT CELL. */
      
      /*<   706 XORDF=XLDCI(N,1) >*/
    L706:
      xordf = xldci_ref(n, 1);
      /*<       XORDL=XLDCI(N+1,1) >*/
      xordl = xldci_ref(n + 1, 1);
      /*<       YORDF=XLDCI(N,2) >*/
      yordf = xldci_ref(n, 2);
      /*<       YORDL=XLDCI(N+1,2) >*/
      yordl = xldci_ref(n + 1, 2);
      /*<       GO TO 1006 >*/
      goto L1006;
      
      /* ***** UNIT FITS ENTIRELY WITHIN NEXT CELL. */
      
      /*<    91 HT=(YORDF-YORDL)*(1.-(CAPX-XORDF)/(XORDL-XORDF)) >*/
    L91:
      ht = (yordf - yordl) * (1.f - (capx - xordf) / (xordl - xordf));
      /*<    >*/
      energ = (capx - xordf) * yordl + (xordl - xordf) * .5f * (yordf - 
								yordl) - (xordl - capx) * .5f * ht;
      /*<       UENER=UENER+ENERG >*/
      uener += energ;
      elec1_1.generation[iu-1] = uener;

      /*<  9442 U=UENER/(CAP(IU)*8760.) >*/
    L9442:
	  /* the utilization factor was calculated based on derated capacity,
	  changed o base cap or capacity after conversion if any
      u = uener / (elec1_1.cap[iu - 1] * 8760.f); */

	  u = uener / (elec1_1.basecap[iu - 1] * 8760.f);
      /*<       IF(U.GE.UMIN(IU))GO TO 1007 >*/
      if (u >= elec1_1.umin[iu - 1]) {
	goto L1007;
      }
      
      /* ***** UNIT CANNOT BE OPERATED BECAUSE UTILIZATION RATE WOULD BE LESS */
      /* ***** THAN MINIMUM. */
      /* ***** "UNLOAD" UNIT. */
      
      /*<       IF(LDONE.GE.1)LDONE=0 >*/
      if (ldone >= 1) {
	ldone = 0;
      }
      /*<       N=NS >*/
      n = ns;
      /*      XORDF=XLDCI(N,1)                                                 BH11/92 */
      /*      XORDL=XLDCI(N+1,1)                                               BH11/92 */
      /*      YORDF=XLDCI(N,2)                                                 BH11/92 */
      /*      YORDL=XLDCI(N+1,2)                                               BH11/92 */
      /*<       XORDF=XORDFS                                                       >*/
      xordf = xordfs;
      /*<       XORDL=XORDLS                                                       >*/
      xordl = xordls;
      /*<       YORDF=YORDFS                                                       >*/
      yordf = yordfs;
      /*<       YORDL=YORDLS                                                       >*/
      yordl = yordls;
      /*<       CAPX=CAPX-CAP(IU) >*/
      capx -= elec1_1.cap[iu - 1];
      
      /* ***** COMPUTE FIXED COST FOR UNIT IN TERMS OF $/MW. */
      
      /*<       IF(NUSE(IU).EQ.0)GO TO 1233 >*/
      if (elec_1.nuse[iu - 1] == 0) {
	goto L1233;
      }
      /*<       PMC=VARCT(IU)*100. >*/
      pmc = elec1_1.varct[iu - 1] * 100.f;
      /*<       FCST=(CAPC(IU)+OMA(IU))*1000. >*/
      fcst = (elec1_1.capc[iu - 1] + elec1_1.oma[iu - 1]) * 1e3f;
      /*<       FCOST=FCST*CAP(IU)/((1.-FORC(IU))*(1.-DMAIN(IU)/365.)) >*/
      fcost = fcst * elec1_1.cap[iu - 1] / ((1.f - elec1_1.forc[iu - 1]) * (
									    1.f - elec1_1.dmain[iu - 1] / 365.f));
      /*<       COST=COST+FCOST >*/
      cost += fcost;
      /*<       SCOST=COST/1.E+06 >*/
      scost = cost / 1e6f;
      
      /*<  1233 IF (IWRE.EQ.1) then >*/
    L1233:
      if (elec_1.iwre == 1) {
	/*<         IF (ispecLOV(iProcNum(IU)) .EQ. 0) THEN >*/
	if (elec4_1.ispeclov[iu - 1] == 0) {
	  /* CMC           WRITE(IELC,7204)(LABE(IU,KK),KK=1,3),                         JL 04/04/97 */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST,             JL 04/04/97 */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  fprintf(ielc, "  %s%10.4f %10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	  
	} else {
	  /* CMC           WRITE(IELC,7205)(LABE(IU,KK),KK=1,3), */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST, */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  fprintf(ielc, "  %s%10.4f*%10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	  
	}
	/*<       end if >*/
	/* In the above print and if staements 	elec4_1.optionallov[iprocnum[iu - 1] - 1] has been changed to
		elec4_1.ispeclov[iu -  1] - Prakash  */
      }

      
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,7203) */
      /* CMC  7203 FORMAT(2X,'UUU*  ABOVE UNIT AVAILABLE BUT UTIL LT MINIMUM') */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  UUU*  ABOVE UNIT AVAILABLE BUT UTIL LT MINIMUM\n");
      
      /*<       IF(NUSE(IU).EQ.0)GO TO 1001 >*/
      if (elec_1.nuse[iu - 1] == 0) {
	goto L1001;
      }
      
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,1804) */
      /* CMC  1804 FORMAT(2X,'UUU*  ABOVE UNIT ALREADY EXISTS. ADD FIXED COSTS.') */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  UUU*  ABOVE UNIT ALREADY EXISTS. ADD FIXED COSTS.\n");
      
      /*<       GO TO 1001 >*/
      goto L1001;
      
      /* ***** UNIT HAS BEEN COMPLETELY LOADED. */
      
      /*<  1007 TENER=TENER+UENER >*/
    L1007:
      tener += uener;
      
      /* ***** UNIT DID NOT EXIST PREVIOUSLY.  BUILD IT. */
      
      /*<       IF(NUSE(IU).EQ.0)KUSE(IU)=ITIME >*/
      if (elec_1.nuse[iu - 1] == 0) {
	elec_1.kuse[iu - 1] = var_1.itime;
      }
      /*<       FCST=(CAPC(IU)+OMA(IU))*1000. >*/
      fcst = (elec1_1.capc[iu - 1] + elec1_1.oma[iu - 1]) * 1e3f;
      /*<       FCOST=FCST*CAP(IU)/((1.-FORC(IU))*(1.-DMAIN(IU)/365.)) >*/
      fcost = fcst * elec1_1.cap[iu - 1] / ((1.f - elec1_1.forc[iu - 1]) * (
									    1.f - elec1_1.dmain[iu - 1] / 365.f));
      /*<       VCOST=VARCT(IU)*UENER*1000. >*/
      vcost = elec1_1.varct[iu - 1] * uener * 1e3f;
      /*<       COST=COST+VCOST+FCOST >*/
      cost = cost + vcost + fcost;
      /*<       SCOST=COST/1.E+06 >*/
      scost = cost / 1e6f;
      /*<       PMC=VARCT(IU)*100. >*/
      pmc = elec1_1.varct[iu - 1] * 100.f;
      
      /* ***** ASSIGN QUANTITIES TO INPUT AND OUTPUT LINKS. */
      
      /*<       LIN=IINLK(IU) >*/
      lin = elec1_1.iinlk[iu - 1];
      /*<       LOU=IOULK(IU) >*/
      lou = elec1_1.ioulk[iu - 1];
      /*<       QOUT=(UENER/1000.)/BOEMWH                                          >*/
      qout = uener / 1e3f / mode_1.boemwh;
      /*<       QIN=QOUT >*/
      qin = qout;
      /*<       Q(LOU)=Q(LOU)+QOUT >*/
      net_1.q[lou - 1] += qout;
      /*<       IF(LIN.EQ.0)GO TO 789 >*/
      if (lin == 0) {
	goto L789;
      }
      /*<       QIN=QOUT*(HTRT(IU)/3413.) >*/
      qin = qout * (elec1_1.htrt[iu - 1] / 3413.f);
      /*<       if (ntime .gt. 1) Q(LIN)=Q(LIN)+QIN >*/
      if (var_1.ntime > 1) {
	net_1.q[lin - 1] += qin;
      }
      
      /*<   789 SENER=TENER/1.E+06 >*/
    L789:
      sener = tener / 1e6f;
      
      /*<       IF (IWRE.EQ.1) then >*/
      if (elec_1.iwre == 1) {
	/*<         IF (ispecLOV(iProcNum(IU)) .EQ. 0) THEN >*/
	if (elec4_1.ispeclov[iu - 1] == 0) {
	  /* CMC           WRITE(IELC,7204)(LABE(IU,KK),KK=1,3),                         JL 04/04/97 */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST,             JL 04/04/97 */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  fprintf(ielc, "  %s%10.4f %10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	} else {
	  /* CMC           WRITE(IELC,7205)(LABE(IU,KK),KK=1,3), */
	  /* CMC      3                    optionalLOV(iProcNum(IU)),V,FCST, */
	  /* CMC      1                    KUSE(IU),CAP(IU),U,UMIN(IU),QIN,UENER,SENER, */
	  /* CMC      2                    SCOST,CAPX,CAPR */
	  fprintf(ielc, "  %s%10.4f*%10.4f%10.f%6d%10.2f%5.2f%5.2f%10.2f%10.0f%10.4f%10.2f%8.2f%8.2f\n",
		  elec1_1.unitname[iu-1],
		  elec4_1.optionallov[iu - 1],
		  v,fcst,elec_1.kuse[iu - 1],elec1_1.cap[iu - 1],u,
		  elec1_1.umin[iu - 1],qin,uener,sener,scost,capx,capr);
	}
	/* In the above print and if staements 	elec4_1.optionallov[iprocnum[iu - 1] - 1] has been changed to
		elec4_1.ispeclov[iu -  1] - Prakash  */
      }
	  if(*ipass==5) 
		fprintf(elecf, "%d'%d'%s%'%d'%f'%f'%f'%f'%f'%f\n",
		  var_1.itime,iprocnum[iu - 1], elec1_1.unitname[iu-1], elec1_1.unitype[iu-1],qin,uener,
		  elec1_1.basecap[iu-1], elec1_1.cap[iu - 1],u,(vcost + fcost)/1e6f);
      
      /* CMC  7204 FORMAT(2X,3A4,f10.4,1H ,F10.4,F10.0,I6,F10.2,f5.2,f5.2,f10.2, */
      /* CMC      1 F10.0,F10.4,F10.2,2F8.2) */
      /* stb 05/1994 : if optionalLOV is specified, then 7205 is used          stb 05/94 */
      /* CMC  7205 FORMAT(2X,3A4,f10.4,1H*,F10.4,F10.0,I6,F10.2,f5.2,f5.2,f10.2,     stb 05/94 */
      /* CMC      1 F10.0,F10.4,F10.2,2F8.2)                                         stb 05/94 */
      
      /*<       XORDF=CAPX >*/
      xordf = capx;
      /*<       YORDF=YORDF-HT >*/
      yordf -= ht;
      
      /* ***** CHECK IF LOADING IS NOW RESTRICTED TO PEAKING UNITS. */
      
      /*<       ENL=1.-TENER/ELECTR >*/
      enl = 1.f - tener / electr;
      /*<       IPKS=IPK >*/
      ipks = ipk;
      /*<       IF(ENL.LE.PEAKF)IPK=1 >*/
      if (enl <= elec3_1.peakf) {
	ipk = 1;
      }
      
      /* CMC C***** WRITE MESSAGE IF SWITCH TO ALL PEAKERS. */
      
      /*<       IF(IPKS+IPK.NE.1)GO TO 1001 >*/
      if (ipks + ipk != 1) {
	goto L1001;
      }
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,6602)PEAKF,ENL */
      /* CMC  6602 FORMAT(2X,'LOAD ONLY PEAKING UNITS FROM NOW ON.  PK FRAC, ENERG', */
      /* CMC      1 ' REM.  =',2F7.3) */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  LOAD ONLY PEAKING UNITS FROM NOW ON.  PK FRAC, ENERG REM.  =%7.3f%7.3f\n",
		elec3_1.peakf,enl );
      
      /* JLin 06/96: output the throughput of the unit to a QUNIT buffer in order */
      /*             to output a file for the IMPACTS data transfer later on. */
      /*<  1001 QUNIT(NTIME, IU) = QIN >*/
    L1001:
      qunit_ref(var_1.ntime, iu) = qin;
      /*<       NOPERAT(NTIME, IU) = 1   >*/
      noperat_ref(var_1.ntime, iu) = 1;
      /*<  1002 CONTINUE >*/
      /* L1002: */
    }
    
    /* ***** LOADING IS COMPLETE. */
    
    /*<       IF(IWRE.EQ.0)GO TO 1407 >*/
    if (elec_1.iwre == 0) {
      goto L1407;
    }
    
    /*<       IF(CAPR.GE.PEAK)GO TO 1414                                         >*/
    if (capr >= peak) {
      goto L1414;
    }
    /* CMC       IF(IWRE.EQ.1)WRITE(IELC,1408)CAPX,PEAK,TENER,ELECTR */
    /* CMC  1408 FORMAT(/,2X,'WARNING - AVAILABLE UNITS CANNOT',                   MJ060686 */
    /* CMC      1 ' MEET PEAK REQTS',/,2X,'CAP, PEAK, SUPPLY, DEMAND =', */
    /* CMC      2 4F15.4) */
    if (elec_1.iwre == 1) {
      fprintf(ielc, "\n  WARNING - AVAILABLE UNITS CANNOT MEET PEAK REQTS");
      fprintf(ielc, "\n  CAP, PEAK, SUPPLY, DEMAND =%15.4f%15.4f%15.4f%15.4f\n",
	      capx,peak,tener,electr);
	  if(*ipass==5) {
	  fprintf(fp21, "\nWarning: Available units can not meet peak requirement");
      fprintf(fp21, "\nCAP, PEAK, SUPPLY, DEMAND =%15.4f%15.4f%15.4f%15.4f\n",
	      capx,peak,tener,electr); 
	  }
    }
    
    /*<       GO TO 1409 >*/
    goto L1409;
    
    /*<  1414 CONTINUE >*/
  L1414:
    /* CMC  1414 IF(IWRE.EQ.1)WRITE(IELC,1415)PEAK,CAPR                            MJ060686 */
    /* CMC  1415 FORMAT(/,2X,'NOTE 1: AVAILABLE CAPACITY IS ADEQUATE TO MEET',     MJ060686 */
    /* CMC      1 ' PEAK REQTS.',/,3X,'PEAK, PRODUC CAPAC =',2F10.0) */
    if (elec_1.iwre == 1) {
      fprintf(ielc, "\n  NOTE 1: AVAILABLE CAPACITY IS ADEQUATE TO MEET PEAK REQTS.");
      fprintf(ielc, "\n   PEAK, PRODUC CAPAC =%10.0f%10.0f\n",peak,capr);
    }
    
    /*<  1409 IF(CAPR.GE.PEAK*(1.+RMARG))GO TO 1416 >*/
  L1409:
    if (capr >= peak * (rmarg + 1.f)) {
      goto L1416;
    }
    /* CMC       IF(IWRE.EQ.1)WRITE(IELC,1410)CAPR,PEAK,RMARG,TENER,ELECTR         MJ060686 */
    /* CMC  1410 FORMAT(/,2X,'WARNING - AVAILABLE AND ELIGIBLE UNITS CANNOT', */
    /* CMC      1 ' MEET RESERVE REQTS',/,2X,'CAP, PEAK, RES MARG, SUPPLY, DEMAND', */
    /* CMC      2 ' =',5F15.4) */
    if (elec_1.iwre == 1) {
      fprintf(ielc, "\n  WARNING - AVAILABLE AND ELIGIBLE UNITS CANNOT MEET RESERVE REQTS");
      fprintf(ielc, "\n  CAP, PEAK, RES MARG, SUPPLY, DEMAND =%15.4f%15.4f%15.4f%15.4f%15.4f\n",
	      capr,peak,rmarg,tener,electr);
	  if(*ipass==5){
      fprintf(fp21, "\nWarning: Available and eligible units can not meet reserve requirements");
      fprintf(fp21, "\n  CAP, PEAK, RES MARG, SUPPLY, DEMAND =%15.4f%15.4f%15.4f%15.4f%15.4f\n\n",
	      capr,peak,rmarg,tener,electr);
	  }

    }
    /*<       GO TO 1407 >*/
    goto L1407;
    
    /*<  1416 CONTINUE >*/
  L1416:
    /* CMC  1416 IF(IWRE.EQ.1)WRITE(IELC,1417)PEAK,RMARG,PKREQ,CAPR */
    /* CMC  1417 FORMAT(/,2X,'NOTE 2: EXISTING CAPAC IS ADEQUATE TO MEET RESERVE', */
    /* CMC      1 ' REQTS.',/,3X,'PEAK, RES MARG, PK REQ, EXIST CAP =', */
    /* CMC      2 F10.0,F7.2,2F10.0) */
    if (elec_1.iwre == 1) {
      fprintf(ielc, "\n  NOTE 2: EXISTING CAPAC IS ADEQUATE TO MEET RESERVE REQTS.");
      fprintf(ielc, "\n   PEAK, RES MARG, PK REQ, EXIST CAP =%10.0f%7.2f%10.0f%10.0f\n",
	      peak,rmarg,pkreq,capr);
    }    
    /* ***** COMPUTE AVERAGE ELECTRICITY COST IN TERMS OF CENTS/KWH FROM */
    /* ***** $/MWH. */
    
    /*<  1407 AVC=COST/TENER/10. >*/
  L1407:
    avc = cost / tener / 10.f;
    /*<       P(IOUEL)=AVC * BOEMWH * 10.                                        >*/
    net_1.p[toload_1.iouel - 1] = avc * mode_1.boemwh * 10.f;
    /*<       RM=((CAPR-PEAK)/PEAK)*100. >*/
    rm = (capr - peak) / peak * 100.f;
    /*<       RAT=TENER/ELECTR >*/
    rat = tener / electr;
    
    /* CMC       IF(IWRE.EQ.1)WRITE(IELC,54)IOUEL,P(IOUEL) */
    if (elec_1.iwre == 1) 
      fprintf(ielc, "\n\n  OUTPUT LINK AND PRICE ($/BOE) =     %5d%12.4f\n",
	      toload_1.iouel,net_1.p[toload_1.iouel - 1]);
    
    /* CMC       IF(IWRE.EQ.1)WRITE(IELC,518) */
    if (elec_1.iwre == 1) 
      fprintf(ielc, "\n");
    
    
    /*<       DO 1501 I=1,NOUPL >*/
    i__2 = elec3_1.noupl;
    for (i__ = 1; i__ <= i__2; ++i__) {
      /*<       L=IOUPL(I) >*/
      l = elec1_1.ioupl[i__ - 1];
      
      /* ***** COMPUTE ANNUAL LOAD FACTOR BASED ON THE TOTAL DERATED CAPACITY */
      /* ***** OF ALL EXISTING UNITS (INCLUDING UNITS NEEDED TO MAINTAIN */
      /* ***** RESERVE MARGIN BUT NOT PRODUCING ELECTRICITY) AND TOTAL */
      /* ***** ELECTRICITY GENERATED. */
      
      /*<       ALOAD(NTIME)=A0+A1/2.+A2/3.+A3/4.+A4/5.+A5/6.                      >*/
      toload_1.aload[var_1.ntime - 1] = a0 + a1 / 2.f + a2 / 3.f + a3 / 4.f 
	+ a4 / 5.f + a5 / 6.f;
      
      /* ***** COMPUTE ANNUAL GENERATION IN MWH FROM 10**3 BOE. */
      
      /*<       AGENR(NTIME)=Q(IOUEL)*BOEMWH                                       >*/
      toload_1.agenr[var_1.ntime - 1] = net_1.q[toload_1.iouel - 1] * 
	mode_1.boemwh;
      
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,5550)L,Q(L) */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  PROC  LINK AND QUANTITY (000 BOE) = %5d%12.4f\n",
		l,net_1.q[l - 1]);
      
      /*<  1501 CONTINUE >*/
      /* L1501: */
      
    }
    /* CMC       IF(IWRE.EQ.1)WRITE(IELC,518) */
    if (elec_1.iwre == 1) 
      fprintf(ielc, "\n");
    
    
    /*<       DO 910 I=1,NINEL >*/
    i__2 = elec3_1.ninel;
    for (i__ = 1; i__ <= i__2; ++i__) {
      /*<       L=IINEL(I) >*/
      l = elec1_1.iinel[i__ - 1];
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,55)L,Q(L) */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  INPUT LINK AND QUANTITY (000 BOE) = %5d%12.4f\n",
		l,net_1.q[l - 1]);
      
      /*<   910 CONTINUE >*/
      /* L910: */
    }
    
    /*<   809 IF(IPASS.EQ.5)GO TO 3999 >*/
    /* L809: */
    if (*ipass == 5) {
      goto L3999;
    }
    /*<       IF(IWR1.EQ.0)GO TO 999 >*/
    if (var_1.iwr1 == 0) {
      goto L999;
    }
    /* CMC       IF(IWRE.EQ.1)WRITE(IELC,223)ELECTR,TENER,RAT,DCAP,CAPR,CAPX,PEAK, */
    /* CMC      1 RM,COST,AVC,PMC */
    
    if (elec_1.iwre == 1) {
      fprintf(ielc, "\n  TOTAL ELECTRICITY DEMAND (MWH) =%12.0f",electr);
      fprintf(ielc, "\n  EST. ELECTRICITY SUPPLY (MWH) = %12.0f",tener);
      fprintf(ielc, "\n  RATIO SUPPLY/DEMAND (FRAC) =    %12.4f",rat);
      fprintf(ielc, "\n\n  AVAIL DERATED CAPACITY (MW) =   %12.2f",dcap);
      fprintf(ielc, "\n  CAPACITY EXISTING UNITS (MW)  = %12.2f",capr);
      fprintf(ielc, "\n  CAPACITY PRODUCING UNITS (MW) = %12.2f",capx);
      fprintf(ielc, "\n  PEAK DEMAND (MW) =              %12.2f",peak);
      fprintf(ielc, "\n  COMPUTED RESERVE MARGIN (%) =   %12.2f",rm);
      fprintf(ielc, "\n\n'  TOTAL GENERATION COST ($) =     %12.5f",cost);
      fprintf(ielc, "\n  AVE. ELECTRICTY COST (c/KWH) =  %12.4f",avc);
      fprintf(ielc, "\n  LARGEST VAR COST (c/KWH) =      %12.4f",pmc);
    }
    /*<       GO TO 3898 >*/
    goto L3898;
    
    /*<  3999 CONTINUE >*/
  L3999:
    /* CMC  3999 IF(IWRE.EQ.1)WRITE(IELC,223)ELECTR,TENER,RAT,DCAP,CAPR,CAPX,PEAK, */
    /* CMC      1 RM,COST,AVC,PMC */
    if (elec_1.iwre == 1) {
      fprintf(ielc, "\n  TOTAL ELECTRICITY DEMAND (MWH) =%12.0f",electr);
      fprintf(ielc, "\n  EST. ELECTRICITY SUPPLY (MWH) = %12.0f",tener);
      fprintf(ielc, "\n  RATIO SUPPLY/DEMAND (FRAC) =    %12.4f",rat);
      fprintf(ielc, "\n\n  AVAIL DERATED CAPACITY (MW) =   %12.2f",dcap);
      fprintf(ielc, "\n  CAPACITY EXISTING UNITS (MW)  = %12.2f",capr);
      fprintf(ielc, "\n  CAPACITY PRODUCING UNITS (MW) = %12.2f",capx);
      fprintf(ielc, "\n  PEAK DEMAND (MW) =              %12.2f",peak);
      fprintf(ielc, "\n  COMPUTED RESERVE MARGIN (%) =   %12.2f",rm);
      fprintf(ielc, "\n\n'  TOTAL GENERATION COST ($) =     %12.5f",cost);
      fprintf(ielc, "\n  AVE. ELECTRICTY COST (c/KWH) =  %12.4f",avc);
      fprintf(ielc, "\n  LARGEST VAR COST (c/KWH) =      %12.4f",pmc);
    }
    
    /* ***** BY-PASS RECORDING P AND Q IF THIS IS NOT A DUMP YEAR OR NO */
    /* ***** OTHER MODULE CALLED */
    



    /*<       ISUM=ILOD+IELE+IMP+IDMP(NTIME) >*/
    isum = mode_1.ilod + mode_1.iele + mode_1.imp + var_1.idmp[var_1.ntime - 
							       1];
    /*<       IF(ISUM.EQ.0)GO TO 999 >*/
    if (isum == 0) {
      goto L999;
    }
    
    /*<       ZEN(1,IOUEL,IOUTX)=Q(IOUEL)*QSCALE >*/
    zen_ref(1, toload_1.iouel, pri_1.ioutx) = net_1.q[toload_1.iouel - 1] * 
      var_1.qscale;
    /*<       ZEN(2,IOUEL,IOUTX)=P(IOUEL)*PSCALE >*/
    zen_ref(2, toload_1.iouel, pri_1.ioutx) = net_1.p[toload_1.iouel - 1] * 
      pri_1.pscale;
    
    /*<       DO 5533 I=1,NOUPL >*/
    i__2 = elec3_1.noupl;
    for (i__ = 1; i__ <= i__2; ++i__) {
      /*<       L=IOUPL(I) >*/
      l = elec1_1.ioupl[i__ - 1];
      /*<       ZEN(1,L,IOUTX)=Q(L)*QSCALE >*/
      zen_ref(1, l, pri_1.ioutx) = net_1.q[l - 1] * var_1.qscale;
      /*<       ZEN(2,L,IOUTX)=P(L)*PSCALE >*/
      zen_ref(2, l, pri_1.ioutx) = net_1.p[l - 1] * pri_1.pscale;
      /*<  5533 CONTINUE >*/
      /* L5533: */
    }
    /*<       GO TO 999 >*/
    goto L999;
    
    /*<  3898 CONTINUE >*/
  L3898:
    /* CMC  3898 IF(IPASS.EQ.1.AND.IWRE.EQ.1)WRITE(IELC,202)IOUEL,NTIME,P(IOUEL) */
    if (*ipass == 1 && elec_1.iwre == 1) 
      fprintf(ielc, "  Q     DEMAN%4d     LINK%4d     TIME%3d    %11.3f\n",
	      toload_1.iouel,var_1.ntime,net_1.p[toload_1.iouel - 1]);
    
    /*<       IF(IPASS.NE.2)GO TO 999 >*/
    if (*ipass != 2) {
      goto L999;
    }
    /*<       DO 603 I=1,NINEL >*/
    i__2 = elec3_1.ninel;
    for (i__ = 1; i__ <= i__2; ++i__) {
      /*<       ILNK=IINEL(I) >*/
      ilnk = elec1_1.iinel[i__ - 1];
      /* CMC       IF(IWRE.EQ.1)WRITE(IELC,602)ILNK,NTIME,Q(ILNK) */
      if (elec_1.iwre == 1) 
	fprintf(ielc, "  LOAD ONLY PEAKING UNITS FROM NOW ON.  PK FRAC, ENERG REM.  =%7.3f%7.3f\n",
		ilnk,var_1.ntime,net_1.q[ilnk - 1]);
      
      /*<   603 CONTINUE >*/
      /* L603: */
    }
    
    /* CMC       if (ntime.eq.1 .and. iwre.eq.1) write(ielc,6603) */
    /* CMC  6603 format(/,2x,'NOTE:  COMPUTED FUEL INPUT TO GENERATING UNITS IN BASE */
    /* CMC     +YEAR MAY DIFFER FROM ACTUAL BASE YEAR QUANTITIES ON INPUT LINKS') */
    if (var_1.ntime == 1 && elec_1.iwre == 1) 
      fprintf(ielc, "\n  NOTE:  COMPUTED FUEL INPUT TO GENERATING UNITS IN BASEYEAR MAY DIFFER FROM ACTUAL BASE YEAR QUANTITIES ON INPUT LINKS\n");
    
    
    
    /* CMC   518 FORMAT(10X,I10,2(10X,2F14.4)) */
    /* CMC   211 FORMAT(5A4,5X,11I5,/,30X,10I5) */
    /* CMC    54 FORMAT(//,2X,'OUTPUT LINK AND PRICE ($/BOE) =     ',I5,F12.4) */
    /* CMC    55 FORMAT(2X,'INPUT LINK AND QUANTITY (000 BOE) = ',I5,F12.4) */
    /* CMC  5550 FORMAT(2X,'PROC  LINK AND QUANTITY (000 BOE) = ',I5,F12.4) */
    /* CMC   202 FORMAT(2X,'P',5X,'ELECS',9X,'LINK',I4,5X,'TIME', */
    /* CMC      1I3,4X,1H$,F10.4) */
    /* CMC   602 FORMAT(2X,'Q',5X,'ELECS',9X,'LINK',I4,5X,'TIME', */
    /* CMC      1I3,4X,F11.3) */
    /* CMC   606 FORMAT(//,2X,'LOAD DURATION CURVE:',/,10X,'POINT',11X,'TIME',11X, */
    /* CMC      1 'LOAD',/) */
    /* CMC   608 FORMAT(//,10X,'UNIT',2X,'OPTIONAL',7X,'UNIT',6X,'UNIT',2X,'YEAR', */
    /* CMC      1 6X,'UNIT',1X,'UNIT',1X,'UTIL',4X,'ENERGY',6X,'UNIT',7X,'CUM',7X, */
    /* CMC      2 'CUM',4X,'PROD',3X,'EXIST', */
    /* CMC      1 /,10X,'NAME',2X,'LD ORDER',5X,'V COST',4X,'F COST',1X,'BUILT',5X, */
    /* CMC      2 'CAPAC',1X,'UTIL',2X,'MIN',8X,'IN',4X,'ENERGY',4X,'ENERGY',6X, */
    /* CMC      3 'COST',3X,'CAPAC',3X,'CAPAC', */
    /* CMC      4 /,30X,'$/MWH',6X,'$/MW',14X,'MW',12X,'10*3 BOE',7X,'MWH',2X, */
    /* CMC      5 '10*6 MWH',4X,'10*6 $',6X,'MW',6X,'MW',/) */
    /* CMC    30 FORMAT(5X,3A4,5X,I5,5X,F12.6) */
    /* CMC    31 FORMAT(5X,I10,2F15.6) */
    /* CMC    20 FORMAT(5A4,6F10.2) */
    /* CMC    99 FORMAT(I3,3A4,2I3,4F7.2,F10.2,2F5.2,2I5,/,13X,F5.2) */
    /* CMC    96 FORMAT(I3,3A4,2I3,4F7.2,F10.2,2F5.2,2I5,/,F18.2,I2,F7.2)          STB 05/94 */
    /* CMC    97 FORMAT(1X,I3,3A4,2I5,7F10.2,2I5,1X,F5.2)                          BH 6/89 */
    /* CMC   207 FORMAT(//,1X,'ELEC DEMAND (MWH) = ',F10.0,5X, */
    /* CMC      1 'PEAK DEMAND (MW) = ',F10.0,5X,'RES MARG =',F5.2, */
    /* CMC      2 5X,'PK + RES REQ (MW) =',F10.0) */
    /* CMC   222 FORMAT(5X,I10,3X,3A4,3X,6E13.5) */
    /* CMC   223 FORMAT(/,2X,'TOTAL ELECTRICITY DEMAND (MWH) =',F12.0, */
    /* CMC      7         /,2X,'EST. ELECTRICITY SUPPLY (MWH) = ',F12.0, */
    /* CMC      8         /,2X,'RATIO SUPPLY/DEMAND (FRAC) =    ',F12.4, */
    /* CMC      2        //,2X,'AVAIL DERATED CAPACITY (MW) =   ',F12.2, */
    /* CMC     X         /,2X,'CAPACITY EXISTING UNITS (MW)  = ',F12.2, */
    /* CMC     3         /,2X,'CAPACITY PRODUCING UNITS (MW) = ',F12.2, */
    /* CMC     1         /,2X,'PEAK DEMAND (MW) =              ',F12.2, */
    /* CMC     4         /,2X,'COMPUTED RESERVE MARGIN (%) =   ',F12.2, */
    /* CMC     5        //,2X,'TOTAL GENERATION COST ($) =     ',E12.5, */
    /* CMC     6         /,2X,'AVE. ELECTRICTY COST (c/KWH) =  ',F12.4, */
    /* CMC     7         /,2X,'LARGEST VAR COST (c/KWH) =      ',F12.4) */
    /* CMC   970 FORMAT(5A4,7X,17I3) */
    /* CMC  1909 FORMAT(5A4,10I5,/,20X,10I5) */
    
    /*<   999 CONTINUE >*/
  L999:
    
    /*<       RETURN >*/
    return 0;
    /*<       END >*/
  } /* elecs_ */
  
#undef noperat_ref
#undef zen_ref
#undef qunit_ref
#undef xldci_ref
#undef labv_ref
#undef labe_ref


