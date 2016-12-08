;----------------------------------------------------------------------------------
;	FILE:			PeripheralAddress_ASM.H
;
;	Description:	Generic Header file for 280x "EPeripheral" register addresses.
;
;	Version: 		1.01
;
;   Target:  		TMS320F280x 
;
;	Type: 			Device dependent
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2007
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date	     | Description
;----------------------------------------------------------------------------------
;  06/30/05  | Release 1.0  		New release.
;  07/21/05  | Release 1.01  		Added more ADC registers.
;  09/18/08  | Release 1.02		Added more ADC registers.
;----------------------------------------------------------------------------------
_DSP_DEVICE		.set 	28035

; EPWM
EPWM1_BASE		.set	0x6800
TBSTS1			.set 	EPWM1_BASE+0x1
TBPHSHR1		.set 	EPWM1_BASE+0x2
TBPHS1 			.set 	EPWM1_BASE+0x3
TBCTR1 			.set 	EPWM1_BASE+0x4
TBPRD1 			.set 	EPWM1_BASE+0x5
CMPAHR1			.set	EPWM1_BASE+0x8
CMPA1 			.set 	EPWM1_BASE+0x9
CMPB1 			.set 	EPWM1_BASE+0xA
DBRED1 			.set 	EPWM1_BASE+0x10
DBFED1 			.set 	EPWM1_BASE+0x11
TZSEL1 			.set 	EPWM1_BASE+0x12
TZCTL1 			.set 	EPWM1_BASE+0x14
TZEINT1 		.set 	EPWM1_BASE+0x15
TZFLG1 			.set 	EPWM1_BASE+0x16
TZCLR1 			.set 	EPWM1_BASE+0x17
TZFRC1 			.set 	EPWM1_BASE+0x18
ETSEL1 			.set 	EPWM1_BASE+0x19
ETPS1 			.set 	EPWM1_BASE+0x1A
ETFLG1 			.set 	EPWM1_BASE+0x1B
ETCLR1 			.set 	EPWM1_BASE+0x1C
ETFRC1 			.set 	EPWM1_BASE+0x1D

EPWM2_BASE		.set	0x6840
TBSTS2			.set 	EPWM2_BASE+0x1
TBPHSHR2		.set 	EPWM2_BASE+0x2
TBPHS2 			.set 	EPWM2_BASE+0x3
TBCTR2 			.set 	EPWM2_BASE+0x4
TBPRD2 			.set 	EPWM2_BASE+0x5
CMPAHR2			.set	EPWM2_BASE+0x8
CMPA2 			.set 	EPWM2_BASE+0x9
CMPB2 			.set 	EPWM2_BASE+0xA
DBRED2			.set 	EPWM2_BASE+0x10
DBFED2 			.set 	EPWM2_BASE+0x11
TZSEL2 			.set 	EPWM2_BASE+0x12
TZCTL2 			.set 	EPWM2_BASE+0x14
TZEINT2 		.set 	EPWM2_BASE+0x15
TZFLG2 			.set 	EPWM2_BASE+0x16
TZCLR2 			.set 	EPWM2_BASE+0x17
TZFRC2 			.set 	EPWM2_BASE+0x18
ETSEL2 			.set 	EPWM2_BASE+0x19
ETPS2 			.set 	EPWM2_BASE+0x1A
ETFLG2 			.set 	EPWM2_BASE+0x1B
ETCLR2 			.set 	EPWM2_BASE+0x1C
ETFRC2 			.set 	EPWM2_BASE+0x1D

EPWM3_BASE		.set	0x6880
TBSTS3			.set 	EPWM3_BASE+0x1
TBPHSHR3		.set 	EPWM3_BASE+0x2
TBPHS3 			.set 	EPWM3_BASE+0x3
TBCTR3 			.set 	EPWM3_BASE+0x4
TBPRD3 			.set 	EPWM3_BASE+0x5
CMPAHR3			.set	EPWM3_BASE+0x8
CMPA3 			.set 	EPWM3_BASE+0x9
CMPB3 			.set 	EPWM3_BASE+0xA
DBRED3 			.set 	EPWM3_BASE+0x10
DBFED3 			.set 	EPWM3_BASE+0x11
TZSEL3 			.set 	EPWM3_BASE+0x12
TZCTL3 			.set 	EPWM3_BASE+0x14
TZEINT3 		.set 	EPWM3_BASE+0x15
TZFLG3 			.set 	EPWM3_BASE+0x16
TZCLR3 			.set 	EPWM3_BASE+0x17
TZFRC3 			.set 	EPWM3_BASE+0x18
ETSEL3 			.set 	EPWM3_BASE+0x19
ETPS3 			.set 	EPWM3_BASE+0x1A
ETFLG3 			.set 	EPWM3_BASE+0x1B
ETCLR3 			.set 	EPWM3_BASE+0x1C
ETFRC3 			.set 	EPWM3_BASE+0x1D

