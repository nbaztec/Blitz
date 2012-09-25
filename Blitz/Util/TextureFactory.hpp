/*
 * TextureFactory.hpp
 *
 *  Created on: Sep 2, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <GL\glfw.h>
#include "ImageFactory.hpp"
#include "..\Core\Texture.hpp"

class TextureFactory
{
public:
	TextureFactory(void);
	virtual ~TextureFactory(void);
	
	static Texture createTextures2D (const RawImage* image);
	static Texture createTextures2D (const RawImage* image, int count);
};