
NUCLEO_VERSION 	:= L432KC
TARGET         	:= NUCLEO_$(NUCLEO_VERSION)
COMPILER       	:= GCC_ARM
BUILD_DST		:= pod-src/BUILD
BIN				:= include.bin
YOUR_PATH		:= `pwd`

##### USER/OS SPECIFIC #####

NUCLEO_PATH    	:= /run/media/$(USERNAME)/NODE_$(NUCLEO_VERSION)# Works for Manjaro (maybe all Linux)
PATH_TO_GCC_ARM := /home/eric/badgerloop/gcc-arm-none-eabi-9-2019-q4-major/bin

############################

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
#	pip install mbed-cli --user
#	git clone https://github.com/ARMmbed/mbed-os
#	cd mbed-os && pip install -r requirements.txt --user && cd ..
	mbed config TOOLCHAIN $(COMPILER)
	mbed config MBED_OS_DIR $(YOUR_PATH)/mbed-os/
	mbed config TARGET $(TARGET)
	mbed config $(COMPILER) $(PATH_TO_GCC_ARM) 
	mbed config GCC_ARM_PATH $(PATH_TO_GCC_ARM)
