#include <vector>
#include <sstream> 
#include "String_Data.h"

using namespace std;

String_Data::String_Data(std::string URL, int useCount): URL(URL),useCount(useCount)
{
}

String_Data::~String_Data(void)
{
}


bool String_Data::operator==( const String_Data &ud)
{
	return (URL == ud.URL);
} 

std::string String_Data::serialize(){
	return (std::string(URL + "," + std::to_string(useCount)));
}

bool String_Data::parseData(std::string &myString, std::string &URL, int &useCount){
	stringstream ss(myString);

	//get URL
	if ( !ss.good() )
		return false;
	getline( ss, URL, ',' );

	//get usecount
	if ( !ss.good() )
		return false;

	string tmpString;	
	getline( ss, tmpString, ',' );
	istringstream( tmpString)>>useCount;

	return true;
}
