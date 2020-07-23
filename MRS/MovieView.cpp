#include "MovieView.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void MovieView::DisplayMovie(vector<Movie> const& movies)
{

	cout << "  " << "\n"; 
	cout << string(10, ' ') << string(20, '-');
	cout << "  " << "Display Movies";
	cout << "  " << string(20, '-') << string(20, ' ') << "\n" << "\n";
	cout << "  " << "Id" << string(4,' ' )<< "Movie Name" << string(46,' ') << "Year" << "\n";
	cout << "  " << "--" << string(4, ' ') << string(11, '-') << string(46, ' ') << "----" << "\n";
	for (const Movie temp : movies)
	{

		string str = temp.MovieName;
		cout << "  " << temp.MovieId << '\t' << setw(50) << std::left << str << '\t' << temp.CreateYear << endl;
		delayer(50);
	}
	cout << "\n  Press 'm' to Main menu , and 'q' to quit  : ";
}

void MovieView::AddRemoveSection()
{
	cout << " " << string(10, '-') << '\n';
	cout << " " << "Add/Remove a movie" << '\n';
	cout << " " << string(10, '-') << "\n" << "\n";
	cout << " " << string(4, '=') << "What do you want to do?" << string(4, '=') << '\n' << '\n';
	cout << " " << "a.Add a new movie " << '\n';
	cout << " " << "b.Remove a movie " << '\n';
	cout << " " << "c.back to main menu " << '\n';
	cout << " " << "d.Exit " << '\n' << '\n';
	cout << " " << "Your Choice? : ";

}

void MovieView::AddMovie(bool yearSection, bool section, bool saved, bool ModelState, bool result, bool section3, bool lastSection)
{
	if (yearSection)
	{
		if (yearSection && !ModelState && !section)
		{
			cout << " " << "Year:";
		}
		if (yearSection && section && !ModelState && !saved)
		{
			cout << " " << string(15, '=') << '\n';
			cout << " " << "Do You Want To Save ? : ";
		}
		if (saved)
		{
			if (ModelState && result)
			{
				cout << "\n\n" << " " << "The record was successfully saved ";
			}
		}
	    if (saved &&!ModelState&& section3)
		{
			cout << "\n " << "This movie already exists"<<'\n';
		}
		else
		{

			if (!result && ModelState && saved)
			{
				cerr << "And Error occured while saving movie";
			}
		}
		if(lastSection)
		{
			cout << "\n\n" << " " << "Press 'r' to retry, 'p' to Previous ,'m' to Main menu , and 'q' to Quit";
			cout << "\n " << "Your Choice? : ";
		}
	}
	else
	{
		cout << " " << string(10, '-') << '\n';
		cout << " " << "Add a new movie" << '\n';
		cout << " " << string(10, '-') << "\n" << "\n";
		cout << " " << "Enter Information Below" << '\n';
		cout << " " << string(15, '=') << '\n';
		cout << " " << "Name:";
	}
}


void MovieView::RemoveMovie(bool ModelState,bool success)
{
	if (ModelState)
	{
		cout << " " << "This movie does not exist" << '\n';
		cout << "\n\n" << " " << "Press 'r' to retry, 'p' to Previous ,'m' to Main menu , and 'q' to Quit";
		cout << "\n " << "Your Choice? : ";
	}
	else if(success)
	{
		cout << " " << "The record was successfully removed." << '\n';
		cout << "\n\n" << " " << "Press 'r' to retry, 'p' to Previous ,'m' to Main menu , and 'q' to Quit";
		cout << "\n " << "Your Choice? : ";
	}
	else
	{
		cout << " " << string(15, '-') << '\n';
		cout << " " << "Remove a movie" << '\n';
		cout << " " << string(15, '-') << "\n" << "\n";
		cout << " " << "a.By Name " << '\n';
		cout << " " << "b.By ID " << '\n';
		cout << "\n " << "Your Choice? : ";
	}
}

void MovieView::RemoveMovie(int movieId)
{
	cout << " " << "Add you sure you want to delete 'movie "<<movieId<<"'(Y/N)? " << '\n';
}

void MovieView::RemoveMovie(const string& movieName)
{
	cout << " " << "Add you sure you want to delete '" << movieName << "'(Y/N)? " << '\n';
}


