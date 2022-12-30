SHELL:=/bin/bash

.PHONY: build clean
build: assets
clean: assets-clean


define ASSETS_H_HEADERS
#pragma once

#include <Arduboy2.h>

endef
export ASSETS_H_HEADERS

assets: assets-clean
	python scripts/image-convert.py assets/*.bmp
	@echo "$$ASSETS_H_HEADERS" > src/assets.h
	sed -e '$$s/$$/\n/' -s assets/*.h >> src/assets.h

assets-clean:
	rm -f assets/*.h
