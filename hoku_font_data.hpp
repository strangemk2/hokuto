#pragma once

vector<font_pattern> predefined_patterns = {
	// {ch, width, height, weight, {data1, data2, ..., datax}},
	{'%', 13, 10, 64, {0,1,1,1,1,0,0,0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,0,0,1,1,1,0,1,1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,}},
	{'-', 6, 2, 12, {1,1,1,1,1,1,1,1,1,1,1,1,}},
	{'0', 10, 10, 57, {0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,}},
	{'1', 6, 10, 27, {0,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,}},
	{'2', 9, 10, 55, {0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}},
	{'3', 9, 10, 52, {0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,}},
	{'4', 10, 10, 53, {0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,1,1,0,0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,}},
	{'5', 9, 10, 57, {0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,}},
	{'6', 9, 10, 53, {0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,}},
	{'7', 9, 10, 43, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,}},
	{'8', 10, 10, 65, {0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,}},
	{'9', 10, 10, 53, {0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,}},
	{'?', 8, 10, 36, {0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,}},
	{'a', 12, 10, 55, {0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,1,}},
	{'b', 9, 10, 66, {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,}},
	{'c', 11, 10, 55, {0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,}},
	{'d', 11, 10, 65, {0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,}},
	{'e', 9, 10, 60, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}},
	{'f', 10, 10, 54, {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,}},
	{'g', 11, 10, 64, {0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,}},
	{'h', 11, 10, 56, {1,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,}},
	{'i', 3, 10, 30, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}},
	{'j', 9, 10, 32, {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,}},
	{'k', 11, 10, 56, {0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,}},
	{'l', 11, 10, 37, {0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,}},
	{'m', 12, 10, 75, {1,1,1,1,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,1,}},
	{'n', 12, 10, 70, {0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,0,1,1,0,1,1,0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,}},
	{'o', 11, 10, 60, {0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,}},
	{'p', 10, 10, 53, {1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,}},
	{'r', 11, 11, 62, {1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,0,0,0,1,1,0,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,}},
	{'s', 10, 10, 61, {0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,}},
	{'t', 12, 10, 39, {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,}},
	{'u', 12, 10, 52, {1,1,1,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,}},
	{'v', 12, 10, 49, {0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,}},
	{'w', 14, 10, 79, {1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,1,0,0,0,1,1,1,1,1,0,1,1,0,1,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,}},
	{'y', 10, 10, 41, {1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,}},
	{'z', 11, 10, 59, {0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,}},
	{'|', 4, 4, 16, {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}},
};
