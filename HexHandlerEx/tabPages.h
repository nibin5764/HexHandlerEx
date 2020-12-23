#pragma once
#include "..\DuiLib\UIlib.h"
using namespace DuiLib;

//×Ö·û´®Ò³Ãæ
class CTabString :public CContainerUI {
public:
	CTabString()
	{
		CDialogBuilder builder;
		CContainerUI* pTabString = static_cast<CContainerUI*>(builder.Create(_T("StringFuncPage.xml"), 0));
		if (pTabString) {
			this->Add(pTabString);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
private:

};

//HASHÒ³Ãæ
class CTabHash :public CContainerUI {
public:
	CTabHash()
	{
		CDialogBuilder builder;
		CContainerUI* pTabHash = static_cast<CContainerUI*>(builder.Create(_T("HashFuncPage.xml"), 0));
		if (pTabHash) {
			this->Add(pTabHash);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
private:

};