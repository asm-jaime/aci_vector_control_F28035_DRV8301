/* ==================================================================================
File name:       sin_cos_table.H

Description: This header file contains macro definition for a discrete sin/cos table.
			 sin and cos tables come from IQmathTables section which could be ROM
			 or RAM               
===================================================================================*/

#ifndef SINCOSTBL_H_
#define SINCOSTBL_H_

#include "IQmathLib.h"

/*-----------------------------------------------------------------------------
	Define the structure of the SINTBL Driver Object 
-----------------------------------------------------------------------------*/
typedef struct {
	    Uint16 AngleShift;	// Input: scale angle to modulo 512 (length of table) 
        Uint16 Angle;    	// Input: angle (Q2-Q9)
        _iq SinOut;    		// Output: Sin (GLOBAL_Q) 
        _iq CosOut;    		// Output: Cos (GLOBAL_Q)
        } SINCOSTBL ;    

/*-----------------------------------------------------------------------------
Default initalizer for the SINCOSTBL object.
-----------------------------------------------------------------------------*/                     
#define SINCOSTBL_DEFAULTS {  0, \
                          0, \
                          0, \
                          0	 \
              			  }

/*------------------------------------------------------------------------------
	SINCOSTBL Update Macro Definition
------------------------------------------------------------------------------*/

    /*symbols from IQmathTables section*/
	extern _iq IQsinTable[];
	extern _iq IQcosTable[];

    Uint16 Angle;
    
#define SINCOSTBL_MACRO(st)														\
																				\
	/* scale angle up to modulo 512 */											\
	Angle = (st.Angle << st.AngleShift) & 0x01FF;								\
																				\
	/* grab sin output from table */											\
	st.SinOut = _IQ30toIQ(IQsinTable[Angle]);									\
																				\
	/* grab cos output from table */											\
	st.CosOut = _IQ30toIQ(IQcosTable[Angle]);									\
  

#endif /*SINCOSTBL_H_*/
