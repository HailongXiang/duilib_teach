#include "stdafx.h"
#include "QRCWnd.h"

QRCWnd::QRCWnd()
{
}

void QRCWnd::Init()
{
	m_pQRCImage = static_cast<CButtonUI*>(m_pq.FindControl(_T("QRCimage")));
}

void QRCWnd::CreatWnd(QRCWnd* pQRC)
{
	pQRC->Create(NULL, _T("QRCWnd"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 256, 256);
	if (pQRC == NULL)
		return;
	::ShowWindow(*pQRC, SW_SHOW);
}

LRESULT QRCWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	CDialogBuilder builder;
	CDuiString strResourcePath;
	strResourcePath = m_pq.GetInstancePath();
	strResourcePath += GetSkinFolder().GetData();
	m_pq.SetResourcePath(strResourcePath.GetData());

	m_pq.Init(m_hWnd);
	CControlUI* pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, NULL, &m_pq);
	ASSERT(pRoot && "Failed to parse XML");
	m_pq.AttachDialog(pRoot);
	m_pq.AddNotifier(this);

	Init();

	m_pQRCImage->SetBkImage("datedu.png");
	POINT pt = MyGetCursorPos();
	SetWindowPos(m_hWnd, NULL, pt.x, pt.y, 256, 256, SWP_SHOWWINDOW);
	return 0;
}

POINT QRCWnd::MyGetCursorPos()
{
	POINT p;
	GetCursorPos(&p);
	return p;
}

BOOL QRCWnd::CursorPos()
{
	POINT pt = MyGetCursorPos();
	ScreenToClient(*this, &pt);
	/*RECT rcClient;
	GetClientRect(*this, &rcClient);*/
	//if (pt.x > rcClient.right || pt.x < rcClient.left || pt.y < rcClient.top || pt.y >rcClient.bottom)
	if (pt.x < 0 || pt.y < 0)
		return false;
	else
		return true;
}

LRESULT QRCWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);
	RECT rcCaption = m_pq.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_pq.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}
	return HTCLIENT;
}

void QRCWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pQRCImage)
		{
			if (m_hWnd != NULL)
				//HWND wnd = FindWindow(NULL, "QRCWnd");
				//ShowWindow(m_hWnd, SW_HIDE);
				//::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
				SendMessage(WM_CLOSE);
				//DestroyWindow(m_hWnd);	
				//SendMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
				//PostQuitMessage(0);
				//delete this;
		}
	}
}

LRESULT QRCWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pq.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}


QRCWnd::~QRCWnd()
{
	
}
