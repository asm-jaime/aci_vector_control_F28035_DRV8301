/**
  ******************************************************************************
  * @file    main.c
  * @author  asm.jaime
  * @version V0.0
  * @date    2007
  * @brief   aci_vector_control
  ******************************************************************************
  * @attention
  *
  * board   :DRV8301
  * href    :https://
  *
  ******************************************************************************
  */

#include "DSP28x_Project.h"		// Device Header file and Examples Include File
#include "main.h"

union DRV8301_STATUS_REG_1	DRV8301_stat_reg1;
union DRV8301_STATUS_REG_2	DRV8301_stat_reg2;
union DRV8301_CONTROL_REG_1	DRV8301_cntrl_reg1;
union DRV8301_CONTROL_REG_2	DRV8301_cntrl_reg2;

#ifdef FLASH
#pragma CODE_SECTION(MainISR, "ramfuncs");
#endif

// Prototype statements for functions found within this file.
interrupt void MainISR(void);
void DRV8301_Configuration(void);
void Module_Init(void);

// Global variables used in this system
_iq VdTesting = _IQ(0.0);			// Vd reference (pu)
_iq VqTesting = _IQ(0.02);			// Vq reference (pu)

_iq IdRef = _IQ(0.0);				// Id reference (pu)
_iq IqRef = _IQ(0.05);				// Iq reference (pu)
_iq SpeedRef = _IQ(0.0);			// Speed reference (pu)

_iq cal_offset_A = _IQ15(0.4975);	//F28035
_iq cal_offset_B = _IQ15(0.4975);	//F28035
_iq cal_filt_gain;

float32 T = 0.001/ISR_FREQUENCY;    // Samping period (sec), see parameter.h

#ifdef SARAM
int DlogCh1 = 0;
int DlogCh2 = 0;
int DlogCh3 = 0;
int DlogCh4 = 0;
#endif

Uint16 RunMotor = FALSE;

Uint16 SpeedLoopPrescaler = 10;      // Speed loop prescaler
Uint16 SpeedLoopCount = 1;           // Speed loop counter

// Instance a few transform objects
CLARKE clarke1 = CLARKE_DEFAULTS;
PARK park1 = PARK_DEFAULTS;
IPARK ipark1 = IPARK_DEFAULTS;

// Instance PID regulators to regulate the d and q  axis currents, and speed
PID_GRANDO_CONTROLLER pid1_id = {PID_TERM_DEFAULTS,PID_PARAM_DEFAULTS,PID_DATA_DEFAULTS};
PID_GRANDO_CONTROLLER pid1_iq = {PID_TERM_DEFAULTS,PID_PARAM_DEFAULTS,PID_DATA_DEFAULTS};
PID_GRANDO_CONTROLLER pid1_spd = {PID_TERM_DEFAULTS,PID_PARAM_DEFAULTS,PID_DATA_DEFAULTS};

// Instance a PWM driver instance
PWMGEN pwm1 = PWMGEN_DEFAULTS;

// Instance a QEP interface driver
QEP qep1 = QEP_DEFAULTS;

// Instance a ramp controller to smoothly ramp the frequency
RMPCNTL rc1 = RMPCNTL_DEFAULTS;

//	Instance a ramp generator to simulate an Anglele
RAMPGEN rg1 = RAMPGEN_DEFAULTS;

// Instance a speed calculator based on QEP
SPEED_MEAS_QEP speed1 = SPEED_MEAS_QEP_DEFAULTS;

// Instance a Space Vector PWM modulator. This modulator generates a, b and c
// phases based on the d and q stationery reference frame inputs
SVGENDQ svgen_dq1 = SVGENDQ_DEFAULTS;

#ifdef SARAM
// Create an instance of DATALOG Module
DLOG_4CH dlog = DLOG_4CH_DEFAULTS;
#endif

