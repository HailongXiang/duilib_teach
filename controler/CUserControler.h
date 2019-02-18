#pragma once
#include "CUserInfo.h"
#include "CNetUtils.h"
#include "CStringUtils.h"
#include <string>
using namespace std;

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

