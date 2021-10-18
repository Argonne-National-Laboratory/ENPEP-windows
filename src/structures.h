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

struct {
	char unitcode[16][50];
	char unitname[16][50];
	float unitcnvt[16];
} units_;

#define units_1 units_

struct {
  integer laby[75];
} outwr_;

#define outwr_1 outwr_

struct {
  integer lwrit[75], itelf[75], itell[75], iecho, ieech, ifinl;
} el1_;

#define el1_1 el1_

struct {
  integer itn, itmax, ntime, nper;
  real rctol, epsn;
  integer iwr1, nnrep, nnrnp, nnpr, iers, ires, lnkmx, nrsmx;
  real whi, wlo, actol;
  integer nrnmx;
  real shr[4000]	/* was [200][10] */;
  integer nprmx, idmp[75], iyrb, itime, nnall, nnre, nnde, nnlnk, nnst,nnmi;
  real qscale;
  char qu[15], pu[15];
} var_;

#define var_1 var_

struct {
  integer ninal[400], iinal[4000]	/* was [200][10] */, noual[400], 
  ioual[4000]	/* was [200][10] */;
  real gm[400], bl[400], split[4000]	/* was [200][10] */;
  integer nalpr[400], ialpr[4000];	/* was [200][10] */

  char cmc_laba[400][20];
  real rms[4000]	/* was [200][10] */, oms[4000]	/* was [200][10] */, 
  oquan, poquan[400];
} all_;

#define all_1 all_


struct {
  integer ngg[400];
} al1_;

#define al1_1 al1_


struct {
  integer iwre, nunit, nuse[300], kuse[300];
  real qunit[22500]	/* was [75][300] */;
  integer noperat[22500]	/* was [75][300] */;
  real Efactors[300][50][3];		/* 300 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
} elec_;

#define elec_1 elec_

struct {
  real q[999], p[999], capl[999];
  integer lab[5], iuse[300], luse[999];
  real noTaxPrice[999];
} net_;

#define net_1 net_

struct {
  integer iours[75];
  real qt[92], hqt[92], hqtm[92], qtm[92], a[75], b[75];
  /* integer labr[375];	/* was [75][5] */
  char cmc_labr[75][30];
  real pprj[5625]	/* was [75][75] */;
  integer kpr[75];
  real plast[75], ab[75];
  real Efactors[75][50][3];		/* 75 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  real		noTaxPrice[75][75];
  real		fuelCost[75][75];
  real		economicRent[75][75];
  real		cumulativeQ[75][75];
} res_;

#define res_1 res_

struct {
  integer ndemx, iinde[200];
  char cmc_labd[200][20];
  real drat[15000]	/* was [200][75] */;
  integer kd[200];
  real qbase[200];
  real Efactors[200][50][3];		/* 200 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
} dem_;

#define dem_1 dem_

struct {
	/* increase arry size from 100 to 300 */
  real alpha[300], delta[300], pmax[300], pmin[300];
  integer iinpp[300];
  real pscale;
  integer ioupp[300];
  char cmc_labp[300][20];
  real sen[1500],	/* was [20][75]; sen is related stock pile rather than pricing node */
	   zen[149850]	/* was [2][999][75]; zen is used to store p and q values for all links */
    ;
  integer ioutx;
  integer linkp[300];
} pri_;

#define pri_1 pri_


struct {
  integer iinpr[300], ioupr[300];
  real om[300], cc[300], eff[300], tci[300], capm[300], cf[300];
  integer life[300];
  real rir[300];
  char cmc_labc[300][20];
  real Efactors[300][50][3];		/* 300 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  integer	baseYearLife[300] ;
  real		baseYearCap[300];
  real		baseYearCapital[300];
  integer	opUnits[300][75];
  real		opCap[300][75];
  integer	baseUnits[300][75];
  real		baseCap[300][75];
  real		baseSunk[300][75];
  integer	existingUnits[300][75];
  real		existingCap[300][75];
  real		existingSunk[300][75];
  real		demandNotServed[300][75];
  integer	newUnits[300][75];
  real		newCap[300][75];
  real		newCapital[300][75];
  real		operatingCost[300][75];
  real		totalCapital[300][75];
  real		avgInvestment[300][75];
  real		avgCap[300][75];
  real		avgCF[300][75];
  real		outputCapability[300][75];
} pro_;

#define pro_1 pro_

struct {
	/* MI Nodes have been increased from 15 to 200 */
  integer ninmi[200], iinmi[1000]	/* was [15][5] */, ioumi[200];
  real omm[200], ccm[200], rio[1000]	/* was [15][5] */, tcim[200], capmm[200], cfm[200];
  integer lifem[200];
  real rirm[200];
  char cmc_labm[201][30];	/* was [15][20] changed to [16][30] - Prakash */

