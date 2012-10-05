/*
 * SoundFactory.hpp
 *
 *  Created on: Sep 1, 2012
 *      Author: Nisheeth
 */

#pragma once


#include <al/al.h>
#include <vorbis/vorbisfile.h>
#include <iostream>
#include <vector>
#include "LogManager.hpp"

class SoundFactory
{
public:
	static bool LoadOgg(const char *file, std::vector<char> &buffer, ALenum &format, ALsizei &freq);	
};
