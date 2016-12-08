/* =================================================================================
File name:        SPEED_EST.H  (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro  definitions for the SPEED_EST module
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-15-2009	Version 1.0                                                
------------------------------------------------------------------------------*/
#ifndef __SPEED_EST_H__
#define __SPEED_EST_H__

typedef struct {
       _iq EstimatedTheta;  	// Input: Electrical angle (pu) 
       _iq OldEstimatedTheta;   // History: Electrical angle at previous step (pu)
       _iq EstimatedSpeed;      // Output: Estimated speed in per-unit  (pu)
       Uint32 BaseRpm;     		// Parameter: Base speed in rpm (Q0) - independently with global Q
       _iq21 K1;       			// Parameter: Constant for differentiator (Q21) - independently with global Q
       _iq K2;     				// Parameter: Constant for low-pass filter (pu)
       _iq K3;     				// Parameter: Constant for low-pass filter (pu)
       int32 EstimatedSpeedRpm; // Output : Estimated speed in rpm  (Q0) - independently with global Q
       } SPEED_ESTIMATION;  	// Data type created 

typedef SPEED_ESTIMATION *SPEED_ESTIMATION_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_ESTIMATION object.
-----------------------------------------------------------------------------*/                     
#define SPEED_ESTIMATION_DEFAULTS   { 0, \
                                	  0, \
                                	  0, \
                                      0, \
                                      0, \
                                      0, \
                                      0, \
                                      0, \
                                    }

#define SE_DIFF_MAX_LIMIT  	_IQ(0.80)
#define SE_DIFF_MIN_LIMIT  	_IQ(0.20)
/*------------------------------------------------------------------------------
 SPEED_EST Macro Definition
------------------------------------------------------------------------------*/


_iq Temp1;

#define SE_MACRO(v)\
if ((v.EstimatedTheta < SE_DIFF_MAX_LIMIT)&(v.EstimatedTheta > SE_DIFF_MIN_LIMIT))	\
	Temp1 = _IQmpy(v.K1,(v.EstimatedTheta - v.OldEstimatedTheta));					\
/*  Q21 = Q21*(GLOBAL_Q-GLOBAL_Q) */												\
else Temp1 = _IQtoIQ21(v.EstimatedSpeed);											\
																					\
/* Low-pass filter */																\
/* Q21 = GLOBAL_Q*Q21 + GLOBAL_Q*Q21 */												\
	Temp1 = _IQmpy(v.K2,_IQtoIQ21(v.EstimatedSpeed))+_IQmpy(v.K3,Temp1);			\
																					\
/* Saturate the output */															\
	Temp1=_IQsat(Temp1,_IQ21(1),_IQ21(-1));											\
	v.EstimatedSpeed = _IQ21toIQ(Temp1);											\
																					\
/* Update the electrical angle */													\
	v.OldEstimatedTheta = v.EstimatedTheta;											\
																					\
/* Change motor speed from pu value to rpm value (GLOBAL_Q -> Q0)*/					\
/* Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q*/									\
	v.EstimatedSpeedRpm = _IQmpy(v.BaseRpm,v.EstimatedSpeed); 
#endif // __SPEED_EST_H__
