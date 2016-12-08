/* =================================================================================
File name:        RMP2CNTL.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
macro definitions for the RMP2 module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 03-01-2010	Version 1.0                                                 
------------------------------------------------------------------------------*/
#ifndef __RMP2_CNTL_H__
#define __RMP2_CNTL_H__

typedef struct { int16 DesiredInput; 	// Input: Desired ramp input (Q15) - independently with global Q
                 int16 Ramp2Max; 		// Parameter: Maximum limit (Q15) - independently with global Q
				 int16 Ramp2Min;		// Parameter: Minimum limit (Q15) - independently with global Q			
				 Uint32 Ramp2DelayCount; // Variable: Incremental delay (Q0) - independently with global Q	
				 Uint32 Ramp2Delay;		// Parameter: Ramp2 delay expressed in no of sampling period (Q0) - independently with global Q			
				 int16 Out;				// Output: Ramp2 output (Q15)
		  	  	
				 } RMP2;

typedef RMP2 *RMP2_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the RMP2 object.
-----------------------------------------------------------------------------*/                     
#define RMP2_DEFAULTS { 0, \
                        0x00007FFF, \
                        0x0000000F, \
                        0, \
                        50, \
                       	0, \
             		   }

/*------------------------------------------------------------------------------
	 RMP2CNTL Macro Definitions
------------------------------------------------------------------------------*/


#define RC2_MACRO(v)							\
if (v.Out != v.DesiredInput)					\
{												\
	v.Ramp2DelayCount++;						\
	if (v.Ramp2DelayCount >= v.Ramp2Delay)		\
	{											\
		v.Ramp2DelayCount = 0;					\
		if (v.Out < v.DesiredInput)				\
		{  										\
			v.Out++;							\
			if (v.Out > v.Ramp2Max)				\
				v.Out = v.Ramp2Max;				\
		}										\
		else									\
		{ 										\
			v.Out--;							\
			if (v.Out < v.Ramp2Min)				\
				v.Out = v.Ramp2Min;				\
		}										\
	}											\
}

#endif // __RMP2_CNTL_H__
