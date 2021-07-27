// roboticsbackend.com
// adapted to use pull up resistors embedded in the ATMEL chip 
#pragma once
#include "Arduino.h"

class Button {
  protected:
    byte pin;
    unsigned long currentMillis = 0;
    unsigned long previousMillis = 0;
    unsigned long buttonDownMillis = 0L;
    const unsigned long returnInverval = 0;
  public:
    bool buttonState = true;
    bool returnButtonState = false;
    Button(byte pin) {
      this->pin = pin;
      init();
    }
    void init() {
      pinMode(pin, INPUT_PULLUP);
      update();
    }
    void update() {
      // Did the button change
      currentMillis = millis(); 
      if (digitalRead(pin) != buttonState) {
        buttonState = !buttonState;
        // Was the button released
        if (buttonState) {
          returnButtonState = false;
        }
        // Was the button pushed
        else {
          buttonDownMillis = currentMillis;
          returnButtonState = true;
        }
      }
      // Check if button was pushed and time for return action
      else if (returnButtonState) {
        if (currentMillis - buttonDownMillis >= returnInverval) {
          returnButtonState = false;
        }
      }
    }
};