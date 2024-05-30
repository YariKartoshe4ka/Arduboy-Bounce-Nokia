#!/bin/bash

mkdir -p build/

python3 scripts/images_convert.py src/assets/images.h assets/images/*
python3 scripts/levels_convert.py build/fxdata.bin src/assets/levels.h assets/levels/*.bin

arduino-cli compile -b arduboy-homemade:avr:arduboy --clean \
    --warnings all -e --output-dir build/ .
