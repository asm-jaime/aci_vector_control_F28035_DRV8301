/* =================================================================================
File name:       CUR_MOD.H  
===================================================================================*/
#ifndef __CUR_MOD_H__
#define __CUR_MOD_H__

typedef struct 	{ _iq  IDs; 		// Input: Syn. rotating d-axis current (pu) 
				  _iq  IQs;			// Input: Syn. rotating q-axis current (pu) 
			      _iq  Wr;			// Input: Rotor electrically angular velocity (pu) 	  			      
				  _iq  IMDs;		// Variable: Syn. rotating d-axis magnetizing current (pu) 
				  _iq  Theta;		// Output: Rotor flux angle (pu)
			      _iq  Kr;			// Parameter: constant using in magnetizing current calculation
			      _iq  Kt;			// Parameter: constant using in slip calculation 
			      _iq  K;			// Parameter: constant using in rotor flux angle calculation
				  _iq  Wslip;		// Variable: Slip
				  _iq  We;			// Variable: Angular freq of the stator	
				} CURMOD;
																																																																																																																																																																																																								

/*-----------------------------------------------------------------------------
Default initalizer for the CURMOD object.
-----------------------------------------------------------------------------*/                     
#define CURMOD_DEFAULTS { 0,0,0,0,0, \
                          0,0,0,0,0 \
                       }

/*------------------------------------------------------------------------------
 CUR_MOD Macro Definition
------------------------------------------------------------------------------*/


#define CUR_MOD_MACRO(v)							\
	v.IMDs +=  _IQmpy(v.Kr,(v.IDs - v.IMDs));		\
	v.Wslip = _IQdiv(_IQmpy(v.Kt,v.IQs),v.IMDs);	\
	v.We = v.Wr + v.Wslip;							\
	v.Theta +=  _IQmpy(v.K,v.We);					\
													\
    if (v.Theta > _IQ(1))							\
       v.Theta -=  _IQ(1);							\
    else if (v.Theta < _IQ(0))						\
       v.Theta += _IQ(1);

//v.Theta=(v.Theta+_IQ(1.0))&& 0x00ffffff;

#endif

