/**************************************************************************************************
* Name:        ByteArray.h
* Purpose:     Byte�������͵ķ�װ����δ�ֶ�����0x00�ַ�������£�����ֱ�ӵ���ASCII�ַ���ʹ��
* Copyright:   Copyright (C) 2010
* Author:      Zhou Fei
* Created:     2010.11.26

*******************************Change History******************************************************

Date        Author      Event
--------------------------------------
2010-11-26  Zhou Fei    Create    

**************************************************************************************************/
#ifndef __ZF_BYTEARRAY_H__
#define __ZF_BYTEARRAY_H__

#include <stdarg.h>
#include "hd_type_def.h"

class ByteArrayBuffer;
class ByteArray 
{
public:
    ByteArray(void);
    ByteArray(const ByteArray &other);
    ByteArray(const hz_byte *pbData, hz_uint32 cbData);
    ByteArray(const char *pszStr);
    ByteArray(hz_byte ch, hz_uint32 ulNumber);

    virtual ~ByteArray(void);
    
    /**
    * ������ĩβ׷�ӳ���ΪcbData������
    */
    virtual hz_bool append(const hz_byte *pbData, hz_uint32 cbData);
    
    /**
    * ���ַ���ĩβ׷���ַ���
    */
    virtual hz_bool append(const char *pszStr);
    virtual hz_bool append(const ByteArray &other);

    /**
    * ���ַ���ĩβ׷��һ���ַ�
    */
    virtual hz_bool append(hz_byte ch);

    /**
    * ��ָ��λ�ò���һ���ַ�
    */
    virtual hz_bool insert(hz_uint32 ulIndex, hz_byte ch);

	/**
	* ��ָ��λ�ò���һ���ַ���(������\0������)
	*/
	hz_bool insert(hz_uint32 ulIndex, const char *str);
	
	/**
	* ��ָ��λ�ò���һ��ByteArray
	*/
	virtual hz_bool insert(hz_uint32 ulIndex, const ByteArray &ba);

    /**
    * ��ȡָ��λ�õ��ֽ�����
    */
    virtual hz_byte at(hz_uint32 ulIndex) const;

    /**
    * ����ָ��λ�õ�ֵ���ú������ã���ByteArray��Ϊ�ַ���ʹ��ʱ��С�Ĳ�Ҫ���ַ����м����0x00��
    */
    virtual hz_bool setAt(hz_uint32 ulIndex, hz_byte ch);

    /**
    * ������ת��ָ�����ƻ����ַ���
    *@param [in] ulNumber ��ת�����ַ�����10����������ֵ
    *@param [in] ulBase ����ʲô���ƽ���ת����ȡֵ��ΧΪ[2,16],��֧�ִӶ����ƿ�ʼ��ʮ�����ƽ���
    */
    virtual ByteArray & fromNumber(hz_int32 ulNumber, hz_uint32 ulBase = 10);

    /**
    * ����ŵ��ַ���ת����10��������
    */
    virtual hz_int32 toNumber() const;

	/** 
	* ��double����ת�����ַ���
	*/
	virtual ByteArray & fromDouble(double dValue, hz_uint8 ulPrecision = 6);

	/** 
	* ���ַ���ת����double
	*/
	virtual double toDouble() const;

    /**
    * ��Byte����ת�����ַ���,��洢����0x30 0x31 0x32 0x33, ת����洢�ľ���30313233
    *@return �ɹ��ͷ���ת������ַ�����ʧ�ܷ��ض��󳤶�Ϊ0
    */
    virtual ByteArray byteToString() const;

    /**
    * ���ַ���ת����Byte����,��洢����30313233,ת�������0x30 0x31 0x32 0x33
    *@return �ɹ��ͷ���ת������ַ�����ʧ�ܷ��ض��󳤶�Ϊ0
    *@note �����ַ���תbyteʱҪ��2���ֽ�ת1���ֽڣ������ԭʼ���ݳ��Ȳ�Ϊ2�ı���ʱ��ת��ʧ�ܣ�
    *      �������ת��ǰ���ַ����а���������0~9,a~z,A~Z��Χ�ڵ��ַ�ʱ��ת��Ҳ��ʧ�ܡ�
    */
    virtual ByteArray stringToByte() const;

    /**
    * ��ulPosStart��ʼ������ch��һ�γ��ֵ�λ��
    */
    virtual hz_int32 indexOf(hz_byte ch, hz_uint32 ulPosStart = 0) const;

	/**
    * ��ulPosStart��ʼ������ba��һ�γ��ֵ�λ��
    */
    virtual hz_int32 indexOf(const ByteArray & ba, hz_uint32 ulPosStart = 0) const;

    /**
    * ����ch���һ�γ��ֵ�λ��
    */
    virtual hz_int32 lastIndexOf(hz_byte ch) const;

	/**
    * ����ba���һ�γ��ֵ�λ��
    */
    virtual hz_int32 lastIndexOf(const ByteArray & ba) const;

