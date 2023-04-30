#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"

namespace esphome {
namespace r24avd1 {


class R24AVD1Component : public Component, public uart::UARTDevice {


 public:
  void setup() override;
  void dump_config() override;
  void loop() override;

}

}  // namespace r24avd1
}  // namespace esphome
