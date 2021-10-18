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

/* b6.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/
#include <stdio.h>
#include "cmc_f2c.h"
#include <stdlib.h>
#include "f2c.h"
#include "structures.h"


/* ******************************************************************** MI */

/*<       SUBROUTINE MI(IPASS,IPR,KSPEC) >*/
/* Subroutine */ int mi_(integer *ipass, integer *ipr, integer *kspec)
{
real emisTax;
int i,j;
extern int emisflag;
extern FILE *fp6, *fp11, *fp25;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer ilnk, iolk;
    static real sump;
    static integer i__, l;
    static real qoutm, qouti, pq;
    static integer nin, ipm;
    static real sum;

/* #define labm_ref(a_1,a_2) min_1.labm[(a_2)*15 + a_1 - 16] */
#define iinmi_ref(a_1,a_2) min_1.iinmi[(a_2)*200 + a_1 - 201]
#define rio_ref(a_1,a_2) min_1.rio[(a_2)*200 + a_1 - 201]
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

/*<       IOLK=IOUMI(IPR) >*/
    iolk = min_1.ioumi[*ipr - 1];
/*<       L=IOLK >*/
    l = iolk;
/*<       IF(IPASS.LT.6)GO TO 4511 >*/
    if (*ipass < 6) {
	goto L4511;
    }
/*<       IPM=IPASS-5 >*/
    ipm = *ipass - 5;
/* CMC       WRITE(11,4903)(LABM(IPR,J),J=1,4) */
/* CMC  4903 FORMAT(2X,5A4) */
fprintf(fp11,"  %s\n", min_1.cmc_labm[*ipr] );


/* CMC       IF(IPASS.EQ.6)WRITE(11,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
/* CMC  4411 FORMAT(1X,I4,1X,'Q',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
/* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
/* CMC      2  ,/,10X,5F11.1) */
    if (*ipass == 6) {
    fprintf(fp11," %4d Q   ", l);
    for(j=1; j<=pri_1.ioutx;j++){
      if( ((j-1)%10==0) && (j>1)) 
	fprintf(fp11,"\n          ");
      fprintf(fp11,"%11.1f", zen_ref(1, l, j));
    }
    fprintf(fp11,"\n");    }


/* CMC       IF(IPASS.EQ.7)WRITE(11,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
/* CMC  4412 FORMAT(1X,I4,1X,'P',3X,10F9.2,/,10X,10F9.2,/,10X,10F9.2 */
/* CMC      1   ,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F2.2 */
/* CMC      2   ,/,10X,5F9.2) */
  if (*ipass == 7) {
    fprintf(fp11," %4d P   ", l);
    for(j=1; j<=pri_1.ioutx;j++){
      if( ((j-1)%10==0) && (j>1)) 
	fprintf(fp11,"\n          ");
      fprintf(fp11,"%9.2f", zen_ref(2,l,j));
    }
    fprintf(fp11,"\n");
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
/*<       IF(IPASS.EQ.2)GO TO 100 >*/
    if (*ipass == 2) {
	goto L100;
    }

/*<       SUM=0. >*/
    sum = 0.f;
/*<       SUMP=0. >*/
    sump = 0.f;
/*<       NIN=NINMI(IPR) >*/
    nin = min_1.ninmi[*ipr - 1];
/*<       QOUTM=1.E+15 >*/
    qoutm = 1e15f;

/*<       DO 110 I=1,NIN >*/
    i__1 = nin;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       L=IINMI(IPR,I) >*/
	l = iinmi_ref(*ipr, i__);
/*<       SUMP=SUMP+P(L)*RIO(IPR,I) >*/
	sump += net_1.p[l - 1] * rio_ref(*ipr, i__);
/*<       SUM=SUM+RIO(IPR,I) >*/
	sum += rio_ref(*ipr, i__);
/*<       QOUTI=1.E+15                                                       >*/
	qouti = 1e15f;
/*<       IF(RIO(IPR,I).NE.0)QOUTI=Q(L)/RIO(IPR,I)                           >*/
	if (rio_ref(*ipr, i__) != 0.f) {
	    qouti = net_1.q[l - 1] / rio_ref(*ipr, i__);
	}
/*<       IF(QOUTI.LT.QOUTM)QOUTM=QOUTI >*/
	if (qouti < qoutm) {
	    qoutm = qouti;
	}
/*<   110 CONTINUE >*/
/* L110: */
    }
/*<       SUMP=SUMP/SUM >*/
    sump /= sum;

/*<       P(IOLK)=SUMP+CCM(IPR)+OMM(IPR) >*/
    net_1.p[iolk - 1] = sump + min_1.ccm[*ipr - 1] + min_1.omm[*ipr - 1];
/*<       IF(NTIME.EQ.1)Q(IOLK)=QOUTM >*/


	/* compute emission tax and add to price */
	emisTax=0;

	for(i=0;i<50;i++){
		emisTax = emisTax +  min_1.Efactors[*ipr-1][i][0] * min_1.Efactors[*ipr-1][i][1]
			       * 5.7356 * min_1.Efactors[*ipr-1][i][2]/1000;
		}
	
	/*fprintf(fp25, "Year  Itn NodeType   NodeName   Sector   UEmisTax   Total P   \n");*/
	if(emisflag==1)
		fprintf(fp25, "%4d%  3d    MI         %s      %s  %10.4f       %10.4f\n",
			var_1.itime, var_1.itn, LinkNodeNames[2][(*ipr)],LinkNodeSector[2][(*ipr)],emisTax/units_1.unitcnvt[3], 
			(emisTax+net_1.p[iolk - 1])/units_1.unitcnvt[3]);

	net_1.p[iolk - 1]=net_1.p[iolk - 1] + emisTax;

    if (var_1.ntime == 1) {
	net_1.q[iolk - 1] = qoutm;
    }

/* CMC       IF(IWR1.GE.2)WRITE(6,202)IPR,IOLK,NTIME,P(IOLK) */
/* CMC   202 FORMAT(2X,'P',5X,'MULIN',I4,5X,'LINK',I4,5X,'TIME', */
/* CMC      1I3,4X,1H$,F10.4) */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  P     MI  %s (%s)     LINK  %s     YEAR%6d    $%10.4f\n",
	      LinkNodeNames[2][(*ipr)],LinkNodeSector[2][(*ipr)],LinkNodeNames[13][iolk],var_1.itime,net_1.p[iolk - 1]/units_1.unitcnvt[3]);
    
/*<       RETURN >*/
    return 0;

/* ***** DOWNPASS LOGIC. */

/*<   100 CONTINUE >*/
L100:

/*<       NIN=NINMI(IPR) >*/
    nin = min_1.ninmi[*ipr - 1];
/*<       DO 111 I=1,NIN >*/
    i__1 = nin;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<       ILNK=IINMI(IPR,I) >*/
	ilnk = iinmi_ref(*ipr, i__);
/*<       Q(ILNK)=Q(IOLK)*RIO(IPR,I) >*/
	net_1.q[ilnk - 1] = net_1.q[iolk - 1] * rio_ref(*ipr, i__);
