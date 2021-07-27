#include "Arduino.h"
#include <Airwick.cpp>
#include <RGBLED.cpp>
#include "State.h"
#include "LiquidCrystal.h"
#include "DallasTemperature.h"
#include <Button.cpp>
#include <Tempsensor.cpp>
#include <MotionSensor.cpp>
#include <DistanceSensor.cpp>
#include <LightSensor.cpp>
#include <MemoryManager.cpp>
#include "Definitions.h"

// Pointers to different states, bit of a hack
extern State *menu;
extern State *idle;
extern State *triggered; 
extern State *useUnkown;
extern State *inUseOne;
extern State *inUseTwo;
extern State *cleaning;
extern State *initializing;

extern LiquidCrystal lcd;
extern Tempsensor tempsensor;
extern MotionSensor motionSensor;
extern DistanceSensor distanceSensor;
extern LightSensor lightSensor;

extern Button buttonL;
extern Button buttonR;
extern Button buttonM;
extern Button buttonF; 

extern Airwick airwick; 
extern MemoryManager memManager; 

extern RGBLED statusLight; 

extern byte sprayAmount;
extern bool personDetected;
extern unsigned long lastMillisTemp;
extern int lastTemp;

void updateTemp();
void clearSecondLine();