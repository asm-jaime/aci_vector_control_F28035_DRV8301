/* -----------------------------------------------------------------------------------
File name:      PID_grando.h

Originator:		C2000 System Applications, Texas Instruments

Description: 	Data and macro definitions for "grando" PID controller
-------------------------------------------------------------------------------------*/

#ifndef __PID_GRANDO_H__
#define __PID_GRANDO_H__

typedef struct {  _iq  Ref;   			// Input: reference set-point
				  _iq  Fbk;   			// Input: feedback
				  _iq  Out;   			// Output: controller output 
				  _iq  c1;   			// Internal: derivative filter coefficient 1
				  _iq  c2;   			// Internal: derivative filter coefficient 2
				} PID_GRANDO_TERMINALS;
				// note: c1 & c2 placed here to keep structure size under 8 words

typedef struct {  _iq  Kr;				// Parameter: reference set-point weighting 
				  _iq  Kp;				// Parameter: proportional loop gain
				  _iq  Ki;			    // Parameter: integral gain
				  _iq  Kd; 		        // Parameter: derivative gain
				  _iq  Km; 		        // Parameter: derivative weighting
				  _iq  Umax;			// Parameter: upper saturation limit
				  _iq  Umin;			// Parameter: lower saturation limit
				} PID_GRANDO_PARAMETERS;

typedef struct {  _iq  up;				// Data: proportional term
				  _iq  ui;				// Data: integral term
				  _iq  ud;				// Data: derivative term
				  _iq  v1;				// Data: pre-saturated controller output
				  _iq  i1;				// Data: integrator storage: ui(k-1)
				  _iq  d1;				// Data: differentiator storage: ud(k-1)
				  _iq  d2;				// Data: differentiator storage: d2(k-1) 
				  _iq  w1;				// Data: saturation record: [u(k-1) - v(k-1)]
				} PID_GRANDO_DATA;


typedef struct {  PID_GRANDO_TERMINALS	term;
				  PID_GRANDO_PARAMETERS param;
				  PID_GRANDO_DATA		data;
				} PID_GRANDO_CONTROLLER;


typedef PID_GRANDO_CONTROLLER	*PID_handle;


/*-----------------------------------------------------------------------------
Default initalisation values for the PID_GRANDO objects
-----------------------------------------------------------------------------*/                     

#define PID_TERM_DEFAULTS {				\
						   0, 			\
                           0, 			\
                           0, 			\
                           0, 			\
						   0 			\
              			  }

#define PID_PARAM_DEFAULTS {			\
                           _IQ(1.0),	\
                           _IQ(1.0), 	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           _IQ(1.0),	\
                           _IQ(1.0),	\
                           _IQ(-1.0) 	\
              			  }

#define PID_DATA_DEFAULTS {			    \
                           _IQ(0.0),	\
                           _IQ(0.0), 	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           _IQ(0.0), 	\
                           _IQ(0.0),	\
                           _IQ(0.0),	\
                           _IQ(1.0) 	\
              			  }


/*------------------------------------------------------------------------------
 	PID_GRANDO Macro Definition
------------------------------------------------------------------------------*/

#define PID_GR_MACRO(v)																				\
																									\
	/* proportional term */ 																		\
	v.data.up = _IQmpy(v.param.Kr, v.term.Ref) - v.term.Fbk;										\
																									\
	/* integral term */ 																			\
	v.data.ui = _IQmpy(v.param.Ki, _IQmpy(v.data.w1, (v.term.Ref - v.term.Fbk))) + v.data.i1;	\
	v.data.i1 = v.data.ui;																			\
																									\
	/* derivative term */ 																			\
	v.data.d2 = _IQmpy(v.param.Kd, _IQmpy(v.term.c1, (_IQmpy(v.term.Ref, v.param.Km) - v.term.Fbk))) - v.data.d2;	\
	v.data.ud = v.data.d2 + v.data.d1;																\
	v.data.d1 = _IQmpy(v.data.ud, v.term.c2);														\
																									\
	/* control output */ 																			\
	v.data.v1 = _IQmpy(v.param.Kp, (v.data.up + v.data.ui + v.data.ud));							\
	v.term.Out= _IQsat(v.data.v1, v.param.Umax, v.param.Umin);									\
	v.data.w1 = (v.term.Out == v.data.v1) ? _IQ(1.0) : _IQ(0.0);									\
	
#endif // __PID_GRANDO_H__

