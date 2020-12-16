#pragma once
#include<tchar.h>
class StringList;
enum  enumStringType { TYPE_STR = 0 ,TYPE_HEX , TYPE_BASE64, TYPE_UNKNOW};
class StringData
{
public:
	StringData() = delete;
	StringData(enumStringType _type, const char* szData);
	StringData(enumStringType _type, const wchar_t* wData);
	~StringData();
	friend class StringList;

	bool IsValid();	//当前对象是否可用
	const char* data();	//返回数据
	enumStringType type();	//返回数据类型
	unsigned int length();	//返回数据长度，和strlen(m_szData)值相同

protected:
	bool IsValidData();	//判断字符串和类型是否相符
	bool IsValidData(enumStringType stType, char* szText);	//判断字符串和类型是否相符
	void Clear();	//清空数据


	enumStringType m_type;
	char* m_szData;			//数据
	unsigned int m_uiDataLen;			//数据长度
};


