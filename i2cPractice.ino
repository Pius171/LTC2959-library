#include <Wire.h>
#include "LTC2959.h"

// Create an instance of the LTC2959 class
LTC2959 batteryMonitor;
// if your rsene is not 250mohms, ucomment he line below and  input your rsense value
// a wrong rsense will affect current values
//LTC2959 batteryMonitor(xxx);

void setup() {
  Serial.begin(115200);
  delay(100);  // Wait for Serial

  Serial.println("Initializing LTC2959...");
  Wire.begin(16, 17);
  // Wire.setSDA(PB9);
  // Wire.setSCL(PB8);
  if (!batteryMonitor.begin()) {
    Serial.println("LTC2959 not found. Check wiring.");
    while (1)
      ;  // Halt
  }

  Serial.println("LTC2959 initialized successfully!");

  // 🟢 Enable Coulomb Counter with LOW deadband (20uV)
  bool counterEnabled = batteryMonitor.enableCounter();
  if (counterEnabled) {
    Serial.println("Coulomb counter enabled successfully.");
  } else {
    Serial.println("Failed to enable Coulomb counter.");
  }
  //batteryMonitor.disableCounter();
  batteryMonitor.resetChargeCounter();

}

void loop() {
 // batteryMonitor.OverwriteMinCurrent(-20.0);
  float voltage     = batteryMonitor.readVoltage();
  float temperature = batteryMonitor.readTemperature();
  float current     = batteryMonitor.readCurrent();
  float mAh         = batteryMonitor.readCharge_mAh();

  float minVoltage  = batteryMonitor.readMinVoltage();
  float maxVoltage  = batteryMonitor.readMaxVoltage();
  float minCurrent  = batteryMonitor.readMinCurrent();
  float maxCurrent  = batteryMonitor.readMaxCurrent();

  char buffer[180];  // Extended for more data

  snprintf(buffer, sizeof(buffer),
           "V: %7.3f V | Vmin: %7.3f V | Vmax: %7.3f V | "
           "I: %7.3f A | Imin: %7.3f A | Imax: %7.3f A | "
           "Temp: %6.2f °C | mAh: %13.6f",
           voltage, minVoltage, maxVoltage,
           current, minCurrent, maxCurrent,
           temperature, mAh);

  Serial.println(buffer);

  delay(1000);
}

