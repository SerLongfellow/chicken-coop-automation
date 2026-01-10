#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

// Relay pin definitions
#define RELAY1_PIN D2 // Connected to IN1
#define RELAY2_PIN D3 // Connected to IN2

// Relay logic (Active Low)
#define RELAY_ON  LOW
#define RELAY_OFF HIGH

// Button pin definitions
#define EXTEND_BUTTON_PIN  D4
#define RETRACT_BUTTON_PIN D5

enum ActuatorState { EXTENDING, RETRACTING, STOPPED };
ActuatorState currentState = STOPPED;

void setup() {
  Serial.begin(115200);
  
  // Wait up to 5 seconds for the Serial Monitor to open
  while (!Serial && millis() < 5000); 
  
  Serial.println("Serial initialized!");

  // Initialize Relay Pins
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  
  // Initialize Button Pins (using internal pull-up)
  pinMode(EXTEND_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RETRACT_BUTTON_PIN, INPUT_PULLUP);
  
  // Ensure relays are OFF initially
  stopActuator();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC - Check your SDA/SCL wiring!");
    while (1);
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void extendActuator() {
  if (currentState != EXTENDING) {
    Serial.println("Extending Actuator...");
    currentState = EXTENDING;
  }
  digitalWrite(RELAY1_PIN, RELAY_ON);
  digitalWrite(RELAY2_PIN, RELAY_OFF);
}

void retractActuator() {
  if (currentState != RETRACTING) {
    Serial.println("Retracting Actuator...");
    currentState = RETRACTING;
  }
  digitalWrite(RELAY1_PIN, RELAY_OFF);
  digitalWrite(RELAY2_PIN, RELAY_ON);
}

void stopActuator() {
  if (currentState != STOPPED) {
    Serial.println("Stopping Actuator.");
    currentState = STOPPED;
  }
  digitalWrite(RELAY1_PIN, RELAY_OFF);
  digitalWrite(RELAY2_PIN, RELAY_OFF);
}

void loop() {

  // Manual Button Control
  if (digitalRead(EXTEND_BUTTON_PIN) == LOW) {
    extendActuator();
  } else if (digitalRead(RETRACT_BUTTON_PIN) == LOW) {
    retractActuator();
  } else {
    stopActuator();
  }

  delay(100); // Faster polling for buttons
}