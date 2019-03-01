#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <codecvt>
#include <list>
#include <queue>
#include <io.h>
#include <fcntl.h>
#include <regex>
#include <iterator>
#include "Flower.h"

using namespace std;

const int Count = 5;
const int Period = 3;

int FindDays(wstring& flower)
{
	int n = 0;
	auto it = std::find_if(flower.begin(), flower.end(), iswdigit);
	if (it != flower.end()) 
		n = _wtoi(flower.c_str() + (it - flower.begin()));
	return n;
}

wstring FindName(wstring& flower)
{
	wstring name;
	for (int i = 0; i < flower.size(); i++)
	{
		if (iswdigit(flower[i]))
		{
			name = flower.substr(0,i);
			return name;
		}
	}
}


priority_queue <Flower> FindFlowers(list<wstring>& listFlowers )
{
	priority_queue <Flower> queueFlowers;
	for (auto it : listFlowers)
	{
		Flower f(FindDays(it), FindName(it));
		queueFlowers.push(f);
	}
	
	return queueFlowers;
};

list<wstring> FillList(wstring name)
{
	wifstream wifile;
	list<wstring> listFlowers;
	wstring line;

	int days;
	wifile.open(name);
	wifile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wifile.ignore(1);
	while (!wifile.eof())
	{
		getline(wifile, line);
		if (!line.empty())
			listFlowers.push_back(line);
	}
	//listFlowers.pop_front();
	return listFlowers;
}

priority_queue <Flower> FillPriorityQueue(wstring name)
{
	list<wstring> listFlowers = FillList(name);
	priority_queue <Flower> mapFlowers = FindFlowers(listFlowers);
	return mapFlowers;
}

void ShowFlower(priority_queue <Flower> queueFlowers)
{
	for (int i = 0 ; i < Count ; i++)
	{
		Flower f = queueFlowers.top();
		f.ShowData();
		queueFlowers.pop();
	}	
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	priority_queue <Flower> queueFlowers = FillPriorityQueue(L"C:\\Users\\Dell\\source\\repos\\Lab4_2sem\\Flowers.txt");
	ShowFlower(queueFlowers);
	system("pause");
}