#include "MovieController.h"
#include "Movie.h"
#include "MovieView.h"
#include <iostream>
#include "MovieService.h"
#include <fstream>
#include <vector>
#include "HomeController.h"

MovieService _moveService;

MovieController::MovieController(MovieService movieService)
{
	_moveService = movieService;
}

void MovieController::DisplayMovies()
{
	const vector<Movie> Movies = MovieService::GetMovies();
	if (!Movies.empty())
	{
		clear_screen();
		MovieView::DisplayMovie(Movies);
		char choice;
		cin >> choice;
		switch (choice)
		{
		case 'm':
			HomeController::Index();
			break;
		case'q':
			exit(0);
		default:
		{
			string str;
			getline(cin, str);
			changeTextColor(1);
			cout << "  Invalid Input";
			delayer(1000);
			changeTextColor(0);
			HomeController::Index();
			break;
		}
		}
	}
	else
	{
		cerr << "No Movies Found";
	}
}

void MovieController::AddMovie()
{
	clear_screen();
	string movieName;
	string year;
	string save;

	MovieView::AddMovie();
	cin >> movieName;
	MovieView::AddMovie(true);
	cin >> year;
	MovieView::AddMovie(true, true);
	cin >> save;
	if (save == "Y" || save == "y")
	{
		MovieView::AddMovie(true, true, true);
		if (_moveService.isMovieExist(movieName))
		{
			return MovieView::AddMovie(true, true, true, false, true);
		}
		const bool result = _moveService.AddMovie(movieName, year);
		if (!result)
		{
			return MovieView::AddMovie(true, true, true, true, false, false, true);
		}
		MovieView::AddMovie(true, true, true, true, true, false, true);
		string p;
		cin >> p;
		if (p == "m")
			HomeController::Index();
		else if (p == "p")
			AddRemoveSection();
		else if (p == "q")
		{
			exit(0);
		}
		else
		{
			return AddRemoveSection();
		}

	}
	else
	{
		MovieView::AddMovie(false, false, false, false, false, false, true);
	}
}

void MovieController::AddRemoveSection()
{
	clear_screen();
	MovieView::AddRemoveSection();
	char choice;
	cin >> choice;
	switch (choice)
	{
	case 'a':
		AddMovie();
		break;
	case'b':
		RemoveMovie();
		break;
	case'c':
		HomeController::Index();
		break;
	case'd':
		exit(0);
	default:
	{
		cout << "Invalid Input";
		delayer(2000);
		AddRemoveSection();
		break;
	}

	}
}

void MovieController::RemoveMovie()
{
	clear_screen();
	MovieView::RemoveMovie();
	string str;
	input(str);
	if (str == "a")
	{
		cout << " " << "Enter Movie Name : ";
		string movieName;
		getline(cin, movieName);
		MovieView::RemoveMovie(movieName);
		string save;
		getline(cin, save);
		if (save == "y" || save == "Y")
		{
			if (_moveService.isMovieExist(movieName))
			{
				_moveService.RemoveMovie(movieName);
				MovieView::RemoveMovie(false, true);
			}
			else
			{
				MovieView::RemoveMovie(true);
			}
		}

	}
	else if (str == "b")
	{
		cout << " " << "Enter Movie ID : " << '\n';
		int movieId;
		input(movieId);
		MovieView::RemoveMovie(movieId);
		string save;
		input(save);
		if (save == "y" || save == "Y")
		{
			if (_moveService.isMovieExist(movieId))
			{
				_moveService.RemoveMovie(movieId);
				MovieView::RemoveMovie(false, true);
			}
			else
			{
				MovieView::RemoveMovie(true);
			}
		}
	}
	else
	{
		return RemoveMovie();
	}
	char choice = ' ';
	cin >> choice;
	switch (choice)
	{
	case 'r':
		return RemoveMovie();
	case 'm':
		HomeController::Index();
		break;
	case'q':
		exit(0);
	default:
	{
		string str;
		getline(cin, str);
		changeTextColor(1);
		cout << "  Invalid Input";
		delayer(1000);
		changeTextColor(0);
		HomeController::Index();
		break;
	}
	}

}


