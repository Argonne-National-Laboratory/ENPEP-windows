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

/* alcheck.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
   -lf2c -lm   (in that order)
   */
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "cmc_f2c.h"

#include "f2c.h"

FILE *fp1, *fp2, *fp3, *fp4;
/*  ALLOCATION CHECK */
/*  Check BALANCE output files to see whether the sum of input link */
/*  quantities going into allocation nodes and refinery nodes */
/*  equals the sum of output link quantities */
/*  A.A.N 1/96 */

/* Infile 1 = b024???.dat  Balance output file    Allocation Node Link Lists */
/* Infile 2 = balim???.dat   "       "     "      Link Quantities */
/* Infile 3 = b029???.dat    "       "     "      Refinery Node Link Lists */
/* Infile 4 = b051???.dat    "       "     "      "Special Events" file */
/* Output file =  alcheck.dat */
/* Modified by J. Lin 4/96 to fit in the balance main program */
/* Append the results on time.out */
/*<        subroutine alcheck() >*/
/* Subroutine */ int alcheck_(void)
{
  FILE *fp1, *fp2, *fp3, *fp4, *fp7, *fp21;
  int pos;
  char buf[1024];
  float cmc_temp[20];
  int cmc_itemp[20];
  int cmc_i, cmc_nrows, cmc_ct, base_yr;
  
  /* System generated locals */
  integer i__1, i__2;
  real r__1;
  
  /* Builtin functions */
  /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
  integer s_cmp(char *, char *, ftnlen, ftnlen);
  
  /* Local variables */
  static integer iref, ninl;
  static real temp[10];
  static integer noml;
  static real rats[65934]	/* was [111][99][6] */;
  static integer linkouts[594]	/* was [99][6] */, i__, j, k, l, m, 
  jnode, ilink, iyear, mlink, jyear;
  static real ratio, a1, a2;
  static integer nskip, nerrs, k1;
  static real totin[111];
  static integer irows;
  static real x1, x2, x3;
  static integer ii, jj, kl, ll, ml;
  static char extyp1[3], extyp2[5];
  static integer kp, iy;
  static char inline__[80];

  static integer ieyear, irnode[99], irlink[99], isyear, olinks[14985]	
    /* was [999][15] */, nyears;
  static char infile1[30], infile2[30], infile3[30], infile4[30];
  static real totout[111], allinks[110889]	/* was [999][111] */;
  static char outfile[30];
  static integer inlinks[14985]	/* was [999][15] */;
  
  static integer k2;
  char desc[16];

  char refnode[99][21];
  static char iline[80];
double x1x2;
#define rats_ref(a_1,a_2,a_3) rats[((a_3)*99 + (a_2))*111 + a_1 - 13080]
#define linkouts_ref(a_1,a_2) linkouts[(a_2)*99 + a_1 - 100]
#define olinks_ref(a_1,a_2) olinks[(a_2)*999 + a_1 - 1000]

#define allinks_ref(a_1,a_2) allinks[(a_2)*999 + a_1 - 1978021]
#define inlinks_ref(a_1,a_2) inlinks[(a_2)*999 + a_1 - 1000]


  /*<        dimension allinks(999,1980:2090) >*/
  /*<        character*30 infile1,infile2,outfile,infile3,infile4 >*/
  /*<        character*15 desc >*/
  /*<        character*20 refnode(99) >*/
  /*<        character*80 inline >*/
  /*<        character*2 extyp1 >*/
  /*<        character*4 extyp2 >*/
  /*<        integer skipnodes,irnode(99) >*/
  /*<        integer inlinks(999,15),olinks(999,15),linkouts(99,6),irlink(99) >*/
  /*<        real temp(10),rats(1980:2090,99,6) >*/
  /*<        real totin(1980:2090), totout(1980:2090) >*/
  /*       common /a1/skipnodes(10) */
  /*<        isyear=1980 >*/
  isyear = 1980;
  /*<        ieyear=2090 >*/
  ieyear = 2090;
  /*       outfile='alcheck.dat'                                           JL 4/96 */
  /*       infile1(1:4)='B024'                                             JL 4/96 */
  /*       infile2(1:5)='balim.dat'                                        JL 4/96 */
  /*       infile3(1:4)='b029'                                             JL 4/96 */
  /*       infile4(1:4)='b051'                                             JL 4/96 */
  /*<        outfile='time.out'                                                >*/
  s_copy(outfile, "time.out", (ftnlen)30, (ftnlen)8);
  /*<        infile1='B024.dat'                                                >*/
  s_copy(infile1, "B024.dat", (ftnlen)30, (ftnlen)8);
  /*<        infile2='balim.dat'                                               >*/
  s_copy(infile2, "balim.dat", (ftnlen)30, (ftnlen)9);
  /*<        infile3='b029.dat'                                                >*/
  s_copy(infile3, "b029.dat", (ftnlen)30, (ftnlen)8);
  /*<        infile4='b051.dat'                                                >*/
  s_copy(infile4, "b051.dat", (ftnlen)30, (ftnlen)8);

  /* CMC        open(unit=7,file=outfile,ACCESS='APPEND', status='unknown') */
  
  if((fp7=fopen("./time.out", "a"))==NULL){
    fprintf(fp21, "Error: Couldnt open alcheck.dat\n");
    exit(0);
  }

  /* CMC        WRITE(7,*) */
  /* CMC        WRITE(7,*) */
  /* CMC        WRITE(7,*)'       **********************************************'JL 4/96 */
  /* CMC        WRITE(7,*)'       *                                            *' */
  /* CMC        WRITE(7,*)'       *                                            *' */
  /* CMC        WRITE(7,*)'       *     CHECK ALLOCATION NODE CONSISTENCY      *'JL 4/96 */
  /* CMC        WRITE(7,*)'       *                                            *' */
  /* CMC        WRITE(7,*)'       *                                            *' */
  /* CMC        WRITE(7,*)'       **********************************************'JL 4/96 */
  /* CMC        WRITE(7,*) */
  /* CMC        WRITE(7,*) */
  
  fprintf(fp7, "\n");
  fprintf(fp7, "\n");
  fprintf(fp7, "       **********************************************\n");
  fprintf(fp7, "       *                                            *\n");
  fprintf(fp7, "       *                                            *\n");
  fprintf(fp7, "       *     CHECK ALLOCATION NODE CONSISTENCY      *\n");
  fprintf(fp7, "       *                                            *\n");
  fprintf(fp7, "       *                                            *\n");
  fprintf(fp7, "       **********************************************\n");
  fprintf(fp7, "\n");
  fprintf(fp7, "\n");
  
  /*<        nskip = 0                                                         >*/
  nskip = 0;
  
  /* CMC        open(unit=1,file=infile1,status='unknown') */
  /* CMC        open(unit=2,file=infile2,status='unknown') */
  /* CMC        open(unit=3,file=infile3,status='unknown') */
  /* CMC        open(unit=4,file=infile4,status='unknown') */
  if((fp1=fopen("./b024.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open b024.dat \n" );
    exit(0);
  }
  if((fp2=fopen("./balim.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open balim.dat \n" );
    exit(0);
  }
  if((fp3=fopen("./b029.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open b029.dat \n" );
    exit(0);
  }
  if((fp4=fopen("./b051.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open b051.dat \n" );
    exit(0);
  }
  
  /*                                                                       JL 4/96 */
  /* Read BALIM file and get quantities for each link,year */
  /* CMC        read(2,*) iyear,nyears */
  fgets(buf, sizeof(buf), fp2);
  sscanf(buf, "%d%d", &iyear, &nyears);
  
  
  /* Determine number of rows */
  
  /*<        irows=int(nyears/10.0) + 1 >*/

	/* If the no. of years is exactly divisible by 10
	then we should not add 1 to no. of rows  -  Prakash */

  if ( (nyears % 10) > 0)
	irows = (integer) (nyears / 10.f) + 1;
  else
	irows = (integer) (nyears / 10.f);

  /*<        mlink = 0 >*/
  mlink = 0;
  /*<        do 1000 i=1,999999 >*/
  for (i__ = 1; i__ <= 999999; ++i__) {
    /*<        do 2000 j=1,irows >*/
    i__1 = irows;
    for (j = 1; j <= i__1; ++j) {
      /*<         if (j.eq.1) then >*/
      /* CMC        read(2,*,end=12000) ilink,(temp(k1),k1=iyear,iyear+9) */
      if (j == 1) {

	if(feof(fp2))
	  goto L12000;

	  fgets(buf, sizeof(buf), fp2);pos=0;
	  cmc_ct = sscanf(buf, "%d%f%f%f%f%f%f%f%f%f%f", &ilink,
			    &cmc_temp[0], &cmc_temp[1], &cmc_temp[2], 
			    &cmc_temp[3], &cmc_temp[4],
			    &cmc_temp[5], &cmc_temp[6], &cmc_temp[7], 
			    &cmc_temp[8], &cmc_temp[9]);

	  if (cmc_ct == -1) /* balim breakline between quantity and price */
	    goto L12000;

      /*<        if (ilink.gt.mlink) then >*/
      /*<         do 2050 k1=iyear,iyear +9 >*/
      /*<          allinks(ilink,k1) = temp(k1) >*/
      /*< 2050    continue >*/
      /* L2050: */
      /*<         endif >*/
      
      if (ilink > mlink) {
	base_yr = ( (j-1) * 10 )+ iyear;
	for (cmc_i = 0; cmc_i < 10; ++cmc_i) 
	  allinks_ref(ilink, (base_yr + cmc_i) ) = cmc_temp[cmc_i];
      }
	
	/* Check for end of quantity section - price info starts when */
	/* link numbers go back to beginning */
	/*<          if (ilink.eq.0.or.ilink .le. mlink) goto 12000 >*/
      if (ilink == 0 || ilink <= mlink) {
	goto L12000;
      }
	/*<              else  >*/
      } else {
	/*<          if (j.eq.2) then  (or j.eq.3) >*/
	
	/* it is possible to have j greater than 3 ! - prakash */
	/* if (j == 2 || j==3) { */
	if (j >1) {
	  /* CMC          read(2,*,end=12000) (allinks(ilink,k2),k2=k1,k1+9) */
	  fgets(buf, sizeof(buf), fp2);
	  sscanf(buf, "%f%f%f%f%f%f%f%f%f%f", 
		 &cmc_temp[0], &cmc_temp[1], &cmc_temp[2], 
		 &cmc_temp[3], &cmc_temp[4],
		 &cmc_temp[5], &cmc_temp[6], &cmc_temp[7], 
		 &cmc_temp[8], &cmc_temp[9]);
	  
	  base_yr = ( (j-1) * 10 )+ iyear;
	  for (cmc_i = 0; cmc_i < 10; ++cmc_i) 
	    allinks_ref(ilink, base_yr + cmc_i ) = cmc_temp[cmc_i];
	  
	  /*<              else  >*/
	}
      }
      /*<         mlink = ilink >*/
      mlink = ilink;
      /*< 2000    continue >*/
      /* L2000: */
    } /* j loop */
    /*< 1000    continue >*/
    /* L1000: */

  } /* i=1..999999 */
  /*< 12000  continue >*/
 L12000:



/* ********** */





  /*  Read and parse b024 file - contains list of allocation nodes and */
  /*  which input and output links go with them */
  /*<        nerrs = 0 >*/
  nerrs = 0;
  /*<        do 13000 i=1,99999 >*/
  for (i__ = 1; i__ <= 99999; ++i__) {
    /*<        do 13200 ll=isyear,ieyear >*/
    i__1 = ieyear;
    for (ll = isyear; ll <= i__1; ++ll) {
      /*<        totin(ll)=0 >*/
      totin[ll - 1980] = 0.f;
      /*<        totout(ll)=0 >*/
      totout[ll - 1980] = 0.f;
      /*< 13200  continue >*/
      /* L13200: */
    }
    /* CMC        read(1,1001,end=17000) jnode,desc */
    /* CMC 1001   format(i5,t9,a15) */
    if(feof(fp1)) goto L17000;
    
    fgets(buf,sizeof(buf),fp1);pos=0;
    
    jnode = atoi(substring(buf, pos, 5)); pos+=5;
    if(jnode==0) /* at EOF */
      goto L17000;

    pos+=3;
    strcpy(desc,(char *) substring(buf, pos, 15)); pos+=15;
    
    /* CMC        read(1,*) (inlinks(jnode,k),k=1,10) */
    fgets(buf, sizeof(buf), fp1);
    sscanf(buf, "%d%d%d%d%d%d%d%d%d%d",
	   &cmc_itemp[0], &cmc_itemp[1], &cmc_itemp[2], 
	   &cmc_itemp[3], &cmc_itemp[4],
	   &cmc_itemp[5], &cmc_itemp[6], &cmc_itemp[7], 
	   &cmc_itemp[8], &cmc_itemp[9]);
    
    for (cmc_i = 1; cmc_i <=10; ++cmc_i) 
      inlinks_ref(jnode, cmc_i) = cmc_itemp[cmc_i-1] ;
    



    /*<        do 14000 m=1,10 >*/
    for (m = 1; m <= 10; ++m) {
      /*<        if (inlinks(jnode,m).gt.0) then >*/
      if (inlinks_ref(jnode, m) > 0) {
	/*<         do 13500 jj=iyear,iyear+nyears-1 >*/
	i__1 = iyear + nyears - 1;

	for (jj = iyear; jj <= i__1; ++jj) {
	  /*<         totin(jj) = totin(jj) + allinks(inlinks(jnode,m),jj) >*/
	  totin[jj - 1980] += allinks_ref(inlinks_ref(jnode, m), jj);

	/*  if( (jnode == 6) && (jj==2008))
	    fprintf(stderr, "%d:%f\n", 
		    m, allinks_ref(inlinks_ref(jnode, m), jj) ); */

	  /*< 13500   continue >*/
	  /* L13500: */
	}
	/*<         ninl=m >*/
	ninl = m;
	/*<        endif >*/
      }
      /*< 14000  continue >*/
      /* L14000: */
    }
    /* CMC        read(1,*) */
    /* CMC        read(1,*) */
    fgets(buf, sizeof(buf), fp1);
    fgets(buf, sizeof(buf), fp1);

    /* CMC        read(1,*) (olinks(jnode,k),k=1,10) */
    fgets(buf, sizeof(buf), fp1);
    sscanf(buf, "%d%d%d%d%d%d%d%d%d%d",
	   &cmc_itemp[0], &cmc_itemp[1], &cmc_itemp[2], 
	   &cmc_itemp[3], &cmc_itemp[4],
	   &cmc_itemp[5], &cmc_itemp[6], &cmc_itemp[7], 
	   &cmc_itemp[8], &cmc_itemp[9]);
    
    for (cmc_i = 1; cmc_i <=10; ++cmc_i) 
      olinks_ref(jnode, cmc_i) = cmc_itemp[cmc_i-1] ;
    


    /* CMC        read(1,*) */
    /* CMC        read(1,*) */
    /* CMC        read(1,*) */
    fgets(buf, sizeof(buf), fp1);
    fgets(buf, sizeof(buf), fp1);
    fgets(buf, sizeof(buf), fp1);
    



    /*<        do 14500 m=1,10 >*/
    for (m = 1; m <= 10; ++m) {
      /*<        if (olinks(jnode,m) .gt. 0) then >*/
      if (olinks_ref(jnode, m) > 0) {
	/*<         do 14700 jj=iyear,iyear+nyears-1 >*/
	i__1 = iyear + nyears - 1;
	for (jj = iyear; jj <= i__1; ++jj) {
	  /*<         totout(jj) = totout(jj) + allinks(olinks(jnode,m),jj) >*/
	  totout[jj - 1980] += allinks_ref(olinks_ref(jnode, m), jj);
	 /* if( (jj==2008) && (jnode == 6) )
	    fprintf(stderr, "%d:%f\n", 
		    m, allinks_ref(olinks_ref(jnode, m), jj) ); */
	    
	  /*< 14700   continue >*/
	  /* L14700: */
	}
	/*<         noml=m >*/
	noml = m;
	/*<        endif >*/
      }
      /*< 14500  continue >*/
      /* L14500: */
    }
    /* Check for sum of ins/outs */
    /* Difference is flagged based on .1 * n where n is the */
    /* greatest number of links - ingoing or outgoing */
    /* The difference flag is reset to 1% of the input, modified by JLin 4/96 */
    /*<        do 16000 m = iyear,iyear + nyears-1 >*/
    i__1 = iyear + nyears - 1;
    for (m = iyear; m <= i__1; ++m) {
      /*<         a1=totin(m) >*/
      a1 = totin[m - 1980];
      /*<         a2=totout(m) >*/
      a2 = totout[m - 1980];
      /*<         if (abs(a1-a2) .gt. 0.1*max(ninl,noml)) then      >*/
      if ((r__1 = a1 - a2, dabs(r__1)) > max(ninl,noml) * .1f) {
	/*<          nerrs= nerrs + 1 >*/
	++nerrs;
	
	/* CMC          write(7,*) ' Allocation Node  ',jnode,' ',desc */
	/* CMC          write(7,*) ' Ingoing Total  = ', totin(m) */
	/* CMC          write(7,*) ' Outgoing Total = ',totout(m),' Year =',m */
	/* CMC          write(7,*) ' === Difference = ',abs(a1-a2) */
	/* CMC          write(7,*) ' In Links : ',(inlinks(jnode,kl),kl=1,ninl) */
	/* CMC          write(7,*) ' Out Links: ',(olinks(jnode,kl),kl=1,noml) */
	/* CMC          write(7,*) */
	
	fprintf(fp7," Allocation Node  %d %s\n", jnode, desc);
	fprintf(fp7," Ingoing Total  = %11.3f\n", totin[m - 1980] );
	fprintf(fp7," Outgoing Total = %11.3f Year =%d\n", totout[m - 1980], m );
	fprintf(fp7," === Difference = %f11\n", dabs(a1-a2) );
	
	fprintf(fp7," In Links : ");
	for(cmc_i=1; cmc_i<=ninl; cmc_i++)
	  fprintf(fp7,"%d ", inlinks_ref(jnode,cmc_i));
	fprintf(fp7,"\n");
	
	fprintf(fp7," Out Links : ");
	for(cmc_i=1; cmc_i<=noml; cmc_i++)
	  fprintf(fp7,"%d ", olinks_ref(jnode,cmc_i));
	fprintf(fp7,"\n");
	
	fprintf(fp7, "\n");
	
	/*<         endif >*/
      }
      /*       check each node in every year                                   JL 4/96 */
      /*        if (a1.ne.0.0 .and. abs(a1-a2)/a1 .gt. 0.01) then                               JLin 4/96 */
      /*         nerrs= nerrs + 1                                               JLin 4/96 */
      /*        endif                                                           JLin 4/96 */
      /*< 16000   continue >*/
      /* L16000: */
    }
    /*< 13000  continue >*/
    /* L13000: */
  }
  /*< 17000  continue >*/
 L17000: 
  


/* ********* */








  /* CMC        write(*,*) */
  /* CMC        write(7,*) */
  /* CMC     +'Number of Possible Errors Detected in Allocation Nodes = ',nerrs */
  /* CMC        write(7,*) */
  /* CMC        write(7,*) */
  /* CMC        write(7,*) ' ===================' */
  /* CMC        write(7,*) ' REFINERY NODE CHECK' */
  /* CMC        write(7,*) ' ===================' */
  /* CMC        write(7,*) */
  
  fprintf(fp7,"\nNumber of Possible Errors Detected in Allocation Nodes = %d\n", nerrs);
  fprintf(fp7, "\n");
  fprintf(fp7, "\n");
  fprintf(fp7, " ===================\n");
  fprintf(fp7, " REFINERY NODE CHECK\n");
  fprintf(fp7, " ===================\n");
  fprintf(fp7, "\n");
  
  
  
  /*<        nerrs=0 >*/
  nerrs = 0;
  /*<        do 20000 i=1,99999 >*/
  for (i__ = 1; i__ <= 99999; ++i__) {
    /*<        do 20500 j=1,11 >*/
    for (j = 1; j <= 11; ++j) {
      /*<        if (j.eq.1) then >*/
      if (j == 1) {
	/* CMC          read(3,303,end=29000) irnode(i),refnode(i) */
	/* CMC 303    format(i5,t9,a20) */
	
	if(feof(fp3)) goto L29000;
	
	fgets(buf,sizeof(buf),fp3);pos=0;
	
	irnode[i__-1] = atoi(substring(buf, pos, 5)); pos+=5;
	if(irnode[i__-1]==0) /* at EOF */
	  goto L29000;
	pos+=9;
	strcpy(refnode[i__ -1], (char *) substring(buf, pos, 20)); pos+=20;
	/*<        else >*/
      } else {
	/*<         if (j.eq.2) then >*/
	if (j == 2) {
	  /* CMC          read(3,*,end=29000) irlink(irnode(i)) */
	  if(feof(fp3)) goto L29000;
	  fgets(buf,sizeof(buf),fp3);pos=0;
	  sscanf(buf, "%d", &irlink[i__-1]);
	  
	  /*<        else >*/
	} else {
	  /*<          if (j.eq.3) then >*/
	  if (j == 3) {
	    /* CMC          read(3,*,end=29000) (linkouts(irnode(i),kl),kl=1,6) */
	    
	    if(feof(fp3)) goto L29000;
	    fgets(buf,sizeof(buf),fp3);pos=0;
	    sscanf(buf, "%d%d%d%d%d%d", 
		   &cmc_itemp[0], &cmc_itemp[1], &cmc_itemp[2], 
		   &cmc_itemp[3], &cmc_itemp[4], &cmc_itemp[5] );

	    for(cmc_i=1;cmc_i<=6;cmc_i++)
	      linkouts_ref(irnode[i__ - 1], cmc_i) = cmc_itemp[cmc_i-1];
	      
	      /*<        else >*/
	  } else {
	    /*<          if (j.eq.4) then >*/
	    if (j == 4) {
	      /* CMC          read(3,20003,end=29000) (temp(ma),ma=1,6) */
	      /*<            do 20031 ml=iyear,iyear+nyears-1 >*/
	      if(feof(fp3)) goto L29000;
	      fgets(buf,sizeof(buf),fp3);pos=0;
	      sscanf(buf, "%f%f%f%f%f%f",
		     &cmc_temp[0], &cmc_temp[1], &cmc_temp[2], 
		     &cmc_temp[3], &cmc_temp[4], &cmc_temp[5] );
	      
	      i__1 = iyear + nyears - 1;
	      for (ml = iyear; ml <= i__1; ++ml) {
		/*<            do 20032 kl=1,6 >*/
		for (kl = 1; kl <= 6; ++kl) {
		  /*<             rats(ml,irnode(i),kl) = temp(kl) >*/
		  rats_ref(ml, irnode[i__ - 1], kl) = cmc_temp[kl - 1];
		  
		  /*< 20032      continue >*/
		  /* L20032: */
		}
		/*< 20031      continue >*/
		/* L20031: */
	      }
	      /* CMC 20003    format(t21,6(f5.0)) */
	      /*<        else >*/
	    } else {
	      /* CMC          read(3,*,end=29000) */
	      if(feof(fp3)) goto L29000;
	      fgets(buf,sizeof(buf),fp3);pos=0;
	      /*<        endif >*/
	    }
	    /*<        endif >*/
	  }
	  /*<        endif >*/
	}
	/*<        endif >*/
      }
      /*< 20500  continue >*/
      /* L20500: */
    }
    /*< 20000  continue >*/
    /* L20000: */
  }
  /*< 29000  continue >*/
L29000: 
  /*  Read exception file */
  
  /*<        do 23500 j=1,99999 >*/
  for (j = 1; j <= 99999; ++j) {
    /* CMC        read(4,4004,end=23700) inline */
    /* CMC 4004   format(a80) */
    /* CMC        read(inline(2:5),340) iy */
    /* CMC 340    format(i4) */
    
    if(feof(fp4)) goto L23700;
    fgets(iline,sizeof(iline),fp4);pos=0;
    iy = atoi( substring(iline,2,4));
    
    /* Year Line */
    /*<        if (iy.gt.0) then >*/
    if (iy > 0) {
      /*<         jyear=iy >*/
      jyear = iy;
      /*<         goto 23500 >*/
      goto L23500;
      /*<        endif >*/
    }
    /*<        extyp1(1:2) =  inline(22:23) >*/
    /*    s_copy(extyp1, inline__ + 21, (ftnlen)2, (ftnlen)2);*/
    strcpy(extyp1, substring(iline,21,2) );
    /*<        if (extyp1(1:2).eq.'RE') then >*/
    if (s_cmp(extyp1, "RE", (ftnlen)2, (ftnlen)2) == 0) {
      
      /* CMC          read(inline(28:30),345)iref */
      /* CMC 345    format(i3) */
      iref = atoi( substring(iline,28,3));
      
      /*<          extyp2(1:4)= inline(32:35) >*/
      /*      s_copy(extyp2, iline + 31, (ftnlen)4, (ftnlen)4);*/
      strcpy(extyp2, substring(iline, 32, 4));
      /*<           if (extyp2(1:4).eq.'SLAT') then >*/
      if (s_cmp(extyp2, "SLAT", (ftnlen)4, (ftnlen)4) == 0) {
	/* CMC           read(inline(38:40),345)k */
	k = atoi( substring(iline,38,3));
	/* CMC           read(inline(44:50),349)ratio */
	ratio = atof((char *) substring(iline,44,7));
	
	/* CMC 349       format(f7.0) */
	
	/*<             do 29053 kp = jyear,iyear+nyears-1 >*/
	i__1 = iyear + nyears - 1;
	for (kp = jyear; kp <= i__1; ++kp) {
	  /*<             rats(kp,iref,k)=ratio >*/
	  rats_ref(kp, iref, k) = ratio;
	  /*< 29053       continue >*/
	  /* L29053: */
	}
	/*<        endif >*/
      }
      /*<        endif >*/
    }
    /*< 23500  continue >*/
  L23500:
    ;
  }
  /*< 23700  continue >*/
 L23700: 
  /* Now check against link quantities */
  
  /*<        do 26000 ii=1,99 >*/
  for (ii = 1; ii <= 99; ++ii) {
    /*<        if (irnode(ii).gt.0) then >*/
    if (irnode[ii - 1] > 0) {
      /*<          j=irlink(irnode(ii)) >*/
	/* the following statement has benn modified as indicated - Prakash 
      j = irlink[irnode[ii - 1] - 1]; */

	  j = irlink[ii - 1];
      /*<          do 27500 k = 1,6 >*/
      for (k = 1; k <= 6; ++k) {
	/*<          m=linkouts(irnode(ii),k) >*/
   /* the following statement has been modified as indicated - Prakash 
	m = linkouts_ref(irnode[ii - 1], k); */

	m = linkouts_ref(ii - 1, k);
	/*<          if (m.gt.0) then >*/
	if (m > 0) {
	  /*<           do 27600 l = iyear,iyear+nyears-1 >*/
	  i__1 = iyear + nyears - 1;
	  for (l = iyear; l <= i__1; ++l) {
	    /*<           x1 = allinks(j,l) *rats(l,irnode(ii),k) >*/
	    x1 = allinks_ref(j, l) * rats_ref(l, irnode[ii - 1], 
					      k);
	    /*<           x2 = allinks(m,l)  >*/
	    x2 = allinks_ref(m, l);
	    /*<           x3 = abs(x1-x2) >*/
	    x3 = (r__1 = x1 - x2, dabs(r__1));
	    /*<           if (x3.gt.0.5) then                                            >*/
	    if (x3 > .5f) {
	      /*<            nerrs = nerrs + 1 >*/
	      ++nerrs;
	      
	      /* CMC           write(7,*) ' Refinery Node  ',irnode(ii),' ',refnode(ii) */
	      /* CMC           write(7,*) ' Year:     ',l */
	      /* CMC           write(7,*) ' In Link : ',irlink(irnode(ii)) */
	      /* CMC           write(7,*) ' Out Link: ',linkouts(irnode(ii),k) */
	      /* CMC           write(7,*) ' Ratio:    ',rats(l,irnode(ii),k) */
	      /* CMC           write(7,*) ' Expected, Actual Values: ',x1,x2 */
	      /* CMC           write(7,*) ' ===  Difference =     ',abs(x1-x2) */
	      /* CMC           write(7,*) */
	      
	      fprintf(fp7," Refinery Node  %d %s\n", irnode[ii-1], refnode[ii-1] );
	      fprintf(fp7," Year:     %d\n",l );
		  /* the following statement has been modified as indicated - Prakash 
	      fprintf(fp7," In Link : %d\n", irlink[irnode[ii-1]-1]); */

		  fprintf(fp7," In Link : %d\n", irlink[ii-1]); 
		  /* the following statement has been modified as indicated 
		  fprintf(fp7," Out Link: %d\n", linkouts_ref(irnode[ii-1],k) ); */

	      fprintf(fp7," Out Link: %d\n", linkouts_ref(ii-1,k) );
	      fprintf(fp7," Ratio:    %f\n", rats_ref(l,irnode[ii-1],k) );
	      fprintf(fp7," Expected, Actual Values: %f %f\n", x1,x2 );
x1x2 = fabs(x1 - x2);
	      fprintf(fp7," ===  Difference =     %f\n", x1x2 );
	      fprintf(fp7, "\n");
	      
	      /*<           endif >*/
	    }
	    /*< 27600    continue >*/
	    /* L27600: */
	  }
	  /*<          endif >*/
	}
	/*< 27500    continue >*/
	/* L27500: */
      }
      /*<          endif >*/
    }
    /*< 26000    continue >*/
    /* L26000: */
  }
  /* CMC          write(7,*) */
  /* CMC        write(7,*) */
  /* CMC     +' Number of Possible Errors Detected in Refinery Nodes = ',nerrs */
  fprintf(fp7, "\n");
  fprintf(fp7, "\n");
  fprintf(fp7, " Number of Possible Errors Detected in Refinery Nodes = %d\n",nerrs);
  
  /*< 32500  continue >*/
  /* L32500: */
  
  /* CMC ** debug write */
  /*       do 32550 j=iyear,iyear+nyears-1 */
  /*       do 32556 j2 = 1,999 */
  /*       if (allinks(j2,j) .gt. 0) then */
  /*       endif */
  /* 32556  continue */
  /* 32550  continue */
  /*< 32600  end        >*/
  /* L32600: */
fclose(fp1);
fclose(fp2);
fclose(fp3);
fclose(fp4);
fclose(fp7);

  return 0;
} /* alcheck_ */

#undef inlinks_ref
#undef allinks_ref
#undef olinks_ref
#undef linkouts_ref
#undef rats_ref
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
