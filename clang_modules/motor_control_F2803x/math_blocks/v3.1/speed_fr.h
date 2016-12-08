/* =================================================================================
File name:        SPEED_FR.H  (IQ version)                    
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
    Header file containing the data types, constants for the rotor angle based
    speed measurement function. Also contains the macro  definitions for the
    for SPEED_FR.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2009	Version 1.0                                                 
------------------------------------------------------------------------------*/
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
       } SPEED_MEAS_QEP;   	// Data type created

typedef SPEED_MEAS_QEP *SPEED_MEAS_QEP_handle;
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
                               	  }	

/*------------------------------------------------------------------------------
 SPEED_FR Macro Definition
------------------------------------------------------------------------------*/


_iq Tmp_fr;

#define SPEED_FR_MACRO(v)											\
/* Differentiator*/													\
/* Synchronous speed computation   */								\
   if ((v.ElecTheta < _IQ(0.9))&(v.ElecTheta > _IQ(0.1)))			\
/* Q21 = Q21*(GLOBAL_Q-GLOBAL_Q)*/									\
		Tmp_fr = _IQmpy(v.K1,(v.ElecTheta - v.OldElecTheta));		\
   else Tmp_fr = _IQtoIQ21(v.Speed);								\
/* Low-pass filter*/												\
/* Q21 = GLOBAL_Q*Q21 + GLOBAL_Q*Q21*/								\
   	Tmp_fr = _IQmpy(v.K2,_IQtoIQ21(v.Speed))+_IQmpy(v.K3,Tmp_fr);	\
/* Saturate the output */											\
	Tmp_fr=_IQsat(Tmp_fr,_IQ21(1),_IQ21(-1));						\
	v.Speed = _IQ21toIQ(Tmp_fr);									\
/* Update the electrical angle */									\
    v.OldElecTheta = v.ElecTheta;									\
/* Change motor speed from pu value to rpm value (GLOBAL_Q -> Q0)*/	\
/* Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q*/					\
    v.SpeedRpm = _IQmpy(v.BaseRpm,v.Speed);

#endif // __SPEED_FR_H__
