/******************************************************************************************************************************************
  EEPROM_get.ino
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
/***
    eeprom_get example.

    This shows how to use the EEPROM.get() method.

    To pre-set the EEPROM data, run the example sketch eeprom_put. This sketch will run without it.
    However, the values shown will be shown from what ever is already on the EEPROM.

    This may cause the serial object to print out a large string of garbage if there is no null character
    inside one of the strings loaded.

    Written by Christopher Andrews 2015
    Released under MIT licence.
***/

//#define EEPROM_EMULATION_SIZE     (4 * 1024)

// Use 0-2. Larger for more debugging messages
#define FLASH_DEBUG       0

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FlashStorage_SAMD.h>

const int WRITTEN_SIGNATURE = 0xBEEFDEED;
const int START_ADDRESS     = 0;

struct MyObject
{
  float field1;
  byte field2;
  char name[10];
};

void printMyObject(MyObject &customVar)
{
  Serial.println("===============");
  Serial.print("Field1: "); Serial.println(customVar.field1, 5);
  Serial.print("Field2: "); Serial.println(customVar.field2);
  Serial.print("Name: "); Serial.println(customVar.name);
  Serial.println("===============");
}

void secondTest()
{
  int eeAddress = START_ADDRESS + sizeof(WRITTEN_SIGNATURE) + sizeof(float); //Move address to the next byte after float 'f'.

  MyObject customVar; //Variable to store custom object read from EEPROM.
  EEPROM.get(eeAddress, customVar);

  Serial.println("Read custom object from EEPROM: ");
  printMyObject(customVar);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStart EEPROM_get on ")); Serial.println(BOARD_NAME);
  Serial.println(FLASH_STORAGE_SAMD_VERSION);

  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());

  // Check signature at address 0
  int signature;

  float f;
  int eeAddress;

  EEPROM.get(START_ADDRESS, signature);

  // If the EEPROM doesn't store valid data, then no WRITTEN_SIGNATURE
  if (signature != WRITTEN_SIGNATURE)
  {
    Serial.println("EEPROM doesn't store valid data, writing WRITTEN_SIGNATURE and some example data");

    EEPROM.put(START_ADDRESS, WRITTEN_SIGNATURE);

    f = 123.456f;  //Variable to store in EEPROM.
    eeAddress = START_ADDRESS + sizeof(WRITTEN_SIGNATURE);   //Location we want the data to be put.

    //One simple call, with the address first and the object second.
    EEPROM.put(eeAddress, f);

    Serial.print("Float written to EEPROM: ");
    Serial.println(f, 3);

    /** Put is designed for use with custom structures also. **/

    //Data to store.
    MyObject customVar =
    {
      3.14159f,
      65,
      "Working!"
    };

    eeAddress += sizeof(float); //Move address to the next byte after float 'f'.

    EEPROM.put(eeAddress, customVar);

    if (!EEPROM.getCommitASAP())
    {
      Serial.println("CommitASAP not set. Need commit()");
      EEPROM.commit();
    }

    Serial.println("Done writing custom object to EEPROM: ");
    printMyObject(customVar);
    Serial.println("Reset to see how you can retrieve the values by using EEPROM_get!");
  }
  else
  {
    Serial.println("EEPROM has valid data with WRITTEN_SIGNATURE. Now read some example data");

    f = 0.00f;   //Variable to store data read from EEPROM.
    eeAddress = START_ADDRESS + sizeof(WRITTEN_SIGNATURE); //EEPROM address to start reading from

    Serial.print("Read float from EEPROM: ");

    //Get the float data from the EEPROM at position 'eeAddress'
    EEPROM.get(eeAddress, f);
    Serial.println(f, 3);    //This may print 'ovf, nan' if the data inside the EEPROM is not a valid float.

    secondTest(); //Run the next test.
  }
}

void loop()
{
  /* Empty loop */
}
