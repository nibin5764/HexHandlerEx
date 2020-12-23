#pragma once
#include"..\DuiLib\UIlib.h"
#include "StringList.h"
using namespace DuiLib;

class CDuiFrameWnd : public WindowImplBase
{
public:
    virtual LPCTSTR    GetWindowClassName() const { return _T("HexHandlerEx"); }
    virtual CDuiString GetSkinFile() { return _T("mainFrame.xml"); }
    virtual CDuiString GetSkinFolder() { return _T("..\\skin\\"); }

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    virtual void Notify(TNotifyUI& msg);
    virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDropFile(HDROP hDropInfo);
    virtual CControlUI* CreateControl(LPCTSTR pstrClass);
    virtual void InitWindow();
    void ChangeTabPage(int index);

    void OnBtnsStringClicked(const CDuiString&  strName);
    void OnBtnsBitsClicked(const CDuiString& strName);
    void OnBtnsHashClicked(const CDuiString& strName);
    void OnBtnsEncryptClicked(const CDuiString& strName);

    void ChooseFile();
protected:
    enumStringType m_lastType;
    StringList strList;             //字符串链表
    CRichEditUI* m_pEdit;         //编辑框
    CTabLayoutUI* m_pTab;      //tab页
    CLabelUI* m_pLtxtLen;      //显示文本长度的Label

    vector<COptionUI*>vecFuncs; //功能option
    vector<COptionUI*>vecTypes; //数据类型option
    BOOL m_NoSwitchType;       //TRUE : 界面切换数据类型时，内部不做数据转换

private:
    const static int func_Str;
    const static int func_Bits;
    const static int func_Hash;
    const static int func_Encrypt;

    const static int type_Str;
    const static int type_Hex;
    const static int type_Base64;
};
