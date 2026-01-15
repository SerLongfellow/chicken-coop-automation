#ifndef MP3_PLAYER_INTERFACE_H
#define MP3_PLAYER_INTERFACE_H

#include <Arduino.h>

/**
 * @brief Generic interface for an MP3 player module.
 */
class IMp3Player {
public:
  virtual ~IMp3Player() {}
  virtual bool begin(Stream &serial, bool isACK = true,
                     bool doReset = true) = 0;
  virtual void volume(uint8_t volume) = 0;
  virtual void playMp3Folder(int trackNumber) = 0;
  virtual bool available() = 0;
  virtual uint8_t readType() = 0;
  virtual int read() = 0;
};

#endif // MP3_PLAYER_INTERFACE_H
