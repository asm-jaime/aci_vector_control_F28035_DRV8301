/* =================================================================================
File name:       SMOPOS_CONST.H                     
===================================================================================*/
#ifndef __SMOPOS_CONST_H__
#define __SMOPOS_CONST_H__

typedef struct 	{ float32  Rs; 				// Input: Stator resistance (ohm) 
			      float32  Ls;				// Input: Stator inductance (H) 	  			      
				  float32  Ib; 				// Input: Base phase current (amp) 
				  float32  Vb;				// Input: Base phase voltage (volt) 
				  float32  Ts;				// Input: Sampling period in sec 
			      float32  Fsmopos;			// Output: constant using in observed current calculation 
			      float32  Gsmopos;			// Output: constant using in observed current calculation 
				  
				} SMOPOS_CONST;
																																																																																																																																																																																																								
/*-----------------------------------------------------------------------------
Default initalizer for the SMOPOS_CONST object.
-----------------------------------------------------------------------------*/                     
#define SMOPOS_CONST_DEFAULTS {0,0,0,0,0,0,0, \
                            }

/*------------------------------------------------------------------------------
Prototypes for the functions in SMOPOS_CONST.C
------------------------------------------------------------------------------*/

#define SMO_CONST_MACRO(v)								\
														\
	v.Fsmopos = exp((-v.Rs/v.Ls)*(v.Ts));				\
	v.Gsmopos = (v.Vb/v.Ib)*(1/v.Rs)*(1-v.Fsmopos);

#endif





