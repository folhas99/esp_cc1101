#include "cc1101_component.h"
#include "esphome/core/log.h"

namespace esphome {
namespace cc1101 {

static const char *const TAG = "cc1101";

void CC1101Component::setup() {
  ESP_LOGI(TAG, "Inicializando CC1101...");
#ifdef USE_ESP32
  pinMode(this->gdo0_pin_, OUTPUT);
  pinMode(this->gdo2_pin_, INPUT);
#else
  pinMode(this->gdo0_pin_, INPUT);
#endif
  ELECHOUSE_cc1101.addSpiPin(sck_, miso_, mosi_, csn_, module_number_);
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
#ifndef USE_ESP32
  pinMode(gdo0_pin_, OUTPUT);
  noInterrupts();
#endif
}

void CC1101Component::end_transmission() {
#ifndef USE_ESP32
  interrupts();
  pinMode(gdo0_pin_, INPUT);
#endif
  ELECHOUSE_cc1101.setModul(module_number_);
  ELECHOUSE_cc1101.SetRx();
  ELECHOUSE_cc1101.SetRx();  // sim, duas vezes
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
