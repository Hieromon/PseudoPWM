// This sketch flashes the onboard LED of ESP8266.
// Also it is blinked 0.2 seconds for one second every 8 seconds.

#include <Arduino.h>
#include "PseudoPWM.h"

PseudoPWM PilotLED(2);              // ESP8266 onboard led is active-low
unsigned  long ts;
boolean   flash;

void setup() {
  digitalWrite(2, HIGH);            // turn off led
  PilotLED.Start(2000, 1700);       // Start PWM, lit for 0.3[s]
  flash = false;
  ts = millis(); 
}

void loop() {
  unsigned long ls = millis();
  unsigned long span = ls - ts;

  delay(500);
  if (span > 1000) {
    if (flash) {
      digitalWrite(2, HIGH);        // turn off led
      PilotLED.Start(2000, 1700);   // Restore cycle and duty
      flash = false;
    }
    if (span > 8000) {
      PilotLED.Start(200, 100);     // Change cycle and duty to blinking 0.2[s]
      flash = true;
      ts = ls;
    }
  }
}
