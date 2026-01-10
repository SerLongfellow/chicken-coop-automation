#!/bin/bash

# Configuration
ARDUINO_CLI="C:/Users/Jeff/AppData/Local/Programs/Arduino IDE/resources/app/lib/backend/resources/arduino-cli.exe"
PORT="COM4"
BAUDRATE="115200"

echo -e "\n--- Opening Serial Monitor ($BAUDRATE baud) ---"
echo "Press Ctrl+C to stop monitoring."
"$ARDUINO_CLI" monitor -p "$PORT" --config baudrate="$BAUDRATE"
