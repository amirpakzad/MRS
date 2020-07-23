#pragma once
#include <string>
using namespace std;

class ServiceBase
{
protected:
	static bool open_file(std::fstream& my_file);
	static bool open_file(std::ostream& my_file);
	static bool open_file(std::istream& my_file);
	static int  find_last_line(string _Filename);
	static string ToString(int input);
	static int ToInt(const string input);
	static string ToLower(string input);
};

