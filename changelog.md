# FlashStorage_SAMD library for Arduino

[![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_SAMD.svg?)](https://www.ardu-badge.com/FlashStorage_SAMD)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/FlashStorage_SAMD.svg)](http://github.com/khoih-prog/FlashStorage_SAMD/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.3.2](#releases-v132)
  * [Releases v1.3.1](#releases-v131)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.1](#releases-v121)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.0](#releases-v100)

  
---
---

## Changelog

### Releases v1.3.2

1. Make compatible with old libraries and codes

### Releases v1.3.1

1. Clean-up by reducing the number of library files


### Releases v1.3.0

1. Fix `multiple-definitions` linker error.
2. Add support to many more boards, such as `SAMD21E1xA`, `SAMD21G1xA` and`SAMD21J1xA`
3. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project.
4. Fix bug
5. Update `Packages' Patches`

### Releases v1.2.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Releases v1.2.0

1. Optimize code.
2. Add debug option.
3. Add support to Industruino DG21 boards using [`IndustruinoSAMD core`](https://github.com/Industruino/IndustruinoSAMD)
4. Add support to Industruino 420MAKER boards using [`IndustruinoSAML core`](https://github.com/Industruino/IndustruinoSAMx)
5. Add support to Sparkfun SAMD21 and SAMD51 boards using [`Sparkfun SAMD core`](https://github.com/sparkfun/Arduino_Boards)

### Releases v1.1.0

1. Add supports to `EEPROM.put()` and `EEPROM.get()` for efficiently writing and reading the whole object. 
2. Add `_commitASAP` flag to permit reduce the number of calls to `EEPROM.commit()` to extend the flash life.
3. Add many modified examples from [Arduino EEPROM library](https://www.arduino.cc/en/Reference/EEPROM)
4. Fix bug.

### Releases v1.0.0

1. Add support to SAMD51 family such as 

  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI WirelessAdafruit Itsy-Bitsy M4, etc.


