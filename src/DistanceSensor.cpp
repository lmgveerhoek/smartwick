#pragma once
#include "Arduino.h"
#include "Definitions.h"

class DistanceSensor {
  protected:
    byte echopin, triggerpin;
  public:
    int distance = 0;
    DistanceSensor(byte triggerpin, byte echopin)
    {
      this->triggerpin = triggerpin;
      this->echopin = echopin;
      init();
    }
    void init()
    {
      pinMode(triggerpin, OUTPUT);
      pinMode(echopin, INPUT);
    }
    void measureDistance()
    {
      digitalWrite(triggerpin, LOW);
      digitalWrite(triggerpin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerpin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      long duration = pulseIn(echopin, HIGH);
      // Calculating the distance
      distance = duration * 0.034 / 2;
    }
};