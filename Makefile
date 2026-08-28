PROJECT  := mission
BUILD    := build
SOURCES  := src

.PHONY: all build clean run debug release

all: build

build:
	@cmake -B $(BUILD) -DCMAKE_BUILD_TYPE=Debug
	@cmake --build $(BUILD) -j $$(nproc)

clean:
	@rm -rf $(BUILD)

run: build
	@./$(BUILD)/$(PROJECT)

debug:
	@cmake -B $(BUILD) -DCMAKE_BUILD_TYPE=Debug
	@cmake --build $(BUILD) -j $$(nproc)

release:
	@cmake -B $(BUILD) -DCMAKE_BUILD_TYPE=Release
	@cmake --build $(BUILD) -j $$(nproc)
