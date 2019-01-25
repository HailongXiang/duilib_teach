#pragma once
#include"interface.h"
#include<iostream>

using namespace std;

class Person : public IAnimal
{
public:
	void Eat()
	{
		cout << "eat bread" << endl;
	}
	void Sleep()
	{
		cout << "sleep 8h" << endl;
	}
	void Breathe()
	{
		cout << "ºôÎü" << endl;
	}
public:
	void Speak();
	void SetName(const string strName);
	string GetName();
	string m_strName;
};

void Person::Speak()
{
	cout << "person speak a lot of language" << endl;
}

void Person::SetName(const string strName)
{
	m_strName = strName;
}
string Person::GetName()
{
	return m_strName;
}




