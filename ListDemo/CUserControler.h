#pragma once
#include "CUserInfo.h"
#include "../libcURL/include/curl.h"
#include <string>
/***
*��ģ�Ͷ�Ӧ�Ŀ������࣬�����˲���ģ�͵���ط��������л��ͷ����л�����
ģ���ṩ���������ݴ洢����������ת������ص����ݲ���Ӧ���ŵ�����������
�����������ṩ��UI����ģ�͵�������

add by ljm
*/
class CUserControler
{
public:
	CUserControler();

	void ParseFromJson(string& url, CUserInfo* info);
	void SaveUserInfoToFile(CUserInfo* info, const string& filepath);
	void GetUserInfoFromFile(CUserInfo* info, const string& filepath);

	string PostReq(const string& url);
	string U8ToUnicode(const string& szU8);
	string GetKeyValue(const string& msg, string key);
	void CutKeyValue(string& msg);
	string Redirect(const string& url);

	virtual ~CUserControler();
};

