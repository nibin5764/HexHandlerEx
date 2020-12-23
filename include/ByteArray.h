/**************************************************************************************************
* Name:        ByteArray.h
* Purpose:     Byte数组类型的封装，在未手动插入0x00字符的情况下，可以直接当作ASCII字符串使用
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

class ByteArrayBuffer;
class ByteArray 
{
public:
    ByteArray(void);
    ByteArray(const ByteArray &other);
    ByteArray(const unsigned char *pbData, unsigned int cbData);
    ByteArray(const char *pszStr);
    ByteArray(unsigned char ch, unsigned int ulNumber);

    virtual ~ByteArray(void);
    
    /**
    * 往数组末尾追加长度为cbData的数据
    */
    virtual bool append(const unsigned char *pbData, unsigned int cbData);
    
    /**
    * 往字符串末尾追加字符串
    */
    virtual bool append(const char *pszStr);
    virtual bool append(const ByteArray &other);

    /**
    * 往字符串末尾追加一个字符
    */
    virtual bool append(unsigned char ch);

    /**
    * 往指定位置插入一个字符
    */
    virtual bool insert(unsigned int ulIndex, unsigned char ch);

	/**
	* 往指定位置插入一个字符串(不包括\0结束符)
	*/
	bool insert(unsigned int ulIndex, const char *str);
	
	/**
	* 往指定位置插入一个ByteArray
	*/
	virtual bool insert(unsigned int ulIndex, const ByteArray &ba);

    /**
    * 获取指定位置的字节内容
    */
    virtual unsigned char at(unsigned int ulIndex) const;

    /**
    * 设置指定位置的值（该函数慎用，当ByteArray作为字符串使用时，小心不要在字符串中间插入0x00）
    */
    virtual bool setAt(unsigned int ulIndex, unsigned char ch);

    /**
    * 将整数转按指定进制化成字符串
    *@param [in] ulNumber 待转化成字符串的10进制整数数值
    *@param [in] ulBase 采用什么进制进行转化，取值范围为[2,16],即支持从二进制开始，十六进制结束
    */
    virtual ByteArray & fromNumber(int ulNumber, unsigned int ulBase = 10);

    /**
    * 将存放的字符串转化成10进制整数
    */
    virtual int toNumber() const;

	/** 
	* 将double类型转换成字符串
	*/
	virtual ByteArray & fromDouble(double dValue, char ulPrecision = 6);

	/** 
	* 将字符串转换成double
	*/
	virtual double toDouble() const;

    /**
    * 将Byte数组转换成字符串,如存储的是0x30 0x31 0x32 0x33, 转换后存储的就是30313233
    *@return 成功就返回转换后的字符串，失败返回对象长度为0
    */
    virtual ByteArray byteToString() const;

    /**
    * 将字符串转换成Byte数组,如存储的是30313233,转换后就是0x30 0x31 0x32 0x33
    *@return 成功就返回转换后的字符串，失败返回对象长度为0
    *@note 由于字符串转byte时要求2个字节转1个字节，因此若原始数据长度不为2的倍数时，转换失败，
    *      另外如果转换前的字符串中包含不属于0~9,a~z,A~Z范围内的字符时，转换也会失败。
    */
    virtual ByteArray stringToByte() const;

    /**
    * 从ulPosStart开始，查找ch第一次出现的位置
    */
    virtual int indexOf(unsigned char ch, unsigned int ulPosStart = 0) const;

	/**
    * 从ulPosStart开始，查找ba第一次出现的位置
    */
    virtual int indexOf(const ByteArray & ba, unsigned int ulPosStart = 0) const;

    /**
    * 查找ch最后一次出现的位置
    */
    virtual int lastIndexOf(unsigned char ch) const;

	/**
    * 查找ba最后一次出现的位置
    */
    virtual int lastIndexOf(const ByteArray & ba) const;

    /**
    * 将外部分配好的一段堆内存直接交付给CByteArry对象使用。Attach成功后,外部不允许继续使用该段内存，也不需要释放内存
    *@param [in] pbData 指向一段外部分配好的内存
    *@param [in] cbData pbData指向的内存大小
    *@return TRUE表示成功，FALSE表示失败
    */
    virtual bool attach(unsigned char *pbData, unsigned int cbData);

    /**
    * 清除所有数据
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
    virtual bool resize(unsigned int ulSize);

	/** 
	* 将字符串转换成大写
	*/
	virtual ByteArray toUpper(void) const;

	/**
	* 将字符串转换成小写
	*/
	virtual ByteArray toLower(void) const;

    /**
    * 判断是否内容为空
    */
    virtual bool isEmpty(void) const;

    /**
    * 移除从ulPosition开始，长度为ulLength的数据
    *@param [in] ulPosition 起始序列号，被移除的数据包含该起始序列号指向的字符
    *@param [in] ulLength 被移除的数据长度，若该长度超过了剩余的数据长度或者ulLength为-1，均表示移除ulPosition以后的所有数据
    */
    virtual bool remove(unsigned int ulPosition, unsigned int ulLength = -1);

	/**
    * Replaces n characters beginning at index ulPosition with the string after
    *@param [in] ulPosition the start position
    *@param [in] n number of characters will be replaced
    *@param [in] after The substring which will be replaced to it.
    *@return a reference to this string.
    */
	virtual ByteArray & replace( unsigned int ulPosition, unsigned int n, const ByteArray & after);
	
	/**
    * Replaces every occurrence of the string before with the string after 
    *@param [in] before The substring which will be replaced.
    *@param [in] after The substring which will be replaced to it.
    *@return a reference to this string.
    */
	virtual ByteArray & replace( const ByteArray & before, const ByteArray & after);

    /**
    * 获取从ulPosition开始，长度为ulLength的一段数据
    *@param [in] ulPosition 起始序列号，截取的数据包含该起始序列号指向的字符
    *@param [in] ulLength 截取的数据长度，若该长度超过了剩余的数据长度或者ulLength为-1，均表示取回ulPosition以后的所有数据
    *@return 返回截取到的数据
    */
    virtual ByteArray sub(unsigned int ulPosition, unsigned int ulLength = -1) const;

    /**
    * 取最左边的长度为length的子串
    */
    virtual ByteArray left(unsigned int length) const;

    /**
    * 取最右边的长度为length的子串
    */
    virtual ByteArray right(unsigned int length) const;

    /**
    * 判断当前数据串(字符串)是否以prefix开头
    */
    virtual bool startsWith(const ByteArray &prefix) const;

    /**
    * 判断当前数据串(字符串)是否以suffix结尾
    */
    virtual bool endsWith(const ByteArray &suffix) const;

    /**
    * 将当前数据串(字符串)反转
    */
    virtual ByteArray &reverse();

	virtual unsigned int capacity() const;

	/** 
	* 统计字符ch在字节数组中出现的次数
	*/
	virtual unsigned int statistics(char ch) const;

	/** 
	* 统计字符ch在字节数组中出现的次数,建议使用count()而不是statistics()
	*/
	virtual unsigned int count(char ch) const;

	/** 
	* 统计数组ba在字节数组中出现的次数
	*/
	virtual unsigned int count(const ByteArray &ba) const;

    /**
    * 直接访问存储的数据内容
    *@note 请注意不要直接修改数据内容
    */
    virtual const unsigned char *data(void) const;

    /**
    * 字节数组或字符串的数据长度（此长度不代表已分配的内存长度，只代表有效数据长度）
    */
    virtual unsigned int length() const;

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
    *    The only value is "l". It's only used with type "s". "ls" means UTF-16 string. 暂时不支持\n
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
    * 输出数组内容到控制台，仅用作调试
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

    unsigned char operator[](unsigned int ulIndex) const;

    friend ByteArray operator+(const char *pszStr, const ByteArray &right);

