#include<iostream>
#include"DerivedClass.h"


void test()
{
	ManH person;
	person.Eat();
	person.Breathe();
	person.Sleep();
	person.work();
	person.SetName("男人的名字叫张三");
	string man_name = person.GetName();
	cout << man_name << endl;

	cout << "----------------" << endl;

	WomanH w_person;
	w_person.Eat();
	w_person.Breathe();
	w_person.Sleep();
	w_person.work();
	w_person.SetName("女人的名字叫王舞");
	string woman_name = w_person.GetName();
	cout << woman_name << endl;
}


int main()
{
	test();
}