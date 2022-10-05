#include <iostream>
#include <string>
#include <map>
#include "My_Exception.h"
#include "Token.h"
#include "Interface.h"
#include "My_Function.h"
#include "Color_Print.h"
using namespace std;

map <string, My_Function*> func;

int main()
{
	string s;
	char head[1005], body[1005];
	int s_len, head_len, body_len;
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
		for (; i < s_len && s[i] != ' '; i++)
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
		//cout << head << " " << body << endl;
		try
		{
			if (body_len == 0)//要求显示函数定义
			{
				if (func.find(head) == func.end())
				{
					My_Function* p = new My_Function(head, head);
					func[head] = p;
				}
				//cout << "*";
				func[head]->print();
				//cout << "#";
			}
			else if (body[0] == '=')//variable = expression 形式
			{
				//cout << "=";
				for (int i = 1; i < body_len; i++)
				{
					body[i - 1] = body[i];
				}
				body_len--;
				body[body_len] = '\0';
				//cout << body << endl;
				if (func.find(head) != func.end())//已有函数定义
				{
					func[head]->redefine(head, body);
				}
				else//未有函数定义
				{
					//cout << "new" << endl;
					My_Function* p = new My_Function(head, body);
					func[head] = p;
				}
			}
			else if (head == "eval")//计算值
			{
				if (func.find(body) == func.end())
				{
					My_Function* p = new My_Function(head, body);
					func[head] = p;
				}
				func[body]->eval();
			}
			else if (head == "show")//打印表达式树
			{
				if (func.find(body) == func.end())
				{
					My_Function* p = new My_Function(head, head);
					func[head] = p;
				}
				func[body]->show();
			}
			else if (head == "undefine")//取消函数的定义
			{
				if (func.find(head) != func.end())
				{
					delete func[body];
					func.erase(body);
				}
			}
			printf(">>>");
		}
		catch(My_Exception ex)
		{
			cout << ex << endl;
		}
	}
}
