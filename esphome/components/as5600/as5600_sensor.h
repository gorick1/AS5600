#include "esphome.h"

class AS5600Sensor : public PollingComponent, public sensor::Sensor {
 public:
  AS5600Sensor() : PollingComponent(250) {}  // Update every 250ms

  void setup() override {
    ESP_LOGD("as5600", "AS5600 setup complete");
  }

  void update() override {
    uint16_t raw_angle = 0;

    Wire.beginTransmission(0x36);
    Wire.write(0x0E);  // High byte register
    Wire.endTransmission(false);
    Wire.requestFrom(0x36, (uint8_t)2);

    if (Wire.available() == 2) {
      uint8_t high = Wire.read();
      uint8_t low  = Wire.read();
      raw_angle = ((high << 8) | low) & 0x0FFF;  // 12-bit mask
    }

    float angle_deg = raw_angle * (360.0 / 4096.0);
    angle_deg -= 22.5;  // calibration offset
    if (angle_deg < 0) angle_deg += 360.0;
    if (angle_deg >= 360) angle_deg -= 360.0;

    publish_state(angle_deg);
  }
};
