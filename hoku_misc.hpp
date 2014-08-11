#pragma once

// The following color judgement should not be change.
// or we must regenerate all font from screenshots.
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
