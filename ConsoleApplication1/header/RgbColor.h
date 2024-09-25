#pragma once
#include <Windows.h>

struct RgbColor {

	BYTE red;
	BYTE green;
	BYTE blue;

	RgbColor(BYTE r, BYTE g, BYTE b) {
		red = r;
		green = r;
		blue = r;
	};
};
