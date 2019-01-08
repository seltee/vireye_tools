// Patcher.cpp: определяет точку входа для консольного приложения.
//
#include <cstdlib>
#include <string>
#include "stdafx.h"
#include "HexReader.h"
#include "HexSaver.h"

int main(int argc, char *argv[])
{
	HexReader reader;
	HexSaver saver;
	bool error = false;
	char *core = 0;
	char *target = 0;
	char *program = 0;

	const char *name = 0;

	for (int i = 1; i < argc; i++) {
		printf("%i - %s\n", i, argv[i]);
		int length = strlen(argv[i]);
		if (length > 4 && argv[i][length - 1] == 'x' && argv[i][length - 2] == 'e' && argv[i][length - 3] == 'h' && argv[i][length - 4] == '.') {
			if (core) {
				target = argv[i];
				printf("Is target\n");
			}
			else {
				core = argv[i];
				printf("Is Core\n");
			}
		}

		if (length > 4 && argv[i][length - 1] == 'x' && argv[i][length - 2] == 'e' && argv[i][length - 3] == 'v' && argv[i][length - 4] == '.') {
			program = argv[i];
			printf("Is Program\n");
		}

	}

	if (core && target && program) {
		if (reader.read(core)) {
			printf("Readed successfull\n");

			FILE *programFile = fopen(program, "rb");
			if (!programFile) {
				printf("Can't read program file %s\n", program);
				system("pause");
				return 0;
			}

			char *programData = new char[1024 * 1024];
			unsigned int programSize = fread(programData, 1, 1024 * 1024, programFile);
			unsigned int bytesPerRecord = reader.normalStringSize;

			fclose(programFile);

			int iterator = 0;
			while (1) {
				HexRecord *rec = reader.records.at(iterator);
				if (rec->type == 5 || rec->type == 1) {
					break;
				}
				iterator++;
				if (iterator >= reader.records.size()) {
					printf("Data is corrupted 2\n");
					system("pause");
					return 0;
				}
			}

			iterator--;
			HexRecord *rec = reader.records.at(iterator);
			if (rec->byteCount != bytesPerRecord) {
				printf("normilizing last data\n");
				char *data = new char[bytesPerRecord * 2 + 1];
				memset(data, '0', bytesPerRecord * 2);
				data[bytesPerRecord * 2] = 0;
				memcpy(data, rec->data, rec->byteCount*2);
				rec->data = data;
				rec->byteCount = bytesPerRecord;
				rec->checksome = reader.calcChecksumm(rec);
				printf("result %s\n", data);
			}
			else {
				printf("last data is ok\n");
			}
			iterator++;

			unsigned short cAddress = rec->address;
			while (1) {
				cAddress += bytesPerRecord;
				if (cAddress >= 16 * 1024) {
					break;
				}
				HexRecord *rec = new HexRecord();
				rec->address = cAddress;
				rec->byteCount = bytesPerRecord;
				rec->type = 0;
				rec->data = new char[bytesPerRecord * 2 + 1];
				memset(rec->data, '0', bytesPerRecord * 2);
				rec->data[bytesPerRecord * 2] = 0;
				rec->checksome = reader.calcChecksumm(rec);
				reader.records.insert(reader.records.begin() + iterator, rec);
				iterator++;
			}

			printf("PROGRAM size %i\n", programSize);
			unsigned int additionalRecords = programSize / bytesPerRecord + ((programSize % bytesPerRecord) ? 1 : 0);
			for (int i = 0; i < additionalRecords; i++) {
				unsigned int left = programSize - i*bytesPerRecord;
				HexRecord *rec = new HexRecord();
				rec->address = cAddress;
				rec->byteCount = (left < bytesPerRecord) ? left : bytesPerRecord;
				rec->type = 0;
				rec->data = new char[rec->byteCount * 2 + 1];
				rec->data[rec->byteCount * 2] = 0;
				for (int c = 0; c < rec->byteCount; c++) {
					saver.setHex(&rec->data[c * 2], programData[i*bytesPerRecord + c]);
				}
				rec->checksome = reader.calcChecksumm(rec);
				reader.records.insert(reader.records.begin() + iterator, rec);

				iterator++;
				cAddress += bytesPerRecord;
			}


			if (saver.save(target, &reader.records)) {
				printf("SAVED\n");
			} else {
				printf("Save failed\n");
			}			
		}
		else {
			printf("Data is corrupted\n");
		}
	}
	else {
		printf("Something is missing\n");
	}

	//system("pause");
	return 0;
}

