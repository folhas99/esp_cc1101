#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

namespace esphome {
namespace cc1101 {

class CC1101Component : public PollingComponent, public sensor::Sensor {
 public:
  CC1101Component(int sck, int miso, int mosi, int csn, int gdo0, int gdo2, float bandwidth_khz, float freq_mhz)
      : PollingComponent(100),
        sck_(sck),
        miso_(miso),
        mosi_(mosi),
        csn_(csn),
        gdo0_pin_(gdo0),
        gdo2_pin_(gdo2),
        bandwidth_khz_(bandwidth_khz),
        freq_mhz_(freq_mhz),
        rssi_on_(true),
        module_number_(CC1101Component::cc1101_module_counter++) {}

  void setup() override;
  void update() override;

  void begin_transmission();
  void end_transmission();

  void set_freq(float freq);
  void set_bw(float bw);

  static int cc1101_module_counter;

 protected:
  int sck_, miso_, mosi_, csn_, gdo0_pin_, gdo2_pin_;
  float bandwidth_khz_;
  float freq_mhz_;
  bool rssi_on_;
  int module_number_;
  int last_rssi_ = 0;
};

inline int CC1101Component::cc1101_module_counter = 0;

}  // namespace cc1101
}  // namespace esphome
