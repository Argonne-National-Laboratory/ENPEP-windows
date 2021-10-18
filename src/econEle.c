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


void econEle(void) {

	extern int Roundup(double aValue);
	extern FILE *fp11, *fp6, *fp21, *fpEleEcon;
	extern char LinkNodeNames[14][999][6];
	extern char LinkNodeSector[14][999][6];

	

	double baseCap, capital, varOM, fixedOM, generation;
	int  i, j, onlineYear, retireYear, thermalUnits; 
	char sector[6];

	thermalUnits =0;
	for(i=1; i<=elec_1.nunit; i++){

		if(elec5_1.unittype[i-1] ==1){
			++thermalUnits;
			strcpy(sector, LinkNodeSector[11][i]);
		}
		else{
			strcpy(sector, LinkNodeSector[12][i-thermalUnits]);
		}


		onlineYear = elec1_1.iyrf[i - 1];
		retireYear = elec1_1.iyrr[i - 1];

		if(var_1.itime >= onlineYear && var_1.itime <= retireYear){
			baseCap = elec1_1.basecap[i - 1];
			varOM = elec1_1.omb[i-1];
			fixedOM = elec1_1.oma[i-1];
			generation = elec1_1.generation[i-1];
		}
		else {
			baseCap = 0.0;
			varOM = 0.0;
			fixedOM = 0.0;
			generation = 0.0;
		}

		if(var_1.itime == elec1_1.iyrf[i - 1])
			capital = elec1_1.baseCapital[i - 1];
		else
			capital=0.0;

		
		//get the capital cost for unit conversion
		for(j=1; j<=elec3_1.munit; j++) {
			if(strcmp(elec1_1.unitname[i-1],elec2_1.unitname[j-1])==0 && elec5_1.unitnumber[i-1] == elec2_1.ic1[j-1] ) {
					if (elec2_1.ic11[j - 1] == var_1.itime)
						capital = elec2_1.rc5[i - 1];
			}
		}


		//Year unitnumber unitname type capacity capital fixedOM variableOM generation onlineyear retireyear

		fprintf(fpEleEcon,	"%4d;%s;%s;%s;%10.2f;%10.2f;%10.2f;%10.2f;%15.2f;%4d;%4d\n", 
				var_1.itime, 
				sector,
				elec5_1.unitname[i-1],"Ele",
				baseCap/units_1.unitcnvt[14], 
				capital/units_1.unitcnvt[6], 
				fixedOM/units_1.unitcnvt[7], 
				varOM/units_1.unitcnvt[9], 
				generation/units_1.unitcnvt[13],
				onlineYear, 
				retireYear);
		

	}

	if(var_1.itime == var_1.iyrb + var_1.nper -1)
		fprintf(fpEleEcon, "\n");



} // end of function econEle