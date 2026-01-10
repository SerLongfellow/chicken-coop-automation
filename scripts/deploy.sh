#!/bin/bash

# Configuration
ARDUINO_CLI="C:/Users/Jeff/AppData/Local/Programs/Arduino IDE/resources/app/lib/backend/resources/arduino-cli.exe"
BOARD_FQBN="arduino:esp32:nano_nora"
PORT="COM4"

echo -e "\n--- Uploading to $BOARD_FQBN on $PORT ---"
# Upload the sketch in the parent directory
"$ARDUINO_CLI" upload -p "$PORT" --fqbn "$BOARD_FQBN" ..

if [ $? -ne 0 ]; then
    echo "Upload failed!"
    exit 1
fi
echo "Upload successful."
