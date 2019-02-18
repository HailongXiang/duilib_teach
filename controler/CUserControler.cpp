#include "stdafx.h"
#include "CUserControler.h"
#define MSG_NULL "0"
#define MSG_OK "1"
#define INFOFILENAME "userinfo.txt"


CUserControler::CUserControler()
{
}

#define K_V(name) m_stringutils.GetKeyValue(msg, name)
void CUserControler::ParseFromJson(string& url, CUserInfo* info)
{
	string msg = m_netutils.Redirect(url);
	if (msg == MSG_NULL)
	{
		GetUserInfoFromFile(info, INFOFILENAME);
		return;
	}
	info->setCode(K_V("code"));
	SetK_V(info, msg);
	SaveUserInfoToFile(info, INFOFILENAME);
}

void CUserControler::SetK_V(CUserInfo* info, const string& msg)
{
	//info->setCode(K_V("code"));
	info->setUserName(K_V("username"));
	info->setId(K_V("uid"));
	info->setAccount(K_V("account"));
	info->setPwd(K_V("pwd"));
	info->setStatus(K_V("status"));
	info->setSiteurl(K_V("siteurl"));
	info->setSchoolname(K_V("schoolname"));
	info->setCategoryName(K_V("categoryName"));
	info->setLedgeName(K_V("ledgeName"));
	info->setBankname(K_V("bankname"));

	string qrc_info = "账号基本信息:%0A姓名:" + info->getUserName() + "%0A账号:" + info->getAccount() + "%0A教学科目:" + info->getBankname() + "%0A分类名称:" + info->getCategoryName() + "%0A教学书目:" + info->getLedgeName() + "%0A学校:" + info->getSchoolname();
	info->setQRCFileName(m_netutils.DownloadQRC(qrc_info));
}

#define FPRINTF(key,value) fprintf(fp,"%s%s%s",key,value,"\n")
void CUserControler::SaveUserInfoToFile(CUserInfo* info, const string& filepath)
{
	FILE* fp = fopen(filepath.c_str(), "w");
	if (fp == NULL)
		return;
	//FPRINTF("code:", info->getCode().c_str());
	FPRINTF("username:", info->getUserName().c_str());
	FPRINTF("uid:", info->getId().c_str());
	FPRINTF("account:", info->getAccount().c_str());
	FPRINTF("pwd:", info->getPwd().c_str());
	FPRINTF("status:", info->getStatus().c_str());
	FPRINTF("siteurl:", info->getSiteurl().c_str());
	FPRINTF("schoolname:", info->getSchoolname().c_str());
	FPRINTF("categoryName:", info->getCategoryName().c_str());
	FPRINTF("ledgeName:", info->getLedgeName().c_str());
	FPRINTF("bankname:", info->getBankname().c_str());

	fclose(fp);
}

void CUserControler::GetUserInfoFromFile(CUserInfo * info, const string & filepath)
{
	FILE* fp = fopen(filepath.c_str(), "r");
	if (fp == NULL)
		return;
	string readbuff;
	while (!feof(fp))
	{
		readbuff += fgetc(fp);
	}
	fscanf(fp, "%s", &readbuff);
	SetK_V(info, readbuff);
	info->setCode(MSG_NULL);
}


CUserControler::~CUserControler()
{
}