EPWM4_BASE		.set	0x68C0
TBSTS4			.set 	EPWM4_BASE+0x1
TBPHSHR4		.set 	EPWM4_BASE+0x2
TBPHS4 			.set 	EPWM4_BASE+0x3
TBCTR4 			.set 	EPWM4_BASE+0x4
TBPRD4 			.set 	EPWM4_BASE+0x5
CMPAHR4			.set	EPWM4_BASE+0x8
CMPA4 			.set 	EPWM4_BASE+0x9
CMPB4 			.set 	EPWM4_BASE+0xA
DBRED4 			.set 	EPWM4_BASE+0x10
DBFED4 			.set 	EPWM4_BASE+0x11
TZSEL4 			.set 	EPWM4_BASE+0x12
TZCTL4 			.set 	EPWM4_BASE+0x14
TZEINT4 		.set 	EPWM4_BASE+0x15
TZFLG4 			.set 	EPWM4_BASE+0x16
TZCLR4 			.set 	EPWM4_BASE+0x17
TZFRC4 			.set 	EPWM4_BASE+0x18
ETSEL4 			.set 	EPWM4_BASE+0x19
ETPS4 			.set 	EPWM4_BASE+0x1A
ETFLG4 			.set 	EPWM4_BASE+0x1B
ETCLR4 			.set 	EPWM4_BASE+0x1C
ETFRC4 			.set 	EPWM4_BASE+0x1D

EPWM5_BASE		.set	0x6900
TBSTS5			.set 	EPWM5_BASE+0x1
TBPHSHR5		.set 	EPWM5_BASE+0x2
TBPHS5 			.set 	EPWM5_BASE+0x3
TBCTR5 			.set 	EPWM5_BASE+0x4
TBPRD5 			.set 	EPWM5_BASE+0x5
CMPAHR5		    .set	EPWM5_BASE+0x8
CMPA5 			.set 	EPWM5_BASE+0x9
CMPB5 			.set 	EPWM5_BASE+0xA
DBRED5 			.set 	EPWM5_BASE+0x10
DBFED5 			.set 	EPWM5_BASE+0x11
TZSEL5 			.set 	EPWM5_BASE+0x12
TZCTL5 			.set 	EPWM5_BASE+0x14
TZEINT5 	    .set 	EPWM5_BASE+0x15
TZFLG5 			.set 	EPWM5_BASE+0x16
TZCLR5 			.set 	EPWM5_BASE+0x17
TZFRC5 			.set 	EPWM5_BASE+0x18
ETSEL5 			.set 	EPWM5_BASE+0x19
ETPS5 			.set 	EPWM5_BASE+0x1A
ETFLG5 			.set 	EPWM5_BASE+0x1B
ETCLR5 			.set 	EPWM5_BASE+0x1C
ETFRC5 			.set 	EPWM5_BASE+0x1D

EPWM6_BASE		.set	0x6940
TBPHS6 			.set 	EPWM6_BASE+0x3
TBCTR6 			.set 	EPWM6_BASE+0x4
TBPRD6 			.set 	EPWM6_BASE+0x5
CMPA6			.set 	EPWM6_BASE+0x9
CMPB6 			.set 	EPWM6_BASE+0xA
DBRED6 			.set 	EPWM6_BASE+0x10
DBFED6 			.set 	EPWM6_BASE+0x11
TZSEL6 			.set 	EPWM6_BASE+0x12
TZCTL6 			.set 	EPWM6_BASE+0x14
TZEINT6 		.set 	EPWM6_BASE+0x15
TZFLG6 			.set 	EPWM6_BASE+0x16
TZCLR6			.set 	EPWM6_BASE+0x17
TZFRC6 			.set 	EPWM6_BASE+0x18
ETSEL6 			.set 	EPWM6_BASE+0x19
ETPS6 			.set 	EPWM6_BASE+0x1A
ETFLG6 			.set 	EPWM6_BASE+0x1B
ETCLR6 			.set 	EPWM6_BASE+0x1C
ETFRC6 			.set 	EPWM6_BASE+0x1D

