#pragma once
#include <string>
using namespace std;
class ControllerBase
{
protected:
	static bool input(int& input, bool Condition = false);
	static bool input(string& input);
	static void clear_screen();
	static void delayer(int delay_amount_in_miliseconds);
	static void changeTextColor(int number);
};