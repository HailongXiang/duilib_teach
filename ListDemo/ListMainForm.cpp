﻿#include "StdAfx.h"
#include "ListMainForm.h"
#include "MenuWnd.h"
#include "flash10a.tlh"

#include <iostream>
#include <windows.h>  
#include <commdlg.h>  


using namespace std;
using namespace DuiLib;

#define TIMER_ID_TEST 100
#define TIMER_TIME_TEST 1000
#define MSG_NULL "0"



/*
* 存放第二列数据
*/
std::vector<std::string> domain;

/*
* 存放第三列数据
*/
std::vector<std::string> desc;

std::vector<std::string> edit;

/**
初始化UI控件
*/
void ListMainForm::Init()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_close")));
	//static_cast 强制类型转换，_T 可以搜索文档16.2小节
	m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
	m_pSearch = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_search")));

	m_pChangeimg = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_changeimg")));
	m_pQRcode = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_QRcode")));
	m_pLogo = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_logo")));
	m_pSetting = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_setting")));
	m_pReturn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_return")));
	m_pQRC_ioc = static_cast<CButtonUI*>(m_pm.FindControl(_T("QRCode_ico")));

	m_pbkc_default = static_cast<CButtonUI*>(m_pm.FindControl(_T("default")));
	m_pbkc_lightblue = static_cast<CButtonUI*>(m_pm.FindControl(_T("lightblue")));
	m_pbkc_green = static_cast<CButtonUI*>(m_pm.FindControl(_T("green")));
	m_pbkc_red = static_cast<CButtonUI*>(m_pm.FindControl(_T("red")));
	m_pbkc_bkiamge = static_cast<CButtonUI*>(m_pm.FindControl(_T("bkiamge")));

	m_pLogin = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("btn_login")));
	m_pSkinlayout = static_cast<CVerticalLayoutUI*>(m_pm.FindControl(_T("skinlayout")));
	m_pLoginpage = static_cast<CVerticalLayoutUI*>(m_pm.FindControl(_T("loginpage")));
	m_pMainbk = static_cast<CVerticalLayoutUI*>(m_pm.FindControl(_T("mainbk")));
	m_pQRcodepage = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("QRcodepage")));

	m_pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("edit")));
	m_pUserName = static_cast<CEditUI*>(m_pm.FindControl(_T("uername")));
	m_pPwd = static_cast<CEditUI*>(m_pm.FindControl(_T("password")));

	//m_pWebBrowser = static_cast<CWebBrowserUI*>(m_pm.FindControl(_T("web")));
}

/**
*这是一个全局测试函数，不属于ListMainForm类。
*一个类里面的函数应该和类密切相关，不相干的函数需要抽出到其他类或者Utils中
*
*/
void TestMemoryFunc()
{
	int* array = new int[10]; //使用vs提供的内存查看工具可以得知 数组的内存是连续的，可以通过memset来统一初始化内存
	memset(array, 0x0F, sizeof(int) * 10);


	char chInput[512];
	sprintf(chInput, "int:%d\n", array[0]);//手动修改内存， 请将array中的第一个数字大小修改为15，
	DUITRACE(_T("array---[0]: %s"), chInput);//注意用此方法可以输出信息到vs的调试窗口中

	//OutputDebugString(chInput);

	//TestMem* m;
	//for (int i = 0; i < 190464; i++) {
	//	m =new  TestMem;
	//	m->count = 15;
	//}
}

DWORD WINAPI ListMainForm::Search(LPVOID lpParameter)
{
	TestMemoryFunc();

	try
	{
		struct Prama* prama = (struct Prama *)lpParameter;//指针类型转换，从void* 转换为目标指针类型
		CListUI* pList = prama->pList;
		CButtonUI* pSearch = prama->pSearch;
		CDuiString tDomain = prama->tDomain;
		//-------------------------------------
		/*
		* 添加数据循环
		*/
		for (int i = 0; i < 100; i++)
		{
			std::stringstream ss;//使用stringstream方便字符串拼接 
			ss << "www." << i << ".com";
			domain.push_back(ss.str());
			ss.clear();
			ss << "it's " << i;
			desc.push_back(ss.str());
			CListTextElementUI* pListElement = new CListTextElementUI;
			pListElement->SetTag(i);
			if (pListElement != NULL)
			{
				::PostMessage(prama->hWnd, WM_ADDLISTITEM, 0L, (LPARAM)pListElement);
			}
			/*
			*	Sleep 为了展示添加的动态效果，故放慢了添加速度，同时可以看到添加过程中界面仍然可以响应
			*/
			::Sleep(100);
		}

		delete prama;//一定要删除这个变量，否则会造成内存泄漏，new Prama和delete要成对出现


		pSearch->SetEnabled(true);
		return 0;
	}
	catch (...)
	{
		return 0;
	}
}



