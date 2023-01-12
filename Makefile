SHELL:=/bin/bash

.PHONY: build clean

build: images compile
clean: assets-clean compile-clean


define IMAGES_H_HEADERS
#pragma once

#include <Arduboy2Ex.h>

endef
export IMAGES_H_HEADERS

images: assets-clean
	pip install -r scripts/requirements.txt
	python scripts/image-convert.py assets/images/*.bmp
	@echo "$$IMAGES_H_HEADERS" > src/assets/images.h
	sed -e '$$s/$$/\n/' -s assets/images/*.h >> src/assets/images.h

assets-clean:
	find assets -name "*.h" -exec rm -f {} \;


compile:
	docker build -t bounce-builder:latest scripts/bounce-builder/
	docker create --name bounce-builder -v $(shell pwd):/root/bounce bounce-builder || true
	docker start -a bounce-builder > bounce-builder-logs.txt

compile-clean:
	docker rm bounce-builder
	docker rmi bounce-builder
