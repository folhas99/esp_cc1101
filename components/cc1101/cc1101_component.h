#pragma once
#include "esphome/core/component.h"

namespace esphome {
namespace cc1101 {

class CC1101Component : public Component {
 public:
  void setup() override;
  void set_pins(int sck, int miso, int mosi, int cs, int gdo0);
  void set_bandwidth(float bw);
  void set_frequency(float mhz);
  void send_byron(uint32_t address, uint8_t command);

 protected:
  int sck_, miso_, mosi_, cs_, gdo0_;
  float bandwidth_khz_, freq_mhz_;
  int module_ = 0;
};

}  // namespace cc1101
}  // namespace esphome
