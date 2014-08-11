#include "hoku_picture.hpp"

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
