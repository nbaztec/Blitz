/*
 * Texture.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <GL\glfw.h>

struct Texture
{
	int count;
	GLuint *textures;

	Texture(void)		
	{
		this->count = 0;
		this->textures = NULL;
	}

	Texture(Texture& t)
	{
		this->count = t.count;
		this->textures = t.textures;
	}

	Texture(int count, GLuint *textures)
	{
		this->count = count;
		this->textures = textures;
	}

	inline GLuint first()
	{
		return this->count > 0? this->textures[0]: NULL;
	}
};