/* Aufgabe3 ****************************************************************
**
** Author: Michael Wolz
** Matrikelnummer: 1195270
**
******************************************************************************/

#include <stdio.h>

char utf8_to_entities(char *utf8) {
	char *x = utf8;
	int state = 0;
	unsigned int utf8character;

	while (*x) {
		if (state > 0) {
			if (state>1) 
				utf8character = (utf8character + (*x & 0x3F))<<6;
			else
				utf8character = utf8character + (*x & 0x3F);				

			printf("UTF-8 (Hex): %x\n", utf8character);
			printf("UTF-8 (Dec): %d\n", utf8character);

			if ((*x & 0xC0) != 0x80) 
				return 0;
			
			printf("\n");
			state--;
			x++;
			continue;
		}

		if ((*x & 0x80) == 0) {
			x++;
			continue;
		}

		if ((*x & 0xE0) == 0xC0) {
			state = 1;
			utf8character = (*x & 0x1F)<<6;
			x++;
			continue;
		}

		if ((*x & 0xF0) == 0xE0) {
			state = 2;
			utf8character = (*x & 0xF)<<6;
			x++;
			continue;
		}

		if ((*x & 0xF8) == 0xF0) {
			state = 3;
			utf8character = (*x & 0x7)<<6;
			x++;
			continue;
		}
		return 0;
	}
	return *utf8;
}

int main() {
	char s[] = "Marius Müller \xF0\x9F\x98\x81€";

	printf("Input String: %s\n\n", s);
	//printf("Output String: %s\n", utf8_to_entities(s));
	utf8_to_entities(s);

	return 0;
}