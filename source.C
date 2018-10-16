#include <image.h>
#include <source.h>
#include <stdio.h>
#include <stdlib.h>

source::source()
{
	imgOut = new Image;
}

source::~source()
{
	if (imgOut != NULL)
	{
		delete imgOut;
	}
}
