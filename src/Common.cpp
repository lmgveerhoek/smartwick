  #include "Common.h"

  void updateTemp() 
  {
    if (millis() - lastMillisTemp >= REQUEST_TEMP)
    {
      // only update temperature if it has changed 
      int currentTemp = (int)tempsensor.getTemperature();
      if (lastTemp != currentTemp) {
        // Clear first two characters
        lcd.setCursor(0,0);
        lcd.print(F("  "));
        // update the temperature on lcd
        lcd.setCursor(0,0);
        lcd.print(currentTemp);
        lastTemp = currentTemp;
      }
      // request new temperature asynchronously, so it can be printed next time
      tempsensor.requestNewTemperature(); 
      lastMillisTemp = millis();
    }
  }

  void clearSecondLine()
  {
    lcd.setCursor(0,1);
    lcd.print(F("                "));
  }