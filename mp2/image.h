#ifndef IMAGE_H
#define IMAGE_H

#include "png.h"

using namespace std;

class Image : public PNG
{
    public:
		void flipleft();
		void adjustbrightness(int r, int g, int b);
		void invertcolors();
};

#endif