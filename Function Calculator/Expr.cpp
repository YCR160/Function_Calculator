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
		if ((*start)->Type == NUMBER)
		{
			long double temp = (*start)->num;
			char temp_s[1005] = { 0 };
			sprintf_s(temp_s, sizeof(temp_s),"%.2lf", temp);
			strncpy_s(Tree+Tree_len, sizeof(Tree) - Tree_len, temp_s, 100);
			Tree_len += strlen(temp_s);
			cout << temp;
		}
		else if ((*start)->Type == VAR)
		{
			const char* temp = (*start)->var.c_str();
			char temp_s[1005] = { 0 };
			sprintf_s(temp_s, sizeof(temp_s), "%s", temp);
			strncpy_s(Tree + Tree_len, sizeof(Tree) - Tree_len, temp_s, 100);
			Tree_len += strlen(temp_s);
			cout << temp;
		}
		else if ((*start)->Type == EXPR)(*start)->expression->Print((*start)->expression->Tokens.rbegin(), (*start)->expression->Tokens.rend());
		return;
	}
	for (it--; it != end; it++)
	{
		if ((*it)->Type == PLUS || (*it)->Type == MINUS)//加减法
		{
			Tree_len+=sprintf_s(Tree + Tree_len, sizeof(Tree) - Tree_len, "(");
			printf("(");

			Print(++it, end);
			it--;

			Tree_len += sprintf_s(Tree + Tree_len, sizeof(Tree)-Tree_len, " %c ", symbol[(*it)->Type]);
			cout << " " << symbol[(*it)->Type] << " ";

			Print(start, it);

			Tree_len += sprintf_s(Tree + Tree_len, sizeof(Tree)-Tree_len, ")");
			printf(")");
			//cout << endl << Tree_len << endl;
			return;
		}
	}
	for (it = start; it != end; it++)
	{
		if ((*it)->Type == MUL || (*it)->Type == SLASH)//乘除法
		{
			Tree_len += sprintf_s(Tree + Tree_len, sizeof(Tree) - Tree_len, "(");
			printf("(");

			Print(++it, end);
			it--;

			Tree_len += sprintf_s(Tree + Tree_len, sizeof(Tree) - Tree_len, " %c ", symbol[(*it)->Type]);
			cout << " " << symbol[(*it)->Type] << " ";

			Print(start, it);

			Tree_len += sprintf_s(Tree + Tree_len, sizeof(Tree) - Tree_len, ")");
			printf(")");
			return;
		}
	}
	for (it = start; it != end; it++)
	{
		if ((*it)->Type == TIP)//乘方
		{
			Tree_len += sprintf_s(Tree + Tree_len, sizeof(Tree) - Tree_len, "(");
			printf("(");

			Print(++it, end);
			it--;

			Tree_len += sprintf_s(Tree + Tree_len, sizeof(Tree) - Tree_len, " %c ", symbol[(*it)->Type]);
			cout << " " << symbol[(*it)->Type] << " ";

			Print(start, it);

			Tree_len += sprintf_s(Tree + Tree_len, sizeof(Tree) - Tree_len, ")");
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

void Expr::Show()
{
	Print(Tokens.rbegin(), Tokens.rend());
	cout << endl;
	//cout << Tree_len << endl;
	int level = 0,cnt=0;
	for (int i = 0; i < Tree_len; i++)//获取括号重数
	{
		if (Tree[i] == '(')cnt++;
		else if (Tree[i] == ')')cnt--;
		if (cnt > level)level = cnt;
	}
	//cout << level << endl;
	for (int i = 1; i <= level; i++)//输出第i重括号的内容
	{
		for (int j = 0; j < Tree_len; j++)//输出运算符号
		{
			if (Tree[j] == '(')cnt++;
			else if (Tree[j] == ')')cnt--;
			else if (cnt == i && (Tree[j] == '+' || Tree[j] == '-' || Tree[j] == '*' || Tree[j] == '/' || Tree[j] == '^'))printf("%c", Tree[j]);
			else printf(" ");
		}
		printf("\n");
		for (int j = 0; j < Tree_len; j++)//输出树的枝干
		{
			if (Tree[j] == '(')
			{
				printf(" ");
				cnt++;
			}
			else if (Tree[j] == ')')
			{
				printf(" ");
				cnt--;
			}
			else if (cnt == i)
			{
				printf("/");
				for (; j < Tree_len && cnt >= i && Tree[j] != '+' && Tree[j] != '-' && Tree[j] != '*' && Tree[j] != '/' && Tree[j] != '^';j++)//去到运算符
				{
					//cout << j << " ";
					if (Tree[j] == '(')cnt++;
					else if (Tree[j] == ')')cnt--;
					printf("-");
				}
				printf("\\");
				for (; cnt >= i; j++)//走完数字
				{
					if (Tree[j] == '(')cnt++;
					else if (Tree[j] == ')')cnt--;
					printf(" ");
				}
			}
			else printf(" ");
		}
		printf("\n");
		for (int j = 0; j < Tree_len; j++)//输出数字或变量
		{
			if (Tree[j] == '(')cnt++;
			else if (Tree[j] == ')')cnt--;
			else if (cnt == i && Tree[j] != '+' && Tree[j] != '-' && Tree[j] != '*' && Tree[j] != '/' && Tree[j] != '^')printf("%c", Tree[j]);
			else printf(" ");
		}
		printf("\n");
	}
}