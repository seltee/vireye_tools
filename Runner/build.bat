clang++ --target=thumb -mthumb -mfloat-abi=soft -fdeclspec -c -m32 -Os runner.cpp
"../Release/linker" runner.o autorun.vex
pause