  real prem[4000]	/* was [200][10] */;
  integer nremx, nmimx;
  real Efactors[200][50][3];		/* 200 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  integer	baseYearLife[200] ;
  real		baseYearCap[200];
  real		baseYearCapital[200];
  integer	opUnits[200][75];
  real		opCap[200][75];
  integer	baseUnits[200][75];
  real		baseCap[200][75];
  real		baseSunk[200][75];
  integer	existingUnits[200][75];
  real		existingCap[200][75];
  real		existingSunk[200][75];
  real		demandNotServed[200][75];
  integer	newUnits[200][75];
  real		newCap[200][75];
  real		newCapital[200][75];
  real		operatingCost[200][75];
  real		totalCapital[200][75];
  real		avgInvestment[200][75];
  real		avgCap[200][75];
  real		avgCF[200][75];
  real		outputCapability[200][75];
} min_;

#define min_1 min_

struct {
  integer ninre[30], iinre[60]	/* was [30][2] */, noure[30], ioure[
								    180]	/* was [30][6] */, istck[180]	/* was [30][6] */;
  real pff[30];
  integer ixces[180]	/* was [30][6] */;
  real slate[180]	/* was [30][6] */, omr[30], ccr[30], prat[180]	/* 
			   was [30][6] */;
  integer iordc[30];
  real tcir[30], capmr[30], cfr[30];
  integer lifer[30];
  real rirr[30];
  char cmc_labe[30][20];

  real remul[180]	/* was [30][6] */;
  integer icntl[180]	/* was [30][6] */, linpr[180]	/* was [30][6] */;
  real Efactors[30][50][3];		/* 30 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  integer	baseYearLife[30] ;
  real		baseYearCap[30];
  real		baseYearCapital[30];
  integer	opUnits[30][75];
  real		opCap[30][75];
  integer	baseUnits[30][75];
  real		baseCap[30][75];
  real		baseSunk[30][75];
  integer	existingUnits[30][75];
  real		existingCap[30][75];
  real		existingSunk[30][75];
  real		demandNotServed[30][75];
  integer	newUnits[30][75];
  real		newCap[30][75];
  real		newCapital[30][75];
  real		operatingCost[30][75];
  real		totalCapital[30][75];
  real		avgInvestment[30][75];
  real		avgCap[30][75];
  real		avgCF[30][75];
  real		outputCapability[30][75];
} ref_;

#define ref_1 ref_

struct {
  integer iourn[17];
  real prn[85]	/* was [17][5] */, qrn[85]	/* was [17][5] */;
  integer  nstep[17];
  char cmc_labn[17][20];

  real rlim[17];
  integer mup[17], jwrit[75], itfir[75], itlas[75];
  char ititl[6][256];								/* was integer changed to char -Prakash */
  real Efactors[17][50][3];		/* 17 nodes, 50 pollutants, and 3 factors namely 
									emission factor, scale value, emission tax */
  real		economicRent[17][75];
  real		fuelCost[17][75];
  real		noTaxPrice[17][75];
} ren_;

#define ren_1 ren_

struct {
  integer ioust[20];
  real stok[20], st[20];
  char cmc_labs[20][20];
  integer ialst[400], istc[20], istkexl[20];
  real stkexr[20];
} stk_;

#define stk_1 stk_

struct {
  integer ireson, ilod, iele, imp;
  real boemwh, boembtu;
} mode_;

#define mode_1 mode_


struct {
  integer mab[5];
  real xldci[104]	/* was [52][2] */, cap[300], varct[300], temp[300];
  integer isun[300], iunit[300], iinlk[300], ioulk[300];
  real htrt[300];
  integer labe[1500]	/* was [300][5] */;
  integer labf[1500]	/* was [300][5] */;
  /* CMC ERROR? added labf */
  real oma[300], omb[300], forc[300], dmain[300], capc[300];
  integer iyrf[300], iyrr[300], iinel[40], ioupl[80];
  real umin[300];
  /* CMC added iblanklov and optionallov below */
  integer iblanklov[300];
  real optionallov[300];
  char unitname[300][9];	/* added by Prakash */
  real basecap[300];		/* added by Prakash - cap is being overwritten by derated cap */
  int unitype[300];			/* added by Prakash - to keep track of unit type in calculating emissions */
  real baseCapital[300];
  real generation[300];
} elec1_;

#define elec1_1 elec1_


struct {
  integer ispeclov[300];
  real optionallov[300], xmlod, xlfac;
} elec4_;

#define elec4_1 elec4_

struct {
  integer ic1[135], ic2[135], ic3[135];
  real rc4[135], rc5[135], rc6[135], rc7[135], rc8[135], rc9[135], rc10[135];
  integer ic11[135], ic12[135];
  real rc11[135];	/* changed all array sizes from 50 to 135 - Prakash */
  integer labv[135]	/* was [50][5] */;
  char unitname[300][9];	/* added by Prakash */
} elec2_;

#define elec2_1 elec2_

struct {
  real peakf, rire;
  integer ninel, noupl;
  real qiouel;
  integer munit;
} elec3_;

#define elec3_1 elec3_


struct {
  int unitnumber[300];
  char unitname[300][9];
  int unittype[300];
} elec5_;

#define elec5_1 elec5_

struct {
  real agenr[75], aload[75];
  integer iouel;
} toload_;

#define toload_1 toload_



struct {
  /* char nodel[7992]	 was [2][999] */
  char nodel[3][999][5]; /* c-ified nodel[up=1|down=2][999][4-char] */

  integer numb[1998]	/* was [2][999] */, ispec[1998]	/* was [2][999] */, 
  labw[1000]	/* was [2][100][5] */, kup, kdwn, ielecs;
} invis_;

#define invis_1 invis_


struct {
  real qnt[92], caplimp[999];
} saveimp_;

#define saveimp_1 saveimp_