void ListMainForm::Login()
{
	::MessageBox(NULL, "登录成功", _T("提示"), MB_OK);
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	WinExec("D:\\c++Study\\duilib_new\\duilib_teach\\bin\\QQDemo.exe", SW_SHOW);
}

//获取图片路径
LPTSTR GetImgPath() {
	OPENFILENAME ofn;
	char szFile[1000];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0" "PNG(*.png)\0*.png\0" "BMP(*.bmp)\0*.bmp\0" "JPEG(*.jpg,*.jpeg)\0*.jpg;*.jpeg\0" "GIF(*.gif)\0*.gif\0";

	LPTSTR path_image;
	if (GetOpenFileName(&ofn)) {
		path_image = ofn.lpstrFile;
		return path_image;
	}
	else {
		return 0;
	}
}

//改变头像并输出路径
void ListMainForm::ChangeImg()
{
	LPTSTR path_image = 0;
	CDuiString path_temp = m_pEdit->GetText();
	if (!access(path_temp, 0))
	{
		m_pChangeimg->SetNormalImage(path_temp);
		m_pEdit->SetText(_T("    恭喜你！头像更换成功"));
	}
	else
		path_image = GetImgPath();

	if (path_image != 0)
	{
		m_pChangeimg->SetNormalImage(_T(path_image));
		m_pEdit->SetText(_T("路径:") + _bstr_t(path_image));
	}
	else if (path_image == 0 && access(path_temp, 0) == -1)
		m_pEdit->SetText(_T("    请选择正确的图片路径哦"));
}

//获取post返回的信息
CUserInfo* ListMainForm::GetLoginUrlData()
{
	string readBuffer;
	string password = m_pPwd->GetText();
	string username = m_pUserName->GetText();
	string host = "http://localhost:8081/autologin?";
	string url = host + "username=" + username + "&pwd=" + password;
	if (!(username[0] && password[0]))
		m_pEdit->SetText(_T("        账号或密码为空"));
	else 
	{
		CUserInfo* m_puserinfo = new CUserInfo();
		m_userctl.ParseFromJson(url, m_puserinfo);
		string code = m_puserinfo->getCode();
		string account = m_puserinfo->getAccount();
		string pwd = m_puserinfo->getPwd();
		if (code == "1")
			return m_puserinfo;
		else if (code == MSG_NULL)
		{
			if (username == account && password == pwd)
			{
				string prompt = "网络连接失败，是否登录本地账号:\n" + account;
				int res = MessageBox(m_hWnd , prompt.c_str(), _T("提示"), MB_YESNO);
				if (res == IDYES)
					return m_puserinfo;
				else
					return NULL;
			}
			m_pEdit->SetText(_T("  网络连接失败，请检查网络"));
		}
		else if (code == "-1")
			m_pEdit->SetText(_T("         账号或密码错误"));
	}
	ShockWnd();
	return NULL;
}

void ListMainForm::OnLogin()
{
	CUserInfo* my_info = GetLoginUrlData();
	if (my_info == NULL)
		return;
	SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
	InfoList* pInfoFrame = new InfoList();
	pInfoFrame->m_puserinfo = my_info;
	pInfoFrame->CreatWnd(pInfoFrame);
	
	/*m_pEdit->SetText(_T("        ") + _bstr_t(username.c_str()) + _T("登录成功"));
	string QRCurl;
	QRCurl = "http://api.k780.com:88/?app=qr.get&data=账号基本信息:%0A姓名:" + username + "%0A账号:" + account + "%0A教学科目:" + bankname + "%0A分类名称:" + categoryName + "%0A教学书目:" + ledgeName + "%0A学校:" + schoolname;
	//QRCurl = "http://api.k780.com:88/?app=qr.get&data=" + my_msg;
	DownloadQRC(QRCurl);*/
}