EPWM7_BASE		.set	0x6980
TBPHSHR7		.set 	EPWM7_BASE+0x2
TBPHS7 			.set 	EPWM7_BASE+0x3
TBCTR7 			.set 	EPWM7_BASE+0x4
TBPRD7 			.set 	EPWM7_BASE+0x5
CMPAHR7			.set	EPWM7_BASE+0x8
CMPA7 			.set 	EPWM7_BASE+0x9
CMPB7 			.set 	EPWM7_BASE+0xA
DBRED7 			.set 	EPWM7_BASE+0x10
DBFED7 			.set 	EPWM7_BASE+0x11
TZSEL7 			.set 	EPWM7_BASE+0x12
TZCTL7 			.set 	EPWM7_BASE+0x14
TZEINT7 		.set 	EPWM7_BASE+0x15
TZFLG7 			.set 	EPWM7_BASE+0x16
TZCLR7 			.set 	EPWM7_BASE+0x17
TZFRC7 			.set 	EPWM7_BASE+0x18
ETSEL7 			.set 	EPWM7_BASE+0x19
ETPS7 			.set 	EPWM7_BASE+0x1A
ETFLG7 			.set 	EPWM7_BASE+0x1B
ETCLR7 			.set 	EPWM7_BASE+0x1C
ETFRC7 			.set 	EPWM7_BASE+0x1D

EPWM8_BASE		.set	0x69C0
TBPHSHR8		.set 	EPWM8_BASE+0x2
TBPHS8 			.set 	EPWM8_BASE+0x3
TBCTR8 			.set 	EPWM8_BASE+0x4
TBPRD8 			.set 	EPWM8_BASE+0x5
CMPAHR8			.set	EPWM8_BASE+0x8
CMPA8 			.set 	EPWM8_BASE+0x9
CMPB8 			.set 	EPWM8_BASE+0xA
DBRED8 			.set 	EPWM8_BASE+0x10
DBFED8 			.set 	EPWM8_BASE+0x11
TZSEL8 			.set 	EPWM8_BASE+0x12
TZCTL8 			.set 	EPWM8_BASE+0x14
TZEINT8 		.set 	EPWM8_BASE+0x15
TZFLG8 			.set 	EPWM8_BASE+0x16
TZCLR8 			.set 	EPWM8_BASE+0x17
TZFRC8 			.set 	EPWM8_BASE+0x18
ETSEL8 			.set 	EPWM8_BASE+0x19
ETPS8 			.set 	EPWM8_BASE+0x1A
ETFLG8 			.set 	EPWM8_BASE+0x1B
ETCLR8 			.set 	EPWM8_BASE+0x1C
ETFRC8 			.set 	EPWM8_BASE+0x1D

EPWM9_BASE		.set	0x6600
TBPHSHR9		.set 	EPWM9_BASE+0x2
TBPHS9 			.set 	EPWM9_BASE+0x3
TBCTR9 			.set 	EPWM9_BASE+0x4
TBPRD9 			.set 	EPWM9_BASE+0x5
CMPAHR9			.set	EPWM9_BASE+0x8
CMPA9 			.set 	EPWM9_BASE+0x9
CMPB9 			.set 	EPWM9_BASE+0xA
DBRED9 			.set 	EPWM9_BASE+0x10
DBFED9 			.set 	EPWM9_BASE+0x11
TZSEL9 			.set 	EPWM9_BASE+0x12
TZCTL9 			.set 	EPWM9_BASE+0x14
TZEINT9 		.set 	EPWM9_BASE+0x15
TZFLG9 			.set 	EPWM9_BASE+0x16
TZCLR9 			.set 	EPWM9_BASE+0x17
TZFRC9 			.set 	EPWM9_BASE+0x18
ETSEL9 			.set 	EPWM9_BASE+0x19
ETPS9 			.set 	EPWM9_BASE+0x1A
ETFLG9 			.set 	EPWM9_BASE+0x1B
ETCLR9 			.set 	EPWM9_BASE+0x1C
ETFRC9 			.set 	EPWM9_BASE+0x1D

