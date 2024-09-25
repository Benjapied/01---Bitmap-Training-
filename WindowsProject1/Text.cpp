#include "Text.h"
#include "windowsx.h"
#include <stdlib.h>

Text::Text() {

    m_hwnd = 0;
    m_textSize = 0;

}

void Text::SetText(const char* text, HWND windowHandler, int x, int y, int w, int h) {

    m_hwnd = CreateWindow(
        L"EDIT",
        (LPCWSTR)text,
        WS_BORDER | WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_MULTILINE | ES_AUTOVSCROLL,
        x,
        y,
        w,
        h,
        windowHandler,
        NULL,
        (HINSTANCE)GetWindowLongPtr(windowHandler, GWLP_HINSTANCE),
        NULL);

}

void Text::ChangeText(const char * text) {

    const char* zob = CropDot(text);;

    int size = MultiByteToWideChar(CP_UTF8, 0, zob, -1, NULL, 0); // Calcul de la taille nécessaire pour le buffer
    WCHAR* buffer = new WCHAR[size];  // Allouer le buffer

    // Effectuer la conversion de char* (UTF-8) à WCHAR* (UTF-16)
    MultiByteToWideChar(CP_UTF8, 0, zob, -1, buffer, size);

    Edit_SetText(m_hwnd, buffer);

    //delete[] buffer;

}

#pragma region Crop Text

const char* Text::CropDot(const char* str) {

    int cursor = 0;

    while (str[cursor] != '\0') {
        if (str[cursor] == '.') {
            break;
        }
        cursor++;
    }

    char* firstPart = substr((char*)str, 0, cursor);

    int cursor2 = cursor;
    int trigger = 0;

    while (str[cursor2] != '\0') {
        if (str[cursor2] != '0' && str[cursor2] != '.') {

            trigger = cursor2;

        }
        cursor2++;
    }

    char* secondPart = substr((char*)str, cursor + 1, trigger);

    if (trigger == 0) {
        return firstPart;
    }

    rsize_t oue2 = sizeof(firstPart + 1);

    strcat_s(firstPart, oue2, ".");

    rsize_t oue = sizeof(firstPart) + sizeof(secondPart);
    
    (const char*)strcat_s(firstPart, oue, secondPart);

    return firstPart;

}

char* Text::substr(char* arr, int begin, int len)
{
    char* res = new char[len + 1];
    for (int i = 0; i < len; i++)
        res[i] = *(arr + begin + i);
    res[len] = 0;
    return res;
}

#pragma endregion