/* CMC       IF(IWR1.GE.2)WRITE(6,602)IPR,ILNK,NTIME,Q(ILNK) */
/* CMC   602 FORMAT(2X,'Q',5X,'MULIN',I4,5X,'LINK',I4,5X,'TIME', */
/* CMC      1I3,4X,F11.3) */
	if (var_1.iwr1 >= 2) 
	  fprintf(fp6, "  Q     MI  %s (%s)     LINK  %s     YEAR%6d    %11.3f\n",
		LinkNodeNames[2][(*ipr)],LinkNodeSector[2][(*ipr)],LinkNodeNames[13][ilnk],var_1.itime,net_1.q[ilnk - 1]/units_1.unitcnvt[8]);

	
	
/*<   111 CONTINUE >*/
/* L111: */
    }

/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* mi_ */
/*#undef labm_ref*/
#undef zen_ref
#undef rio_ref
#undef iinmi_ref



/* ****************************************************************** OUTW */

/*<       SUBROUTINE OUTW(ICODE) >*/
/* Subroutine */ int outw_(integer *icode)
{
int pos;
char buf[1024];
extern FILE *fp5, *fp12, *fp11, *fp21;
FILE *fp2;
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    cllist cl__1;

    /* Builtin functions */
    integer f_clos(cllist *);

    /* Local variables */
    static integer labz[75];
    static real pave, drev, dpqq;
    static integer isum;
    static real revs[75];
    static integer iouw;
    static real pqqs[75], qsum, pqqz[76];
    static integer i__, j, k, n, kcode, ncode[99], lcode, llink[23760]	/* 
	    was [99][12][20] */, ispan;
    static real pqdis, rspan;
    static integer nentr[99];
    static real revds;
    static integer ntitl, kount, joutx;
    static real dq;
    static integer ng;
    static real rj;
    static integer kv, nt;
    static real qs[75], qz[76];
    static integer nne;
    static real dpq, sdr, rev[76];
    static integer iqz[76];
    static real pqs[75];
    static integer ntv;
    static real pqz[76], yrs;

    static integer ltitl[1287];	/* was [99][13] */
    static integer lable[15444];	/* was [99][12][13] */


#define lable_ref(a_1,a_2,a_3) lable[((a_3)*12 + (a_2))*99 + a_1 - 1288]
#define llink_ref(a_1,a_2,a_3) llink[((a_3)*12 + (a_2))*99 + a_1 - 1288]
#define ltitl_ref(a_1,a_2) ltitl[(a_2)*99 + a_1 - 100]
#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]

/*<    >*/

/*<    >*/
/*<       COMMON/EL1/LWRIT(75),ITELF(75),ITELL(75),IECHO,IEECH,IFINL >*/
/*<    >*/
/*<       COMMON/OUTWR/ LABY(75) >*/

/* CMC C***** READ IF ICODE=1. */
/* CMC C***** WRITE IF ICODE=2. */

/*<       GO TO (101,102),ICODE >*/
    switch (*icode) {
	case 1:  goto L101;
	case 2:  goto L102;
    }
/*<  101   CONTINUE >*/
L101:
/* CMC   101 IF(IECHO.EQ.0)WRITE(12,888) */
/* CMC   888 FORMAT(1X,'OUTPUT WRITER DATA:') */
    if (el1_1.iecho == 0) 
      fprintf(fp12, "OUTPUT WRITER DATA:\n");

/* CMC       READ(5,498)NTITL */
    fgets(buf, sizeof(buf), fp5);
    ntitl = atoi( substring(buf,5,5));
/* CMC       IF(IECHO.EQ.0)WRITE(12,498)NTITL */
    fprintf(fp12, "     %5d\n", ntitl);
/* CMC   498 FORMAT(5X,I5) */

/*<       IF(NTITL.EQ.0)GO TO 99 >*/
    if (ntitl == 0) {
	goto L99;
    }

/* ***** MAJOR LOOP ON TITLES. */

/*<       DO 499 I=1,NTITL >*/
    i__1 = ntitl;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* CMC       READ(5,500)NENTR(I),NCODE(I),(LTITL(I,J),J=1,13) */
      fgets(buf, sizeof(buf), fp5);
      nentr[i__ - 1] = atoi( substring(buf,1,4));
      ncode[i__ - 1] = atoi( substring(buf,5,5));
      pos = 15;
      for(j=1;j<=13;j++){
	ltitl_ref(i__, j) = atoi( substring(buf,pos,4));
	pos+=4;
      }

/* CMC       IF(IECHO.EQ.0)WRITE(12,500)NENTR(I),NCODE(I),(LTITL(I,J),J=1,13) */	
      if (el1_1.iecho == 0) {

	fprintf(fp12, " %4d%5d     ", nentr[i__ - 1], ncode[i__ - 1] );
	for(j=1;j<=13;j++)
	  fprintf(fp12, "%4d", ltitl_ref(i__, j));
	fprintf(fp12, "\n");
      }
/* CMC   500 FORMAT(1X,I4,I5,5X,13A4) */

/*<       IF(NCODE(I).LE.0)NCODE(I)=1 >*/
	if (ncode[i__ - 1] <= 0) {
	    ncode[i__ - 1] = 1;
	}
/*<       NNE=NENTR(I) >*/
	nne = nentr[i__ - 1];
/*<       KV=0 >*/
	kv = 0;

/* ***** LOOP ON ENTRIES WITHIN A TITLE I. */

/*<       DO 501 K=1,NNE >*/
	i__2 = nne;
	for (k = 1; k <= i__2; ++k) {
/*<       KV=KV+1 >*/
	    ++kv;
/* CMC       READ(5,513)(LABLE(I,K,J),J=1,13) */
	    fgets(buf, sizeof(buf), fp5);
	    pos = 5;
	    for (j = 1; j <= 13; ++j) {
	      lable_ref(i__, k, j) = atoi( substring(buf,pos,4));
	      pos += 4;
	    }
/* CMC       IF(IECHO.EQ.0)WRITE(12,513)(LABLE(I,K,J),J=1,13) */
	    if (el1_1.iecho == 0) {
	      fprintf(fp12, "     ");
	      for(j=1;j<=13;j++)
		fprintf(fp12, "%4d", lable_ref(i__, k, j));
	      fprintf(fp12, "\n");
	      
	    }
/* CMC   513 FORMAT(5X,13A4) */

/* CMC       READ(5,502)(LLINK(I,KV,J),J=1,15) */
	    fgets(buf, sizeof(buf), fp5);
	    pos = 5;
	    for (j = 1; j <= 15; ++j) {
	      llink_ref(i__, kv, j) = atoi( substring(buf,pos,5));
	      pos += 5;
	    }
/* CMC       IF(IECHO.EQ.0)WRITE(12,502)(LLINK(I,KV,J),J=1,15) */
	    if (el1_1.iecho == 0) {
	      fprintf(fp12, "     ");
	      for(j=1;j<=15;j++)
		fprintf(fp12, "%5d", llink_ref(i__, kv, j));
	      fprintf(fp12, "\n");
	      
	    }

/*<       IF(NCODE(I).NE.4)GO TO 501 >*/
	    if (ncode[i__ - 1] != 4) {
		goto L501;
	    }
/*<       KV=KV+1 >*/
	    ++kv;
/* CMC       READ(5,502)(LLINK(I,KV,J),J=1,15) */
	    fgets(buf, sizeof(buf), fp5);
	    pos = 5;
	    for (j = 1; j <= 15; ++j) {
	      llink_ref(i__, kv, j) = atoi( substring(buf,pos,5));
	      pos += 5;
	    }
/* CMC       IF(IECHO.EQ.0)WRITE(12,502)(LLINK(I,KV,J),J=1,15) */
	    if (el1_1.iecho == 0) {
	      fprintf(fp12, "     ");
	      for(j=1;j<=15;j++)
		fprintf(fp12, "%5d", llink_ref(i__, kv, j));
	      fprintf(fp12, "\n");
	      
	    }
/* CMC   502 FORMAT(5X,15I5) */

/*<   501 CONTINUE >*/
L501:
	    ;
	}
/*<   499 CONTINUE >*/
/* L499: */
    }

