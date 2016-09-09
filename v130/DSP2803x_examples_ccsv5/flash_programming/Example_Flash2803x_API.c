//###########################################################################
// Description:
//! \addtogroup f2803x_example_list
//! <h1> Flash Programming (flash_programming)</h1>
//!
//! This example shows how to program flash using flash API.
//! It shows.
//! - The required software setup before calling the API (setting the
//!   PLL, checking for limp mode etc.),
//! - How to copy the API from flash into SARAM for execution.
//! - How to call the API functions.
//!
//! \note
//! This example runs from Flash.  First program the example
//! into flash.  The code will then copy the API's to RAM and
//! modify the flash.
//!
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

/*---- Flash API include file -------------------------------------------------*/
#include "Flash2803x_API_Library.h"

/*---- example include file ---------------------------------------------------*/
#include "Example_Flash2803x_API.h"

/*---- device support includes ------------------------------------------------*/
#include "DSP28x_Project.h"

/*---- Standard headers -------------------------------------------------------*/
#include <stdio.h>

/*--- Callback function.  Function specified by defining Flash_CallbackPtr */
void MyCallbackFunction(void);
Uint32 MyCallbackCounter; // Just increment a counter in the callback function

/*--- Global variables used to interface to the flash routines */
FLASH_ST FlashStatus;

/*---------------------------------------------------------------------------
  Data/Program Buffer used for testing the flash API functions
---------------------------------------------------------------------------*/
#define  WORDS_IN_FLASH_BUFFER 0x100         // Programming data buffer, Words
Uint16  Buffer[WORDS_IN_FLASH_BUFFER];

/*---------------------------------------------------------------------------
  Sector address info
---------------------------------------------------------------------------*/
typedef struct {
     Uint16 *StartAddr;
     Uint16 *EndAddr;
} SECTOR;

#define OTP_START_ADDR  0x3D7800
#define OTP_END_ADDR    0x3D7BFF

#define FLASH_END_ADDR    0x3F7FFF

#if (FLASH_F28035 || FLASH_F28034)
#define FLASH_START_ADDR  0x3E8000
SECTOR Sector[8]= {
         (Uint16 *) 0x3E8000,(Uint16 *) 0x3E9FFF,
         (Uint16 *) 0x3EA000,(Uint16 *) 0x3EBFFF,
         (Uint16 *) 0x3EC000,(Uint16 *) 0x3EDFFF,
         (Uint16 *) 0x3EE000,(Uint16 *) 0x3EFFFF,
         (Uint16 *) 0x3F0000,(Uint16 *) 0x3F1FFF,
         (Uint16 *) 0x3F2000,(Uint16 *) 0x3F3FFF,
         (Uint16 *) 0x3F4000,(Uint16 *) 0x3F5FFF,
         (Uint16 *) 0x3F6000,(Uint16 *) 0x3F7FFF,
};

#elif (FLASH_F28033 || FLASH_F28032)
#define FLASH_START_ADDR  0x3F0000
SECTOR Sector[8] = {
         (Uint16 *) 0x3F0000,(Uint16 *) 0x3F0FFF,
         (Uint16 *) 0x3F1000,(Uint16 *) 0x3F1FFF,
         (Uint16 *) 0x3F2000,(Uint16 *) 0x3F2FFF,
         (Uint16 *) 0x3F3000,(Uint16 *) 0x3F3FFF,
         (Uint16 *) 0x3F4000,(Uint16 *) 0x3F4FFF,
         (Uint16 *) 0x3F5000,(Uint16 *) 0x3F5FFF,
         (Uint16 *) 0x3F6000,(Uint16 *) 0x3F6FFF,
         (Uint16 *) 0x3F7000,(Uint16 *) 0x3F7FFF,
};
#endif