protected:
	bool _init();

    virtual bool resizeBuffer(unsigned int ulLength);

	ByteArray & format_(const char *pszFormat, va_list ap);

	bool replaceInStr_(unsigned char *pszOldStr, unsigned int ulOldStrLen,
						unsigned int ulFrom, unsigned int ulLen, 
						unsigned char *pszReplaceStr, unsigned int ulRepStrLen);

    unsigned int m_ulDataSize;      //数组内包含的数据长度
    unsigned int m_ulAllocSize;     //数组已分配的内存大小
    unsigned char *m_pbData;          //内容缓冲区
};

/** 
* 与ByteArray的主要区别是，该类必须定义时，事先分配好空间，当空间不足时，不会自动重新分配。
* 主要用于Dll中作为出参时使用。防止待dll中分配的堆空间，在dll外释放（当底层采用/MT编译选项时），因为不同的
* 堆指针列表，导致析构函数释放内存时提示异常。
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

	virtual bool append(const unsigned char* pbData, unsigned int cbData);
	virtual bool append(const ByteArray &other);

	void clear();

	bool isEmpty() const;
	/**
    * 直接访问存储的数据内容
    *@note 请注意不要直接修改数据内容
    */
    virtual const unsigned char *data(void) const;

    /**
    * 字节数组或字符串的数据长度（此长度不代表已分配的内存长度，只代表有效数据长度）
    */
    virtual unsigned int length() const;

	virtual unsigned int capacity() const;

	unsigned char operator[](unsigned int ulIndex) const;

private:
	unsigned int m_ulDataSize;      //数组内包含的数据长度
	unsigned int m_ulAllocSize;     //数组已分配的内存大小
	unsigned char *m_pbData;          //内容缓冲区
};

#endif//__ZF_BYTEARRAY_H__


