#include <vector>
#include <sstream>
#include <iostream>
#include "DataStore.h"

using namespace std;


DataStore::DataStore(Crypto *pCrypt){

	myCrypto = pCrypt;
}
DataStore::~DataStore(void){
	if(myCrypto){
		myCrypto = NULL;
	}
	delete myCrypto;
}
bool DataStore::decrypt(std::string &myString){

	try{
		if(myCrypto != 0){
			myCrypto->decrypt(myString);
		}else{
			return true;
		}
	}catch(exception& roException){
		cout << roException.what() << endl;
	}
	return true;
}
bool DataStore::encrypt(std::string &myString){

	try{
		if(myCrypto != 0){
			myCrypto->encrypt(myString);
		}else{
			return true;
		}
	}catch(exception& roException){
		cout << roException.what() << endl;
	}
	return true;
}


