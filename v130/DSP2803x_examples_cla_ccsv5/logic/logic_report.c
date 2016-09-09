//###########################################################################
// Description:
//
// Compare observed output against expected output and print a
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
    long a,b,mask,r;
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    //implement same set of operations as the CLA
    //as a point of comparision

    //1. Compute sign of an integer
    a = -12;
    (-(a<0) == -1)?pass_count++:fail_count++;

    //2.Detect if two integers have opposite signs
    a = -12; b =12;
    ((a^b) < 0)?pass_count++:fail_count++;

    //3.compute absolute value of 'a'
    a = -13; b = 4;
    mask = a >> 31;
    r = (a + mask)^mask;
    (r == 13)? pass_count++ : fail_count++;
    mask = b >> 31;
    r = (b + mask)^mask;
    (r == 4)? pass_count++ : fail_count++;

    //4.Compute min of two integers
    a = 5; b = 2;
    r = b^((a ^ b) & -( a < b ));
    (r == 2)? pass_count++ : fail_count++;
    r = b^((a^b) & -(a>b));
    (r == 5)? pass_count++ : fail_count++;

    //5. determine if a number is a power of 2
    a = 64; b = 37;
    r = ((a & (a -1)) == 0); //do a boolean operation
    (r == 1)? pass_count++ : fail_count++;
    r = ((b & (b -1)) == 0); //do a boolean operation
    (r == 0)? pass_count++ : fail_count++;

	if(cla_fail_count)
	   printf("FAIL , Pass Count = %lu Fail Count = %lu\n",cla_pass_count,cla_fail_count);
    else
       puts("PASS\n");
}
