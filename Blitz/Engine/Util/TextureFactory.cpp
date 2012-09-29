/*
 * TextureFactory.cpp
 *
 *  Created on: Sep 2, 2012
 *      Author: Nisheeth
 */

#include "TextureFactory.hpp"

TextureFactory::TextureFactory(void)
{
}


TextureFactory::~TextureFactory(void)
{
}


Texture TextureFactory::createTextures2D(const RawImage* image)
{
	return TextureFactory::createTextures2D(image, 1);
}

Texture TextureFactory::createTextures2D(const RawImage* image, int count)
{
	GLuint *textures = new GLuint[count];
	// allocate a texture name
	glGenTextures(1, textures);
	// select current texture
	for(int i=0; i<count; i++)
	{		
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the original
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// the texture wraps over at the edges (repeat)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		// Write Data
		
		gluBuild2DMipmaps( GL_TEXTURE_2D, image->hasAlpha()? 4 : 3, image->getWidth(), image->getHeight(), image->hasAlpha() ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image->getData() );
	}
	//glTexImage2D(GL_TEXTURE_2D, 0, image->hasAlpha()? 4 : 3, image->getWidth(), image->getHeight(), 0, image->hasAlpha() ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image->getData());
	return Texture(count, textures);
}