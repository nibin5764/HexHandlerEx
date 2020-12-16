#include"UIMessageBox.h"



DWORD DuiMessageBox(HWND hParent, LPCTSTR lpText ,LPCTSTR lpCaption, UINT uType) {
    CDuiMessageBox msgb;
    msgb.Init( hParent,lpText,lpCaption,uType);
    msgb.CenterWindow();
    msgb.ShowModal();
    return msgb.GetReturnVal();
}
CDuiMessageBox::CDuiMessageBox() :m_hWnd(NULL), m_hParent(NULL), m_lpText(NULL), m_lpCaption(NULL), m_uType(0) {
    m_rtnVal = 0;
}

int CDuiMessageBox::GetReturnVal() {
    return m_rtnVal;
}
void CDuiMessageBox::Init(HWND hParent, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType) {
    m_hParent = hParent;
    m_lpText = lpText;
    m_lpCaption = lpCaption;
    m_uType = uType;
    m_hWnd = __super::Create(hParent, _T("DuiMsgBox"), WS_POPUP, WS_EX_TOOLWINDOW);
    //int charDrawlen = 0;
    //for (BYTE* p = (BYTE*)lpText; (*p) | *(p + 1); p += 2) {
    //    if (*p) ++charDrawlen;
    //    if (*(p + 1)) ++charDrawlen;
    //}
    //int lines = charDrawlen / 40;

    int lines = 1;
    SIZE size = { 0,0 };
    CTextUI* pText = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textt")));

    if (pText && lpText && _tcslen(lpText) < MSGBOX_MAX_TEXT_LEN) {
        
        //自动换行
        int fIndex = pText->GetFont();
        HDC hdc = GetDC(this->m_hWnd);
        HFONT hFont = m_PaintManager.GetFont(fIndex);
        HFONT holdf = (HFONT)::SelectObject(hdc, hFont);
        TCHAR appendText[320] = { 0 }; int aLen = 0;
        LPCTSTR lastStart = lpText;
        int curLen = 0;
        
        //获取宽度
        for (int i = 0; lastStart[i] != '\0'; ++i) {
            GetTextExtentPoint32(hdc, lastStart, ++curLen, &size);
            if (size.cx > MSGBOX_MAX_DRAW_LEN) {
                appendText[aLen++] = '\n';
                appendText[aLen++] = lastStart[i];
                lastStart += i;
                i = 0;
                curLen = 1;
                ++lines;
            }
            else {
                appendText[aLen++] = lastStart[i];
            }
        }
        appendText[aLen++] = '\0';
        pText->SetText(appendText);

    }

    RECT rcWindow, rcText;
    GetWindowRect(m_hWnd, &rcWindow);
    MoveWindow(m_hWnd, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top + size.cy * lines - 20,true);
    return;
}

#define BTN_BKCOLOR     0xffFFFFFF
void CDuiMessageBox::InitWindow() {
    CTextUI* pTitle = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("title")));
    if (pTitle && m_lpCaption) {
        pTitle->SetText(m_lpCaption);
    }
    CHorizontalLayoutUI * btnArea = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("btnArea")));
    if (!btnArea)
        return;

    if ((m_uType &0x0F) == MB_OK) {
        CButtonUI* pBtn = new CButtonUI;
        pBtn->SetFloat();
        pBtn->SetName(_T("btnok"));
        pBtn->SetText(_T("确定"));
        //pBtn->SetToolTip(_T("我是一个按钮"));
        pBtn->SetBkColor(BTN_BKCOLOR);
        pBtn->SetAttributeList(_T("borderround=\"1,1\" bordercolor=\"#FF444444\" focusbordercolor=\"#FF666666\" bordersize=\"3\""));
        SIZE leftTop = { (300 - 80)/2 ,10 };
        pBtn->SetFixedXY(leftTop);
        pBtn->SetFixedWidth(80);
        pBtn->SetFixedHeight(30);
        btnArea->Add(pBtn);
    }
    else if ((m_uType & 0x0F) == MB_OKCANCEL) {
        CButtonUI* pBtnok = new CButtonUI;
        pBtnok->SetFloat();
        pBtnok->SetName(_T("btnok"));
        pBtnok->SetText(_T("确定"));
        pBtnok->SetBkColor(BTN_BKCOLOR);
        SIZE leftTop = { 40 ,10 };
        pBtnok->SetFixedXY(leftTop);
        pBtnok->SetFixedWidth(80);
        pBtnok->SetFixedHeight(30);
        btnArea->Add(pBtnok);

        CButtonUI* pBtncancel = new CButtonUI;
        pBtncancel->SetFloat();
        pBtncancel->SetName(_T("btncancel"));
        pBtncancel->SetText(_T("取消"));
        pBtncancel->SetBkColor(BTN_BKCOLOR);
        pBtncancel->SetFixedXY({ 180 ,10 });
        pBtncancel->SetFixedWidth(80);
        pBtncancel->SetFixedHeight(30);
        btnArea->Add(pBtncancel);
    }
    




    

}

void CDuiMessageBox::Notify(TNotifyUI& msg)
{
    CDuiString  strName = msg.pSender->GetName();
    if (msg.sType == _T("click"))
    {
        CDuiString  strName = msg.pSender->GetName();
        if (strName == _T("closebtn")) {
            //Close();
            PostQuitMessage(0);
            return;
        }
        else if (strName == _T("btnok")) {
            m_rtnVal = IDOK;
            Close();
            //PostQuitMessage(0);
            return;
        }
        else if (strName == _T("btncancel")) {
            m_rtnVal = IDCANCEL;
            Close();
            //PostQuitMessage(0);
            return;
        }
    }
    __super::Notify(msg);
}


//把非控件区域都当做非客户区处理，方便用鼠标拖动
LRESULT CDuiMessageBox::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &pt);

    RECT rcClient;
    ::GetClientRect(*this, &rcClient);

    if (!::IsZoomed(*this))
    {
        RECT rcSizeBox = m_PaintManager.GetSizeBox();
        if (pt.y < rcClient.top + rcSizeBox.top)
        {
            if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
            if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
            return HTTOP;
        }
        else if (pt.y > rcClient.bottom - rcSizeBox.bottom)
        {
            if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
            if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
            return HTBOTTOM;
        }

        if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
        if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
    }

    CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
    if (pControl) {
        CDuiString pname = pControl->GetClass();
    }

    //比较过程需要优化
    if (pControl && _tcsicmp(pControl->GetClass(), _T("Button")) == 0)
        return HTCLIENT;
    if (pControl && _tcsicmp(pControl->GetClass(), _T("Option")) == 0)
        return HTCLIENT;
    if (pControl && _tcsicmp(pControl->GetClass(), _T("RichEdit")) == 0)
        return HTCLIENT;

    return HTCAPTION;
}