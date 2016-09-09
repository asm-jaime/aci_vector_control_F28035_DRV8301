//###########################################################################
// Description:
//
// Call Task 1
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
    unsigned int  i;
    for(i=0;i<BUFFER_SIZE;i++){
        x[0][0] = (float)i+1;
        x[0][1] = (float)i+2;
        x[0][2] = (float)i+3;
        x[1][0] = (float)i-1;
        x[1][1] = (float)i-2;
        x[1][2] = (float)i-3;
        x[2][0] = (float)i-7;
        x[2][1] = (float)i+3;
        x[2][2] = (float)i-9;
	 Cla1ForceTask1andWait();
     z[i] = fDet;
}
#if 0
    Cla1ForceTask2andWait();

    Cla1ForceTask3andWait();

    Cla1ForceTask4andWait();

    Cla1ForceTask5andWait();

    Cla1ForceTask6andWait();

    Cla1ForceTask7andWait();

    Cla1ForceTask8andWait();
#endif
}
