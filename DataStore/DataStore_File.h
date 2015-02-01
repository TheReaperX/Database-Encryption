#pragma once
#include <vector>
#include "String_Data.h"
#include "DataStore.h"

//loads data from a file and saves it back to a file
class DataStore_File :
	public DataStore
{
public:
	//loads 
	DataStore_File(std::string fileName, Crypto* crypto = 0);
	virtual ~DataStore_File(void);

	bool load(std::vector<String_Data> &myVector);
	bool save(std::vector<String_Data> &myVector);
private:
	bool openFile(std::fstream& myfile,const std::string& myFileName, std::ios_base::openmode mode);
	void closeFile(std::fstream& myfile);
private:
	std::string myFileName;

};

