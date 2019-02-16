#pragma once
#include "../libcURL/include/curl.h"
#include "../stringutilslib/CStringUtils.h"

#ifdef _DEBUG
#pragma comment(lib, "../libcURL/lib/libcurld.lib")
#else
#pragma comment(lib, "../libcURL/lib/libcurl.lib")
#endif

#include <string>
using namespace std;

class CNetUtils
{
public:
	CNetUtils();
	~CNetUtils();

public:
	string Redirect(const string& url);
	string DownloadQRC(string& qrc_url);

public:
	CStringUtils m_stringutils;

};

