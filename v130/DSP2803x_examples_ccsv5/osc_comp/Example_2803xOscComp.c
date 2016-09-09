//###########################################################################
//
//!  \addtogroup f2803x_example_list
//!  <h1>Internal Oscillator Compensation(osc_comp)</h1>
//!
//!  This program shows how to use the internal oscillator compensation
//!  functions in DSP2803x_OscComp.c. The temperature sensor is sampled
//!  and the raw temp sensor value is passed to the oscillator compensation
//!  function, which uses this parameter to compensate for
//!  frequency drift of the internal oscillator over temperature
//!
//!  \note
//!  - This program makes use of variables stored in OTP during factory
//!    test on 2803x TMS devices.
//!  - These OTP locations on pre-TMS devices may not be populated.
//!    Ensure that the following memory locations in TI OTP are populated
//!    (not 0xFFFF) before use:
//!    - 0x3D7E90 to 0x3D7EA4
//!
//!  \b Watch \b Variables \n
//!  - temp
//!  - SysCtrlRegs.INTOSC1TRIM
//!  - SysCtrlRegs.INTOSC2TRIM
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // DSP28x Headerfile


int16 temp;   //Temperature sensor reading

void main()
{
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2803x_SysCtrl.c file.
       InitSysCtrl();

    // Step 2. Initialize GPIO:
    // Enable XCLOCKOUT to allow monitoring of oscillator 1
       EALLOW;
       GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3; //enable XCLOCKOUT through GPIO mux
       SysCtrlRegs.XCLK.bit.XCLKOUTDIV = 2; //XCLOCKOUT = SYSCLK

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
    // Not required for this example

    // Configure the ADC:
    // Initialize the ADC
       InitAdc();
       AdcOffsetSelfCal();

       EALLOW;
       AdcRegs.ADCCTL1.bit.TEMPCONV  = 1;  //Connect channel A5 internally to the temperature sensor
       AdcRegs.ADCSOC0CTL.bit.CHSEL  = 5;  //Set SOC0 channel select to ADCINA5
       AdcRegs.ADCSOC1CTL.bit.CHSEL  = 5;  //Set SOC1 channel select to ADCINA5
       AdcRegs.ADCSOC0CTL.bit.ACQPS  = 36; //Set SOC0 acquisition period to 37 ADCCLK
       AdcRegs.ADCSOC1CTL.bit.ACQPS  = 36; //Set SOC1 acquisition period to 37 ADCCLK
       AdcRegs.INTSEL1N2.bit.INT1SEL = 1;  //Connect ADCINT1 to EOC1
       AdcRegs.INTSEL1N2.bit.INT1E  =  1;  //Enable ADCINT1


    // Note: two channels have been connected to the temp sensor
    // so that the first sample can be discarded to avoid the
    // ADC first sample issue.  See the device errata.

    // Set the flash OTP wait-states to minimum. This is important
    // for the performance of the compensation function.
       FlashRegs.FOTPWAIT.bit.OTPWAIT = 3;

    //Main program loop
    for(;;)
    {
        // Sample temperature sensor. Note: the end application will
        // be responsible for deciding how and when to sample the
        // temperature sensor so that the value can be passed to the
        // compensation function

           //Force start of conversion on SOC0 and SOC1
           AdcRegs.ADCSOCFRC1.all = 0x03;

           //Wait for end of conversion.
           while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0){}  //Wait for ADCINT1
           AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;        //Clear ADCINT1

           //Get temp sensor sample result from SOC1
           temp = AdcResult.ADCRESULT1;

          //Use temp sensor measurement to perform oscillator compensation even as temperature changes.
            Osc1Comp(temp);
            Osc2Comp(temp); //Also possible to recalibrate osc. 2

        //...other application tasks here...
    }
}


