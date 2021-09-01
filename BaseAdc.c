/**********************************************************************
* File: Adc.c -- Solution File
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Base.h"                          // Main include file


/**********************************************************************
* Function: InitAdca()
*
* Description: Initializes ADC-A on the F28004x
**********************************************************************/
void InitAdca(void)
{
//--- Reset the ADC.  This is good programming practice.
	SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ADCA);     // Reset ADC

//--- Configure the ADC-A base registers
	ADC_disableConverter(ADCA_BASE);                                    // Power down ADC for configuration
	ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V); // VREF internal 3.3V
	ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);                       // ADC clock prescaler = CPUCLK/4
	ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);        // INT pulse generation = end of conversion

//--- SOC0 configuration - Trigger using ePWM1-ADCSOCA; Convert channel ADCINA0; Acquisition window = 8 cycles
	ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 8);

//--- No ADC interrupt triggers SOC0 (TRIGSEL determined by SOC and not ADCINT1 or ADCINT2)
	ADC_setInterruptSOCTrigger(ADCA_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);

	ADC_setSOCPriority(ADCA_BASE, ADC_PRI_ALL_ROUND_ROBIN);             // All SOCs handled in round-robin mode

//--- ADCA1 interrupt configuration
	ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);                       // Interrupt pulses regardless of flag state
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);        // EOC0 triggers the interrupt
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);                            // Enable the interrupt in the ADC

//--- Enable ADCA1 interrupt
	Interrupt_register(INT_ADCA1, &adcA1ISR);    // Re-map ADCA1 interrupt signal to call the ISR function
//	Interrupt_enable(INT_ADCA1);                 // Enable ADCA1 in PIE group 1 and enable INT1 in IER to enable PIE group 1

//--- Finish up
	ADC_enableConverter(ADCA_BASE); 			// Power up the ADC
	DEVICE_DELAY_US(1000);						// Wait 1 ms after power-up before using the ADC

} // end InitAdca()


//--- end of file -----------------------------------------------------
