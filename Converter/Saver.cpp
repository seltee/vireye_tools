#include "Saver.h"
#include <stdio.h>

#define SAVE_BUFFER_SIZE (1024*16)

void Saver::save(Pallete* pallete, std::vector<Image*>* images) {
	FILE* header, *source;
	fopen_s(&header, "pallete.h", "w");
	fopen_s(&source, "pallete.c", "w");
	

	if (header && source) {
		char* buffer1 = new char[SAVE_BUFFER_SIZE];
		char* buffer2 = new char[SAVE_BUFFER_SIZE];

		fputs("#pragma once\n\n", header);
		fputs("#include \"pallete.h\"\n\n", source);

		sprintf_s(buffer1, SAVE_BUFFER_SIZE, "extern const unsigned short pallete[%i];\n\n", pallete->getPalleteColorsCount());
		fputs(buffer1, header);

		
		pallete->getPallete(buffer1);
		sprintf_s(buffer2, 1024 * 16, "const unsigned short pallete[%i] = { \n%s\n};\n\n", pallete->getPalleteColorsCount(), buffer1);
		fputs(buffer2, source);

		for (std::vector<Image*>::iterator it = images->begin(); it != images->end(); ++it) {
			sprintf_s(buffer1, SAVE_BUFFER_SIZE, "#define %s_width %i\n", (*it)->getName(), (*it)->getFramesCount() > 1 ? (*it)->getFrameWidth() : (*it)->getWidth());
			fputs(buffer1, header);
			sprintf_s(buffer1, SAVE_BUFFER_SIZE, "#define %s_height %i\n", (*it)->getName(), (*it)->getHeight());
			fputs(buffer1, header);

			if ((*it)->getFramesCount() > 1) {
				sprintf_s(buffer1, SAVE_BUFFER_SIZE, "#define %s_framecount %i\n", (*it)->getName(), (*it)->getFramesCount());
				fputs(buffer1, header);

				sprintf_s(buffer1, SAVE_BUFFER_SIZE, "extern const unsigned char %s[%i][%i];\n\n", (*it)->getName(), (*it)->getFramesCount(), (*it)->getFrameWidth() * (*it)->getHeight());
				fputs(buffer1, header);

				sprintf_s(buffer1, SAVE_BUFFER_SIZE, "const unsigned char %s[%i][%i] = {\n", (*it)->getName(), (*it)->getFramesCount(), (*it)->getFrameWidth() * (*it)->getHeight());
				fputs(buffer1, source);
				for (int i = 0; i < (*it)->getFramesCount(); i++) {
					fputs("{\n", source);
					(*it)->save(source, i);
					fputs(i == (*it)->getFramesCount() - 1 ? "}\n" : "},\n", source);
				}

				fputs("};\n", source);
			}
			else 
			{
				sprintf_s(buffer1, SAVE_BUFFER_SIZE, "extern const unsigned char %s[%i];\n\n", (*it)->getName(), (*it)->getWidth() * (*it)->getHeight());
				fputs(buffer1, header);

				sprintf_s(buffer1, SAVE_BUFFER_SIZE, "const unsigned char %s[%i] = {\n", (*it)->getName(), (*it)->getWidth() * (*it)->getHeight());
				fputs(buffer1, source);
				(*it)->save(source);
				fputs("};\n", source);
			}
			
			
		}

		fclose(header);
		fclose(source);
	}
}