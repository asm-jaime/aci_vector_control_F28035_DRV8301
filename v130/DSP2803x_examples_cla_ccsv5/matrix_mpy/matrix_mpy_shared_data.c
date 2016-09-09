//###########################################################################
// Description:
//
// Declare shared memory variables and assign them to specific CLA-accessible
// memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 to CPU Message RAM
//!    - z - Result of the matrix multiplication
//!  - CPU to CLA1 Message RAM
//!    - x - 3X3 Input Matrix
//!    - y - 3X3 Input Matrix
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
#pragma DATA_SECTION(x,"CpuToCla1MsgRAM")
float x[][N] = {{10,3,4}, {3,1,2}, {4,2,6}}; 
#pragma DATA_SECTION(y,"CpuToCla1MsgRAM")
float y[][N] = {{1,2,1}, {2,1,2}, {1,2,6}};
#pragma DATA_SECTION(z,"Cla1ToCpuMsgRAM")
float z[M][N];

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables


