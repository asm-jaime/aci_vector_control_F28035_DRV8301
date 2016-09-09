/*
 * main.h
 *
 *  Created on: 2015-1-10
 *      Author: 芯源电子工作室
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "com.h"
#include "IQmathLib.h"
#include "DRV8301_SPI.h"
#include "f2803xpwm.h"
#include "f2803xileg_vdc.h"
#include "f2803xqep.h"
#include "clarke.h"
#include "ipark.h"
#include "park.h"
#include "pid_grando.h"
#include "rampgen.h"
#include "rmp_cntl.h"
#include "speed_fr.h"
#include "svgen_dq.h"
#include <math.h>

#ifdef SARAM
#include "dlog4ch.h"
#endif

/*------------------------------------------------------------------------------
Following is the list of the Build Level choices.
------------------------------------------------------------------------------*/
#define LEVEL1  1      		// Open loop and speed measurement
#define LEVEL2	2			// Auto-calibrate the current sensor offsets
#define LEVEL3  3           // Closed current(torque) loop and speed measurement
#define LEVEL4	4			// Closed current(torque) loop and closed speed loop

/*------------------------------------------------------------------------------
This line sets the BUILDLEVEL to one of the available choices.
------------------------------------------------------------------------------*/
#define   BUILDLEVEL LEVEL3

#ifndef BUILDLEVEL
#error  Critical: BUILDLEVEL must be defined !!
#endif  // BUILDLEVEL
//------------------------------------------------------------------------------

#ifndef TRUE
#define FALSE 0
#define TRUE  1
#endif

#define PI 3.14159265358979

// Define the system frequency (MHz)
#define SYSTEM_FREQUENCY 60

// Define the ISR frequency (kHz)
#define ISR_FREQUENCY 10

//cutoff freq and time constant of the offset calibration LPF
#define WC_CAL	100.0
#define TC_CAL	1/WC_CAL

// This machine parameters are based on 24V PM motors inside Multi-Axis +PFC package
// Define the PMSM motor parameters
//#define RS 		0.79               	// Stator resistance (ohm)	Anaheim
#define RS 		0.6               		// Stator resistance (ohm)	57BL52-230
//#define RS 		0.89               	// Stator resistance (ohm)	test motor
#define RR   	0               		// Rotor resistance (ohm)
//#define LS   	0.0012     				// Stator inductance (H)	Anaheim
#define LS   	0.00075     			// Stator inductance (H)	57BL52-230
//#define LS   	0.62     				// Stator inductance (H)	test motor
#define LR   	0						// Rotor inductance (H)
#define LM   	0						// Magnetizing inductance (H)
#define POLES   4						// Number of poles

// Define the base quantites
#define BASE_VOLTAGE    38.29		    // Base peak phase voltage (volt), maximum measurable DC Bus(66.32V)/sqrt(3)

//options for BASE_CURRENT based on DRV830x current-sense amplifier gain setting
//NOTE: DRV8302 can only be set to gain of 10 or 40
//#define DRV_GAIN	10
//#define DRV_GAIN	20
//#define DRV_GAIN	40
#define DRV_GAIN	80

#if DRV_GAIN == 10
#define BASE_CURRENT    82.5           	// Base peak phase current (amp) , maximum measurable peak current (with DRV830x gain set to 10)
#elif DRV_GAIN == 20
#define BASE_CURRENT    41.25          	// Base peak phase current (amp) , maximum measurable peak current (with DRV830x gain set to 20)
#elif DRV_GAIN == 40
#define BASE_CURRENT    20.625         	// Base peak phase current (amp) , maximum measurable peak current (with DRV830x gain set to 40)
#elif DRV_GAIN == 80
#define BASE_CURRENT    10.3125        	// Base peak phase current (amp) , maximum measurable peak current (with DRV830x gain set to 80)
#else
#error  Invalid GAIN selection !!
#endif

#define BASE_FREQ      	200           	// Base electrical frequency (Hz)

// Defines the direction of rotation of motor
//#define MOTOR_DIR	0					// CW
#define MOTOR_DIR	1					// CCW

#define GATE_ON		GpioDataRegs.GPBSET.bit.GPIO40    = 1;
#define GATE_OFF	GpioDataRegs.GPBCLEAR.bit.GPIO40  = 1;
#define LED_ON		GpioDataRegs.GPBCLEAR.bit.GPIO34  = 1;
#define LED_OFF		GpioDataRegs.GPBSET.bit.GPIO34    = 1;
#define LED_BLINK	GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

#define VCC_3V3		3.32				// V
#define SAMP_RES	0.002				// Ω

#define TXBUFLEN	10

#endif /* MAIN_H_ */
