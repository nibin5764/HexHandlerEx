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
	int PushCurrent(enumStringType stType, const char* szText);	//在当前位置后加入字符串
	const char* GetNext();				//返回下一个字符串。
	const char* SwitchNext();			//返回下一个字符串，并切换当前位置
	const char* GetLast();				//返回上一个字符串
	const char* SwitchLast();			//返回上一个，并切换当前位置
	const char* GetCurrent();			//返回当前字符串
	enumStringType GetcurrentType();	//返回当前类型



	//数据类型转换
	const char* toText();	//转普通字符串
	const char* toHex();	//转十六进制字符串
	const char* toBase64();	//转BASE64字符串

	//String Function
	const char* toUper(const char* sztext);	//转为大写
	const char* toLower(const char* sztext);	//转为小写

	//
	const char* toTrimAll(const char* sztext);	//去除全部回车空格
	const char* toRemove0x(const char* sztext);	//去除,0x
	const char* toNormalBase64(const char* sztext);	//URL Base64转普通Base64

	//Hex Function
	const char* toReverse(const char* sztext);	//大小端翻转
	const char* toAddSpace(const char* sztext);	//添加空格
	const char* toAdd0x(const char* sztext);		//添加 ,0x

	//Base64 Function
	const char* toURLBase64(const char* sztext);	//转为URL Base64


private:
	StringNode*	pCurNode;
	int m_curNodeCount;			//当前保留的节点个数
	StringNode* m_headNode;				//头结点，当节点数超过限制时，从头节点开始删除节点，直至不超过节点个数限制
	int judgeData(const char* input,enumStringType type);
};

