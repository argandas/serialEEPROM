#include <serialEEPROM.h>

/*
 * Atmel AT24C256 EEPROM Memory
 * Device Address 0x50 (A0 = GND, A1 = GND)
 * 256K bit memory = 32768 Bytes
 * 64-Byte Page Write Buffer
 */

serialEEPROM myEEPROM(0x50, 32768, 64);

void setup()
{
	Serial.begin(9600);
	Serial.println("Atmel AT24C256 EEPROM Memory Example");

	Wire.begin();
	
	/* Write byte (Address 0x10) */
	myEEPROM.write(0x10, 0x87);

	/* Read byte (Address 0x10) */
	uint8_t num = 0x00;
	num = myEEPROM.read(0x10);
	Serial.print("Read byte: ");
	Serial.println(num, HEX);

	/* Write buffer (Address 0x30) */
	const char* name = "Hello World!";
	myEEPROM.write(0x30, (uint8_t*)name, strlen(name)+1);

	/* Read buffer (Address 0x30) */
	char aName[16] = {0};
	myEEPROM.read(0x30, (uint8_t*)aName, sizeof(aName));
	Serial.print("Read buffer: ");
	Serial.println(aName);
}

void loop()
{
	delay(1000);
}