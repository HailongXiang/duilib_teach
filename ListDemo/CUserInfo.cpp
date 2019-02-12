#include "stdafx.h"
#include "CUserInfo.h"


CUserInfo::CUserInfo()
{
}

void CUserInfo::setCode(string code)
{
	m_code = code;
}

string CUserInfo::getCode()
{
	return m_code;
}

void CUserInfo::setId(string id)
{
	m_uid = id;
}

string CUserInfo::getId()
{
	return m_uid; 
}


void CUserInfo::setUserName(string username)
{
	m_username = username;
}

string CUserInfo::getUserName() 
{ 
	return m_username; 
}


void CUserInfo::setAccount(string account)
{
	m_account = account;
}

string CUserInfo::getAccount()
{
	return m_account;
}


void CUserInfo::setStatus(string status)
{
	m_status = status;
}

string CUserInfo::getStatus()
{
	return m_status;
}


void CUserInfo::setSiteurl(string siteurl)
{
	m_siteurl = siteurl;
}

string CUserInfo::getSiteurl()
{
	return m_siteurl;
}


void CUserInfo::setSchoolname(string schoolname)
{
	m_schoolname = schoolname;
}

string CUserInfo::getSchoolname()
{
	return m_schoolname;
}


void CUserInfo::setCategoryName(string categoryname)
{
	m_categoryname = categoryname;
}

string CUserInfo::getCategoryName()
{
	return m_categoryname;
}


void CUserInfo::setLedgeName(string ledgename)
{
	m_ledgename = ledgename;
}

string CUserInfo::getLedgeName()
{
	return m_ledgename;
}


void CUserInfo::setBankname(string bankname)
{
	m_bankname = bankname;
}

string CUserInfo::getBankname()
{
	return m_bankname;
}



CUserInfo::~CUserInfo()
{
}
