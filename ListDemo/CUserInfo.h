#pragma once
/**
*用户模型，提供基础数据，将客观存在的实体抽象为类和模型是面向对象编程的基础
将复杂的过程抽象为单个存粹的子过程之组合就是抽象层次
*/
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
	string m_siteurl;
	string m_schoolname;
	string m_categoryname;
	string m_ledgename;
	string m_bankname;
	string m_status;
	string m_QRCfilename;


};

