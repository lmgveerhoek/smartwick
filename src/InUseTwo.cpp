#include "Common.h"
#include "Definitions.h"

class InUseTwo : public State {
  public:
    unsigned long triggerDelay = DEFAULT_TRIGGER_DELAY;
    State* run() {
      // return to menu if a button is pushed
      if (buttonL.returnButtonState || buttonR.returnButtonState) 
        return menu; 
      // toilet was flushed , set spray amount and go to triggered
      if (buttonF.returnButtonState){
        sprayAmount = 2;
        return triggered; 
      }
      // after a certain amount of time, assume someone forgot to flush
      if (millis() - lastMillis > TWO_TIME) {
        sprayAmount = memManager.toSpray2;
        return triggered; 
      }
      statusLight.setColor(CHOCOLATE);
      statusLight.blink(3000, 100);
      updateTemp();
      return this;
    }
    void enter() {
      clearSecondLine();
      lcd.setCursor(0,1);
      lcd.print(F("In use #2"));
      lastMillis = millis();
    }
};