#include "LTC2959.h"
#include <stdint.h>

LTC2959::LTC2959(float rSenseOhms) {
  _address = 0x63;
  _adcAddr = 0x01;
  _adcConfig = 0xA4;
  _rSense = rSenseOhms;
  // 0XA4  = 10100100. The third bit from behind control which voltage is read
  // if it 0 as in 10100000 = 0xA0 , it will read the supply voltage
  // if it 1 as in 10100100 = 0xA4 , it will read the battery voltage [ which is voltage at SENSEN pin]
  // refer to datasheet page 12 for more information

}

bool LTC2959::begin() {
  Wire.begin();  // Start I2C if not already running

  // Simple check: try to read a known register (e.g., voltage MSB at 0x0F)
  Wire.beginTransmission(_address);
  Wire.write(0x0F);  // Voltage MSB . Just using it to check if the device will respond
  if (Wire.endTransmission(false) != 0) {
    // Ends the write phase, but sets false to send a repeated start, not a STOP.

    // This is important when you want to follow the write with a read (which we’ll do later).

    // The return value tells us if the transmission succeeded.

    return false;  // Device not responding
  }

  Wire.requestFrom(_address, (uint8_t)1);
  return Wire.available() == 1;  // check if it responded with data
}

float LTC2959::readVoltage() {
  writeRegister(_adcAddr, _adcConfig);
  uint16_t raw = readRegister16(0x0F);  // 0x0F = Voltage MSB
  return 62.6 * raw / 65536.0;
}

float LTC2959::readTemperature() {
  writeRegister(_adcAddr, _adcConfig);
  uint16_t raw = readRegister16(0x23);  // 0x23 = Temperature MSB
  return 825.0 * raw / 65536.0 - 273.15;
}

float LTC2959::readCurrent() {
  writeRegister(_adcAddr, _adcConfig);  // tell ADC to convert voltage, current and temp readings
  int16_t raw = readRegister16(0x19);   // 0x19 = Current MSB
  return (97.5e-3 / _rSense) * (raw / 32768.0);
}

bool LTC2959::enableCounter(Deadband deadband, bool counterON) {
  // check the difference when you enable ADC
if(counterON){
  writeRegister(0x02, deadband); // deadband: voltage level to ignore counting
}
else{
  writeRegister(0x02, 0x1C); // disable counting
}
  // verify by reading back
  Wire.beginTransmission(_address);
  Wire.write(0x02);
  Wire.endTransmission(false);
  Wire.requestFrom(_address, (uint8_t)1);

  if (Wire.available()) {
    uint8_t ctrl = Wire.read();
    return (ctrl & 0x08) == 0;  // Bit 3 should be 0 if counting is enabled
  }

  return false;
}

float LTC2959::readCharge_mAh() {
  uint32_t raw = readRegister32(0x03); // 0x03 is the starting register for columb readings
  // Each count = 533 nAh
  return raw * 0.000533; // in mAh
}


int16_t LTC2959::readRegister16(uint8_t reg) {
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(_address, (uint8_t)2);
  if (Wire.available() < 2) return 0;

  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();

  return (int16_t)(msb << 8 | lsb);
}

uint32_t LTC2959::readRegister32(uint8_t reg) {
  Wire.beginTransmission(_address);
  Wire.write(reg); // start
  Wire.endTransmission(false);

  Wire.requestFrom(_address, (uint8_t)4);
  if (Wire.available() < 4) return 0;

//timeout functionality
//   unsigned long start = millis();
// while (Wire.available() < 4) {
//   if (millis() - start > 100) return 0; // timeout after 100 ms
// }

  uint8_t msb = Wire.read();
  uint8_t e = Wire.read();
  uint8_t f = Wire.read();
  uint8_t lsb = Wire.read();

  return ((uint32_t)msb << 24) | ((uint32_t)e << 16) | ((uint32_t)f << 8) | lsb;
}



void LTC2959::writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}
