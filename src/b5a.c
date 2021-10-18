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

/* b5a.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
   -lf2c -lm   (in that order)
   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmc_f2c.h"
#include "f2c.h"
#include "structures.h"


/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c_n1 = -1;
static integer c__3 = 3;


/* Last Update: Jean Trommels - 6/13/89 */
/*              Jean Trommels - 8/18/89 */

/* Last update: Jianwen Lin - 1/27/97 */
/*              special events for load factor and loading order enabled */

/* ***************************************************************** INPUT */

/*<       SUBROUTINE INPUT >*/
/* Subroutine */ int input_(void)
{
  char buf[1024];
  extern FILE *fp12, *fp5, *fp21;
  FILE *fp15, *fp14;
  int pos;
  char cmc_lab[255];
  char cmc_la[10];
  /* System generated locals */
  integer i__1;
  real r__1, r__2;
  
  /* Builtin functions */
  /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
  double pow_ri(real *, integer *);
  integer s_cmp(char *, char *, ftnlen, ftnlen);
  /* Subroutine */ int s_stop(char *, ftnlen);
  
  /* Local variables */
  static char leff[4], lpff[4], ltci[4], lpab[4], lmld[4], lalf[4];
  static real gmax;
  static char lpri[4], litm[4], llov[4];
  static integer nppr, iord;
  extern /* Subroutine */ int outw_(integer *);
  static real tboembtu, stxr, capl2;
  static integer link, iloc, i__, j, k, l, m, n, jalpr[10];
  static char lcapl[4], lcapm[4], llife[4], lslat[4], lprat[4], lstoc[4], 
  lexcs[4], lcntl[4], lremu[4], lalph[4], ldelt[4], lpmax[4], lpmin[
								    4], llinp[4], lsize[4];
  static integer nalmx, nppmx, nstmx;
  extern /* Subroutine */ int input2_(void);
  static integer nnrnp, n1, il;
  static real stock;
  static integer no, istxl;
  extern /* Subroutine */ int elecs_(integer *);
  static integer nn, jj, lv;
  static real qq;
  static integer ia;
  static char lca[4];
  static integer kdd;
  static char lde[4], lcf[4], lal[4], lbl[4], lel[4];
  static real crf;
  static integer jin;
  static char lmi[4], lre[4], lio[4];
  static integer ial;
  static char lpp[4], lwr[4], lpr[4], lrs[4], lrn[4], lom[4], lir[4];
  extern /* Subroutine */ int use_(integer *, integer *);
  static real tboemwh;
  extern /* Subroutine */ int err_(integer *);
  static integer iou, npp, kwr, num;
  static real val;
  
  static integer la1, la2;
  static integer  iy;
  static integer kk, i, cpt;

  	
#define prn_ref(a_1,a_2) ren_1.prn[(a_2)*17 + a_1 - 18]
#define pprj_ref(a_1,a_2) res_1.pprj[(a_2)*75 + a_1 - 76]
#define qrn_ref(a_1,a_2) ren_1.qrn[(a_2)*17 + a_1 - 18]
#define prem_ref(a_1,a_2) min_1.prem[(a_2)*400 + a_1 - 401]
#define split_ref(a_1,a_2) all_1.split[(a_2)*400 + a_1 - 401]
#define drat_ref(a_1,a_2) dem_1.drat[(a_2)*200 + a_1 - 201]
#define linpr_ref(a_1,a_2) ref_1.linpr[(a_2)*30 + a_1 - 31]
#define numb_ref(a_1,a_2) invis_1.numb[(a_2)*2 + a_1 - 3]
#define ispec_ref(a_1,a_2) invis_1.ispec[(a_2)*2 + a_1 - 3]
  
/* #define labc_ref(a_1,a_2) pro_1.labc[(a_2)*300 + a_1 - 301] */
/* #define labd_ref(a_1,a_2) dem_1.labd[(a_2)*200 + a_1 - 201] */
/* #define labe_ref(a_1,a_2) ref_1.labe[(a_2)*30 + a_1 - 31] */
/* #define labm_ref(a_1,a_2) min_1.labm[(a_2)*15 + a_1 - 16] */
/* #define labn_ref(a_1,a_2) ren_1.labn[(a_2)*17 + a_1 - 18] */
/* #define labp_ref(a_1,a_2) pri_1.labp[(a_2)*100 + a_1 - 101] */
/*#define labr_ref(a_1,a_2) res_1.labr[(a_2)*75 + a_1 - 76]*/
/* #define labs_ref(a_1,a_2) stk_1.labs[(a_2)*20 + a_1 - 21] */
#define labw_ref(a_1,a_2,a_3) invis_1.labw[((a_3)*100 + (a_2))*2 + a_1 - \
					   203]