;   EPWM7       : origin = 0x006980, length = 0x000022     /* Enhanced PWM 7 registers */
;   EPWM8       : origin = 0x0069C0, length = 0x000022     /* Enhanced PWM 8 registers */
;   EPWM9       : origin = 0x006600, length = 0x000022     /* Enhanced PWM 9 registers */
;   EPWM10      : origin = 0x006640, length = 0x000022     /* Enhanced PWM 10 registers */
;   EPWM11      : origin = 0x006680, length = 0x000022     /* Enhanced PWM 11 registers */
;   EPWM12      : origin = 0x0066C0, length = 0x000022     /* Enhanced PWM 12 registers */
;   EPWM13      : origin = 0x006700, length = 0x000022     /* Enhanced PWM 13 registers */
;   EPWM14      : origin = 0x006740, length = 0x000022     /* Enhanced PWM 14 registers */
;   EPWM15      : origin = 0x006780, length = 0x000022     /* Enhanced PWM 15 registers */
;   EPWM16      : origin = 0x0067C0, length = 0x000022     /* Enhanced PWM 16 registers */

; ECAP
;=======================================
ECAP1_BASE		.set	0x6A00
TSCTR1			.set 	ECAP1_BASE+0x0
CTRPHS1			.set 	ECAP1_BASE+0x2
CAP11 			.set 	ECAP1_BASE+0x4
CAP21 			.set 	ECAP1_BASE+0x6
CAP31			.set	ECAP1_BASE+0x8
CAP41			.set	ECAP1_BASE+0xA
ECCTL11			.set	ECAP1_BASE+0x14
ECCTL21			.set	ECAP1_BASE+0x15
ECFLG1			.set	ECAP1_BASE+0x17
ECCLR1			.set	ECAP1_BASE+0x18
;---------------------------------------
ECAP2_BASE		.set	0x6A20
TSCTR2			.set 	ECAP2_BASE+0x0
CTRPHS2			.set 	ECAP2_BASE+0x2
CAP12 			.set 	ECAP2_BASE+0x4
CAP22 			.set 	ECAP2_BASE+0x6
CAP32			.set	ECAP2_BASE+0x8
CAP42			.set	ECAP2_BASE+0xA
ECCTL12			.set	ECAP2_BASE+0x14
ECCTL22			.set	ECAP2_BASE+0x15
ECFLG2			.set	ECAP2_BASE+0x17
ECCLR2			.set	ECAP2_BASE+0x18
;---------------------------------------
ECAP3_BASE		.set	0x6A40
TSCTR3			.set 	ECAP3_BASE+0x0
CTRPHS3			.set 	ECAP3_BASE+0x2
CAP13 			.set 	ECAP3_BASE+0x4
CAP23 			.set 	ECAP3_BASE+0x6
CAP33			.set	ECAP3_BASE+0x8
CAP43			.set	ECAP3_BASE+0xA
ECCTL13			.set	ECAP3_BASE+0x14
ECCTL23			.set	ECAP3_BASE+0x15
ECFLG3			.set	ECAP3_BASE+0x17
ECCLR3			.set	ECAP3_BASE+0x18
;---------------------------------------
ECAP4_BASE		.set	0x6A60
TSCTR4			.set 	ECAP4_BASE+0x0
CTRPHS4			.set 	ECAP4_BASE+0x2
CAP14 			.set 	ECAP4_BASE+0x4
CAP24 			.set 	ECAP4_BASE+0x6
CAP34			.set	ECAP4_BASE+0x8
CAP44			.set	ECAP4_BASE+0xA
ECCTL14			.set	ECAP4_BASE+0x14
ECCTL24			.set	ECAP4_BASE+0x15
ECFLG4			.set	ECAP4_BASE+0x17
ECCLR4			.set	ECAP4_BASE+0x18
;---------------------------------------
ECAP5_BASE		.set	0x6A80
TSCTR5			.set 	ECAP5_BASE+0x0
CTRPHS5			.set 	ECAP5_BASE+0x2
CAP15 			.set 	ECAP5_BASE+0x4
CAP25 			.set 	ECAP5_BASE+0x6
CAP35			.set	ECAP5_BASE+0x8
CAP45			.set	ECAP5_BASE+0xA
ECCTL15			.set	ECAP5_BASE+0x14
ECCTL25			.set	ECAP5_BASE+0x15
ECFLG5			.set	ECAP5_BASE+0x17
ECCLR5			.set	ECAP5_BASE+0x18
;---------------------------------------
ECAP6_BASE		.set	0x6AA0
TSCTR6			.set 	ECAP6_BASE+0x0
CTRPHS6			.set 	ECAP6_BASE+0x2
CAP16 			.set 	ECAP6_BASE+0x4
CAP26 			.set 	ECAP6_BASE+0x6
CAP36			.set	ECAP6_BASE+0x8
CAP46			.set	ECAP6_BASE+0xA
ECCTL16			.set	ECAP6_BASE+0x14
ECCTL26			.set	ECAP6_BASE+0x15
ECFLG6			.set	ECAP6_BASE+0x17
ECCLR6			.set	ECAP6_BASE+0x18
;---------------------------------------



