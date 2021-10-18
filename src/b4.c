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

/* b4.f -- translated by f2c (version 19990210).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/
#include <stdio.h>
#include "cmc_f2c.h"
#include "f2c.h"
#include "structures.h"



/* *****************************************************************   ERR */


/*<       SUBROUTINE ERR(ICODE) >*/
/* Subroutine */ int err_(integer *icode)
{
extern FILE *fp12, *fp21;
/*<       COMMON/EL1/LWRIT(75),ITELF(75),ITELL(75),IECHO,IEECH,IFINL >*/
/*<    >*/

/*<       IF(ICODE.GT.3)RETURN >*/
    if (*icode > 3) {
	return 0;
    }
/*<       GO TO(1,2,3),ICODE >*/
    switch (*icode) {
	case 1:  goto L1;
	case 2:  goto L2;
	case 3:  goto L3;
    }

/*<  1    CONTINUE >*/
L1:
/* CMC     1 WRITE(12,11) */
/* CMC    11 FORMAT(1X,'******** ERROR 1 FROM INPUT. PROCESS NUMBER ALREADY', */
/* CMC      1 ' DEFINED') */
fprintf(fp12, " ******** ERROR 1 FROM INPUT. PROCESS NUMBER ALREADY DEFINED\n");
fprintf(fp21, "Error: Error 1 from input. Process number already defined.\n");
/*<       GO TO 99 >*/
    goto L99;

/*<  2     CONTINUE >*/
L2:
/* CMC     2 WRITE(12,12) */
/* CMC    12 FORMAT(1X,'******** ERROR 2 FROM INPUT. LINK NUMBER ALREADY' */
/* CMC      1 ,' DEFINED') */
fprintf(fp12, " ******** ERROR 2 FROM INPUT. LINK NUMBER ALREADY DEFINED\n");
fprintf(fp21, "Error: Error 2 from input. Link number already defined.\n");
/*<       GO TO 99 >*/
    goto L99;

/*<  3    CONTINUE >*/
L3:
/* CMC     3 WRITE(12,13) */
/* CMC    13 FORMAT(1X,'******** ERROR 3 FROM INPUT.  CAPACITATED LINK IS',/, */
/* CMC      1 ' NOT AN INPUT LINK TO SPECIFIED DECISION NODE') */
fprintf(fp12, " ******** ERROR 3 FROM INPUT.  CAPACITATED LINK IS NOT AN INPUT LINK TO SPECIFIED DECISION NODE\n");
fprintf(fp21, "Error: Error 3 from input. Capacitated link is not an input link to specified decision node.\n");

/*<       GO TO 99 >*/
    goto L99;

/*<    99 IERS=IERS+1 >*/
L99:
    ++var_1.iers;
/*<       RETURN >*/
    return 0;
/*<       END >*/
} /* err_ */

