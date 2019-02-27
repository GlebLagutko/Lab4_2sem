#pragma once
#include <iostream>
#include <string>

using namespace std;

class Flower 
{
private :
	wstring name;
	int days;
public :
	Flower(int d, wstring n) : days(d), name(n) {};
	int GetDays() { return days; };
	void ShowData()
	{
		wcout << name;
		wcout << L" " << days << L" дней" << endl;			 
	}
	friend bool operator< (const Flower &f1, const Flower &f2) ;
};

bool operator < (const Flower &f1, const Flower &f2)
{
	return f1.days < f2.days;
};