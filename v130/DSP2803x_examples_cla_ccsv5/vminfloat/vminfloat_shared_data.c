//###########################################################################
// Description:
//
// Declare shared memory variables and assign them to specific CLA-accessible
// memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 to CPU Message RAM
//!    - min1 - Minimum value in vector 1
//!    - index1 - Index of the minimum value in vector 1
//!    - min2 - Minimum value in vector 2
//!    - index2 - Index of the minimum value in vector 2
//!    - min3 - Minimum value in vector 3
//!    - index3 - Index of the minimum value in vector 3
//!  - CPU to CLA1 Message RAM
//!    - vector1 - Input vector to task 1
//!    - vector2 - Input vector to task 2
//!    - vector3 - Input vector to task 3
//!    - length1 - Length of vector 1
//!    - length2 - Length of vector 2
//!    - length3 - Length of vector 3
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
// CLA Input Data
#pragma DATA_SECTION(vector1,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(length1,"CpuToCla1MsgRAM");
float  vector1[] = {1.0,-11.3,6.2,10.8,2.5};
int32  length1 = 5;
// Length 3 and 4 are #defined in vmaxfloat_shared.h

// CLA Output Data
#pragma DATA_SECTION(min1,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(index1,"Cla1ToCpuMsgRAM");
float32 min1;
int32   index1;

//Task 2 (C) Variables
// CLA Input Data
#pragma DATA_SECTION(vector2,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(length2,"CpuToCla1MsgRAM");
float  vector2[] = {2.0,-11.3,16.2,10.8,2.5,-12.5,-13.3}; // min = -12.5 (-13.3 is out of bounds)
int32  length2 = 6;

// CLA Output Data
#pragma DATA_SECTION(min2,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(index2,"Cla1ToCpuMsgRAM");
float32 min2;
int32   index2;

//Task 3 (C) Variables
// CLA Input Data
#pragma DATA_SECTION(vector3,"CpuToCla1MsgRAM");
float  vector3[] = {0.2,2.3,9.6,9.2,6.2,10.8,2.5,-13.3};  // min = .02   (-13.3 is out of bounds)
int32 length3 = 7;

// CLA Output Data
#pragma DATA_SECTION(min3,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(index3,"Cla1ToCpuMsgRAM");
int32   index3;
float32 min3;

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables
#pragma DATA_SECTION(i,"Cla1ToCpuMsgRAM");
int32   i;

