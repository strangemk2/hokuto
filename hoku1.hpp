#include <vector>
#include <string>

#include "png.h"
#include "bitmap_image.hpp"

using namespace std;

class bitmap_image;

typedef unsigned char color;

struct rgb
{
	color r;
	color g;
	color b;
};

class point
{
	public:
		float x = 0.0f;
		float y = 0.0f;

		point(float a, float b):
			x(a),
			y(b)
		{}
};
typedef vector<point> point_set;

class coordinate
{
	public:
		unsigned int x;
		unsigned int y;

		coordinate():
			x(0),
			y(0)
		{}

		operator bool() const
		{
			return (x + y);
		}
};

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

class matching
{
	private:
		static constexpr float FLOAT_THREASHOLD = 0.1f;

		static bool threashold_equal(float a, float b);

		static inline float distance_2d(const point &a, const point &b)
		{
			return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
		}

	public:
		static float hausdorff_distance_2d(const point_set &a_set, const point_set &b_set);
};

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

		void pirate_hash(double *) const;
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

static inline bool is_black(rgb c)
{
	return ((c.r + c.g + c.b) <= 50)?true:false;
}

static inline bool is_yellow(rgb c)
{
	return (c.r > 80 && c.g > 80 && c.b < 30)?true:false;
}

static inline bool is_red(rgb c)
{
	return ((c.r - c.g > 100) && (c.r - c.b) > 100)?true:false;
}

static inline bool is_backgroud_red(rgb c)
{
	return (c.r == 97 && c.g == 0 && c.b == 0)?true:false;
}

static inline bool is_real_red(rgb c)
{
	return (c.r >= 250 && c.g == 0 && c.b == 0)?true:false;
}

static inline bool is_glyph_black(rgb c)
{
	return (c.r == 0 && c.g == 0 && c.b == 0)?true:false;
}