#define prat_ref(a_1,a_2) ref_1.prat[(a_2)*30 + a_1 - 31]
#define iinal_ref(a_1,a_2) all_1.iinal[(a_2)*400 + a_1 - 401]
#define iinmi_ref(a_1,a_2) min_1.iinmi[(a_2)*200 + a_1 - 201]
#define iinre_ref(a_1,a_2) ref_1.iinre[(a_2)*30 + a_1 - 31]
#define ioual_ref(a_1,a_2) all_1.ioual[(a_2)*400 + a_1 - 401]
#define ialpr_ref(a_1,a_2) all_1.ialpr[(a_2)*400 + a_1 - 401]
#define ioure_ref(a_1,a_2) ref_1.ioure[(a_2)*30 + a_1 - 31]
#define istck_ref(a_1,a_2) ref_1.istck[(a_2)*30 + a_1 - 31]
#define ixces_ref(a_1,a_2) ref_1.ixces[(a_2)*30 + a_1 - 31]
#define slate_ref(a_1,a_2) ref_1.slate[(a_2)*30 + a_1 - 31]
#define remul_ref(a_1,a_2) ref_1.remul[(a_2)*30 + a_1 - 31]
#define icntl_ref(a_1,a_2) ref_1.icntl[(a_2)*30 + a_1 - 31]

					     
#define rio_ref(a_1,a_2) min_1.rio[(a_2)*200 + a_1 - 201]
/* #define laba_ref(a_1,a_2) all_1.laba[(a_2)*200 + a_1 - 201] */
    
    /*<       DIMENSION JALPR(10) >*/
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
    /*<       COMMON/SAVEIMP/QNT(92),CAPLIMP(999)                                >*/
    /*<       COMMON/ELEC4/ispecLOV(300), optionalLOV(300), XMLOD, XLFAC         >*/
    
    /*<       CHARACTER*4 NODEL >*/
    /*<       CHARACTER*4  LBL,LWR,LAL,LPR,LMI,LRE,LEL,LPP,LDE,LRS,LRN >*/
    /*<       CHARACTER*4 LCAPL,LPRI,LOM,LEFF,LTCI,LCAPM,LCF,LLIFE,LIR >*/
    /*<       CHARACTER*4 LIO,LSLAT,LPFF,LPRAT,LSTOC,LEXCS,LCNTL,LREMU >*/
    /*<       CHARACTER*4 LALPH,LDELT,LPMAX,LPMIN,LLINP,LSIZE,LCA,LITM,LPAB >*/
    /*<       CHARACTER*4 LLOV, LMLD, LALF >*/
    
    /*<       LBL='    ' >*/
 
  s_copy(lbl, "    ", (ftnlen)4, (ftnlen)4);
     /*  strcpy(lbl, "  ");*/
  /*<       LWR='WR  ' >*/
  s_copy(lwr, "WR  ", (ftnlen)4, (ftnlen)4);
  /*strcpy(lwr, "WR");*/

  /*<       LAL='AL  ' >*/
  s_copy(lal, "AL  ", (ftnlen)4, (ftnlen)4);
  /*<       LPR='PR  ' >*/
  s_copy(lpr, "PR  ", (ftnlen)4, (ftnlen)4);
  /*<       LMI='MI  ' >*/
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
  /*<       LCAPL='CAPL' >*/
  s_copy(lcapl, "CAPL", (ftnlen)4, (ftnlen)4);
  /*<       LCA='CA  ' >*/
  s_copy(lca, "CA  ", (ftnlen)4, (ftnlen)4);
  /*<       LSIZE='SIZE' >*/
  s_copy(lsize, "SIZE", (ftnlen)4, (ftnlen)4);
  /*<       LPRI='PRI ' >*/
  s_copy(lpri, "PRI ", (ftnlen)4, (ftnlen)4);
  /*<       LOM='OM  ' >*/
  s_copy(lom, "OM  ", (ftnlen)4, (ftnlen)4);
  /*<       LEFF='EFF ' >*/
  s_copy(leff, "EFF ", (ftnlen)4, (ftnlen)4);
  /*<       LTCI='TCI ' >*/
  s_copy(ltci, "TCI ", (ftnlen)4, (ftnlen)4);
  /*<       LCAPM='CAPM' >*/
  s_copy(lcapm, "CAPM", (ftnlen)4, (ftnlen)4);
  /*<       LCF='CF  ' >*/
  s_copy(lcf, "CF  ", (ftnlen)4, (ftnlen)4);
  /*<       LLIFE='LIFE' >*/
  s_copy(llife, "LIFE", (ftnlen)4, (ftnlen)4);
  /*<       LIR='IR  ' >*/
  s_copy(lir, "IR  ", (ftnlen)4, (ftnlen)4);
  /*<       LIO='IO  ' >*/
  s_copy(lio, "IO  ", (ftnlen)4, (ftnlen)4);
  /*<       LSLAT='SLAT' >*/
  s_copy(lslat, "SLAT", (ftnlen)4, (ftnlen)4);
  /*<       LPFF='PFF ' >*/
  s_copy(lpff, "PFF ", (ftnlen)4, (ftnlen)4);
  /*<       LPRAT='PRAT' >*/
  s_copy(lprat, "PRAT", (ftnlen)4, (ftnlen)4);
  /*<       LSTOC='STOC' >*/
  s_copy(lstoc, "STOC", (ftnlen)4, (ftnlen)4);
  /*<       LEXCS='EXCS' >*/
  s_copy(lexcs, "EXCS", (ftnlen)4, (ftnlen)4);
  /*<       LCNTL='CNTL' >*/
  s_copy(lcntl, "CNTL", (ftnlen)4, (ftnlen)4);
  /*<       LREMU='REMU' >*/
  s_copy(lremu, "REMU", (ftnlen)4, (ftnlen)4);
  /*<       LALPH='ALPH' >*/
  s_copy(lalph, "ALPH", (ftnlen)4, (ftnlen)4);
  /*<       LDELT='DELT' >*/
  s_copy(ldelt, "DELT", (ftnlen)4, (ftnlen)4);
  /*<       LPMAX='PMAX' >*/
  s_copy(lpmax, "PMAX", (ftnlen)4, (ftnlen)4);
  /*<       LPMIN='PMIN' >*/
  s_copy(lpmin, "PMIN", (ftnlen)4, (ftnlen)4);
  /*<       LLINP='LINP' >*/
  s_copy(llinp, "LINP", (ftnlen)4, (ftnlen)4);
  /*<       LMLD='MLD '                                                        >*/
  s_copy(lmld, "MLD ", (ftnlen)4, (ftnlen)4);
  /*<       LALF='ALF '                                                        >*/
  s_copy(lalf, "ALF ", (ftnlen)4, (ftnlen)4);
  /*<       LLOV='LOV '                                                        >*/
  s_copy(llov, "LOV ", (ftnlen)4, (ftnlen)4);
  


  /* ***** BRANCH FOR EVENTS AFTER FIRST TIME PERIOD. */
  
  /*<       IF(NTIME.GT.1)GO TO 308 >*/
  if (var_1.ntime > 1) {
    goto L308;
  }
 
  /* CMC C**** READ NETWORK DATA FOR FIRST TIME PERIOD. */
  
  /* CMC       WRITE (*,*) 'Reading network data for first time period ...'      MJ060486 */
  
  /* CMC       READ(5,118)(LAB(J),J=1,5),RCTOL */
  fprintf(fp21, "Reading network data for first time period ...\n");     
  
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  var_1.rctol = atof(substring(buf, pos, 10)); pos+=10;
  
  /* CMC       WRITE(12,118)(LAB(J),J=1,5),RCTOL */
  fprintf(fp12, "%s",cmc_lab);
  fprintf(fp12, "%10.3f\n", var_1.rctol);
  
  /* CMC       READ(5,118)(LAB(J),J=1,5),ACTOL */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  var_1.actol = atof(substring(buf, pos, 10)); pos+=10;
  
  /* CMC       WRITE(12,118)(LAB(J),J=1,5),ACTOL */
  fprintf(fp12, "%s", cmc_lab);
  fprintf(fp12, "%10.3f\n", var_1.actol);
  
  /* CMC       READ(5,10)(LAB(J),J=1,5),ITMAX */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  var_1.itmax = atoi(substring(buf, pos, 10)); pos+=10;
  
  /* CMC       WRITE(12,10)(LAB(J),J=1,5),ITMAX */
  fprintf(fp12, "%s", cmc_lab);
  fprintf(fp12, "%10d\n", var_1.itmax );
  
  
  /* ***** SET ERROR CODE TO ZERO AND ASSIGN FIRST TIME PERIOD AS BASE YEAR. */
  
  /*<       IERS=0 >*/
  var_1.iers = 0;
  /*<       ITIME=IYRB >*/
  var_1.itime = var_1.iyrb;
  
  /* CMC       READ(5,9200)(LAB(J),J=1,5),WLO,WHI */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=5;
  var_1.wlo = atof(substring(buf, pos, 5)); pos+=5;
  var_1.whi = atof(substring(buf, pos, 5)); pos+=5;
  
  /* CMC       WRITE(12,9200)(LAB(J),J=1,5),WLO,WHI */
  /* CMC  9200 FORMAT(5A4,5X,4F5.2,2I5,F5.1,2I5) */
  fprintf(fp12, "%s", cmc_lab);
  fprintf(fp12, "     %5.2f%5.2f\n", var_1.wlo,  var_1.whi);
  
  
  
  /* CMC C***** READ ECHO CODE AND FINAL REPORT DETAIL CODE. */
  
  /* CMC       WRITE (*,*) 'Reading echo codes ...'                              MJ060486 */
  
  /* CMC       READ(5,1317)(LAB(J),J=1,5),IECHO,IFINL */
  fprintf(fp21, "Reading echo codes ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  el1_1.iecho  = atoi(substring(buf, pos, 5)); pos+=5;
  el1_1.ifinl  = atoi(substring(buf, pos, 5)); pos+=5;
  
  /* CMC       WRITE(12,1317)(LAB(J),J=1,5),IECHO,IFINL */
  fprintf(fp12, "%s", cmc_lab);
  fprintf(fp12, "%5d%5d\n", el1_1.iecho,  el1_1.ifinl);
  
  
  /* CMC       WRITE (*,*) 'Opening MODE.DAT ...'                                MJ060486 */
  
  /* CMC       OPEN (15,FILE = 'MODE.DAT', STATUS = 'OLD') */
  /* CMC       READ (15,427)IRES,ILOD,IELE,IMP */
  /* CMC   427 FORMAT(I4,/,I4,/,I4,/I4) */
  /* CMC       CLOSE (15) */
  fprintf(fp21,"Opening MODE.DAT ...\n");

  if((fp15=fopen("./mode.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open MODE.DAT\n");
    exit(0);
  }
  fgets(buf,sizeof(buf),fp15);pos=0;
  var_1.ires = atoi(substring(buf, pos, 4)); pos+=4;
  fgets(buf,sizeof(buf),fp15);pos=0;
  mode_1.ilod = atoi(substring(buf, pos, 4)); pos+=4;
  fgets(buf,sizeof(buf),fp15);pos=0;
  mode_1.iele = atoi(substring(buf, pos, 4)); pos+=4;
  fgets(buf,sizeof(buf),fp15);pos=0;
  mode_1.imp = atoi(substring(buf, pos, 4)); pos+=4;
  fclose(fp15);
  
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,7989) */
  /* CMC  7989 FORMAT(//,' FILE: MODE.DAT ; RUN MODE DATA READ BY INPUT:') */
  if (el1_1.iecho == 0) 
    fprintf(fp12, "\n\n FILE: MODE.DAT ; RUN MODE DATA READ BY INPUT:\n");
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,8899)IRES,ILOD,IELE,IMP */
  /* CMC  8899 FORMAT(  ' RES MODE INDICATOR        = ',I5, */
  /* CMC      1       /,' OUTPUT TO LOAD INDICATOR     = ',I2, */
  /* CMC      1       /,' OUTPUT TO ELECTRIC INDICATOR = ',I2, */
  /* CMC      1       /,' OUTPUT TO IMPACTS INDICATOR  = ',I2) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, " RES MODE INDICATOR        = %5d\n", var_1.ires);
    fprintf(fp12, " OUTPUT TO LOAD INDICATOR     = %2d\n", mode_1.ilod);
    fprintf(fp12, " OUTPUT TO ELECTRIC INDICATOR = %2d\n", mode_1.iele);
    fprintf(fp12, " OUTPUT TO IMPACTS INDICATOR  = %2d\n", mode_1.imp);
  }
  
  /*<       IF(IRES.EQ.0)IRES=3000 >*/
  if (var_1.ires == 0) {
    var_1.ires = 3000;
  }
  
  /* CMC C***** READ OUTPUT CODES FOR YEARS TO RECORD IN OUTPUT WRITER AND */
  /* ***** P AND Q LINKS. */
  
  /* CMC       READ(5,4907)LA1,LA2,(IDMP(IY),IY=1,75) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_la, substring(buf, pos, 5)); pos+=5;
  
  for(iy=1;iy<=25;iy++){
    var_1.idmp[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  fgets(buf,sizeof(buf),fp5);pos=5;
  for(iy=26;iy<=50;iy++){
    var_1.idmp[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  fgets(buf,sizeof(buf),fp5);pos=5;
  for(iy=51;iy<=75;iy++){
    var_1.idmp[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,4907)LA1,LA2,(IDMP(IY),IY=1,NPER) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_la);
    for(iy=1;iy<=var_1.nper;iy++){
      if ((((iy-1)%25)==0)&&(iy>1))
	fprintf(fp12, "\n     ");
      fprintf(fp12, "%3d", var_1.idmp[iy - 1]);
    }
    fprintf(fp12, "\n");
  }
  
  
  /* CMC C***** READ OUTPUT CODES FOR DETAILED ITERATION CALCULATIONS. */
  
  /* CMC       READ(5,4907)LA1,LA2,(JWRIT(IY),IY=1,75) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_la, substring(buf, pos, 5)); pos+=5;
  for(iy=1;iy<=25;iy++){
    ren_1.jwrit[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  fgets(buf,sizeof(buf),fp5);pos=5;
  for(iy=26;iy<=50;iy++){
    ren_1.jwrit[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  fgets(buf,sizeof(buf),fp5);pos=5;
  for(iy=51;iy<=75;iy++){
    ren_1.jwrit[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,4907)LA1,LA2,(JWRIT(IY),IY=1,NPER) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_la);
    for(iy=1;iy<=var_1.nper;iy++){
      if ((((iy-1)%25)==0)&&(iy>1))
	fprintf(fp12, "\n     ");
      fprintf(fp12, "%3d", ren_1.jwrit[iy - 1]);
    }
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,4907)LA1,LA2,(ITFIR(IY),IY=1,75) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_la, substring(buf, pos, 5)); pos+=5;
  for(iy=1;iy<=25;iy++){
    ren_1.itfir[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  fgets(buf,sizeof(buf),fp5);pos=5;
  for(iy=26;iy<=50;iy++){
    ren_1.itfir[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  fgets(buf,sizeof(buf),fp5);pos=5;
  for(iy=51;iy<=75;iy++){
    ren_1.itfir[iy - 1] =  atoi(substring(buf, pos, 3)); pos+=3;
  }
  /* CMC       IF(IECHO.EQ.0)WRITE(12,4907)LA1,LA2,(ITFIR(IY),IY=1,NPER) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s",cmc_la);
    for(iy=1;iy<=var_1.nper;iy++){
      if ((((iy-1)%25)==0)&&(iy>1))
	fprintf(fp12, "\n     ");
      fprintf(fp12, "%3d", ren_1.itfir[iy - 1]);
    }
    fprintf(fp12, "\n");
  }
  /* CMC       READ(5,4907)LA1,LA2,(ITLAS(IY),IY=1,75) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_la, substring(buf, pos, 5)); pos+=5;
  for(iy=1;iy<=25;iy++){
    ren_1.itlas[iy - 1]=  atoi(substring(buf, pos, 3)); pos+=3;
  }
  fgets(buf,sizeof(buf),fp5);pos=5;
  for(iy=26;iy<=50;iy++){
    ren_1.itlas[iy - 1]=  atoi(substring(buf, pos, 3)); pos+=3;
  }
  fgets(buf,sizeof(buf),fp5);pos=5;
  for(iy=51;iy<=75;iy++){
    ren_1.itlas[iy - 1]=  atoi(substring(buf, pos, 3)); pos+=3;
  }
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,4907)LA1,LA2,(ITLAS(IY),IY=1,NPER) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_la);
    for(iy=1;iy<=var_1.nper;iy++){
      if ((((iy-1)%25)==0)&&(iy>1))
	fprintf(fp12, "\n     ");
      fprintf(fp12, "%3d", ren_1.itlas[iy - 1]);
    }
    fprintf(fp12, "\n");
  }
  /* ***** ASSIGN MAXIMUM NUMBERS OF PROCESSES AND LINKS. */
  
  /*<       LNKMX=999 >*/
  var_1.lnkmx = 999;
  /*<       NRSMX=75 >*/
  var_1.nrsmx = 75;
  /*<       NRNMX=17 >*/
  var_1.nrnmx = 17;
  /*<       NDEMX=200                                                          >*/
  dem_1.ndemx = 200;
  /*<       NALMX=200 >*/
  nalmx = 400;
  /*<       NPRMX=300 >*/
  var_1.nprmx = 300;
  /*<       NMIMX=15 >*/
  min_1.nmimx = 200;
  /*<       NREMX=30 >*/
  min_1.nremx = 30;
  /*<       NPPMX=100 >*/
  nppmx = 300;
  /*<       NSTMX=20 >*/
  nstmx = 20;
  /*<       BOEMWH=1.594444                                                    >*/
  mode_1.boemwh = 1.594444f;
  /*<       BOEMBTU=5.44076                                                    >*/
  mode_1.boembtu = 5.44076f;
  /*<       TBOEMWH=0.0 >*/
  tboemwh = 0.f;
  /*<       TBOEMBTU=0.0 >*/
  tboembtu = 0.f;
  
  /* enter boemwh and boembtu conversions bph 12/90 */
  
  /* CMC       OPEN (14, FILE = 'b060.dat',  STATUS = 'UNKNOWN') */
  /* CMC       read (14,884,end=883) TBOEMWH */
  /* CMC       read (14,884,end=883) TBOEMBTU */
  /*<   883 continue >*/
  /* L883: */
  /* CMC   884 format (F10.5) */
  /* CMC   885 format (2F10.5) */
  /* CMC       close (14) */
  if((fp14=fopen("./b060.dat", "r"))!=NULL){
    
    fgets(buf,sizeof(buf),fp14);pos=0;
    tboemwh = atof(substring(buf, pos, 10)); pos+=10;
    fgets(buf,sizeof(buf),fp14);pos=0;
    tboembtu = atof(substring(buf, pos, 10)); pos+=10;
    fclose(fp14);
  }
  else{
    fprintf(fp21, "Warning: b060.dat not found, continuing...\n");
  }
  
  
  
  /*<       IF (TBOEMWH.NE.0) BOEMWH=TBOEMWH >*/
  if (tboemwh != 0.f) {
    mode_1.boemwh = tboemwh;
  }
  /*<       IF (TBOEMBTU.NE.0) BOEMBTU=TBOEMBTU >*/
  if (tboembtu != 0.f) {
    mode_1.boembtu = tboembtu;
  }
  
  /* CMC       WRITE (*,*) '   BOEMWH    BOEMBTU' */
  /* CMC       WRITE (*,885) BOEMWH, BOEMBTU */
  
  /* CMC       READ(5,118)(LAB(J),J=1,5),QSCALE,(QU(J),J=1,3) */
  fprintf(fp21,"   BOEMWH    BOEMBTU\n");
  fprintf(fp21,"   %10.5f    %10.5f\n", mode_1.boemwh,mode_1.boembtu);
  
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  var_1.qscale =  atof(substring(buf, pos, 10)); pos+=10;
  pos+=3;
  strcpy(var_1.qu, substring(buf, pos, 12)); pos+=12;
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,118)(LAB(J),J=1,5),QSCALE,(QU(J),J=1,3) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%10.4f   ", var_1.qscale);
    fprintf(fp12, "%s", var_1.qu);
    fprintf(fp12, "\n");
  }
  
  
  /* CMC       READ(5,118)(LAB(J),J=1,5),PSCALE,(PU(J),J=1,3) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  pri_1.pscale =  atof(substring(buf, pos, 10)); pos+=10;
  pos+=3;
  strcpy(var_1.pu, substring(buf, pos, 12)); pos+=12;
  
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,118)(LAB(J),J=1,5),PSCALE,(PU(J),J=1,3) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%10.4f   ", pri_1.pscale);
    fprintf(fp12, "%s", var_1.pu);
    fprintf(fp12, "\n");
  }
  
  
  /*<        CALL INPUT2 >*/
  input2_();
  
  /* CMC C**** READ RESOURCE NODE DATA */
  
  /* CMC       WRITE (*,*) 'Reading resource node data ...'                      MJ060486 */
  /* CMC       READ(5,117) */
  fprintf(fp21,"Reading resource node data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1810)(LAB(J),J=1,5) */
  /* CMC  1810 FORMAT(/,1X,5A4) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "\n ");
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<       NNREP=0 >*/
  var_1.nnrep = 0;
  /*<       CALL USE(1,NRSMX) >*/
  use_(&c__1, &var_1.nrsmx);
  
  /*<  11   CONTINUE >*/
 L11:
  
  /* CMC    11 READ(5,818)L,(LAB(K),K=1,4) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  l =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;
  
  
  /*<       IF(L.EQ.0)GO TO 8919 >*/
  if (l == 0) {
    goto L8919;
  }
  /*<       DO 3700 K=1,4 >*/
  /*    for (k = 1; k <= 4; ++k) {*/
  /*<       LABR(L,K)=LAB(K) >*/
  /*	labr_ref(l, k) = net_1.lab[k - 1];*/
  /*<  3700 CONTINUE >*/
  /* L3700: */
  /*    }*/
  strcpy(res_1.cmc_labr[l], cmc_lab);
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)L,(LABR(L,K),K=1,4) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", l);
    fprintf(fp12, "%s",res_1.cmc_labr[l]);
    fprintf(fp12, "\n");
  }
  
  
  /*<       IF(IUSE(L).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[l - 1] == 1) {
    err_(&c__1);
  }
  /*<       IUSE(L)=1 >*/
  net_1.iuse[l - 1] = 1;
  
  /* CMC       READ(5,650)(LAB(K),K=1,5),IOURS(L),KPR(L) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  pos+=5;
  res_1.iours[l - 1] =  atoi(substring(buf, pos, 5)); pos+=5;
  res_1.kpr[l - 1] =  atoi(substring(buf, pos, 5)); pos+=5;
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,25)L,(LAB(K),K=1,5),IOURS(L),KPR(L) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d", l);
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%5d%5d\n", res_1.iours[l - 1], res_1.kpr[l - 1]);
  }
  
  /*<       J=IOURS(L) >*/
  j = res_1.iours[l - 1];
  
  /* CMC       READ(5,319)(LAB(K),K=1,5),A(L),B(L),AB(L)               JT8/89 */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,319)(LAB(K),K=1,5),A(L),B(L),AB(L)      JT8/89 */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  res_1.a[l - 1]  =  atof(substring(buf, pos, 10)); pos+=10;
  res_1.b[l - 1]  =  atof(substring(buf, pos, 10)); pos+=10;
  res_1.ab[l - 1]  =  atof(substring(buf, pos, 10)); pos+=10;
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%10.2E%10.2E%10.2E\n", res_1.a[l - 1] , res_1.b[l - 1],res_1.ab[l - 1]);
  }
  
  /*<       PLAST(L)=A(L) >*/
  res_1.plast[l - 1] = res_1.a[l - 1];
  
  /* CMC       READ(5,17)(LAB(K),K=1,5),Q(J),CAPL(J)                             JT1-89 */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy( cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  net_1.q[j - 1]  =  atof(substring(buf, pos, 10)); pos+=10;
  net_1.capl[j - 1]  =  atof(substring(buf, pos, 10)); pos+=10;
  
  
  /*      IF (QCAPL .LT. CAPL(J)) CAPL(J) = QCAPL                           JT1-89 */
  /*<       CAPLIMP(J) = CAPL(J)                                               >*/
  saveimp_1.caplimp[j - 1] = net_1.capl[j - 1];
  /* CMC       IF(IECHO.EQ.0)WRITE(12,17)(LAB(K),K=1,5),Q(J),CAPL(J) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%10.2E%10.2E\n", net_1.q[j - 1], net_1.capl[j - 1]);
  }
  
  
  /*<       NNREP=NNREP+1 >*/
  ++var_1.nnrep;
  /*<       GO TO 11 >*/
  goto L11;
  /* loop here until done with resource data */

  /* CMC C***** READ RESOURCE PRICE PROJECTION DATA. */
  
  /*<  8919 NPPR=75 >*/
 L8919:
  nppr = 75;
  /*<       CALL USE(2,NRSMX) >*/
  use_(&c__2, &var_1.nrsmx);
  /* CMC       WRITE (*,*) 'Reading resource price projection data ...'          MJ060486 */
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading resource price projection data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  8772 CONTINUE >*/
 L8772:
  
  /* CMC  8772 READ(5,818)K,(LAB(J),J=1,4) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)K,(LAB(J),J=1,4) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  k =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;
  
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", k);
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  
  /*<       IF(K.EQ.0)GO TO 1919 >*/
  if (k == 0) {
    goto L1919;
  }
  /* CMC       READ(5,7064)(PPRJ(K,J),J=1,NPPR) */

  for(j=1;j<=nppr;j++){
    if((j-1)%10==0) {
      fgets(buf,sizeof(buf),fp5);pos=0;
      pos+=30;
    }
    pprj_ref(k, j)  = atof(substring(buf, pos, 5)); pos+=5;
  }    
  

  /* CMC  7064 FORMAT(30X,10F5.2) */
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,7064)(PPRJ(K,J),J=1,NPPR) */
  if (el1_1.iecho == 0) {
    for(j=1;j<=nppr;j++){
      if((j-1)%10==0)
	fprintf(fp12, "                              ");
      fprintf(fp12, "%5.2f",  pprj_ref(k, j) );
      if(j%10==0)
	fprintf(fp12, "\n");
    }
      if( ( (j-1)%10) !=0 )
	fprintf(fp12, "\n");
  }

  /*<       GO TO 8772 >*/
  goto L8772;
  
  /* CMC C**** READ RENEWABLE RESOURCE NODE DATA */
  
  /*<  1919 NNRNP=0 >*/
 L1919:
  nnrnp = 0;
  var_1.nnrnp=0;

  /*<       CALL USE(1,NRNMX) >*/
  use_(&c__1, &var_1.nrnmx);
  
  /* CMC       WRITE (*,*) 'Reading renewable resource node data ...'            MJ060486 */
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading renewable resource node data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab );
    fprintf(fp12, "\n");
  }
  
  /*<  1199 CONTINUE >*/
 L1199:
  
  /* CMC  1199 READ(5,818)L,(LAB(K),K=1,4) */
  
  
  fgets(buf,sizeof(buf),fp5);pos=0;
  l =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;

  
  
  
  /*<       IF(L.EQ.0)GO TO 191 >*/
  if (l == 0) {
    goto L191;
  }
  /*<       DO 3701 K=1,4 >*/
  /*     for (k = 1; k <= 4; ++k) { */
  /*<       LABN(L,K)=LAB(K) >*/
  /* 	labn_ref(l, k) = net_1.lab[k - 1]; */
  /*<  3701 CONTINUE >*/
  /* L3701: */
  /*    } */
  strcpy(ren_1.cmc_labn[l], cmc_lab);

  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)L,(LABN(L,K),K=1,4) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", l);
    fprintf(fp12, "%s", ren_1.cmc_labn[l] );
    fprintf(fp12, "\n");
  }
  
  /*<       IF(IUSE(L).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[l - 1] == 1) {
    err_(&c__1);
  }
  
  /*<       IUSE(L)=1 >*/
  net_1.iuse[l - 1] = 1;
  
  /* CMC       READ(5,1618)(LAB(K),K=1,5),IOURN(L),NSTEP(L) */
  /* CMC  1618 FORMAT(5A4,5X,2I5,E10.2,I5) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=5;
  ren_1.iourn[l - 1] = atoi(substring(buf, pos, 5)); pos+=5;
  ren_1.nstep[l - 1] = atoi(substring(buf, pos, 5)); pos+=5;
  


  /* CMC       IF(IECHO.EQ.0)WRITE(12,1625)L,(LAB(K),K=1,5),IOURN(L),NSTEP(L) */
  /* CMC  1625 FORMAT(I5,5A4,2I5,E10.2,I5) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d", l);
    fprintf(fp12, "%s",cmc_lab);
    fprintf(fp12,"%5d%5d", ren_1.iourn[l - 1], ren_1.nstep[l - 1]);
    fprintf(fp12, "\n");
  }
  
  /*<       J=IOURN(L) >*/
  j = ren_1.iourn[l - 1];
  /*<       M=NSTEP(L) >*/
  m = ren_1.nstep[l - 1];

  /* CMC       READ(5,319)(LAB(K),K=1,5),(QRN(L,KK),KK=1,M)                       JT8/89 */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,319)(LAB(K),K=1,5),(QRN(L,KK),KK=1,M)       JT8/89 */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  for (kk = 1; kk <= m; ++kk) {
    qrn_ref(l, kk) =  atof(substring(buf, pos, 10)); pos+=10;
  } 
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s",cmc_lab);
    for (kk = 1; kk <= m; ++kk) 
      fprintf(fp12, "%10.2e",qrn_ref(l, kk) );
    fprintf(fp12, "\n");
  }

  /* CMC       READ(5,319)(LAB(K),K=1,5),(PRN(L,KK),KK=1,M)                       JT8/89 */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,319)(LAB(K),K=1,5),(PRN(L,KK),KK=1,M)       JT8/89 */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;

  for (kk = 1; kk <= m; ++kk) {
    prn_ref(l, kk) =  atof(substring(buf, pos, 10)); pos+=10;
  }
 
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    for (kk = 1; kk <= m; ++kk) 
      fprintf(fp12, "%10.2e",prn_ref(l, kk) );
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,1317)(LAB(K),K=1,5),MUP(L) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1317)(LAB(K),K=1,5),MUP(L) */
  /* 1317 FORMAT(5A4,10I5)*/
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  ren_1.mup[l - 1] =  atoi(substring(buf, pos, 5)); pos+=5;
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%5d",ren_1.mup[l - 1]);
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,17)(LAB(K),K=1,5),Q(J),CAPL(J)                             JT6/13/89 */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  net_1.q[j - 1] =  atof(substring(buf, pos, 10)); pos+=10;
  net_1.capl[j - 1] =  atof(substring(buf, pos, 10)); pos+=10;
  
  /*      IF (QCAPL .LT. CAPL(J)) CAPL(J) = QCAPL                            JT6/13/89 */
  /*<       CAPLIMP(J) = CAPL(J)                                               >*/
  saveimp_1.caplimp[j - 1] = net_1.capl[j - 1];
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,17)(LAB(K),K=1,5),Q(J),CAPL(J) */
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%10.2e%10.2e", net_1.q[j - 1], net_1.capl[j - 1]);
    fprintf(fp12, "\n");
  }
  
  
  /*<       NNRNP=NNRNP+1 >*/

  ++nnrnp;
  ++var_1.nnrnp;
  /*<       GO TO 1199 >*/
  goto L1199;
  
  /* CMC C**** READ ALLOCATION NODE DATA */
  
  /*<   191 NNALL=0 >*/
 L191:
  var_1.nnall = 0;
  /*<       CALL USE(2,NRNMX) >*/
  use_(&c__2, &var_1.nrnmx);
  /*<       CALL USE(1,NALMX) >*/
  use_(&c__1, &nalmx);
  /* CMC       WRITE (*,*) 'Reading allocation node data ...'                    MJ060486 */
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading allocation node data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  16   CONTINUE >*/
 L16:
  /* CMC    16 READ(5,818)L,(LAB(K),K=1,4) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  l =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;
  
  
  
  /*<       IF(L.EQ.0)GO TO 192 >*/
  if (l == 0) {
    goto L192;
  }
  /*<       DO 3702 K=1,4 >*/
  /*     for (k = 1; k <= 4; ++k) { */
  /*<       LABA(L,K)=LAB(K) >*/
  /* 	laba_ref(l, k) = net_1.lab[k - 1]; */
  /*<  3702 CONTINUE >*/
  /* L3702: */
  /*     } */
