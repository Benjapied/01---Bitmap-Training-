#pragma once
#include "Windows.h"
#include "RgbColor.h"

class File;

class Bitmap {

private:

	BITMAPFILEHEADER*	m_pBitmapFileHeader;
	BITMAPINFOHEADER*	m_pBitmapInfoHeader;
	BYTE*				m_pBgr;
	BYTE*				m_pTempBgrBuffer;

	File*				m_pFile;

public:

	File* GetFile() {
		return m_pFile;
	}

	BYTE* GetBgr() {
		return m_pBgr;
	}

	void SetCanva(BYTE* b) {
		delete[] m_pBgr;
		m_pBgr = b;
	}

	void SetCanva() {
		delete[] m_pBgr;
		m_pBgr = m_pTempBgrBuffer;
	}

public:

	Bitmap();
	bool InitBitmap(File* file);
	void Write(long coordinates, BYTE value);
	void Write(long coordinates, RgbColor color);

	//void static ConvertRgbToBgr(RgbColor color);
	//void static ConvertRgbToBgr(BYTE r, BYTE g, BYTE b);

};