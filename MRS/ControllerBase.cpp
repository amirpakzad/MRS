#include "ControllerBase.h"
#include <iostream>
#include <istream>
#include <Windows.h>
using namespace std;

bool ControllerBase::input(int& input,bool Condition)
{
	if (Condition)
		cin.ignore();
	cin >> input;
	if (!cin.fail())
	{
		return true;
	}
	cin.clear();
	cin.ignore();
	return false;
}
bool ControllerBase::input(string& input)
{
	cin.ignore();
	getline(cin, input);
	if (!cin.fail())
	{
		return true;
	}
	cin.clear();
	cin.ignore();
	return false;
}
void ControllerBase::clear_screen()
{
	system("CLS");
}
void ControllerBase::delayer(int delay_amount_in_miliseconds)
{
	Sleep(delay_amount_in_miliseconds);
}
void ControllerBase::changeTextColor(int number)
{
	if(number==0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	else if(number==1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
}