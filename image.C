#include <image.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
Image::Image(void)
{
	width = 0;
	height = 0;
	bin_data = NULL; // not sure what to init to
}
Image::~Image()
{
	if (bin_data != NULL)
	{
		delete [] bin_data;
	}
}
Image::Image(int w, int h)
{
	width = w;
	height = h;
	bin_data = new unsigned char[3*w*h];
}
Image::Image(Image &img)
{
	width = img.width;
	height = img.height;
	bin_data = new unsigned char[3*width*height];
	memcpy(bin_data, img.bin_data, 3*width*height);
}
void Image::ResetSize(int w, int h)
{
	if (bin_data == NULL)
	{
		delete [] bin_data;
	}
	width = w;
	height = h;
	bin_data = new unsigned char[3*w*h];
}

void Image::Update() const
{
	ImgSource->Update();
}
