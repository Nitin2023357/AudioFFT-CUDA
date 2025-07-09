#!/bin/bash

# Ensure script exits on any command failure
set -e

# Create output directory if it doesn't exist
mkdir -p output_data

# Build the project
make clean
make

# Run the executable
./bin/fft_processor.exe
