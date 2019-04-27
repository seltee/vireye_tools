#include "HexReader.h"

HexReader::HexReader()
{
}

HexReader::~HexReader()
{
}

bool HexReader::read(char *fileName) {
	printf("\nReading %s\n", fileName);
	FILE *file = fopen(fileName, "r");
	normalStringSize = 0;

	if (file) {
		char *megaFile = new char[64 * 1024];
		fread(megaFile, 1, 64 * 1024, file);
		fclose(file);

		char *reader = megaFile;
		while (1) {
			if (*reader == ':') {
				reader++;
				HexRecord *record = new HexRecord();
				record->byteCount = getByte(reader);
				reader += 2;
				record->address = getWord(reader);
				reader += 4;
				record->type = getByte(reader);
				reader += 2;
				record->data = new char[record->byteCount*2]+1;
				memcpy(record->data, reader, record->byteCount * 2);
				record->data[record->byteCount * 2] = 0;
				
				reader += record->byteCount * 2;
				record->checksome = getByte(reader);
				reader += 3;

				records.push_back(record);
				if (record->type == 1) {
					printf("Readed size %i\n", reader - megaFile);
					return true;
				}
				if (record->type == 0 && normalStringSize == 0) {
					normalStringSize = record->byteCount;
				}
				if (record->checksome != calcChecksumm(record)) {
					printf("WRONG CHECKSOME %i %i\n", record->checksome, calcChecksumm(record));
					return false;
				}
			}
			else {
				printf("SOMETHING BROKE\n");
				return false;
			}
		}
	}
	return false;
}

unsigned char HexReader::getByte(char *str) {
	return (getCharEqual(str[0]) << 4) + getCharEqual(str[1]);
}

unsigned short HexReader::getWord(char *str) {
	return (getByte(str) << 8) + getByte(str + 2);
}

unsigned char HexReader::getCharEqual(char chr) {
	switch (chr) {
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	default:
		return chr - '0';
	}
}

unsigned char HexReader::calcChecksumm(HexRecord *record) {
	unsigned char accumulator = (record->address & 0xff) + (record->address >> 8) + record->byteCount + record->type;
	for (int i = 0; i < record->byteCount; i++) {
		accumulator += getByte(&record->data[i * 2]);
	}
	return 1 + (accumulator^0xff);
}