void main( void )
{
/*------------------------------------------------------------------
 To use the Flash API, the following steps
 must be followed:

      1. Modify Flash2803x_API_Config.h for your targets operating
         conditions.
      2. Include Flash2803x_API_Library.h in the application.
      3. Add the appropriate Flash API library to the project.

  The user's code is responsible for the following:

      4. Initialize the PLL to the proper CPU operating frequency.
      5. If required, copy the flash API functions into on-chip zero waitstate
         RAM.
      6. Initialize the Flash_CPUScaleFactor variable to SCALE_FACTOR
      7. Initialize the callback function pointer or set it to NULL
      8. Optional: Run the Toggle test to confirm proper frequency configuration
         of the API.
      9. Optional: Unlock the CSM.
     10. Make sure the PLL is not running in limp mode
     11. Call the API functions: Flash_Erase(), Flash_Program(), Flash_Verify()

  The API functions will:

       Disable the watchdog
       Check the device PARTID.
       Disable interrupts during time critical code.
       Perform the desired operation and return status
------------------------------------------------------------------*/

   Uint16 Status;
/*------------------------------------------------------------------
 Initialize the PLLCR value before calling any of the F2803x Flash API
 functions.

     Check to see if the PLL needs to changed
     PLLCR_VALUE is defined in Example_Flash2803x_API.h
     1) Make sure PLL is not in limp mode
     2) Disable missing clock detect logic
     3) Make the change
     4) Wait for the DSP to switch to the PLL clock
        This wait is performed to ensure that the flash API functions
        will be executed at the correct frequency.
     5) While waiting, feed the watchdog so it will not reset.
     6) Re-enable the missing clock detect logic
------------------------------------------------------------------*/

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2803x_SysCtrl.c file.
   InitSysCtrl();

/*------------------------------------------------------------------
 Unlock the CSM.
    If the API functions are going to run in unsecured RAM
    then the CSM must be unlocked in order for the flash
    API functions to access the flash.

    If the flash API functions are executed from secure memory
    (L0-L3) then this step is not required.
------------------------------------------------------------------*/
   Status = Example_CsmUnlock();
   if(Status != STATUS_SUCCESS)
   {
       Example_Error(Status);
   }


/*------------------------------------------------------------------
    Copy API Functions into SARAM

    The flash API functions MUST be run out of internal
    zero-waitstate SARAM memory.  This is required for
    the algos to execute at the proper CPU frequency.
    If the algos are already in SARAM then this step
    can be skipped.
    DO NOT run the algos from Flash
    DO NOT run the algos from external memory
------------------------------------------------------------------*/
/******************************************************************/
// For 2803x, we dont need to copy the API from Flash as it is
// present in BOOT ROM
/******************************************************************/

// If the build links in the 2803x_FlashAPI_BootROMSymbols.lib, then
// The API is in boot ROM and we do not need to copy it from flash.
//
// If the build links in the software API library:
// i.e. Flash2803x_API_<version>.lib
// then we need to copy the flash API from the flash memory to RAM.

#if (BOOT_ROM_API == 0)
   Example_MemCopy(&Flash28_API_LoadStart, &Flash28_API_LoadEnd, &Flash28_API_RunStart);
#endif

    // We must also copy required user interface functions to RAM.
    Example_MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);


/*------------------------------------------------------------------
  Initialize Flash_CPUScaleFactor.

   Flash_CPUScaleFactor is a 32-bit global variable that the flash
   API functions use to scale software delays. This scale factor
   must be initialized to SCALE_FACTOR by the user's code prior
   to calling any of the Flash API functions. This initialization
   is VITAL to the proper operation of the flash API functions.

   SCALE_FACTOR is defined in Example_Flash2803x_API.h as
     #define SCALE_FACTOR  1048576.0L*( (200L/CPU_RATE) )

   This value is calculated during the compile based on the CPU
   rate, in nanoseconds, at which the algorithms will be run.
------------------------------------------------------------------*/
   EALLOW;
   Flash_CPUScaleFactor = SCALE_FACTOR;
   EDIS;


/*------------------------------------------------------------------
  Initialize Flash_CallbackPtr.

   Flash_CallbackPtr is a pointer to a function.  The API uses
   this pointer to invoke a callback function during the API operations.
   If this function is not going to be used, set the pointer to NULL
   NULL is defined in <stdio.h>.
------------------------------------------------------------------*/
   EALLOW;
   Flash_CallbackPtr = &MyCallbackFunction;
   EDIS;

   MyCallbackCounter = 0; // Increment this counter in the callback function


   // Jump to SARAM and call the Flash API functions
   Example_CallFlashAPI();
}

