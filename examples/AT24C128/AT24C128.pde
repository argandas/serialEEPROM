#include <Wire.h>
#include <serialEEPROM.h>

serialEEPROM myEEPROM(0x50, 16384, 64);

void setup()
{
	char* name = "argandas";
	Serial.begin(9600);
	Serial.println("Writting to EEPROM");
	myEEPROM.write(0x20, (uint8_t*)name, strlen(name)+1);
}

void loop()
{
	char aName[32] = {0};

	myEEPROM.read(0x20, (uint8_t*)aName, 32);

	Serial.print("Hello ");
	Serial.print(aName);
	Serial.println("!");
}