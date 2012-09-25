/*
 * TextureManager.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: Nisheeth
 */
 
#include "TextureManager.hpp"

TextureManager::TextureManager(void)
{
}

TextureManager::~TextureManager(void)
{
	std::map<std::string, Texture>::iterator it;
	while(!this->_textures.empty())
	{		
		
		it = this->_textures.begin();		
		glDeleteTextures(it->second.count, it->second.textures);		
		this->_textures.erase(it);
	}
}

Texture TextureManager::operator[](const char* key)
{
	return this->_textures[key];
}

void TextureManager::load(const char* key, const char* file, int count)
{
	RawImage *img = ImageFactory::loadPNG(file);
	this->_textures[key] = TextureFactory::createTextures2D(img, count);
	delete img;
}

void TextureManager::load(const char* key, const char* file)
{
	this->load(key, file, 1);
}

void TextureManager::remove(const char* key)
{
	this->_textures.erase(this->_textures.find(key));
}

bool TextureManager::has_texture(const char* key)
{
	return this->_textures.find(key) != this->_textures.end();
}