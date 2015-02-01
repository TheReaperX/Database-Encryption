#pragma once
#include <string>

//used to store string/count pairs
class String_Data
{
private:
	std::string URL;
	int useCount;
	
	//copy constructor, destructor
	//do not make this private or vector will not work
	//(push_back makes a copy)
	//String_Data(String_Data const &other);

	// overloaded assignment
	String_Data const &operator=(String_Data const &other);
public:
	//create
	String_Data(std::string URL, int useCount=1);
	~String_Data(void);

	//how many times seen
	inline int getCount(){return useCount;}
	inline void increment(){useCount++;}

	//serialize for saving
	std::string serialize();

	//compare
	bool operator==( const String_Data &ud); 

	//static helper function, parses URL and usecount out of a string
	//so if myString = "Thread 0,20" when done URL = "Thread 0" and useCount=20
	static bool parseData(std::string &myString, std::string &URL, int &useCount);
};
