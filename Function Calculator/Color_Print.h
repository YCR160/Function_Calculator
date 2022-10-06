#pragma once
#include <stdio.h>
#include <string>
#include <windows.h>
using namespace std;

enum colors { white, red, yellow, green, cyan, blue, purple };
void SetColor(colors color);
void Color_Print(colors color, const char* out);
void INIT();