#include "cc1101_component.h"
#include "esphome/core/log.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

namespace esphome {
namespace cc1101 {

static const char *const TAG = "cc1101";

void CC1101Component::set_pins(int sck, int miso, int mosi, int csn, int gdo0) {
  sck_ = sck;
  miso_ = miso;
  mosi_ = mosi;
  csn_ = csn;
  gdo0_ = gdo0;
}

void CC1101Component::set_bandwidth(float bw) {
  bandwidth_khz_ = bw;
}

void CC1101Component::set_frequency(float mhz) {
  freq_mhz_ = mhz;
}

void CC1101Component::setup() {
  pinMode(gdo0_, OUTPUT);
  ELECHOUSE_cc1101.addSpiPin(sck_, miso_, mosi_, csn_, module_);
  ELECHOUSE_cc1101.setModul(module_);
  ELECHOUSE_cc1101.Init();
  ELECHOUSE_cc1101.setRxBW(bandwidth_khz_);
  ELECHOUSE_cc1101.setMHZ(freq_mhz_);
  ELECHOUSE_cc1101.SetRx();
  ESP_LOGI(TAG, "CC1101 initialized at %.2f MHz", freq_mhz_);
}

void CC1101Component::send_byron(uint32_t address, uint8_t command) {
  ESP_LOGI(TAG, "Sending ByronSX: address=0x%08X, command=0x%02X", address, command);
  ELECHOUSE_cc1101.setModul(module_);
  ELECHOUSE_cc1101.SetTx();
  ELECHOUSE_cc1101.Send0(address, command);  // Exemplo genérico
  ELECHOUSE_cc1101.SetRx();
}

}  // namespace cc1101
}  // namespace esphome
