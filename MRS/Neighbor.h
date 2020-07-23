#pragma once
class Neighbor
{
public :
	Neighbor();
	Neighbor(int first, double s)
	{
		NeighborId = first;
		Score = s;
	}
	int NeighborId;
	double Score;
};

