/* =================================================================================
File name:       ACI_FE.H   (IQ version)                  
                     
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro definition for the ACIFE.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 5-15-2010	Version 1.1  
------------------------------------------------------------------------------*/
#ifndef __ACI_FE_H__
#define __ACI_FE_H__

typedef struct {  _iq  ThetaFlux;      	// Output: Rotor flux angle 
	              _iq  IQsS;		    // Input: Stationary q-axis stator current  
	              _iq  IDsS;         	// Input: Stationary d-axis stator current  
	              _iq  K1;           	// Parameter: Constant using in current model 
	              _iq  FluxDrE;        	// Variable: Rotating d-axis rotor flux (current model)
	              _iq  K2;           	// Parameter: Constant using in current model 
	              _iq  FluxQrS;        	// Variable: Stationary q-axis rotor flux (current model) 
	              _iq  FluxDrS;        	// Variable: Stationary d-axis rotor flux (current model) 
	              _iq  K3;           	// Parameter: Constant using in stator flux computation 
	              _iq  K4;           	// Parameter: Constant using in stator flux computation 
	              _iq  FluxDsS;        	// Variable: Stationary d-axis stator flux (current model) 
	              _iq  FluxQsS;        	// Variable: Stationary q-axis stator flux (current model) 
				  _iq  PsiDsS;			// Variable: Stationary d-axis stator flux (voltage model) 
	              _iq  Kp;           	// Parameter: PI proportionnal gain 
	              _iq  UiDsS;           // Variable: Stationary d-axis integral term 
	              _iq  UCompDsS;        // Variable: Stationary d-axis compensated voltage 
	              _iq  Ki;           	// Parameter: PI integral gain 
	              _iq  PsiQsS;       	// Variable: Stationary q-axis stator flux (voltage model) 
	              _iq  UiQsS;           // Variable: Stationary q-axis integral term  
	              _iq  UCompQsS;        // Variable: Stationary q-axis compensated voltage 
	              _iq  EmfDsS;          // Variable: Stationary d-axis back emf 
	              _iq  UDsS;         	// Input: Stationary d-axis stator voltage 
	              _iq  K5;           	// Parameter: Constant using in back emf computation 
	              _iq  K6;           	// Parameter: Constant using in back emf computation 
	              _iq  EmfQsS;          // Variable: Stationary q-axis back emf  
	              _iq  UQsS;         	// Input: Stationary q-axis stator voltage 
	              _iq  K8;           	// Parameter: Constant using in rotor flux computation 
	              _iq  K7;           	// Parameter: Constant using in rotor flux computation 
				  _iq  PsiDrS;			// Output: Stationary d-axis estimated rotor flux 
				  _iq  PsiQrS;			// Output: Stationary q-axis estimated rotor flux 
				 } ACIFE;	            

typedef ACIFE *ACIFE_handle;
/*-----------------------------------------------------------------------------
	Default initalizer for the ACIFE object.
-----------------------------------------------------------------------------*/                     
#define ACIFE_DEFAULTS {  0,    /*  ThetaFlux  */  	\
	                      0,    /*  IDsS  */     	\
	                      0,    /*  IQsS  */     	\
	                      0,    /*  K1 */       	\
	                      0,    /*  FluxDrE  */    	\
	                      0,    /*  K2  */       	\
	                      0,    /*  FluxDrS  */    	\
	                      0,    /*  FluxQrS  */    	\
	                      0,    /*  K3  */       	\
	                      0,    /*  K4  */       	\
	                      0,    /*  FluxDsS  */    	\
	                      0,    /*  FluxQsS  */    	\
	 		              0,    /*  PsiDsS  */   	\
	                      0,    /*  Kp  */       	\
	                      0,    /*  UiDsS  */    	\
	                      0,    /*  UCompDsS  */    \
	                      0,    /*  Ki  */ 			\
	                      0,    /*  PsiQsS  */   	\
 	                      0,    /*  UiQsS  */    	\
	                      0,    /*  UCompQsS  */    \
	                      0,    /*  EmfDsS  */      \
                          0,    /*  UDsS  */     	\
	                      0,    /*  K5  */       	\
	                      0,    /*  K6  */       	\
	                      0,    /*  EmfQsS  */      \
                          0,    /*  UQsS  */     	\
	                      0,    /*  K8  */       	\
	                      0,    /*  K7  */       	\
		                  0,    /*  PsiDrS  */   	\
		                  0,	/*  PsiQrS  */   	\
						}	              			 

