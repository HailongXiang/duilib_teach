#include "stdafx.h"
#include "CStringUtils.h"


CStringUtils::CStringUtils()
{
}


void CStringUtils::CutKeyValue(string& msg)
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

string CStringUtils::U8ToUnicode(const string& szU8)
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

string CStringUtils::GetKeyValue(const string& msg, string key)
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


CStringUtils::~CStringUtils()
{
}
