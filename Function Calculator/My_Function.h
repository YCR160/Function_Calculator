#pragma once
#include <iostream>
#include <string>
#include "Interface.h"
#include "Token.h"
using namespace std;

class My_Function :virtual public Interface
{
public:
	string Function_name;
	Expr* expression;
	My_Function(string name = "", string body = "");
	void redefine(string name = "", string body = "");
	void eval();
	void print();
	void show();
	~My_Function() { this->redefine(Function_name, Function_name); }
};
