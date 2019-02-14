#pragma once
class CStringUtils
{
public:
	CStringUtils();
	~CStringUtils();

	void CutKeyValue(string& msg);
	string U8ToUnicode(const string& szU8);
	string GetKeyValue(const string& msg, string key);
};

