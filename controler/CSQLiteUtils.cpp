#include "stdafx.h"
#include "CSQLiteUtils.h"


CSQLiteUtils::CSQLiteUtils()
{
}

const wchar_t* Utf8ToWchar(const char *pStr)
{
	if (pStr == NULL)
	{
		return NULL;
	}

	int len = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0);
	if (len <= 0)
	{
		return NULL;
	}
	wchar_t *pwStr = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, pStr, -1, pwStr, len);
	return pwStr;
}

const char* WcharToUtf8(const wchar_t *pwStr)
{
	if (pwStr == NULL)
	{
		return NULL;
	}

	int len = WideCharToMultiByte(CP_UTF8, 0, pwStr, -1, NULL, 0, NULL, NULL);
	if (len <= 0)
	{
		return NULL;
	}
	char *pStr = new char[len];
	WideCharToMultiByte(CP_UTF8, 0, pwStr, -1, pStr, len, NULL, NULL);
	return pStr;
}



int CSQLiteUtils::Open(const string& filename)
{
	pDB = NULL;
	return sqlite3_open(filename.c_str(), &pDB);
}

bool CSQLiteUtils::AddUser(const string& value)
{
	string strSql = "insert into userinfo values(" + value + ");";
	char* cErrMsg;
	int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
	{
		MessageBox(NULL, Utf8ToWchar(cErrMsg), L"add userinfo fail", NULL);
		return false;
	}
	return true;
}

bool CSQLiteUtils::DeleteUser(const string& keyname, const string& value)
{
	string strSql = "";
	strSql += "delete from userinfo where name='";
	strSql += keyname;
	strSql += "';";

	char* cErrMsg;
	int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
	{
		MessageBox(NULL, (LPCWSTR)cErrMsg, L"delete user fail:", NULL);
		return false;
	}

	return true;
}

bool CSQLiteUtils::ModifyUser(const string& keyname, const string& value)
{
	string strSql = "";
	strSql += "update userinfo set name =";
	strSql += keyname;
	strSql += ";";

	char* cErrMsg;
	int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
	{
		MessageBox(NULL, (LPCWSTR)cErrMsg, L"modify user fail: ", NULL);
		return false;
	}

	return true;
}

string my_info;
static int UserResult(void *NotUsed, int argc, char **argv, char **azColName)
{
	stringstream info;
	for (int i = 0; i < argc; i++)
	{
		info << azColName[i] << ":" << (argv[i] ? argv[i] : "NULL") << "\n";
	}
	my_info = info.str();
	return 0;
}

string CSQLiteUtils::SelectUser(string account)
{
	char* cErrMsg;
	string str = "select * from userinfo where account='" + account + "';";
	int res = sqlite3_exec(pDB, str.c_str(), UserResult, 0, &cErrMsg);

	if (res != SQLITE_OK)
	{
		//MessageBox(NULL, (LPCWSTR)cErrMsg, L"select fail:", NULL);
		return NULL;
	}

	return my_info;
}

void CSQLiteUtils::Close()
{
	sqlite3_close(pDB);
}

CSQLiteUtils::~CSQLiteUtils()
{
}
