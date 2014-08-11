#pragma once

#include <vector>
#include <string>

#include "hoku_matching.hpp"

class glyph
{
	private:
		unsigned int _weight = 0;

		unsigned int _width;
		unsigned int _height;

		vector<unsigned char> _data;

		void _calculate_weight();

		unsigned char _get_point(unsigned int x, unsigned int y) const;

	public:
		glyph(unsigned int width, unsigned int height):
			_width(width),
			_height(height)
		{
			_data.resize(width * height);
		}

		operator bool() const
		{
			return get_weight();
		}

		void set_point(unsigned int x, unsigned int y);
		unsigned int get_weight() const;

		bool save_bmp(const string &filename);

		void get_pointset(point_set &pset) const;
};

class font_pattern : public glyph
{
	private:
		unsigned char _ch = 0;

	public:
		constexpr static int WEIGHT_THREASHOLD = 10;

		font_pattern(unsigned int width, unsigned int height):
			glyph(width, height)
		{}

		unsigned char charactor() const
		{
			return _ch;
		}
		void set_charactor(unsigned char ch)
		{
			_ch = ch;
		}
};
