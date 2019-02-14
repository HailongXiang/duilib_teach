#include "stdafx.h"
#include "Utils.h"
#define MSG_NULL to_string(0)
#define MSG_OK "1"

Utils::Utils()
{
}


size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	int written = 0;
	written = fwrite(ptr, size, nmemb, stream);	//fwrite��������ļ�д��һ�����ݿ飬ptr ��ȡ���ݵĵ�ַ��stream Ŀ���ļ�ָ��
	return written;		//����д����ַ���
}

//����url���ض�ά�벢��������ָ���ļ�����,�����ļ���
string Utils::DownloadQRC(string& qrc_info)
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

string Utils::Redirect(const string& url)
{
	CURL* curl;
	CURLcode res;
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
		CutKeyValue(readBuffer);
		return U8ToUnicode(readBuffer);
	}
	else
		return MSG_NULL;
}

void Utils::CutKeyValue(string& msg)
{
	int msg_len = msg.length();
	int count = 0;
	string temp;
	for (int i = 0; i < msg_len; i++)
	{
		if (msg[i] == '"' || msg[i] == '{' || msg[i] == '}')
		{
			msg.erase(i, 1);	//ȥ�����źʹ�����
			i--;
			msg_len--;
		}
		else  if (msg[i] == ',' && msg[i + 1] == '"')
			msg[i] = '\n';		//���Ż��ɻ���
	}
}

string Utils::U8ToUnicode(const string& szU8)
{
	//UTF8 to Unicode
	//Ԥת�����õ�����ռ�Ĵ�С
	LPCCH szU8_str = szU8.c_str();
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8_str, strlen(szU8_str), NULL, 0);
	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	//ת��
	::MultiByteToWideChar(CP_UTF8, NULL, szU8_str, strlen(szU8_str), wszString, wcsLen);
	//������'\0'
	wszString[wcsLen] = '\0';

	char *m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wszString, wcslen(wszString), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

string Utils::GetKeyValue(const string& msg, string key)
{
	int key_len = key.length();
	int msg_len = msg.length();
	int virtue_len;
	size_t start_pos = 0;
	size_t end_pos = 0;
	start_pos = msg.find(key, start_pos);	//�ؼ��ֵ�һ���ַ���λ��
	if (start_pos > msg_len)
		return "��Ϣ������";
	end_pos = msg.find("\n", start_pos);

	if (end_pos > msg_len)
		virtue_len = msg_len - start_pos - key_len;
	virtue_len = end_pos - start_pos - key_len - 1;
	string value = msg.substr(start_pos + key_len + 1, virtue_len);
	return value;
}


Utils::~Utils()
{
}
