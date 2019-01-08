clang++ --target=thumb -mthumb -mfloat-abi=soft -fdeclspec -c -m32 -Os test.cpp
linker test.o test.vex
patcher vireye_core.hex test.vex vireye_core_patched.hex
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -P vireye_core_patched.hex 0x08000000
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -Rst
pause