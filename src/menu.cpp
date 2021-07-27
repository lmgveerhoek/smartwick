#include "Common.h"
#include <Menus.cpp>
// MenuState menuState;  

enum MenuState {
  MAIN,
  SET_SPRAY_1,
  SET_SPRAY_2,
  SET_DELAY,
  RESET_SPRAY,
  EXIT
};

class Menu : public State {
  private: 
    unsigned long lastInteraction; 
    byte menuState;
    byte menuItem;
    bool enterMenu;
    bool itemChanged;
    bool executeAction;
    // give pointers to the items to update the menu
    void updateMenu(const String& menu, const String& item)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(menu);
      updateItem(item);
    }
    void updateItem(const String& item)
    {
      clearSecondLine();
      lcd.setCursor(0,1);
      lcd.print(F(">"));
      lcd.print(item);
    }
    void mainMenu() 
    {
      if (enterMenu) {
        menuItem = 0;
        updateMenu(menus[MAIN], main_items[0]);
        enterMenu = false;
      } else if (itemChanged) {
        updateItem(main_items[menuItem % MAIN_MENU_SIZE]);
        itemChanged = false;
      } else if (executeAction) {
        enterMenu = true;
        executeAction = false;
        switch(menuItem % MAIN_MENU_SIZE) {
          case 0:
            menuState = SET_SPRAY_1;
            break;
          case 1: 
            menuState = SET_SPRAY_2;
            break;
          case 2:
            menuState = SET_DELAY;
            break;
          case 3:
            menuState = RESET_SPRAY;
            break;
          case 4:
            menuState = EXIT; 
            break; 
          default:
            menuState = MAIN;
            break;
        }
      }
    }
    void sprayMenu(byte n)
    {
      if (enterMenu) {
        menuItem = 0;
        updateMenu(menus[menuState],"");
        lcd.setCursor(9,0);
        lcd.print(memManager.getToSpray(n));
        lcd.print(F(" times"));
        itemChanged = true;
        enterMenu = false;
        return;
      } else if (itemChanged) {
        updateItem("");
        lcd.setCursor(1,1);
        if (menuItem % SPRAY_MENU_ITEMS < SPRAY_MENU_ITEMS - 1)
          lcd.print(menuItem % SPRAY_MENU_ITEMS);
        else {
          lcd.print(F("Return"));
        }
        itemChanged = false;
        return;
      }
      if (executeAction) {
        enterMenu = true;
        executeAction = false;
        switch(menuItem % SPRAY_MENU_ITEMS) {
          case 0 ... 5:
            // store amount of sprays in memory
            memManager.setToSpray(n, menuItem % SPRAY_MENU_ITEMS);
            confirmed();
            menuState = MAIN;
            break;
          case 6: 
            lcd.print(F("Returning..."));
            menuState = MAIN;
            break;
          default:
            menuState = MAIN;
            break;
        }
      }
    }
    void delayMenu()
    {
      if (enterMenu) {
        menuItem = 0;
        updateMenu(menus[SET_DELAY],delay_items[0]);
        lcd.setCursor(7,0);
        lcd.print(memManager.sprayDelay / 1000);
        lcd.print(F(" sec"));
        enterMenu = false;
        return;
      } else if (itemChanged) {
          updateItem(delay_items[menuItem % DELAY_MENU_ITEMS]);
          itemChanged = false;
          return;
      }
      if (executeAction) {
        enterMenu = true;
        executeAction = false;
        switch(menuItem % DELAY_MENU_ITEMS) {
          case 0 ... 2:
            // store delay in memory
            memManager.setDelay((unsigned long)((menuItem % DELAY_MENU_ITEMS) + 1) * DEFAULT_TRIGGER_DELAY);
            confirmed();
            menuState = MAIN;
            break;
          case 3:
            menuState = MAIN;
            break;
          default:
            menuState = MAIN;
            break;
        }
      }
    }
    void resetSprayMenu()
    {
      if (enterMenu) {
        menuItem = 0;
        updateMenu(menus[RESET_SPRAY],reset_items[0]);
        lcd.setCursor(9,0);
        lcd.print(memManager.sprayLeft);
        enterMenu = false;
        return;
      } else if (itemChanged) {
        updateItem(reset_items[menuItem % RESET_MENU_ITEMS]);
        itemChanged = false;
        return;
      }
      if (executeAction) {
        enterMenu = true;
        executeAction = false;
        switch(menuItem % RESET_MENU_ITEMS) {
          case 0:
            lcd.clear();
            lcd.print(F("Resetting..."));
            memManager.resetSpray(); 
            delay(1500);
            menuState = MAIN;
            break;
          case 1:
            lcd.clear();
            lcd.print(F("Aborting..."));
            delay(1500);
            menuState = MAIN;
            break;
          default:
            menuState = MAIN;
            break;
        }
      }
    }
    void exitMenu()
    {
      if (enterMenu) {
        lcd.clear();
        lcd.print(F("Exiting..."));
        enterMenu = false;
        delay(1500);
      }  
    }
    void confirmed()
    {
      lcd.clear();
      lcd.print(F("Confirmed..."));
      delay(1500);
    }
  public:
    void enter()
    {
      menuState = MAIN;
      menuItem = 0;
      enterMenu = true;
      itemChanged = false;
      executeAction = false;
      lcd.clear();
      lastMillis = millis();
    }
    State* run()
    {
      // if last interaction was too long ago, return to initializing
      if (millis() - lastMillis > MENU_TIMEOUT) {
        return initializing;
      }
      if (buttonL.returnButtonState) {
          menuItem++; 
          itemChanged = true;
          lastMillis = millis(); 
      }
      if (buttonR.returnButtonState) {
          executeAction = true;
          lastMillis = millis();
      }
      statusLight.setColor(CYAN);
      statusLight.blink(3000, 100);
      //check the state of the menu
      switch (menuState) {
        case MAIN:
          mainMenu(); 
          break;
        case SET_SPRAY_1:
          sprayMenu(1); 
          break;
        case SET_SPRAY_2:
          sprayMenu(2);
          break;
        case SET_DELAY:
          delayMenu();
          break;
        case RESET_SPRAY:
          resetSprayMenu(); 
          break;
        case EXIT:
          exitMenu();
          return initializing;
        default:
          menuState = EXIT;
          break;
      }
      return menu; 
    }
};