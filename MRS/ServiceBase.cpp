#include "ServiceBase.h"
#include <fstream>
#include <iostream>
#include "Movie.h"
using namespace std;

bool ServiceBase::open_file(std::fstream& my_file)
{
	if (!my_file)
	{
		cerr << "File Not Found" << "\n";
		return false;
	}
	return true;
}

bool ServiceBase::open_file(std::ostream& my_file)
{
	if (!my_file)
	{
		cerr << "File Not Found" << "\n";
		return false;
	}
	return true;
}

bool ServiceBase::open_file(std::istream& my_file)
{
	if (!my_file)
	{
		cerr << "File Not Found" << "\n";
		return false;
	}
	return true;
}

string ServiceBase::ToString(const int input)
{
	return to_string(input);
}

int ServiceBase::ToInt(const string input)
{
	int output = 0;

	int i = 0;
	for (char ch : input)
	{
		if (ch > 47 && ch < 58)
		{
			int temp = 0;
			temp += ch - 48;
			if (i == 0)
				output += temp;
			else
				output = output * 10 + temp;
		}
		i++;
	}
	return output;
	/*
	 * Another Way
	  return scanf_s(input.c_str());
	 */
}

string ServiceBase::ToLower(string input)
{
	string output;
	for (char item : input)
	{
		if (item >= 65 && item <= 90)
			item = item + 32;
		output += item;
	}
	return output;
}

int ServiceBase::find_last_line(string _Filename)
{
	ifstream my_file(_Filename, ios::in);
	int lastId = 0;
	if (open_file(my_file))
	{
		string temp;
		while (!my_file.eof())
		{
			getline(my_file, temp);
			lastId++;
		}
		my_file.close();
	}
	return lastId;
}
