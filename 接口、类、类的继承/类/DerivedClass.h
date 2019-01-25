#pragma once
#include"BaseClass.h"



class WomanH : public Person
{
public:
	void Eat() { cout << "女人吃东西" << endl; }
	void Sleep() { cout << "女人睡觉" << endl; }
	void Breathe() { cout << "女人呼吸" << endl; }
public:
	void Speak() { cout << "女人说话" << endl; }
	void SetName(const string strName) { m_strName = strName; }
	string GetName() { return m_strName; }
	string m_strName;
public:
	void work() { cout << "女人工作" << endl; }
};

class ManH : public Person
{
public:
	void Eat()
	{
		cout << "男人吃东西" << endl;
	}
	void Sleep()
	{
		cout << "男人睡觉" << endl;
	}
	void Breathe()
	{
		cout << "男人呼吸" << endl;
	}
public:
	void Speak()
	{
		cout << "男人说话" << endl;
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
		cout << "男人工作" << endl;
	}
};