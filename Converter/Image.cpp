#include "Image.h"
#include "stb_image.h"
#include <stdio.h>

Image::Image(char* path, Flag* flag) {
	this->flag = flag ? flag : new Flag();
	data = stbi_load(path, &width, &height, &components, 4);
	converted = new unsigned char[width * height];
	
	int pixelSize = width * height;
	for (int i = 0; i < pixelSize; i++) {
		unsigned int d = ((unsigned int*)data)[i];
		unsigned int a = components <= 3 ? 0xff : (d >> 24);
		unsigned int b = ((d >> 16) & 0xff);
		unsigned int g = ((d >> 8) & 0xff);
		unsigned int r = ((d >> 0) & 0xff);
		((unsigned int*)data)[i] = a + (b << 8) + (g << 16) + (r << 24);
	}

	char *b = path + strlen(path) - 1;
	while (*b != '/' && b != path) b--;
	char* newName = new char[strlen(b) + 16];
	strcpy_s(newName, strlen(b) + 16, "image_");
	strcat_s(newName, strlen(b) + 16, b);
	name = newName;

	while (newName != 0 && *newName != '.') newName++;
	*newName = 0;
}

bool Image::isImage(char* path) {
	FILE* file;
	fopen_s(&file, path, "r");

	if (file) {
		fclose(file);
		return true;
	}
	return false;
}

bool Image::isValid() {
	return data != 0;
}

void Image::injectColors(Pallete* pallete) {
	int pixelSize = width * height;
	for (int i = 0; i < pixelSize; i++) {
		pallete->addColor(((unsigned int*)data)[i] >> 8, flag->isPrimary());
	}
}

void Image::convert(Pallete* pallete) {
	int pixelSize = width * height;
	for (int i = 0; i < pixelSize; i++) {
		unsigned int rgba = ((unsigned int*)data)[i];
		unsigned char alpha = rgba & 0xff;
		unsigned int color = rgba >> 8;
		
		if (alpha > 128) {
			converted[i] = pallete->getColorNumber(color);
		}
		else {
			converted[i] = 0;
		}
	}
}

char* Image::getName() {
	return name;
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

int Image::getFramesCount() {
	return flag->getWidthFrames();
}

int Image::getFrameWidth() {
	return width / getFramesCount();
}

void Image::save(FILE* file, int frame) {
	if (frame >= 0 && frame < getFramesCount()) {
		int frameWidth = getFrameWidth();
		int totalPixels = height * frameWidth;
		int counter = 0;
		char buffer[16];
		for (int ih = 0; ih < height; ih++) {
			for (int iw = 0; iw < frameWidth; iw++) {
				sprintf_s(buffer, "0x%02x%s", converted[ih*width + frame*frameWidth + iw], counter == (totalPixels - 1) ? "" : ", ");
				fputs(buffer, file);
				counter++;
				if ((counter % 16) == 15) {
					fputs("\n", file);
				}
			}
		}
	}
}