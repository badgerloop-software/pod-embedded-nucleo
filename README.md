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

## Accessing Serial Terminal Remotely

Accessing the Badgerloop Utility & Testing Terminal is a combination of using Secure Shell (SSH) and a serial communication protocall called UART. Follow these steps for best results

1. `make rem` force your latest changes onto the Nucleos
2. `ssh developer@hitl.badgerloop.org` Contact Eric Udlis to get your ssh key in the server. **Right now the PI is connected to my home network, for security we do not use passwords**
3. `screen /dev/ttyACM0` or `screen /dev/ttyACM1` depending on which nucleo you want to view

## FAQ:
-
