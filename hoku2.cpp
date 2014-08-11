#include <iostream>
#include <limits>
#include <cstring>

#include "hoku1.hpp"

void usage(char *);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		usage(argv[0]);
		return 1;
	}

	string pic_filename = argv[1];

	hoku_screenshot scr = hoku_screenshot(pic_filename);
	if (!scr.init())
	{
		return 1;
	}

	char bmp_filename[20] = "hokuaa.bmp";
	while (glyph *gly = scr.get_glyph())
	{
		gly->save_bmp(bmp_filename);
		bmp_filename[5]++;
		if (bmp_filename[5] == 'z')
		{
			bmp_filename[4]++;
			bmp_filename[5] = 'a';
		}

		delete (gly);
	}

	return 0;
}

void usage(char *program_name)
{
	cout << program_name << ": [pic]" << endl;
}