void main(void)
{
	Uint16 i;
	Uint8 rxdata = 0;
	char TxBuf[TXBUFLEN];

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2803x_SysCtrl.c file.
	InitSysCtrl();

// Only used if running from FLASH
// Note that the variable FLASH is defined by the compiler
#ifdef FLASH
// Copy time critical code and Flash setup code to RAM
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the linker files.
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
	InitFlash();	// Call the flash wrapper init function
#endif

// Step 2. Initialize GPIO:
// This example function is found in the DSP2803x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
	InitGpio();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
	DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2803x_PieCtrl.c file.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2803x_DefaultIsr.c.
// This function is found in DSP2803x_PieVect.c.
	InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
	EALLOW;		// This is needed to write to EALLOW protected registers
	PieVectTable.EPWM1_INT = &MainISR;
	EDIS;		// This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2803x_InitPeripherals.c
// InitPeripherals(); // Not required for this example

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK   = 1;		// ADC
	SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;  	// eQEP1
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;		// ePWM1
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;		// ePWM2
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;		// ePWM3
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK  = 1;		// SCI-A
	SysCtrlRegs.PCLKCR0.bit.SPIBENCLK  = 1;		// SPI-B
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC  = 1;		// Enable TBCLK
	EDIS;

// Initialize ADC module (F2803XILEG_VDC.H)
	ADC_MACRO_INIT()

// Initialize SPI for communication to the DRV8301
	DRV8301_SPI_Init(&SpibRegs);

// Initialize the PID_GRANDO_CONTROLLER module for Id
//	pid1_id.param.Kp   = _IQ(3.176*BASE_CURRENT/BASE_VOLTAGE);	//Anaheim
	pid1_id.param.Kp   = _IQ(0.25*BASE_CURRENT/BASE_VOLTAGE);	//test motor 24V
//	pid1_id.param.Kp   = _IQ(0.125*BASE_CURRENT/BASE_VOLTAGE);	//test motor 48V
	pid1_id.param.Kr   = _IQ(1.0);
//	pid1_id.param.Ki   = _IQ(T/0.0005);							//Anaheim
	pid1_id.param.Ki   = _IQ(T/0.0956);							//test motor
	pid1_id.param.Kd   = _IQ(0/T);
	pid1_id.param.Km   = _IQ(1.0);
	pid1_id.param.Umax = _IQ(0.50);
	pid1_id.param.Umin = _IQ(-0.50);

// Initialize the PID_GRANDO_CONTROLLER module for Iq
//	pid1_iq.param.Kp   = _IQ(3.176*BASE_CURRENT/BASE_VOLTAGE);	//Anaheim
	pid1_iq.param.Kp   = _IQ(0.25*BASE_CURRENT/BASE_VOLTAGE);	//test motor 24V
//	pid1_iq.param.Kp   = _IQ(0.125*BASE_CURRENT/BASE_VOLTAGE);	//test motor 48V
	pid1_iq.param.Kr   = _IQ(1.0);
//	pid1_iq.param.Ki   = _IQ(T/0.0005);							//Anaheim
	pid1_iq.param.Ki   = _IQ(T/0.0956);							//test motor
	pid1_iq.param.Kd   = _IQ(0/T);
	pid1_iq.param.Km   = _IQ(1.0);
	pid1_iq.param.Umax = _IQ(0.95);
	pid1_iq.param.Umin = _IQ(-0.95);

// Initialize the PID_GRANDO_CONTROLLER module for Speed
//	pid1_spd.param.Kp   = _IQ(0.2*BASE_FREQ/BASE_CURRENT/(POLES/2));	//Anaheim
	pid1_spd.param.Kp   = _IQ(0.1*BASE_FREQ/BASE_CURRENT/(POLES/2));		//test motor
	pid1_spd.param.Kr   = _IQ(1.0);
//	pid1_spd.param.Ki   = _IQ(T*SpeedLoopPrescaler/0.3);				//Anaheim
	pid1_spd.param.Ki   = _IQ(T*SpeedLoopPrescaler/1.0);				//test motor
	pid1_spd.param.Kd   = _IQ(0/(T*SpeedLoopPrescaler));
	pid1_spd.param.Km   = _IQ(1.0);
	pid1_spd.param.Umax = _IQ(0.95);
	pid1_spd.param.Umin = _IQ(-0.95);

// Initialize PWM module
	pwm1.PeriodMax = SYSTEM_FREQUENCY*1000000*T/2;  // Prescaler X1 (T1), ISR period = T x 1
	PWM_INIT_MACRO(pwm1)

// Initialize QEP module
	qep1.LineEncoder = 2500;
	qep1.MechScaler = _IQ30(0.25/qep1.LineEncoder);
	qep1.PolePairs = POLES/2;
	qep1.CalibratedAngle = 0;
	QEP_INIT_MACRO(qep1)

// Initialize the RAMPGEN module
	rg1.StepAngleMax = _IQ(BASE_FREQ*T);

// Initialize the Speed module for QEP based speed calculation
	speed1.K1 = _IQ21(1/(BASE_FREQ*T));
	speed1.K2 = _IQ(1/(1+T*2*PI*5));	// Low-pass cut-off frequency
	speed1.K3 = _IQ(1)-speed1.K2;
	speed1.BaseRpm = 120*(BASE_FREQ/POLES);

// Initialize the SCI communication module
	SciaRegs.SCICCR.bit.SCICHAR  = 7;
	SciaRegs.SCICTL1.bit.TXENA   = 0;
	SciaRegs.SCICTL1.bit.RXENA   = 1;
	SciaRegs.SCILBAUD            = 0x0F;		// Baud Rate : 115200
	SciaRegs.SCICTL1.bit.SWRESET = 1;

#ifdef SARAM
// Initialize DATALOG module
	dlog.iptr1 = &DlogCh1;
	dlog.iptr2 = &DlogCh2;
	dlog.iptr3 = &DlogCh3;
	dlog.iptr4 = &DlogCh4;
	dlog.trig_value = 0x1;
	dlog.size = 0x00c8;
	dlog.prescalar = 5;
	dlog.init(&dlog);
#endif

// Initialize the phase current offset calibration filter
	cal_filt_gain = _IQ15(T/(T+TC_CAL));

// Enable PIE group 3 interrupt 1 for EPWM1_INT
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

// Enable CNT_zero interrupt using EPWM1 Time-base
	EPwm1Regs.ETSEL.bit.INTEN  = 1;   // Enable EPWM1INT generation
	EPwm1Regs.ETSEL.bit.INTSEL = 1;   // Enable interrupt CNT_zero event
	EPwm1Regs.ETPS.bit.INTPRD  = 1;   // Generate interrupt on the 1st event
	EPwm1Regs.ETCLR.bit.INT    = 1;   // Enable more interrupts

// Enable CPU INT3 for EPWM1_INT:
	IER |= M_INT3;

// Enable global Interrupts and higher priority real-time debug events:
	EINT;	// Enable Global interrupt INTM
	ERTM;	// Enable Global realtime interrupt DBGM

// Step 5. User specific code:
	while(1)
	{
		if (CpuTimer1.InterruptCount >= 5000)
		{
			CpuTimer1.InterruptCount = 0;
			LED_BLINK
		}
		if (GpioDataRegs.GPADAT.bit.GPIO22 == 1)
		{
			if (SciaRegs.SCIRXST.bit.RXRDY == 1)
				rxdata = SciaRegs.SCIRXBUF.bit.RXDT;
			if (rxdata == 0xFF)
				SciaRegs.SCICTL1.bit.TXENA = 1;
			if (rxdata < 50)
			{
#if MOTOR_DIR == 0			// CW
				SpeedRef = _IQ(rxdata / 100.0);
#elif MOTOR_DIR == 1		// CCW
				SpeedRef = _IQ(rxdata / -100.0);
#endif
//				VdTesting = 1.5 * SpeedRef;		// BLDC 24V
				VdTesting = 1.0 * SpeedRef;		// PMSM 24V
			}
		}
		else
		{
#if MOTOR_DIR == 0			// CW
				SpeedRef = _IQ(0.1);
#elif MOTOR_DIR == 1		// CCW
				SpeedRef = _IQ(-0.1);
#endif
//				VdTesting = 1.5 * SpeedRef;		// BLDC 24V
//				VdTesting = 1.0 * SpeedRef;		// PMSM 24V
		}
		if ((RunMotor == FALSE) && (fabs(SpeedRef) > _IQ(0.05)))
		{
			GATE_ON
			DELAY_US(50000);
			DRV8301_Configuration();
			Module_Init();
			RunMotor = TRUE;
			EALLOW;
			EPwm1Regs.TZCLR.bit.OST=1;
			EPwm2Regs.TZCLR.bit.OST=1;
			EPwm3Regs.TZCLR.bit.OST=1;
			EDIS;
		}
		if ((RunMotor == TRUE) && (fabs(SpeedRef) < _IQ(0.05)))
		{
			GATE_OFF
			speed1.SpeedRpm = 0;
			RunMotor = FALSE;
			EALLOW;
		 	EPwm1Regs.TZFRC.bit.OST=1;
			EPwm2Regs.TZFRC.bit.OST=1;
			EPwm3Regs.TZFRC.bit.OST=1;
		 	EDIS;
		}
		if (CpuTimer2.InterruptCount >= 15)
		{
			CpuTimer2.InterruptCount = 0;
			TxBuf[0] = 0xFE;
			TxBuf[1] = 0xFE;
			TxBuf[2] = (int16)(AdcResult.ADCRESULT4 * VCC_3V3 * 5L) >> 8;								// Ua * 4(V)
			TxBuf[3] = (int16)(AdcResult.ADCRESULT5 * VCC_3V3 * 5L) >> 8;								// Ub * 4(V)
			TxBuf[4] = (int16)(AdcResult.ADCRESULT6 * VCC_3V3 * 5L) >> 8;								// Uc * 4(V)
			TxBuf[5] = (int16)((2048L - AdcResult.ADCRESULT1) * VCC_3V3 / SAMP_RES / DRV_GAIN) >> 7;	// Ib * 32(A), Uout = 1.65 - 20 * Uin
			TxBuf[6] = (int16)((2048L - AdcResult.ADCRESULT2) * VCC_3V3 / SAMP_RES / DRV_GAIN) >> 7;	// Ic * 32(A), Uout = 1.65 - 20 * Uin
			TxBuf[7] = (Uint16)(fabs(speed1.SpeedRpm)) >> 4;											// MotorSpeed / 16(RPM)
			TxBuf[8] = (int16)(AdcResult.ADCRESULT3 * VCC_3V3 * 5L) >> 8;								// SupplyVoltage * 4(V)
			TxBuf[9] = GetTemperatureC(AdcResult.ADCRESULT7);											// ChipTemperature(¡æ)
			for(i=0; i<TXBUFLEN; i++)
			{
				comPutChar(TxBuf[i]);
			}
		}
		comTXD();
	}
}

