#include "../header/File.h"
#include "../header/Bitmap.h"


File::File() {
    
}

bool File::GenerateFile(const char* path) {

    fopen_s(&m_pFile, path, "rb"); //rb = lecture binaire

    if (m_pFile == 0) {
        std::cout << "File not read";
        return false;
    }

    m_path = GetPath(path);
    m_size = GetFileSize();

    m_pBuffer = new BYTE[m_size];
    fread(m_pBuffer, sizeof(BYTE), m_size, m_pFile);

    //Ce cas est fonctionnel seulement si le file est un bitmap
    m_pBitmapImage = new Bitmap();
    m_pBitmapImage->InitBitmap(this);

    return true;

}

void File::SetCanvaBitmap() {

    m_pBitmapImage->SetCanva();

}

long File::GetFileSize() {

    fseek(m_pFile, 0, SEEK_END);
    long size = ftell(m_pFile);
    fseek(m_pFile, 0, SEEK_SET);
    return size;

}

#pragma region Path

const char* File::GetPath(const char * str) {

    int cursor = 0;

    while (str[cursor] != '\0') {
        if (str[cursor] == '.') {
            break;
        }
        cursor++;
    }
    return (const char *)substr((char*)str,0,cursor);
}

char* File::substr(char* arr, int begin, int len)
{
    char* res = new char[len + 1];
    for (int i = 0; i < len; i++)
        res[i] = *(arr + begin + i);
    res[len] = 0;
    return res;
}

#pragma endregion

File* File::SaveModifications() {
    
    char* newPath = new char[sizeof(m_path) + 3];
    strcpy(newPath, m_path);
    strcat(newPath, "-1.bmp");

    std::cout << newPath;

    FILE* newFile = fopen((const char *)newPath, "wb");
    File* newFileClass = new File();
    newFileClass->GenerateFile(newPath);
    fwrite(newFileClass->GetBuffer(), m_size, 1, newFile);

    return newFileClass;

}