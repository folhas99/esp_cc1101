#include "cc1101_component.h"
#include "esphome/core/log.h"

namespace esphome {
namespace cc1101 {

static const char *const TAG = "cc1101";

void CC1101Component::set_pins(int sck, int miso, int mosi, int cs, int gdo0, int gdo2) {
  sck_ = sck;
  miso_ = miso;
  mosi_ = mosi;
  cs_ = cs;
  gdo0_pin_ = gdo0;
  gdo2_pin_ = gdo2;
  module_number_ = CC1101Component::cc1101_module_counter++;
}

void CC1101Component::setup() {
  ESP_LOGI(TAG, "Inicializando CC1101...");
  pinMode(this->gdo0_pin_, OUTPUT);
  pinMode(this->gdo2_pin_, INPUT);

  ELECHOUSE_cc1101.addSpiPin(sck_, miso_, mosi_, cs_, module_number_);
  ELECHOUSE_cc1101.setModul(module_number_);
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.setRxBW(bandwidth_khz_);
  ELECHOUSE_cc1101.setMHZ(freq_mhz_);
  ELECHOUSE_cc1101.SetRx();
}

void CC1101Component::update() {
  if (!rssi_on_)
    return;
  ELECHOUSE_cc1101.setModul(module_number_);
  int rssi = ELECHOUSE_cc1101.getRssi();
  if (rssi != last_rssi_) {
    publish_state(rssi);
    last_rssi_ = rssi;
  }
}

void CC1101Component::begin_transmission() {
  ELECHOUSE_cc1101.setModul(module_number_);
  ELECHOUSE_cc1101.SetTx();
  pinMode(gdo0_pin_, OUTPUT);
  noInterrupts();
}

void CC1101Component::end_transmission() {
  interrupts();
  pinMode(gdo0_pin_, INPUT);
  ELECHOUSE_cc1101.setModul(module_number_);
  ELECHOUSE_cc1101.SetRx();
  ELECHOUSE_cc1101.SetRx();
}

void CC1101Component::set_freq(float freq) {
  freq_mhz_ = freq;
  ELECHOUSE_cc1101.setModul(module_number_);
  ELECHOUSE_cc1101.setMHZ(freq);
}

void CC1101Component::set_bw(float bw) {
  bandwidth_khz_ = bw;
  ELECHOUSE_cc1101.setModul(module_number_);
  ELECHOUSE_cc1101.setRxBW(bw);
}

}  // namespace cc1101
}  // namespace esphome
