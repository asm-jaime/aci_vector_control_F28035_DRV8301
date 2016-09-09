//###########################################################################
// Description:
//
// Declare shared memory variables and assign them to specific CLA-accessible
// memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1 (RAML2)
//!    - vector3 - Input/Output to task 3(in-place sorting)
//!  - CLA1 to CPU Message RAM
//!    - vector1_sorted - Sorted output Task 1
//!    - vector2_sorted - Sorted output Task 2
//!  - CPU to CLA1 Message RAM
//!    - vector1 - Input vector to task 1
//!    - vector2 - Input vector to task 2
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
float  vector1[5] =  {1.0,-11.3,6.2,10.8,2.5};              
// CLA Output Data
#pragma DATA_SECTION(vector1_sorted,"Cla1ToCpuMsgRAM");
float   vector1_sorted[LENGTH1];

//Task 2 (C) Variables
// CLA Input Data
#pragma DATA_SECTION(vector2,"CpuToCla1MsgRAM");
float  vector2[10] = {-10.1,-9.9,-8.8,1.0,2.2,3.3,0.0,4.4,8.8,9.9}; 
// CLA Output Data
#pragma DATA_SECTION(vector2_sorted,"Cla1ToCpuMsgRAM");
float   vector2_sorted[LENGTH2];

//Task 3 (C) Variables
// CLA Input Data
// Note: vector3 is input and output (in-place sort)
#pragma DATA_SECTION(vector3,"Cla1DataRam1");
int32  vector3[9] =  {-9,-8,1,2,3,0,4,8,9};
// CLA Output Data
// vector3_sorted is vector3 (in place sort);

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables
