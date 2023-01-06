SHELL:=/bin/bash

.PHONY: build clean
build: images
clean: assets-clean


define IMAGES_H_HEADERS
#pragma once

#include <Arduboy2.h>

endef
export IMAGES_H_HEADERS

images: assets-clean
	python scripts/image-convert.py assets/images/*.bmp
	@echo "$$IMAGES_H_HEADERS" > src/assets/images.h
	sed -e '$$s/$$/\n/' -s assets/images/*.h >> src/assets/images.h

assets-clean:
	find assets -name "*.h" -exec rm -f {} \;
