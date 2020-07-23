#pragma once
#include "ControllerBase.h"
#include "MovieService.h"

class MovieController : public ControllerBase
{
public:
	MovieController(MovieService movieService);
	static void DisplayMovies();
	static void AddMovie();
	static void AddRemoveSection();
	static void RemoveMovie();
};

