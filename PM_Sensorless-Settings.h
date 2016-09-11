/* =================================================================================
File name:  PM_Sensorless-Settings.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Incremental Build Level control file.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2010	Version 1.1
=================================================================================  */
#ifndef PROJ_SETTINGS_H

/*------------------------------------------------------------------------------
Following is the list of the Build Level choices.
------------------------------------------------------------------------------*/
#define LEVEL1  1      		// Module check out (do not connect the motors) 
#define LEVEL2  2           // Verify ADC, park/clarke 
#define LEVEL3	3			// Auto-calibrate the current sensor offsets
#define LEVEL4  4           // Verify closed current(torque) loop and PIDs and speed measurement
#define LEVEL5  5           // Verify speed estimation and rotor position est.
#define LEVEL6  6           // Verify closed speed loop and speed PID
#define LEVEL7  7           // Verify closed speed loop (sensorless)
						
/*------------------------------------------------------------------------------
This line sets the BUILDLEVEL to one of the available choices.
------------------------------------------------------------------------------*/
#define   BUILDLEVEL LEVEL1



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
#if (DSP2803x_DEVICE_H==1)
#define SYSTEM_FREQUENCY 60
#elif (DSP280x_DEVICE_H==1)
#define SYSTEM_FREQUENCY 100
#elif (F2806x_DEVICE_H==1)
#define SYSTEM_FREQUENCY 80
#endif

//Define system Math Type
// Select Floating Math Type for 2806x
// Select IQ Math Type for 2803x 
#if (DSP2803x_DEVICE_H==1)
#define MATH_TYPE 0 
#elif (F2806x_DEVICE_H==1)
#define MATH_TYPE 1
#endif


// Define the ISR frequency (kHz)
#define ISR_FREQUENCY 10

//cutoff freq and time constant of the offset calibration LPF
#define WC_CAL	100.0
#define TC_CAL	1/WC_CAL

// This machine parameters are based on 24V PM motors inside Multi-Axis +PFC package
// Define the PMSM motor parameters
//#define RS 		0.79               		// Stator resistance (ohm)	Anaheim
#define RS 		0.0725               		// Stator resistance (ohm)	test motor
#define RR   	0               		// Rotor resistance (ohm) 
//#define LS   	0.0012     				// Stator inductance (H)		Anaheim 
#define LS   	0.000693     				// Stator inductance (H)	test motor 
#define LR   	0						// Rotor inductance (H) 	
#define LM   	0						// Magnetizing inductance (H)
#define POLES   8						// Number of poles 

// Define the base quantites 
#define BASE_VOLTAGE    38.29		    // Base peak phase voltage (volt), maximum measurable DC Bus(66.32V)/sqrt(3) 

//options for BASE_CURRENT based on DRV830x current-sense amplifier gain setting
//NOTE: DRV8302 can only be set to gain of 10 or 40
//#define DRV_GAIN	10
//#define DRV_GAIN	20
#define DRV_GAIN	40
//#define DRV_GAIN	80

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

#endif 
