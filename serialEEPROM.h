/* 
 * Arduino Library for I2C EEPROM
 * @author: Hugo Arganda 
 * @date: 08/19/2016
 */

#include "Arduino.h"
 
#define EEPROM_DUMP_EN 1 /* Enable(1)/Disabled(0) EEPROM Dump method, Disabled by default */

class serialEEPROM {
  public:
    serialEEPROM(uint8_t deviceAddress, uint16_t memSize, uint8_t pageSize);

    void write(uint16_t memaddress, uint8_t data);
    void write(uint16_t memaddress, uint8_t*  src, int len);

    uint8_t read(uint16_t memaddress);
    void read(uint16_t memaddress, uint8_t* dest, int len);

#if (EEPROM_DUMP_EN == 1)
    void dump(HardwareSerial &port, uint16_t memaddress, int len);
#endif

  private:
    uint8_t _address;  /* Device Address */
    uint16_t _memSize; /* Device Memory Size */
    uint8_t _pageSize; /* Device Memory Page Size */
};