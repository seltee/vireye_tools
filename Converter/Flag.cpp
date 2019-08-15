#include "Flag.h"
#include <string.h>
#include <stdio.h>

Flag::Flag(char* string) {
	primaryFlag = false;
	widthFrames = 1;

	if (string && isFlag(string)) {
		int length = strlen(string);
		for (int i = 0; i < length; i++) {
			if (string[i] == 'p') primaryFlag = true;
			if (string[i] == 'w') {
				i += getFramesCount(&string[i + 1], &widthFrames);
			}
		}
	}
}

bool Flag::isFlag(char* string) {
	if (string && string[0] == '-') {
		return true;
	}
	return false;
}

bool Flag::isPrimary() {
	return primaryFlag;
}

int Flag::getWidthFrames() {
	return widthFrames;
}

int Flag::getFramesCount(char* string, int* out) {
	*out = 0;
	int counter = 0;
	while (*string >= '0' && *string <= '9') {
		*out *= 10;
		*out += *string - '0';
		counter++;
		string++;
	}
	return counter;
}