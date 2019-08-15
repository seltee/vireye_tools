#include "Pallete.h"
#include <string.h>
#include <stdio.h>

#define COLOR_IN_UZE 0x01
#define COLOR_PRIORITY 0x02

Pallete::Pallete() {
	colorInfo = new char[0xffff];
	memset(colorInfo, 0, 0xffff);
	palleteColorsCount = 0;
}

unsigned short int Pallete::toRGB565(unsigned int rgb888) {
	unsigned short int rgb565 = 0;

	rgb565 += (rgb888 & 0xff) >> 3;
	rgb565 += (((rgb888 >> 8) & 0xff) >> 2) << 5;
	rgb565 += (((rgb888 >> 16) & 0xff) >> 3) << 11;
	return rgb565;
}

unsigned int Pallete::compareRGB565(unsigned int rgb565first, unsigned int rbg565second) {
	int r = ((rgb565first >> 11) & 0x1f) - ((rbg565second >> 11) & 0x1f);
	int g = ((rgb565first >> 5) & 0x3f) - ((rbg565second >> 5) & 0x3f);
	int b = (rgb565first & 0x1f) - (rbg565second & 0x1f);
	return r * r + g * g + b * b;
}

bool Pallete::isColor(char* string) {
	return (string[0] == '0' && string[1] == 'x' && (strlen(string) == 6 || strlen(string) == 8));
}

void Pallete::addColor(unsigned int number, bool isPrioritized) {
	unsigned short int rgb565 = toRGB565(number);

	colorInfo[rgb565] |= COLOR_IN_UZE;
	if (isPrioritized) {
		colorInfo[rgb565] |= COLOR_PRIORITY;
	}
	matchPermanent();
}

void Pallete::addPermanentColor(char *color) {
	if (isColor(color)) {
		unsigned int intColor = 0;
		char* parser = color + 2;

		while (*parser) {
			intColor *= 16;
			if (*parser >= '0' && *parser <= '9') intColor += *parser - '0';
			if (*parser >= 'a' && *parser <= 'f') intColor += *parser - 'a' + 10;
			if (*parser >= 'A' && *parser <= 'F') intColor += *parser - 'A' + 10;
			parser++;
		}
	
		if (strlen(color) == 6) {
			permanentColors.push_back(intColor);
		}
		else {
			permanentColors.push_back(toRGB565(intColor));
		}
		matchPermanent();
	}
}

void Pallete::matchPermanent() {
	for (std::list<int>::iterator it = permanentColors.begin(); it != permanentColors.end(); ++it) {
		colorInfo[*it] = 0;
	}
}

int Pallete::getTotalColorsCount() {
	int count = 0;
	for (int i = 0; i < 0xffff; i++) {
		if (colorInfo[i]) {
			count++;
		}
	}
	return count + getPermanentColorsCount();
}

int Pallete::getPriorityColorsCount() {
	int count = 0;
	for (int i = 0; i < 0xffff; i++) {
		if (colorInfo[i] & COLOR_PRIORITY) {
			count++;
		}
	}
	return count;
}

int Pallete::getPermanentColorsCount() {
	return permanentColors.size();
}

void Pallete::reduceColors() {
	std::list<int> colorList;
	int lastNearest = 0;
	int maxColors = 254 - getPermanentColorsCount();

	bool reduceUsual = getPriorityColorsCount() < maxColors;

	for (int i = 0; i < 0xffff; i++) {
		if ((colorInfo[i] & COLOR_PRIORITY) || (colorInfo[i] && reduceUsual)) {
			colorList.push_back(i);
		}
	}

	while (colorList.size() > maxColors) {
		int listSize = colorList.size();
		std::list<int>::iterator candidate;
		int nearestVal = 0xffff;
		
		std::list<int>::iterator end = colorList.end();

		for (std::list<int>::iterator it = colorList.begin(); it != end; ++it) {
			if (!reduceUsual || !(colorInfo[*it] & COLOR_PRIORITY)) {
				int baseColor = *it;
				
				for (std::list<int>::iterator it2 = colorList.begin(); it2 != end; ++it2) {
					int compColor = *it2;
					if (baseColor != compColor) {
						int res = compareRGB565(baseColor, compColor);
						if (res < nearestVal) {
							candidate = it;
							nearestVal = res;
						}
					}
				}

				for (std::list<int>::iterator it2 = permanentColors.begin(); it2 != permanentColors.end(); ++it2) {
					int compColor = *it2;
					if (baseColor != compColor) {
						int res = compareRGB565(baseColor, compColor);
						if (res < nearestVal) {
							candidate = it;
							nearestVal = res;
						}
					}
				}

				if (nearestVal <= lastNearest) break;
			}
		}

		lastNearest = nearestVal;
		colorList.remove(*candidate);
	}

	memset(colorInfo, 0, 0xffff);
	for (std::list<int>::iterator it = colorList.begin(); it != colorList.end(); ++it) {
		colorInfo[*it] = COLOR_IN_UZE;
	}
}

void Pallete::makePallete() {
	pallete[0] = 0;
	int r = 1;
	for (std::list<int>::iterator it = permanentColors.begin(); it != permanentColors.end(); ++it) {
		pallete[r] = *it;
		r++;
	}

	for (unsigned short int i = 0; i < 0xffff && r < 256; i++) {
		if (colorInfo[i]) {
			pallete[r] = i;
			r++;
		}
	}

	palleteColorsCount = r;
}

unsigned int Pallete::getColorNumber(unsigned int rbg888) {
	unsigned short int rgb565 = toRGB565(rbg888);
	unsigned int color = 1;
	unsigned int nearestVal = 0xffffffff;

	for (int i = 1; i < palleteColorsCount; i++) {
		unsigned int res = compareRGB565(rgb565, pallete[i]);
		if (res < nearestVal) {
			color = i;
			nearestVal = res;
		}
	}

	return color;
}

void Pallete::getPallete(char* out) {
	out[0] = 0;
	char buffer[16];
	for (int i = 0; i < palleteColorsCount; i++) {
		unsigned short fColor = ((pallete[i] & 0xff) << 8) + (pallete[i] >> 8);
		sprintf_s(buffer, "0x%04x%s", fColor, i == (palleteColorsCount - 1) ? "" : ", ");
		strcat_s(out, 8096, buffer);
	}
}

int Pallete::getPalleteColorsCount() {
	return palleteColorsCount;
}