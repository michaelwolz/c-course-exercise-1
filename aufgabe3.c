/* Aufgabe3 ****************************************************************
**
** Author: Michael Wolz
** Matrikelnummer: 1195270
**
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * utf8_to_entities(char *utf8) {
	int state = 0;
	char *tmp = malloc(sizeof(utf8) * 5); 
	char *result = tmp;
	unsigned int utf8character;

	while (*utf8) {
		while (state > 0) {
			if (state>1) 
				utf8character = (utf8character + (*utf8 & 0x3F))<<6;
			else
				utf8character = utf8character + (*utf8 & 0x3F);				

			if ((*utf8 & 0xC0) != 0x80) 
				return 0;
			
			state--;
			utf8++;

			if (state == 0) {
				printf("UTF-8 (Hex): %x\n", utf8character);
				printf("UTF-8 (Dec): %d\n\n", utf8character);
				sprintf(tmp + strlen(tmp), "%d;", utf8character);
				while (*tmp != 0) tmp++; 
			}
		}

		if ((*utf8 & 0x80) == 0) {
			*tmp = *utf8;
			tmp++;
			utf8++;
			continue;
		}

		if ((*utf8 & 0xE0) == 0xC0) {
			state = 1;
			sprintf(tmp + strlen(tmp), "%s", "&#");
			tmp += 2;
			utf8character = (*utf8 & 0x1F)<<6;
			utf8++;
			continue;
		}

		if ((*utf8 & 0xF0) == 0xE0) {
			state = 2;
			sprintf(tmp + strlen(tmp), "%s", "&#");
			tmp += 2;
			utf8character = (*utf8 & 0xF)<<6;
			utf8++;
			continue;
		}

		if ((*utf8 & 0xF8) == 0xF0) {
			state = 3;
			sprintf(tmp + strlen(tmp), "%s", "&#");
			tmp += 2;
			utf8character = (*utf8 & 0x7)<<6;
			utf8++;
			continue;
		}
		utf8++;
	}

	*(tmp+1) = 0;
	return result;
}

int main() {
	char s[] = "Während Adam lacht, jagen zwölf Boxkämpfer Eva quer über den großen Teich";

	printf("Input String: %s\n\n", s);
	printf("Output String: %s\n", utf8_to_entities(s));



	return 0;
}