/*==================================================================================*/
/*	User specific Linker command file for running from RAM							*/
/*==================================================================================*/
/*	FILE:			F28069_RAM_2xPM_Sensorless.CMD                                  */
/*                                                                                  */
/*	Description:	Linker command file for User custom sections targetted to run   */
/*					from RAM.  			                                            */
/*                                                                                  */
/*  Target:  		TMS320F2806x					                                */
/*                                                                                  */
/*	Version: 		1.0                                 							*/
/*                                                                                  */
/*----------------------------------------------------------------------------------*/
/*  Copyright Texas Instruments © 2010                                			    */	
/*----------------------------------------------------------------------------------*/
/*  Revision History:                                                               */
/*----------------------------------------------------------------------------------*/
/*  Date	  | Description                                                         */
/*----------------------------------------------------------------------------------*/
/*  01/11/11  | Release 1.0  		 			                                    */
/*----------------------------------------------------------------------------------*/


/* Define the memory block start/length for the DSP2802x 
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes: 
         Memory blocks on F2806x are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.  
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program 
         and/or data. 
         
         The L0 memory blocks is mirrored - that is
         it can be accessed in high memory or low memory.
         For simplicity only one instance is used in this
         linker file. 
         
         Contiguous SARAM memory blocks can be combined 
         if required to create a larger memory block. 
*/

MEMORY
{
PAGE 0 :
   
	BEGIN		: origin = 0x000000,	length = 0x000002
	BOOT_RSVD	: origin = 0x000002,	length = 0x00004E             
	RAMM0		: origin = 0x000050,	length = 0x0003B0
	progRAM		: origin = 0x008000,	length = 0x001800

	FPUTABLES   : origin = 0x3FD860, length = 0x0006A0	   /* FPU Tables in Boot ROM */
   	IQTABLES   	: origin = 0x3FDF00, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   	IQTABLES2  	: origin = 0x3FEA50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   	IQTABLES3  	: origin = 0x3FEADC, length = 0x0000AA	   /* IQ Math Tables in Boot ROM */

    BOOTROM    	: origin = 0x3FF3B0, length = 0x000C10

	RESET       : origin = 0x3FFFC0, 	length = 0x000002               

         
PAGE 1 : 

	RAMM1		: origin = 0x000480,	length = 0x000380
	dataRAM		: origin = 0x009800,	length = 0x000800
}
 
 
SECTIONS
{

   codestart        : > BEGIN,      PAGE = 0
   ramfuncs         : > progRAM,       PAGE = 0  

   .text            : > progRAM,     PAGE = 0

   .cinit           : > RAMM0,      PAGE = 0
   .pinit           : > RAMM0,      PAGE = 0
   .switch          : > RAMM0,      PAGE = 0
   .reset           : > RESET,      PAGE = 0, TYPE = DSECT
   
   .stack           : > RAMM1,      PAGE = 1

   .ebss            : > dataRAM,     PAGE = 1
   .econst          : > dataRAM,     PAGE = 1      

   .esysmem         : > RAMM1,      PAGE = 1

   IQmath           : >  progRAM,   PAGE = 0
   IQmathTables     : >  IQTABLES, 	PAGE = 0, TYPE = NOLOAD
   FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD
}

   
SECTIONS
{
	DLOG: > dataRAM,PAGE=1
}



 
