#include "Arduino.h"
#include "Common.h"
#include "Menu.cpp"
#include "Idle.cpp"
#include <Triggered.cpp>
#include <UseUnknown.cpp>
#include <InUseOne.cpp>
#include <InUseTwo.cpp>
#include <Cleaning.cpp>
#include <Initializing.cpp>

// setup LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// initialize temperature sensor
Tempsensor tempsensor(TEMP_SENSOR); 
MotionSensor motionSensor(PIR_SENSOR);
DistanceSensor distanceSensor(ULTRASOUND_TRIGGER, ULTRASOUND_ECHO);
LightSensor lightSensor(LDR_SENSOR);

// initialize LEDs
LED builtin(LED_BUILTIN);
RGBLED statusLight(RED_LED, GREEN_LED, BLUE_LED);

// initialize buttons
Button buttonL(LEFT_BUTTON);
Button buttonR(RIGHT_BUTTON);
Button buttonM(SPRAY_BUTTON);
Button buttonF(FLUSH_BUTTON);

// initialize smell spreader
Airwick airwick(MOSFET); 

// declare memory manager
MemoryManager memManager; 

// states have to be declared here
Menu menuState;
Idle idleState; 
Triggered triggerState;
UseUnknown unkownState;
InUseOne useOneState;
InUseTwo useTwoState;
Cleaning cleaningState;
Initializing initializeState;

// pointers to states, so every state can access them
State* menu = &menuState; 
State* idle = &idleState;
State* triggered = &triggerState;
State* useUnkown = &unkownState;
State* inUseOne = &useOneState;
State* inUseTwo = &useTwoState;
State* cleaning = &cleaningState;
State* initializing = &initializeState;

// other needed variables
byte sprayAmount = 1;
bool personDetected = false;
unsigned long lastMillisTemp = 0;
int lastTemp = 0;

// statemachine initialization
bool isChanged = true;
State *state = initializing;
State *lastState = state;

// functions that will be called by interrupts
void manualSpray()
{
  // if pressed, then change state to triggering
  if (buttonM.returnButtonState)
  {
    sprayAmount = 1;
    lastState = triggered;
    isChanged = true;
  }
}

void distanceInterrupt()
{
  if (!personDetected) {
    personDetected = true;
  }
}

void setup()
{
  // attach interrupt to manual override and distance sensor
  attachInterrupt(digitalPinToInterrupt(SPRAY_BUTTON), manualSpray, LOW);
  attachInterrupt(digitalPinToInterrupt(PIR_SENSOR), distanceInterrupt, HIGH);
  // initialize LCD
  lcd.begin(16, 2);
  // initialize memory manager
  memManager = MemoryManager();
  // load stored settings
  triggerState.triggerDelay = memManager.sprayDelay;
}

void loop()
{
  // update button and distance sensor readings every cycle
  buttonL.update();
  buttonR.update();
  buttonM.update();
  buttonF.update();
  motionSensor.measureMotion();

  // if state changed last time, call enter
  if (isChanged) {
    lastState->enter();
  }
  // call run repeatedly
  state = lastState->run();
  // if state changed, record it;
  isChanged = (state != lastState);
  // reset lastState to current
  lastState = state;
}