#include "Common.h"
#include "Definitions.h"

class Cleaning : public State {
  public:
    unsigned long triggerDelay = DEFAULT_TRIGGER_DELAY;
    State* run() {
      // if a button is pressed, return to menu
      if (buttonL.returnButtonState || buttonR.returnButtonState) 
        return menu; 
      // return to initializing after a time-out
      if (millis() - lastMillis > CLEANING_TIME) {
        return initializing;
      }
      // return to initializing after flushing
      if (buttonF.returnButtonState) {
        return initializing; 
      }
      // set color status light and turn it on
      statusLight.setColor(BLUE);
      statusLight.blink(3000, 100);
      updateTemp();
      return this;
    }
    void enter() {
      clearSecondLine();
      lcd.setCursor(0,1);
      lcd.print(F("Cleaning"));
      lastMillis = millis();
    }
};