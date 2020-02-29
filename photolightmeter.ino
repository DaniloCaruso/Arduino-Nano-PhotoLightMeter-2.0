#include <math.h>
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <BH1750.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

BH1750          lightSensor;
#include "config.h"
#include "setup.h"

Adafruit_ST7735 display     = getDisplay();


#include "utils.h"
#include "measure.manager.h"
#include "operation.manager.h"
#include "view.manager.h"


void setup() {
  
  Serial.begin(9600);
  Wire.begin();
  initializeDisplay(display);
  lightSensor.configure(BH1750::ONE_TIME_HIGH_RES_MODE_2);
  lightSensor.begin();
  //initializeSensor(lightSensor);   
  initFromEPROM();
  setupButtonPin();
  initializeDefaults();
  evaluateBattVolts();
}

void loop() {
  manageBattVolts();
  uint16_t luxValue = getLuxFromSensor();
  uint16_t evValue  = luxToEvConversion(luxValue);

  Serial.print(String(getLuxFromSensor()) + "\n");
  
  writeCalculatedInfo(display);
  // drawHeader(display, luxValue, evValue);
}
