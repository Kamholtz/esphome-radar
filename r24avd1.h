#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace r24avd1 {

const uint8_t START_VAL = 0x55;
const uint8_t START_IDX = 0;
const uint8_t ADDRESS_START_IDX = 1;
const uint8_t ADDRESS_L_IDX = 1;
const uint8_t ADDRESS_H_IDX = 2;
const uint8_t ADDRESS_LEN = 2;
const uint8_t FUNCTION_CODE_IDX = 3;
const uint8_t ADDRESS_CODE_1_IDX = 4;
const uint8_t ADDRESS_CODE_2_IDX = 5;
const uint8_t DATA_START_IDX = 5;
const uint8_t DATA_MAX_LEN = 4;
const uint8_t PACKET_MAX_LEN = 12;

using float_data = union {
  uint8_t data[4];
  float f;
};

class R24AVD1Component : public Component, public uart::UARTDevice {

  public:
    R24AVD1Component(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}
    sensor::Sensor *sensor1 = new sensor::Sensor();
    void setup() override;
    void dump_config() override;
    void loop() override;


  protected:
    int readline_(int readch, uint8_t *buffer, int len, int initial_pos); 

};
}  // namespace r24avd1
}  // namespace esphome
