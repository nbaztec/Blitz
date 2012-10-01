/*
 * TextureManager.hpp
 *
 *  Created on: Sep 20, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include <GL\glfw.h>
#include <map>
#include <string>
#include "../Core/Texture.hpp"
#include "RawImage.hpp"
#include "ImageFactory.hpp"
#include "TextureFactory.hpp"

class TextureManager
{
private:
	std::map<std::string, Texture> _textures;
public:
	TextureManager(void);
	virtual ~TextureManager(void);

	bool load(const char* key, const char* file, int count);
	bool load(const char* key, const char* file);
	void remove(const char* key);
	bool has_texture(const char* key);
	Texture operator[](const char* key);
};