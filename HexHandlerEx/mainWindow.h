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
    StringList strList;             //�ַ�������
    CRichEditUI* m_pEdit;         //�༭��
    CTabLayoutUI* m_pTab;      //tabҳ
    CLabelUI* m_pLtxtLen;      //��ʾ�ı����ȵ�Label

    vector<COptionUI*>vecFuncs; //����option
    vector<COptionUI*>vecTypes; //��������option
    BOOL m_NoSwitchType;       //TRUE : �����л���������ʱ���ڲ���������ת��

private:
    const static int func_Str;
    const static int func_Bits;
    const static int func_Hash;
    const static int func_Encrypt;

    const static int type_Str;
    const static int type_Hex;
    const static int type_Base64;
};
