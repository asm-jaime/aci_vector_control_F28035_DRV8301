/* =================================================================================
File name:       ACI_FE_CONST.H                     
====================================================================================*/
#ifndef __ACI_FE_CONST_H__
#define __ACI_FE_CONST_H__

typedef struct 	{ float32  Rs; 				// Input: Stator resistance (ohm) 
				  float32  Rr;				// Input: Rotor resistance (ohm) 
			      float32  Ls;				// Input: Stator inductance (H) 	  			      
				  float32  Lr;				// Input: Rotor inductance (H) 			
				  float32  Lm;				// Input: Magnetizing inductance (H)
				  float32  Ib; 				// Input: Base phase current (amp) 
				  float32  Vb;				// Input: Base phase voltage (volt) 
				  float32  Ts;				// Input: Sampling period in sec 
				  float32  Tr;				// Parameter: Rotor time constant 
			      float32  K1;				// Output: constant using in rotor flux calculation  
			      float32  K2;				// Output: constant using in rotor flux calculation  
			      float32  K3;				// Output: constant using in rotor flux calculation 
			      float32  K4;				// Output: constant using in stator current calculation  
			      float32  K5;				// Output: constant using in stator current calculation  
			      float32  K6;				// Output: constant using in stator current calculation  
			      float32  K7;				// Output: constant using in stator current calculation  
			      float32  K8;				// Output: constant using in torque calculation  
				} ACIFE_CONST;

/*-----------------------------------------------------------------------------
	Default initalizer for the ACIFE_CONST object.
-----------------------------------------------------------------------------*/                     
#define ACIFE_CONST_DEFAULTS {0,0,0,0, 		\
                              0,0,0,0,		\
                              0,0,0,0,		\
 		          	          0,0,0,0,	 	\
                             }

/*------------------------------------------------------------------------------
	ACIFE_CONST MACRO Definition
------------------------------------------------------------------------------*/


#define ACIFE_CONST_MACRO(v)					\
												\
/* Rotor time constant (sec)*/					\
   v.Tr = v.Lr/v.Rr;							\
   												\
   v.K1 = v.Tr/(v.Tr+v.Ts);						\
   v.K2 = v.Ts/(v.Tr+v.Ts);						\
   v.K3 = v.Lm/v.Lr;							\
   v.K4 = (v.Ls*v.Lr-v.Lm*v.Lm)/(v.Lr*v.Lm);	\
   v.K5 = v.Ib*v.Rs/v.Vb;						\
   v.K6 = v.Vb*v.Ts/(v.Lm*v.Ib);				\
   v.K7 = v.Lr/v.Lm;							\
   v.K8 = (v.Ls*v.Lr-v.Lm*v.Lm)/(v.Lm*v.Lm);

#endif






