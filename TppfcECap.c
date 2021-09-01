// Mostly stolen from TI's TMS320F28004x lab class
// -Justin Walraven, The Engineering Shop
// 01SEP2021

/**********************************************************************
* File: ECap.c -- Solution File
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include <TPPFC.h>                          // Main include file


/**********************************************************************
* Function: InitECap()
*
* Description: Initializes the Enhanced Capture modules on the F28004x
**********************************************************************/
void InitECap(void)
{
//---------------------------------------------------------------------
//--- Configure eCAP1 unit for capture                        
//---------------------------------------------------------------------

//--- Reset the eCAP1.  This is good programming practice.
	SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAP1);        // Reset eCAP1

//--- Disable all capture interrupts and clear all capture flags
    ECAP_disableInterrupt(ECAP1_BASE,
                          (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                           ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                           ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                           ECAP_ISR_SOURCE_COUNTER_COMPARE));
    ECAP_clearInterrupt(ECAP1_BASE,
                        (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE));


    ECAP_disableTimeStampCapture(ECAP1_BASE);                       // Disable CAP1-CAP4 register loads
    ECAP_stopCounter(ECAP1_BASE);                                   // Stop the counter
    ECAP_selectECAPInput(ECAP1_BASE, ECAP_INPUT_INPUTXBAR7);        // Select Input X-BAR INPUT7 as the source for eCAP1

//--- Configure eCAP1
    ECAP_enableCaptureMode(ECAP1_BASE);                                             // Enable capture mode
    ECAP_setCaptureMode(ECAP1_BASE, ECAP_CONTINUOUS_CAPTURE_MODE, ECAP_EVENT_4);    // Continuous mode and wrap after 4 captures

    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_1, ECAP_EVNT_RISING_EDGE);         // Capture event 1 on rising edge
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_2, ECAP_EVNT_FALLING_EDGE);        // Capture event 2 on falling edge
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_3, ECAP_EVNT_RISING_EDGE);         // Capture event 3 on rising edge
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_4, ECAP_EVNT_FALLING_EDGE);        // Capture event 4 on falling edge

    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_1);                      // Do not reset counter on capture event 1 (absolute time stamp)
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_2);                      // Do not reset counter on capture event 2 (absolute time stamp)
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_3);                      // Do not reset counter on capture event 3 (absolute time stamp)
    ECAP_disableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_4);                      // Do not reset counter on capture event 4 (absolute time stamp)

    ECAP_enableInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_3);              // Capture event 3 interrupt enabled

//--- Enable eCAP1 interrupt
	Interrupt_register(INT_ECAP1, &ecap1ISR);       // Re-map ECAP1 interrupt signal to call the ISR function
	Interrupt_enable(INT_ECAP1);                    // Enable ECAP1 in PIE group 4 and enable INT4 in IER to enable PIE group

//--- Finish up
    ECAP_enableTimeStampCapture(ECAP1_BASE);                // Enable CAP1-CAP4 register loads
    ECAP_startCounter(ECAP1_BASE);                          // Start the counter

} // end InitECap()


//--- end of file -----------------------------------------------------
