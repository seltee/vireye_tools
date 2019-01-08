#include "HexSaver.h"

const char bit4eq[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

HexSaver::HexSaver()
{
}


HexSaver::~HexSaver()
{
}

bool HexSaver::save(char *name, std::vector<HexRecord*>* records) {
	FILE *file = fopen(name, "w");
	char string[256];
	unsigned int it;
	for (int i = 0; i < records->size(); i++) {
		HexRecord *rec = records->at(i);
		it = 1;
		string[0] = ':';
		setHex(&string[1], rec->byteCount);
		setHex(&string[3], (rec->address >> 8));
		setHex(&string[5], (rec->address & 0xff));
		setHex(&string[7], rec->type);
		memcpy(&string[9], rec->data, rec->byteCount * 2);
		setHex(&string[9 + rec->byteCount * 2], rec->checksome);
		string[9 + rec->byteCount * 2 + 2] = '\n';
		string[9 + rec->byteCount * 2 + 3] = 0;
		fputs(string, file);
	}
	fclose(file);
	return true;
}

void HexSaver::setHex(char *target, unsigned char byte) {
	target[0] = bit4eq[byte >> 4];
	target[1] = bit4eq[byte & 0x0f];
}