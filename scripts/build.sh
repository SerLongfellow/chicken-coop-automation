#!/bin/bash

# Load common helper
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
source "$SCRIPT_DIR/common.sh"

# Configuration
BOARD_FQBN="arduino:esp32:nano_nora"

echo "--- Compiling Sketch ---"
"$ARDUINO_CLI" compile --fqbn "$BOARD_FQBN" "$PROJECT_ROOT"

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi
echo "Compilation successful."
