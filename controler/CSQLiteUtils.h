#pragma once
#include <windows.h>
#include "sqlite3.h" 
#include <string>
#include <sstream>

using namespace std;
class CSQLiteUtils
{
public:
	CSQLiteUtils();
	~CSQLiteUtils();

	int Open(const string& filename);
	//增加用户
	bool AddUser(const string& value);
	//删除用户
	bool DeleteUser(const string& keyname, const string& value);
	//修改用户
	bool ModifyUser(const string& keyname, const string& value);
	//查找用户
	string SelectUser(string account);

	void Close();

private:
	sqlite3* pDB;
	
};

