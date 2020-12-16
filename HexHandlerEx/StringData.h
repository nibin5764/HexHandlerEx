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

	bool IsValid();	//��ǰ�����Ƿ����
	const char* data();	//��������
	enumStringType type();	//������������
	unsigned int length();	//�������ݳ��ȣ���strlen(m_szData)ֵ��ͬ

protected:
	bool IsValidData();	//�ж��ַ����������Ƿ����
	bool IsValidData(enumStringType stType, char* szText);	//�ж��ַ����������Ƿ����
	void Clear();	//�������


	enumStringType m_type;
	char* m_szData;			//����
	unsigned int m_uiDataLen;			//���ݳ���
};


