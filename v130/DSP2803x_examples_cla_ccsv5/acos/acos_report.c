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

float acos_expected[BUFFER_SIZE]={
0, 0.1770077, 0.2506557, 0.3073950, 0.3554212, 
0.3979045, 0.4364690, 0.4720786, 0.5053605, 0.5367502, 
0.5665643, 0.5950419, 0.6223685, 0.6486915, 0.6741305, 
0.6987840, 0.7227343, 0.7460509, 0.7687935, 0.7910135, 
0.8127556, 0.8340589, 0.8549583, 0.8754844, 0.8956648, 
0.9155242, 0.9350851, 0.9543675, 0.9733899, 0.9921693, 
1.010721, 1.029059, 1.047198, 1.065148, 1.082921, 
1.100529, 1.117980, 1.135284, 1.152450, 1.169486, 
1.186400, 1.203198, 1.219889, 1.236478, 1.252973, 
1.269378, 1.285700, 1.301944, 1.318116, 1.334221, 
1.350263, 1.366248, 1.382180, 1.398064, 1.413903, 
1.429704, 1.445469, 1.461202, 1.476908, 1.492592, 
1.508256, 1.523904, 1.539541, 1.555171, };

void test_report(void)
{
	unsigned int i;
	unsigned int pass_count=0;
	unsigned int fail_count=0;
	float fError[BUFFER_SIZE];
	for(i=0;i<BUFFER_SIZE;i++){
		fError[i] = fabs(acos_expected[i]-y[i]);
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
