#include "hoku_screenshot.hpp"
#include "hoku_misc.hpp"

// class hoku_screenshot
hoku_screenshot::~hoku_screenshot()
{
	if (_pic) delete(_pic);
	if (_textarea) delete(_textarea);
}

bool hoku_screenshot::init()
{
	_pic = picture::get_picture(_pic_filename);
	if (_pic == nullptr)
		return false;

	_textarea = this->find_textarea();
	if (_textarea == nullptr)
		return false;

	return true;
}

bitmap_image *hoku_screenshot::find_textarea()
{
	// find text area coordinates.
	coordinate left_up, right_down;
	for (unsigned int x = 0; x < _pic->width(); ++x)
	{
		for (unsigned int y = 0; y < _pic->height(); ++y)
		{
			if (is_backgroud_red(_pic->get_pixel(x, y)))
			{
				if (!left_up)
				{
					if (is_real_red(_pic->get_pixel(x-1, y)))
					{
						left_up.x = x;
						left_up.y = y;
					}
				}
				else
				{
					if (is_real_red(_pic->get_pixel(x+1,y)))
					{
						right_down.x = x;
						right_down.y = y;
					}
				}
			}
		}
	}
	if (!left_up || !right_down)
	{
		return nullptr;
	}

	// copy to local bitmap
	bitmap_image *img = new bitmap_image(right_down.x - left_up.x, right_down.y - left_up.y);
	if (!img)
	{
		return nullptr;
	}

	for (unsigned int x = left_up.x; x < right_down.x; ++x)
	{
		for (unsigned int y = left_up.y; y < right_down.y; ++y)
		{
			rgb ret = _pic->get_pixel(x, y);
			img->set_pixel(x - left_up.x, y - left_up.y, ret.r, ret.g, ret.b);
		}
	}
	return img;
}

glyph *hoku_screenshot::get_glyph()
{
	unsigned int up = 0, down = 0, left = 0, right = 0;
	bool yellow_flag;

	for (unsigned int x = _current_charactor.x; x < _textarea->width(); ++x)
	{
		for (unsigned int y = _current_charactor.y; y < _textarea->height(); ++y)
		{
			rgb c;
			_textarea->get_pixel(x, y, c.r, c.g, c.b);
			if (is_yellow(c))
			{
				left = x;
				break;
			}
		}
		if (left)
			break;
	}
	if (left == 0)
	{
		return nullptr;
	}

	for (unsigned int x = left; x < _textarea->width(); ++x)
	{
		for (unsigned int y = 0; y < _textarea->height(); ++y)
		{
			rgb c;
			_textarea->get_pixel(x, y, c.r, c.g, c.b);
			if (is_yellow(c))
			{
				yellow_flag = true;
				break;
			}
		}
		if (yellow_flag)
		{
			yellow_flag = false;
		}
		else
		{
			_current_charactor.x = x;
			right = x;
			break;
		}
	}
	yellow_flag = false;
	if (right <= left)
	{
		return nullptr;
	}

	for (unsigned int y = 0; y < _textarea->height(); ++y)
	{
		for (unsigned int x = left; x < right; ++x)
		{
			rgb c;
			_textarea->get_pixel(x, y, c.r, c.g, c.b);
			if (is_yellow(c))
			{
				up = y;
				break;
			}
		}
		if (up)
			break;
	}
	if (up == 0)
	{
		return nullptr;
	}

	for (unsigned int y = up; y < _textarea->height(); ++y)
	{
		for (unsigned int x = left; x < right; ++x)
		{
			rgb c;
			_textarea->get_pixel(x, y, c.r, c.g, c.b);
			if (is_yellow(c))
			{
				yellow_flag = true;
				break;
			}
		}
		if (yellow_flag)
		{
			yellow_flag = false;
		}
		else
		{
			down = y;
			break;
		}
	}
	yellow_flag = false;
	if (down <= up)
	{
		return nullptr;
	}

	glyph *ret = new glyph(right - left, down - up);

#ifdef SPECIAL_PATCH
	// special patch for fonts "!"
	if (((right - left) == 2 || (right - left) == 3) && (down - up) == 10)
	{
		rgb c;
		_textarea->get_pixel(left+1, down-2, c.r, c.g, c.b);

		if (c.r < 190 || c.g < 190 || c.b > 30)
		{
			ret->set_point(0, 0);
			return ret;
		}
	}
	// end patch
#endif

	for (unsigned int x = left; x < right; ++x)
	{
		for (unsigned int y = up; y < down; ++y)
		{
			rgb c;
			_textarea->get_pixel(x, y, c.r, c.g, c.b);

			if (is_yellow(c))
			{
				ret->set_point(x - left, y - up);
			}
		}
	}

	return ret;
}