/*------------------------------------------------------------------
   Example_CallFlashAPI

   This function will interface to the flash API.

   Parameters:

   Return Value:

   Notes:  This function will be executed from SARAM

-----------------------------------------------------------------*/
#pragma CODE_SECTION(Example_CallFlashAPI,"ramfuncs");
void Example_CallFlashAPI(void)
{
   Uint16  i;
   Uint16  Status;
   Uint16  *Flash_ptr;     // Pointer to a location in flash
   Uint32  Length;         // Number of 16-bit values to be programmed
   float32 Version;        // Version of the API in floating point
   Uint16  VersionHex;     // Version of the API in decimal encoded hex

/*------------------------------------------------------------------
  Toggle Test

  The toggle test is run to verify the frequency configuration of
  the API functions.

  The selected pin will toggle at 10kHz (100uS cycle time) if the
  API is configured correctly.

  Example_ToggleTest() supports common output pins. Other pins can be used
  by modifying the Example_ToggleTest() function or calling the Flash_ToggleTest()
  function directly.

  Select a pin that makes sense for the hardware platform being used.

  This test will run forever and not return, thus only run this test
  to confirm frequency configuration and not during normal API use.
------------------------------------------------------------------*/

   // Example: Toggle GPIO0
   // Example_ToggleTest(0);

   // Example: Toggle GPIO10
   // Example_ToggleTest(10);

   // Example: Toggle GPIO15
   // Example_ToggleTest(15);

   // Example: Toggle GPIO31
   // Example_ToggleTest(31);

   // Example: Toggle GPIO34
   // Example_ToggleTest(34);

/*------------------------------------------------------------------
  Check the version of the API

  Flash_APIVersion() returns the version in floating point.
  FlashAPIVersionHex() returns the version as a decimal encoded hex.

  FlashAPIVersionHex() can be used to avoid processing issues
  associated with floating point values.
------------------------------------------------------------------*/
   VersionHex = Flash_APIVersionHex();
   if(VersionHex != 0x0100)
   {
       // Unexpected API version
       // Make a decision based on this info.
       asm("    ESTOP0");
   }

   Version = Flash_APIVersion();
   if(Version != (float32)1.00)
   {
       // Unexpected API version
       // Make a decision based on this info.
       asm("    ESTOP0");
   }

/*------------------------------------------------------------------
  Before programming make sure the sectors are Erased.

------------------------------------------------------------------*/

   // Example: Erase Sector B - Sector H
   // Sectors A has example code so leave them unerased

   // SECTORA-SECTORH are defined in Flash2803x_API_Library.h
   Status = Flash_Erase((SECTORB|SECTORC|SECTORD|SECTORE|SECTORF|SECTORG|SECTORH),&FlashStatus);
   if(Status != STATUS_SUCCESS)
   {
       Example_Error(Status);
   }


/*------------------------------------------------------------------
  Program Flash Examples

------------------------------------------------------------------*/

// A buffer can be supplied to the program function.  Each word is
// programmed until the whole buffer is programmed or a problem is
// found.  If the buffer goes outside of the range of OTP or Flash
// then nothing is done and an error is returned.


    // Example: Program 0x400 values in Flash SectorG

    // In this case just fill a buffer with data to program into the flash.
    for(i=0;i<WORDS_IN_FLASH_BUFFER;i++)
    {
        Buffer[i] = 0x100+i;
    }

    Flash_ptr = Sector[1].StartAddr;
    Length = 0x400;
    Status = Flash_Program(Flash_ptr,Buffer,Length,&FlashStatus);
    if(Status != STATUS_SUCCESS)
    {
        Example_Error(Status);
    }

    // Verify the values programmed.  The Program step itself does a verify
    // as it goes.  This verify is a 2nd verification that can be done.
    Status = Flash_Verify(Flash_ptr,Buffer,Length,&FlashStatus);
    if(Status != STATUS_SUCCESS)
    {
        Example_Error(Status);
    }

    // Example: Program 0x199 values in Flash SectorG
    for(i=0;i<WORDS_IN_FLASH_BUFFER;i++)
    {
        Buffer[i] = 0x4500+i;
    }

    Flash_ptr = (Uint16 *)Sector[1].StartAddr+0x450;
    Length = 0x199;
    Status = Flash_Program(Flash_ptr,Buffer,Length,&FlashStatus);
    if(Status != STATUS_SUCCESS)
    {
        Example_Error(Status);
    }

    // Verify the values programmed.  The Program step itself does a verify
    // as it goes.  This verify is a 2nd verification that can be done.
    Status = Flash_Verify(Flash_ptr,Buffer,Length,&FlashStatus);
    if(Status != STATUS_SUCCESS)
    {
        Example_Error(Status);
    }

// You can program a single bit in a memory location and then go back to
// program another bit in the same memory location.

   // Example: Program bit 0 in location in Flash SectorF.
   // That is program the value 0xFFFE
   Flash_ptr = Sector[2].StartAddr;
   i = 0xFFFE;
   Length = 1;
   Status = Flash_Program(Flash_ptr,&i,Length,&FlashStatus);
   if(Status != STATUS_SUCCESS)
   {
       Example_Error(Status);
   }

   // Example: Program bit 1 in the same location. Remember
   // that bit 0 was already programmed so the value will be 0xFFFC
   // (bit 0 and bit 1 will both be 0)

   i = 0xFFFC;
   Length = 1;
   Status = Flash_Program(Flash_ptr,&i,Length,&FlashStatus);
   if(Status != STATUS_SUCCESS)
   {
       Example_Error(Status);
   }

   // Verify the value.  This first verify should fail.
   i = 0xFFFE;
   Status = Flash_Verify(Flash_ptr,&i,Length,&FlashStatus);
   if(Status != STATUS_FAIL_VERIFY)
   {
       Example_Error(Status);
   }

   // This is the correct value and will pass.
   i = 0xFFFC;
   Status = Flash_Verify(Flash_ptr,&i,Length,&FlashStatus);
   if(Status != STATUS_SUCCESS)
   {
       Example_Error(Status);
   }

// If a bit has already been programmed, it cannot be brought back to a 1 by
// the program function.  The only way to bring a bit back to a 1 is by erasing
// the entire sector that the bit belongs to.  This example shows the error
// that program will return if a bit is specified as a 1 when it has already
// been programmed to 0.

   // Example: Program a single 16-bit value 0x0002, in Flash Sector B
   Flash_ptr = Sector[2].StartAddr+1;
   i = 0x0002;
   Length = 1;
   Status = Flash_Program(Flash_ptr,&i,Length,&FlashStatus);
   if(Status != STATUS_SUCCESS)
   {
       Example_Error(Status);
   }

   // Example: This will return an error!!  Can't program 0x0001
   // because bit 0 in the the location was previously programmed
   // to zero!

   i = 0x0001;
   Length = 1;
   Status = Flash_Program(Flash_ptr,&i,Length,&FlashStatus);
   // This should return a STATUS_FAIL_ZERO_BIT_ERROR
   if(Status != STATUS_FAIL_ZERO_BIT_ERROR)
   {
       Example_Error(Status);
   }

   // Example: This will return an error!!  The location specified
   // is outside of the Flash and OTP!
   Flash_ptr = (Uint16 *)0x00340000;
   i = 0x0001;
   Length = 1;
   Status = Flash_Program(Flash_ptr,&i,Length,&FlashStatus);
   // This should return a STATUS_FAIL_ADDR_INVALID error
   if(Status != STATUS_FAIL_ADDR_INVALID)
   {
       Example_Error(Status);
   }

   // Example: This will return an error!!  Can't program 1
   // because bit 0 in the the location was previously programmed
   // to zero!
    for(i=0;i<WORDS_IN_FLASH_BUFFER;i++)
    {
        Buffer[i] = 0xFFFF;
    }

    Flash_ptr = Sector[0].EndAddr;
    Length = 13;
    Status = Flash_Program(Flash_ptr,Buffer,Length,&FlashStatus);
    if(Status != STATUS_FAIL_ZERO_BIT_ERROR)//STATUS_FAIL_ADDR_INVALID)
    {
        Example_Error(Status);
    }

/*------------------------------------------------------------------
  More Erase Sectors Examples - Clean up the sectors we wrote to:

------------------------------------------------------------------*/

   // Example: Erase Sector G
   // SECTORB is defined in Flash2803x_API_Library.h
   Status = Flash_Erase(SECTORG,&FlashStatus);
   if(Status != STATUS_SUCCESS)
   {
       Example_Error(Status);
   }

   // Example: Erase Sector F
   // SECTORC is defined in Flash2803x_API_Library.h
   Status = Flash_Erase((SECTORF),&FlashStatus);
   if(Status != STATUS_SUCCESS)
   {
       Example_Error(Status);
   }

   // Example: This will return an error. No valid sector is specified.
   Status = Flash_Erase(0,&FlashStatus);
   // Should return STATUS_FAIL_NO_SECTOR_SPECIFIED
   if(Status != STATUS_FAIL_NO_SECTOR_SPECIFIED)
   {
       Example_Error(Status);
   }

   Example_Done();
}


