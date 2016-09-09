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

void test_report(void)
{
	Uint16 fail_flag = 0x0000;
	Uint16 i;
	float vector1_gold[] = {1/1.0, 1/4.0, 1/8.0, 1/.5, 1/.25};
	float vector2_gold[] = {-1/.25,-1/.5,-1/.125,-1/2.0,-1/4.0,-1/8.0,1/8.0,1/4.0,1/.25,1/.125}; 
	
    for(i=0; i < LENGTH1; i++)
    {
        if(vector1_inverse[i] != vector1_gold[i]) fail_flag = fail_flag | M_INT1;
    }
    // 
    // Map the data memory back to the CPU so we can check the
    // results of task 2
    //
    EALLOW;
    Cla1Regs.MMEMCFG.bit.RAM0E	= 0;
    Cla1Regs.MMEMCFG.bit.RAM1E	= 0;
    EDIS;
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");   
       
    for(i=0; i < LENGTH2; i++)
    {
        if(vector2[i] != vector2_gold[i]) fail_flag = fail_flag | M_INT2;
    }    
    if(fail_flag == 0) puts("PASS\n");
    else
       printf("FAIL  fail_flag = 0x%d\n",fail_flag);

}
