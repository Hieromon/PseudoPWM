# PseudoPWM for Arduino

*Output pseudo PWM wave.*

It generates a relatively long cycle pseudo PWM as milliseconds and output to the port.

## Features

* Specify cycle and duty in millisecond unit
* Change cycle and duty dynamically
* Suspend output and resume
* It uses two ticker objects

## Works on

It uses two Ticker objects. Useally Ticker class depends on the hardware timers equipped on the various Arduino boards. Hardware timers are implemented as Timer libraries and eventually work as Ticker's reality.
Therefore, whether the PseudoPWM works properly depends on the Arduino board. However, ESP8266 works correctly.

## Installation

Download this file as a zip, and extract the resulting folder into your Arduino Libraries folder.  
See ![Installing Additional Arduino Libraries](https://www.arduino.cc/en/Guide/Libraries).

## Example
- Simple
```c++
// This sketch blinks simply the onboard LED of ESP8266.

#include <Arduino.h>
#include "PseudoPWM.h"

PseudoPWM PilotLED(2);

void setup() {
  PilotLED.Start(1000, 500);
}

void loop() {
  delay(100);
}
```

- Change duty rate dynamically
```c++
// This sketch flashes the onboard LED of ESP8266.
// Also it is blinked 0.2 seconds for one second every 8 seconds.

#include <Arduino.h>
#include "PseudoPWM.h"

PseudoPWM PilotLED(2);              // ESP8266 onboard led is active-low
unsigned  long ts;
boolean   flash;

void setup() {
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
      PilotLED.Start(2000, 1700);   // Restore cycle and duty
      digitalWrite(2, HIGH);        // turn off led
      flash = false;
    }
    if (span > 8000) {
      PilotLED.Start(200, 100);     // Change cycle and duty to blinking 0.2[s]
      flash = true;
      ts = ls;
    }
  }
}
```

## Usage

### Declare PseudoPWM object
```c++
#include "PseudoPWM.h"

PseudoPWM pwmout(uint8_t port);
```
Specify the port to output PWM. Output mode of the port is set to DIGITAL OUT in the constructor.
Incidentally, Ticker.h is also included from PseudoPWM.h.

### Methods

#### Start()
```c++
void PseudoPWM::Start(unsigned int cycle, unsigned int duty);
```
Starts PWM output. Specify cycle for the PWM cycle and duty for  duty of PWM by millisecond unit.

#### Stop()
```c++
void PseudoPWM::Stop();
```
Stop PWM output. It only temporarily stops output and the timer is running. From this state, the output can be resumed by the Start method.

#### attach()
```c++
void PseudoPWM::attach(void(*callback)(void));
```
The function attached here is called every cycle period. 
```c++
PseudoPWM pwmout(2);

void callbackOne() {
  // This is called every second. 
  Serial.println("Cycle tick.");
}

void setup() {
  pwmout.attach(callbackOne);
  pwmout.Start(1000, 100);
}

void loop() {
  ...
}
```
#### detach()
```c++
void PseudoPWM::detach();
```
Disable callback.

License
-----------
The PseudoPWM class is licensed under the [MIT License](LICENCE.md).  
Copyright &copy; 2017 hieromon@gmail.com