    /**
    * ���ⲿ����õ�һ�ζ��ڴ�ֱ�ӽ�����CByteArry����ʹ�á�Attach�ɹ���,�ⲿ���������ʹ�øö��ڴ棬Ҳ����Ҫ�ͷ��ڴ�
    *@param [in] pbData ָ��һ���ⲿ����õ��ڴ�
    *@param [in] cbData pbDataָ����ڴ��С
    *@return TRUE��ʾ�ɹ���FALSE��ʾʧ��
    */
    virtual hz_bool attach(hz_byte *pbData, hz_uint32 cbData);

    /**
    * �����������
    */
    virtual void clear(void);

	/**
    * Set the capacity of the string to ulSize characters.
    *If ulSize is greater than the current capacity, the capacity of the string is extended to make it ulSize characters long.
    *The new characters will be initialized to '\\0'.
    *If ulSize is less than the current capacity, characters are removed from the end.
    *Do nothing if ulSize is equal to current capacity.
    *@param [in] ulSize The size of string buffer.
    */
    virtual hz_bool resize(hz_uint32 ulSize);

	/** 
	* ���ַ���ת���ɴ�д
	*/
	virtual ByteArray toUpper(void) const;

	/**
	* ���ַ���ת����Сд
	*/
	virtual ByteArray toLower(void) const;

    /**
    * �ж��Ƿ�����Ϊ��
    */
    virtual hz_bool isEmpty(void) const;

    /**
    * �Ƴ���ulPosition��ʼ������ΪulLength������
    *@param [in] ulPosition ��ʼ���кţ����Ƴ������ݰ�������ʼ���к�ָ����ַ�
    *@param [in] ulLength ���Ƴ������ݳ��ȣ����ó��ȳ�����ʣ������ݳ��Ȼ���ulLengthΪ-1������ʾ�Ƴ�ulPosition�Ժ����������
    */
    virtual hz_bool remove(hz_uint32 ulPosition, hz_uint32 ulLength = -1);

	/**
    * Replaces n characters beginning at index ulPosition with the string after
    *@param [in] ulPosition the start position
    *@param [in] n number of characters will be replaced
    *@param [in] after The substring which will be replaced to it.
    *@return a reference to this string.
    */
	virtual ByteArray & replace( hz_uint32 ulPosition, hz_uint32 n, const ByteArray & after);
	
	/**
    * Replaces every occurrence of the string before with the string after 
    *@param [in] before The substring which will be replaced.
    *@param [in] after The substring which will be replaced to it.
    *@return a reference to this string.
    */
	virtual ByteArray & replace( const ByteArray & before, const ByteArray & after);

    /**
    * ��ȡ��ulPosition��ʼ������ΪulLength��һ������
    *@param [in] ulPosition ��ʼ���кţ���ȡ�����ݰ�������ʼ���к�ָ����ַ�
    *@param [in] ulLength ��ȡ�����ݳ��ȣ����ó��ȳ�����ʣ������ݳ��Ȼ���ulLengthΪ-1������ʾȡ��ulPosition�Ժ����������
    *@return ���ؽ�ȡ��������
    */
    virtual ByteArray sub(hz_uint32 ulPosition, hz_uint32 ulLength = -1) const;

    /**
    * ȡ����ߵĳ���Ϊlength���Ӵ�
    */
    virtual ByteArray left(hz_uint32 length) const;

    /**
    * ȡ���ұߵĳ���Ϊlength���Ӵ�
    */
    virtual ByteArray right(hz_uint32 length) const;

    /**
    * �жϵ�ǰ���ݴ�(�ַ���)�Ƿ���prefix��ͷ
    */
    virtual hz_bool startsWith(const ByteArray &prefix) const;

    /**
    * �жϵ�ǰ���ݴ�(�ַ���)�Ƿ���suffix��β
    */
    virtual hz_bool endsWith(const ByteArray &suffix) const;

    /**
    * ����ǰ���ݴ�(�ַ���)��ת
    */
    virtual ByteArray &reverse();

	virtual hz_uint32 capacity() const;

	/** 
	* ͳ���ַ�ch���ֽ������г��ֵĴ���
	*/
	virtual hz_uint32 statistics(hz_char ch) const;

	/** 
	* ͳ���ַ�ch���ֽ������г��ֵĴ���,����ʹ��count()������statistics()
	*/
	virtual hz_uint32 count(hz_char ch) const;

	/** 
	* ͳ������ba���ֽ������г��ֵĴ���
	*/
	virtual hz_uint32 count(const ByteArray &ba) const;

    /**
    * ֱ�ӷ��ʴ洢����������
    *@note ��ע�ⲻҪֱ���޸���������
    */
    virtual const hz_byte *data(void) const;

    /**
    * �ֽ�������ַ��������ݳ��ȣ��˳��Ȳ������ѷ�����ڴ泤�ȣ�ֻ������Ч���ݳ��ȣ�
    */
    virtual hz_uint32 length() const;

