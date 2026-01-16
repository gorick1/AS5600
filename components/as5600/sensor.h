#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace as5600 {

class AS5600Sensor : public PollingComponent,
                     public sensor::Sensor,
                     public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
};

}  // namespace as5600
}  // namespace esphome