interrupt void MainISR(void)
{
	CpuTimer1.InterruptCount++;
	CpuTimer2.InterruptCount++;
	if (RunMotor == TRUE)
	{
// =============================== LEVEL 1 ======================================
//	 Open loop and speed measurement
// ==============================================================================
#if (BUILDLEVEL==LEVEL1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
		rc1.TargetValue = SpeedRef;
		RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
		rg1.Freq = rc1.SetpointValue;
		RG_MACRO(rg1)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
		clarke1.As=-(_IQ15toIQ((AdcResult.ADCRESULT1<<3)-cal_offset_A)<<1);
		clarke1.Bs=-(_IQ15toIQ((AdcResult.ADCRESULT2<<3)-cal_offset_B)<<1);

		CLARKE_MACRO(clarke1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
		park1.Alpha = clarke1.Alpha;
		park1.Beta  = clarke1.Beta;
		park1.Angle = rg1.Out;

		park1.Sine   = _IQsinPU(park1.Angle);
		park1.Cosine = _IQcosPU(park1.Angle);

		PARK_MACRO(park1)

// ------------------------------------------------------------------------------
//	Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
		ipark1.Ds     = VdTesting;
		ipark1.Qs     = VqTesting;
		ipark1.Sine   = park1.Sine;
		ipark1.Cosine = park1.Cosine;

		IPARK_MACRO(ipark1)

// ------------------------------------------------------------------------------
//    Call the QEP calculation module
// ------------------------------------------------------------------------------
		QEP_MACRO(qep1);

// ------------------------------------------------------------------------------
//    Connect inputs of the SPEED_FR module and call the speed calculation macro
// ------------------------------------------------------------------------------
		speed1.ElecTheta    = qep1.ElecTheta;
		speed1.DirectionQep = (int32)(qep1.DirectionQep);
		SPEED_FR_MACRO(speed1)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
		svgen_dq1.Ualpha = ipark1.Alpha;
		svgen_dq1.Ubeta = ipark1.Beta;
		SVGEN_MACRO(svgen_dq1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
		pwm1.MfuncC1 = _IQtoQ15(svgen_dq1.Ta);
		pwm1.MfuncC2 = _IQtoQ15(svgen_dq1.Tb);
		pwm1.MfuncC3 = _IQtoQ15(svgen_dq1.Tc);
		PWM_MACRO(pwm1)							   	   // Calculate the new PWM compare values


		EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;	// PWM 1A - PhaseA
		EPwm2Regs.CMPA.half.CMPA=pwm1.PWM2out;	// PWM 2A - PhaseB
		EPwm3Regs.CMPA.half.CMPA=pwm1.PWM3out;	// PWM 3A - PhaseC

#ifdef SARAM
// ------------------------------------------------------------------------------
//  Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
		DlogCh1 = _IQtoQ15(park1.Qs);
		DlogCh2 = _IQtoQ15(clarke1.Bs);
		DlogCh3 = _IQtoQ15(svgen_dq1.Ta);
		DlogCh4 = _IQtoQ15(svgen_dq1.Tc);
#endif
#endif // (BUILDLEVEL==LEVEL1)

// =============================== LEVEL 2 ======================================
//	 Auto-calibrate the current sensor offsets
// ==============================================================================
#if (BUILDLEVEL==LEVEL2)

		_iq IAfdbk;
		_iq IBfdbk;
// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
// ------------------------------------------------------------------------------
		IAfdbk=_IQ15toIQ((AdcResult.ADCRESULT1<<3)-cal_offset_A)<<1;
		IBfdbk=_IQ15toIQ((AdcResult.ADCRESULT2<<3)-cal_offset_B)<<1;

// ------------------------------------------------------------------------------
//  LPF to average the calibration offsets
//  Use the offsets calculated here to initialize cal_offset_A and cal_offset_B
//  so that they are used for the remaining build levels
// ------------------------------------------------------------------------------
		cal_offset_A = _IQ15mpy(cal_filt_gain,_IQtoIQ15(IAfdbk)) + cal_offset_A;
		cal_offset_B = _IQ15mpy(cal_filt_gain,_IQtoIQ15(IBfdbk)) + cal_offset_B;

// ------------------------------------------------------------------------------
//  force all PWMs to 0% duty cycle
// ------------------------------------------------------------------------------
		EPwm1Regs.CMPA.half.CMPA=pwm1.PeriodMax;	// PWM 1A - PhaseA
		EPwm2Regs.CMPA.half.CMPA=pwm1.PeriodMax;	// PWM 2A - PhaseB
		EPwm3Regs.CMPA.half.CMPA=pwm1.PeriodMax;	// PWM 3A - PhaseC

// ------------------------------------------------------------------------------
//  Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
		DlogCh1 = _IQtoQ15(IAfdbk);
		DlogCh2 = _IQtoQ15(IBfdbk);
		DlogCh3 = _IQtoQ15(cal_offset_A);
		DlogCh4 = _IQtoQ15(cal_offset_B);
#endif // (BUILDLEVEL==LEVEL2)

// =============================== LEVEL 3 ======================================
//	 Closed current(torque) loop and speed measurement
// ==============================================================================
#if (BUILDLEVEL==LEVEL3)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
		rc1.TargetValue = SpeedRef;
		RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
		rg1.Freq = rc1.SetpointValue;
		RG_MACRO(rg1)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
		clarke1.As=-(_IQ15toIQ((AdcResult.ADCRESULT1<<3)-cal_offset_A)<<1);
		clarke1.Bs=-(_IQ15toIQ((AdcResult.ADCRESULT2<<3)-cal_offset_B)<<1);

		CLARKE_MACRO(clarke1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
		park1.Alpha = clarke1.Alpha;
		park1.Beta = clarke1.Beta;
		park1.Angle = rg1.Out;

		park1.Sine = _IQsinPU(park1.Angle);
		park1.Cosine = _IQcosPU(park1.Angle);

		PARK_MACRO(park1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_GRANDO_CONTROLLER module and call the PID IQ controller macro
// ------------------------------------------------------------------------------
		pid1_iq.term.Ref = IqRef;
		pid1_iq.term.Fbk = park1.Qs;
		PID_GR_MACRO(pid1_iq)

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_GRANDO_CONTROLLER module and call the PID ID controller macro
// ------------------------------------------------------------------------------
		pid1_id.term.Ref = IdRef;
		pid1_id.term.Fbk = park1.Ds;
		PID_GR_MACRO(pid1_id)

// ------------------------------------------------------------------------------
//	Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
		ipark1.Ds = pid1_id.term.Out;
		ipark1.Qs = pid1_iq.term.Out;
		ipark1.Sine   = park1.Sine;
		ipark1.Cosine = park1.Cosine;

		IPARK_MACRO(ipark1)

// ------------------------------------------------------------------------------
//    Call the QEP calculation module
// ------------------------------------------------------------------------------
		QEP_MACRO(qep1);

// ------------------------------------------------------------------------------
//    Connect inputs of the SPEED_FR module and call the speed calculation macro
// ------------------------------------------------------------------------------
		speed1.ElecTheta = qep1.ElecTheta;
		speed1.DirectionQep = (int32)(qep1.DirectionQep);
		SPEED_FR_MACRO(speed1)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
		svgen_dq1.Ualpha = ipark1.Alpha;
		svgen_dq1.Ubeta = ipark1.Beta;
		SVGEN_MACRO(svgen_dq1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
		pwm1.MfuncC1 = _IQtoQ15(svgen_dq1.Ta);
		pwm1.MfuncC2 = _IQtoQ15(svgen_dq1.Tb);
		pwm1.MfuncC3 = _IQtoQ15(svgen_dq1.Tc);
		PWM_MACRO(pwm1)							   	   // Calculate the new PWM compare values


		EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;	// PWM 1A - PhaseA
		EPwm2Regs.CMPA.half.CMPA=pwm1.PWM2out;	// PWM 2A - PhaseB
		EPwm3Regs.CMPA.half.CMPA=pwm1.PWM3out;	// PWM 3A - PhaseC

#ifdef SARAM
// ------------------------------------------------------------------------------
//  Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
	    DlogCh1 = _IQtoQ15(rg1.Out);
	    DlogCh2 = _IQtoQ15(park1.Qs);
	    DlogCh3 = _IQtoQ15(clarke1.As);
	    DlogCh4 = _IQtoQ15(clarke1.Bs);
#endif
#endif // (BUILDLEVEL==LEVEL3)

// =============================== LEVEL 4 ======================================
//	 Closed current(torque) loop and closed speed loop
// ==============================================================================
#if (BUILDLEVEL==LEVEL4)

// ------------------------------------------------------------------------------
//  Connect inputs of the RMP module and call the ramp control macro
// ------------------------------------------------------------------------------
		rc1.TargetValue = SpeedRef;
		RC_MACRO(rc1)

// ------------------------------------------------------------------------------
//  Connect inputs of the RAMP GEN module and call the ramp generator macro
// ------------------------------------------------------------------------------
		rg1.Freq = rc1.SetpointValue;
		RG_MACRO(rg1)

// ------------------------------------------------------------------------------
//  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
//	Connect inputs of the CLARKE module and call the clarke transformation macro
// ------------------------------------------------------------------------------
		clarke1.As=-(_IQ15toIQ((AdcResult.ADCRESULT1<<3)-cal_offset_A)<<1);
		clarke1.Bs=-(_IQ15toIQ((AdcResult.ADCRESULT2<<3)-cal_offset_B)<<1);

		CLARKE_MACRO(clarke1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PARK module and call the park trans. macro
// ------------------------------------------------------------------------------
		park1.Alpha = clarke1.Alpha;
		park1.Beta  = clarke1.Beta;
		park1.Angle = rg1.Out;

		park1.Sine   = _IQsinPU(park1.Angle);
		park1.Cosine = _IQcosPU(park1.Angle);

		PARK_MACRO(park1)

// ------------------------------------------------------------------------------
//    Connect inputs of the PID_GRANDO_CONTROLLER module and call the PID speed controller macro
// ------------------------------------------------------------------------------
		if (SpeedLoopCount==SpeedLoopPrescaler)
		{
			pid1_spd.term.Ref = rc1.SetpointValue;
			pid1_spd.term.Fbk = speed1.Speed;
			PID_GR_MACRO(pid1_spd)
			SpeedLoopCount=1;
		}
		else
			SpeedLoopCount++;

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_GRANDO_CONTROLLER module and call the PID IQ controller macro
// ------------------------------------------------------------------------------
		pid1_iq.term.Ref = pid1_spd.term.Out;
		pid1_iq.term.Fbk = park1.Qs;
		PID_GR_MACRO(pid1_iq)

// ------------------------------------------------------------------------------
//  Connect inputs of the PID_GRANDO_CONTROLLER module and call the PID ID controller macro
// ------------------------------------------------------------------------------
		pid1_id.term.Ref = 0;
		pid1_id.term.Fbk = park1.Ds;
		PID_GR_MACRO(pid1_id)

// ------------------------------------------------------------------------------
//	Connect inputs of the INV_PARK module and call the inverse park trans. macro
// ------------------------------------------------------------------------------
		ipark1.Ds = pid1_id.term.Out;
		ipark1.Qs = pid1_iq.term.Out;
		ipark1.Sine   = park1.Sine;
		ipark1.Cosine = park1.Cosine;

		IPARK_MACRO(ipark1)

// ------------------------------------------------------------------------------
//    Call the QEP calculation module
// ------------------------------------------------------------------------------
		QEP_MACRO(qep1);

// ------------------------------------------------------------------------------
//    Connect inputs of the SPEED_FR module and call the speed calculation macro
// ------------------------------------------------------------------------------
		speed1.ElecTheta = qep1.ElecTheta;
		speed1.DirectionQep = (int32)(qep1.DirectionQep);
		SPEED_FR_MACRO(speed1)

// ------------------------------------------------------------------------------
//  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
// ------------------------------------------------------------------------------
		svgen_dq1.Ualpha = ipark1.Alpha;
		svgen_dq1.Ubeta = ipark1.Beta;
		SVGEN_MACRO(svgen_dq1)

// ------------------------------------------------------------------------------
//  Connect inputs of the PWM_DRV module and call the PWM signal generation macro
// ------------------------------------------------------------------------------
		pwm1.MfuncC1 = _IQtoQ15(svgen_dq1.Ta);
		pwm1.MfuncC2 = _IQtoQ15(svgen_dq1.Tb);
		pwm1.MfuncC3 = _IQtoQ15(svgen_dq1.Tc);
		PWM_MACRO(pwm1)							   	   // Calculate the new PWM compare values


		EPwm1Regs.CMPA.half.CMPA=pwm1.PWM1out;	// PWM 1A - PhaseA
		EPwm2Regs.CMPA.half.CMPA=pwm1.PWM2out;	// PWM 2A - PhaseB
		EPwm3Regs.CMPA.half.CMPA=pwm1.PWM3out;	// PWM 3A - PhaseC

#ifdef SARAM
// ------------------------------------------------------------------------------
//  Connect inputs of the DATALOG module
// ------------------------------------------------------------------------------
		DlogCh1 = _IQtoQ15(clarke1.As);
		DlogCh2 = _IQtoQ15(park1.Qs);
		DlogCh3 = _IQtoQ15(ipark1.Alpha);
		DlogCh4 = _IQtoQ15(svgen_dq1.Ta);
#endif
#endif // (BUILDLEVEL==LEVEL4)
	}

#ifdef SARAM
// ------------------------------------------------------------------------------
//    Call the DATALOG update function.
// ------------------------------------------------------------------------------
	dlog.update(&dlog);
#endif

// Enable more interrupts from this timer
	EPwm1Regs.ETCLR.bit.INT = 1;

// Acknowledge interrupt to recieve more interrupts from PIE group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

void DRV8301_Configuration(void)
{
	DRV8301_cntrl_reg1.bit.GATE_CURRENT = 0;		// full current 1.7A
//	DRV8301_cntrl_reg1.bit.GATE_CURRENT = 1;		// med current 0.7A
//	DRV8301_cntrl_reg1.bit.GATE_CURRENT = 2;		// min current 0.25A
	DRV8301_cntrl_reg1.bit.GATE_RESET = 0;			// Normal Mode
	DRV8301_cntrl_reg1.bit.PWM_MODE = 0;			// six independant PWMs
//	DRV8301_cntrl_reg1.bit.OC_MODE = 0;				// current limiting when OC detected
	DRV8301_cntrl_reg1.bit.OC_MODE = 1;				// latched OC shutdown
//	DRV8301_cntrl_reg1.bit.OC_MODE = 2;				// Report on OCTWn pin and SPI reg only, no shut-down
//	DRV8301_cntrl_reg1.bit.OC_MODE = 3;				// OC protection disabled
//	DRV8301_cntrl_reg1.bit.OC_ADJ_SET = 0;			// OC @ Vds=0.060V
//	DRV8301_cntrl_reg1.bit.OC_ADJ_SET = 4;			// OC @ Vds=0.097V
//	DRV8301_cntrl_reg1.bit.OC_ADJ_SET = 6;			// OC @ Vds=0.123V
//	DRV8301_cntrl_reg1.bit.OC_ADJ_SET = 9;			// OC @ Vds=0.175V
	DRV8301_cntrl_reg1.bit.OC_ADJ_SET = 15;			// OC @ Vds=0.358V
//	DRV8301_cntrl_reg1.bit.OC_ADJ_SET = 16;			// OC @ Vds=0.403V
//	DRV8301_cntrl_reg1.bit.OC_ADJ_SET = 17;			// OC @ Vds=0.454V
//	DRV8301_cntrl_reg1.bit.OC_ADJ_SET = 18;			// OC @ Vds=0.511V
	DRV8301_cntrl_reg1.bit.Reserved = 0;

//	DRV8301_cntrl_reg2.bit.OCTW_SET = 0;			// report OT and OC
	DRV8301_cntrl_reg2.bit.OCTW_SET = 1;			// report OT only
#if DRV_GAIN == 10
	DRV8301_cntrl_reg2.bit.GAIN = 0;				// CS amplifier gain = 10
#elif DRV_GAIN == 20
	DRV8301_cntrl_reg2.bit.GAIN = 1;				// CS amplifier gain = 20
#elif DRV_GAIN == 40
	DRV8301_cntrl_reg2.bit.GAIN = 2;				// CS amplifier gain = 40
#elif DRV_GAIN == 80
	DRV8301_cntrl_reg2.bit.GAIN = 3;				// CS amplifier gain = 80
#endif
	DRV8301_cntrl_reg2.bit.DC_CAL_CH1 = 0;			// not in CS calibrate mode
	DRV8301_cntrl_reg2.bit.DC_CAL_CH2 = 0;			// not in CS calibrate mode
	DRV8301_cntrl_reg2.bit.OC_TOFF    = 0;			// normal mode
	DRV8301_cntrl_reg2.bit.Reserved   = 0;

	//write to DRV8301 control register 1, returns status register 1
	DRV8301_stat_reg1.all = DRV8301_SPI_Write(&SpibRegs,CNTRL_REG_1_ADDR,DRV8301_cntrl_reg1.all);
	//write to DRV8301 control register 2, returns status register 1
	DRV8301_stat_reg1.all = DRV8301_SPI_Write(&SpibRegs,CNTRL_REG_2_ADDR,DRV8301_cntrl_reg2.all);
}

void Module_Init(void)
{
	pid1_id.data.d1 = 0;
	pid1_id.data.d2 = 0;
	pid1_id.data.i1 = 0;
	pid1_id.data.ud = 0;
	pid1_id.data.ui = 0;
	pid1_id.data.up = 0;
	pid1_id.data.v1 = 0;
	pid1_id.data.w1 = 0;
	pid1_id.term.Out = 0;

	pid1_iq.data.d1 = 0;
	pid1_iq.data.d2 = 0;
	pid1_iq.data.i1 = 0;
	pid1_iq.data.ud = 0;
	pid1_iq.data.ui = 0;
	pid1_iq.data.up = 0;
	pid1_iq.data.v1 = 0;
	pid1_iq.data.w1 = 0;
	pid1_iq.term.Out = 0;

	pid1_spd.data.d1 = 0;
	pid1_spd.data.d2 = 0;
	pid1_spd.data.i1 = 0;
	pid1_spd.data.ud = 0;
	pid1_spd.data.ui = 0;
	pid1_spd.data.up = 0;
	pid1_spd.data.v1 = 0;
	pid1_spd.data.w1 = 0;
	pid1_spd.term.Out = 0;

	rg1.Freq=0;
	rg1.Out=0;
	rg1.Angle=0;
	rc1.TargetValue=0;
	rc1.SetpointValue=0;
}

//===========================================================================
// No more.
//===========================================================================
