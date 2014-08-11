#include <iostream>
#include <limits>
#include <cstring>

#include <dirent.h>

#include "hoku1.hpp"

void usage(char *);
bool load_font_patterns(const string &, vector<font_pattern> &);
char glyph_match(const vector<font_pattern> &, const glyph &);

matching matching::_instance;

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

	while (glyph *gly = scr.get_glyph())
	{
		cout << glyph_match(glyph_patterns, *gly);

		delete (gly);
	}
	//cout << endl;

	return 0;
}

void usage(char *program_name)
{
	cout << program_name << ": [pic] [fonts]" << endl;
}

bool load_font_patterns(const string &pattern_folder, vector<font_pattern> &glyph_patterns)
{
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
		point_set font_set;
		pattern.get_pointset(font_set);
		point_set glyph_set;
		glyph.get_pointset(glyph_set);

#ifdef SPECIAL_PATCH
		// special patch for fonts ", ."
		auto s = glyph_set.size();
		if (s == 1)
		{
			ch = '!';
			return ch;
		}
		else if (s < 6)
		{
			ch = '.';
			return ch;
		}
		else if(s < 9 && 6 <= s)
		{
			ch = ',';
			return ch;
		}
		// end patch
#endif

		if (abs(static_cast<int>(glyph.get_weight() - pattern.get_weight())) > font_pattern::WEIGHT_THREASHOLD)
		{
			continue;
		}

		float d = matching::instance()->hausdorff_distance_2d(font_set, glyph_set);
		if (d < hd)
		{
			hd = d;
			ch = pattern.charactor();
		}
	}
	return ch;
}
