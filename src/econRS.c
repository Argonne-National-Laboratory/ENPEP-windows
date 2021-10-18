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



void econRS(void) {

	extern int Roundup(double aValue);
	extern FILE *fp11, *fp6, *fp21, *fpReEcon;
	extern char LinkNodeNames[14][999][6];
	extern char LinkNodeSector[14][999][6];

	#define pprj_ref(a_1,a_2) res_1.pprj[(a_2)*75 + a_1 - 76]
	#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]

	double q, p1, p2;
	int i, iolk;
	integer ks;
	real rat;

	int studyEndYear;

	studyEndYear = var_1.iyrb + var_1.nper-1;


	for(i=1;i <= var_1.nnrep;i++) {
		iolk = res_1.iours[i - 1];
		
		if(var_1.ntime == 1){
			q =  zen_ref(1, iolk, var_1.ntime);
			p1 = res_1.a[i - 1] - (res_1.b[i - 1]*q + res_1.ab[i - 1]*q*q); // price before baseyear
			p2 = res_1.noTaxPrice[i-1][var_1.ntime-1];
			res_1.fuelCost[i-1][var_1.ntime-1] =	p1*(q) + 
													res_1.b[i - 1]*(q*q)/2 +  
													res_1.ab[i - 1]*(q*q*q)/3;

			res_1.economicRent[i-1][var_1.ntime-1] = q*p2 - res_1.fuelCost[i-1][var_1.ntime-1];
		}
		else {
			q =  zen_ref(1, iolk, var_1.ntime);
			p1 = res_1.noTaxPrice[i-1][var_1.ntime-2]; //previous year price
			p2 = res_1.noTaxPrice[i-1][var_1.ntime-1]; // current year price

			ks = res_1.kpr[i - 1];
			rat = pprj_ref(ks, var_1.ntime - 1) + 1.f;
			
			res_1.fuelCost[i-1][var_1.ntime-1] =	p1 * rat * (q) + 
													res_1.b[i - 1]*(q*q)/2 +
													res_1.ab[i - 1]*(q*q*q)/3; 

			res_1.economicRent[i-1][var_1.ntime-1] = (q)*p2 - res_1.fuelCost[i-1][var_1.ntime-1];

		}

		fprintf(fpReEcon,	"%4d;%s;%s;%s;%15.2f;%10.2f;%15.2f;%15.2f;%4d\n",
						var_1.itime, 
						LinkNodeSector[7][i],
						LinkNodeNames[7][i],
						"RS",  
						q/units_1.unitcnvt[8],
						res_1.noTaxPrice[i-1][var_1.ntime-1]/units_1.unitcnvt[3],
						res_1.fuelCost[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						res_1.economicRent[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						studyEndYear);
	} // end of for loop

	

} // end of econRS