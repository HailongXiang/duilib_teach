#pragma once
#include "curl.h"
#include "CStringUtils.h"
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

private:
	CStringUtils m_stringutils;

};

