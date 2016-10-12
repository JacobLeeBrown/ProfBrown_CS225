#include "rgbapixel.h"
#include "png.h"

using namespace std;

int main()
{
	PNG in_image("in.png");
	PNG out_image(in_image.width(), in_image.height());
	
    for(size_t yi = 0; yi < in_image.height(); yi++){
    	for(size_t xi = 0; xi < in_image.width(); xi++){
    		out_image(in_image.width() - xi - 1, in_image.height() - yi - 1)->red = in_image(xi, yi)->red;
    		out_image(in_image.width() - xi - 1, in_image.height() - yi - 1)->green = in_image(xi, yi)->green;
    		out_image(in_image.width() - xi - 1, in_image.height() - yi - 1)->blue = in_image(xi, yi)->blue;
    		out_image(in_image.width() - xi - 1, in_image.height() - yi - 1)->alpha = in_image(xi, yi)->alpha;
    	}
	}
	
	out_image.writeToFile("out.png");
	
	return 0;
}
