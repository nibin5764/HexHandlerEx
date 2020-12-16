#pragma once
#include"StringData.h"
#include<initializer_list>
#include"Utility.h"

using namespace std;

class StringNode :public StringData {
private:
	friend class StringList;
	StringNode* pLast;
	StringNode* pNext;
	StringNode(enumStringType stType,const char* szText) :StringData(stType, szText), pLast(nullptr), pNext(nullptr) {

	}
};

#define SL_MAX_NODE_NUM		100
class StringList
{
public:
	StringList();
	StringList(initializer_list<StringNode*> initlist);
	~StringList();

	int PushCurrent(StringNode* pNode);
	int PushCurrent(enumStringType stType, const char* szText);	//�ڵ�ǰλ�ú�����ַ���
	const char* GetNext();				//������һ���ַ�����
	const char* SwitchNext();			//������һ���ַ��������л���ǰλ��
	const char* GetLast();				//������һ���ַ���
	const char* SwitchLast();			//������һ�������л���ǰλ��
	const char* GetCurrent();			//���ص�ǰ�ַ���
	enumStringType GetcurrentType();	//���ص�ǰ����



	//��������ת��
	const char* toText();	//ת��ͨ�ַ���
	const char* toHex();	//תʮ�������ַ���
	const char* toBase64();	//תBASE64�ַ���

	//String Function
	const char* toUper(const char* sztext);	//תΪ��д
	const char* toLower(const char* sztext);	//תΪСд

	//
	const char* toTrimAll(const char* sztext);	//ȥ��ȫ���س��ո�
	const char* toRemove0x(const char* sztext);	//ȥ��,0x
	const char* toNormalBase64(const char* sztext);	//URL Base64ת��ͨBase64

	//Hex Function
	const char* toReverse(const char* sztext);	//��С�˷�ת
	const char* toAddSpace(const char* sztext);	//��ӿո�
	const char* toAdd0x(const char* sztext);		//��� ,0x

	//Base64 Function
	const char* toURLBase64(const char* sztext);	//תΪURL Base64


private:
	StringNode*	pCurNode;
	int m_curNodeCount;			//��ǰ�����Ľڵ����
	StringNode* m_headNode;				//ͷ��㣬���ڵ�����������ʱ����ͷ�ڵ㿪ʼɾ���ڵ㣬ֱ���������ڵ��������
	int judgeData(const char* input,enumStringType type);
};

