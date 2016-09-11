//============================================================================
//============================================================================
//
// FILE:	DRV8301_SPI.c
//
// TITLE:	DRV8301 SPI comm functions
// 
// Version: 1.0 	
//
// Date: 	24 May 2011
//
//============================================================================
//============================================================================
#include "PeripheralHeaderIncludes.h"
#include "DRV8301_SPI.h"

/*****************************************************************************/
// Initialize the SPI peripheral
/*****************************************************************************/
void DRV8301_SPI_Init(volatile struct SPI_REGS *s)
{
	s->SPICCR.bit.SPISWRESET = 0; 		// Put SPI in reset state
	s->SPICCR.bit.SPICHAR = 0xF;		// 16-bit character
	s->SPICCR.bit.SPILBK = 0;     		// loopback off
	s->SPICCR.bit.CLKPOLARITY = 0;  	// Rising edge without delay

	s->SPICTL.bit.SPIINTENA = 0;		// disable SPI interrupt
	s->SPICTL.bit.TALK = 1;				// enable transmission
	s->SPICTL.bit.MASTER_SLAVE = 1;		// master
	s->SPICTL.bit.CLK_PHASE = 0;    	// Rising edge without delay
	s->SPICTL.bit.OVERRUNINTENA = 0;	// disable reciever overrun interrupt
	
	s->SPIBRR = 0;						// SPICLK = LSPCLK / 4 (max SPICLK)

	s->SPICCR.bit.SPISWRESET=1;  		// Enable SPI
}

/*****************************************************************************/
// Read from a DRV8301 Register
/*****************************************************************************/
Uint16 DRV8301_SPI_Read(volatile struct SPI_REGS *s, Uint16 address)
{
	union DRV8301_SPI_WRITE_WORD_REG w;
	volatile Uint16 dummy;
	
	w.bit.R_W = 1;							//we are initiating a read
	w.bit.ADDRESS = address;				//load the address
	w.bit.DATA = 0;							//dummy data;
	
	s->SPITXBUF = w.all;					//send out the data
	
	while(s->SPISTS.bit.INT_FLAG == 0);		//wait for the packet to complete
	
	dummy = s->SPIRXBUF;					//dummy read to clear the INT_FLAG bit
	
	w.bit.R_W = 1;							//we are initiating a read
	w.bit.ADDRESS = address;				//load the address
	w.bit.DATA = 0;							//dummy data;
	
	s->SPITXBUF = w.all;					//send out the data
	
	while(s->SPISTS.bit.INT_FLAG == 0);		//wait for the packet to complete
	
	dummy = s->SPIRXBUF;					//dummy read to clear the INT_FLAG bit

	return(dummy);
	
}

/*****************************************************************************/
// Write to a DRV8301 Register
// SPI writes always clock out the data in Status Register 1.
// Since it's available we'll return the status from this function
/*****************************************************************************/
Uint16 DRV8301_SPI_Write(volatile struct SPI_REGS *s, Uint16 address, Uint16 data)
{
	union DRV8301_SPI_WRITE_WORD_REG w;
	volatile Uint16 stat_reg1;
	
	w.bit.R_W = 0;							//we are initiating a write
	w.bit.ADDRESS = address;				//load the address
	w.bit.DATA = data;						//data to be written;
	
	s->SPITXBUF = w.all;					//send out the data
	
	while(s->SPISTS.bit.INT_FLAG == 0);		//wait for the packet to complete
	
	stat_reg1 = s->SPIRXBUF;				//read returned value of Status Register 1 and clear the INT_FLAG bit
	
	return(stat_reg1);
	
}
