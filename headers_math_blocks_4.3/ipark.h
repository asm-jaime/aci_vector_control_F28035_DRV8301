/* =================================================================================
File name:       IPARK.H   
===================================================================================*/

#ifndef __IPARK_H__
#define __IPARK_H__

typedef struct {  _iq  Alpha;  		// Output: stationary d-axis stator variable
				  _iq  Beta;		// Output: stationary q-axis stator variable
				  _iq  Angle;		// Input: rotating angle (pu)
				  _iq  Ds;			// Input: rotating d-axis stator variable
				  _iq  Qs;			// Input: rotating q-axis stator variable
				  _iq  Sine;		// Input: Sine term
				  _iq  Cosine;		// Input: Cosine term
		 	    } IPARK;	            

/*-----------------------------------------------------------------------------
Default initalizer for the IPARK object.
-----------------------------------------------------------------------------*/                     
#define IPARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
						  0, \
                          0, \
              		   }

/*------------------------------------------------------------------------------
	Inverse PARK Transformation Macro Definition
------------------------------------------------------------------------------*/


#define IPARK_MACRO(v)										\
															\
v.Alpha = _IQmpy(v.Ds,v.Cosine) - _IQmpy(v.Qs,v.Sine);		\
v.Beta  = _IQmpy(v.Qs,v.Cosine) + _IQmpy(v.Ds,v.Sine);

#endif // __IPARK_H__

