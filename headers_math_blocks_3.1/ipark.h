/* =================================================================================
File name:       IPARK.H   (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro definitions for the IPARK.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 10-15-2009	Version 1.0                                                  
------------------------------------------------------------------------------*/
#ifndef __IPARK_H__
#define __IPARK_H__

typedef struct {  _iq  Alpha;  		// Output: stationary d-axis stator variable
				  _iq  Beta;		// Output: stationary q-axis stator variable
				  _iq  Angle;		// Input: rotating angle (pu)
				  _iq  Ds;			// Input: rotating d-axis stator variable
				  _iq  Qs;			// Input: rotating q-axis stator variable
				  _iq  Sine;
				  _iq  Cosine;	
		 	 	} IPARK;	            

typedef IPARK *IPARK_handle;
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
v.Beta = _IQmpy(v.Qs,v.Cosine) + _IQmpy(v.Ds,v.Sine);

#endif // __IPARK_H__

