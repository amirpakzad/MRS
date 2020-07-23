#pragma once
#include "ControllerBase.h"
class HomeController : public ControllerBase
{
public:
    static void Index();
	static void DisplayRatings();
	static void DisplaySimilarityBetweenTwoUsers();
	static void GenerateRecommendations(int count=5);
	static void GenerateRecommendationsAdjustedCosineFormula(int count=5);
	static void RateMovie();
	static void PopularMovies(bool popular = false,bool ModelStateError = false);
};