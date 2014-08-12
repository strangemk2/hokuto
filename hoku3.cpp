#include <iostream>
#include <fstream>
#include <limits>

#include "hoku1.hpp"

void usage(char *);

matching matching::_instance;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		usage(argv[0]);
		return 1;
	}

	string font_dirname = argv[1];

	vector<font_pattern> glyph_patterns;
	if (!load_font_patterns(font_dirname, glyph_patterns))
	{
		return 1;
	}

	string data_header = dump_font_patterns(glyph_patterns);
	ofstream ofs("hoku_font_data.hpp");
	ofs << data_header;
	ofs.close();

	return 0;
}

void usage(char *program_name)
{
	cout << program_name << ": [fonts]" << endl;
}
