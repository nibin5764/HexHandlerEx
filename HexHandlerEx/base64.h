#ifndef _BASE64_H_
#define _BASE64_H_

//#if 0
//unsigned char *base64_encode(unsigned char *src,int srclen);
//unsigned char *base64_decode(unsigned char *src);
//#else
//////////////////////////////////////////////////////////////////////////
//
//    pcTxt: 编码前数据
//    nTxtlen：编码前数据的长度
//    pcBuf：字符串的内容
//    返回字符串的长度。
//////////////////////////////////////////////////////////////////////////
#ifdef  __cplusplus 
extern "C"
{
#endif
	
int base64_encode(unsigned char *pcTxt, int nTxtlen, char *pcBuf);

//////////////////////////////////////////////////////////////////////////
//
//    pcTxt: 编码前数据
//    nTxtlen：编码前数据的长度
//    pcBuf：字符串的内容
//    返回字符串的长度。
//////////////////////////////////////////////////////////////////////////

int base64_decode(const char *pcTxt, int nTxtlen, unsigned char *pcBuf);
#ifdef __cplusplus
}
#endif

#endif