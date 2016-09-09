//###########################################################################
//
// FILE:	DSP2803x_Gpio.c
//
// TITLE:	DSP2803x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V126 $
// $Release Date: November 30, 2011 $
//###########################################################################

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

//---------------------------------------------------------------------------
// InitGpio:
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example.
void InitGpio(void)
{
// Define the type of control board
	#define F28035_DEVICE	0				// Without simulator
//	#define F28035_DEVICE	1				// With simulator

	EALLOW;

	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;		// PWM_AH
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;		// PWM_AL
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;		// PWM_BH
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;		// PWM_BL
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;		// PWM_CH
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;		// PWM_CL
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;		// Input
	GpioCtrlRegs.GPADIR.bit.GPIO6 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
//	GpioDataRegs.GPASET.bit.GPIO6 = 1;

#if F28035_DEVICE == 0
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;		// SCI_RX
	GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 3;
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 2;
#elif F28035_DEVICE == 1
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;		// Input
	GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
//	GpioDataRegs.GPASET.bit.GPIO7 = 1;
#endif

	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;		// Input
	GpioCtrlRegs.GPADIR.bit.GPIO8 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;
//	GpioDataRegs.GPASET.bit.GPIO8 = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;		// Input
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO9 = 1;
//	GpioDataRegs.GPASET.bit.GPIO9 = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;	// DC_CAL
	GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
	GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
//	GpioDataRegs.GPASET.bit.GPIO10 = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
//	GpioDataRegs.GPASET.bit.GPIO11 = 1;

#if F28035_DEVICE == 0
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;		// SCI_TX
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 2;
#elif F28035_DEVICE == 1
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;
//	GpioDataRegs.GPASET.bit.GPIO12 = 1;
#endif

	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;		// OCTW
	GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3;
	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;		// FAULT
	GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3;
	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;

	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO15 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;
//	GpioDataRegs.GPASET.bit.GPIO15 = 1;

	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;
//	GpioDataRegs.GPASET.bit.GPIO16 = 1;

	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;
//	GpioDataRegs.GPASET.bit.GPIO17 = 1;

	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;
//	GpioDataRegs.GPASET.bit.GPIO18 = 1;

	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;
//	GpioDataRegs.GPASET.bit.GPIO19 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;		// CAP1/QEPA
	GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;		// CAP2/QEPB
	GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;

	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO22 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO22 = 1;
//	GpioDataRegs.GPASET.bit.GPIO22 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;		// CAP3/QEPI
	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0;
	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;		// SDI
	GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3;
	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 3;

	GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;		// SDO
	GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3;
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 3;

	GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;		// SCLK
	GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3;
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 3;

	GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;		// SCS
	GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3;
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 3;

#if F28035_DEVICE == 0
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;
//	GpioDataRegs.GPASET.bit.GPIO28 = 1;

	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;
//	GpioDataRegs.GPASET.bit.GPIO29 = 1;
#elif F28035_DEVICE == 1
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;		// SCI_RX
	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;

	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;		// SCI_TX
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
#endif

	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;
//	GpioDataRegs.GPASET.bit.GPIO30 = 1;

	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;	// Input
	GpioCtrlRegs.GPADIR.bit.GPIO31 = 0;
//	GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
//	GpioDataRegs.GPASET.bit.GPIO31 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;	// Input
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;
//	GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
//	GpioDataRegs.GPBSET.bit.GPIO32 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;	// 0:BLDC <> 1:PMSM
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;
//	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;
	GpioDataRegs.GPBSET.bit.GPIO33 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;	// STATUS
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
//	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
	GpioDataRegs.GPBSET.bit.GPIO34 = 1;

	// GPIO35 : TDI
	// GPIO36 : TMS
	// GPIO37 : TDO
	// GPIO38 : TCK

	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;	// Input
	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 0;
//	GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1;
//	GpioDataRegs.GPBSET.bit.GPIO39 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;	// EN_GATE
	GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1;
	GpioDataRegs.GPBCLEAR.bit.GPIO40 = 1;
//	GpioDataRegs.GPBSET.bit.GPIO40 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;	// Input
	GpioCtrlRegs.GPBDIR.bit.GPIO41 = 0;
//	GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
//	GpioDataRegs.GPBSET.bit.GPIO41 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 0;	// Input
	GpioCtrlRegs.GPBDIR.bit.GPIO42 = 0;
//	GpioDataRegs.GPBCLEAR.bit.GPIO42 = 1;
//	GpioDataRegs.GPBSET.bit.GPIO42 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 0;	// Input
	GpioCtrlRegs.GPBDIR.bit.GPIO43 = 0;
//	GpioDataRegs.GPBCLEAR.bit.GPIO43 = 1;
//	GpioDataRegs.GPBSET.bit.GPIO43 = 1;

	GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;	// Input
	GpioCtrlRegs.GPBDIR.bit.GPIO44 = 0;
//	GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
//	GpioDataRegs.GPBSET.bit.GPIO44 = 1;

	EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
