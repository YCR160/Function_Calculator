#pragma once
#include<string>
#include <vector>
#include <map>
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
	int Start, End, Type;
	char act = 0;//操作符号
	string var;//变量
	long double num = 0;//数字
	Expr* expression = nullptr;
	Token(int type, string s, int start, int end);
};


using namespace std;

class Expr
{
public:
	vector <Token*> Tokens;
	Expr(const string& s);
	void Print(vector<Token*>::reverse_iterator, vector<Token*>::reverse_iterator);
	long double Show();
	long double Eval(vector<Token*>::reverse_iterator, vector<Token*>::reverse_iterator);
};
