#include <string>
#include "Token.h"
#include "My_Exception.h"
using namespace std;

Token::Token(int type, string s, int start, int end)
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
			//cout << i << " ";
		}
		if (s[i] == '.')
		{
			if (i == End - 1)throw(Number_Ex(Start));
			long double base = 0.1;
			for (i++; s[i] >= '0' && s[i] <= '9' && i < End; i++)
			{
				num += (s[i] - '0') * base;
				base /= 10;
			}
		}
		//cout << num << endl;
		if (i != End)throw(Number_Ex(Start));
		break;
	case VAR:
		var = s.substr(start, end-start);
		break;
	case EXPR:
		//cout << endl << s.substr(start, end-start) << endl;
		expression = new Expr(s.substr(start, end-start));
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