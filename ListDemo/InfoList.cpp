#include "stdafx.h"
#include "InfoList.h"

#define TIMER_ID_TEST 100
#define TIMER_TIME_TEST 1000

InfoList::InfoList()
{
}

void InfoList::Init()
{
	m_pTopMostBtn = static_cast<CButtonUI*>(m_pl.FindControl(_T("btn_topmost")));
	m_pCloseBtn = static_cast<CButtonUI*>(m_pl.FindControl(_T("btn_close")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_pl.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pl.FindControl(_T("restorebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_pl.FindControl(_T("minbtn")));

	m_pPortraitBtn = static_cast<CButtonUI*>(m_pl.FindControl(_T("portrait")));

	m_pUserInfo = static_cast<CRichEditUI*>(m_pl.FindControl(_T("userinfo")));
}

LRESULT InfoList::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	CDialogBuilder builder;
	CDuiString strResourcePath;
	strResourcePath = m_pl.GetInstancePath();
	strResourcePath += GetSkinFolder().GetData();
	m_pl.SetResourcePath(strResourcePath.GetData());

	m_pl.Init(m_hWnd);
	CControlUI* pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, NULL, &m_pl);

	ASSERT(pRoot && "Failed to parse XML");
	m_pl.AttachDialog(pRoot);
	m_pl.AddNotifier(this);		//注册Notifier

	Init();

	ShowUserInfo();
	SetForegroundWindow(m_hWnd);
	
	return 0;
}


void InfoList::CreatWnd(InfoList* pFrame)
{
	pFrame->Create(NULL, _T("InfoList"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 320);
	if (pFrame == NULL)
		return;
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);
}

void InfoList::ShowUserInfo()
{
	string username = userinfo->getUserName();
	string uid = userinfo->getId();
	string account = userinfo->getAccount();
	string status = userinfo->getStatus();
	string siteurl = userinfo->getSiteurl();
	string categoryName = userinfo->getCategoryName();
	string ledgeName = userinfo->getLedgeName();
	string schoolname = userinfo->getSchoolname();
	string bankname = userinfo->getBankname();

	//CListTextElementUI* pListElement = new CListTextElementUI;
	////pListElement->SetTag(i);
	//if (pListElement != NULL)
	//{
	//	::PostMessage(this->m_hWnd, WM_ADDLISTITEM, 0L, (LPARAM)pListElement);
	//}


	user = "姓名:" + username + "\n账号 : " + account + "\n教学科目 : " + bankname + "\n分类名称 : " + categoryName + "\n教学书目 : " + ledgeName + "\n学校 : " + schoolname;
	m_pUserInfo->SetText(user.c_str());
}

void InfoList::CreatQRCWnd()
{
	QRCWnd* pQRC = new QRCWnd();
	//pQRC->CreatWnd(pQRC);
	if (pQRC == NULL) { Close(); return; }
	pQRC->Create(m_hWnd, _T(""), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
	pQRC->ShowModal();
}

void InfoList::SetTopMost()
{
	if (GetWindowLong(m_hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
	{
		SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		m_pTopMostBtn->SetBkImage("topmost.png");
	}
	else
	{
		SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		m_pTopMostBtn->SetBkImage("topmost_pushed.png");
	}
		
}

void InfoList::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pTopMostBtn)
		{
			SetTopMost();
		}
		else if (msg.pSender == m_pCloseBtn)
		{
			PostQuitMessage(0);
			//DestroyWindow(m_hWnd);
			return;
		}
		else if (msg.pSender == m_pMinBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pMaxBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return;
		}
		else if (msg.pSender == m_pRestoreBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return;
		}
		else if (msg.pSender == m_pPortraitBtn)
		{
			CreatQRCWnd();
		}
		//else if (msg.pSender != m_pPortraitBtn)
		//{
		//	HWND wnd = FindWindow(NULL, "QRCWnd");
		//	//HWND wnd1 = FindWindow(NULL, "InfoList");
		//	DestroyWindow(wnd);
		//}
	}
}


LRESULT  InfoList::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pl.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		RECT rc = { rcWnd.left, rcWnd.top + szRoundCorner.cx, rcWnd.right, rcWnd.bottom };
		HRGN hRgn1 = ::CreateRectRgnIndirect(&rc);
		HRGN hRgn2 = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom - szRoundCorner.cx, szRoundCorner.cx, szRoundCorner.cy);
		::CombineRgn(hRgn1, hRgn1, hRgn2, RGN_OR);
		::SetWindowRgn(*this, hRgn1, TRUE);
		::DeleteObject(hRgn1);
		::DeleteObject(hRgn2);
	}
	bHandled = FALSE;
	return 0;
}

LRESULT InfoList::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if (!::IsZoomed(*this)) {
		RECT rcSizeBox = m_pl.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_pl.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_pl.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT  InfoList::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right;
	lpMMI->ptMaxSize.y = rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT  InfoList::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
	if (wParam == SC_CLOSE) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed) {
		if (!bZoomed) {
			if (m_pMaxBtn) m_pMaxBtn->SetVisible(false);
			if (m_pRestoreBtn) m_pRestoreBtn->SetVisible(true);
		}
		else {
			if (m_pMaxBtn) m_pMaxBtn->SetVisible(true);
			if (m_pRestoreBtn) m_pRestoreBtn->SetVisible(false);
		}
	}
	return lRes;
}


LRESULT InfoList::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pl.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

InfoList::~InfoList()
{
}
