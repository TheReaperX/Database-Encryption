#pragma once
#include <string>
#include <vector>
#include <mutex>
#include "..\DataStore\String_Data.h"
#include "..\DataStore\DataStore_File.h"

class String_Database
{
private:
	std::mutex mutex;
	std::vector<String_Data> myURLs;
	std::vector<String_Data>::iterator  myURLiter;

public:
	String_Database(void);
	~String_Database(void);

	//add or increment the count for myURL
	void add(std::string &myURL);

	//get number of times myURL has been seen
	//sometimes you need getters
	int getCount(std::string &myURL);

	//clear the cache
	void clear();

	//load from datastore
	bool load(DataStore  *myDataStore);

	//save to datastore
	bool save(DataStore *myDataStore);
};

