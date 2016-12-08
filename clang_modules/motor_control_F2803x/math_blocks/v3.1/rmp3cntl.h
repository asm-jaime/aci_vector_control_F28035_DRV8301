/* =================================================================================
File name:        RMP3CNTL.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
macro definitions for the RMP3 module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 03-01-2010	Version 1.0                                                  
------------------------------------------------------------------------------*/
#ifndef __RMP3_CNTL_H__
#define __RMP3_CNTL_H__

typedef struct { Uint32 DesiredInput; 		// Input: Desired ramp input (Q0) - independently with global Q
				 Uint32 Ramp3Delay;			// Parameter: Ramp3 delay expressed in no of sampling period (Q0) - independently with global Q		
		 	 	 Uint32 Ramp3DelayCount;	// Variable: Counter for rmp3 delay (Q0) - independently with global Q
				 int32 Out;					// Output: Ramp3 output (Q0) - independently with global Q
				 int32 Ramp3Min;	    	// Parameter: Minimum ramp output (Q0) - independently with global Q
				 Uint32 Ramp3DoneFlag;		// Output: Flag output (Q0) - independently with global Q
		  	  	 
				 } RMP3;	            

typedef RMP3 *RMP3_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the RMP3 object.
-----------------------------------------------------------------------------*/                     
#define RMP3_DEFAULTS { 0, \
                        0, \
                        0, \
                        0, \
                        0x00000050, \
                       	0, \
             		  }


/*------------------------------------------------------------------------------
 RMP3CNTL Macro Definition
------------------------------------------------------------------------------*/

#define RC3_MACRO(v)								\
   if (v.Out == v.DesiredInput)						\
      v.Ramp3DoneFlag = 0x7FFFFFFF;					\
   else												\
    {												\
													\
      v.Ramp3DelayCount++;							\
													\
      if (v.Ramp3DelayCount >= v.Ramp3Delay)		\
      {												\
        v.Out--;									\
													\
        if (v.Out < v.Ramp3Min)						\
           v.Out = v.Ramp3Min;						\
													\
        v.Ramp3DelayCount = 0;						\
      }                          					\
 													\
    }

#endif // __RMP3_CNTL_H__

