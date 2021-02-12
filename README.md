# serialEEPROM

[![Arduino CI](https://github.com/argandas/serialEEPROM/workflows/Arduino_CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)

Arduino Library for I2C EEPROM

<!-- START COMPATIBILITY TABLE -->

## Compatibility

Device      | Tested Works | Doesn't Work | Not Tested | Size (Bytes) | Page Size (Bytes) | Address range 
----------- | :----------: | :----------: | :--------: | :----------: | :---------------: | :------------
AT24C256    |       X      |              |            | 32768        | 64                | 0x50 ~ 0x53
AT24C128    |       X      |              |            | 16384        | 64                | 0x50 ~ 0x53
24C01C      |       X      |              |            | 128          | 16                | 0x50 ~ 0x57

  * [AT24C128/256](http://www.atmel.com/Images/doc0670.pdf): Atmel 128K/256K I2C EEPROM (16KB/32KB)
  * [24C01C](http://ww1.microchip.com/downloads/en/DeviceDoc/21201K.pdf): Microchip 1K I2C EEPROM (128B)

<!-- END COMPATIBILITY TABLE -->

## Usage

For example if you are using the Microchip's 24C01C Serial EEPROM, you should define a serialEEPROM object as follow:
```c++
serialEEPROM myEEPROM(0x50, 128, 16);
```
Where "0x50" is the device address, 128 is the memory size in bytes and 16 is the page address in bytes.

For more information about how to use this library please take a look on the examples folder.

## License

-------------------------------------------------------------------------------

		DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
				Version 2, December 2004 

		Copyright (C) 2014 ITEAD Studio

		Everyone is permitted to copy and distribute verbatim or modified 
		copies of this license document, and changing it is allowed as long 
		as the name is changed. 

				DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
				
		TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 

		0. You just DO WHAT THE FUCK YOU WANT TO.

-------------------------------------------------------------------------------

