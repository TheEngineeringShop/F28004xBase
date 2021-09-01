/**********************************************************************
* File: DefaultIsr_9_10.c
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include "Base.h"                          // Main include file


//---------------------------------------------------------------------
interrupt void adcA1ISR(void)                           // PIE1.1 @ 0x000D40  ADC-A interrupt #1
{
static uint16_t *AdcBufPtr = AdcBuf;                    // Pointer to buffer
static uint16_t iQuadratureTable = 0;                   // Quadrature table index
static volatile uint16_t GPIO34_count = 0;              // Counter for pin toggle
static volatile uint16_t PwmModDelay = 0;               // Counter to change PWM
static volatile uint16_t PwmModDir = 1;                 // Create a direction for PWM
static volatile uint16_t PwmCmpaVal = PWM_MAX_DUTY;     // Starting value for PWM

	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);      // Must acknowledge the PIE group

//--- Manage the ADC interrupt flag
	ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);	// Clear ADCINT1 flag

//--- Read the ADC result
	*AdcBufPtr++ = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);    // Read the result

//--- Brute-force the circular buffer
	if( AdcBufPtr == (AdcBuf + ADC_BUF_LEN) )
	{	
		AdcBufPtr = AdcBuf;						    // Rewind the pointer to beginning
	}

//--- Example: Toggle GPIO25 so we can read it with the ADC ***/
	if(DEBUG_TOGGLE == 1)
	{
        GPIO_togglePin(25);                         // Toggle the pin
	}

//--- Example: Toggle GPIO34 at a 0.5 sec rate (connected to the LED).
//             (1/50000 sec/sample)*(1 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
//             ==> x = 25000
	if(GPIO34_count++ > 25000)					    // Toggle slowly to see the LED blink
	{
	    GPIO_togglePin(34);	                        // Toggle the pin
		GPIO34_count = 0;						    // Reset the counter
	}

//--- Write to DAC-B to create input to ADC-A0
	if(SINE_ENABLE == 1)
	{
		DacOutput = DacOffset + ((QuadratureTable[iQuadratureTable++] ^ 0x8000) >> 5);
	}
	else
	{
		DacOutput = DacOffset;
	}
    if(iQuadratureTable > (SINE_PTS - 1))            // Wrap the index
    {
        iQuadratureTable = 0;
    }
    DAC_setShadowValue(DACB_BASE, DacOutput);

//--- Example: Modulate ePWM1A output between 10% and 90% duty cycle
	if(PWM_MODULATE == 1)
	{
		if(PwmModDelay++ >= 100)				    // Change PWM slowly to see waveform
		{
			// Modulate PWM waveform
			if(PwmModDir == 0)
			{
				PwmCmpaVal += PWM_STEP;				// Increment CMPA value by step size
				if(PwmCmpaVal >= PWM_MIN_DUTY)		// If limit reached then change direction
				{
					PwmCmpaVal = PWM_MIN_DUTY;		// Set to minimum duty cycle
					PwmModDir = 1;					// Reverse direction
				}
			}
			else
			{
				PwmCmpaVal -= PWM_STEP;				// Decrement CMPA value by step size
				if(PwmCmpaVal <= PWM_MAX_DUTY)		// If limit reached then change direction
				{
					PwmCmpaVal = PWM_MAX_DUTY;		// Set to maximum duty cycle
					PwmModDir = 0;					// Reverse direction
				}
			}
			EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PwmCmpaVal);    // Updated PWM CMPA value
			PwmModDelay = 0;						// Reset the delay counter
		}  	// end of modulate PWM waveform
	}
}

//---------------------------------------------------------------------
interrupt void wakeISR(void)                            // PIE1.8 @ 0x000D4E  WAKE interrupt (LPM/WD)
{
	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);      // Must acknowledge the PIE group
  
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");                                    // Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ecap1ISR(void)                           // PIE4.1 @ 0x000D70  eCAP1 interrupt
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);      // Must acknowledge the PIE group

	ECAP_clearGlobalInterrupt(ECAP1_BASE);		        // Clear the ECAP1 interrupt flag
	ECAP_clearInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_3);    // Clear the CEVT3 flag

// Note: Remember that the eCAP is running at the full 100 MHz of the device.
//       Captured values reflect this time base.

//--- Compute the PWM duty (rising edge to falling edge)
	PwmDuty = (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_2) - (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_1);

//--- Compute the PWM period (rising edge to rising edge)
	PwmPeriod = (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_3) - (int32_t)ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_1);
}

