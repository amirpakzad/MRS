#include "ReviewService.h"
#include <cmath>
#include <fstream>
#include <vector>
#include "MovieService.h"
#include "Review.h"
using namespace std;
MovieService _movieService;

static vector<Review> reviews;

vector<Review> ReviewService::GetReviews(bool reset)
{
	if (reviews.empty() || reset)
	{
		ifstream my_file("Ratings.txt", ios::in);
		if (open_file(my_file))
		{
			Review review{};
			while (!my_file.eof())
			{
				my_file >> review.UserId;
				my_file >> review.MovieId;
				my_file >> review.Score;
				reviews.push_back(review);
			}
			my_file.close();
		}
	}
	return reviews;
}


void ReviewService::AddReview(Review review)
{
	bool ReviewExist = false;
	if (reviews.empty())
	{
		GetReviews();
	}
	for (int i = 0; i < static_cast<int>(reviews.size()); i++)
	{
		if (reviews[i].MovieId == review.MovieId && reviews[i].UserId == review.UserId)
		{
			ReviewExist = true;
			reviews.at(i) = review;
			break;
		}
	}
	if (ReviewExist)
	{
		UpdateReviews();
	}
	else
	{
		ofstream my_file("Ratings.txt", ios::app);
		if (open_file(my_file))
		{
			my_file <<'\n' <<review.UserId << '\t' << review.MovieId << '\t' << review.Score;
		}
		my_file.close();
		reviews.push_back(review);
	}
}

vector<Review> ReviewService::GetUserReviews(int userId) const
{
	if (reviews.empty())
		GetReviews();
	vector<Review> userReviews;
	for (size_t i = 0; i < reviews.size(); i++)
	{
		if (reviews[i].UserId == userId)
		{
			userReviews.push_back(reviews[i]);
		}
	}
	return userReviews;
}

bool ReviewService::isUserExist(int userId) const
{
	if (reviews.empty())
		GetReviews();
	for (Review item : reviews)
	{
		if (item.UserId == userId)
		{
			return true;
		}
	}
	return false;
}

double ReviewService::GetSimilarityBetweenTwoUsers(int userId1, int userId2) const
{
	vector<Review> userList1 = GetUserReviews(userId1);
	vector<Review> userList2 = GetUserReviews(userId2);
	vector<double> scores;
	vector<double> firstUserReviews;
	vector<double> secondUserReviews;
	for (Review item : userList1)
	{
		for (Review sub : userList2)
		{
			if (item.MovieId == sub.MovieId)
			{
				double a =  pow(item.Score,2);
				double b = pow(sub.Score, 2);
				double score = (item.Score* sub.Score);
				scores.push_back(score);
				firstUserReviews.push_back(a);
				secondUserReviews.push_back(b);
			}
		}
	}
	double totalScore = 0;
	double a1 = 0;
	double a2 = 0;

	for (auto t : scores)
	{
		totalScore = t + totalScore;
	}
	for (auto t : firstUserReviews)
	{
		a1 = t + a1;
	}
	for (auto t : secondUserReviews)
	{
		a2 = t + a2;
	}

	double i = totalScore / (sqrt(a1) * sqrt(a2));
	return i;
}

double ReviewService::GetUserVotesForSpecificMovie(int userId, int movieId)
{
	double score = -1;
	for (Review item : reviews)
	{
		if (item.UserId == userId && item.MovieId == movieId)
		{
			score = item.Score;
			break;
		}
	}
	return score;
}

vector<int> ReviewService::GetUsers() const
{
	vector<int> users;
	int userId;

	const int j = find_last_line("Ratings.txt");
	ifstream my_file("Ratings.txt", ios::in);
	if (open_file(my_file))
	{
		string temp;
		for (int i = 0; i < j; i++)
		{
			bool userExist = false;
			my_file >> userId;
			getline(my_file, temp);
			for (int item : users)
			{
				if (userId == item)
				{
					userExist = true;
					break;
				}
			}
			if (!userExist)
			{
				users.push_back(userId);
			}
		}
		my_file.close();
	}
	return users;
}

vector<Neighbor> ReviewService::OrderByDescending(vector<Neighbor> Neighbors)
{
	vector<Neighbor> result;
	if (Neighbors.size() <= 1)
		return Neighbors;
	vector<Neighbor> left, right;
	int middle = ((int)Neighbors.size() + 1) / 2;

	for (int i = 0; i < middle; i++)
	{
		left.push_back(Neighbors[i]);
	}

	for (int i = middle; i < (int)Neighbors.size(); i++)
	{
		right.push_back(Neighbors[i]);;
	}

	left = OrderByDescending(left);
	right = OrderByDescending(right);
	result = Sort(left, right);

	return result;
}

