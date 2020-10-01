# FlashStorage_SAMD library for Arduino

[![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/FlashStorage_SAMD.svg)](http://github.com/khoih-prog/FlashStorage_SAMD/issues)

---
---

### Initial Version v1.0.0

1. Add support to SAMD51 family such as Itsy-Bitsy M4, etc.

Library is based on and modified from:
1. [Cristian Maglie's FlashStorage](https://github.com/cmaglie/FlashStorage)

The FlashStorage library aims to provide a convenient way to store and retrieve
user's data using the non-volatile flash memory of microcontrollers.

The flash memory, due to his properties, is generally used to store the firmware
code, but it can also be used to store user data.

## Supported hardware

Currently, ***ATSAMD21 and ATSAMD51*** are supported (and consequently every board based on 
this cpu like the ***Arduino Zero, Aduino MKR1000, Nano-33 IoT, Itsy-Bitsy M4, etc***).

## Limited number of writes

The flash memory has a limited amount of write cycles. Typical flash
memories can perform about 10000 writes cycles to the same flash block
before starting to "wear out" and begin to lose the ability to retain data.

So **BEWARE: IMPROPER USE OF THIS LIBRARY CAN QUICKLY AND PERMANENTLY
DESTROY THE FLASH MEMORY OF YOUR MICRO**, in particular you should avoid to
call the `write()` function too often and make sure that in the entire life
of the micro the number of calls to `write` stay well below the above limit
of 10000 (it's a good rule-of-thumb to keep that number in mind even if the
manufacturer of the micro guarantees a bigger number of cycles).

The same caution must be taken if you're using the EEPROM API emulation (see
below) with the `EEPROM.commit()` function.

---
---
 
## Prerequisite

 1. [`Arduino IDE v1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino SAMD core v1.8.8+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards. ***Ready*** from v1.0.0.
 3. [`Adafruit SAMD core v1.6.3+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). ***Ready*** from v1.0.0.
 4. [`Seeeduino SAMD core 1.7.9+`](https://www.seeedstudio.com/) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). ***Ready*** from v1.0.4.

---

## Installation


### Manual Install

1. Navigate to [FlashStorage_SAMD](https://github.com/khoih-prog/FlashStorage_SAMD) page.
2. Download the latest release `FlashStorage_SAMD-master.zip`.
3. Extract the zip file to `FlashStorage_SAMD-master` directory 
4. Copy whole 
  - `FlashStorage_SAMD-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:
1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **FlashStorage_SAMD** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for FlashStorage_SAMD in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---

### Packages' Patches

 1. ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.8](Packages_Patches/arduino/hardware/samd/1.8.8) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.8).
 
Supposing the Arduino SAMD version is 1.8.8. These files must be copied into the directory:
- `~/.arduino15/packages/arduino/hardware/samd/1.8.8/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.8/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

 2. ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.3) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.3). 

Supposing the Adafruit SAMD core version is 1.6.3. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.3/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

 3. ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.7.9) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.7.9). 

