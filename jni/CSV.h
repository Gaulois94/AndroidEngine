#ifndef  CSV_INC
#define  CSV_INC

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "typedefine.h"

class CVSParser
{
	public:
		CSVParser();
		CSVParser(const char* string);
		~CSVParser();

		/** \brief parse the string "string". After each number, this function calls itself, while the string isn't read entirely.
		 * \param string the string to parse
		 * \return return if the parser has correctly parsed the file or not*/
		bool parse(const char* string);

		/** \brief get the value of the Parser
		 * \return the value array of the parser. Use getLen to get the value array's length*/
		const int32_t* getValues();

		/** \brief returns the length of the array values
		 * \return the number of values of the parser*/
		const uint32_t getLen();
	private:
		int32_t* values;
		uint32_t nbValue;
};
#endif
