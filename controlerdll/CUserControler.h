#pragma once
#include "..\modellib\CUserInfo.h"
#include "..\netutilslib\CNetUtils.h"
#include "..\stringutilslib\CStringUtils.h"
#include <string>
using namespace std;

#ifdef _DEBUG
#pragma comment(lib, "../libcURL/lib/libcurld.lib")
#else
#pragma comment(lib, "../libcURL/lib/libcurl.lib")
#endif

#define DLL_API __declspec(dllexport)

class DLL_API CUserControler
{
public:
	CUserControler();
	virtual ~CUserControler();

public:
	void ParseFromJson(string& url, CUserInfo* info);
	void SaveUserInfoToFile(CUserInfo* info, const string& filepath);
	void GetUserInfoFromFile(CUserInfo* info, const string& filepath);
	void SetK_V(CUserInfo* info, const string& msg);

public:
	CStringUtils m_stringutils;
	CNetUtils m_netutils;
};

