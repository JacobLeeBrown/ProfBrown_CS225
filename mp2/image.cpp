#include "image.h"

// flips the image over a vertical centered axis
void Image::flipleft()
{
	size_t height = this->height();
	size_t width = this->width();
    for (size_t yi = 0; yi < height; yi++) 
	{
        for (size_t xi = 0; xi < width/2; xi++) 
		{ 
			uint8_t tempRed = (*this)(xi, yi)->red;
			(*this)(xi, yi)->red = (*this)(width - 1 - xi, yi)->red;
			(*this)(width - 1 - xi, yi)->red = tempRed;
			
			uint8_t tempGreen = (*this)(xi, yi)->green;
			(*this)(xi, yi)->green = (*this)(width - 1 - xi, yi)->green;
			(*this)(width - 1 - xi, yi)->green = tempGreen;
			
			uint8_t tempBlue = (*this)(xi, yi)->blue;
			(*this)(xi, yi)->blue = (*this)(width - 1 - xi, yi)->blue;
			(*this)(width - 1 - xi, yi)->blue = tempBlue;
			
			uint8_t tempAlpha = (*this)(xi, yi)->alpha;
			(*this)(xi, yi)->alpha = (*this)(width - 1 - xi, yi)->alpha;
			(*this)(width - 1 - xi, yi)->alpha = tempAlpha;
		}
	}
}

// adjusts RGB values of the image by the passes arguments
void Image::adjustbrightness(int r, int g, int b)
{
	size_t height = this->height();
	size_t width = this->width();
	for (size_t yi = 0; yi < height; yi++) 
	{
        for (size_t xi = 0; xi < width; xi++) 
		{
			if(((*this)(xi, yi)->red) + r > 255) ((*this)(xi, yi)->red) = 255;
			else if(((*this)(xi, yi)->red) + r < 0) ((*this)(xi, yi)->red) = 0;
			else ((*this)(xi, yi)->red) += r;
			
			if(((*this)(xi, yi)->green) + g > 255) ((*this)(xi, yi)->green) = 255;
			else if(((*this)(xi, yi)->green) + g < 0) ((*this)(xi, yi)->green) = 0;
			else ((*this)(xi, yi)->green) += g;
			
			if(((*this)(xi, yi)->blue) + b > 255) ((*this)(xi, yi)->blue) = 255;
			else if(((*this)(xi, yi)->blue) + b < 0) ((*this)(xi, yi)->blue) = 0;
			else ((*this)(xi, yi)->blue) += b;
		}
	}
}

// reverses RGB values of the image
void Image::invertcolors()
{
	size_t height = this->height();
	size_t width = this->width();
	for (size_t yi = 0; yi < height; yi++) 
	{
        for (size_t xi = 0; xi < width; xi++) 
		{
			(*this)(xi, yi)->red = 255 - (*this)(xi, yi)->red;
			(*this)(xi, yi)->green = 255 - (*this)(xi, yi)->green;
			(*this)(xi, yi)->blue = 255 - (*this)(xi, yi)->blue;
		}
	}
}