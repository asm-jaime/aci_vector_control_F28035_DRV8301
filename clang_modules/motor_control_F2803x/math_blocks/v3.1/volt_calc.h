/* =================================================================================
File name:        VOLT_CAL.H (IQ version)                      
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
 Header file containing constants, data type, and macro  definitions for the VOLT_CALC module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 4-15-2010	Version 1.1                                               
------------------------------------------------------------------------------*/
#ifndef __VOLT_CAL_H__
#define __VOLT_CAL_H__

typedef struct 	{ _iq  DcBusVolt;		// Input: DC-bus voltage (pu)
			  	  _iq  MfuncV1;  		// Input: Modulation voltage phase A (pu)
		  	  	  _iq  MfuncV2;			// Input: Modulation voltage phase B (pu)	
		   	  	  _iq  MfuncV3;			// Input: Modulation voltage phase C (pu) 
                  Uint32  OutOfPhase; 	// Parameter: Out of Phase adjustment (0 or 1) (Q0) - independently with global Q
	  	  	  	  _iq  VphaseA;			// Output: Phase voltage phase A (pu)
		   	  	  _iq  VphaseB;			// Output: Phase voltage phase B (pu) 
		  	  	  _iq  VphaseC;			// Output: Phase voltage phase C (pu) 
		  	  	  _iq  Valpha;			// Output: Stationary d-axis phase voltage (pu)
		  	  	  _iq  Vbeta;  			// Output: Stationary q-axis phase voltage (pu)
		  	  	} PHASEVOLTAGE;	                   

typedef PHASEVOLTAGE *PHASEVOLTAGE_handle; 

/*
OutOfPhase = 1 for the out of phase correction if
* MfuncV1 is out of phase with PWM1,
* MfuncV2 is out of phase with PWM3,
* MfuncV3 is out of phase with PWM5,
otherwise, set 0 if their phases are correct.
*/

/*-----------------------------------------------------------------------------
Default initalizer for the PHASEVOLTAGE object.
-----------------------------------------------------------------------------*/                     
#define PHASEVOLTAGE_DEFAULTS { 0, \
                          		0, \
                          		0, \
                          		0, \
                          		1, \
                          		0, \
                          		0, \
                          		0, \
		         				0, \
 		          				0, \
                  				}

#define ONE_THIRD  _IQ(0.33333333333333)
#define TWO_THIRD  _IQ(0.66666666666667)
#define INV_SQRT3  _IQ(0.57735026918963)
/*------------------------------------------------------------------------------
 	Phase Voltage Calculation (VOLT_C) Macro Definition
------------------------------------------------------------------------------*/


#define VOLT_MACRO(v)															\
																				\
if (v.OutOfPhase > 0)															\
{ v.MfuncV1 = -v.MfuncV1;														\
  v.MfuncV2 = -v.MfuncV2;														\
  v.MfuncV3 = -v.MfuncV3; 														\
}																				\
																				\
/* Scale the incomming Modulation functions with the DC bus voltage value*/		\
  v.MfuncV1 = _IQmpy(v.DcBusVolt,v.MfuncV1);									\
  v.MfuncV2 = _IQmpy(v.DcBusVolt,v.MfuncV2);									\
  v.MfuncV3 = _IQmpy(v.DcBusVolt,v.MfuncV3);									\
																				\
/* Calculate the 3 Phase voltages */											\
																				\
/* Phase A */																	\
  v.VphaseA = _IQmpy(TWO_THIRD,v.MfuncV1);										\
  v.VphaseA -= _IQmpy(ONE_THIRD,v.MfuncV2);										\
  v.VphaseA -= _IQmpy(ONE_THIRD,v.MfuncV3);										\
																				\
/* Phase B */																	\
  v.VphaseB = _IQmpy(TWO_THIRD,v.MfuncV2);										\
  v.VphaseB -= _IQmpy(ONE_THIRD,v.MfuncV1);										\
  v.VphaseB -= _IQmpy(ONE_THIRD,v.MfuncV3);										\
																				\
/* Voltage transformation (a,b,c)  ->  (Alpha,Beta)	*/							\
  v.Valpha = v.VphaseA;															\
  v.Vbeta = _IQmpy((v.VphaseA + _IQmpy2(v.VphaseB)),INV_SQRT3);


#endif // __VOLT_CAL_H__

// Phase C (if needed)
//	   v->VphaseC = _IQmpy(TWO_THIRD,v->MfuncV3);
//     v->VphaseC -= _IQmpy(ONE_THIRD,v->MfuncV1); 
//     v->VphaseC -= _IQmpy(ONE_THIRD,v->MfuncV2);






















