#pragma once
#include"..\DuiLib\UIlib.h"
using namespace DuiLib;
DWORD DuiMessageBox(HWND hParent, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);

const static int MSGBOX_MAX_TITLE_LEN = 20;             //�������󳤶�
const static int MSGBOX_MAX_TEXT_LEN = 256;             //���ĵ���󳤶�

const static int MSGBOX_MAX_DRAW_LEN = 282;             //�����ı�ʱ�������Ƴ��ȣ��������ȵĻ���

class CDuiMessageBox : public WindowImplBase
{
public:
    CDuiMessageBox();
    void Init(HWND hParent, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
    
    
    virtual LPCTSTR    GetWindowClassName() const { return _T("msgBox"); }
    virtual CDuiString GetSkinFile() { return _T("msgBox.xml"); }
    virtual CDuiString GetSkinFolder() { return _T("..\\skin\\"); }
    virtual void InitWindow();
    virtual void Notify(TNotifyUI& msg);
    virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    int GetReturnVal();
private:
    HWND m_hWnd;
    HWND m_hParent;
    LPCTSTR m_lpText;
    LPCTSTR m_lpCaption;
    UINT m_uType;
    int m_rtnVal;
};