/* =================================================================================
File name:       ACI_SE_CONST.H                     
===================================================================================*/
#ifndef __ACI_SE_CONST_H__
#define __ACI_SE_CONST_H__

typedef struct 	{ float32  Rr;				// Input: Rotor resistance (ohm) 
				  float32  Lr;				// Input: Rotor inductance (H) 	
				  float32  Tr;				// Variable: Rotor time constant 			
				  float32  fb;              // Input: Base electrical frequency (Hz)
				  float32  Wb;              // Variable: Base angular speed (rad/s)
                  float32  fc;              // Input: Cut-off frequency of lowpass filter (Hz)
                  float32  Tc;              // Variable: Time constant (sec)
				  float32  Ts;				// Input: Sampling period in sec 
			      float32  K1;				// Output: constant using in rotor flux calculation 
			      float32  K2;				// Output: constant using in rotor flux calculation 
			      float32  K3;				// Output: constant using in rotor flux calculation 
			      float32  K4;				// Output: constant using in stator current calculation 
				} ACISE_CONST;

/*-----------------------------------------------------------------------------
	Default initalizer for the ACISE_CONST object.
-----------------------------------------------------------------------------*/                     
#define ACISE_CONST_DEFAULTS {0,0,0,0,	\
                              0,0,0,0, 	\
 		          	          0,0,0,0, 	\
                             }

/*------------------------------------------------------------------------------
	ACI_SE_CONST macro definition  
------------------------------------------------------------------------------*/


#define PI 3.14159265358979  

#define ACISE_CONST_MACRO(v)				\
											\
/* Rotor time constant (sec) */				\
	v.Tr = v.Lr/v.Rr;						\
											\
/* Lowpass filter time constant (sec) */	\
	v.Tc = 1/(2*PI*v.fc);					\
											\
	v.Wb = 2*PI*v.fb;						\
	v.K1 = 1/(v.Wb*v.Tr);					\
	v.K2 = 1/(v.fb*v.Ts);					\
	v.K3 = v.Tc/(v.Tc+v.Ts);				\
	v.K4 = v.Ts/(v.Tc+v.Ts); 

	
#endif

