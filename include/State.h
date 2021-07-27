#pragma once
#include "Arduino.h"

// built upon the code explained at 
// https://create.arduino.cc/projecthub/DGarbanzo/object-oriented-state-machine-efbc96

class State
{
protected:
  unsigned long lastMillis; 
public:
  State(); 
  virtual ~State() {}
  virtual void enter(){};
  virtual State *run() = 0;
};