/* =================================================================================
File name:       COM_TRIG.H  (IQ version)                    

Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the CMTN.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 03-01-2010	Version 1.0                                       
------------------------------------------------------------------------------*/
#include "PeripheralHeaderIncludes.h"

typedef  struct { Uint32 CmtnTrig;       	// Output: Commutation trigger output (0 or 0x00007FFF)       
                  _iq Va;                 	// Input: Motor phase a voltage referenced to GND (pu)  
                  _iq Vb;                 	// Input: Motor phase b voltage referenced to GND (pu)  
                  _iq Vc;                 	// Input: Motor phase c voltage referenced to GND (pu) 
                  _iq Neutral;            	// Variable: 3*Motor netural voltage (pu) 
                  Uint32 RevPeriod;      	// Variable: revolution time counter (Q0)        
                  Uint32 ZcTrig;         	// Variable: Zero-Crossing trig flag (0 or 0x00007FFF)  
                  Uint32 CmtnPointer;     	// Input: Commutation state pointer input (0,1,2,3,4,5)
                  _iq DebugBemf;         	// Variable: 3*Back EMF = 3*(vx=vn), x=a,b,c (pu)
                  Uint32 NoiseWindowCounter;// Variable: Noise windows counter (Q0) 
                  Uint32 Delay30DoneFlag;   // Variable: 30 Deg delay flag (0 or 0x0000000F) 
                  Uint32 NewTimeStamp;  	// Variable: Time stamp (Q0) 
                  Uint32 OldTimeStamp;  	// History: Previous time stamp (Q0) 
	              Uint32 VirtualTimer;    	// Input: Virtual timer (Q0) 
                  Uint32 CmtnDelay;      	// Variable: Time delay in terms of number of sampling time periods (Q0)    
                  Uint32 DelayTaskPointer; 	// Variable: Delay task pointer, see note below (0 or 1)
                  Uint32 NoiseWindowMax;  	// Variable: Maximum noise windows counter (Q0)
                  Uint32 CmtnDelayCounter; 	// Variable: Time delay counter (Q0) 
                  Uint32 NWDelta;      		// Variable: Noise windows delta (Q0)
                  Uint32 NWDelayThres;    	// Variable: Noise windows dynamic threshold (Q0)
		 	 	  
                } CMTN;

/*
Note: 
DelayTaskPointer = 0, branch for #COUNT_DWN
DelayTaskPointer = 1, branch for #CHK_TRIGGER
*/

typedef CMTN *CMTN_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the CMTN object.
-----------------------------------------------------------------------------*/                     
#define CMTN_DEFAULTS { 0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        0, \
                        1, \
                        0, \
                        0, \
                        0, \
                        0, \
              		   }

/*----------------------------------------------------------------------------------------------
	 CMTN_TRIG Macro Definition
----------------------------------------------------------------------------------------------*/

#define CMTN_TRIG_MACRO(v)																\
																						\
/* Always clear flags on entry*/														\
    v.CmtnTrig = 0;																		\
    v.ZcTrig = 0;																		\
        																				\
/* Neutral voltage calculation (3*motor Neutral voltage)*/								\
	v.Neutral = v.Va + v.Vb + v.Vc;														\
																						\
/* Commutation State table Tasks*/														\
/* State s1: current flows to motor windings from phase A->B, de-energized phase = C*/	\
   if (v.CmtnPointer == 0)																\
    {																					\
	  v.DebugBemf = _IQmpy(_IQ(3),v.Vc) - v.Neutral;									\
	  if (v.DebugBemf > 0)																\
	       v.NoiseWindowCounter = 0;													\
	  else   /*  Zero crossing Noise window processing*/								\
           NOISE_WINDOW_CNT_MACRO(v);													\
    }   /* else if-end: State s1*/ 														\
																						\
/* State s2: current flows to motor windings from phase A->C, de-energized phase = B*/ 	\
    else if (v.CmtnPointer == 1)  														\
	{																					\
	  v.DebugBemf = _IQmpy(_IQ(3),v.Vb) - v.Neutral;									\
	  if (v.DebugBemf < 0)																\
	       v.NoiseWindowCounter = 0;													\
	  else   /*  Zero crossing Noise window processing*/								\
           NOISE_WINDOW_CNT_MACRO(v);													\
    }   /* else if-end: State s2*/														\
																						\
/* State s3: current flows to motor windings from phase B->C, de-energized phase = A*/ 	\
    else if (v.CmtnPointer == 2)  														\
    {																					\
	  v.DebugBemf = _IQmpy(_IQ(3),v.Va) - v.Neutral;									\
	  if (v.DebugBemf > 0)																\
	       v.NoiseWindowCounter = 0;													\
	  else  /*  Zero crossing Noise window processing*/									\
           NOISE_WINDOW_CNT_MACRO(v);													\
    }   /* else if-end: State s3*/														\
																						\
/* State s4: current flows to motor windings from phase B->A, de-energized phase = C*/	\
    else if (v.CmtnPointer == 3)  														\
    {																					\
	  v.DebugBemf = _IQmpy(_IQ(3),v.Vc) - v.Neutral;									\
	  if (v.DebugBemf < 0)																\
	       v.NoiseWindowCounter = 0;													\
	  else   /*  Zero crossing Noise window processing*/								\
           NOISE_WINDOW_CNT_MACRO(v);													\
    }   /* else if-end: State s4*/														\
																						\
