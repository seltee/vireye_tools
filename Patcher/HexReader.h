#pragma once
#include "stdafx.h"

struct HexRecord {
	unsigned char byteCount;
	unsigned short address;
	unsigned char type;
	unsigned char checksome;
	char *data;
};

class HexReader
{
public:
	HexReader();
	~HexReader();

	std::vector<HexRecord*> records;

	bool read(char *fileName);
	unsigned int normalStringSize;
	unsigned char getByte(char *str);
	unsigned short getWord(char *str);
	unsigned char getCharEqual(char chr);
	unsigned char calcChecksumm(HexRecord *record);
};

