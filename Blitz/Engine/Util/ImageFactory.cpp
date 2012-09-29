/*
 * ImageFactory.cpp
 *
 *  Created on: Sep 1, 2012
 *      Author: Nisheeth
 */

#include "ImageFactory.hpp"

/*
 * getint and getshort are help functions to load the bitmap byte by byte on
 * SPARC platform (actually, just makes the thing work on platforms of either
 * endianness, not just Intel's little endian)
 */

unsigned int ImageFactory::getint(FILE *fp)
{
	int c, c1, c2, c3;

	// get 4 bytes
	c = getc(fp);
	c1 = getc(fp);
	c2 = getc(fp);
	c3 = getc(fp);

	return ((unsigned int) c) +
			(((unsigned int) c1) << 8) +
			(((unsigned int) c2) << 16) +
			(((unsigned int) c3) << 24);
}

unsigned int ImageFactory::getshort(FILE *fp)
{
	int c, c1;

	//get 2 bytes
	c = getc(fp);
	c1 = getc(fp);

	return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

RawImage* ImageFactory::loadBMP(const char* filename)
{
	FILE *file;
	unsigned long size;                 // size of the image in bytes.
	unsigned long i;                    // standard counter.
	unsigned short int planes;          // number of planes in image (must be 1)
	unsigned short int bpp;             // number of bits per pixel (must be 24)
	char temp;                          // used to convert bgr to rgb color.

	// make sure the file is there.
	if ((file = fopen(filename, "rb"))==NULL)
	{
		printf("File Not Found : %s\n",filename);
		return NULL;
	}


	// seek through the bmp header, up to the width/height:
	fseek(file, 18, SEEK_CUR);

	// No 100% error checking anymore!!!

	//image = new Image();

	// read the width
	ulong width, height;
	width = ImageFactory::getint (file);
	printf("Width of %s: %lu\n", filename, width);

	// read the height
	height = ImageFactory::getint (file);
	printf("Height of %s: %lu\n", filename, height);

	// calculate the size (assuming 24 bits or 3 bytes per pixel).
	size = width * height * 3;

	// read the planes
	planes = ImageFactory::getshort(file);
	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return NULL;
	}

	// read the bpp
	bpp = ImageFactory::getshort(file);
	if (bpp != 24)
	{
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return NULL;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	// read the data.
	printf("%d\n", size);
	ubyte* data = (ubyte*)malloc(size);
	if (data == NULL)
	{
		printf("Error allocating memory for color-corrected image data");
		return NULL;
	}

	if ((i = fread(data, size, 1, file)) != 1)
	{
		printf("Error reading image data from %s.\n", filename);
		return NULL;
	}

	for (i=0;i<size;i+=3)	// reverse all of the colors. (bgr -> rgb)
	{
		temp = data[i];
		data[i] = data[i+2];
		data[i+2] = temp;
	}

	// we're done.
	return new RawImage(width, height, false, data);
}

RawImage* ImageFactory::loadTGA(const char* filename)
{
	TextureInfo tex;
	LoadTGA(&tex, filename);
	
	return new RawImage(tex.width, tex.height, tex.type == GL_RGBA, tex.imageData);
}

RawImage* ImageFactory::loadPNG(const char *filename)
{		
	int outWidth, outHeight;
	bool outHasAlpha;
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;

    if ((fp = fopen(filename, "rb")) == NULL)
        return false;

    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);

    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }

    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }

    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }

    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);

    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

    outWidth = width;
    outHeight = height;
    switch (color_type) {
        case PNG_COLOR_TYPE_RGBA:
            outHasAlpha = true;
            break;
        case PNG_COLOR_TYPE_RGB:
            outHasAlpha = false;
            break;
        default:
            printf("Color type %d not supported.", color_type);
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
            return false;
    }
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    //*outData = (unsigned char*) malloc(row_bytes * outHeight);
	GLubyte *outData = (unsigned char*) malloc(row_bytes * outHeight);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }

    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    /* Close the file */
    fclose(fp);

	
    /* That's it */
    return new RawImage(outWidth, outHeight, outHasAlpha, outData);
}