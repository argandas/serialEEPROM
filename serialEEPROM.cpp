#include <serialEEPROM.h>
#include <Wire.h>


#define EEPROM_BUFF_LEN (BUFFER_LENGTH - 2) /* Arduino Wire Buffer is 32 bytes, 2 are used for address */

/* Constructor for serialEEPROM class */
serialEEPROM::serialEEPROM(uint8_t deviceAddress, uint16_t memSize, uint8_t pageSize) : 
  _address(deviceAddress),
  _memSize(memSize),
  _pageSize(pageSize)
{
  Wire.begin();
}

void serialEEPROM::write(uint16_t memaddress, uint8_t data)
{
  write(memaddress, &data, 1);
}

void serialEEPROM::write(uint16_t memaddress, uint8_t*  src, int len)
{
  uint8_t i;
  
  int index = 0;          /* Sent bytes */
  uint8_t pageSpace  = 0; /* Available page space */
  uint8_t pageOffset = 0; /* Current page offset */
  uint8_t packLength = 0; /* Length of package to send */

  /* Memory protection, don't write beyond memory limits */
  if((memaddress + len) >= _memSize)
  {
    len = (_memSize - memaddress);
  }

  for(index = 0; index < len; index += packLength)
  {
    /* Check available page space */
    pageOffset = (uint8_t)((memaddress + index) % _pageSize);
    pageSpace = (_pageSize - pageOffset); 

    if(pageSpace <= EEPROM_BUFF_LEN) 
    {
      /* If Page has less or equal space than we want to send */
      packLength = pageSpace;
    }
    else 
    {
      /* Else, send the max allowed amount of data */
      packLength = EEPROM_BUFF_LEN;
    }
    
    /* Use only needed space, check for pending data to send */
    if((len - index) < packLength) 
    {
      packLength = (uint8_t)(len - index);
    }

    Wire.beginTransmission(_address);
    Wire.write((uint8_t)(memaddress >> 8)); /* ADDR MSB */
    Wire.write((uint8_t)(memaddress & 0xFF)); /* ADDR LSB */
    for (i = 0; i < packLength; i++)
    {
      Wire.write(*src++);
    }
    Wire.endTransmission();

    if(packLength > 1)
    {
      /* Delay 6 ms to ensure Page write */
      delay(6);
    }
    else
    {
      /* Delay ~3.5 ms to ensure byte write */
      delay(4);    
    }
  }
}

uint8_t serialEEPROM::read(uint16_t memaddress)
{
  uint8_t rdata = 0xFF;
  read(memaddress, &rdata, 1);
  return rdata;
}

void serialEEPROM::read(uint16_t memaddress, uint8_t* dest, int len)
{
  int c;

  /* Read protection, don't read beyond memory limits */
  if((memaddress + len) >= _memSize)
  {
    len = (_memSize - memaddress);
  }

  Wire.beginTransmission(_address);
  Wire.write((uint8_t)(memaddress >> 8));   // MSB
  Wire.write((uint8_t)(memaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom((int)_address, len);

  for (c = 0; c < len; c++)
  {
    if (Wire.available())
    {
      *dest++ = Wire.read();
    }
  }
}


#if (EEPROM_DUMP_EN == 1)
void serialEEPROM::dump(HardwareSerial &port, uint16_t memaddress, int len)
{
  uint8_t i;

  uint8_t data[EEPROM_BUFF_LEN] = {0};
  
  int index = 0;          /* Sent bytes */
  uint8_t pageSpace  = 0; /* Available page space */
  uint8_t pageOffset = 0; /* Current page offset */
  uint8_t packLength = 0; /* Length of package to send */

  /* Memory protection, don't write beyond memory limits */
  if((memaddress + len) >= _memSize)
  {
    len = (_memSize - memaddress);
  }

  for(index = 0; index < len; index += packLength)
  {
    /* Print memory address */
    port.print((memaddress + index), HEX);
    port.print(": ");
    
    /* Check available page space */
    pageOffset = (uint8_t)((memaddress + index) % _pageSize);
    pageSpace = (_pageSize - pageOffset); 

    if(pageSpace <= EEPROM_BUFF_LEN) 
    {
      /* If Page has less or equal space than we want to send */
      packLength = pageSpace;
    }
    else 
    {
      /* Else, send the max allowed amount of data */
      packLength = EEPROM_BUFF_LEN;
    }
    
    /* Use only needed space, check for pending data to send */
    if((len - index) < packLength) 
    {
      packLength = (uint8_t)(len - index);
    }

    read((memaddress + index), (uint8_t*) data, sizeof(data));

    for (i = 0; i < packLength; i++)
    {
      port.print(data[i], HEX);
      port.print(" ");
    }

    port.print("| ");

    for (i = 0; i < packLength; i++)
    {
      if(isprint(data[i]))
      {
        port.write(data[i]);
      }
    }

    port.println();
  }
}
#endif