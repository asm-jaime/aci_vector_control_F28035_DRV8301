/* =================================================================================
File name:       SVGEN_MF.H  
===================================================================================*/

#ifndef __SVGEN_MF_H__
#define __SVGEN_MF_H__

typedef struct 	{ _iq  Gain; 				// Input: reference gain voltage (pu) 
				  _iq  Offset;				// Input: reference offset voltage (pu)
				  _iq  Freq;				// Input: reference frequency (pu)
                  _iq  FreqMax;  			// Parameter: Maximum step angle = 6*base_freq*T (pu)
                  _iq  Alpha;     			// History: Sector angle (pu)
                  _iq  NewEntry;    		// History: Sine (angular) look-up pointer (pu)
                  Uint32  SectorPointer;   	// History: Sector number (Q0) - independently with global Q
				  _iq  Ta;					// Output: reference phase-a switching function (pu)		
				  _iq  Tb;					// Output: reference phase-b switching function (pu)
				  _iq  Tc;					// Output: reference phase-c switching function (pu)
				  _iq  StepAngle;			// Variable
				  _iq  EntryOld;				// Variable
				  _iq  dx;					// Variable
				  _iq  dy;					// Variable
				  
				} SVGENMF;

/*-----------------------------------------------------------------------------
Default initalizer for the SVGENMF object.
-----------------------------------------------------------------------------*/                     
#define SVGENMF_DEFAULTS { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }

/*------------------------------------------------------------------------------
	 SVGENMF Macro Definitions
------------------------------------------------------------------------------*/
		
#define	PI_THIRD	_IQ(1.04719755119660)    /* This is 60 degree */

#define SVGENMF_MACRO(v)																			\
	/* Normalise the freq input to appropriate step angle	*/										\
    	/* Here, 1 pu. = 60 degree			*/														\
    	v.StepAngle = _IQmpy(v.Freq,v.FreqMax);														\
	/* Calculate new angle alpha			*/														\
    	v.EntryOld = v.NewEntry;																	\
    	v.Alpha = v.Alpha + v.StepAngle;															\
	if (v.Alpha >= _IQ(1.0))																		\
		v.Alpha = v.Alpha-_IQ(1.0); 																\
	v.NewEntry = v.Alpha;																			\
        v.dy = _IQsin(_IQmpy(v.NewEntry,PI_THIRD));              /* v.dy = sin(NewEntry)	*/		\
    	v.dx = _IQsin(PI_THIRD-_IQmpy(v.NewEntry,PI_THIRD));     /* v.dx = sin(60-NewEntry)	*/		\
  	/* Determine which sector			*/															\
    	if (v.NewEntry-v.EntryOld<0)																\
    	{																							\
      		if (v.SectorPointer==5)																	\
         		v.SectorPointer = 0;																\
      		else																					\
         		v.SectorPointer = v.SectorPointer + 1; 												\
    	}																							\
 	if (v.SectorPointer==0)  /* Sector 1 calculations - a,b,c -. a,b,c*/							\
    	{																							\
		v.Ta = (_IQ(1.0)-v.dx-v.dy)>>1;																\
		v.Tb = v.Ta + v.dx;																			\
		v.Tc = _IQ(1.0) - v.Ta; 																	\
    	}																							\
    	else if (v.SectorPointer==1)  /* Sector 2 calculations - a,b,c -. b,a,c  &  v.dx <-. v.dy*/	\
    	{																							\
		v.Tb = (_IQ(1.0)-v.dx-v.dy)>>1;																\
		v.Ta = v.Tb + v.dy;																			\
		v.Tc = _IQ(1.0) - v.Tb; 																	\
    	}																							\
    	else if (v.SectorPointer==2)  /* Sector 3 calculations - a,b,c -. b,c,a		*/				\
    	{																							\
		v.Tb = (_IQ(1.0)-v.dx-v.dy)>>1;																\
		v.Tc = v.Tb + v.dx;																			\
	    	v.Ta = _IQ(1.0) - v.Tb; 																\
    	}																							\
    	else if (v.SectorPointer==3)  /* Sector 4 calculations - a,b,c -. c,b,a  &  v.dx <-. v.dy*/	\
    	{																							\
		v.Tc = (_IQ(1.0)-v.dx-v.dy)>>1;																\
		v.Tb = v.Tc + v.dy;																			\
		v.Ta = _IQ(1.0) - v.Tc; 																	\
    	}																							\
    	else if (v.SectorPointer==4)  /* Sector 5 calculations - a,b,c -. c,a,b		*/				\
    	{																							\
		v.Tc = (_IQ(1.0)-v.dx-v.dy)>>1;																\
		v.Ta = v.Tc + v.dx;																			\
		v.Tb = _IQ(1.0) - v.Tc; 																	\
    	}																							\
    	else if (v.SectorPointer==5)  /* Sector 6 calculations - a,b,c -. a,c,b  &  v.dx <-. v.dy*/	\
    	{																							\
		v.Ta = (_IQ(1.0)-v.dx-v.dy)>>1;																\
		v.Tc = v.Ta + v.dy;																			\
		v.Tb = _IQ(1.0) - v.Ta; 																	\
    	}																							\
/* Convert the unsigned GLOBAL_Q format (ranged (0,1)) . signed GLOBAL_Q format (ranged (-1,1))	*/	\
/* Then, multiply with a gain and add an offset.						*/							\
    	v.Ta = (v.Ta-_IQ(0.5))<<1;																	\
    	v.Ta = _IQmpy(v.Gain,v.Ta) + v.Offset;														\
																									\
 	v.Tb = (v.Tb-_IQ(0.5))<<1;																		\
    	v.Tb = _IQmpy(v.Gain,v.Tb) + v.Offset;														\
																									\
    	v.Tc = (v.Tc-_IQ(0.5))<<1;																	\
    	v.Tc = _IQmpy(v.Gain,v.Tc) + v.Offset;														\

#endif // __SVGEN_MF_H__
