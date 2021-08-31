/**********************************************************************
* File: Gpio.c
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Base.h"                          // Main include file


/**********************************************************************
* Function: InitGpio()
*
* Description: Initializes the shared GPIO pins on the F28004x
**********************************************************************/
void InitGpio(void)
{
//--- Unlock the configuration registers for pins on all ports
	Device_initGPIO();                              // (FILE: device.c)

//--- Configure EPWM1A on GPIO0 (used in Lab 7)
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_PULLUP);     // Enable pull-up on GPIO0
    GPIO_setPinConfig(GPIO_0_EPWM1A);               // GPIO0 = EPWM1A
	
//--- Configure GPIO24 as input for ECAP1 via INPUT X-BAR (used in Lab 7)
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_PULLUP);    // Enable pull-up on GPIO24
    GPIO_setPinConfig(GPIO_24_GPIO24);              // GPIO24 = GPIO24	
    GPIO_setQualificationMode(24, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setDirectionMode(24, GPIO_DIR_MODE_IN);    // GPIO24 = input
    XBAR_setInputPin(XBAR_INPUT7, 24);              // GPIO24 = ECAP1	

//--- Configure GPIO34 as output (connected to LED)
    GPIO_setPadConfig(34, GPIO_PIN_TYPE_PULLUP);     // Enable pull-up on GPIO34
    GPIO_setPinConfig(GPIO_34_GPIO34);               // GPIO34 = GPIO34
    GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);    // GPIO34 = output
    GPIO_writePin(34, 1);                            // Load output latch
	
//--- Configure GPIO59 as output (used in Lab 6 - pin high)
    GPIO_setPadConfig(59, GPIO_PIN_TYPE_PULLUP);     // Enable pull-up on GPIO59
    GPIO_setPinConfig(GPIO_59_GPIO59);               // GPIO59 = GPIO59
    GPIO_setDirectionMode(59, GPIO_DIR_MODE_OUT);    // GPIO59 = output
    GPIO_writePin(59, 1);                            // Load output latch

//--- Configure GPIO25 as output (used in Lab 6 - pin toggle)
    GPIO_setPadConfig(25, GPIO_PIN_TYPE_PULLUP);     // Enable pull-up on GPIO25
    GPIO_setPinConfig(GPIO_25_GPIO25);               // GPIO25 = GPIO25
    GPIO_setDirectionMode(25, GPIO_DIR_MODE_OUT);    // GPIO25 = output
	
//--- Lock the configuration registers for pins on all ports
    GPIO_lockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_lockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
    GPIO_lockPortConfig(GPIO_PORT_H, 0xFFFFFFFF);

} // end InitGpio()


//--- end of file -----------------------------------------------------
