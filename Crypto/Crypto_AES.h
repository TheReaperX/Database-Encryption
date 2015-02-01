// Crypto_AES is a concrete class that derives from Crypto, use it for all your encryption needs

#ifndef CRYPTO_AES_H_
#define CRYPTO_AES_H_
#include <string>
#include "Reindaal.h"
#include "crypto.h"

//keylength  can be 16, 24 or 32 bytes
const int KEYLENGTH = 16;

// blockSize  - The block size in bytes of this Rijndael (16, 24 or 32 bytes).
const int BLOCKSIZE = 16;

enum cryptType{ENCRYPT,DECRYPT};
class Crypto_AES: public Crypto
{
private:
	//does the encrypt/decrypt
	Reindaal  reindaal;

	//common code for actual encryption
	bool crypt(std::string &myData, cryptType myCryptType);

public:
	int getLastError();

	Crypto_AES(char *pKey);
	virtual ~Crypto_AES(void);

	bool encrypt(std::string &myDecryptedData);
	bool decrypt(std::string &myEncryptedData);
};


#endif /*  CRYPTO_AES_H_ */
