/* ==================================================================================
File name:        F2803XCAP.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments
Description:  
Header file containing data type and object definitions and 
macro. 

Target: TMS320F280x family
              
=====================================================================================
History:
-------------------------------------------------------------------------------------
 04-15-2009	Version 1.0: Using DSP280x v. 1.10 or higher 
------------------------------------------------------------------------------------*/

#ifndef __F280X_CAP_H__
#define __F280X_CAP_H__

#include "f2803xbmsk.h"

/*-----------------------------------------------------------------------------
    Initialization states for ECAP Control Registers 1 and 2 for ECAP1
------------------------------------------------------------------------------*/
#define ECCTL1_INIT_STATE   ( CAP1POL_RISING_EDGE +  \
                              CAPLDEN_ENABLE + \
                              CTRRST1_DIFFERENCE_TS + \
                              EVTFLTPS_X_1 + \
                              EMULATION_FREE  )

#define ECCTL2_INIT_STATE   ( CONTINUOUS_MODE + \
                              TSCNTSTP_FREE + \
                              SYNCI_DISABLE + \
                              SYNCO_DISABLE + \
                              CAPTURE_MODE )

/*-----------------------------------------------------------------------------
Define the structure of the Capture Driver Object 
------------------------------------------------------------------------------*/
typedef struct { int32 EventPeriod;    // Output: Timer value difference between two edges detected (Q0) 
               	 Uint16 CapReturn;
               } CAPTURE;

/*-----------------------------------------------------------------------------
Define a handle for the CAPTURE object
------------------------------------------------------------------------------*/
typedef CAPTURE *CAPTURE_handle;

/*------------------------------------------------------------------------------
Default Initializer for the F280X CAPTURE Object
------------------------------------------------------------------------------*/
#define F280XCAP1       {1,0 \
                        }

/*------------------------------------------------------------------------------
Target Independent Default Initializer CAPTURE Object
------------------------------------------------------------------------------*/
#define CAPTURE_DEFAULTS  F280XCAP1

/*------------------------------------------------------------------------------
	CAP_INIT & CAP Macro Definitions
------------------------------------------------------------------------------*/                                             

#define CAP_INIT_MACRO(v)											\
    /* Init ECAP Control Registers 1 and 2 for ECAP1*/				\
    ECap1Regs.ECCTL1.all = ECCTL1_INIT_STATE;						\
    ECap1Regs.ECCTL2.all = ECCTL2_INIT_STATE;						\
																	\
    EALLOW;                       /* Enable EALLOW */				\
    /* Set up the ECAP1 pin to primary function*/					\
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;  /* GPIO24 is ECAP1 */		\
    EDIS;                         /* Disable EALLOW	*/				

	
	
#define CAP_MACRO(v)																					\
    if(ECap1Regs.ECFLG.bit.CEVT1 != 0)/* Check status of one entry of first event of ECAP1 pin */		\
    {																									\
    v.EventPeriod = ECap1Regs.CAP1;  /* Stamp the timer counter difference between two edges detected*/	\
    v.CapReturn=0;                   /* Then, return zero*/												\
    } 																									\
    else																								\
    {																									\
    v.CapReturn=1;                   /* Else, return one */												\
    }


#endif //  __F280X_CAP_H__




