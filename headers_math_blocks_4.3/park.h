/* =================================================================================
File name:       PARK.H 
===================================================================================*/

#ifndef __PARK_H__
#define __PARK_H__

typedef struct {  _iq  Alpha;  		// Input: stationary d-axis stator variable 
				  _iq  Beta;	 	// Input: stationary q-axis stator variable 
				  _iq  Angle;		// Input: rotating angle (pu) 
				  _iq  Ds;			// Output: rotating d-axis stator variable 
				  _iq  Qs;			// Output: rotating q-axis stator variable
				  _iq  Sine;
				  _iq  Cosine; 	 
		 	 	} PARK;	            

/*-----------------------------------------------------------------------------
Default initalizer for the PARK object.
-----------------------------------------------------------------------------*/                     
#define PARK_DEFAULTS {   0, \
                          0, \
                          0, \
                          0, \
                          0, \
						  0, \
                          0, \
              			  }

/*------------------------------------------------------------------------------
	PARK Transformation Macro Definition
------------------------------------------------------------------------------*/


#define PARK_MACRO(v)											\
																\
	v.Ds = _IQmpy(v.Alpha,v.Cosine) + _IQmpy(v.Beta,v.Sine);	\
    v.Qs = _IQmpy(v.Beta,v.Cosine) - _IQmpy(v.Alpha,v.Sine);

#endif // __PARK_H__
