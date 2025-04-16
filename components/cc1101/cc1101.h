#pragma once
#include "esphome/core/component.h"

class CC1101 : public esphome::Component {
 public:
  virtual void beginTransmission() = 0;
  virtual void endTransmission() = 0;
};
