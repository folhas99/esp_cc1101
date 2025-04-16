#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

namespace esphome {
namespace cc1101 {

class CC1101Component : public PollingComponent, public sensor::Sensor {
 public:
  CC1101Component() : PollingComponent(100) {}

  void setup() override;
  void update() override;

  void begin_transmission();
  void end_transmission();

  void set_freq(float freq);
  void set_bw(float bw);

  void set_pins(int sck, int miso, int mosi, int cs, int gdo0, int gdo2);
  void set_bandwidth(float bw) { bandwidth_khz_ = bw; }
  void set_frequency(float freq) { freq_mhz_ = freq; }

  static int cc1101_module_counter;

 protected:
  int sck_, miso_, mosi_, cs_, gdo0_pin_, gdo2_pin_;
  float bandwidth_khz_;
  float freq_mhz_;
  bool rssi_on_ = true;
  int module_number_;
  int last_rssi_ = 0;
};

inline int CC1101Component::cc1101_module_counter = 0;

}  // namespace cc1101
}  // namespace esphome
