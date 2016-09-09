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
	Uint16 i;
	Uint16 fail_flag = 0x0000;

    // 
    // Map the data memory back to the CPU so we can check
    //    
    EALLOW;
    Cla1Regs.MMEMCFG.bit.RAM0E	= 0;
    Cla1Regs.MMEMCFG.bit.RAM1E	= 0;
    EDIS;
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");       
       
    for(i = 0; i < 256; i++)
    {
       if (table[i] !=  crc8_table[i] )
       {
          fail_flag = 1;
       }
    } 
     
    if(fail_flag == 0) puts("PASS\n");
    else
       printf("FAIL  fail_flag = 0x%d\n",fail_flag);
}
