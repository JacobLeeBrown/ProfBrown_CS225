/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 */
#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

/**
 * This function accepts a PNG object, two integer coordinates and a color, and
 * proceeds to draw a horizontal line across the image at the y coordinate and
 * a vertical line down the image at the x coordinage using the given color.
 * The modified PNG is then returned.
 *
 * @param original A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 * @param color The color of the lines to be drawn.
 *
 * @return The image on which a crosshair has been drawn.
 */
PNG drawCrosshairs(PNG original, int centerX, int centerY, RGBAPixel color)
{
    /// This function is already written for you so you can see how to
    /// interact with our PNG class.
    for (size_t x = 0; x < original.width(); x++)
        *original(x, centerY) = color;

    for (size_t y = 0; y < original.height(); y++)
        *original(centerX, y) = color;

    return original;
}

/**
 * This function brightens a rectangle of a PNG, increasing the components
 * (red, green, blue) of each pixel by the given amount. You must account
 * for potential overflow issues (color components can only store numbers
 * between 0 and 255). If you attempt to store a value greater than 255
 * into a color component, the result will wrap around (and you won't be
 * able to check if it was greater than 255).
 *
 * @param original A PNG object which holds the image data to be modified.
 * @param amount The integer amount by which to increase each pixel's
 * components.
 *
 * @return The brightened image.
 */
PNG brighten(PNG original, int amount)
{
    /// You can assume amount is positive.
    for (size_t yi = 0; yi < original.height(); yi++) {
        for (size_t xi = 0; xi < original.width(); xi++) {
			// Obtain RGB values
			int red = original(xi, yi)->red;
			int green = original(xi, yi)->green;
			int blue = original(xi, yi)->blue;

			// Increment RGB values
			red += amount;
			green += amount;
			blue += amount;

			// Check that the values are within the proper bounds
			if(red > 255) red = 255;
			if(green > 255) green = 255;
			if(blue > 255) blue = 255;
		
			// Update RGB values
			original(xi, yi)->red = red;
			original(xi, yi)->green = green;
			original(xi, yi)->blue = blue;
        }
    }
    return original;
}

/**
 * This function blends, or averages, two PNGs together. That is, each pixel in
 * the returned image consists of the averaged components (red, green, blue) of
 * the two input images.
 *
 * @param firstImage  The first of the two PNGs to be averaged together.
 * @param secondImage The second of the two PNGs to be averaged together.
 *
 * @return The averaged image.
 */
PNG blendImages(PNG firstImage, PNG secondImage)
{
	for (size_t yi = 0; yi < firstImage.height(); yi++) {
		for (size_t xi = 0; xi < firstImage.width(); xi++) {
			// Obtain RGB values
			int red1 = firstImage(xi, yi)->red;
			int green1 = firstImage(xi, yi)->green;
			int blue1 = firstImage(xi, yi)->blue;
			
			int red2 = secondImage(xi, yi)->red;
			int green2 = secondImage(xi, yi)->green;
			int blue2 = secondImage(xi, yi)->blue;
			
			// Average RGB values
			int red = (int)((red1 + red2)/2);
			int green = (int)((green1 + green2)/2);
			int blue = (int)((blue1 + blue2)/2);

			// Update RGB values
			firstImage(xi, yi)->red = red;
			firstImage(xi, yi)->green = green;
			firstImage(xi, yi)->blue = blue;
		}
	}
    return firstImage;
}

/**
 * The main function in this program (the starting point of the execution of our
 * code).
 *
 * @return An integer indicating whether execution was successful.
 */
int main()
{
    // Open a new PNG image from the file sample.png.
    PNG image("sample.png");

    // Open a new PNG image from the file overlay.png.
    PNG overlay("overlay.png");

    // Brighten the image read from overlay.png.
    overlay = brighten(overlay, 128);

    // Blend sample.png and overlay.png together.
    image = blendImages(image, overlay);

    // Create a new RGBAPixel color for drawCrosshairs which is cyan.
    RGBAPixel cyanColor;
    cyanColor.red = 0;
    cyanColor.green = 255;
    cyanColor.blue = 255;

    // Draw two crosshairs on the image.
    image = drawCrosshairs(image, 400, 330, cyanColor);
    image = drawCrosshairs(image, 620, 424, cyanColor);

    // Save the modified image to a file called output.png, overwriting the file
    // if it already exists.
    image.writeToFile("output.png");

    return 0;
}