////---------------------------------------------------------------------
//interrupt void dmaCh1ISR(void)							// PIE7.1 @ 0x000DA0  DMA channel 1 interrupt
//{
//uint16_t *AdcBufPtr = AdcBuf;                           // Pointer to buffer
//static uint16_t iQuadratureTable = 0;                   // Quadrature table index
//static volatile uint16_t GPIO34_count = 0;              // Counter for pin toggle
//static volatile uint16_t PwmModDelay = 0;               // Counter to change PWM
//static volatile uint16_t PwmModDir = 1;                 // Create a direction for PWM
//static volatile uint16_t PwmCmpaVal = PWM_MAX_DUTY;     // Starting value for PWM
//static uint16_t iPingPong = 0;                          // Ping Pong flag
//uint16_t *AdcBufRawPtr;                                 // Pointer to ADC raw data buffer
//uint16_t i;                                             // General purpose uint16_t
//
//	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);      // Must acknowledge the PIE group
//
////--- Process the ADC data
//	if(iPingPong == 0)	// Ping buffer filling, process Pong buffer
//	{
//		// Manage the DMA address registers - adjust DST start address for Pong buffer
//		DMA_configAddresses(DMA_CH1_BASE, (const void *)(AdcBufRaw + ADC_BUF_LEN), (const void *)(ADCARESULT_BASE + ADC_O_RESULT0));
//
//		// Initialization the raw data buffer pointer
//		AdcBufRawPtr = AdcBufRaw + ADC_BUF_LEN;			// Point to Pong buffer
//
//		// Raw ADC data
//		for(i=0; i<ADC_BUF_LEN; i++)
//		{
//			//--- Read the ADC result:
//			*AdcBufPtr++ = *AdcBufRawPtr++;
//		}
//	}
//	else	// Pong buffer filling, process Ping buffer
//	{
//		// Manage the DMA address registers - adjust DST start address for Ping buffer
//		DMA_configAddresses(DMA_CH1_BASE, (const void *)AdcBufRaw, (const void *)(ADCARESULT_BASE + ADC_O_RESULT0));
//
//		// Initialization the raw data buffer pointer
//		AdcBufRawPtr = AdcBufRaw;						// Point to Ping buffer
//
//		// Raw ADC data
//		for(i=0; i<ADC_BUF_LEN; i++)
//		{
//			//--- Read the ADC result:
//			*AdcBufPtr++ = *AdcBufRawPtr++;
//		}
//	}
////--- Update the Ping Pong buffer flag
//	iPingPong ^= 1;								    	// iPingPong toggles between 0 and 1
//
////--- Example: Toggle GPIO25 so we can read it with the ADC ***/
//	if(DEBUG_TOGGLE == 1)
//	{
//        GPIO_togglePin(25);                          // Toggle the pin
//	}
//
////--- Example: Toggle GPIO34 at a 0.5 sec rate (connected to the LED).
////             (1/50000 sec/sample)*(50 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
////             ==> x = 500
//	if(GPIO34_count++ > 500)					    // Toggle slowly to see the LED blink
//	{
//        GPIO_togglePin(34);                         // Toggle the pin
//		GPIO34_count = 0;						    // Reset the counter
//	}
//
////--- Write to DAC-B to create input to ADC-A0
//	if(SINE_ENABLE == 1)
//	{
//		DacOutput = DacOffset + ((QuadratureTable[iQuadratureTable++] ^ 0x8000) >> 5);
//	}
//	else
//	{
//		DacOutput = DacOffset;
//	}
//    if(iQuadratureTable > (SINE_PTS - 1))               // Wrap the index
//    {
//        iQuadratureTable = 0;
//    }
//    DAC_setShadowValue(DACB_BASE, DacOutput);
//
////--- Example: Modulate ePWM1A output between 10% and 90% duty cycle
//	if(PWM_MODULATE == 1)
//	{
//		if(PwmModDelay++ >= 100)				        // Change PWM slowly to see waveform
//		{
//			// Modulate PWM waveform
//			if(PwmModDir == 0)
//			{
//				PwmCmpaVal += PWM_STEP;			    	// Increment CMPA value by step size
//				if(PwmCmpaVal >= PWM_MIN_DUTY)		    // If limit reached then change direction
//				{
//					PwmCmpaVal = PWM_MIN_DUTY;		    // Set to minimum duty cycle
//					PwmModDir = 1;					    // Reverse direction
//				}
//			}
//			else
//			{
//				PwmCmpaVal -= PWM_STEP;				    // Decrement CMPA value by step size
//				if(PwmCmpaVal <= PWM_MAX_DUTY)		    // If limit reached then change direction
//				{
//					PwmCmpaVal = PWM_MAX_DUTY;		    // Set to maximum duty cycle
//					PwmModDir = 0;					    // Reverse direction
//				}
//			}
//			EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PwmCmpaVal);    // Updated PWM CMPA value
//			PwmModDelay = 0;						    // Reset the delay counter
//		}  	// end of modulate PWM waveform
//	}
//}

