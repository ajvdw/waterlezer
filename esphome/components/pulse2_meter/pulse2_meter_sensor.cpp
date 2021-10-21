#include "pulse2_meter_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pulse2_meter {

static const char *const TAG = "pulse2_meter";

void Pulse2MeterSensor::setup() {
  this->pin_a_->setup();
  this->isr_pin_a_ = pin_a_->to_isr();
  this->pin_a_->attach_interrupt(Pulse2MeterSensor::gpio_intr, this, gpio::INTERRUPT_ANY_EDGE);
 
  this->pin_b_->setup();
  this->isr_pin_b_ = pin_b_->to_isr();
  this->pin_b_->attach_interrupt(Pulse2MeterSensor::gpio_intr, this, gpio::INTERRUPT_ANY_EDGE);

  this->last_detected_edge_us_ = 0;
  this->last_valid_edge_us_ = 0;
}

void Pulse2MeterSensor::loop() {
  const uint32_t now = micros();

  // If we've exceeded our timeout interval without receiving any pulse2s, assume 0 pulse2s/min until
  // we get at least two valid pulse2s.
  const uint32_t time_since_valid_edge_us = now - this->last_valid_edge_us_;
  if ((this->last_valid_edge_us_ != 0) && (time_since_valid_edge_us > this->timeout_us_)) {
    ESP_LOGD(TAG, "No pulse2 detected for %us, assuming 0 pulse2s/min", time_since_valid_edge_us / 1000000);
    this->last_valid_edge_us_ = 0;
    this->pulse2_width_us_ = 0;
  }

  // We quantize our pulse2 widths to 1 ms to avoid unnecessary jitter
  const uint32_t pulse2_width_ms = this->pulse2_width_us_ / 1000;
  if (this->pulse2_width_dedupe_.next(pulse2_width_ms)) {
    if (pulse2_width_ms == 0) {
      // Treat 0 pulse2 width as 0 pulse2s/min (normally because we've not detected any pulse2s for a while)
      this->publish_state(0);
    } else {
      // Calculate pulse2s/min from the pulse2 width in ms
      this->publish_state((60.0 * 1000.0) / pulse2_width_ms);
    }
  }

  if (this->total_sensor_ != nullptr) {
    const uint32_t total = this->total_pulses_;
    if (this->total_dedupe_.next(total)) {
      this->total_sensor_->publish_state(total);
    }
  }
}

void Pulse2MeterSensor::set_total_pulses(uint32_t pulses) { this->total_pulses_ = pulses; }

void Pulse2MeterSensor::dump_config() {
  LOG_SENSOR("", "Pulse2 Meter", this);
  LOG_PIN("  Pin A: ", this->pin_a_);
  LOG_PIN("  Pin B: ", this->pin_b_);
  ESP_LOGCONFIG(TAG, "  Filtering pulse2s shorter than %u µs", this->filter_us_);
  ESP_LOGCONFIG(TAG, "  Assuming 0 pulse2s/min after not receiving a pulse2 for %us", this->timeout_us_ / 1000000);
}

void IRAM_ATTR Pulse2MeterSensor::gpio_intr(Pulse2MeterSensor *sensor) {
  // This is an interrupt handler - we can't call any virtual method from this method

  // Get the current time before we do anything else so the measurements are consistent
  const uint32_t now = micros();
  static bool flipflop=false; 

  const bool pa= sensor->isr_pin_a_.digital_read();
  const bool pb= sensor->isr_pin_b_.digital_read();

  // We only look at rising edges
  if (pa != pb ) {
    return;
  }

  if( !flipflop && pa )
  {
    flipflop = true;
    return;
  } 

  
  if( flipflop && pb )
  {
    flipflop = false;
    // continue to the actual counting
  }
  else return; 


  // Check to see if we should filter this edge out
  if ((now - sensor->last_detected_edge_us_) >= sensor->filter_us_) {
    // Don't measure the first valid pulse2 (we need at least two pulse2s to measure the width)
    if (sensor->last_valid_edge_us_ != 0) {
      sensor->pulse2_width_us_ = (now - sensor->last_valid_edge_us_);
    }

    sensor->total_pulses_++;
    sensor->last_valid_edge_us_ = now;
  }

  sensor->last_detected_edge_us_ = now;
}

}  // namespace pulse2_meter
}  // namespace esphome
