#include "Arduino.h"

static const String menus[] =
{
  "SmartWick Menu",
  "Spray 1:",
  "Spray 2:",
  "Delay:",
  "Charges:"
};

#define MAIN_MENU_SIZE 5
static const String main_items[] =
{
  "Set spray 1",
  "Set spray 2",
  "Set delay",
  "Reset sprays",
  "Exit"
};

#define RESET_MENU_ITEMS 2
static const String reset_items[] = 
{
  "Confirm",
  "Abort"
};

#define DELAY_MENU_ITEMS 4
static const String delay_items[] = 
{
  "30 seconds",
  "60 seconds",
  "90 seconds",
  "Return"
};

#define SPRAY_MENU_ITEMS 7