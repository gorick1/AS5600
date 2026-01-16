#include "sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace as5600 {

static const char *const TAG = "as5600";

void AS5600Sensor::setup() {
  ESP_LOGI(TAG, "Setting up AS5600 sensor...");
}

void AS5600Sensor::update() {
  uint8_t buffer[2];

  // AS5600 raw angle register (0x0E, 0x0F)
  if (!this->read_bytes(0x0E, buffer, 2)) {
    ESP_LOGW(TAG, "Failed to read AS5600 angle");
    return;
  }

  uint16_t raw_angle = ((buffer[0] & 0x0F) << 8) | buffer[1];

  // Convert to degrees (12-bit → 0–360)
  float angle = (raw_angle * 360.0f) / 4096.0f;

  this->publish_state(angle);
}

}  // namespace as5600
}  // namespace esphome
