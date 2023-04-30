#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace r24avd1 {


class R24AVD1Component : public Component, public sensor::Sensor, public uart::UARTDevice {


};
}  // namespace r24avd1
}  // namespace esphome
