#pragma once
#include "CUserInfo.h"
#include "Utils.h"
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
	virtual ~CUserControler();

public:
	void ParseFromJson(string& url, CUserInfo* info);
	void SaveUserInfoToFile(CUserInfo* info, const string& filepath);
	void GetUserInfoFromFile(CUserInfo* info, const string& filepath);
	void SetK_V(CUserInfo* info, const string& msg);

public:
	Utils m_utils;
};

