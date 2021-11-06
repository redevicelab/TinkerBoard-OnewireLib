#ifndef ONEWIRE_H
#define ONEWIRE_H
 
#define CMD_CONVERTTEMP    0x44
#define CMD_RSCRATCHPAD    0xbe
#define CMD_WSCRATCHPAD    0x4e
#define CMD_CPYSCRATCHPAD  0x48
#define CMD_RECEEPROM      0xb8
#define CMD_RPWRSUPPLY     0xb4
#define CMD_SEARCHROM      0xf0
#define CMD_READROM        0x33
#define CMD_MATCHROM       0x55
#define CMD_SKIPROM        0xcc
#define CMD_ALARMSEARCH    0xec
 
#include <stdint.h>
 
class OneWire {
private:
  int pin;
  uint64_t searchNextAddress(uint64_t, int&);
 
public:
  OneWire(int);
  virtual ~OneWire();
 
  int reset(void);
  int crcCheck(uint64_t, uint8_t);
  uint8_t crc8(uint8_t*, uint8_t);
  void oneWireInit();
  void writeBit(uint8_t);
  void writeByte(uint8_t);
  void setDevice(uint64_t);
  void searchRom(uint64_t*, int&);
  void skipRom(void);
  uint8_t readByte(void);
  uint8_t readBit(void);
  uint64_t readRom(void);
};
 
#endif // ONEWIRE_H