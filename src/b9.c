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

/* b9.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
   -lf2c -lm   (in that order)
   */
#include <stdio.h>
#include "cmc_f2c.h"
#include <time.h>
#include "f2c.h"
#include "structures.h"



/* ***************************************************************** TOIMP */
/* the subroutine has been modified to create an additional files called
balimw.dat and balimf.dat This file is used in Windows version only and has more precision than balim.dat
The balim.dat file has not been modified as it is used by other ENPEP programs. - Prakash */

/*<       SUBROUTINE TOIMP >*/
/* Subroutine */ int toimp_(void)
{
extern FILE *fp11, *fp21;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];

int ct;
  FILE *fp2, *fp20, *fp22;
  char buf[1024];
  int g, ll, ii;
  char cmc_lab[255];
  int pos;
  char datebuf[128], timebuf[128];
  time_t ltime;
  
  /* System generated locals */
  integer i__1, i__2, i__3;
  
  /* Local variables */
  static real holdlink[999];
  static integer lenstudy, i__, j, k, l, nodep, iyear, nhydr, jk, ilinks, 
  izeros, iqp;
  
  static integer  baseyr;
    static real rmarg;
  
#define labc_ref(a_1,a_2) pro_1.labc[(a_2)*300 + a_1 - 301]
#define labe_ref(a_1,a_2) ref_1.labe[(a_2)*30 + a_1 - 31]
#define labf_ref(a_1,a_2) elec1_1.labf[(a_2)*300 + a_1 - 301]
#define labm_ref(a_1,a_2) min_1.labm[(a_2)*200 + a_1 - 201]
#define labn_ref(a_1,a_2) ren_1.labn[(a_2)*17 + a_1 - 18]
/* #define labr_ref(a_1,a_2) res_1.labr[(a_2)*75 + a_1 - 76]*/
#define prat_ref(a_1,a_2) ref_1.prat[(a_2)*30 + a_1 - 31]
#define iinmi_ref(a_1,a_2) min_1.iinmi[(a_2)*200 + a_1 - 201]
#define iinre_ref(a_1,a_2) ref_1.iinre[(a_2)*30 + a_1 - 31]
#define slate_ref(a_1,a_2) ref_1.slate[(a_2)*30 + a_1 - 31]
#define ioure_ref(a_1,a_2) ref_1.ioure[(a_2)*30 + a_1 - 31]
#define qunit_ref(a_1,a_2) elec_1.qunit[(a_2)*75 + a_1 - 76]
#define rio_ref(a_1,a_2) min_1.rio[(a_2)*200 + a_1 - 201]
#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
#define noperat_ref(a_1,a_2) elec_1.noperat[(a_2)*75 + a_1 - 76]


  /* ***** CREATE DATA FILE TO GO FROM BALANCE TO IMPACTS */
  /* ***** WRITTEN BY JEAN TROMMELS  Feb. 5, 1989 */
  /* ***** MODIFIED BY JEAN TROMMELS Sep. 3, 1989 */
  /* ***** MODIFIED BY JEAN TROMMELS Sep. 24, 1989 */
  /* ***** bph - Jan. 19, 1991 - fix subscript out of range with 10 refineries */
  /* ***** MODIFIED BY JEAN TROMMELS March 3, 1991 discontinued reading from */
  /* ***** ipact.dat for base year and end year. now reads from b011.dat for */
  /* ***** base year and length of planning study. */
  /* ***** MODIFIED BY JEAN TROMMELS 3/23/91 - see comments by NON-ELECTRIC PROCESS DATA */
  /* ***** Steve Bacon: handle the optional loading order sort value */
  
  /*<       DIMENSION HOLDLINK(999) >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  /*<    >*/
  
  /* STB 04/1994: modified the ELEC1 common block to carry the optional */
  /*   loading order value */
  
  /* JLIN 06/96: output the unit throughput quantities by year from buffer QUNIT */
  /*             for IMPACTS data transfer */
  /*<    >*/
  /*<    >*/
  /*<       COMMON/ELEC3/PEAKF,RIRE,NINEL,NOUPL,QIOUEL,MUNIT >*/
  /*<       COMMON/TOLOAD/AGENR(75),ALOAD(75),IOUEL >*/
  /*<       COMMON/SAVEIMP/QNT(92),CAPLIMP(999) >*/
  
  /*<       INTEGER        BASEYR,NODEP,HILINK,LENSTUDY >*/
  /*<       CHARACTER*77   GARBAGE >*/
  /*           NODEP is the max. number of records in the depletable resource loop */
  /*           LENSTUDY is the length of the planning study */
  
  /*     Get baseyear and endyear */
  
  /* CMC       OPEN (2, FILE='B011.DAT',STATUS = 'UNKNOWN') */
  if((fp2=fopen("./b011.dat", "r"))==NULL){
    fprintf(fp21, "Couldnt open B011.DAT\n");
    exit(0);
  }
  /*     read in first 11 lines as garbage */
  /* CMC  11   READ (2,95) GARBAGE */
  /* CMC       READ (2,89) BASEYR */
  /* CMC       READ (2,89) LENSTUDY */
  /* CMC       CLOSE(UNIT=2) */
  
  
  for(g=0;g<11;g++)
    fgets(buf, sizeof(buf), fp2);
  baseyr = atoi( fgets(buf, sizeof(buf), fp2) );
  lenstudy = atoi( fgets(buf, sizeof(buf), fp2) );
  fclose(fp2);
  
  
  /*     Open BALANCE-TO-IMPACTS file. */
  
  /* CMC       OPEN (11, FILE='BALIM.DAT',STATUS = 'UNKNOWN') */
  if((fp11=fopen("./balim.dat", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open BALIM.DAT\n");
    exit(0);
  }

  if((fp20=fopen("./balimw.dat", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open BALIMW.DAT\n");
    exit(0);
  }

	if((fp22=fopen("./balimf.dat", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open BALIMF.DAT\n");
    exit(0);
	}



/* write the header info into baliw.dat */
	

	fprintf(fp20, "LINKS QUANTITY AND PRICE SUMMARY\n");
    time( &ltime );
    fprintf(fp20, "SIMULATION RUN ON:%s", ctime( &ltime ) );


  /*     Write out baseyear and lenstudy */
  /* CMC       WRITE(11,*) BASEYR, LENSTUDY */
  fprintf(fp11, "%d %d\n", baseyr, lenstudy);
  fprintf(fp20, "Baseyear: %d  Number of Years: %d\n\n", baseyr, lenstudy);
  fprintf(fp22, "%d'%d\n", baseyr, lenstudy);


  /*  PRICE/QUANTITY LINK DATA************************************************** */
  /*  Write price/quantity link data. */
  /*  The first time through is for quantity link data; second for price link data */
  
  /*<       DO 620 IQP= 1,2 >*/
  for (iqp = 1; iqp <= 2; ++iqp) {
    
    /* CMC           IF (IQP .EQ. 2) WRITE(11,*) */
    /* CMCUNKNOWN */
    
	if (iqp==1)
		fprintf(fp20, "QUANTITY (%s)\n",units_1.unitname[8]);
	else
		fprintf(fp20, "PRICE (%s)\n", units_1.unitname[3]);

    /*<           DO 711 ILINKS=1,999 >*/
    for (ilinks = 1; ilinks <= 999; ++ilinks) {
     
	/* the code has been modified by Prakash
	the original code was checking if link has quantity > 0.1 in any year
	this resulted in not writing the link info if values are all either zero or has negative
	so I am using net_1.luse, which indicate whether the link is used or not in the network and 
	if it is used write the quantity and price irrespective of their values */

	if (net_1.luse[ilinks-1]==1) {
		fprintf(fp11, "%3d ", ilinks);
		fprintf(fp20, "%s ", LinkNodeNames[13][ilinks]);
		fprintf(fp22, "%d", ilinks);

		for(ct=1; ct<=10; ct++) {
			fprintf(fp11, "%11.1f", zen_ref(iqp, ilinks, ct) );
			if(ct<=lenstudy && iqp==1)
				fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[8] );
			if(ct<=lenstudy && iqp==2)
				fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[3] );
			fprintf(fp22, "'%f", zen_ref(iqp, ilinks, ct) );
			
		}
		fprintf(fp11, "\n");
		fprintf(fp20, "\n");
		fprintf(fp22, "\n");
	}
	else
		goto L711;
      /* CMC               WRITE(11,7) ILINKS, ZEN(IQP,ILINKS,1), ZEN(IQP,ILINKS,2), */
      /* CMC      1            ZEN(IQP,ILINKS,3),ZEN(IQP,ILINKS,4),ZEN(IQP,ILINKS,5), */
      /* CMC      1            ZEN(IQP,ILINKS,6),ZEN(IQP,ILINKS,7),ZEN(IQP,ILINKS,8), */
      /* CMC      1            ZEN(IQP,ILINKS,9), ZEN(IQP,ILINKS,10) */
      
      /*<               IF (LENSTUDY .LT. 11) GO TO 711       >*/
      if (lenstudy < 11) {
	goto L711;
      }
      
      fprintf(fp11, "    ");
      fprintf(fp20, "      ");


      for(ct=11; ct<=20; ct++){
		fprintf(fp11, "%11.1f", zen_ref(iqp, ilinks, ct) );
		if(ct<=lenstudy && iqp==1)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[8] );
		if(ct<=lenstudy && iqp==2)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[3] );
		fprintf(fp22, "'%f", zen_ref(iqp, ilinks, ct) );

	  }

      fprintf(fp11, "\n");
      fprintf(fp20, "\n");
      fprintf(fp22, "\n");

      /* CMC               WRITE(11,8) ZEN(IQP,ILINKS,11), ZEN(IQP,ILINKS,12), */
      /* CMC      1        ZEN(IQP,ILINKS,13),ZEN(IQP,ILINKS,14),ZEN(IQP,ILINKS,15), */
      /* CMC      1        ZEN(IQP,ILINKS,16),ZEN(IQP,ILINKS,17),ZEN(IQP,ILINKS,18), */
      /* CMC      1        ZEN(IQP,ILINKS,19), ZEN(IQP,ILINKS,20) */
      
      /*<               IF (LENSTUDY .LT. 21) GO TO 711       >*/
      if (lenstudy < 21) {
	goto L711;
      }
      fprintf(fp11, "    " );
      fprintf(fp20, "      " );


      for(ct=21; ct<=30; ct++) {
		fprintf(fp11, "%11.1f", zen_ref(iqp, ilinks, ct) );
		if(ct<=lenstudy && iqp==1)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[8] );
		if(ct<=lenstudy && iqp==2)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[3] );
		fprintf(fp22, "'%f", zen_ref(iqp, ilinks, ct) );
		
	  }
      fprintf(fp11, "\n");
      fprintf(fp20, "\n");
      fprintf(fp22, "\n");

      /* CMC               WRITE(11,8) ZEN(IQP,ILINKS,21), ZEN(IQP,ILINKS,22), */
      /* CMC      1        ZEN(IQP,ILINKS,23),ZEN(IQP,ILINKS,24),ZEN(IQP,ILINKS,25), */
      /* CMC      1        ZEN(IQP,ILINKS,26),ZEN(IQP,ILINKS,27),ZEN(IQP,ILINKS,28), */
      /* CMC      1        ZEN(IQP,ILINKS,29), ZEN(IQP,ILINKS,30) */
      
      /*<               IF (LENSTUDY .LT. 31) GO TO 711       >*/
      if (lenstudy < 31) {
	goto L711;
      }
      fprintf(fp11, "    ");
      fprintf(fp20, "      ");


      for(ct=31; ct<=40; ct++) {
		fprintf(fp11, "%11.1f", zen_ref(iqp, ilinks, ct) );
		if(ct<=lenstudy && iqp==1)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[8] );
		if(ct<=lenstudy && iqp==2)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[3] );
		fprintf(fp22, "'%f", zen_ref(iqp, ilinks, ct) );
	  }
      fprintf(fp11, "\n");
      fprintf(fp20, "\n");
      fprintf(fp22, "\n");

      /* CMC               WRITE(11,8) ZEN(IQP,ILINKS,31), ZEN(IQP,ILINKS,32), */
      /* CMC      1        ZEN(IQP,ILINKS,33),ZEN(IQP,ILINKS,34),ZEN(IQP,ILINKS,35), */
      /* CMC      1        ZEN(IQP,ILINKS,36),ZEN(IQP,ILINKS,37),ZEN(IQP,ILINKS,38), */
      /* CMC      1        ZEN(IQP,ILINKS,39), ZEN(IQP,ILINKS,40) */
      
      /*<               IF (LENSTUDY .LT. 41) GO TO 711       >*/
      if (lenstudy < 41) {
	goto L711;
      }
      fprintf(fp11, "    ");
      fprintf(fp20, "      ");


      for(ct=41; ct<=50; ct++) {
		fprintf(fp11, "%11.1f", zen_ref(iqp, ilinks, ct) );
		if(ct<=lenstudy && iqp==1)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[8] );
		if(ct<=lenstudy && iqp==2)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[3] );
		fprintf(fp22, "'%f", zen_ref(iqp, ilinks, ct) );

	  }
      fprintf(fp11, "\n");
	  fprintf(fp20, "\n");	
	  fprintf(fp22, "\n");

      /* CMC               WRITE(11,8) ZEN(IQP,ILINKS,41), ZEN(IQP,ILINKS,42), */
      /* CMC      1        ZEN(IQP,ILINKS,43),ZEN(IQP,ILINKS,44),ZEN(IQP,ILINKS,45), */
      /* CMC      1        ZEN(IQP,ILINKS,46),ZEN(IQP,ILINKS,47),ZEN(IQP,ILINKS,48), */
      /* CMC      1        ZEN(IQP,ILINKS,49), ZEN(IQP,ILINKS,50) */
      
      /*<               IF (LENSTUDY .LT. 51) GO TO 711       >*/
      if (lenstudy < 51) {
	goto L711;
      }
      fprintf(fp11, "    ");
	  fprintf(fp20, "      ");


      for(ct=51; ct<=60; ct++) {
		fprintf(fp11, "%11.1f", zen_ref(iqp, ilinks, ct) );
		if(ct<=lenstudy && iqp==1)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[8] );
		if(ct<=lenstudy && iqp==2)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[3] );
		fprintf(fp22, "'%f", zen_ref(iqp, ilinks, ct) );

	  }
      fprintf(fp11, "\n");
	  fprintf(fp20, "\n");
	  fprintf(fp22, "\n");

      /* CMC               WRITE(11,8) ZEN(IQP,ILINKS,51), ZEN(IQP,ILINKS,52), */
      /* CMC      1        ZEN(IQP,ILINKS,53),ZEN(IQP,ILINKS,54),ZEN(IQP,ILINKS,55), */
      /* CMC      1        ZEN(IQP,ILINKS,56),ZEN(IQP,ILINKS,57),ZEN(IQP,ILINKS,58), */
      /* CMC      1        ZEN(IQP,ILINKS,59), ZEN(IQP,ILINKS,60) */
      
      /*<               IF (LENSTUDY .LT. 61) GO TO 711      >*/
      if (lenstudy < 61) {
	goto L711;
      }
      fprintf(fp11, "    ");
      fprintf(fp20, "      ");


      for(ct=61; ct<=70; ct++) {
		fprintf(fp11, "%11.1f", zen_ref(iqp, ilinks, ct) );
		if(ct<=lenstudy && iqp==1)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[8] );
		if(ct<=lenstudy && iqp==2)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[3] );
		fprintf(fp22, "'%f", zen_ref(iqp, ilinks, ct) );
	  }
      fprintf(fp11, "\n");
	  fprintf(fp20, "\n");
	  fprintf(fp22, "\n");

      /* CMC               WRITE(11,8) ZEN(IQP,ILINKS,61), ZEN(IQP,ILINKS,62), */
      /* CMC      1        ZEN(IQP,ILINKS,63),ZEN(IQP,ILINKS,64),ZEN(IQP,ILINKS,65), */
      /* CMC      1        ZEN(IQP,ILINKS,66),ZEN(IQP,ILINKS,67),ZEN(IQP,ILINKS,68), */
      /* CMC      1        ZEN(IQP,ILINKS,69), ZEN(IQP,ILINKS,70) */
      
      /*<               IF (LENSTUDY .LT. 71) GO TO 711       >*/
      if (lenstudy < 71) {
	goto L711;
      }
      fprintf(fp11, "    ");
	  fprintf(fp20, "      ");



      for(ct=71; ct<=75; ct++) {
		fprintf(fp11, "%11.1f", zen_ref(iqp, ilinks, ct) );
		if(ct<=lenstudy && iqp==1)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[8] );
		if(ct<=lenstudy && iqp==2)
			fprintf(fp20, "%13.3f", zen_ref(iqp, ilinks, ct)/units_1.unitcnvt[3] );
		fprintf(fp22, "'%f", zen_ref(iqp, ilinks, ct) );
	  }
      fprintf(fp11, "\n");
	  fprintf(fp20, "\n");
	  fprintf(fp22, "\n");


      /* CMC               WRITE(11,8) ZEN(IQP,ILINKS,71), ZEN(IQP,ILINKS,72), */
      /* CMC      1        ZEN(IQP,ILINKS,73),ZEN(IQP,ILINKS,74),ZEN(IQP,ILINKS,75) */
      
      /*< 711       CONTINUE >*/
    L711:
      ;
    }
    /*< 620   CONTINUE >*/
    /* L620: */
    fprintf(fp11, "\n"); /* line break between price and quanitity */
	fprintf(fp20, "\n"); /* line break between price and quanitity */
	fprintf(fp22, "\n"); /* line break between price and quanitity */
   }
  
  /*  NON-ELECTRIC PROCESS DATA************************************************ */
  /*  Last modified: 3/23/91 Jean Trommels - altered lines 90,205,305,405,& 505 */
  /*                                        so that all processes would be */
  /*                                        written to balim.dat; */
  /*                                        if the process has no link number(s) */
  /*                                        it is not written out */
  /*     Write depletable resource data (B021) */
  
  /*<       L = 1 >*/
  l = 1;
  /* CMC       WRITE(11,*) */
  /* CMC UNKNOWN */
  /*     90    IF(IOURS(L).EQ.0) GO TO 200 */
  /*     go through all to make sure none are skipped */
  /*< 90    IF(L.EQ.(NRSMX+1)) GO TO 200 >*/
 L90:
  if (l == var_1.nrsmx + 1) {
    goto L200;
  }
  /*         if the link number is 0 then don't write out anything */
  /*<           IF (IOURS(L).EQ.0) GO TO 5   >*/
  if (res_1.iours[l - 1] == 0) {
    goto L5;
  }
  /*<           J = IOURS(L) >*/
  j = res_1.iours[l - 1];
  
  
	fprintf(fp11, "%2d", l);
	fprintf(fp11, "%s", res_1.cmc_labr[l]) ;
	fprintf(fp11, "%3d%12.5E%12.5E\n", res_1.iours[l-1], saveimp_1.qnt[l-1], saveimp_1.caplimp[j-1]);
	

  /* CMC           WRITE(11,92) L,(LABR(L,K),K=1,4),IOURS(L),QNT(L),CAPLIMP(J) */
  /*< 5         L = L + 1 >*/
 L5:
  ++l;
  /*<       GO TO 90  >*/
  goto L90;
  
  /*     Write renewable resource data (B023) */
  
  /*<  200  CONTINUE >*/
 L200:
  /* CMC 200   WRITE(11,*) */
  /* CMC UNKNOWN */
  /*<       NODEP = 30 + 1                                                     >*/
  nodep = 31;
  /*<       L = 1 >*/
  l = 1;
  /*     205   IF (IOURN(L).EQ.0) GO TO 300 */
  /*     go through all 18 to make sure none are skipped */
  /*< 205   IF (L.EQ.(NRNMX+1)) GO TO 300 >*/
 L205:
  if (l == var_1.nrnmx + 1) {
    goto L300;
  }
  /*         if the link number is 0 then don't write out anything */
  /*<           IF (IOURN(L).EQ.0) GO TO 10 >*/
  if (ren_1.iourn[l - 1] == 0) {
    goto L10;
  }
  /*<           J = IOURN(L) >*/
  j = ren_1.iourn[l - 1];
  
	fprintf(fp11, "%2d", l);
    fprintf(fp11, "%s", ren_1.cmc_labn[l] );
	fprintf(fp11, "%3d%12.5E%12.5E\n", ren_1.iourn[l-1], saveimp_1.qnt[nodep-1], saveimp_1.caplimp[j-1]);
  

	/* CMC           WRITE(11,92) L,(LABN(L,K),K=1,4),IOURN(L),QNT(NODEP), */
  /* CMC      1    CAPLIMP(J) */
  /*< 10        NODEP = NODEP + 1 >*/
 L10:
  ++nodep;
  /*<           L = L + 1 >*/
  ++l;
  /*<       GO TO 205 >*/
  goto L205;
  
  /*     Write conversion process data  (B025) */
  
  /*<  300  CONTINUE >*/
 L300:
  /* CMC 300   WRITE(11,*) */
  /* CMC UNKNOWN */
  /*<       L = 1 >*/
  l = 1;
  /*     305   IF (IINPR(L).EQ.0) GO TO 400 */
  /*     go through all to make sure none are skipped */
  /*< 305   IF (L.EQ.(NPRMX+1)) GO TO 400 >*/
 L305:
  if (l == var_1.nprmx + 1) {
    goto L400;
  }
  /*         if both the link numbers are 0 then don't write out anything */
  /*<           IF (IINPR(L).EQ.0.OR.IOUPR(L).EQ.0) GO TO 21 >*/
  if (pro_1.iinpr[l - 1] == 0 || pro_1.ioupr[l - 1] == 0) {
    goto L21;
  }
  /*<           J = IOUPR(L) >*/
  j = pro_1.ioupr[l - 1];
  
  ll = l-1;
  fprintf(fp11, "%3d", l);
  fprintf(fp11,"%s", pro_1.cmc_labc[l] );
  fprintf(fp11, "%3d%3d", pro_1.iinpr[ll], pro_1.ioupr[ll]);
  fprintf(fp11, "%12.5f%12.5f%12.5f%12.5f%12.5f%5d%12.5f%12.5f\n",
	  pro_1.om[ll], pro_1.eff[ll], pro_1.tci[ll], pro_1.capm[ll], pro_1.cf[ll], pro_1.life[ll], pro_1.rir[ll], saveimp_1.caplimp[j-1] );
  

  /* CMC           WRITE(11,94) L,(LABC(L,K),K=1,4),IINPR(L),IOUPR(L),OM(L), */
  /* CMC      1    EFF(L),TCI(L), CAPM(L), CF(L), LIFE(L), RIR(L), CAPLIMP(J) */
  
  /*< 21        L = L + 1 >*/
 L21:
  ++l;
  /*<       GO TO 305 >*/
  goto L305;
  
  /*     Write multi-input conversion process data  (B026) */
  
  /*<  400  CONTINUE >*/
 L400:
  /* CMC 400   WRITE(11,*) */
  /* CMC UNKNOWN */
  /*<       L = 1 >*/
  l = 1;
  /*     405   IF (IOUMI(L).EQ.0) GO TO 500 */
  /*     go through all to make sure none are skipped */
  /*< 405   IF (L.EQ.(NMIMX+1)) GO TO 500 >*/
 L405:
  if (l == min_1.nmimx + 1) {
    goto L500;
  }
  /*         if the link number is 0 then don't write out anything */
  /*<           IF (IOUMI(L).EQ.0) GO TO 23 >*/
  if (min_1.ioumi[l - 1] == 0) {
    goto L23;
  }
  /*<           J = IOUMI(L) >*/
  j = min_1.ioumi[l - 1];
  
  ll = l-1;
  fprintf(fp11, "%2d", l);
  fprintf(fp11,"%s", min_1.cmc_labm[l] );
  fprintf(fp11, "%3d%12.5E%12.5E%12.5E%12.5E%5d%12.5E%12.5E%4d%4d",
	  min_1.ioumi[ll], min_1.omm[ll], min_1.tcim[ll], min_1.capmm[ll], min_1.cfm[ll], min_1.lifem[ll], min_1.rirm[ll], saveimp_1.caplimp[j-1], min_1.ninmi[ll] );
 

  /* CMC 440   FORMAT(I2,4A4,I3,4(1PE12.5),I5,2(1PE12.5),6I4) */

  for(ct=1; ct<=min_1.ninmi[ll]; ct++) {
    fprintf(fp11, "%4d", iinmi_ref(l,ct));
  }
  fprintf(fp11, "\n");
  /* CMC           WRITE(11,440) L,(LABM(L,K),K=1,4),IOUMI(L),OMM(L),TCIM(L), */
  /* CMC      1    CAPMM(L),CFM(L),LIFEM(L),RIRM(L),CAPLIMP(J), */
  /* CMC      1    NINMI(L),(IINMI(L,K),K=1,NINMI(L)) */
  
  for(ct=1; ct<=min_1.ninmi[ll]; ct++) {
	  fprintf(fp11, "%12.5", rio_ref(l,ct));
  }
  fprintf(fp11, "\n");

  /* CMC 470   FORMAT(5(1PE12.5)) */
  /* CMC           WRITE(11,470) (RIO(L,K),K=1,NINMI(L)) */
  
  
  /*< 23        L = L + 1 >*/
 L23:
  ++l;
  /*<       GO TO 405 >*/
  goto L405;
  
  /*     Write refinery node data (multi-output) (B029) */
  
  /*<  500  CONTINUE >*/
 L500:
  /* CMC 500   WRITE(11,*) */
  /* CMC UNKNOWN */
  /*<       L = 1 >*/
  l = 1;
  /*     505   IF (IINRE(L,1).EQ.0) GO TO 600 */
  /*     go through all to make sure none are skipped */
  /*< 505   IF (L.EQ.(NREMX+1)) GO TO 600 >*/
 L505:
  if (l == min_1.nremx + 1) {
    goto L600;
  }
  /*         if the link number is 0 then don't write out anything */
  /*<           IF (IINRE(L,1).EQ.0) GO TO 27 >*/
  if (iinre_ref(l, 1) == 0) {
    goto L27;
  }
  /*<           J = IINRE(L,1) >*/
  j = iinre_ref(l, 1);
  
  
  ll = l-1;
  fprintf(fp11, "%2d", l);
  fprintf(fp11, "%s", ref_1.cmc_labe[l]);
  fprintf(fp11, "%12.5E%12.5E%12.5E%12.5E%3d%12.5E%12.5E%12.5E",
	  ref_1.omr[ll], ref_1.tcir[ll], ref_1.capmr[ll], ref_1.cfr[ll], ref_1.lifer[ll], ref_1.rirr[ll], ref_1.pff[ll], saveimp_1.caplimp[j-1] );
  fprintf(fp11, "%4d%4d%4d", iinre_ref(l,1), ref_1.iordc[ll], ref_1.noure[ll] );
  

  for(ct=1; ct<=ref_1.noure[ll]; ct++) {
	  fprintf(fp11, "%4d", ioure_ref(l,ct));
  }
  fprintf(fp11, "\n");

  /* CMC 550   FORMAT(I2,4A4,4(1PE12.5),I3,3(1PE12.5),9I4) */
  /* CMC           WRITE(11,550) L,(LABE(L,K),K=1,4),OMR(L),TCIR(L),CAPMR(L), */
  /* CMC      1    CFR(L),LIFER(L),RIRR(L),PFF(L),CAPLIMP(J),IINRE(L,1), */
  /* CMC      1    IORDC(L),NOURE(L),(IOURE(L,K),K=1,NOURE(L)) */
  
  
  ll = l-1;
  for(ct=1; ct<=ref_1.noure[ll]; ct++) {
	  fprintf(fp11, "%12.5E", slate_ref(l,ct));

  }
  fprintf(fp11, "\n");


  for(ct=1; ct<=ref_1.noure[ll]; ct++) {
	  fprintf(fp11, "%12.5E", prat_ref(l,ct));

  }
  fprintf(fp11, "\n");


  /* CMC           WRITE(11,553) (SLATE(L,K),K=1,NOURE(L)) */
  /* CMC           WRITE(11,553) (PRAT(L,K),K=1,NOURE(L)) */
  
  
  /*< 27        L = L + 1 >*/
 L27:
  ++l;
  /*         IF (L.gt.10) GO TO 600 */
  /*<       GO TO 505 >*/
  goto L505;
  
  /*  ELECTRIC SYSTEM DATA***************************************************** */
  
  /*  Write electric sector data (B032) */
  
  /*<  600   CONTINUE >*/
 L600:
  /* CMC 600   WRITE(11,*) */
  /* CMC UNKNOWN */
  
  fprintf(fp11, "%4d", elec3_1.ninel);


  for(j=1; j<=elec3_1.ninel; j++) {
    fprintf(fp11, "%4d", elec1_1.iinel[j - 1] );

  }
  fprintf(fp11, "\n");


  fprintf(fp11, "%4d", elec3_1.noupl);

  for(j=1; j<=elec3_1.noupl; j++) {
    fprintf(fp11, "%4d", elec1_1.ioupl[j - 1] );

  }
  fprintf(fp11, "\n");


  fprintf(fp11, "%4d%10.2f%10.2f%10.2f%10.2f\n", toload_1.iouel, elec3_1.qiouel, elec3_1.peakf, rmarg, elec3_1.rire);

  /* CMC 211   FORMAT(20I4) */
  /* CMC 213   FORMAT(I4,4(F10.2)) */
  /* CMC       WRITE(11,211) NINEL, (IINEL(J),J=1,NINEL) */
  /* CMC       WRITE(11,211) NOUPL, (IOUPL(J),J=1,NOUPL) */
  /* CMC       WRITE(11,213) IOUEL, QIOUEL, PEAKF, RMARG, RIRE */
  
  /*  Write thermal electric process data  (B033) */
  
  /*       JLin 07/96 We will sum the quantitity of the units having the same name */
  /*                  and the operating number(NOPERAT) for the plant */
  
  /*<       DO 1105 I = 2, NUNIT >*/
  i__1 = elec_1.nunit;
  for (i__ = 2; i__ <= i__1; ++i__) {
    /*<         DO 1104 J = 1, I-1 >*/
    i__2 = i__ - 1;
    for (j = 1; j <= i__2; ++j) {
      /*<            IF ((LABF(I,1).EQ.LABF(J,1)).AND.(LABF(J,2).NE.0)) THEN >*/
      if (labf_ref(i__, 1) == labf_ref(j, 1) && labf_ref(j, 2) != 0) {
	/*<               LABF(I,2) = 0 >*/
	labf_ref(i__, 2) = 0;
	/*<               DO 1103 K = 1, LENSTUDY >*/
	i__3 = lenstudy;
	for (k = 1; k <= i__3; ++k) {
	  /*<                  QUNIT(K,J) = QUNIT(K,J) + QUNIT(K,I) >*/
	  qunit_ref(k, j) = qunit_ref(k, j) + qunit_ref(k, i__);
	  /*<                  NOPERAT(K,J) = NOPERAT(K,J) + NOPERAT(K,I) >*/
	  noperat_ref(k, j) = noperat_ref(k, j) + noperat_ref(k, 
							      i__);
	  /*< 1103          CONTINUE >*/
	  /* L1103: */
	}
	/*<            END IF >*/
      }
      /*< 1104    CONTINUE >*/
      /* L1104: */
    }
    /*< 1105  CONTINUE >*/
    /* L1105: */
  }
  /* CMC       WRITE(11,*) */
  /* CMC UNKNOWN */
  /*<       J = 0 >*/
  j = 0;
  /*<       DO 1800 I = 1,NUNIT >*/
  i__1 = elec_1.nunit;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       IF (IINLK(I).EQ.0) THEN >*/
    if (elec1_1.iinlk[i__ - 1] == 0) {
      /*<         J = J + 1 >*/
      ++j;
      /*<         HOLDLINK(J) = I >*/
      holdlink[j - 1] = (real) i__;
      /*<       ELSE >*/
    } else {
      /*<         IF (LABF(I,2).NE.0) THEN >*/
      if (labf_ref(i__, 2) != 0) {
	
	ii = i__ - 1;
	fprintf(fp11, "%3d", i__);

	for(ct=1; ct<=3; ct++) {
		fprintf(fp11, "%4d", labf_ref(ii,ct));

	}
	fprintf(fp11, "%4d%4d", elec1_1.iinlk[ii], elec1_1.ioulk[ii] );
	fprintf(fp11, "%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%5.2f\n",
		elec1_1.cap[ii]/((1.0 - elec1_1.forc[ii] )*(1.0 - elec1_1.dmain[ii]/365.0) ),
		elec1_1.capc[ii], elec1_1.oma[ii], elec1_1.omb[ii], elec1_1.htrt[ii], elec1_1.forc[ii], elec1_1.dmain[ii], elec1_1.umin[ii] );


	/* CMC 97    FORMAT(I3,3A4,2I4,7(F10.2),F5.2) */
	/* CMC           WRITE(11,97) I,(LABF(I,KK),KK=1,3), IINLK(I), IOULK(I), */
	/* CMC      1        CAP(I)/((1.-FORC(I))*(1.-DMAIN(I)/365.)),                 JLin 7/96, restore capacity */
	/* CMC      1        CAPC(I), OMA(I), OMB(I),HTRT(I),FORC(I),DMAIN(I),UMIN(I) */
	
	/*<         END IF >*/
      }
      /*<       ENDIF  >*/
    }
    /*< 1800  CONTINUE >*/
    /* L1800: */
  }
  
  /* JLin 06/96: write the energy quantities by unit and by year */
  
  /* CMC       WRITE(11,*) */
  /* CMC UNKNOWN */
  /*<       JK = 0 >*/
  jk = 0;
  /*<       DO 1002 I = 1, NUNIT >*/
  i__1 = elec_1.nunit;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<         IF (IINLK(I)*LABF(I,2).NE.0) THEN >*/
    if (elec1_1.iinlk[i__ - 1] * labf_ref(i__, 2) != 0) {
      /*<               IZEROS = 0  >*/
      izeros = 0;
      /*<               IYEAR = 1 >*/
      iyear = 1;
      /*< 121           IF ((IZEROS .EQ. 1) .OR. (IYEAR .GT. 75)) GO TO 191 >*/
    L121:
      if (izeros == 1 || iyear > 75) {
	goto L191;
      }
      /*<                   IF (QUNIT(IYEAR, I) .GT. 0.1) IZEROS = 1 >*/
      if (qunit_ref(iyear, i__) > .1f) {
	izeros = 1;
      }
      /*<                   IYEAR = IYEAR + 1 >*/
      ++iyear;
      /*<               GO TO 121 >*/
      goto L121;
      /*< 191           IF (IZEROS .EQ. 0) GO TO 1002 >*/
    L191:
      if (izeros == 0) {
	goto L1002;
      }
      /*<               JK = JK + 1 >*/
      ++jk;
      /* CMC               WRITE(11,7) JK, (QUNIT(K,I), K =1,10) */
      fprintf(fp11, "%3d ", jk);


      for(ct=1; ct<=10; ct++) {
		fprintf(fp11, "%11.1f", qunit_ref(ct, i__));

	  }
      fprintf(fp11, "\n");

      /*<               IF (LENSTUDY .LT. 11) GO TO 1002 >*/
      if (lenstudy < 11) {
	goto L1002;
      }
      /* CMC               WRITE(11,8) (QUNIT(K,I), K =11,20) */
      fprintf(fp11, "    " );
      for(ct=11; ct<=20; ct++) {
		fprintf(fp11, "%11.1f", qunit_ref(ct, i__));

	  }
      fprintf(fp11, "\n");

      
      /*<               IF (LENSTUDY .LT. 21) GO TO 1002 >*/
      if (lenstudy < 21) {
	goto L1002;
      }
      /* CMC               WRITE(11,8) (QUNIT(K,I), K =21,30) */
      fprintf(fp11, "    " );

      for(ct=21; ct<=30; ct++) {
		fprintf(fp11, "%11.1f", qunit_ref(ct, i__));

	  }
      fprintf(fp11, "\n");
  
      /*<               IF (LENSTUDY .LT. 31) GO TO 1002       >*/
      if (lenstudy < 31) {
	goto L1002;
      }
      /* CMC               WRITE(11,8) (QUNIT(K,I), K =31,40) */
      fprintf(fp11, "    " );

      for(ct=31; ct<=40; ct++) {
		fprintf(fp11, "%11.1f", qunit_ref(ct, i__));

	  }
      fprintf(fp11, "\n");


      /*<               IF (LENSTUDY .LT. 41) GO TO 1002       >*/
      if (lenstudy < 41) {
	goto L1002;
      }
      /* CMC               WRITE(11,8) (QUNIT(K,I), K =41,50) */
      fprintf(fp11, "    " );


      for(ct=41; ct<=50; ct++) {
		fprintf(fp11, "%11.1f", qunit_ref(ct, i__));

	  }
      fprintf(fp11, "\n");

      
      /*<               IF (LENSTUDY .LT. 51) GO TO 1002       >*/
      if (lenstudy < 51) {
	goto L1002;
      }
      /* CMC               WRITE(11,8) (QUNIT(K,I), K =51,60) */
      fprintf(fp11, "    " );

      for(ct=51; ct<=60; ct++) {
		fprintf(fp11, "%11.1f", qunit_ref(ct, i__));

	  }
      fprintf(fp11, "\n");


      /*<               IF (LENSTUDY .LT. 61) GO TO 1002      >*/
      if (lenstudy < 61) {
	goto L1002;
      }
      /* CMC               WRITE(11,8) (QUNIT(K,I), K = 61,70) */
      fprintf(fp11, "    " );


      for(ct=61; ct<=70; ct++) {
		fprintf(fp11, "%11.1f", qunit_ref(ct, i__));

	  }
      fprintf(fp11, "\n");

      
      /*<               IF (LENSTUDY .LT. 71) GO TO 1002       >*/
      if (lenstudy < 71) {
	goto L1002;
      }
      /* CMC               WRITE(11,8) (QUNIT(K,I), K =71,75) */
      fprintf(fp11, "    " );


      for(ct=71; ct<=75; ct++) {
		fprintf(fp11, "%11.1f", qunit_ref(ct, i__));

	  }
      fprintf(fp11, "\n");

      /*<            ENDIF >*/
    }
    /*< 1002    CONTINUE >*/
  L1002:
    ;
  }
  
  /* JLin 07/96: write the operating unit number by plant and by year */
  
  /* CMC       WRITE(11,*) */
  /* CMC UNKNOWN */
  /*<       JK = 0 >*/
  jk = 0;
  /*<       DO 1003 I = 1, NUNIT >*/
  i__1 = elec_1.nunit;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<         IF (IINLK(I)*LABF(I,2).NE.0) THEN >*/
    if (elec1_1.iinlk[i__ - 1] * labf_ref(i__, 2) != 0) {
      /*<               IZEROS = 0  >*/
      izeros = 0;
      /*<               IYEAR = 1 >*/
      iyear = 1;
      /*< 122           IF ((IZEROS .EQ. 1) .OR. (IYEAR .GT. 75)) GO TO 192 >*/
    L122:
      if (izeros == 1 || iyear > 75) {
	goto L192;
      }
      /*<                   IF (QUNIT(IYEAR, I) .GT. 0.1) IZEROS = 1 >*/
      if (qunit_ref(iyear, i__) > .1f) {
	izeros = 1;
      }
      /*<                   IYEAR = IYEAR + 1 >*/
      ++iyear;
      /*<               GO TO 122 >*/
      goto L122;
      /*< 192           IF (IZEROS .EQ. 0) GO TO 1003 >*/
    L192:
      if (izeros == 0) {
	goto L1003;
      }
      /*<               JK = JK + 1 >*/
      ++jk;
      /* CMC               WRITE(11,7) JK, (NOPERAT(K,I), K =1,10) */
      fprintf(fp11, "%3d ", jk);


      for(ct=1; ct<=10; ct++) {
		fprintf(fp11, "%11.1f", noperat_ref(ct, i__) );

	  }
      fprintf(fp11, "\n");

      
      /*<               IF (LENSTUDY .LT. 11) GO TO 1003 >*/
      if (lenstudy < 11) {
	goto L1003;
      }
      /* CMC               WRITE(11,8) (NOPERAT(K,I), K =11,20) */
      fprintf(fp11, "    ");


      for(ct=11; ct<=20; ct++) {
		fprintf(fp11, "%11.1f", noperat_ref(ct, i__) );

	  }
      fprintf(fp11, "\n");

      
      /*<               IF (LENSTUDY .LT. 21) GO TO 1003 >*/
      if (lenstudy < 21) {
	goto L1003;
      }
      /* CMC               WRITE(11,8) (NOPERAT(K,I), K =21,30) */
      fprintf(fp11, "    ");


      for(ct=21; ct<=30; ct++) {
		fprintf(fp11, "%11.1f", noperat_ref(ct, i__) );

	  }

      fprintf(fp11, "\n");
  
      /*<               IF (LENSTUDY .LT. 31) GO TO 1003       >*/
      if (lenstudy < 31) {
	goto L1003;
      }
      /* CMC               WRITE(11,8) (NOPERAT(K,I), K =31,40) */
      fprintf(fp11, "    ");


      for(ct=31; ct<=40; ct++) {
		fprintf(fp11, "%11.1f", noperat_ref(ct, i__) );

	}
      fprintf(fp11, "\n");

      
      
      /*<               IF (LENSTUDY .LT. 41) GO TO 1003       >*/
      if (lenstudy < 41) {
	goto L1003;
      }
      /* CMC               WRITE(11,8) (NOPERAT(K,I), K =41,50) */
      fprintf(fp11, "    ");


      for(ct=41; ct<=50; ct++) {
		fprintf(fp11, "%11.1f", noperat_ref(ct, i__) );

	}
      fprintf(fp11, "\n");
    
      
      /*<               IF (LENSTUDY .LT. 51) GO TO 1003       >*/
      if (lenstudy < 51) {
	goto L1003;
      }
      /* CMC               WRITE(11,8) (NOPERAT(K,I), K =51,60) */
      fprintf(fp11, "    ");


      for(ct=51; ct<=60; ct++) {
		fprintf(fp11, "%11.1f", noperat_ref(ct, i__) );

	  }

      fprintf(fp11, "\n");
 
      
      /*<               IF (LENSTUDY .LT. 61) GO TO 1003      >*/
      if (lenstudy < 61) {
	goto L1003;
      }
      /* CMC               WRITE(11,8) (NOPERAT(K,I), K = 61,70) */
      fprintf(fp11, "    ");


      for(ct=61; ct<=70; ct++) {
		fprintf(fp11, "%11.1f", noperat_ref(ct, i__) );

	  }

      fprintf(fp11, "\n");
  
      
      /*<               IF (LENSTUDY .LT. 71) GO TO 1003       >*/
      if (lenstudy < 71) {
	goto L1003;
      }
      /* CMC               WRITE(11,8) (NOPERAT(K,I), K =71,75) */
      fprintf(fp11, "    ");


      for(ct=71; ct<=75; ct++) {
		fprintf(fp11, "%11.1f", noperat_ref(ct, i__) );

	  }

      fprintf(fp11, "\n");

      
      /*<            ENDIF >*/
    }
    /*< 1003    CONTINUE >*/
  L1003:
    ;
  }
  
  /*  Write hydroelectric process data  (B034) */
  
  /* CMC       WRITE(11,*) */
  /* CMC UNKNOWN */
  /*<       NHYDR =  J >*/
  nhydr = j;
  /*<       DO 1850 K = 1, NHYDR >*/
  i__1 = nhydr;
  for (k = 1; k <= i__1; ++k) {
    /*<        I = HOLDLINK(K)   >*/
    i__ = holdlink[k - 1];
    
    ii = i__1 - 1;
    fprintf(fp11, "%3d", i__1);

    for(ct=1; ct<=3; ct++) {
		fprintf(fp11, "%4d", labf_ref(i__1,ct));

	}
    fprintf(fp11, "%4d%4d", elec1_1.iinlk[ii], elec1_1.ioulk[ii] );
    fprintf(fp11, "%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%10.2f%5.2f\n",
	    elec1_1.cap[ii], elec1_1.capc[ii], elec1_1.oma[ii], elec1_1.omb[ii], elec1_1.htrt[ii], elec1_1.forc[ii], elec1_1.dmain[ii], elec1_1.umin[ii] );
    

	/* CMC 97    FORMAT(I3,3A4,2I4,7(F10.2),F5.2) */
    /* CMC        WRITE(11,97) I,(LABF(I,KK),KK=1,3), IINLK(I), IOULK(I), CAP(I), */
    /* CMC      1      CAPC(I), OMA(I), OMB(I), HTRT(I), FORC(I),DMAIN(I), UMIN(I) */
    /*< 1850  CONTINUE >*/
    /* L1850: */
  }
  
  /*  Write data for unit conversions (B035) */
  /* ******** COMMENTED OUT IN FORTRAN CODE ***********  */
  /* CMC       WRITE(11,*) */
  /*      DO 1750 K = 1,MUNIT */
  /* CMC c      WRITE(11,96) IC1(K),(LABV(K,KK),KK=1,3), IC2(K), IC3(K), RC4(K), */
  /*     1     RC5(K), RC6(K), RC7(K), RC8(K), RC9(K), RC10(K), IC11(K), */
  /*     1     IC12(K), RC11(K) */
  /* 1750  CONTINUE */
  /* CMC       WRITE(11,*) */
  /* ******** COMMENTED OUT IN FORTRAN CODE ***********  */
  
  /*   Go back to main (b1) */
  /* CMC       CLOSE (UNIT=11) */
  fclose(fp11);
  fclose(fp20);
  fclose(fp22);

  /*<       RETURN >*/
  return 0;
  /* *************************************************************************** */
  /* CMC 7     FORMAT(I3,' ',10(F11.1)) */
  /* CMC 8     FORMAT('    ',10(F11.1)) */
  /* CMC 92    FORMAT(I2,4A4,I3,2(1PE12.5)) */
  /* CMC 94    FORMAT(I3,4A4,2(I3),5(1PE12.5),I5,2(1PE12.5)) */
  /* CMC 440   FORMAT(I2,4A4,I3,4(1PE12.5),I5,2(1PE12.5),6I4) */
  /* CMC 470   FORMAT(5(1PE12.5)) */
  /* CMC 550   FORMAT(I2,4A4,4(1PE12.5),I3,3(1PE12.5),9I4) */
  /* CMC 553   FORMAT(6(1PE12.5)) */
  /* CMC 211   FORMAT(20I4) */
  /* CMC 213   FORMAT(I4,4(F10.2)) */
  /* CMC 97    FORMAT(I3,3A4,2I4,7(F10.2),F5.2) */
  /* CMC 96    FORMAT(I3,3A4,2I4,7(F10.2),2I5,F5.2) */
  /* CMC 89    FORMAT(I6) */
  /* CMC 103   FORMAT(A8) */
  /* CMC 91    FORMAT(A3) */
  /* CMC 95    FORMAT(A10) */
  /* CMC 98    FORMAT(A24) */
  /* CMC 99    FORMAT(A77) */
  /* CMC 100   FORMAT(A77) */
  /* CMC 101   FORMAT(A77) */
  /* CMC 102   FORMAT(A2) */
  /*<       END  >*/
} /* toimp_ */



#undef noperat_ref
#undef zen_ref
#undef rio_ref
#undef qunit_ref
#undef ioure_ref
#undef slate_ref
#undef iinre_ref
#undef iinmi_ref
#undef prat_ref
/* #undef labr_ref*/
#undef labn_ref
#undef labm_ref
#undef labf_ref
#undef labe_ref
#undef labc_ref
