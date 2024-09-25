#pragma once
#include <iostream>
#include "windows.h"

class Bitmap;

class File
{
private:

    FILE*           m_pFile;
    long            m_size;
    BYTE*           m_pBuffer;
    Bitmap*         m_pBitmapImage;
    const char*     m_path;

public:

    // GETTERS / SETTERS

    FILE* GetFile() {
        return m_pFile;
    }
    long GetSize() {
        return m_size;
    }
    BYTE* GetBuffer() {
        return m_pBuffer;
    }
    Bitmap* GetBitmap() {
        return m_pBitmapImage;
    }
    void SetBitmap(Bitmap* b) {
        m_pBitmapImage = b;
    }
    const char* GetPath() {
        return m_path;
    }
    

public:

    File();
    bool GenerateFile(const char* path);
    File * SaveModifications();

private:    
    
    void SetCanvaBitmap();
    long GetFileSize();
    const char* GetPath(const char* str);
    char* substr(char* arr, int begin, int len);

};