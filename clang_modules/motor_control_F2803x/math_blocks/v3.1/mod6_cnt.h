/* =================================================================================
File name:        MOD6_CNT.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
macro definitions for the MOD6CNT module.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 03-01-2010	Version 1.0                                             
------------------------------------------------------------------------------*/
#ifndef __MOD6_CNT_H__
#define __MOD6_CNT_H__

typedef struct { Uint32  TrigInput;   	// Input: Modulo 6 counter trigger input - Q0 (0x00000000 or 0x00007FFF)
				 Uint32  Counter;	    // Output: Modulo 6 counter output - Q0 (0,1,2,3,4,5)			
		  	  	 
				 } MOD6CNT;	            

typedef MOD6CNT *MOD6CNT_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the MOD6CNT object.
-----------------------------------------------------------------------------*/                     
#define MOD6CNT_DEFAULTS { 0,0 }

/*------------------------------------------------------------------------------
	MOD6_CNT Macro Definition
------------------------------------------------------------------------------*/


#define MOD6CNT_MACRO(v)												\
																		\
 if (v.TrigInput > 0)													\
   {																	\
     if (v.Counter == 5)    /* Reset the counter when it is 5 */		\
       v.Counter = 0;													\
     else																\
       v.Counter++;         /* Otherwise, increment by 1 */				\
   }																	

#endif // __MOD_6CNT_H__ 
