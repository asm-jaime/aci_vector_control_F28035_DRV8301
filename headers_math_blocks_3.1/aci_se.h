/* =================================================================================
File name:       ACI_SE.H   (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro definition for the ACISE.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 5-15-2010	Version 1.1                                                  
------------------------------------------------------------------------------ */
#ifndef __ACI_SE_H__
#define __ACI_SE_H__

typedef struct {  _iq  IQsS;  			// Input: Stationary q-axis stator current  
				  _iq  PsiDrS;  		// Input: Stationary d-axis rotor flux  
				  _iq  IDsS;			// Input: Stationary d-axis stator current  
				  _iq  PsiQrS;			// Input: Stationary q-axis rotor flux  		
		 	 	  _iq  K1;				// Parameter: Constant using in speed computation  
                  _iq  SquaredPsi; 		// Variable: Squared rotor flux    
    			  _iq  ThetaFlux;  		// Input: Rotor flux angle      		  
		 	 	  _iq21  K2;			// Parameter: Constant using in differentiator (Q21) - independently with global Q 
    			  _iq  OldThetaFlux; 	// Variable: Previous rotor flux angle      		  
		 	 	  _iq  K3;				// Parameter: Constant using in low-pass filter   
		 	 	  _iq21  WPsi;			// Variable: Synchronous rotor flux speed (Q21) - independently with global Q 
		 	 	  _iq  K4;				// Parameter: Constant using in low-pass filter  
		 	 	  _iq  WrHat;			// Output: Estimated speed in per unit  
				  Uint32  BaseRpm; 		// Parameter: Base rpm speed (Q0) - independently with global Q  		 	 	  
		 	 	  int32  WrHatRpm;		// Output: Estimated speed in rpm (Q0) - independently with global Q   
				 } ACISE;	            
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																			
typedef ACISE *ACISE_handle;

/*-----------------------------------------------------------------------------
Default initalizer for the ACISE object.
----------------------------------------------------------------------------- */                    
#define ACISE_DEFAULTS {  0, 			\
                          0, 			\
                          0, 			\
                          0, 			\
                          _IQ(0.1), 	\
                          0, 			\
                          0, 			\
                          _IQ21(0.1), 	\
                          0, 			\
                          _IQ(0.1), 	\
                          0, 			\
                          _IQ(0.1), 	\
                          0, 			\
                          3600, 		\
              			  0, 			\
              			}

#define DIFF_MAX_LIMIT  	_IQ(0.80)
#define DIFF_MIN_LIMIT  	_IQ(0.20)

/*------------------------------------------------------------------------------
	ACI Speed Estimator MACRO Definition 
------------------------------------------------------------------------------ */


_iq WSlip, WSyn;

#define ACISE_MACRO(v)															\
																				\
/*  Slip computation */															\
	v.SquaredPsi = _IQmpy(v.PsiDrS,v.PsiDrS)+_IQmpy(v.PsiQrS,v.PsiQrS);			\
																				\
	WSlip = _IQmpy(v.K1,(_IQmpy(v.PsiDrS,v.IQsS) - _IQmpy(v.PsiQrS,v.IDsS)));	\
	WSlip = _IQdiv(WSlip,v.SquaredPsi);											\
																				\
/*	Synchronous speed computation	*/											\
	if ((v.ThetaFlux < DIFF_MAX_LIMIT)&(v.ThetaFlux > DIFF_MIN_LIMIT))			\
/* 	Q21 = Q21*(GLOBAL_Q-GLOBAL_Q)*/												\
		  WSyn = _IQmpy(v.K2,(v.ThetaFlux - v.OldThetaFlux));					\
	else  WSyn = v.WPsi;														\
																				\
/* low-pass filter, Q21 = GLOBAL_Q*Q21 + GLOBAL_Q*Q21	*/						\
	v.WPsi = _IQmpy(v.K3,v.WPsi) + _IQmpy(v.K4,WSyn);							\
																				\
/* Q21 = Q21 - GLOBAL_Q */														\
	v.OldThetaFlux = v.ThetaFlux;												\
	v.WrHat = v.WPsi - _IQtoIQ21(WSlip);										\
																				\
/* Limit the estimated speed between -1 and 1 per-unit */						\
	v.WrHat=_IQsat(v.WrHat,_IQ21(1),_IQ21(-1));									\
	v.WrHat = _IQ21toIQ(v.WrHat);												\
																				\
/* Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q */								\
	v.WrHatRpm = _IQmpy(v.BaseRpm,v.WrHat);	

#endif // __ACI_SE_H__
