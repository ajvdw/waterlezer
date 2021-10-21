#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/pulse2_meter/pulse2_meter_sensor.h"

namespace esphome {

namespace pulse2_meter {

template<typename... Ts> class SetTotalPulsesAction : public Action<Ts...> {
 public:
  SetTotalPulsesAction(Pulse2MeterSensor *pulse2_meter) : pulse2_meter_(pulse2_meter) {}

  TEMPLATABLE_VALUE(uint32_t, total_pulses)

  void play(Ts... x) override { this->pulse2_meter_->set_total_pulses(this->total_pulses_.value(x...)); }

 protected:
  Pulse2MeterSensor *pulse2_meter_;
};

}  // namespace pulse2_meter
}  // namespace esphome
