//###########################################################################
//
// FILE:	DSP2803x_MemCopy.c
//
// TITLE:	Memory Copy Utility
//
// ASSUMPTIONS:
//
//          
//
// DESCRIPTION:
//
//          This function will copy the specified memory contents from
//          one location to another. 
// 
//          Uint16 *SourceAddr        Pointer to the first word to be moved
//                                    SourceAddr < SourceEndAddr
//          Uint16* SourceEndAddr     Pointer to the last word to be moved
//          Uint16* DestAddr          Pointer to the first destination word
//
//          No checks are made for invalid memory locations or that the
//          end address is > then the first start address.
// 
//          
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V1.25 $
// $Release Date: August 26, 2011 $
//###########################################################################

#include "DSP2803x_Device.h"

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    { 
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

//===========================================================================
// End of file.
//===========================================================================
