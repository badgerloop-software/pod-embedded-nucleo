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

If you are missing the needed compilers (ARM GCC), follow this tutorial as well:
https://wiki.badgerloop.com/index.php/Controls#ARM_GCC_Toolchain_for_Cross-Compiling

This is a very barebones setup guide, for the rest check out:
https://github.com/ARMmbed/mbed-cli/blob/1.8.3/README.md#installing-mbed-cli

As questions or issues with the workflow arise, update the README's FAQ so that
we can keep track of them!

## Development
Please do all development on a branch from dev. For example, if you want to work
on the io expander, you can branch dev-iox from dev: `git checkout -b dev-iox`.

## FAQ:
-