strcpy(all_1.cmc_laba[l], cmc_lab);
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)L,(LABA(L,K),K=1,4) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", l);
    fprintf(fp12, "%s", all_1.cmc_laba[l]);
    fprintf(fp12, "\n");
  }
  
  
  /*<       IF(IUSE(L).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[l - 1] == 1) {
    err_(&c__1);
  }
  /*<       IUSE(L)=1 >*/
  net_1.iuse[l - 1] = 1;
  /* CMC       READ(5,18)(LAB(K),K=1,5),(IINAL(L,J),J=1,10) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=10;
  for(j=1;j<=10;j++){
    iinal_ref(l, j) = atoi(substring(buf, pos, 5)); pos+=5;
  }
  
  /*<       N=0 >*/
  n = 0;
  /*<       DO 619 LV=1,10 >*/
  for (lv = 1; lv <= 10; ++lv) {
    /*<       IF(IINAL(L,LV).EQ.0)GO TO 620 >*/
    if (iinal_ref(l, lv) == 0) {
      goto L620;
    }
    /*<       N=N+1 >*/
    ++n;
    /*<   619 CONTINUE >*/
    /* L619: */
  }
  /*<   620 CONTINUE >*/
 L620:   
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,25)L,(LAB(K),K=1,5),N,(IINAL(L,J),J=1,N) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d",l);
    fprintf(fp12, "%s", cmc_lab);
      fprintf(fp12, "%5d",n);
    for (j = 1; j <= n; ++j) 
      fprintf(fp12, "%5d",  iinal_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  
  /* CMC       READ(5,18)(LAB(K),K=1,5),(IALPR(L,J),J=1,N) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=10;
  for(j=1;j<=n;j++){
    ialpr_ref(l, j) = atoi(substring(buf, pos, 5)); pos+=5;
  }
  
  /*<       NALPR(L)=0 >*/
  all_1.nalpr[l - 1] = 0;
  /*<       DO 625 LV=1,N >*/
  i__1 = n;
  for (lv = 1; lv <= i__1; ++lv) {
    /*<       IF(IALPR(L,LV).EQ.0)GO TO 626 >*/
    if (ialpr_ref(l, lv) == 0) {
      goto L626;
    }
    /*<   625 NALPR(L)=NALPR(L)+1 >*/
    /* L625: */
    ++all_1.nalpr[l - 1];
  }
  /*<   626 CONTINUE >*/
 L626:
  /*<       N1=NALPR(L) >*/
  n1 = all_1.nalpr[l - 1];
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,18)(LAB(K),K=1,5),(IALPR(L,J),J=1,N1) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "          ");
    for (j = 1; j <= n1; ++j) 
      fprintf(fp12, "%5d",  ialpr_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,318)(LAB(K),K=1,5),(PREM(L,J),J=1,N) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  

  pos+=10;
  for(j=1;j<=n;j++){
	prem_ref(l, j) = atof(substring(buf, pos, 5)); pos+=5;
	  }
	

  /* CMC       IF(IECHO.EQ.0)WRITE(12,7318)(LAB(K),K=1,5),(PREM(L,J),J=1,N) */
  /* CMC  7318 FORMAT(5A4,10X,10F5.1) */
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "          ");
    for (j = 1; j <= n; ++j) 
      fprintf(fp12, "%5.1f", prem_ref(l, j));
    fprintf(fp12, "\n");
  }
  
  /* CMC  1719 READ(5,18)(LAB(K),K=1,5),(IOUAL(L,J),J=1,10) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=10;
  for(j=1;j<=10;j++){
    ioual_ref(l, j) = atoi(substring(buf, pos, 5)); pos+=5;
  }
  
  /*<       M=0 >*/
  m = 0;
  /*<       DO 621 LV=1,10 >*/
  for (lv = 1; lv <= 10; ++lv) {
    /*<       IF(IOUAL(L,LV).EQ.0)GO TO 622 >*/
    if (ioual_ref(l, lv) == 0) {
      goto L622;
    }
    /*<       M=M+1 >*/
    ++m;
    /*<   621 CONTINUE >*/
    /* L621: */
  }
  /*<   622 CONTINUE >*/
 L622:
  /* CMC       IF(IECHO.EQ.0)WRITE(12,18)(LAB(K),K=1,5),(IOUAL(L,J),J=1,M) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "          ");
    for (j = 1; j <= m; ++j) 
      fprintf(fp12, "%5d",  ioual_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  
  /*<       NINAL(L)=N >*/
  all_1.ninal[l - 1] = n;
  /*<       DO 397 I=1,N >*/
  i__1 = n;
  for (i__ = 1; i__ <= i__1; ++i__) {
    /*<       IL=IINAL(L,I) >*/
    il = iinal_ref(l, i__);
    /*<       IF(LUSE(IL).EQ.1)CALL ERR(2) >*/
    if (net_1.luse[il - 1] == 1) {
      err_(&c__2);
    }
    /*<       LUSE(IL)=1 >*/
    net_1.luse[il - 1] = 1;
    /*<   397 CONTINUE >*/
    /* L397: */
  }
  /*<       NOUAL(L)=M >*/
  all_1.noual[l - 1] = m;
  
  /* CMC       READ(5,317)(LAB(K),K=1,5),(SPLIT(L,J),J=1,M) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=10;
  for(j=1;j<=m;j++){
    split_ref(l, j) = atof(substring(buf, pos, 5)); pos+=5;
  }
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,317)(LAB(K),K=1,5),(SPLIT(L,J),J=1,M) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "          ");
    for (j = 1; j <= m; ++j) 
      fprintf(fp12, "%5.3f",  split_ref(l, j) );
    fprintf(fp12, "\n");
  }
  /* CMC       READ(5,1317)(LAB(K),K=1,5),IALST(L),NGG(L) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
    
  stk_1.ialst[l - 1] = atoi(substring(buf, pos, 5)); pos+=5;
  al1_1.ngg[l - 1] = atoi(substring(buf, pos, 5)); pos+=5;
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1317)(LAB(K),K=1,5),IALST(L),NGG(L) */
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%5d",  stk_1.ialst[l - 1]);
    fprintf(fp12, "%5d",  al1_1.ngg[l - 1]);
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,617)(LAB(K),K=1,5),GM(L),BL(L) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab,substring(buf, pos,20)); pos+=20;
  
  all_1.gm[l - 1] = atof(substring(buf, pos, 5)); pos+=5;
  all_1.bl[l - 1] = atof(substring(buf, pos, 5)); pos+=5;
  
  
  /*<       GMAX=15.0 >*/
  gmax = 15.f;
  /*<       IF(GM(L).LE.GMAX)GO TO 4433 >*/
  if (all_1.gm[l - 1] <= gmax) {
    goto L4433;
  }
  /*<       GM(L)=GMAX >*/
  all_1.gm[l - 1] = gmax;
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,4617)(LAB(K),K=1,5),GM(L),BL(L) */
  /* CMC  4617 FORMAT(5A4,5F5.2) */
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%5.2f",  all_1.gm[l - 1]);
    fprintf(fp12, "%5.2f",    all_1.bl[l - 1] );
    fprintf(fp12, "\n");
  }
  
  /*<  4433 if (n .eq. 1)  gm(l) = 0.0 >*/
 L4433:
  if (n == 1) {
    all_1.gm[l - 1] = 0.f;
  }
  /*<       NNALL=NNALL+1 >*/
  ++var_1.nnall;
  /*<       GO TO 16 >*/
  goto L16;
  
  /* CMC C*** READ CONVERSION PROCESS DATA */
  
  /*<   192 NNPR=0 >*/
 L192:
  var_1.nnpr = 0;
  /*<       CALL USE(2,NALMX) >*/
  use_(&c__2, &nalmx);
  /*<       CALL USE(1,NPRMX) >*/
  use_(&c__1, &var_1.nprmx);
  
  /* CMC       WRITE (*,*) 'Reading conversion process data ...'                 MJ060486 */
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading conversion process data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  22   CONTINUE >*/
 L22:
  /* CMC    22 READ(5,818)L,(LAB(K),K=1,4) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  l =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  strcpy(cmc_lab,substring(buf, pos, 16)); pos+=16;
  
  
  
  /*<       IF(L.EQ.0)GO TO 193 >*/
  if (l == 0) {
    goto L193;
  }
  /*<       DO 3704 K=1,4 >*/
  /*    for (k = 1; k <= 4; ++k) {*/
  /*<       LABC(L,K)=LAB(K) >*/
  /*	labc_ref(l, k) = net_1.lab[k - 1];*/
  /*<  3704 CONTINUE >*/
  /* L3704: */
  /*    }*/
  strcpy(pro_1.cmc_labc[l], cmc_lab);
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)L,(LABC(L,K),K=1,4) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", l);
    fprintf(fp12, "%s", cmc_lab);
      fprintf(fp12, "\n");
  }
  
  /*<       IF(IUSE(L).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[l - 1] == 1) {
    err_(&c__1);
  }
  /*<       IUSE(L)=1 >*/
  net_1.iuse[l - 1] = 1;
  
  /* CMC       READ(5,1317)(LAB(K),K=1,5),IINPR(L),IOUPR(L) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  
  pro_1.iinpr[l - 1] = atoi(substring(buf, pos, 5)); pos+=5;
  pro_1.ioupr[l - 1]= atoi(substring(buf, pos, 5)); pos+=5;
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,25)L,(LAB(K),K=1,5),IINPR(L),IOUPR(L) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d",l);
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%5d%5d\n",pro_1.iinpr[l - 1],pro_1.ioupr[l - 1]);
  }
  
  /*<       IL=IINPR(L) >*/
  il = pro_1.iinpr[l - 1];
  /*<       IF(LUSE(IL).EQ.1)CALL ERR(2) >*/
  if (net_1.luse[il - 1] == 1) {
    err_(&c__2);
  }
  /*<       LUSE(IL)=1 >*/
  net_1.luse[il - 1] = 1;
  /*<       J=IOUPR(L) >*/
  j = pro_1.ioupr[l - 1];
  
  /* CMC       READ(5,14)(LAB(K),K=1,5),OM(L),EFF(L), */
  /* CMC      1 TCI(L),CAPM(L),CF(L),LIFE(L),RIR(L),CAPL(J) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  
  pos+=5;
  pro_1.om[l - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  pro_1.eff[l - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  pro_1.tci[l - 1] =  atof(substring(buf, pos, 10)); pos+=10;
  pro_1.capm[l - 1] =  atof(substring(buf, pos, 10)); pos+=10;
  pro_1.cf[l - 1]=  atof(substring(buf, pos, 5)); pos+=5;
  pro_1.life[l - 1]=  atoi(substring(buf, pos, 5)); pos+=5;
  pro_1.rir[l - 1]=  atof(substring(buf, pos, 5)); pos+=5;
  net_1.capl[j - 1] =  atof(substring(buf, pos, 10)); pos+=10;
  
  /* CMC C      READ(5,14)(LAB(K),K=1,5),OM(L),EFF(L),                          JT6/13/89 */
  /*     1 TCI(L),CAPM(L),CF(L),LIFE(L),RIR(L),QCAPL                      JT6/13/89 */
  /*      IF (QCAPL .LT. CAPL(J)) CAPL(J) = QCAPL                         JT6/13/89 */
  /*<       CAPLIMP(J) = CAPL(J)                                               >*/
  saveimp_1.caplimp[j - 1] = net_1.capl[j - 1];
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,6614)(LAB(K),K=1,5),OM(L),EFF(L), */
  /* CMC      1 TCI(L),CAPM(L),CF(L),LIFE(L),RIR(L),CAPL(J) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "     ");
    fprintf(fp12, "%10.2f",pro_1.om[l - 1] );
    fprintf(fp12, "%10.2f",pro_1.eff[l - 1] );
    fprintf(fp12, "%10.2e",pro_1.tci[l - 1] );
    fprintf(fp12, "%10.2e",pro_1.capm[l - 1]);
    fprintf(fp12, "%5.2f",pro_1.cf[l - 1]);
    fprintf(fp12, "%5d", pro_1.life[l - 1]);
    fprintf(fp12, "%5.2f", pro_1.rir[l - 1]);
    fprintf(fp12, "%10.2e",net_1.capl[j - 1]);
    fprintf(fp12, "\n");
  }
  
  /*<       CRF=(RIR(L)*(1.+RIR(L))**LIFE(L))/((1.+RIR(L))**LIFE(L)-1.) >*/
  r__1 = pro_1.rir[l - 1] + 1.f;
  r__2 = pro_1.rir[l - 1] + 1.f;
  crf = pro_1.rir[l - 1] * pow_ri(&r__1, &pro_1.life[l - 1]) / (pow_ri(&
								       r__2, &pro_1.life[l - 1]) - 1.f);
  /*<       CC(L)=(TCI(L)*CRF)/(CAPM(L)*CF(L)) >*/
  pro_1.cc[l - 1] = pro_1.tci[l - 1] * crf / (pro_1.capm[l - 1] * pro_1.cf[
									   l - 1]);
  /* CMC       IF(IECHO.EQ.0)WRITE(12,6614)(LAB(K),K=1,5),OM(L),EFF(L), */
  /* CMC      1 TCI(L),CAPM(L),CF(L),LIFE(L),RIR(L),CAPL(J) */
  /* CMC  6614 FORMAT(5A4,5X,2F10.2,2E10.2,F5.2,I5,F5.2,E10.2) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "     ");
    fprintf(fp12, "%10.2f",pro_1.om[l - 1] );
    fprintf(fp12, "%10.2f",pro_1.eff[l - 1] );
    fprintf(fp12, "%10.2e",pro_1.tci[l - 1] );
    fprintf(fp12, "%10.2e",pro_1.capm[l - 1]);
    fprintf(fp12, "%5.2f",pro_1.cf[l - 1]);
    fprintf(fp12, "%5d", pro_1.life[l - 1]);
    fprintf(fp12, "%5.2f", pro_1.rir[l - 1]);
    fprintf(fp12, "%10.2e",net_1.capl[j - 1]);
    fprintf(fp12, "\n");
  }
  
  
  
  /*<       NNPR=NNPR+1 >*/
  ++var_1.nnpr;
  /*<       GO TO 22 >*/
  goto L22;
  
  /* CMC C*** READ MULTI-INPUT CONVERSION PROCESS DATA */
  
  /*<   193 NNMI=0 >*/
 L193:
  
  var_1.nnmi = 0;
  /*<       CALL USE(2,NPRMX) >*/
  use_(&c__2, &var_1.nprmx);
  /*<       CALL USE(1,NMIMX) >*/
  use_(&c__1, &min_1.nmimx);
  /* CMC       WRITE (*,*) 'Reading multi-input conversion process data ...'     MJ060486 */
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading multi-input conversion process data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  
  
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s",cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  72   CONTINUE >*/
 L72:
  /* CMC    72 READ(5,818)L,(LAB(K),K=1,4) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  l =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  
  strcpy(cmc_lab,substring(buf, pos, 16)); pos+=16;
  
  
  /*<       IF(L.EQ.0)GO TO 197 >*/
  if (l == 0) {
    goto L197;
  }
  /*<       DO 3705 K=1,4 >*/
  /*    for (k = 1; k <= 4; ++k) {*/
  /*<       LABM(L,K)=LAB(K) >*/
  /*     labm_ref(l, k) = net_1.lab[k - 1];*/
  /*<  3705 CONTINUE >*/
  /* L3705: */
  /*    }*/
  

   strcpy(min_1.cmc_labm[l], cmc_lab); 
  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)L,(LABM(L,K),K=1,4) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", l);
	fprintf(fp12, "%s",min_1.cmc_labm[l]);
    fprintf(fp12, "\n");
  }
  
  /*<       IF(IUSE(L).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[l - 1] == 1) {
    err_(&c__1);
  }
  /*<       IUSE(L)=1 >*/
  net_1.iuse[l - 1] = 1;
  /* CMC       READ(5,18)(LAB(K),K=1,5),(IINMI(L,J),J=1,5) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  
  pos+=10;
  for(j=1;j<=5;j++){
    iinmi_ref(l, j) = atoi(substring(buf, pos, 5)); pos+=5;
  }
  
  /*<       N=0 >*/
  n = 0;
  /*<       DO 724 LV=1,5 >*/
  for (lv = 1; lv <= 5; ++lv) {
    /*<       IF(IINMI(L,LV).EQ.0)GO TO 725 >*/
    if (iinmi_ref(l, lv) == 0) {
      goto L725;
    }
    /*<       N=N+1 >*/
    ++n;
    /*<   724 CONTINUE >*/
    /* L724: */
  }
  /*<   725 CONTINUE >*/
 L725:
  /* CMC       IF(IECHO.EQ.0)WRITE(12,25)L,(LAB(K),K=1,5),(IINMI(L,J),J=1,N) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d",l);
    fprintf(fp12, "%s", cmc_lab);
    for (j = 1; j <= n; ++j) 
      fprintf(fp12, "%5d",  iinmi_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  /*<       NINMI(L)=N >*/
  min_1.ninmi[l - 1] = n;
  
  /*<       DO 497 J=1,N >*/
  i__1 = n;
  for (j = 1; j <= i__1; ++j) {
    /*<       IL=IINMI(L,J) >*/
    il = iinmi_ref(l, j);
    /*<       IF(LUSE(IL).EQ.1)CALL ERR(2) >*/
    if (net_1.luse[il - 1] == 1) {
      err_(&c__2);
    }
    /*<       LUSE(IL)=1 >*/
    net_1.luse[il - 1] = 1;
    /*<   497 CONTINUE >*/
    /* L497: */
  }
  
  /* CMC       READ(5,318)(LAB(K),K=1,5),(RIO(L,J),J=1,N) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  
  pos+=10;
  for(j=1;j<=n;j++){
    rio_ref(l, j) = atof(substring(buf, pos, 5)); pos+=5;
  } 
  /* CMC       IF(IECHO.EQ.0)WRITE(12,318)(LAB(K),K=1,5),(RIO(L,J),J=1,N) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "          ");
    for (j = 1; j <= n; ++j) 
      fprintf(fp12, "%5.2f",  rio_ref(l, j) );
    fprintf(fp12, "\n");
  }
  /* CMC       READ(5,18)(LAB(K),K=1,5),IOUMI(L) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab,substring(buf, pos, 20)); pos+=20;
  
  pos+=10;
  min_1.ioumi[l - 1]= atoi(substring(buf, pos, 5)); pos+=5;
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,18)(LAB(K),K=1,5),IOUMI(L) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "          ");
    fprintf(fp12, "%5d", min_1.ioumi[l - 1] );
    fprintf(fp12, "\n");
  }
  
  
  /*<       J=IOUMI(L) >*/
  j = min_1.ioumi[l - 1];
  
  /* CMC       READ(5,953)(LAB(K),K=1,5),OMM(L), */
  /* CMC      1 TCIM(L),CAPMM(L),CFM(L),LIFEM(L),RIRM(L),CAPL(J) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=5;
  min_1.omm[l - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  min_1.tcim[l - 1] =  atof(substring(buf, pos,10 )); pos+=10;
  min_1.capmm[l - 1] =  atof(substring(buf, pos,10 )); pos+=10;
  min_1.cfm[l - 1] =  atof(substring(buf, pos,5 )); pos+=5;
  min_1.lifem[l - 1] =  atoi(substring(buf, pos,5 )); pos+=5;
  min_1.rirm[l - 1] =  atof(substring(buf, pos,5 )); pos+=5;
  net_1.capl[j - 1] =  atof(substring(buf, pos,10 )); pos+=10;
  
  /*      IF (QCAPL .LT. CAPL(J)) CAPL(J) = QCAPL                         JT6/13/89 */
  /*<       CAPLIMP(J) = CAPL(J)                                          >*/
  saveimp_1.caplimp[j - 1] = net_1.capl[j - 1];
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,953)(LAB(K),K=1,5),OMM(L), */
  /* CMC      1 TCIM(L),CAPMM(L),CFM(L),LIFEM(L),RIRM(L),CAPL(J) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "     ");
    fprintf(fp12, "%5.2f", min_1.omm[l - 1]  );
    fprintf(fp12, "%10.2e",   min_1.tcim[l - 1] );
    fprintf(fp12, "%10.2e",    min_1.capmm[l - 1] );
    fprintf(fp12, "%5.2f",   min_1.cfm[l - 1]  );
    fprintf(fp12, "%5d",   min_1.lifem[l - 1]  );
    fprintf(fp12, "%5.2f",  min_1.rirm[l - 1]  );
    fprintf(fp12, "%10.2e",  net_1.capl[j - 1] );
    fprintf(fp12, "\n");
  }
  
  
  /*<       CRF=(RIRM(L)*(1.+RIRM(L))**LIFEM(L))/((1.+RIRM(L))**LIFEM(L)-1.) >*/
  r__1 = min_1.rirm[l - 1] + 1.f;
  r__2 = min_1.rirm[l - 1] + 1.f;
  crf = min_1.rirm[l - 1] * pow_ri(&r__1, &min_1.lifem[l - 1]) / (pow_ri(&
									 r__2, &min_1.lifem[l - 1]) - 1.f);
  /*<       CCM(L)=(TCIM(L)*CRF)/(CAPMM(L)*CFM(L)) >*/
  min_1.ccm[l - 1] = min_1.tcim[l - 1] * crf / (min_1.capmm[l - 1] * 
						min_1.cfm[l - 1]);
  /*<       NNMI=NNMI+1 >*/
  ++var_1.nnmi;
  /*<       GO TO 72 >*/
  goto L72;
  
  /* CMC C***** READ DEMAND PROCESS DATA. */
  
  /*<   197 NNDE=0 >*/
 L197:
  var_1.nnde = 0;
  /*<       CALL USE(2,NMIMX) >*/
  use_(&c__2, &min_1.nmimx);
  /*<       CALL USE(1,NDEMX) >*/
  use_(&c__1, &dem_1.ndemx);
  
  /* CMC       WRITE (*,*) 'Reading demand process data ...'                     MJ060486 */
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading demand process data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  19   CONTINUE >*/
 L19:
  /* CMC    19 READ(5,2999)L,(LAB(K),K=1,4),IL,KDD */
  fgets(buf,sizeof(buf),fp5);pos=0;
  pos+=1;
  l = atoi(substring(buf, pos, 4)); pos+=4;
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;
  
  pos+=4;
  il = atoi(substring(buf, pos, 5)); pos+=5;
  kdd = atoi(substring(buf, pos, 5)); pos+=5;
  
  /*<       IF(L.EQ.0)GO TO 194 >*/
  if (l == 0) {
    goto L194;
  }
  /*<       KD(L)=KDD >*/
  dem_1.kd[l - 1] = kdd;
  /*<       DO 3706 K=1,4 >*/
  /*    for (k = 1; k <= 4; ++k) { */
  /*<       LABD(L,K)=LAB(K) >*/
  /*	labd_ref(l, k) = net_1.lab[k - 1]; */
  /*<  3706 CONTINUE >*/
  /* L3706: */
  /*    } */
  strcpy(dem_1.cmc_labd[l], cmc_lab);
  /* CMC       IF(IECHO.EQ.0)WRITE(12,2999)L,(LABD(L,K),K=1,5),IL,KD(L) */
  /* CMC  2999 FORMAT(1X,I4,4A4,4X,2I5) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, " %4d", l);
    fprintf(fp12, "%s    ", dem_1.cmc_labd[l]);
    fprintf(fp12, "    %5d%5d\n", il, dem_1.kd[l - 1]);

  }  
  
  /*<       IF(IUSE(L).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[l - 1] == 1) {
    err_(&c__1);
  }
  /*<       IUSE(L)=1 >*/
  net_1.iuse[l - 1] = 1;
  /*<       IINDE(L)=IL >*/
  dem_1.iinde[l - 1] = il;
  /*<       IF(LUSE(IL).EQ.1)CALL ERR(2) >*/
  if (net_1.luse[il - 1] == 1) {
    err_(&c__2);
  }
  /*<       LUSE(IL)=1 >*/
  net_1.luse[il - 1] = 1;
  /*<       NNDE=NNDE+1 >*/
  ++var_1.nnde;
  /*<       GO TO 19 >*/
  goto L19;
  
  /* CMC C***** READ GROWTH RATES FOR DEMAND PROJECTIONS. */
  
  /*<  194  CONTINUE >*/
 L194:
  /* CMC   194 READ(5,10)(LAB(J),J=1,5) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  /* CMC       WRITE (*,*) 'Reading demand growth rates ...'                     MJ060486 */
  
  /*<       CALL USE(2,NDEMX) >*/
  fprintf(fp21,"Reading demand growth rates ...\n");

  use_(&c__2, &dem_1.ndemx);
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s",cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  2772 CONTINUE >*/
 L2772:
  /* CMC  2772 READ(5,818)K,(LAB(J),J=1,4) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)K,(LAB(J),J=1,4) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  k =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;
  
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", k);
    fprintf(fp12, "%s", cmc_lab);
      fprintf(fp12, "\n");
  }
  
  /*<       IF(K.EQ.0)GO TO 7194 >*/
  if (k == 0) {
    goto L7194;
  }
  /* CMC       READ(5,7064)(DRAT(K,J),J=1,NPPR) */

  for(j=1;j<=nppr;j++){
    if((j-1)%10==0) {
      fgets(buf,sizeof(buf),fp5);pos=0;
      pos+=30;
    }
    drat_ref(k, j)   = atof(substring(buf, pos, 5)); pos+=5;
  }    
  

  /* CMC  7064 FORMAT(30X,10F5.2) */
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,7064)(PPRJ(K,J),J=1,NPPR) */
  if (el1_1.iecho == 0) {
    for(j=1;j<=nppr;j++){
      if((j-1)%10==0)
	fprintf(fp12, "                              ");
      fprintf(fp12, "%5.2f",  drat_ref(k, j) );
      if(j%10==0)
	fprintf(fp12, "\n");
    }
      if( ( (j-1)%10) !=0 )
	fprintf(fp12, "\n");
  }



  /*<       GO TO 2772 >*/
  goto L2772;
  
  
  /* CMC C**** READ REFINERY NODE DATA */
  
  /*<  7194 NNRE=0 >*/
 L7194:
  var_1.nnre = 0;
  /*<       CALL USE(1,NREMX) >*/
  use_(&c__1, &min_1.nremx);
  /* CMC       WRITE (*,*) 'Reading multi-output node data ...'                  MJ060486 */
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading multi-output node data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;    
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  23   CONTINUE >*/
 L23:
  /* CMC    23 READ(5,818)L,(LAB(K),K=1,4) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  l =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;    
  
  /*<       IF(L.EQ.0)GO TO 195 >*/
  if (l == 0) {
    goto L195;
  }
  /*<       DO 3707 K=1,4 >*/
  /*    for (k = 1; k <= 4; ++k) {*/
  /*<       LABE(L,K)=LAB(K) >*/
  /*	labe_ref(l, k) = net_1.lab[k - 1];*/
  /*<  3707 CONTINUE >*/
  /* L3707: */
  /*    }*/
