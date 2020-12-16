#pragma once
#include "..\DuiLib\UIlib.h"
using namespace DuiLib;

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
