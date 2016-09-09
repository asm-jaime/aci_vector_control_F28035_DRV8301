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
    Uint16 const gold1 = 0x0043;   
    Uint16 const gold2 = 0x009f;
    Uint16 const gold3 = 0x00CE;
    Uint16 const gold4 = 0x00c0;
                
    if(gold1 != crc8_msg1) fail_flag = 1;
    if(gold2 != crc8_msg2) fail_flag = 2;          
    if(gold3 != crc8_msg3) fail_flag = 3; 
    if(gold4 != crc8_msg4) fail_flag = 4;           
     
    if(fail_flag == 0) puts("PASS\n");
    else
       printf("FAIL  fail_flag = 0x%d\n",fail_flag);
}
