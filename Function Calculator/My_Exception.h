#pragma once
#include <iostream>
#include <string>
#include "Color_Print.h"
using namespace std;

class My_Exception
{
public:
	int pos;
	string description;
	My_Exception(string des, int pos) : description(des), pos(pos) {}
	friend ostream& operator<<(ostream& os, const My_Exception& ex)
	{
		SetColor(yellow);
		os << "[x] " << ex.description << " at " << ex.pos << endl;
		SetColor(white);
		return os;
	}
};

class Syntax_Ex :public My_Exception
{
public:
	Syntax_Ex(int pos) :My_Exception("Number Exeption", pos) {}
};

class Symbol_Ex :public My_Exception
{
public:
	Symbol_Ex(int pos) :My_Exception("Symbol Exeption", pos) {}
};

class Number_Ex :public My_Exception
{
public:
	Number_Ex(int pos) :My_Exception("Number Exeption", pos) {}
};

class Bracket_Ex :public My_Exception
{
public:
	Bracket_Ex(int pos) :My_Exception("Bracket Exeption", pos) {}
};

class Ex_Command:public My_Exception
{
public:
	Ex_Command(int pos) :My_Exception("Command Exeption", pos) {}
};
class Var_Ex:public My_Exception
{
public:
	Var_Ex(int pos) :My_Exception("Has Undefine Var(s)", pos) {}
};

class Func_Ex:public My_Exception
{
public:
	Func_Ex(int pos) :My_Exception("Has No Input", pos) {}
};