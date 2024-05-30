SHELL:=/bin/bash

.PHONY: *
all: deps build


deps: clean
	docker build -t bounce-builder:latest scripts/bounce-builder/
	docker create --name bounce-builder -v $(shell pwd):/root/bounce bounce-builder || true

build:
	docker start -a bounce-builder > bounce-builder-logs.txt

clean:
	docker rm bounce-builder || true
	docker rmi bounce-builder || true
