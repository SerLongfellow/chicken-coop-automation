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

// Relay pin definitions
#define RELAY1_PIN D2 // Connected to IN1
#define RELAY2_PIN D3 // Connected to IN2

// Actuator
Actuator actuator(RELAY1_PIN, RELAY2_PIN);

// Button pin definitions
#define EXTEND_BUTTON_PIN D4
#define RETRACT_BUTTON_PIN D5

void setup() {
  Serial.begin(115200);

  // Wait up to 5 seconds for the Serial Monitor to open
  while (!Serial && millis() < 5000)
    ;

  Serial.println("Serial initialized!");

  // Initialize Actuator
  actuator.begin();

  // Initialize Button Pins (using internal pull-up)
  pinMode(EXTEND_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RETRACT_BUTTON_PIN, INPUT_PULLUP);

  // Ensure relays are OFF initially
  actuator.stop();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC - Check your SDA/SCL wiring!");
    while (1)
      ;
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Initialize Mp3 Player
  // Note: Serial0 is used for DFPlayer on Nano ESP32 (D0/D1)
  Serial0.begin(9600);
  if (!mp3Controller.begin(Serial0)) {
    Serial.println("Unable to begin Mp3Controller:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
  } else {
    Serial.println("Mp3Controller online.");
  }
}

void openCoop() {
  if (actuator.getState() != ACTUATOR_OPENING) {
    Serial.println("Opening Coop...");
    mp3Controller.playTrack(1); // Play track 1 for opening
  }
  actuator.open();
}

void closeCoop() {
  if (actuator.getState() != ACTUATOR_CLOSING) {
    Serial.println("Closing Coop...");
    mp3Controller.playTrack(2); // Play track 2 for closing
  }
  actuator.close();
}

void stopActuator() {
  if (actuator.getState() != ACTUATOR_STOPPED) {
    Serial.println("Stopping Actuator.");
  }
  actuator.stop();
}

void loop() {

  // Manual Button Control
  if (digitalRead(EXTEND_BUTTON_PIN) == LOW) {
    openCoop();
  } else if (digitalRead(RETRACT_BUTTON_PIN) == LOW) {
    closeCoop();
  } else {
    stopActuator();
  }

  mp3Controller.update();
  delay(100); // Faster polling for buttons
}