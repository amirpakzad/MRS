#include "HomeView.h"
#include <iomanip>
#include <iostream>
#include "Recommendation.h"
using namespace std;
void HomeView::Index()
{
	cout << "\n";
	cout << "\t" << "\t" << "\t" << "MOVIE RECOMMENDATION SYSTEM" << "\n";
	cout << "\t" << "\t" << "********** " << "WELCOME TO THE MAIN MENU" << " **********" << "\n" << "\n";
	cout << " 1." << "  " << "Display movies" << "\n";
	cout << " 2." << "  " << "Display ratings" << "\n";
	cout << " 3." << "  " << "Display similarity between two users" << "\n";
	cout << " 4." << "  " << "Generate recommendations" << "\n";
	cout << " 5." << "  " << "Rate a movie" << "\n";
	cout << " 6." << "  " << "Add/Remove a movie" << "\n";
	cout << " 7." << "  " << "Generate Recommendation (Adjusted Cosine Similarity)" << "\n";
	cout << " 8." << "  " << "Most Rated Movies" << "\n";
	cout << " 9." << "  " << "Most Popular Movies" << "\n";
	cout << " 10." << " " << "Exit" << "\n";
	cout << "\n" << "\n" << "\n";
}

void HomeView::DisplayRatings()
{
	cout << "\n  " << string(20, '-');
	cout << "\n  " << "Display Ratings \n";
	cout << "  " << string(20, '-') << string(10, ' ') << "\n" << "\n";
	cout << "  " << "Enter User Id : ";
}


void HomeView::DisplayRatings(const vector<Review>& reviews, int userId, bool ModelState)
{
	if (ModelState)
	{
		cerr << "This User Id doesn't exist . Try Again";
	}
	else
	{
		cout << "\n\n  " << "Ratings of User " << userId << " are : \n\n";
		cout << "  " << "Movie Id" << "\t" << "Rating\n";
		cout << "  " << "--------" << "\t" << "------" << "\n";
		for (const Review temp : reviews)
		{
			cout << "  " << temp.MovieId << setw(11) << std::left << '\t' << temp.Score << endl;
			delayer(50);
		}
		cout << "\n  Press 'r' to retry ,'m' to Main menu , and 'q' to quit  : ";
	}
}

void HomeView::DisplaySimilarityBetweenTwoUsers(bool first, bool ModelState)
{
	if (!first && !ModelState)
	{
		cout << "\n  " << string(39, '-');
		cout << "\n  " << "Display Similarity between two users \n";
		cout << "  " << string(39, '-') << string(10, ' ') << "\n" << "\n";
		cout << "  " << "Enter first User Id : ";
	}
	else if (first)
	{
		cout << "\n\n  " << "Enter second User Id : ";
	}
	else
	{
		cout << "  " << "\nThis userid doesn't exist.TryAgain ";
	}
}

void HomeView::DisplaySimilarityBetweenTwoUsers(int userId1, int userId2, double score)
{
	printf("\n\n  Similarity between user %i and user %i is: %f\n", userId1, userId2, score);
	cout << "\n  Press 'r' to retry ,'m' to Main menu , and 'q' to quit  : ";
}

void HomeView::GenerateRecommendations(int userId, const vector<Recommendation>& recommendations, bool all)
{
	string amount = "Top 5 Recommendations for user ";
	if (all)
		amount = "Predictions of unseen movies by user ";
	cout << "\n  " << amount <<userId << " : \n\n";
	cout << "  Id" << "\tMovie Name" << "\t\t\t\tYear" << "\tPredicted Rating" << "\n";
	cout << "  --" << "\t----------" << "\t\t\t\t----" << "\t----------------" << "\n";
	for (const Recommendation& temp : recommendations)
	{
		string str = temp.MovieName;
		if (temp.similarityScore != 0)
			cout << "  " << temp.MovieId << '\t' << setw(35) << std::left << str << '\t' << temp.CreateYear << "\t      " <<setprecision(2)<<fixed<<temp.similarityScore<< endl;
		else
			cout << "  " << temp.MovieId << '\t' << setw(35) << std::left << str << '\t' << temp.CreateYear << "\t    " << "Not Predictable" << endl;
		delayer(50);
	}
	cout << "\n " << string(4, '=') << "What do you want to do?" << string(4, '=') << '\n' << '\n';
	cout << " " << "a.Display All Predictions for this user " << '\n';
	cout << " " << "b.Retry " << '\n';
	cout << " " << "c.back to main menu " << '\n';
	cout << " " << "d.Exit " << '\n' << '\n';
	cout << " " << "Your Choice? : ";
}

void HomeView::GenerateRecommendations(bool ModelState)
{
	if (!ModelState)
	{
		cout << "\n  " << string(24, '-');
		cout << "\n  " << "Generate Recommendations \n";
		cout << "  " << string(24, '-') << string(10, ' ') << "\n" << "\n";
		cout << "  " << "Enter User Id : ";
	}
	else
	{
		cout << "  " << "\nThis userid doesn't exist.TryAgain ";
	}
}

void HomeView::RateMovie(bool movieId, bool rating, bool save, bool section)
{

	if (movieId)
	{
		cout << " " << "Movie Id:";
	}
	else if (rating)
	{
		cout << " " << "Rating:";
	}
	else if (save)
	{
		cout << " " << string(15, '=') << '\n';
		cout << " " << "Do You Want To Save ? : ";
	}
	else if (section)
	{
		cout << "\n\n" << " " << "Press 'r' to retry, 'p' to Previous ,'m' to Main menu , and 'q' to Quit";
		cout << "\n " << "Your Choice? : ";
	}
	else
	{
		cout << " " << string(10, '-') << '\n';
		cout << " " << "Rate a movie" << '\n';
		cout << " " << string(10, '-') << "\n" << "\n";
		cout << " " << "Enter Information Below" << '\n';
		cout << " " << string(15, '=') << '\n';
		cout << " " << "User Id:";
	}
}

void HomeView::PopularMovies(const vector<Recommendation>& movies, bool popular)
{
	string str = "\tTotal Votes";
	if (popular)
	{
		str = "\tTotal Score";
	}
	cout << "\n  " << string(24, '-');
	if (popular)
	{
		cout << "\n  Most Popular Movies " << " \n";
	}
	else
	{
		cout << "\n  Most Rated Movies " << " \n";
	}
	cout << "  " << string(24, '-') << string(10, ' ') << "\n" << "\n";
	cout << "  Id" << "\tMovie Name" << "\t\t\t\tYear" << str << "\n";
	cout << "  --" << "\t----------" << "\t\t\t\t----" << "\t-----------" << "\n";
	for (const Recommendation& temp : movies)
	{
		string str = temp.MovieName;
		if (temp.similarityScore != 0)
			cout << "  " << temp.MovieId << '\t' << setw(35) << std::left << str << '\t' << temp.CreateYear << "\t  " << temp.similarityScore << endl;
		else
			cout << "  " << temp.MovieId << '\t' << setw(35) << std::left << str << '\t' << temp.CreateYear << "\t    " << "Not Predictable" << endl;
	}
	cout << "\n\n" << " " << "Press 'm' to Main menu or 'q' to Quit";
	cout << "\n " << "Your Choice? : ";
}


