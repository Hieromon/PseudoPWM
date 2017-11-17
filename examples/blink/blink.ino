// This sketch blinks simply the onboard LED of ESP8266.

#include <Arduino.h>
#include "PseudoPWM.h"

PseudoPWM PilotLED(2);

void setup() {
  digitalWrite(2, HIGH);
  PilotLED.Start(1000, 500);
}

void loop() {
  delay(100);
}

