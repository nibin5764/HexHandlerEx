/****************************************************************
This is a sample routine of base64 algorithm.The goal is to
illustrate principles,so some details may be ignored.
Author email:zhangwu2003@163.com
*****************************************************************/
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#if 0
char*  ch64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char *base64_encode(unsigned char *src,int srclen)
{
	int n,buflen,i,j;
	int pading=0;
	unsigned char *buf;
	static unsigned char *dst; 
	
	buf=src;
	buflen=n=srclen;
	if(n%3!=0)  /* pad with '=' by using a temp buffer */
	{
		pading=1;
		buflen=n+3-n%3;
		buf=malloc(buflen+1);
		memset(buf,0,buflen+1);
		memcpy(buf,src,n);
		for(i=0;i<3-n%3;i++)
			buf[n+i]='=';
	}
	dst=malloc(buflen*4/3+1);
	memset(dst,0,buflen*4/3+1);
	for(i=0,j=0;i<buflen;i+=3,j+=4)
	{
		dst[j]=(buf[i]&0xFC)>>2;
		dst[j+1]=((buf[i]&0x03)<<4) + ((buf[i+1]&0xF0)>>4);
		dst[j+2]=((buf[i+1]&0x0F)<<2) + ((buf[i+2]&0xC0)>>6);
		dst[j+3]=buf[i+2]&0x3F; 
	}
	for(i=0;i<buflen*4/3;i++) /* map 6 bit value to base64 ASCII character */
		dst[i]=ch64[dst[i]];
	if(pading)
		free(buf);
	return dst;
}

unsigned char *base64_decode(unsigned char *src)
{
	int n,i,j;
	unsigned char *p;
	static unsigned char *dst; 
	
	n=strlen(src);
	for(i=0;i<n;i++) /* map base64 ASCII character to 6 bit value */
	{
		p=strchr(ch64,src[i]);
		if(!p)
			break;
		src[i]=p-ch64;
	}
	dst=malloc(n*3/4+1);
	memset(dst,0,n*3/4+1);
	for(i=0,j=0;i<n;i+=4,j+=3)
	{
		dst[j]=(src[i]<<2) + ((src[i+1]&0x30)>>4);
		dst[j+1]=((src[i+1]&0x0F)<<4) + ((src[i+2]&0x3C)>>2);
		dst[j+2]=((src[i+2]&0x03)<<6) + src[i+3];
	}
	return dst;
}
#else
//////////////////////////////////////////////////////////////////////////
//
//    pcTxt: ����ǰ����
//    nTxtlen������ǰ���ݵĳ���
//    pcBuf���ַ���������
//    �����ַ����ĳ��ȡ�
//////////////////////////////////////////////////////////////////////////
int base64_encode(unsigned char *pcTxt, int nTxtlen, char *pcBuf)
{ 
    const unsigned char Base64_EnCoding[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int nBuflen = 0; 
    unsigned char *pt = (unsigned char *)pcTxt;
    
    /* nTxtlen С�� 0�������м��� pcTxt �ĳ��� */
    if( nTxtlen < 0 )
    {
        while( *pt++ ){ nTxtlen++; }
        pt = (unsigned char *)pcTxt;
    }
    if( !nTxtlen ) return 0;
	
    while( nTxtlen > 0 )
    {
        *pcBuf++ = Base64_EnCoding[ ( pt[0] >> 2 ) & 0x3f];
        if( nTxtlen > 2 )
        {
            *pcBuf++ = Base64_EnCoding[((pt[0] & 3) << 4) | (pt[1] >> 4)];
            *pcBuf++ = Base64_EnCoding[((pt[1] & 0xF) << 2) | (pt[2] >> 6)];
            *pcBuf++ = Base64_EnCoding[ pt[2] & 0x3F];
        }
        else
        {
            switch( nTxtlen )
            {
            case 1:
                *pcBuf++ = Base64_EnCoding[(pt[0] & 3) << 4 ];
                *pcBuf++ = '=';
                *pcBuf++ = '=';
                break;
            case 2: 
                *pcBuf++ = Base64_EnCoding[((pt[0] & 3) << 4) | (pt[1] >> 4)]; 
                *pcBuf++ = Base64_EnCoding[((pt[1] & 0x0F) << 2)]; 
                *pcBuf++ = '='; 
            } 
        } 
        pt += 3; 
        nTxtlen -= 3; 
        nBuflen += 4; 
    } 
    *pcBuf = 0; 
    return nBuflen; 
}

//////////////////////////////////////////////////////////////////////////
//
//    pcTxt: ����ǰ����
//    nTxtlen������ǰ���ݵĳ���
//    pcBuf����������
//    �����ֽ����ݵó��ȡ�
//////////////////////////////////////////////////////////////////////////
int base64_decode(const char *pcTxt,int nTxtlen, unsigned char *pcBuf) 
{
    unsigned char ucs[4];
    char *pt = (char *)pcTxt;
    int nBuflen = 0 , nfag = 0 , i = 0;
    /* nTxtlen С�� 0�������м��� pcTxt �ĳ��� */
    if( nTxtlen < 0 )
    {
        while( *pt++ ){ nTxtlen++; }
        pt = (char *)pcTxt;
    }
    if( !nTxtlen ) return 0;
    while( nTxtlen > 0 )
    {
        nfag = 0;
        for( i=0 ; i<4 ; i++ )
        {
            if (*pt >= 'A' && *pt <= 'Z') 
                ucs[i] = *pt - 'A'; 
            else if (*pt >= 'a' && *pt <= 'z') 
                ucs[i] = *pt - 'a' + 26; 
            else if (*pt >= '0' && *pt <= '9') 
                ucs[i] = *pt - '0' + 52; 
            else{
                switch (*pt)
                { 
                case '+': 
                    ucs[i] = 62;
                    break;
                case '/': 
                    ucs[i] = 63;
                    break;
                case '=': /* base64 padding */ 
                    ucs[i] = 0; 
                    nBuflen --;
                    break;
                case '\t':
                case '\r':
                case '\n':
                case ' ':
                    nfag++;
                    i--;
                    break;
                case '\0': /* ������β,ֱ�ӷ����ϴ��ַ� buf �ĳ��� */ 
                    *pcBuf = 0;
                    return nBuflen;
                    break;
                default:  /* ���������Ƿ��ַ�,ֱ�ӷ��� */
                    *pcBuf = 0;
                    return -1;
                }
            }
            pt++;
        }
        *pcBuf++ = (ucs[0] << 2) | (ucs[1] >> 4);
        *pcBuf++ = (ucs[1] << 4) | (ucs[2] >> 2);
        *pcBuf++ = (ucs[2] << 6) | (ucs[3]);
        nTxtlen -= nfag + 4;
        nBuflen += 3;
    }
    *pcBuf = 0;
    //���� buf ����
    return nBuflen;
}
#endif