/* State s5: current flows to motor windings from phase C->A, de-energized phase = B*/	\
    else if (v.CmtnPointer == 4)														\
    {																					\
	  v.Delay30DoneFlag = 0;	       /* clear flag for delay calc in State 5*/		\
	  																					\
	  v.DebugBemf = _IQmpy(_IQ(3),v.Vb) - v.Neutral;									\
	  if (v.DebugBemf > 0)																\
	       v.NoiseWindowCounter = 0;													\
	  else   /*  Zero crossing Noise window processing */								\
           NOISE_WINDOW_CNT_MACRO(v);													\
    }   /* else if-end: State s5	 */													\
																						\
/* State s6: current flows to motor windings from phase C->B, de-energized phase = A*/	\
    else if (v.CmtnPointer == 5)  														\
    {																					\
	  v.DebugBemf = _IQmpy(_IQ(3),v.Va) - v.Neutral;									\
	  if (v.DebugBemf < 0)																\
	       v.NoiseWindowCounter = 0;													\
	  else   /*  Zero crossing Noise window processing*/								\
           NOISE_WINDOW_CNT_MACRO(v);													\
      DELAY_30DEG_MACRO(v);																\
    }   /* else if-end: State s6*/														\
																						\
/* Zero crossing to Commutation trigger delay*/											\
   v.CmtnTrig = 0;     /* Always clear flag on entry */									\
																						\
   if (v.DelayTaskPointer > 0)     /* v.DelayTaskPointer = 1 for #CHK_TRIGGER*/			\
   { 																					\
      if (v.ZcTrig != 0)																\
      {																					\
      /* Substract NoiseWindowMax to compensate the advanced zero-crossing validation point */	\
          v.CmtnDelayCounter = v.CmtnDelay - v.NoiseWindowMax;									\
          v.DelayTaskPointer = 0;     /* v.DelayTaskPointer = 0 for #COUNT_DWN*/				\
      }																							\
   }																							\
   else     /* v.DelayTaskPointer = 0 for #COUNT_DWN */											\
   {  																							\
       v.CmtnDelayCounter -= 1;																	\
       if (v.CmtnDelayCounter == 0) 															\
       {																						\
          v.CmtnTrig = 0x00007FFF; /* Yes!- Set trigger. This is used */						\
/* as an input to "MOD6_CNTR" module that changes the commutation sequence.*/					\
						             															\
          v.DelayTaskPointer = 1;       /* v.DelayTaskPointer = 1 for #CHK_TRIGGER*/			\
       }    																					\
   }

/*----------------------------------------------------------------------------------------------
	 NOISE_WINDOW_CNT Macro Definition
----------------------------------------------------------------------------------------------*/

#define NOISE_WINDOW_CNT_MACRO(v)																\
   if (v.CmtnDelay >= v.NWDelayThres)      /* noise window is fixed Value*/						\
      v.NoiseWindowMax = v.NWDelayThres - v.NWDelta;											\
   else                                       /* noise window adjusted dynamically*/			\
      v.NoiseWindowMax = v.CmtnDelay - v.NWDelta;												\
																								\
   v.NoiseWindowCounter += 1;																	\
																								\
   if (v.NoiseWindowCounter == v.NoiseWindowMax)  /* zc must occur max_noise_window times*/		\
   {																							\
     v.ZcTrig = 0x00007FFF;       /* Yes! Set trigger */										\
     v.NoiseWindowCounter = 0;																	\
   }								

/*----------------------------------------------------------------------------------------------
	DELAY_30DEG Macro Definition
----------------------------------------------------------------------------------------------*/

   int32 Tmp, GPR1_COM_TRIG;

#define DELAY_30DEG_MACRO(v)																	\
/* Delay 30 deg calculator*/																	\
   if (v.Delay30DoneFlag == 0)																	\
   {  																							\
      v.OldTimeStamp = v.NewTimeStamp;															\
      v.NewTimeStamp = v.VirtualTimer; 															\
      Tmp = v.NewTimeStamp - v.OldTimeStamp; 													\
      																							\
      if (Tmp > 0) /* Period = NewTimeStamp - OldTimeStamp*/									\
          v.RevPeriod = Tmp;																	\
      else       /* If Period is negative, allow "wrapping"  */									\
          v.RevPeriod = 0x00007FFF + Tmp;														\
																								\
      v.RevPeriod &= 0x0000FFFF;																\
																								\
      v.CmtnDelay = v.RevPeriod/12;                  /* Division quotient*/						\
      GPR1_COM_TRIG = v.RevPeriod - v.CmtnDelay*12;  /* Division reminder*/						\
      if (GPR1_COM_TRIG >= 6) 																	\
           v.CmtnDelay += 1;       /* if Division reminder >= 6, rounding division quotient*/	\
      v.Delay30DoneFlag = 0x0000000F;  /* flag indicates "gone through" once*/					\
   }   /* if-end: v.Delay30DoneFlag == 0*/    
