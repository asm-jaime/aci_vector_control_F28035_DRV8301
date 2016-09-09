//###########################################################################
//
// FILE:   DSP2803x_HRCap.c
//
// TITLE:  DSP2803x HRCAP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

//---------------------------------------------------------------------------
// InitHRCap:
//---------------------------------------------------------------------------
// This function initializes the HRCAP(s) to a known state.
//
void InitHRCap(void)
{
   // Initialize HRCAP1, 2...

   //tbd...

}

//---------------------------------------------------------------------------
// Example: InitHRCapGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as ECAP pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each HRCAP peripheral
// Only one GPIO pin should be enabled for ECAP operation.
// Comment out other unwanted lines.

void InitHRCapGpio()
{
#if DSP28_HRCAP1
    InitHRCap1Gpio();
#endif
#if DSP28_HRCAP2
    InitHRCap2Gpio();
#endif
}

void InitHRCap1Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;      // Enable pull-up on GPIO9  (HRCAP1)
 GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;     // Enable pull-up on GPIO26 (HRCAP1)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAQSEL1.bit.GPIO9  =3;   // Asynch to SYSCLKOUT GPIO9  (HRCAP1)
 GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3;   // Asynch to SYSCLKOUT GPIO26 (HRCAP1)



/* Configure HRCAP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be HRCAP1 functional pins.
// Comment out other unwanted lines.

//   GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 3;    // Configure GPIO9 as HRCAP1
 GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // Configure GPIO26 as GRCAP1

    EDIS;
}

void InitHRCap2Gpio(void)
{
   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;     // Enable pull-up on GPIO11 (HRCAP2)
// GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;     // Enable pull-up on GPIO27 (HRCAP2)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;   // Asynch to SYSCLKOUT GPIO11 (HRCAP2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3;   // Asynch to SYSCLKOUT GPIO27 (HRCAP2)



/* Configure HRCAP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be HRCAP1 functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;    // Configure GPIO11 as HRCAP2
// GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;    // Configure GPIO27 as HRCAP2

    EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