; ADC
ADCCTL1 		.set 	0x7100


;ADCMAXCONV		.set	0x7102
;ADCASEQSR		.set	0x7107
;ADCREFSEL		.set	0x711C
;ADCOFFTRIM		.set	0x711D
;ADCCHSELSEQ1	.set	0x7103
;ADCCHSELSEQ2	.set	0x7104
;ADCCHSELSEQ3	.set	0x7105
;ADCCHSELSEQ4	.set	0x7106
;ADCST 			.set 	0x7119
;INT_SEQ1_CLR 	.set 	0x0010

ADCRESULT0 		.set 	0x7108
ADCRESULT1 		.set 	0x7109
ADCRESULT2 		.set 	0x710A
ADCRESULT3 		.set 	0x710B
ADCRESULT4 		.set 	0x710C
ADCRESULT5 		.set 	0x710D
ADCRESULT6 		.set 	0x710E
ADCRESULT7 		.set 	0x710F
ADCRESULT8 		.set 	0x7110
ADCRESULT9 		.set 	0x7111
ADCRESULT10 	.set 	0x7112
ADCRESULT11 	.set 	0x7113
ADCRESULT12 	.set 	0x7114
ADCRESULT13 	.set 	0x7115
ADCRESULT14 	.set 	0x7116
ADCRESULT15 	.set 	0x7117

ADCPF0R0 		.set 	0x0B00
ADCPF0R1 		.set 	0x0B01
ADCPF0R2 		.set 	0x0B02
ADCPF0R3 		.set 	0x0B03
ADCPF0R4 		.set 	0x0B04
ADCPF0R5 		.set 	0x0B05
ADCPF0R6 		.set 	0x0B06
ADCPF0R7 		.set 	0x0B07
ADCPF0R8 		.set 	0x0B08
ADCPF0R9 		.set 	0x0B09
ADCPF0R10 		.set 	0x0B0A
ADCPF0R11 		.set 	0x0B0B
ADCPF0R12 		.set 	0x0B0C
ADCPF0R13 		.set 	0x0B0D
ADCPF0R14 		.set 	0x0B0E
ADCPF0R15 		.set 	0x0B0F

;SPI
;=======================================
SPIA_BASE		.set	0x7740
SPIACCR			.set 	SPIA_BASE+0x0
SPIACTL			.set 	SPIA_BASE+0x1
SPIAST			.set 	SPIA_BASE+0x2

SPIARXBUF		.set 	SPIA_BASE+0x7
SPIATXBUF		.set 	SPIA_BASE+0x8
SPIADAT			.set 	SPIA_BASE+0x9
;---------------------------------------
SPIB_BASE		.set	0x7750
SPIBCCR			.set 	SPIB_BASE+0x0
SPIBCTL			.set 	SPIB_BASE+0x1
SPIBST			.set 	SPIB_BASE+0x2