/*------------------------------------------------------------------------------
	ACI Flux Estimator MACRO Definition 
------------------------------------------------------------------------------*/


_iq IDsE, Error, OldEmf;

#define ACIFE_MACRO(v)															\
																				\
/* Park transformation on the measured stator current*/							\
	IDsE = _IQmpy(v.IQsS,_IQsinPU(v.ThetaFlux));								\
	IDsE += _IQmpy(v.IDsS,_IQcosPU(v.ThetaFlux));								\
																				\
/* The current model section (Classical Rotor Flux Vector Control Equation)*/	\
	v.FluxDrE = _IQmpy(v.K1,v.FluxDrE) + _IQmpy(v.K2,IDsE);						\
																				\
/* Inverse park transformation on the rotor flux from the current model*/		\
	v.FluxDrS = _IQmpy(v.FluxDrE,_IQcosPU(v.ThetaFlux));						\
	v.FluxQrS = _IQmpy(v.FluxDrE,_IQsinPU(v.ThetaFlux));						\
																				\
/* Compute the stator flux based on the rotor flux from current model*/			\
	v.FluxDsS = _IQmpy(v.K3,v.FluxDrS) + _IQmpy(v.K4,v.IDsS);					\
	v.FluxQsS = _IQmpy(v.K3,v.FluxQrS) + _IQmpy(v.K4,v.IQsS);					\
																				\
/* Conventional PI controller section */										\
	Error =  v.PsiDsS - v.FluxDsS;												\
	v.UCompDsS = _IQmpy(v.Kp,Error) + v.UiDsS;									\
	v.UiDsS = _IQmpy(v.Kp,_IQmpy(v.Ki,Error)) + v.UiDsS;						\
																				\
	Error =  v.PsiQsS - v.FluxQsS;												\
	v.UCompQsS = _IQmpy(v.Kp,Error) + v.UiQsS;									\
	v.UiQsS = _IQmpy(v.Kp,_IQmpy(v.Ki,Error)) + v.UiQsS;						\
																				\
/* Compute the estimated stator flux based on the integral of back emf*/		\
	OldEmf = v.EmfDsS;															\
	v.EmfDsS = v.UDsS - v.UCompDsS - _IQmpy(v.K5,v.IDsS);						\
	v.PsiDsS = v.PsiDsS + _IQdiv2(_IQmpy(v.K6,(v.EmfDsS + OldEmf)));			\
																				\
	OldEmf = v.EmfQsS;															\
	v.EmfQsS = v.UQsS - v.UCompQsS - _IQmpy(v.K5,v.IQsS);						\
	v.PsiQsS = v.PsiQsS + _IQdiv2(_IQmpy(v.K6,(v.EmfQsS + OldEmf)));			\
																				\
/* Estimate the rotor flux based on stator flux from the integral of back emf*/	\
																				\
	v.PsiDrS = _IQmpy(v.K7,v.PsiDsS) - _IQmpy(v.K8,v.IDsS);						\
	v.PsiQrS = _IQmpy(v.K7,v.PsiQsS) - _IQmpy(v.K8,v.IQsS);						\
																				\
/* Compute the rotor flux angle*/												\
	v.ThetaFlux = _IQatan2PU(v.PsiQrS,v.PsiDrS);

#endif // __ACI_FE_H__

