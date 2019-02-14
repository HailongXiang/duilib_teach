#pragma once
#include <string>
#include "../libcURL/include/curl.h"
class Utils
{
public:
	Utils();
	~Utils();

public:
	void CutKeyValue(string& msg);
	string U8ToUnicode(const string& szU8);
	string GetKeyValue(const string& msg, string key);
	string Redirect(const string& url);
	string DownloadQRC(string& qrc_url);
};

