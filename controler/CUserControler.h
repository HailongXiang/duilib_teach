#pragma once
#include "CUserInfo.h"
#include "CNetUtils.h"
#include "CStringUtils.h"
#include "CSQLiteUtils.h"
#include <string>
#include "sqlite3.h"
//#include "sqlite.h"
using namespace std;

#define DLL_API __declspec(dllexport)

class DLL_API CUserControler
{
public:
	CUserControler();
	virtual ~CUserControler();

public:
	void ParseFromJson(string& url, CUserInfo* info, string infofilename);

private:
	void SaveUserInfoToFile(CUserInfo* info, const string& filepath);
	void GetUserInfoFromFile(CUserInfo* info, const string& filepath);
	void SetK_V(CUserInfo* info, const string& msg);
	void SaveUserToDB(CUserInfo* info, const string& msg);
	void GetUserFromDB(CUserInfo* info);

private:
	CStringUtils m_stringutils;
	CNetUtils m_netutils;
	sqlite3* m_pdb;
};

