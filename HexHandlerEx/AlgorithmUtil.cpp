#include "AlgorithmUtil.h"
#include <string.h>
#pragma comment(lib,"Algorithm.lib")

int CalMd5(const char* szHexIndata, char* szOut) {
	ByteArray baIndata = szHexIndata;
	baIndata = baIndata.stringToByte();
	if (baIndata.length() <= 0) {
		return -1;
	}
	ByteArray  out;
	CalcMd5(out, baIndata, baIndata.length());
	out = out.byteToString();
	strcpy_s(szOut,33, (char*)out.data());
	return 0;
}


int CalSHA1(const char* szHexIndata, char* szOut) {
	ByteArray baIndata = szHexIndata;
	baIndata = baIndata.stringToByte();
	if (baIndata.length() <= 0) {
		return -1;
	}
	ByteArrayBuffer  out;
	CalcSha1(out, baIndata);
	ByteArray baout = out.toByteArray().byteToString();
	strcpy_s(szOut,33, (char*)baout.data());
	return 0;
}

int CalSHA256(const char* szHexIndata, char* szOut) {
	ByteArray baIndata = szHexIndata;
	baIndata = baIndata.stringToByte();
	if (baIndata.length() <= 0) {
		return -1;
	}
	ByteArrayBuffer  out;
	CalcSha256(out, baIndata);
	ByteArray baout = out.toByteArray().byteToString();
	strcpy_s(szOut,33, (char*)baout.data());
	return 0;
}

int CalSHA512(const char* szHexIndata, char* szOut) {
	ByteArray baIndata = szHexIndata;
	baIndata = baIndata.stringToByte();
	if (baIndata.length() <= 0) {
		return -1;
	}
	ByteArrayBuffer  out;
	CalcSha512(out, baIndata);
	ByteArray baout = out.toByteArray().byteToString();
	strcpy_s(szOut,33, (char*)baout.data());
	return 0;
}