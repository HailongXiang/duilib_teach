#include "stdafx.h"
#include "QRCWnd.h"

QRCWnd::QRCWnd()
{
}

void QRCWnd::Init()
{
	m_pQRCImage = static_cast<CButtonUI*>(m_pq.FindControl(_T("QRCimage")));
}

void QRCWnd::CreatWnd(QRCWnd* pQRC, CUserInfo* userinfo)
{
	QRCinfo = new CUserInfo();
	QRCinfo = userinfo;
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

	string qrc_filename = QRCinfo->getQRCFileName();
	m_pQRCImage->SetBkImage(qrc_filename.c_str());

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

void QRCWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pQRCImage)
		{
			if (m_hWnd != NULL)
				SetWindowPos(m_hWnd, NULL,0, 0, 0, 0, SWP_HIDEWINDOW);
				//HWND wnd = FindWindow(NULL, "QRCWnd");
				//SendMessage(WM_CLOSE);
				//Close();
				//DestroyWindow(m_hWnd);
				//SendMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
				//::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
				//PostQuitMessage(0);
				//delete this;
			return;
		}
	}
}

LRESULT QRCWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pq.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

