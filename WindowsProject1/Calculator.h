#pragma once
#include "Text.h"
#include <vector>

class Button;



class Calculator
{
	
public:

	static enum Inputs : char
	{
		NONE = ' ',
		PLUS = '+',
		MINUS = '-',
		MULTIPLY = '*',
		DIVIDE = '/',
		EQUAL = '=',
		POINT = '.',
		ERASE = 'C',
		ERASEONE = 'T'
	};

	long float m_previousDisplay;
	long float m_currentDisplay;
	
	Text * m_text;
	std::vector<Button*> m_buttons;

	int m_pointRange;

	int m_x;
	int m_y;

	Calculator(int x = 0, int y = 0);
	void InitAll(HWND* window);
	void SetText(char input);
	void Calculate();
	char ShowSign(Inputs input);

	Inputs m_previousSign;

};

