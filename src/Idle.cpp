#include "Common.h"

class Idle : public State {
  public:
    State* run()
    {
      // return to menu if a button is pressed
      if (buttonL.returnButtonState || buttonR.returnButtonState) 
        return menu; 
      // personDetected can be set to true by an interrupt
      // if true -> go to use unknown
      if(personDetected){
        personDetected = false;
        return useUnkown;
      }
      statusLight.setColor(GREEN);
      statusLight.blink(3000, 100);
      updateTemp(); 
      return idle; 
    }
    void enter()
    {
      clearSecondLine();
      lcd.setCursor(0,1);
      lcd.print(F("Spray left: "));
      // Retrieve remaining perfume from memory
      lcd.print(memManager.sprayLeft);
      this->lastMillis = millis();
    }
};