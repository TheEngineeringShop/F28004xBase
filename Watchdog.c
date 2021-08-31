/**********************************************************************
* File: Watchdog.c -- Solution File
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitWatchdog()
*
* Description: Initializes Watchdog Timer for the F28004x
**********************************************************************/
void InitWatchdog(void)
{
//--- Configure Watchdog
	SysCtl_setWatchdogPredivider(SYSCTL_WD_PREDIV_512);      // WDPRECLKDIV = INTOSC1/512
	SysCtl_setWatchdogPrescaler(SYSCTL_WD_PRESCALE_1);       // WDCLK=OSCCLK/512/1
	SysCtl_setWatchdogWindowValue(0);                        // Minimum window threshold value (disabled)

//--- Set Watchdog Mode (Reset / Interrupt)
//	SysCtl_setWatchdogMode(SYSCTL_WD_MODE_RESET);           // watchdog generates a reset
	SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);       // watchdog generates an interrupt

//--- Enable / Disable Watchdog	
	SysCtl_disableWatchdog();                               // Disable watchdog
//	SysCtl_enableWatchdog();                                // Enable watchdog

//--- Enable Watchdog interrupt
	Interrupt_register(INT_WAKE, &wakeISR);     // Re-map watchdog wake interrupt signal to call the ISR function
    Interrupt_enable(INT_WAKE);                 // Enable WAKEINT in PIE group 1 and enable INT1 in IER to enable PIE group 1
	
} // end of InitWatchdog()


//--- end of file -----------------------------------------------------
