#pragma once
#include "Arduino.h"
#include <LED.cpp>

// pre-configured colors
static byte RED[3] = {255, 0, 0};
static byte GREEN[3] = {0, 255, 0};
static byte BLUE[3] = {0, 0, 255};
static byte ORANGE[3] = {255, 165, 0};
static byte CHOCOLATE[3] = {210, 105, 30};
static byte CYAN[3] = {0, 255, 255};
static byte YELLOW[3] = {255, 255, 0};
static byte MAGENTA[3] = {255, 0, 255};
static byte WHITE[3] = {255, 255, 255};

class RGBLED {
  protected:
    LED redLED;
    LED greenLED;
    LED blueLED;
    byte rgb[3] = {0, 0, 0};
    unsigned long lastMillis;
  public:
    RGBLED(byte pinR, byte pinG, byte pinB) {
      redLED = LED(pinR);
      greenLED = LED(pinG);
      blueLED = LED(pinB);
      lastMillis = 0;
      init();
    }
    void init() {
      off();
    }
    void off() {
      color(0, 0, 0);
    }
    // LED will turn on and use last chosen color
    void on() {
      color(rgb[0], rgb[1], rgb[2]);
    }
    void setColor(byte r, byte b, byte g) {
      this->rgb[0] = (byte)r;
      this->rgb[1] = (byte)g; 
      this->rgb[2] = (byte)b;
    }
    void setColor(byte rgb[3]) {
      setColor(rgb[0], rgb[1], rgb[2]);
    }
    void color(byte r, byte b, byte g) {
      redLED.analogOn(r);
      greenLED.analogOn(g);
      blueLED.analogOn(b);
    }
    void blink(unsigned int onInterval, unsigned int offInterval) {
      if (millis() - lastMillis >= onInterval) {
        lastMillis = millis();
        this->on();
      }
      else if (millis() - lastMillis > offInterval) {
        this->off();
      }
    }
};