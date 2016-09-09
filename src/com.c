/*************************************************************
 * com.c
 *
 *  Created on: 2013-5-4
 *      Author: 芯源电子工作室
 *************************************************************/

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File
#include "com.h"

volatile Uint16 comTXRd = 0;
volatile Uint16 comTXWr = 0;
volatile Uint16 comTXLen = 0;
char comTXBuf[COM_TXBUFLEN];

void comInit(Uint16 baud)
{
    SciaRegs.SCICCR.bit.SCICHAR = 7;
    SciaRegs.SCICTL1.bit.TXENA  = 1;
    SciaRegs.SCIHBAUD = baud >> 8;
    SciaRegs.SCILBAUD = baud;
    SciaRegs.SCICTL1.bit.SWRESET = 1;
}

void comPutChar(char data)
{
    if (comTXLen < COM_TXBUFLEN)
    {
        comTXBuf[comTXWr++] = data;
        if (comTXWr >= COM_TXBUFLEN)
            comTXWr = 0;
        comTXLen++;
    }
}

void comPutString(char *str)
{
    while (*str != '\0')
    {
        comPutChar(*str);
        str++;
    }
}

void comTXD(void)
{
    if ((comTXLen > 0) && (SciaRegs.SCICTL2.bit.TXRDY == 1))
    {
        SciaRegs.SCITXBUF = comTXBuf[comTXRd++];
        if (comTXRd >= COM_TXBUFLEN)
            comTXRd = 0;
        comTXLen--;
    }
}
