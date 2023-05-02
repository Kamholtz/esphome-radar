#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
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
const uint8_t DATA_START_IDX = 6;
const uint8_t DATA_MAX_LEN = 4;
const uint8_t PACKET_MAX_LEN = 12;
const uint8_t CRC_LEN = 2;

const uint8_t APPROACH_DATA_IDX = 2;

// enums
enum class ApproachStatus: uint8_t {
  NONE = 0x01,
  CLOSE = 0x02,
  FAR = 0x03,
};

using float_data = union {
  uint8_t data[4];
  float f;
};

class R24AVD1Component : public Component, public uart::UARTDevice {

  public:
    R24AVD1Component(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}
    sensor::Sensor *motion_amplitude = new sensor::Sensor();
    void set_approach_sensor(text_sensor::TextSensor *sens) { this->approach_text_sensor_ = sens; };

    void setup() override;
    void dump_config() override;
    void loop() override;


  protected:
    int readline_(int readch, uint8_t *buffer, int len, int initial_pos); 
    text_sensor::TextSensor *approach_text_sensor_{nullptr};
};
}  // namespace r24avd1
}  // namespace esphome
