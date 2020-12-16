#include"mainWindow.h"
#include "UIMessageBox.h"
#include "tabString.h"
const  int CDuiFrameWnd::func_Str = 0;
const  int CDuiFrameWnd::func_Bits = 1;
const  int CDuiFrameWnd::func_Hash = 2;
const  int CDuiFrameWnd::func_Encrypt = 3;

const  int CDuiFrameWnd::type_Str = 0;
const  int CDuiFrameWnd::type_Hex = 1;
const  int CDuiFrameWnd::type_Base64 = 2;

void CDuiFrameWnd::Notify(TNotifyUI& msg)
{
    CDuiString  strName = msg.pSender->GetName();
    if (msg.sType == _T("click"))
    {
        CDuiString text = m_pEdit->GetText();

        CDuiString  strName = msg.pSender->GetName();
        if (strName == _T("btnback")) {
            return;
        }
        else if (strName == _T("closebtn")) {
            //Close();
            PostQuitMessage(0);
            return;
        }
        else if (strName == _T("btnbackward")) {                //回退
            const char* result = strList.SwitchLast();
            if (result) {
                m_pEdit->SetText(result);
                m_NoSwitchType = true;
                vecTypes[strList.GetcurrentType()]->Selected(true);
            }
            return;
        }
        else if (strName == _T("btnforward")) {                 //前进
            const char* result = strList.SwitchNext();
            if (result) {
                m_pEdit->SetText(result);
                m_NoSwitchType = true;
                vecTypes[strList.GetcurrentType()]->Selected(true);
            }
            return;
        }
        else if (strName == _T("btnUper")) {
            const char* result = strList.toUper(text.GetData());
            if (result) {
                m_pEdit->SetText(result);
            }
            return;
        }
        else if (strName == _T("btnLower")) {
            const char* result = strList.toLower(text.GetData());
            if (result) {
                m_pEdit->SetText(result);
            }
            return;
        }
        else if (strName == _T("btnTrimAll")) {
            const char* result = strList.toTrimAll(text.GetData());
            if (result) {
                m_pEdit->SetText(result);
            }
            return;
        }
        else if (strName == _T("btnq0x")) {
            const char* result = strList.toRemove0x(text.GetData());
            if (result) {
                m_pEdit->SetText(result);
            }
            return;
        }
        else if (strName == _T("btnbackward")) {
            const char* result = strList.SwitchLast();
            if (result) {
                m_pEdit->SetText(result);
            }
            return;
        }
        else if (strName == _T("btnReverse")) {
            const char* result = strList.toReverse(text.GetData());
            if (result) {
                m_pEdit->SetText(result);
            }
            return;
        }
        else if (strName == _T("btnAddSpace")) {
            const char* result = strList.toAddSpace(text.GetData());
            if (result) {
                m_pEdit->SetText(result);
                m_NoSwitchType = TRUE;
                vecTypes[type_Str]->Selected(true);
            }
            return;
        }
        else if (strName == _T("btnAdd0x")) {
            const char* result = strList.toAdd0x(text.GetData());
            if (result) {
                m_pEdit->SetText(result);
                m_NoSwitchType = TRUE;
                vecTypes[type_Str]->Selected(true);
            }
            return;
        }

    }
    else if (msg.sType == _T("selectchanged")) {
        CDuiString text = m_pEdit->GetText();
        CDuiString  strName = msg.pSender->GetName();
        if (strName == _T("btnStr")) {
            DuiMessageBox(this->m_hWnd, _T("str"), _T("41231231"), MB_OK);
        }
        //数据类型
        else if (strName == _T("opTypeStr")) {
            if (m_NoSwitchType) {
                m_NoSwitchType = FALSE;
                return;
            }
            if (text.GetLength() == 0) {
                m_lastType = enumStringType::TYPE_STR;
                return;
            }
            if (strList.GetCurrent() == nullptr || text != strList.GetCurrent()) {
                strList.PushCurrent(m_lastType, text.GetData());
            }
            const char* ptext = strList.toText();
            if (ptext) {
                m_pEdit->SetText(ptext);
            }
            m_lastType = enumStringType::TYPE_STR;
            return;
        }
        else if (strName == _T("opTypeHex")) {
            if (m_NoSwitchType) {
                m_NoSwitchType = FALSE;
                return;
            }
            if (text.GetLength() == 0) {
                m_lastType = enumStringType::TYPE_HEX;
                return;
            }
            if (strList.GetCurrent()== nullptr ||text != strList.GetCurrent()) {
                strList.PushCurrent(m_lastType, text.GetData());
            }
            const char* ptext = strList.toHex();
            if (ptext) {
                m_pEdit->SetText(ptext);
            }
            m_lastType = enumStringType::TYPE_HEX;
            return;
        }
        else if (strName == _T("opTypeBase64")) {
            if (m_NoSwitchType) {
                m_NoSwitchType = FALSE;
                return;
            }
            if (text.GetLength() == 0) {
                m_lastType = enumStringType::TYPE_BASE64;
                return;
            }
            if (strList.GetCurrent() == nullptr || text != strList.GetCurrent()) {
                strList.PushCurrent(m_lastType, text.GetData());
            }
            const char* ptext = strList.toBase64();
            if (ptext) {
                m_pEdit->SetText(ptext);
            }
            m_lastType = enumStringType::TYPE_BASE64;
            return;
        }
    }
    else if (msg.sType == _T("textchanged")) {
        CDuiString strText = m_pEdit->GetText();
        const char* cszText = strText.GetData();
        int len = m_pEdit->GetTextLength();
        long nStartChar, nEndChar;
        m_pEdit->GetSel(nStartChar,nEndChar);       //保存光标位置
        
        //屏蔽非ASCII 字符
        TCHAR* szOnlyASCII = new TCHAR[len + 1];
        memset(szOnlyASCII, 0, (len + 1) * sizeof(TCHAR));
        for (int i = 0, j = 0; i < len; ++i) {
            if (cszText[i] > 128 || cszText[i] < 0) {
                continue;
            }
            szOnlyASCII[j++] = cszText[i];
        }
        m_pEdit->SetText(szOnlyASCII);
        len = m_pEdit->GetTextLength();
        delete[] szOnlyASCII;
        szOnlyASCII = nullptr;

        m_pEdit->SetSel(nStartChar, nEndChar);  //设置光标

        //设置显示文本长度
        TCHAR szLenTips[256] = { 0 };
        _stprintf_s(szLenTips, _T("<f 5>文本长度:</f><n><c #FF0000><b><f 5>%7d</f></b></c>"), len);
        m_pLtxtLen->SetText(szLenTips);

        m_pEdit->EndDown();//滚动条设置到最下
    }
    __super::Notify(msg);
}

