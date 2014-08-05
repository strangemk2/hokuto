#include <iostream>
#include <cstdlib>

#include "hoku1.hpp"

void usage(char *);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	string pic_filename = argv[1];
	string txt_filename = argv[2];

	hoku_screenshot scr = hoku_screenshot(pic_filename);
	if (!scr.init())
	{
		return 1;
	}

	char bmp_filename[20] = "hokua.bmp";
	while (glyph *gly = scr.get_glyph())
	{
		/*
		for (auto pattern : glyph_patterns)
		{
			if (gly->match(pattern))
			{
				cout << pattern.charactor();
			}
		}
		cout << " ";
		*/
		gly->save_bmp(bmp_filename);
		bmp_filename[4]++;

		delete (gly);
	}
	cout << endl;

	return 0;
}

void usage(char *program_name)
{
	cout << program_name << ": [pic] [txt]" << endl;
}

// class picture
picture *picture::get_picture(const string filename)
{
	picture *ret;

	string extension = filename.substr(filename.length() - 3);
	if (extension == "bmp")
	{
		ret = new bmp;
		if (!ret->init(filename))
		{
			return nullptr;
		}
	}
	else if (extension == "png")
	{
		ret = new png;
		if (!ret->init(filename))
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}

	return ret;
}

rgb picture::get_pixel(coordinate cord)
{
	return get_pixel(cord.x, cord.y);
}

// class png
png::~png()
{
	if (_fp) fclose(_fp);
	if (_png_ptr && _info_ptr)
		png_destroy_read_struct(&_png_ptr, &_info_ptr, png_infopp_NULL);
	if (_png_ptr && !_info_ptr)
		png_destroy_read_struct(&_png_ptr, png_infopp_NULL, png_infopp_NULL);
}

unsigned int png::height()
{
	return _info_ptr->height;
}

unsigned int png::width()
{
	return _info_ptr->width;
}

bool png::init(const string filename)
{
	unsigned int sig_read = 0;

	if ((_fp = fopen(filename.c_str(), "rb")) == NULL)
		return false;

	_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (_png_ptr == nullptr)
		return false;

	_info_ptr = png_create_info_struct(_png_ptr);
	if (_info_ptr == nullptr)
		return false;

	if (setjmp(png_jmpbuf(_png_ptr)))
		return false;

	png_init_io(_png_ptr, _fp);

	png_set_sig_bytes(_png_ptr, sig_read);

	png_read_png(_png_ptr, _info_ptr, PNG_TRANSFORM_STRIP_ALPHA, png_voidp_NULL);

	int color_type = _info_ptr->color_type;  
	int bit_depth = _info_ptr->pixel_depth;  
	if (color_type != 2 || bit_depth != 24)
		return false;

	_row_pointers = png_get_rows(_png_ptr, _info_ptr);
	if (_row_pointers == nullptr)
		return false;

	return true;
}

rgb png::get_pixel(unsigned int x, unsigned int y)
{
	rgb ret;
	unsigned int xx = x * 3;

	ret.r = _row_pointers[y][xx];
	ret.g = _row_pointers[y][xx+1];
	ret.b = _row_pointers[y][xx+2];
	return ret;
}

// class bmp
bmp::~bmp()
{
	if (_img) delete (_img);
}

unsigned int bmp::height()
{
	return _img->height();
}

unsigned int bmp::width()
{
	return _img->width();
}

bool bmp::init(const string filename)
{
	_img = new bitmap_image(filename);
	if (_img == nullptr)
		return false;
	return true;
}

rgb bmp::get_pixel(unsigned int x, unsigned int y)
{
	rgb ret;

	_img->get_pixel(x, y, ret.r, ret.g, ret.b);
	return ret;
}

// glyph
void glyph::_calculate_weight()
{
	for (unsigned char i : _data)
	{
		_weight_all += i;
	}
}

unsigned char glyph::get_point(unsigned int x, unsigned int y)
{
	return _data[y * _width + x];
}

void glyph::set_point(unsigned int x, unsigned int y)
{
	_data[y * _width + x] = 1;
}

bool glyph::match(const font_pattern &pattern)
{
	// check and generate _weight
	if (_weight_all == 0)
	{
		_calculate_weight();
	}

	if (abs(pattern.weight() - _weight_all) > WEIGHT_THREASHOLD)
	{
		return false;
	}

	return true;
}

bool glyph::save_bmp(const string &filename)
{
	bitmap_image img(_width, _height);

	img.clear(0xff);
	for (unsigned int x = 0; x < _width; ++x)
	{
		for (unsigned int y = 0; y < _height; ++y)
		{
			if (get_point(x, y))
			{
				img.set_pixel(x, y, 0x0, 0x0, 0x0);
			}
		}
	}
	img.save_image(filename);

	return true;
}

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

//coordinate hoku_screenshot::find_charactor()
//{
//	coordinate ret;
//	for (unsigned int x = _current_charactor.x; x < _textarea->width(); ++x)
//	{
//		for (unsigned int y = _current_charactor.y; y < _textarea->height(); ++y)
//		{
//			rgb c;
//			_textarea->get_pixel(x, y, c.r, c.g, c.b);
//			if (is_yellow(c))
//			{
//				_current_charactor.x = x;
//
//				ret.x = x;
//				ret.y = y;
//				return ret;
//			}
//		}
//	}
//	return ret;
//}
//
//void hoku_screenshot::proceed_characor()
//{
//	bool yellow_flag = false;
//	for (unsigned int x = _current_charactor.x; x < _textarea->width(); ++x)
//	{
//		for (unsigned int y = 0; y < _textarea->height(); ++y)
//		{
//			rgb c;
//			_textarea->get_pixel(x, y, c.r, c.g, c.b);
//			if (is_yellow(c))
//			{
//				yellow_flag = true;
//				break;
//			}
//		}
//		if (yellow_flag)
//		{
//			yellow_flag = false;
//		}
//		else
//		{
//			_current_charactor.x = x;
//			break;
//		}
//	}
//}
