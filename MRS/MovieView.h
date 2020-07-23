#pragma once

#include <vector>


#include "Movie.h"
#include "ViewBase.h"

class MovieView : public ViewBase
{
public :
	
	static void DisplayMovie(const vector<Movie>& movies);
	static void AddRemoveSection();
	static void RemoveMovie(bool ModelState=false,bool success=false);
	static void RemoveMovie(int movieId);
	static void RemoveMovie(const string& movieName);
	static void AddMovie(bool yearSection=false, bool section=false, bool saved=false, bool ModelState=false, bool result=false, bool section3 = false,bool lastSection = false);
	
};