/* CMC       READ(5,502) */
	    fgets(buf, sizeof(buf), fp5);
/*<       GO TO 99 >*/
    goto L99;

/* ***** THIS SECTION FOR WRITING RESULTS. */

/*<   102 IOUW=0 >*/
L102:
    iouw = 0;
/*<       DO 1202  N=1,IOUTX >*/
    i__1 = pri_1.ioutx;
    for (n = 1; n <= i__1; ++n) {
/*<       IF (IDMP(N).EQ.0) GO TO 1202 >*/
	if (var_1.idmp[n - 1] == 0) {
	    goto L1202;
	}
/*<       IOUW=IOUW+1 >*/
	++iouw;
/*<       LABZ(IOUW)=LABY(N) >*/
	labz[iouw - 1] = outwr_1.laby[n - 1];
/*<  1202 CONTINUE >*/
L1202:
	;
    }
/*<       IF(IOUW.GT.0) GO TO 1203 >*/
    if (iouw > 0) {
	goto L1203;
    }
/* CMC       WRITE (11,1204) */
/* CMC  1204 FORMAT(1H1,1X, */
/* CMC      1' OUTPUT WRITER NOT CREATED: NO YEARS SPECIFIED IN IDMP VECTOR')  MJ060886 */
fprintf(fp11, "  OUTPUT WRITER NOT CREATED: NO YEARS SPECIFIED IN IDMP VECTOR\n");

/*<       GO TO 99 >*/
    goto L99;
/*<  1203 CONTINUE >*/
L1203:
/* CMC  1203 WRITE(11,503)(LABZ(J),J=1,IOUW) */
/* CMC   503 FORMAT(1H1,1X,'OUTPUT WRITER SUMMARY',/,1X,100(1H-), */
/* CMC      1 /,1X,100(1H-),///,6X,'YEAR=  YR AGG',5X,10I8,/,24X, */
/* CMC      2 10I8,/,24X,10I8,/,24X,10I8,/,24X,10I8,/,24X,10I8,/,24X,10I8,/ */
/* CMC      3 ,24X,5I8,/) */

    fprintf(fp11, "1 OUTPUT WRITER SUMMARY");
    fprintf(fp11, "\n ----------------------------------------------------------------------------------------------------");
    fprintf(fp11, "\n ----------------------------------------------------------------------------------------------------");
    fprintf(fp11, "\n\n\n      YEAR=  YR AGG     ");
    for(j=1; j<=iouw; j++){
      if( ( (j-1)%10==0)&&(j>1))
	fprintf(fp11, "\n                        ");
      fprintf(fp11, "%8d", labz[j - 1]);
    }
    fprintf(fp11, "\n");

/*  write graphics file b070.dat containing output writer information -  bph7-90 */
/* CMC       OPEN (2,FILE = 'b070.dat', STATUS = 'UNKNOWN')                    bph7-90 */
/* CMC       WRITE(2,1502)(IOUW)                                               bph7-90 */
/* CMC  1502 FORMAT(I8)                                                        bph7-90 */
/* CMC       WRITE(2,1503)(LABZ(J),J=1,IOUW)                                   bph7-90 */
/* CMC  1503 FORMAT(10I8,/,10I8,/,10I8,/,10I8,/,10I8,/,10I8,/,10I8,/,5I8)      bph7-90 */
    if((fp2=fopen("./b070.dat", "w"))==NULL){
      fprintf(fp21, "Error: Couldnt open b070.dat\n");
      exit(0);
    }
    fprintf(fp2, "%8d\n", iouw);
    for(j=1; j<=iouw; j++){
      if( ( (j-1)%10==0)&&(j>1))
	fprintf(fp2, "\n");
      fprintf(fp2, "%8d", labz[j - 1]);
    }
    fprintf(fp2, "\n");
    

/* ***** LOOP ON TITLES. */

/* CMC       WRITE(2,1502)(NTITL)                                              bph7-90 */
    fprintf(fp2, "%8d\n", ntitl);

/*<       DO 504 I=1,NTITL >*/
    i__1 = ntitl;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* CMC       WRITE(11,609)(LTITL(I,J),J=1,13) */
    fprintf(fp11, "\n\n ");
    for(j=1; j<=13; j++)
      fprintf(fp11, "%4d", ltitl_ref(i__, j));
    fprintf(fp11, "\n ----------------------------------------------------------------------------------------------------\n");

/* CMC       WRITE(2,1609)(LTITL(I,J),J=1,13)  
    for(j=1; j<=13; j++)
      fprintf(fp2, "%4d", ltitl_ref(i__, j));
    fprintf(fp2, "\n");
                                bph7-90 */
/* CMC   609 FORMAT(//,1X,13A4,/,1X,100(1H-)) */
/* CMC  1609 FORMAT(13A4)                                                      bph7-90 */

/*<       NNE=NENTR(I) >*/
	nne = nentr[i__ - 1];

/*<       KV=0 >*/
	kv = 0;

/* ***** LOOP ON ENTRIES WITHIN A TITLE I. */

/* CMC       WRITE(2,1502)(NNE)                                                bph7-90 */
      fprintf(fp2, "%8d", nne);

