#include "Utility.h"
#include<stdio.h>
#include<string>
#include<ctype.h>
//判断是否是合法的十六进制字符串
bool isHexString(char* szHex) {
	int len = 0;
	for (char* p = szHex; *p != '\0'; ++p){
		if (*p == '\n' || *p == ' ' || *p == '\r') {
			continue;
		}
		if (!isalnum(*p)) {
			return false;
		}
		++len;
	}
	return (len+1)&1;
}

//判断是否是合法的base64字符串
bool isBase64String(char* szBase64) {
	int len = 0;
	for (char* p = szBase64; *p != '\0'; ++p) {
		if(*p == '\n' || *p == ' ' || *p == '\r')
		if (isalnum(*p) || *p == '+' || *p == '/') {
			++len;
		}
		else if (*p == '=') {
			if (*(p + 1) == '\0' || (*(p + 1) == '=' && *(p + 2) == '\0')) {
				++len;
			}
			else {
				return false;
			}
		}
	}
	return (len & 3) == 0;
}
inline int alphToInt(char ch) {
	if (ch >= '0' && ch <= '9') {
		return ch - '0';
	}
	if (ch >= 'A' && ch <= 'F') {
		return ch - 'A' + 10;
	}
	if (ch >= 'a' && ch <= 'f') {
		return ch - 'a' + 10;
	}
	return 0xff;
}
int HexStr2Byte(const char* hex, unsigned char* out, unsigned int* outlen) {
	int n = strlen(hex);
	if (n % 2) {
		return -1;
	}
	if (outlen != nullptr  && *outlen < n / 2) {
		return -2;
	}
	unsigned char* _byte = new unsigned char[n / 2 + 1];
	unsigned char low = 0,high = 0;
	for (int i = 0; hex[i] != '\0'; i+= 2) {
		high = alphToInt(hex[i]);
		low = alphToInt(hex[i + 1]);
		if (high == 0xff || low == 0xff) {
			return -3;
		}
		_byte[i / 2] = high << 4 | low;
	}
	_byte[n / 2 ] = '\0';
	memcpy(out,  _byte, n / 2 + 1);
	*outlen = n / 2;
	return 0;
}


int Byte2HexStr(const unsigned char byte_arr[], int arr_len, char* HexStr, int* HexStrLen ) {
	int  i, index = 0;
	if (HexStrLen != nullptr && *HexStrLen <= arr_len * 2) {
		return -1;
	}
	for (i = 0; i < arr_len; i++)
	{
		char hex1;
		char hex2;
		int value = byte_arr[i];
		int v1 = value / 16;
		int v2 = value % 16;
		if (v1 >= 0 && v1 <= 9)
			hex1 = (char)(48 + v1);
		else
			hex1 = (char)(55 + v1);
		if (v2 >= 0 && v2 <= 9)
			hex2 = (char)(48 + v2);
		else
			hex2 = (char)(55 + v2);
		HexStr[index++] = hex1;
		HexStr[index++] = hex2;
	}
	if(HexStrLen != nullptr)
		*HexStrLen = index;
	return 0;
}