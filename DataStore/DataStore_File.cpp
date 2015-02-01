#include <vector>
#include <sstream>
#include <fstream> 
#include "DataStore_File.h"

using namespace std;


DataStore_File::DataStore_File(std::string fileName, Crypto* crypto): myFileName(fileName), DataStore(crypto){

}
DataStore_File::~DataStore_File(void){
}
bool DataStore_File::openFile(std::fstream& myfile,const std::string& myFileName, std::ios_base::openmode mode){
	if(myfile.is_open()){
		return true;
	}
	myfile.open(myFileName.c_str(),mode);
	return myfile.is_open();
}
void DataStore_File::closeFile(std::fstream& myfile){
	if (myfile.is_open()){
		myfile.close();
	}
}
bool DataStore_File::load(std::vector<String_Data> &myVector){
	fstream 			myfile;
	string				line;
	string				token;
	string				url;
	std::vector<string> mytokens;
	int					useCount;
	openFile(myfile, myFileName,std::ios_base::in);
	while(!myfile.eof()){
		getline(myfile, line);
		decrypt(line);
		stringstream ss(line);
		while(getline(ss,token,',')){
			mytokens.push_back(token);
		}
		url = mytokens.at(0);
		istringstream buffer(mytokens.at(1));
		buffer >> useCount;
		
		String_Data data(url,useCount);
		myVector.push_back(data);
	}
	closeFile(myfile);
	return true;
}
bool DataStore_File::save(std::vector<String_Data> &myVector){
	fstream  outfile;
	openFile(outfile, myFileName,std::ios_base::out);
	for (std::vector<String_Data>::iterator it = myVector.begin() ; it != myVector.end(); ++it){
		string serialized = it->serialize();
		encrypt(serialized);
		outfile<<serialized<<endl;
	}
	closeFile(outfile);
	return true;
}
