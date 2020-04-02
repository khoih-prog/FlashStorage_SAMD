# FlashStorage_SAMD library for Arduino

It's always preferable to use the original just-updated-to-support-SAMD51 library [FlashStorage](https://github.com/cmaglie/FlashStorage), unless you need to use some new and different features to be added in the future, if any.

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

## Installation

### Manual Install

1. Navigate to [FlashStorage_SAMD](https://github.com/khoih-prog/FlashStorage_SAMD) page.
2. Download the latest release `FlashStorage_SAMD-master.zip`.
3. Extract the zip file to `FlashStorage_SAMD-master` directory 
4. Copy whole 
  - `FlashStorage_SAMD-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

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

### Examples

 1. [EmulateEEPROM](examples/EmulateEEPROM)
 2. [FlashStoreAndRetrieve](examples/FlashStoreAndRetrieve)
 3. [StoreNameAndSurname](examples/StoreNameAndSurname)

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

## License

This library is released under MIT license.

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

### Contributions and thanks
1. Based on and modified from [Cristian Maglie's FlashStorage](https://github.com/cmaglie/FlashStorage). All the credits go to [Cristian Maglie](https://github.com/cmaglie)

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

