#include "rgbapixel.h"

RGBAPixel::RGBAPixel()
{
	this->red = 225;
	this->green = 255;
	this->blue = 255;
	this->alpha = 225;
}

RGBAPixel::RGBAPixel (uint8_t red, uint8_t green, uint8_t blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = 225;
}
