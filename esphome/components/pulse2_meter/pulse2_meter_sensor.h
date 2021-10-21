#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace pulse2_meter {

class Pulse2MeterSensor : public sensor::Sensor, public Component {
 public:
  void set_pin_a(InternalGPIOPin *pin) { this->pin_a_ = pin; }
  void set_pin_b(InternalGPIOPin *pin) { this->pin_b_ = pin; }

  void set_filter_us(uint32_t filter) { this->filter_us_ = filter; }
  void set_timeout_us(uint32_t timeout) { this->timeout_us_ = timeout; }
  void set_total_sensor(sensor::Sensor *sensor) { this->total_sensor_ = sensor; }

  void set_total_pulses(uint32_t pulses);

  void setup() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  void dump_config() override;

 protected:
  static void gpio_intr(Pulse2MeterSensor *sensor);

  InternalGPIOPin *pin_a_ = nullptr;
  InternalGPIOPin *pin_b_ = nullptr;

  ISRInternalGPIOPin isr_pin_a_;
  ISRInternalGPIOPin isr_pin_b_;

  uint32_t filter_us_ = 0;
  uint32_t timeout_us_ = 1000000UL * 60UL * 5UL;
  sensor::Sensor *total_sensor_ = nullptr;

  Deduplicator<uint32_t> pulse2_width_dedupe_;
  Deduplicator<uint32_t> total_dedupe_;

  volatile uint32_t last_detected_edge_us_ = 0;
  volatile uint32_t last_valid_edge_us_ = 0;
  volatile uint32_t pulse2_width_us_ = 0;
  volatile uint32_t total_pulses_ = 0;
};

}  // namespace pulse2_meter
}  // namespace esphome
