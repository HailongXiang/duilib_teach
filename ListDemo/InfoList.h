#pragma once

#include "ListMainForm.h"
#include "QRCWnd.h"
using namespace DuiLib;

class InfoList : public WindowImplBase
{
public:
	InfoList();
	~InfoList();
public:
	
	CDuiString GetSkinFolder()
	{
		return _T("skin\\WeChatRes\\main\\");
	}

	CDuiString GetSkinFile()
	{
		return _T("InfoList.xml");
	}

	LPCTSTR GetWindowClassName() const
	{
		return _T("InfoList");
	};

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::PostQuitMessage(0L);
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (::IsIconic(*this)) bHandled = FALSE;
		return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	*大小改变的回调函数，可以尝试注释，修改代码 看效果
	*/
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void Notify(TNotifyUI& msg);

	//LRESULT OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	void OnTimer(WPARAM wParam, LPARAM lParam); //定时器
	void onTimerTest();
	void Init();
	void ShowUserInfo();
	void CreatWnd(InfoList* pFrame);

	void CreatQRCWnd();
	void SetTopMost();
public:
	CPaintManagerUI m_pl;
	
	CUserInfo* userinfo;
	string user;

public:
	CButtonUI* m_pTopMostBtn;
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;
	CButtonUI* m_pPortraitBtn;

	CRichEditUI* m_pUserInfo;

	CEditUI* m_pUserName;
	CEditUI* m_pPwd;
};

