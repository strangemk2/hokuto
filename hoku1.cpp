#include <iostream>
#include <limits>
#include <cstdlib>
#include <cstring>

#include <dirent.h>

#include "hoku1.hpp"

void usage(char *);
bool load_font_patterns(const string &, vector<font_pattern> &);
char glyph_match(const vector<font_pattern> &, const glyph &);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	string pic_filename = argv[1];
	string font_dirname = argv[2];

	vector<font_pattern> glyph_patterns;
	if (!load_font_patterns(font_dirname, glyph_patterns))
	{
		return 1;
	}

	// code for test load pattern
	/*
	for (auto pattern : glyph_patterns)
	{
		char file[20] = "ppp?.bmp";
		file[3] = pattern.charactor();
		pattern.save_bmp(file);
	}
	*/

	hoku_screenshot scr = hoku_screenshot(pic_filename);
	if (!scr.init())
	{
		return 1;
	}

#ifdef OUTPUT
	char bmp_filename[20] = "hokuaa.bmp";
#endif
	while (glyph *gly = scr.get_glyph())
	{
#ifndef OUTPUT
		cout << glyph_match(glyph_patterns, *gly) << " ";
#else
		gly->save_bmp(bmp_filename);
		bmp_filename[5]++;
		if (bmp_filename[5] == 'z')
		{
			bmp_filename[4]++;
			bmp_filename[5] = 'a';
		}
#endif

		delete (gly);
	}
	cout << endl;

	return 0;
}

void usage(char *program_name)
{
	cout << program_name << ": [pic] [fonts]" << endl;
}

bool load_font_patterns(const string &pattern_folder, vector<font_pattern> &glyph_patterns)
{
#ifdef OUTPUT
	return true;
#endif

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

	return true;
}

char glyph_match(const vector<font_pattern> &glyph_patterns, const glyph &glyph)
{
	float hd = numeric_limits<float>::max();
	char ch = 0;
	for (auto pattern : glyph_patterns)
	{
		if (abs(static_cast<int>(glyph.get_weight() - pattern.get_weight())) > font_pattern::WEIGHT_THREASHOLD)
		{
			continue;
		}

		point_set font_set;
		pattern.get_pointset(font_set);
		point_set glyph_set;
		glyph.get_pointset(glyph_set);

		float d = matching::hausdorff_distance_2d(font_set, glyph_set);
		if (d < hd)
		{
			hd = d;
			ch = pattern.charactor();
		}
	}
	return ch;
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
		png_destroy_read_struct(&_png_ptr, &_info_ptr, NULL);
	if (_png_ptr && !_info_ptr)
		png_destroy_read_struct(&_png_ptr, NULL, NULL);
}

unsigned int png::height()
{
	return png_get_image_height(_png_ptr, _info_ptr);
}

unsigned int png::width()
{
	return png_get_image_width(_png_ptr, _info_ptr);
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

	png_read_png(_png_ptr, _info_ptr, PNG_TRANSFORM_STRIP_ALPHA, NULL);

	int color_type = png_get_color_type(_png_ptr, _info_ptr);
	int bit_depth = png_get_bit_depth(_png_ptr, _info_ptr);
	if (color_type != 2 || bit_depth != 8)
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

// matching
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

void glyph::pirate_hash(double *hash) const
{
	unsigned int center_x = _width / 2;
	unsigned int center_y = _height / 2;

	for (unsigned int x = 0; x < _width; ++x)
	{
		for (unsigned int y = 0; y < _height; ++y)
		{
			if (_get_point(x, y))
			{
				hash[0] += sqrt((center_x - x) * (center_x - x) + (center_y - y) * (center_y - y));
				hash[1] += sqrt((0 - x) * (0 - x) + (0 - y) * (0 - y));
				hash[2] += sqrt((0 - x) * (0 - x) + (_height - y) * (_height - y));
				hash[3] += sqrt((_width - x) * (_width - x) + (0 - y) * (0 - y));
				hash[4] += sqrt((_width - x) * (_height - x) + (_width - y) * (_height - y));
			}
		}
	}
	hash[0] /= (_width * _height);
	hash[1] /= (_width * _height);
	hash[2] /= (_width * _height);
	hash[3] /= (_width * _height);
	hash[4] /= (_width * _height);
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
