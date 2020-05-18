/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008 - 2013 Code Red Technologies Ltd, 
 * Copyright 2015, 2018 NXP
 * (c) NXP Semiconductors 2013-2020
 * Generated linker script file for LPC810
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * MCUXpresso IDE v10.3.1 [Build 2233] [2019-02-20] on May 18, 2020 9:52:26 PM
 */

MEMORY
{
  /* Define each memory region */
  MFlash4 (rx) : ORIGIN = 0x0, LENGTH = 0x1000 /* 4K bytes (alias Flash) */  
  RamLoc1 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x400 /* 1K bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_MFlash4 = 0x0  ; /* MFlash4 */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_MFlash4 = 0x0 + 0x1000 ; /* 4K bytes */  
  __top_Flash = 0x0 + 0x1000 ; /* 4K bytes */  
  __base_RamLoc1 = 0x10000000  ; /* RamLoc1 */  
  __base_RAM = 0x10000000 ; /* RAM */  
  __top_RamLoc1 = 0x10000000 + 0x400 ; /* 1K bytes */  
  __top_RAM = 0x10000000 + 0x400 ; /* 1K bytes */  
