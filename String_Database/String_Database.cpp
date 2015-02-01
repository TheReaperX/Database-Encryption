#include "String_Database.h";

using namespace std;


String_Database::String_Database(void){

}
String_Database::~String_Database(void){

}

//add or increment the count for myURL
void String_Database::add(std::string &myURL){
	    std::lock_guard<std::mutex> lck (mutex);
		String_Data data(myURL);

		myURLiter = find (myURLs.begin(), myURLs.end(), data);
		if (myURLiter != myURLs.end())
			myURLiter->increment();
		else
			myURLs.push_back(data);
}

//get number of times myURL has been seen
//sometimes you need getters
int String_Database::getCount(std::string &myURL){
	std::lock_guard<std::mutex> lck (mutex);
	String_Data data(myURL);
	for(myURLiter = myURLs.begin(); myURLiter != myURLs.end(); myURLiter++){
		if(myURLiter->operator==(myURL)){
			return myURLiter->getCount();;	
		}
	}
	return 0;

}

//clear the cache
void String_Database::clear(){
	std::lock_guard<std::mutex> lck (mutex);
	myURLs.clear();
}

//load from datastore
bool String_Database::load(DataStore  *myDataStore){
	std::lock_guard<std::mutex> lck (mutex);
	myDataStore->load(myURLs);
	return true;
}

//save to datastore
bool String_Database::save(DataStore *myDataStore){
	std::lock_guard<std::mutex> lck (mutex);
	myDataStore->save(myURLs);
	return true;
}