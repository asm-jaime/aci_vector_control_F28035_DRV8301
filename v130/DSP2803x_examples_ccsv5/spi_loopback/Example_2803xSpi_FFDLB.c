//###########################################################################
//
//!  \addtogroup f2803x_example_list
//!  <h1>SPI Digital Loop Back(spi_loopback)</h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required. Interrupts are not used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The sent data looks like this: \n
//!  0000 0001 0002 0003 0004 0005 0006 0007 .... FFFE FFFF \n
//!  This pattern is repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - \b sdata , sent data
//!  - \b rdata , received data
//
////###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Prototype statements for functions found within this file.
void spi_xmit(Uint16 a);
void spi_fifo_init(void);
void spi_init(void);
void error(void);

void main(void)
{
   Uint16 sdata;  // send data
   Uint16 rdata;  // received data

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2803x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the DSP2803x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
// Setup only the GP I/O only for SPI-A functionality
// This function is found in DSP2803x_Spi.c
   InitSpiaGpio();

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

// Step 4. Initialize all the Device Peripherals:
   spi_fifo_init();	  // Initialize the Spi FIFO
   spi_init();		  // init SPI

// Step 5. User specific code:
// Interrupts are not used in this example.
   sdata = 0x0000;
   for(;;)
   {
     // Transmit data
     spi_xmit(sdata);
     // Wait until data is received
     while(SpiaRegs.SPIFFRX.bit.RXFFST !=1) { }
     // Check against sent data
     rdata = SpiaRegs.SPIRXBUF;
     if(rdata != sdata) error();
     sdata++;
   }
}

// Step 7. Insert all local Interrupt Service Routines (ISRs) and functions here:

void error(void)
{
    __asm("     ESTOP0");						// Test failed!! Stop!
    for (;;);
}

void spi_init()
{
	SpiaRegs.SPICCR.all =0x000F;	             // Reset on, rising edge, 16-bit char bits
	SpiaRegs.SPICTL.all =0x0006;    		     // Enable master mode, normal phase,
                                                 // enable talk, and SPI int disabled.
	SpiaRegs.SPIBRR =0x007F;
    SpiaRegs.SPICCR.all =0x009F;		         // Relinquish SPI from Reset
    SpiaRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
}

void spi_xmit(Uint16 a)
{
    SpiaRegs.SPITXBUF=a;
}

void spi_fifo_init()
{
// Initialize SPI FIFO registers
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x2044;
    SpiaRegs.SPIFFCT.all=0x0;
}

//===========================================================================
// No more.
//===========================================================================


