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

struct DirectoryReader{
	int currentCluster;
	unsigned short sectorShift;
	unsigned short inSectorShift;
};

struct FileInfo{
	unsigned int fileSize;
	
	unsigned char modifiedSeconds;
	unsigned char modifiedMinutes;
	unsigned char modifiedHours;
	unsigned char modifiedMonth;
		
	unsigned char modifiedDay;
	unsigned short modifiedYear;
	unsigned char createSeconds;
	
	unsigned char createMinutes;
	unsigned char createHours;
	unsigned char createMonth;
	unsigned char flags;
	
	unsigned char fileType;
	unsigned char r1, r2, r3;	
	
	unsigned short createYear;
	unsigned short permissions;
};

struct FileWorker{
	int startCluster;
	int currentCluster;
	unsigned short sectorShift;
	unsigned short inSectorShift;
	unsigned int fileSize;
	char *buffer;
	unsigned int readed;
	unsigned char mode;
	unsigned char r1;
	unsigned char r2;
	unsigned char r3;
	unsigned int reserved;
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

enum SpriteFlags{
	SPRITE_FLAG_NO = 0x00,
	SPRITE_FLAG_V_MIRROR = 0x01,
	SPRITE_FLAG_H_MIRROR = 0x02
};

enum FileTypes{
	FILE_TYPE_UKNOWN = 0x00,
	FILE_TYPE_RUNNABLE = 0x01,
	FILE_TYPE_DIRECTORY = 0x02
};

enum FileFlags{
	FILE_FLAG_NONE = 0x00,
	FILE_FLAG_HIDDEN = 0x01,
	FILE_FLAG_SYSTEM = 0x02
};

// DISPLAY FUNCTIONS
// Enable or disable line clear, when rendering lines on display. May fasten rendering, when disabled.
SYS_FN void dSetLineClear(bool state);

// Fill color of the line.
SYS_FN void dSetFillColor(FillColor fillNum);

// Sprites need some memory to be placed in. If you want more sprites - give them more memory. It's good idea to start from 800 bytes and rise this value if it will be not enough.
SYS_FN void dSetSpriteMemory(uint8 *address, unsigned int size);

// Displays sprite on the screen. For all drawing sprite functions you need to set up sprite memory, or it will not work
SYS_FN void dDisplaySprite(const uint8 *sprite, int16 x, int16 y, int16 width, int16 height, uint8 flags, bool upScale = true);

// Displays sprite with selected color. One byte contents eight pixels, each bit presents selected color.
SYS_FN void dDisplaySpriteBitMask(const uint8 *sprite, uint8 color, int16 x, int16 y, uint8 bytesPerWidth, int16 height, uint8 flags = SPRITE_FLAG_NO, bool upScale = true);

// Displays sprite with selected color. One byte contents eight pixels, each bit presents selected color.
SYS_FN void dDisplaySpriteByteMask(const uint8 *sprite, uint8 color, int16 x, int16 y, int16 width, int16 height, uint8 flags = SPRITE_FLAG_NO, bool upScale = true);

// Displays sprite matrix. Matrix in matrix structure contains numbers of the sprites in the structure field sprites. Sprites contain array of pointers to the sprite data. All of them need to be same with and height (sprites must be squares) defined by size.
SYS_FN void dDisplaySpriteMatrix(const Matrix *matrix, int8 size, int16 x, int16 y, int16 width, int16 height, uint8 flags = SPRITE_FLAG_NO, bool upScale = true);

// Displays text. Note - each letter is independent sprite, so, it will take sprite memory.
SYS_FN void dDisplayText(const int8 *string, uint8 color, uint16 x, uint16 y, bool upscale = true);

// Presents all of your sprites on the display, then clears sprite memory counter (you need to draw all again)
SYS_FN void dSync();

// Get the current framerate. Value updates each second
SYS_FN uint16 dGetFPS();

// Set fps limit
SYS_FN void dSetFPS(unsigned short limit);

// Set color pallete. Each color is 2 bytes in the following model - rrrrrggggggbbbbb. as format use COLOR_TYPE_RGB565
SYS_FN void dSetPalette(const uint16 *colors);


// INPUT
// Get state of button
SYS_FN bool iGetState(uint8 buttonId);

// Get state of X axis of analog.
SYS_FN int16 iGetXAxis();
	
// Get state of Y axis of analog.
SYS_FN int16 iGetYAxis();

// FILE SYSTEM
// Init file system. Buffer of 512 bytes is needed
SYS_FN bool fsInit(uint8 *newBuffer);

// Open folder to read
SYS_FN bool fsReadDir(int8 *path, DirectoryReader *dirReader);

// Read next file. Buffer for name must be at least 14 bytes
SYS_FN bool fsReadNextFile(int8 *fileName, int32 fileNameMaxLength, DirectoryReader *dirReader, FileInfo *fileInfo);

// Open file for reading
SYS_FN bool fsReadFile(int8 *filePath, FileWorker *fileWorker);

// Read data from file to buffer. In return you will get bytes actually readed
SYS_FN uint32 fsRead(FileWorker *fileWorker, void *dst, uint32 length);

// Close file after read
SYS_FN bool fsClose(FileWorker *fileWorker);


// HELPERS
// Compares two strings 
SYS_FN int16 hCmp(const int8 *str1, const int8 *str2);

// Converts integer to string
SYS_FN void hItoa(int32 n, int8 str1[]);

// SYSTEM
// You need to pass buffer with at least 6 kb free to run the programm
SYS_FN void sRun(int8 *path, uint8 *ramBuffer);

// Default
SYS_FN void memcpy(void *dest, const void *src, unsigned int count);
SYS_FN void memset(void *s, int value, int count);
SYS_FN int strlen(const int8 *string);