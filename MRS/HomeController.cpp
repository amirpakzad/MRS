#include "HomeController.h"
#include "HomeView.h"
#include <iostream>
#include "MovieController.h"
#include <Windows.h>
#include "ReviewService.h"
ControllerBase _controllerBase;
ReviewService _reviewService;
MovieService movieService;
using namespace std;
void HomeController::Index()
{
	clear_screen();
	HomeView::Index();
	cout << "Enter your choice: ";
	int choice;
	const bool result = input(choice);
	if (result)
	{
		switch (choice)
		{
		case 1:
		{
			MovieController::DisplayMovies();
			break;
		}
		case 2:
		{
			DisplayRatings();
			break;
		}
		case 3:
		{
			DisplaySimilarityBetweenTwoUsers();
			break;
		}
		case 4:
		{
			GenerateRecommendations();
			break;
		}
		case 5:
		{
			RateMovie();
			break;
		}
		case 6:
		{
			MovieController::AddRemoveSection();
			break;
		}
		case 7:
		{
			GenerateRecommendationsAdjustedCosineFormula();
			break;
		}
		case 8:
		{
			PopularMovies();
			break;
		}
		case 9:
		{
			PopularMovies(true);
			break;
		}
		case 10:
		{
			exit(0);
		}
		default:
		{
			changeTextColor(1);
			cout << "Entered Amount is incorrect";
			changeTextColor(0);
			delayer(2000);
			clear_screen();
			Index();
			break;
		};
		}
	}
	else
	{
		Index();
	}

}

void HomeController::DisplayRatings()
{
	clear_screen();
	int userId = 0;
	HomeView::DisplayRatings();
	if (input(userId, true))
	{
		if (!_reviewService.isUserExist(userId))
		{

			DisplayRatings();
		}
		const vector<Review> reviews = _reviewService.GetUserReviews(userId);
		if (reviews.empty())
		{
			cerr << "No Movies Found";
		}
		HomeView::DisplayRatings(reviews, userId);
		string str;
		cin >>str;
		if (cin.good())
		{
			if (str == "m" || str == "M")
			{
				Index();
			}
			else if (str == "r" || str == "R")
			{
				DisplayRatings();
			}
			else if (str == "q" || str == "Q")
			{
				exit(0);
			}
			else
			{
				DisplayRatings();
			}
		}
	}
	else
	{
		changeTextColor(1);
		string str;
		getline(cin, str);
		cout << "  Invalid Input";
		str = " ";
		delayer(500);
		changeTextColor(0);
		cin.ignore();
		DisplayRatings();
	}
}

