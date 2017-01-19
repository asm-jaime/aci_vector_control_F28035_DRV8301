// TI File $Revision: /main/1 $
// Checkin $Date: December 5, 2008   18:04:43 $
//###########################################################################
//
// FILE:    DSP2803x_BootVars.h
//
// TITLE:   DSP2803x Boot Variable Definitions.
//
// NOTES:
//
//###########################################################################
// $TI Release: 2803x C/C++ Header Files V1.22 $
// $Release Date: June 10, 2010 $
//###########################################################################

#ifndef DSP2803x_BOOT_VARS_H
#define DSP2803x_BOOT_VARS_H

#ifdef __cplusplus
extern "C" {
#endif



//---------------------------------------------------------------------------
// External Boot ROM variable definitions:
//
extern Uint16 EmuKey;
extern Uint16 EmuBMode;
extern Uint32 Flash_CPUScaleFactor;
extern void (*Flash_CallbackPtr) (void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_BOOT_VARS_H definition

//===========================================================================
// End of file.
//===========================================================================

