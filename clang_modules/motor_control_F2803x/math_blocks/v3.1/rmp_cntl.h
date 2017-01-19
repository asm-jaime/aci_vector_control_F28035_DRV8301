/* =================================================================================
File name:        RMP_CNTL.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro  definitions for the RMPCNTL module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-15-2009	Version 1.0                                                 
------------------------------------------------------------------------------*/
#ifndef __RMP_CNTL_H__
#define __RMP_CNTL_H__

typedef struct { _iq    TargetValue; 	// Input: Target input (pu)
				 Uint32 RampDelayMax;	// Parameter: Maximum delay rate (Q0) - independently with global Q			
		 	 	 _iq    RampLowLimit;	// Parameter: Minimum limit (pu)				  
				 _iq    RampHighLimit;	// Parameter: Maximum limit (pu)
				 Uint32 RampDelayCount; // Variable: Incremental delay (Q0) - independently with global Q	
				 _iq    SetpointValue;	// Output: Target output (pu)				 
				 Uint32 EqualFlag;		// Output: Flag output (Q0) - independently with global Q
		  	   } RMPCNTL;	            

typedef RMPCNTL *RMPCNTL_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the RMPCNTL object.
-----------------------------------------------------------------------------*/                     
#define RMPCNTL_DEFAULTS { 0, 		 \
                           5,		 \
                          	_IQ(-1), \
                          	_IQ(1),  \
                          	0,       \
                          	0,       \
                          	0,       \
                   		  }

/*------------------------------------------------------------------------------
 	RAMP Controller Macro Definition
------------------------------------------------------------------------------*/

_iq rc_tmp;

#define RC_MACRO(v)										\
	rc_tmp = v.TargetValue - v.SetpointValue;			\
/*  0.0000305 is resolution of Q15 */					\
if (_IQabs(rc_tmp) > _IQ(0.0000305))					\
{														\
	v.RampDelayCount += 1;								\
		if (v.RampDelayCount >= v.RampDelayMax)			\
		{												\
			if (v.TargetValue >= v.SetpointValue)		\
			{											\
				v.SetpointValue += _IQ(0.0000305);		\
				if (v.SetpointValue > v.RampHighLimit)	\
					v.SetpointValue = v.RampHighLimit;	\
				v.RampDelayCount = 0;					\
			}											\
			else										\
			{											\
			v.SetpointValue -= _IQ(0.0000305);			\
			if (v.SetpointValue < v.RampLowLimit)		\
				v.SetpointValue = v.RampLowLimit;		\
			v.RampDelayCount = 0;						\
			}											\
		}												\
}														\
else v.EqualFlag = 0x7FFFFFFF;

#endif // __RMP_CNTL_H__
