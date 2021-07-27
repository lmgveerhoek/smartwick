#include "Common.h"

class Triggered : public State {
  public:
    byte triggerTimes = 0; 
    unsigned long triggerDelay = DEFAULT_TRIGGER_DELAY;
    unsigned long lastSpray = 0; 
    bool initialized = false;
    bool inbetween = false;
    State* run() {
      // if a button is pressed, return to menu
      if (buttonL.returnButtonState || buttonR.returnButtonState) 
        return menu; 
      // depending on the amount of times that have to be sprayed act accordingly
      switch(triggerTimes) {
        case 0:
          return initializing;
        case 1 ... 5:
          statusLight.setColor(MAGENTA);
          statusLight.blink(200, 100);
          // start the Airwick after some time (delay - the initialization period)
          // so it will actually spray at the desired delay.
          if (millis() - lastMillis > triggerDelay - FRESHNER_INIT) {
            if (!initialized) {
              lastSpray = millis();
              initialized = true; 
            } else if (inbetween) {
              // let the airwick turn off, so it can be powered up again
              delay(FRESHNER_DELAY);
              inbetween = false;
            }
            trigger();
          }
          return this;
        default:
          return this;
      }
    }
    void enter() {
      triggerTimes = sprayAmount; 
      lcd.clear();
      lcd.print(F("Triggering..."));
      lcd.setCursor(0,1);
      lcd.print(F("Times:"));
      lcd.print(triggerTimes);
      initialized = false;
      lastMillis = millis();
    }
    void trigger() {
      // Turn the airwick off after the initialization period
      if (millis() - lastSpray > FRESHNER_INIT) {
        airwick.off(); 
        // The perfume count can be lowered
        memManager.decreaseSpray(); 
        if (triggerTimes > 0) {
          triggerTimes--;
          lcd.setCursor(6,1);
          lcd.print(triggerTimes);
          inbetween = true;
          lastSpray = millis();
        }
      } else {
        airwick.on();
      }
    }
};



