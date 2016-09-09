//###########################################################################
// Description:
//! \addtogroup f2803x_example_list
//! <h1> ADC Start of Conversion (adc_soc)</h1>
//!
//! This ADC example uses ePWM1 to generate a periodic ADC SOC - ADCINT1.
//! Two channels are converted, ADCINA4 and ADCINA2.
//!
//! \b Watch \b Variables \n
//! - Voltage1[10]    - Last 10 ADCRESULT0 values
//! - Voltage2[10]    - Last 10 ADCRESULT1 values
//! - ConversionCount - Current result number 0-9
//! - LoopCount       - Idle loop counter
//
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Prototype statements for functions found within this file.
__interrupt void adc_isr(void);
void Adc_Config(void);

// Global variables used in this example:
Uint16 LoopCount;
Uint16 ConversionCount;
Uint16 Voltage1[10];
Uint16 Voltage2[10];

main()
{
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
   EALLOW;  // This is needed to write to EALLOW protected register
   PieVectTable.ADCINT1 = &adc_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
   InitAdc();  // For this example, init the ADC
   AdcOffsetSelfCal();

// Step 5. User specific code, enable interrupts:

// Enable ADCINT1 in PIE
   PieCtrlRegs.PIEIER1.bit.INTx1 = 1;	// Enable INT 1.1 in the PIE
   IER |= M_INT1; 						// Enable CPU Interrupt 1
   EINT;          						// Enable Global interrupt INTM
   ERTM;          						// Enable Global realtime interrupt DBGM

   LoopCount = 0;
   ConversionCount = 0;

// Configure ADC
// Note: Channel ADCINA4  will be double sampled to workaround the ADC 1st sample issue for rev0 silicon errata

   EALLOW;
   AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;	//ADCINT1 trips after AdcResults latch
   AdcRegs.INTSEL1N2.bit.INT1E      = 1;	//Enabled ADCINT1
   AdcRegs.INTSEL1N2.bit.INT1CONT   = 0;	//Disable ADCINT1 Continuous mode
   AdcRegs.INTSEL1N2.bit.INT1SEL	= 2;	//setup EOC2 to trigger ADCINT1 to fire
   AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 4;	//set SOC0 channel select to ADCINA4(dummy sample for rev0 errata workaround)
   AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 4;	//set SOC1 channel select to ADCINA4
   AdcRegs.ADCSOC2CTL.bit.CHSEL 	= 2;	//set SOC2 channel select to ADCINA2
   AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 5;	//set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1, then SOC2
   AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 5;	//set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1, then SOC2
   AdcRegs.ADCSOC2CTL.bit.TRIGSEL 	= 5;	//set SOC2 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1, then SOC2
   AdcRegs.ADCSOC0CTL.bit.ACQPS 	= 6;	//set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
   AdcRegs.ADCSOC1CTL.bit.ACQPS 	= 6;	//set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
   AdcRegs.ADCSOC2CTL.bit.ACQPS 	= 6;	//set SOC2 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
   EDIS;

// Assumes ePWM1 clock is already enabled in InitSysCtrl();
   EPwm1Regs.ETSEL.bit.SOCAEN	= 1;		// Enable SOC on A group
   EPwm1Regs.ETSEL.bit.SOCASEL	= 4;		// Select SOC from from CPMA on upcount
   EPwm1Regs.ETPS.bit.SOCAPRD 	= 1;		// Generate pulse on 1st event
   EPwm1Regs.CMPA.half.CMPA 	= 0x0080;	// Set compare A value
   EPwm1Regs.TBPRD 				= 0xFFFF;	// Set period for ePWM1
   EPwm1Regs.TBCTL.bit.CTRMODE 	= 0;		// count up and start

// Wait for ADC interrupt
   for(;;)
   {
      LoopCount++;
   }
}

__interrupt void  adc_isr(void)
{
  Voltage1[ConversionCount] = AdcResult.ADCRESULT1; //discard ADCRESULT0 as part of the workaround to the 1st sample errata for rev0
  Voltage2[ConversionCount] = AdcResult.ADCRESULT2;

  // If 20 conversions have been logged, start over
  if(ConversionCount == 9)
  {
     ConversionCount = 0;
  }
  else
  {
      ConversionCount++;
  }

  AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;		//Clear ADCINT1 flag reinitialize for next SOC
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

  return;
}



