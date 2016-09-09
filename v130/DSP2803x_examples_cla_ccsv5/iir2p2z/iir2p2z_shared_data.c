//###########################################################################
// Description:
//
// Declare shared memory variables and assign them to specific CLA-accessible
// memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1 (RAML2)
//!    - S1_A - Feedback coefficients
//!    - S1_B - Feedforward coefficients
//!  - CLA1 to CPU Message RAM
//!    - yn - Output of the Biquad
//!  - CPU to CLA1 Message RAM
//!    - xn - Sample input to the filter
//!
//! \latexonly \input{examples_cla_iir2p2z} \endlatexonly
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

//GLobal Data
 //Ensure that all data is placed in the data rams

//Task 1 (C) Variables
#pragma DATA_SECTION(S1_B,"Cla1DataRam1")
float S1_B[]={0.02008, 0.04017, 0.02008};
#pragma DATA_SECTION(S1_A,"Cla1DataRam1")
float S1_A[]={1.0, 1.56102, -0.64135};
#pragma DATA_SECTION(xn,"CpuToCla1MsgRAM")
float xn;
#pragma DATA_SECTION(yn,"Cla1ToCpuMsgRAM")
float yn;

float fBiquadOutput[NUM_SAMPLES];
float fAdcInput[NUM_SAMPLES] = {
	0, 0.4359, -0.4129, 0.2482, 
	0.4182, -0.3455, 0.4780, 0.3674, 
	-0.2347, 0.6724, 0.2939, -0.0858, 
	0.8178, 0.2100, 0.0914, 0.9045, 
	0.1283, 0.2836, 0.9279, 0.0604, 
	0.4755, 0.8888, 0.0156, 0.6506, 
	0.7929, 0, 0.7929, 0.6506, 
	0.0156, 0.8888, 0.4755, 0.0604, 
	0.9279, 0.2836, 0.1283, 0.9045, 
	0.0914, 0.2100, 0.8178, -0.0858, 
	0.2939, 0.6724, -0.2347, 0.3674, 
	0.4780, -0.3455, 0.4182, 0.2482, 
	-0.4129, 0.4359, 0.0000, -0.4359, 
	0.4129, -0.2482, -0.4182, 0.3455, 
	-0.4780, -0.3674, 0.2347, -0.6724, 
	-0.2939, 0.0858, -0.8178, -0.2100, 
	-0.0914, -0.9045, -0.1283, -0.2836, 
	-0.9279, -0.0604, -0.4755, -0.8888, 
	-0.0156, -0.6506, -0.7929, 0,
	-0.7929, -0.6506, -0.0156, -0.8888, 
	-0.4755, -0.0604, -0.9279, -0.2836, 
	-0.1283, -0.9045, -0.0914, -0.2100, 
	-0.8178, 0.0858, -0.2939, -0.6724, 
	0.2347, -0.3674, -0.4780, 0.3455, 
	-0.4182, -0.2482, 0.4129, -0.4359, 
	-0.0000, 0.4359, -0.4129, 0.2482, 
	0.4182, -0.3455, 0.4780, 0.3674, 
	-0.2347, 0.6724, 0.2939, -0.0858, 
	0.8178, 0.2100, 0.0914, 0.9045, 
	0.1283, 0.2836, 0.9279, 0.0604, 
	0.4755, 0.8888, 0.0156, 0.6506, 
	0.7929, 0, 0.7929, 0.6506
	};
//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables



