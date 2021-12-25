
// Unit test, right values
#include "stdafx.h"
using namespace System;

// function that finds the maximum value between three integers
int Max(int a, int b, int c)

// a - Cola, b - Root bear , c- lemon lime 
{
    int max = a;
    if (max < b) max = b;
    if (max < c) max = c;
    return max;
}

int main(array<System::String^> ^ args)
{
    Console::WriteLine(L"Unit-test in MS Visual Studio.");
    return 0;
}