SPIBRXBUF		.set 	SPIB_BASE+0x7
SPIBTXBUF		.set 	SPIB_BASE+0x8
SPIBDAT			.set 	SPIB_BASE+0x9
;---------------------------------------
SPIC_BASE		.set	0x7760
SPICCCR			.set 	SPIC_BASE+0x0
SPICCTL			.set 	SPIC_BASE+0x1
SPICST			.set 	SPIC_BASE+0x2

SPICRXBUF		.set 	SPIC_BASE+0x7
SPICTXBUF		.set 	SPIC_BASE+0x8
SPICDAT			.set 	SPIC_BASE+0x9
;---------------------------------------
SPID_BASE		.set	0x7780
SPIDCCR			.set 	SPID_BASE+0x0
SPIDCTL			.set 	SPID_BASE+0x1
SPIDST			.set 	SPID_BASE+0x2

SPIDRXBUF		.set 	SPID_BASE+0x7
SPIDTXBUF		.set 	SPID_BASE+0x8
SPIDDAT			.set 	SPID_BASE+0x9
;---------------------------------------

;McBSP
;=======================================
McBSPA_BASE		.set	0x5000
DRR2A			.set 	McBSPA_BASE+0x0
DRR1A			.set 	McBSPA_BASE+0x1
DXR2A			.set 	McBSPA_BASE+0x2
DXR1A			.set 	McBSPA_BASE+0x3
SPCR2A			.set 	McBSPA_BASE+0x4
SPCR1A			.set 	McBSPA_BASE+0x5
RCR2A			.set 	McBSPA_BASE+0x6
RCR1A			.set 	McBSPA_BASE+0x7
XCR2A			.set 	McBSPA_BASE+0x8
XCR1A			.set 	McBSPA_BASE+0x9
SRGR2A			.set 	McBSPA_BASE+0xA
SRGR1A			.set 	McBSPA_BASE+0xB
;---------------------------------------
McBSPB_BASE		.set	0x5040
DRR2B			.set 	McBSPB_BASE+0x0
DRR1B			.set 	McBSPB_BASE+0x1
DXR2B			.set 	McBSPB_BASE+0x2
DXR1B			.set 	McBSPB_BASE+0x3
SPCR2B			.set 	McBSPB_BASE+0x4
SPCR1B			.set 	McBSPB_BASE+0x5
RCR2B			.set 	McBSPB_BASE+0x6
RCR1B			.set 	McBSPB_BASE+0x7
XCR2B			.set 	McBSPB_BASE+0x8
XCR1B			.set 	McBSPB_BASE+0x9
SRGR2B			.set 	McBSPB_BASE+0xA
SRGR1B			.set 	McBSPB_BASE+0xB
;---------------------------------------

; Interrupts
PIEACK 			.set 	0x0CE1
PIEACK_GROUP1   .set	0x0001
PIEACK_GROUP2   .set 	0x0002
PIEACK_GROUP3   .set 	0x0004
PIEACK_GROUP4   .set 	0x0008
PIEACK_GROUP5   .set 	0x0010
PIEACK_GROUP6   .set 	0x0020
PIEACK_GROUP7   .set 	0x0040
PIEACK_GROUP8   .set 	0x0080
PIEACK_GROUP9   .set 	0x0100
PIEACK_GROUP10  .set 	0x0200
PIEACK_GROUP11  .set 	0x0400
PIEACK_GROUP12  .set 	0x0800

; GPIO Port B
GPBMUX1 		.set 	0x6F96
GPBDIR 			.set 	0x6F9A
GPBDAT			.set 	0x6FC8
GPBSET 			.set 	0x6FCA
GPBCLEAR		.set 	0x6FCC
GPBTOGGLE		.set 	0x6FCE


CONTEXT_SAVE 	.macro		
			PUSH AR1H:AR0H ; 32-bit
			PUSH XAR2 ; 32-bit
			PUSH XAR3 ; 32-bit
			PUSH XAR4 ; 32-bit
			PUSH XAR5 ; 32-bit
			PUSH XAR6 ; 32-bit
			PUSH XAR7 ; 32-bit
			PUSH XT ; 32-bit
		.endm
		
CONTEXT_REST		.macro
			POP XT
			POP XAR7
			POP XAR6
			POP XAR5
			POP XAR4
			POP XAR3
			POP XAR2
			POP AR1H:AR0H
		.endm







