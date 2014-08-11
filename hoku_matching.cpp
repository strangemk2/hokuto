#include <algorithm>

#include "hoku_matching.hpp"

// matching
matching::matching()
{
	_distance_cache = new float[MAX_DIMENSION][MAX_DIMENSION][MAX_DIMENSION][MAX_DIMENSION];
	char *t = reinterpret_cast<char *>(_distance_cache);
	fill_n(t, MAX_DIMENSION*MAX_DIMENSION*MAX_DIMENSION*MAX_DIMENSION*sizeof(float), 0);
}

matching::~matching()
{
	delete [](_distance_cache);
}

bool matching::threashold_equal(float a, float b)
{
	if (abs(a - b) < FLOAT_THREASHOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float matching::distance_2d(const point &a, const point &b)
{
	if (_distance_cache[a.x][a.y][b.x][b.y] == 0.0f)
	{
		 _distance_cache[a.x][a.y][b.x][b.y] =
			 sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	return _distance_cache[a.x][a.y][b.x][b.y];
}

// hausdorff distance and matching point percentage optimize
float matching::hausdorff_distance_2d(const point_set &a_set, const point_set &b_set)
{
	float hausdorff_distance = 0.0f;
	float match = 0.0f;
	for (auto a : a_set)
	{
		float min_distance = numeric_limits<float>::max();
		for (auto b : b_set)
		{
			float d = distance_2d(a, b);
			if (min_distance > d)
			{
				min_distance = d;
			}

		}
		if (threashold_equal(min_distance, 0.0f))
		{
			match += 1.0f;
		}
		if (min_distance > hausdorff_distance)
		{
			hausdorff_distance = min_distance;
		}
	}
	return hausdorff_distance * b_set.size() / match;
	//return hausdorff_distance;
}
