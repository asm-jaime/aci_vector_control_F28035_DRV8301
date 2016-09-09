//###########################################################################
//
// FILE:   DSP2803x_Comp.h
//
// TITLE:  DSP2803x Device Comparator Register Definitions
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef DSP2803x_COMP_H
#define DSP2803x_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================
//  Comparator Register Bit Definitions
//

struct COMPCTL_BITS {            // bit       description
    Uint16   COMPDACEN:1;        // 0         Comparator/DAC  Enable
    Uint16   COMPSOURCE:1;       // 1         Source select for comparator inverting input
    Uint16   CMPINV:1;           // 2         Invert select for Comparator
    Uint16   QUALSEL:5;          // 7:03      Qualification Period for synchronized output of the comparator
    Uint16   SYNCSEL:1;          // 8         Synchronization select for output of the comparator
    Uint16   rsvd1:7;            // 15:09     reserved
};

union COMPCTL_REG  {
    Uint16                         all;
    struct COMPCTL_BITS            bit;
};

struct COMPSTS_BITS {            // bit       description
    Uint16   COMPSTS:1;          // 0         Logical latched value of the comparator
    Uint16   rsvd1:15;           // 15:01     reserved
};

union COMPSTS_REG  {
    Uint16                         all;
    struct COMPSTS_BITS            bit;
};

struct DACCTL_BITS {            // bits      description
    Uint16   DACSOURCE:1;        // 0         DAC source control bits.
    Uint16   RAMPSOURCE:4;       // 4:01      Ramp generator source control bits
    Uint16   rsvd1:9;            // 13:05     reserved
    Uint16   FREE_SOFT:2;        // 15:14     Debug Mode Bit
};

union DACCTL_REG  {
    Uint16                         all;
    struct DACCTL_BITS             bit;
};

struct DACVAL_BITS {             // bit       description
    Uint16   DACVAL:10;          // 9:00      DAC Value bit
    Uint16   rsvd1:6;            // 15:10     reserved
};

union DACVAL_REG  {
    Uint16                         all;
    struct DACVAL_BITS             bit;
};

//===========================================================================
//  Comparator Register Definitions
//

struct COMP_REGS {
    union  COMPCTL_REG         COMPCTL;
    Uint16                     rsvd1;
    union  COMPSTS_REG         COMPSTS;
    Uint16                     rsvd2;
    union  DACCTL_REG          DACCTL;
    Uint16                     rsvd3;
    union  DACVAL_REG          DACVAL;
    Uint16                     rsvd4;
    Uint16                     RAMPMAXREF_ACTIVE;
    Uint16                     rsvd5;
    Uint16                     RAMPMAXREF_SHDW;
    Uint16                     rsvd6;
    Uint16                     RAMPDECVAL_ACTIVE;
    Uint16                     rsvd7;
    Uint16                     RAMPDECVAL_SHDW;
    Uint16                     rsvd8;
    Uint16                     RAMPSTS;
    Uint16                     rsvd9[3];
};

//===========================================================================
//  Comparator External References and Function Declarations
//

extern volatile struct COMP_REGS Comp1Regs;
extern volatile struct COMP_REGS Comp2Regs;
extern volatile struct COMP_REGS Comp3Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_COMP_H definition

//===========================================================================
// End of file
//===========================================================================
