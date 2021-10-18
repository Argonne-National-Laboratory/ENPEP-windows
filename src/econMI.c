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



void econMI(void) {

	extern int Roundup(double aValue);
	extern FILE *fp11, *fp6, *fp21, *fpPrEcon;
	extern char LinkNodeNames[14][999][6];
	extern char LinkNodeSector[14][999][6];
 
	#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]

	double output, avgCap, avgCF, tci, om;
	int i,j, avgLife, iolk;



	//process conversion node
	for(i=1;i <= var_1.nnmi;i++) {
		iolk = min_1.ioumi[i - 1];
		output =  zen_ref(1, iolk, var_1.ntime);
		avgCap = min_1.capmm[i - 1];
		avgCF = min_1.cfm[i - 1];
		avgLife = min_1.lifem[i - 1];
		tci = min_1.tcim[i - 1];
		om = min_1.omm[i - 1];




		if(var_1.ntime == 1) {
			min_1.baseYearLife[i-1] = avgLife;
			min_1.baseYearCap[i-1] = avgCap;
			min_1.baseYearCapital[i-1] = tci;

			if(avgCap < 0.00001 || avgCF < 0.00001)
				min_1.opUnits[i-1][var_1.ntime-1] = 0;
			else
				min_1.opUnits[i-1][var_1.ntime-1] = Roundup(output/(avgCap*avgCF));
			
			min_1.opCap[i-1][var_1.ntime-1] = min_1.opUnits[i-1][var_1.ntime-1]*avgCap;
			min_1.baseUnits[i-1][var_1.ntime-1] = min_1.opUnits[i-1][var_1.ntime-1];
			min_1.baseCap[i-1][var_1.ntime-1] = min_1.opCap[i-1][var_1.ntime-1];
			min_1.baseSunk[i-1][var_1.ntime-1] = min_1.baseUnits[i-1][var_1.ntime-1]*tci;


			if(avgLife <1)
				min_1.newUnits[i-1][var_1.ntime-1] =0;
			else
				min_1.newUnits[i-1][var_1.ntime-1] = Roundup((float)min_1.opUnits[i-1][var_1.ntime-1]/avgLife);
			
			min_1.newCap[i-1][var_1.ntime-1] = min_1.newUnits[i-1][var_1.ntime-1] * avgCap;
		
		// assume that capital cost of new units in base year is sunk cost and add it to existing units sunk cost
			min_1.newCapital[i-1][var_1.ntime-1] = 0.0f;
		//	min_1.newCapital[i-1][var_1.ntime-1] = min_1.newUnits[i-1][var_1.ntime-1] * tci;
			
			min_1.operatingCost[i-1][var_1.ntime-1]=output*om;
			min_1.existingUnits[i-1][var_1.ntime-1] = min_1.opUnits[i-1][var_1.ntime-1]  - min_1.newUnits[i-1][var_1.ntime-1];
			min_1.existingCap[i-1][var_1.ntime-1] = min_1.existingUnits[i-1][var_1.ntime-1] * avgCap;
		
		//  add the capital cost of new units in base yaer to sunk cost of exsiting units
			min_1.existingSunk[i-1][var_1.ntime-1] = (min_1.existingUnits[i-1][var_1.ntime-1] + min_1.newUnits[i-1][var_1.ntime-1]) * tci;
		//	min_1.existingSunk[i-1][var_1.ntime-1] = min_1.existingUnits[i-1][var_1.ntime-1] * tci;
		
			min_1.demandNotServed[i-1][var_1.ntime-1] = output - min_1.existingCap[i-1][var_1.ntime-1] * avgCF;
			min_1.totalCapital[i-1][var_1.ntime-1] = min_1.newCapital[i-1][var_1.ntime-1] + min_1.existingSunk[i-1][var_1.ntime-1];
			
			if(min_1.opUnits[i-1][var_1.ntime-1] >0){
				min_1.avgInvestment[i-1][var_1.ntime-1] = min_1.totalCapital[i-1][var_1.ntime-1]/min_1.opUnits[i-1][var_1.ntime-1];
  				min_1.avgCap[i-1][var_1.ntime-1] = min_1.opCap[i-1][var_1.ntime-1]/min_1.opUnits[i-1][var_1.ntime-1];
			}
			else {
				min_1.avgInvestment[i-1][var_1.ntime-1] = 0.0;
				min_1.avgCap[i-1][var_1.ntime-1] = 0.0;
			}

			if(min_1.opCap[i-1][var_1.ntime-1] < 0.00001)
				min_1.avgCF[i-1][var_1.ntime-1] = 0.0;
			else
				min_1.avgCF[i-1][var_1.ntime-1] = output/min_1.opCap[i-1][var_1.ntime-1];
  			
			min_1.outputCapability[i-1][var_1.ntime-1] =min_1.opCap[i-1][var_1.ntime-1]*avgCF;
		}
		else {
			if(var_1.ntime < min_1.baseYearLife[i-1] && min_1.baseYearLife[i-1] >0){
				min_1.baseUnits[i-1][var_1.ntime-1] = Roundup(min_1.opUnits[i-1][0]*((float)(min_1.baseYearLife[i-1]-var_1.ntime+1))/((float)min_1.baseYearLife[i-1]));
			}
			else {
				min_1.baseUnits[i-1][var_1.ntime-1] = 0;
			}

			min_1.baseCap[i-1][var_1.ntime-1] = min_1.baseUnits[i-1][var_1.ntime-1] * min_1.baseYearCap[i-1];
			min_1.baseSunk[i-1][var_1.ntime-1] = min_1.baseUnits[i-1][var_1.ntime-1] * min_1.baseYearCapital[i-1];
			
			if(var_1.ntime ==2) {
				min_1.existingUnits[i-1][var_1.ntime-1] = min_1.baseUnits[i-1][var_1.ntime-1];  
				min_1.existingCap[i-1][var_1.ntime-1] = min_1.baseCap[i-1][var_1.ntime-1];
				min_1.existingSunk[i-1][var_1.ntime-1] = min_1.baseSunk[i-1][var_1.ntime-1];
			}
			else {
				min_1.existingUnits[i-1][var_1.ntime-1] = min_1.baseUnits[i-1][var_1.ntime-1]+min_1.existingUnits[i-1][var_1.ntime-1];  
				min_1.existingCap[i-1][var_1.ntime-1] = min_1.baseCap[i-1][var_1.ntime-1]+min_1.existingCap[i-1][var_1.ntime-1];
				min_1.existingSunk[i-1][var_1.ntime-1] = min_1.baseSunk[i-1][var_1.ntime-1] + min_1.existingSunk[i-1][var_1.ntime-1];
			}
			
			
			min_1.demandNotServed[i-1][var_1.ntime-1] = output - min_1.existingCap[i-1][var_1.ntime-1] * avgCF;
			
			if(min_1.demandNotServed[i-1][var_1.ntime-1] > 0) {
				if(avgCF < 0.00001 || avgCap < 0.000001)
						min_1.newUnits[i-1][var_1.ntime-1] =0;
				else {
					if(Roundup((min_1.existingCap[i-1][var_1.ntime-1]+
						min_1.demandNotServed[i-1][var_1.ntime-1]/avgCF)/avgCap) > min_1.existingUnits[i-1][var_1.ntime-1]){

						min_1.newUnits[i-1][var_1.ntime-1] =Roundup((min_1.existingCap[i-1][var_1.ntime-1]+
															min_1.demandNotServed[i-1][var_1.ntime-1]/avgCF)/avgCap) - min_1.existingUnits[i-1][var_1.ntime-1];
					}
					else {
						min_1.newUnits[i-1][var_1.ntime-1] =1;
					}
				}
			}
			else {
				min_1.newUnits[i-1][var_1.ntime-1] =0;
			}
	
			min_1.operatingCost[i-1][var_1.ntime-1] =output*om;
			min_1.opUnits[i-1][var_1.ntime-1] = min_1.existingUnits[i-1][var_1.ntime-1] + min_1.newUnits[i-1][var_1.ntime-1];
			
			if(min_1.newUnits[i-1][var_1.ntime-1] >0) {
				min_1.newCap[i-1][var_1.ntime-1] = avgCap * min_1.opUnits[i-1][var_1.ntime-1] - min_1.existingCap[i-1][var_1.ntime-1];
			}
			else {
				min_1.newCap[i-1][var_1.ntime-1] =0;
			}

			min_1.opCap[i-1][var_1.ntime-1] = min_1.existingCap[i-1][var_1.ntime-1] + min_1.newCap[i-1][var_1.ntime-1];

			if(min_1.newUnits[i-1][var_1.ntime-1] >0) {
				if(tci*min_1.opUnits[i-1][var_1.ntime-1] > min_1.existingSunk[i-1][var_1.ntime-1]) {
					min_1.newCapital[i-1][var_1.ntime-1] = tci*min_1.opUnits[i-1][var_1.ntime-1] - min_1.existingSunk[i-1][var_1.ntime-1];
				}
				else {
					min_1.newCapital[i-1][var_1.ntime-1] =0;
				}
			}
			else{
				min_1.newCapital[i-1][var_1.ntime-1] =0;
			}


			min_1.totalCapital[i-1][var_1.ntime-1] = min_1.newCapital[i-1][var_1.ntime-1] + min_1.existingSunk[i-1][var_1.ntime-1];
			
			if(min_1.opUnits[i-1][var_1.ntime-1] >0){
				min_1.avgInvestment[i-1][var_1.ntime-1] = min_1.totalCapital[i-1][var_1.ntime-1]/min_1.opUnits[i-1][var_1.ntime-1];
  				min_1.avgCap[i-1][var_1.ntime-1] = min_1.opCap[i-1][var_1.ntime-1]/min_1.opUnits[i-1][var_1.ntime-1];
			}
			else{
				min_1.avgInvestment[i-1][var_1.ntime-1] = 0.0;
				min_1.avgCap[i-1][var_1.ntime-1] = 0.0;
			}

			if(min_1.opCap[i-1][var_1.ntime-1] < 0.00001)
				min_1.avgCF[i-1][var_1.ntime-1] =0.0;
			else
				min_1.avgCF[i-1][var_1.ntime-1] = output/min_1.opCap[i-1][var_1.ntime-1];
  			
			min_1.outputCapability[i-1][var_1.ntime-1] =min_1.opCap[i-1][var_1.ntime-1]*avgCF;

			if(var_1.ntime >2){
				for(j=1; j<avgLife;j++){
					min_1.existingUnits[i-1][var_1.ntime-1+j] = min_1.existingUnits[i-1][var_1.ntime-1+j] + min_1.newUnits[i-1][var_1.ntime-1];
					min_1.existingCap[i-1][var_1.ntime-1+j]  = min_1.existingCap[i-1][var_1.ntime-1+j] + min_1.newCap[i-1][var_1.ntime-1];
					min_1.existingSunk[i-1][var_1.ntime-1+j] = min_1.existingSunk[i-1][var_1.ntime-1+j] + min_1.newCapital[i-1][var_1.ntime-1];
				}
			}


		}
		

		fprintf(fpPrEcon,	"%4d;%s;%s;%s;%10.2f;%10.2f;%10.2f;%10.2f;%4d;%4d;%10.2f;%4d;%10.2f;%10.2f;%4d;%10.2f;%10.2f;%10.2f;%4d;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f\n",
						var_1.itime, 
						LinkNodeSector[2][i],
						LinkNodeNames[2][i],
						"MI", 
						output/units_1.unitcnvt[8],
						avgCap/units_1.unitcnvt[8],
						tci/units_1.unitcnvt[0],
						avgCF,
						avgLife,
						min_1.opUnits[i-1][var_1.ntime-1],
						min_1.opCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						min_1.baseUnits[i-1][var_1.ntime-1],
						min_1.baseCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						min_1.baseSunk[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						min_1.existingUnits[i-1][var_1.ntime-1],
						min_1.existingCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						min_1.existingSunk[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						min_1.demandNotServed[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						min_1.newUnits[i-1][var_1.ntime-1],
						min_1.newCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						min_1.newCapital[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						min_1.operatingCost[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						min_1.totalCapital[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						min_1.avgInvestment[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						min_1.avgCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						min_1.avgCF[i-1][var_1.ntime-1],
						min_1.outputCapability[i-1][var_1.ntime-1]/units_1.unitcnvt[8]);


	} // end of for loop

} // end of econMI