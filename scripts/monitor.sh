#!/bin/bash

# Load common helper
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source "$SCRIPT_DIR/common.sh"

# Configuration
PORT="COM4"
BAUDRATE="115200"

echo -e "\n--- Opening Serial Monitor ($BAUDRATE baud) ---"
echo "Press Ctrl+C to stop monitoring."
"$ARDUINO_CLI" monitor -p "$PORT" --config baudrate="$BAUDRATE"
