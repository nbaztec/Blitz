/*
 * ImageFactory.hpp
 *
 *  Created on: Sep 1, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <cstdio>
#include <GL/glfw.h>
#include <libpng\png.h>
#include "TGATexture.hpp"
#include "RawImage.hpp"

typedef unsigned long ulong;
typedef unsigned char ubyte;

class ImageFactory
{
protected:
	static unsigned int getint(FILE *fp);
	static unsigned int getshort(FILE *fp);
public:
	static RawImage* loadBMP(const char* filename);	
	static RawImage* loadTGA(const char* filename);
	static RawImage* loadPNG(const char *filename);
};
