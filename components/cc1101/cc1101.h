#pragma once

#include "esphome.h"
#include "cc1101.h"  // tua biblioteca nativa do repositório

class CC1101Component : public esphome::Component {
 public:
  CC1101Component(int sck, int miso, int mosi, int csn, int gdo0, int gdo2, float bandwidth, float frequency)
      : sck_(sck), miso_(miso), mosi_(mosi), csn_(csn), gdo0_(gdo0), gdo2_(gdo2),
        bandwidth_(bandwidth), frequency_(frequency) {}

  void setup() override {
    cc1101.set_pins(sck_, miso_, mosi_, csn_, gdo0_, gdo2_);
    cc1101.setup();
    cc1101.set_rx_bandwidth(bandwidth_);
    cc1101.set_carrier_freq_MHz(frequency_);
    cc1101.set_receive();  // coloca em modo recepção por padrão
  }

  void beginTransmission() {
    cc1101.set_transmit();  // muda para modo de transmissão
  }

  void endTransmission() {
    cc1101.set_receive();   // volta a escutar
  }

 protected:
  int sck_, miso_, mosi_, csn_, gdo0_, gdo2_;
  float bandwidth_;
  float frequency_;
  CC1101 cc1101;
};

// helper para usar em lambda
CC1101Component *get_cc1101(CC1101Component *comp) {
  return comp;
}
