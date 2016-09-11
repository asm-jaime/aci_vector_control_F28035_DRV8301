/*==================================================================================*/
/*	User specific Linker command file for running from RAM							*/
/*==================================================================================*/
/*	FILE:			F28035_RAM_2xPM_Sensorless.CMD                                  */
/*                                                                                  */
/*	Description:	Linker command file for User custom sections targetted to run   */
/*					from RAM.  			                                            */
/*                                                                                  */
/*  Target:  		TMS320F28035 device                                             */
/*                                                                                  */
/*	Version: 		1.00                                							*/
/*                                                                                  */
/*----------------------------------------------------------------------------------*/
/*  Copyright Texas Instruments © 2009                                			    */	
/*----------------------------------------------------------------------------------*/
/*  Revision History:                                                               */
/*----------------------------------------------------------------------------------*/
/*  Date	  | Description                                                         */
/*----------------------------------------------------------------------------------*/
/*  10/24/08  | Release 1.0  		New release.                                    */
/*----------------------------------------------------------------------------------*/

/* Define the memory block start/length for the DSP2803x
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes:
         Memory blocks on F28035 are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program
         and/or data.

         L0 block is mirrored - that is it
         can be accessed in high memory or low memory.
         For simplicity only one instance is used in this
         linker file.

         Contiguous SARAM memory blocks can be combined
         if required to create a larger memory block.
*/

MEMORY
{
PAGE 0 :
/* Note that the memory allocation below does not create sections as necessary for
   the CLA on the F2803x. 
*/
   
	BEGIN		   : origin = 0x000000,	length = 0x000002
	BOOT_RSVD	   : origin = 0x000002,	length = 0x00004E             
	RAMM0		   : origin = 0x000050,	length = 0x0003B0

	progRAM		   : origin = 0x008000,	length = 0x001800

	IQTABLES       : origin = 0x3FE000, length = 0x000B50    /* IQ Math Tables in Boot ROM */
	IQTABLES2      : origin = 0x3FEB50, length = 0x00008C    /* IQ Math Tables in Boot ROM */
	IQTABLES3      : origin = 0x3FEBDC, length = 0x0000AA	 /* IQ Math Tables in Boot ROM */

	RESET          : origin = 0x3FFFC0, length = 0x000002
	BOOTROM        : origin = 0x3FF27C, length = 0x000D44               

         
PAGE 1 : 

	RAMM1		   : origin = 0x000480,	length = 0x000380

	dataRAM	 	   : origin = 0x009800,	length = 0x000800

	CLA_CPU_MSGRAM : origin = 0x001480, length = 0x000080
	CPU_CLA_MSGRAM : origin = 0x001500, length = 0x000080
}
 
 
SECTIONS
{
   codestart        : > BEGIN,      PAGE = 0
   ramfuncs         : > RAMM0,      PAGE = 0  

   .text            : > progRAM,    PAGE = 0

   .cinit           : > RAMM0,      PAGE = 0
   .pinit           : > RAMM0,      PAGE = 0
   .switch          : > RAMM0,      PAGE = 0
   .reset           : > RESET,      PAGE = 0, TYPE = DSECT
   
   .stack           : > RAMM1,      PAGE = 1

   .ebss            : > dataRAM,    PAGE = 1
   .econst          : > dataRAM,    PAGE = 1      

   .esysmem         : > RAMM1,      PAGE = 1

   IQmath           : > progRAM,    PAGE = 0
   IQmathTables     : > IQTABLES, 	PAGE = 0, TYPE = NOLOAD

   Cla1ToCpuMsgRAM  : > CLA_CPU_MSGRAM, PAGE = 1
   CpuToCla1MsgRAM  : > CPU_CLA_MSGRAM, PAGE = 1

 /* Uncomment the section below if calling the IQNexp() or IQexp()
      functions from the IQMath.lib library in order to utilize the
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD
   {

              IQmath.lib<IQNexpTable.obj> (IQmathTablesRam)

   }
   */
   /* Uncomment the section below if calling the IQNasin() or IQasin()
      functions from the IQMath.lib library in order to utilize the
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables3    : > IQTABLES3, PAGE = 0, TYPE = NOLOAD
   {

              IQmath.lib<IQNasinTable.obj> (IQmathTablesRam)

   }
   */

}


    
SECTIONS
{
	DLOG: > dataRAM,PAGE=1
}


 
