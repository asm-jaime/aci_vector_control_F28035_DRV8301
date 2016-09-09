//###########################################################################
// Description:
//
// Simulate an ADC sampling loop by feeding in pre-calculated samples of
// a noisy sine wave to task 1 of the CLA and then triggering the task
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"
#include "DSP2803x_Cla_defines.h"  
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

void test_run(void)
{
	int i;
	
    Cla1ForceTask8andWait();

	for(i=0; i<NUM_SAMPLES; i++){
	  xn = fAdcInput[i];
	  Cla1ForceTask1andWait();
	  fBiquadOutput[i] = yn;
	}
	
#if 0
    Cla1ForceTask2andWait();

    Cla1ForceTask3andWait();

    Cla1ForceTask4andWait();

    Cla1ForceTask5andWait();

    Cla1ForceTask6andWait();

    Cla1ForceTask7andWait();
#endif
}
