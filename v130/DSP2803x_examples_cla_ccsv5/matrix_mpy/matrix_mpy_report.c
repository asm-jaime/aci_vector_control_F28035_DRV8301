//###########################################################################
// Description:
//
// Compare observed output against expected output vector and print a 
// PASS/FAIL report to the console
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include <stdio.h>
#include <math.h>
#include "DSP28x_Project.h"
#include "DSP2803x_Cla_defines.h"  
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

float z_expected[][N]={{20,31,40},{7,11,17},{14,22,44}};

void test_report(void)
{
	unsigned int i,j;
	unsigned int pass_count=0;
	unsigned int fail_count=0;
	float fError[M][N];
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
		  fError[i][j] = fabs(z_expected[i][j]-z[i][j]);
		  if( fError[i][j] == 0){
			 pass_count++;
		  }else{
			 fail_count++;
		  }
		}
	  }
	if(fail_count)
	   printf("FAIL , Pass Count = %d Fail Count = %d\n",pass_count,fail_count); 
    else
       puts("PASS\n");     
}
