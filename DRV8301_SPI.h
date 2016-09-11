//============================================================================
//============================================================================
//
// FILE:	DRV8301_SPI.h
//
// TITLE:	Header file for DRV8301 SPI comm functions
// 
// Version: 1.0 	
//
// Date: 	24 May 2011
//
//============================================================================
//============================================================================

// DRV8301 SPI Input Data bit definitions:
struct  DRV8301_SPI_WRITE_WORD_BITS {       // bit    	description
   Uint16 DATA:11;          				// 10:0		FIFO reset
   Uint16 ADDRESS:4;        				// 14:11	Enhancement enable
   Uint16 R_W:1;          					// 15		R/W
};

union DRV8301_SPI_WRITE_WORD_REG {
   Uint16               				all;
   struct DRV8301_SPI_WRITE_WORD_BITS	bit;
};

// DRV8301 SPI Status Reister 1 bit definitions:
struct  DRV8301_STATUS_REG_1_BITS {		// bit    	description
   Uint16 FETLC_OC:1;					// 0		Phase C, low-side FET OC
   Uint16 FETHC_OC:1;					// 1		Phase C, high-side FET OC
   Uint16 FETLB_OC:1;					// 2		Phase B, low-side FET OC
   Uint16 FETHB_OC:1;					// 3		Phase B, high-side FET OC
   Uint16 FETLA_OC:1;					// 4		Phase A, low-side FET OC
   Uint16 FETHA_OC:1;					// 5		Phase A, high-side FET OC
   Uint16 OTW:1;	        			// 6		Over-temperature warning
   Uint16 OTSD:1;	          			// 7		Over-temperature shut down
   Uint16 PVDD_UV:1;					// 8		PVDD < 6V
   Uint16 GVDD_UV:1;					// 9		GVDD < 8V
   Uint16 FAULT:1;						// 10		FAULTn pin is asserted
   Uint16 Reserved:5;					// 15:11 
};

union DRV8301_STATUS_REG_1 {
   Uint16               			all;
   struct DRV8301_STATUS_REG_1_BITS	bit;
};

// DRV8301 SPI Status Reister 2 bit definitions:
struct  DRV8301_STATUS_REG_2_BITS {		// bit    	description
   Uint16 DEVICE_ID:4;					// 3:0		Device ID
   Uint16 Reserved1:3;					// 6:4
   Uint16 GVDD_OV:1;					// 7		GVDD > 16V
   Uint16 Reserved2:8;					// 15:8 
};

union DRV8301_STATUS_REG_2 {
   Uint16               			all;
   struct DRV8301_STATUS_REG_2_BITS	bit;
};

// DRV8301 SPI Control Reister 1 bit definitions:
struct  DRV8301_CONTROL_REG_1_BITS {	// bit    	description
   Uint16 GATE_CURRENT:2;				// 1:0		Gate driver peak current, 1.7A (00b), 0.7A (01b), 0.25A (10b), Reserved (11b)
   Uint16 GATE_RESET:1;        			// 2		Reset all latched faults (1), Normal Mode (0)
   Uint16 PWM_MODE:1;          			// 3		Three (1) or six (0) pwm inputs
   Uint16 OC_MODE:2;					// 5:4		over-current mode, current limit (00b), latched shut down (01b), Report only (10b), OC disabled (11b)
   Uint16 OC_ADJ_SET:5;					// 10:6		Set Vds trip point for OC see the table in the datasheet
   Uint16 Reserved:5;					// 15:11 
};

union DRV8301_CONTROL_REG_1 {
   Uint16               				all;
   struct DRV8301_CONTROL_REG_1_BITS	bit;
};

// DRV8301 SPI Control Reister 2 bit definitions:
struct  DRV8301_CONTROL_REG_2_BITS {	// bit    	description
   Uint16 OCTW_SET:2;					// 1:0		Report OT and OC (00b), Report OT (01b), Report OC (10b), Reserved (11b)
   Uint16 GAIN:2;        				// 3:2		Gain of shunt amplifier, 10 (00b), 20 (01b), 40 (10b), 80 (11b)
   Uint16 DC_CAL_CH1:1;        			// 4		Shunt amplifier inputs shorted and disconnected from load (1) or shunt amplifier inputs connected to load (0)
   Uint16 DC_CAL_CH2:1;        			// 5		Shunt amplifier inputs shorted and disconnected from load (1) or shunt amplifier inputs connected to load (0)
   Uint16 OC_TOFF:1;					// 6		Normal CBC operation (0), off time control during OC (1)
   Uint16 Reserved:9;					// 15:7 
};

union DRV8301_CONTROL_REG_2 {
   Uint16               				all;
   struct DRV8301_CONTROL_REG_2_BITS	bit;
};

/***************************************************************************************************/
//defines
/***************************************************************************************************/
//DRV8301 Register Addresses
#define STAT_REG_1_ADDR		0x00
#define STAT_REG_2_ADDR		0x01
#define CNTRL_REG_1_ADDR	0x02
#define CNTRL_REG_2_ADDR	0x03

/***************************************************************************************************/
//function prototypes
/***************************************************************************************************/
void DRV8301_SPI_Init(volatile struct SPI_REGS *s);
Uint16 DRV8301_SPI_Read(volatile struct SPI_REGS *s, Uint16 address);
Uint16 DRV8301_SPI_Write(volatile struct SPI_REGS *s, Uint16 address, Uint16 data);

