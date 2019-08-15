#pragma once
class Flag
{
public:
	Flag(char* string = 0);
	static bool isFlag(char* string);

	bool isPrimary();
	int getWidthFrames();
private:
	int getFramesCount(char* string, int* out);
	int widthFrames;
	bool primaryFlag;
};