/*<       DO 505 K=1,NNE >*/
	i__2 = nne;
	for (k = 1; k <= i__2; ++k) {
/*<       KV=KV+1 >*/
	    ++kv;
/*<       KCODE=0 >*/
	    kcode = 0;

/* ***** LOOP ON TIME PERIODS. */

/*<   525 DO 507 NT=1,IOUTX >*/
L525:
	    i__3 = pri_1.ioutx;
	    for (nt = 1; nt <= i__3; ++nt) {
/*<       QZ(NT)=0. >*/
		qz[nt - 1] = 0.f;
/*<       PQZ(NT)=0. >*/
		pqz[nt - 1] = 0.f;
/*<       PQQZ(NT)=0. >*/
		pqqz[nt - 1] = 0.f;

/* ***** LOOP OVER ALL LINKS FOR ENTRY K AT TIME NT. */

/*<       DO 506 KOUNT=1,15 >*/
		for (kount = 1; kount <= 15; ++kount) {
/*<       LCODE=LLINK(I,KV,KOUNT) >*/
		    lcode = llink_ref(i__, kv, kount);
/*<       IF(LCODE.EQ.0)GO TO 506 >*/
		    if (lcode == 0) {
			goto L506;
		    }

/* ***** ADD Q TO QSUM AND ADD P*Q TO P*Q SUM. */

/*<       QZ(NT)=QZ(NT)+ZEN(1,LCODE,NT) >*/
		    qz[nt - 1] += zen_ref(1, lcode, nt);
/*<       PQZ(NT)=PQZ(NT)+ZEN(1,LCODE,NT) * ZEN(2,LCODE,NT) /1.E+03 >*/
		    pqz[nt - 1] += zen_ref(1, lcode, nt) * zen_ref(2, lcode, 
			    nt) / 1e3f;
/*<   506 CONTINUE >*/
L506:
		    ;
		}
/* ***** END LOOP OVER LINKS. */


/*<       IQZ(NT)=QZ(NT) >*/
		iqz[nt - 1] = qz[nt - 1];

/* ***** COMPUTE WTD AVE PRICE. */

/*<       IF(QZ(NT).GT.1.E-03)GO TO 55 >*/
		if (qz[nt - 1] > .001f) {
		    goto L55;
		}
/*<       PQQZ(NT)=0.0 >*/
		pqqz[nt - 1] = 0.f;
/*<       GO TO 507 >*/
		goto L507;

/*<    55 PQQZ(NT)=PQZ(NT) * 1.E+03/ QZ(NT) >*/
L55:
		pqqz[nt - 1] = pqz[nt - 1] * 1e3f / qz[nt - 1];
/*<   507 CONTINUE >*/
L507:
		;
	    }
/* ***** END LOOP OVER TIME PERIODS. */

/*<       IF(NCODE(I).NE.4)GO TO 608 >*/
	    if (ncode[i__ - 1] != 4) {
		goto L608;
	    }

/* ***** LOGIC FOR NET REVENUE CALCULATION. */

/*<       IF(KCODE.EQ.1)GO TO 72 >*/
	    if (kcode == 1) {
		goto L72;
	    }

/*<       KCODE=1 >*/
	    kcode = 1;
/*<       KV=KV+1 >*/
	    ++kv;
/*<       DO 88 NT=1,IOUTX >*/
	    i__3 = pri_1.ioutx;
	    for (nt = 1; nt <= i__3; ++nt) {
/*<       REV(NT)=PQZ(NT) >*/
		rev[nt - 1] = pqz[nt - 1];
/*<    88 CONTINUE >*/
/* L88: */
	    }
/*<       GO TO 525 >*/
	    goto L525;

/*<    72 KCODE=0 >*/
L72:
	    kcode = 0;
/*<       DO 89 NT=1,IOUTX >*/
	    i__3 = pri_1.ioutx;
	    for (nt = 1; nt <= i__3; ++nt) {
/*<       REV(NT)=REV(NT)-PQZ(NT) >*/
		rev[nt - 1] -= pqz[nt - 1];
/*<    89 CONTINUE >*/
/* L89: */
	    }

/* ***** CONSTRUCT ANNUAL SERIES.  INSERT MISSING YEARS. */

/*<   608 QS(1)=QZ(1) >*/
L608:
	    qs[0] = qz[0];
/*<       PQS(1)=PQZ(1) >*/
	    pqs[0] = pqz[0];
/*<       PQQS(1)=PQQZ(1) >*/
	    pqqs[0] = pqqz[0];
/*<       REVS(1)=REV(1) >*/
	    revs[0] = rev[0];
/*<       NTV=1 >*/
	    ntv = 1;

/*<       IF(IOUTX.EQ.1)GO TO 309 >*/
	    if (pri_1.ioutx == 1) {
		goto L309;
	    }
/*<       DO 207 NT=2,IOUTX >*/
	    i__3 = pri_1.ioutx;
	    for (nt = 2; nt <= i__3; ++nt) {
/*<       ISPAN=LABY(NT)-LABY(NT-1) >*/
		ispan = outwr_1.laby[nt - 1] - outwr_1.laby[nt - 2];
/*<       RSPAN=ISPAN >*/
		rspan = (real) ispan;
/*<       IF(ISPAN.GT.1)GO TO 902 >*/
		if (ispan > 1) {
		    goto L902;
		}

/*<       NTV=NTV+1 >*/
		++ntv;
/*<       QS(NTV)=QZ(NT) >*/
		qs[ntv - 1] = qz[nt - 1];
/*<       PQS(NTV)=PQZ(NT) >*/
		pqs[ntv - 1] = pqz[nt - 1];
/*<       PQQS(NTV)=PQQZ(NT) >*/
		pqqs[ntv - 1] = pqqz[nt - 1];
/*<       REVS(NTV)=REV(NT) >*/
		revs[ntv - 1] = rev[nt - 1];
/*<       GO TO 207 >*/
		goto L207;

/*<   902 DQ=(QZ(NT)-QZ(NT-1))/RSPAN >*/
L902:
		dq = (qz[nt - 1] - qz[nt - 2]) / rspan;
/*<       DPQ=(PQZ(NT)-PQZ(NT-1))/RSPAN >*/
		dpq = (pqz[nt - 1] - pqz[nt - 2]) / rspan;
/*<       DPQQ=(PQQZ(NT)-PQQZ(NT-1))/RSPAN >*/
		dpqq = (pqqz[nt - 1] - pqqz[nt - 2]) / rspan;
/*<       DREV=(REV(NT)-REV(NT-1))/RSPAN >*/
		drev = (rev[nt - 1] - rev[nt - 2]) / rspan;

/*<       DO 209 J=1,ISPAN >*/
		i__4 = ispan;
		for (j = 1; j <= i__4; ++j) {
/*<       RJ=J >*/
		    rj = (real) j;
/*<       NTV=NTV+1 >*/
		    ++ntv;

/*<       QS(NTV)=QZ(NT-1)+DQ*RJ >*/
		    qs[ntv - 1] = qz[nt - 2] + dq * rj;
/*<       PQS(NTV)=PQZ(NT-1)+DPQ*RJ >*/
		    pqs[ntv - 1] = pqz[nt - 2] + dpq * rj;
/*<       PQQS(NTV)=PQQZ(NT-1)+DPQQ*RJ >*/
		    pqqs[ntv - 1] = pqqz[nt - 2] + dpqq * rj;
/*<       REVS(NTV)=REV(NT-1)+DREV*RJ >*/
		    revs[ntv - 1] = rev[nt - 2] + drev * rj;
/*<   209 CONTINUE >*/
/* L209: */
		}
/*<   207 CONTINUE >*/
L207:
		;
	    }

/* ***** AGGREGATE VALUES ACROSS YEARS. */

/*<   309 SDR=0. >*/
L309:
	    sdr = 0.f;
/*<       QSUM=0. >*/
	    qsum = 0.f;
/*<       PAVE=0. >*/
	    pave = 0.f;
/*<       PQDIS=0. >*/
	    pqdis = 0.f;
/*<       REVDS=0. >*/
	    revds = 0.f;

/*<       DO 208 N=1,NTV >*/
	    i__3 = ntv;
	    for (n = 1; n <= i__3; ++n) {
/*<       QSUM=QSUM+QS(N) >*/
		qsum += qs[n - 1];
/*<       PQDIS=PQDIS+PQS(N)/(1.+SDR) >*/
		pqdis += pqs[n - 1] / (sdr + 1.f);
/*<       PAVE=PAVE+PQQS(N) >*/
		pave += pqqs[n - 1];
/*<       REVDS=REVDS+REVS(N)/(1.+SDR) >*/
		revds += revs[n - 1] / (sdr + 1.f);
/*<   208 CONTINUE >*/
/* L208: */
	    }

/*<       YRS=LABY(IOUTX)-LABY(1)+1 >*/
	    yrs = (real) (outwr_1.laby[pri_1.ioutx - 1] - outwr_1.laby[0] + 1)
		    ;
/*<       PAVE=PAVE/YRS >*/
	    pave /= yrs;
/*<       ISUM=QSUM >*/
	    isum = qsum;

/*<       NG=NCODE(I) >*/
	    ng = ncode[i__ - 1];
/*<       JOUTX=0 >*/
	    joutx = 0;
/*<       DO 1201  N=1,IOUTX >*/
	    i__3 = pri_1.ioutx;
	    for (n = 1; n <= i__3; ++n) {
/*<       IF (IDMP(N).EQ.0) GO TO 1201 >*/
		if (var_1.idmp[n - 1] == 0) {
		    goto L1201;
		}
/*<       JOUTX=JOUTX+1 >*/
		++joutx;
/*<       IQZ(JOUTX) = IQZ(N) >*/
		iqz[joutx - 1] = iqz[n - 1];
/*<       PQZ(JOUTX) = PQZ(N) >*/
		pqz[joutx - 1] = pqz[n - 1];
/*<       PQQZ(JOUTX)= PQQZ(N) >*/
		pqqz[joutx - 1] = pqqz[n - 1];
/*<       REV(JOUTX) = REV(N) >*/
		rev[joutx - 1] = rev[n - 1];
/*<  1201 CONTINUE >*/
L1201:
		;
	    }
/*<       GO TO (100,200,300,400),NG >*/
	    switch (ng) {
		case 1:  goto L100;
		case 2:  goto L200;
		case 3:  goto L300;
		case 4:  goto L400;
	    }

/*<  100  CONTINUE >*/
L100:
/* CMC   100 WRITE(11,508)(LABLE(I,K,J),J=1,13),ISUM,(IQZ(NT),NT=1,JOUTX) */
/* CMC   508 FORMAT(/,1X,'QUAN.:  ',13A4,/,8X,I10,5X,10I8,/,23X,10I8,/,23X,    MJ060686 */
/* CMC      110I8,/,23X,10I8,/,23X,10I8,/,23X,10I8,/,23X,10I8,/,23X,5I8) */
	    fprintf(fp11, "\n QUAN.:  ");
	    for(j=1;j<=13;j++)
	      fprintf(fp11, "%4d", lable_ref(i__, k, j) );
	    fprintf(fp11, "\n        %10d     ", isum);
	    for(nt=1;nt<=joutx;nt++){
	      if( ( (nt-1)%10==0)&& (nt>1))
		fprintf(fp11, "\n                       ");
	      fprintf(fp11, "%8d", iqz[nt - 1]);
	    }
	    fprintf(fp11, "\n");

/* CMC       WRITE(2,1508)(LABLE(I,K,J),J=1,13),ISUM,(IQZ(NT),NT=1,JOUTX)      bph7-90 */
/* CMC  1508 FORMAT('QUAN.:  ',13A4,/,8X,I10,5X,10I8,/,23X,10I8,/,23X,10I8 */
/* CMC      1 ,/,23X,10I8,/,23X,10I8,/,23X,10I8,/,23X,10I8,/,23X,5I8)          bph7-90 */
	    fprintf(fp2, "QUAN.:  ");
	    for(j=1;j<=13;j++)
	      fprintf(fp2, "%4d", lable_ref(i__, k, j) );
	    fprintf(fp2, "\n        %10d     ", isum);
	    for(nt=1;nt<=joutx;nt++){
	      if( ( (nt-1)%10==0)&& (nt>1))
		fprintf(fp2, "\n                       ");
	      fprintf(fp2, "%8d", iqz[nt - 1]);
	    }
	    fprintf(fp2, "\n");


/*<       GO TO 505 >*/
	    goto L505;

/*<  200  CONTINUE >*/
L200:
/* CMC   200 WRITE(11,509)(LABLE(I,K,J),J=1,13),PQDIS,(PQZ(NT),NT=1,JOUTX)     MJ060686 */
/* CMC   509 FORMAT(/,1X,'PRICE * QUAN.:  ',13A4,/,8X,F10.1,5X,10F8.1,/,23X,   MJ060686 */
/* CMC      1 10F8.1,/,23X,10F8.1,/,23X,10F8.1,/,23X,10F8.1,/,23X,10F8.1 */
/* CMC      2 ,/,23X,10F8.1,/,23X,5F8.1) */
	    fprintf(fp11, "\n PRICE * QUAN.:  ");
	    for(j=1;j<=13;j++)
	      fprintf(fp11, "%4d", lable_ref(i__, k, j) );
	    fprintf(fp11, "\n        %10.1f     ", pqdis);
	    for(nt=1;nt<=joutx;nt++){
	      if( ( (nt-1)%10==0)&& (nt>1))
		fprintf(fp11, "\n                       ");
	      fprintf(fp11, "%8.1f", pqz[nt - 1]);
	    }
	    fprintf(fp11, "\n");

/* CMC       WRITE(2,1509)(LABLE(I,K,J),J=1,13),PQDIS,(PQZ(NT),NT=1,JOUTX)     bph7-90 */
/* CMC  1509 FORMAT('PRICE * QUAN.:  ',13A4,/,8X,F10.1,5X,10F8.1,/,23X,        bph7-90 */
/* CMC      1 10F8.1,/,23X,10F8.1,/,23X,10F8.1,/,23X,10F8.1,/,23X,10F8.1 */
/* CMC      2 ,/,23X,10F8.1,/,23X,5F8.1) */
	    fprintf(fp2, "PRICE * QUAN.:  ");
	    for(j=1;j<=13;j++)
	      fprintf(fp2, "%4d", lable_ref(i__, k, j) );
	    fprintf(fp2, "\n        %10.1f     ", pqdis);
	    for(nt=1;nt<=joutx;nt++){
	      if( ( (nt-1)%10==0)&& (nt>1))
		fprintf(fp2, "\n                       ");
	      fprintf(fp2, "%8.1f", pqz[nt - 1]);
	    }
	    fprintf(fp2, "\n");

/*<       GO TO 505 >*/
	    goto L505;

/*<  300  CONTINUE >*/
L300:
/* CMC   300 WRITE(11,510)(LABLE(I,K,J),J=1,13),PAVE,(PQQZ(NT),NT=1,JOUTX) */
/* CMC   510 FORMAT(/,1X,'WTD. AVE. PRICE:  ',13A4,/,8X,F10.2,5X,10F8.2,/23X,  MJ060686 */
/* CMC      1 10F8.2,/,23X,10F8.2,/,23X,10F8.2,/,23X,10F8.2,/,23X,10F8.2 */
/* CMC      2 ,/,23X,10F8.2,/,23X,5F8.2) */
	    fprintf(fp11, "\n WTD. AVE. PRICE:  ");
	    for(j=1;j<=13;j++)
	      fprintf(fp11, "%4d", lable_ref(i__, k, j) );
	    fprintf(fp11, "\n        %10.2f     ", pave);
	    for(nt=1;nt<=joutx;nt++){
	      if( ( (nt-1)%10==0)&& (nt>1))
		fprintf(fp11, "\n                       ");
	      fprintf(fp11, "%8.2f", pqqz[nt - 1]);
	    }
	    fprintf(fp11, "\n");

/* CMC       WRITE(2,1510)(LABLE(I,K,J),J=1,13),PAVE,(PQQZ(NT),NT=1,JOUTX)     bph7-90 */
/* CMC  1510 FORMAT('WTD. AVE. PRICE:  ',13A4,/,8X,F10.2,5X,10F8.2,/23X,       bph7-90 */
/* CMC      1 10F8.2,/,23X,10F8.2,/,23X,10F8.2,/,23X,10F8.2,/,23X,10F8.2 */
/* CMC      2 ,/,23X,10F8.2,/,23X,5F8.2) */
	    fprintf(fp2, "WTD. AVE. PRICE:  ");
	    for(j=1;j<=13;j++)
	      fprintf(fp2, "%4d", lable_ref(i__, k, j) );
	    fprintf(fp2, "\n        %10.2f     ", pave);
	    for(nt=1;nt<=joutx;nt++){
	      if( ( (nt-1)%10==0)&& (nt>1))
		fprintf(fp2, "\n                       ");
	      fprintf(fp2, "%8.2f", pqqz[nt - 1]);
	    }
	    fprintf(fp2, "\n");

/*<       GO TO 505 >*/
	    goto L505;

/*<  400  CONTINUE >*/
L400:
/* CMC   400 WRITE(11,511)(LABLE(I,K,J),J=1,13),REVDS,(REV(NT),NT=1,JOUTX) */
/* CMC   511 FORMAT(/,1X,'NET REVENUE:  ',13A4,/,8X,F10.0,5X,10F8.0,/,23X,     MJ060686 */
/* CMC      1 10F8.0,/,23X,10F8.0,/,23X,10F8.0,/,23X,10F8.0,/,23X,10F8.0 */
/* CMC      2 ,/,23X,10F8.0,/,23X,5F8.0) */
	    fprintf(fp11, "\n NET REVENUE:  ");
	    for(j=1;j<=13;j++)
	      fprintf(fp11, "%4d", lable_ref(i__, k, j) );
	    fprintf(fp11, "\n        %10.2f     ", revds);
	    for(nt=1;nt<=joutx;nt++){
	      if( ( (nt-1)%10==0)&& (nt>1))
		fprintf(fp11, "\n                       ");
	      fprintf(fp11, "%8.2f", rev[nt - 1]);
	    }
	    fprintf(fp11, "\n");

/* CMC       WRITE(2,1511)(LABLE(I,K,J),J=1,13),REVDS,(REV(NT),NT=1,JOUTX)     bph7-90 */
/* CMC  1511 FORMAT('NET REVENUE:  ',13A4,/,8X,F10.0,5X,10F8.0,/,23X,          bph7-90 */
/* CMC      1 10F8.0,/,23X,10F8.0,/,23X,10F8.0,/,23X,10F8.0,/,23X,10F8.0 */
/* CMC      2 ,/,23X,10F8.0,/,23X,5F8.0) */
	    fprintf(fp2, "NET REVENUE:  ");
	    for(j=1;j<=13;j++)
	      fprintf(fp2, "%4d", lable_ref(i__, k, j) );
	    fprintf(fp2, "\n        %10.2f     ", revds);
	    for(nt=1;nt<=joutx;nt++){
	      if( ( (nt-1)%10==0)&& (nt>1))
		fprintf(fp2, "\n                       ");
	      fprintf(fp2, "%8.2f", rev[nt - 1]);
	    }
	    fprintf(fp2, "\n");

/*<   505 CONTINUE >*/
L505:
	    ;
	}

