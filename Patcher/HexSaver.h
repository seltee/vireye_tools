#pragma once
#include "HexReader.h"

class HexSaver
{
public:
	HexSaver();
	~HexSaver();

	bool save(char *name, std::vector<HexRecord*>* records);
	void setHex(char *target, unsigned char byte);
};

