#pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace as5600 {

class AS5600Sensor : public PollingComponent, public sensor::Sensor {
 public:
  i2c::I2CDevice *i2c_dev;

  AS5600Sensor(i2c::I2CDevice *i2c, uint8_t update_interval_ms = 250)
      : PollingComponent(update_interval_ms), i2c_dev(i2c) {}

  void setup() override {
    // Nothing needed in setup
  }

  void update() override {
    uint8_t high_byte, low_byte;
    i2c_dev->read_register(0x0E, &high_byte); // AS5600 angle high byte
    i2c_dev->read_register(0x0F, &low_byte);  // low byte

    int raw_angle = ((high_byte << 8) | low_byte) & 0x0FFF; // 12-bit
    float angle_deg = raw_angle * 360.0 / 4096.0;            // convert to degrees

    // Optional calibration
    angle_deg -= 22.5;
    if (angle_deg < 0)
      angle_deg += 360;
    if (angle_deg >= 360)
      angle_deg -= 360;

    // Publish the reading
    this->publish_state(angle_deg);
  }
};

}  // namespace as5600
}  // namespace esphome
