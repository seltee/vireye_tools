clang++ --target=thumb -mthumb -mfloat-abi=soft -fdeclspec -c -m32 -Os runner.cpp
"../Release/linker" runner.o autorun.vex
"../Release/patcher" "../Release/vireye_core.hex" autorun.vex vireye_core_patched.hex
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -P vireye_core_patched.hex 0x08000000
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -Rst
pause