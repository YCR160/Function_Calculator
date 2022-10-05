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
	friend std::ostream& operator<<(std::ostream& os, const My_Exception& ex)
	{
		SetColor(red);
		os << ex.description << " at " << ex.pos << endl;
		SetColor(white);
		return os;
	}
};

class Syntax_Ex :My_Exception
{
public:
	Syntax_Ex(int pos) :My_Exception("Number Exeption", pos) {}
};

class Symbol_Ex :My_Exception
{
public:
	Symbol_Ex(int pos) :My_Exception("Symbol Exeption",pos){}
};

class Number_Ex :My_Exception
{
public:
	Number_Ex(int pos) :My_Exception("Number Exeption", pos) {}
};

class Bracket_Ex :My_Exception
{
public:
	Bracket_Ex(int pos) :My_Exception("Bracket Exeption", pos) {}
};
