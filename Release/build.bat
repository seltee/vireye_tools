clang++ --target=thumb -mthumb -mfloat-abi=soft -fdeclspec -c -m32 -Os hello_world.cpp
linker hello_world.o hello_world.vex
patcher vireye_core.hex hello_world.vex vireye_core_patched.hex
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -P vireye_core_patched.hex 0x08000000
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -Rst
pause