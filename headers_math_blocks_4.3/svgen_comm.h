/* =================================================================================
File name:       SVGEN_COMM.H  
===================================================================================*/

#ifndef __SVGEN_COMM_H__
#define __SVGEN_COMM_H__



typedef struct 	{ _iq  Ualpha; 			// Input: reference alpha-axis phase voltage 
				  _iq  Ubeta;			// Input: reference beta-axis phase voltage 
				  _iq  Ta;				// Output: reference phase-a switching function		
				  _iq  Tb;				// Output: reference phase-b switching function 
				  _iq  Tc;				// Output: reference phase-c switching function
				  _iq  Va;				// Variable: reference phase-a voltage 		
				  _iq  Vb;				// Variable: reference phase-b voltage
				  _iq  Vc;				// Variable: reference phase-c voltage
				  _iq  Vmax;			// Variable: max phase
				  _iq  Vmin;			// Variable: min phase
				  _iq  Vcomm;			// Variable: common mode voltage
				  _iq  tmp1;			// Variable: temp variable
				  _iq  tmp2;			// Variable: temp variable
				} SVGENCOMM;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																				

/*-----------------------------------------------------------------------------
Default initalizer for the SVGENCOMM object.
-----------------------------------------------------------------------------*/                     
#define SVGENCOMM_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,0,0,0 }                       

/*------------------------------------------------------------------------------
	Space Vector Generator (Common Mode) Macro Definition
------------------------------------------------------------------------------*/

#define SVGENCOMM_MACRO(v)														\
																				\
	v.tmp1=_IQdiv2(v.Ualpha); 					/*divide by 2*/					\
	v.tmp2=_IQmpy(_IQ(0.8660254),v.Ubeta);		/* 0.8660254 = sqrt(3)/2*/		\
																				\
	v.Va = v.Ualpha;							/*Inv Clarke*/					\
	v.Vb = -v.tmp1 + v.tmp2;													\
	v.Vc = -v.tmp1 - v.tmp2;													\
																				\
	if (v.Va>v.Vb) {v.Vmax=v.Va; v.Vmin=v.Vb;}	/*Find max and min phase*/		\
	else 	   	   {v.Vmax=v.Vb; v.Vmin=v.Va;}									\
	if (v.Vc>v.Vmax) v.Vmax=v.Vc;												\
	if (v.Vc<v.Vmin) v.Vmin=v.Vc;												\
																				\
	v.Vcomm = _IQdiv2(v.Vmax+v.Vmin);			/*Calculate common mode*/		\
																				\
	v.Ta = v.Va-v.Vcomm;														\
	v.Tb = v.Vb-v.Vcomm;														\
	v.Tc = v.Vc-v.Vcomm;														\
	

#endif // __SVGEN_COMM_H__
