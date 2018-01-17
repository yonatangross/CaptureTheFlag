#include "stringUtils.h"

int stringToint(const char * value)
{
	stringstream strValue;
	strValue << value;

	unsigned int intValue;
	strValue >> intValue;
}