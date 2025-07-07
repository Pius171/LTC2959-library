#ifndef LTC2959_H
#define LTC2959_H

#include <Arduino.h>
#include <Wire.h>

class LTC2959 {
public:
  /**
     * @brief Deadband configuration for Coulomb Counter.
     *
     * Sets the voltage threshold below which current changes are ignored.
     * See LTC2959 datasheet, Coulomb Control Register (0x02), bits 7:6.
     */
  enum Deadband : uint8_t {
    /** @brief No deadband. Counts even microcurrent changes. */
    NO_DEADBAND = 0x10,

    /** @brief Low deadband (20 µV). Suitable for low noise. */
    LOW_DEADBAND = 0x50,

    /** @brief Medium deadband (40 µV). Good for general use. */
    MEDIUM_DEADBAND = 0x90,

    /** @brief High deadband (80 µV). Use in noisy systems. */
    HIGH_DEADBAND = 0xD0
  };

  LTC2959(float rSenseOhms = 0.250);  // Constructor

  bool begin();  // Initializes I2C and checks device
  float readVoltage();
  float readTemperature();
  float readCurrent();
  bool enableCounter(Deadband deadband = NO_DEADBAND);
  bool disableCounter();
  void resetChargeCounter();
  float readMaxCurrent();
  float readMinCurrent();
  float readMinVoltage();
  float readMaxVoltage();
  float readCharge_mAh();
  void OverwriteMinCurrent(float current);
  void OverwriteMaxCurrent(float current);
  void OverwriteMinVoltage(float Voltage);
  void OverwriteMaxVoltage(float Voltage);

  bool setChargeHighThreshold_mAh(float mAh);
  bool setChargeLowThreshold_mAh(float mAh);
  // Add more functions later...

private:
  uint8_t _address;
  uint8_t _adcAddr;
  uint8_t _adcConfig;  // decides what data the ADC returns
  float _rSense;
  int16_t readRegister16(uint8_t reg);
  uint32_t readRegister32(uint8_t reg);
  void writeRegister(uint8_t reg, uint8_t value);
  void writeRegister2(uint8_t reg, int16_t raw);
};

#endif
