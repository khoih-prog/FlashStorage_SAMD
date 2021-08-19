/******************************************************************************************************************************************
  FlashStorage_SAMD51.h
  For SAMD21/SAMD51 using Flash emulated-EEPROM

  The FlashStorage_SAMD library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of SAMD21/SAMD51. It now supports writing and reading the whole object, not just byte-and-byte.

  Based on and modified from Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_SAMD
  Licensed under LGPLv3 license
  
  Orginally written by Cristian Maglie
  
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2020 Khoi Hoang.
  
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public License along with this library. 
  If not, see (https://www.gnu.org/licenses/)
  
  Version: 1.2.0

  Version Modified By   Date        Comments
  ------- -----------  ----------   -----------
  1.0.0   K Hoang      28/03/2020  Initial coding to add support to SAMD51 besides SAMD21
  1.1.0   K Hoang      26/01/2021  Add supports to put() and get() for writing and reading the whole object. Fix bug.
  1.2.0   K Hoang      18/08/2021  Optimize code. Add debug option
 ******************************************************************************************************************************************/

#pragma once


#ifndef FlashStorage_SAMD51_h
#define FlashStorage_SAMD51_h

#ifndef BOARD_NAME
  #define BOARD_NAME    "Unknown SAMD51 board"
#endif

static const uint32_t pageSizes[] = { 8, 16, 32, 64, 128, 256, 512, 1024 };

/////////////////////////////////////////////////////

FlashClass::FlashClass(const void *flash_addr, uint32_t size) :
  PAGE_SIZE(pageSizes[NVMCTRL->PARAM.bit.PSZ]),
  PAGES(NVMCTRL->PARAM.bit.NVMP),
  MAX_FLASH(PAGE_SIZE * PAGES),
  ROW_SIZE(MAX_FLASH / 64),
  flash_address((volatile void *)flash_addr),
  flash_size(size)
{
}

/////////////////////////////////////////////////////

static inline uint32_t read_unaligned_uint32(const void *data)
{
  union {
    uint32_t u32;
    uint8_t u8[4];
  } res;
  const uint8_t *d = (const uint8_t *)data;
  res.u8[0] = d[0];
  res.u8[1] = d[1];
  res.u8[2] = d[2];
  res.u8[3] = d[3];
  return res.u32;
}

/////////////////////////////////////////////////////

void FlashClass::write(const volatile void *flash_ptr, const void *data)
{
  // Calculate data boundaries
  uint32_t size = (flash_size + 3) / 4;
  
  volatile uint32_t *dst_addr = (volatile uint32_t *)flash_ptr;
  const uint8_t *src_addr = (uint8_t *)data;

  // Disable automatic page write
  NVMCTRL->CTRLA.bit.WMODE = 0;
  
  ////KH
  /*
    1. Configure manual write for the NVM using WMODE (NVMCTRL.CTRLA).
    2. Make sure the NVM is ready to accept a new command (NVMCTRL.STATUS).
    3. Clear page buffer ( NVMCTRL.CTRLB).
    4. Make sure NVM is ready to accept a new command (NVMCTRL.STATUS).
    5. Clear the DONE Flag (NVMCTRL.INTFLAG).
    6. Write data to page buffer with 32-bit accesses at the needed address.
    7. Perform page write (NVMCTRL.CTRLB).
    8. Make sure NVM is ready to accept a new command (NVMCTRL.STATUS).
    9. Clear the DONE Flag (NVMCTRL.INTFLAG).
  */
  //KH
 
  // 2. Make sure the NVM is ready to accept a new command (NVMCTRL.STATUS).
  while (NVMCTRL->STATUS.bit.READY != NVMCTRL_STATUS_READY ) { } 
  
  // Do writes in pages
  while (size) 
  {
    // Execute "PBC" Page Buffer Clear
    // 3. Clear page buffer ( NVMCTRL.CTRLB).
    NVMCTRL->CTRLB.reg = NVMCTRL_CTRLB_CMDEX_KEY | NVMCTRL_CTRLB_CMD_PBC;
    
    // 4. Make sure the NVM is ready to accept a new command (NVMCTRL.STATUS).
    //while (NVMCTRL->STATUS.bit.READY != NVMCTRL_STATUS_READY ) { } 
    
    // 5. Clear the DONE Flag (NVMCTRL.INTFLAG)
    while (NVMCTRL->INTFLAG.bit.DONE == 0) { }

    // 6. Write data to page buffer with 32-bit accesses at the needed address.
    // Fill page buffer
    uint32_t i;
    
    for (i=0; i<(PAGE_SIZE/4) && size; i++) 
    {
      *dst_addr = read_unaligned_uint32(src_addr);
      src_addr += 4;
      dst_addr++;
      size--;
    }

    //7. Perform page write (NVMCTRL.CTRLB).
    // Execute "WP" Write Page
    NVMCTRL->CTRLB.reg = NVMCTRL_CTRLB_CMDEX_KEY | NVMCTRL_CTRLB_CMD_WP;
    
    // 8. Make sure NVM is ready to accept a new command (NVMCTRL.STATUS).
    //while (NVMCTRL->STATUS.bit.READY != NVMCTRL_STATUS_READY ) { } 
    
    // 9. Clear the DONE Flag (NVMCTRL.INTFLAG)
    while (NVMCTRL->INTFLAG.bit.DONE == 0) { }
  }
}

/////////////////////////////////////////////////////

void FlashClass::read(const volatile void *flash_ptr, void *data)
{
  FLASH_LOGERROR3(F("MAX_FLASH (KB) = "), MAX_FLASH / 1024, F(", ROW_SIZE ="), ROW_SIZE);
  FLASH_LOGERROR1(F("FlashStorage size = "), flash_size);
  FLASH_LOGERROR0(F("FlashStorage Start Address: 0x")); FLASH_HEXLOGERROR0((uint32_t ) flash_address);
  
  FLASH_LOGDEBUG0(F("Read: flash_ptr = 0x")); FLASH_HEXLOGDEBUG0((uint32_t ) flash_ptr);
  FLASH_LOGDEBUG0(F("data = 0x")); FLASH_HEXLOGDEBUG0(* (uint32_t *) data);
  
  memcpy(data, (const void *)flash_ptr, flash_size);
}

/////////////////////////////////////////////////////

void FlashClass::erase(const volatile void *flash_ptr, uint32_t size)
{
  const uint8_t *ptr = (const uint8_t *)flash_ptr;
  
  while (size > ROW_SIZE) 
  {
    erase(ptr);
    ptr += ROW_SIZE;
    size -= ROW_SIZE;
  }
  
  erase(ptr);
}

/////////////////////////////////////////////////////

void FlashClass::erase(const volatile void *flash_ptr)
{
  NVMCTRL->ADDR.reg = ((uint32_t)flash_ptr);
  
  // Check, now erase PAGE, instead of ROW !!!
  NVMCTRL->CTRLB.reg = NVMCTRL_CTRLB_CMDEX_KEY | NVMCTRL_CTRLB_CMD_EB;
  
  while (NVMCTRL->INTFLAG.bit.DONE == 0) { }
}

/////////////////////////////////////////////////////

#endif      //#ifndef FlashStorage_SAMD51_h

