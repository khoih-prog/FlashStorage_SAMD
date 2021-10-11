/******************************************************************************************************************************************
  StoreNameAndSurname.ino
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

// Demonstrate how to use FlashStorage_SAMD with an API that is similar to the EEPROM library to Store and retrieve structured data.
//#define EEPROM_EMULATION_SIZE     (4 * 1024)

// Use 0-2. Larger for more debugging messages
#define FLASH_DEBUG       0

#include <FlashStorage_SAMD.h>

const int WRITTEN_SIGNATURE = 0xBEEFDEED;

// Create a structure that is big enough to contain a name
// and a surname. The "valid" variable is set to "true" once
// the structure is filled with actual data for the first time.
typedef struct
{
  char name[100];
  char surname[100];
} Person;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart StoreNameAndSurname on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_SAMD_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());

  // Check signature at address 0
  int signature;

  // Create a "Person" variable and call it "owner"
  uint16_t storedAddress = 0;
  Person owner;

  EEPROM.get(storedAddress, signature);

  // If the EEPROM is empty then no WRITTEN_SIGNATURE
  if (signature == WRITTEN_SIGNATURE)
  {
    EEPROM.get(storedAddress + sizeof(signature), owner);

    // Say hello to the returning user!
    Serial.print("Hi "); Serial.print(owner.name); Serial.print(" "); Serial.print(owner.surname);
    Serial.println(", nice to see you again :-)");

    Serial.println("Clearing WRITTEN_SIGNATURE for next try");

    EEPROM.put(0, 0);
    Serial.println("Done clearing signature in emulated EEPROM. You can reset now");
  }
  else
  {
    Serial.println("EEPROM is empty, writing WRITTEN_SIGNATURE and some example data:");

    EEPROM.put(storedAddress, WRITTEN_SIGNATURE);

    // ...in this case we ask for user data.
    Serial.setTimeout(30000);
    Serial.print("Insert your name : ");
    String name = Serial.readStringUntil('\n');
    Serial.println(name);
    Serial.print("Insert your surname : ");
    String surname = Serial.readStringUntil('\n');
    Serial.println(surname);

    // Fill the "owner" structure with the data entered by the user...
    name.toCharArray(owner.name, 100);
    surname.toCharArray(owner.surname, 100);

    // ...and finally save everything into emulated-EEPROM
    EEPROM.put(storedAddress + sizeof(signature), owner);

    if (!EEPROM.getCommitASAP())
    {
      Serial.println("CommitASAP not set. Need commit()");
      EEPROM.commit();
    }

    // Print a confirmation of the data inserted.
    Serial.print("<< Your name: "); Serial.print(owner.name);
    Serial.print(". Your surname: "); Serial.print(owner.surname);
    Serial.println(" >> have been saved. Thank you!");
    Serial.println("You can reset to check emulated-EEPROM data retention.");
  }
}

void loop()
{
  // Do nothing...
}
