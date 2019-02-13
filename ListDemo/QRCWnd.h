#pragma once
#include "InfoList.h"

class QRCWnd:public WindowImplBase
{
public:
	QRCWnd();

public:
	CDuiString GetSkinFolder()
	{
		return _T("skin\\WeChatRes\\main\\");
	}

	CDuiString GetSkinFile()
	{
		return _T("QRCWnd.xml");
	}

	LPCTSTR GetWindowClassName() const
	{
		return _T("QRCWnd");
	};

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	void Notify(TNotifyUI& msg);
	void Init();

	void CreatWnd(QRCWnd* pQRC, CUserInfo* userinfo);
	POINT MyGetCursorPos();
	BOOL CursorPos();
	//void DownloadQRC(string& qrc_url);

	void Destroy()
	{
		//DestroyWindow(m_hWnd);
		SendMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
	}

public:
	string userinfo_QRC;
	
	CUserInfo* QRCinfo;

public:
	CPaintManagerUI m_pq;

public:
	CButtonUI* m_pQRCImage;
};

