### This is tools for homebrew game console Vireye. 

More infomation about this: https://github.com/seltee/vireye_core

### Linker

Linker is the program, that gets .o files and combines them into .vex file. This format is executable of Vireye console. The main reason to use own format is to load 48 kb games with using of only 16 kb of ram.

### Patcher

This program used to combite core hex firmware for mcu with .vex file. Then you can upload core with program to your board through swd.

See command line example in release/build.bat, also there is a hello world program. 

You also need to install clang++ and STM32 ST-LINK Utility to use it.

### Runner

It's a program to run other programs for the system. After compile put autorun.vex on your SD card.