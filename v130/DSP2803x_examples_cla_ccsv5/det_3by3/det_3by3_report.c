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

float z_expected[BUFFER_SIZE] = {
	0, 44, 88, 132, 176, 
	220, 264, 308, 352, 
	396, 440, 484, 528, 
	572, 616, 660, 704, 
	748, 792, 836, 880, 
	924, 968, 1012, 1056, 
	1100, 1144, 1188, 1232, 
	1276, 1320, 1364
};

void test_report(void)
{
	unsigned int i;
	unsigned int pass_count=0;
	unsigned int fail_count=0;
    
    for(i = 0;i<BUFFER_SIZE;i++){
     (fabs(z_expected[i]-z[i]) < 1e-4)?pass_count++ : fail_count++;
    }

	if(fail_count)
	   printf("FAIL , Pass Count = %d Fail Count = %d\n",pass_count,fail_count); 
    else
       puts("PASS\n");     
}
