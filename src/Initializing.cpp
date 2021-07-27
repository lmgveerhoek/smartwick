#include "Common.h"

class Initializing : public State {
  public:
    State* run() {
      if (buttonL.returnButtonState || buttonR.returnButtonState) 
        return menu; 
      // return to idle once the initialization time runs out
      if (millis() - lastMillis > INITIALIZE_TIME) {
        personDetected = false;
        return idle; 
      }
      statusLight.setColor(RED);
      statusLight.blink(3000, 100);
      updateTemp();
      return this;
    }
    void enter() {
      lcd.clear();
      // set the lcd up for 
      lcd.setCursor(0,0);
      lcd.print(F("  "));
      lcd.print((char)223);
      lcd.print(F("C"));
      lcd.setCursor(0,0);
      lcd.print(lastTemp);
      clearSecondLine();
      lcd.setCursor(0,1);
      lcd.print(F("Initializing..."));
      lastMillis = millis();
    }
};