/*------------------------------------------------------------------
   Example_CsmUnlock

   Unlock the code security module (CSM)

   Parameters:

   Return Value:

            STATUS_SUCCESS         CSM is unlocked
            STATUS_FAIL_UNLOCK     CSM did not unlock

   Notes:

-----------------------------------------------------------------*/
Uint16 Example_CsmUnlock()
{
    volatile Uint16 temp;

    // Load the key registers with the current password
    // These are defined in Example_Flash2803x_CsmKeys.asm

    EALLOW;
    CsmRegs.KEY0 = PRG_key0;
    CsmRegs.KEY1 = PRG_key1;
    CsmRegs.KEY2 = PRG_key2;
    CsmRegs.KEY3 = PRG_key3;
    CsmRegs.KEY4 = PRG_key4;
    CsmRegs.KEY5 = PRG_key5;
    CsmRegs.KEY6 = PRG_key6;
    CsmRegs.KEY7 = PRG_key7;
    EDIS;

    // Perform a dummy read of the password locations
    // if they match the key values, the CSM will unlock

    temp = CsmPwl.PSWD0;
    temp = CsmPwl.PSWD1;
    temp = CsmPwl.PSWD2;
    temp = CsmPwl.PSWD3;
    temp = CsmPwl.PSWD4;
    temp = CsmPwl.PSWD5;
    temp = CsmPwl.PSWD6;
    temp = CsmPwl.PSWD7;

    // If the CSM unlocked, return success, otherwise return
    // failure.
    if ( (CsmRegs.CSMSCR.all & 0x0001) == 0) return STATUS_SUCCESS;
    else return STATUS_FAIL_CSM_LOCKED;
}

