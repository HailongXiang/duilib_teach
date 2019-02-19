#pragma once
#include<string>
#include<Windows.h>
using namespace std;
class CStringUtils
{
public:
	CStringUtils();
	~CStringUtils();

	void CutKeyValue(string& msg);
	string U8ToUnicode(const string& szU8);
	string G2U(const char* gb2312);
	string GetKeyValue(const string& msg, string key);
};

