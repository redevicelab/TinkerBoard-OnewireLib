/* 
 Ссылка на https://www.asus.com/us/Single-Board-Computer/Tinker-Board/
 Ссылка на репозаторий wget http://dlcdnet.asus.com/pub/ASUS/mb/Linux/Tinker_Board_2GB/GPIO_API_for_C.zip
*/
#include <iostream>
#include <wiringPi.h>
#include "OneWire.h"
 
using namespace std;
 
double getTemp(OneWire * oneWire, uint64_t ds18b20s) {
  uint8_t data[9];
 
  do {
    oneWire->setDevice(ds18b20s);
    oneWire->writeByte(CMD_CONVERTTEMP);
 
    delay(750);
 
    oneWire->setDevice(ds18b20s);
    oneWire->writeByte(CMD_RSCRATCHPAD);
 
    for (int i = 0; i < 9; i++) {
      data[i] = oneWire->readByte();
    }
  } while (oneWire->crc8(data, 8) != data[8]);
 
  return ((data[1] << 8) + data[0]) * 0.0625;
}
 
int main() {
  OneWire * ds18b20 = new OneWire(7); // тут указывается пин на DATA для датчика pin 17 asus tinkerboard
  try {
    ds18b20->oneWireInit();
 
    double temperature;
    int n = 100;
    uint64_t roms[n];
    ds18b20->searchRom(roms, n);
    cout << "---------------------------------" << endl; 
    cout << "devices = " << n << endl;
    cout << "---------------------------------" << endl; 
    for (int i = 0; i < n; i++) {
      cout << "addr T[" << (i + 1) << "] = " << roms[i] << endl;
    }
    cout << "---------------------------------" << endl;
    while (1) {
      for (int i = 0; i < n; i++) {
        temperature = getTemp(ds18b20, roms[i]);
        cout << "T[" << (i + 1) << "] = " << temperature << "°C" << endl;
      }
      cout << "---------------------------------" << endl;
      delay(500);
    }
  } catch (exception & e) {
    cout << e.what() << endl;
  }
 
}