Supposing the Seeeduino SAMD core version is 1.7.9. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.7.9/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`


---
---

## Usage

First of all you must declare a global `FlashStorage` object for each piece of
data you intend to store in the flash memory.
For example if you want to store the age of a person you must declare an
`age_storage` like this:

```c++
FlashStorage(age_storage, int);
```

this instruction means "create a `FlashStorage` to store an `int` variable and call
it `age_storage`". Now you can use `age_storage` as a place to safely store an integer:

```c++
void readAndStoreUserAge() {
  Serial.println("Please enter your age:");
  String age = Serial.readStringUntil('\n');

  age_storage.write(age.toInt());  // <-- save the age
}
```

after a reset of the microcontroller to retrieve the stored age you can use:

```c++
int user_age = age_storage.read();
```

### Using the alternative EEPROM-like API

If you include `FlashAsEEPROM.h` you'll get an EEPROM emulation with the internal flash memory.
See [EmulateEEPROM](examples/EmulateEEPROM) sketch for an example.

The API is very similar to the well known Arduino EEPROM.h API but with two additional functions:

* `EEPROM.isValid()` returns `true` if data in the EEPROM is valid or, in other words, if the data has been written at least once, otherwise EEPROM data is "undefined" and the function returns `false`.
* `EEPROM.commit()` store the EEPROM data in flash. Use this with care: Every call writes the complete EEPROM data to flash. This will reduce the remainig flash-write-cycles. Don't call this method in a loop or [you will kill your flash soon](https://github.com/khoih-prog/FlashStorage_SAMD#limited-number-of-writes).

---
---

### Examples

 1. [EmulateEEPROM](examples/EmulateEEPROM)
 2. [FlashStoreAndRetrieve](examples/FlashStoreAndRetrieve)
 3. [StoreNameAndSurname](examples/StoreNameAndSurname)

### Examples from other libraries

### 1. Library [BlynkEthernet_WM](https://github.com/khoih-prog/BlynkEthernet_WM)

 4. [AM2315_W5500](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/AM2315_W5500)
 5. [DHT11_W5500](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/DHT11_W5500)
 6. [ENC28J60_Blynk](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/ENC28J60_Blynk)
 7. [ENC28J60_Blynk_Email](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/ENC28J60_Blynk_Email)
 8. [ENC28J60_WM_Config](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/ENC28J60_WM_Config)
 9. [EthernetENC_Blynk_SAMD](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/EthernetENC_Blynk_SAMD)
10. [W5500_Blynk](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/W5500_Blynk)
11. [W5500_Blynk_Email](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/W5500_Blynk_Email)
12. [W5500_WM_Config](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/W5500_WM_Config)
13. [W5500_Blynk_Email_SAMD](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/W5500_Blynk_Email_SAMD)
14. [W5500_Blynk_SAMD](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/W5500_Blynk_SAMD)
15. [W5500_WM_Config_SAMD](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/W5500_WM_Config_SAMD)
 
### 2. Library [Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
 
16. [SAMD_ESP8266Shield](https://github.com/khoih-prog/Blynk_Esp8266AT_WM/tree/master/examples/SAMD_ESP8266Shield)
 
### 3. Library [Blynk_WiFiNINA_WM](https://github.com/khoih-prog/Blynk_WiFiNINA_WM)
 
17. [SAMD_WiFiNINA_WM](https://github.com/khoih-prog/Blynk_WiFiNINA_WM/tree/master/examples/SAMD_WiFiNINA_WM)
 
### 4. Library [ESP_AT_WiFiManager](https://github.com/khoih-prog/ESP_AT_WiFiManager) 
 
18. [AutoConnect](https://github.com/khoih-prog/ESP_AT_WiFiManager/tree/master/examples/AutoConnect)
19. [AutoConnectWithFeedback](https://github.com/khoih-prog/ESP_AT_WiFiManager/tree/master/examples/AutoConnectWithFeedback)
20. [ConfigOnStartup](https://github.com/khoih-prog/ESP_AT_WiFiManager/tree/master/examples/ConfigOnStartup)
21. [ConfigOnSwitch](https://github.com/khoih-prog/ESP_AT_WiFiManager/tree/master/examples/ConfigOnSwitch)

### 5. Library [ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite) 
 
22. [SAMD_ESP8266Shield](https://github.com/khoih-prog/ESP_AT_WM_Lite/tree/master/examples/SAMD_ESP8266Shield)


### 6. Library [WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite) 
 
23. [SAMD_WiFiNINA](https://github.com/khoih-prog/WiFiManager_NINA_Lite/tree/master/examples/SAMD_WiFiNINA)
24. [SAMD_WiFiNINA_MQTT](https://github.com/khoih-prog/ESP_AT_WM_Lite/tree/master/examples/SAMD_WiFiNINA_MQTT)

### 7. Library [DoubleResetDetector_Generic](https://github.com/khoih-prog/DoubleResetDetector_Generic) 
 
25. [minimal](https://github.com/khoih-prog/DoubleResetDetector_Generic/tree/master/examples/minimal)


---
---

This is the code of [StoreNameAndSurname](examples/StoreNameAndSurname)

```cpp
#include <FlashStorage_SAMD.h>

