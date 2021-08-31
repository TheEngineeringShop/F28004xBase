// Stolen from the TMS320F2800x Labs provided by TI
// -Justin Walraven, The Engineering Shop
// 31AUG2021

/**********************************************************************************
* File: Lab_10.cmd -- Solution File for Lab 10 (Boot to FLASH boot mode)
* Devices: TMS320F280049
* Author: C2000 Technical Training, Texas Instruments
**********************************************************************************/

MEMORY
{
PAGE 0:    /* Program Memory */
   BEGIN_M0            : origin = 0x000000, length = 0x000002     /* Part of M0 RAM - used for "Boot to M0" bootloader mode */
   RAMLS4              : origin = 0x00A000, length = 0x000800     /* LS4 RAM, DCSM secure, CLA Program RAM */
   RAMLS5              : origin = 0x00A800, length = 0x000800     /* LS5 RAM, DCSM secure, CLA Program RAM */
   RAMGS01             : origin = 0x00C000, length = 0x004000     /* GS0-1 RAM, Parity, DMA */
   BEGIN_FLASH         : origin = 0x080000, length = 0x000002     /* Part of FLASH_BANK0_SEC0 - used for "Jump to flash" bootloader mode */
   FLASH_BANK0_SEC0    : origin = 0x080002, length = 0x000FFE     /* Part of FLASH_BANK0_SEC0 - DCSM secure */
   FLASH_BANK0_SEC1_15 : origin = 0x081000, length = 0x00F000     /* FLASH_BANK0_SEC1_15 combined - DCSM secure */
   FLASH_BANK1_SEC0_15 : origin = 0x090000, length = 0x010000     /* FLASH_BANK1_SEC0_15 combined - DCSM secure */
   RESET           (R) : origin = 0x3FFFC0, length = 0x000002     /* Part of Boot ROM */

PAGE 1:    /* Data Memory */
   BOOT_RSVD           : origin = 0x000002, length = 0x0000F3     /* Part of M0 RAM, BOOT rom will use this for stack */
   RAMM0               : origin = 0x0000F5, length = 0x00030B     /* M0 RAM */
   RAMM1               : origin = 0x000400, length = 0x000400     /* M1 RAM */
   CLA1_MSGRAMLOW      : origin = 0x001480, length = 0x000080     /* CLA to CPU Message RAM, DCSM secure */
   CLA1_MSGRAMHIGH     : origin = 0x001500, length = 0x000080     /* CPU to CLA Message RAM, DCSM secure */
   RAMLS0              : origin = 0x008000, length = 0x000800     /* LS0 RAM, DCSM secure, CLA Data RAM */
   RAMLS1              : origin = 0x008800, length = 0x000800     /* LS1 RAM, DCSM secure, CLA Data RAM */
   RAMLS2              : origin = 0x009000, length = 0x000800     /* LS2 RAM, DCSM secure, CLA Data RAM */
   RAMLS3              : origin = 0x009800, length = 0x000800     /* LS3 RAM, DCSM secure, CLA Data RAM */
   RAMLS6              : origin = 0x00B000, length = 0x000800     /* LS6 RAM, DCSM secure, CLA Data RAM */
   RAMLS7              : origin = 0x00B800, length = 0x000800     /* LS7 RAM, DCSM secure, CLA Data RAM */   
   RAMGS2              : origin = 0x010000, length = 0x002000     /* GS2 RAM, Parity, DMA */
   RAMGS3              : origin = 0x012000, length = 0x002000     /* GS3 RAM, Parity, DMA */
}

 
SECTIONS
{
/*** Compiler Required Sections ***/

   /* Program memory (PAGE 0) sections */
   .text               : > FLASH_BANK0_SEC1_15,   PAGE = 0
   .cinit              : > FLASH_BANK0_SEC1_15,   PAGE = 0
   .const              : > FLASH_BANK0_SEC1_15,   PAGE = 0
   .econst             : > FLASH_BANK0_SEC1_15,   PAGE = 0      
   .pinit              : > FLASH_BANK0_SEC1_15,   PAGE = 0
   .reset              : > RESET,                 PAGE = 0, TYPE = DSECT  /* Not using the .reset section */
   .switch             : > FLASH_BANK0_SEC1_15,   PAGE = 0

   /* Data Memory (PAGE 1) sections */
   .bss                : > RAMM0,                 PAGE = 1
   .ebss               : > RAMM0,                 PAGE = 1
   .cio                : > RAMM0,                 PAGE = 1
   .stack              : > RAMM1,                 PAGE = 1
   .sysmem             : > RAMM1,                 PAGE = 1
   .esysmem            : > RAMM1,                 PAGE = 1

/*** CLA Compiler Required Sections ***/
   .scratchpad         : > RAMLS0,                PAGE = 1                /* Scratchpad memory for the CLA C Compiler */

/*** User Defined Sections ***/
   codestart           : > BEGIN_FLASH,           PAGE = 0                /* Used by file CodeStartBranch.asm */
   dmaMemBufs          : > RAMGS2,                PAGE = 1                /* Link to DMA accessible memory */
   Cla1ToCpuMsgRAM     : > CLA1_MSGRAMLOW,        PAGE = 1                /* Link to CLA Message RAM */
   CpuToCla1MsgRAM     : > CLA1_MSGRAMHIGH,       PAGE = 1                /* Link to CLA Message RAM */
   Cla1Data1           : > RAMLS1,                PAGE = 1                /* Link to CLA Data RAM */
   Cla1Data2           : > RAMLS2,                PAGE = 1                /* Link to CLA Data RAM */

   /* Section .TI.ramfuncs used by file device.c. */
   .TI.ramfunc         :  LOAD = FLASH_BANK0_SEC1_15, PAGE = 0            /* Load to flash, run from DCSM secure RAM */
                          RUN = RAMLS5,               PAGE = 0
                          LOAD_START(_RamfuncsLoadStart),
                          LOAD_SIZE(_RamfuncsLoadSize),
                          RUN_START(_RamfuncsRunStart)

   /* Section Cla1Prog used by file Cla.c */
   Cla1Prog            :  LOAD = FLASH_BANK0_SEC1_15, PAGE = 0            /* Load to flash, run from CLA Program RAM */
                          RUN = RAMLS4,               PAGE = 0
                          LOAD_START(_Cla1ProgLoadStart),
                          LOAD_SIZE(_Cla1ProgLoadSize),
                          RUN_START(_Cla1ProgRunStart)
}

/******************* end of file ************************/
