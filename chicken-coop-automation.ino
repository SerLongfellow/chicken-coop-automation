#include "RTClib.h"
#include "src/Actuator/Actuator.h"
#include "src/Mp3Player/DFPlayerWrapper.h"
#include "src/Mp3Player/Mp3Controller.h"
#include <Wire.h>

RTC_DS3231 rtc;

// Mp3 Player
DFRobotDFPlayerMini myDFPlayer;
DFPlayerWrapper playerWrapper(myDFPlayer);
Mp3Controller mp3Controller(playerWrapper);

// Button pin definitions
#define EXTEND_BUTTON_PIN D4
#define RETRACT_BUTTON_PIN D5

// Relay pin definitions
#define RELAY1_PIN D2 // Connected to IN1
#define RELAY2_PIN D3 // Connected to IN2

// Actuator
Actuator actuator(RELAY1_PIN, RELAY2_PIN);
ActuatorState lastState = ACTUATOR_STOPPED;

void setup() {
  Serial.begin(115200);

  // Wait up to 5 seconds for the Serial Monitor to open
  while (!Serial && millis() < 5000)
    ;

  Serial.println(F("Chicken Coop Automation Starting..."));

  // Initialize Actuator
  actuator.begin();

  // Initialize Button Pins (using internal pull-up)
  pinMode(EXTEND_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RETRACT_BUTTON_PIN, INPUT_PULLUP);
  actuator.stop();

  Serial.println(F("Initializing RTC..."));
  if (!rtc.begin()) {
    Serial.println(F("ERROR: Couldn't find RTC - Check SDA/SCL wiring!"));
    // Don't hang here during debug, just continue
  } else {
    Serial.println(F("RTC initialized."));
    if (rtc.lostPower()) {
      Serial.println(F("RTC lost power, setting time!"));
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  }

  if (!mp3Controller.begin(Serial0)) {
    Serial.println(F("Mp3Player: Failed to initialize."));
  } else {
    Serial.println(F("Mp3Player: Online."));
  }

  Serial.println(F("Setup Complete."));
}

void openCoop() {
  if (actuator.getState() != ACTUATOR_OPENING) {
    Serial.println(F(">>> STATE CHANGE: OPENING"));
    mp3Controller.playTrack(1); // Play track 1 for opening
  }
  actuator.open();
}

void closeCoop() {
  if (actuator.getState() != ACTUATOR_CLOSING) {
    Serial.println(F(">>> STATE CHANGE: CLOSING"));
    mp3Controller.playTrack(2); // Play track 2 for closing
  }
  actuator.close();
}

void stopActuator() {
  if (actuator.getState() != ACTUATOR_STOPPED) {
    Serial.println(F(">>> STATE CHANGE: STOPPED"));
  }
  actuator.stop();
}

void loop() {
  int btnOpen = digitalRead(EXTEND_BUTTON_PIN);
  int btnClose = digitalRead(RETRACT_BUTTON_PIN);

  // Manual Button Control
  if (btnOpen == LOW) {
    openCoop();
  } else if (btnClose == LOW) {
    closeCoop();
  } else {
    stopActuator();
  }

  mp3Controller.update();
  delay(50); // Small polling delay
}