FROM ubuntu:latest

RUN apt-get update && apt-get install -y curl bash
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/bin bash

RUN arduino-cli config init && \
    arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/MrBlinky/Arduboy-homemade-package/master/package_arduboy_homemade_index.json && \
    arduino-cli core update-index && \
    arduino-cli core install arduino:avr && \
    arduino-cli core install arduboy-homemade:avr@1.3.7

VOLUME /root/bounce

COPY Arduboy2 /root/.arduino15/packages/arduboy-homemade/hardware/avr/1.3.7/libraries/Arduboy2/src/

ENTRYPOINT cd /root/bounce && arduino-cli compile --clean --warnings all -b arduboy-homemade:avr:arduboy -e .
