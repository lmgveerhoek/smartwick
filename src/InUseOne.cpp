#include "Common.h"
#include "Definitions.h"

class InUseOne : public State {
  public:
    unsigned long triggerDelay = DEFAULT_TRIGGER_DELAY;
    State* run() {
      // if a button is pressed, return to menu
      if (buttonL.returnButtonState || buttonR.returnButtonState) 
        return menu; 
      // if a person remains in the toilet, assume they are taking a number two
      if (millis() - lastMillis > ONE_TIME) {
        return inUseTwo; 
      }
      // toilet was flushed , set spray amount and go to triggered
      if (buttonF.returnButtonState) {
        sprayAmount = memManager.toSpray1;
        return triggered;
      }
      // set color status light and turn it on
      statusLight.setColor(YELLOW);
      statusLight.blink(3000, 100);
      updateTemp();
      return this;
    }
    void enter() {
      clearSecondLine();
      lcd.setCursor(0,1);
      lcd.print(F("In use #1"));
      lastMillis = millis();
    }
};