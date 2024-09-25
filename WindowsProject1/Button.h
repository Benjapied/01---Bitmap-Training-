#pragma once
#include "windows.h"

class Button
{
public: 

	HWND m_hwnd;
	char m_id;

	Button();
	void SetButton(const char* text, HWND windowHandler, int x = 50, int y = 50, int w = 100, int h = 100);
	
	void SetValue(const char* text);
	void SetValue(int text);

};

