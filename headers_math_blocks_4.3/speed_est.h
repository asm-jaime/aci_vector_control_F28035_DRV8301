/* =================================================================================
File name:        SPEED_EST.H  
===================================================================================*/


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
       _iq Temp;				// Variable : Temp variable
       } SPEED_ESTIMATION;  	// Data type created 


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
                                      0, \
                                    }

/*------------------------------------------------------------------------------
 SPEED_EST Macro Definition
------------------------------------------------------------------------------*/


#define SE_MACRO(v)																    \
/* Synchronous speed computation   */												\
    v.Temp = v.EstimatedTheta - v.OldEstimatedTheta;		                    	\
    if (v.Temp < -_IQ(0.5))			                                				\
        v.Temp = v.Temp + _IQ(1.0);                                                 \
    else if (v.Temp > _IQ(0.5))			                            				\
        v.Temp = v.Temp - _IQ(1.0);                                      			\
    v.Temp = _IQmpy(v.K1,v.Temp);		                               				\
																					\
/* Low-pass filter */																\
/* Q21 = GLOBAL_Q*Q21 + GLOBAL_Q*Q21 */												\
	v.Temp = _IQmpy(v.K2,_IQtoIQ21(v.EstimatedSpeed))+_IQmpy(v.K3,v.Temp);			\
																					\
/* Saturate the output */															\
	v.Temp=_IQsat(v.Temp,_IQ21(1),_IQ21(-1));										\
	v.EstimatedSpeed = _IQ21toIQ(v.Temp);											\
																					\
/* Update the electrical angle */													\
	v.OldEstimatedTheta = v.EstimatedTheta;											\
																					\
/* Change motor speed from pu value to rpm value (GLOBAL_Q -> Q0)*/					\
/* Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q*/									\
	v.EstimatedSpeedRpm = _IQmpy(v.BaseRpm,v.EstimatedSpeed);
#endif // __SPEED_EST_H__
