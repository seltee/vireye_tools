#pragma once
#include "Flag.h"
#include "Pallete.h"
#include <stdio.h>

class Image
{
public:
	Image(char* path, Flag *flag);
	static bool isImage(char* path);
	bool isValid();
	void injectColors(Pallete* pallete);
	void convert(Pallete* pallete);
	char* getName();
	int getWidth();
	int getHeight();
	int getFramesCount();
	int getFrameWidth();
	void save(FILE* file, int frame = 0);

private:
	Flag* flag;
	int width, height, components;
	unsigned char* data;
	unsigned char* converted;
	char* name;
};

