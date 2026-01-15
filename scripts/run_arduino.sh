#!/bin/bash

# Get the directory of the current script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

"$SCRIPT_DIR/build.sh"
if [ $? -ne 0 ]; then exit 1; fi

"$SCRIPT_DIR/deploy.sh"
if [ $? -ne 0 ]; then exit 1; fi

"$SCRIPT_DIR/monitor.sh"
