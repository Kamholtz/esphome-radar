#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace r24avd1 {


class R24AVD1Component : public Component, public uart::UARTDevice {

  public:
    R24AVD1Component(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}
    sensor::Sensor *sensor1 = new sensor::Sensor();
    void setup() override;
    void dump_config() override;
    void loop() override;


  protected:
    void readline_(int readch, uint8_t *buffer, int len); 

};
}  // namespace r24avd1
}  // namespace esphome
