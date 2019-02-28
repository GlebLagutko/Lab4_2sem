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

bool CheckStacks(stack<wchar_t> stackDigits, stack<wchar_t> stackOperators)
{
	if (stackDigits.size() >= stackOperators.size() + 1)
		return true;
	else
		return false;
}

bool IsOperator(wchar_t str)
{
	if (str == L'+' || str == L'-' || str == L'*' || str == L'/')
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

double Answer(queue<wchar_t> queueRPN)
{
	stack<double> stackRPN;
	while (!queueRPN.empty())
	{
		if (iswdigit(queueRPN.front()))
		{
			wchar_t ch = queueRPN.front();
			double i = _wtoi(&ch);
			stackRPN.push(i);
			queueRPN.pop();
		}
		else
		{
				double op2 = stackRPN.top();
				stackRPN.pop();
				double op1 = stackRPN.top();
				stackRPN.pop();
				stackRPN.push(ArithmeticOperations(op1, op2, queueRPN.front()));
				queueRPN.pop();
		}
	}
	return stackRPN.top();
}

queue<wchar_t> FillQueue(wstring RPN)
{
	queue<wchar_t> queueRPN;
	
	for(int  i = 0; i < RPN.size(); i++)
	{
		if (RPN[i] != L' ')
		{
			queueRPN.push(RPN[i]);
		}
	}

	return queueRPN;
}

bool CheckString(wstring str)
{
	int i = 0;
	stack<wchar_t> stackDigits;
	stack<wchar_t> stackOperators;
	while(i < str.size())
	{
		if (str[i] != L' ')
		{
			if (iswdigit(str[i]))
			{
				stackDigits.push(str[i]);
				i++;
			}
			else
			{
				if (IsOperator(str[i]))
				{
					stackOperators.push(str[i]);
					i++;
					if (!CheckStacks(stackDigits, stackOperators))
						return false;
				}
				else
					i++;
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
	int  i = 0;
	wstring str;
	
	while (i == 0)
	{
		wcout << "Input RPN or Exit : ";
		getline(wcin, str);
		if (str != L"Exit")
		{
			if (CheckString(str) != false && Answer(FillQueue(str)) != NULL)
			{
				double p = Answer(FillQueue(str));
				wcout << L"Answer : " << p << endl;
			}
			else
				wcout << L"Error !!! Try again " << endl;
		}
		else
			break;
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