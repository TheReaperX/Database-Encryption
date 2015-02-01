#pragma once
//this class is not meant for instantiation, just a static helper
//HexHelper a static class with methods used to convert binary 1 byte chars to their 2 byte hex equivelant 'D' => "44" and back
//this means that your binary strings double in size when converted to hex and vice versa. Not the most effecient way Base64 
//is better as the final size of the converted binary string is not doubled.  But this is fine for this project
class HexHelper
{
public:
	//converts from 1 byte binary to 2 byte hex
	static void Char2Hex(unsigned char ch, char* szHex);
	static void Hex2Char(char const* szHex, unsigned char& rch);
	static void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);
	static void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);

private:
	HexHelper(void);
	~HexHelper(void);
};

