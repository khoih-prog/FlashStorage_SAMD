/******************************************************************************************************************************************
  FlashStoreAndRetrieve.ino
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

//#define EEPROM_EMULATION_SIZE     (4 * 1024)

// Use 0-2. Larger for more debugging messages
#define FLASH_DEBUG       0

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FlashStorage_SAMD.h>

// Note: the area of flash memory reserved for the variable is
// lost every time the sketch is uploaded on the board.

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart FlashStoreAndRetrieve on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_SAMD_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());

  uint16_t address = 0;
  int number;

  // Read the content of emulated-EEPROM
  EEPROM.get(address, number);

  // Print the current number on the serial monitor
  Serial.print("Number = 0x"); Serial.println(number, HEX);

  // Save into emulated-EEPROM the number increased by 1 for the next run of the sketch
  EEPROM.put(address, (int) (number + 1));

  if (!EEPROM.getCommitASAP())
  {
    Serial.println("CommitASAP not set. Need commit()");
    EEPROM.commit();
  }

  Serial.println("Done writing to emulated EEPROM. You can reset now");
}

void loop()
{
  // Do nothing...
}
