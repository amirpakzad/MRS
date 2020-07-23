#pragma once
#include <vector>
#include "Movie.h"
#include "Neighbor.h"
#include "Recommendation.h"
#include "ServiceBase.h"

class MovieService :public ServiceBase
{
public :
	//Create,Read,Update,Delete
	static vector<Movie> GetMovies(bool Reset = false);
    bool AddMovie(const string& movieName,const string& year) const;
	void RemoveMovie(int movieId);
	void RemoveMovie(string movieName) const;
	void UpdateMovies() const;
	//Find
	static Movie FindMovieById(int movieId);
	static int FindId();
	static vector<Recommendation> FindMoviesById(vector<Neighbor> idsList, int count);
	//Check
    bool isMovieExist(string movie_name);
    bool isMovieExist(int movie_id);
	
	static vector<Movie> GetNotReviewedMovies(int userId);
};

