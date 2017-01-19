/* =================================================================================
File name:       CUR_MOD.H  (IQ version)                   
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type and macro definitions for the CURMOD.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2009	Version 1.0
------------------------------------------------------------------------------*/

typedef struct 	{ _iq  IDs; 		// Input: Syn. rotating d-axis current (pu) 
				  _iq  IQs;			// Input: Syn. rotating q-axis current (pu) 
			      _iq  Wr;			// Input: Rotor electrically angular velocity (pu) 	  			      
				  _iq  IMDs;		// Variable: Syn. rotating d-axis magnetizing current (pu) 
				  _iq  Theta;		// Output: Rotor flux angle (pu)
			      _iq  Kr;			// Parameter: constant using in magnetizing current calculation
			      _iq  Kt;			// Parameter: constant using in slip calculation 
			      _iq  K;			// Parameter: constant using in rotor flux angle calculation
				} CURMOD;
																																																																																																																																																																																																								
typedef CURMOD *CURMOD_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the CURMOD object.
-----------------------------------------------------------------------------*/                     
#define CURMOD_DEFAULTS { 0,0,0,0,0, \
                          0,0,0, \
                       }

/*------------------------------------------------------------------------------
 CUR_MOD Macro Definition
------------------------------------------------------------------------------*/

	_iq Wslip, We;

#define CUR_MOD_MACRO(v)							\
	v.IMDs +=  _IQmpy(v.Kr,(v.IDs - v.IMDs));		\
	Wslip = _IQdiv(_IQmpy(v.Kt,v.IQs),v.IMDs);		\
	We = v.Wr + Wslip;								\
	v.Theta +=  _IQmpy(v.K,We);						\
													\
    if (v.Theta > _IQ(1))							\
       v.Theta -=  _IQ(1);							\
    else if (v.Theta < _IQ(0))						\
       v.Theta += _IQ(1);


