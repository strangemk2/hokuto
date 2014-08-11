#pragma once

using namespace std;

typedef unsigned char color;

struct rgb
{
	color r;
	color g;
	color b;
};

class coordinate
{
	public:
		unsigned int x;
		unsigned int y;

		coordinate():
			x(0),
			y(0)
		{}

		operator bool() const
		{
			return (x + y);
		}
};
