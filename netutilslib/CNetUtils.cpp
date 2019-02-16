#include "stdafx.h"
#include "CNetUtils.h"
#define MSG_NULL "0"
#define MSG_OK "1"

CNetUtils::CNetUtils()
{
}


size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	int written = 0;
	written = fwrite(ptr, size, nmemb, stream);	//fwrite��������ļ�д��һ�����ݿ飬ptr ��ȡ���ݵĵ�ַ��stream Ŀ���ļ�ָ��
	return written;		//����д����ַ���
}

//����url���ض�ά�벢��������ָ���ļ�����,�����ļ���
string CNetUtils::DownloadQRC(string& qrc_info)
{
	CURL *curl;
	CURLcode res;
	FILE *file = NULL;
	string filename;
	//�������������ά���ļ�����������˺��޷��Զ�������ά�������
	filename = "..\\bin\\skin\\WeChatRes\\main\\" + to_string(rand() % 2000) + ".jpg";
	qrc_info = "http://api.k780.com:88/?app=qr.get&data=" + qrc_info;
	if (qrc_info.length() > 900)
		qrc_info = qrc_info.substr(0, 900);
	file = fopen(filename.c_str(), "wb");
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, qrc_info.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)file);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
	res = curl_easy_perform(curl);
	if ((res != CURLE_OK) && (res != CURLE_WRITE_ERROR)) {
		return MSG_NULL;
	}
	curl_easy_cleanup(curl);
	fclose(file);
	return filename;
}

static size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

string CNetUtils::Redirect(const string& url)
{
	CURL* curl;
	CURLcode res = (CURLcode)100;
	string readBuffer;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		CURL* url_r;
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);		//������ȡ�ض���ҳ��
		curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &url_r);		//��ȡ�ض����url
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	if (res == CURLE_OK)
	{
		m_stringutils.CutKeyValue(readBuffer);
		return m_stringutils.U8ToUnicode(readBuffer);
	}
	else
		return MSG_NULL;
}


CNetUtils::~CNetUtils()
{
}
