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



void econMO(void) {

	extern int Roundup(double aValue);
	extern FILE *fp11, *fp6, *fp21, *fpPrEcon;
	extern char LinkNodeNames[14][999][6];
	extern char LinkNodeSector[14][999][6];
 
	#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
	#define iinre_ref(a_1,a_2) ref_1.iinre[(a_2)*30 + a_1 - 31]


	double output, avgCap, avgCF, tci, om;
	int i,j, avgLife, inlk;

	//Multiple Output node
	for(i=1;i <= var_1.nnre;i++) {
		inlk = iinre_ref(i, 1);
		output =  zen_ref(1, inlk, var_1.ntime);
		avgCap = ref_1.capmr[i - 1];
		avgCF = ref_1.cfr[i - 1];
		avgLife = ref_1.lifer[i - 1];
		tci = ref_1.tcir[i - 1];
		om = ref_1.omr[i - 1];


		if(var_1.ntime == 1) {
			ref_1.baseYearLife[i-1] = avgLife;
			ref_1.baseYearCap[i-1] = avgCap;
			ref_1.baseYearCapital[i-1] = tci;
			
			if(avgCap < 0.00001 || avgCF < 0.00001)
				ref_1.opUnits[i-1][var_1.ntime-1] =0;
			else
				ref_1.opUnits[i-1][var_1.ntime-1] = Roundup(output/(avgCap*avgCF));

			ref_1.opCap[i-1][var_1.ntime-1] = ref_1.opUnits[i-1][var_1.ntime-1]*avgCap;
			ref_1.baseUnits[i-1][var_1.ntime-1] = ref_1.opUnits[i-1][var_1.ntime-1];
			ref_1.baseCap[i-1][var_1.ntime-1] = ref_1.opCap[i-1][var_1.ntime-1];
			ref_1.baseSunk[i-1][var_1.ntime-1] = ref_1.baseUnits[i-1][var_1.ntime-1]*tci;
			

			if(avgLife <1)
				ref_1.newUnits[i-1][var_1.ntime-1] =0;
			else
				ref_1.newUnits[i-1][var_1.ntime-1] = Roundup((float)ref_1.opUnits[i-1][var_1.ntime-1]/avgLife);
			
			ref_1.newCap[i-1][var_1.ntime-1] = ref_1.newUnits[i-1][var_1.ntime-1] * avgCap;
		
		// assume that capital cost of new units in base year is sunk cost and add it to existing units sunk cost	
			ref_1.newCapital[i-1][var_1.ntime-1] = 0.0f;
		//	ref_1.newCapital[i-1][var_1.ntime-1] = ref_1.newUnits[i-1][var_1.ntime-1] * tci;

			ref_1.operatingCost[i-1][var_1.ntime-1]=output*om;
			ref_1.existingUnits[i-1][var_1.ntime-1] = ref_1.opUnits[i-1][var_1.ntime-1]  - ref_1.newUnits[i-1][var_1.ntime-1];
			ref_1.existingCap[i-1][var_1.ntime-1] = ref_1.existingUnits[i-1][var_1.ntime-1] * avgCap;
		
		//  add the capital cost of new units in base yaer to sunk cost of exsiting units	
			ref_1.existingSunk[i-1][var_1.ntime-1] = (ref_1.existingUnits[i-1][var_1.ntime-1] + ref_1.newUnits[i-1][var_1.ntime-1] ) * tci;
		//	ref_1.existingSunk[i-1][var_1.ntime-1] = ref_1.existingUnits[i-1][var_1.ntime-1] * tci;
		
			ref_1.demandNotServed[i-1][var_1.ntime-1] = output - ref_1.existingCap[i-1][var_1.ntime-1] * avgCF;
			ref_1.totalCapital[i-1][var_1.ntime-1] = ref_1.newCapital[i-1][var_1.ntime-1] + ref_1.existingSunk[i-1][var_1.ntime-1];
			
			if(ref_1.opUnits[i-1][var_1.ntime-1] <1){
				ref_1.avgInvestment[i-1][var_1.ntime-1] =0.0;
				ref_1.avgCap[i-1][var_1.ntime-1] = 0.0;
			}
			else{
				ref_1.avgInvestment[i-1][var_1.ntime-1] = ref_1.totalCapital[i-1][var_1.ntime-1]/ref_1.opUnits[i-1][var_1.ntime-1];
				ref_1.avgCap[i-1][var_1.ntime-1] = ref_1.opCap[i-1][var_1.ntime-1]/ref_1.opUnits[i-1][var_1.ntime-1];
			}

			if(ref_1.opCap[i-1][var_1.ntime-1] < 0.00001)
				ref_1.avgCF[i-1][var_1.ntime-1] = 0.0;
			else
  				ref_1.avgCF[i-1][var_1.ntime-1] = output/ref_1.opCap[i-1][var_1.ntime-1];
  			
			ref_1.outputCapability[i-1][var_1.ntime-1] = ref_1.opCap[i-1][var_1.ntime-1]*avgCF;
		}
		else {
			if(var_1.ntime < ref_1.baseYearLife[i-1] && ref_1.baseYearLife[i-1] > 0){
				ref_1.baseUnits[i-1][var_1.ntime-1] = Roundup(ref_1.opUnits[i-1][0]*((float)(ref_1.baseYearLife[i-1]-var_1.ntime+1))/((float)ref_1.baseYearLife[i-1]));
			}
			else {
				ref_1.baseUnits[i-1][var_1.ntime-1] = 0;
			}

			ref_1.baseCap[i-1][var_1.ntime-1] = ref_1.baseUnits[i-1][var_1.ntime-1] * ref_1.baseYearCap[i-1];
			ref_1.baseSunk[i-1][var_1.ntime-1] = ref_1.baseUnits[i-1][var_1.ntime-1] * ref_1.baseYearCapital[i-1];
			
			if(var_1.ntime ==2) {
				ref_1.existingUnits[i-1][var_1.ntime-1] = ref_1.baseUnits[i-1][var_1.ntime-1];  
				ref_1.existingCap[i-1][var_1.ntime-1] = ref_1.baseCap[i-1][var_1.ntime-1];
				ref_1.existingSunk[i-1][var_1.ntime-1] = ref_1.baseSunk[i-1][var_1.ntime-1];
			}
			else {
				ref_1.existingUnits[i-1][var_1.ntime-1] = ref_1.baseUnits[i-1][var_1.ntime-1]+ref_1.existingUnits[i-1][var_1.ntime-1];  
				ref_1.existingCap[i-1][var_1.ntime-1] = ref_1.baseCap[i-1][var_1.ntime-1]+ref_1.existingCap[i-1][var_1.ntime-1];
				ref_1.existingSunk[i-1][var_1.ntime-1] = ref_1.baseSunk[i-1][var_1.ntime-1] + ref_1.existingSunk[i-1][var_1.ntime-1];
			}
			
			
			ref_1.demandNotServed[i-1][var_1.ntime-1] = output - ref_1.existingCap[i-1][var_1.ntime-1] * avgCF;
			
			if(ref_1.demandNotServed[i-1][var_1.ntime-1] > 0) {
				if(avgCF < 0.00001 || avgCap < 0.000001)
					ref_1.newUnits[i-1][var_1.ntime-1] =0;
				else {
					if(Roundup((ref_1.existingCap[i-1][var_1.ntime-1]+
						ref_1.demandNotServed[i-1][var_1.ntime-1]/avgCF)/avgCap) > ref_1.existingUnits[i-1][var_1.ntime-1]){

						ref_1.newUnits[i-1][var_1.ntime-1] =Roundup((ref_1.existingCap[i-1][var_1.ntime-1]+
															ref_1.demandNotServed[i-1][var_1.ntime-1]/avgCF)/avgCap) - ref_1.existingUnits[i-1][var_1.ntime-1];
					}
					else {
						ref_1.newUnits[i-1][var_1.ntime-1] =1;
					}
				}
			}
			else {
				ref_1.newUnits[i-1][var_1.ntime-1] =0;
			}
	
			ref_1.operatingCost[i-1][var_1.ntime-1] =output*om;
			ref_1.opUnits[i-1][var_1.ntime-1] = ref_1.existingUnits[i-1][var_1.ntime-1] + ref_1.newUnits[i-1][var_1.ntime-1];
			
			if(ref_1.newUnits[i-1][var_1.ntime-1] >0) {
				ref_1.newCap[i-1][var_1.ntime-1] = avgCap * ref_1.opUnits[i-1][var_1.ntime-1] - ref_1.existingCap[i-1][var_1.ntime-1];
			}
			else {
				ref_1.newCap[i-1][var_1.ntime-1] =0;
			}

			ref_1.opCap[i-1][var_1.ntime-1] = ref_1.existingCap[i-1][var_1.ntime-1] + ref_1.newCap[i-1][var_1.ntime-1];

			if(ref_1.newUnits[i-1][var_1.ntime-1] >0) {
				if(tci*ref_1.opUnits[i-1][var_1.ntime-1] > ref_1.existingSunk[i-1][var_1.ntime-1]) {
					ref_1.newCapital[i-1][var_1.ntime-1] = tci*ref_1.opUnits[i-1][var_1.ntime-1] - ref_1.existingSunk[i-1][var_1.ntime-1];
				}
				else {
					ref_1.newCapital[i-1][var_1.ntime-1] =0;
				}
			}
			else{
				ref_1.newCapital[i-1][var_1.ntime-1] =0;
			}


			ref_1.totalCapital[i-1][var_1.ntime-1] = ref_1.newCapital[i-1][var_1.ntime-1] + ref_1.existingSunk[i-1][var_1.ntime-1];

			if(ref_1.opUnits[i-1][var_1.ntime-1] >0){
				ref_1.avgInvestment[i-1][var_1.ntime-1] = ref_1.totalCapital[i-1][var_1.ntime-1]/ref_1.opUnits[i-1][var_1.ntime-1];
  				ref_1.avgCap[i-1][var_1.ntime-1] = ref_1.opCap[i-1][var_1.ntime-1]/ref_1.opUnits[i-1][var_1.ntime-1];
			}
			else{
				ref_1.avgInvestment[i-1][var_1.ntime-1] =0.0;
				ref_1.avgCap[i-1][var_1.ntime-1] = 0.0;
			}

			if(ref_1.opCap[i-1][var_1.ntime-1] < 0.00001)
				ref_1.avgCF[i-1][var_1.ntime-1] = 0.0;
			else
				ref_1.avgCF[i-1][var_1.ntime-1] = output/ref_1.opCap[i-1][var_1.ntime-1];
  			
			ref_1.outputCapability[i-1][var_1.ntime-1] =ref_1.opCap[i-1][var_1.ntime-1]*avgCF;

			if(var_1.ntime >2){
				for(j=1; j<avgLife;j++){
					ref_1.existingUnits[i-1][var_1.ntime-1+j] = ref_1.existingUnits[i-1][var_1.ntime-1+j] + ref_1.newUnits[i-1][var_1.ntime-1];
					ref_1.existingCap[i-1][var_1.ntime-1+j]  = ref_1.existingCap[i-1][var_1.ntime-1+j] + ref_1.newCap[i-1][var_1.ntime-1];
					ref_1.existingSunk[i-1][var_1.ntime-1+j] = ref_1.existingSunk[i-1][var_1.ntime-1+j] + ref_1.newCapital[i-1][var_1.ntime-1];
				}
			}


		}
		

		fprintf(fpPrEcon,	"%4d;%s;%s;%s;%10.2f;%10.2f;%10.2f;%10.2f;%4d;%4d;%10.2f;%4d;%10.2f;%10.2f;%4d;%10.2f;%10.2f;%10.2f;%4d;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f;%10.2f\n",
						var_1.itime, 
						LinkNodeSector[5][i],
						LinkNodeNames[5][i],
						"MO", 
						output/units_1.unitcnvt[8],
						avgCap/units_1.unitcnvt[8],
						tci/units_1.unitcnvt[0],
						avgCF,
						avgLife,
						ref_1.opUnits[i-1][var_1.ntime-1],
						ref_1.opCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						ref_1.baseUnits[i-1][var_1.ntime-1],
						ref_1.baseCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						ref_1.baseSunk[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						ref_1.existingUnits[i-1][var_1.ntime-1],
						ref_1.existingCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						ref_1.existingSunk[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						ref_1.demandNotServed[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						ref_1.newUnits[i-1][var_1.ntime-1],
						ref_1.newCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						ref_1.newCapital[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						ref_1.operatingCost[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						ref_1.totalCapital[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						ref_1.avgInvestment[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						ref_1.avgCap[i-1][var_1.ntime-1]/units_1.unitcnvt[8],
						ref_1.avgCF[i-1][var_1.ntime-1],
						ref_1.outputCapability[i-1][var_1.ntime-1]/units_1.unitcnvt[8]);


	} // end of for loop
	if(var_1.itime == var_1.iyrb + var_1.nper -1)
		fprintf(fpPrEcon, "\n");


} // end of econMO