//---------------------------------------------------------------------
interrupt void cla1Isr1(void)                           // PIE11.1 @ 0x000DE0 CLA1 interrupt #1
{
static uint16_t *AdcBufPtr = AdcBuf;                    // Pointer to buffer
static uint16_t iQuadratureTable = 0;                   // Quadrature table index
static uint16_t *AdcBufFilteredPtr = AdcBufFiltered;    // Pointer to ADC filtered data buffer
static volatile uint16_t GPIO34_count = 0;              // Counter for pin toggle
static volatile uint16_t PwmModDelay = 0;               // Counter to change PWM
static volatile uint16_t PwmModDir = 1;                 // Create a direction for PWM
static volatile uint16_t PwmCmpaVal = PWM_MAX_DUTY;     // Starting value for PWM

	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);     // Must acknowledge the PIE group

//--- Manage the ADC interrupt flag
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);   // Clear ADCINT1 flag

//--- Read the ADC result
    *AdcBufPtr++ = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);    // Read the result

//--- Read the CLA filter result
	*AdcBufFilteredPtr++ = ClaFilteredOutput;	        // Read the CLA filter output

//--- Brute-force the circular buffer
	if( AdcBufPtr == (AdcBuf + ADC_BUF_LEN) )
	{	
		AdcBufPtr = AdcBuf;						        // Rewind the pointer to the beginning
		AdcBufFilteredPtr = AdcBufFiltered;		        // Rewind the pointer to the beginning
	}

//--- Example: Toggle GPIO25 so we can read it with the ADC ***/
	if(DEBUG_TOGGLE == 1)
	{
        GPIO_togglePin(25);                         // Toggle the pin
	}

//--- Example: Toggle GPIO34 at a 0.5 sec rate (connected to the LED).
//             (1/50000 sec/sample)*(1 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
//             ==> x = 25000
	if(GPIO34_count++ > 25000)					    // Toggle slowly to see the LED blink
	{
        GPIO_togglePin(34);                         // Toggle the pin
		GPIO34_count = 0;						    // Reset the counter
	}

//--- Write to DAC-B to create input to ADC-A0
	if(SINE_ENABLE == 1)
	{
		DacOutput = DacOffset + ((QuadratureTable[iQuadratureTable++] ^ 0x8000) >> 5);
	}
	else
	{
		DacOutput = DacOffset;
	}
    if(iQuadratureTable > (SINE_PTS - 1))               // Wrap the index
    {
        iQuadratureTable = 0;
    }
    DAC_setShadowValue(DACB_BASE, DacOutput);

//--- Example: Modulate ePWM1A output between 10% and 90% duty cycle
	if(PWM_MODULATE == 1)
	{
		if(PwmModDelay++ >= 100)				        // Change PWM slowly to see waveform
		{
			// Modulate PWM waveform
			if(PwmModDir == 0)
			{
				PwmCmpaVal += PWM_STEP;				    // Increment CMPA value by step size
				if(PwmCmpaVal >= PWM_MIN_DUTY)		    // If limit reached then change direction
				{
					PwmCmpaVal = PWM_MIN_DUTY;	    	// Set to minimum duty cycle
					PwmModDir = 1;					    // Reverse direction
				}
			}
			else
			{
				PwmCmpaVal -= PWM_STEP;				    // Decrement CMPA value by step size
				if(PwmCmpaVal <= PWM_MAX_DUTY)		    // If limit reached then change direction
				{
					PwmCmpaVal = PWM_MAX_DUTY;		    // Set to maximum duty cycle
					PwmModDir = 0;					    // Reverse direction
				}
			}
			EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PwmCmpaVal);    // Updated PWM CMPA value
			PwmModDelay = 0;						    // Reset the delay counter
		}  	// end of modulate PWM waveform
	}
}


//--- end of file -----------------------------------------------------
