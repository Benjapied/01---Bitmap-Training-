#pragma once
#include "windows.h"


class Text
{
public:

	HWND m_hwnd;
	long m_textSize;

	Text();
	void SetText(const char* text, HWND windowHandler, int x = 50, int y = 50, int w = 100, int h = 100);

	void ChangeText(const char* text);
	
	const char* CropDot(const char* str);
	char* substr(char* arr, int begin, int len);
};

