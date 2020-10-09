# Getting Started

## Installation


```bash
git clone https://github.com/badgerloop-software/pod-embedded-nucleo
cd pod-embedded-nucleo
```

Fill out the path to your GCC_ARM, username, and any other enviroment variables in Makefile.example then set it as the Makefile
```bash
cp Makefile.example Makefile
```

```bash
make install # Installs build tools
make config # Run if you skipped installation
make build  # Builds the project linked with MbedOS
make flash  # Flashs (and builds) the project linked with MbedOS
```

If you are missing the needed compilers (ARM GCC), download this compiler and keep track of it's path.
[GCC-ARM-Nabi](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)



This is a very barebones setup guide, for the rest check out:
https://github.com/ARMmbed/mbed-cli/blob/1.8.3/README.md#installing-mbed-cli

As questions or issues with the workflow arise, update the README's FAQ so that
we can keep track of them!

## Development
Please do all development on a branch from dev. For example, if you want to work
on the io expander, you can branch dev-iox from dev: `git checkout -b dev-iox`.

### MBed Studio
As with any project, there are a million ways to flash an ARM chip. I prefer Mbed Studio because of it's all in one approach to building and flashing our STM32s under the hood. If you would like to use the CLI or some other method, feel free.
To get started with Mbed Studio follow this quick guide
1. Install [Mbed Studio](https://studio.os.mbed.com)
2. Create an [Mbed OS Account](https://os.mbed.com) - They don't send emails so thumbs up for that
3. Log into Mbed studio with your mbed os Account
4. Clone this repository
5. Click File -> Open Workspace, and select the newly clones repository as the folder
6. Set the target as the "NUCLEO-L432KC"
7. Enjoy programming your Mbed enabled STM Nucleo

### Sensor Development
If you're writing code for a new peripheral, please create a `<sensor name>.cpp`.
Make sure to write a initilization function for the Power On Self Test (POST). The function must follow the naming scheme `init<filename>` that returns an int.
For example the init function for the comms.cpp file is `int initComms()`

### Power On Self Test (POST)
On startup the nucleo will automatically go through a Power On Self test (POST). The POST is automatically created from a python file `POST.py` you must have a working python3 installation to run this.
Anytime that you add a new sensor or are building for the first time, run the POST.py file in pod-src/src/

## Accessing Serial Terminal Remotely

Accessing the Badgerloop Utility & Testing Terminal is a combination of using Secure Shell (SSH) and a serial communication protocall called UART. Follow these steps for best results

1. `make rem` force your latest changes onto the Nucleos
2. `ssh developer@hitl.badgerloop.org` Contact Eric Udlis to get your ssh key in the server. **Right now the PI is connected to my home network, for security we do not use passwords**
3. `screen /dev/ttyACM0` or `screen /dev/ttyACM1` depending on which nucleo you want to view

## FAQ:
-
