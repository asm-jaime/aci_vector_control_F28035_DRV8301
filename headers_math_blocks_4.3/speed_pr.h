/* =================================================================================
File name:        SPEED_PR.H  
===================================================================================*/


#ifndef __SPEED_PR_H__
#define __SPEED_PR_H__

typedef struct {
       Uint32 NewTimeStamp;  	// Variable : New 'Timestamp' corresponding to a capture event (Q0) - independently with global Q 
       Uint32 OldTimeStamp;  	// Variable : Old 'Timestamp' corresponding to a capture event (Q0) - independently with global Q 
       Uint32 TimeStamp; 	   	// Input : Current 'Timestamp' corresponding to a capture event (Q0) - independently with global Q 
       Uint32 SpeedScaler;    	// Parameter :  Scaler converting 1/N cycles to a GLOBAL_Q speed (Q0) - independently with global Q
       int32 EventPeriod;    	// Input/Variable :  Event Period (Q0) - independently with global Q
       int16 InputSelect;       // Input : Input selection between TimeStamp (InputSelect=0) and EventPeriod (InputSelect=1)
       _iq Speed;             	// Output :  speed in per-unit
       Uint32 BaseRpm;         	// Parameter : Scaler converting GLOBAL_Q speed to rpm (Q0) speed - independently with global Q
       int32 SpeedRpm;        	// Output : speed in r.p.m. (Q0) - independently with global Q
       } SPEED_MEAS_CAP;       	// Data type created


/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_MEAS_CAP object.
-----------------------------------------------------------------------------*/                     

#define SPEED_MEAS_CAP_DEFAULTS   { 0, \
                                    0, \
                                    0, \
                                   260, \
                                    0, \
                                    0, \
                                    0, \
                                   1800, \
                                    0, \
                                  }

/*------------------------------------------------------------------------------
	SPEED_PR Macro Definition
------------------------------------------------------------------------------*/

#define SPEED_PR_MACRO(v)										\
   if (v.InputSelect == 0)										\
   {															\
     v.OldTimeStamp = v.NewTimeStamp;							\
     v.NewTimeStamp = v.TimeStamp;								\
     v.EventPeriod = v.NewTimeStamp - v.OldTimeStamp;			\
																\
      	if (v.EventPeriod < 0)									\
  	    	v.EventPeriod += 32767;   /* 0x7FFF = 32767*/		\
    }															\
																\
     v.Speed = _IQdiv(v.SpeedScaler,v.EventPeriod);				\
      															\
/* Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q*/				\
   v.SpeedRpm = _IQmpy(v.BaseRpm,v.Speed);						\

#endif // __SPEED_PR_H__
