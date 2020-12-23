#pragma once
#include "ByteArray.h"
#include "softAlgorithm.h"


int CalMd5(const char* szHexIndata, char* szOut);

int CalSHA1(const char* szHexIndata, char* szOut);

int CalSHA256(const char* szHexIndata, char* szOut);

int CalSHA512(const char* szHexIndata, char* szOut);