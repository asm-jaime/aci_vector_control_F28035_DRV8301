//###########################################################################
// Description:
//! \addtogroup f2803x_example_list
//! <h1>External Interrupt (external_interrupt)</h1>
//!
//! This program sets up GPIO0 as XINT1 and GPIO1 as XINT2.  Two other
//! GPIO signals are used to trigger the interrupt (GPIO30 triggers
//! XINT1 and GPIO31 triggers XINT2). XINT1 input is synched to SYSCLKOUT
//! XINT2 has a long qualification - 6 samples at 510*SYSCLKOUT each.
//! GPIO34 will go high outside of the interrupts and low within the
//! interrupts. This signal can be monitored on a scope.
//! Each interrupt is fired in sequence - XINT1 first and then XINT2.
//!
//! Monitor GPIO34 with an oscilloscope. GPIO34 will be high outside of
//! the ISRs and low within each ISR.
//!
//! \b External \b Connections \n
//!  - Connect GPIO30 to GPIO0. GPIO0 is assigned to XINT1
//!  - Connect GPIO31 to GPIO1. GPIO1 is assigned to XINT2
//!
//! \b Watch \b Variables \n
//!  - Xint1Count - XINT1 interrupt count
//!  - Xint2Count - XINT2 interrupt count
//!  - LoopCount  - idle loop count
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Prototype statements for functions found within this file.
__interrupt void xint1_isr(void);
__interrupt void xint2_isr(void);

// Global variables for this example
volatile Uint32 Xint1Count;
volatile Uint32 Xint2Count;
Uint32 LoopCount;

#define DELAY (CPU_RATE/1000*6*510)  //Qual period at 6 samples

void main(void)
{
   Uint32 TempX1Count;
   Uint32 TempX2Count;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2803x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the DSP2803x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
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
   EALLOW;	// This is needed to write to EALLOW protected registers
   PieVectTable.XINT1 = &xint1_isr;
   PieVectTable.XINT2 = &xint2_isr;
   EDIS;   // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// Not required for this example

// Step 5. User specific code, enable interrupts:

// Clear the counters
   Xint1Count = 0; // Count XINT1 interrupts
   Xint2Count = 0; // Count XINT2 interrupts
   LoopCount = 0;  // Count times through idle loop

// Enable XINT1 and XINT2 in the PIE: Group 1 interrupt 4 & 5
// Enable INT1 which is connected to WAKEINT:
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
   PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Group 1 INT4
   PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Group 1 INT5
   IER |= M_INT1;                              // Enable CPU INT1
   EINT;                                       // Enable Global Interrupts

// GPIO30 & GPIO31 are outputs, start GPIO30 high and GPIO31 low
   EALLOW;
   GpioDataRegs.GPASET.bit.GPIO30 = 1;         // Load the output latch
   GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;        // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO30 = 1;         // output

   GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;       // Load the output latch
   GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;        // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;         // output
   EDIS;

// GPIO0 and GPIO1 are inputs
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;          // input
   GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;        // XINT1 Synch to SYSCLKOUT only

   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;          // input
   GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 2;        // XINT2 Qual using 6 samples
   GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0xFF;   // Each sampling window is 510*SYSCLKOUT
   EDIS;

// GPIO0 is XINT1, GPIO1 is XINT2
   EALLOW;
   GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0;   // XINT1 is GPIO0
   GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 1;   // XINT2 is GPIO1
   EDIS;

// Configure XINT1
   XIntruptRegs.XINT1CR.bit.POLARITY = 0;      // Falling edge interrupt
   XIntruptRegs.XINT2CR.bit.POLARITY = 1;      // Rising edge interrupt

// Enable XINT1 and XINT2
   XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable XINT1
   XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2


// GPIO34 will go low inside each interrupt.  Monitor this on a scope
   EALLOW;
   GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;        // GPIO
   GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;         // output
   EDIS;

// Step 6. IDLE loop:
   for(;;)
   {
      TempX1Count = Xint1Count;
      TempX2Count = Xint2Count;

      // Trigger both XINT1
      GpioDataRegs.GPBSET.bit.GPIO34 = 1;   // GPIO34 is high
      GpioDataRegs.GPACLEAR.bit.GPIO30 = 1; // Lower GPIO30, trigger XINT1
      while(Xint1Count == TempX1Count) {}

      // Trigger both XINT2

      GpioDataRegs.GPBSET.bit.GPIO34 = 1;   // GPIO34 is high
      DELAY_US(DELAY);                      // Wait for Qual period
      GpioDataRegs.GPASET.bit.GPIO31 = 1;   // Raise GPIO31, trigger XINT2
      while(Xint2Count == TempX2Count) {}

      // Check that the counts were incremented properly and get ready
      // to start over.
      if(Xint1Count == TempX1Count+1 && Xint2Count == TempX2Count+1)
      {
          LoopCount++;
          GpioDataRegs.GPASET.bit.GPIO30 = 1;   // raise GPIO30
          GpioDataRegs.GPACLEAR.bit.GPIO31 = 1; // lower GPIO31
      }
      else
      {
          __asm("      ESTOP0"); // stop here
      }
   }
}

// Step 7. Insert all local Interrupt Service Routines (ISRs) and functions here:
// If local ISRs are used, reassign vector addresses in vector table as
// shown in Step 5
__interrupt void xint1_isr(void)
{
	GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
	Xint1Count++;

	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void xint2_isr(void)
{
	GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
	Xint2Count++;

	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//===========================================================================
// No more.
//===========================================================================

