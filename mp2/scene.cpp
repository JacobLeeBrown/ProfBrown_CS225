#include "scene.h"
#include <string>
#include <iostream>
using namespace std;

Scene::Scene(int max)
{
	// initialize all private member variables
	this->max = max;
	xCoords = new int[max];
	yCoords = new int[max];
	layers = new Image *[max];
	// set default data to all of the arrays
	for(int i = 0; i < max; i++)
	{
		layers[i] = NULL;
		xCoords[i] = 0;
		yCoords[i] = 0;
	}
}
Scene::~Scene()
{
	// call a helper method to assist with cleanup
	deleteScene();
}
Scene::Scene(const Scene &source)
{
	// call a helper method to assist with copying
	copyScene(source);
}
const Scene & Scene::operator= (const Scene &source)
{
	if(this != &source)
	{
		// delete the old stuff and replace with the new
		deleteScene();
		copyScene(source);
	}
	return *this;
}
void Scene::changemaxlayers(int newmax)
{
	// the only situation that an invalid newmax is possible
    if(newmax < max)
    {
        for(int i = newmax; i < max; i++)
        {
            if(layers[i] != NULL)
            {
                cout<< "invalid newmax" << endl;
                return;
            }
        }
    }
	// instantiate all new arrays
    int *newXCoords = new int[newmax];
    int *newYCoords = new int[newmax];
    Image **newLayers = new Image *[newmax];
	// populate them
    for(int i = 0; i < newmax; i++)
    {
        newXCoords[i] = 0;
        newYCoords[i] = 0;
        newLayers[i] = NULL;
    }
	// you only need to copy to the size of the smaller of the two
    int min = (newmax < max) ? newmax : max;
    for(int i = 0; i < min; i++)
    {
        newXCoords[i] = xCoords[i];
        newYCoords[i] = yCoords[i];
        *newLayers[i] = *(layers[i]);
    }
	// get rid of old data
    deleteScene();
	// set new data
    xCoords = newXCoords;
    yCoords = newYCoords;
    layers = newLayers;
	max = newmax;
	
	// delete the temp variables used to load new data
	delete newXCoords;
	delete newYCoords;
	for(int i = 0; i < newmax; i++)
	{
		delete newLayers[i];
	}
	delete [] newLayers;
}
void Scene::addpicture(const char *FileName, int index, int x, int y)
{
	// check for invalid index
	if(index >= max || index < 0)
	{
		cout << "index out of bounds" << endl;
		return;
	}
	// initialize new picture
	Image *in = new Image();
	in->readFromFile(FileName);
	xCoords[index] = x;
	yCoords[index] = y;
	// check if there is a picture in the way
	if(layers[index] != NULL)
	{
		delete layers[index];
	}
	// set new image at proper index
	layers[index] = in;
}
void Scene::changelayer(int index, int newindex)
{
	// check that parameters are valid
	if(index >= max || newindex >= max || index < 0 || newindex < 0)
	{
		cout << "invalid index" << endl;
		return;
	}
	// if the parameters are the same, job's done
	else if(index == newindex)
	{
		return;
	}
	// check that the layer we're going to is empty, if not, make it so
	if(layers[newindex] != NULL)
	{
		delete layers[newindex];
	}
	// update values
	xCoords[newindex] = xCoords[index];
	yCoords[newindex] = yCoords[index];
	layers[newindex] = layers[index];
	// clear old values
	xCoords[index] = 0;
	yCoords[index] = 0;
	layers[index] = NULL;
}
void Scene::translate(int index, int xcoord, int ycoord)
{
	// first, check that the index is valid
	if(index >= max || index < 0)
	{
		cout << "invalid index" << endl;
		return;
	}
	// second, check that the image in the layer is valid
	else if(layers[index] == NULL)
	{
		cout << "invalid index" << endl;
		return;
	}
	// update coords
	xCoords[index] = xcoord;
	yCoords[index] = ycoord;
}
void Scene::deletepicture(int index)
{
	// first, check that the index is valid
	if(index >= max || index < 0)
	{
		cout << "invalid index" << endl;
		return;
	}
	// second, check that the image in the layer is valid
	else if(layers[index] == NULL)
	{
		cout << "invalid index" << endl;
		return;
	}
	// delete image
	delete layers[index];
	// reset old values
	xCoords[index] = 0;
	yCoords[index] = 0;
	layers[index] = NULL;
}
Image * Scene::getpicture(int index) const
{
	// check that the index is valid
	if(index >= max || index < 0)
	{
		cout << "invalid index" << endl;
		return NULL;
	}
	return layers[index];
}
Image Scene::drawscene() const
{
	// need to determine length and width of new image (scene)
	int width = 0;
	int height = 0;
	for(int i = 0; i < max; i++)
	{
		Image * curImage = layers[i];
		if(curImage != NULL)
		{
			if((int)(curImage->width() + xCoords[i]) > width)
			{
				width = (curImage->width() + xCoords[i]);
			}
			if((int)(curImage->height() + yCoords[i]) > height)
			{
				height = (curImage->height() + yCoords[i]);
			}
		}
	}
	// initialize scene with proper size
	Image theScene{};
	theScene.resize(width, height);
	for(int i = 0; i < max; i++)
	{
		Image * curImage = layers[i];
		if(curImage != NULL)
		{
			for(int yi = 0; yi < (int)curImage->height(); yi++)
			{
				for(int xi = 0; xi < (int)curImage->width(); xi++)
				{
					*theScene(xCoords[i] + xi, yCoords[i] + yi) = *(*curImage)(xi, yi);
				}
			}
		}
	}
	return theScene;
}
void Scene::copyScene(const Scene &source)
{
	// copy max over
	max = source.max;
	// initialize blank arrays
    xCoords = new int[max];
    yCoords = new int[max];
    layers = new Image *[max];
	// fill the arrays
    for(int i = 0; i < max; i++)
    {
		// copy coords
        xCoords[i] = source.xCoords[i];
        yCoords[i] = source.yCoords[i];
		// check each layer is present before copying
        if (source.layers[i] != NULL)
		{
            layers[i] = new Image(*(source.layers[i]));
        }
        else
        {
			layers[i] = NULL;
		}
    }
}
void Scene::deleteScene()
{
	// delete coordinate arrays
	delete xCoords;
	delete yCoords;
	// delete each index of the layers array (each is a pointer)
	for(int i = 0; i < max; i++)
	{
		delete layers[i];
	}
	// delete the whole deal when done
	delete [] layers;
}