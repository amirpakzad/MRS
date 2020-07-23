#pragma once
#include <vector>
#include "Movie.h"
#include "Neighbor.h"
#include "Recommendation.h"
#include "Review.h"
#include "ServiceBase.h"


class ReviewService :public ServiceBase
{
public:
    // Create,Read,Update,Delete Reviews
    static vector<Review> GetReviews(bool reset = false);
    void AddReview(Review review);
    vector<Review> GetUserReviews(int userId) const;
    void RemoveReviewByMovieId(int movieId) const;
    void UpdateReviews() const;
	// User
    bool isUserExist(int userId) const;
    static double GetUserVotesForSpecificMovie(int userId, int movieId);
    vector<int> GetUsers() const;
    // Similarity
    double GetSimilarityBetweenTwoUsers(int userId1, int userId2) const;
    double AdjustedCosineFormula(int userId1, int userId2) const;
    static double GetUsersAverageScore(int userId);
    // Neighbors
    vector<Neighbor> GetUserNeighbors(int userId) const;
    vector<Neighbor> GetUserNeighborsByAdjustedCosineFormula(int userId) const;
    //Order & Sort
    static vector<Neighbor> OrderByDescending(vector<Neighbor> Neighbors);
    static vector<Neighbor> Sort(vector<Neighbor> left, vector<Neighbor> right);
    //Prediction
    vector<Recommendation> PredictUserReviews(int userId, int count = -1);
    vector<Recommendation> PredictUserReviewsAdjustedFormula(int userId, int count = -1);
	//Movie
    static vector<Recommendation> MostRatedMovies();
    static vector<Recommendation> MostPopularMovies();
    static vector<Recommendation> FindMoviesById(vector<Neighbor> idsList, int count);
};