	/**
    * Safely builds a formatted string from the format string cFormat and an arbitrary list of arguments.
    *@param [in] strFormat format description string.
    *@return A reference to this string.
    *@note 
    *pszFormat %[flag][width][.precision][length flag]type\n
    *flag : \n
    *    0 is only supported flag. It means that zero padded if the length of destination is smaller than width.\n
    *width : \n
    *    specific width, when the length of destination is smaller than width, using zero to pad if flag is 0, and using ' ' to pad if flag is not 0.\n
    *.precision :\n
    *    specific precision of destination. If destination is string, it means length of string.\n
    *length flag:\n
    *    The only value is "l". It's only used with type "s". "ls" means UTF-16 string. ��ʱ��֧��\n
    *type:\n
    *    d, i     : signed decimal integer\n
    *    u        : unsigned decimal integer\n
    *    o        : unsigned octal\n
    *    x        : unsigned hexadecimal\n
    *    X        : unsigned hexadecimal in upper mode\n
    *    f        : float \n
    *    p        : address of pointer\n
    *    c        : character\n
    *    s        : string
    *    %        : a character "%"
    */
	virtual ByteArray & format(const char *pszFormat, ...);

	/**
    * Removes white-space from the left and from the right end of the string. 
    *Whitespace includes the ASCII characters '\\t', '\\n', '\\v', '\\f', '\\r', and ' '.
    *@return return a trimmed string.
    */
    virtual ByteArray & trim();

	virtual ByteArray & trimLeft();
	virtual ByteArray & trimRight();

#ifdef SUPPORT_PRINT_LOG
    /**
    * ����������ݵ�����̨������������
    */
    virtual void print(void) const;
#endif

    ByteArray & operator=(const ByteArray &other);
	ByteArray & operator=(const ByteArrayBuffer &other);
    ByteArray & operator=(const char *pszStr);

    ByteArray operator+(const ByteArray &other) const;
    ByteArray operator+(const char *pszStr) const;

    ByteArray & operator+=(const ByteArray &other);
    ByteArray & operator+=(const char *pszStr);

    bool operator==(const ByteArray &other) const;
    bool operator==(const char *pszStr) const;

    bool operator!=(const ByteArray &other) const;
    bool operator!=(const char *pszStr) const;

    bool operator <(const ByteArray &other) const;

    hz_byte operator[](hz_uint32 ulIndex) const;

    friend ByteArray operator+(const char *pszStr, const ByteArray &right);

protected:
	hz_bool _init();

    virtual hz_bool resizeBuffer(hz_uint32 ulLength);

	ByteArray & format_(const char *pszFormat, va_list ap);

	hz_bool replaceInStr_(hz_byte *pszOldStr, hz_uint32 ulOldStrLen,
						hz_uint32 ulFrom, hz_uint32 ulLen, 
						hz_byte *pszReplaceStr, hz_uint32 ulRepStrLen);

    hz_uint32 m_ulDataSize;      //�����ڰ��������ݳ���
    hz_uint32 m_ulAllocSize;     //�����ѷ�����ڴ��С
    hz_byte *m_pbData;          //���ݻ�����
};

/** 
* ��ByteArray����Ҫ�����ǣ�������붨��ʱ�����ȷ���ÿռ䣬���ռ䲻��ʱ�������Զ����·��䡣
* ��Ҫ����Dll����Ϊ����ʱʹ�á���ֹ��dll�з���Ķѿռ䣬��dll���ͷţ����ײ����/MT����ѡ��ʱ������Ϊ��ͬ��
* ��ָ���б��������������ͷ��ڴ�ʱ��ʾ�쳣��
*/
class ByteArrayBuffer
{
public:
	ByteArrayBuffer();
	ByteArrayBuffer(unsigned int length);
	ByteArrayBuffer(const ByteArrayBuffer& other);
	virtual ~ByteArrayBuffer();

	ByteArrayBuffer & operator=(const ByteArrayBuffer &other);
	ByteArrayBuffer & operator=(const ByteArray &other);

	ByteArray toByteArray() const;

	virtual hz_bool append(const hz_byte* pbData, hz_uint32 cbData);
	virtual hz_bool append(const ByteArray &other);

	void clear();

	hz_bool isEmpty() const;
	/**
    * ֱ�ӷ��ʴ洢����������
    *@note ��ע�ⲻҪֱ���޸���������
    */
    virtual const hz_byte *data(void) const;

    /**
    * �ֽ�������ַ��������ݳ��ȣ��˳��Ȳ������ѷ�����ڴ泤�ȣ�ֻ������Ч���ݳ��ȣ�
    */
    virtual hz_uint32 length() const;

	virtual hz_uint32 capacity() const;

	hz_byte operator[](hz_uint32 ulIndex) const;

private:
	hz_uint32 m_ulDataSize;      //�����ڰ��������ݳ���
	hz_uint32 m_ulAllocSize;     //�����ѷ�����ڴ��С
	hz_byte *m_pbData;          //���ݻ�����
};

#endif//__ZF_BYTEARRAY_H__


