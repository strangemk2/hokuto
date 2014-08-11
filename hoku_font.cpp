#include "hoku_font.hpp"

#include "bitmap_image.hpp"

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
