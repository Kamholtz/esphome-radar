#include "r24avd1.h"
#include "crc.h"

namespace esphome {
namespace r24avd1 {

static const char *const TAG = "r24avd1";

void R24AVD1Component::setup() {
  // nothing to do

  // This is likely where I need to put the setup
  unsigned char command_data[1] = {0};
  uart::UARTDevice * this_uart = (uart::UARTDevice*)this;
  write_to_uart((unsigned char)FunctionCode::WRITE_COMMAND, (unsigned char)WriteAddressCode1::SYSTEM_PARAMETER, (unsigned char)AddressCode2::THRESHOLD_GEAR, command_data, 1, *this_uart);
}
void R24AVD1Component::dump_config() {
  ESP_LOGCONFIG(TAG, "LD2410:");
#ifdef USE_BINARY_SENSOR
  LOG_TEXT_SENSOR("  ", "HasTargetSensor", this->approach_text_sensor_)
  LOG_BINARY_SENSOR("  ", "MovingSensor", this->motion_binary_sensor_);
  LOG_BINARY_SENSOR("  ", "StillSensor", this->presence_binary_sensor_);
#endif
  // this->get_version_();
  // ESP_LOGCONFIG(TAG, "  Firmware Version : %u.%u.%u%u%u%u", this->version_[0], this->version_[1], this->version_[2],
  //               this->version_[3], this->version_[4], this->version_[5]);
}
void R24AVD1Component::loop() {
  const int max_line_length = 80;
  static uint8_t buffer[max_line_length];

  int pos = 0;

  while (available()) {
    pos = this->readline_(read(), buffer, max_line_length, pos);
  }
}

uint16_t get_packet(uint8_t function_code, uint8_t address_code_1, uint8_t address_code_2, const uint8_t *data, uint16_t data_len, unsigned char *buf_out, uint16_t buf_max_len) {

    uint16_t total_length = (8 + data_len);
    if (total_length > buf_max_len) {
        // error
        return -1;
    }
    uint16_t buf_out_ii = 0;
    buf_out[buf_out_ii] = 0x55; buf_out_ii++;
    buf_out[buf_out_ii] = (total_length - 1) & 0xFF; buf_out_ii++; // low
    buf_out[buf_out_ii] = ((total_length - 1) >> 8) & 0xFF; buf_out_ii++; // high
    buf_out[buf_out_ii] = function_code; buf_out_ii++;
    buf_out[buf_out_ii] = address_code_1; buf_out_ii++;
    buf_out[buf_out_ii] = address_code_2; buf_out_ii++;

    uint16_t buf_out_jj = 0;
    for (buf_out_jj = 0; buf_out_jj < data_len; buf_out_jj++) {
        buf_out[buf_out_ii] = data[buf_out_jj];
        buf_out_ii++;
    }

    uint16_t crc = crc::us_calculate_crc16(buf_out, buf_out_ii);
    buf_out[buf_out_ii] = (crc >> 8) & 0xFF; buf_out_ii++;
    buf_out[buf_out_ii] = (crc) & 0xFF; buf_out_ii++;

    return buf_out_ii; // final packet len
}

uint16_t write_to_uart(unsigned char function_code,
                                     unsigned char address_code_1,
                                     unsigned char address_code_2,
                                     unsigned char *data,
                                     uint16_t data_len,
                                     uart::UARTDevice uart) 
{

    unsigned char packet[MAX_PACKET_LEN] = {0};
    uint16_t packet_len = get_packet(function_code, address_code_1, address_code_2, data, data_len, packet, MAX_PACKET_LEN);

    uint16_t log_ii = 0;
    ESP_LOGD("crc", "packet_len: %d", packet_len);
    for (log_ii = 0; log_ii < packet_len; log_ii++) {
      ESP_LOGD("packet", "log_ii: %d, %X", log_ii, packet[log_ii]);
    }

    uart.write_array(packet, packet_len);
    return packet_len;
}


uint16_t R24AVD1Component::write_select_scene(uint8_t scene) {
    // ESP_LOGD("packet", "select_scene: %s, %d", x.c_str(), i);
    uint8_t data[1] = { scene };
    uart::UARTDevice * this_uart = (uart::UARTDevice*)this;
    return write_to_uart(0x02, 0x04, 0x10, data, 1, *this_uart);
}


int R24AVD1Component::readline_(int readch, uint8_t *buffer, int len, int initial_pos) {
  int pos = initial_pos;

  if (readch >= 0) {
    // ESP_LOGD(TAG, "%c", readch);
    if (pos < len - 1 && ((pos == START_IDX && readch == START_VAL) || pos != 0)) {
      buffer[pos++] = readch;
      buffer[pos] = 0;
    } else {
      pos = 0;
    }

    if (pos > DATA_START_IDX) {
      const uint16_t pkt_len = (buffer[ADDRESS_H_IDX] << 8) | buffer[ADDRESS_L_IDX];
      const uint16_t pkt_len_incl_start = pkt_len + 1;

      if (pkt_len_incl_start > PACKET_MAX_LEN) {
        ESP_LOGI(TAG, "Total packet len (%d) too long, discarding", pkt_len_incl_start);
        pos = 0;
      } else {
        if (pos > (pkt_len_incl_start - 1)) {
          const uint8_t function_code = buffer[FUNCTION_CODE_IDX];
          const uint8_t address_code_1 = buffer[ADDRESS_CODE_1_IDX];
          const uint8_t address_code_2 = buffer[ADDRESS_CODE_2_IDX];
          const uint8_t crc_l_idx = pkt_len_incl_start - 2;
          const uint8_t crc_l = buffer[crc_l_idx];
          const uint8_t crc_h = buffer[crc_l_idx + 1];
          const uint8_t data_len = crc_l_idx - DATA_START_IDX;

          //TODO: check CRC is valid
          
          ESP_LOGD(TAG, "function_code: %X", function_code);
          ESP_LOGD(TAG, "address_code_1: %X", address_code_1);
          ESP_LOGD(TAG, "address_code_2: %X", address_code_2);
          ESP_LOGD(TAG, "crc_l: %X", crc_l);
          ESP_LOGD(TAG, "crc_h: %X", crc_h);
          ESP_LOGD(TAG, "data_len: %d", data_len);

          uint16_t calculated_crc = crc::us_calculate_crc16(buffer, pkt_len_incl_start - CRC_LEN);
          if ((((calculated_crc >> 8) & 0xFF) == crc_l) &&
              (((calculated_crc & 0xFF)) == crc_h)) {

            if (data_len > DATA_MAX_LEN) {
              // Invalid
              ESP_LOGI(TAG, "Data len (%d) too long, discarding", data_len);

            } else {
              // we don't expect data_len to be larger than a 4 byte float
              float_data motion_amplitude_prev;
              float_data float_data_curr_union;
              for (uint8_t data_ii = 0; data_ii < data_len; data_ii++) {
                float_data_curr_union.data[data_ii] = buffer[DATA_START_IDX + data_ii];
              }

              ESP_LOGD(TAG, "float_data_union.data: %X %X %X %X", float_data_curr_union.data[0], float_data_curr_union.data[1], float_data_curr_union.data[2], float_data_curr_union.data[3]);


              // --- motion amplitude
              // CACHE the last array here
              if (this->motion_amplitude_sensor_ != nullptr &&
                  function_code == (uint8_t)FunctionCode::ACTIVELY_REPORT_COMMAND &&
                  address_code_1 == (uint8_t)PassiveReportAddressCode1::REPORT_RADAR_INFORMATION &&
                  address_code_2 == 0x06) {

                // each byte equal?
                bool all_equal = true;
                all_equal &= (motion_amplitude_prev.data[0] == float_data_curr_union.data[0]);
                all_equal &= (motion_amplitude_prev.data[1] == float_data_curr_union.data[1]);
                all_equal &= (motion_amplitude_prev.data[2] == float_data_curr_union.data[2]);
                all_equal &= (motion_amplitude_prev.data[3] == float_data_curr_union.data[3]);

                if (!all_equal) {
                  ESP_LOGD(TAG, "float_data_union: %f", float_data_curr_union.f);
                  this->motion_amplitude_sensor_->publish_state(float_data_curr_union.f);
                  
                  // cache for comparison later
                  motion_amplitude_prev.data[0] = float_data_curr_union.data[0];
                  motion_amplitude_prev.data[1] = float_data_curr_union.data[1];
                  motion_amplitude_prev.data[2] = float_data_curr_union.data[2];
                  motion_amplitude_prev.data[3] = float_data_curr_union.data[3];
                }
              }

              // --- approach status
              if (function_code == (uint8_t)FunctionCode::ACTIVELY_REPORT_COMMAND &&
                  address_code_1 == (uint8_t)PassiveReportAddressCode1::REPORT_RADAR_INFORMATION &&
                  address_code_2 == 0x07) {

                ESP_LOGD(TAG, "approach_status: %X", float_data_curr_union.data[APPROACH_DATA_IDX]);

                const char unknown_string[] = "Unknown";
                const char none_string[] = "None";
                const char close_string[] = "Close";
                const char far_string[] = "Far";
                char * state_str;

                switch (float_data_curr_union.data[APPROACH_DATA_IDX]) {
                  case (uint8_t)ApproachStatus::NONE:
                    state_str = (char*)none_string;
                    break;
                  case (uint8_t)ApproachStatus::CLOSE:
                    state_str = (char*)close_string;
                    break;
                  case (uint8_t)ApproachStatus::FAR:
                    state_str = (char*)far_string;
                    break;
                  default:
                    state_str = (char*)unknown_string;
                    break;
                }

                if (this->approach_text_sensor_ != nullptr && this->approach_text_sensor_->get_state() != state_str) {
                  ESP_LOGD(TAG, "Approach: %s", state_str);
                  this->approach_text_sensor_->publish_state(state_str);
                }
              }

              // motion/presence 
              if (function_code == (uint8_t)FunctionCode::ACTIVELY_REPORT_COMMAND &&
                  address_code_1 == (uint8_t)PassiveReportAddressCode1::REPORT_RADAR_INFORMATION &&
                  address_code_2 == (uint8_t)AddressCode2::ENVIRONMENT_STATUS) {


                bool presence = false;
                bool motion = false;

                uint32_t status = float_data_curr_union.data[0] << 16 | float_data_curr_union.data[1] << 8 | float_data_curr_union.data[2] << 0;
                switch (status) {
                  case (uint32_t)EnvironmentStatus::UNMANNED:
                    presence = false;
                    motion = false;
                    break;
                  case (uint32_t)EnvironmentStatus::PRESCENCE:
                    presence = true;
                    motion = false;
                    break;
                  case (uint32_t)EnvironmentStatus::MOTION:
                    presence = true;
                    motion = true;
                    break;
                  default:
                    break;
                }

                const char false_string[] = "FALSE";
                const char true_string[] = "TRUE";
                if (this->motion_binary_sensor_ != nullptr && this->motion_binary_sensor_->state != motion) {
                  ESP_LOGD(TAG, "motion: %s", motion ? true_string : false_string);
                  this->motion_binary_sensor_->publish_state(motion);
                }

                if (this->presence_binary_sensor_ != nullptr && this->presence_binary_sensor_->state != presence) {
                  ESP_LOGD(TAG, "presence: %s", presence ? true_string : false_string);
                  this->presence_binary_sensor_->publish_state(presence);
                }
              }
            }

          } else {
            ESP_LOGD(TAG, "CRC failed %X", calculated_crc);
          }


          // finished parsing
          pos = 0;
        }
      }
    }
  }

  return pos;
}





}  // namespace r24avd1
}  // namespace esphome
