//###########################################################################
// Description:
//
// Declare shared variables
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef VMINFLOAT_SHARED_H_
#define VMINFLOAT_SHARED_H_
#ifdef __cplusplus
extern "C" {
#endif

//Task 1 (C) Variables
extern int32 index1;
extern int32 length1;
extern float32 min1;
extern float32 vector1[];

//Task 2 (C) Variables
extern int32 index2;
extern int32 length2;
extern float32 min2;
extern float32 vector2[];

//Task 3 (C) Variables
extern int32 index3;
extern int32 length3;
extern float32 min3;
extern float32 vector3[];

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables
extern int32 i;

//CLA C Tasks
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

//C Function Prototypes
void test_run();
void test_report();

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /*VMINFLOAT_SHARED_H_*/
