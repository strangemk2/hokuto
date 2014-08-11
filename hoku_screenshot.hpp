#pragma once
#include "bitmap_image.hpp"

#include "hoku_font.hpp"
#include "hoku_picture.hpp"

class hoku_screenshot
{
	private:
		picture *_pic = nullptr;
		bitmap_image *_textarea = nullptr;
		const string _pic_filename;

		coordinate _current_charactor;

		bitmap_image *find_textarea();

	public:
		hoku_screenshot(const string filename):
			_pic_filename(filename)
		{};
		~hoku_screenshot();

		bool init();
		glyph *get_glyph();
};
