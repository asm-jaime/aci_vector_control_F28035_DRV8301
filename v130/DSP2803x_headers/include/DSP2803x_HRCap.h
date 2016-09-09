//###########################################################################
//
// FILE:   DSP2803x_HRCap.h
//
// TITLE:  DSP2803x High Resolution Capture Register Definitions
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef DSP2803x_HRCAP_H
#define DSP2803x_HRCAP_H

#ifdef __cplusplus
extern "C" {
#endif

//===========================================================================
//  High-Resolution Capture Register Bit Definitions
//

struct HCCTL_BITS {            // bit       description
    Uint16   SOFTRESET:1;      // 0         Soft Reset
    Uint16   RISEINTE:1;       // 1         RISE Capture Interrupt Enable Bit
    Uint16   FALLINTE:1;       // 2         FALL Capture Interrupt Enable Bit
    Uint16   OVFINTE:1;        // 3         Counter Overflow Interrupt Enable Bit
    Uint16   rsvd1:4;          // 7:4       reserved
    Uint16   HCCAPCLKSEL:1;    // 8         Capture Clock Select Bit
	Uint16   rsvd2:7; 		   // 15:9	    reserved
};

union HCCTL_REG  {
    Uint16                       all;
    struct HCCTL_BITS            bit;
};

struct HCIFR_BITS {            // bit       description
    Uint16   INT:1;            // 0         Global Interrupt Flag
    Uint16   RISE:1;           // 1         RISE Capture Interrupt Flag
    Uint16   FALL:1;           // 2         FALL Capture Interrupt Flag
    Uint16   COUNTEROVF:1;     // 3         Counter Overflow Interrupt Flag
	Uint16   RISEOVF:1;  	   // 4         RISE Interrupt Overflow Event Flag
    Uint16   rsvd1:11;         // 15:5      reserved
};

union HCIFR_REG  {
    Uint16                       all;
    struct HCIFR_BITS            bit;
};

struct HCICLR_BITS {           // bit       description
    Uint16   INT:1;            // 0         Global Interrupt Flag Clear Bit
    Uint16   RISE:1;           // 1         RISE Capture Interrupt Flag Clear Bit
    Uint16   FALL:1;           // 2         FALL Capture Interrupt Flag Clear Bit
    Uint16   COUNTEROVF:1;     // 3         Counter Overflow Interrupt Flag Clear Bit
	Uint16   RISEOVF:1;  	   // 4         RISE Interrupt Overflow Event Flag Clear Bit
    Uint16   rsvd1:11;         // 15:5      reserved
};

union HCICLR_REG  {
    Uint16                       all;
    struct HCICLR_BITS           bit;
};

struct HCIFRC_BITS {           // bit       description
    Uint16   rsvd1:1;          // 0         reserved
    Uint16   RISE:1;           // 1         RISE Capture Interrupt Flag Force Bit
    Uint16   FALL:1;           // 2         FALL Capture Interrupt Flag Force Bit
    Uint16   COUNTEROVF:1;     // 3         Counter Overflow Interrupt Flag Force Bit
	Uint16   RISEOVF:1;  	   // 4         RISE Interrupt Overflow Event Flag Force Bit
    Uint16   rsvd2:11;         // 15:5      reserved
};

union HCIFRC_REG  {
    Uint16                       all;
    struct HCIFRC_BITS           bit;
};
/*
struct HCCAPDLYRISE0_BITS {   // bit        description
    Uint16  CAPDLYRISE:7;     // 6:0        Capture Delay on Rising Edge 0
	Uint16  rsvd1:9;          // 15:7		reserved
};

union HCCAPDLYRISE0_REG  {
	Uint16                       all;
	struct HCCAPDLYRISE0_BITS    bit;
};

struct HCCAPDLYRISE1_BITS {   // bit        description
    Uint16  CAPDLYRISE:7;     // 6:0        Capture Delay on Rising Edge 1
	Uint16  rsvd1:9;          // 15:7		reserved
};

union HCCAPDLYRISE1_REG  {
	Uint16                       all;
	struct HCCAPDLYRISE1_BITS    bit;
};

struct HCCAPDLYFALL0_BITS {   // bit        description
    Uint16  CAPDLYFALL:7;     // 6:0        Capture Delay on Falling Edge 0
	Uint16  rsvd1:9;          // 15:7		reserved
};

union HCCAPDLYFALL0_REG  {
	Uint16                       all;
	struct HCCAPDLYFALL0_BITS    bit;
};

struct HCCAPDLYFALL1_BITS {   // bit        description
    Uint16  CAPDLYFALL:7;     // 6:0        Capture Delay on Falling Edge 1
	Uint16  rsvd1:9;          // 15:7		reserved
};

union HCCAPDLYFALL1_REG  {
	Uint16                       all;
	struct HCCAPDLYFALL1_BITS    bit;
};

struct HCCALCTL_BITS {       // bit        description
    Uint16  HRPWMSEL:1;      // 0          Calibration Input Select bit
	Uint16  rsvd1:15;        // 15:1	   reserved
};

union HCCALCTL_REG  {
	Uint16                  all;
	struct HCCALCTL_BITS    bit;
};
*/


//===========================================================================
//  High Resolution Capture Register Definitions
//
/*
struct HRCAP_REGS {
    union  HCCTL_REG           HCCTL;
	union  HCIFR_REG           HCIFR;
	union  HCICLR_REG          HCICLR;
	union  HCIFRC_REG          HCIFRC;
	Uint16                     HCCOUNTER;
    Uint16                     rsvd1[3];
	union  HCCALCTL_REG        HCCALCTL;
	Uint16                     rsvd2[7];
	Uint16                     HCCAPCNTRISE0;
	Uint16                     rsvd3;
	Uint16                     HCCAPCNTFALL0;
	Uint16                     rsvd4;
	union  HCCAPDLYRISE0_REG   HCCAPDLYRISE0;
	union  HCCAPDLYFALL0_REG   HCCAPDLYFALL0;
	Uint16                     rsvd5[2];
	Uint16                     HCCAPCNTRISE1;
	Uint16                     rsvd6;
	Uint16                     HCCAPCNTFALL1;
	Uint16                     rsvd7;
	union  HCCAPDLYRISE1_REG   HCCAPDLYRISE1;
	union  HCCAPDLYFALL1_REG   HCCAPDLYFALL1;
    Uint16                     rsvd8[2];
};
*/

struct HRCAP_REGS {
    union  HCCTL_REG           HCCTL;
	union  HCIFR_REG           HCIFR;
	union  HCICLR_REG          HCICLR;
	union  HCIFRC_REG          HCIFRC;
	Uint16                     HCCOUNTER;
    Uint16                     rsvd1[4];
	Uint16                     rsvd2[7];
	Uint16                     HCCAPCNTRISE0;
	Uint16                     rsvd3;
	Uint16                     HCCAPCNTFALL0;
	Uint16                     rsvd4;
	Uint16                     rsvd5;
	Uint16                     rsvd6;
	Uint16                     rsvd7[2];
	Uint16                     HCCAPCNTRISE1;
	Uint16                     rsvd8;
	Uint16                     HCCAPCNTFALL1;
	Uint16                     rsvd9;
	Uint16                     rsvd10;
	Uint16                     rsvd11;
    Uint16                     rsvd12[2];
};

//===========================================================================
//  High Resolution Capture External References and Function Declarations
//

extern volatile struct HRCAP_REGS HRCap1Regs;
extern volatile struct HRCAP_REGS HRCap2Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_HRCAP_H definition

//===========================================================================
// End of file
//===========================================================================
