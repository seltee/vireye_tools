#pragma once

typedef char int8;
typedef short int16;
typedef int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#define SYS_FN extern "C" __declspec(dllimport)

struct Matrix{
	const uint8 **sprites;
	uint8 *matrix;
};

enum FillColor{
	FILL_COLOR_BLACK = 0,
	FILL_COLOR_WHITE = 1
};

enum ButtonId {
	INPUT_SELECT = 0,
	INPUT_START,
	INPUT_A,
	INPUT_X,
	INPUT_B,
	INPUT_Y
};

enum ColorFormat{
	COLOR_FORMAT_UNKNOWN,
	COLOR_FORMAT_RGB565 = 1
};

// DISPLAY FUNCTIONS
// Enable or disable line clear, when rendering lines on display. May fasten rendering, when disabled.
SYS_FN void dSetLineClear(bool state);

// Fill color of the line.
SYS_FN void dSetFillColor(FillColor fillNum);

// Sprites need some memory to be placed in. If you want more sprites - give them more memory. It's good idea to start from 800 bytes and rise this value if it will be not enough.
SYS_FN void dSetSpriteMemory(uint8 *address, unsigned int size);

// Displays sprite on the screen. For all drawing sprite functions you need to set up sprite memory, or it will not work
SYS_FN void dDisplaySprite(const uint8 *sprite, int16 x, int16 y, int16 width, int16 height, bool upScale = false);

// Displays sprite with selected color. One byte contents eight pixels, each bit presents selected color.
SYS_FN void dDisplaySpriteMask(const uint8 *sprite, uint8 color, int16 x, int16 y, uint8 bytesPerWidth, int16 height, bool upScale = false);

// Displays sprite matrix. Matrix in matrix structure contains numbers of the sprites in the structure field sprites. Sprites contain array of pointers to the sprite data. All of them need to be same with and height (sprites must be squares) defined by size.
SYS_FN void dDisplaySpriteMatrix(const Matrix *matrix, int8 size, int16 x, int16 y, int16 width, int16 height, bool upScale = false);

// Displays text. Note - each letter is independent sprite, so, it will take sprite memory.
SYS_FN void dDisplayText(const int8 *string, uint8 color, uint16 x, uint16 y, bool upscale = false);

// Presents all of your sprites on the display, then clears sprite memory counter (you need to draw all again)
SYS_FN void dSync();

// Get the current framerate. Value updates each second
SYS_FN uint16 dGetFPS();

// Set fps limit
SYS_FN void dSetFPS(unsigned short limit);

// Set color pallete. Each color is 2 bytes in the following model - rrrrrggggggbbbbb. as format use COLOR_TYPE_RGB565
SYS_FN void dSetPalette(const uint16 *colors, uint8 format, uint8 colorCount);


// INPUT
// Get state of button
SYS_FN void iGetState(uint8 buttonId);

// Get state of X axis of analog.
SYS_FN int16 iGetXAxis();
	
// Get state of Y axis of analog.
SYS_FN int16 iGetYAxis();

// HELPERS
// Compares two strings 
SYS_FN int16 hCmp(const int8 *str1, const int8 *str2);

// Converts integer to string
SYS_FN void hItoa(int32 n, int8 str1[]);

// Fast copy memory from one place to another
SYS_FN void hMemcpy(int8 *dest, const int8 *src, unsigned int count);
