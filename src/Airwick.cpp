#pragma once
#include "Arduino.h"

class Airwick {
  protected:
    byte pin;
  public:
    Airwick(byte pin) {
      this->pin = pin;
      init();
    }
    void init() {
      pinMode(pin, OUTPUT);
      off();
    }
    void on() {
      digitalWrite(pin, HIGH);
    }
    void off() {
      digitalWrite(pin, LOW);
    }
}; 
