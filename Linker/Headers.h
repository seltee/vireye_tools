#pragma once

#pragma once
#define SAVE_BLOCK_TYPE_END 0
#define SAVE_BLOCK_TYPE_MAP 1
#define SAVE_BLOCK_TYPE_CODE 2
#define SAVE_BLOCK_TYPE_RAM 3
#define SAVE_BLOCK_TYPE_RODATA 4
#define SAVE_BLOCK_TYPE_SYMTABLE 5
#define SAVE_BLOCK_TYPE_CODE_PART 6
#define SAVE_BLOCK_TYPE_RAM_RELOCATION 7
#define SAVE_BLOCK_TYPE_PROGRAM_NAME 8

#define SAVE_SOURCE_UNKNOWN 0
#define SAVE_SOURCE_CODE 1
#define SAVE_SOURCE_RAM 2

enum Arhitecture {
	ARHITECTURE_UNKNOWN = 0,
	ARHITECTURE_THUMB = 1,
	ARHITECTURE_ARM = 2
};

enum SaveSectionType {
	SAVE_SECTION_TYPE_UNKNOWN = 0,
	SAVE_SECTION_TYPE_CODE,
	SAVE_SECTION_TYPE_ROM,
	SAVE_SECTION_TYPE_RAM,
	SAVE_SECTION_TYPE_LIB
};

struct SaveMainHeader {
	unsigned char mark[4];
	unsigned char version;
	unsigned char subVersion;
	unsigned char architecture;
	unsigned char reserved;
	unsigned int maxCodeBlockSize;
	unsigned int ramSize;
	unsigned int codeSize;
	unsigned int romSize;
	unsigned int entry;
};

struct SaveUsualHeader {
	unsigned char type;
	unsigned char version;
	unsigned short reserved;
	unsigned int size;
};

struct SaveCodePartHeader {
	unsigned int globalShift;
	unsigned int codeLength;
	unsigned int symNameTableLength;
	unsigned int relocationsCount;
};

struct SaveRelocation {
	unsigned int shift;
	unsigned short type;
	unsigned char bind;
	unsigned char source;
	unsigned int nameShift;
	unsigned int targetShift;
};