/* Aufgabe3 ****************************************************************
**
** Author: Michael Wolz
** Matrikelnummer: 1195270
**
** Author: Aaron Winziers
** Matrikelnummer: 1176638
**
** Die Umrechnung des UTF-8 Zeichens zum Codepunkt
** basiert auf der Rückkehrung des Beispiels auf Wikipedia:
** https://en.wikipedia.org/wiki/UTF-8#Examples
**
******************************************************************************/

#include <stdio.h>
#include <stdlib.h> //für sprintf
#include <string.h> //für strlen

char * utf8_to_entities(char *utf8) {
	int state = 0; //Größe des UTF8-Zeichens 
	char *tmp = malloc(sizeof(utf8)); //Alloziere ausreichend Speicherplatz für den Ergebnis-String
	char *result = tmp; //Pointer für den Ergebnis-String 
	unsigned int utf8character; //Temporäre Variable zur Generierung der einzelnen Codepunkten

	if (tmp == 0) { //Prüfe ob Speicherplatz korrekt alloziert wurde
		printf("ERROR: Out of memory\n");
		return NULL;
	}

	while (*utf8) {
		while (state > 0) { //Weiterverarbeitung des UTF-8 Zeichens, falls es länger als 1 Byte ist
			if (state>1) //Handelt es sich um das letzte Byte?
				utf8character = (utf8character + (*utf8 & 0x3F))<<6; //Maskiere die ersten beiden Bits weg, konkateniere mit vorherigem Ergebnis (siehe unten) und verschiebe Bitweise um 6 nach links
			else 
				utf8character = utf8character + (*utf8 & 0x3F); //Maskiere die ersten beiden Bits weg und konkateniere mit vorherigem Ergebnis			

			if ((*utf8 & 0xC0) != 0x80) 
				return 0;
			
			state--; //Dekrementiere state 
			utf8++; //Inkrementiere Pointer auf nächstes Zeichen des Strings

			//hängt einen fertig generierten Codepunkt an tmp an
			if (state == 0) {
				sprintf(tmp + strlen(tmp), "%d;", utf8character);
				while (*tmp != 0) tmp++; //Incrementiert die Position von tmp wieder auf das Ende des Strings
			}
		}

		//Unicode Zeichen deren Werte unter 0x80 liegen werden direkt an den Result-String angehangen (bis auf Sonderfälle)
		if ((*utf8 & 0x80) == 0) {
			//Sonderfälle abarbeiten
			switch (*utf8) {
				case '&': sprintf(tmp + strlen(tmp), "%s", "&#38;"); tmp += 5; break;
				case '<': sprintf(tmp + strlen(tmp), "%s", "&#60;"); tmp += 5; break;
				case '>': sprintf(tmp + strlen(tmp), "%s", "&#62;"); tmp += 5; break;
				case '"': sprintf(tmp + strlen(tmp), "%s", "&#34;"); tmp += 5; break;
				case '\'': sprintf(tmp + strlen(tmp), "%s", "&#39;"); tmp += 5; break;
				default: *tmp = *utf8; tmp++; break;
			}			
		}

		//UTF-8 Character ist 2 Byte groß z.B. $
		if ((*utf8 & 0xE0) == 0xC0) {
			state = 1;
			//Zunächst werden die ersten 3 Bit wegmaksiert und anschließend Bitweise 6x nach links geschoben
			utf8character = (*utf8 & 0x1F)<<6; 
		}

		//UTF-8 Character ist 3 Byte groß z.B. €
		if ((*utf8 & 0xF0) == 0xE0) {
			state = 2;
			//Zunächst werden die ersten 4 Bit wegmaksiert und anschließend Bitweise 6x nach links geschoben
			utf8character = (*utf8 & 0xF)<<6;
		}

		//UTF-8 Character ist 4 Byte groß z.B. Smileys
		if ((*utf8 & 0xF8) == 0xF0) {
			state = 3;
			//Zunächst werden die ersten 5 Bit wegmaksiert und anschließend Bitweise 6x nach links geschoben
			utf8character = (*utf8 & 0x7)<<6;
		}

		//Hänge "&#" an den Result-String an, wenn es sich um ein Sonderzeichen handelt.
		if (state > 0) {
			sprintf(tmp + strlen(tmp), "%s", "&#");
			tmp += 2;	
		}			
		utf8++;
	}

	//Beende String
	*(tmp+1) = 0;
	return result;
}

int main() {
	//Beispiel String mit allen Sonderformen und Bytegrößen für UTF-8 Zeichen
	char s[] = "<b>Während Adam lacht, jagen zwölf Boxkämpfer 'Eva' \"quer\" über den großen Teich & ... 𐍈$€</b>";

	printf("Input String: %s\n", s);
	printf("Output String: %s\n", utf8_to_entities(s));

	return 0;
}