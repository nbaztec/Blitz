/*
 * RawImage.hpp
 *
 *  Created on: Sep 2, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <cstdio>

class RawImage
{
public:

	unsigned long _width;
	unsigned long _height;
	bool _alpha;
	unsigned char *_data;

public:
	RawImage(const unsigned long &width, const unsigned long &height, const bool &hasAlpha, unsigned char *data)
	{
		this->_width = width;
		this->_height = height;
		this->_alpha = hasAlpha;
		this->_data = data;
	}

	inline unsigned long getWidth() const
	{
		return this->_width;
	}

	inline unsigned long getHeight() const
	{
		return this->_height;
	}
	inline bool hasAlpha() const
	{
		return this->_alpha;
	}

	inline unsigned char* getData() const
	{
		return this->_data;
	}


	virtual ~RawImage(void)
	{
		if(this->_data)
		{
			free(this->_data);
		}
	}
};