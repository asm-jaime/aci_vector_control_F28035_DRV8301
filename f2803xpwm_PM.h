/* ==================================================================================
File name:        F2803xPWM_PM.H                     
                    
Originator:	 Digital Control Systems Group
			 Texas Instruments
Description: Header file containing data type, object, macro definitions and 
			 initializers. This file is specific to "DRV8301" kit and configures
			 PWM 1,2,3

Target: TMS320F2803x family
              
=====================================================================================
History:
-------------------------------------------------------------------------------------
 02-09-2011	Version 1.0
------------------------------------------------------------------------------------*/

#ifndef __F2803X_PWM_H__
#define __F2803X_PWM_H__

#include "f2803xbmsk.h"

/*----------------------------------------------------------------------------
Initialization constant for the F280X Time-Base Control Registers for PWM Generation. 
Sets up the timer to run free upon emulation suspend, count up-down mode
prescaler 1.
----------------------------------------------------------------------------*/
#define PWM_INIT_STATE ( FREE_RUN_FLAG +         \
                         PRDLD_IMMEDIATE  +       \
                         TIMER_CNT_UPDN +         \
                         HSPCLKDIV_PRESCALE_X_1 + \
                         CLKDIV_PRESCALE_X_1  +   \
                         PHSDIR_CNT_UP    +       \
                         CNTLD_DISABLE )

/*----------------------------------------------------------------------------
Initialization constant for the F280X Compare Control Register. 
----------------------------------------------------------------------------*/
#define CMPCTL_INIT_STATE ( LOADAMODE_ZRO + \
                            LOADBMODE_ZRO + \
                            SHDWAMODE_SHADOW + \
                            SHDWBMODE_SHADOW )

/*----------------------------------------------------------------------------
Initialization constant for the F280X Action Qualifier Output A Register. 
----------------------------------------------------------------------------*/
#define AQCTLA_INIT_STATE ( CAU_SET + CAD_CLEAR )

/*----------------------------------------------------------------------------
Initialization constant for the F280X Dead-Band Generator registers for PWM Generation. 
Sets up the dead band for PWM and sets up dead band values.
----------------------------------------------------------------------------*/
#define DBCTL_INIT_STATE  (BP_ENABLE + POLSEL_ACTIVE_HI_CMP)

#define DBCNT_INIT_STATE   100   // 100 counts = 1.66 usec (delay) * 100 count/usec (for TBCLK = SYSCLK/1)

/*----------------------------------------------------------------------------
Initialization constant for the F280X PWM Chopper Control register for PWM Generation. 
----------------------------------------------------------------------------*/
#define  PCCTL_INIT_STATE  CHPEN_DISABLE

/*----------------------------------------------------------------------------
Initialization constant for the F280X Trip Zone Select Register 
----------------------------------------------------------------------------*/
#define  TZSEL_INIT_STATE  (ENABLE_TZ3_OST + ENABLE_TZ2_OST)
//#define  TZSEL_INIT_STATE  DISABLE_TZSEL
//#define  TZSEL_INIT_STATE  ENABLE_TZ3_OST
							            
/*----------------------------------------------------------------------------
Initialization constant for the F280X Trip Zone Control Register 
----------------------------------------------------------------------------*/
#define  TZCTL_INIT_STATE ( TZA_FORCE_LO + TZB_FORCE_LO + \
                            DCAEVT1_HI_Z + DCAEVT2_HI_Z + \
                            DCBEVT1_HI_Z + DCBEVT2_HI_Z )
                                                                 
/*-----------------------------------------------------------------------------
	Define the structure of the PWM Driver Object 
-----------------------------------------------------------------------------*/
typedef struct {   
        Uint16 PeriodMax;     // Parameter: PWM Half-Period in CPU clock cycles (Q0)
        int16 MfuncPeriod;    // Input: Period scaler (Q15) 
        int16 MfuncC1;        // Input: EPWM1 A&B Duty cycle ratio (Q15)
        int16 MfuncC2;        // Input: EPWM2 A&B Duty cycle ratio (Q15) 
        int16 MfuncC3;        // Input: EPWM3 A&B Duty cycle ratio (Q15)
		int16 PWM1out;
		int16 PWM2out;
		int16 PWM3out;
        } PWMGEN ;    

/*-----------------------------------------------------------------------------
	Define a PWMGEN_handle
-----------------------------------------------------------------------------*/
typedef PWMGEN *PWMGEN_handle;

/*------------------------------------------------------------------------------
	Default Initializers for the F280X PWMGEN Object 
------------------------------------------------------------------------------*/
#define F280X_FC_PWM_GEN    { 1000,   \
                              0x7FFF, \
                              0x4000, \
                              0x4000, \
                              0x4000, \
							  0x4000, \
							  0x4000, \
							  0x4000, \
                             }
                             

#define PWMGEN_DEFAULTS 	F280X_FC_PWM_GEN
/*------------------------------------------------------------------------------
	PWM Init & PWM Update Macro Definitions
------------------------------------------------------------------------------*/


