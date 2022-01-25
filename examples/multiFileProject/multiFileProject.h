/****************************************************************************************************************************
  multiFileProject.h
  
  For SAMD21/SAMD51 using Flash emulated-EEPROM

  The FlashStorage_SAMD library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of SAMD21/SAMD51. It now supports writing and reading the whole object, not just byte-and-byte.

  Based on and modified from Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_SAMD
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "FlashStorage_SAMD.hpp"

const int WRITTEN_SIGNATURE = 0xBEEFDEED;

// Create a structure that is big enough to contain a name
// and a surname. The "valid" variable is set to "true" once
// the structure is filled with actual data for the first time.
typedef struct
{
  char name[100];
  char surname[100];
} Person;

void testEEPROM();
