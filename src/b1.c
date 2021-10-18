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
				 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f2c.h"
#include "cmc_f2c.h"
#include <time.h>
#include "structures.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__5 = 5;
static integer c__6 = 6;
static integer c__7 = 7;


/* ***** MAIN PROGRAM. */
FILE *fp5, *fp6, *fp10, *fp11, *fp12,  *fp13, *fp23, *fp24, *fp25, *elecf, 
	 *fpPrEcon, *fpReEcon, *fpEleEcon;
int emisflag=1;
char cmc_titl[6][256];
char cmc_lab[256];
char LinkNodeNames[14][999][6];
char LinkNodeSector[14][999][6];
char *token;
char seps[] ="'";

/*<       COMMON/OUTWR/ LABY(75) >*/
/* Main program */ MAIN__(void)
{
  /* System generated locals */
  integer i__1, i__2;
extern  FILE *fp5, *fp6, *fp10, *fp11, *fp12,  *fp13, *fp21, *fp23, *fp24, *fp25, *elecf, 
			 *fpPrEcon, *fpReEcon, *fpEleEcon;
extern int emisflag;

extern char **xargv;
extern char LinkNodeNames[14][999][6];
extern char LinkNodeSector[14][999][6];
time_t ltime;

  /* Builtin functions */
  /* Subroutine */ int s_stop(char *, ftnlen);
  
  /* Local variables */
  static integer icon;
  extern /* Subroutine */ int outw_(integer *);
  static integer k, l;
  extern /* Subroutine */ int input_(void), visit_(integer *), 
	  convg_(integer *), otput_(void), tolod_(void), toele_(void), toimp_(void), alcheck_(void);
  extern int emisinput_(void);
  extern void economic_(void);
  static integer ist, iut;
  
  /*<       COMMON/EL1/LWRIT(75),ITELF(75),ITELL(75),IECHO,IEECH,IFINL >*/
  /*<    >*/
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
  /*<       COMMON/MODE/IRESON,ILOD,IELE,IMP,BOEMWH,BOEMBTU >*/
  
  
  /*     * * * *       O P E N     F I L E S       * * * * */
  
  /* CMC       OPEN (5, FILE = 'TJAM.DAT', STATUS = 'OLD') */
  /* CMC       OPEN (6, FILE = 'SUM.OUT',  STATUS = 'UNKNOWN')                   bph10/88 */
  /* CMC       OPEN (11,FILE = 'TIME.OUT', STATUS = 'UNKNOWN')                      " */
  /* CMC       OPEN (12,FILE = 'DATA.OUT', STATUS = 'UNKNOWN')                      " */
  /* CMC       OPEN (13,FILE = 'ELEC.OUT', STATUS = 'UNKNOWN')                   bph10/88 */
  
  int ct;
  char buf [1024];
  int lct;
  int pos;
  int i,j;

  if((fp5=fopen("./tjam.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open TJAM.DAT\n");
    exit(0);
  }
  if((fp6=fopen("./sum.out", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open SUM.OUT\n");
    exit(0);
  }
  if((fp11=fopen("./time.out", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open TIME.OUT\n");
    exit(0);
  }
  if((fp12=fopen("./data.out", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open DATA.OUT\n");
    exit(0);
  }
  if((fp13=fopen("./elec.out", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open ELEC.OUT\n");
    exit(0);
  }
  
  if((elecf=fopen("./elecf.out", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open ELECF.OUT\n");
    exit(0);
  }

  if((fpPrEcon=fopen("./EconProcess.out", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open ECONPROCESS.OUT\n");
    exit(0);
  }

  if((fpReEcon=fopen("./EconResource.out", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open ECONRESOURCE.OUT\n");
    exit(0);
  }

  if((fpEleEcon=fopen("./EconElectric.out", "w"))==NULL){
    fprintf(fp21, "Error: Couldnt open ECONELECTRIC.OUT\n");
    exit(0);
  }

  
  if((fp23=fopen("./bmap.dat", "r"))==NULL){
    fprintf(fp21, "Error: Couldnt open BMAP.DAT\n");
    exit(0);
  }	

 if((fp24=fopen("./balemis.dat", "r"))==NULL){
    fprintf(fp21, "Emission Calculations Not Performed\n");
	emisflag =0;
  }		

 if(emisflag==1){
 	if((fp25=fopen("./emis.out", "w"))==NULL){
    fprintf(fp21, "Error Couldn't open EMIS.OUT\n");
	exit(0);
	}
  }	



	/* initialize the Efactors with default values
	Emission Factor 0.0
	Scalevalue 1.0
	Emission Tax 0.0 */

	for(i=0;i<75;i++) {
		for(j=0;j<50;j++){
			res_1.Efactors[i][j][0]=0.0;
			res_1.Efactors[i][j][1]=1.0;
			res_1.Efactors[i][j][2]=0.0;
		}
	}

	for(i=0;i<17;i++) {
		for(j=0;j<50;j++){
			ren_1.Efactors[i][j][0]=0.0;
			ren_1.Efactors[i][j][1]=1.0;
			ren_1.Efactors[i][j][2]=0.0;
		}
	}

	for(i=0;i<300;i++) {
		for(j=0;j<50;j++){
			pro_1.Efactors[i][j][0]=0.0;
			pro_1.Efactors[i][j][1]=1.0;
			pro_1.Efactors[i][j][2]=0.0;
		}
	}


	for(i=0;i<15;i++) {
		for(j=0;j<50;j++){
			min_1.Efactors[i][j][0]=0.0;
			min_1.Efactors[i][j][1]=1.0;
			min_1.Efactors[i][j][2]=0.0;
		}
	}

	for(i=0;i<200;i++) {
		for(j=0;j<50;j++){
			dem_1.Efactors[i][j][0]=0.0;
			dem_1.Efactors[i][j][1]=1.0;
			dem_1.Efactors[i][j][2]=0.0;
		}
	}

	for(i=0;i<30;i++) {
		for(j=0;j<50;j++){
			ref_1.Efactors[i][j][0]=0.0;
			ref_1.Efactors[i][j][1]=1.0;
			ref_1.Efactors[i][j][2]=0.0;
		}
	}


	for(i=0;i<300;i++) {
		for(j=0;j<50;j++){
			elec_1.Efactors[i][j][0]=0.0;
			elec_1.Efactors[i][j][1]=1.0;
			elec_1.Efactors[i][j][2]=0.0;
		}
	}



	/* Reading Bmap */

	/*read next 2 lines as Allocation Nodes and Empty Line*/
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[0][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[0][ct][6]='\0';
		strcpy(LinkNodeSector[0][ct], substring(buf, pos,5 ));
		LinkNodeSector[0][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Demand Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[1][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[1][ct][6]='\0';
		strcpy(LinkNodeSector[1][ct], substring(buf, pos,5 ));
		LinkNodeSector[1][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}


	/*read next line as Multiple Input Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[2][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[2][ct][6]='\0';
		strcpy(LinkNodeSector[2][ct], substring(buf, pos,5 ));
		LinkNodeSector[2][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Price Projection Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[3][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[3][ct][6]='\0';
		strcpy(LinkNodeSector[3][ct], substring(buf, pos,5 ));
		LinkNodeSector[3][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}


	/*read next line as Conversion Process Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[4][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[4][ct][6]='\0';
		strcpy(LinkNodeSector[4][ct], substring(buf, pos,5 ));
		LinkNodeSector[4][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Multiple Output Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[5][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[5][ct][6]='\0';
		strcpy(LinkNodeSector[5][ct], substring(buf, pos,5 ));
		LinkNodeSector[5][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Renewable Resources Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[6][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[6][ct][6]='\0';
		strcpy(LinkNodeSector[6][ct], substring(buf, pos,5 ));
		LinkNodeSector[6][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Depletable Resources Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[7][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[7][ct][6]='\0';
		strcpy(LinkNodeSector[7][ct], substring(buf, pos,5 ));
		LinkNodeSector[7][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Stockpile Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[8][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[8][ct][6]='\0';
		strcpy(LinkNodeSector[8][ct], substring(buf, pos,5 ));
		LinkNodeSector[8][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Transportation Nodes and Empty Line */
	/* Transportation node is same as conversion process node */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[4][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[4][ct][6]='\0';
		strcpy(LinkNodeSector[4][ct], substring(buf, pos,5 ));
		LinkNodeSector[4][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}


	/*read next line as Electric Dispatcher Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[10][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[10][ct][6]='\0';
		strcpy(LinkNodeSector[10][ct], substring(buf, pos,5 ));
		LinkNodeSector[10][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Thermoelectric Units and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[11][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[11][ct][6]='\0';
		strcpy(LinkNodeSector[11][ct], substring(buf, pos,5 ));
		LinkNodeSector[11][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}


	/*read next line as Hydroelectric Units and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);pos=7;
	ct =  atoi(substring(buf, pos,3)); pos+=11;
	while(ct!=0){
		strcpy(LinkNodeNames[12][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[12][ct][6]='\0';
		strcpy(LinkNodeSector[12][ct], substring(buf, pos,5 ));
		LinkNodeSector[12][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}

	/*read next line as Links Nodes and Empty Line */
	fgets(buf,sizeof(buf),fp23);
	fgets(buf,sizeof(buf),fp23);
	while(!feof(fp23)){
		strcpy(LinkNodeNames[13][ct], substring(buf, pos,5 ));pos+=26;
		LinkNodeNames[13][ct][6]='\0';
		strcpy(LinkNodeSector[13][ct], substring(buf, pos,5 ));
		LinkNodeSector[13][ct][6]='\0';
		fgets(buf,sizeof(buf),fp23);pos=7;
		ct =  atoi(substring(buf, pos,3)); pos+=11;
	}
	
	fclose(fp23);


	/* Read BALUNITS.DAT */
	if((fp23=fopen("./balunits.dat", "r"))==NULL){
		fprintf(fp21, "Error: Couldnt open BALUNITS.DAT\n");
		exit(0);
	}
	
	/* Right Now I need currency unit, Price and Quantity Units only.
	   Fix the code when need to use other units also 
	*/

	k=0;
	while(!feof(fp23)){
		fgets(buf,sizeof(buf),fp23);pos=0;
		token =  strtok(buf, seps);
		
		//Currency units
		if(strcmp(token,"CI")==0){
			strcpy(units_1.unitcode[0],token);
			token=strtok(NULL, seps);
			strcpy(units_1.unitname[0],token);
			token=strtok(NULL, seps);
			units_1.unitcnvt[0] = atof(token);
		}

		//Fuel Price
		if(strcmp(token,"PR")==0){
			strcpy(units_1.unitcode[3],token);
			token=strtok(NULL, seps);
			strcpy(units_1.unitname[3],token);
			token=strtok(NULL, seps);
			units_1.unitcnvt[3] = atof(token);
		}
		
		//CapitalCost for electruc units
		if(strcmp(token,"PR_ECC")==0){
			strcpy(units_1.unitcode[6],token);
			token=strtok(NULL, seps);
			strcpy(units_1.unitname[6],token);
			token=strtok(NULL, seps);
			units_1.unitcnvt[6] = atof(token);
		}

		//Fixed Cost for electruc units
		if(strcmp(token,"PR_EFOM")==0){
			strcpy(units_1.unitcode[7],token);
			token=strtok(NULL, seps);
			strcpy(units_1.unitname[7],token);
			token=strtok(NULL, seps);
			units_1.unitcnvt[7] = atof(token);
		}

		//Capacity for non-electruc units
		if(strcmp(token,"QT")==0){
			strcpy(units_1.unitcode[8],token);
			token=strtok(NULL, seps);
			strcpy(units_1.unitname[8],token);
			token=strtok(NULL, seps);
			units_1.unitcnvt[8] = atof(token);
		}
		
		//variable Cost for electruc units
		if(strcmp(token,"PR_EVOM")==0){
			strcpy(units_1.unitcode[9],token);
			token=strtok(NULL, seps);
			strcpy(units_1.unitname[9],token);
			token=strtok(NULL, seps);
			units_1.unitcnvt[9] = atof(token);
		}


		//Generation for Electric Units
		if(strcmp(token,"QT_EL_GEN")==0){
			strcpy(units_1.unitcode[13],token);
			token=strtok(NULL, seps);
			strcpy(units_1.unitname[13],token);
			token=strtok(NULL, seps);
			units_1.unitcnvt[13] = atof(token);
		}

		//Capacity for Electric Units
		if(strcmp(token,"QT_ETCAP")==0){
			strcpy(units_1.unitcode[14],token);
			token=strtok(NULL, seps);
			strcpy(units_1.unitname[14],token);
			token=strtok(NULL, seps);
			units_1.unitcnvt[14] = atof(token);
		}
	

		k=k+1;
	}



  /*     * * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  
  /*<       EPSN=1.E-08 >*/
  var_1.epsn = 1e-8f;
  /*<       IOUTX=0 >*/
  pri_1.ioutx = 0;
  
  /* CMC       WRITE (*,*) 'Reading TJAM.DAT ...'             MJ060486 */
  
  /* CMC       READ(5,6446)(ITITL(K),K=1,114) */
  /* CMC  6446 FORMAT(1X,19A4,5(/,1X,19A4)) */
  /* ititl is integer, but it should be character */
  fprintf(fp21,"Reading TJAM.DAT ...\n");

  for(lct=1; lct<=6; lct++) {
    fgets(cmc_titl[lct-1], sizeof(cmc_titl[lct-1]), fp5);
	strcpy(ren_1.ititl[lct-1],cmc_titl[lct-1]);
  }

  /* CMC       WRITE(12,6446)(ITITL(K),K=1,114) */
  /* CMC  6446 FORMAT(1X,19A4,5(/,1X,19A4)) */
  for(lct=1; lct<=6; lct++){
      fprintf(fp12, "%s", cmc_titl[lct-1]);
  }
  
  /* CMC       READ(5,650)(LAB(J),J=1,5),IYRB,NPER */
  /* CMC   650 FORMAT(5A4,5X,11I5) */
  fgets(buf, sizeof(buf), fp5); pos = 0; 

  strcpy(cmc_lab, (char *) substring(buf,0,20));pos+=20;
  pos+=5;
  var_1.iyrb = atoi(substring(buf,pos,5)); pos+=5;
  var_1.nper = atoi(substring(buf,pos,5)); pos+=5;
  
  /* CMC       WRITE(12,650)(LAB(J),J=1,5),IYRB,NPER */
  /* CMC   650 FORMAT(5A4,5X,11I5) */
  
  fprintf(fp12, "%s", cmc_lab);
  fprintf(fp12, "     %5d %5d\n", var_1.iyrb, var_1.nper);


  time( &ltime );
  fprintf(fp6, "SIMULATION RUN ON:%s", ctime( &ltime ) );
  /*     Write out baseyear and lenstudy */
  fprintf(fp6, "Baseyear: %d  Number of Years: %d\n\n", var_1.iyrb, var_1.nper);
  fprintf(fp6, "Quantities are in %s and Prices are in %s\n\n", units_1.unitname[8], units_1.unitname[3]);
  
  if(emisflag==1){ 		
	fprintf(fp25, "SIMULATION RUN ON:%s", ctime( &ltime ) );	
	fprintf(fp25, "Baseyear: %d  Number of Years: %d\n\n", var_1.iyrb, var_1.nper);
	fprintf(fp25, "Emission Taxes and Total Prices are in %s\n\n", units_1.unitname[3]);
	fprintf(fp25, "Year  Itn  NodeType   NodeName   Sector     EmissionTax     TotalPrice\n");
  }

  fprintf(elecf,"Year'UnitNo'UnitName'UnitType'EnergyInkBOE'EnergyOutMwh'UnitBaseCap'UnitDeratedCap'CapacityFactor'Cost\n");


  fprintf(fpPrEcon,"Year;Sec;Node;Type;Quantity;AvgCap;AvgCapital;AvgCF;AvgLife;opUnits;opCap;baseUnits;baseCap;baseSunk;existingUnits;existingCap;existingSunk;dNotServed;newUnits;newCap;newCapital;operatingCost;totalCap;avgInvst;avgCap;avgCF;effOutput\n");
  fprintf(fpPrEcon,";;;;%s;%s;%s;;years;;%s;;%s;%s;;%s;%s;k%s;;%s;%s;%s;%s;%s;%s;;%s\n",
					units_1.unitname[8],units_1.unitname[8],units_1.unitname[0],units_1.unitname[8],units_1.unitname[8],units_1.unitname[0],units_1.unitname[8],units_1.unitname[0],units_1.unitname[8],units_1.unitname[8],units_1.unitname[0],units_1.unitname[0],units_1.unitname[0],
					units_1.unitname[0], units_1.unitname[8],units_1.unitname[8]);

  fprintf(fpReEcon, "Year;Sector;NodeID;Type;Quantity;NoTaxPrice;fuelCost;EconomicRent;StudyEnd\n");
  fprintf(fpReEcon, "; ; ; ; %s; %s; %s; %s; \n",
					units_1.unitname[8],units_1.unitname[3],units_1.unitname[0],units_1.unitname[0]);

  fprintf(fpEleEcon, "Year;Sector;UnitName;Type;Capacity;Capital;fixedOM;variableOM;generation;onlineyear; retireyear\n");
  fprintf(fpEleEcon, ";;;;%s;%s;%s;%s;%s;;\n",
					  units_1.unitname[14],units_1.unitname[6],units_1.unitname[7],units_1.unitname[9],units_1.unitname[13]);


  /* +++++ MAIN TIME LOOP BEGIN +++++++++++++++++++++++++++++++++++++++++ */
  
  
  /*<       DO 13 NTIME=1,NPER >*/
  i__1 = var_1.nper;
  for (var_1.ntime = 1; var_1.ntime <= i__1; ++var_1.ntime) {
    /*<       ITN=0 >*/
    var_1.itn = 0;
	var_1.itime = var_1.iyrb + var_1.ntime - 1;
    /*<   100 ITN=ITN+1 >*/
  L100:
    ++var_1.itn;

    /*<       IF(ITN.EQ.1)CALL INPUT                                            >*/
    if (var_1.itn == 1) {
      input_();
	  if (emisflag==1)
		emisinput_();
    }
 
    
    /* ***** DUMP VISIT SUMMARY IN BASE YEAR UP-PASS AND SECOND */
    /* ***** YEAR UP- AND DOWN-PASSES ON FIRST ITERATION ONLY. */
    
    /* CMC       IF(NTIME.EQ.1)WRITE(11,4343)(ITITL(K),K=1,114) */
    /* CMC  4343 FORMAT(1H1,6(/,1X,'**********',2X,19A4),//) */
    
    if (var_1.ntime == 1) {
      fprintf(fp11, "1\n"); /* CMC CHECK */
      for(lct=1; lct<=6; lct++){
		fprintf(fp11, " **********  ");
		fprintf(fp11, "%s", cmc_titl[lct-1] );
      }
		fprintf(fp11, "\n\n");
    }
    /* C***** SET WRITE FLAG FOR UNIT 6: SUM OUT. */
    /* C***** IF JWRIT(NTIME)=1, WRITE PRICE AND QUANTITY CALCULATION */
    /* C***** RESULTS AT EVERY PROCESS CALL FOR ITERATIONS ITFIR TO */
    /* C***** ITLAS.  ELSE, DO NOT WRITE TO UNIT 6 THIS YEAR. */
    
    /*<       IWR1=0 >*/
    var_1.iwr1 = 0;
    /*<       IF(JWRIT(NTIME).EQ.0)GO TO 6033 >*/
    if (ren_1.jwrit[var_1.ntime - 1] == 0) {
      goto L6033;
    }
    /*<       IF(ITN.LT.ITFIR(NTIME))GO TO 6033 >*/
    if (var_1.itn < ren_1.itfir[var_1.ntime - 1]) {
      goto L6033;
    }
    /*<       IF(ITN.GT.ITLAS(NTIME))GO TO 6033 >*/
    if (var_1.itn > ren_1.itlas[var_1.ntime - 1]) {
      goto L6033;
    }
    /*<       IWR1=JWRIT(NTIME) >*/
    var_1.iwr1 = ren_1.jwrit[var_1.ntime - 1];
    /*<  6033 CONTINUE >*/
  L6033:
    
    /* C***** SET WRITE FLAG FOR ELECTRIC SECTOR OUTPUT WHILE ITERATING: */
    /* C***** ELEC OUT. */
    /* C***** IF LWRIT(NTIME)=1, WRITE ELECTRIC SECTOR CALCULATION */
    /* C***** RESULTS FOR ITERATIONS ITELF TO ITELL. */
    /* C***** ELSE, DO NOT WRITE TO UNIT 10 THIS YEAR. */
    
    /*<       IWRE=0 >*/
    elec_1.iwre = 0;
    /*<       IF(LWRIT(NTIME).EQ.0)GO TO 7914 >*/
    if (el1_1.lwrit[var_1.ntime - 1] == 0) {
      goto L7914;
    }
    /*<       IF(ITN.LT.ITELF(NTIME))GO TO 7914 >*/
    if (var_1.itn < el1_1.itelf[var_1.ntime - 1]) {
      goto L7914;
    }
    /*<       IF(ITN.GT.ITELL(NTIME))GO TO 7914 >*/
    if (var_1.itn > el1_1.itell[var_1.ntime - 1]) {
      goto L7914;
    }
    /*<       IWRE=LWRIT(NTIME) >*/
    elec_1.iwre = el1_1.lwrit[var_1.ntime - 1];
    /*<  7914 CONTINUE >*/
  L7914:
    
    /*<       ITIME=IYRB+NTIME-1 >*/
    var_1.itime = var_1.iyrb + var_1.ntime - 1;
    
    /* CMC       IF(IWR1.GE.1)WRITE(6,200)ITN,ITIME */
    /* CMC   200 FORMAT(1H1,'ITERATION NO.',I6,10X,'PERIOD NO.',I6,/) */
    if (var_1.iwr1 >= 1) {
      fprintf(fp6, "1"); /* CMC CHECK 1H1 */
      fprintf(fp6, "ITERATION NO.%6d          YEAR%6d\n",var_1.itn,var_1.itime);
    }

	

    /* ***** INITIALIZE STOCKPILES FOR THIS ITERATION. */
    
    /*<       IF(NNST.EQ.0)GO TO 723 >*/
    if (var_1.nnst == 0) {
      goto L723;
    }
    /*<       DO 701 K=1,NNST >*/
    i__2 = var_1.nnst;
    for (k = 1; k <= i__2; ++k) {
      /*<       IST=ISTC(K) >*/
      ist = stk_1.istc[k - 1];
      /*<       IF(IST.EQ.0)GO TO 701 >*/
      if (ist == 0) {
	goto L701;
      }
      /*<       ST(IST)=STOK(IST) >*/
      stk_1.st[ist - 1] = stk_1.stok[ist - 1];
      /*<   701 CONTINUE >*/
    L701:
      ;
    }
    /*<   723 CONTINUE >*/
  L723:
    
    
    /* ***** UP-PASS. */
    
    /* CMC       IF(IWR1.GE.1)WRITE(6,201) */
    /* CMC   201 FORMAT(2X,'UP-PASS :') */
    if (var_1.iwr1 >= 1) {
      fprintf(fp6, "  UP-PASS :\n");
    }
    
    /* ***** IF FIRST PERIOD COMPUTE ALL BASE YEAR QUANTITIES FROM RESOURCE */
    /* ***** QUANTITIES, EFF, SLATE, AND SPLIT. */
    
    /*<       CALL VISIT(1) >*/
    visit_(&c__1);

    /*<       IF(NTIME.EQ.1)GO TO 123 >*/
    if (var_1.ntime == 1) {
      goto L123;
    }
    
    /* ***** DOWN-PASS. */
    
    /* CMC       IF(IWR1.GE.1)WRITE(6,202) */
    /* CMC   202 FORMAT(/////,2X,'DOWN-PASS :') */
    if (var_1.iwr1 >= 1) {
      fprintf(fp6, "\n\n\n\n\n  DOWN-PASS :\n");

    }
    
    
    /* ***** SET FLAG FOR REFERENCE ENERGY SIMULATION (CONSTANT SHARES */
    /* ***** STARTING IN YEAR IRES). */
    
    /*<       IRESON=0 >*/
    mode_1.ireson = 0;
    /*<       IF(ITIME.GE.IRES)IRESON=1 >*/
    if (var_1.itime >= var_1.ires) {
      mode_1.ireson = 1;
    }
    
    /*<       CALL VISIT(2) >*/
    visit_(&c__2);
    
    /* ***** CHECK FOR CONVERGENCE UNLESS IN RES MODE.  IF IN RES MODE, */
    /* ***** NO MORE ITERATIONS ARE REQUIRED FOR THIS YEAR. */
    
    /*<       IF(IRESON.NE.1)GO TO 107 >*/
    if (mode_1.ireson != 1) {
      goto L107;
    }
    /* CMC       IF(IWR1.GE.1)WRITE(6,721)ITIME */
    /* CMC   721 FORMAT(///,2X,'##',5X,I5,5X,'RES MODE CALCULATION', */
    /* CMC      1 ' COMPLETE',/) */
    if (var_1.iwr1 >= 1) {
      fprintf(fp6, "\n\n\n  ##     %5d     RES MODE CALCULATION COMPLETE\n", var_1.itime);
    }
    
    /* CMC       WRITE(11,4721)ITIME */
    fprintf(fp11, "%5d\n", var_1.itime);
    /* CMC       WRITE(*,4721)ITIME */
    /*CMC UNKNOWN*/
    /* CMC  4721 FORMAT(2X,I5,5X,'RES MODE CALCULATION COMPLETE',/) */
    /*<       GO TO 109 >*/
    
    goto L109;
    
    /* ***** CONVERGENCE CHECK: */
    
    /*<   107 ICON = 0 >*/
  L107:
    icon = 0;
    /*<       CALL CONVG(ICON) >*/
    convg_(&icon);
    /*<       IF(ICON)11,11,101 >*/
    if (icon <= 0) {
      goto L11;
    } else {
      goto L101;
    }
    
    /* ***** CONTINUE ITERATING IF NOT CONVERGED AND MAX ITERATIONS NOT MET. */
    /* ***** CALL VISIT(3) TO ASSIGN NEW QUANTITY GUESSES TO OUTPUT LINKS */
    /* ***** OF RESOURCE PROCESSES. */
    
    /*<    11 IF(ITN.GE.ITMAX)GO TO 97 >*/
  L11:
    if (var_1.itn >= var_1.itmax) {
      goto L97;
    }
    /*<       CALL VISIT(3) >*/
    visit_(&c__3);
    /*<       GO TO 100 >*/
    goto L100;
    
    /* ***** TERMINATE DUE TO MAXIMUM ITERATIONS. */
    
    /*<  97   CONTINUE >*/
  L97:     
    /* CMC    97 WRITE(11,127)ITMAX */
    fprintf(fp11, "\n **********************************************************************\n\n     TERMINATION DUE TO MAX ITNS:%6d\n\n **********************************************************************\n\n",var_1.itmax);
    
    /* CMC       WRITE(*,127)ITMAX */
    /* CMC UNKNOWN */
    
    /* CMC   127 FORMAT(1H1,/,1X,70(1H*),//,5X,'TERMINATION DUE TO MAX ITNS:', */
    /* CMC      1 I6,//,1X,70(1H*),//) */
    
    
    /*<       CALL OTPUT >*/
    otput_();
    /*<       GO TO 99 >*/
    goto L99;
    
    /* ***** CONVERGENCE ACHIEVED. */
    
    /*     UP-PASS again to calculate the prices                             JL 12/20/95 */
    /*     CALL VISIT(3)                                                     JL 12/28/95 */
    /*<   101 IF(NNST.EQ.0)GO TO 703 >*/
  L101:
    if (var_1.nnst == 0) {
      goto L703;
    }
    /*<       DO 702 K=1,NNST >*/
    i__2 = var_1.nnst;
    for (k = 1; k <= i__2; ++k) {
      /*<       IST=ISTC(K) >*/
      ist = stk_1.istc[k - 1];
      /*<       IF(IST.EQ.0)GO TO 702 >*/
      if (ist == 0) {
	goto L702;
      }
      /*<       ST(IST)=STOK(IST) >*/
      stk_1.st[ist - 1] = stk_1.stok[ist - 1];
      /*<   702 CONTINUE >*/
    L702:
      ;
    }
    /*<   703 CONTINUE >*/
  L703:
    /* CMC       IF(IWR1.GE.1)WRITE(6,201) */
    fprintf(fp6, "  UP-PASS :\n");
    
    /*<       CALL VISIT(1) >*/
	if(var_1.itn >1)
    visit_(&c__1);
    /* CMC       IF(IWR1.GE.1)WRITE(6,121)ITIME,RCTOL,ITN */
    if (var_1.iwr1 >= 1) {
      fprintf(fp6, "\n\n\n  ##     %5d     CONVERGENCE AT TOLERANCE%10.6f   AFTER%5d   ITERATIONS\n",
	      var_1.itime, var_1.rctol, var_1.itn);
      
      
      /* CMC   121 FORMAT(///,2X,'##',5X,I5,5X,'CONVERGENCE AT ', */
      /* CMC      1 'TOLERANCE',F10.6, */
      /* CMC      2 3X,'AFTER',I5,3X,'ITERATIONS',/) */
      
    }
    
    
    /* CMC       WRITE(11,4121)ITIME,RCTOL,ACTOL,ITN */
    fprintf(fp11, "  %5d     CONVERGENCE AT REL. TOL. =%10.6f   AND ABS. TOL. =%8.1f   AFTER%5d   ITERATIONS.    ##\n\n",var_1.itime, var_1.rctol,var_1.actol, var_1.itn);
    fprintf(fp21,"  %5d     CONVERGENCE AT REL. TOL. =%10.6f   AND ABS. TOL. =%8.1f   AFTER%5d   ITERATIONS.    ##\n\n",var_1.itime, var_1.rctol,var_1.actol, var_1.itn);
    
    /* CMC  4121 FORMAT(2X,I5,5X,'CONVERGENCE AT REL. TOL. =',F10.6,3X, */
    /* CMC      1 'AND ABS. TOL. =',F8.1,3X,'AFTER',I5,3X,'ITERATIONS.    ##',/) */
    
    /* CMC UNKNOWN */
    /* CMC       WRITE(*,5121)ITIME,RCTOL,ACTOL,ITN */
    /* CMC  5121 FORMAT(2X,I5,2X,'CONVERG RTOL=',F10.6,2X, */
    /* CMC      1 'ATOL=',F8.1,2X,'AFTER',I5,2X,'ITNS.##',/) */
    
    /* ***** ADJUST STOCKPILES ONCE PER YEAR AFETER CONVERGENCE. */
    
    /*<   109 IF(NNST.EQ.0)GO TO 123 >*/
  L109:
    if (var_1.nnst == 0) {
      goto L123;
    }
    /*<       DO 1101 K=1,NNST >*/
    i__2 = var_1.nnst;
    for (k = 1; k <= i__2; ++k) {
      /*<       IST=ISTC(K) >*/
      ist = stk_1.istc[k - 1];
      /*<       IF(IST.EQ.0)GO TO 1101 >*/
      if (ist == 0) {
	goto L1101;
      }
      /*<       L=IOUST(IST) >*/
      l = stk_1.ioust[ist - 1];
      /*<       IF(L.EQ.0)GO TO 1101 >*/
      if (l == 0) {
	goto L1101;
      }
      /*<       STOK(IST)=STOK(IST)-Q(L) >*/
      stk_1.stok[ist - 1] -= net_1.q[l - 1];
      /*<       IF (ISTKEXL(IST).EQ.0) GO TO 1101                                  >*/
      if (stk_1.istkexl[ist - 1] == 0) {
	goto L1101;
      }
      /*<          Q(ISTKEXL(IST)) = STOK(IST) * STKEXR(IST)                       >*/
      net_1.q[stk_1.istkexl[ist - 1] - 1] = stk_1.stok[ist - 1] * 
	stk_1.stkexr[ist - 1];
      /*<          STOK(IST) = STOK(IST) * (1.0 - STKEXR(IST))                     >*/
      stk_1.stok[ist - 1] *= 1.f - stk_1.stkexr[ist - 1];
      /*<  1101 CONTINUE >*/
    L1101:
      ;
    }
    /*<   123 CONTINUE >*/
  L123:
    
    /* ***** SET IWRE FOR ELEC SECTOR OUTPUT. */
    /* ***** IWR1 FOR P AND Q CALCULATION RESULTS IS ALREADY SET */
    /* ***** ASSIGN LABEL FOR COLUMN AS YEAR, ITIME. */
    
    /*<  2200 IWRE=1 >*/
    /* L2200: */
    elec_1.iwre = 1;
    /*<       IOUTX=IOUTX+1 >*/
    ++pri_1.ioutx;
    /*<       LABY(IOUTX)=ITIME >*/
    outwr_1.laby[pri_1.ioutx - 1] = var_1.itime;
    
    /* ***** CALL VISIT(5) FOR RECORDING P AND Q LINK DATA IN ZEN FOR THIS */
    /* ***** YEAR. */
    
    /*<       CALL VISIT(5) >*/
    visit_(&c__5);
    
    /* ***** ADJUST ARRAYS FOR ELECTRIC SECTOR TO REFLECT CONVERGENCE. */
    
    /*<  1313 DO 3340 IUT=1,NUNIT >*/
    /* L1313: */
    i__2 = elec_1.nunit;
    for (iut = 1; iut <= i__2; ++iut) {
      
      /* *****IF UNIT DID NOT EXIST BEFORE THIS YEAR BUT IT */
      /* ***** WAS USED THIS YEAR, THEN RECORD THAT IT WAS BUILT */
      /* ***** THIS YEAR. */
      
      /*<       IF(NUSE(IUT).EQ.0.AND.KUSE(IUT).GT.0)NUSE(IUT)=KUSE(IUT) >*/
      if (elec_1.nuse[iut - 1] == 0 && elec_1.kuse[iut - 1] > 0) {
	elec_1.nuse[iut - 1] = elec_1.kuse[iut - 1];
      }
      
      /*<  3340 CONTINUE >*/
      /* L3340: */
    }
    /*<    13 CONTINUE >*/
    /* L13: */
	economic_();
  }
  
  /* +++++ MAIN TIME LOOP END +++++++++++++++++++++++++++++++++++++++++++ */
  
  /* ***** ACTIVATE OUTPUT WRITER. */
  
  /*<       CALL OUTW(2) >*/
  outw_(&c__2);
 
  /* ***** IF IFINL=1 DO NOT WRITE P AND Q LINK SUMMARY. */
  
  /*<       IF(IFINL.EQ.1)GO TO 99 >*/
  if (el1_1.ifinl == 1) {
    goto L99;
  }
  
  /* ***** REPORT QUANTITIES ON LINKS FOR ENTIRE TIME PERIOD. */
  
  
  fprintf(fp11, "1\n");/*1H1*/
  for(lct=1; lct<=6; lct++){
    fprintf(fp11, " **********  ");
    fprintf(fp11, "%s", cmc_titl[lct-1] );
  }
  fprintf(fp11, "\n");
  
  fprintf(fp11, "  ENERGY FLOW SUMMARY BY LINK\n\n\n");
  fprintf(fp11, "     YEAR=");
  for(ct=1; ct<=pri_1.ioutx; ct++) {
    if ((((ct-1)%10)==0) && ct>1 )
      fprintf(fp11, "\n          ");
    fprintf(fp11, "%11d", outwr_.laby[ct-1]);
  } 
  fprintf(fp11, "\n");
  
  
  /* CMC       WRITE(11,4319)(ITITL(K),K=1,114),(LABY(J),J=1,IOUTX) */
  /* CMC  4319 FORMAT(1H1,6(/,1X,'**********',2X,19A4), */
  /* CMC      X //,2X,'ENERGY FLOW SUMMARY', */
  /* CMC      1 ' BY LINK',///,5X,'YEAR=',10I11,/,10X,10I11,/,10X,10I11,/ */
  /* CMC      2 ,10X,10I11,/,10X,10I11,/,10X,10I11,/,10X,10I11,/,10X,5I11,//) */
  
  //cmc_dbg();
   
  /* ***** DUMP ZEN(1 FOR ALL YEARS AND LINKS. */
  
  /*<       CALL VISIT(6) >*/
  visit_(&c__6);
  
  /* ***** PRINT PRICE SUMMARY FOR ENTIRE TIME PERIOD. */
  
  /* CMC       WRITE(11,4320)(ITITL(K),K=1,114),(LABY(J),J=1,IOUTX) */
  /* CMC  4320 FORMAT(1H1,6(/,1X,'**********',2X,19A4), */
  /* CMC      A //,2X,'ENERGY PRICE SUMMARY', */
  /* CMC      1 ' BY LINK',///,5X,'YEAR=',10I9,/,10X,10I9,/,10X,10I9,/ */
  /* CMC      2 ,10X,10I9,/,10X,10I9,/,10X,10I9,/,10X,10I9,/,10X,5I9,//) */
  
  fprintf(fp11, "1\n");/*1H1*/
  for(lct=1; lct<=6; lct++){
    fprintf(fp11, " **********  ");
    fprintf(fp11, "%s", cmc_titl[lct-1] );
  }
  fprintf(fp11, "\n");
  
  fprintf(fp11, "  ENERGY PRICE SUMMARY BY LINK\n\n\n");
  fprintf(fp11, "     YEAR=");
  
  
  for(ct=1; ct<=pri_1.ioutx; ct++) {
    if ((((ct-1)%10)==0) && ct>1 )
      fprintf(fp11, "\n          ");
    fprintf(fp11, "%11d", outwr_.laby[ct-1]);
  } 
  fprintf(fp11, "\n");  
  
  /* ***** DUMP ZEN(2 FOR ALL YEARS AND LINKS. */
  
  /*<       CALL VISIT(7) >*/
  visit_(&c__7);
  
  /*<    99 CONTINUE >*/
 L99:
  
  /* ***** INTERFACE WITH LOAD MODULE. */
  
  /*<       IF(ILOD.EQ.1)CALL TOLOD >*/
  if (mode_1.ilod == 1) {
    tolod_();
  }
  
  /* ***** INTERFACE WITH ELECTRIC MODULE. */
  
  /*<       IF(IELE.EQ.1)CALL TOELE >*/
  if (mode_1.iele == 1) {
    toele_();
  }
  
  /* ***** INTERFACE WITH IMPACTS MODULE. */
  
  /* CMC       CLOSE (11)                                      JT6/13/89 */
  fclose(fp11);
  /*<       IF(IMP.EQ.1)CALL TOIMP >*/
  if (mode_1.imp == 1) {
    toimp_();
  }
  
  /*     * * * *      C L O S E    F I L E S      * * * * */
  
  /* CMC       CLOSE (5) */
  /* CMC       CLOSE (6) */
  /* CMC C     CLOSE (11)                                            JT6/13/89 */
  /* CMC       CLOSE (12) */
  /* CMC       CLOSE (13) */
  fclose(fp5);
  fclose(fp6);
  fclose(fp12);
  fclose(fp11);
  fclose(fpPrEcon);
  fclose(fpReEcon);
  fclose(fpEleEcon);
  fclose(elecf);
  
  /*     * * * * * * * * * * * * * * * * * * * * * * * * * */
  
  /*       CHECK ALLOCATION NODES                                          JL 4/96 */
  /*<       CALL ALCHECK() >*/
  alcheck_();
  /*<       STOP 'End of IDES program'                                         >*/
  s_stop("End of IDES program", (ftnlen)19);
  /*<       END >*/
  return 0;
} /* MAIN__ */
