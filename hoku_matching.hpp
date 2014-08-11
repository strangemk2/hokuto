#pragma once

#include <vector>

#include "hoku_common.hpp"

class point
{
	public:
		unsigned int x = 0;
		unsigned int y = 0;

		point(unsigned int a, unsigned int b):
			x(a),
			y(b)
		{}
};
typedef vector<point> point_set;

class matching
{
	private:
		static constexpr float FLOAT_THREASHOLD = 0.1f;
		static constexpr int MAX_DIMENSION = 15;

		static bool threashold_equal(float a, float b);

		float (*_distance_cache)[MAX_DIMENSION][MAX_DIMENSION][MAX_DIMENSION];

		float distance_2d(const point &a, const point &b);

		matching();
		~matching();

		static matching _instance;

	public:
		static matching *instance()
		{
			return &_instance;
		}

		float hausdorff_distance_2d(const point_set &a_set, const point_set &b_set);
};
