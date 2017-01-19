/* =================================================================================
File name:       CUR_CONST.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type and macro definitions for the CURMOD_CONST.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2009	Version 1.0
------------------------------------------------------------------------------*/

typedef struct 	{ float32  Rr;			// Input: Rotor resistance (ohm)	      			      
				  float32  Lr;			// Input: Rotor inductance (H)					  
				  float32  fb;          // Input: Base electrical frequency (Hz)
				  float32  Ts;			// Input: Sampling period (sec) 
			      float32  Kr;			// Output: constant using in magnetizing current calculation
			      float32  Kt;			// Output: constant using in slip calculation 
			      float32  K;	    	// Output: constant using in rotor flux angle calculation
				} CURMOD_CONST;
																																																																																																																																																																																																								
typedef CURMOD_CONST *CURMOD_CONST_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the CURMOD_CONST object.
-----------------------------------------------------------------------------*/                     
#define CURMOD_CONST_DEFAULTS { 0,0,0,0, \
                                0,0,0, \
                               }

/*------------------------------------------------------------------------------
 CUR_CONST Macro Definition
------------------------------------------------------------------------------*/

#define PI 3.14159265358979

	float32 Tr_cm;   // Rotor time constant (sec)

#define CUR_CONST_MACRO(v)		\
	Tr_cm = v.Lr/v.Rr;			\
   								\
    v.Kr = v.Ts/Tr_cm;			\
	v.Kt = 1/(Tr_cm*2*PI*v.fb);	\
	v.K = v.Ts*v.fb;





