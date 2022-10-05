#include "Token.h"
#include "My_Exception.h"

void Bracket_Match(Expr* ex, int& i, const string& s, int len)
{
	//cout << "*";
	int start = i, end;
	i++;
	for (; i < len && s[i] != ')'; i++) {
		if (s[i] == '(')Bracket_Match(ex, i, s, len);
	}
	end = i;
	if (end == len)throw(Bracket_Ex(start));
	ex->Tokens.push_back(new Token(EXPR, s, start, end));
	//cout << "#";
}

Expr::Expr(const string& s)
{
	int len = s.length();
	//cout << len << endl;
	for (int i = 0; i < len;)//切割成一串token
	{
		//cout << i << " ";
		if (s[i] >= '0' && s[i] <= '9')//遇到数字
		{
			int start = i, end;
			for (; i < len && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'); i++);
			end = i;
			Tokens.push_back(new Token(NUMBER, s, start, end));
		}
		else if (s[i] == '(')
		{
			Bracket_Match(this, i, s, len);
		}
		else if (s[i] == '+')
		{
			int start = i, end;
			for (; i < len && (s[i] < '0' || s[i] > '9'); i++);
			end = i;
			Tokens.push_back(new Token(PLUS, s, start, end));
		}
		else if (s[i] == '-')
		{
			int start = i, end;
			for (; i < len && (s[i] < '0' || s[i] > '9'); i++);
			end = i;
			Tokens.push_back(new Token(MINUS, s, start, end));
		}
		else if (s[i] == '*')
		{
			int start = i, end;
			for (; i < len && (s[i] < '0' || s[i] > '9'); i++);
			end = i;
			Tokens.push_back(new Token(MUL, s, start, end));
		}
		else if (s[i] == '/')
		{
			int start = i, end;
			for (; i < len && (s[i] < '0' || s[i] > '9'); i++);
			end = i;
			Tokens.push_back(new Token(SLASH, s, start, end));
		}
		else if (s[i] == '^')
		{
			int start = i, end;
			for (; i < len && (s[i] < '0' || s[i] > '9'); i++);
			end = i;
			Tokens.push_back(new Token(TIP, s, start, end));
		}
		else if (isalpha(s[i]))
		{
			int start = i, end;
			for (; i < len && (s[i] < 0 || s[i]>9); i++);
			end = i;
			Tokens.push_back(new Token(VAR, s, start, end));
		}
		else throw(Syntax_Ex(i));
	}
}

void Expr::Print()
{
	for (auto it = Tokens.begin(); it != Tokens.end(); it++)
	{
		if ((*it)->Type == NUMBER)cout << (*it)->num << " ";

	}
}

long double Expr::Show()
{
	return 0;
}