#include <iostream>
#include <cstring>
#include <cstdio>

#include "Windows.h"
#include "iomanip"
#include "header/File.h"
#include "header/Bitmap.h"

int main()
{

	File* file = new File();
	bool result = file->GenerateFile("BitmapImg/bee.bmp");
	
	if (result == false) {
		return 0;
	}

	file->GetBitmap()->Write(0,100);

	file->SaveModifications();
	
}
