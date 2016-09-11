/* =================================================================================
File name:        F2806XQEP_PM.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments
Description:  
Header file containing data type, object, macro definitions and initializers. 
====================================================================================
History:
-------------------------------------------------------------------------------------
 02-06-2011	Version 1.0
----------------------------------------------------------------------------------*/

#ifndef __F2806X_QEP_H__
#define __F2806X_QEP_H__

#include "f2806xbmsk.h"

/*-----------------------------------------------------------------------------
    Initialization states for EQEP Decode Control Register
------------------------------------------------------------------------------*/
#define QDECCTL_INIT_STATE     ( XCR_X2 + QSRC_QUAD_MODE )

/*-----------------------------------------------------------------------------
    Initialization states for EQEP Control Register
------------------------------------------------------------------------------*/
#define QEPCTL_INIT_STATE      ( QEP_EMULATION_FREE + \
                                 PCRM_INDEX + \
                                 IEI_RISING + \
                                 IEL_RISING + \
                                 QPEN_ENABLE + \
                                 QCLM_TIME_OUT + \
                                 UTE_ENABLE )  

/*-----------------------------------------------------------------------------
    Initialization states for EQEP Position-Compare Control Register
------------------------------------------------------------------------------*/
#define QPOSCTL_INIT_STATE      PCE_DISABLE 

/*-----------------------------------------------------------------------------
    Initialization states for EQEP Capture Control Register
------------------------------------------------------------------------------*/
#define QCAPCTL_INIT_STATE     ( UPPS_X32 + \
                                 CCPS_X128 + \
                                 CEN_ENABLE )

/*-----------------------------------------------------------------------------
Define the structure of the QEP (Quadrature Encoder) Driver Object 
-----------------------------------------------------------------------------*/
typedef struct {_iq ElecTheta;        // Output: Motor Electrical angle (Q24)
                _iq MechTheta;        // Output: Motor Mechanical Angle (Q24) 
                Uint16 DirectionQep;    // Output: Motor rotation direction (Q0)
                Uint16 QepPeriod;       // Output: Capture period of QEP signal in number of EQEP capture timer (QCTMR) period  (Q0)
                Uint32 QepCountIndex;   // Variable: Encoder counter index (Q0) 
                 int32 RawTheta;        // Variable: Raw angle from EQEP Postiion counter (Q0)
                _iq MechScaler;      // Parameter: 0.9999/total count (Q30) 
                Uint16 LineEncoder;     // Parameter: Number of line encoder (Q0) 
                Uint16 PolePairs;       // Parameter: Number of pole pairs (Q0) 
                 int32 CalibratedAngle; // Parameter: Raw angular offset between encoder index and phase a (Q0)
                Uint16 IndexSyncFlag;   // Output: Index sync status (Q0) 
                }  QEP;

/*-----------------------------------------------------------------------------
Define a QEP_handle
-----------------------------------------------------------------------------*/
typedef QEP *QEP_handle;

/*-----------------------------------------------------------------------------
Default initializer for the QEP Object.
-----------------------------------------------------------------------------*/

#define QEP_DEFAULTS { 0x0,0x0,0x0,0x0,0x0,0x0,0x00020000,0x0,2,0,0x0}  
               

/*-----------------------------------------------------------------------------
	QEP Init and QEP Update Macro Definitions                                 
-----------------------------------------------------------------------------*/


#define QEP_INIT_MACRO(v)																		\
																								\
     EQep1Regs.QDECCTL.all = QDECCTL_INIT_STATE;												\
     EQep1Regs.QEPCTL.all = QEPCTL_INIT_STATE;													\
     EQep1Regs.QPOSCTL.all = QPOSCTL_INIT_STATE;												\
     EQep1Regs.QUPRD = 600000;		        	/* Unit Timer for 100Hz*/						\
     EQep1Regs.QCAPCTL.all = QCAPCTL_INIT_STATE;												\
     EQep1Regs.QPOSMAX = 4*v.LineEncoder;														\
																								\
     EALLOW;                       /* Enable EALLOW*/											\
     GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;  /* GPIO20 is EQEP1A */								\
     GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;  /* GPIO21 is EQEP1B */								\
     GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;  /* GPIO23 is EQEP1I  */								\
     EDIS;                         /* Disable EALLOW*/							


#define QEP_MACRO(v)																			\
																								\
/* Check the rotational direction */															\
     v.DirectionQep = EQep1Regs.QEPSTS.bit.QDF;													\
																								\
/* Check the position counter for EQEP1 */														\
     v.RawTheta = EQep1Regs.QPOSCNT + v.CalibratedAngle;										\
     																							\
     if (v.RawTheta < 0)																		\
       v.RawTheta = v.RawTheta + EQep1Regs.QPOSMAX;												\
     else if (v.RawTheta > EQep1Regs.QPOSMAX)													\
       v.RawTheta = v.RawTheta - EQep1Regs.QPOSMAX;												\
       																							\
/* Compute the mechanical angle */																\
     v.MechTheta = v.MechScaler*v.RawTheta;														\
																								\
/* Compute the electrical angle */														\
     v.ElecTheta = (v.PolePairs*v.MechTheta) -floor(v.PolePairs*v.MechTheta); /* Q24 = Q0*Q24 */\
																								\
/* Check an index occurrence*/																	\
     if (EQep1Regs.QFLG.bit.IEL == 1)    														\
     {  																						\
     	v.IndexSyncFlag = 0x00F0;																\
        v.QepCountIndex = EQep1Regs.QPOSILAT;													\
    	EQep1Regs.QCLR.bit.IEL = 1;	/* Clear interrupt flag */									\
     }																							\
																								\
/* Check unit Time out-event for speed calculation: */											\
/* Unit Timer is configured for 100Hz in INIT function*/										\
	if(EQep1Regs.QFLG.bit.UTO == 1)																\
    {																							\
     		/***** Low Speed Calculation   ****/												\
   		if((EQep1Regs.QEPSTS.bit.COEF || EQep1Regs.QEPSTS.bit.CDEF))							\
  		{	/* Capture Counter overflowed, hence do no compute speed*/							\
  			EQep1Regs.QEPSTS.all = 0x000C;														\
   		}																						\
   		else if(EQep1Regs.QCPRDLAT!=0xffff)														\
   			/* Compute lowspeed using capture counter value*/									\
   			v.QepPeriod = EQep1Regs.QCPRDLAT;													\
    }




#endif // __F280X_QEP_H__ 




