#include <iostream>
#include <string>
#include "Token.h"
#include "My_Function.h"
#include "My_Exception.h"
using namespace std;

map <string, My_Function*> func;

Expr* Get(string s)
{
	if (func.find(s) == func.end())throw(Var_Ex(0));
	return func[s]->expression;
}

int main()
{
	string s;
	char head[1005], body[1005];
	int s_len, head_len, body_len;
	INIT();
	printf(">>>");
	while (getline(cin, s) && s != "exit" && s != "quit")
	{
		//对输入的指令和表达式（如果存在的话）进行分割
		s_len = s.length();
		memset(head, 0, sizeof(head));
		memset(body, 0, sizeof(body));
		head_len = 0;
		body_len = 0;
		int i = 0;
		for (; i < s_len && s[i] != ' ' && s[i] != '='; i++)
		{
			head[i] = s[i];
		}
		head_len = i;
		head[head_len] = '\0';
		while (s[i] == ' ')i++;
		for (; i < s_len; i++)
		{
			if (s[i] == ' ')continue;
			body[body_len++] = s[i];
		}
		//cout << head << endl << body << endl;
		//My_Exception* p = new Syntax_Ex(1);
		try
		{
			if (body_len == 0)//要求显示函数定义
			{
				if (func.find(head) == func.end())
				{
					My_Function* p = new My_Function(head, head);
					func[head] = p;
				}
				func[head]->print();
				//for (auto ptr = func[head]->expression->Tokens.begin(); ptr != func[head]->expression->Tokens.end(); ptr++)
				//{
				//	if ((*ptr)->Type == VAR)cout << (*ptr)->var << " ";
				//}
			}
			else if (body[0] == '=')//variable = expression 形式
			{
				for (int i = 1; i < body_len; i++)
				{
					body[i - 1] = body[i];
				}
				body_len--;
				body[body_len] = '\0';
				if (!body_len)throw(Func_Ex(0));
				//cout << body << endl;
				if (func.find(head) != func.end())//已有函数定义
				{
					func[head]->redefine(head, body);
				}
				else//未有函数定义
				{
					My_Function* p = new My_Function(head, body);
					func[head] = p;
				}
			}
			else if (!strcmp(head, "eval\0"))//计算值
			{				
				if (func.find(body) == func.end())
				{
					My_Function* p = new My_Function(body, body);
					func[body] = p;
				}
				func[body]->eval();
			}
			else if (!strcmp(head, "show\0"))//打印表达式树
			{
				if (func.find(body) == func.end())
				{
					My_Function* p = new My_Function(head, head);
					func[head] = p;
				}
				func[body]->show();
			}
			else if (!strcmp(head, "undefine\0"))//取消函数的定义
			{
				if (func.find(body) != func.end())
				{
					//cout << "*";
					delete func[body];
					func.erase(body);
				}
			}
			else throw(Ex_Command(0));
		}
		catch (My_Exception ex)
		{
			Color_Print(red, "[!] An exception has occurred!\n");
			cout << ex;
		}
		printf(">>>");
	}
}
