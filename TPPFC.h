/*
 * Base.h
 *
 *  Created on: Aug 31, 2021
 *      Author: Justin Walraven, The Engineering Shop
 *
 *      This file borrows heavily from "lab.h" from TI's TMS320F28004x lab course
 */

#ifndef TPPFC_H_
#define TPPFC_H_


//---------------------------------------------------------------------------
// Constant Definitions
//
#define ADC_BUF_LEN         50              // ADC buffer length
#define ADC_SAMPLE_PERIOD   1999            // 1999 = 50 kHz sampling w/ 100 MHz ePWM clock
#define PWM_HALF_PERIOD     200             // period/2 for 250 kHz symmetric PWM w/ 100 MHz ePWM clock
#define PWM_DUTY_CYCLE      50              // 25% duty cycle
#define PWM_MIN_DUTY        20              // 10% duty cycle for PWM modulation
#define PWM_MAX_DUTY        180             // 90% duty cycle for PWM modulation
#define PWM_STEP            2              // Step size change for PWM modulation
#define FILTER_LEN          5               // filter length
#define SINE_PTS            25              // number of point in sine wave


//---------------------------------------------------------------------------
// Include Standard C Language Header Files
// (Header file <string.h> not supported by CLA compiler)
//
#if !defined(__TMS320C28XX_CLA__)
    #include <string.h>
#endif


//---------------------------------------------------------------------------
// Include Driver Library Header Files
// (Header files <driverlib.h> and <device.h> not supported by CLA compiler)
//
#if !defined(__TMS320C28XX_CLA__)
    #include "driverlib.h"                     // F28004x Driver Library
    #include "device.h"                        // Device include file
#else
    #include "hw_types.h"                      // Driver Library type definitions
#endif


//---------------------------------------------------------------------------
// Function Prototypes
//
extern void Device_init(void);
extern void Device_initGPIO(void);
extern void InitAdca(void);
extern void InitCla(void);
extern void InitDacb(void);
extern void InitDma(void);
extern void InitECap(void);
extern void InitEPwm(void);
extern void InitGpio(void);
extern void InitWatchdog(void);


//---------------------------------------------------------------------------
// Function Prototypes - ISR Declarations
//
extern interrupt void adcA1ISR(void);             // 1.1 - ADCA Interrupt 1
extern interrupt void wakeISR(void);              // 1.8 - Watchdog Wake Interrupt
extern interrupt void ecap1ISR(void);             // 4.1 - eCAP1 Interrupt
extern interrupt void dmaCh1ISR(void);            // 7.1 - DMA Channel 1 Interrupt
extern interrupt void cla1Isr1(void);             // 11.1 - CLA1 Interrupt 1


//---------------------------------------------------------------------------
// CLA Function Prototypes
//
extern interrupt void Cla1Task1();
extern interrupt void Cla1Task2();
extern interrupt void Cla1Task3();
extern interrupt void Cla1Task4();
extern interrupt void Cla1Task5();
extern interrupt void Cla1Task6();
extern interrupt void Cla1Task7();
extern interrupt void Cla1Task8();


//---------------------------------------------------------------------------
// Global symbols defined in the linker command file
//
extern uint16_t Cla1ProgLoadStart;
extern uint16_t Cla1ProgLoadSize;
extern uint16_t Cla1ProgRunStart;
extern uint16_t RamfuncsLoadStart;
extern uint16_t RamfuncsLoadSize;
extern uint16_t RamfuncsRunStart;


//---------------------------------------------------------------------------
// Global Variables References
//
extern float32_t xDelay[FILTER_LEN];
extern float32_t coeffs[FILTER_LEN];
extern uint16_t AdcBuf[ADC_BUF_LEN];
extern uint16_t AdcBufFiltered[ADC_BUF_LEN];
extern uint16_t AdcBufRaw[2*ADC_BUF_LEN];
extern uint16_t ClaFilteredOutput;
extern uint16_t DacOffset;
extern uint16_t DacOutput;
extern uint32_t PwmDuty;
extern uint32_t PwmPeriod;
extern uint16_t DEBUG_TOGGLE;
extern uint16_t SINE_ENABLE;
extern uint16_t PWM_MODULATE;
extern int QuadratureTable[SINE_PTS];



#endif /* TPPFC_H_ */
