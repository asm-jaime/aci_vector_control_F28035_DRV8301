/* ==============================================================================
System Name:  	PM_Sensorless

File Name:		PM_Sensorless.h

Description:	Primary system header file for the Real Implementation of Sensorless  
          		Field Orientation Control for a Three Phase Permanent-Magnet
          		Synchronous Motor 

Originator:		Digital control systems Group - Texas Instruments

Note: In this software, the default inverter is supposed to be DRV8312-EVM. 
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 02-07-2011	Version 1.0
=================================================================================  */

/*-------------------------------------------------------------------------------
Next, Include project specific include files.
-------------------------------------------------------------------------------*/

#include "smopos.h"       		// Include header for the SMOPOS object 
#include "smopos_const.h"       // Include header for the SMOPOS object
#include "park.h"       		// Include header for the PARK object 
#include "ipark.h"       		// Include header for the IPARK object 
#include "pid_grando.h"       	// Include header for the PID_GRANDO_CONTROLLER object 
#include "clarke.h"         	// Include header for the CLARKE object 
#include "svgen_dq.h"       	// Include header for the SVGENDQ object 
#include "rampgen.h"        	// Include header for the RAMPGEN object 
#include "rmp_cntl.h"       	// Include header for the RMPCNTL object 
#include "volt_calc.h"      	// Include header for the PHASEVOLTAGE object 
#include "speed_est.h"          // Include header for the SPEED_ESTIMATION object 
#include "speed_fr.h"			// Include header for the SPEED_MEAS_QEP object

#if (DSP2803x_DEVICE_H==1)
#include "f2803xileg_vdc_PM.h" 	// Include header for the ILEG2DCBUSMEAS object 
#include "f2803xpwm_PM.h"       // Include header for the PWMGEN object
#include "f2803xpwmdac_PM.h"    // Include header for the PWMGEN object
#include "f2803xqep_PM.h"       // Include header for the QEP object
#endif

#if (F2806x_DEVICE_H==1)
#include "f2806xileg_vdc_PM.h" 	// Include header for the ILEG2DCBUSMEAS object 
#include "f2806xpwm_PM.h"       // Include header for the PWMGEN object
#include "f2806xpwmdac_PM.h"    // Include header for the PWMGEN object
#include "f2806xqep_PM.h"       // Include header for the QEP object
#endif

#include "dlog4ch-PM_Sensorless.h" // Include header for the DLOG_4CH object

#ifdef DRV8301
#include "DRV8301_SPI.h"
#endif

//===========================================================================
// No more.
//===========================================================================
