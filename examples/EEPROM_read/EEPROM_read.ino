/******************************************************************************************************************************************
  EEPROM_read.ino
  For SAMD21/SAMD51 using Flash emulated-EEPROM

  The FlashStorage_SAMD library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of SAMD21/SAMD51. It now supports writing and reading the whole object, not just byte-and-byte.

  Based on and modified from Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_SAMD
  Licensed under LGPLv3 license
  
  Orginally written by A. Christian
  
  Copyright (c) 2015-2016 Arduino LLC.  All right reserved.
  Copyright (c) 2020 Khoi Hoang.
  
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public License along with this library. 
  If not, see (https://www.gnu.org/licenses/)
 ******************************************************************************************************************************************/
/*
   EEPROM Read

   Reads the value of each byte of the EEPROM and prints it to the computer.
   This example code is in the public domain.
*/

//#define EEPROM_EMULATION_SIZE     (4 * 1024)

// Use 0-2. Larger for more debugging messages
#define FLASH_DEBUG       0

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FlashStorage_SAMD.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart EEPROM_read on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_SAMD_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());
}

void loop() 
{
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();
 
  if (++address == EEPROM.length()) 
  {
    address = 0;
  }

  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= EEPROM.length() - 1;
  ***/

  delay(500);
}