#define PWM_INIT_MACRO(v)													\
	     /* Setup Sync*/													\
         EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/			\
         EPwm2Regs.TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/			\
         EPwm3Regs.TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/			\
        																	\
																			\
         /* Allow each timer to be sync'ed*/								\
         EPwm1Regs.TBCTL.bit.PHSEN = 1;										\
         EPwm2Regs.TBCTL.bit.PHSEN = 1;										\
         EPwm3Regs.TBCTL.bit.PHSEN = 1;										\
																			\
         /* Init Timer-Base Period Register for EPWM1-EPWM3*/				\
         EPwm1Regs.TBPRD = v.PeriodMax;										\
         EPwm2Regs.TBPRD = v.PeriodMax;										\
         EPwm3Regs.TBPRD = v.PeriodMax;										\
																			\
         /* Init Timer-Base Phase Register for EPWM1-EPWM3*/				\
         EPwm1Regs.TBPHS.half.TBPHS = 0;									\
         EPwm2Regs.TBPHS.half.TBPHS = 0;									\
         EPwm3Regs.TBPHS.half.TBPHS = 0;									\
																			\
         /* Init Timer-Base Control Register for EPWM1-EPWM3*/				\
         EPwm1Regs.TBCTL.all = PWM_INIT_STATE;								\
         EPwm2Regs.TBCTL.all = PWM_INIT_STATE;								\
         EPwm3Regs.TBCTL.all = PWM_INIT_STATE;								\
																			\
         /* Init Compare Control Register for EPWM1-EPWM3*/					\
         EPwm1Regs.CMPCTL.all = CMPCTL_INIT_STATE;							\
         EPwm2Regs.CMPCTL.all = CMPCTL_INIT_STATE;							\
         EPwm3Regs.CMPCTL.all = CMPCTL_INIT_STATE;							\
																			\
         /* Init Action Qualifier Output A Register for EPWM1-EPWM3*/		\
         EPwm1Regs.AQCTLA.all = AQCTLA_INIT_STATE;							\
         EPwm2Regs.AQCTLA.all = AQCTLA_INIT_STATE;							\
         EPwm3Regs.AQCTLA.all = AQCTLA_INIT_STATE;							\
																			\
         /* Init Dead-Band Generator Control Register for EPWM1-EPWM3*/		\
         EPwm1Regs.DBCTL.all = DBCTL_INIT_STATE;							\
         EPwm2Regs.DBCTL.all = DBCTL_INIT_STATE;							\
         EPwm3Regs.DBCTL.all = DBCTL_INIT_STATE;							\
																			\
         /* Init Dead-Band Generator for EPWM1-EPWM3*/						\
         EPwm1Regs.DBFED = DBCNT_INIT_STATE;								\
         EPwm1Regs.DBRED = DBCNT_INIT_STATE;								\
         EPwm2Regs.DBFED = DBCNT_INIT_STATE;								\
         EPwm2Regs.DBRED = DBCNT_INIT_STATE;								\
         EPwm3Regs.DBFED = DBCNT_INIT_STATE;								\
         EPwm3Regs.DBRED = DBCNT_INIT_STATE;								\
																			\
         /* Init PWM Chopper Control Register for EPWM1-EPWM3*/				\
         EPwm1Regs.PCCTL.all = PCCTL_INIT_STATE;							\
         EPwm2Regs.PCCTL.all = PCCTL_INIT_STATE;							\
         EPwm3Regs.PCCTL.all = PCCTL_INIT_STATE;							\
																			\
         EALLOW;                       /* Enable EALLOW */					\
																			\
         /* Init Trip Zone Select Register*/								\
         EPwm1Regs.TZSEL.all = TZSEL_INIT_STATE;							\
         EPwm2Regs.TZSEL.all = TZSEL_INIT_STATE;							\
         EPwm3Regs.TZSEL.all = TZSEL_INIT_STATE;							\
 																			\
         /* Init Trip Zone Control Register*/								\
         EPwm1Regs.TZCTL.all = TZCTL_INIT_STATE;							\
         EPwm2Regs.TZCTL.all = TZCTL_INIT_STATE;							\
         EPwm3Regs.TZCTL.all = TZCTL_INIT_STATE;							\
																			\
         EDIS;                         /* Disable EALLOW*/			





	int16 MPeriod;
	int32 Tmp;

#define PWM_MACRO(v)																		\
																							\
/* Compute the timer period (Q0) from the period modulation input (Q15)*/					\
																							\
	Tmp = (int32)v.PeriodMax*(int32)v.MfuncPeriod;			/* Q15 = Q0*Q15	*/				\
	MPeriod = (int16)(Tmp>>16) + (int16)(v.PeriodMax>>1);	/*Q0 = (Q15->Q0)/2 + (Q0/2)*/	\
																							\
	EPwm1Regs.TBPRD = MPeriod;																\
	EPwm2Regs.TBPRD = MPeriod;																\
	EPwm3Regs.TBPRD = MPeriod;																\
																							\
/*Compute the compare value (Q0) from the related duty cycle ratio (Q15)*/					\
																							\
	Tmp = (int32)MPeriod*(int32)v.MfuncC1;				/* Q15 = Q0*Q15	*/					\
	v.PWM1out = (int16)(Tmp>>16) + (int16)(MPeriod>>1);	/*Q0 = (Q15->Q0)/2 + (Q0/2)*/		\
																							\
/*Compute the compare value (Q0) from the related duty cycle ratio (Q15)*/					\
																							\
	Tmp = (int32)MPeriod*(int32)v.MfuncC2;				/* Q15 = Q0*Q15	*/					\
	v.PWM2out= (int16)(Tmp>>16) + (int16)(MPeriod>>1);	/*Q0 = (Q15->Q0)/2 + (Q0/2)*/		\
																							\
/*Compute the compare value (Q0) from the related duty cycle ratio (Q15)*/					\
																							\
	Tmp = (int32)MPeriod*(int32)v.MfuncC3;				/* Q15 = Q0*Q15	*/					\
	v.PWM3out= (int16)(Tmp>>16) + (int16)(MPeriod>>1);	/*Q0 = (Q15->Q0)/2 + (Q0/2)*/

#endif  // __F2803X_PWM_H__
