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

    if(index1 != 1 || min1 != -11.3) fail_flag = fail_flag | M_INT1;
    if(index2 != 5 || min2 != -12.5) fail_flag = fail_flag | M_INT2;
    if(index3 != 0 || min3 != 0.2) fail_flag =   fail_flag | M_INT3;
    if(fail_flag == 0) puts("Pass\n");
    else
       printf("FAIL  fail_flag = 0x%d\n",fail_flag);
}
