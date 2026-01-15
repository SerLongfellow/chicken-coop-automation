#ifndef DFPLAYER_WRAPPER_H
#define DFPLAYER_WRAPPER_H

#include "IMp3Player.h"
#include <DFRobotDFPlayerMini.h>

/**
 * @brief DFPlayer implementation of IMp3Player.
 */
class DFPlayerWrapper : public IMp3Player {
public:
  DFPlayerWrapper(DFRobotDFPlayerMini &player) : _player(player) {}

  bool begin(Stream &serial, bool isACK = true, bool doReset = true) override {
    return _player.begin(serial, isACK, doReset);
  }

  void volume(uint8_t volume) override { _player.volume(volume); }

  void playMp3Folder(int trackNumber) override {
    _player.playMp3Folder(trackNumber);
  }

  bool available() override { return _player.available(); }

  uint8_t readType() override { return _player.readType(); }

  int read() override { return _player.read(); }

private:
  DFRobotDFPlayerMini &_player;
};

#endif // DFPLAYER_WRAPPER_H