//窗口抖动
void ListMainForm::ShockWnd()
{
	RECT rcWnd;
	::GetWindowRect(*this, &rcWnd);
	LONG left = rcWnd.left;
	LONG top = rcWnd.top;
	LONG width = rcWnd.right - rcWnd.left;
	LONG height = rcWnd.bottom - rcWnd.top;
	for (int i = 0; i < 10; i++)
	{
		SetWindowPos(m_hWnd, NULL, left - 7, top, width, height, SWP_SHOWWINDOW);
		::Sleep(10);
		SetWindowPos(m_hWnd, NULL, left + 7, top, width, height, SWP_SHOWWINDOW);
		::Sleep(10);
		SetWindowPos(m_hWnd, NULL, left, rcWnd.top, width, height, SWP_SHOWWINDOW);
		::Sleep(10);
	}
}



/***
*TODO 编写函数在点击search按钮之后当前窗口围绕左上角旋转，旋转半径为50，考虑多线程，定时器

*/

void ListMainForm::OnSearch()
{

	struct Prama *prama = new Prama;

	CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("domainlist"))); //提问： 此处可以如何优化？
	CEditUI* pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("input")));
	pEdit->SetEnabled(false);
	CDuiString input = pEdit->GetText();
	m_pSearch->SetEnabled(false);//提问：此处为何要SetEnabled(false);？
	pList->RemoveAll();
	domain.empty();
	domain.resize(0);
	desc.empty();
	desc.resize(0);
	DWORD dwThreadID = 0;
	pList->SetTextCallback(this);//[1]

	prama->hWnd = GetHWND();//给结构体赋值，用结构体传递参数的好处是：当要增加或者删除一个参数的时候可以直接修改结构体
	prama->pList = pList;
	prama->pSearch = m_pSearch;
	prama->tDomain = input;

	//开启线程进入线程执行函数，search,
	HANDLE hThread = CreateThread(NULL, 0, &ListMainForm::Search, (LPVOID)prama, 0, &dwThreadID);
}

