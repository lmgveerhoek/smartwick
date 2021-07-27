#include "Common.h"
#include "Definitions.h"

class UseUnknown : public State {
  public:
    unsigned long triggerDelay = DEFAULT_TRIGGER_DELAY;
    State* run() {
      // if a button is pressed, return to menu
      if (buttonL.returnButtonState || buttonR.returnButtonState) 
        return menu; 
      // wait a certain time, before checking how the toilet will be used
      if (millis() - lastMillis > TIMEOUT_DOOR) { 
        lightSensor.measureLight();
        if (lightSensor.lightState) { 
          distanceSensor.measureDistance();
          if(distanceSensor.distance > DISTANCE_DOOR)
            return cleaning;
          else
            return inUseOne;
        }
        return initializing;
      }
      // set color status light and turn it on
      statusLight.setColor(WHITE);
      statusLight.blink(3000, 100);

      updateTemp();
      return this;
    }
    void enter() {
      clearSecondLine();
      lcd.setCursor(0,1);
      lcd.print(F("Use unknown"));
      lastMillis = millis();
    }
};