strcpy(ref_1.cmc_labe[l], cmc_lab);
  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)L,(LABE(L,K),K=1,4) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", l);
    fprintf(fp12, "%s",ref_1.cmc_labe[l]);
    fprintf(fp12, "\n");
  }
  
  /*<       IF(IUSE(L).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[l - 1] == 1) {
    err_(&c__1);
  }
  /*<       IUSE(L)=1 >*/
  net_1.iuse[l - 1] = 1;
  /* CMC       READ(5,1317)(LAB(K),K=1,5),IINRE(L,1),IORDC(L) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  iinre_ref(l, 1) = atoi(substring(buf, pos, 5)); pos+=5;
  ref_1.iordc[l - 1] = atoi(substring(buf, pos, 5)); pos+=5;
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,25)L,(LAB(K),K=1,5),IINRE(L,1),IORDC(L) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d",l);
    fprintf(fp12, "%s",cmc_lab);
    fprintf(fp12, "%5d",  iinre_ref(l, 1) );
    fprintf(fp12, "%5d",  ref_1.iordc[l - 1] );
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,1317)(LAB(K),K=1,5),(IOURE(L,J),J=1,6) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  for(j=1;j<=6;j++){
    ioure_ref(l, j)= atoi(substring(buf, pos, 5)); pos+=5;
  }
  
  /*<       M=0 >*/
  m = 0;
  /*<       DO 829 LV=1,6 >*/
  for (lv = 1; lv <= 6; ++lv) {
    /*<       IF(IOURE(L,LV).EQ.0)GO TO 828 >*/
    if (ioure_ref(l, lv) == 0) {
      goto L828;
    }
    /*<       M=M+1 >*/
    ++m;
    /*<   829 CONTINUE >*/
    /* L829: */
  }
  /*<   828 CONTINUE >*/
 L828:
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1317)(LAB(K),K=1,5),(IOURE(L,J),J=1,M) */
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s",cmc_lab);
    for(j=1;j<=m;j++)
      fprintf(fp12, "%5d",   ioure_ref(l, j));
    fprintf(fp12, "\n");
  }
  
  /*<       NOURE(L)=M >*/
  ref_1.noure[l - 1] = m;
  /*<       NINRE(L)=1 >*/
  ref_1.ninre[l - 1] = 1;
  /*<       IORD=IORDC(L) >*/
  iord = ref_1.iordc[l - 1];
  /* 1318 FORMAT(5A4,10F5.2)  1317 FORMAT(5A4,10I5) */
  /* CMC       READ(5,1318)(LAB(K),K=1,5),(SLATE(L,J),J=1,M) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1318)(LAB(K),K=1,5),(SLATE(L,J),J=1,M) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  for(j=1;j<=m;j++){
    slate_ref(l, j)= atof(substring(buf, pos, 5)); pos+=5;
  }
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s",cmc_lab);
    for(j=1;j<=m;j++)
      fprintf(fp12, "%5.2f", slate_ref(l, j));
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,1317)(LAB(K),K=1,5),(LINPR(L,J),J=1,M) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1317)(LAB(K),K=1,5),(LINPR(L,J),J=1,M) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  for(j=1;j<=m;j++){
    linpr_ref(l, j)= atoi(substring(buf, pos, 5)); pos+=5;
  }
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    for(j=1;j<=m;j++)
      fprintf(fp12, "%5d",  linpr_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,1318)(LAB(K),K=1,5),(PRAT(L,J),J=1,M) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1318)(LAB(K),K=1,5),(PRAT(L,J),J=1,M) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  for(j=1;j<=m;j++){
    prat_ref(l, j)= atof(substring(buf, pos, 5)); pos+=5;
  }
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s",cmc_lab);
    for(j=1;j<=m;j++)
      fprintf(fp12, "%5.2f", prat_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,1317)(LAB(K),K=1,5),(ISTCK(L,J),J=1,M) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1317)(LAB(K),K=1,5),(ISTCK(L,J),J=1,M) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  for(j=1;j<=m;j++){
    istck_ref(l, j)= atoi(substring(buf, pos, 5)); pos+=5;
  }
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s",cmc_lab);
    for(j=1;j<=m;j++)
      fprintf(fp12, "%5d",  istck_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,1317)(LAB(K),K=1,5),(IXCES(L,J),J=1,M) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1317)(LAB(K),K=1,5),(IXCES(L,J),J=1,M) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  for(j=1;j<=m;j++){
    ixces_ref(l, j)= atoi(substring(buf, pos, 5)); pos+=5;
  }
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    for(j=1;j<=m;j++)
      fprintf(fp12, "%5d",  ixces_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  /* CMC       READ(5,1317)(LAB(K),K=1,5),(ICNTL(L,J),J=1,M) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1317)(LAB(K),K=1,5),(ICNTL(L,J),J=1,M) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  for(j=1;j<=m;j++){
    icntl_ref(l, j)= atoi(substring(buf, pos, 5)); pos+=5;
  }
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s",cmc_lab);
    for(j=1;j<=m;j++)
      fprintf(fp12, "%5d",  icntl_ref(l, j) );
    fprintf(fp12, "\n");
  }
  /* CMC       READ(5,1318)(LAB(K),K=1,5),(REMUL(L,J),J=1,M) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1318)(LAB(K),K=1,5),(REMUL(L,J),J=1,M) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  for(j=1;j<=m;j++){
    remul_ref(l, j)= atof(substring(buf, pos, 5)); pos+=5;
  }
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    for(j=1;j<=m;j++)
      fprintf(fp12, "%5.2f", remul_ref(l, j) );
    fprintf(fp12, "\n");
  }
  
  /*<       J=IINRE(L,1) >*/
  j = iinre_ref(l, 1);
  /*<       IF(LUSE(J).EQ.1)CALL ERR(2) >*/
  if (net_1.luse[j - 1] == 1) {
    err_(&c__2);
  }
  /*<       LUSE(J)=1 >*/
  net_1.luse[j - 1] = 1;
  
  
  /* CMC       READ(5,959)(LAB(K),K=1,5),OMR(L),                                  JT6/13/89 */
  /* CMC      1 TCIR(L),CAPMR(L),CFR(L),LIFER(L),RIRR(L),PFF(L),CAPL(J)           JT6/13/89 */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=5;
  ref_1.omr[l - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  ref_1.tcir[l - 1] =  atof(substring(buf, pos, 10)); pos+=10;
  ref_1.capmr[l - 1] =  atof(substring(buf, pos, 10)); pos+=10;
  ref_1.cfr[l - 1]=  atof(substring(buf, pos, 5)); pos+=5;
  ref_1.lifer[l - 1]=  atoi(substring(buf, pos, 5)); pos+=5;
  ref_1.rirr[l - 1]=  atof(substring(buf, pos, 5)); pos+=5;
  ref_1.pff[l - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  net_1.capl[j - 1] =  atof(substring(buf, pos, 10)); pos+=10;
  
  /*<       CAPLIMP(J) = CAPL(J)                                               >*/
  saveimp_1.caplimp[j - 1] = net_1.capl[j - 1];
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,959)(LAB(K),K=1,5),OMR(L), */
  /* CMC      1 TCIR(L),CAPMR(L),CFR(L),LIFER(L),RIRR(L),PFF(L),CAPL(J) */
  /* CMC   959 FORMAT(5A4,5X,F5.2,2E10.2,F5.2,I5,2F5.2,E10.2) */
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "     ");
    fprintf(fp12, "%5.2f",  ref_1.omr[l - 1]);
    fprintf(fp12, "%10.2e", ref_1.tcir[l - 1]);
    fprintf(fp12, "%10.2e", ref_1.capmr[l - 1] );
    fprintf(fp12, "%5.2f",   ref_1.cfr[l - 1]);
    fprintf(fp12, "%5d",     ref_1.lifer[l - 1]);
    fprintf(fp12, "%5.2f",  ref_1.rirr[l - 1]);
    fprintf(fp12, "%5.2f",  ref_1.pff[l - 1] );
    fprintf(fp12, "%10.2e", net_1.capl[j - 1] );
    fprintf(fp12, "\n");
  }
  
  
  /*<       CRF=(RIRR(L)*(1.+RIRR(L))**LIFER(L))/((1.+RIRR(L))**LIFER(L)-1.)   >*/
  r__1 = ref_1.rirr[l - 1] + 1.f;
  r__2 = ref_1.rirr[l - 1] + 1.f;
  crf = ref_1.rirr[l - 1] * pow_ri(&r__1, &ref_1.lifer[l - 1]) / (pow_ri(&
									 r__2, &ref_1.lifer[l - 1]) - 1.f);
  /*<       CCR(L)=(TCIR(L)*CRF)/(CAPMR(L)*CFR(L)) >*/
  ref_1.ccr[l - 1] = ref_1.tcir[l - 1] * crf / (ref_1.capmr[l - 1] * 
						ref_1.cfr[l - 1]);
  /*<       NO=NOURE(L) >*/
  no = ref_1.noure[l - 1];
  
  /*<       JIN=J >*/
  jin = j;
  /*<       DO 40 J=1,NO >*/
  i__1 = no;
  for (j = 1; j <= i__1; ++j) {
    /*<       IOU=IOURE(L,J) >*/
    iou = ioure_ref(l, j);
    /*<       CAPL(IOU)=CAPL(JIN)*SLATE(L,J) >*/
    net_1.capl[iou - 1] = net_1.capl[jin - 1] * slate_ref(l, j);
    /*<    40 CONTINUE >*/
    /* L40: */
  }
  /*<       NNRE=NNRE+1 >*/
  ++var_1.nnre;
  /*<       GO TO 23 >*/
  goto L23;
  
  /* CMC C***** READ STOCKPILE NODE DATA. */
  
  /*<   195 NNST=0 >*/
 L195:
  var_1.nnst = 0;
  /*<       CALL USE(2,NREMX) >*/
  use_(&c__2, &min_1.nremx);
  /*<       CALL USE(1,NSTMX) >*/
  use_(&c__1, &nstmx);
  /* CMC       WRITE (*,*) 'Reading stockpile data ...'                          MJ060486 */
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading stockpile data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  207  CONTINUE >*/
 L207:
  /* CMC   207 READ(5,819)L,(LAB(J),J=1,4),IOU,QQ,STOCK,STXR,ISTXL */
  fgets(buf,sizeof(buf),fp5);pos=0;
  l= atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;
  
  pos+=1;
  iou = atoi(substring(buf, pos,5 )); pos+=5;
  qq = atof(substring(buf, pos, 10)); pos+=10;
  stock = atof(substring(buf, pos,10 )); pos+=10;
  stxr = atof(substring(buf, pos,10 )); pos+=10;
  istxl = atoi(substring(buf, pos,10 )); pos+=10;
  
  
  /*<       IF(L.EQ.0)GO TO 196 >*/
  if (l == 0) {
    goto L196;
  }
  /*<       DO 3708 K=1,4 >*/
