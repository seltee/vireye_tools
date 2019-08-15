### This is tools for homebrew game console Vireye. 

More infomation about this: https://github.com/seltee/vireye_core

### Linker

Linker is the program, that gets .o files and combines them into .vex file. This format is executable of Vireye console.

Usage example: **linker.exe main.o main.vex**

### Converter

This program turnes your images into something you can show on vireye. It creates pallete of colors and image arrays in .c and .h files. The maximum amount of colors is 255 (not 256 because 0 is always transparent color) and if you will exceed this value converter will reduce amount of colors to 255. For images it will choose nearest value, dithering is not supported. Note, that header files contain not only "extern"'s of your sprites, but also their width and height.

Basic usage: **converter.exe image.png**

This command will produce pallete.h and pallete.c, that you need to include into your object.

Also converter supports constant colors like this: **converter.exe 0xffff 0x000000 image.png** (both RGB565 and RGB888. RGB888 will be simply reduced to RGB565)

Constant colors will never be reduced and will be placed in the exect order, that you wrote them in command, starting from 1 (zero is transparent, do you remember?). Images may also use it after color reduction, if your constant colors will be close enough to reduced ones.

For specifying some parameters you need to use flages. **-p** flag sets image colors to be prioritized on the image reduction process. It's may be usefull if your game for example uses 128 colors for sprites and you have big images with a lot of colors and lazy enough to not convert them into your primary pallete with Photoshop or Aseprite. Converter will do it for you, but with saving your basic sprite colors.

Usage: **converter.exe image.png -p sprite.png -p sprite2.png bigimage.png**

With w[number of frames] you may split up sprites into an array of sprites. For example you have animation in the single image, that contains 10 sprites. Just use:

**converter.exe image.png -w10p sprite.png -p sprite2.png -w5 sprite3.png**

Width constant in header will contain width of one frame.