/*
* 关键的回调函数，IListCallbackUI 中的一个虚函数，渲染时候会调用,在[1]中设置了回调对象
*/
LPCTSTR  ListMainForm::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	switch (iSubItem)
	{
	case 0:
		_stprintf(szBuf, _T("%d"), iIndex);
		break;
	case 1:
	{
#ifdef _UNICODE		
		int iLen = domain[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, domain[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		_stprintf(szBuf, lpText);
		delete[] lpText;
#else
		_stprintf(szBuf, domain[iIndex].c_str());
#endif
	}
	break;
	case 2:
	{
#ifdef _UNICODE
		int iLen = desc[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, desc[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		_stprintf(szBuf, lpText);
		delete[] lpText;
#else
		_stprintf(szBuf, desc[iIndex].c_str());
#endif
	}
	break;
	}
	pControl->SetUserData(szBuf);
	return pControl->GetUserData();
}

void ListMainForm::ClickBack()
{
	if (m_pLoginpage) m_pLoginpage->SetVisible(true);
	if (m_pSkinlayout) m_pSkinlayout->SetVisible(false);
	if (m_pReturn) m_pReturn->SetVisible(false);
	if (m_pSetting) m_pSetting->SetVisible(true);
	if (m_pQRcodepage) m_pQRcodepage->SetVisible(false);
	m_pQRcode->SetBkImage("datedu.png");
}

void ListMainForm::ClickSetting()
{
	if (m_pLoginpage) m_pLoginpage->SetVisible(false);
	if (m_pSkinlayout) m_pSkinlayout->SetVisible(true);
	if (m_pReturn) m_pReturn->SetVisible(true);
	if (m_pSetting) m_pSetting->SetVisible(false);
	if (m_pQRcodepage) m_pQRcodepage->SetVisible(false);
	SetColorTag();
}

void ListMainForm::ClickQRCioc()
{
	if (m_pQRcodepage) m_pQRcodepage->SetVisible(true);
	if (m_pLoginpage) m_pLoginpage->SetVisible(false);

	if (m_pSkinlayout) m_pSkinlayout->SetVisible(false);
	if (m_pReturn) m_pReturn->SetVisible(true);
	if (m_pSetting) m_pSetting->SetVisible(false);
}

void ListMainForm::Setbkc(DWORD color)
{
	m_pMainbk->SetBkColor(color);
	m_pMainbk->SetBkImage(_T("透明.png"));
}

void ListMainForm::SetColorTag()
{
	m_pbkc_default->SetTag(1);
	m_pbkc_lightblue->SetTag(2);
	m_pbkc_green->SetTag(3);
	m_pbkc_red->SetTag(4);
	m_pbkc_bkiamge->SetTag(5);
}

void ListMainForm::ChangeBk(const int& tag)
{
	switch (tag)
	{
	case 1:Setbkc(m_pbkc_default->GetBkColor());
		break;
	case 2:Setbkc(m_pbkc_lightblue->GetBkColor());
		break;
	case 3:Setbkc(m_pbkc_green->GetBkColor());
		break;
	case 4:Setbkc(m_pbkc_red->GetBkColor());
		break;
	case 5:
	{
		LPTSTR path_image;
		path_image = GetImgPath();
		if (path_image)
			m_pMainbk->SetBkImage(_T(path_image));
	}
	break;
	}
}
/**
* DUI框架内部定义的消息回调函数，消息体TNotifyUI包括一个消息很自然的一些属性如消息的类型，
消息的发送者，消息发生的时间，消息发生时候鼠标的位置等等， 可以在此处打上断点，查看dui消息流转顺序
*/
void  ListMainForm::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("windowinit"))
		OnPrepare(msg);
	else if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pCloseBtn)
		{
			PostQuitMessage(0);
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
		else if (msg.pSender == m_pSearch)
		{
			OnSearch();
		}
		else if (msg.pSender == m_pChangeimg)
		{
			ChangeImg();
		}
		else if (msg.pSender == m_pLogo)
		{
			ShellExecute(NULL, _T("open"), _T("http://www.datedu.cn/"), NULL, NULL, SW_SHOW);
		}
		else if (msg.pSender == m_pLogin)
		{
			OnLogin();
			return;
		}
		else if (msg.pSender == m_pQRC_ioc)
		{
			ClickQRCioc();
		}
		else if (msg.pSender == m_pSetting)
		{
			ClickSetting();
		}
		else if (msg.pSender == m_pReturn)
		{
			ClickBack();
		}
		else if (msg.pSender->GetTag())
		{
			int color_tag = msg.pSender->GetTag();
			ChangeBk(color_tag);
		}
	}
	else if (msg.sType == _T("return"))
		OnLogin();
	else if (msg.sType == _T("setfocus"))
	{
	}
	else if (msg.sType == _T("itemclick"))
	{
	}
	else if (msg.sType == _T("itemactivate"))
	{
		int iIndex = msg.pSender->GetTag();
		CDuiString sMessage = _T("Click: ");;
#ifdef _UNICODE		  //思考此处宏定义的目的是什么，
		int iLen = domain[iIndex].length();
		LPWSTR lpText = new WCHAR[iLen + 1];
		::ZeroMemory(lpText, (iLen + 1) * sizeof(WCHAR));
		::MultiByteToWideChar(CP_ACP, 0, domain[iIndex].c_str(), -1, (LPWSTR)lpText, iLen);
		sMessage += lpText;
		delete[] lpText;
#else
		sMessage += domain[iIndex].c_str();//此处参详c++运算符重载，代码	CDuiString CDuiString::operator+(LPCTSTR lpStr) const

#endif
		::MessageBox(NULL, sMessage.GetData(), _T("提示(by tojen)"), MB_OK);
	}

	else if (msg.sType == _T("showactivex")) {
		if (msg.pSender->GetName() != _T("flash")) return;
		IShockwaveFlash* pFlash = NULL;
		CActiveXUI* pActiveX = static_cast<CActiveXUI*>(msg.pSender);
		pActiveX->GetControl(IID_IUnknown, (void**)&pFlash);
		if (pFlash != NULL) {
			pFlash->put_WMode(_bstr_t(_T("Transparent")));
			pFlash->put_Movie(_bstr_t(CPaintManagerUI::GetInstancePath() + _T("\\skin\\WeChatRes\\二维码.swf")));
			pFlash->DisableLocalSecurity();
			pFlash->put_AllowScriptAccess(L"always");
			BSTR response;
			pFlash->CallFunction(L"<invoke name=\"setButtonText\" returntype=\"xml\"><arguments><string>Click me!</string></arguments></invoke>", &response);
			pFlash->Release();
		}
	}

	else if (msg.sType == _T("menu"))
	{
		if (msg.pSender->GetName() != _T("domainlist")) return;
		CMenuWnd* pMenu = new CMenuWnd();
		if (pMenu == NULL) { return; }
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		::ClientToScreen(*this, &pt);//当前窗口坐标转换为系统坐标，相当于局部坐标系转换为绝对坐标系。
		pMenu->Init(msg.pSender, pt);
	}
	else if (msg.sType == _T("menu_Delete")) {
		CListUI* pList = static_cast<CListUI*>(msg.pSender);
		int nSel = pList->GetCurSel();//dui提供的快捷方法，
		if (nSel < 0) return;
		pList->RemoveAt(nSel);
		domain.erase(domain.begin() + nSel);//请思考此处为何要删除domain内数据
		desc.erase(desc.begin() + nSel);
	}
}

