#include"StringList.h"

StringList::StringList()
{
	pCurNode = nullptr;
	m_curNodeCount = 0;
	m_headNode = nullptr;
}

StringList::StringList(initializer_list<StringNode*> initlist)
{
	pCurNode = nullptr;
	m_curNodeCount = 0;
	m_headNode = nullptr;
	for (auto pNode : initlist) {
		PushCurrent(pNode);
	}
}

StringList::~StringList()
{
	if (!pCurNode) {
		return;
	}
	StringNode* psnNext = pCurNode->pNext;
	StringNode* psnLast = pCurNode->pLast;

	while (psnNext) {
		pCurNode->pNext = psnNext->pNext;
		delete psnNext;
		psnNext = pCurNode->pNext;
	}
	while (psnLast) {
		pCurNode->pLast = psnLast->pLast;
		delete psnLast;
		psnLast = pCurNode->pLast;
	}
	delete pCurNode;
	pCurNode = nullptr;
}

int StringList::PushCurrent(StringNode* pNode) {
	if (pNode == nullptr || !pNode->IsValid()) {
		return -1;
	}

	//列表为空
	if (!pCurNode) {
		pCurNode = pNode;
		m_curNodeCount = 1;
		m_headNode = pNode;
		return 0;
	}

	//清空Current后面的所有节点，并把pNode插入到pCurNode之后，切换pNode为Current
	StringNode* psnNext = pCurNode->pNext;
	while (psnNext) {
		pCurNode->pNext = psnNext->pNext;
		delete psnNext;
		psnNext = pCurNode->pNext;
		-- m_curNodeCount;
	}

	pCurNode->pNext = pNode;
	pNode->pLast = pCurNode;
	pCurNode = pNode;
	++m_curNodeCount;

	if (m_curNodeCount > SL_MAX_NODE_NUM && m_headNode != nullptr) {
		m_headNode = m_headNode->pNext;
		delete m_headNode->pLast;
		m_headNode->pLast = nullptr;
		-- m_curNodeCount;
	}



	return 0;
}
int StringList::PushCurrent(enumStringType stType, const char* szText) {
	StringNode* pNode = new StringNode(stType, szText);
	return PushCurrent(pNode);
}

//返回下一个字符串。
const char* StringList::GetNext() {
	if (pCurNode && pCurNode->pNext) {
		return pCurNode->pNext->data();
	}
	return NULL;
}

//返回下一个字符串，并切换当前位置
const char* StringList::SwitchNext() {
	if (pCurNode && pCurNode->pNext) {
		pCurNode = pCurNode->pNext;
		return pCurNode->data();
	}
	return NULL;
}

//返回上一个字符串
const char* StringList::GetLast() {
	if (pCurNode && pCurNode->pLast) {
		return pCurNode->pLast->data();
	}
	return NULL;
}

//返回上一个，并切换当前位置
const char* StringList::SwitchLast() {
	if (pCurNode && pCurNode->pLast) {
		pCurNode = pCurNode->pLast;
		return pCurNode->data();
	}
	return NULL;
}

//返回当前字符串
const char* StringList::GetCurrent() {
	if (pCurNode ) {
		return pCurNode->data();
	}
	return NULL;
}

//返回当前类型
enumStringType StringList::GetcurrentType() {
	return pCurNode->type();
}