// Create a structure that is big enough to contain a name
// and a surname. The "valid" variable is set to "true" once
// the structure is filled with actual data for the first time.
typedef struct
{
  boolean valid;
  char name[100];
  char surname[100];
} Person;

// Reserve a portion of flash memory to store a "Person" and
// call it "my_flash_store".
FlashStorage(my_flash_store, Person);

// Note: the area of flash memory reserved lost every time
// the sketch is uploaded on the board.

void setup()
{
  SERIAL_PORT_MONITOR.begin(9600);
  while (!SERIAL_PORT_MONITOR);

  // Create a "Person" variable and call it "owner"
  Person owner;

  // Read the content of "my_flash_store" into the "owner" variable
  owner = my_flash_store.read();

  // If this is the first run the "valid" value should be "false"...
  if (owner.valid == false)
  {
    // ...in this case we ask for user data.
    SERIAL_PORT_MONITOR.setTimeout(30000);
    SERIAL_PORT_MONITOR.println("Insert your name:");
    String name = SERIAL_PORT_MONITOR.readStringUntil('\n');
    SERIAL_PORT_MONITOR.println("Insert your surname:");
    String surname = SERIAL_PORT_MONITOR.readStringUntil('\n');

    // Fill the "owner" structure with the data entered by the user...
    name.toCharArray(owner.name, 100);
    surname.toCharArray(owner.surname, 100);
    // set "valid" to true, so the next time we know that we
    // have valid data inside
    owner.valid = true;

    // ...and finally save everything into "my_flash_store"
    my_flash_store.write(owner);

    // Print a confirmation of the data inserted.
    SERIAL_PORT_MONITOR.println();
    SERIAL_PORT_MONITOR.print("Your name: ");
    SERIAL_PORT_MONITOR.println(owner.name);
    SERIAL_PORT_MONITOR.print("and your surname: ");
    SERIAL_PORT_MONITOR.println(owner.surname);
    SERIAL_PORT_MONITOR.println("have been saved. Thank you!");

  }
  else
  {
    // Say hello to the returning user!
    SERIAL_PORT_MONITOR.println();
    SERIAL_PORT_MONITOR.print("Hi ");
    SERIAL_PORT_MONITOR.print(owner.name);
    SERIAL_PORT_MONITOR.print(" ");
    SERIAL_PORT_MONITOR.print(owner.surname);
    SERIAL_PORT_MONITOR.println(", nice to see you again :-)");
  }
}

