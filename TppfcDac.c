// Mostly stolen from TI's TMS320F28004x lab class
// -Justin Walraven, The Engineering Shop
// 01SEP2021

/**********************************************************************
* File: Dac.c
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include <TPPFC.h>                          // Main include file


/**********************************************************************
* Function: InitDacb()
*
* Description: Initializes DAC-B for the F28004x
**********************************************************************/
void InitDacb(void)
{
//************************************************************************************************************//
//*** Note: DAC-B is being configured to use the VREFHI internal voltage reference.  For proper operation, ***//
//*** the reference modes for ADC-B and ADC-C must be configured.  When using the internal reference of    ***//
//*** 3.3V, the DAC gain of x2 should be set.  If using an external reference for DAC-B, remove the two    ***//
//*** ADC_setVREF() and DAC_setGainMode() code lines below.                                                ***//
//************************************************************************************************************//
    ADC_setVREF(ADCB_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);     // ADC-B VREF internal 3.3V
    ADC_setVREF(ADCC_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);     // ADC-C VREF internal 3.3V
    DAC_setGainMode(DACB_BASE, DAC_GAIN_TWO);                               // DAC-B x2 gain

//--- Set VREFHI as as the DAC reference voltage
    DAC_setReferenceVoltage(DACB_BASE, DAC_REF_ADC_VREFHI);

//-- Set load mode
    DAC_setLoadMode(DACB_BASE, DAC_LOAD_SYSCLK);    // Load on next SYSCLK (not using the DAC PWMSYNC signal)

//--- Set DAC-B output to mid-range
    DAC_setShadowValue(DACB_BASE, 0x0800);          // DACVALS = bits 11-0, bits 15-12 reserved; 0x0800 = 2048

//--- Enable DAC-B output
    DAC_enableOutput(DACB_BASE);                    // Enable DAC output
    DEVICE_DELAY_US(10);                            // Required delay after enabling the DAC (delay for DAC to power up)

} // end of InitDacb()


//--- end of file -----------------------------------------------------
