#pragma once
#include"BaseClass.h"



class WomanH : public Person
{
public:
	void Eat() { cout << "Ů�˳Զ���" << endl; }
	void Sleep() { cout << "Ů��˯��" << endl; }
	void Breathe() { cout << "Ů�˺���" << endl; }
public:
	void Speak() { cout << "Ů��˵��" << endl; }
	void SetName(const string strName) { m_strName = strName; }
	string GetName() { return m_strName; }
	string m_strName;
public:
	void work() { cout << "Ů�˹���" << endl; }
};

class ManH : public Person
{
public:
	void Eat()
	{
		cout << "���˳Զ���" << endl;
	}
	void Sleep()
	{
		cout << "����˯��" << endl;
	}
	void Breathe()
	{
		cout << "���˺���" << endl;
	}
public:
	void Speak()
	{
		cout << "����˵��" << endl;
	}
	void SetName(const string strName)
	{
		m_strName = strName;
	}
	string GetName()
	{
		return m_strName;
	}
	string m_strName;
public:
	void work()
	{
		cout << "���˹���" << endl;
	}
};