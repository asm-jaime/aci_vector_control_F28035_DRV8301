//###########################################################################
//
// FILE:   CLAShared.h
//
// TITLE:  CLA and CPU shared variables and constants
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef CLA_SHARED_H
#define CLA_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

  #include "IQmathLib.h"
  #include "DSP28x_Project.h"

  #define FILTER_LEN          5

  extern Uint16  VoltFilt;
  extern float32  X[FILTER_LEN];
  extern float32 A[FILTER_LEN];

// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

  extern Uint32 Cla1Task1;
  extern Uint32 Cla1Task2;
  extern Uint32 Cla1Task3;
  extern Uint32 Cla1Task4;
  extern Uint32 Cla1Task5;
  extern Uint32 Cla1Task6;
  extern Uint32 Cla1Task7;
  extern Uint32 Cla1Task8;
  extern Uint32 Cla1Prog_Start;
  extern Uint32 Cla1T1End;
  extern Uint32 Cla1T2End;
  extern Uint32 Cla1T3End;
  extern Uint32 Cla1T4End;
  extern Uint32 Cla1T5End;
  extern Uint32 Cla1T6End;
  extern Uint32 Cla1T7End;
  extern Uint32 Cla1T8End;

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  // end of CLA_SHARED definition