/*   for (k = 1; k <= 4; ++k) { */
    /*<       LABS(L,K)=LAB(K) >*/
/*     labs_ref(l, k) = net_1.lab[k - 1]; */
    /*<  3708 CONTINUE >*/
    /* L3708: */
/*   } */
strcpy( stk_1.cmc_labs[l], cmc_lab);  


  /*<       IOUST(L)=IOU >*/
  stk_1.ioust[l - 1] = iou;
  /*<       Q(IOU)=QQ >*/
  net_1.q[iou - 1] = qq;
  /*<       STOK(L)=STOCK >*/
  stk_1.stok[l - 1] = stock;
  /*<       ISTKEXL(L)=ISTXL                                                   >*/
  stk_1.istkexl[l - 1] = istxl;
  /*<       STKEXR(L)=STXR                                                     >*/
  stk_1.stkexr[l - 1] = stxr;
  
  /* 819 FORMAT(I5,3X,4A4,1X,I5,2F10.2,1F10.7,I10)  */
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,819)L,(LABS(L,J),J=1,4),IOUST(L),Q(IOU), */
  /* CMC      1 STOK(L),STXR,ISTXL*/      
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", l);
    fprintf(fp12, "%s",stk_1.cmc_labs[l]);
    fprintf(fp12, " ");
    fprintf(fp12, "%5d", iou );
    fprintf(fp12, "%10.2f", qq );
    fprintf(fp12, "%10.2f", stock);
    fprintf(fp12, "%10.7f", stxr );
    fprintf(fp12, "%10d", istxl);
    fprintf(fp12, "\n");
  }
  
  /*<       IF(IUSE(L).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[l - 1] == 1) {
    err_(&c__1);
  }
  /*<       IUSE(L)=1 >*/
  net_1.iuse[l - 1] = 1;
  /*<       NNST=NNST+1 >*/
  ++var_1.nnst;
  /*<       ISTC(NNST)=L >*/
  stk_1.istc[var_1.nnst - 1] = l;
  /*<       GO TO 207 >*/
  goto L207;
  
  /* CMC C**** READ PRICING POLICY DATA */
  
  /*<   196 NPP=0 >*/
 L196:
  npp = 0;
  /*<       CALL USE(2,NSTMX) >*/
  use_(&c__2, &nstmx);
  /*<       CALL USE(1,NPPMX) >*/
  use_(&c__1, &nppmx);
  
  /* CMC       WRITE (*,*) 'Reading pricing policy data ...'                     MJ060486 */
  /* CMC       READ(5,10)(LAB(K),K=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(K),K=1,5) */
  fprintf(fp21,"Reading pricing policy data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  if (el1_1.iecho == 0) {
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /*<  802  CONTINUE >*/
 L802:
  /* CMC   802 READ(5,818)J,(LAB(K),K=1,4) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  j =  atoi(substring(buf, pos, 5)); pos+=5;
  pos+=3;
  strcpy(cmc_lab, substring(buf, pos, 16)); pos+=16;
  
  
  /*<       IF(J.EQ.0)GO TO 987 >*/
  if (j == 0) {
    goto L987;
  }
  /*<       DO 3710 K=1,4 >*/
  /* for (k = 1; k <= 4; ++k) { */
    /*<       LABP(J,K)=LAB(K) >*/
   /*  labp_ref(j, k) = net_1.lab[k - 1]; */
    /*<  3710 CONTINUE >*/
    /* L3710: */
  /* } */
  strcpy(pri_1.cmc_labp[j], cmc_lab); /* the index for cmc_labp was changed from l to j - Prakash */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,818)J,(LABP(J,K),K=1,4) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d   ", j);
    fprintf(fp12, "%s", pri_1.cmc_labp[j]); /* the index for cmc_labp was changed from l to j - Prakash */
    fprintf(fp12, "\n");
  }
  
  /*<       IF(IUSE(J).EQ.1)CALL ERR(1) >*/
  if (net_1.iuse[j - 1] == 1) {
    err_(&c__1);
  }
  /*<       IUSE(J)=1 >*/
  net_1.iuse[j - 1] = 1;
  /* CMC       READ(5,650)(LAB(K),K=1,5),IINPP(J),IOUPP(J) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,25)J,(LAB(K),K=1,5),IINPP(J),IOUPP(J) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  pos+=5;
  pri_1.iinpp[j - 1] =  atoi(substring(buf, pos, 5)); pos+=5;
  pri_1.ioupp[j - 1] =  atoi(substring(buf, pos, 5)); pos+=5;
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d", k);
    
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%5d%5d\n",   pri_1.iinpp[j - 1],   pri_1.ioupp[j - 1] );
  }
  
  /*<       IL=IINPP(J) >*/
  il = pri_1.iinpp[j - 1];
  /*<       IF(LUSE(IL).EQ.1)CALL ERR(2) >*/
  if (net_1.luse[il - 1] == 1) {
    err_(&c__2);
  }
  /*<       LUSE(IL)=1 >*/
  net_1.luse[il - 1] = 1;
  /* CMC       READ(5,820)(LAB(K),K=1,5),ALPHA(J),DELTA(J),PMAX(J),PMIN(J), */
  /* CMC      1 LINKP(J) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  pos+=5;
  pri_1.alpha[j - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  pri_1.delta[j - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  pri_1.pmax[j - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  pri_1.pmin[j - 1] =  atof(substring(buf, pos, 5)); pos+=5;
  pri_1.linkp[j - 1] =  atoi(substring(buf, pos, 5)); pos+=5;
  
  
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,5820)(LAB(K),K=1,5),ALPHA(J),DELTA(J), */
  /* CMC      1 PMAX(J),PMIN(J), */
  /* CMC      1 LINKP(J) */
  /* CMC  5820 FORMAT(5A4,5X,4E10.2,I5) */
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "     ");
    fprintf(fp12, "%10.2e", pri_1.alpha[j - 1] );
    fprintf(fp12, "%10.2e", pri_1.delta[j - 1] );
    fprintf(fp12, "%10.2e", pri_1.pmax[j - 1]  );
    fprintf(fp12, "%10.2e", pri_1.pmin[j - 1]  );
    fprintf(fp12, "%5d",    pri_1.linkp[j - 1]);
    fprintf(fp12, "\n");
  }
  
  /*<       NPP=NPP+1 >*/
  ++npp;
  /*<       GO TO 802 >*/
  goto L802;
  
  /* CMC C***** READ ELECTRIC SECTOR DATA. */
  
  /*<   987 CALL USE (2,NPPMX) >*/
 L987:
  use_(&c__2, &nppmx);
  /* CMC       WRITE (*,*) 'Reading electric sector data ...'                    MJ060486 */
  
  /* CMC       READ(5,25)IELECS,(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,25)IELECS,(LAB(J),J=1,5) */
  fprintf(fp21,"Reading electric sector data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  invis_1.ielecs=  atoi(substring(buf, pos, 5)); pos+=5;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%5d",  invis_1.ielecs);
    
    fprintf(fp12, "%s", cmc_lab);
  }
  
  /*<       IF(IELECS.EQ.0)GO TO 989 >*/
  if (invis_1.ielecs == 0) {
    goto L989;
  }
  /*<       CALL ELECS(-1) >*/
  elecs_(&c_n1);
  /*<  989  CONTINUE >*/
 L989:
  /* CMC   989 READ(5,117) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  
  /*<       NNLNK=0 >*/
  var_1.nnlnk = 0;
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1602)LNKMX */
  if (el1_1.iecho == 0) 
    fprintf(fp12,"\n\n     MAX LINKS =%10d\n     AVAILABLE LINKS:\n", var_1.lnkmx);
  
  /*<       DO 599 J=1,LNKMX >*/
  i__1 = var_1.lnkmx;
  for (j = 1; j <= i__1; ++j) {
    /*<       IF(LUSE(J).EQ.0)GO TO 598 >*/
    if (net_1.luse[j - 1] == 0) {
      goto L598;
    }
    /*<       NNLNK=NNLNK+1 >*/
    ++var_1.nnlnk;
    /*<       GO TO 599 >*/
    goto L599;
    /*<  598  CONTINUE >*/
  L598:
    /* CMC   598 IF(IECHO.EQ.0)WRITE(12,1600)J */
    if (el1_1.iecho == 0) 
      fprintf(fp12,"     %10d\n", j);
    
    /*<   599 CONTINUE >*/
  L599:
    ;
  }
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1603)NNLNK,LNKMX */
  if (el1_1.iecho == 0) 
    fprintf(fp12,"     THERE ARE%6d  LINKS OUT OF%6d  POSSIBLE.\n\n", 
	    var_1.nnlnk,var_1.lnkmx);
  
  /* CMC C***** READ OUTPUT WRITER DATA. */
  
  /* CMC       WRITE (*,*) 'Reading output writer data ...'                      MJ060486 */
  /*<       CALL OUTW(1) >*/
  fprintf(fp21,"Reading output writer data ...\n");

  outw_(&c__1);
  
  /* CMC C***** READ CAPACITATED LINK DATA. */
  
  /* CMC       WRITE (*,*) 'Reading capacitated link data ...'                   MJ060486 */
  
  /* CMC       READ(5,10)(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1810)(LAB(J),J=1,5) */
  fprintf(fp21,"Reading capacitated link data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  if (el1_1.iecho == 0) {
      fprintf(fp12, "\n%s\n",cmc_lab);
  }
  
  /*<  1954 CONTINUE >*/
 L1954:
  /* CMC  1954 READ(5,1957)(LAB(J),J=1,5),L,IAL,CAPL2 */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1957)(LAB(J),J=1,5),L,IAL,CAPL2 */
  /* CMC  1957 FORMAT(5A4,2I5,F10.2) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  l =  atoi(substring(buf, pos, 5)); pos+=5;
  ial =  atoi(substring(buf, pos, 5)); pos+=5;
  capl2 =  atof(substring(buf, pos, 10)); pos+=10;
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "%5d", l );
    fprintf(fp12, "%5d", ial );
    fprintf(fp12, "%10.2f", capl2 );
    fprintf(fp12, "\n");
  }
  
  /* ***** IF L (LINK) = 0, END OF CAPAC LINK DATA. */
  
  /*<       IF(L.EQ.0)GO TO 1953 >*/
  if (l == 0) {
    goto L1953;
  }
  
  /* ***** CHECK THAT CAPAC LINK IS REALLY AN INPUT LINK TO SPECIFIED */
  /* ***** DECISION NODE. */
  
  /*<       CAPL(L)=CAPL2 >*/
  net_1.capl[l - 1] = capl2;
  /*<       NN=NINAL(IAL) >*/
  nn = all_1.ninal[ial - 1];
  /*<       DO 1955 J=1,NN >*/
  i__1 = nn;
for (j = 1; j <= i__1; ++j) {
    /*<       IF(L.EQ.IINAL(IAL,J)) GO TO 1956 >*/
    if (l == iinal_ref(ial, j)) {
      goto L1956;
    }
    /*<  1955 CONTINUE >*/
    /* L1955: */
  }
  /*<       CALL ERR(3) >*/
  err_(&c__3);
  /*<  1956 CONTINUE >*/
 L1956:
  /*<       GO TO 1954 >*/
  goto L1954;
  
  /*<  1953 CONTINUE >*/
 L1953:
  
  /* CMC C***** READ UP-PASS CALL SEQUENCE. */
  
  /* CMC       WRITE (*,*) 'Reading up-pass data ...'                            MJ060486 */
  /* CMC       READ(5,10)(LAB(I),I=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(I),I=1,5) */
  fprintf(fp21,"Reading up-pass data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "\n ");
    
    fprintf(fp12, "%s", cmc_lab);
    
    fprintf(fp12, "\n");
  }
  
  /*<       K=0 >*/
  k = 0;
  /*<       KWR=0 >*/
  kwr = 0;
  
  /* ***** ROW 1 IS UP-PASS DATA. */
  
  /*<  1965 K=K+1 >*/
 L1965:
  ++k;
  /* CMC       READ(5,1961)NODEL(1,K),NUMB(1,K),ISPEC(1,K),(LAB(J),J=1,5) */
  fgets(buf,sizeof(buf),fp5);pos=0;
  pos+=3;
  strcpy(invis_1.nodel[1][k], substring(buf, pos, 2)); pos+=2;
  numb_ref(1, k) =  atoi(substring(buf, pos, 5)); pos+=5;
  ispec_ref(1, k) =  atoi(substring(buf, pos, 5)); pos+=5;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1961)NODEL(1,K),NUMB(1,K),ISPEC(1,K), */
  /* CMC      1 (LAB(J),J=1,5) */
  /* CMC  1961 FORMAT(3X,A2,2I5,5A4) */
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "   ");  
    fprintf(fp12, "%s",   invis_1.nodel[1][k] );
    fprintf(fp12, "%5d", numb_ref(1, k));
    fprintf(fp12, "%5d",ispec_ref(1, k) );
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /* ***** IF CARD IS BLANK KICK OUT OF INPUT LOOP.  ELSE, COUNT ENTRY */
  /* CMC C***** AND READ NEXT CARD. */
  
  /*<       IF(NODEL(1,K).EQ.LBL)GO TO 1962 >*/
/*   if (s_cmp(nodel_ref(0, 1, k), lbl, (ftnlen)4, (ftnlen)4) == 0) { */
/*     goto L1962; */
/*   } */

  /*  if(strcmp(  invis_1.nodel[1][k], lbl)==0) */
    if(s_cmp(  invis_1.nodel[1][k], lbl, (ftnlen)4, (ftnlen)4) ==0 ) 
    goto L1962;


  /*<       IF(NODEL(1,K).NE.LWR)GO TO 1965 >*/
/*   if (s_cmp(nodel_ref(0, 1, k), lwr, (ftnlen)4, (ftnlen)4) != 0) { */
/*     goto L1965; */
/*   } */
/*  if(strcmp(invis_1.nodel[1][k], lwr)!=0)*/
  if(s_cmp(invis_1.nodel[1][k], lwr, (ftnlen)4, (ftnlen)4)!=0)
    goto L1965;
  
  /* ***** RECORD MESSAGE FOR FUTURE OUTPUT. */
  
  /*<       KWR=KWR+1 >*/
  ++kwr;
  /*<       DO 1968 JJ=1,5 >*/
  for (jj = 1; jj <= 5; ++jj) {
    /*<       LABW(1,KWR,JJ)=LAB(JJ) >*/
    labw_ref(1, kwr, jj) = net_1.lab[jj - 1];
    /*<  1968 CONTINUE >*/
    /* L1968: */
  }
  
  /*<       GO TO 1965 >*/
  goto L1965;
  
  /* ***** ASSIGN KUP THE NUMBER OF ENTRIES ON UP-PASS SEQUENCE. */
  
  /*<  1962 KUP=K-1 >*/
 L1962:
  invis_1.kup = k - 1;
  /* CMC       IF(IECHO.EQ.0)WRITE(12,9002)KUP,KWR */
  /* CMC  9002 FORMAT(' UP-PASS HAS ',I4,' CALLS INCLUDING ', */
  /* CMC      1 I4,' WRITES',//) */
  if (el1_1.iecho == 0) 
    fprintf(fp12, " UP-PASS HAS %4d CALLS INCLUDING %4d WRITES\n\n",invis_1.kup,kwr);
  
  /* CMC C***** READ DOWN-PASS CALL SEQUENCE. */
  
  /* CMC       WRITE (*,*) 'Reading down-pass data ...'                          MJ060486 */
  /* CMC       READ(5,10)(LAB(I),I=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(I),I=1,5) */
  fprintf(fp21,"Reading down-pass data ...\n");

  fgets(buf,sizeof(buf),fp5);pos=0;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "\n ");
    fprintf(fp12, "%s", cmc_lab);
    fprintf(fp12, "\n");
  }
  
  
  /*<       K=0 >*/
  k = 0;
  /*<       KWR=0 >*/
  kwr = 0;
  
  /* ***** ROW 2 IS DOWN-PASS DATA. */
  
  /*<  1963 K=K+1 >*/
 L1963:
  ++k;
  /* CMC       READ(5,1961)NODEL(2,K),NUMB(2,K),ISPEC(2,K),(LAB(J),J=1,5) */
  /* CMC       IF(IECHO.EQ.0)WRITE(12,1961)NODEL(2,K),NUMB(2,K),ISPEC(2,K), */
  /* CMC      1 (LAB(J),J=1,5) */
  
  
  fgets(buf,sizeof(buf),fp5);pos=0;
  pos+=3;
  strcpy(invis_1.nodel[2][k], substring(buf, pos, 2)); pos+=2;
  numb_ref(2, k) =  atoi(substring(buf, pos, 5)); pos+=5;
  ispec_ref(2, k) =  atoi(substring(buf, pos, 5)); pos+=5;
  strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
  
  if (el1_1.iecho == 0) {
    fprintf(fp12, "   ");  
    fprintf(fp12, "%s",  invis_1.nodel[2][k]);
    fprintf(fp12, "%5d",numb_ref(2, k));
    fprintf(fp12, "%5d",ispec_ref(2, k) );
    fprintf(fp12, "%s",cmc_lab);
    fprintf(fp12, "\n");
  }
  
  /* ***** IF CARD IS BLANK KICK OUT OF INPUT LOOP.  ELSE, COUNT ENTRY */
  /* CMC C***** AND READ NEXT CARD. */
  
  /*<       IF(NODEL(2,K).EQ.LBL)GO TO 1964 >*/
