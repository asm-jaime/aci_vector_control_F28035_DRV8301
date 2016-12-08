/* =================================================================================
File name:        SPEED_FR.H  
===================================================================================*/


#ifndef __SPEED_FR_H__
#define __SPEED_FR_H__

typedef struct {
       _iq ElecTheta;  		// Input: Electrical angle (pu) 
       Uint32 DirectionQep; // Variable: Direction of rotation (Q0) - independently with global Q
       _iq OldElecTheta;   	// History: Electrical angle at previous step (pu)
       _iq Speed;       	// Output: Speed in per-unit  (pu)
       Uint32 BaseRpm;      // Parameter: Base speed in rpm (Q0) - independently with global Q
       _iq21 K1;         	// Parameter: Constant for differentiator (Q21) - independently with global Q
       _iq K2;         		// Parameter: Constant for low-pass filter (pu)
       _iq K3;         		// Parameter: Constant for low-pass filter (pu)
       int32 SpeedRpm;      // Output : Speed in rpm  (Q0) - independently with global Q
       _iq Tmp;				//Variable: Temp variable
       } SPEED_MEAS_QEP;   	// Data type created

/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_MEAS_QEP object.
-----------------------------------------------------------------------------*/                     
#define SPEED_MEAS_QEP_DEFAULTS   { 0, \
                                    1, \
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
 SPEED_FR Macro Definition
------------------------------------------------------------------------------*/


#define SPEED_FR_MACRO(v)											\
/* Differentiator*/													\
/* Synchronous speed computation   */								\
   v.Tmp = v.ElecTheta - v.OldElecTheta;		                    \
   if (v.Tmp < -_IQ(0.5))			                                \
     v.Tmp = v.Tmp + _IQ(1.0);                                      \
   else if (v.Tmp > _IQ(0.5))			                            \
     v.Tmp = v.Tmp - _IQ(1.0);                                      \
   v.Tmp = _IQmpy(v.K1,v.Tmp);		                                \
/* Low-pass filter*/												\
/* Q21 = GLOBAL_Q*Q21 + GLOBAL_Q*Q21*/								\
   	v.Tmp = _IQmpy(v.K2,_IQtoIQ21(v.Speed))+_IQmpy(v.K3,v.Tmp);		\
/* Saturate the output */											\
	v.Tmp=_IQsat(v.Tmp,_IQ21(1),_IQ21(-1));							\
	v.Speed = _IQ21toIQ(v.Tmp);										\
/* Update the electrical angle */									\
    v.OldElecTheta = v.ElecTheta;									\
/* Change motor speed from pu value to rpm value (GLOBAL_Q -> Q0)*/	\
/* Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q*/					\
    v.SpeedRpm = _IQmpy(v.BaseRpm,v.Speed);

#endif // __SPEED_FR_H__
