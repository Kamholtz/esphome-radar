#include "r24avd1.h"
#include "crc.h"

namespace esphome {
namespace r24avd1 {

static const char *const TAG = "r24avd1";

void R24AVD1Component::setup() {
  // nothing to do
}
void R24AVD1Component::dump_config() {
  // not implemented
}
void R24AVD1Component::loop() {
  const int max_line_length = 80;
  static uint8_t buffer[max_line_length];

  int pos = 0;
  while (available()) {
    pos = this->readline_(read(), buffer, max_line_length, pos);
  }
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
              ESP_LOGI(TAG, "Data len (%d) too long, discarding", data_len);
            } else  {
              // we don't expect data_len to be larger than a 4 byte float
              float_data float_data_union;
              for (uint8_t data_ii = 0; data_ii < data_len; data_ii++) {
                float_data_union.data[data_ii] = buffer[DATA_START_IDX + data_ii];
              }

              ESP_LOGD(TAG, "float_data_union.data: %X %X %X %X", float_data_union.data[0], float_data_union.data[1], float_data_union.data[2], float_data_union.data[3]);
              ESP_LOGD(TAG, "float_data_union: %f", float_data_union.f);
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
