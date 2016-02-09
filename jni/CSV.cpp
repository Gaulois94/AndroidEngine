#include "csv.h"

CSVParser::CSVParser() : value(NULL), nbValue(0)
{
}

CSVParser::CSVParser(const char* string) : value(NULL), nbValue(0)
{
	parse(string);
}

CSVParser::~CSVParser()
{
	if(values)
		free(values);
}

bool CSVParser::parse(const char* string)
{
	int32_t value=0;
	int8_t signe=1;
	int32_t exposant=1;
	int8_t numberSize=-1;
	uint32_t stringIndice;

	//Get only a number
	for(stringIndice=0; string[stringIndice] != ',' && string[stringIndice] != ';' && string[stringIndice] != '\0' && string[stringIndice] != '\n'; stringIndice++)
	{
		//Set the signe if needed
		if(string[stringIndice] == '-' && value == 0)
			signe *= -1;

		//Don't read spaces
		else if(string[stringIndice] == ' ')
			continue;

		//If the character is a number
		else if(string[stringIndice] - '0' >= 0 && string[stringIndice] - '0' <= 9)
		{
			value += exposant * (string[stringIndice] - '0');
			exposant *= 10;
			numberSize++;
		}

		else
		{
			LOG_ERROR("Error while parsing. Abort \n");
			return false;
		}
	}

	if(numberSize == -1)
	{
		LOG_ERROR("Error while parsing. Abord \n");
		return false;
	}
	
	//Replace the number correctly (in the first for loop, the number is mirrored)
	int32_t stringValue=0;
	int32_t i;
	for(i=0; i <= numberSize; i++)
	{
		stringValue *=10;
		stringValue += value % 10;
		value /=10;
	}

	stringValue *= signe;

	//Set our values array
	values = (int32_t*)realloc(values, (self->nbValue + 1)*sizeof(int32_t));
	values[self->nbValue] = stringValue;
	nbValue++;

	//If the string is finished to be read, return true
	if(string[stringIndice] == '\n' || string[stringIndice] == '\0')	
		return true;

	//Else, continue to parse on the second number
	return parse(&(string[stringIndice+1]));
}

const int32_t* CSVParser::getValues()
{
	return values;
}

const uint32_t CSVParser::getLen()
{
	return nbValue;
}
