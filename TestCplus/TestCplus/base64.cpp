#include "stdafx.h"
#include "base64.h"  
#include <iostream>  

static const std::string base64_chars =   
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"  
	"abcdefghijklmnopqrstuvwxyz"  
	"0123456789+/";  


static inline bool is_base64(unsigned char c) {  
	return (isalnum(c) || (c == '+') || (c == '/'));  
}  
/*
base64编码
*/
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {  
	std::string ret;  
	int i = 0;  
	int j = 0;  
	unsigned char char_array_3[3];  
	unsigned char char_array_4[4];  

	while (in_len--) {  
		char_array_3[i++] = *(bytes_to_encode++);  
		if (i == 3) {  
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;  
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);  
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);  
			char_array_4[3] = char_array_3[2] & 0x3f;  

			for(i = 0; (i <4) ; i++)  
				ret += base64_chars[char_array_4[i]];  
			i = 0;  
		}  
	}  

	if (i)  
	{  
		for(j = i; j < 3; j++)  
			char_array_3[j] = '\0';  

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;  
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);  
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);  
		char_array_4[3] = char_array_3[2] & 0x3f;  

		for (j = 0; (j < i + 1); j++)  
			ret += base64_chars[char_array_4[j]];  

		while((i++ < 3))  
			ret += '=';  

	}  

	return ret;  

}  
/*
base64解码
*/
std::string base64_decode(std::string const& encoded_string) {  
	int in_len = encoded_string.size();  
	int i = 0;  
	int j = 0;  
	int in_ = 0;  
	unsigned char char_array_4[4], char_array_3[3];  
	std::string ret;  

	while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {  
		char_array_4[i++] = encoded_string[in_]; in_++;  
		if (i ==4) {  
			for (i = 0; i <4; i++)  
				char_array_4[i] = base64_chars.find(char_array_4[i]);  

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);  
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);  
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];  

			for (i = 0; (i < 3); i++)  
				ret += char_array_3[i];  
			i = 0;  
		}  
	}  

	if (i) {  
		for (j = i; j <4; j++)  
			char_array_4[j] = 0;  

		for (j = 0; j <4; j++)  
			char_array_4[j] = base64_chars.find(char_array_4[j]);  

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);  
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);  
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];  

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];  
	}  

	return ret;  
}  
/*
base64编码第二种方式，也可用
*/
std::string b64decodestring(const std::string &strString)
{
	int nByteSrc = strString.length();
	std::string pszSource = strString;

	const int dekey[] = {
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		62, // '+'
		-1, -1, -1,
		63, // '/'
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
		-1, -1, -1, -1, -1, -1, -1,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		-1, -1, -1, -1, -1, -1,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
	};

	if(nByteSrc%4 != 0)
		throw "bad base64 string";

	std::string pszDecode(nByteSrc*3/4+4, '\0');
	int nLoop = pszSource[nByteSrc-1]  == '=' ? nByteSrc - 4 : nByteSrc;
	int b[4];
	int i = 0, n = 0;
	for(i = 0; i < nLoop; i += 4 )
	{
		b[0] = dekey[pszSource[i]];        b[1] = dekey[pszSource[i+1]];
		b[2] = dekey[pszSource[i+2]];    b[3] = dekey[pszSource[i+3]];
		if(b[0] == -1 || b[1] == -1 || b[2] == -1 || b[3] == -1)
			throw "bad base64 string";

		pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
		pszDecode[n+1] = ((b[1] & 0xf) << 4) | ((b[2] & 0x3c) >> 2);
		pszDecode[n+2] =  ((b[2] & 0x3) << 6) | b[3];

		n+=3;
	}

	if( pszSource[nByteSrc-1] == '=' && pszSource[nByteSrc-2] == '=' )
	{
		b[0] = dekey[pszSource[i]];        b[1] = dekey[pszSource[i+1]];
		if(b[0] == -1 || b[1] == -1)
			throw "bad base64 string";

		pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
		pszDecode[n+1] = '\0';
	}

	if( pszSource[nByteSrc-1] == '=' && pszSource[nByteSrc-2] != '=' )
	{
		b[0] = dekey[pszSource[i]];        b[1] = dekey[pszSource[i+1]];
		b[2] = dekey[pszSource[i+2]];
		if(b[0] == -1 || b[1] == -1 || b[2] == -1)
			throw "bad base64 string";

		pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
		pszDecode[n+1] = ((b[1] & 0xf) << 4) | ((b[2] & 0x3c) >> 2);
		pszDecode[n+2] = '\0';
	}

	if( pszSource[nByteSrc-1] != '=' && pszSource[nByteSrc-2] != '=' )
		pszDecode[n] = '\0';

	return pszDecode;
}