void loop()
{
  // Do nothing...
}
```

---
---

### Sample terminal output

The following is the sample terminal output when running example [W5500_Blynk](https://github.com/khoih-prog/BlynkEthernet_WM/tree/master/examples/W5500_Blynk) on Adafruit SAMD51 ITSYBITSY_M4 uisng W5500 Ethernet shield:

1. No Config Data with **LOAD_DEFAULT_CONFIG_DATA = false** => Config Portal don't loads default Credential

```
Start W5500_Blynk on ITSYBITSY_M4
[936] ChkCrR:CrCCSum=0xaf50,CrRCSum=0xffffffff
[936] CCSum=0x0,RCSum=0x0
[936] Invalid Stored Dynamic Data. Load default from Sketch
[937] SaveEEPROM,Sz=1024,DataSz=0,WCSum=0x1d4d
[944] CrCCSum=0x29a6
[944] MAC:FE-A8-80-C6-CE-A3
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 1
W5100::init: W5500, SSIZE =8192
[2632] IP:192.168.2.153
[2633] b:Stay in CfgPortal:No CfgDat
[2633] CfgIP=192.168.2.153
F
Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
FFFFF
[339285] SaveEEPROM,Sz=1024,DataSz=0,WCSum=0x2e89
[339292] CrCCSum=0x219f
```

2. Input valid credentials with **LOAD_DEFAULT_CONFIG_DATA = false**. Click `Save` => reboot

```
Start W5500_Blynk on ITSYBITSY_M4
[1547] ChkCrR:CrCCSum=0x219f,CrRCSum=0x219f
[1547] CCSum=0x0,RCSum=0x0
[1548] CrCCSum=0x219f,CrRCSum=0x219f
[1548] ======= Start Stored Config Data =======
[1548] Hdr=W5X00,BName=Seeeduino_W5500_BlynkWM
[1548] Svr=account.duckdns.org,Tok=new_token1
[1549] Svr1=account.ddns.net,Tok1=new_token2
[1549] Prt=8080,SIP=192.168.2.220
[1549] connectEthernet: Use static_IP=192.168.2.220
[1549] MAC:FE-A1-D4-BC-E8-CB

W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 1
W5100::init: W5500, SSIZE =8192
[3131] IP:192.168.2.220
[3131] bg:ECon.TryB
[3131] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino Zero

[3132] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[3244] Ready (ping: 6ms).
[3311] Connected to BlynkServer=account.duckdns.org,Token=new_token1
[3311] bg:EBCon
Conn2Blynk: server = account.duckdns.org, port = 8080
Token = new_token1, IP = 192.168.2.220
B
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = new-mqtt-password
Subs Topics = new-mqtt-SubTopic
Pubs Topics = new-mqtt-PubTopic
BBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB BBBBBBBBBB
```

---
---

## Releases

### Initial Version v1.0.0

1. Add support to SAMD51 family such as Itsy-Bitsy M4, etc.

Library is based on and modified from:
1. [Cristian Maglie's FlashStorage](https://github.com/cmaglie/FlashStorage)

The FlashStorage library aims to provide a convenient way to store and retrieve
user's data using the non-volatile flash memory of microcontrollers.

The flash memory, due to his properties, is generally used to store the firmware
code, but it can also be used to store user data.

## Supported hardware

Currently, ***ATSAMD21 and ATSAMD51*** are supported (and consequently every board based on 
this cpu like the ***Arduino Zero, Aduino MKR1000, Nano-33 IoT, Itsy-Bitsy M4, etc***).

---
---

## License

- The library is licensed under [MIT](https://github.com/khoih-prog/FlashStorage_SAMD/blob/master/LICENSE)


---

## FAQ

### Can I use a single FlashStorage object to store more stuff?

Yes, you can declare a `struct` with more fields and create a `FlashStorage` object to
store the entire structure. See the [StoreNameAndSurname](examples/StoreNameAndSurname)
sketch for an example on how to do it.

### The content of the FlashStorage is erased each time a new sketch is uploaded?

Yes, every time you upload a new sketch, the previous content of the FlashStorage is erased.

### Do you recommend to use FLASH instead of EEPROM?

No. If your micro provides an EEPROM it's almost always better to use that because
it's a kind of memory designed with the specific purpose to store user data (it has a
longer lifetime, number of write cycles, etc...).

In the absence of an EEPROM you can use this library to use a piece of the flash memory
as an alternative to EEPROM but you must always keep in mind his limits.

---

### Contributions and thanks

1. Based on and modified from [Cristian Maglie's FlashStorage](https://github.com/cmaglie/FlashStorage). All the credits go to [Cristian Maglie](https://github.com/cmaglie)

<table>
  <tr>
    <td align="center"><a href="https://github.com/cmaglie"><img src="https://github.com/cmaglie.png" width="100px;" alt="cmaglie"/><br /><sub><b>⭐️⭐️ Cristian Maglie</b></sub></a><br /></td>
  </tr> 
</table>

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

