#ifndef MP3_CONTROLLER_H
#define MP3_CONTROLLER_H

#include "IMp3Player.h"
#include <Arduino.h>


class Mp3Controller {
public:
  /**
   * @brief Construct a new Mp3Controller object
   *
   * @param player Reference to an IMp3Player instance (Dependency Injection)
   */
  Mp3Controller(IMp3Player &player);

  /**
   * @brief Initialize the MP3 player
   *
   * @param serial The hardware/software serial port to use
   * @param volume Initial volume level (0-30)
   * @return true if initialization succeeded
   */
  bool begin(Stream &serial, uint8_t volume = 20);

  /**
   * @brief Play a specific track from the /mp3/ folder
   *
   * @param trackNumber Track index (1, 2, 3...)
   */
  void playTrack(int trackNumber);

  /**
   * @brief Set the playback volume
   *
   * @param volume Volume level (0-30)
   */
  void setVolume(uint8_t volume);

  /**
   * @brief Must be called in the main loop to handle status updates
   */
  void update();

private:
  IMp3Player &_player;
  void handleStatus(uint8_t type, int value);
};

#endif // MP3_CONTROLLER_H
