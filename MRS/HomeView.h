#pragma once
#include <vector>
#include "Recommendation.h"
#include "Review.h"
#include "ViewBase.h"
using namespace std;
class HomeView : public ViewBase
{
public:
	static void Index();
	static void DisplayRatings();
	static void DisplayRatings(const vector<Review>& reviews, int userId, bool ModelState = false);
	static void DisplaySimilarityBetweenTwoUsers(bool first=false,bool ModelState=false);
	static void DisplaySimilarityBetweenTwoUsers(int userId1,int userId2,double score);
	static void GenerateRecommendations(int userId, const vector<Recommendation>& recommendations, bool all = false);
	static void GenerateRecommendations(bool ModelState=false);
	static void RateMovie(bool movieId = false, bool rating = false, bool save = false, bool section = false);
	static void PopularMovies(const vector<Recommendation>& movies,bool popular=false);
};

