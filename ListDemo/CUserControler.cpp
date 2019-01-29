#include "stdafx.h"
#include "CUserControler.h"
#define MSG_NULL to_string(0)
#define MSG_OK "1"

CUserControler::CUserControler()
{
}

static size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string CUserControler::PostReq(const string& url)
{
	CURL *curl;
	CURLcode res;
	string readBuffer;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);	//传递所有的参数到WriteCallback
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if (curl && res == CURLE_OK)
		return U8ToUnicode(readBuffer);
	else
		return MSG_NULL;
}

void CUserControler::CutKeyValue(string& msg)
{
	int msg_len = msg.length();
	int count = 0;
	string temp;
	for (int i = 0; i < msg_len; i++)
	{
		if (msg[i] == '"' || msg[i] == '{' || msg[i] == '}')
		{
			msg.erase(i, 1);	//去除引号和大括号
			i--;
			msg_len--;
		}
		else  if (msg[i] == ',' && msg[i + 1] == '"')
			msg[i] = '\n';		//逗号换成换行
	}
}

string CUserControler::U8ToUnicode(const string& szU8)
{
	//UTF8 to Unicode
	//预转换，得到所需空间的大小
	LPCCH szU8_str = szU8.c_str();
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8_str, strlen(szU8_str), NULL, 0);
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szU8_str, strlen(szU8_str), wszString, wcsLen);
	//最后加上'\0'
	wszString[wcsLen] = '\0';

	char *m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

string CUserControler::GetKeyValue(const string& msg, string key)
{
	int key_len = key.length();
	int msg_len = msg.length();
	int virtue_len;
	size_t start_pos = 0;
	size_t end_pos = 0;
	start_pos = msg.find(key, start_pos);	//关键字第一个字符的位置
	if (start_pos > msg_len)
		return "信息不存在";
	end_pos = msg.find("\n", start_pos);

	if (end_pos > msg_len)
		virtue_len = msg_len - start_pos - key_len;
	virtue_len = end_pos - start_pos - key_len - 1;
	string value = msg.substr(start_pos + key_len + 1, virtue_len);
	return value;
}

#define K_V(name) GetKeyValue(msg, name)

void CUserControler::ParseFromJson(string& url, CUserInfo* info)
{
	string& msg = PostReq(url);
	if (msg == MSG_NULL)
		return;
	CutKeyValue(msg);

	info->setCode(K_V("code"));
	info->setUserName(K_V("username"));
	info->setId(K_V("uid"));
	info->setAccount(K_V("account"));
	info->setStatus(K_V("status"));
	info->setSiteurl(K_V("siteurl"));
	info->setSchoolname(K_V("schoolname"));
	info->setCategoryName(K_V("categoryName"));
	info->setLedgeName(K_V("ledgeName"));
	info->setBankname(K_V("bankname"));
}


void CUserControler::SaveUserInfoToFile(CUserInfo * info, const string & filepath)
{
}

void CUserControler::GetUserInfoFromFile(CUserInfo * info, const string & filepath)
{
}


CUserControler::~CUserControler()
{
}
