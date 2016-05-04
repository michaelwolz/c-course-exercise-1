/* Aufgabe1 ****************************************************************
**
** Author: Michael Wolz
** Matrikelnummer: 1195270
**
******************************************************************************/

#include <stdio.h>
#include <string.h>

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

void test(char *s) {
	printf("\n#################################\n");
	printf("String ohne Trim: \"%s\"\n", s);
	printf("String mit Trim: \"%s\"", trim(s));
	printf("\n#################################\n");
}

int main() {
    char s1[] = " Hallo Test";
    char s2[] = "Hallo Test ";
    char s3[] = "    Hallo Test ";
    char s4[] = "";
 	char s5[] = "  	 	     Hallo Test       	";
    
    test(s1);
    test(s2);
    test(s3);
    test(s4);
    test(s5);
    
    return 0;
}


