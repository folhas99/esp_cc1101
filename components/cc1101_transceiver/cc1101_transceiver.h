#pragma once

#include "esphome/core/component.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

class CC1101Component : public esphome::Component {
 public:
  CC1101Component(int sck, int miso, int mosi, int csn, int gdo0, int gdo2, float mhz, int bandwidth)
      : sck_(sck), miso_(miso), mosi_(mosi), csn_(csn), gdo0_(gdo0), gdo2_(gdo2),
        freq_mhz_(mhz), bandwidth_khz_(bandwidth) {}

  void setup() override {
    ELECHOUSE_cc1101.setSpiPin(sck_, miso_, mosi_, csn_);
    ELECHOUSE_cc1101.Init();
    ELECHOUSE_cc1101.setMHZ(freq_mhz_);
    ELECHOUSE_cc1101.setRxBW(bandwidth_khz_);
    ELECHOUSE_cc1101.setGDO(gdo0_, gdo2_);
  }

  void beginTransmission() {
    ELECHOUSE_cc1101.SetTx();
  }

  void endTransmission() {
    ELECHOUSE_cc1101.SetRx();
  }

 private:
  int sck_, miso_, mosi_, csn_, gdo0_, gdo2_;
  float freq_mhz_;
  int bandwidth_khz_;
};