LRESULT CDuiFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    if (uMsg == WM_KEYDOWN)
    {
        switch (wParam)
        {
        case VK_RETURN:
        case VK_ESCAPE:
            return FALSE;
        default:
            break;
        }
    }
    else if (uMsg == WM_ACTIVATE) {
        DuiMessageBox(NULL, _T("min"), NULL, MB_OK);
    }
    return __super::MessageHandler(uMsg, wParam, lParam, bHandled);
}

//把非控件区域都当做非客户区处理，方便用鼠标拖动
LRESULT CDuiFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
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

    if (pControl && _tcsicmp(pControl->GetClass(), _T("Button")) == 0)
        return HTCLIENT;
    if (pControl && _tcsicmp(pControl->GetClass(), _T("Option")) == 0)
        return HTCLIENT;
    if (pControl && _tcsicmp(pControl->GetClass(), _T("RichEdit")) == 0)
        return HTCLIENT;
    if (pControl && _tcsicmp(pControl->GetClass(), _T("ScrollBar")) == 0)
        return HTCLIENT;
    return HTCAPTION;
}

void CDuiFrameWnd::InitWindow() {
    m_NoSwitchType = FALSE;

    SetForegroundWindow(this->m_hWnd);

    m_pEdit = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("reText")));
    m_pEdit->SetFont(_T("微软雅黑"), 18, false, false, false);
    m_pEdit->SetInset({ 5,3,5,3 });

    m_pLtxtLen = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("txtEditLen")));

    m_pTab = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("TabPages")));



    vecFuncs = vector<COptionUI*>(4,nullptr);    //将来扩展需要增加
    vecTypes = vector<COptionUI*>(3, nullptr);

    COptionUI* pOpFuncStr = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("opFuncStr")));
    vecFuncs[func_Str] = pOpFuncStr;
    COptionUI* pOpFuncBits = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("opFunBit")));
    vecFuncs[func_Bits] = pOpFuncBits;
    COptionUI* pOpFuncHash = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("opFunHash")));
    vecFuncs[func_Hash] = pOpFuncHash;
    COptionUI* pOpFuncEncrypt = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("opFunEncrypt")));
    vecFuncs[func_Encrypt] = pOpFuncEncrypt;


    COptionUI* pOpTypeStr = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("opTypeStr")));
    vecTypes[type_Str] = pOpTypeStr;
    COptionUI* pOpTypeHex = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("opTypeHex")));
    vecTypes[type_Hex] = pOpTypeHex;
    COptionUI* pOpTypeBase64 = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("opTypeBase64")));
    vecTypes[type_Base64] = pOpTypeBase64;
    
    vecFuncs[func_Str]->Selected(true);
    vecTypes[type_Str]->Selected(true);
    m_lastType = enumStringType::TYPE_STR;
}


void CDuiFrameWnd::ChangeTabPage(int index) {
    
    m_pTab->SelectItem(index);
}

CControlUI* CDuiFrameWnd::CreateControl(LPCTSTR pstrClass) {
    if (_tcscmp(pstrClass, _T("StringFuncPage")) == 0){
        return new CTabString();
    }
    return NULL;
}