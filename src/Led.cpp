// addopted from  https://roboticsbackend.com/arduino-object-oriented-programming-oop/
#include "Arduino.h"

class LED {
  protected:
    byte pin;
    unsigned long lastMillis;
  public:
    LED() {}
    LED(byte pin) {
      this->pin = pin;
      lastMillis = 0;
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
    void analogOn(byte val) {
      analogWrite(pin,val);
    }
};
