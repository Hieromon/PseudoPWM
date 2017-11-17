#include <Arduino.h>
#include "PseudoPWM.h"

PseudoPWM	PilotLED(2);
int callback_counter = 0;

void callback() {
	Serial.print("callback occurred");
  if (++callback_counter > 10) {
    PilotLED.Stop();
    Serial.print(" - stopped");
  }
  Serial.println();
}

void setup() {
	Serial.begin(115200);
	PilotLED.attach(callback);
	PilotLED.Start(2000, 200);
}

void loop() {
	delay(1000);
	Serial.println("delayed");
}
