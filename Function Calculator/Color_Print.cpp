#include "Color_Print.h"

void SetColor(colors color)
{
	switch (color)
	{
	case white:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	case red:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); break;
	case yellow:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); break;
	case green:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); break;
	case cyan:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	case blue:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); break;
	case purple:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE); break;
	default:break;
	}
}
void Color_Print(colors color, const char* out)
{
	SetColor(color);
	printf("%s", out);
	SetColor(white);
}
void INIT()
{
	Color_Print(green,"-Funtion Calculator-\n");
	Color_Print(green,"Hello! You can:\n\n");
	Color_Print(cyan,"a=x^2+x+1     ����һ������\n");
	Color_Print(cyan, "a             ����������\n");
	Color_Print(cyan, "eval a        �����������ֵ\n");
	Color_Print(cyan, "undefine a    ȡ������������Ķ���\n");
	Color_Print(cyan, "show a        ��ӡ����������﷨������ûд��������\n");
	Color_Print(cyan, "exit quit     �˳�\n\n");
}