/*   if (s_cmp(nodel_ref(0, 2, k), lbl, (ftnlen)4, (ftnlen)4) == 0) { */
/*     goto L1964; */
/*   } */
/*  if(strcmp(invis_1.nodel[2][k], lbl)==0)*/
  if(s_cmp(invis_1.nodel[2][k], lbl, (ftnlen)4, (ftnlen)4)==0)
    goto L1964;
  /*<       IF(NODEL(2,K).NE.LWR)GO TO 1963 >*/
/*   if (s_cmp(nodel_ref(0, 2, k), lwr, (ftnlen)4, (ftnlen)4) != 0) { */
/*     goto L1963; */
/*   } */
/*   if(strcmp(invis_1.nodel[2][k],lwr)!=0) */
  if(s_cmp(invis_1.nodel[2][k],lwr, (ftnlen)4, (ftnlen)4)!=0)
    goto L1963;
  
  /* ***** RECORD MESSAGE FOR FUTURE OUTPUT. */
  
  /*<       KWR=KWR+1 >*/
  ++kwr;
  /*<       DO 1969 JJ=1,5 >*/
  for (jj = 1; jj <= 5; ++jj) {
    /*<       LABW(2,KWR,JJ)=LAB(JJ) >*/
    labw_ref(2, kwr, jj) = net_1.lab[jj - 1];
    /*<  1969 CONTINUE >*/
    /* L1969: */
  }
  
  /*<       GO TO 1963 >*/
  goto L1963;
  
  /* ***** ASSIGN KDWN THE NUMBER OF ENTRIES ON DOWN-PASS SEQUENCE. */
  
  /*<  1964 KDWN=K-1 >*/
 L1964:
  invis_1.kdwn = k - 1;
  /* CMC       IF(IECHO.EQ.0)WRITE(12,9003)KDWN,KWR */
  /* CMC  9003 FORMAT(' DOWN-PASS HAS ',I4,' CALLS INCLUDING ', */
  /* CMC      1 I4,' WRITES',//) */
  if (el1_1.iecho == 0) 
    fprintf(fp12, " DOWN-PASS HAS %4d CALLS INCLUDING %4d WRITES\n\n",invis_1.kdwn,kwr);
  
  /* ***** SAVE QUANTITIES ON RESOURCE PROCESS OUTPUT LINKS. */
  
     /*<       IF(NNREP.EQ.0)GO TO 7114 >*/
     if (var_1.nnrep == 0) {
       goto L7114;
     }
     /*<       DO 105 I=1,NRSMX >*/
     i__1 = var_1.nrsmx;
     for (i__ = 1; i__ <= i__1; ++i__) {
       /*<       L=IOURS(I) >*/
       l = res_1.iours[i__ - 1];
       /*<       IF(L.EQ.0)GO TO 105 >*/
       if (l == 0) {
	 goto L105;
       }
       /*<       QT(I)=Q(L) >*/
       res_1.qt[i__ - 1] = net_1.q[l - 1];
       /*<       QNT(I)=Q(L)                                                        >*/
       saveimp_1.qnt[i__ - 1] = net_1.q[l - 1];
       /*<   105 CONTINUE >*/
     L105:
       ;
     }
     
     /* ***** SAVE RENEWABLE RESOURCE QUANTITIES. */
     
     /*<  7114 IF(NNRNP.EQ.0)GO TO 199 >*/
   L7114:
     if (nnrnp == 0) {
       goto L199;
     }
     /*<       DO 7113 I=1,NRNMX >*/
     i__1 = var_1.nrnmx;
     for (i__ = 1; i__ <= i__1; ++i__) {
       /*<       L=IOURN(I) >*/
       l = ren_1.iourn[i__ - 1];
       /*<       IF(L.EQ.0)GO TO 7113 >*/
       if (l == 0) {
	 goto L7113;
       }
       /*<       IA=NRSMX+I >*/
       ia = var_1.nrsmx + i__;
       /*<       QT(IA)=Q(L) >*/
       res_1.qt[ia - 1] = net_1.q[l - 1];
       /*<       QNT(IA)=Q(L)                                                       >*/
       saveimp_1.qnt[ia - 1] = net_1.q[l - 1];
       /*<  7113 CONTINUE >*/
     L7113:
       ;
     }
     
     /* ***** INPUT INDICATOR FOR RES MODE. */
     
     /*<   199 CONTINUE >*/
   L199:
     
     /* ***** ASSIGN 0 PRICES TO STOCKPILE LINKS. */
     
     /*<       IF(NNST.EQ.0)RETURN >*/
     if (var_1.nnst == 0) {
       return 0;
     }
     /*<       DO 307 I=1,NNST >*/
     i__1 = var_1.nnst;
     for (i__ = 1; i__ <= i__1; ++i__) {
       /*<       L=IOUST(I) >*/
       l = stk_1.ioust[i__ - 1];
       /*<       P(L)=0. >*/
       net_1.p[l - 1] = 0.f;
       /*<   307 CONTINUE >*/
       /* L307: */
     }
     /*<       RETURN >*/

     return 0;
     
     
     
     
     /* CMC C**** READ CHANGES IN DATA FOR NEXT TIME PERIOD( Special Events). */
     
     /*<   308 CONTINUE >*/
   L308:
     
     /*<       IERS=0 >*/
     var_1.iers = 0;
     /* CMC       READ(5,10)(LAB(I),I=1,5) */
     /* CMC       IF(IECHO.EQ.0)WRITE(12,10)(LAB(I),I=1,5) */
     fgets(buf,sizeof(buf),fp5);pos=0;
     strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;
 
     if (el1_1.iecho == 0) {
       fprintf(fp12, "\n ");
	 fprintf(fp12, "%s", cmc_lab);
       
       fprintf(fp12, "\n");
     }
    
     /*<  2001 CONTINUE >*/
   L2001:
     /* CMC  2001 READ(5,9990)(LAB(J),J=1,5),LPAB,NUM,LITM,ILOC,VAL */
     /* CMC  9990 FORMAT(5A4,1X,A4,I5,1X,A4,I5,F10.2) */
     fgets(buf,sizeof(buf),fp5);pos=0;
     strcpy(cmc_lab, substring(buf, pos, 20)); pos+=20;

     pos+=1;

     /*    strcpy(charbuf, (char*)substring(buf, pos, 4)); pos+=4;*/
     /*     for(cpt=1; cpt<=4;cpt++) lpab[cpt-1] = charbuf[cpt-1];*/
     s_copy(lpab,(char*)substring(buf, pos, 4), (ftnlen)4, (ftnlen)4); pos+=4;
     num =  atoi(substring(buf, pos, 5)); pos+=5;
     pos+=1;

     /*   strcpy( charbuf, (char *)substring(buf, pos, 4)); pos+=4;*/
     /*     for(cpt=1; cpt<=4;cpt++) litm[cpt-1] = charbuf[cpt-1];*/
     s_copy(litm,(char*)substring(buf, pos, 4), (ftnlen)4, (ftnlen)4 ); pos+=4;

     iloc =  atoi(substring(buf, pos, 5)); pos+=5;
     val=  atof(substring(buf, pos, 10)); pos+=10;
	 

     /* CMC       IF(IECHO.EQ.0)WRITE(12,9949)(LAB(J),J=1,5),LPAB,NUM,LITM, */
     /* CMC      1 ILOC,VAL */
     /* CMC  9949 FORMAT(5A4,1X,A4,I5,1X,A4,I5,F15.4) */
     
     if (el1_1.iecho == 0) {
       fprintf(fp12, "%s", cmc_lab);
       fprintf(fp12, " %c%c%c%c", lpab[0], lpab[1], lpab[2], lpab[3]);
       fprintf(fp12, "%5d", num);
       fprintf(fp12, " %c%c%c%c", litm[0], litm[1], litm[2], litm[3]);
       fprintf(fp12, "%5d",iloc);
       fprintf(fp12, "%15.4f",val);
       fprintf(fp12, "\n");
     }
     
    
     /* ***** IF NUM IS 0 CARD IS BLANK, END OF EVENT INPUT */
     /* ***** FOR THIS YEAR. */
     
     /*<       IF(NUM.EQ.0)GO TO 1959 >*/
     if (num == 0) {
       goto L1959;
     }

     /*<       IF(LPAB.NE.LRS)GO TO 2002 >*/
     if (s_cmp(lpab, lrs, (ftnlen)4, (ftnlen)4) != 0) {      
		 goto L2002;
     } 

     /*<       LINK=IOURS(NUM) >*/
     link = res_1.iours[num - 1];
     /*<       IF(LITM.EQ.LCAPL)CAPL(LINK)=VAL >*/
     if (s_cmp(litm, lcapl, (ftnlen)4, (ftnlen)4) == 0) {
       net_1.capl[link - 1] = val;
     }
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /*<  2002 IF(LPAB.NE.LRN)GO TO 2003 >*/
   L2002:
     if (s_cmp(lpab, lrn, (ftnlen)4, (ftnlen)4) != 0) {
		 goto L2003;
     }

     /*<       LINK=IOURN(NUM) >*/
     link = ren_1.iourn[num - 1];
     /*<       IF(LITM.EQ.LCAPL)CAPL(LINK)=VAL >*/
     if (s_cmp(litm, lcapl, (ftnlen)4, (ftnlen)4) == 0) {
       net_1.capl[link - 1] = val;
     }
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /*<  2003 IF(LPAB.NE.LAL)GO TO 2004 >*/
   L2003:
     if (s_cmp(lpab, lal, (ftnlen)4, (ftnlen)4) != 0) {
       goto L2004;
     }
     /*<       IF(LITM.EQ.LPRI)IALPR(NUM,ILOC)=VAL >*/
     if (s_cmp(litm, lpri, (ftnlen)4, (ftnlen)4) == 0) {
       ialpr_ref(num, iloc) = val;
     }
     
     /* * INIT JALPR */
     /*<       DO 889 I=1,10 >*/
     for (i__ = 1; i__ <= 10; ++i__) {
       /*<       JALPR(I)=0 >*/
       jalpr[i__ - 1] = 0;
       /*<   889 CONTINUE >*/
       /* L889: */
     }
     /* * ASSIGN NONZERO VALUES IN IALPR TO JALPR */
     /*<       NN=0 >*/
     nn = 0;
     /*<       DO 887 I=1,10 >*/
     for (i__ = 1; i__ <= 10; ++i__) {
       /*<       IF (IALPR(NUM,I).EQ.0)GO TO 887 >*/
       if (ialpr_ref(num, i__) == 0) {
	 goto L887;
       }
       /*<       NN=NN+1 >*/
       ++nn;
       /*<       JALPR(NN)=IALPR(NUM,I) >*/
	   /* code changed as indicated in the next line -Prakash */
       /*jalpr[nn - 1] = ialpr_ref(num, i__);*/ 
	   jalpr[i__ - 1] = ialpr_ref(num, i__);
       /*<   887 CONTINUE >*/
     L887:
       ;
     }
     /* * REASSIGN JALPR THAT EXCLUDES ZEROS */
     /*<       NALPR(NUM)=NN >*/
     all_1.nalpr[num - 1] = nn;
     /*<       DO 890 I=1,10 >*/
     for (i__ = 1; i__ <= 10; ++i__) {
       /*<       IALPR(NUM,I)=JALPR(I) >*/
       ialpr_ref(num, i__) = jalpr[i__ - 1];
       /*<   890 CONTINUE >*/
       /* L890: */
     }
     
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /*<  2004 IF(LPAB.NE.LPR)GO TO 2005 >*/
   L2004:
     if (s_cmp(lpab, lpr, (ftnlen)4, (ftnlen)4) != 0) {
       goto L2005;
     }
     /*<       LINK=IOUPR(NUM) >*/
     link = pro_1.ioupr[num - 1];
     /*<       IF(LITM.EQ.LOM)OM(NUM)=VAL >*/
     if (s_cmp(litm, lom, (ftnlen)4, (ftnlen)4) == 0) {
       pro_1.om[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LEFF)EFF(NUM)=VAL >*/
     if (s_cmp(litm, leff, (ftnlen)4, (ftnlen)4) == 0) {
       pro_1.eff[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LTCI)TCI(NUM)=VAL >*/
     if (s_cmp(litm, ltci, (ftnlen)4, (ftnlen)4) == 0) {
       pro_1.tci[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCAPM)CAPM(NUM)=VAL >*/
     if (s_cmp(litm, lcapm, (ftnlen)4, (ftnlen)4) == 0) {
       pro_1.capm[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCF)CF(NUM)=VAL >*/
     if (s_cmp(litm, lcf, (ftnlen)4, (ftnlen)4) == 0) {
       pro_1.cf[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LLIFE)LIFE(NUM)=VAL >*/
     if (s_cmp(litm, llife, (ftnlen)4, (ftnlen)4) == 0) {
       pro_1.life[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LIR)RIR(NUM)=VAL >*/
     if (s_cmp(litm, lir, (ftnlen)4, (ftnlen)4) == 0) {
       pro_1.rir[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCAPL)CAPL(LINK)=VAL >*/
     if (s_cmp(litm, lcapl, (ftnlen)4, (ftnlen)4) == 0) {
       net_1.capl[link - 1] = val;
     }
     /*<    >*/
     r__1 = pro_1.rir[num - 1] + 1.f;
     r__2 = pro_1.rir[num - 1] + 1.f;
     crf = pro_1.rir[num - 1] * pow_ri(&r__1, &pro_1.life[num - 1]) / (pow_ri(&
									      r__2, &pro_1.life[num - 1]) - 1.f);
     /*<    >*/
     if (pro_1.capm[num - 1] * pro_1.cf[num - 1] != 0.f) {
       pro_1.cc[num - 1] = pro_1.tci[num - 1] * crf / (pro_1.capm[num - 1] * 
						       pro_1.cf[num - 1]);
     }
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /*<  2005 IF(LPAB.NE.LMI)GO TO 2006 >*/
   L2005:
     if (s_cmp(lpab, lmi, (ftnlen)4, (ftnlen)4) != 0) {
       goto L2006;
     }
     /*<       LINK=IOUMI(NUM) >*/
     link = min_1.ioumi[num - 1];
     /*<       IF(LITM.EQ.LOM)OMM(NUM)=VAL >*/
     if (s_cmp(litm, lom, (ftnlen)4, (ftnlen)4) == 0) {
       min_1.omm[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LIO)RIO(NUM,ILOC)=VAL >*/
     if (s_cmp(litm, lio, (ftnlen)4, (ftnlen)4) == 0) {
       rio_ref(num, iloc) = val;
     }
     /*<       IF(LITM.EQ.LTCI)TCIM(NUM)=VAL >*/
     if (s_cmp(litm, ltci, (ftnlen)4, (ftnlen)4) == 0) {
       min_1.tcim[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCAPM)CAPMM(NUM)=VAL >*/
     if (s_cmp(litm, lcapm, (ftnlen)4, (ftnlen)4) == 0) {
       min_1.capmm[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCF)CFM(NUM)=VAL >*/
     if (s_cmp(litm, lcf, (ftnlen)4, (ftnlen)4) == 0) {
       min_1.cfm[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LLIFE)LIFEM(NUM)=VAL >*/
     if (s_cmp(litm, llife, (ftnlen)4, (ftnlen)4) == 0) {
       min_1.lifem[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LIR)RIRM(NUM)=VAL >*/
     if (s_cmp(litm, lir, (ftnlen)4, (ftnlen)4) == 0) {
       min_1.rirm[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCAPL)CAPL(LINK)=VAL >*/
     if (s_cmp(litm, lcapl, (ftnlen)4, (ftnlen)4) == 0) {
       net_1.capl[link - 1] = val;
     }
     /*<    >*/
     r__1 = min_1.rirm[num - 1] + 1.f;
     r__2 = min_1.rirm[num - 1] + 1.f;
     crf = min_1.rirm[num - 1] * pow_ri(&r__1, &min_1.lifem[num - 1]) / (
									 pow_ri(&r__2, &min_1.lifem[num - 1]) - 1.f);
     /*<    >*/
     if (min_1.capmm[num - 1] * min_1.cfm[num - 1] != 0.f) {
       min_1.ccm[num - 1] = min_1.tcim[num - 1] * crf / (min_1.capmm[num - 1]
							 * min_1.cfm[num - 1]);
     }
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /*<  2006 IF(LPAB.NE.LRE)GO TO 2007 >*/
   L2006:
     if (s_cmp(lpab, lre, (ftnlen)4, (ftnlen)4) != 0) {
       goto L2007;
     }
     /*<       LINK=IINRE(NUM,1) >*/
     link = iinre_ref(num, 1);
     /*<       IF(LITM.EQ.LSIZE)IORDC(NUM)=VAL >*/
     if (s_cmp(litm, lsize, (ftnlen)4, (ftnlen)4) == 0) {
       ref_1.iordc[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LOM)OMR(NUM)=VAL >*/
     if (s_cmp(litm, lom, (ftnlen)4, (ftnlen)4) == 0) {
       ref_1.omr[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LSLAT)SLATE(NUM,ILOC)=VAL >*/
     if (s_cmp(litm, lslat, (ftnlen)4, (ftnlen)4) == 0) {
       slate_ref(num, iloc) = val;
     }
     /*<       IF(LITM.EQ.LTCI)TCIR(NUM)=VAL >*/
     if (s_cmp(litm, ltci, (ftnlen)4, (ftnlen)4) == 0) {
       ref_1.tcir[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCAPM)CAPMR(NUM)=VAL >*/
     if (s_cmp(litm, lcapm, (ftnlen)4, (ftnlen)4) == 0) {
       ref_1.capmr[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCF)CFR(NUM)=VAL >*/
     if (s_cmp(litm, lcf, (ftnlen)4, (ftnlen)4) == 0) {
       ref_1.cfr[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LLIFE)LIFER(NUM)=VAL >*/
     if (s_cmp(litm, llife, (ftnlen)4, (ftnlen)4) == 0) {
       ref_1.lifer[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LIR)RIRR(NUM)=VAL >*/
     if (s_cmp(litm, lir, (ftnlen)4, (ftnlen)4) == 0) {
       ref_1.rirr[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LCAPL)CAPL(LINK)=VAL >*/
     if (s_cmp(litm, lcapl, (ftnlen)4, (ftnlen)4) == 0) {
       net_1.capl[link - 1] = val;
     }
     /*<       IF(LITM.EQ.LPFF)PFF(NUM)=VAL >*/
     if (s_cmp(litm, lpff, (ftnlen)4, (ftnlen)4) == 0) {
       ref_1.pff[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LPRAT)PRAT(NUM,ILOC)=VAL >*/
     if (s_cmp(litm, lprat, (ftnlen)4, (ftnlen)4) == 0) {
       prat_ref(num, iloc) = val;
     }
     /*<       IF(LITM.EQ.LSTOC)ISTCK(NUM,ILOC)=VAL >*/
     if (s_cmp(litm, lstoc, (ftnlen)4, (ftnlen)4) == 0) {
       istck_ref(num, iloc) = val;
     }
     /*<       IF(LITM.EQ.LEXCS)IXCES(NUM,ILOC)=VAL >*/
     if (s_cmp(litm, lexcs, (ftnlen)4, (ftnlen)4) == 0) {
       ixces_ref(num, iloc) = val;
     }
     /*<       IF(LITM.EQ.LCNTL)ICNTL(NUM,ILOC)=VAL >*/
     if (s_cmp(litm, lcntl, (ftnlen)4, (ftnlen)4) == 0) {
       icntl_ref(num, iloc) = val;
     }
     /*<       IF(LITM.EQ.LREMU)REMUL(NUM,ILOC)=VAL >*/
     if (s_cmp(litm, lremu, (ftnlen)4, (ftnlen)4) == 0) {
       remul_ref(num, iloc) = val;
     }
     /*<    >*/
     r__1 = ref_1.rirr[num - 1] + 1.f;
     r__2 = ref_1.rirr[num - 1] + 1.f;
     crf = ref_1.rirr[num - 1] * pow_ri(&r__1, &ref_1.lifer[num - 1]) / (
									 pow_ri(&r__2, &ref_1.lifer[num - 1]) - 1.f);
     /*<    >*/
     if (ref_1.capmr[num - 1] * ref_1.cfr[num - 1] != 0.f) {
       ref_1.ccr[num - 1] = ref_1.tcir[num - 1] * crf / (ref_1.capmr[num - 1]
							 * ref_1.cfr[num - 1]);
     }
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /*<  2007 IF(LPAB.NE.LPP)GO TO 2008 >*/
   L2007:
     if (s_cmp(lpab, lpp, (ftnlen)4, (ftnlen)4) != 0) {
       goto L2008;
     }
     /*<       IF(LITM.EQ.LALPH)ALPHA(NUM)=VAL >*/
     if (s_cmp(litm, lalph, (ftnlen)4, (ftnlen)4) == 0) {
       pri_1.alpha[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LDELT)DELTA(NUM)=VAL >*/
     if (s_cmp(litm, ldelt, (ftnlen)4, (ftnlen)4) == 0) {
       pri_1.delta[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LPMAX)PMAX(NUM)=VAL >*/
     if (s_cmp(litm, lpmax, (ftnlen)4, (ftnlen)4) == 0) {
       pri_1.pmax[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LPMIN)PMIN(NUM)=VAL >*/
     if (s_cmp(litm, lpmin, (ftnlen)4, (ftnlen)4) == 0) {
       pri_1.pmin[num - 1] = val;
     }
     /*<       IF(LITM.EQ.LLINP)LINKP(NUM)=VAL >*/
     if (s_cmp(litm, llinp, (ftnlen)4, (ftnlen)4) == 0) {
       pri_1.linkp[num - 1] = val;
     }
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /*<  2008 IF(LPAB.NE.LCA)GO TO 2009 >*/
   L2008:
     if (s_cmp(lpab, lca, (ftnlen)4, (ftnlen)4) != 0) {
       goto L2009;
     }
     /*<       IF(LITM.EQ.LCAPL)CAPL(NUM)=VAL >*/
     if (s_cmp(litm, lcapl, (ftnlen)4, (ftnlen)4) == 0) {
       net_1.capl[num - 1] = val;
     }
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /*     JLin 1/97: special events for loading order value */
     
     /*< 2009  IF(LPAB.NE.LEL) GO TO 2001                                         >*/
   L2009:
     if (s_cmp(lpab, lel, (ftnlen)4, (ftnlen)4) != 0) {
       goto L2001;
     }
     /*<         IF(LITM.EQ.LLOV) THEN                                            >*/
     if (s_cmp(litm, llov, (ftnlen)4, (ftnlen)4) == 0) {
       /*<                 optionalLOV(NUM)=VAL                                     >*/
        elec4_1.optionallov[num - 1] = val; 
       /*<                 ispecLOV(NUM) = 1                                        >*/
        elec4_1.ispeclov[num - 1] = 1; 
       /* CMC                 write(*,*) optionalLOV(NUM), NUM */
	
		/* I HAVE TO IMPLEMENT SOME CHNAGES IN THE CODE BELOW ACCORDING TO THE 
			LATESt FORTRAN CODE - Prakash 
		
		  for(j=1; j<=300;j++){
			 if (iProcNUM(j-1) == num) {
				 go to 2011;
			 }
		 } 

	L2011:
		elec4_1.optionallov[j]=val    
		elec4_1.ispeclov[j] = 1         */                                	

       /*<         ELSE IF(LITM.EQ.LMLD) THEN                                       >*/
     } else if (s_cmp(litm, lmld, (ftnlen)4, (ftnlen)4) == 0) {
       /*<                 XMLOD=VAL                                                >*/
       elec4_1.xmlod = val;
       /*<         ELSE IF(LITM.EQ.LALF) THEN                                       >*/
     } else if (s_cmp(litm, lalf, (ftnlen)4, (ftnlen)4) == 0) {
       /*<                 XLFAC=VAL                                                >*/
       elec4_1.xlfac = val;
       /*<         END IF                                                           >*/
     }
     /*<       GO TO 2001 >*/
     goto L2001;
     
     /* ***** END OF EVENT INPUT DATA LOOP. */
     
     
     
     
     /* CMC   117 FORMAT(2X) */
     /* CMC   980 FORMAT(1H1,'NO DATA CHANGES IN PERIOD ',I6) */
     /* CMC   118 FORMAT(5A4,F10.3,3X,3A4) */
     /* CMC   650 FORMAT(5A4,5X,11I5) */
     /* CMC    10 FORMAT(5A4,I10,I5) */
     /* CMC    25 FORMAT(I5,5A4,11I5) */
     /* CMC  7070 FORMAT(5A4,E10.2,I10) */
     /* CMC    17 FORMAT(5A4,5E10.2) */
     /* CMC C   17 FORMAT(5A4,E10.2,(1PE10.0))                                       JT8/89 */
     /* CMC   319 FORMAT(5A4,5E10.2)                                                 JT8/89 */
     /* CMC   617 FORMAT(5A4,5E5.2) */
     /* CMC    18 FORMAT(5A4,10X,10I5) */
     /* CMC    14 FORMAT(5A4,5X,2F5.2,2E10.2,F5.2,I5,F5.2,E10.2) */
     /* CMC C   14 FORMAT(5A4,5X,2F5.2,2E10.2,F5.2,I5,F5.2,(1PE10.0))                JT8/89 */
     /* CMC    20 FORMAT(5A4,5X,4F5.2,6I5) */
     /* CMC   820 FORMAT(5A4,5X,4F5.2,I5,F5.2) */
     /* CMC  9200 FORMAT(5A4,5X,4F5.2,2I5,F5.1,2I5) */
     /* CMC   918 FORMAT(I5,3X,3A4,I5,2F10.2) */
     /* CMC   818 FORMAT(I5,3X,4A4,1X,I5,2F10.2) */
     /* CMC   819 FORMAT(I5,3X,4A4,1X,I5,2F10.2,1F10.7,I10)                         BPH10-92 */
     /* CMC   953 FORMAT(5A4,5X,F5.2,2E10.2,F5.2,I5,F5.2,E10.2) */
     /* CMC C  953 FORMAT(5A4,5X,F5.2,2E10.2,F5.2,I5,F5.2,(1PE10.0))                  JT8/89 */
     /* CMC  1317 FORMAT(5A4,10I5) */
     /* CMC   317 FORMAT(5A4,10X,10F5.3) */
     /* CMC   318 FORMAT(5A4,10X,10F5.2) */
     /* CMC  1318 FORMAT(5A4,10F5.2) */
     /* CMC   102 FORMAT(5A4,I10,2F10.3) */
     /* CMC  1602 FORMAT(//,5X,'MAX LINKS =',I10,/,5X,'AVAILABLE LINKS:') */
     /* CMC  1600 FORMAT(5X,I10) */
     /* CMC  1603 FORMAT(5X,'THERE ARE',I6,2X,'LINKS OUT OF',I6,2X, */
     /* CMC      1 'POSSIBLE.',//) */
     /* CMC  4907 FORMAT(A2,A3,25I3,/,5X,25I3,/,5X,25I3) */
     
     /*<  1959 IF(IERS.EQ.0)GO TO 1989 >*/
   L1959:
     if (var_1.iers == 0) {
       goto L1989;
     }
     /* CMC       WRITE(12,1960)IERS */
     /* CMC       WRITE(*,1960)IERS */
     /* CMC  1960 FORMAT(5X,'********  TERMINATION DUE TO',I5,2X,' ERRORS IN ', */
     /* CMC      1 /,5X,'INPUT DATA.  SEE INPUT DATA ECHO FOR ERRORS.') */
     fprintf(fp12, "     ********  TERMINATION DUE TO%5d   ERRORS IN \n", var_1.iers);
     fprintf(fp12, "     INPUT DATA.  SEE INPUT DATA ECHO FOR ERRORS.\n");
     fprintf(fp21, "Error: Termination due to%5d   errors in \n", var_1.iers);
     fprintf(fp21, "       input data.  See input data echo for errors.\n");
     
     
     
     
     /*<       STOP >*/
     s_stop("", (ftnlen)0);
     
     /*<  1989 CONTINUE >*/
   L1989:
     /*<       RETURN >*/
     return 0;
     
     /*<       END >*/
   } /* input_ */
     



/* #undef laba_ref */
#undef rio_ref
#undef icntl_ref
#undef remul_ref
#undef slate_ref
#undef ixces_ref
#undef istck_ref
#undef ioure_ref
#undef ialpr_ref
#undef ioual_ref
#undef iinre_ref
#undef iinmi_ref
#undef iinal_ref
#undef prat_ref
#undef labw_ref
/* #undef labs_ref */
/* #undef labr_ref */
/* #undef labp_ref */
/* #undef labn_ref */
/* #undef labm_ref*/
/* #undef labe_ref */
/* #undef labd_ref */
/* #undef labc_ref */
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
