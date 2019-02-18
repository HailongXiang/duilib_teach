#pragma once
#include<string>
using  namespace std;

class CUserInfo
{
public:
	CUserInfo();
	~CUserInfo();

	void setCode(string code);
	string getCode();

	void setId(string id);
	string getId();

	void setUserName(string username);
	string getUserName();

	void setAccount(string account);
	string getAccount();

	void setPwd(string pwd);
	string getPwd();

	void setStatus(string status);
	string getStatus();

	void setSiteurl(string siteurl);
	string getSiteurl();

	void setSchoolname(string schoolname);
	string getSchoolname();

	void setCategoryName(string categoryname);
	string getCategoryName();

	void setLedgeName(string ledgename);
	string getLedgeName();

	void setBankname(string bankname);
	string getBankname();

	void setQRCFileName(string QRCfilename);
	string getQRCFileName();


private:
	string m_code;
	string m_uid;
	string m_username;
	string m_account;
	string m_pwd;
	string m_siteurl;
	string m_schoolname;
	string m_categoryname;
	string m_ledgename;
	string m_bankname;
	string m_status;
	string m_QRCfilename;


};