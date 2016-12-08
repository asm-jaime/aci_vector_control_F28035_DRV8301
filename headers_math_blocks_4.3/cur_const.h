/* =================================================================================
File name:       CUR_CONST.H   
===================================================================================*/
#ifndef __CUR_CONST_H__
#define __CUR_CONST_H__

typedef struct 	{ float32  Rr;			// Input: Rotor resistance (ohm)	      			      
				  float32  Lr;			// Input: Rotor inductance (H)					  
				  float32  fb;          // Input: Base electrical frequency (Hz)
				  float32  Ts;			// Input: Sampling period (sec) 
			      float32  Kr;			// Output: constant using in magnetizing current calculation
			      float32  Kt;			// Output: constant using in slip calculation 
			      float32  K;	    	// Output: constant using in rotor flux angle calculation
			      float32  Tr;			// Variable: Rotor time constant (sec)
				} CURMOD_CONST;
																																																																																																																																																																																																								

/*-----------------------------------------------------------------------------
Default initalizer for the CURMOD_CONST object.
-----------------------------------------------------------------------------*/                     
#define CURMOD_CONST_DEFAULTS { 0,0,0,0, \
                                0,0,0,0  \
                               }

/*------------------------------------------------------------------------------
 CUR_CONST Macro Definition
------------------------------------------------------------------------------*/

#define PI 3.14159265358979


#define CUR_CONST_MACRO(v)		\
	v.Tr = v.Lr/v.Rr;			\
   								\
    v.Kr = v.Ts/v.Tr;			\
	v.Kt = 1/(v.Tr*2*PI*v.fb);	\
	v.K = v.Ts*v.fb;

#endif



