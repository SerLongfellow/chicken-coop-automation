#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

enum ActuatorState { ACTUATOR_STOPPED, ACTUATOR_OPENING, ACTUATOR_CLOSING };

class Actuator {
public:
  /**
   * @brief Construct a new Actuator object
   *
   * @param relay1Pin Pin for relay 1 (e.g., EXTEND)
   * @param relay2Pin Pin for relay 2 (e.g., RETRACT)
   * @param activeLow True if the relay is active-low (default: true)
   */
  Actuator(uint8_t relay1Pin, uint8_t relay2Pin, bool activeLow = true);

  /**
   * @brief Initialize the relay pins
   */
  void begin();

  /**
   * @brief Start opening the coop (extend)
   */
  void open();

  /**
   * @brief Start closing the coop (retract)
   */
  void close();

  /**
   * @brief Stop the actuator
   */
  void stop();

  /**
   * @brief Get the current state of the actuator
   *
   * @return ActuatorState
   */
  ActuatorState getState() const { return _state; }

private:
  uint8_t _relay1Pin;
  uint8_t _relay2Pin;
  uint8_t _onLevel;
  uint8_t _offLevel;
  ActuatorState _state;

  void setRelays(uint8_t r1, uint8_t r2);
};

#endif // ACTUATOR_H