vector<Neighbor> ReviewService::Sort(vector<Neighbor> left, vector<Neighbor> right)
{
	vector<Neighbor> result;

	while (static_cast<int>(left.size()) > 0 || static_cast<int>(right.size()) > 0)
	{
		if (static_cast<int>(left.size()) > 0 && static_cast<int>(right.size()) > 0)
		{
			if (static_cast<double>(left.at(0).Score) >= static_cast<double>(right.at(0).Score))
			{
				Neighbor neighbor = Neighbor(left.at(0).NeighborId, left.at(0).Score);
				result.push_back(neighbor);
				left.erase(left.begin());
			}
			else {
				Neighbor neighbor = Neighbor(right.at(0).NeighborId, right.at(0).Score);
				result.push_back(neighbor);
				right.erase(right.begin());
			}
		}
		else if (static_cast<int>(left.size()) > 0)
		{
			for (int i = 0; i < static_cast<int>(left.size()); i++)
			{
				result.push_back(left[i]);
			}
			break;
		}
		else if (static_cast<int>(right.size()) > 0)
		{
			for (int i = 0; i < static_cast<int>(right.size()); i++)
			{
				result.push_back(right[i]);
			}
			break;
		}
	}

	return result;
}


vector<Recommendation> ReviewService::PredictUserReviews(int userId, int count)
{
	MovieService a;
	vector<Neighbor> predictedReviews;
	vector<Neighbor> neighborsList = GetUserNeighbors(userId);
	vector<Movie> moviesList = a.GetNotReviewedMovies(userId);
	if (count == -1)
		count = moviesList.size();

	for (const auto& sub : moviesList)
	{
		double similarityScore = 0;
		double a1 = 0;
		double a2 = 0;
		vector<double> scores1;
		vector<double> scores2;
		for (auto item : neighborsList)
		{
			double neighborScoreForMovie =
				GetUserVotesForSpecificMovie(item.NeighborId, ToInt(sub.MovieId));
			if (static_cast<int>(neighborScoreForMovie) != -1)
			{
				similarityScore = item.Score;
				scores1.push_back(neighborScoreForMovie * similarityScore);
				scores2.push_back(similarityScore);
			}
		}
		for (auto sub2 : scores1)
		{
			a1 = a1 + sub2;
		}
		for (auto sub3 : scores2)
		{
			a2 = a2 + sub3;
		}
		Neighbor a(ToInt(sub.MovieId), a1 / (a2));
		predictedReviews.push_back(a);
	}
	predictedReviews = OrderByDescending(predictedReviews);
	predictedReviews.resize(count);

	vector<Recommendation> recommendations = FindMoviesById(predictedReviews, count);
	return recommendations;
}

vector<Recommendation> ReviewService::PredictUserReviewsAdjustedFormula(int userId, int count)
{
	MovieService a;
	vector<Neighbor> predictedReviews;
	vector<Neighbor> neighborsList = GetUserNeighborsByAdjustedCosineFormula(userId);
	vector<Movie> moviesList = a.GetNotReviewedMovies(userId);
	if (count == -1)
		count = moviesList.size();

	for (const auto& sub : moviesList)
	{
		double similarityScore = 0;
		double a1 = 0;
		double a2 = 0;
		vector<double> scores1;
		vector<double> scores2;
		for (auto item : neighborsList)
		{
			double neighborScoreForMovie =
				GetUserVotesForSpecificMovie(item.NeighborId, ToInt(sub.MovieId));
			if (static_cast<int>(neighborScoreForMovie) != -1)
			{
				similarityScore = item.Score;
				scores1.push_back(neighborScoreForMovie * similarityScore);
				scores2.push_back(similarityScore);
			}
		}
		for (auto sub2 : scores1)
		{
			a1 = a1 + sub2;
		}
		for (auto sub3 : scores2)
		{
			a2 = a2 + sub3;
		}
		double a3 = a1 / (a2);
		if(a3>0)
		{
			Neighbor a(ToInt(sub.MovieId), a3);
			predictedReviews.push_back(a);
		}
	}
	predictedReviews = OrderByDescending(predictedReviews);
	predictedReviews.resize(count);

	vector<Recommendation> recommendations = FindMoviesById(predictedReviews, count);
	return recommendations;
}

double ReviewService::AdjustedCosineFormula(int userId1, int userId2) const
{
	vector<Review> userList1 = GetUserReviews(userId1);
	vector<Review> userList2 = GetUserReviews(userId2);
	double user1Avg = GetUsersAverageScore(userId1);
	double user2Avg = GetUsersAverageScore(userId1);
	vector<double> scores;
	vector<double> firstUserReviews;
	vector<double> secondUserReviews;
	for (Review item : userList1)
	{
		for (Review sub : userList2)
		{
			if (item.MovieId == sub.MovieId)
			{
				double score = (item.Score-user1Avg) *(sub.Score-user2Avg);
				scores.push_back(score);
				firstUserReviews.push_back(pow((item.Score - user1Avg),2));
				secondUserReviews.push_back(pow((sub.Score - user2Avg),2));
			}
		}
	}
	double totalScore = 0;
	double a1 = 0;
	double a2 = 0;

	for (auto t : scores)
	{
		totalScore = t + totalScore;
	}
	for (auto t : firstUserReviews)
	{
		a1 = t + a1;
	}
	for (auto t : secondUserReviews)
	{
		a2 = t + a2;
	}

	double i = totalScore / (sqrt(a1+a2));
	return i;
}