/*<   504 CONTINUE >*/
/* L504: */
    }
/* CMC close(2) */
fclose(fp2);

/*<    99 RETURN >*/
L99:
    return 0;
/*<       END >*/
} /* outw_ */

#undef zen_ref
#undef ltitl_ref
#undef llink_ref
#undef lable_ref



/* ***************************************************************** OTPUT */

/*<       SUBROUTINE OTPUT >*/
/* Subroutine */ int otput_(void)
{
extern FILE *fp6;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];

    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer l;
    static real pq;

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

/*<       IF(NTIME.GT.1)GO TO 200 >*/
    if (var_1.ntime > 1) {
	goto L200;
    }
/* CMC       WRITE(6,101)IYRB */
/* CMC   101 FORMAT(1H1,2X,'NETWORK LINK SUMMARY FOR BASE YEAR ',I6,/) */
fprintf(fp6, "  NETWORK LINK SUMMARY FOR BASE YEAR %6d\n\n",var_1.iyrb);
/*<       GO TO 505 >*/
    goto L505;

/*<   200 IF(IWR1.LE.1)RETURN >*/
L200:
    if (var_1.iwr1 <= 1) {
	return 0;
    }
/* CMC       WRITE(6,100)ITIME */
/* CMC   100 FORMAT(1H1,2X,'NETWORK LINK SUMMARY FOR YEAR ',I6,/) */
fprintf(fp6, "  NETWORK LINK SUMMARY FOR YEAR %6d\n\n",var_1.itime);

