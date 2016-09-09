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

float atan_expected[BUFFER_SIZE]={
 1.5395565,  1.5385494,  1.5374753,  1.5363272, 
 1.5350972,  1.5337762,  1.5323538,  1.5308176, 
 1.5291537,  1.5273454,  1.5253731,  1.5232133, 
 1.5208379,  1.5182133,  1.5152978,  1.5120405, 
 1.5083776,  1.5042281,  1.4994888,  1.4940244, 
 1.4876550,  1.4801364,  1.4711276,  1.4601392, 
 1.4464413,  1.4288993,  1.4056476,  1.3734008, 
 1.3258177,  1.2490457,  1.1071488,  0.7853982, 
 0.0000000, -0.7853982, -1.1071488, -1.2490457, 
-1.3258177, -1.3734008, -1.4056476, -1.4288993, 
-1.4464413, -1.4601392, -1.4711276, -1.4801364, 
-1.4876550, -1.4940244, -1.4994888, -1.5042281, 
-1.5083776, -1.5120405, -1.5152978, -1.5182133, 
-1.5208379, -1.5232133, -1.5253731, -1.5273454, 
-1.5291537, -1.5308176, -1.5323538, -1.5337762, 
-1.5350972, -1.5363272, -1.5374753, -1.5385494
};

void test_report(void)
{
	unsigned int i;
	unsigned int pass_count=0;
	unsigned int fail_count=0;
	float fError[BUFFER_SIZE];
	for(i=0;i<BUFFER_SIZE;i++){
		fError[i] = fabs(atan_expected[i]-y[i]);
		if( fError[i] < 0.01){
			pass_count++;
		}else{
			fail_count++;
		}
	}
	if(fail_count)
	   printf("FAIL , Pass Count = %d Fail Count = %d\n",pass_count,fail_count); 
    else
       puts("PASS\n");     
}
