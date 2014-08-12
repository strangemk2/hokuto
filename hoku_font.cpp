#include <sstream>
#include <cstring>
#include <dirent.h>

#include "bitmap_image.hpp"

#include "hoku_font.hpp"
#include "hoku_picture.hpp"
#include "hoku_misc.hpp"

#ifdef PREDEFINED_FONT_DATA
#include "hoku_font_data.hpp"
#endif

// glyph
void glyph::_calculate_weight()
{
	for (unsigned char i : _data)
	{
		_weight += i;
	}
}

unsigned char glyph::_get_point(unsigned int x, unsigned int y) const
{
	return _data[y * _width + x];
}

void glyph::set_point(unsigned int x, unsigned int y)
{
	_data[y * _width + x] = 1;
	_weight++;
}

unsigned int glyph::get_weight() const
{
	return _weight;
}

bool glyph::save_bmp(const string &filename)
{
	bitmap_image img(_width, _height);

	img.clear(0xff);
	for (unsigned int x = 0; x < _width; ++x)
	{
		for (unsigned int y = 0; y < _height; ++y)
		{
			if (_get_point(x, y))
			{
				img.set_pixel(x, y, 0x0, 0x0, 0x0);
			}
		}
	}
	img.save_image(filename);

	return true;
}

void glyph::get_pointset(point_set &pset) const
{
	for (unsigned int x = 0; x < _width; ++x)
	{
		for (unsigned int y = 0; y < _height; ++y)
		{
			if (_get_point(x, y))
			{
				point p(x, y);
				pset.push_back(p);
			}
		}
	}
}

string glyph::dump_header()
{
	ostringstream oss;
	oss << _width << ", " << _height << ", " << _weight << ", {";
	for (auto ch : _data)
	{
		oss << static_cast<int>(ch) << ",";
	}
	oss << "}";

	string ret = oss.str();
	return ret;
}

string font_pattern::dump_header()
{
	ostringstream oss;
	oss << "'" <<  _ch << "'" << ", ";
	string ret = oss.str();
	ret.append(glyph::dump_header());
	return ret;
}

bool load_font_patterns(const string &pattern_folder, vector<font_pattern> &glyph_patterns)
{
#ifdef PREDEFINED_FONT_DATA
	glyph_patterns = predefined_patterns;
#else
	DIR *dp = nullptr;
	dp = opendir(pattern_folder.c_str());
	if (!dp)
	{
		return false;
	}

	struct dirent *dir = nullptr;
	while ((dir = readdir(dp)))
	{
		if (strstr(dir->d_name, ".bmp") == (dir->d_name + 5))
		{
			string font_filename = pattern_folder + dir->d_name;
			picture *pic = picture::get_picture(font_filename);

			font_pattern f(pic->width(), pic->height());
			for (unsigned int y = 0; y < pic->height(); ++y)
			{
				for (unsigned int x = 0; x < pic->width(); ++x)
				{
					rgb c = pic->get_pixel(x, y);
					if (is_glyph_black(c))
					{
						f.set_point(x, y);
					}
				}
			}
			f.set_charactor(dir->d_name[4]);
			glyph_patterns.push_back(f);

			delete (pic);
		}
		else
		{
			// warning
		}
	}
	closedir(dp);
#endif

	return true;
}

string dump_font_patterns(vector<font_pattern> &glyph_patterns)
{
	string ret;
	// header
	ret.append("#pragma once\n");
	ret.append("\n");
	ret.append("vector<font_pattern> predefined_patterns = {\n");
	ret.append("	// {ch, width, height, weight, {data1, data2, ..., datax}},\n");

	for (auto glyph : glyph_patterns)
	{
		ret.append("\t{");
		ret.append(glyph.dump_header());
		ret.append("},\n");
	}

	// footer
	ret.append("};\n");

	return ret;
}
