#include<iostream>
#include"DerivedClass.h"


void test()
{
	ManH person;
	person.Eat();
	person.Breathe();
	person.Sleep();
	person.work();
	person.SetName("���˵����ֽ�����");
	string man_name = person.GetName();
	cout << man_name << endl;

	cout << "----------------" << endl;

	WomanH w_person;
	w_person.Eat();
	w_person.Breathe();
	w_person.Sleep();
	w_person.work();
	w_person.SetName("Ů�˵����ֽ�����");
	string woman_name = w_person.GetName();
	cout << woman_name << endl;
}


int main()
{
	test();
}