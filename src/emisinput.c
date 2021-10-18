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

/* This function reads the necessary data for 
	Emission calculations */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "f2c.h"
#include "structures.h"


int emisinput_(void) 
{
char buf [1024];
char *token;
char seps[] ="'";
int nodeNumber, year, pollID;
char nodeAbbv[3];
extern FILE *fp24;

	fseek(fp24,0L,SEEK_SET);


  	while(!feof(fp24)){
		fgets(buf,sizeof(buf),fp24);
		token =  strtok(buf, seps);
		nodeNumber =atoi(token);
		if (nodeNumber==0)
			return 0;
		token=strtok(NULL, seps);
		strcpy(nodeAbbv,token);
		token=strtok(NULL, seps);
		year=atoi(token);

		if (year > var_1.itime)
			return 0;
		else {
			if (year< var_1.itime)
				;
			else {
				if(strcmp(nodeAbbv,"RS")==0){
					token=strtok(NULL, seps);
					pollID=atoi(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						res_1.Efactors[nodeNumber-1][pollID-1][0]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						res_1.Efactors[nodeNumber-1][pollID-1][1]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						res_1.Efactors[nodeNumber-1][pollID-1][2]=atof(token);
				}

				if(strcmp(nodeAbbv,"RN")==0){
					token=strtok(NULL, seps);
					pollID=atoi(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						ren_1.Efactors[nodeNumber-1][pollID-1][0]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						ren_1.Efactors[nodeNumber-1][pollID-1][1]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						ren_1.Efactors[nodeNumber-1][pollID-1][2]=atof(token);
				}

				if(strcmp(nodeAbbv,"PR")==0 || strcmp(nodeAbbv,"TR")==0){
					token=strtok(NULL, seps);
					pollID=atoi(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						pro_1.Efactors[nodeNumber-1][pollID-1][0]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						pro_1.Efactors[nodeNumber-1][pollID-1][1]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						pro_1.Efactors[nodeNumber-1][pollID-1][2]=atof(token);
				}

				if(strcmp(nodeAbbv,"MI")==0){
					token=strtok(NULL, seps);
					pollID=atoi(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						min_1.Efactors[nodeNumber-1][pollID-1][0]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						min_1.Efactors[nodeNumber-1][pollID-1][1]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						min_1.Efactors[nodeNumber-1][pollID-1][2]=atof(token);
				}

				if(strcmp(nodeAbbv,"DE")==0){
					token=strtok(NULL, seps);
					pollID=atoi(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						dem_1.Efactors[nodeNumber-1][pollID-1][0]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						dem_1.Efactors[nodeNumber-1][pollID-1][1]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						dem_1.Efactors[nodeNumber-1][pollID-1][2]=atof(token);
				}
				
				if(strcmp(nodeAbbv,"RE")==0){
					token=strtok(NULL, seps);
					pollID=atoi(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						ref_1.Efactors[nodeNumber-1][pollID-1][0]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						ref_1.Efactors[nodeNumber-1][pollID-1][1]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						ref_1.Efactors[nodeNumber-1][pollID-1][2]=atof(token);
				}

				if(strcmp(nodeAbbv,"TU")==0){
					token=strtok(NULL, seps);
					pollID=atoi(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						elec_1.Efactors[nodeNumber-1][pollID-1][0]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						elec_1.Efactors[nodeNumber-1][pollID-1][1]=atof(token);
					token=strtok(NULL, seps);
					if(strcmp(token,"%") != 0)
						elec_1.Efactors[nodeNumber-1][pollID-1][2]=atof(token);
				}

			}

		}


	} /* end of while loop */



} /* emisinput_ */

