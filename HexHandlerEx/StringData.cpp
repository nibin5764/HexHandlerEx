#include"StringData.h"
#include<string>
#include<new>
#include<Windows.h>
#include"Utility.h"

//StringData::StringData()
//{
//	m_type = enumStringType::TYPE_UNKNOW;
//	m_szData = nullptr;
//	m_uiDataLen = 0;
//}
StringData::StringData(enumStringType _type, const char* szData) {
	m_type = _type;
	int len = strlen(szData);
	m_szData = new(std::nothrow) char[len + 1];
	memset(m_szData, 0, len + 1);
	strcpy_s(m_szData,len+1, szData);
	m_uiDataLen = m_szData == nullptr ? 0 : len;
}

StringData::StringData(enumStringType _type, const wchar_t* wData) {

	int len = WideCharToMultiByte(CP_ACP, 0, wData, wcslen(wData), NULL, 0, NULL, NULL);
	m_szData = new(std::nothrow) char[len + 1];
	if (m_szData == nullptr) {
		m_type = enumStringType::TYPE_UNKNOW;
		m_uiDataLen = 0;
		return;
	}
	WideCharToMultiByte(CP_ACP, 0, wData, wcslen(wData), m_szData, len, NULL, NULL);
	m_szData[len] = '\0';

	m_type = _type;
	m_uiDataLen = len;

	if (!IsValidData()) {
		Clear();
	}
}

StringData::~StringData()
{
	if (m_szData) {
		delete[] m_szData;
		m_szData = nullptr;
	}
	m_type = enumStringType::TYPE_UNKNOW;
	m_uiDataLen = 0;
}

//��ǰ�����Ƿ����
bool StringData::IsValid() {
	if (m_type == enumStringType::TYPE_UNKNOW || m_szData == nullptr || m_uiDataLen == 0) {
		return false;
	}
	return true;
}

//�ж��ַ����������Ƿ����
bool StringData::IsValidData(enumStringType stType, char* szText) {
	if (stType == enumStringType::TYPE_STR && szText != nullptr) {
		return true;
	}
	if (stType == enumStringType::TYPE_HEX && isHexString(szText)) {
		return true;
	}
	if (stType == enumStringType::TYPE_BASE64 && isBase64String(szText)) {
		return true;
	}
	return false;
}
//�ж��ַ����������Ƿ����
bool StringData::IsValidData() {
	if (m_type == enumStringType::TYPE_STR && m_szData != nullptr) {
		return true;
	}
	if (m_type == enumStringType::TYPE_HEX && isHexString(m_szData)) {
		return true;
	}
	if (m_type == enumStringType::TYPE_BASE64 && isBase64String(m_szData)) {
		return true;
	}
	return false;
}

//�������
void StringData::Clear() {
	m_type = enumStringType::TYPE_UNKNOW;
	if (m_szData) {
		delete[] m_szData;
	}
	m_uiDataLen = 0;
}
//��������
const char* StringData::data() {
	return m_szData;
}

//������������
enumStringType StringData::type() {
	return m_type;
}

//�������ݳ��ȣ���strlen(m_szData)ֵ��ͬ
unsigned int StringData::length() {
	return m_uiDataLen;
}