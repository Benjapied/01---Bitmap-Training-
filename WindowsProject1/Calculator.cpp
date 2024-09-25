#include "Calculator.h"
#include <string>
#include "Button.h"

Calculator::Calculator(int x, int y) {

	m_currentDisplay = 0;
	m_previousDisplay = 0;
	m_text = 0;

	m_pointRange = 0;

	m_x = x;
	m_y = y;

	m_previousSign = NONE;
}

void Calculator::InitAll(HWND* window) {

	m_text = new Text();
	m_text->SetText("0", *window, m_x, m_y, 200, 50);

	for (int i = 0; i < 9; i++) {

		//Faut convertir char en int

		m_buttons.push_back(new Button());
		m_buttons[i]->SetButton(" ", *window, m_x + (i % 3) * 50, m_y + (i / 3) * 50 + 50, 50, 50);
		m_buttons[i]->SetValue(9 - i);
	}

	//On place le 0	
	m_buttons.push_back(new Button());
	m_buttons[9]->SetButton(" ", *window, m_x + 50, m_y + 200, 50, 50);
	m_buttons[9]->SetValue(0);

	//Le plus 
	m_buttons.push_back(new Button());
	m_buttons[10]->SetButton(" ", *window, m_x +  150, m_y + 50, 50, 50);
	m_buttons[10]->SetValue("+");

	//Le moins 
	m_buttons.push_back(new Button());
	m_buttons[11]->SetButton(" ", *window, m_x + 150, m_y + 100, 50, 50);
	m_buttons[11]->SetValue("-");

	//Le fois 
	m_buttons.push_back(new Button());
	m_buttons[12]->SetButton(" ", *window, m_x + 150, m_y + 150, 50, 50);
	m_buttons[12]->SetValue("*");

	//Le plus 
	m_buttons.push_back(new Button());
	m_buttons[13]->SetButton(" ", *window, m_x + 150, m_y + 200, 50, 50);
	m_buttons[13]->SetValue("/");

	//Le égal 
	m_buttons.push_back(new Button());
	m_buttons[14]->SetButton(" ", *window, m_x + 100, m_y + 200, 50, 50);
	m_buttons[14]->SetValue("=");

	//Le point 
	m_buttons.push_back(new Button());
	m_buttons[15]->SetButton(" ", *window, m_x + 0, m_y + 200, 50, 50);
	m_buttons[15]->SetValue(".");

	//Erase
	m_buttons.push_back(new Button());
	m_buttons[16]->SetButton(" ", *window, m_x + 200, m_y + 50 , 50, 50);
	m_buttons[16]->SetValue("C");

}

void Calculator::SetText(char input) {

	if ((Inputs)input == ERASE) {
		m_pointRange = 0;
		m_previousSign = NONE;
		m_previousDisplay = 0;
		m_currentDisplay = 0;

		char buffer[64];
		int ret = snprintf(buffer, sizeof buffer, "%f", m_currentDisplay);
		m_text->ChangeText(buffer);
	}

	if (m_previousSign == EQUAL) {
		//Si l'opération est terminée
		m_pointRange = 0;
		m_previousDisplay = m_currentDisplay;
		m_currentDisplay = 0;
		m_previousSign = NONE;
	}

	int n = input;
	if (m_pointRange < 0) { m_pointRange = 0; } // Le clamp du gitan

	if (n >= 48 && n <= 57) {
		
		//On transforme l'input en int
		n = input - 48;

		if (m_pointRange == 0) {
			m_currentDisplay = m_currentDisplay * 10 + n;
		}
		else {
			float oue2 = 3 / 10;
			float oue = (float)n / ((float)m_pointRange * (float)10);
			m_currentDisplay = m_currentDisplay + ((float)n / ((float)m_pointRange * (float)10)) ;
			m_pointRange++;
		}

		char buffer[64];
		int ret = snprintf(buffer, sizeof buffer, "%f", m_currentDisplay);

		m_text->ChangeText(buffer);

		return;
	}
	

	//TODO faire un switch case pour tous les autres inputs

	if (m_currentDisplay == 0) { return; }

	if ((Inputs)input == NULL) {
		//Si l'input n'est pas compris dans l'enum swtich
		return;
	}

	input = (Inputs)input;

	switch (input) {
	case PLUS:
	case MINUS:
	case DIVIDE:
	case MULTIPLY: {
		Calculate();

		char buffer[64];
		int ret = snprintf(buffer, sizeof buffer, "%c", ShowSign((Inputs)input));

		m_text->ChangeText((const char*)buffer);
		break;
	}
	case POINT: {
		m_pointRange++;
		break;
	}
	case ERASE: {
		m_pointRange = 0;
		m_previousSign = NONE;
		m_previousDisplay = 0;
		m_currentDisplay = 0;

		char buffer[64];
		int ret = snprintf(buffer, sizeof buffer, "%f", m_currentDisplay);
		m_text->ChangeText(buffer);

		break;
	}
	case ERASEONE: {

		m_pointRange--;
		break;
	}
	case EQUAL: {

		Calculate();
		char buffer[64];
		int ret = snprintf(buffer, sizeof buffer, "%f", m_currentDisplay);
		m_text->ChangeText(buffer);

		m_previousDisplay = m_currentDisplay;
		m_previousSign = (Inputs)input;

		return;
	}
	}

	if(input != ERASE) m_previousSign = (Inputs)input;
	
};

void Calculator::Calculate() {

	char sign = static_cast<char>(m_previousSign);

	switch (m_previousSign) {
		case NONE:
			return;
		case PLUS: 
			m_currentDisplay = m_currentDisplay + m_previousDisplay;
			break;
		case MINUS:
			m_currentDisplay = m_previousDisplay - m_currentDisplay;
			break;
		case MULTIPLY:
			m_currentDisplay = m_currentDisplay * m_previousDisplay;
			break;
		case DIVIDE:
			m_currentDisplay = m_previousDisplay / m_currentDisplay;
			break;
		case POINT:
			m_pointRange = 1;
			break;
		default:
			break;
	}

	return;

}

char Calculator::ShowSign(Inputs input) {

	m_pointRange = 0;
	m_previousDisplay = m_currentDisplay;
	m_currentDisplay = 0;

	if (input == PLUS
		|| input == MINUS
		|| input == MULTIPLY
		|| input == DIVIDE)
		return static_cast<char>(input);
	else
		return ' ';

}