#pragma once
#include "base64.h"

//判断是否是合法的十六进制字符串
bool isHexString(char* szHex);

//判断是否是合法的base64字符串
bool isBase64String(char* szBase64);

//16进制字符串转字节数组
int HexStr2Byte(const char* hex, unsigned char* out, unsigned int* outlen);

//字节数组转16进制字符串
int  Byte2HexStr(const unsigned char byte_arr[], int arr_len, char* HexStr, int* HexStrLen = nullptr);