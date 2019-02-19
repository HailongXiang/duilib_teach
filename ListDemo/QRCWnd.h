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
	void SetWndSize();

private:
	CPaintManagerUI m_pq;

	CButtonUI* m_pQRCImage;
	string userinfo_QRC;
	CUserInfo* m_pQRCinfo;
};

