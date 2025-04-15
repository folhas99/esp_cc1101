#pragma once

#include "esphome.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

class CC1101Component : public esphome::Component {
 public:
  CC1101Component(int sck, int miso, int mosi, int csn, int gdo0, int gdo2, float bandwidth, float frequency)
      : sck_(sck), miso_(miso), mosi_(mosi), csn_(csn), gdo0_(gdo0), gdo2_(gdo2),
        bandwidth_(bandwidth), frequency_(frequency) {}

  void setup() override {
    ELECHOUSE_cc1101.setSpiPin(sck_, miso_, mosi_, csn_);
    ELECHOUSE_cc1101.init();
    ELECHOUSE_cc1101.setMHZ(frequency_);
    ELECHOUSE_cc1101.setRxBW(bandwidth_);
    ELECHOUSE_cc1101.SetRx();
  }

  void beginTransmission() {
    ELECHOUSE_cc1101.SetTx();
  }

  void endTransmission() {
    ELECHOUSE_cc1101.SetRx();
  }

 protected:
  int sck_, miso_, mosi_, csn_, gdo0_, gdo2_;
  float bandwidth_;
  float frequency_;
};

CC1101Component *get_cc1101(CC1101Component *comp) {
  return comp;
}
