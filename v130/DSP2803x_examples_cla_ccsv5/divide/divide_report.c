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

//Golden Test Values
float div_expected[BUFFER_SIZE]={
	1, 0.9692308, 0.9393939, 0.9104478, 0.8823529, 
	0.8550724, 0.8285714, 0.8028169, 0.7777778, 0.7534246, 
	0.7297297, 0.7066666, 0.6842105, 0.6623377, 0.6410257, 
	0.6202531, 0.6000000, 0.5802469, 0.5609756, 0.5421687, 
	0.5238096, 0.5058824, 0.4883721, 0.4712644, 0.4545455, 
	0.4382023, 0.4222222, 0.4065934, 0.3913043, 0.3763441, 
	0.3617021, 0.3473684, 0.3333333, 0.3195876, 0.3061225, 
	0.2929293, 0.2800000, 0.2673267, 0.2549020, 0.2427184, 
	0.2307692, 0.2190476, 0.2075472, 0.1962617, 0.1851852, 
	0.1743119, 0.1636364, 0.1531532, 0.1428571, 0.1327434, 
	0.1228070, 0.1130435, 0.1034483, 0.09401710, 0.08474576, 
	0.07563026, 0.06666667, 0.05785124, 0.04918033, 0.04065040, 
	0.03225806, 0.02400000, 0.01587302, 0.007874016
};


void test_report(void)
{
	unsigned int i;
	unsigned int pass_count=0;
	unsigned int fail_count=0;
	float fError[BUFFER_SIZE];
	for(i=0;i<BUFFER_SIZE;i++){
		fError[i] = fabs(div_expected[i]-y[i]);
		if( fError[i] < 0.01){
			pass_count++;
		}else{
			fail_count++;
		}
	}
    if(fail_count) 
       printf("FAIL , Fail Count = %d, Pass Count = %d\n",fail_count,pass_count);
    else
       puts("PASS\n");
}
