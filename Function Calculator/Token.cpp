#include <string>
#include "Token.h"
#include "My_Exception.h"
using namespace std;

Token::Token(int type, const string& s, int start, int end)
{
	Type = type;
	Start = start;
	End = end;
	int i = Start;
	switch (Type)
	{
	case NUMBER:
		for (; s[i] != '.' && i < End; i++)
		{
			//cout << num << endl;
			num *= 10;
			num += s[i] - '0';
		}
		if (s[i] == '.')
		{
			if (i == End - 1)throw(Number_Ex(Start));
			long double base = 1;
			for (i++; s[i] >= '0' && s[i] <= '9'; i++)
			{
				num += (s[i] - '0') * base;
				base /= 10;
			}
		}
		//cout << num << endl;
		if (i != End)throw(Number_Ex(Start));
		break;
	case VAR:
		var = s.substr(start, end);
		break;
	case EXPR:
		expression = new Expr(s.substr(start + 1, end - 1));
		break;
	case PLUS:
		if (End - Start != 1)throw(Symbol_Ex(Start));
		act = s[Start];
		break;
	case MINUS:
		if (End - Start != 1)throw(Symbol_Ex(Start));
		act = s[Start];
		break;
	case MUL:
		if (End - Start != 1)throw(Symbol_Ex(Start));
		act = s[Start];
		break;
	case SLASH:
		if (End - Start != 1)throw(Symbol_Ex(Start));
		act = s[Start];
		break;
	case TIP:
		if (End - Start != 1)throw(Symbol_Ex(Start));
		act = s[Start];
		break;
	default:break; throw(Syntax_Ex(start));
	}
}