const char* StringList::toText() {
	if (!pCurNode) {
		return nullptr;
	}
	if (pCurNode->type() == enumStringType::TYPE_STR) {
		return pCurNode->data();
	}
	if (pCurNode->type() == enumStringType::TYPE_HEX) {
		int hexLen = pCurNode->length() / 2 + 1;
		char* pText = new char[hexLen];
		memset(pText, 0, hexLen);
		unsigned int outLen = hexLen;
		HexStr2Byte(pCurNode->data(), (unsigned char*)pText, &outLen);
		if (PushCurrent(enumStringType::TYPE_STR, pText) == 0) {
			delete[] pText;
			return pCurNode->data();
		}
		delete[] pText;
		return nullptr;
	}
	if (pCurNode->type() == enumStringType::TYPE_BASE64) {
		unsigned char* ucDecode = new unsigned char[pCurNode->length()];
		memset(ucDecode, 0, pCurNode->length());
		int nlen = base64_decode(pCurNode->data(), pCurNode->length(), ucDecode);
		if (PushCurrent(enumStringType::TYPE_STR, (char*)ucDecode) == 0) {
			delete[] ucDecode;
			return pCurNode->data();
		}
		delete[] ucDecode;
		return nullptr;
	}
	return nullptr;
}
const char* StringList::toHex() {
	if (!pCurNode) {
		return nullptr;
	}
	if (pCurNode->type() == enumStringType::TYPE_STR) {
		char* pHex = new char[pCurNode->length() * 2 + 1];
		memset(pHex, 0, pCurNode->length() * 2 + 1);
		Byte2HexStr((unsigned char*)pCurNode->data(), pCurNode->length(), pHex);
		if (PushCurrent(enumStringType::TYPE_HEX, pHex) == 0) {
			delete[] pHex;
			return pCurNode->data();
		}
		delete[] pHex;
		return nullptr;
	}
	if (pCurNode->type() == enumStringType::TYPE_HEX) {
		return pCurNode->data();
	}
	if (pCurNode->type() == enumStringType::TYPE_BASE64) {
		unsigned char* ucDecode = new unsigned char[pCurNode->length()];
		memset(ucDecode, 0, pCurNode->length());
		int nlen = base64_decode(pCurNode->data(), pCurNode->length(), ucDecode);
		
		char* pHex = new char[nlen * 2 + 1];
		memset(pHex, 0, nlen * 2 + 1);
		Byte2HexStr(ucDecode, nlen, pHex);
		delete[] ucDecode;
		ucDecode = nullptr;
		if (PushCurrent(enumStringType::TYPE_HEX, pHex) == 0) {
			delete[] pHex;
			return pCurNode->data();
		}
		delete[] pHex;
		return nullptr;
	}
	return nullptr;
}
const char* StringList::toBase64() {
	if (!pCurNode ) {
		return nullptr;
	}
	if (pCurNode->type() == enumStringType::TYPE_STR) {
		char* pEncode = new char[pCurNode->length() * 2 + 2];
		memset(pEncode, 0, pCurNode->length() * 2 + 2);
		
		int nlen = base64_encode((unsigned char*)pCurNode->data(), pCurNode->length(), pEncode);
		if (PushCurrent(enumStringType::TYPE_BASE64, pEncode) == 0) {
			delete[] pEncode;
			return pCurNode->data();
		}
		delete[] pEncode;
		return nullptr;
	}
	if (pCurNode->type() == enumStringType::TYPE_HEX) {
		int hexLen = pCurNode->length() / 2 + 1;
		unsigned char* pHex = new unsigned char[hexLen];
		memset(pHex, 0, hexLen);
		unsigned int outLen = hexLen;
		HexStr2Byte(pCurNode->data(), pHex, &outLen);

		char* pEncode = new char[outLen * 2 + 2];
		memset(pEncode, 0, outLen * 2 + 2);

		int nlen = base64_encode((unsigned char*)pHex, outLen, pEncode);
		delete[] pHex;
		pHex = nullptr;
		if (PushCurrent(enumStringType::TYPE_BASE64, pEncode) == 0) {
			delete[] pEncode;
			return pCurNode->data();
		}
		delete[] pEncode;
		return nullptr;
	}
	if (pCurNode->type() == enumStringType::TYPE_BASE64) {
		return pCurNode->data();
	}
	return nullptr;
}

#define	ASSERT_P(pointer) \
		if(pointer == nullptr){\
			return nullptr;\
		}

#define ASSERT_CURRENT_POINTER  ASSERT_P(pCurNode)

#define ASSERT_TYPE(type2) \
		if(pCurNode->type() != type2){\
			return nullptr;\
		}

#define ASSERT_TYPE_STR	;    //ASSERT_TYPE(enumStringType::TYPE_STR)
#define ASSERT_TYPE_HEX	;    //ASSERT_TYPE(enumStringType::TYPE_HEX)
#define ASSERT_TYPE_BASE64	;	//ASSERT_TYPE(enumStringType::TYPE_BASE64)