void HomeController::DisplaySimilarityBetweenTwoUsers()
{
	changeTextColor(1);
	changeTextColor(0);
	clear_screen();
	HomeView::DisplaySimilarityBetweenTwoUsers();
	int user1;
	input(user1);
	if (!_reviewService.isUserExist(user1))
	{
		changeTextColor(1);
		HomeView::DisplaySimilarityBetweenTwoUsers(false, true);
		delayer(1000);
		changeTextColor(0);
		DisplaySimilarityBetweenTwoUsers();
	}
	HomeView::DisplaySimilarityBetweenTwoUsers(true);
	int user2;
	input(user2);
	if (!_reviewService.isUserExist(user2))
	{
		changeTextColor(1);
		HomeView::DisplaySimilarityBetweenTwoUsers(false, true);
		delayer(1000);
		changeTextColor(0);
		DisplaySimilarityBetweenTwoUsers();
	}
	double score = _reviewService.GetSimilarityBetweenTwoUsers(user1, user2);
	HomeView::DisplaySimilarityBetweenTwoUsers(user1, user2, score);
	char choice;
	cin >> choice;
	switch (choice)
	{
	case 'r':
		DisplaySimilarityBetweenTwoUsers();
	case 'm':
		Index();
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

void HomeController::GenerateRecommendations(int count)
{
	static int userId;
	clear_screen();
	bool all = true;
	if (count != -1)
	{
		all = false;
		HomeView::GenerateRecommendations();
		input(userId);
	}
	if (!_reviewService.isUserExist(userId))
	{
		changeTextColor(1);
		HomeView::GenerateRecommendations(true);
		delayer(1000);
		changeTextColor(0);
		return GenerateRecommendations();
	}
	HomeView::GenerateRecommendations(userId, _reviewService.PredictUserReviews(userId, count), all);
	char choice;
	cin >> choice;
	switch (choice)
	{
	case 'a':
		GenerateRecommendations(-1);
		break;
	case'b':
		GenerateRecommendations();
		break;
	case'c':
		Index();
		break;
	case'd':
		exit(0);
	default:
	{
		cout << "Invalid Input";
		delayer(1000);
		GenerateRecommendations();
		break;
	}
	}
}

void HomeController::GenerateRecommendationsAdjustedCosineFormula(int count)
{
	static int userId;
	clear_screen();
	bool all = true;
	if (count != -1)
	{
		all = false;
		HomeView::GenerateRecommendations();
		input(userId);
	}
	if (!_reviewService.isUserExist(userId))
	{
		changeTextColor(1);
		HomeView::GenerateRecommendations(true);
		delayer(1000);
		changeTextColor(0);
		return GenerateRecommendationsAdjustedCosineFormula();
	}
	HomeView::GenerateRecommendations(userId, _reviewService.PredictUserReviewsAdjustedFormula(userId, count), all);
	char choice;
	cin >> choice;
	switch (choice)
	{
	case 'a':
		GenerateRecommendationsAdjustedCosineFormula(-1);
		break;
	case'b':
		GenerateRecommendationsAdjustedCosineFormula();
		break;
	case'c':
		Index();
		break;
	case'd':
		exit(0);
	default:
	{
		cout << "Invalid Input";
		delayer(1000);
		GenerateRecommendationsAdjustedCosineFormula();
		break;
	}
	}
}

void HomeController::RateMovie()
{
	clear_screen();
	Review review{};
	bool ModelState = true;
	bool Saved = false;
	HomeView::RateMovie();
	input(review.UserId);
	HomeView::RateMovie(true);
	input(review.MovieId);
	HomeView::RateMovie(false, true);
	input(review.Score);
	HomeView::RateMovie(false, false, true);
	string save;
	input(save);
	if (save == "Y" || save == "y")
	{
		Saved = true;
	}
	if (Saved)
	{
		if (!_reviewService.isUserExist(review.UserId))
		{
			ModelState = false;
			changeTextColor(1);
			cout << "\n  This User id doesn't exits;";
			changeTextColor(0);
		}
		if (!movieService.isMovieExist(review.MovieId))
		{
			ModelState = false;
			changeTextColor(1);
			cout << "\n  This Movie id doesn't exits;";
			changeTextColor(0);
		}
		if (review.Score < 0 || review.Score>5)
		{
			ModelState = false;
			changeTextColor(1);
			cout << "\n  This rating is not valid.(Only between 1 to 5)";
			changeTextColor(0);
		}
		if (ModelState)
		{
			_reviewService.AddReview(review);
		}
	}
	HomeView::RateMovie(false, false, false, true);
	char choice;
	cin >> choice;
	switch (choice)
	{
	case 'r':
		return RateMovie();
	case 'm':
		return Index();
	case'q':
		exit(0);
	default:
	{
		string str;
		getline(cin, str);
		changeTextColor(1);
		cout << " Invalid Input.... Redirecting to MainMenu";
		delayer(1000);
		changeTextColor(0);
		return Index();
	}
	}

}



void HomeController::PopularMovies(bool popular, bool ModelStateError)
{
	if (!ModelStateError)
	{
		clear_screen();
		vector<Recommendation> movies;
		if (popular)
		{
			movies = ReviewService::MostPopularMovies();
			HomeView::PopularMovies(movies, true);
		}
		else
		{
			movies = ReviewService::MostRatedMovies();
			HomeView::PopularMovies(movies);
		}

	}
	string choice;
	while (choice != "m" || choice != "q")
	{
		cin >> choice;
		if (choice == "m")
			Index();
		else if (choice == "q")
		{
			exit(0);
		}
		else
		{
			if (popular)
			{
				PopularMovies(true);
			}
			else
			{
				PopularMovies();
			}
		}
	}
}
