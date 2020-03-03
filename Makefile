
NUCLEO_VERSION 	:= L432KC
TARGET         	:= NUCLEO_$(NUCLEO_VERSION)
COMPILER       	:= GCC_ARM
BUILD_DST		:= pod-src/BUILD
BIN				:= pod-src.bin
PATH			:= $(shell pwd)

##### USER/OS SPECIFIC #####

NUCLEO_PATH    	:= /run/media/$(USERNAME)/NODE_$(NUCLEO_VERSION)  # Works for Manjaro (maybe all Linux)

#########################

.PHONY: all build flash open install

all: build flash

flash: 
	@echo "-----------------"
	@echo "Copying to board"
	@echo "-----------------"
	-cp $(BUILD_DST)/$(BIN) $(NUCLEO_PATH)
	-cp $(BUILD_DST)/$(BIN) $(NUCLEO_PATH)1

# Lazy way to open a terminal to control a nucleo, can't promise it'll work for
# you
open:
	screen /dev/ttyACM0

build:
	mbed compile -v -t $(COMPILER) -m $(TARGET) --source pod-src/include --source pod-src/src --source mbed-os/ --build $(BUILD_DST)

# installs Mbed related stuff
install:
	pip install mbed-cli --user
	git clone https://github.com/ARMmbed/mbed-os
	cd mbed-os && pip install -r requirements.txt --user && cd ..
	mbed config TOOLCHAIN $(COMPILER)
	mbed config MBED_OS_DIR $(PATH)/mbed-os/
	mbed config TARGET $(TARGET)
