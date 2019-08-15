#pragma once
#include <vector>
#include "Pallete.h"
#include "Image.h"

class Saver
{
public:
	void save(Pallete *pallete, std::vector<Image*> *images);
};

