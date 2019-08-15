#pragma once
#include <list>

class Pallete
{
public:
	Pallete();
	static unsigned short int toRGB565(unsigned int rgb888);
	static unsigned int compareRGB565(unsigned int rgb565first, unsigned int rbg565second);
	static bool isColor(char* string);
	void addColor(unsigned int number, bool isPrioritized);
	void addPermanentColor(char* color);
	void matchPermanent();
	int getTotalColorsCount();
	int getPriorityColorsCount();
	int getPermanentColorsCount();
	void reduceColors();
	void makePallete();
	unsigned int getColorNumber(unsigned int rbg888);
	void getPallete(char* pallete);
	int getPalleteColorsCount();
private:
	char *colorInfo;
	unsigned short pallete[256];
	std::list<int> permanentColors;
	unsigned short palleteColorsCount;
};

