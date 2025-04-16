#pragma once
#include "esphome/core/component.h"
#include "cc1101.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

namespace esphome {
namespace cc1101 {

class CC1101Component : public CC1101 {
 public:
  CC1101Component(int sck, int miso, int mosi, int csn, int gdo0, int gdo2, float bandwidth, float freq)
      : sck_(sck), miso_(miso), mosi_(mosi), csn_(csn), gdo0_(gdo0), gdo2_(gdo2),
        bandwidth_(bandwidth), freq_(freq) {}

  void setup() override {
    ELECHOUSE_cc1101.setSpiPin(miso_, mosi_, sck_, csn_);
    ELECHOUSE_cc1101.Init();
    ELECHOUSE_cc1101.setMHZ(freq_);
    ELECHOUSE_cc1101.setRxBW(bandwidth_);
    ELECHOUSE_cc1101.SetRx();
  }

  void loop() override {}

  void beginTransmission() override {
    ELECHOUSE_cc1101.SetTx();
  }

  void endTransmission() override {
    ELECHOUSE_cc1101.SetRx();
  }

 protected:
  int sck_, miso_, mosi_, csn_, gdo0_, gdo2_;
  float bandwidth_, freq_;
};

}  // namespace cc1101
}  // namespace esphome
