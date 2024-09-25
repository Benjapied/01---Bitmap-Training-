#include "../header/Bitmap.h"
#include <cstring>
#include "../header/File.h"

Bitmap::Bitmap() {

	m_pBitmapFileHeader = 0;
	m_pBitmapInfoHeader = 0;
	m_pBgr = 0;

	m_pFile = 0;
	m_pTempBgrBuffer = 0;

}

bool Bitmap::InitBitmap(File* file) {

	m_pFile = file;
	//SI CA NE FONCTIONNE PAS, PEU-ETRE LE PB VIENT D'ICI
	m_pBitmapFileHeader = (BITMAPFILEHEADER*) file->GetBuffer() + sizeof(BITMAPFILEHEADER);
	m_pBitmapInfoHeader = (BITMAPINFOHEADER*) file->GetBuffer() + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	m_pBgr = file->GetBuffer() + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	m_pTempBgrBuffer = new BYTE[m_pFile->GetSize()];
	std::memcpy(m_pTempBgrBuffer, m_pBgr, m_pFile->GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));

	return true;
	
}

void Bitmap::Write(long coordinates, BYTE value) {

	m_pTempBgrBuffer[coordinates] = value;
}

void Bitmap::Write(long coordinates, RgbColor color) {

	long trueCoo = m_pFile->GetSize() / 3 * coordinates;
	m_pTempBgrBuffer[trueCoo] = color.blue;
	m_pTempBgrBuffer[trueCoo + 1] = color.green;
	m_pTempBgrBuffer[trueCoo + 2] = color.red;
}
