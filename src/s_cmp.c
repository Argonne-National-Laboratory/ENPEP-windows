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

#include "f2c.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
extern FILE  *fp21;
/* compare two strings */
void cmc_dbg(void){};

#ifdef KR_headers
integer s_cmp(a0, b0, la, lb) char *a0, *b0; ftnlen la, lb;
#else
integer s_cmp(char *a0, char *b0, ftnlen la, ftnlen lb)
#endif
{
  register unsigned char *a, *aend, *b, *bend;

  int i;
  char *pad_a0;
  integer retval;


  retval = 0;
  pad_a0 = (char *) calloc((la+1), sizeof(char) );
  if (pad_a0 == NULL) {fprintf(fp21, "error allocating pad_a0\n");exit(0);}
	

  /* the for loop has been modified as indicated - Prakash */
  
  for(i=0; i< la; i++){ 
  /*for(i=0; i< strlen(a0); i++){ */
   pad_a0[i] = a0[i];
  }
  
  for(i=strlen(a0); i< la; i++){
    pad_a0[i] = ' ';
  }

  pad_a0[la] = '\0';
  
a = (unsigned char *)pad_a0;
b = (unsigned char *)b0;
aend = a + la;
bend = b + lb;


if(la <= lb)
	{
	while(a < aend)
		if(*a != *b){
			retval = ( *a - *b );
			break;
		      }
		else
			{ ++a; ++b; }

	while(b < bend)
		if(*b != ' '){
			retval = ( ' ' - *b );
			break;
		      }
		else	++b;
	}

else
	{
	while(b < bend)
		if(*a == *b)
			{ ++a; ++b; }
		else{
			retval = ( *a - *b );
		      break;
		      }
	while(a < aend)
		if(*a != ' '){
			retval = (*a - ' ');
		      break;}
		else	++a;
	}


free(pad_a0); 
return(retval);
}

