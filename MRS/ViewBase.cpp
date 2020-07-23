#include "ViewBase.h"
#include <Windows.h>

void ViewBase::clear_screen()
{
	system("cls");
}

void ViewBase::delayer(int delay_amount_in_miliseconds)
{
	Sleep(delay_amount_in_miliseconds);
}

void ViewBase::changeTextColor(int number)
{
	switch (number)
	{
	case 0:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	case 1:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	default:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}
