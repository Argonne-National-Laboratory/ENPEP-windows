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
#include <math.h>
#include "cmc_f2c.h"
#include <stdlib.h>
#include "f2c.h"
#include "structures.h"



void econPR(void) {

	extern int Roundup(double aValue);
	extern FILE *fp11, *fp6, *fp21, *fpPrEcon;
	extern char LinkNodeNames[14][999][6];
	extern char LinkNodeSector[14][999][6];
 
	#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]

	double output, avgCap, avgCF, tci, om, temp;
	int i,j, avgLife, iolk, nPlants;

	//process conversion node
	for(i=1;i <= var_1.nnpr;i++) {
		iolk = pro_1.ioupr[i - 1];
		output =  zen_ref(1, iolk, var_1.ntime);
		avgCap = pro_1.capm[i - 1];
		avgCF = pro_1.cf[i - 1];
		avgLife = pro_1.life[i - 1];
		tci = pro_1.tci[i - 1];
		om = pro_1.om[i - 1];


		if(var_1.ntime == 1) {
			pro_1.baseYearLife[i-1] = avgLife;
			pro_1.baseYearCap[i-1] = avgCap;
			pro_1.baseYearCapital[i-1] = tci;

			if(avgCap < 0.00001 || avgCF < 0.00001)
				pro_1.opUnits[i-1][var_1.ntime-1] = 0;
			else
				pro_1.opUnits[i-1][var_1.ntime-1] = Roundup(output/(avgCap*avgCF));

			pro_1.opCap[i-1][var_1.ntime-1] = pro_1.opUnits[i-1][var_1.ntime-1]*avgCap;
			pro_1.baseUnits[i-1][var_1.ntime-1] = pro_1.opUnits[i-1][var_1.ntime-1];
			pro_1.baseCap[i-1][var_1.ntime-1] = pro_1.opCap[i-1][var_1.ntime-1];
			pro_1.baseSunk[i-1][var_1.ntime-1] = pro_1.baseUnits[i-1][var_1.ntime-1]*tci;
			

			if(avgLife < 1)
				pro_1.newUnits[i-1][var_1.ntime-1] =0;
			else
				pro_1.newUnits[i-1][var_1.ntime-1] = Roundup((float)pro_1.opUnits[i-1][var_1.ntime-1]/avgLife);
			
			pro_1.newCap[i-1][var_1.ntime-1] = pro_1.newUnits[i-1][var_1.ntime-1] * avgCap;
		
		// assume that capital cost of new units in base year is sunk cost and add it to existing units sunk cost	
			pro_1.newCapital[i-1][var_1.ntime-1] = 0.0f;
		//	pro_1.newCapital[i-1][var_1.ntime-1] = pro_1.newUnits[i-1][var_1.ntime-1] * tci;
			
			pro_1.operatingCost[i-1][var_1.ntime-1]=output*om;
			pro_1.existingUnits[i-1][var_1.ntime-1] = pro_1.opUnits[i-1][var_1.ntime-1]  - pro_1.newUnits[i-1][var_1.ntime-1];
			pro_1.existingCap[i-1][var_1.ntime-1] = pro_1.existingUnits[i-1][var_1.ntime-1] * avgCap;
		
		//  add the capital cost of new units in base yaer to sunk cost of exsiting units	
			pro_1.existingSunk[i-1][var_1.ntime-1] = (pro_1.existingUnits[i-1][var_1.ntime-1] + pro_1.newUnits[i-1][var_1.ntime-1]) * tci;
		//	pro_1.existingSunk[i-1][var_1.ntime-1] = pro_1.existingUnits[i-1][var_1.ntime-1] * tci;
		
			pro_1.demandNotServed[i-1][var_1.ntime-1] = output - pro_1.existingCap[i-1][var_1.ntime-1] * avgCF;
			pro_1.totalCapital[i-1][var_1.ntime-1] = pro_1.newCapital[i-1][var_1.ntime-1] + pro_1.existingSunk[i-1][var_1.ntime-1];
			
			if(pro_1.opUnits[i-1][var_1.ntime-1] < 1) {
			  	pro_1.avgInvestment[i-1][var_1.ntime-1] =0.0;	
				pro_1.avgCap[i-1][var_1.ntime-1] =0;
			}
			else {
				pro_1.avgInvestment[i-1][var_1.ntime-1] = pro_1.totalCapital[i-1][var_1.ntime-1]/pro_1.opUnits[i-1][var_1.ntime-1];
				pro_1.avgCap[i-1][var_1.ntime-1] = pro_1.opCap[i-1][var_1.ntime-1]/pro_1.opUnits[i-1][var_1.ntime-1];	
			}

			if(pro_1.opCap[i-1][var_1.ntime-1] < 0.00001)
				pro_1.avgCF[i-1][var_1.ntime-1] =0;
			else
				pro_1.avgCF[i-1][var_1.ntime-1] = output/pro_1.opCap[i-1][var_1.ntime-1];

  			pro_1.outputCapability[i-1][var_1.ntime-1] =pro_1.opCap[i-1][var_1.ntime-1]*avgCF;
		}
		else {
			if(var_1.ntime < pro_1.baseYearLife[i-1] && pro_1.baseYearLife[i-1] > 0){
				pro_1.baseUnits[i-1][var_1.ntime-1] = Roundup(pro_1.opUnits[i-1][0]*((float)(pro_1.baseYearLife[i-1]-var_1.ntime+1))/((float)pro_1.baseYearLife[i-1]));
			}
			else {
				pro_1.baseUnits[i-1][var_1.ntime-1] = 0;
			}

			pro_1.baseCap[i-1][var_1.ntime-1] = pro_1.baseUnits[i-1][var_1.ntime-1] * pro_1.baseYearCap[i-1];
			pro_1.baseSunk[i-1][var_1.ntime-1] = pro_1.baseUnits[i-1][var_1.ntime-1] * pro_1.baseYearCapital[i-1];
			
			if(var_1.ntime ==2) {
				pro_1.existingUnits[i-1][var_1.ntime-1] = pro_1.baseUnits[i-1][var_1.ntime-1];  
				pro_1.existingCap[i-1][var_1.ntime-1] = pro_1.baseCap[i-1][var_1.ntime-1];
				pro_1.existingSunk[i-1][var_1.ntime-1] = pro_1.baseSunk[i-1][var_1.ntime-1];
			}
			else {
				pro_1.existingUnits[i-1][var_1.ntime-1] = pro_1.baseUnits[i-1][var_1.ntime-1]+pro_1.existingUnits[i-1][var_1.ntime-1];  
				pro_1.existingCap[i-1][var_1.ntime-1] = pro_1.baseCap[i-1][var_1.ntime-1]+pro_1.existingCap[i-1][var_1.ntime-1];
				pro_1.existingSunk[i-1][var_1.ntime-1] = pro_1.baseSunk[i-1][var_1.ntime-1] + pro_1.existingSunk[i-1][var_1.ntime-1];
			}
			
			
			pro_1.demandNotServed[i-1][var_1.ntime-1] = output - pro_1.existingCap[i-1][var_1.ntime-1] * avgCF;
			
			if(pro_1.demandNotServed[i-1][var_1.ntime-1] > 0) {
				if(avgCF < 0.00001 || avgCap < 0.00001)
					pro_1.newUnits[i-1][var_1.ntime-1] =0;
				else {
					if(Roundup((pro_1.existingCap[i-1][var_1.ntime-1]+
						pro_1.demandNotServed[i-1][var_1.ntime-1]/avgCF)/avgCap) > pro_1.existingUnits[i-1][var_1.ntime-1]){

						pro_1.newUnits[i-1][var_1.ntime-1] =Roundup((pro_1.existingCap[i-1][var_1.ntime-1]+
															pro_1.demandNotServed[i-1][var_1.ntime-1]/avgCF)/avgCap) - pro_1.existingUnits[i-1][var_1.ntime-1];
					}
					else {
						pro_1.newUnits[i-1][var_1.ntime-1] =1;
					}
				}
			}
			else {
				pro_1.newUnits[i-1][var_1.ntime-1] =0;
			}
	
			pro_1.operatingCost[i-1][var_1.ntime-1] =output*om;
			pro_1.opUnits[i-1][var_1.ntime-1] = pro_1.existingUnits[i-1][var_1.ntime-1] + pro_1.newUnits[i-1][var_1.ntime-1];
			
			if(pro_1.newUnits[i-1][var_1.ntime-1] >0) {
				pro_1.newCap[i-1][var_1.ntime-1] = avgCap * pro_1.opUnits[i-1][var_1.ntime-1] - pro_1.existingCap[i-1][var_1.ntime-1];
			}
			else {
				pro_1.newCap[i-1][var_1.ntime-1] =0;
			}

			pro_1.opCap[i-1][var_1.ntime-1] = pro_1.existingCap[i-1][var_1.ntime-1] + pro_1.newCap[i-1][var_1.ntime-1];

			if(pro_1.newUnits[i-1][var_1.ntime-1] >0) {
				if(tci*pro_1.opUnits[i-1][var_1.ntime-1] > pro_1.existingSunk[i-1][var_1.ntime-1]) {
					pro_1.newCapital[i-1][var_1.ntime-1] = tci*pro_1.opUnits[i-1][var_1.ntime-1] - pro_1.existingSunk[i-1][var_1.ntime-1];
				}
				else {
					pro_1.newCapital[i-1][var_1.ntime-1] =0;
				}
			}
			else{
				pro_1.newCapital[i-1][var_1.ntime-1] =0;
			}


			pro_1.totalCapital[i-1][var_1.ntime-1] = pro_1.newCapital[i-1][var_1.ntime-1] + pro_1.existingSunk[i-1][var_1.ntime-1];
			
			if(pro_1.opUnits[i-1][var_1.ntime-1] >0){
				pro_1.avgInvestment[i-1][var_1.ntime-1] = pro_1.totalCapital[i-1][var_1.ntime-1]/pro_1.opUnits[i-1][var_1.ntime-1];
  				pro_1.avgCap[i-1][var_1.ntime-1] = pro_1.opCap[i-1][var_1.ntime-1]/pro_1.opUnits[i-1][var_1.ntime-1];
			}
			else{
				pro_1.avgInvestment[i-1][var_1.ntime-1]=0.0;
				pro_1.avgCap[i-1][var_1.ntime-1] =0.0;
			}
			
			if(pro_1.opCap[i-1][var_1.ntime-1] < 0.00001)
				pro_1.avgCF[i-1][var_1.ntime-1] = 0.0;
			else
				pro_1.avgCF[i-1][var_1.ntime-1] = output/pro_1.opCap[i-1][var_1.ntime-1];

  			pro_1.outputCapability[i-1][var_1.ntime-1] =pro_1.opCap[i-1][var_1.ntime-1]*avgCF;

			if(var_1.ntime >2){
				for(j=1; j<avgLife;j++){
					pro_1.existingUnits[i-1][var_1.ntime-1+j] = pro_1.existingUnits[i-1][var_1.ntime-1+j] + pro_1.newUnits[i-1][var_1.ntime-1];
					pro_1.existingCap[i-1][var_1.ntime-1+j]  = pro_1.existingCap[i-1][var_1.ntime-1+j] + pro_1.newCap[i-1][var_1.ntime-1];
					pro_1.existingSunk[i-1][var_1.ntime-1+j] = pro_1.existingSunk[i-1][var_1.ntime-1+j] + pro_1.newCapital[i-1][var_1.ntime-1];
				}
			}


		}
		
	//	fprintf(fpPrEcon,"Year Sec   Node  Type Quantity AvgCap AvgCapital AvgCF AvgLife opUnits opCap baseUnits baseCap baseSunk existingUnits existingCap existingSunk, dNotServed newUnits newCap newCapital operatingCost totalCap avgInvst avgCap avgCF effOutput\n");


		fprintf(fpPrEcon,	"%4d;%s;%s;%s;%10.2f;%10.2f;%10.2f;%10.2f;%4d;%4d;%10.2f;%4d;%10.2f;%10.2f;%4d;%10.2f;%10.2f;%10.2f;%4d;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f\n",
						var_1.itime, 
						LinkNodeSector[4][i],
						LinkNodeNames[4][i],
						"PR", 
						output/units_1.unitcnvt[8],
						avgCap/units_1.unitcnvt[8],
						tci/units_1.unitcnvt[0],
						avgCF,
						avgLife,
						pro_1.opUnits[i-1][var_1.ntime-1],
						pro_1.opCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						pro_1.baseUnits[i-1][var_1.ntime-1],
						pro_1.baseCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						pro_1.baseSunk[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						pro_1.existingUnits[i-1][var_1.ntime-1],
						pro_1.existingCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						pro_1.existingSunk[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						pro_1.demandNotServed[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						pro_1.newUnits[i-1][var_1.ntime-1],
						pro_1.newCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						pro_1.newCapital[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						pro_1.operatingCost[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						pro_1.totalCapital[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						pro_1.avgInvestment[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						pro_1.avgCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						pro_1.avgCF[i-1][var_1.ntime-1],
						pro_1.outputCapability[i-1][var_1.ntime-1]/units_1.unitcnvt[8]);


	} // end of for loop

	

} // end of econPR