//判断输入数据 
//	返回-1 输入数据有误，返回-1
int StringList::judgeData(const char* input ,enumStringType type) {
	if ( !input) {
		return -1;
	}
	if (pCurNode== nullptr || strcmp(pCurNode->data(), input) != 0) {
		int rv = PushCurrent(type, input);
		if (rv != 0) {
			return -1;
		}
	}
	return 0;
}
//转为大写
const char* StringList::toUper(const char* sztext) {
	ASSERT_TYPE_STR
	int rv = 0;
	if (judgeData(sztext,enumStringType::TYPE_STR)) {
		return nullptr;
	}

	char* pUper = new char[pCurNode->length() + 1];
	pUper[pCurNode->length()] = 0;

	const char* p = pCurNode->data();
	for (int i = 0; p[i] != '\0'; ++i) {
		if (p[i] >= 'a' && p[i] <= 'z') {
			pUper[i] = p[i] - 32;
		}
		else {
			pUper[i] = p[i];
		}
	}
	rv = PushCurrent(enumStringType::TYPE_STR, pUper);
	delete[] pUper;
	pUper = nullptr;

	return rv == 0 ? pCurNode->data() : nullptr;
}

//转为小写
const char* StringList::toLower(const char* sztext) {
	ASSERT_TYPE_STR
	if (judgeData(sztext, enumStringType::TYPE_STR)) {
		return nullptr;
	}

	char* pLower = new char[pCurNode->length() + 1];
	pLower[pCurNode->length()] = 0;

	const char* p = pCurNode->data();
	for (int i = 0; p[i] != '\0'; ++i) {
		if (p[i] >= 'A' && p[i] <= 'Z') {
			pLower[i] = p[i] + 32;
		}
		else {
			pLower[i] = p[i];
		}
	}
	int rv = PushCurrent(enumStringType::TYPE_STR, pLower);
	delete[] pLower;
	pLower = nullptr;

	return rv == 0 ? pCurNode->data():nullptr;
}

//去除全部回车空格
const char* StringList::toTrimAll(const char* sztext) {
	ASSERT_TYPE_STR
	if (judgeData(sztext, enumStringType::TYPE_STR)) {
		return nullptr;
	}

	char* pNewChars = new char[pCurNode->length() + 1];

	const char* p = pCurNode->data();
	int inew = 0;
	for (int i = 0; p[i] != '\0'; ++i) {
		if (p[i] == '\n' || p[i] == '\r' || p[i] == ' ') {
			continue;
		}
		else {
			pNewChars[inew++] = p[i];
		}
	}
	pNewChars[inew] = '\0';

	int rv = PushCurrent(enumStringType::TYPE_STR, pNewChars);
	delete[] pNewChars;
	pNewChars = nullptr;

	return rv == 0 ? pCurNode->data() : nullptr;
}

//去除,0x
const char* StringList::toRemove0x(const char* sztext){
	ASSERT_TYPE_STR
		if (judgeData(sztext, enumStringType::TYPE_STR)) {
			return nullptr;
		}

	char* pNewChars = new char[pCurNode->length() + 1];

	const char* p = pCurNode->data();
	int inew = 0;

	int length = pCurNode->length();
	for (int i = 0; i < length ; ++i) {
		if ((i+2)< length && p[i] == ',' && p[i+1] == '0' && p[i+2] == 'x') {
			i += 2;
		}
		else if ((i+1) < length && p[i] == '0' && p[i + 1] == 'x') {
			i += 1;
		}
		else {
			pNewChars[inew++] = p[i];
		}
	}
	pNewChars[inew] = '\0';

	int rv = PushCurrent(enumStringType::TYPE_STR, pNewChars);
	delete[] pNewChars;
	pNewChars = nullptr;

	return rv == 0 ? pCurNode->data() : nullptr;
}
//URL Base64转普通Base64
const char* StringList::toNormalBase64(const char* sztext) {
	ASSERT_TYPE_STR
	if (judgeData(sztext, enumStringType::TYPE_STR)) {
		return nullptr;
	}

	char* pNewChars = new char[pCurNode->length() + 1];
	pNewChars[pCurNode->length()] = 0;

	const char* p = pCurNode->data();
	int inew = 0;
	for (int i = 0; p[i] != '\0'; ++i) {
		if (p[i] == '-') {
			pNewChars[i] = '+';
		}
		else if(p[i] == '_'){
			pNewChars[i] = '/';
		}
		else {
			pNewChars[i] = p[i];
		}
	}

	int rv = PushCurrent(enumStringType::TYPE_BASE64, pNewChars);
	delete[] pNewChars;
	pNewChars = nullptr;

	return rv == 0 ? pCurNode->data() : nullptr;
}


