#pragma once
#include "base64.h"

//�ж��Ƿ��ǺϷ���ʮ�������ַ���
bool isHexString(char* szHex);

//�ж��Ƿ��ǺϷ���base64�ַ���
bool isBase64String(char* szBase64);

//16�����ַ���ת�ֽ�����
int HexStr2Byte(const char* hex, unsigned char* out, unsigned int* outlen);

//�ֽ�����ת16�����ַ���
int  Byte2HexStr(const unsigned char byte_arr[], int arr_len, char* HexStr, int* HexStrLen = nullptr);