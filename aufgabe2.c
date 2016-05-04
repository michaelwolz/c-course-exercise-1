/* Aufgabe2 ****************************************************************
**
** Author: Michael Wolz
** Matrikelnummer: 1195270
**
** Author: Aaron Winziers
** Matrikelnummer: 1176638
**
******************************************************************************/

#include <stdio.h>
#include <string.h> //für strlen

//**Defintion der Trim Funktion aus Aufgabe 1 (normalerweise wäre ein Include hier besser aber für die Aufgabenstellung belasse ich es jetzt bei dieser Lösung)**//

char *trim(char *s) {
	char *end;
	end = s + strlen(s) - 1;

	//Vordere Leerzeichen
    while (*s == ' ' || *s == '\t') s++;

	if (*s == 0)
		return s;

	//Hintere Leerzeichen
	while ((end > s) && (*end == ' ' || *end == '\t')) end--;
	*(end+1) = 0;
	 
    return s;
}

//**Ende Trim**//

int parseInt(char *s) {
	char *trimmedString = trim(s); //Trim Leerzeichen
    int sign = 1; //Vorzeichen initialisiert mit 1 (für +)
    int result = 0;
    
    if (*trimmedString == '-') {
    	sign = -1; //Vorzeichen auf -1 setzen (für -)
    	trimmedString++; //Weiter zum nächsten Zeichen
    }
        
    while (*trimmedString != 0) { //Solange Zeichen vorhanden sind.
    	result = result * 10 + *trimmedString - '0'; //Zwischenergebnis um "10er" Stelle "verschieben" und nächstes Zeichen als "1er" Stelle hinzufügen
    	trimmedString++; //Weiter zum nächsten Zeichen
    }
    
    result = result * sign; //Vorzeichen hinzufügen
    return result;
}

void test(char *s) {
	printf("\n#################################\n");
	printf("Zahl als String: \"%s\"\n", s);
	printf("Zahl als Integer: %i", parseInt(s));
	printf("\n#################################\n");
}

int main() {
    char s1[] = "212";
    char s2[] = "-2200";
    char s3[] = "0210";
    char s4[] = " 1 ";
   
    test(s1);
    test(s2);
    test(s3);
    test(s4);
     
    return 0;
}