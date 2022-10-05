#pragma once
#include<string>
#include <vector>
using namespace std;

enum TokenType {
	// Single-character tokens.
	EXPR,
	PLUS, MINUS, MUL, SLASH, TIP,

	VAR, NUMBER,

	NONE
};

class Expr;

class Token
{
public:
	int Start, End,Type;
	char act = 0;//��������
	string var;//����
	long double num = 0;//����
	Expr* expression;
	Token(int type, const string& s, int start, int end);
};


using namespace std;

class Expr
{
public:
	vector <Token*> Tokens;
	Expr(const string& s);
	void Print();
	long double Show();
	long double Eval();
};
