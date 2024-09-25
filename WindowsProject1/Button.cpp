#include "Button.h"
#include "windowsx.h"
#include "Tools.h"

Button::Button() {
	
    m_id = '0';
}

void Button::SetButton(const char* text, HWND windowHandler, int x, int y, int w, int h) {

    m_hwnd = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"oui",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        x,         // x position 
        y,         // y position 
        w,        // Button width
        h,        // Button height
        windowHandler,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(windowHandler, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
}

void Button::SetValue(const char * text) 
{
    m_id = text[0];

    int size = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0); // Calcul de la taille nécessaire pour le buffer
    WCHAR* buffer = new WCHAR[size];  // Allouer le buffer

    // Effectuer la conversion de char* (UTF-8) à WCHAR* (UTF-16)
    MultiByteToWideChar(CP_UTF8, 0, text, -1, buffer, size);

    Button_SetText(m_hwnd, buffer);
}

void Button::SetValue(int text) 
{
    m_id = ConvertIntToConstChar(text)[0];

    const char* value = ConvertIntToConstChar(text);

    int size = MultiByteToWideChar(CP_UTF8, 0, value, -1, NULL, 0); // Calcul de la taille nécessaire pour le buffer
    WCHAR* buffer = new WCHAR[size];  // Allouer le buffer

    // Effectuer la conversion de char* (UTF-8) à WCHAR* (UTF-16)
    MultiByteToWideChar(CP_UTF8, 0, value, -1, buffer, size);

    
    Button_SetText(m_hwnd, buffer);
}
