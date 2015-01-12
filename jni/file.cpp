#include "file.h"

char* getLine(FILE* file, int maxCharacters)
{
	char* line = (char*) malloc(maxCharacters*sizeof(char));
	char c;
	int i=0;
	
	while((c = fgetc(file)) != EOF && c != '\n' && i < maxCharacters-1)
	{
		*(line + i)=c;
		i++;
	}
	
	*(line + i) = '\0';
	return line;
}