void ReviewService::RemoveReviewByMovieId(int movieId) const
{
	if (reviews.empty())
		GetReviews();
	for (int i = 0; i < static_cast<int>(reviews.size()); i++)
	{
		if (reviews[i].MovieId == movieId)
		{
			reviews.erase(reviews.begin() + i);
		}
	}
	UpdateReviews();
}

void ReviewService::UpdateReviews() const
{
	if (reviews.empty())
		GetReviews();
	ofstream my_file("Ratings.txt", ios::out);
	if (open_file(my_file))
	{
		int back = reviews.size();
		for (int i = 0; i < static_cast<int>(reviews.size()); i++)
		{
			my_file << reviews[i].UserId << '\t' << reviews[i].MovieId << '\t' << reviews[i].Score;
			if (i != (static_cast<int>(reviews.size()) - 1))
				my_file << '\n';
		}
	}
	my_file.close();
}

vector<Recommendation> ReviewService::MostRatedMovies()
{
	ReviewService a;
	if (reviews.empty())
	{
		a.GetReviews();
	}
	vector<Neighbor> moviesList;
	for (Movie element : MovieService::GetMovies())
	{
		int count = 0;
		for (Review item : reviews)
		{
			if (item.MovieId == ToInt(element.MovieId))
			{
				count++;
			}
		}
		Neighbor movie = Neighbor(ToInt(element.MovieId), count);
		moviesList.push_back(movie);
	}
	moviesList = OrderByDescending(moviesList);
	moviesList.resize(5);
	vector<Recommendation> recommendations = FindMoviesById(moviesList, 5);
	return recommendations;
}

vector<Recommendation> ReviewService::MostPopularMovies()
{
	ReviewService a;
	if (reviews.empty())
	{
		a.GetReviews();
	}
	vector<Neighbor> moviesList;
	for (Movie element : MovieService::GetMovies())
	{
		double a1 = 0;
		vector<int> scores;
		int count = 0;
		for (Review item : reviews)
		{
			if (item.MovieId == ToInt(element.MovieId))
			{
				scores.push_back(item.Score);
			}
		}
		for (double sub1 : scores)
		{
			a1 += sub1;
		}
		Neighbor movie = Neighbor(ToInt(element.MovieId), a1 / (static_cast<int>(scores.size())));
		moviesList.push_back(movie);
	}
	moviesList = OrderByDescending(moviesList);
	moviesList.resize(5);
	vector<Recommendation> recommendations = FindMoviesById(moviesList, 5);
	return recommendations;
}

vector<Recommendation> ReviewService::FindMoviesById(vector<Neighbor> idsList, int count)
{
	vector<int> ids;
	for (auto m : idsList)
	{
		ids.push_back(m.NeighborId);
	}
	Movie movie;
	vector<Recommendation> recommendations;
	for (int i = 0; i < count; i++)
	{
		movie = MovieService::FindMovieById(ids[i]);
		if (movie.MovieName.size() > 25)
		{
			movie.MovieName.resize(25);
		}
		Recommendation r;
		r.similarityScore = idsList[i].Score;
		r.MovieName = movie.MovieName;
		r.MovieId = movie.MovieId;
		r.CreateYear = movie.CreateYear;
		recommendations.push_back(r);
	}

	return recommendations;
}

double ReviewService::GetUsersAverageScore(int userId)
{
	if (reviews.empty())
	{
		ReviewService a;
		a.GetReviews();
	}
	vector<double> userReviews;
	double averageScore = 0;
	for (Review item : reviews)
	{
		if (item.UserId == userId)
		{
			userReviews.push_back(item.Score);
		}
	}
	for (double sub : userReviews)
	{
		averageScore += sub;
	}
	averageScore = averageScore / (static_cast<int>(userReviews.size()));
	return averageScore;
}


vector<Neighbor> ReviewService::GetUserNeighbors(int userId) const
{
	vector<double> scores;
	vector<int> users = GetUsers();
	vector<Neighbor> neighborList;
	for (int item : users)
	{
		if (userId != item)
		{
			double score = GetSimilarityBetweenTwoUsers(userId, item);
			Neighbor neighbor = Neighbor(item, score);
			neighborList.push_back(neighbor);
		}
	}
	neighborList = OrderByDescending(neighborList);
	neighborList.resize(8);
	return neighborList;
}

vector<Neighbor> ReviewService::GetUserNeighborsByAdjustedCosineFormula(int userId) const
{
	vector<double> scores;
	vector<int> users = GetUsers();
	vector<Neighbor> neighborList;
	for (int item : users)
	{
		if (userId != item)
		{
			double score = AdjustedCosineFormula(userId, item);
			Neighbor neighbor = Neighbor(item, score);
			neighborList.push_back(neighbor);
		}
	}
	neighborList = OrderByDescending(neighborList);
	neighborList.resize(8);
	return neighborList;
}
