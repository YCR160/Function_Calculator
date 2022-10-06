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


class Expr
{
public:
	vector <Token*> Tokens;
	char Tree[1005] = { 0 };
	int Tree_len = 0;
	Expr(const string& s);
	void Print(vector<Token*>::reverse_iterator, vector<Token*>::reverse_iterator);
	void Show();
	long double Eval(vector<Token*>::reverse_iterator, vector<Token*>::reverse_iterator);
};
