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

char * substring(char *s, int start, int length)
{
  /* returns the substring of s[start]..s[start+length] */
  /* ie substring("abcdefg", 2, 3) returns "cde" */

  int pos, retpos, len;
  char *retstr;
  len = strlen(s);
  retstr = (char *)calloc(length+1, sizeof(char));
  
  for(pos = start; pos< (start+length); pos++){
    retpos = pos - start;
    if(pos<=len)
      retstr[retpos] = s[pos];
    else
      retstr[retpos] = ' ';
      
  }
  retstr[length] = '\0';
  return(retstr);
}
#ifdef DEBUGSUBSTR
main()
{
  int l, ct, i, pos;
  int ary[10];
  char buf[255];
  char *ptbuf;
    FILE *fpin;
  
  fpin = fopen("tst1.dat", "r");
  
  for(l=1; l<=2; l++){
    fgets(buf, sizeof(buf),fpin);
    pos = 0;
    for(ct=1; ct<=5; ct++){
      ary[ (ct-1) + (5*(l-1))] = atoi( substring(buf,pos,4));
      pos +=4;
      
    }
  }
  for(i=0;i<10;i++)
    fprintf(fp21, "%d: %d\n", i, ary[i] );
}
#endif /* DEBUGSUBSTR */
