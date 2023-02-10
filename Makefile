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

build-assets:
	python scripts/images_convert.py src/assets/images.h assets/images/*
	python scripts/levels_convert.py src/assets/levels.h assets/levels/*.bin

compile:
	docker start -a bounce-builder > bounce-builder-logs.txt


# CLEAN
clean: clean-docker

clean-docker:
	docker rm bounce-builder || true
	docker rmi bounce-builder || true
