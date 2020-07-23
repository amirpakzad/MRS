#include "MovieService.h"
#include <fstream>
#include <iostream>
#include "Review.h"
#include "ReviewService.h"

static vector<Movie> movies;

ReviewService re;
vector<Movie> MovieService::GetMovies(bool Reset)
{
	if (movies.empty() || Reset)
	{
		ifstream my_file("Movies.txt", ios::in);
		if (open_file(my_file))
		{
			Movie movie;
			while (!my_file.eof())
			{
				getline(my_file, movie.MovieId, '\t');
				getline(my_file, movie.MovieName, '\t');
				if (movie.MovieName.size() > 45)
				{
					movie.MovieName.resize(45);
				}
				getline(my_file, movie.CreateYear,'\t');
				string temp;
				getline(my_file, temp);
				movies.push_back(movie);
			}
			my_file.close();
		}
	}
	return movies;
}

bool MovieService::AddMovie(const string& movieName, const string& year) const
{
	ofstream my_file("Movies.txt", ios::app);
	if (open_file(my_file))
	{
		Movie movie;
		int id = FindId() + 1;
		movie.MovieId = ToString(id);
		movie.MovieName = movieName;
		movie.CreateYear = year;
		my_file << '\n' << movie.MovieId << '\t' << movie.MovieName << '\t' << movie.CreateYear << '\t';
		my_file.close();
		movies.push_back(movie);
		return true;
	}
	my_file.close();
	return false;
}

bool MovieService::isMovieExist(string movie_name)
{
	if (movies.empty())
	{
		GetMovies();
	}
	movie_name = ToLower(movie_name);
	for (Movie item : movies)
	{
		string temp = ToLower(item.MovieName);
		if (temp == movie_name)
		{
			return true;
		}
	}
	return false;
}

bool MovieService::isMovieExist(int movie_id)
{
	if (movies.empty())
	{
		GetMovies();
	}
	for (Movie item : movies)
	{
		if (ToInt(item.MovieId) == movie_id)
		{
			return true;
		}
	}
	return false;
}

vector<Movie> MovieService::GetNotReviewedMovies(int userId)
{
	if (movies.empty())
		GetMovies();
	vector<Movie> pMovies;
	vector<Review> reviews = re.GetReviews();
	for (Movie item : movies)
	{
		int movieId = ToInt(item.MovieId);
		if (ReviewService::GetUserVotesForSpecificMovie(userId, movieId) == -1)
			pMovies.push_back(item);
	}
	return pMovies;
}


Movie MovieService::FindMovieById(int movieId)
{
	int j = FindId();
	Movie movie;
	if (movies.empty())
	{
		GetMovies();
	}
	for (Movie item : movies)
	{
		if (item.MovieId == ToString(movieId))
		{
			return item;
		}
	}
	return movie;
}


int MovieService::FindId()
{
	static int id;
	if (!movies.empty())
		id = ToInt(GetMovies().back().MovieId);
	else
		id = find_last_line("Movies.txt");
	return id;
}

void MovieService::RemoveMovie(int movieId)
{
	if (movies.empty())
	{
		GetMovies();
	}
	for (int i = 0; i < static_cast<int>(movies.size()); i++)
	{
		if (ToInt(movies[i].MovieId) == movieId)
		{
			re.RemoveReviewByMovieId(ToInt(movies[i].MovieId));
			movies.erase(movies.begin()+i);
			break;
		}
	}
	UpdateMovies();
}

void MovieService::RemoveMovie(string movieName) const
{
	movieName=ToLower(movieName);
	if (movies.empty())
	{
		GetMovies();
	}
	for (int i = 0; i < static_cast<int>(movies.size()); i++)
	{
		string temp =ToLower(movies[i].MovieName);
		if (temp == movieName)
		{
			re.RemoveReviewByMovieId(ToInt(movies[i].MovieId));
			movies.erase(movies.begin() + i);
			break;
		}
	}
	UpdateMovies();
}

void MovieService::UpdateMovies() const
{
	ofstream my_file("Movies.txt", ios::out);
	if (open_file(my_file))
	{
		for (int i = 0; i < static_cast<int>(movies.size()); i++)
		{
			my_file << movies[i].MovieId << '\t' << movies[i].MovieName << '\t' << movies[i].CreateYear<<'\t';
			if (i != (static_cast<int>(movies.size()) - 1))
				my_file << '\n';
		}
	}
	my_file.close();
}

