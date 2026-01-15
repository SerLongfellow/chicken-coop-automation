#include "Mp3Controller.h"
#include <DFRobotDFPlayerMini.h> // Keep for enums if needed, or define generic ones

Mp3Controller::Mp3Controller(IMp3Player &player) : _player(player) {}

bool Mp3Controller::begin(Stream &serial, uint8_t volume) {
  Serial.println(F("Initializing Mp3Player ..."));

  bool success = false;
  for (int i = 0; i < 3; i++) {
    if (_player.begin(serial)) {
      success = true;
      break;
    }
    Serial.print(F("."));
    delay(1000);
  }

  if (success) {
    Serial.println(F("\nMp3Player online."));
    _player.volume(volume);
  } else {
    Serial.println(F("\nERROR: Unable to begin MP3 module."));
  }

  return success;
}

void Mp3Controller::playTrack(int trackNumber) {
  Serial.print(F("Playing track: "));
  Serial.println(trackNumber);
  _player.playMp3Folder(trackNumber);
}

void Mp3Controller::setVolume(uint8_t volume) { _player.volume(volume); }

void Mp3Controller::update() {
  if (_player.available()) {
    handleStatus(_player.readType(), _player.read());
  }
}

void Mp3Controller::handleStatus(uint8_t type, int value) {
  // Note: These constants currently come from DFRobotDFPlayerMini.h
  // In a fully generic version, we'd define our own event types.
  switch (type) {
  case TimeOut:
    Serial.println(F("Mp3: Time Out!"));
    break;
  case WrongStack:
    Serial.println(F("Mp3: Stack Wrong!"));
    break;
  case DFPlayerCardInserted:
    Serial.println(F("Mp3: Card Inserted!"));
    break;
  case DFPlayerCardRemoved:
    Serial.println(F("Mp3: Card Removed!"));
    break;
  case DFPlayerCardOnline:
    Serial.println(F("Mp3: Card Online!"));
    break;
  case DFPlayerPlayFinished:
    Serial.print(F("Mp3: Finished track "));
    Serial.println(value);
    break;
  case DFPlayerError:
    Serial.print(F("Mp3 Error: "));
    Serial.println(value);
    break;
  default:
    break;
  }
}
