/* =================================================================================
File name:       VHZ_PROF.H  (IQ version)                   
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type, and macro  definitions for the VHZPROF.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 07-29-2010	Version 1.00                                                
------------------------------------------------------------------------------*/
#ifndef __VHZ_PROF_H__
#define __VHZ_PROF_H__

typedef struct 	{ _iq  Freq; 		    // Input: Input Frequency (pu)
				_iq  VoltOut;			// Output: Output voltage (pu)
				_iq  LowFreq;			// Parameter: Low Frequency (pu)			
				_iq  HighFreq;			// Parameter: High Frequency at rated voltage (pu)
				_iq  FreqMax; 			// Parameter: Maximum Frequency (pu)
				_iq  VoltMax;			// Parameter: Rated voltage (pu)					  
			    _iq  VoltMin;	 		// Parameter: Voltage at low Frequency range (pu)
		  	  	  
				} VHZPROF;	                   

typedef VHZPROF *VHZPROF_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the VHZPROF object.
-----------------------------------------------------------------------------*/                     
#define VHZPROF_DEFAULTS { 0,0, 		\
                           0,0,0,0,0, 	\
                  		 }

/*------------------------------------------------------------------------------
	 VHZ_PROF Macro Definitions
------------------------------------------------------------------------------*/

_iq VfSlope, AbsFreq;

#define VHZ_PROF_MACRO(v)															\
/* Take absolute frequency to allow the operation of both rotational directions	*/	\
    AbsFreq = labs(v.Freq);															\
	if (AbsFreq <= v.LowFreq)   													\
	        /* Compute output voltage in profile #1	*/								\
        	v.VoltOut = v.VoltMin;													\
	else if ((AbsFreq > v.LowFreq)&&(AbsFreq <= v.HighFreq))      					\
       {																			\
        	/* Compute slope of V/f profile	*/										\
        	VfSlope = _IQdiv((v.VoltMax - v.VoltMin),(v.HighFreq - v.LowFreq));		\
        	/* Compute output voltage in profile #2	*/								\
        	v.VoltOut = v.VoltMin + _IQmpy(VfSlope,(AbsFreq-v.LowFreq));			\
       }																			\
    	else if ((AbsFreq > v.HighFreq)&&(AbsFreq < v.FreqMax))      				\
        	/* Compute output voltage in profile #3	*/								\
        	v.VoltOut = v.VoltMax;


#endif  // __VHZ_PROF_H__
