#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/select/select.h"
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

enum class EnvironmentStatus: uint32_t {
    UNMANNED = 0x00FFFF,
    PRESCENCE = 0x0100FF,
    MOTION = 0x010101,
};

// function code
enum class FunctionCode : uint8_t {
    READ_COMMAND = 0x01,
    WRITE_COMMAND = 0x02,
    PASSIVE_REPORT_COMMAND = 0x03,
    ACTIVELY_REPORT_COMMAND = 0x04,
};


// address code 1
enum class ReadAddressCode1 {
    ID_QUERY = 0x01,
    RADAR_INFORMATION_QUERY = 0x03,
    SYSTEM_PARAMETER = 0x04,
};
enum class WriteAddressCode1 {
    SYSTEM_PARAMETER = 0x04,
    OTHER_FUNCTIONS = 0x05,
};
enum class PassiveReportAddressCode1 {
    REPORTING_MODULE = 0x01,
    REPORT_RADAR_INFORMATION = 0x03,
    REPORT_SYSTEM_PARAMETERS = 0x04,
    // REPORT_OTHER_INFORMATION = ???
};
enum class ActiveReportAddressCode1 {
    REPORT_RADAR_INFORMATION = 0x03,
    REPORT_OTHER_INFORMATION = 0x05,
};

// address code 2
enum class AddressCode2 {
    // -- read
    DEVICE_ID = 0x01,
    SOFTWARE_VERSION = 0x02,
    HARDWARE_VERSION = 0x03,
    PROTOCOL_VERSION = 0x04,

    ENVIRONMENT_STATUS = 0x05,
    PHYSICAL_PARAMETERS = 0x06,

    THRESHOLD_GEAR = 0x0C,
    SCENE_SETTING = 0x10,
    FORCE_INTO_UNMANNED_STALL = 0x12,

    // TODO: continue
    // -- write
    // THRESHOLD_GEAR = 0x0C,
    // SCENE_SETTING = 0x10,
    // FORCE_INTO_UNMANNED_STALL = 0x12,

    // -- passive_report
    // REPORTING_MODULE = 0x01,
    // REPORT_RADAR_INFORMATION = 0x03,
    // REPORT_SYSTEM_PARAMETERS = 0x04,
    // REPORT_OTHER_INFORMATION = ???

    // -- actively report command
    // REPORT_RADAR_INFORMATION = 0x03,
    // REPORT_OTHER_INFORMATION = 0x05,

};


enum class ReportRadarInformation {
    ENVIRONMENT_STATUS = 0x05,
    MOVEMENT_SIGN_PARAMETER = 0x06,
    CLOSE_TO_FAR_AWAY_STATE = 0x07,
};

enum class ReportOtherInformation {
    HEARTBEAT_PACKET = 0x01,
    ABNORMAL_RESET = 0x02,
    INITIALIZATION_SUCCESSFUL = 0x0A,
};

enum class UnmannedStallData0 {
    UNMANNED_NO_COERSION = 0x00,
    UNMANNED_10S = 0X01,
    UNMANNED_30S = 0X02,
    UNMANNED_1MIN = 0X03,
    UNMANNED_2MIN = 0X04,
    UNMANNED_5MIN = 0X05,
    UNMANNED_10MIN = 0X06,
    UNMANNED_30MIN = 0X07,
    UNMANNED_60MIN = 0X08,
};

using float_data = union {
  uint8_t data[DATA_MAX_LEN];
  float f;
};

#define MAX_PACKET_LEN 50

uint16_t get_packet(uint8_t function_code, uint8_t address_code_1, uint8_t address_code_2, const uint8_t *data, uint16_t data_len, unsigned char *buf_out, uint16_t buf_max_len);
uint16_t write_to_uart(unsigned char function_code, unsigned char address_code_1, unsigned char address_code_2, unsigned char *data, uint16_t data_len, uart::UARTDevice uart);

class R24AVD1Component : public Component, public uart::UARTDevice {

  public:
    sensor::Sensor *motion_binary_sensor = new sensor::Sensor();
    void set_enable_radar_binary_sensor(binary_sensor::BinarySensor *sens) { this->enable_radar_binary_sensor_ = sens; };
    void set_motion_binary_sensor(binary_sensor::BinarySensor *sens) { this->motion_binary_sensor_ = sens; };
    void set_presence_binary_sensor(binary_sensor::BinarySensor *sens) { this->presence_binary_sensor_ = sens; };
    void set_approach_text_sensor(text_sensor::TextSensor *sens) { this->approach_text_sensor_ = sens; };
    void set_motion_amplitude_sensor(sensor::Sensor *sens) { this->motion_amplitude_sensor_ = sens; };
    // TODO: remove
    void set_scene_select(select::Select *sens) { this->scene_select_ = sens; };

    uint16_t write_enable_radar(bool enable);
    uint16_t write_select_scene(uint8_t scene);
    uint16_t write_select_gear_threshold(uint8_t gear_threshold);
    uint16_t write_force_unmanned_stall(uint8_t unmanned_stall_option);

    void setup() override;
    void dump_config() override;
    void loop() override;


  protected:
    int readline_(int readch, uint8_t *buffer, int len, uint8_t *prev_buffer, int prev_len, int initial_pos); 
    text_sensor::TextSensor *approach_text_sensor_{nullptr};
    sensor::Sensor *motion_amplitude_sensor_ = {nullptr};
    binary_sensor::BinarySensor *enable_radar_binary_sensor_{nullptr};
    binary_sensor::BinarySensor *motion_binary_sensor_{nullptr};
    binary_sensor::BinarySensor *presence_binary_sensor_{nullptr};
    select::Select *scene_select_{nullptr};
    
};
}  // namespace r24avd1
}  // namespace esphome