/*<   505 CONTINUE >*/
L505:
/* CMC       WRITE(6,202)(PU(J),J=1,3),(QU(J),J=1,3) */
/* CMC   202 FORMAT(/,3X,'LINK',14X,'PRICE',11X,'QUANTITY', */
/* CMC      1 10X,16X,'P*Q',/,14X,3A4,7X,3A4,/) */
fprintf(fp6, "\n   LINK              PRICE           QUANTITY                          P*Q\n");
fprintf(fp6, "              %4d%4d%4d       %4d%4d%4d\n\n", 
var_1.pu[0],var_1.pu[1],var_1.pu[2],
var_1.qu[0],var_1.qu[1],var_1.qu[2]);


/* ***** OUTPUT PRICE AND QUANTITY ON ALL LINKS. */

/*<       DO 102 L=1,LNKMX >*/
    i__1 = var_1.lnkmx;
    for (l = 1; l <= i__1; ++l) {
/*<       IF(LUSE(L).EQ.0)GO TO 102 >*/
	if (net_1.luse[l - 1] == 0) {
	    goto L102;
	}
/*<       PQ=P(L)*Q(L) >*/
	pq = net_1.p[l - 1] * net_1.q[l - 1];
/* CMC       WRITE(6,103)L,P(L),Q(L),PQ */
/* CMC   103 FORMAT(1X,I6,5X,F14.2,5X,F14.3,15X,F14.3) */
fprintf(fp6, " %6d     %14.2f     %14.3f               %13.3f\n",
	LinkNodeNames[13][l], net_1.p[l - 1]/units_1.unitcnvt[3],net_1.q[l - 1]/units_1.unitcnvt[8],pq/units_1.unitcnvt[3]/units_1.unitcnvt[8]);


/*<   102 CONTINUE >*/
L102:
	;
    }