//大小端翻转
const char* StringList::toReverse(const char* sztext) {
	ASSERT_TYPE_HEX
	if (judgeData(sztext, enumStringType::TYPE_HEX)) {
		return nullptr;
	}

	char* pNewChars = new char[pCurNode->length() + 1];
	pNewChars[pCurNode->length()] = 0;

	const char* p = pCurNode->data();
	int inew = 0;
	
	int textLen = pCurNode->length();
	for (int i = 0; i < textLen / 4 * 2; i += 2) {
		pNewChars[i] = p[textLen - i - 2];		pNewChars[textLen - i - 2] = p[i];
		pNewChars[i + 1] = p[textLen - i - 1];	pNewChars[textLen - i - 1] = p[i + 1];
	}

	int rv = PushCurrent(enumStringType::TYPE_HEX, pNewChars);
	delete[] pNewChars;
	pNewChars = nullptr;

	return rv == 0 ? pCurNode->data() : nullptr;
}

//添加空格
const char* StringList::toAddSpace(const char* sztext) {
	ASSERT_TYPE_HEX
		if (judgeData(sztext, enumStringType::TYPE_HEX)) {
			return nullptr;
		}
	char* pNewChars = new char[pCurNode->length()*3/2 + 4];
	const char* p = pCurNode->data();
	int inew = 0;

	int textLen = pCurNode->length();
	for (int i = 0; i < textLen; ++i) {
		if (i % 2 == 0 && i != 0) {
			pNewChars[inew++] = ' ';
			pNewChars[inew++] = p[i];
		}
		else {
			pNewChars[inew++] = p[i];
		}
	}
	pNewChars[inew] = 0;
	int rv = PushCurrent(enumStringType::TYPE_STR, pNewChars);
	delete[] pNewChars;
	pNewChars = nullptr;

	return rv == 0 ? pCurNode->data() : nullptr;
}

//添加 ,0x
const char* StringList::toAdd0x(const char* sztext) {
	ASSERT_TYPE_HEX
		if (judgeData(sztext, enumStringType::TYPE_HEX)) {
			return nullptr;
		}

	char* pNewChars = new char[pCurNode->length()*5/2 + 4];

	const char* p = pCurNode->data();
	int inew = 0;


	int textLen = pCurNode->length();
	for (int i = 0; i < textLen; ++i) {
		if (i % 2 == 0 ) {
			if (i != 0) {
				pNewChars[inew++] = ',';
			}
			pNewChars[inew++] = '0';
			pNewChars[inew++] = 'x';
			pNewChars[inew++] = p[i];
		}
		else {
			pNewChars[inew++] = p[i];
		}
	}
	pNewChars[inew] = 0;
	int rv = PushCurrent(enumStringType::TYPE_STR, pNewChars);
	delete[] pNewChars;
	pNewChars = nullptr;

	return rv == 0 ? pCurNode->data() : nullptr;
}

//转为URL Base64
const char* StringList::toURLBase64(const char* sztext) {
	ASSERT_TYPE_BASE64
		if (judgeData(sztext, enumStringType::TYPE_BASE64)) {
			return nullptr;
		}

	char* pNewChars = new char[pCurNode->length() + 1];
	pNewChars[pCurNode->length()] = 0;

	const char* p = pCurNode->data();
	int inew = 0;
	for (int i = 0; p[i] != '\0'; ++i) {
		if (p[i] == '+') {
			pNewChars[i] = '-';
		}
		else if (p[i] == '/') {
			pNewChars[i] = '_';
		}
		else {
			pNewChars[i] = p[i];
		}
	}

	int rv = PushCurrent(enumStringType::TYPE_BASE64, pNewChars);
	delete[] pNewChars;
	pNewChars = nullptr;

	return rv == 0 ? pCurNode->data() : nullptr;
}