#include "stdafx.h"
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <sstream>
#include "..\String_Database\String_Database.h"
#include "..\DataStore\DataStore_File.h"
#ifdef JUST_FOR_KEITH
#include "..\DataStore\DataStore_String.h"
#endif
#include "..\Crypto\Crypto_AES.h"

//global database object 
String_Database myGlobalCache;

const int TOTAL_ADDED	=20;
const int TOTAL_THREADS =20;
const std::string ENCRYPT_FILE1 = "Encryptfile1.txt";
const std::string ENCRYPT_FILE2 = "Encryptfile2.txt";


const std::string NO_ENCRYPT_FILE1 = "noEncryptfile1.txt";
const std::string NO_ENCRYPT_FILE2 = "noEncryptfile2.txt";

//will add myString numbTimes to myGlobalCache
void ThreadFunc(int numbTimes, std::string myString) 
{
	for (int i = 0; i < numbTimes; i++)
	{
		myGlobalCache.add(myString);
	}
}
bool testSerialization(const std::string &MYFILE1, const std::string &MYFILE2, Crypto *pCrypto){
	DataStore_File myDataStore_File1(MYFILE1,pCrypto);
	myGlobalCache.save(&myDataStore_File1);
//	std::cout<<"Saving to file "+ MYFILE1 +" \n";

	//clear cache
	myGlobalCache.clear();
//	std::cout<<"Clearing Cache\n";

	//load it
	myGlobalCache.load(&myDataStore_File1);
//	std::cout<<"Loading from file "+ MYFILE1 +" \n";

	//save to a different file
	DataStore_File myDataStore_File2(MYFILE2,pCrypto);
	myGlobalCache.save(&myDataStore_File2);
//	std::cout<<"Saving to file "+ MYFILE2 +" \n";

#ifdef JUST_FOR_KEITH
	//helper class for verifying that file text is the same
	//see if they are both the same
	DataStore_String myDataStore_String1(MYFILE1, pCrypto);
	DataStore_String myDataStore_String2(MYFILE2, pCrypto);
	myDataStore_String1.load();
	myDataStore_String2.load();

	//are they the same
	return  (myDataStore_String1 == myDataStore_String2);
#else
	return false;
#endif

}
int main() 
{
	//1. create a vector of thread names Thread 1 Thread 2 etc. 
	std::vector<std::string> myURLs;
	for(int i = 0; i < TOTAL_THREADS; ++i){
		myURLs.push_back("Thread "+std::to_string(i) );
	}

	//2. create and run the threads
	std::vector<std::thread> threads;
	for(int i = 0; i < TOTAL_THREADS; ++i){
		threads.push_back(std::thread(ThreadFunc,TOTAL_ADDED,myURLs[i]));
	}

	//3. wait for all threads to finish
    for(auto& thread : threads){
        thread.join();
    }

	//ThreadFunc(TOTAL_ADDED,myURLs[0]);
	//ThreadFunc(TOTAL_ADDED,myURLs[1]);

	//for each thread created in 1. 
	//ThreadFunc added the string 'Thread n' TOTAL_ADDED times to  myGlobalCache
	//This bit just verifies that fact
	int myCount;
	bool bSuccess = true;
	for(int i = 0; i < TOTAL_THREADS; ++i){
		myCount = myGlobalCache.getCount(myURLs[i]);
		if (myCount != TOTAL_ADDED){
			std::cout<<"ERROR "<<myURLs[i]<<" found "<<myCount<<" times, Should have been " <<TOTAL_ADDED<< " times \n";
			bSuccess = false;
		}
	}

	if (bSuccess)
		std::cout<<"CORRECT ... Database verification (correct # entries and count) \n";
	else
		std::cout<<"YIKES, ITS BROKEN ... Database verification (correct # entries and count)\n";

#ifdef JUST_FOR_KEITH
	//test without encryption
	if (testSerialization(NO_ENCRYPT_FILE1, NO_ENCRYPT_FILE2, 0))
		std::cout<<"CORRECT ... FILE I/O NO encryption "+ NO_ENCRYPT_FILE1 +" is the same as " + NO_ENCRYPT_FILE2+ " \n";
	else
		std::cout<<"FAILED ... FILE I/O NO encryption "+ NO_ENCRYPT_FILE1 +" is different from " + NO_ENCRYPT_FILE2+ " \n";

	
	//test with encryption
	Crypto_AES myCrypto("I Like Rollos   ");
	if (testSerialization(ENCRYPT_FILE1, ENCRYPT_FILE2, &myCrypto))
		std::cout<<"CORRECT ... FILE I/O ENCRYPTING "+ ENCRYPT_FILE1 +" is the same as " + ENCRYPT_FILE2+ " \n";
	else
		std::cout<<"FAILED ... FILE I/O ENCRYPTING "+ ENCRYPT_FILE1 +" is different from " + ENCRYPT_FILE2+ " \n";
#else
	testSerialization(NO_ENCRYPT_FILE1, NO_ENCRYPT_FILE2, 0);
	std::cout<<"FILE I/O NO encryption, manually compare "+ NO_ENCRYPT_FILE1 +" and " + NO_ENCRYPT_FILE2+ " \n";

	Crypto_AES myCrypto("I Like Rollos   ");
	testSerialization(ENCRYPT_FILE1, ENCRYPT_FILE2, &myCrypto);
	std::cout<<"FILE I/O encryption, manually compare "+ ENCRYPT_FILE1 +" and " + ENCRYPT_FILE2+ " \n";

#endif

}