#include <iostream>

#include <stack>
#include <algorithm>
#include <algorithm>
#include <sstream>
#include <codecvt>
#include <queue>
#include <io.h>
#include <fcntl.h>

using namespace std;

bool CheckStacks(stack<wstring> stackDigits, stack<wstring> stackOperators)
{
	if (stackDigits.size() >= stackOperators.size() + 1)
		return true;
	else
		return false;
}

bool IsOperator(wchar_t str)
{
	if (str == '+' || str == '-' || str == '*' || str == '/')
		return true;
	else
		return false;
}

double ArithmeticOperations(const double &op1,const double &op2,const wchar_t   &operation)
{
	double result = 0.0;
	switch (operation)
	{
	case ('+'):  result = op1 + op2;
		break;
	case ('-'):  result = op1 - op2;
		break;
	case ('*'):  result = op1 * op2;
		break;
	case ('/'):  result = op1 / op2;
		break;
	}
	return result;
}

double Answer(queue<wstring> queueRPN)
{
	stack<double> stackRPN;
	while (!queueRPN.empty())
	{
		if (iswdigit(queueRPN.front()[0]))
		{
			double value = (double)_wtof(queueRPN.front().c_str());
			stackRPN.push(value);
			queueRPN.pop();
		}
		else
		{
				double op2 = stackRPN.top();
				stackRPN.pop();
				double op1 = stackRPN.top();
				stackRPN.pop();
				stackRPN.push(ArithmeticOperations(op1, op2, queueRPN.front()[0]));
				queueRPN.pop();
		}
	}
	return stackRPN.top();
}

queue<wstring> FillQueue(wstring RPN)
{
	queue<wstring> queueRPN;
	
	for(int  i = 0; i < RPN.size(); i++)
	{
		if (RPN[i] != L' ')
		{
			wstring str;
			if (!iswdigit(RPN[i])) 
			{
				str = RPN[i];
				queueRPN.push(str);
			}
			else
			{
				int k = i;
				while (iswdigit(RPN[i]))
					i++;
				str = RPN.substr(k, i);
				queueRPN.push(str);
				i--;
			}
		}
	}

	return queueRPN;
}

bool CheckString(wstring str)
{
	int i = 0;
	stack<wstring> stackDigits;
	stack<wstring> stackOperators;
	while(i < str.size())
	{
		if (str[i] != L' ')
		{
			if (iswdigit(str[i]))
			{
				int k = i;
				while (iswdigit(str[i]))
					i++;
				wstring ch = str.substr(k, i);
				stackDigits.push(ch);
			}
			else
			{
				if (IsOperator(str[i]))
				{
					stackOperators.push(str);
					i++;
					if (CheckStacks(stackDigits, stackOperators) == false)
						return false;
				}
				else
					return false;
			}
		}
		else
			i++;
	}
	if (stackDigits.size() == stackOperators.size() + 1)
		return true;
	else
		return false;

}

int Menu()
{
	wstring str;
	
	while (true)
	{
		wcout << "Input RPN or Exit : ";
		getline(wcin, str);
		if (str != L"Exit")
		{
			if (CheckString(str) == true)
			{
				double p = Answer(FillQueue(str));
				wcout << L"Answer : " << p << endl;
			}
			else
				wcout << L"Error !!! Try again " << endl;
		}
		else
		{
			wcout << L"Goodbye " << endl;
			break;
		}
	}
	return 0;
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	Menu();

	system("pause");

}