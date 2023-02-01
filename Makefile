SHELL:=/bin/bash

.PHONY: *

all: deps build


# DEPS
deps: deps-scripts deps-docker

deps-scripts:
	pip install -r scripts/requirements.txt

deps-docker: clean-docker
	docker build -t bounce-builder:latest scripts/bounce-builder/
	docker create --name bounce-builder -v $(shell pwd):/root/bounce bounce-builder || true


# BUILD
build: build-assets compile
build-assets: build-images

define IMAGES_H_HEADERS
#pragma once

#include <Arduboy2Ex.h>

endef
export IMAGES_H_HEADERS

build-images:
	python scripts/image-convert.py assets/images/*.bmp
	@echo "$$IMAGES_H_HEADERS" > src/assets/images.h
	sed -e '$$s/$$/\n/' -s assets/images/*.h >> src/assets/images.h

compile:
	docker start -a bounce-builder > bounce-builder-logs.txt


# CLEAN
clean: clean-assets clean-docker

clean-assets:
	find assets -name "*.h" -exec rm -f {} \;

clean-docker:
	docker rm bounce-builder || true
	docker rmi bounce-builder || true
