/* =================================================================================
File name:       CLARKE.H  
===================================================================================*/


#ifndef __CLARKE_H__
#define __CLARKE_H__

typedef struct {  _iq  As;  		// Input: phase-a stator variable
				  _iq  Bs;			// Input: phase-b stator variable
				  _iq  Cs;			// Input: phase-c stator variable  
				  _iq  Alpha;		// Output: stationary d-axis stator variable 
				  _iq  Beta;		// Output: stationary q-axis stator variable
		 	 	} CLARKE;	            

/*-----------------------------------------------------------------------------
	Default initalizer for the CLARKE object.
-----------------------------------------------------------------------------*/                     
#define CLARKE_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			} 

/*------------------------------------------------------------------------------
	CLARKE Transformation Macro Definition
------------------------------------------------------------------------------*/

//  1/sqrt(3) = 0.57735026918963
#define  ONEbySQRT3   0.57735026918963    /* 1/sqrt(3) */
	

// Clarke transform macro (with 2 currents)
//==========================================
#define CLARKE_MACRO(v)										\
v.Alpha = v.As;												\
v.Beta = _IQmpy((v.As +_IQmpy2(v.Bs)),_IQ(ONEbySQRT3));


// Clarke transform macro (with 3 currents)
//==========================================
#define CLARKE1_MACRO(v)									\
v.Alpha = v.As;											    \
v.Beta  = _IQmpy((v.Bs - v.Cs),_IQ(ONEbySQRT3));

#endif // __CLARKE_H__

