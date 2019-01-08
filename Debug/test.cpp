#include "./core.h"

uint8 sprites[800];
int c = 0;
int dir = 3;
const uint16 pallette[] = {0x0000, 0x07e0, 0xffff, 0x7a7a};

int32 main(){
	dSetSpriteMemory(sprites, 800);
	dSetPalette(pallette, COLOR_FORMAT_RGB565, 3);
	dSetFPS(30);
	
	while (1) {
		c += dir;
		if (c > 200){
			dir = -1;
		}
		if (c < 0){
			dir = 1;
		}
		dDisplayText("HELLO WORLD", 2, 10, c);
		dDisplayText("HELLO PEOPLE", 2, 10, c+24);
		
		int8 string[16];
		hItoa(dGetFPS(), string);
		dDisplayText(string, 3, 100, 10);
		
		dSync();
	}
	return 0;
}