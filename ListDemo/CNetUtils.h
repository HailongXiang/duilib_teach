#pragma once
#include <string>
#include "../libcURL/include/curl.h"
#include "CStringUtils.h"
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

