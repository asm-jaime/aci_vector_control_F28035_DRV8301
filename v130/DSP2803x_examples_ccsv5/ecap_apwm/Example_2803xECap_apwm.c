//###########################################################################
// Description:
//! \addtogroup f2803x_example_list
//! <h1>eCAP APWM (ecap_epwm)</h1>
//!
//! This program sets up the eCAP pins in the APWM mode.
//! eCAP1 will come out on the GPIO19 pin.
//! This pin is configured to vary between 3 Hz and 6 Hz using
//! the shadow registers to load the next period/compare values
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Global variables
Uint16 direction = 0;

void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2803x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the DSP2803x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// Initialize the GPIO pins for eCAP.
// This function is found in the DSP2803x_ECap.c file
   InitECapGpio();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2803x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2803x_DefaultIsr.c.
// This function is found in DSP2803x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
// No interrupts used for this example.

// Step 4. Initialize all the Device Peripherals:
// Not required for this example

// Step 5. User specific code

   // Setup APWM mode on CAP1, set period and compare registers
   ECap1Regs.ECCTL2.bit.CAP_APWM = 1;	// Enable APWM mode
   ECap1Regs.CAP1 = 0x01312D00;			// Set Period value
   ECap1Regs.CAP2 = 0x00989680;			// Set Compare value
   ECap1Regs.ECCLR.all = 0x0FF;			// Clear pending interrupts
   ECap1Regs.ECEINT.bit.CTR_EQ_CMP = 1; // enable Compare Equal Int

   // Start counters
   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;
   for(;;)
   {
      // vary freq between 3 Hz and 6 Hz
      if(ECap1Regs.CAP1 >= 0x01312D00)
      {
         direction = 0;
      }
      else if (ECap1Regs.CAP1 <= 0x00989680)
      {
         direction = 1;
      }
      // update the period using CAP3 (APRD) shadow register
      if(direction == 0)
      {
         ECap1Regs.CAP3 = ECap1Regs.CAP1 - 500000;
      }
      else
      {
         ECap1Regs.CAP3 = ECap1Regs.CAP1 + 500000;
      }
   }
}

//===========================================================================
// No more.
//===========================================================================

