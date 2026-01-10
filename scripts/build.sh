#!/bin/bash

# Configuration
ARDUINO_CLI="C:/Users/Jeff/AppData/Local/Programs/Arduino IDE/resources/app/lib/backend/resources/arduino-cli.exe"
BOARD_FQBN="arduino:esp32:nano_nora"

echo "--- Compiling Sketch ---"
# Compile the sketch in the parent directory
"$ARDUINO_CLI" compile --fqbn "$BOARD_FQBN" ..

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi
echo "Compilation successful."
