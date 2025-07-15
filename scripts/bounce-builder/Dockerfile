FROM ubuntu:latest

RUN apt-get update && apt-get install -y curl bash python3-full
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/bin bash

RUN arduino-cli config init && \
    arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/YariKartoshe4ka/Arduboy-homemade-package/patch-index/package_arduboy_homemade_index.json && \
    arduino-cli core update-index && \
    arduino-cli core install arduino:avr && \
    arduino-cli core install arduboy-homemade:avr


RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

COPY requirements.txt /opt
RUN pip install -r /opt/requirements.txt

WORKDIR /root/bounce

COPY entrypoint.sh /opt
ENTRYPOINT ["/opt/entrypoint.sh"]