/*------------------------------------------------------------------
   Example_ToggleTest

   This function shows example calls to the ToggleTest.

   This test is used to Toggle a GPIO pin at a known rate and thus
   confirm the frequency configuration of the API functions.

   A pin should be selected based on the hardware being used.

   Return Value: The toggle test does not return.  It will loop
                 forever and is used only for testing purposes.

   Notes:
----------------------------------------------------------------*/
void Example_ToggleTest(Uint16 PinNumber)
{
       Uint32 mask;

       // Before calling the Toggle Test, we must setup
       // the MUX and DIR registers.

       if(PinNumber > (Uint16)34)
       {
           asm("    ESTOP0");  // Stop here. Invalid option.
           for(;;);
       }

       // Pins GPIO16-GPIO31
       else if(PinNumber >= 32)
       {
           EALLOW;
           mask = ~( ((Uint32)1 << (PinNumber-16)*2) | ((Uint32)1 << (PinNumber-32)*2+1) );
           GpioCtrlRegs.GPBMUX1.all &= mask;
           GpioCtrlRegs.GPBDIR.all = GpioCtrlRegs.GPADIR.all | ((Uint32)1 << (PinNumber-32) );
           Flash_ToggleTest(&GpioDataRegs.GPBTOGGLE.all, ((Uint32)1 << PinNumber) );
           EDIS;
       }

       // Pins GPIO16-GPIO31
       else if(PinNumber >= 16)
       {
           EALLOW;
           mask = ~( ((Uint32)1 << (PinNumber-16)*2) | ((Uint32)1 << (PinNumber-16)*2+1) );
           GpioCtrlRegs.GPAMUX2.all &= mask;
           GpioCtrlRegs.GPADIR.all = GpioCtrlRegs.GPADIR.all | ((Uint32)1 << PinNumber);
           Flash_ToggleTest(&GpioDataRegs.GPATOGGLE.all, ((Uint32)1 << PinNumber) );
           EDIS;
       }

       // Pins GPIO0-GPIO15
       else
       {
           EALLOW;
           mask = ~( ((Uint32)1 << PinNumber*2) | ((Uint32)1 << PinNumber*2+1 ));
           GpioCtrlRegs.GPAMUX1.all &= mask;
           GpioCtrlRegs.GPADIR.all = GpioCtrlRegs.GPADIR.all | ((Uint32)1 << PinNumber);
           EDIS;
           Flash_ToggleTest(&GpioDataRegs.GPATOGGLE.all, ((Uint32)1 << PinNumber) );
       }
}


/*------------------------------------------------------------------
  Simple memory copy routine to move code out of flash into SARAM
-----------------------------------------------------------------*/
void Example_MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    {
       *DestAddr++ = *SourceAddr++;
    }
    return;
}


/*------------------------------------------------------------------
  For this example, if an error is found just stop here
-----------------------------------------------------------------*/
#pragma CODE_SECTION(Example_Error,"ramfuncs");
void Example_Error(Uint16 Status)
{
//  Error code will be in the AL register.
    asm("    ESTOP0");
    asm("    SB 0, UNC");
}


/*------------------------------------------------------------------
  For this example, once we are done just stop here
-----------------------------------------------------------------*/
#pragma CODE_SECTION(Example_Done,"ramfuncs");
void Example_Done(void)
{
    asm("    ESTOP0");
    asm("    SB 0, UNC");
}


/*------------------------------------------------------------------
  Callback function - must be executed from outside flash/OTP
-----------------------------------------------------------------*/
#pragma CODE_SECTION(MyCallbackFunction,"ramfuncs");
void MyCallbackFunction(void)
{
    // Toggle pin, service external watchdog etc
    MyCallbackCounter++;
    asm("    NOP");
}



