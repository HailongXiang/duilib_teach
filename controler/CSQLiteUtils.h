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
	//�����û�
	bool AddUser(const string& value);
	//ɾ���û�
	bool DeleteUser(const string& keyname, const string& value);
	//�޸��û�
	bool ModifyUser(const string& keyname, const string& value);
	//�����û�
	string SelectUser(string account);

	void Close();

private:
	sqlite3* pDB;
	
};

