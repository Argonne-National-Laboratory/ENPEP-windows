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



void econRN(void) {

	extern int Roundup(double aValue);
	extern FILE *fp11, *fp6, *fp21, *fpReEcon;
	extern char LinkNodeNames[14][999][6];
	extern char LinkNodeSector[14][999][6];
 
	#define zen_ref(a_1,a_2,a_3) pri_1.zen[((a_3)*999 + (a_2))*2 + a_1 - 2001]
	#define prn_ref(a_1,a_2) ren_1.prn[(a_2)*17 + a_1 - 18]
	#define qrn_ref(a_1,a_2) ren_1.qrn[(a_2)*17 + a_1 - 18]

	double output, tempQ, price;
	int i, j, k, iolk, nSteps;
	int studyEndYear;

	studyEndYear = var_1.iyrb + var_1.nper-1;


	for(i=1;i <= var_1.nnrnp;i++) {
		iolk = ren_1.iourn[i - 1];
		output =  zen_ref(1, iolk, var_1.ntime);
		price = ren_1.noTaxPrice[i-1][var_1.ntime-1];
		nSteps = ren_1.nstep[i - 1];
		ren_1.fuelCost[i-1][var_1.ntime-1]=0;


		for(j=1; j<=nSteps; j++){
			if(output <=  qrn_ref(i, j))
				break;
		}

		switch(j) {
			case 1:
				ren_1.fuelCost[i-1][var_1.ntime-1] = output * prn_ref(i, j);
				break;
			case 2:
				if(j <= nSteps)
					ren_1.fuelCost[i-1][var_1.ntime-1] = qrn_ref(i, 1) * prn_ref(i, 1) +
														(output - qrn_ref(i, 1)) * prn_ref(i, j);
				else
					ren_1.fuelCost[i-1][var_1.ntime-1] = output * prn_ref(i,1);
				break;
			case 3:
				if(j <= nSteps)
					ren_1.fuelCost[i-1][var_1.ntime-1] = qrn_ref(i, 1) * prn_ref(i, 1) +
														(qrn_ref(i, 2) -qrn_ref(i, 1)) * prn_ref(i, 2)+
														(output - qrn_ref(i, 2)) * prn_ref(i, j);
				else
					ren_1.fuelCost[i-1][var_1.ntime-1] = qrn_ref(i, 1) * prn_ref(i, 1) +
														 (output - qrn_ref(i, 1)) * prn_ref(i,2);
				break;
			case 4:
				if(j<=nSteps)
					ren_1.fuelCost[i-1][var_1.ntime-1] = qrn_ref(i, 1) * prn_ref(i, 1) +
														 (qrn_ref(i, 2) - qrn_ref(i, 1)) * prn_ref(i, 2)+
														(qrn_ref(i, 3) - qrn_ref(i, 2)) * prn_ref(i, 3)+
														(output - qrn_ref(i, 3)) * prn_ref(i, j);
				else
					ren_1.fuelCost[i-1][var_1.ntime-1] = qrn_ref(i, 1) * prn_ref(i, 1) +
														(qrn_ref(i, 2) - qrn_ref(i, 1))* prn_ref(i, 2)+
														(output - qrn_ref(i, 2)) * prn_ref(i, 3);
				break;
			case 5:
				if(j <= nSteps)
					ren_1.fuelCost[i-1][var_1.ntime-1] = qrn_ref(i, 1) * prn_ref(i, 1) +
														(qrn_ref(i, 2) - qrn_ref(i, 1)) * prn_ref(i, 2)+
														(qrn_ref(i, 3) - qrn_ref(i, 2)) * prn_ref(i, 3)+
														(qrn_ref(i, 4) - qrn_ref(i, 3)) * prn_ref(i, 4)+
														(output - qrn_ref(i, 4)) * prn_ref(i, j);
				else
					ren_1.fuelCost[i-1][var_1.ntime-1] = qrn_ref(i, 1) * prn_ref(i, 1) +
														 (qrn_ref(i, 2) - qrn_ref(i, 1)) * prn_ref(i, 2)+
														(qrn_ref(i, 3) - qrn_ref(i, 2)) * prn_ref(i, 3)+
														(output - qrn_ref(i, 3)) * prn_ref(i, 4);

				break;
			case 6:
				ren_1.fuelCost[i-1][var_1.ntime-1] =	qrn_ref(i, 1) * prn_ref(i, 1) +
														(qrn_ref(i, 2) - qrn_ref(i, 1)) * prn_ref(i, 2)+
														(qrn_ref(i, 3) - qrn_ref(i, 2)) * prn_ref(i, 3)+
														(qrn_ref(i, 4) - qrn_ref(i, 3)) * prn_ref(i, 4)+
														(output - qrn_ref(i, 4)) * prn_ref(i, 5);

			default :
				printf("Error in Computing Economic Costs\n");
				break;
		}


		ren_1.economicRent[i-1][var_1.ntime-1] = output*price - ren_1.fuelCost[i-1][var_1.ntime-1];

		fprintf(fpReEcon,	"%4d;%s;%s;%s;%15.2f;%10.2f;%15.2f;%15.2f;%4d\n",
						var_1.itime, 
						LinkNodeSector[6][i],
						LinkNodeNames[6][i],
						"RN", 
						output/units_1.unitcnvt[8],
						ren_1.noTaxPrice[i-1][var_1.ntime-1]/units_1.unitcnvt[3],
						ren_1.fuelCost[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						ren_1.economicRent[i-1][var_1.ntime-1]/units_1.unitcnvt[0],
						studyEndYear);
	} // end of for loop

	if(var_1.itime == var_1.iyrb + var_1.nper -1)
		fprintf(fpReEcon, "\n");

} // end of econRN