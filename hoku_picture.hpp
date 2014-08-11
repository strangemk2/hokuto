#pragma once

#include <string>

#include "png.h"
#include "bitmap_image.hpp"

#include "hoku_common.hpp"

class picture
{
	private:

	public:
		//picture();
		virtual ~picture(){};

		virtual unsigned int height() = 0;
		virtual unsigned int width() = 0;

		virtual bool init(const string filename) = 0;
		virtual rgb get_pixel(coordinate cord);
		virtual rgb get_pixel(unsigned int x, unsigned int y) = 0;

		static picture *get_picture(const string filename);
};

class png : public picture
{
	private:
		FILE *_fp = nullptr;
		png_structp _png_ptr = nullptr;
		png_infop _info_ptr = nullptr;
		png_bytep *_row_pointers = nullptr;		// memory will freed by library.

	public:
		png(){};
		~png();

		unsigned int height();
		unsigned int width();

		bool init(const string filename);
		rgb get_pixel(unsigned int x, unsigned int y);
};

class bmp : public picture
{
	private:
		bitmap_image *_img;

	public:
		bmp(){};
		~bmp();

		unsigned int height();
		unsigned int width();

		bool init(const string filename);
		rgb get_pixel(unsigned int x, unsigned int y);
};
