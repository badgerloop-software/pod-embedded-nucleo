# Getting Started

## Installation
```bash
git clone https://github.com/badgerloop-software/pod-embedded-nucleo
cd pod-embedded-nucleo
pip install mbed-cli --user
git clone https://github.com/ARMmbed/mbed-os    # Installs the base libraries for MbedOS
cd mbed-os
pip install -r requirements.txt --user
cd ..
make build  # Builds the project linked with MbedOS
make flash  # Flashs (and builds) the project linked with MbedOS
```

If you are missing the needed compilers (ARM GCC), follow this tutorial as well:
https://wiki.badgerloop.com/index.php/Controls#ARM_GCC_Toolchain_for_Cross-Compiling

This is a very barebones setup guide, for the rest check out:
https://github.com/ARMmbed/mbed-cli/blob/1.8.3/README.md#installing-mbed-cli

As questions or issues with the workflow arise, update the README's FAQ so that
we can keep track of them!

## FAQ:
-
