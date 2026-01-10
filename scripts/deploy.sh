#!/bin/bash

# Load common helper
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source "$SCRIPT_DIR/common.sh"

# Configuration
BOARD_FQBN="arduino:esp32:nano_nora"
PORT="COM4"

echo -e "\n--- Uploading to $BOARD_FQBN on $PORT ---"
"$ARDUINO_CLI" upload -p "$PORT" --fqbn "$BOARD_FQBN" "$PROJECT_ROOT"

if [ $? -ne 0 ]; then
    echo "Upload failed!"
    exit 1
fi
echo "Upload successful."
