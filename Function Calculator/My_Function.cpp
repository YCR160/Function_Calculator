#include <string>
#include "My_Function.h"
#include "Color_Print.h"
using namespace std;

My_Function::My_Function(string name, string body)
{
	Function_name = name;
	//cout << "*";
	expression = new Expr(body);
	//cout << "#";
}
void My_Function::redefine(string name, string body)
{
	Function_name = name;
	delete expression;
	expression = new Expr(body);
}
void My_Function::eval()
{
	//for (auto ptr = expression->Tokens.begin(); ptr != expression->Tokens.end(); ptr++)
	//{
	//	if ((*ptr)->Type == VAR)cout << (*ptr)->var << ",";
	//}
	long double ans = expression->Eval(expression->Tokens.rbegin(), expression->Tokens.rend());
	Color_Print(green, "[=]");	
	cout << ans << endl;
}
void My_Function::print()
{
	Color_Print(green, "[+]");
	expression->Print(expression->Tokens.rbegin(), expression->Tokens.rend());
	printf("\n");
}
void My_Function::show()
{
	expression->Show();
	printf("\n");
}