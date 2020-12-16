#ifndef _BASE64_H_
#define _BASE64_H_

//#if 0
//unsigned char *base64_encode(unsigned char *src,int srclen);
//unsigned char *base64_decode(unsigned char *src);
//#else
//////////////////////////////////////////////////////////////////////////
//
//    pcTxt: ����ǰ����
//    nTxtlen������ǰ���ݵĳ���
//    pcBuf���ַ���������
//    �����ַ����ĳ��ȡ�
//////////////////////////////////////////////////////////////////////////
#ifdef  __cplusplus 
extern "C"
{
#endif
	
int base64_encode(unsigned char *pcTxt, int nTxtlen, char *pcBuf);

//////////////////////////////////////////////////////////////////////////
//
//    pcTxt: ����ǰ����
//    nTxtlen������ǰ���ݵĳ���
//    pcBuf���ַ���������
//    �����ַ����ĳ��ȡ�
//////////////////////////////////////////////////////////////////////////

int base64_decode(const char *pcTxt, int nTxtlen, unsigned char *pcBuf);
#ifdef __cplusplus
}
#endif

#endif