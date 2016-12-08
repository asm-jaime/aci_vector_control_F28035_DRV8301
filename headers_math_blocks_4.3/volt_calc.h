/* =================================================================================
File name:        VOLT_CAL.H 
===================================================================================*/


#ifndef __VOLT_CAL_H__
#define __VOLT_CAL_H__

typedef struct 	{ _iq  DcBusVolt;		// Input: DC-bus voltage (pu)
			  	  _iq  MfuncV1;  		// Input: Modulation voltage phase A (pu)
		  	  	  _iq  MfuncV2;			// Input: Modulation voltage phase B (pu)	
		   	  	  _iq  MfuncV3;			// Input: Modulation voltage phase C (pu) 
                  Uint16  OutOfPhase; 	// Parameter: Out of Phase adjustment (0 or 1) (Q0) - independently with global Q
	  	  	  	  _iq  VphaseA;			// Output: Phase voltage phase A (pu)
		   	  	  _iq  VphaseB;			// Output: Phase voltage phase B (pu) 
		  	  	  _iq  VphaseC;			// Output: Phase voltage phase C (pu) 
		  	  	  _iq  Valpha;			// Output: Stationary d-axis phase voltage (pu)
		  	  	  _iq  Vbeta;  			// Output: Stationary q-axis phase voltage (pu)
		  	  	  _iq  temp;				// Variable: temp variable
		  	  	} PHASEVOLTAGE;	                   


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
 	Phase Voltage Calculation Macro Definition
------------------------------------------------------------------------------*/


#define PHASEVOLT_MACRO(v)														\
																				\
																				\
/* Scale the incomming Modulation functions with the DC bus voltage value*/		\
/* and calculate the 3 Phase voltages */										\
  v.temp 	  = _IQmpy(v.DcBusVolt,ONE_THIRD);									\
  v.VphaseA   = _IQmpy(v.temp,(_IQmpy2(v.MfuncV1)-v.MfuncV2-v.MfuncV3));		\
  v.VphaseB   = _IQmpy(v.temp,(_IQmpy2(v.MfuncV2)-v.MfuncV1-v.MfuncV3));		\
																				\
  if (v.OutOfPhase==0)															\
  {	  v.VphaseA=-v.VphaseA;														\
  	  v.VphaseB=-v.VphaseB;														\
  }	   																			\
/* Voltage transformation (a,b,c)  ->  (Alpha,Beta)	*/							\
  v.Valpha = v.VphaseA;															\
  v.Vbeta = _IQmpy((v.VphaseA + _IQmpy2(v.VphaseB)),INV_SQRT3);


#endif // __VOLT_CAL_H__

// Phase C (if needed)
// v.VphaseC   = _IQmpy(v.temp,(_IQmpy2(v.MfuncV3)-v.MfuncV2-v.MfuncV1));	\






















