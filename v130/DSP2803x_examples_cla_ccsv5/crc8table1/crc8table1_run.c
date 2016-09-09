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

void ram_enable(void);
void ram_disable(void);

void test_run(void)
{
    Uint16 i;
    
    //
    // Assign the RAM to the CPU
    // Clear out the table
    // Assign the RAM back to the CLA
    //
    ram_disable();
    for (i = 0; i < 256; i++) table[i] = 0x12345678;
    ram_enable();
       
    
    Cla1ForceTask1andWait();

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

void ram_disable()
{
    EALLOW;
    Cla1Regs.MMEMCFG.bit.RAM0E  = 0;
    Cla1Regs.MMEMCFG.bit.RAM1E  = 0;
    EDIS;
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");
    return; 
}

void ram_enable()
{
    EALLOW;
    Cla1Regs.MMEMCFG.bit.RAM0E  = 1;
    Cla1Regs.MMEMCFG.bit.RAM1E  = 1;
    EDIS;
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");
   __asm("   NOP");  
}
