#include "HomeController.h"
#include "ReviewService.h"

int main()
{
	ReviewService a;
	a.PredictUserReviewsAdjustedFormula(1);
	ReviewService::GetUsersAverageScore(1);
	HomeController::Index();
	system("pause");
}