/* CMC       WRITE(6,110) */
/* CMC   110 FORMAT(//) */
fprintf(fp6, "\n\n");

/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* otput_ */


/* ******************************************************************** PP */

/* CMC 990427 ADDED ,POQUAN(200) TO COMMON ALL */

/*<       SUBROUTINE PP(IPASS,IPR,KSPEC) >*/
/* Subroutine */ int pp_(integer *ipass, integer *ipr, integer *kspec)
{
extern FILE *fp11, *fp6;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];

int j;

    static integer link, l, ii, iu;
    static real pq;
    static integer ipm;

/* #define labp_ref(a_1,a_2) pri_1.labp[(a_2)*100 + a_1 - 101] */
#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]

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

/*<       IU=IOUPP(IPR) >*/
    iu = pri_1.ioupp[*ipr - 1];
/*<       II=IINPP(IPR) >*/
    ii = pri_1.iinpp[*ipr - 1];
/*<       L=IU >*/
    l = iu;

/*<       IF(IPASS.LT.6)GO TO 4511 >*/
    if (*ipass < 6) {
	goto L4511;
    }
/*<       IPM=IPASS-5 >*/
    ipm = *ipass - 5;
/* CMC       WRITE(11,4903)(LABP(IPR,J),J=1,4) */
/* CMC  4903 FORMAT(2X,5A4) */
      fprintf(fp11, "  %s\n", pri_1.cmc_labp[*ipr]);



/* CMC       IF(IPASS.EQ.6)WRITE(11,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
/* CMC  4411 FORMAT(1X,I4,1X,'Q',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
/* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
/* CMC      2  ,/,10X,5F11.1) */
    if (*ipass == 6) {

      fprintf(fp11, " %4d Q   ",l);
      for (j = 1; j <= pri_1.ioutx; ++j) {
	if(( ((j-1)%10)==0)&&(j>1))
	  fprintf(fp11, "\n          ");
	fprintf(fp11, "%11.1f", zen_ref(1, l, j) );
      }
      fprintf(fp11, "\n");
    }

/* CMC       IF(IPASS.EQ.7)WRITE(11,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
/* CMC  4412 FORMAT(1X,I4,1X,'P',3X,10F9.2,/,10X,10F9.2,/,10X,10F9.2 */
/* CMC      1   ,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F2.2 */
/* CMC      2   ,/,10X,5F9.2) */
    if (*ipass == 7) {

      fprintf(fp11, " %4d P   ",l);
      for (j = 1; j <= pri_1.ioutx; ++j) {
	if(( ((j-1)%10)==0)&&(j>1))
	  fprintf(fp11, "\n          ");
	fprintf(fp11, "%9.2f", zen_ref(2, l, j) );
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
/*<       IF(IPASS.EQ.2)GO TO 100 >*/
    if (*ipass == 2) {
	goto L100;
    }

/*<       LINK=LINKP(IPR) >*/
    link = pri_1.linkp[*ipr - 1];
/*<       IF(LINK.EQ.0)LINK=II >*/
    if (link == 0) {
	link = ii;
    }

/*<       P(IU)=P(LINK)*ALPHA(IPR)+DELTA(IPR) >*/
    net_1.p[iu - 1] = net_1.p[link - 1] * pri_1.alpha[*ipr - 1] + pri_1.delta[
	    *ipr - 1];
/*<       IF(P(IU).LT.PMIN(IPR))P(IU)=PMIN(IPR) >*/
    if (net_1.p[iu - 1] < pri_1.pmin[*ipr - 1]) {
	net_1.p[iu - 1] = pri_1.pmin[*ipr - 1];
    }
/*<       IF(P(IU).GT.PMAX(IPR))P(IU)=PMAX(IPR) >*/
    if (net_1.p[iu - 1] > pri_1.pmax[*ipr - 1]) {
	net_1.p[iu - 1] = pri_1.pmax[*ipr - 1];
    }

/*<  2694 IF(NTIME.EQ.1)Q(IU)=Q(II) >*/
/* L2694: */
    if (var_1.ntime == 1) {
	net_1.q[iu - 1] = net_1.q[ii - 1];
    }
/* CMC       IF(IWR1.GE.2)WRITE(6,805)IPR,IU,NTIME,P(IU) */
/* CMC   805 FORMAT(2X,'P',5X,'PRPOL',I4,5X,'LINK',I4,5X, */
/* CMC      1'TIME',I3,4X,1H$,F10.4) */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  P     PP  %s (%s)     LINK  %s     YEAR%6d    $%10.4f\n",
	      LinkNodeNames[3][(*ipr)],LinkNodeSector[3][(*ipr)],LinkNodeNames[13][iu],var_1.itime,net_1.p[iu - 1]/units_1.unitcnvt[3]);
    /*<       RETURN >*/
    return 0;
    
    /* ***** DOWNPASS LOGIC. */
    
    /*<   100 CONTINUE >*/
  L100:
    /*<       Q(II)=Q(IU) >*/
    net_1.q[ii - 1] = net_1.q[iu - 1];
    /* CMC       IF(IWR1.GE.2)WRITE(6,602)IPR,II,NTIME,Q(II) */
    /* CMC   602 FORMAT(2X,'Q',5X,'PRPOL',I4,5X,'LINK',I4,5X,'TIME', */
    /* CMC      1I3,4X,F11.3) */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  Q     PP  %s (%s)     LINK  %s     YEAR%6d    %11.3\n",
	      LinkNodeNames[3][(*ipr)],LinkNodeSector[3][(*ipr)],LinkNodeNames[13][ii],var_1.itime,net_1.q[iu - 1]/units_1.unitcnvt[8]);


