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

bool TextureManager::load(const char* key, const char* file, int count)
{
	RawImage *img = ImageFactory::loadPNG(file);
	if(img != NULL)
	{
		this->_textures[key] = TextureFactory::createTextures2D(img, count);
		delete img;
		return true;
	}
	else
		return false;

}

bool TextureManager::load(const char* key, const char* file)
{
	return this->load(key, file, 1);
}

void TextureManager::remove(const char* key)
{
	this->_textures.erase(this->_textures.find(key));
}

bool TextureManager::has_texture(const char* key)
{
	return this->_textures.find(key) != this->_textures.end();
}