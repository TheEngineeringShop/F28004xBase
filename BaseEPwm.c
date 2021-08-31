/**********************************************************************
* File: EPwm.c -- Solution File
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Base.h"                          // Main include file


/**********************************************************************
* Function: InitEPwm()
*
* Description: Initializes the Enhanced PWM modules on the F28004x
**********************************************************************/
void InitEPwm(void)
{
// Must disable the clock to the ePWM modules to have all ePWM modules synchronized
	SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


//---------------------------------------------------------------------
//--- Configure ePWM2 to trigger ADC SOCA at a 50 kHz rate
//---------------------------------------------------------------------
//	SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_EPWM2);    // Reset ePWM2
//
//    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);             // Disable the timer
//    EPWM_setClockPrescaler(EPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);   // TBCLK = EPWMCLK
//    EPWM_setSyncOutPulseMode(EPWM2_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);                 // Disable sync-out
//    EPWM_setEmulationMode(EPWM2_BASE, EPWM_EMULATION_FREE_RUN);                         // Ignore emulation suspend
//
//	EPWM_setTimeBaseCounter(EPWM2_BASE, 0U);				        // Clear timer counter
//	EPWM_setTimeBasePeriod(EPWM2_BASE, ADC_SAMPLE_PERIOD);          // Set timer period
//	EPWM_setPhaseShift(EPWM2_BASE, 0U);                             // Set timer phase
//	EPWM_disablePhaseShiftLoad(EPWM2_BASE);                         // Disable phase load
//
//	EPWM_enableADCTrigger(EPWM2_BASE, EPWM_SOC_A);                               // Enable ADC SOCA event
//	EPWM_setADCTriggerSource(EPWM2_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_PERIOD);     // Set SOCA on PRD event
//	EPWM_setADCTriggerEventPrescale(EPWM2_BASE, EPWM_SOC_A, 1);                  // Generate SOCA on first event
//
//	EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP);  // Enable the timer in count up mode


//---------------------------------------------------------------------
//--- Configure ePWM1 for 250 kHz symmetric PWM on EPWM1A pin
//---------------------------------------------------------------------
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_EPWM1);    // Reset ePWM1

    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);             // Disable the timer
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);   // TBCLK = EPWMCLK
    EPWM_setSyncOutPulseMode(EPWM1_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);                 // Disable sync-out
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_FREE_RUN);                         // Ignore emulation suspend

	EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);                        // Clear timer counter
    EPWM_setTimeBasePeriod(EPWM1_BASE, PWM_HALF_PERIOD);            // Set timer period
    EPWM_setPhaseShift(EPWM1_BASE, 0U);                             // Set timer phase
    EPWM_disablePhaseShiftLoad(EPWM1_BASE);                         // Disable phase load

	EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);    // Set PWM duty cycle

	EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);   // Load on zero or PRD match

	// Done this way (opposite the labs) so 0-1 duty cycle corresponds to 0-PRD in the right direction
	EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);   // Set pin on down count
	EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);  // Clear pin on up count

	EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);                               // Enable ADC SOCA event
	EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);       // Set SOCA on ZRO event
	EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);                  // Generate SOCA on first event

//--- Enable Deadband
//    EPWM_setDeadBandDelayMode(EPWM1_BASE, EPWM_DB_RED, true);   // EPWM_DB_RED is don't care with 'false'

//--- Disable, PWM chopper, and all trip zone and DC compare actions
	EPWM_setDeadBandDelayMode(EPWM1_BASE, EPWM_DB_RED, false);   // EPWM_DB_RED is don't care with 'false'
	EPWM_disableChopper(EPWM1_BASE);
	EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_DISABLE);
	EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_DISABLE);
	EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_DISABLE);
	EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_DISABLE);
	EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_DISABLE);
	EPWM_setTripZoneAction(EPWM1_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_DISABLE);
	EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_A1, EPWM_TZ_EVENT_DC_DISABLED);
	EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_A2, EPWM_TZ_EVENT_DC_DISABLED);
	EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DC_DISABLED);
	EPWM_setTripZoneDigitalCompareEventCondition(EPWM1_BASE, EPWM_TZ_DC_OUTPUT_B2, EPWM_TZ_EVENT_DC_DISABLED);

//--- Enable the timer in count up/down mode
	EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);

//---------------------------------------------------------------------
//--- Enable the clocks to the ePWM module.                   
//--- Note: this should be done after all ePWM modules are configured
//--- to ensure synchronization between the ePWM modules.
//---------------------------------------------------------------------
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);	// TBCLK to ePWM modules enabled

} // end InitEPwm()


//--- end of file -----------------------------------------------------
