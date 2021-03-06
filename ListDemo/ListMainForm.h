#pragma once

/*
* Code By Tojen (qq:342269237)
* 界面设计图片资源80%原创，布局完全原创,学习作品，不好请拍砖
*/
#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include <comdef.h>
#include <vector>
#include <sstream>
#include <io.h>
#include <shellapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <map>

#include "MenuWnd.h"
#include "..\DuiLib\UIlib.h"

#include "CUserControler.h"
#include "InfoList.h"

#include<iostream>
#include <string>

#include "kutfconv.h"

using namespace DuiLib;

#define WM_ADDLISTITEM WM_USER + 50


/*
*  线程函数中传入的结构体变量，使用线程为了使界面线程立即返回，防止卡住，你们懂得。
*/
struct Prama
{
	HWND hWnd;
	CListUI* pList;
	CButtonUI* pSearch;
	CDuiString tDomain;
};

struct TestMem {
	int count;
};


class ListMainForm : public CWindowWnd, public INotifyUI, public IListCallbackUI
{
public:
    ListMainForm() {
    };
	CDuiString GetSkinFolder()
	{

		return _T("skin\\WeChatRes\\");
	}

	CDuiString GetSkinFile()
	{
		return _T("Login.xml");
	}

    LPCTSTR GetWindowClassName() const 
    { 
        return _T("ScanMainForm"); 
    };

    UINT GetClassStyle() const
    { 
        return CS_DBLCLKS; 
    };

    void OnFinalMessage(HWND /*hWnd*/) 
    { 
        delete this;
    };

	void Init();

    void OnPrepare(TNotifyUI& msg) 
    {

    }

	static DWORD WINAPI Search(LPVOID lpParameter);

	void Login();
	
	void ChangeImg();

	void ShockWnd();

	void OnLogin();

	CUserInfo* GetLoginUrlData();

	void ClickBack();

	void ClickSetting();

	void ClickQRCioc();

	void SetColorTag();

	void ChangeBk(const int& msg);

	void OnSearch();

	void Setbkc(DWORD color);
 
	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);

	void Notify(TNotifyUI& msg);

	LRESULT OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;
        return 0;
    }
	void					onTimerTest();
	void				  OnTimer(WPARAM wParam, LPARAM lParam); //定时器

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        ::PostQuitMessage(0L);
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        if( ::IsIconic(*this) ) bHandled = FALSE;
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

	/***
	* 处理来着windows系统的各种消息，WM= windows  message
	*/
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    CPaintManagerUI m_pm;


public:
	CUserControler m_userctl;
	
	

private:
    CButtonUI* m_pCloseBtn;  //此处成员变量用m_ 开头，请务必准守，不对外暴露的成员一律用private修饰
    CButtonUI* m_pMaxBtn;
    CButtonUI* m_pRestoreBtn;
    CButtonUI* m_pMinBtn;
    CButtonUI* m_pSearch;
    CButtonUI* m_pChangeimg;
    CButtonUI* m_pQRcode;
    CButtonUI* m_pLogo;
    CButtonUI* m_pSetting;
    CButtonUI* m_pReturn;
    CButtonUI* m_pbkc_default;
	CButtonUI* m_pbkc_lightblue;
	CButtonUI* m_pbkc_green;
	CButtonUI* m_pbkc_red;
	CButtonUI* m_pbkc_bkiamge;
	CButtonUI* m_pQRC_ioc;

    CEditUI* m_pEdit;
    CEditUI* m_pUserName;
    CEditUI* m_pPwd;

    CHorizontalLayoutUI* m_pLogin;
    CHorizontalLayoutUI* m_pQRcodepage;

    CVerticalLayoutUI* m_pSkinlayout;
    CVerticalLayoutUI* m_pLoginpage;
    CVerticalLayoutUI* m_pMainbk;

};
