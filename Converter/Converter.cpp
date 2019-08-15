#include <stdio.h>
#include <vector>
#include "Image.h"
#include "Flag.h"
#include "Image.h"
#include "Pallete.h"
#include "Saver.h"

int main(int argc, char *argv[])
{
	Flag* currentFlag = 0;
	bool errors = false;
	Saver saver;

	printf("Converter launched ...\n");
	std::vector<Image*> images;
	Pallete pallete;

	for (int i = 1; i < argc; i++) {
		printf("%s\n", argv[i]);
		if (Flag::isFlag(argv[i])) {
			currentFlag = new Flag(argv[i]);
		} else {
			if (Image::isImage(argv[i])) {
				Image* newImage = new Image(argv[i], currentFlag);
				if (!newImage->isValid()) {
					printf("ERROR: image is corrupted or unsupported format %s\n", argv[i]);
					errors = true;
				}
				images.push_back(newImage);
				currentFlag = 0;
				printf("Image %s\n", argv[i]);
			}
			else {
				if (Pallete::isColor(argv[i])) {
					pallete.addPermanentColor(argv[i]);
				}
				else {
					printf("ERROR: not an image or flag %s\n", argv[i]);
					errors = true;
				}
			}
		}
	}

	if (errors) {
		return 0;
	}

	printf("Getting colors ...\n");

	for (std::vector<Image*>::iterator it = images.begin(); it != images.end(); ++it) {
		(*it)->injectColors(&pallete);
	}

	printf("Total colors: %i\nPriority: %i\nPermanent: %i\n", pallete.getTotalColorsCount(), pallete.getPriorityColorsCount(), pallete.getPermanentColorsCount());
	if (pallete.getPriorityColorsCount() > 254 - pallete.getPermanentColorsCount()) {
		printf("WARNING: priority colors exceeds limit of %i colors, amount will be reduced\n", 254 - pallete.getPermanentColorsCount());
	}
	if (pallete.getPermanentColorsCount() > 254) {
		printf("ERROR: permanent colors exceeds limit of 254 colors\n");
		return 0;
	}
	if (pallete.getTotalColorsCount() > 254) {
		printf("Reducing colors count ...\n");
		pallete.reduceColors();
		printf("Total colors: %i\n", pallete.getTotalColorsCount());
	}

	printf("Converting images ...\n");
	pallete.makePallete();
	for (std::vector<Image*>::iterator it = images.begin(); it != images.end(); ++it) {
		(*it)->convert(&pallete);
	}

	printf("Saving ...\n");
	saver.save(&pallete, &images);

	printf("Done\n\n");
	return 0;
}
