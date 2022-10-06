#include "Token.h"
#include "My_Function.h"
#include "My_Exception.h"

//void Bracket_Match(Expr* ex, int& i, const string& s, int len)
//{
//	//cout << "*";
//	int start = i, end;
//	i++;
//	for (; i < len && s[i] != ')'; i++) {
//		if (s[i] == '(')Bracket_Match(ex, i, s, len);
//	}
//	end = i;
//	if (end == len)throw(Bracket_Ex(start));
//	ex->Tokens.push_back(new Token(EXPR, s, start, end));
//	//cout << "#";
//}

char symbol[] = " +-*/^   ";

Expr* Get(string s);

Expr::Expr(const string& s)
{
	int len = s.length();
	//cout << len << endl;
	for (int i = 0; i < len;)//切割成一串token
	{
		if (s[i] >= '0' && s[i] <= '9')//遇到数字
		{
			int start = i, end;
			for (; i < len && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'); i++);
			end = i;
			Tokens.push_back(new Token(NUMBER, s, start, end));
		}
		else if (s[i] == '(')
		{
			//Bracket_Match(this, i, s, len);
			int start=i+1,end, cnt = 1;
			//while (end > i && s[end] != ')')end--;
			for (i++; i < len && cnt; i++)
			{
				if (s[i] == '(')cnt++;
				else if (s[i] == ')')cnt--;
			}
			if (cnt)throw(Bracket_Ex(i));
			//Tokens.push_back(new Token(EXPR, s.substr(i + 1, end), 0, end - i));
			end = i - 1;
			Tokens.push_back(new Token(EXPR, s, start, end));
		}
		else if (s[i] == '+')
		{
			int start = i, end;
			for (; i < len && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'); i++);
			end = i;
			Tokens.push_back(new Token(PLUS, s, start, end));
		}
		else if (s[i] == '-')
		{
			int start = i, end;
			for (; i < len && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'); i++);
			end = i;
			Tokens.push_back(new Token(MINUS, s, start, end));
		}
		else if (s[i] == '*')
		{
			int start = i, end;
			for (; i < len && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'); i++);
			end = i;
			Tokens.push_back(new Token(MUL, s, start, end));
		}
		else if (s[i] == '/')
		{
			int start = i, end;
			for (; i < len && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'); i++);
			end = i;
			Tokens.push_back(new Token(SLASH, s, start, end));
		}
		else if (s[i] == '^')
		{
			int start = i, end;
			for (; i < len && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'); i++);
			end = i;
			Tokens.push_back(new Token(TIP, s, start, end));
		}
		else if (isalpha(s[i]))
		{
			int start = i, end;
			for (; i < len && isalpha(s[i]); i++);
			end = i;
			Tokens.push_back(new Token(VAR, s, start, end));
			//cout << start<<" "<<end << endl;
		}
		else throw(Syntax_Ex(i));
	}
	//for (auto ptr = Tokens.begin(); ptr != Tokens.end(); ptr++)
	//{
	//	if ((*ptr)->Type == VAR)cout << (*ptr)->var << " , ";
	//}
}

void Expr::Print(vector<Token*>::reverse_iterator start, vector<Token*>::reverse_iterator end)
{
	auto it = start;
	if (++it == end)
	{
		if ((*start)->Type == NUMBER)cout << (*start)->num;
		else if ((*start)->Type == VAR)cout << (*start)->var;
		else if ((*start)->Type == EXPR)(*start)->expression->Print((*start)->expression->Tokens.rbegin(), (*start)->expression->Tokens.rend());
		return;
	}
	for (it--; it != end; it++)
	{
		if ((*it)->Type == PLUS || (*it)->Type == MINUS)
		{
			printf("(");
			Print(++it, end);
			it--;
			cout << " " << symbol[(*it)->Type] << " ";
			Print(start, it);
			printf(")");
			return;
		}
	}
	for (it = start; it != end; it++)
	{
		if ((*it)->Type == MUL || (*it)->Type == SLASH)
		{
			printf("(");
			Print(++it, end);
			it--;
			cout << " " << symbol[(*it)->Type] << " ";
			Print(start, it);
			printf(")");
			return;
		}
	}
	for (it = start; it != end; it++)
	{
		if ((*it)->Type == TIP)
		{
			printf("(");
			Print(++it, end);
			it--;
			cout << " " << symbol[(*it)->Type] << " ";
			Print(start, it);
			printf(")");
			return;
		}
	}
}

long double Expr::Eval(vector<Token*>::reverse_iterator start, vector<Token*>::reverse_iterator end)
{
	auto it = start;
	if (++it == end)
	{
		if ((*start)->Type == NUMBER)return (*start)->num;
		else if ((*start)->Type == VAR)
		{
			Expr* temp = Get((*start)->var);
			if ((*start)->var == (*temp->Tokens.rbegin())->var)throw(Var_Ex(0));
			return Eval(temp->Tokens.rbegin(), temp->Tokens.rend());
		}
		else if ((*start)->Type == EXPR)return (*start)->expression->Eval((*start)->expression->Tokens.rbegin(), (*start)->expression->Tokens.rend());
	}
	for (it--; it != end; it++)
	{
		if ((*it)->Type == PLUS || (*it)->Type == MINUS)
		{
			long double ans = Eval(++it, end);
			it--;
			if ((*it)->Type == PLUS) ans += Eval(start, it);
			else ans -= Eval(start, it);
			return ans;
		}
	}
	for (it = start; it != end; it++)
	{
		if ((*it)->Type == MUL || (*it)->Type == SLASH)
		{
			long double ans = Eval(++it, end);
			it--;
			if ((*it)->Type == MUL) ans *= Eval(start, it);
			else ans /= Eval(start, it);
			return ans;
		}
	}
	for (it = start; it != end; it++)
	{
		if ((*it)->Type == TIP)
		{
			long double ans = Eval(++it, end);
			it--;
			ans = pow(ans, Eval(start, it));
			return ans;
		}
	}
	return 0;
}

long double Expr::Show()
{
	return 0;
}