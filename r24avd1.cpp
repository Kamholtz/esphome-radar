#include "r24avd1.h"

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

  while (available()) {
    this->readline_(read(), buffer, max_line_length);
  }
}

void R24AVD1Component::readline_(int readch, uint8_t *buffer, int len) {
  static int pos = 0;

  if (readch >= 0) {
    ESP_LOGD(TAG, "%c", readch);
    if (pos < len - 1) {
      buffer[pos++] = readch;
      buffer[pos] = 0;
    } else {
      pos = 0;
    }
    if (pos >= 4) {
      if (buffer[pos - 4] == 0xF8 && buffer[pos - 3] == 0xF7 && buffer[pos - 2] == 0xF6 && buffer[pos - 1] == 0xF5) {
        // ESP_LOGV(TAG, "Will handle Periodic Data");
        // this->handle_periodic_data_(buffer, pos);
        pos = 0;  // Reset position index ready for next time

        // if (this->sensor1_sensor_ != nullptr) {
        //   int new_sensor1 = 0x01;
        //   if (this->sensor1_sensor_->get_state() != new_sensor1)
        //     this->sensor1_sensor_->publish_state(new_sensor1);
        // }

      } else if (buffer[pos - 4] == 0x04 && buffer[pos - 3] == 0x03 && buffer[pos - 2] == 0x02 &&
                 buffer[pos - 1] == 0x01) {
        // ESP_LOGV(TAG, "Will handle ACK Data");
        // this->handle_ack_data_(buffer, pos);
        pos = 0;  // Reset position index ready for next time
      }
    }
  }
}





}  // namespace r24avd1
}  // namespace esphome