/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* pp_ */

#undef labp_ref
#undef zen_ref



/* ******************************************************************** PR */

/* CMC ADDED ,POQUAN(200) TO COMMON ALL */
/*<       SUBROUTINE PR(IPASS,IPR,KSPEC) >*/
/* Subroutine */ int pr_(integer *ipass, integer *ipr, integer *kspec)
{
extern int emisflag;
extern FILE *fp11, *fp6, *fp25;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];
real emisTax;
int i,j;
    static integer ilnk, iolk;
    static real pout;
    static integer l;
    static real pq;
    static integer ipm;

/* #define labc_ref(a_1,a_2) pro_1.labc[(a_2)*300 + a_1 - 301] */
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

/*<       ILNK=IINPR(IPR) >*/
    ilnk = pro_1.iinpr[*ipr - 1];
/*<       IOLK=IOUPR(IPR) >*/
    iolk = pro_1.ioupr[*ipr - 1];
/*<       L=IOLK >*/
    l = iolk;

/*<       IF(IPASS.LT.6)GO TO 4511 >*/
    if (*ipass < 6) {
	goto L4511;
    }
/*<       IPM=IPASS-5 >*/
    ipm = *ipass - 5;
/* CMC       WRITE(11,4903)(LABC(IPR,J),J=1,4) */
/* CMC  4903 FORMAT(2X,5A4) */
      fprintf(fp11, "  %s\n", pro_1.cmc_labc[*ipr] );


/* CMC       IF(IPASS.EQ.6)WRITE(11,4411)L,(ZEN(1,L,J),J=1,IOUTX) */
/* CMC  4411 FORMAT(1X,I4,1X,'Q',3X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
/* CMC      1  ,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1,/,10X,10F11.1 */
/* CMC      2  ,/,10X,5F11.1) */
    if (*ipass == 6) {
      fprintf(fp11, " %4d Q   ",l);
      for(j=1; j<= pri_1.ioutx;j++){
	if((((j-1)%10)==0) && (j>1))
	  fprintf(fp11, "\n          ");
	fprintf(fp11, "%11.1f", zen_ref(1, l, j) );
      }
      fprintf(fp11, "\n");
    }


/* CMC       IF(IPASS.EQ.7)WRITE(11,4412)L,(ZEN(2,L,J),J=1,IOUTX) */
/* CMC  4412 FORMAT(1X,I4,1X,'P',3X,10F9.2,/,10X,10F9.2,/,10X,10F9.2 */
/* CMC      1   ,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F9.2,/,10X,10F2.2 */
/* CMC      2   ,/,10X,5F9.2) */
    if (*ipass == 7) {
      fprintf(fp11, " %4d P   ",l);
      for(j=1; j<= pri_1.ioutx;j++){
	if((((j-1)%10)==0) && (j>1))
	  fprintf(fp11, "\n          ");
	fprintf(fp11, "%9.2f", zen_ref(2, l, j) );
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
/*<       IF(IPASS.EQ.2)GO TO 100 >*/
    if (*ipass == 2) {
	goto L100;
    }
/*<       POUT=P(ILNK)/EFF(IPR)+OM(IPR)+CC(IPR) >*/
    pout = net_1.p[ilnk - 1] / pro_1.eff[*ipr - 1] + pro_1.om[*ipr - 1] + 
	    pro_1.cc[*ipr - 1];
/*<       P(IOLK)=POUT >*/
	
	/* compute emission tax and add to price */
	emisTax=0;
	
	for(i=0;i<50;i++){
		emisTax = emisTax +  pro_1.Efactors[*ipr-1][i][0] * pro_1.Efactors[*ipr-1][i][1]
				    * 5.7356 * pro_1.Efactors[*ipr-1][i][2]/1000/pro_1.eff[*ipr - 1];
	}

    /*fprintf(fp25, "Year  Itn NodeType   NodeName   Sector   UEmisTax   Total P   \n");*/
	if(emisflag==1)
		fprintf(fp25, "%4d%  3d    PR         %s      %s  %10.4f       %10.4f\n",
			var_1.itime, var_1.itn, LinkNodeNames[4][(*ipr)],LinkNodeSector[4][(*ipr)],emisTax/units_1.unitcnvt[3],
			(emisTax+pout)/units_1.unitcnvt[3]);


	pout = pout+emisTax;

    net_1.p[iolk - 1] = pout;
/*<       IF(NTIME.EQ.1)Q(IOLK)=Q(ILNK)*EFF(IPR) >*/
    if (var_1.ntime == 1) {
	net_1.q[iolk - 1] = net_1.q[ilnk - 1] * pro_1.eff[*ipr - 1];
    }

/* CMC       IF(IWR1.GE.2)WRITE(6,202)IPR,IOLK,NTIME,P(IOLK) */
/* CMC   202 FORMAT(2X,'P',5X,'PROCS',I4,5X,'LINK',I4,5X,'TIME', */
/* CMC      1I3,4X,1H$,F10.4) */
    if (var_1.iwr1 >= 2) 
      fprintf(fp6, "  P     PR  %s (%s)     LINK  %s     YEAR%6d    $%10.4f\n",
	      LinkNodeNames[4][(*ipr)],LinkNodeSector[4][(*ipr)],LinkNodeNames[13][iolk],var_1.itime,net_1.p[iolk - 1]/units_1.unitcnvt[3]);
    
    
    /*<       RETURN >*/
    return 0;
    
    /* ***** DOWNPASS LOGIC. */
    
    /*<   100 CONTINUE >*/
  L100:
    /*<       Q(ILNK)=Q(IOLK)/EFF(IPR) >*/
    net_1.q[ilnk - 1] = net_1.q[iolk - 1] / pro_1.eff[*ipr - 1];
	

    /* CMC       IF(IWR1.GE.2)WRITE(6,602)IPR,ILNK,NTIME,Q(ILNK) */
    /* CMC   602 FORMAT(2X,'Q',5X,'PROCS',I4,5X,'LINK',I4,5X,'TIME', */
    /* CMC      1I3,4X,F11.3) */
    
    if (var_1.iwr1 >= 2) 
      /* The print was changed from output link quantity to input link quantity - Prakash */

	  /*	fprintf(fp6, "  Q     PROCS%4d     LINK%4d     TIME%3d    $%11.3f\n",
	      (*ipr),ilnk,var_1.ntime,net_1.q[iolk - 1]); */
    
	  fprintf(fp6, "  Q     PR  %s (%s)     LINK  %s     YEAR%6d    $%11.3f\n",
	      LinkNodeNames[4][(*ipr)],LinkNodeSector[4][(*ipr)],LinkNodeNames[13][ilnk],var_1.itime,net_1.q[ilnk - 1]/units_1.unitcnvt[8]);	



    /*<       RETURN >*/
    return 0;
    /*<       END >*/
  } /* pr_ */

#undef zen_ref
#undef labc_ref

