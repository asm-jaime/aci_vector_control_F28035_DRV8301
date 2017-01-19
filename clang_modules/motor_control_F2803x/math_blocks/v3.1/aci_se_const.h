/* =================================================================================
File name:       ACI_SE_CONST.H                     
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro definition for the ACISE_CONST.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 5-15-2009	Version 1.1
------------------------------------------------------------------------------*/

typedef struct 	{ float32  Rr;				// Input: Rotor resistance (ohm) 
				  float32  Lr;				// Input: Rotor inductance (H) 			
				  float32  fb;              // Input: Base electrical frequency (Hz)
                  float32  fc;              // Input: Cut-off frequency of lowpass filter (Hz)
				  float32  Ts;				// Input: Sampling period in sec 
			      float32  K1;				// Output: constant using in rotor flux calculation 
			      float32  K2;				// Output: constant using in rotor flux calculation 
			      float32  K3;				// Output: constant using in rotor flux calculation 
			      float32  K4;				// Output: constant using in stator current calculation 
				} ACISE_CONST;
																																																																																																																																																																																																								
typedef ACISE_CONST *ACISE_CONST_handle;

/*-----------------------------------------------------------------------------
	Default initalizer for the ACISE_CONST object.
-----------------------------------------------------------------------------*/                     
#define ACISE_CONST_DEFAULTS {0,0,0,	\
                             0,0,0, 	\
 		          	         0,0,0, 	\
                             }

/*------------------------------------------------------------------------------
	ACI_SE_CONST macro definition  
------------------------------------------------------------------------------*/


#define PI 3.14159265358979  

float32 Wb, Trr, tc;

#define ACISE_CONST_MACRO(v)				\
											\
/* Rotor time constant (sec) */				\
	Trr = v.Lr/v.Rr;						\
											\
/* Lowpass filter time constant (sec) */	\
	tc = 1/(2*PI*v.fc);						\
											\
	Wb = 2*PI*v.fb;							\
	v.K1 = 1/(Wb*Trr);						\
	v.K2 = 1/(v.fb*v.Ts);					\
	v.K3 = tc/(tc+v.Ts);					\
	v.K4 = v.Ts/(tc+v.Ts); 
