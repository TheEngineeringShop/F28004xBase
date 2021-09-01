// Mostly stolen from TI's TMS320F28004x lab class
// -Justin Walraven, The Engineering Shop
// 01SEP2021

/**********************************************************************
* File: Main_9.c -- File for Lab 9
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include <TPPFC.h>                          // Main include file

//--- Global Variables
uint16_t DEBUG_TOGGLE = 1;                // Used for realtime mode investigation test
uint16_t SINE_ENABLE = 0;                 // Used for DAC waveform generation
uint16_t PWM_MODULATE = 0;                // Used for PWM modulation
uint16_t AdcBuf[ADC_BUF_LEN];             // ADC buffer allocation
uint16_t AdcBufFiltered[ADC_BUF_LEN];     // ADC filtered data buffer allocation
uint16_t DacOffset;                       // DAC offset
uint16_t DacOutput;                       // DAC output
uint32_t PwmDuty;                         // measured PWM duty cycle
uint32_t PwmPeriod;                       // measured PWM period
uint16_t ClaFilteredOutput;               // Output of CLA filter

float32_t xDelay[FILTER_LEN] = {0,0,0,0,0};	// filter delay chain
float32_t coeffs[FILTER_LEN] = {0.0625, 0.25, 0.375, 0.25, 0.0625};	// filter coefficients

#pragma DATA_SECTION(xDelay, "Cla1Data1");
#pragma DATA_SECTION(ClaFilteredOutput, "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(coeffs, "Cla1Data2");

//#pragma DATA_SECTION(AdcBufRaw, "dmaMemBufs");
uint16_t AdcBufRaw[2*ADC_BUF_LEN];			// ADC raw data buffer allocation


/**********************************************************************
* Function: main()
*
* Description: Main function for C28x workshop labs
**********************************************************************/
void main(void)
{
//--- CPU Initialization
    Device_init();                      // Initialize device and peripherals clock (FILE: device.c)
	Interrupt_initModule();             // Initializes PIE, clear PIE registers, disables CPU interrupts, and clear all CPU interrupt flags (FILE: interrupt.c)
	Interrupt_initVectorTable();        // Initialize the PIE vector table with pointers to the shell interrupt Service Routines (FILE: interrupt.c)
    InitGpio();                         // Initialize the shared GPIO pins (FILE: Gpio.c)
	InitWatchdog();						// Initialize the Watchdog Timer (FILE: WatchDog.c)

//--- Peripheral Initialization
	InitAdca();							// Initialize the ADC-A (FILE: BaseAdc.c)
	InitDacb();                         // Initialize the DAC-B (File: BaseDac.c)
	InitEPwm();							// Initialize the EPwm (FILE: BaseEPwm.c)
	InitECap();							// Initialize the ECap (FILE: BaseECap.c)
	InitCla();							// Initialize the Cla (FILE: BaseCla.c)

//--- Enable global interrupts and real-time debug
	EINT;                               // Enable global interrupts - defined as: asm(" clrc INTM"); (FILE: cpu.h)
	ERTM;                               // Enable real-time debug - defined as: asm(" clrc DBGM"); (FILE: cpu.h)

//--- Main Loop
	while(1)							// endless loop - wait for an interrupt
	{
		NOP;                            // No operation - defined as: asm(" NOP"); (FILE: cpu.h)
	}

} //end of main()


/*** end of file *****************************************************/
