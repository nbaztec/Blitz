#pragma once

//#include "MainHeader.h"
//#include "TextureHeader.h"

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>


//#include "gl.h"

#include <math.h>

typedef	struct									
{
	GLubyte	*imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
} TextureInfo;	

typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;


typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

bool LoadTGA(TextureInfo * texture, const char * filename);
bool LoadCompressedTGA(TextureInfo * texture, const char * filename, FILE * fTGA);
bool LoadUncompressedTGA(TextureInfo * texture, const char * filename, FILE * fTGA);
