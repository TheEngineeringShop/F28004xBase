// Stolen from the TMS320F2800x Labs provided by TI
// -Justin Walraven, The Engineering Shop
// 31AUG2021

/**********************************************************************
* File: Cla_9.c -- File for Lab 9
* Devices: TMS320F28004x
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************/

#include <TPPFC.h>                          // Main include file


/**********************************************************************
* Function: InitCla()
*
* Description: Initializes CLA for the F28004x
**********************************************************************/
void InitCla(void)
{
#ifdef _FLASH
//--- Copy the CLA program code from its load address to the CLA program
//--- memory (using memcpy() from RTS library).
    memcpy(&Cla1ProgRunStart, &Cla1ProgLoadStart, (uint32_t)&Cla1ProgLoadSize);
#endif

//--- Memory Configuration - Master CPU and CLA Select
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);     // Shared between the CPU and the CLA
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);     // Shared between the CPU and the CLA
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS2, MEMCFG_LSRAMMASTER_CPU_CLA1);     // Shared between the CPU and the CLA
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS3, MEMCFG_LSRAMMASTER_CPU_ONLY);     // Dedicated to the CPU
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS4, MEMCFG_LSRAMMASTER_CPU_CLA1);     // Shared between the CPU and the CLA
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS5, MEMCFG_LSRAMMASTER_CPU_ONLY);     // Dedicated to the CPU
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS6, MEMCFG_LSRAMMASTER_CPU_ONLY);     // Dedicated to the CPU
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS7, MEMCFG_LSRAMMASTER_CPU_ONLY);     // Dedicated to the CPU

//--- Memory Configuration - CLA Data Memory and CLA Program Memory Select
	MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
	MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
	MemCfg_setCLAMemType(MEMCFG_SECT_LS2, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
	MemCfg_setCLAMemType(MEMCFG_SECT_LS3, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
	MemCfg_setCLAMemType(MEMCFG_SECT_LS4, MEMCFG_CLA_MEM_PROGRAM);  // Configured as CLA program memory
	MemCfg_setCLAMemType(MEMCFG_SECT_LS5, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
	MemCfg_setCLAMemType(MEMCFG_SECT_LS6, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory
	MemCfg_setCLAMemType(MEMCFG_SECT_LS7, MEMCFG_CLA_MEM_DATA);     // Configured as CLA data memory

//--- Initialize CLA task interrupt vectors
//*******************************************************************************************************//
//*** Note: suppressing compiler #770-D "conversion from pointer to smaller integer" warning.         ***//
//*** The CLA address range is 16 bits and the addresses passed to the MVECT registers will be in the ***//
//*** lower 64Kw address space. The warning is turned back on after the MVECTs are assigned addresses ***//
//*******************************************************************************************************//
#pragma diag_suppress=770
	CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_1, (uint16_t)&Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_2, (uint16_t)&Cla1Task2);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_3, (uint16_t)&Cla1Task3);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_4, (uint16_t)&Cla1Task4);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_5, (uint16_t)&Cla1Task5);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_6, (uint16_t)&Cla1Task6);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_7, (uint16_t)&Cla1Task7);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_8, (uint16_t)&Cla1Task8);
#pragma diag_warning=770

//--- Select Task interrupt source
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_ADCA1);        // ADCAINT1 is trigger source for Task1
    CLA_setTriggerSource(CLA_TASK_8, CLA_TRIGGER_SOFTWARE);     // Software (none) is trigger source for Task8

//--- Disable background task
    CLA_disableBackgroundTask(CLA1_BASE);       // Disable background task

//--- Enable use of software to start a task (IACK)
    CLA_enableIACK(CLA1_BASE);                  // Enable IACKE to start task using software

//--- Force one-time initialization Task 8 - zero delay buffer
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_8);                // Enable CLA task interrupt 8
    asm("  IACK  #0x0080");                                     // IACK - CLA task force instruction
    asm("  RPT #3 || NOP");                                     // Wait at least 4 cycles
    while(CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_8) == 1);    // Loop until task completes
    CLA_disableTasks(CLA1_BASE, CLA_TASKFLAG_8);                // Disable CLA task interrupt 8

//--- Enable CLA task interrupt 1
    CLA_enableTasks(CLA1_BASE, CLA_TASKFLAG_1);                 // Enable CLA interrupt 1

//--- Enable CLA1_1 interrupt
    Interrupt_register(INT_CLA1_1, &cla1Isr1);           // Re-map CLA1 Task1 interrupt signal to call the ISR function
    Interrupt_enable(INT_CLA1_1);                     // Enable CLA1 Task1 in PIE group 11 and enable INT11 in IER to enable PIE group 11

} // end of InitCla()


//--- end of file -----------------------------------------------------
