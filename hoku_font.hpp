#pragma once

#include <vector>
#include <string>

#include "hoku_matching.hpp"

class glyph
{
	private:
		unsigned int _width;
		unsigned int _height;

		unsigned int _weight = 0;

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

		glyph(unsigned int width, unsigned int height, unsigned int weight, vector<unsigned char> data):
			_width(width),
			_height(height),
			_weight(weight),
			_data(data)
		{}

		operator bool() const
		{
			return get_weight();
		}

		void set_point(unsigned int x, unsigned int y);
		unsigned int get_weight() const;

		bool save_bmp(const string &filename);

		void get_pointset(point_set &pset) const;

		string dump_header();
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

		font_pattern(unsigned char ch,
				unsigned int width, unsigned int height, unsigned int weight, vector<unsigned char> data):
			glyph(width, height, weight, data),
			_ch(ch)
		{}

		unsigned char charactor() const
		{
			return _ch;
		}
		void set_charactor(unsigned char ch)
		{
			_ch = ch;
		}
		string dump_header();
};

bool load_font_patterns(const string &, vector<font_pattern> &);
string dump_font_patterns(vector<font_pattern> &);