LRESULT  ListMainForm::OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CListTextElementUI* pListElement = (CListTextElementUI*)lParam;
	CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("domainlist")));
	if (pList) pList->Add(pListElement);
	return 0;
}

/***
*以下部分代码来自WindowImplBase::OnCreate， 可以了解最原始的窗口建立过程
*/
LRESULT  ListMainForm::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);



	CDialogBuilder builder;
	CDuiString strResourcePath = m_pm.GetResourcePath();
	if (strResourcePath.IsEmpty())
	{
		strResourcePath = m_pm.GetInstancePath();
		strResourcePath += GetSkinFolder().GetData();
	}
	m_pm.SetResourcePath(strResourcePath.GetData());

	m_pm.Init(m_hWnd);
	CControlUI* pRoot = builder.Create(GetSkinFile().GetData(), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	SetTimer(this->m_hWnd, TIMER_ID_TEST, TIMER_TIME_TEST, 0);


	return 0;
}



/***
可以使用内存诊断工具（调试，窗口，显示诊断工具）清晰的看到内存只增不减的情形
*/
void ListMainForm::onTimerTest()
{
	void * ptr = malloc(1024 * 1024);

	Sleep(10);//注释以下三句
	if (ptr)
		free(ptr);
}


void ListMainForm::OnTimer(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case TIMER_ID_TEST:
	{
		onTimerTest();
		break;
	}
	default:
		break;
	}
}


LRESULT  ListMainForm::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	/*if (!::IsZoomed(*this)) {
		RECT rcSizeBox = m_pm.GetSizeBox();
		if (pt.y-3 < rcClient.top + rcSizeBox.top) {
			if (pt.x-3 < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x+3 > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}*/

	RECT rcCaption = m_pm.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

/**
*大小改变的回调函数，可以尝试注释，修改代码 看效果
*/
LRESULT  ListMainForm::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
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

LRESULT  ListMainForm::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT  ListMainForm::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

/***
* 处理来着windows系统的各种消息，WM= windows  message
*/
LRESULT  ListMainForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_ADDLISTITEM:   lRes = OnAddListItem(uMsg, wParam, lParam, bHandled); break;
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_TIMER:
	{
		OnTimer(wParam, lParam);
		break;
	}
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

/****
提问：
1.请统计下执行search前后listdemo.exe的内存增长情况（）28
2.请自己添加一个内存泄漏的代码，在执行serarch之后内存占用超过1M，


*/