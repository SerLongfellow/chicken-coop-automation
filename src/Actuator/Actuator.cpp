#include "Actuator.h"

Actuator::Actuator(uint8_t relay1Pin, uint8_t relay2Pin, bool activeLow)
    : _relay1Pin(relay1Pin), _relay2Pin(relay2Pin), _state(ACTUATOR_STOPPED) {
  _onLevel = activeLow ? LOW : HIGH;
  _offLevel = activeLow ? HIGH : LOW;
}

void Actuator::begin() {
  pinMode(_relay1Pin, OUTPUT);
  pinMode(_relay2Pin, OUTPUT);
  stop();
}

void Actuator::open() {
  if (_state != ACTUATOR_OPENING) {
    setRelays(_onLevel, _offLevel);
    _state = ACTUATOR_OPENING;
  }
}

void Actuator::close() {
  if (_state != ACTUATOR_CLOSING) {
    setRelays(_offLevel, _onLevel);
    _state = ACTUATOR_CLOSING;
  }
}

void Actuator::stop() {
  if (_state != ACTUATOR_STOPPED) {
    setRelays(_offLevel, _offLevel);
    _state = ACTUATOR_STOPPED;
  }
}

void Actuator::setRelays(uint8_t r1, uint8_t r2) {
  digitalWrite(_relay1Pin, r1);
  digitalWrite(_relay2Pin, r2);
}
