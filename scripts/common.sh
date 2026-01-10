#!/bin/bash

# Find the arduino-cli executable
if command -v arduino-cli >/dev/null 2>&1; then
    ARDUINO_CLI="arduino-cli"
elif command -v arduino-cli.exe >/dev/null 2>&1; then
    ARDUINO_CLI="arduino-cli.exe"
else
    echo "Error: arduino-cli or arduino-cli.exe not found in PATH."
    exit 1
fi

# Get the directory of the project root
PROJECT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"
