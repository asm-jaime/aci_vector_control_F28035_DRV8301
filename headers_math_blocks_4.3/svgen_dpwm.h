/* =================================================================================
File name:       SVGENDPWM.H  
===================================================================================*/


#ifndef __SVGENDPWM_H__
#define __SVGENDPWM_H__

typedef struct 	{ _iq  Ualpha; 			// Input: reference alpha-axis phase voltage 
				  _iq  Ubeta;			// Input: reference beta-axis phase voltage 
				  _iq  Ta;				// Output: reference phase-a switching function		
				  _iq  Tb;				// Output: reference phase-b switching function 
				  _iq  Tc;				// Output: reference phase-c switching function
				  _iq  tmp1;			// Variable: temp variable
				  _iq  tmp2;			// Variable: temp variable
				  _iq  tmp3;			// Variable: temp variable
				  Uint16 VecSector;		// Space vector sector
				} SVGENDPWM;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				

/*-----------------------------------------------------------------------------
Default initalizer for the SVGENDPWM object.
-----------------------------------------------------------------------------*/                     
#define SVGENDPWM_DEFAULTS { 0,0,0,0,0 }                       

/*------------------------------------------------------------------------------
Space Vector  Generator for Discontinuous PWM (SVGENDPWM) Macro Definition
------------------------------------------------------------------------------*/


#define SVGENDPWM_MACRO(v)														\
																				\
	v.tmp1= v.Ubeta;															\
	v.tmp2= _IQdiv2(v.Ubeta) + (_IQmpy(_IQ(0.866),v.Ualpha));					\
    v.tmp3= v.tmp2 - v.tmp1;													\
																				\
	v.VecSector=3;																\
	v.VecSector=(v.tmp2> 0)?( v.VecSector-1):v.VecSector;						\
	v.VecSector=(v.tmp3> 0)?( v.VecSector-1):v.VecSector;						\
	v.VecSector=(v.tmp1< 0)?(7-v.VecSector) :v.VecSector;						\
																				\
	if     (v.VecSector==1 || v.VecSector==6)									\
		{																			\
			v.Ta= 0; 																\
			v.Tb= v.tmp3; 															\
			v.Tc= v.tmp2 ;															\
		}																			\
	else if(v.VecSector==2 || v.VecSector==3)									\
		{																			\
			v.Ta= -v.tmp3; 															\
			v.Tb= 0; 																\
			v.Tc= v.tmp1;															\
		}																			\
	else 																		\
		{																			\
			v.Ta= -v.tmp2; 															\
			v.Tb= -v.tmp1; 															\
			v.Tc= 0;																\
		}																			\
																				\
	v.Ta= _IQmpy2(v.Ta)-_IQ(1.0);												\
	v.Tb= _IQmpy2(v.Tb)-_IQ(1.0);												\
	v.Tc= _IQmpy2(v.Tc)-_IQ(1.0);												\
	
//  v.Tx is converted from (0,1) range to (-1,1) for PWM macro   
	
#endif // __SVGENDPWM_H__
